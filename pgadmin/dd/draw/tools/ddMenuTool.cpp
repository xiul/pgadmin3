//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddMenuTool.cpp 
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

//Allow Edition of textTool (double click) or show a menu to modifiy in someway text (right click).
ddMenuTool::ddMenuTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{
	menuFigure = (ddAbstractMenuFigure*) this->getFigure();
	editor->view()->setMenuToolFigure(NULL);
}

ddMenuTool::~ddMenuTool()
{
}

/*void ddSimpleTextTool::calculateSizeEntry(ddDrawingView *view)
{
	if(edit)
	{
	//	edit->SetPosition(txtFigure->displayBox().GetPosition());
		ddPoint p=txtFigure->displayBox().GetPosition();
		view->CalcScrolledPosition(p.x,p.y,&p.x,&p.y);
		edit->SetPosition(p);
		edit->SetSize(txtFigure->displayBox().GetSize());
		//DD-TODO: avoid in a future twin function in DrawingView because tool hack
	}
}*/

void ddMenuTool::mouseDown(ddMouseEvent& event)
{	
	//linux hack for bug
	int x=event.GetPosition().x, y=event.GetPosition().y;
	setAnchorCoords(x,y);
	
	if(menuFigure->menuEnabled() && event.RightDown())
	{
        wxMenu menu;
        getDrawingEditor()->view()->setMenuToolFigure(menuFigure);
        getDrawingEditor()->view()->setTextPopUpList(menuFigure->popupStrings(),menu);
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
	//getDrawingEditor()->view()->setSimpleTextToolFigure(NULL);
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
