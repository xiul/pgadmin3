//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddLocatorConnector.cpp 
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
//#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/connectors/ddLocatorConnector.h"

class ddLineConnection;  //HACK-FIX to circular reference
class ddIFigure;

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

/*ddIFigure* ddLocatorConnector::getOwner()
{
	return figureOwner;

}

void ddLocatorConnector::setOwner(ddIFigure *owner)
{
	figureOwner=owner;
}
*/

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
