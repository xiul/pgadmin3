//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawingView.cpp - Main canvas where all tables and relationships are drawn
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/ddmodel/ddDrawingView.h"
#include "dd/wxhotdraw/utilities/wxhdArrayCollection.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"
#include "dd/dditems/utilities/ddDataType.h"

ddDrawingView::ddDrawingView(wxWindow *ddParent, wxhdDrawingEditor *editor ,wxSize size, wxhdDrawing *drawing)
:wxhdDrawingView(ddParent,editor,size,drawing)
{
}

void ddDrawingView::deleteSelectedFigures()
{
	wxhdIFigure *tmp;
    ddTableFigure *table;
	int answer;
	int numbTables = 0;

    if (selection->count() == 1)
    {
		tmp = (wxhdIFigure*) selection->getItemAt(0);
		if(tmp->getKindId() == DDTABLEFIGURE)
		{
			numbTables = 1;
			table = (ddTableFigure *)tmp;	
			answer = wxMessageBox(_("Are you sure you wish to delete table ") + table->getTableName() + wxT("?"), _("Delete table?"), wxYES_NO|wxNO_DEFAULT);
		}
    }
    else if (selection->count() > 1)
    {
		numbTables = 0;
		wxhdIteratorBase *iterator=selection->createIterator();
		while(iterator->HasNext())
		{
		 tmp=(wxhdIFigure *)iterator->Next();
		 if(tmp->getKindId() == DDTABLEFIGURE)
			numbTables++;
		}
		delete iterator;

		answer = wxMessageBox(
          wxString::Format(_("Are you sure you wish to delete %d tables?"), numbTables),
          _("Delete tables?"), wxYES_NO|wxNO_DEFAULT);
    }

    if (answer == wxYES)
    {
        while(numbTables > 0)
        {
			tmp = (wxhdIFigure*) selection->getItemAt(0);
			if(tmp->getKindId() == DDTABLEFIGURE)
			{
				table = (ddTableFigure *)tmp;	
				removeFromSelection(table);
				table->processDeleteAlert(this);
				remove(table);
				if(table)
					delete table;
				numbTables--;
			}
			else
			{
				removeFromSelection(tmp); //isn't a tables is probably a relationship
			}
        }
		clearSelection();  //after delete all items all relationships remains at selection and should be removed
	}
}