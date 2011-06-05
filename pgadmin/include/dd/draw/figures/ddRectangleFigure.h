//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRectangleFigure.h - A simple rectangle  figure
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDRECTANGLEFIGURE_H
#define DDRECTANGLEFIGURE_H

#include <wx/dcbuffer.h>

#include "dd/draw/figures/ddAbstractFigure.h"


class ddDrawingView;

class ddRectangleFigure : public ddAbstractFigure
{
public:
	ddRectangleFigure();
    ~ddRectangleFigure();
	void basicDraw(wxBufferedDC& context, ddDrawingView *view);
	void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);
	void setRectangle(ddRect& rect);
	void setSize(wxSize& size);

protected:
private:
};
#endif
