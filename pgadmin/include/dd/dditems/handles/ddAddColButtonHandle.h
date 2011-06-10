//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAddColButtonHandle.h - A handle for a table figure that allow to graphically add columns 
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDADDCOLBUTTONHANDLE_H
#define DDADDCOLBUTTONHANDLE_H

#include "dd/wxhotdraw/handles/wxhdButtonHandle.h"

class ddAddColButtonHandle : public ddButtonHandle
{
public:
	ddAddColButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size);
    ~ddAddColButtonHandle();

	virtual void invokeStart(ddMouseEvent &event, ddDrawingView *view);
	virtual void invokeStep(ddMouseEvent &event, ddDrawingView *view);
	virtual void invokeEnd(ddMouseEvent &event, ddDrawingView *view);
	wxCursor createCursor();
protected:

private:
    wxImage handleCursorImage;
    wxCursor handleCursor;
};
#endif
