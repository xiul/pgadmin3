//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdDragTrackerTool.h - A Tool that allow to drag and drop figures at the view
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdDRAGTRACKERTOOL_H
#define hdDRAGTRACKERTOOL_H

#include "dd/wxhotdraw/main/hdObject.h"
#include "dd/wxhotdraw/tools/hdITool.h"
#include "dd/wxhotdraw/figures/hdIFigure.h"
#include "dd/wxhotdraw/main/hdDrawingEditor.h"
#include "dd/wxhotdraw/tools/hdAbstractTool.h"


class hdDragTrackerTool : public hdAbstractTool
{
public:
	hdDragTrackerTool(hdDrawingView *view, hdIFigure *anchor);
	~hdDragTrackerTool();

	void setLastCoords(int x, int y);
	bool hasMoved();
	virtual void mouseDown(hdMouseEvent &event);  //Mouse Right Click
	virtual void mouseUp(hdMouseEvent &event);
	virtual void mouseDrag(hdMouseEvent &event);

protected:
	hdIFigure *anchorFigure;
	bool hasMovedValue;

private:
	int lastX, lastY;

};
#endif
