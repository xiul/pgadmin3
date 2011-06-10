//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPolyLineHandle.cpp - Handle for manipulation of multiple flexibility points lines.
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/wxhotdraw/handles/wxhdPolyLineHandle.h"
#include "dd/wxhotdraw/figures/wxhdPolyLineFigure.h"
#include "dd/wxhotdraw/locators/wxhdPolyLineLocator.h"
#include "dd/wxhotdraw/main/wxhdDrawingView.h"


ddPolyLineHandle::ddPolyLineHandle(ddPolyLineFigure *figure, ddILocator *loc, int index):
ddLocatorHandle((ddIFigure *)figure,loc)
{
	indx=index;
}

ddPolyLineHandle::~ddPolyLineHandle()
{
}

void ddPolyLineHandle::draw(wxBufferedDC& context, ddDrawingView *view)
{
	ddRect copy = getDisplayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);

	double middle=copy.width/2;
	context.DrawCircle(
        wxPoint(copy.x+middle,copy.y+middle),
        wxCoord(middle)
        );
}

void ddPolyLineHandle::invokeStep(ddMouseEvent& event, ddDrawingView *view)
{
	int x=event.GetPosition().x, y=event.GetPosition().y;
	((ddPolyLineFigure*) getOwner())->setPointAt(indx,x,y);
	
}

void ddPolyLineHandle::invokeStart(ddMouseEvent& event, ddDrawingView *view)
{
	if(event.RightDown())
	{
		((ddPolyLineFigure*) getOwner())->removePointAt(indx);
	}
}
wxCursor ddPolyLineHandle::createCursor()
{
	return wxCursor(wxCURSOR_CROSS);

}

int ddPolyLineHandle::getIndex()
{
	return indx;
}

void ddPolyLineHandle::setIndex(int index)
{
	indx=index;
	ddPolyLineLocator *l = (ddPolyLineLocator*) locator();
	l->setIndex(index);
}
