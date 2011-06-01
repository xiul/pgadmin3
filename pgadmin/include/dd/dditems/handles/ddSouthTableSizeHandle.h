//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddSouthTableSizeHandle.h - Allow to change table size by using drag and drop from south side of table rectangle
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDSOUTHTABLESIZEHANDLE_H
#define DDSOUTHTABLESIZEHANDLE_H

#include "dd/draw/handles/ddLocatorHandle.h"

class ddTableFigure;

class ddSouthTableSizeHandle : public ddLocatorHandle
{
public:
	ddSouthTableSizeHandle(ddTableFigure *owner, ddILocator *locator);
    ~ddSouthTableSizeHandle();
	virtual wxCursor createCursor();
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual ddRect& getDisplayBox();
	virtual void invokeStart(ddMouseEvent &event, ddDrawingView *view);
	virtual void invokeStep(ddMouseEvent &event, ddDrawingView *view);
	virtual void invokeEnd(ddMouseEvent &event, ddDrawingView *view);
protected:

private:
	int anchorY;

};
#endif
