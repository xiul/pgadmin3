//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAddFkButtonHandle.h - A handle for a table figure that allow to graphically add relationships (fk) 
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDADDFKBUTTONHANDLE_H
#define DDADDFKBUTTONHANDLE_H

#include "dd/wxhotdraw/handles/ddButtonHandle.h"

class ddAddFkButtonHandle : public ddButtonHandle
{
public:
	ddAddFkButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size);
    ~ddAddFkButtonHandle();

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
