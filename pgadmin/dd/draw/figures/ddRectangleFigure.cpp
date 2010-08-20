//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRectangleFigure.cpp
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/draw/figures/ddRectangleFigure.h"
#include "dd/draw/main/ddDrawingView.h"

ddRectangleFigure::ddRectangleFigure(){
	
}

ddRectangleFigure::~ddRectangleFigure(){

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