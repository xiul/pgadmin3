//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddLocatorHandle.h - Base class for Handles that are located at locator position
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDLOCATORHANDLE_H
#define DDLOCATORHANDLE_H

#include "dd/wxhotdraw/handles/ddIHandle.h"
#include "dd/wxhotdraw/utilities/ddRect.h"
#include "dd/wxhotdraw/locators/ddILocator.h"

class ddDrawingView;

class ddLocatorHandle : public ddIHandle
{
public:
	ddLocatorHandle(ddIFigure *owner, ddILocator *locator);
    ~ddLocatorHandle();

	virtual ddPoint& locate();
	virtual ddILocator* locator();
	virtual void invokeStart(ddMouseEvent& event, ddDrawingView *view);
	virtual void invokeStep(ddMouseEvent& event, ddDrawingView *view);
	virtual void invokeEnd(ddMouseEvent& event, ddDrawingView *view);
protected:

private:
	ddILocator *loc;
	ddPoint p;

};
#endif
