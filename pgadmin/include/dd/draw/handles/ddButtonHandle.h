//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddButtonHandle.h - Handle to allow creation of buttons at figures
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDBUTTONHANDLE_H
#define DDBUTTONHANDLE_H

#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/handles/ddLocatorHandle.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/utilities/ddPoint.h"

class ddButtonHandle : public ddIHandle
{
public:
	ddButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size);
    ~ddButtonHandle();

	virtual wxCursor createCursor();
	virtual ddRect& getDisplayBox();
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual ddPoint& locate();
	virtual void invokeStart(ddMouseEvent& event, ddDrawingView *view)=0;
	virtual void invokeStep(ddMouseEvent& event, ddDrawingView *view)=0;
	virtual void invokeEnd(ddMouseEvent& event, ddDrawingView *view)=0;
protected:
	wxBitmap buttonIcon;
private:
	bool clicked;
	ddILocator *bLocator;
	ddPoint pointLocate;

};
#endif
