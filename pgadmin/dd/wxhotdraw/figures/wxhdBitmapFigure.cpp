//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddCompositeFigure.cpp - Figure that draw a bitmap
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/wxhotdraw/figures/wxhdBitmapFigure.h"
#include "dd/wxhotdraw/main/wxhdDrawingView.h"


ddBitmapFigure::ddBitmapFigure(wxBitmap image)
{
	imageToDraw=image;
	this->getBasicDisplayBox().width=imageToDraw.GetWidth();
	this->getBasicDisplayBox().height=imageToDraw.GetHeight();
}

ddBitmapFigure::~ddBitmapFigure()
{
}

void ddBitmapFigure::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	context.DrawBitmap(imageToDraw,copy.GetPosition(),true);
}

void ddBitmapFigure::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	basicDraw(context,view);
}

void ddBitmapFigure::changeBitmap(wxBitmap image)
{
	imageToDraw=image;
	this->getBasicDisplayBox().width=imageToDraw.GetWidth();
	this->getBasicDisplayBox().height=imageToDraw.GetHeight();
}

int ddBitmapFigure::getWidth()
{
	return imageToDraw.GetWidth();
}

int ddBitmapFigure::getHeight()
{
	return imageToDraw.GetHeight();
}
