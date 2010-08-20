//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddMinMaxTableButtonHandle.cpp
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/handles/ddMinMaxTableButtonHandle.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/utilities/ddDataType.h"

//Images
#include "images/ddMinMaxCursor.xpm"

ddMinMaxTableButtonHandle::ddMinMaxTableButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxBitmap &buttonSecondImage, wxSize &size):
ddButtonHandle(owner,buttonLocator,buttonImage,size)
{
	handleCursorImage = wxBitmap(ddMinMaxCursor_xpm).ConvertToImage();
    handleCursor=wxCursor(handleCursorImage);
	buttonMaximizeImage = buttonSecondImage;
	tmpImage = buttonImage;
	showFirst = true;
}

ddMinMaxTableButtonHandle::~ddMinMaxTableButtonHandle(){
}

void ddMinMaxTableButtonHandle::invokeStart(ddMouseEvent &event, ddDrawingView *view)
{
}

void ddMinMaxTableButtonHandle::invokeStep(ddMouseEvent &event, ddDrawingView *view)
{
}

void ddMinMaxTableButtonHandle::invokeEnd(ddMouseEvent &event, ddDrawingView *view)
{
	ddTableFigure *table = (ddTableFigure*) getOwner();

	if(showFirst)
	{
		buttonIcon = buttonMaximizeImage;
		table->setColumnsWindow(1);
	}
	else
	{
		buttonIcon = tmpImage;
		table->setColumnsWindow(table->getTotalColumns(),true);
	}
	showFirst=!showFirst;
}


wxCursor ddMinMaxTableButtonHandle::createCursor()
{
	return handleCursor;
}