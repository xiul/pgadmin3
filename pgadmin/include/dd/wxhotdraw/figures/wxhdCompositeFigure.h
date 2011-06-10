//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddCompositeFigure.h - Base class for all figures composite with figures
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCOMPOSITEFIGURE_H
#define DDCOMPOSITEFIGURE_H
#include "dd/wxhotdraw/figures/wxhdAbstractFigure.h"

class ddCompositeFigure : public ddAbstractFigure
{
public:
	ddCompositeFigure();
    ~ddCompositeFigure();
	virtual void basicMoveBy(int x, int y);
	virtual bool containsPoint(int x, int y);
	virtual ddIteratorBase* figuresEnumerator();
	virtual ddIteratorBase* figuresInverseEnumerator();
	virtual ddRect& getBasicDisplayBox();
	virtual ddCollection* handlesEnumerator();
	virtual void add(ddIFigure *figure);
	virtual void remove(ddIFigure *figure);
	virtual bool includes(ddIFigure *figure);
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual void drawSelected(wxBufferedDC& context, ddDrawingView *view);
	virtual ddIFigure* findFigure(int x, int y);
	virtual ddIFigure* getFigureAt(int pos);
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
protected:
	ddCollection *figureFigures;
	ddCollection *figureHandles;
private:
	
};
#endif
