//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdAbstractFigure.cpp - Base class for all figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/wxhotdraw/figures/wxhdAbstractFigure.h"
#include "dd/wxhotdraw/figures/wxhdIFigure.h"
#include "dd/wxhotdraw/utilities/wxhdArrayCollection.h"
#include "dd/wxhotdraw/main/wxhdDrawingView.h"

wxhdAbstractFigure::wxhdAbstractFigure()
{
}

wxhdAbstractFigure::~wxhdAbstractFigure()
{
}

bool wxhdAbstractFigure::canConnect ()
{
    return true;
}

bool wxhdAbstractFigure::includes(wxhdIFigure *figure)
{
	return (this==figure);	
}

void wxhdAbstractFigure::draw(wxBufferedDC& context, wxhdDrawingView *view)
{
	wxhdIFigure::draw(context,view);
	basicDraw(context,view);
}

void wxhdAbstractFigure::basicDraw(wxBufferedDC& context, wxhdDrawingView *view)
{
	wxhdRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);

	context.SetPen(*wxGREEN_PEN);
	context.SetBrush(wxBrush (wxColour(208, 208, 208),wxSOLID));
	context.DrawRectangle(copy);
}

void wxhdAbstractFigure::drawSelected(wxBufferedDC& context, wxhdDrawingView *view)
{
	wxhdIFigure::drawSelected(context,view);	
	basicDrawSelected(context,view);
}

void wxhdAbstractFigure::basicDrawSelected(wxBufferedDC& context, wxhdDrawingView *view)
{
	wxhdRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	
	context.SetPen(*wxRED_PEN);
	context.SetBrush(wxBrush (wxColour(133, 133, 133),wxSOLID));
	context.DrawRectangle(copy);
}


wxhdITool* wxhdAbstractFigure::CreateFigureTool(wxhdDrawingEditor *editor, wxhdITool *defaultTool)
{
	return defaultTool;
}

void wxhdAbstractFigure::moveBy(int x, int y)
{
	willChange();
	basicMoveBy(x,y);
	changed();
}

void wxhdAbstractFigure::basicMoveBy(int x, int y)
{
		wxhdRect r = basicDisplayBox;
		r.x += x;
		r.y += y;
		basicDisplayBox = r;
}


void wxhdAbstractFigure::moveTo(int x, int y)
{
		wxhdRect r = basicDisplayBox;
		r.x = x;
		r.y = y;
		basicDisplayBox = r;
}

void wxhdAbstractFigure::willChange()
{
	invalidate();
}

void wxhdAbstractFigure::changed()
{
    invalidate();
    onFigureChanged(this);
}

void wxhdAbstractFigure::invalidate()
{

}

bool wxhdAbstractFigure::containsPoint(int x, int y)
{
	return basicDisplayBox.Contains(x,y);
}

void wxhdAbstractFigure::onFigureChanged(wxhdIFigure *figure)
{
	//go to figure procedure to alert observers of changes on this figure
	wxhdIFigure::onFigureChanged(figure);
}