//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPoint.cpp
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