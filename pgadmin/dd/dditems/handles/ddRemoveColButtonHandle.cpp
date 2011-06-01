//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRemoveColButtonHandle.cpp - A handle for a table figure that allow to graphically selecting a column for delete
//
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
