//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdLineTerminal.cpp - Base class for line terminal figure
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/wxhotdraw/figures/hdLineTerminal.h"
#include "dd/wxhotdraw/utilities/hdPoint.h"
#include "dd/wxhotdraw/utilities/hdRect.h"
#include "dd/wxhotdraw/utilities/hdGeometry.h"
#include "dd/wxhotdraw/main/hdDrawingView.h"

hdLineTerminal::hdLineTerminal()
{
	middle = hdPoint(0, 0);
	terminalLinePen = wxPen(wxString(wxT("BLACK")), 1, wxSOLID);
}

hdLineTerminal::~hdLineTerminal()
{
}

void hdLineTerminal::setLinePen(wxPen pen)
{
	terminalLinePen = pen;
}

hdPoint &hdLineTerminal::draw (wxBufferedDC &context, hdPoint &a, hdPoint &b, hdDrawingView *view)
{
	hdGeometry g;
	context.SetPen(terminalLinePen);

	hdPoint copyA = hdPoint (a);
	view->CalcScrolledPosition(copyA.x, copyA.y, &copyA.x, &copyA.y);
	hdPoint copyB = hdPoint (b);
	view->CalcScrolledPosition(copyB.x, copyB.y, &copyB.x, &copyB.y);
	context.DrawLine(copyA, copyB);

	context.SetPen(wxPen(wxString(wxT("BLACK")), 1, wxSOLID));
	int x = copyA.x + g.ddabs(copyA.x - copyB.x);
	int y = copyA.y + g.ddabs(copyA.y - copyB.y);
	middle = hdPoint(x, y);

	context.DrawRectangle(wxRect(copyA.x, copyA.y, 5, 5));
	context.DrawCircle(copyA, 10);
	return middle;
}
