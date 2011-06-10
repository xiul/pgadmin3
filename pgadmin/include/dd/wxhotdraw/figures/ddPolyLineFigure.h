//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPolyLineFigure.h - A simple line figure that can be split on several lines joined by flexibility points
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDPOLYLINEFIGURE_H
#define DDPOLYLINEFIGURE_H

#include "dd/wxhotdraw/figures/ddAbstractMenuFigure.h"
#include "dd/wxhotdraw/figures/ddLineTerminal.h"
#include "dd/wxhotdraw/utilities/ddArrayCollection.h"
#include "dd/wxhotdraw/utilities/ddPoint.h"

class ddPolyLineFigure : public ddAbstractMenuFigure
{
public:
	ddPolyLineFigure();
    ~ddPolyLineFigure();

	virtual ddRect& getBasicDisplayBox();
	virtual void basicDraw (wxBufferedDC& context, ddDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);
	virtual int pointCount();
	virtual ddPoint& getStartPoint();
	virtual void setStartPoint(ddPoint point);
	virtual ddPoint& getEndPoint();
	virtual void setEndPoint(ddPoint point);
	virtual void setStartTerminal(ddLineTerminal *terminal);
	virtual ddLineTerminal* getStartTerminal();
	virtual void setEndTerminal(ddLineTerminal *terminal);
	virtual ddLineTerminal* getEndTerminal();
	ddCollection* handlesEnumerator();
	virtual int findSegment (int x, int y);
	virtual void splitSegment(int x, int y);
	virtual void changed();

	virtual void addPoint (int x, int y);
	virtual void clearPoints ();
	virtual void insertPointAt (int index, int x, int y);
	virtual void setPointAt (int index, int x, int y);
	virtual void removePointAt (int index);
	virtual void basicMoveBy(int x, int y);
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);

	virtual ddPoint& pointAt(int index);
	virtual bool containsPoint (int x, int y);
	virtual void setLinePen(wxPen pen);

protected:
	virtual void updateHandlesIndexes();
	ddArrayCollection *points;
	ddPoint endPoint, startPoint, pointAtPos;
private:
	ddLineTerminal *startTerminal, *endTerminal;
	bool handlesChanged;
	wxPen linePen;

};
#endif
