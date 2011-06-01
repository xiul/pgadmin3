//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRemoveColButtonHandle.h - A handle for a table figure that allow to graphically selecting a column for delete
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDREMOVECOLBUTTONHANDLE_H
#define DDREMOVECOLBUTTONHANDLE_H

#include "dd/draw/handles/ddButtonHandle.h"

class ddRemoveColButtonHandle : public ddButtonHandle
{
public:
	ddRemoveColButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size);
    ~ddRemoveColButtonHandle();

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
