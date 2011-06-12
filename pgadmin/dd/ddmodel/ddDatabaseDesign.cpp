//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDatabaseDesign.cpp - Manages all design related info and contains all model(s) and tables.
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/ddmodel/ddDatabaseDesign.h"
#include "dd/wxhotdraw/tools/wxhdSelectionTool.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/ddmodel/ddDrawingEditor.h"


ddDatabaseDesign::ddDatabaseDesign(wxWindow *parent)
{
	draw = new ddDrawingEditor(parent, this);
	tool = new wxhdSelectionTool(draw);
	draw->setTool(tool);
}

ddDatabaseDesign::~ddDatabaseDesign()
{
	if(draw)
		delete draw;
}

wxhdDrawingEditor* ddDatabaseDesign::getEditor()
{
	return draw;
}

wxhdDrawingView* ddDatabaseDesign::getView()
{
	return draw->view();
}

void ddDatabaseDesign::addTable(wxhdIFigure *figure)
{
	draw->view()->add(figure);
}

void ddDatabaseDesign::removeTable(wxhdIFigure *figure)
{
	draw->view()->remove(figure);
}

void ddDatabaseDesign::removeSelectedObjects(int kind)
{
    int answer;
	wxhdIteratorBase *iterator=draw->model()->figuresEnumerator();
    wxhdArrayCollection itemsToBeDeleted;
	wxhdIFigure *tmp;
    ddTableFigure *table;
    while(iterator->HasNext())
    {
        tmp=(wxhdIFigure *)iterator->Next();
        if (tmp->isSelected())
        {
            if(kind == 0 || tmp->getKindId() == kind)
            {
                itemsToBeDeleted.addItem(tmp);
            }
        }
	 }
	delete iterator;
    
    if (itemsToBeDeleted.count() == 1)
    {
		tmp = (wxhdIFigure*) itemsToBeDeleted.getItemAt(0);
        table = (ddTableFigure *)tmp;	
        answer = wxMessageBox(_("Are you sure you wish to delete table ") + table->getTableName() + wxT("?"), _("Delete table?"), wxYES_NO|wxNO_DEFAULT);
    }
    else if (itemsToBeDeleted.count() > 1)
    {
        answer = wxMessageBox(
          wxString::Format(_("Are you sure you wish to delete %d tables?"), itemsToBeDeleted.count()),
          _("Delete table?"), wxYES_NO|wxNO_DEFAULT);
    }

    if (answer == wxYES)
    {
        while(itemsToBeDeleted.count()>0)
        {
            tmp = (wxhdIFigure*) itemsToBeDeleted.getItemAt(0);
            table = (ddTableFigure *)tmp;	
            draw->view()->removeFromSelection(table);
            table->processDeleteAlert(draw->view());
            draw->view()->remove(table);
            if(table)
                delete table;
            itemsToBeDeleted.removeItemAt(0);
        }
	}
    else
    {
        while(itemsToBeDeleted.count()>0)
            itemsToBeDeleted.removeItemAt(0);
    }
}

void ddDatabaseDesign::setTool(wxhdITool* tool)
{
	draw->setTool(tool);
}

void ddDatabaseDesign::refreshDraw()
{
	draw->view()->Refresh();
}

void ddDatabaseDesign::eraseModel()
{
	draw->view()->removeAll();
}

wxString ddDatabaseDesign::generateModel()
{
	wxString out;
	wxhdIteratorBase *iterator=draw->model()->figuresEnumerator();
	wxhdIFigure *tmp;
	ddTableFigure *table;
	while(iterator->HasNext())
    {
		tmp=(wxhdIFigure *)iterator->Next();
		if(tmp->getKindId() == ddTableFig)
		{
			out+=wxT(" \n");
			table=(ddTableFigure*)tmp;
			out+=wxT("--\n-- ");
            out+=_("Generating SQL for table: ");
			out+=table->getTableName();
			out+=wxT(" \n--\n");
			out+=table->generateSQL();
			out+=wxT(" \n");
			out+=wxT(" \n");
		}
	 }
	delete iterator;
	return out;
}

wxString ddDatabaseDesign::getNewTableName()
{
	wxString out,tmpStr;
	wxhdIteratorBase *iterator=draw->model()->figuresEnumerator();
	wxhdIFigure *tmp;
	ddTableFigure *table;
	int indx=0;
	bool repeat;
	do
    {
		repeat=false;
		iterator->ResetIterator();
		while(iterator->HasNext())
        {
			tmp=(wxhdIFigure *)iterator->Next();
			if(tmp->getKindId() == ddTableFig)
			{
				table=(ddTableFigure*)tmp;
				if(indx==0)
					tmpStr=_("NewTable");
				else
					tmpStr=wxString::Format(_("NewTable%d"),indx);

				if(table->getTableName().Contains(tmpStr))
				{
					indx++;
					repeat=true;
					break;
				}
			}
		 }
	} while(repeat);
	delete iterator;
	out=wxString::Format(_("NewTable%d"),indx);
	return out;
}

ddTableFigure* ddDatabaseDesign::getSelectedTable()
{
	wxhdIteratorBase *iterator=draw->model()->figuresEnumerator();
	wxhdIFigure *tmp;
    ddTableFigure *table = 0L;
    while(iterator->HasNext())
    {
        tmp=(wxhdIFigure *)iterator->Next();
        if (tmp->isSelected() && tmp->getKindId() == ddTableFig)
            table = (ddTableFigure *)tmp;
	 }
	delete iterator;
    return table;
}

bool ddDatabaseDesign::containsTable(wxString tableName)
{
	bool out=false;
	wxhdIteratorBase *iterator=draw->model()->figuresEnumerator();
	wxhdIFigure *tmp;
	ddTableFigure *table;
	while(iterator->HasNext())
    {
		tmp=(wxhdIFigure *)iterator->Next();
		if(tmp->getKindId() == ddTableFig)
		{
			table=(ddTableFigure*)tmp;
			if(table->getTableName().Contains(tableName))
			{
				out=true;
			}
		}
	}
	delete iterator;
	return out;
}
