//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdAbstractFigure.cpp - A StickyRectangleConnector locates connection points by choping
// the connection between the centers of the two figures at the display box. The location 
// of the connection point is computed once, when the user connects the figure. 
// Moving the figure around will not change the location.
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/connectors/wxhdStickyRectangleConnector.h"
#include "dd/wxhotdraw/figures/wxhdLineConnection.h"
#include "dd/wxhotdraw/connectors/wxhdChopBoxConnector.h"
#include "dd/wxhotdraw/utilities/wxhdGeometry.h"

class wxhdLineConnection;
class wxhdIFigure;

wxhdStickyRectangleConnector::wxhdStickyRectangleConnector(wxhdIFigure *owner, wxhdPoint p):
wxhdChopBoxConnector(owner)
{
	wxhdGeometry g;
	updateAnchor(p);
}

wxhdStickyRectangleConnector::~wxhdStickyRectangleConnector()
{
}

void wxhdStickyRectangleConnector::setAngle(float newAngle)
{
	angle=newAngle;
}

void wxhdStickyRectangleConnector::updateAnchor(wxhdPoint p)
{
	wxhdGeometry g;

	wxhdRect rect = getDisplayBox();  //hack to avoid linux bug
	angle = g.angleFromPoint(rect, p);
}

wxhdPoint wxhdStickyRectangleConnector::getAnchor()
{
	wxhdGeometry g;

	wxhdRect rect = getDisplayBox();  //hack to avoid linux bug	
	return g.edgePointFromAngle(rect, angle);
}

wxhdPoint wxhdStickyRectangleConnector::chop(wxhdIFigure *target, wxhdPoint point){
	
	wxhdGeometry g;
	
	wxhdRect rect = target->displayBox();  //hack to avoid linux bug
	point=g.edgePointFromAngle(rect, angle);
	return point; 
}

void wxhdStickyRectangleConnector::draw(wxBufferedDC& context)
{
}