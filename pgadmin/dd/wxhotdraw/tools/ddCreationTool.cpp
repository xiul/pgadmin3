//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddCreationTool.cpp - A Tool that create a figure by just click on view
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/tools/ddCreationTool.h"
#include "dd/wxhotdraw/tools/ddSelectionTool.h"

ddCreationTool::ddCreationTool(ddDrawingEditor *editor, ddIFigure *prototype):
ddAbstractTool(editor)
{
	figurePrototype=prototype;
}

ddCreationTool::~ddCreationTool()
{
}

void ddCreationTool::mouseDown(ddMouseEvent& event)
{
	ddAbstractTool::mouseDown(event);
	if(event.LeftDown())
	{
		getDrawingEditor()->view()->getDrawing()->add(figurePrototype);
		int x=event.GetPosition().x, y=event.GetPosition().y;
		figurePrototype->moveTo(x,y);
		getDrawingEditor()->view()->clearSelection();
		getDrawingEditor()->view()->addToSelection(figurePrototype);
	}
}

void ddCreationTool::mouseUp(ddMouseEvent& event)
{
	ddAbstractTool::mouseUp(event);
	getDrawingEditor()->setTool(new ddSelectionTool(getDrawingEditor()));
}

void ddCreationTool::activate()
{
	ddAbstractTool::activate();
	getDrawingEditor()->view()->SetCursor(wxCursor(wxCURSOR_CROSS));
}

void ddCreationTool::deactivate()
{
	ddAbstractTool::deactivate();
	getDrawingEditor()->view()->SetCursor(wxCursor(wxCURSOR_ARROW));
}

void ddCreationTool::setPrototype(ddIFigure *prototype)
{
	figurePrototype=prototype;
}

ddIFigure* ddCreationTool::getPrototype()
{
	return figurePrototype;
}
