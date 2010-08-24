//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddLineTerminal.cpp 
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

//DD-TODO: this need this ddDrawingView *view ??? or just avoid this and always pass calcscrolled points
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
	//DD-TODO: improve this function is bad just for testing, fix memory leak
	int x=copyA.x+g.ddabs(copyA.x - copyB.x);
	int y=copyA.y+g.ddabs(copyA.y - copyB.y);
	middle = ddPoint(x,y);

	//context.DrawCircle(*middle,10);
	context.DrawRectangle(wxRect(copyA.x,copyA.y,5,5));
	context.DrawCircle(copyA,10);
	return middle;
}
