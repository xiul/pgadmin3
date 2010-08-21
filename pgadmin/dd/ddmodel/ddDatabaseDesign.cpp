//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDatabaseDesign.cpp 
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/ddmodel/ddDatabaseDesign.h"
#include "dd/draw/tools/ddSelectionTool.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"


ddDatabaseDesign::ddDatabaseDesign(wxWindow *parent)
{
	draw = new ddDrawingEditor(parent);
	tool = new ddSelectionTool(draw);
	draw->setTool(tool);
}

ddDatabaseDesign::~ddDatabaseDesign()
{
	if(draw)
		delete draw;
}

ddDrawingEditor* ddDatabaseDesign::getEditor()
{
	return draw;
}

ddDrawingView* ddDatabaseDesign::getView()
{
	return draw->view();
}

void ddDatabaseDesign::addTable(ddIFigure *figure)
{
	draw->view()->add(figure);
}

void ddDatabaseDesign::removeTable(ddIFigure *figure)
{
	draw->view()->remove(figure);
}

void ddDatabaseDesign::setTool(ddITool* tool)
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
	ddIteratorBase *iterator=draw->model()->figuresEnumerator();
	ddIFigure *tmp;
	ddTableFigure *table;
	while(iterator->HasNext()){
		tmp=(ddIFigure *)iterator->Next();
		if(tmp->getKindId()==100)
		{
			out+=wxT(" \n");
			table=(ddTableFigure*)tmp;
			out+=wxT("--\n-- ")+_("Generating SQL for table: ");
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
	ddIteratorBase *iterator=draw->model()->figuresEnumerator();
	ddIFigure *tmp;
	ddTableFigure *table;
	int indx=0;
	bool repeat;
	do{
		repeat=false;
		iterator->ResetIterator();
		while(iterator->HasNext()){
			tmp=(ddIFigure *)iterator->Next();
			if(tmp->getKindId()==100)
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
	}while(repeat);
	delete iterator;
	out=wxString::Format(_("NewTable%d"),indx);
	return out;
}

bool ddDatabaseDesign::containsTable(wxString tableName)
{
	bool out=false;
	ddIteratorBase *iterator=draw->model()->figuresEnumerator();
	ddIFigure *tmp;
	ddTableFigure *table;
	while(iterator->HasNext()){
		tmp=(ddIFigure *)iterator->Next();
		if(tmp->getKindId()==100)
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
