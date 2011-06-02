//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPolyLineFigureTool.cpp - Tool to allow creation of flexibility points at polylines figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/tools/ddPolyLineFigureTool.h"
#include "dd/draw/tools/ddFigureTool.h"
#include "dd/draw/tools/ddHandleTrackerTool.h"
#include "dd/draw/figures/ddPolyLineFigure.h"
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/tools/ddMenuTool.h"

ddPolyLineFigureTool::ddPolyLineFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{
}

ddPolyLineFigureTool::~ddPolyLineFigureTool()
{
}

void ddPolyLineFigureTool::mouseDown(ddMouseEvent& event)
{
	int x=event.GetPosition().x, y=event.GetPosition().y;
	setAnchorCoords(x,y);
	//Other events like other mouse button click (no left double click) should be done at handle
	//because this tool only add flexibility points to polylines.
	if(event.LeftDClick())
    {
		ddPolyLineFigure *connection = (ddPolyLineFigure*) figure;
		connection->splitSegment(x,y);
		getDrawingEditor()->view()->clearSelection();
		getDrawingEditor()->view()->addToSelection(figure);
		ddIHandle *handle = getDrawingEditor()->view()->findHandle(x,y);
		getDrawingEditor()->view()->SetCursor(handle->createCursor());
		if(defaultTool)
			delete defaultTool;
		defaultTool = new ddHandleTrackerTool(getDrawingEditor(), handle);
	}
	defaultTool->mouseDown(event);
}
