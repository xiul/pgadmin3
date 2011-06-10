//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddChopBoxConnector.cpp - Connector for center of figure to line crossing one limit line of rect
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/connectors/ddChopBoxConnector.h"
#include "dd/wxhotdraw/utilities/ddGeometry.h"

ddChopBoxConnector::ddChopBoxConnector(ddIFigure *owner):
ddIConnector(owner)
{
}

ddChopBoxConnector::~ddChopBoxConnector()
{
}


ddPoint ddChopBoxConnector::chop(ddIFigure *target, ddPoint point){
	if(target && target->containsPoint(point.x, point.y))
	{
		point=target->displayBox().center();
		return point;
	}
	else if(!target)
	{
		point = ddPoint(0,0);		
		return point;
	}
	
	ddGeometry g;
	
	rect = getDisplayBox();  //hack to avoid linux bug
	double angle = g.angleFromPoint(rect, point);
	point=g.edgePointFromAngle(rect, angle);
	return point; 
}

ddPoint ddChopBoxConnector::findStart(ddLineConnection *connFigure)
{
	if(!connFigure)
	{
		point=getDisplayBox().center();
		return point; 
	}
	
	if(connFigure->pointCount()<2)
	{
		point=getDisplayBox().center();
		return point;
	}

	ddIFigure *start = connFigure->getStartConnector()->getOwner();
	point = connFigure->pointAt(1);
	point = chop(start,point);
	return point;
}

ddPoint ddChopBoxConnector::findEnd(ddLineConnection *connFigure)
{
	if(!connFigure)
	{
		return getDisplayBox().center();
	}
	ddIFigure *end = connFigure->getEndConnector()->getOwner();
	point = connFigure->pointAt(connFigure->pointCount()-2);
	point = chop(end,point);
	return point;
}
