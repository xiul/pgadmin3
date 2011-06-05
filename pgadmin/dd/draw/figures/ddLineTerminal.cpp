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
#include "dd/draw/figures/ddLineTerminal.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/utilities/ddGeometry.h"
#include "dd/draw/main/ddDrawingView.h"

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
