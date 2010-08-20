//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAddColButtonHandle.cpp 
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/handles/ddAddColButtonHandle.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/utilities/ddDataType.h"

//Images
#include "images/ddAddColumnCursor.xpm"

ddAddColButtonHandle::ddAddColButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size):
ddButtonHandle(owner,buttonLocator,buttonImage,size)
{
	handleCursorImage = wxBitmap(ddAddColumnCursor_xpm).ConvertToImage();
    handleCursor=wxCursor(handleCursorImage);
}

ddAddColButtonHandle::~ddAddColButtonHandle(){
}

void ddAddColButtonHandle::invokeStart(ddMouseEvent &event, ddDrawingView *view)
{
	ddTableFigure *table = (ddTableFigure*) getOwner();
	wxString title = wxString(wxT("NewColumn"));
	table->addColumn(new ddColumnFigure( title, table));
}

void ddAddColButtonHandle::invokeStep(ddMouseEvent &event, ddDrawingView *view)
{
}

void ddAddColButtonHandle::invokeEnd(ddMouseEvent &event, ddDrawingView *view)
{
}

wxCursor ddAddColButtonHandle::createCursor()
{
	return handleCursor;
}