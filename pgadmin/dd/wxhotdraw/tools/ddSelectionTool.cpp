//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddSelectionTool.cpp - Tool to allow selection of figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/tools/ddSelectionTool.h"
#include "dd/wxhotdraw/tools/ddITool.h"
#include "dd/wxhotdraw/main/ddDrawingView.h"
#include "dd/wxhotdraw/main/ddDrawingEditor.h"
#include "dd/wxhotdraw/tools/ddHandleTrackerTool.h"
#include "dd/wxhotdraw/tools/ddDragTrackerTool.h"
#include "dd/wxhotdraw/tools/ddSelectAreaTool.h"


class ddDrawingView;
class ddDrawingEditor;

ddSelectionTool::ddSelectionTool(ddDrawingEditor *owner):
ddAbstractTool(owner)
{
	_delegateTool=NULL;
}

ddSelectionTool::~ddSelectionTool()
{
	if(_delegateTool)
		delete _delegateTool;
}

void ddSelectionTool::mouseDown(ddMouseEvent& event)
{
	ddITool::mouseDown(event);

	ddDrawingView *view=getDrawingEditor()->view();
	int x=event.GetPosition().x, y=event.GetPosition().y;

	ddIHandle *handle = view->findHandle(x,y);
	if(handle)
    {
		setDelegateTool(new ddHandleTrackerTool(getDrawingEditor(),handle));
	}
	else
	{
        ddIFigure *figure = view->getDrawing()->findFigure(x,y);
        if(figure)
        {
			view->getDrawing()->bringToFront(figure);
			setDelegateTool(figure->CreateFigureTool(getDrawingEditor(),new ddDragTrackerTool(getDrawingEditor(),figure)));
        }
        else
        {
            setDelegateTool(new ddSelectAreaTool(getDrawingEditor()));
        }
	}

	ddITool *delegateTool = getDelegateTool();
	if (delegateTool)
        delegateTool->mouseDown(event);
}

void ddSelectionTool::mouseUp(ddMouseEvent& event)
{
	ddAbstractTool::mouseUp(event);
	ddITool *delegateTool = getDelegateTool();
	if (delegateTool)
			delegateTool->mouseUp(event);
}

void ddSelectionTool::mouseMove(ddMouseEvent& event)
{
	ddAbstractTool::mouseMove(event);
	ddDrawingView *view=getDrawingEditor()->view();
	int x=event.GetPosition().x, y=event.GetPosition().y;
	ddIHandle *handle = view->findHandle(x,y);

	if(handle)
    {
		view->SetCursor(handle->createCursor());
	}
	else
	{
		ddIFigure *figure = view->getDrawing()->findFigure(x,y);
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

void ddSelectionTool::mouseDrag(ddMouseEvent& event)
{
	ddAbstractTool::mouseDrag(event);
	ddITool *delegateTool = getDelegateTool();
	if (delegateTool)
			delegateTool->mouseDrag(event);
}

void ddSelectionTool::keyDown(wxKeyEvent& event)
{
	if(getDelegateTool())
    {
		getDelegateTool()->keyDown(event);
	}
	if(event.GetKeyCode() == WXK_DELETE)
    {
		deleteFigures(getDrawingEditor()->view());
	}
}

void ddSelectionTool::keyUp(wxKeyEvent& event)
{
	if(getDelegateTool())
    {
		getDelegateTool()->keyUp(event);
	}
}

void ddSelectionTool::setDelegateTool(ddITool *tool)
{
	if(_delegateTool)
    {
		_delegateTool->deactivate();
		delete _delegateTool;
	}

	_delegateTool = tool;
	
	if(_delegateTool)
    {
		_delegateTool->activate();
	}
}

ddITool* ddSelectionTool::getDelegateTool()
{
	return _delegateTool;
}

void ddSelectionTool::deleteFigures(ddDrawingView *view)
{
	view->clearSelection();
	view->getDrawing()->deleteFigures();
}
