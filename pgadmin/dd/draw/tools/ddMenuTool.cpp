//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddMenuTool.cpp - Allow Edition of textTool (double click) or show a menu to modifiy in someway text (right click).
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/choicdlg.h>

// App headers
#include "dd/draw/tools/ddMenuTool.h"
#include "dd/draw/figures/ddIFigure.h"

class ddDrawingEditor;

ddMenuTool::ddMenuTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{
	menuFigure = (ddAbstractMenuFigure*) this->getFigure();
	editor->view()->setMenuToolFigure(NULL);
}

ddMenuTool::~ddMenuTool()
{
}

void ddMenuTool::mouseDown(ddMouseEvent& event)
{	
	//Linux hack for bug
	int x=event.GetPosition().x, y=event.GetPosition().y;
	setAnchorCoords(x,y);
	
	if(menuFigure->menuEnabled() && event.RightDown())
	{
        wxMenu menu;
        getDrawingEditor()->view()->setMenuToolFigure(menuFigure);
        menuFigure->createMenu(menu);
        getDrawingEditor()->view()->connectPopUpMenu(menu);
        ddPoint p=event.GetPosition();
        event.getView()->CalcScrolledPosition(p.x,p.y,&p.x,&p.y);
        getDrawingEditor()->view()->PopupMenu(&menu, p);
		return;
	}

	getDefaultTool()->mouseDown(event);
}

void ddMenuTool::activate()
{
	ddFigureTool::activate();
}

void ddMenuTool::deactivate()
{
	ddFigureTool::deactivate();
}

void ddMenuTool::mouseDrag(ddMouseEvent& event)
{
		getDefaultTool()->mouseDrag(event);
}

void ddMenuTool::OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view)
{
	menuFigure->OnTextPopupClick(event,view);
}
