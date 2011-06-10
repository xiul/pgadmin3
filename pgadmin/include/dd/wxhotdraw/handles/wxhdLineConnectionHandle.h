//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddLineConnectionHandle.h - Base class for Handles that are located at locator position
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDLINECONNECTIONHANDLE
#define DDLINECONNECTIONHANDLE

#include "dd/wxhotdraw/handles/wxhdPolyLineHandle.h"

class ddLineConnectionHandle : public ddPolyLineHandle
{
public:
	ddLineConnectionHandle(ddPolyLineFigure *figure, ddILocator *loc, int index);
	virtual void invokeEnd(ddMouseEvent& event, ddDrawingView *view);
private:

};
#endif
