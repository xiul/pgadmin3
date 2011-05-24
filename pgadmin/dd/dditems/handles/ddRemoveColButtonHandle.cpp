//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRemoveColButtonHandle.cpp 
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/handles/ddRemoveColButtonHandle.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/utilities/ddDataType.h"

//Images
#include "images/ddRemoveColumnCursor.xpm"

ddRemoveColButtonHandle::ddRemoveColButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size):
ddButtonHandle(owner,buttonLocator,buttonImage,size)
{
	handleCursorImage = wxBitmap(ddRemoveColumnCursor_xpm).ConvertToImage();
    handleCursor=wxCursor(handleCursorImage);
}

ddRemoveColButtonHandle::~ddRemoveColButtonHandle()
{
}

void ddRemoveColButtonHandle::invokeStart(ddMouseEvent &event, ddDrawingView *view)
{
	ddTableFigure *table = (ddTableFigure*) getOwner();
	ddTextTableItemFigure *column = (ddTextTableItemFigure*) table->findFigure(event.GetPosition().x,event.GetPosition().y);
	if(column)
			table->toggleColumnDeleteMode();
}

void ddRemoveColButtonHandle::invokeStep(ddMouseEvent &event, ddDrawingView *view)
{
}

void ddRemoveColButtonHandle::invokeEnd(ddMouseEvent &event, ddDrawingView *view)
{
}

wxCursor ddRemoveColButtonHandle::createCursor()
{
	return handleCursor;
}
