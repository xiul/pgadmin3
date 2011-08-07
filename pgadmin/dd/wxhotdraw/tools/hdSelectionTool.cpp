//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdSelectionTool.cpp - Tool to allow selection of figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/tools/hdSelectionTool.h"
#include "dd/wxhotdraw/tools/hdITool.h"
#include "dd/wxhotdraw/main/hdDrawingView.h"
#include "dd/wxhotdraw/main/hdDrawingEditor.h"
#include "dd/wxhotdraw/tools/hdHandleTrackerTool.h"
#include "dd/wxhotdraw/tools/hdDragTrackerTool.h"
#include "dd/wxhotdraw/tools/hdSelectAreaTool.h"
#include "dd/wxhotdraw/tools/hdCanvasMenuTool.h"


class hdDrawingView;
class hdDrawingEditor;

hdSelectionTool::hdSelectionTool(hdDrawingView *owner):
	hdAbstractTool(owner)
{
	_delegateTool = NULL;
}

hdSelectionTool::~hdSelectionTool()
{
	if(_delegateTool)
		delete _delegateTool;
}

void hdSelectionTool::mouseDown(hdMouseEvent &event)
{
	hdITool::mouseDown(event);

	hdDrawingView *view = event.getView();
	int x = event.GetPosition().x, y = event.GetPosition().y;

	hdIHandle *handle = view->findHandle(view->getIdx(), x, y);
	if(handle)
	{
		setDelegateTool(view, new hdHandleTrackerTool(view, handle));
	}
	else
	{
		hdIFigure *figure = view->getDrawing()->findFigure(view->getIdx(), x, y);
		if(figure)
		{
			view->getDrawing()->bringToFront(figure);
			setDelegateTool(event.getView(), figure->CreateFigureTool(view, new hdDragTrackerTool(view, figure)));
		}
		else
		{
			setDelegateTool(event.getView(),  new hdCanvasMenuTool(view, new hdSelectAreaTool(view)) );
		}
	}

	hdITool *delegateTool = getDelegateTool();
	if (delegateTool)
		delegateTool->mouseDown(event);
}

void hdSelectionTool::mouseUp(hdMouseEvent &event)
{
	hdAbstractTool::mouseUp(event);
	hdITool *delegateTool = getDelegateTool();
	if (delegateTool)
		delegateTool->mouseUp(event);
}

void hdSelectionTool::mouseMove(hdMouseEvent &event)
{
	hdAbstractTool::mouseMove(event);
	hdDrawingView *view = event.getView();
	int x = event.GetPosition().x, y = event.GetPosition().y;
	hdIHandle *handle = view->findHandle(view->getIdx(), x, y);

	if(handle)
	{
		view->SetCursor(handle->createCursor());
	}
	else
	{
		hdIFigure *figure = view->getDrawing()->findFigure(view->getIdx(), x, y);
		if(figure)
		{
			view->SetCursor(wxCursor(wxCURSOR_HAND));
		}
		else
		{
			view->SetCursor(wxCursor(wxCURSOR_ARROW));
		}
	}
}

void hdSelectionTool::mouseDrag(hdMouseEvent &event)
{
	hdAbstractTool::mouseDrag(event);
	hdITool *delegateTool = getDelegateTool();
	if (delegateTool)
		delegateTool->mouseDrag(event);
}

void hdSelectionTool::keyDown(hdKeyEvent &event)
{
	if(getDelegateTool())
	{
		getDelegateTool()->keyDown(event);
	}
	if(event.GetKeyCode() == WXK_DELETE)
	{
		event.getView()->getDrawing()->deleteSelectedFigures();
	}
}

void hdSelectionTool::keyUp(hdKeyEvent &event)
{
	if(getDelegateTool())
	{
		getDelegateTool()->keyUp(event);
	}
}

void hdSelectionTool::setDelegateTool(hdDrawingView *view, hdITool *tool)
{
	if(_delegateTool)
	{
		_delegateTool->deactivate(view);
		delete _delegateTool;
	}

	_delegateTool = tool;

	if(_delegateTool)
	{
		_delegateTool->activate(view);
	}
}

hdITool *hdSelectionTool::getDelegateTool()
{
	return _delegateTool;
}

void hdSelectionTool::deleteAllFigures(hdDrawingView *view)
{
	view->getDrawing()->clearSelection();
	view->getDrawing()->deleteAllFigures();
}

