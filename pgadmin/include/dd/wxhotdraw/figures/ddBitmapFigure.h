//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddCompositeFigure.h - Figure that draw a bitmap
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDBITMAPFIGURE_H
#define DDBITMAPFIGURE_H

#include "dd/wxhotdraw/figures/ddAbstractFigure.h"

class ddBitmapFigure : public ddAbstractFigure
{
public:
	ddBitmapFigure(wxBitmap image);
    ~ddBitmapFigure();

	virtual void basicDraw(wxBufferedDC& context, ddDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);		
	virtual void changeBitmap(wxBitmap image);
	virtual int getWidth();
	virtual int getHeight();

protected:

private:
	wxBitmap imageToDraw;
};
#endif
