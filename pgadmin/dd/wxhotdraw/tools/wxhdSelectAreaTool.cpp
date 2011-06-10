//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddSelectAreaTool.cpp - Tool to allow selection of figures inside a rectangle
//
//////////////////////////////////////////////////////////////////////////


#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/scrolwin.h>
#include <wx/pen.h>

// App headers
#include "dd/wxhotdraw/tools/wxhdSelectAreaTool.h"
#include "dd/wxhotdraw/tools/wxhdAbstractTool.h"
#include "dd/wxhotdraw/utilities/wxhdGeometry.h"


ddSelectAreaTool::ddSelectAreaTool(ddDrawingEditor *editor)
:ddAbstractTool(editor)
{
	view = editor->view();
}

ddSelectAreaTool::~ddSelectAreaTool()
{
}

void ddSelectAreaTool::mouseDown(ddMouseEvent& event)
{
	ddAbstractTool::mouseDown(event);
	if(!event.ShiftDown())
    {
		view->clearSelection();
	}
	if(event.LeftDown())
	{
		int x=event.GetPosition().x, y=event.GetPosition().y;
		selectionRect.x=x;
		selectionRect.y=y;
		selectionRect.width=0;
		selectionRect.height=0;
		drawSelectionRect();
	}
}

void ddSelectAreaTool::mouseUp(ddMouseEvent& event)
{
	ddAbstractTool::mouseUp(event);
	ddGeometry g;
	//hack-fix for bug when selecting figures from right to left
	if(event.LeftUp())
	{
		if( selectionRect.width < 0 ) 
		{
			int tmp;
			tmp=selectionRect.width;
			selectionRect.x += tmp;
			selectionRect.width=g.ddabs(tmp);

		}
		if( selectionRect.height < 0 )
		{
			int tmp;
			tmp=selectionRect.height;
			selectionRect.y += tmp;
			selectionRect.height=g.ddabs(tmp);
		}
		//end hack-fix 
		drawSelectionRect();
		selectFiguresOnRect(event.ShiftDown());
		view->disableSelRectDraw();
	}
}

void ddSelectAreaTool::mouseDrag(ddMouseEvent& event)
{
	ddAbstractTool::mouseDrag(event);
	if(event.LeftIsDown())
	{
		drawSelectionRect();
		int x=event.GetPosition().x, y=event.GetPosition().y;
		selectionRect.x=anchorX;
		selectionRect.y=anchorY;
		selectionRect.SetBottomRight(wxPoint(x,y));
		drawSelectionRect();
		view->ScrollToMakeVisible(event.GetPosition());
	}
}

void ddSelectAreaTool::selectFiguresOnRect(bool shiftPressed)
{
	ddIFigure *figure;
	ddIteratorBase *iterator = getDrawingEditor()->model()->figuresInverseEnumerator();
	while(iterator->HasNext())
	{
		figure=(ddIFigure *)iterator->Next();
		if(selectionRect.Contains(figure->displayBox()))
        {
			if(shiftPressed)
            {
				view->toggleSelection(figure);
			}
			else
			{
				view->addToSelection(figure);
			}
		}
	}
	delete iterator;
}

void ddSelectAreaTool::drawSelectionRect()
{
	view->setSelRect(selectionRect);
}

