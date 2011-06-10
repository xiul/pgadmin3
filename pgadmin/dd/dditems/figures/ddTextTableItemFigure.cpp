//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddTextTableItemFigure.cpp - Draw a column inside a table
//
//////////////////////////////////////////////////////////////////////////// 

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/numdlg.h>

// App headers
#include "dd/dditems/figures/ddTextTableItemFigure.h"
#include "dd/dditems/figures/ddRelationshipItem.h"
#include "dd/dditems/tools/ddColumnTextTool.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/wxhotdraw/figures/ddSimpleTextFigure.h"
#include "dd/wxhotdraw/main/ddDrawingView.h"
#include "dd/dditems/figures/ddTableFigure.h"

ddTextTableItemFigure::ddTextTableItemFigure(wxString& columnName, ddDataType dataType, ddColumnFigure *owner):
ddSimpleTextFigure(columnName)
{
	ownerTable = NULL;
	oneTimeNoAlias = false;
	columnType = dataType;
	this->setEditable(true);
	enablePopUp();
	ownerColumn = owner;
	showDataType = true;
	showAlias=false;
	recalculateDisplayBox();
	precision=-1;
}

ddTextTableItemFigure::~ddTextTableItemFigure()
{
}

void ddTextTableItemFigure::displayBoxUpdate()
{
	recalculateDisplayBox();
}

void ddTextTableItemFigure::setOwnerTable(ddTableFigure *table)
{
	ownerTable = table;
}

wxString& ddTextTableItemFigure::getText(bool extended)
{
	if(showDataType && extended && getOwnerColumn())
	{
		wxString ddType = dataTypes()[getDataType()];   //Should use getDataType() & getPrecision(), because when column is fk, type is not taken from this column, instead from original column (source of fk)
		if(columnType==dt_varchar && getPrecision()>0)
		{
			ddType.Truncate(ddType.Find(wxT("(")));
			ddType+=wxString::Format(wxT("(%d)"),getPrecision());
		}
		out = wxString( ddSimpleTextFigure::getText() + wxString(wxT(" : ")) + ddType );
		return  out;
	}
	else if( showAlias && getOwnerColumn()==NULL )
	{
		if(!oneTimeNoAlias)
			out = wxString( ddSimpleTextFigure::getText() + wxString(wxT(" ( ")) + colAlias + wxString(wxT(" ) ")) );
		else
		{
			out = wxString( ddSimpleTextFigure::getText() );
			oneTimeNoAlias = false;
		}
		return out;
	}
	else 
	{
		return ddSimpleTextFigure::getText();
	}
}

wxString ddTextTableItemFigure::getType()
{
    wxString ddType = dataTypes()[columnType];
    if(columnType==dt_varchar && getPrecision()>0)
    {
        ddType.Truncate(ddType.Find(wxT("(")));
        ddType+=wxString::Format(wxT("(%d)"),getPrecision());
    }
    return ddType;
}

//WARNING: event ID must match enum ddDataType!!! this event was created on view
void ddTextTableItemFigure::OnGenericPopupClick(wxCommandEvent& event, ddDrawingView *view)
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
		case MNU_AUTONAMCOLUMN:
				getOwnerColumn()->activateGenFkName(); 
				getOwnerColumn()->getFkSource()->syncAutoFkName();
			break;
		case MNU_RENAMECOLUMN:
				nameDialog = new wxTextEntryDialog(view, wxT("New column name"), wxT("Rename Column"), getText());
				nameDialog->ShowModal();
				if(getOwnerColumn()->isForeignKey()) //after a manual user column rename, deactivated automatic generation of fk name.
					getOwnerColumn()->deactivateGenFkName();
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
            setDataType(dt_serial);  //Should use setDataType always to set this value to allow fk to work flawlessly
            recalculateDisplayBox();
            getOwnerColumn()->displayBoxUpdate();
            getOwnerColumn()->getOwnerTable()->updateTableSize();
            break;
		case MNU_TYPEBOOLEAN:
            setDataType(dt_boolean);
            recalculateDisplayBox();
            getOwnerColumn()->displayBoxUpdate();
            getOwnerColumn()->getOwnerTable()->updateTableSize();
            break;
		case MNU_TYPEINTEGER:
			setDataType(dt_integer);
            recalculateDisplayBox();
            getOwnerColumn()->displayBoxUpdate();
            getOwnerColumn()->getOwnerTable()->updateTableSize();
            break;
		case MNU_TYPEMONEY:
            setDataType(dt_money);
            recalculateDisplayBox();
            getOwnerColumn()->displayBoxUpdate();
            getOwnerColumn()->getOwnerTable()->updateTableSize();
            break;
		case MNU_TYPEVARCHAR:
            setDataType(dt_varchar);
            tmpprecision = wxGetNumberFromUser(_("Varchar size"),
                _("Size for varchar datatype"),
                _("Varchar size"),
                getPrecision(), 0, 255, view);
            if (tmpprecision > 0)
                setPrecision(tmpprecision);
            recalculateDisplayBox();
            getOwnerColumn()->displayBoxUpdate();
            getOwnerColumn()->getOwnerTable()->updateTableSize();
            break;
		case MNU_TYPEOTHER:
            setDataType((ddDataType) wxGetSingleChoiceIndex(wxT("New column datatype"),wxT("Column Datatypes"),dataTypes(),view));
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
                //Unselect table
                if(view->isFigureSelected(table))
                {
                    view->removeFromSelection(table);
                }
                //Drop foreign keys with this table as origin or destination
                table->processDeleteAlert(view);
                //Drop table
                view->remove(table);
                if(table)
                {
                    delete table;
                }						
            }
            break;
	}
}

void ddTextTableItemFigure::createMenu(wxMenu &mnu)
{
    wxMenu *submenu;
    wxMenuItem *item;
    
    mnu.Append(MNU_DDADDCOLUMN, _("Add a column..."));
	item = mnu.Append(MNU_DELCOLUMN, _("Delete the selected column..."));
    if(getOwnerColumn()->isForeignKey())
        item->Enable(false);
    mnu.Append(MNU_RENAMECOLUMN, _("Rename the selected column..."));
	if(getOwnerColumn()->isForeignKey() && !getOwnerColumn()->isFkNameGenerated())
		mnu.Append(MNU_AUTONAMCOLUMN, _("Activate fk auto-naming..."));
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


const wxArrayString ddTextTableItemFigure::dataTypes()
{
	if(ddDatatypes.IsEmpty())
	{
	//Fast access ddDatatypes
		ddDatatypes.Add(wxT("ANY"));
		ddDatatypes.Add(wxT("serial"));
		ddDatatypes.Add(wxT("boolean"));
		ddDatatypes.Add(wxT("integer"));
		ddDatatypes.Add(wxT("money"));
		ddDatatypes.Add(wxT("varchar(1)"));
	//Normal access ddDatatypes
			ddDatatypes.Add(wxT("bigint"));
			ddDatatypes.Add(wxT("bit(1)"));
			ddDatatypes.Add(wxT("bytea"));
			ddDatatypes.Add(wxT("char(n)"));
			ddDatatypes.Add(wxT("cidr"));
			ddDatatypes.Add(wxT("circle"));
			ddDatatypes.Add(wxT("date"));
			ddDatatypes.Add(wxT("double precision"));
			ddDatatypes.Add(wxT("inet"));
			ddDatatypes.Add(wxT("interval(1)"));
			ddDatatypes.Add(wxT("line"));
			ddDatatypes.Add(wxT("lseg"));
			ddDatatypes.Add(wxT("macaddr"));
			ddDatatypes.Add(wxT("numeric(1,1)"));
			ddDatatypes.Add(wxT("path"));
			ddDatatypes.Add(wxT("point"));
			ddDatatypes.Add(wxT("polygon"));
			ddDatatypes.Add(wxT("real"));
			ddDatatypes.Add(wxT("smallint"));
			ddDatatypes.Add(wxT("text"));
			ddDatatypes.Add(wxT("time"));
			ddDatatypes.Add(wxT("timestamp"));
			ddDatatypes.Add(wxT("varbit(1)"));
	}
	return ddDatatypes;
}

void ddTextTableItemFigure::setText(wxString textString)
{
	ddSimpleTextFigure::setText(textString);
	
	//Hack to allow column text to submit new size of text signal to tablefigure 
	//and then recalculate displaybox. Helps with fk autorenaming too.
	if(ownerColumn)
	{
		ownerColumn->displayBoxUpdate();
		ownerColumn->getOwnerTable()->updateTableSize();
		ownerColumn->getOwnerTable()->updateFkObservers();
	}
}

wxString ddTextTableItemFigure::getAlias()
{
	return colAlias;
}

//Activate use of alias or short names at ddtextTableItems like TableNames [Columns don' use it]
void ddTextTableItemFigure::setAlias(wxString alias)
{
	if(alias.length()<=0 || alias.length()>3 )
	{
		showAlias=false;
		colAlias = wxEmptyString;
	}
	else
	{
		showAlias=true;
		colAlias = alias;
	}
	recalculateDisplayBox();
	ownerTable->updateFkObservers(); //Only triggered by a tableName item [Not a column]
	ownerTable->updateTableSize();
}

void ddTextTableItemFigure::setOneTimeNoAlias()
{
	oneTimeNoAlias = true;
}

ddColumnFigure* ddTextTableItemFigure::getOwnerColumn()
{
	return ownerColumn;
}

void ddTextTableItemFigure::setOwnerColumn(ddColumnFigure *column)
{
	ownerColumn = column;
}

void ddTextTableItemFigure::setShowDataType(bool value)
{
	showDataType = value;
}

ddITool* ddTextTableItemFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	if(getOwnerColumn())
	{
		return textEditable ? new ddColumnTextTool(editor,this,defaultTool,false,wxT("New Column Name"),wxT("Rename Column")) : defaultTool;
	}
	else
	{
		setOneTimeNoAlias();
		return textEditable ? new ddColumnTextTool(editor,this,defaultTool,false,wxT("New Table Name"),wxT("Rename Table")) : defaultTool;
	}
}

int ddTextTableItemFigure::getTextWidth()
{
	int w,h;
	getFontMetrics(w,h);
	return w;
}

int ddTextTableItemFigure::getTextHeight()
{
	int w,h;
	getFontMetrics(w,h);
	return h;
}

ddDataType ddTextTableItemFigure::getDataType()
{
	if(!getOwnerColumn()->isForeignKey())
		return columnType;
	else
	{
		columnType = getOwnerColumn()->getFkSource()->original->getDataType();
		return columnType;
	}
}

void ddTextTableItemFigure::setDataType(ddDataType type)
{
	columnType=type;
	ownerColumn->getOwnerTable()->updateSizeOfObservers();
}

int ddTextTableItemFigure::getPrecision()
{
	if(getOwnerColumn()->isForeignKey())
	{
		precision = getOwnerColumn()->getFkSource()->original->getPrecision();
		return precision;
	}
	else
	{
		return precision;
	}
}

void ddTextTableItemFigure::setPrecision(int value)
{
	if(!getOwnerColumn()->isForeignKey())
	{
		precision = value;
		ownerColumn->getOwnerTable()->updateSizeOfObservers();
	}
}