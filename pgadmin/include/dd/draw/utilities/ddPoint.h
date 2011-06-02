//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPoint.h - wxPoint class to be used as wrapper and allow independence of point class
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDPOINT_H
#define DDPOINT_H

class ddPoint : public wxPoint{
public:
	ddPoint();
	ddPoint(int x, int y);
	ddPoint(const ddPoint& p);
	ddPoint(const wxPoint& p);
};

#endif
