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

#include "dd/wxhotdraw/main/wxhdObject.h"
#include "dd/wxhotdraw/tools/wxhdITool.h"
#include "dd/wxhotdraw/figures/wxhdIFigure.h"
#include "dd/wxhotdraw/main/wxhdDrawingEditor.h"
#include "dd/wxhotdraw/tools/wxhdAbstractTool.h"


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
