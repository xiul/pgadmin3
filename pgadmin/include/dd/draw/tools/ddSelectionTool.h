//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddSelectionTool.h - Tool to allow selection of figures
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDSELECTIONTOOL_H
#define DDSELECTIONTOOL_H

#include "dd/draw/tools/ddITool.h"
#include "dd/draw/tools/ddAbstractTool.h"

class ddSelectionTool : public ddAbstractTool
{
public:
	ddSelectionTool(ddDrawingEditor *owner);
    ~ddSelectionTool();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseMove(ddMouseEvent& event);
	virtual void mouseDrag(ddMouseEvent& event);
	virtual void keyDown(wxKeyEvent& event);
	virtual void keyUp(wxKeyEvent& event);
	void setDelegateTool(ddITool *tool);
	ddITool* getDelegateTool();

protected:
	ddITool *_delegateTool;
private:
	void deleteFigures(ddDrawingView *view);
};
#endif
