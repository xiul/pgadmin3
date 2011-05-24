//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddStickyRectangleConnector.cpp 
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
//#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/connectors/ddStickyRectangleConnector.h"
#include "dd/draw/connectors/ddChopBoxConnector.h"
#include "dd/draw/utilities/ddGeometry.h"

class ddLineConnection;  //HACK-FIX to circular reference
class ddIFigure;

/*
A StickyRectangleConnector locates connection points by choping the connection between the centers of the
two figures at the display box.  The location of the connection point is computed once,
when the user connects the figure. Moving the figure around will not change the location.
*/

ddStickyRectangleConnector::ddStickyRectangleConnector(ddIFigure *owner, ddPoint p):
ddChopBoxConnector(owner)
{
	ddGeometry g;
	
	updateAnchor(p);
	/*	ddRect rect = getDisplayBox();  //hack to avoid linux bug
	angle = g.angleFromPoint(rect, p);*/
}

ddStickyRectangleConnector::~ddStickyRectangleConnector()
{
}

void ddStickyRectangleConnector::setAngle(float newAngle)
{
	angle=newAngle;
}

void ddStickyRectangleConnector::updateAnchor(ddPoint p)
{
	ddGeometry g;

	ddRect rect = getDisplayBox();  //hack to avoid linux bug
	angle = g.angleFromPoint(rect, p);
}

ddPoint ddStickyRectangleConnector::getAnchor()
{
	ddGeometry g;

	ddRect rect = getDisplayBox();  //hack to avoid linux bug	
	return g.edgePointFromAngle(rect, angle);
}

ddPoint ddStickyRectangleConnector::chop(ddIFigure *target, ddPoint point){
	
	ddGeometry g;
	
	ddRect rect = target->displayBox();  //hack to avoid linux bug
	point=g.edgePointFromAngle(rect, angle);
	return point; 
}

void ddStickyRectangleConnector::draw(wxBufferedDC& context)
{
}

/*
ddRect& ddStickyRectangleConnector::getDisplayBox()
{
	return getOwner()->displayBox();
}

bool ddStickyRectangleConnector::containsPoint(int x, int y)
{
	return getOwner()->containsPoint(x,y);
}

ddPoint ddStickyRectangleConnector::findStart(ddLineConnection *connection)
{
	return getDisplayBox().center();
}

ddPoint ddStickyRectangleConnector::findEnd(ddLineConnection *connection)
{
	return getDisplayBox().center();
}
*/