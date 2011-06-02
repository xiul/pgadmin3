//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddSelectAreaTool.h - Tool to allow selection of figures inside a rectangle
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDSELECTAREATOOL_H
#define DDSELECTAREATOOL_H

#include "dd/draw/main/ddObject.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/tools/ddAbstractTool.h"


class ddSelectAreaTool : public ddAbstractTool
{
public:
	ddSelectAreaTool(ddDrawingEditor *editor);
    ~ddSelectAreaTool();

	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseDrag(ddMouseEvent& event);
	void selectFiguresOnRect(bool shiftPressed);
protected:
	void drawSelectionRect();
private:
	ddDrawingView *view;
	ddRect selectionRect;
};
#endif
