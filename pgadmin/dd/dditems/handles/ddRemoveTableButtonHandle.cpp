//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRemoveTableButtonHandle.cpp - A handle for a table figure that allow to delete it
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/handles/ddRemoveTableButtonHandle.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/wxhotdraw/main/wxhdDrawingView.h"
#include "dd/wxhotdraw/utilities/wxhdRemoveDeleteDialog.h"

//Images
#include "images/ddDeleteTableCursor.pngc"

ddRemoveTableButtonHandle::ddRemoveTableButtonHandle(wxhdIFigure *owner, wxhdILocator *buttonLocator , wxBitmap &buttonImage, wxSize &size):
	wxhdButtonHandle(owner, buttonLocator, buttonImage, size)
{
	handleCursorImage = wxBitmap(*ddDeleteTableCursor_png_img).ConvertToImage();
	handleCursor = wxCursor(handleCursorImage);
}

ddRemoveTableButtonHandle::~ddRemoveTableButtonHandle()
{
}

void ddRemoveTableButtonHandle::invokeStart(wxhdMouseEvent &event, wxhdDrawingView *view)
{
}

void ddRemoveTableButtonHandle::invokeStep(wxhdMouseEvent &event, wxhdDrawingView *view)
{
}

void ddRemoveTableButtonHandle::invokeEnd(wxhdMouseEvent &event, wxhdDrawingView *view)
{
//666 use here remOrDelSelFigures()
	if(view && getOwner())
	{
		ddTableFigure *table = (ddTableFigure *) getOwner();
		wxhdRemoveDeleteDialog dialog(_("Are you sure you wish to delete table ") + table->getTableName() + wxT("?"), _("Delete table?"), view);
		int answer = dialog.ShowModal();
		if (answer == DD_DELETE)
		{
			/* 666
			//unselect table
			if(view->getDrawing()->isFigureSelected(table))
			{
				view->getDrawing()->removeFromSelection(table);
			}
			//drop foreign keys with this table as origin or destination
			table->processDeleteAlert(view->getDrawing());
			//drop table
			view->getDrawing()->remove(table);
			if(table)
			{
				delete table;
			}
			*/
			ddDrawingEditor *editor = (ddDrawingEditor*) view->editor();
			//Unselect table at all diagrams
			editor->removeFromAllSelections(table);
			//Drop foreign keys with this table as origin or destination
			table->processDeleteAlert(view->getDrawing());
			//Drop table
			editor->deleteModelFigure(table);
			editor->getDesign()->refreshBrowser();
		}
		else if(answer == DD_REMOVE)
		{
			ddDrawingEditor *editor = (ddDrawingEditor*) view->editor();
			editor->getExistingDiagram(view->getIdx())->removeFromSelection(table); 
			editor->getExistingDiagram(view->getIdx())->remove(table);
		}

	}
}

wxCursor ddRemoveTableButtonHandle::createCursor()
{
	return handleCursor;
}
