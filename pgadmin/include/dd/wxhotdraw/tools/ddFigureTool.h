//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddFigureTool.h - Base class for all figure tools
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDFIGURETOOL_H
#define DDFIGURETOOL_H

#include "dd/wxhotdraw/tools/ddAbstractTool.h"


class ddFigureTool : public ddAbstractTool
{
public:
	ddFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt);
    ~ddFigureTool();
	void setDefaultTool(ddITool *dt);
	ddITool* getDefaultTool();
	void setFigure(ddIFigure *fig);
	ddIFigure* getFigure();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseMove(ddMouseEvent& event);
	virtual void mouseDrag(ddMouseEvent& event);
	virtual void keyDown(wxKeyEvent& event);
	virtual void keyUp(wxKeyEvent& event);
protected:
	ddITool *defaultTool;
	ddIFigure *figure;
private:
};
#endif
