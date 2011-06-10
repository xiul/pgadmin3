//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractFigure.h - Base class for all figures
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDABSTRACTFIGURE_H
#define DDABSTRACTFIGURE_H
#include "dd/wxhotdraw/utilities/wxhdRect.h"
#include "dd/wxhotdraw/figures/wxhdIFigure.h"
#include "dd/wxhotdraw/tools/wxhdITool.h"
#include "dd/wxhotdraw/handles/wxhdIHandle.h"
#include "dd/wxhotdraw/utilities/wxhdCollection.h"

class ddAbstractFigure : public ddIFigure
{
public:
	ddAbstractFigure();
    ~ddAbstractFigure();
	
	virtual bool canConnect ();
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual void drawSelected(wxBufferedDC& context, ddDrawingView *view);
	virtual bool includes(ddIFigure *figure);
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
	virtual void moveBy(int x, int y);
	virtual void basicMoveBy(int x, int y);
	virtual void moveTo(int x, int y);
	virtual bool containsPoint(int x, int y);
	virtual void onFigureChanged(ddIFigure *figure);

protected:
	virtual void basicDraw(wxBufferedDC& context, ddDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);		
	void willChange();
	void changed();
	void invalidate();
	wxColour fillColor, lineColor;
	double lineWidth;

private:

};
#endif
