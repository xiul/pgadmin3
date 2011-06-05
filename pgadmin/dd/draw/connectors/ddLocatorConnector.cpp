//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddLocatorConnector.cpp - class that puts connects at locator position
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/connectors/ddLocatorConnector.h"
ddLocatorConnector::ddLocatorConnector(ddIFigure *owner, ddILocator *locator):
ddIConnector(owner)
{
	figureOwner = owner;
	figureLocator = locator;
	size = 8;
}

ddLocatorConnector::~ddLocatorConnector()
{
}

ddPoint ddLocatorConnector::locate()
{
	return figureLocator->locate(getOwner());
}

void ddLocatorConnector::draw(wxBufferedDC& context)
{
}

ddRect& ddLocatorConnector::getDisplayBox()
{
	ddPoint p = figureLocator->locate(getOwner());
	displayBox = ddRect(p.x-(size/2), p.y-(size/2), size,size);
	return displayBox;
}

bool ddLocatorConnector::containsPoint(int x, int y)
{
	return getDisplayBox().Contains(x,y);
}

ddPoint ddLocatorConnector::findStart(ddLineConnection *connection)
{
	return getDisplayBox().center();
}

ddPoint ddLocatorConnector::findEnd(ddLineConnection *connection)
{
	return getDisplayBox().center();
}
