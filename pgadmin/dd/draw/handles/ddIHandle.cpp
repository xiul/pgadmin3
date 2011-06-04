//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddIHandle.cpp - Base class for all Handles
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/utilities/ddPoint.h"

ddIHandle::ddIHandle(ddIFigure *owner)
{
	figureOwner=owner;
}
ddIHandle::~ddIHandle()
{
}

ddIFigure* ddIHandle::getOwner()
{
	return figureOwner;
}

ddRect& ddIHandle::getDisplayBox()
{
	ddPoint p = locate();
	displayBox.width=0;
	displayBox.height=0;
	displayBox.SetPosition(p);
	displayBox.Inflate(size,size);
	return displayBox;
}

bool ddIHandle::containsPoint(int x, int y)
{
	return getDisplayBox().Contains(x,y);
}
