//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdConnectionCreationTool.cpp - A Tool that allow to create a connection figure between two figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/tools/wxhdConnectionCreationTool.h"
#include "dd/wxhotdraw/tools/wxhdSelectionTool.h"
#include "dd/wxhotdraw/main/wxhdDrawingView.h"

wxhdConnectionCreationTool::wxhdConnectionCreationTool(wxhdDrawingView *view, wxhdLineConnection *figure):
	wxhdAbstractTool(view)
{
	toolConnection = figure;
	toolConnection->disconnectStart();
	toolConnection->disconnectEnd();
	handle = NULL;
	numClicks = 0;
	dragged = false;
}

wxhdConnectionCreationTool::~wxhdConnectionCreationTool()
{
}

void wxhdConnectionCreationTool::mouseDrag(wxhdMouseEvent &event)
{
	if(handle && event.LeftIsDown())
	{
		dragged = true;
		//666 000 handle->invokeStep(event, getDrawingEditor()->view());
		handle->invokeStep(event, event.getView());
	}
}

void wxhdConnectionCreationTool::mouseDown(wxhdMouseEvent &event)
{
	wxhdAbstractTool::mouseDown(event);
	if(event.LeftDown())
	{
		numClicks++;
		int x = event.getScrolledPosX(), y = event.getScrolledPosY();
		wxhdDrawingView *view = event.getView();
		wxhdIFigure *figure = view->getDrawing()->findFigure(view->getIdx(), x, y);

		if(figure)
		{
			if(numClicks == 1) //first mouse click to select start/end figure
			{
				toolConnection->setEndPoint(wxhdPoint(x, y));
				toolConnection->setStartPoint(wxhdPoint(x, y));
				toolConnection->connectStart(figure->connectorAt(event.getView()->getIdx(), x, y));
				toolConnection->updateConnection(event.getView()->getIdx());
				view->getDrawing()->add(toolConnection);
				view->getDrawing()->clearSelection();
				view->getDrawing()->addToSelection(toolConnection);
				handle = toolConnection->getEndHandle();
			}
			else if(numClicks > 1) //second mouse click to select end figure only
			{
				toolConnection->setEndPoint(wxhdPoint(x, y));
				toolConnection->updateConnection(event.getView()->getIdx());
			}
		}
		else
		{
			//666 000 getDrawingEditor()->setTool(new wxhdSelectionTool(getDrawingEditor()));
			event.getView()->setTool(new wxhdSelectionTool(event.getView()));
		}
	}
}

void wxhdConnectionCreationTool::mouseUp(wxhdMouseEvent &event)
{
	if(event.LeftUp())
	{
		//Hack to allow one click and drag creation of connections
		if(handle)
		{
			if(!dragged && numClicks == 1) //mouse haven't be dragged and is first click of mouse at this tool
			{
				toolConnection->setEndPoint(event.GetPosition());
				toolConnection->updateConnection(event.getView()->getIdx());
			}
			else
			{
				//666 000 handle->invokeEnd(event, getDrawingEditor()->view());
				handle->invokeEnd(event, event.getView());
			}
		}

		if((toolConnection->getEndConnector() == NULL && numClicks > 1) || (toolConnection->getEndConnector() == NULL && dragged)) //Delete connection only if a second click a connection figures isn't found
		{
			toolConnection->disconnectStart();
			toolConnection->disconnectEnd();
			//666 000 getDrawingEditor()->view()->remove(toolConnection);
			event.getView()->getDrawing()->remove(toolConnection);
			//666 000 getDrawingEditor()->view()->clearSelection();
			event.getView()->getDrawing()->clearSelection();
		}
	}
	if(dragged || numClicks > 1) //if drag to select a figure or is second or higher click (to select end figure) then this tool ends.
	{
		//666 000 getDrawingEditor()->setTool(new wxhdSelectionTool(getDrawingEditor()));
		event.getView()->setTool(new wxhdSelectionTool(event.getView()));
	}
	else if(!dragged && numClicks == 1) //if not dragged before and is first click then allow to select end, disconnecting it
	{
		toolConnection->disconnectEnd();
	}

}

void wxhdConnectionCreationTool::mouseMove(wxhdMouseEvent &event)
{
	int x = event.GetPosition().x, y = event.GetPosition().y;
	//666 000 wxhdDrawingView *view = getDrawingEditor()->view();   //666 eliminar estas expresiones por ahi
	wxhdDrawingView *view = event.getView();   //666 eliminar estas expresiones por ahi
	//666 000 wxhdIFigure *figure = view->getDrawing()->findFigure(view->getIdx(), x, y);
	wxhdIFigure *figure = view->getDrawing()->findFigure(view->getIdx(), x, y);
	if(figure)
	{
		//666 000 getDrawingEditor()->view()->SetCursor(wxCursor(wxCURSOR_PENCIL));
		view->SetCursor(wxCursor(wxCURSOR_PENCIL));
	}
	else
	{
		//666 000 getDrawingEditor()->view()->SetCursor(wxCursor(wxCURSOR_CROSS));
		view->SetCursor(wxCursor(wxCURSOR_CROSS));
	}

	if(handle && numClicks > 0)
	{
		//666 000 handle->invokeStep(event, getDrawingEditor()->view());
		handle->invokeStep(event, view);
	}
}
