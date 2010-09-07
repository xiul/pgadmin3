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
	precision=-1;
}

ddTextColumnFigure::~ddTextColumnFigure()
{
}

wxString& ddTextColumnFigure::getText(bool extended)
{
	if(showDataType && extended)
	{
		wxString ddType = dataTypes(true)[columnType];
		if(columnType==dt_varchar && precision>0)
		{
			ddType.Truncate(ddType.Find(wxT("(")));
			ddType+=wxString::Format(wxT("(%d)"),precision);
		}
		out = wxString( ddSimpleTextFigure::getText() + wxString(wxT(" : ")) + ddType );
		return  out;
	}
	else
	{
		return ddSimpleTextFigure::getText();
	}
}

wxString ddTextColumnFigure::getType()
{
    wxString ddType = dataTypes(true)[columnType];
    if(columnType==dt_varchar && precision>0)
    {
        ddType.Truncate(ddType.Find(wxT("(")));
        ddType+=wxString::Format(wxT("(%d)"),precision);
    }
    return ddType;
}

//event ID must match enum ddDataType!!! this event was created on view
void ddTextColumnFigure::OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view)
{
	wxTextEntryDialog *nameDialog=NULL;
	wxString tmpString;
	int answer;
    int tmpprecision;

	switch(event.GetId())
	{
		case MNU_DDADDCOLUMN:
            nameDialog = new wxTextEntryDialog(view, wxT("New column name"), wxT("Add a column"), wxT("NewColumn"));
            answer = nameDialog->ShowModal();
            if (answer == wxID_OK)
            {
                tmpString=nameDialog->GetValue();
                getOwnerColumn()->getOwnerTable()->addColumn(new ddColumnFigure(tmpString,getOwnerColumn()->getOwnerTable()));
            }
            delete nameDialog;
            break;
		case MNU_DELCOLUMN:
            answer = wxMessageBox(wxT("Are you sure you wish to delete column ") + getText(true) + wxT("?"), wxT("Delete column?"), wxYES_NO|wxNO_DEFAULT, view);
            if (answer == wxYES)
                getOwnerColumn()->getOwnerTable()->removeColumn(getOwnerColumn());
            break;
		case MNU_RENAMECOLUMN:
            nameDialog = new wxTextEntryDialog(view, wxT("New column name"), wxT("Rename Column"), getText());   //DD-TODO: change for dialog like in option 17
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
            recalculateDisplayBox();
            getOwnerColumn()->displayBoxUpdate();
            getOwnerColumn()->getOwnerTable()->updateTableSize();
            break;
		case MNU_TYPEBOOLEAN:
            columnType = dt_boolean;
            recalculateDisplayBox();
            getOwnerColumn()->displayBoxUpdate();
            getOwnerColumn()->getOwnerTable()->updateTableSize();
            break;
		case MNU_TYPEINTEGER:
			columnType = dt_integer;
            recalculateDisplayBox();
            getOwnerColumn()->displayBoxUpdate();
            getOwnerColumn()->getOwnerTable()->updateTableSize();
            break;
		case MNU_TYPEMONEY:
            columnType = dt_money;
            recalculateDisplayBox();
            getOwnerColumn()->displayBoxUpdate();
            getOwnerColumn()->getOwnerTable()->updateTableSize();
            break;
		case MNU_TYPEVARCHAR:
            columnType = dt_varchar;
            tmpprecision = wxGetNumberFromUser(_("Varchar size"),
                _("Size for varchar datatype"),
                _("Varchar size"),
                precision, 0, 255, view);
            if (tmpprecision > 0)
                precision = tmpprecision;
            recalculateDisplayBox();
            getOwnerColumn()->displayBoxUpdate();
            getOwnerColumn()->getOwnerTable()->updateTableSize();
            break;
		case MNU_TYPEOTHER:
            //DD-TODO: Add all types, improve and separate from quick access types
            columnType = (ddDataType) wxGetSingleChoiceIndex(wxT("New column datatype"),wxT("Column Datatypes"),dataTypes(true),view);
            recalculateDisplayBox();
            getOwnerColumn()->displayBoxUpdate();
            getOwnerColumn()->getOwnerTable()->updateTableSize();
            break;
		case MNU_TYPEPKEY_CONSTRAINTNAME:
            tmpString=wxGetTextFromUser(wxT("New name of primary key:"),getOwnerColumn()->getOwnerTable()->getPkConstraintName(),getOwnerColumn()->getOwnerTable()->getPkConstraintName(),view);
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
            answer = wxMessageBox(wxT("Are you sure you wish to delete table ") + getOwnerColumn()->getOwnerTable()->getTableName() + wxT("?"), wxT("Delete table?"), wxYES_NO|wxNO_DEFAULT, view);
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
	item = submenu->AppendCheckItem(MNU_TYPESERIAL, _("serial"));
    item->Check(columnType==dt_bigint);
	item = submenu->AppendCheckItem(MNU_TYPEBOOLEAN, _("boolean"));
    item->Check(columnType==dt_boolean);
	item = submenu->AppendCheckItem(MNU_TYPEINTEGER, _("integer"));
    item->Check(columnType==dt_integer);
	item = submenu->AppendCheckItem(MNU_TYPEMONEY, _("money"));
    item->Check(columnType==dt_money);
    item = submenu->AppendCheckItem(MNU_TYPEVARCHAR, _("varchar()"));
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
    datatypes.Add(wxT("ANY"));
    datatypes.Add(wxT("serial"));
    datatypes.Add(wxT("boolean"));
    datatypes.Add(wxT("integer"));
    datatypes.Add(wxT("money"));
    datatypes.Add(wxT("varchar(1)"));
    if (full)
    {
        //not fast access datatypes
        datatypes.Add(wxT("bigint"));
        datatypes.Add(wxT("bit(1)"));
        datatypes.Add(wxT("bytea"));
        datatypes.Add(wxT("char(n)"));
        datatypes.Add(wxT("cidr"));
        datatypes.Add(wxT("circle"));
        datatypes.Add(wxT("date"));
        datatypes.Add(wxT("double precision"));
        datatypes.Add(wxT("inet"));
        datatypes.Add(wxT("interval(1)"));
        datatypes.Add(wxT("line"));
        datatypes.Add(wxT("lseg"));
        datatypes.Add(wxT("macaddr"));
        datatypes.Add(wxT("numeric(1,1)"));
        datatypes.Add(wxT("path"));
        datatypes.Add(wxT("point"));
        datatypes.Add(wxT("polygon"));
        datatypes.Add(wxT("real"));
        datatypes.Add(wxT("smallint"));
        datatypes.Add(wxT("text"));
        datatypes.Add(wxT("time"));
        datatypes.Add(wxT("timestamp"));
        datatypes.Add(wxT("varbit(1)"));
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
