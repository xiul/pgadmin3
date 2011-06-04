//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPolyLineHandle.h - Handle for manipulation of multiple flexibility points lines.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDPOLYLINEHANDLE
#define DDPOLYLINEHANDLE

#include "dd/draw/handles/ddLocatorHandle.h"
#include "dd/draw/utilities/ddRect.h"

class ddDrawingView; 
class ddPolyLineFigure;

class ddPolyLineHandle : public ddLocatorHandle
{
public:
	ddPolyLineHandle(ddPolyLineFigure *figure, ddILocator *loc, int index);
    ~ddPolyLineHandle();

	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual void invokeStart(ddMouseEvent& event, ddDrawingView *view);
	virtual void invokeStep(ddMouseEvent& event, ddDrawingView *view);
	virtual wxCursor createCursor();
	virtual int getIndex();
	virtual void setIndex(int index);
protected:

private:
	int indx;


};
#endif
