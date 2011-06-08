//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRect.h - wxRect improved class with new needed functionalities
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDRECT_H
#define DDRECT_H
#include "dd/draw/utilities/ddPoint.h"

class ddRect : public wxRect
{
public:
	ddRect();
	ddRect(int xx, int yy, int ww, int hh);
	ddRect(ddPoint *topLeft, ddPoint *bottomRight);
	ddRect(ddPoint *point);
	ddRect(ddPoint &point);
	void add (int newX, int netY);
	void add (ddRect *newRect);
	void add (ddRect& newRect);
	void add (ddPoint *p);
	ddPoint center();

protected:

private:
	int min(int a, int b);
	int max(int a, int b);  //DD-TODO: delete this functions use ddGeometry instead of after convert methods of this class to static
	ddPoint point;
};
#endif
