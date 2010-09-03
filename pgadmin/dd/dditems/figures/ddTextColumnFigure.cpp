//////////////////	////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddTextColumnFigure.cpp - 
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/numdlg.h>

// App headers
#include "dd/dditems/figures/ddTextColumnFigure.h"
#include "dd/dditems/tools/ddColumnTextTool.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"
#include "dd/draw/main/ddDrawingView.h"
#include "dd/dditems/figures/ddTableFigure.h"

//DD-TODO: Add composite column functionality by addin subcolumn for
//         composite types, but care: composite types can be recursive (using inside other composite types)

ddTextColumnFigure::ddTextColumnFigure(wxString& columnName, ddDataType dataType, ddColumnFigure *owner):
ddSimpleTextFigure(columnName)
{
	columnType = dataType;
	this->setEditable(true);
	enablePopUp();
	ownerColumn = owner;
	showDataType = true;
	recalculateDisplayBox();
	n=-1;
	m=-1;
}

ddTextColumnFigure::~ddTextColumnFigure()
{
}

wxString& ddTextColumnFigure::getText(bool extended)
{
	if(showDataType && extended)
	{
		wxString ddType = dataTypes(true)[columnType];
		if(columnType==dt_varchar && n>0)
		{
			ddType.Truncate(ddType.Find(wxT("(")));
			ddType+=wxString::Format(wxT("(%d)"),n);
		}
		out = wxString( ddSimpleTextFigure::getText() + wxString(wxT(" : ")) + ddType );
		return  out;
	}
	else
	{
		return ddSimpleTextFigure::getText();
	}
}

//event ID must match enum ddDataType!!! this event was created on view
void ddTextColumnFigure::OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view)
{
	wxTextEntryDialog *nameDialog=NULL;
	wxString tmpString;
	int answer;
	n=-1;
	m=-1;

	switch(event.GetId())
	{
		case MNU_DDADDCOLUMN:
            tmpString=wxString(wxT("NewColumn"));
            getOwnerColumn()->getOwnerTable()->addColumn(new ddColumnFigure(tmpString,getOwnerColumn()->getOwnerTable()));
            break;
		case MNU_DELCOLUMN:
            answer = wxMessageBox(wxT("Delete column: ") + getText(true) + wxT("?"), wxT("Confirm"),wxYES_NO, view);
            if (answer == wxYES)
                getOwnerColumn()->getOwnerTable()->removeColumn(getOwnerColumn());
            break;
		case MNU_RENAMECOLUMN:
            nameDialog = new wxTextEntryDialog(view,wxT("Input column name"),wxT("Rename Column"),getText());   //DD-TODO: change for dialog like in option 17
            nameDialog->ShowModal();
            setText(nameDialog->GetValue());
            delete nameDialog;
            break;
		case MNU_NOTNULL:
            if(getOwnerColumn()->isNotNull())
                getOwnerColumn()->setColumnOption(null);
            else
                getOwnerColumn()->setColumnOption(notnull);
            break;
		case MNU_PKEY:
            if(getOwnerColumn()->isPrimaryKey())
            {
                getOwnerColumn()->setColumnKind(none);
            }
            else
            {	
                getOwnerColumn()->setColumnKind(pk);
                getOwnerColumn()->setColumnOption(notnull);
            }
            break;
		case MNU_UKEY:
            getOwnerColumn()->setColumnKind(uk,view);
            break;
		case MNU_TYPESERIAL:
            columnType = dt_serial;
            break;
		case MNU_TYPEBOOLEAN:
            columnType = dt_boolean;
            break;
		case MNU_TYPEINTEGER:
			columnType = dt_integer;
            break;
		case MNU_TYPEMONEY:
            columnType = dt_money;
            break;
		case MNU_TYPEVARCHAR:
            columnType = dt_varchar;
            n=wxGetNumberFromUser(wxT("Varchar Size"),wxT("Input a Valid Size for Varchar datatype"),wxT("Varchar Size"),1,0,255,view);
            break;
		case MNU_TYPEOTHER:
            //DD-TODO: Add all types, improve and separate from quick access types
            columnType = (ddDataType) wxGetSingleChoiceIndex(wxT("Select column datatype"),wxT("Column Datatypes"),dataTypes(true),view);
            break;
		case MNU_TYPEPKEY_CONSTRAINTNAME:
            tmpString=wxGetTextFromUser(wxT("Change name of Primary Key constraint:"),getOwnerColumn()->getOwnerTable()->getPkConstraintName(),getOwnerColumn()->getOwnerTable()->getPkConstraintName(),view);
            if(tmpString.length()>0)
                getOwnerColumn()->getOwnerTable()->setPkConstraintName(tmpString);
            break;
		case MNU_TYPEUKEY_CONSTRAINTNAME:
            answer = wxGetSingleChoiceIndex(wxT("Select Unique Key constraint to edit name"),wxT("Select Unique Constraint to edit name:"),getOwnerColumn()->getOwnerTable()->getUkConstraintsNames(),view);
            if(answer>=0)
            {
                tmpString=wxGetTextFromUser(wxT("Change name of Unique Key constraint:"),getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Item(answer),getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Item(answer),view);
                if(tmpString.length()>0)
                    getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Item(answer)=tmpString;
            }
            break;
		case MNU_DELTABLE:
            answer = wxMessageBox(wxT("Delete Table: ") + getOwnerColumn()->getOwnerTable()->getTableName() + wxT("?"), wxT("Confirm"),wxYES_NO, view);
            if (answer == wxYES)
            {
                ddTableFigure *table = getOwnerColumn()->getOwnerTable();	
                //unselect table
                if(view->isFigureSelected(table))
                {
                    view->removeFromSelection(table);
                }
                //drop foreign keys with this table as origin or destination
                table->processDeleteAlert(view);
                //drop table
                view->remove(table);
                if(table)
                {
                    delete table;
                }						
            }
            break;
	}
}

void ddTextColumnFigure::createMenu(wxMenu &mnu)
{
    wxMenu *submenu;
    wxMenuItem *item;
    
    mnu.Append(MNU_DDADDCOLUMN, _("Add a column..."));
	item = mnu.Append(MNU_DELCOLUMN, _("Delete the selected column..."));
    if(getOwnerColumn()->isForeignKey())
        item->Enable(false);
    mnu.Append(MNU_RENAMECOLUMN, _("Rename the selected column..."));
    mnu.AppendSeparator();
	item = mnu.AppendCheckItem(MNU_NOTNULL, _("Not NULL constraint"));
    if(getOwnerColumn()->isNotNull())
        item->Check(true);
    if(getOwnerColumn()->isForeignKey())
        item->Enable(false);
    mnu.AppendSeparator();
	item = mnu.AppendCheckItem(MNU_PKEY, _("Primary Key"));
    if(getOwnerColumn()->isPrimaryKey())
        item->Check(true);
    if(getOwnerColumn()->isForeignKey())	
        item->Enable(false);
	item = mnu.AppendCheckItem(MNU_UKEY, _("Unique Key"));
    if(getOwnerColumn()->isUniqueKey())
        item->Check(true);
    mnu.AppendSeparator();
    submenu = new wxMenu(_("Column datatype")); 
	item = mnu.AppendSubMenu(submenu, _("Column datatype"));
    if(getOwnerColumn()->isForeignKey())	
        item->Enable(false);
	item = submenu->AppendCheckItem(MNU_TYPESERIAL, _("Serial"));
    item->Check(columnType==dt_bigint);
	item = submenu->AppendCheckItem(MNU_TYPEBOOLEAN, _("Boolean"));
    item->Check(columnType==dt_boolean);
	item = submenu->AppendCheckItem(MNU_TYPEINTEGER, _("Integer"));
    item->Check(columnType==dt_integer);
	item = submenu->AppendCheckItem(MNU_TYPEMONEY, _("Money"));
    item->Check(columnType==dt_money);
    item = submenu->AppendCheckItem(MNU_TYPEVARCHAR, _("Varchar()"));
    item->Check(columnType==dt_varchar);
	item = submenu->Append(MNU_TYPEOTHER, _("Choose another datatype..."));
    mnu.AppendSeparator();
	mnu.Append(MNU_TYPEPKEY_CONSTRAINTNAME, _("Primary Key Constraint name..."));
	mnu.Append(MNU_TYPEUKEY_CONSTRAINTNAME, _("Unique Key Constraint name..."));
    mnu.AppendSeparator();
	mnu.Append(MNU_DELTABLE, _("Delete table..."));
};

wxArrayString& ddTextColumnFigure::dataTypes(bool full)
{
    datatypes.Clear();
    datatypes.Add(wxT("Not Defined"));
    datatypes.Add(wxT("Serial"));
    datatypes.Add(wxT("Boolean"));
    datatypes.Add(wxT("Integer"));
    datatypes.Add(wxT("Money"));
    datatypes.Add(wxT("Varchar(1)"));
    if (full)
    {
        //not fast access datatypes
        datatypes.Add(wxT("Bigint"));
        datatypes.Add(wxT("Bit(1)"));
        datatypes.Add(wxT("Bytea"));
        datatypes.Add(wxT("Char(n)"));
        datatypes.Add(wxT("Cidr"));
        datatypes.Add(wxT("Circle"));
        datatypes.Add(wxT("Date"));
        datatypes.Add(wxT("Double Precision"));
        datatypes.Add(wxT("Inet"));
        datatypes.Add(wxT("Interval(1)"));
        datatypes.Add(wxT("Line"));
        datatypes.Add(wxT("LSeg"));
        datatypes.Add(wxT("MacAddr"));
        datatypes.Add(wxT("Numeric(1,1)"));
        datatypes.Add(wxT("Path"));
        datatypes.Add(wxT("Point"));
        datatypes.Add(wxT("Polygon"));
        datatypes.Add(wxT("Real"));
        datatypes.Add(wxT("Smallint"));
        datatypes.Add(wxT("Text"));
        datatypes.Add(wxT("Time"));
        datatypes.Add(wxT("Timestamp"));
        datatypes.Add(wxT("Varbit(1)"));
    }
	return datatypes;
}

//DD-TODO: when a event onfigurechange exists, replace this hack with that event
//Hack to allow column text to submit new size of text signal to tablefigure and then recalculate displaybox
void ddTextColumnFigure::setText(wxString textString)
{
	ddSimpleTextFigure::setText(textString);
	if(ownerColumn)
	{
		ownerColumn->displayBoxUpdate();
		ownerColumn->getOwnerTable()->updateTableSize();
	}
}

ddColumnFigure* ddTextColumnFigure::getOwnerColumn()
{
	return ownerColumn;
}

void ddTextColumnFigure::setOwnerColumn(ddColumnFigure *column)
{
	ownerColumn = column;
}

void ddTextColumnFigure::setShowDataType(bool value)
{
	showDataType = value;
}

ddITool* ddTextColumnFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return textEditable ? new ddColumnTextTool(editor,this,defaultTool) : defaultTool;
}

int ddTextColumnFigure::getTextWidth()
{
	int w,h;
	getFontMetrics(w,h);
	return w;
}

int ddTextColumnFigure::getTextHeight()
{
	int w,h;
	getFontMetrics(w,h);
	return h;
}

ddDataType ddTextColumnFigure::getDataType()
{
	return columnType;
}

void ddTextColumnFigure::setDataType(ddDataType type)
{
	columnType=type;
}
