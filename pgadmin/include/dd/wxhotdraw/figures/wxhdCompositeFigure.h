//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdCompositeFigure.h - Base class for all figures composite with figures
//
//////////////////////////////////////////////////////////////////////////

#ifndef WXHDCOMPOSITEFIGURE_H
#define WXHDCOMPOSITEFIGURE_H
#include "dd/wxhotdraw/figures/wxhdAbstractFigure.h"

class wxhdCompositeFigure : public wxhdAbstractFigure
{
public:
	wxhdCompositeFigure();
    ~wxhdCompositeFigure();
	virtual void basicMoveBy(int x, int y);
	virtual bool containsPoint(int x, int y);
	virtual wxhdIteratorBase* figuresEnumerator();
	virtual wxhdIteratorBase* figuresInverseEnumerator();
	virtual wxhdRect& getBasicDisplayBox();
	virtual wxhdCollection* handlesEnumerator();
	virtual void add(wxhdIFigure *figure);
	virtual void remove(wxhdIFigure *figure);
	virtual bool includes(wxhdIFigure *figure);
	virtual void draw(wxBufferedDC& context, wxhdDrawingView *view);
	virtual void drawSelected(wxBufferedDC& context, wxhdDrawingView *view);
	virtual wxhdIFigure* findFigure(int x, int y);
	virtual wxhdIFigure* getFigureAt(int pos);
	virtual wxhdITool* CreateFigureTool(wxhdDrawingEditor *editor, wxhdITool *defaultTool);
protected:
	wxhdCollection *figureFigures;
	wxhdCollection *figureHandles;
private:
	
};
#endif
