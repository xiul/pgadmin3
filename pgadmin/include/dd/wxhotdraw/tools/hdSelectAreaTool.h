//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdSelectAreaTool.h - Tool to allow selection of figures inside a rectangle
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdSELECTAREATOOL_H
#define hdSELECTAREATOOL_H

#include "dd/wxhotdraw/main/hdObject.h"
#include "dd/wxhotdraw/tools/hdITool.h"
#include "dd/wxhotdraw/figures/hdIFigure.h"
#include "dd/wxhotdraw/main/hdDrawingEditor.h"
#include "dd/wxhotdraw/tools/hdAbstractTool.h"


class hdSelectAreaTool : public hdAbstractTool
{
public:
	hdSelectAreaTool(hdDrawingView *view);
	~hdSelectAreaTool();

	virtual void mouseDown(hdMouseEvent &event);  //Mouse Right Click
	virtual void mouseUp(hdMouseEvent &event);
	virtual void mouseDrag(hdMouseEvent &event);
	void selectFiguresOnRect(bool shiftPressed, hdDrawingView *view);
protected:
	void drawSelectionRect(hdDrawingView *view);
private:
	hdRect selectionRect;
};
#endif
