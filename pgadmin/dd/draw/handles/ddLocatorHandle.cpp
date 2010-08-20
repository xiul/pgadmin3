//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddLocatorHandle.cpp 
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/handles/ddLocatorHandle.h"

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
	return loc==NULL ? p : loc->locate(getOwner()) ;
}

ddILocator* ddLocatorHandle::locator()
{
	return loc;
}

void ddLocatorHandle::invokeStart(ddMouseEvent& event, ddDrawingView *view){
}

void ddLocatorHandle::invokeStep(ddMouseEvent& event, ddDrawingView *view){
}

void ddLocatorHandle::invokeEnd(ddMouseEvent& event, ddDrawingView *view){
}
