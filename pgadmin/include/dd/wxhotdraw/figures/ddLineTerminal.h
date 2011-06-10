//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddLineTerminal.h - Base class for line terminal figure
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDLINETERMINAL_H
#define DDLINETERMINAL_H
#include "dd/wxhotdraw/figures/ddIFigure.h"
#include "dd/wxhotdraw/utilities/ddPoint.h"

class ddLineTerminal : public ddObject
{
public:
	ddLineTerminal();
    ~ddLineTerminal();

	virtual ddPoint& draw (wxBufferedDC& context, ddPoint& a, ddPoint& b, ddDrawingView *view);
	virtual void setLinePen(wxPen pen);
protected:
	wxPen terminalLinePen;	
private:
	ddPoint middle;

};
#endif
