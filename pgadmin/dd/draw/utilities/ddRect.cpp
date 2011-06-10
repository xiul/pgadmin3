//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRect.cpp - wxRect improved class with new needed functionalities
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/utilities/ddGeometry.h"

ddRect::ddRect()
{
}

ddRect::ddRect(int xx, int yy, int ww, int hh):
wxRect(xx,yy,ww,hh)
{
}

ddRect::ddRect(ddPoint *topLeft, ddPoint *bottomRight):
wxRect(*topLeft, *bottomRight)
{
}

ddRect::ddRect(ddPoint *point):
wxRect(point->x,point->y,0,0)
{
}

ddRect::ddRect(ddPoint& point):
wxRect(point.x,point.y,0,0)
{
}

void ddRect::add (int newX, int newY)
{
	int x1 = ddGeometry::min(x , newX);
	int x2 = ddGeometry::max(x+width , newX);
	int y1 = ddGeometry::min(y , newY);
	int y2 = ddGeometry::max(y+height , newY);

	SetX(x1);
	SetWidth(x2-x1);
	SetY(y1);
	SetHeight(y2-y1);
}


void ddRect::add (ddRect *newRect)
{
	add(newRect->GetTopLeft().x , newRect->GetTopLeft().y);
	add(newRect->GetBottomRight().x , newRect->GetBottomRight().y);
}

void ddRect::add (ddRect& newRect)
{
	add(newRect.GetTopLeft().x , newRect.GetTopLeft().y);
	add(newRect.GetBottomRight().x , newRect.GetBottomRight().y);
}

void ddRect::add(ddPoint *p)
{
	add(p->x,p->y);
}



ddPoint ddRect::center()
{
	point = ddPoint(x+(width/2) , y+(height/2)); 
	return point;
}

