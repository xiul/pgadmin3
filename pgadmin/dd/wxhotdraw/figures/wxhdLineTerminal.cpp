//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddLineTerminal.cpp - Base class for line terminal figure
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/wxhotdraw/figures/wxhdLineTerminal.h"
#include "dd/wxhotdraw/utilities/wxhdPoint.h"
#include "dd/wxhotdraw/utilities/wxhdRect.h"
#include "dd/wxhotdraw/utilities/wxhdGeometry.h"
#include "dd/wxhotdraw/main/wxhdDrawingView.h"

ddLineTerminal::ddLineTerminal()
{
	middle = ddPoint(0,0);
	terminalLinePen = wxPen(wxString(wxT("BLACK")),1,wxSOLID);
}

ddLineTerminal::~ddLineTerminal()
{
}

void ddLineTerminal::setLinePen(wxPen pen)
{
	terminalLinePen=pen;
}

ddPoint& ddLineTerminal::draw (wxBufferedDC& context, ddPoint& a, ddPoint& b, ddDrawingView *view)
{
	ddGeometry g;
	context.SetPen(terminalLinePen);

	ddPoint copyA = ddPoint (a);
	view->CalcScrolledPosition(copyA.x,copyA.y,&copyA.x,&copyA.y);
	ddPoint copyB = ddPoint (b);
	view->CalcScrolledPosition(copyB.x,copyB.y,&copyB.x,&copyB.y);
	context.DrawLine(copyA, copyB);
	
	context.SetPen(wxPen(wxString(wxT("BLACK")),1,wxSOLID));
	int x=copyA.x+g.ddabs(copyA.x - copyB.x);
	int y=copyA.y+g.ddabs(copyA.y - copyB.y);
	middle = ddPoint(x,y);

	context.DrawRectangle(wxRect(copyA.x,copyA.y,5,5));
	context.DrawCircle(copyA,10);
	return middle;
}
