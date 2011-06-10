//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRectangleFigure.cpp - A simple rectangle  figure
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/wxhotdraw/figures/wxhdRectangleFigure.h"
#include "dd/wxhotdraw/main/wxhdDrawingView.h"

ddRectangleFigure::ddRectangleFigure()
{
}

ddRectangleFigure::~ddRectangleFigure()
{
}

void ddRectangleFigure::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	context.DrawRectangle(copy);
}

void ddRectangleFigure::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	context.DrawRectangle(copy);
}

void ddRectangleFigure::setRectangle(ddRect& rect)
{
	basicDisplayBox=rect;
}

void ddRectangleFigure::setSize(wxSize& size)
{
	basicDisplayBox.SetSize(size);
}
