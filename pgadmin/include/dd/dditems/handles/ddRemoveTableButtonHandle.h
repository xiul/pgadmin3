//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRemoveTableButtonHandle.h - A handle for a table figure that allow to delete it
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDREMOVETABLEBUTTONHANDLE_H
#define DDREMOVETABLEBUTTONHANDLE_H

#include "dd/wxhotdraw/handles/ddButtonHandle.h"

class ddRemoveTableButtonHandle : public ddButtonHandle
{
public:
	ddRemoveTableButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size);
    ~ddRemoveTableButtonHandle();

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
