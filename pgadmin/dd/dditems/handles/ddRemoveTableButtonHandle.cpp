//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRemoveTableButtonHandle.cpp 
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
#include "dd/draw/main/ddDrawingView.h"

//Images
#include "images/ddDeleteTableCursor.xpm"

ddRemoveTableButtonHandle::ddRemoveTableButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size):
ddButtonHandle(owner,buttonLocator,buttonImage,size)
{
	handleCursorImage = wxBitmap(ddDeleteTableCursor_xpm).ConvertToImage();
    handleCursor=wxCursor(handleCursorImage);
}

ddRemoveTableButtonHandle::~ddRemoveTableButtonHandle()
{
}

void ddRemoveTableButtonHandle::invokeStart(ddMouseEvent &event, ddDrawingView *view)
{
}

void ddRemoveTableButtonHandle::invokeStep(ddMouseEvent &event, ddDrawingView *view)
{
}

void ddRemoveTableButtonHandle::invokeEnd(ddMouseEvent &event, ddDrawingView *view)
{

	if(view && getOwner())
	{
		ddTableFigure *table = (ddTableFigure*) getOwner();	
		int answer = wxMessageBox(_("Are you sure you wish to delete table ") + table->getTableName() + wxT("?"), _("Delete table?"), wxYES_NO|wxNO_DEFAULT, view);
		if (answer == wxYES)
		{
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
	}
}

wxCursor ddRemoveTableButtonHandle::createCursor()
{
	return handleCursor;
}
