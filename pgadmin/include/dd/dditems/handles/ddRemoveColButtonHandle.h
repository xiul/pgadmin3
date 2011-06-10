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

#include "dd/wxhotdraw/handles/wxhdButtonHandle.h"

class ddRemoveColButtonHandle : public wxhdButtonHandle
{
public:
	ddRemoveColButtonHandle(wxhdIFigure *owner, wxhdILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size);
    ~ddRemoveColButtonHandle();

	virtual void invokeStart(wxhdMouseEvent &event, wxhdDrawingView *view);
	virtual void invokeStep(wxhdMouseEvent &event, wxhdDrawingView *view);
	virtual void invokeEnd(wxhdMouseEvent &event, wxhdDrawingView *view);
	wxCursor createCursor();
protected:

private:
    wxImage handleCursorImage;
    wxCursor handleCursor;
};
#endif
