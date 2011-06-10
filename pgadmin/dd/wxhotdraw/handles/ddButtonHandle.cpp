//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddButtonHandle.cpp - Handle to allow creation of buttons at figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/handles/ddButtonHandle.h"
#include "dd/wxhotdraw/utilities/ddPoint.h"
#include "dd/wxhotdraw/main/ddDrawingView.h"



ddButtonHandle::ddButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size):
ddIHandle(owner)
{
	buttonIcon = buttonImage;
	clicked=false;
	bLocator = buttonLocator;
	displayBox.SetSize(size);
}

ddButtonHandle::~ddButtonHandle()
{
	if(bLocator)
		delete bLocator;
}

wxCursor ddButtonHandle::createCursor()
{
	return wxCursor(wxCURSOR_PENCIL);
}

ddRect& ddButtonHandle::getDisplayBox()
{
	ddPoint p = locate();		
	displayBox.SetPosition(p);
	return displayBox;
}

void ddButtonHandle::draw(wxBufferedDC& context, ddDrawingView *view)
{
	wxPoint copy = getDisplayBox().GetPosition();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	if(buttonIcon.IsOk())
		context.DrawBitmap(buttonIcon,copy.x,copy.y,true);
}


ddPoint& ddButtonHandle::locate()
{
	if(bLocator)
	{
		pointLocate=bLocator->locate(getOwner());
		return pointLocate;
	}
	else
	{
		pointLocate=ddPoint(0,0);	
		return pointLocate;		
	}
}
