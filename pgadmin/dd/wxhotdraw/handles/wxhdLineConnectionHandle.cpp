//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddLineConnectionHandle.cpp - Base class for Handles that are located at locator position
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/wxhotdraw/handles/wxhdLineConnectionHandle.h"
#include "dd/wxhotdraw/figures/wxhdPolyLineFigure.h"
#include "dd/wxhotdraw/utilities/wxhdPoint.h"
#include "dd/wxhotdraw/utilities/wxhdGeometry.h"

ddLineConnectionHandle::ddLineConnectionHandle(ddPolyLineFigure *figure, ddILocator *loc, int index):
ddPolyLineHandle(figure,loc,index)
{
}

void ddLineConnectionHandle::invokeEnd(ddMouseEvent& event, ddDrawingView *view)
{
	int x=event.GetPosition().x, y=event.GetPosition().y;
	ddPolyLineFigure *figure = (ddPolyLineFigure *) getOwner();
	//eliminate all handles in the middle of a straight line
	
	if( figure->pointCount() > 2 && getIndex() != 0 && getIndex() != (figure->pointCount()-1) )
	{
		ddPoint p1 = figure->pointAt(getIndex()-1);
		ddPoint p2 = figure->pointAt(getIndex()+1);
		ddGeometry g;
		if(g.lineContainsPoint(p1.x, p1.y, p2.x, p2.y, x, y))
		{
			figure->removePointAt(getIndex());
		}
	}
}
