//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddSimpleTextTool.cpp 
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/choicdlg.h>

// App headers
#include "dd/draw/tools/ddSimpleTextTool.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"

class ddDrawingEditor;

//Allow Edition of textTool (double click) or show a menu to modifiy in someway text (right click).
ddSimpleTextTool::ddSimpleTextTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{
	showEdit = false;
	//DD-TODO: set this value: edit.SetFont();  and fix layout and fix ID of edit because it should be a constant
	txtFigure = ((ddSimpleTextFigure *)this->getFigure());
	editor->view()->setSimpleTextToolFigure(NULL);
	edit = getDrawingEditor()->view()->getSimpleTextToolEdit();
	okButton = getDrawingEditor()->view()->getOkTxt();
	cancelButton = getDrawingEditor()->view()->getCancelTxt();
	calculateSizeEntry(editor->view());
}

ddSimpleTextTool::~ddSimpleTextTool()
{
}

void ddSimpleTextTool::calculateSizeEntry(ddDrawingView *view)
{
	if(edit)
	{
	//	edit->SetPosition(txtFigure->displayBox().GetPosition());
		ddPoint p=txtFigure->displayBox().GetPosition();
		view->CalcScrolledPosition(p.x,p.y,&p.x,&p.y);
		edit->SetPosition(p);
		edit->SetSize(txtFigure->displayBox().GetSize());
		okButton->SetPosition(wxPoint(p.x+edit->GetSize().GetWidth()+4,p.y));
		cancelButton->SetPosition(wxPoint(okButton->GetPosition().x+okButton->GetSize().GetWidth()+4,p.y));
		//DD-TODO: avoid in a future twin function in DrawingView because tool hack
	}
}

void ddSimpleTextTool::mouseDown(ddMouseEvent& event)
{	
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);

    // Right click to get the contextual menu
	if(txtFigure->menuEnabled() && event.RightDown())
	{
        wxMenu menu;
        getDrawingEditor()->view()->setSimpleTextToolFigure(txtFigure);
        txtFigure->createMenu(menu);
        getDrawingEditor()->view()->connectPopUpMenu(menu);
        ddPoint p=event.GetPosition();
        event.getView()->CalcScrolledPosition(p.x,p.y,&p.x,&p.y);
        getDrawingEditor()->view()->PopupMenu(&menu, p);
		return;
	}

    // Double click to rename an object
	if(event.LeftDClick())
	{
        wxString sNewValue = wxGetTextFromUser(_("New table name"), _("Rename table"), txtFigure->getText());
        if (!sNewValue.IsEmpty())
            txtFigure->setText(sNewValue);
		return;
	}
	getDefaultTool()->mouseDown(event);
}

void ddSimpleTextTool::activate()
{
	showEdit = false;
	ddFigureTool::activate();
}

void ddSimpleTextTool::deactivate()
{
	if(edit)
	{
        // Can't delete this objects because view is the owner of this objects
		edit->Hide();
		okButton->Hide();
		cancelButton->Hide();
		getDrawingEditor()->view()->setSimpleTextToolFigure(NULL);
	}
	ddFigureTool::deactivate();
}

void ddSimpleTextTool::mouseDrag(ddMouseEvent& event)
{
	if(!showEdit)
	{
		getDefaultTool()->mouseDrag(event);
	}
}

void ddSimpleTextTool::OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view)
{
	txtFigure->OnTextPopupClick(event,view);
}
