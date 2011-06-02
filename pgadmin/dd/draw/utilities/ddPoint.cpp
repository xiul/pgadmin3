//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPoint.cpp - wxPoint class to be used as wrapper and allow independence of point class
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/utilities/ddPoint.h"

ddPoint::ddPoint():
wxPoint()
{
}

ddPoint::ddPoint(int x, int y):
wxPoint(x,y)
{
}

ddPoint::ddPoint(const ddPoint& p):
wxPoint(p.x,p.y)
{
}

ddPoint::ddPoint(const wxPoint& p):
wxPoint(p.x,p.y)
{
}