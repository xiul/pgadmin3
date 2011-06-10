//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractFigure.cpp - Base class for all figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/wxhotdraw/figures/ddAbstractFigure.h"
#include "dd/wxhotdraw/figures/ddIFigure.h"
#include "dd/wxhotdraw/utilities/ddArrayCollection.h"
#include "dd/wxhotdraw/main/ddDrawingView.h"

ddAbstractFigure::ddAbstractFigure()
{
}

ddAbstractFigure::~ddAbstractFigure()
{
}

bool ddAbstractFigure::canConnect ()
{
    return true;
}

bool ddAbstractFigure::includes(ddIFigure *figure)
{
	return (this==figure);	
}

void ddAbstractFigure::draw(wxBufferedDC& context, ddDrawingView *view)
{
	ddIFigure::draw(context,view);
	basicDraw(context,view);
}

void ddAbstractFigure::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);

	context.SetPen(*wxGREEN_PEN);
	context.SetBrush(wxBrush (wxColour(208, 208, 208),wxSOLID));
	context.DrawRectangle(copy);
}

void ddAbstractFigure::drawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	ddIFigure::drawSelected(context,view);	
	basicDrawSelected(context,view);
}

void ddAbstractFigure::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	
	context.SetPen(*wxRED_PEN);
	context.SetBrush(wxBrush (wxColour(133, 133, 133),wxSOLID));
	context.DrawRectangle(copy);
}


ddITool* ddAbstractFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return defaultTool;
}

void ddAbstractFigure::moveBy(int x, int y)
{
	willChange();
	basicMoveBy(x,y);
	changed();
}

void ddAbstractFigure::basicMoveBy(int x, int y)
{
		ddRect r = basicDisplayBox;
		r.x += x;
		r.y += y;
		basicDisplayBox = r;
}


void ddAbstractFigure::moveTo(int x, int y)
{
		ddRect r = basicDisplayBox;
		r.x = x;
		r.y = y;
		basicDisplayBox = r;
}

void ddAbstractFigure::willChange()
{
	invalidate();
}

void ddAbstractFigure::changed()
{
    invalidate();
    onFigureChanged(this);
}

void ddAbstractFigure::invalidate()
{

}

bool ddAbstractFigure::containsPoint(int x, int y)
{
	return basicDisplayBox.Contains(x,y);
}

void ddAbstractFigure::onFigureChanged(ddIFigure *figure)
{
	//go to figure procedure to alert observers of changes on this figure
	ddIFigure::onFigureChanged(figure);
}