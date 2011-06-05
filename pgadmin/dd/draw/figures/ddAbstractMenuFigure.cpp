//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractMenuFigure.cpp - Base class for figures that show a menu with right click
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/draw/figures/ddAbstractMenuFigure.h"
#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/utilities/ddArrayCollection.h"
#include "dd/draw/main/ddDrawingView.h"
#include "dd/draw/tools/ddMenuTool.h"

ddAbstractMenuFigure::ddAbstractMenuFigure()
{
}

ddAbstractMenuFigure::~ddAbstractMenuFigure()
{
}


ddITool* ddAbstractMenuFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return new ddMenuTool(editor,this,defaultTool);
}

void ddAbstractMenuFigure::enablePopUp()
{
	showMenu = true;
}

void ddAbstractMenuFigure::disablePopUp()
{
	showMenu = false;
}

bool ddAbstractMenuFigure::menuEnabled()
{
	return 	showMenu;
}

void ddAbstractMenuFigure::OnGenericPopupClick(wxCommandEvent& event, ddDrawingView *view)
{
	//Action on popup goes here
	//strings[event.GetId()]
}
