//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDragTrackerTool.h - A Tool that allow to drag and drop figures at the view
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDDRAGTRACKERTOOL_H
#define DDDRAGTRACKERTOOL_H

#include "dd/draw/main/ddObject.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/tools/ddAbstractTool.h"


class ddDragTrackerTool : public ddAbstractTool
{
public:
	ddDragTrackerTool(ddDrawingEditor *editor, ddIFigure *anchor);
    ~ddDragTrackerTool();

	void setLastCoords(int x, int y);
	bool hasMoved();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseDrag(ddMouseEvent& event);

protected:
	ddIFigure *anchorFigure;
	bool hasMovedValue;

private:
	int lastX, lastY;
	ddDrawingView *view;

};
#endif
