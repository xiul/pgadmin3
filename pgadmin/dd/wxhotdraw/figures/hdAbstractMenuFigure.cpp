//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdAbstractMenuFigure.cpp - Base class for figures that show a menu with right click
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/wxhotdraw/figures/hdAbstractMenuFigure.h"
#include "dd/wxhotdraw/figures/hdIFigure.h"
#include "dd/wxhotdraw/utilities/hdArrayCollection.h"
#include "dd/wxhotdraw/main/hdDrawingView.h"
#include "dd/wxhotdraw/tools/hdMenuTool.h"

hdAbstractMenuFigure::hdAbstractMenuFigure()
{
}

hdAbstractMenuFigure::~hdAbstractMenuFigure()
{
}


hdITool *hdAbstractMenuFigure::CreateFigureTool(hdDrawingView *view, hdITool *defaultTool)
{
	return new hdMenuTool(view, this, defaultTool);
}

void hdAbstractMenuFigure::enablePopUp()
{
	showMenu = true;
}

void hdAbstractMenuFigure::disablePopUp()
{
	showMenu = false;
}

bool hdAbstractMenuFigure::menuEnabled()
{
	return 	showMenu;
}

void hdAbstractMenuFigure::OnGenericPopupClick(wxCommandEvent &event, hdDrawingView *view)
{
	//Action on popup goes here
	//strings[event.GetId()]
}
