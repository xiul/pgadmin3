//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddConnectionCreationTool.cpp - A Tool that allow to create a connection figure between two figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/tools/wxhdConnectionCreationTool.h"
#include "dd/wxhotdraw/tools/wxhdSelectionTool.h"
#include "dd/wxhotdraw/main/wxhdDrawingView.h"

ddConnectionCreationTool::ddConnectionCreationTool(ddDrawingEditor *editor, ddLineConnection *figure):
ddAbstractTool(editor)
{
	toolConnection=figure;
	toolConnection->disconnectStart();
	toolConnection->disconnectEnd();
	handle=NULL;
	numClicks=0;
	dragged=false;
}

ddConnectionCreationTool::~ddConnectionCreationTool()
{
}

void ddConnectionCreationTool::mouseDrag(ddMouseEvent& event)
{
	if(handle && event.LeftIsDown())
	{
		dragged=true;
		handle->invokeStep(event,getDrawingEditor()->view());
	}
}

void ddConnectionCreationTool::mouseDown(ddMouseEvent& event)
{
	ddAbstractTool::mouseDown(event);
	if(event.LeftDown())
	{
		numClicks++;
		int x=event.GetPosition().x, y=event.GetPosition().y;
		ddDrawingView *view = getDrawingEditor()->view();
		ddIFigure *figure = view->getDrawing()->findFigure(x,y);

		if(figure)
		{
			if(numClicks==1)  //first mouse click to select start/end figure
			{
				toolConnection->setEndPoint(ddPoint(x,y));
				toolConnection->setStartPoint(ddPoint(x,y));
				toolConnection->connectStart(figure->connectorAt(x,y));
				toolConnection->updateConnection();
				view->add(toolConnection);
				view->clearSelection();
				view->addToSelection(toolConnection);
				handle = toolConnection->getEndHandle();
			}
			else if(numClicks>1) //second mouse click to select end figure only
			{
					toolConnection->setEndPoint(ddPoint(x,y));
					toolConnection->updateConnection();
			}
		}
		else
		{
			getDrawingEditor()->setTool(new ddSelectionTool(getDrawingEditor()));
		}
	}
}

void ddConnectionCreationTool::mouseUp(ddMouseEvent& event)
{
	if(event.LeftUp())
	{
		if(handle)
		{
			handle->invokeEnd(event,getDrawingEditor()->view());
		}

		if(toolConnection->getEndConnector()==NULL)
		{
			toolConnection->disconnectStart();
			toolConnection->disconnectEnd();
			getDrawingEditor()->view()->remove(toolConnection);
			getDrawingEditor()->view()->clearSelection();
		}
	}
	if(dragged || numClicks>1)   //if drag to select a figure or is second or higher click (to select end figure) then this tool ends.
	{
		getDrawingEditor()->setTool(new ddSelectionTool(getDrawingEditor()));
	}
	else if(!dragged && numClicks==1)  //if not dragged before and is first click then allow to select end, disconnecting it
	{
		toolConnection->disconnectEnd();
	}

}

void ddConnectionCreationTool::mouseMove(ddMouseEvent& event)
{
	int x=event.GetPosition().x, y=event.GetPosition().y;
	ddDrawingView *view = getDrawingEditor()->view();
	ddIFigure *figure = view->getDrawing()->findFigure(x,y);
	if(figure)
	{
		getDrawingEditor()->view()->SetCursor(wxCursor(wxCURSOR_PENCIL));
	}
	else
	{
		getDrawingEditor()->view()->SetCursor(wxCursor(wxCURSOR_CROSS));
	}

	if(handle && numClicks>0)
	{
		handle->invokeStep(event,getDrawingEditor()->view());
	}
}
