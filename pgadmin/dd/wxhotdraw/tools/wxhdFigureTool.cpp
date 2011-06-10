//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddFigureTool.cpp - Base class for all figure tools
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/tools/wxhdFigureTool.h"

ddFigureTool::ddFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddAbstractTool(editor)
{
	defaultTool=dt;
	figure=fig;
}

ddFigureTool::~ddFigureTool()
{
	if(defaultTool)
	{
		delete defaultTool;
	}
}

void ddFigureTool::setDefaultTool(ddITool *dt)
{
	defaultTool=dt;
}

ddITool* ddFigureTool::getDefaultTool()
{
	return defaultTool;
}

void ddFigureTool::setFigure(ddIFigure *fig)
{
	figure=fig;
}

ddIFigure* ddFigureTool::getFigure()
{
	return figure;
}

void ddFigureTool::mouseDown(ddMouseEvent& event)
{
	if(defaultTool)
	{
		defaultTool->mouseDown(event);
	}
}

void ddFigureTool::mouseUp(ddMouseEvent& event)
{
	if(defaultTool)
	{
		defaultTool->mouseUp(event);
	}
}

void ddFigureTool::mouseMove(ddMouseEvent& event)
{
	if(defaultTool)
	{
		defaultTool->mouseMove(event);
	}
}

void ddFigureTool::mouseDrag(ddMouseEvent& event)
{
	if(defaultTool)
	{
		defaultTool->mouseDrag(event);
	}
}

void ddFigureTool::keyDown(wxKeyEvent& event)
{
	if(defaultTool)
	{
		defaultTool->keyDown(event);
	}
}

void ddFigureTool::keyUp(wxKeyEvent& event)
{
		if(defaultTool)
	{
		defaultTool->keyUp(event);
	}
}
