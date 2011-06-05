//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractFigure.cpp - A StickyRectangleConnector locates connection points by choping
// the connection between the centers of the two figures at the display box. The location 
// of the connection point is computed once, when the user connects the figure. 
// Moving the figure around will not change the location.
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/connectors/ddStickyRectangleConnector.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/connectors/ddChopBoxConnector.h"
#include "dd/draw/utilities/ddGeometry.h"

class ddLineConnection;
class ddIFigure;

ddStickyRectangleConnector::ddStickyRectangleConnector(ddIFigure *owner, ddPoint p):
ddChopBoxConnector(owner)
{
	ddGeometry g;
	updateAnchor(p);
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