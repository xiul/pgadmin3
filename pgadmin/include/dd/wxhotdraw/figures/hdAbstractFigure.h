//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdAbstractFigure.h - Base class for all figures
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdABSTRACTFIGURE_H
#define hdABSTRACTFIGURE_H
#include "dd/wxhotdraw/utilities/hdRect.h"
#include "dd/wxhotdraw/figures/hdIFigure.h"
#include "dd/wxhotdraw/tools/hdITool.h"
#include "dd/wxhotdraw/handles/hdIHandle.h"
#include "dd/wxhotdraw/utilities/hdCollection.h"

class hdAbstractFigure : public hdIFigure
{
public:
	hdAbstractFigure();
	~hdAbstractFigure();

	virtual bool canConnect ();
	virtual void draw(wxBufferedDC &context, hdDrawingView *view);
	virtual void drawSelected(wxBufferedDC &context, hdDrawingView *view);
	virtual bool includes(hdIFigure *figure);
	virtual hdITool *CreateFigureTool(hdDrawingView *view, hdITool *defaultTool);
	virtual void moveBy(int posIdx, int x, int y);
	virtual void basicMoveBy(int posIdx, int x, int y);
	virtual void moveTo(int posIdx, int x, int y);
	virtual bool containsPoint(int posIdx, int x, int y);
	virtual void onFigureChanged(int posIdx, hdIFigure *figure);

protected:
	virtual void basicDraw(wxBufferedDC &context, hdDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC &context, hdDrawingView *view);
	void willChange();
	void changed(int posIdx);
	void invalidate();
	wxColour fillColor, lineColor;
	double lineWidth;
	wxSize spaceForMovement;

private:

};
#endif
