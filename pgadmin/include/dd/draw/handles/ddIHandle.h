//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddIHandle.cpp - Base class for all Handles
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDIHANDLE_H
#define DDIHANDLE_H

#include "wx/dcbuffer.h"
#include "dd/draw/main/ddObject.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/utilities/ddPoint.h"

class ddDrawingView;
class ddIFigure;
class ddMouseEvent;

class ddIHandle : public ddObject
{
public:
	ddIHandle(ddIFigure *owner);
    ~ddIHandle();
	
	static const int size = 4;

	virtual bool containsPoint(int x, int y);
	virtual void draw(wxBufferedDC& context, ddDrawingView *view)=0;
	virtual ddPoint& locate()=0;
	virtual void invokeStart(ddMouseEvent& event, ddDrawingView *view)=0;
	virtual void invokeStep(ddMouseEvent& event, ddDrawingView *view)=0;
	virtual void invokeEnd(ddMouseEvent& event, ddDrawingView *view)=0;
	virtual wxCursor createCursor()=0;
	virtual ddRect& getDisplayBox();
protected:
	virtual ddIFigure* getOwner();
	ddRect displayBox;
private:
	ddIFigure *figureOwner;
	double lineWidth;
	//DD-TODO: Add	fillColor and addColor


};
#endif
