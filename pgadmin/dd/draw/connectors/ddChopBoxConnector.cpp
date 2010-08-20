//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddChopBoxConnector.cpp 
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/connectors/ddChopBoxConnector.h"
#include "dd/draw/utilities/ddGeometry.h"

ddChopBoxConnector::ddChopBoxConnector(ddIFigure *owner):
ddIConnector(owner)
{
}

ddChopBoxConnector::~ddChopBoxConnector()
{
}

//DD-TODO: change to reference ddPoint&
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
