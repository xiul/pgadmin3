//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawing.h - Main storage class for all objects of the model
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDDRAWING_H
#define DDDRAWING_H

#include "dd/wxhotdraw/figures/ddIFigure.h"

// Main model of drawing
class ddDrawing : public wxObject
{
public:
	ddDrawing();
	virtual ~ddDrawing();
	virtual void add(ddIFigure *figure);
	virtual void remove(ddIFigure *figure);
	virtual bool includes(ddIFigure *figure);
	virtual ddIFigure* findFigure(int x, int y);
	virtual void recalculateDisplayBox();
	virtual void bringToFront(ddIFigure *figure);
	virtual void sendToBack(ddIFigure *figure);
	virtual ddRect& DisplayBox();
	virtual ddIteratorBase* figuresEnumerator();
	virtual ddIteratorBase* figuresInverseEnumerator();
	virtual void deleteFigures();

protected:

private:
	ddCollection *figures;
	ddCollection *handles;
	ddRect displayBox;
};
#endif
