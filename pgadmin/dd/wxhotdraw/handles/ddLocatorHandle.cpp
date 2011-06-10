//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddLocatorHandle.cpp - Base class for Handles that are located at locator position
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/handles/ddLocatorHandle.h"

ddLocatorHandle::ddLocatorHandle(ddIFigure *owner, ddILocator *locator):
ddIHandle(owner)
{
	loc=locator;
}

ddLocatorHandle::~ddLocatorHandle()
{
	if(loc)
		delete loc;
}

ddPoint& ddLocatorHandle::locate()
{
	p=ddPoint(0,0);
	return loc==NULL ? p : loc->locate(getOwner());
}

ddILocator* ddLocatorHandle::locator()
{
	return loc;
}

void ddLocatorHandle::invokeStart(ddMouseEvent& event, ddDrawingView *view)
{
}

void ddLocatorHandle::invokeStep(ddMouseEvent& event, ddDrawingView *view)
{
}

void ddLocatorHandle::invokeEnd(ddMouseEvent& event, ddDrawingView *view)
{
}
