//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdSimpleTextTool.cpp - Tool to allow edition of textTool with a double click or show a menu with a right click.
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/choicdlg.h>

// App headers
#include "dd/wxhotdraw/tools/wxhdSimpleTextTool.h"
#include "dd/wxhotdraw/figures/wxhdSimpleTextFigure.h"

class wxhdDrawingEditor;

wxhdSimpleTextTool::wxhdSimpleTextTool(wxhdDrawingView *view, wxhdIFigure *fig, wxhdITool *dt, bool fastEdit , wxString dialogCaption, wxString dialogMessage):
	wxhdFigureTool(view, fig, dt)
{
	dlgMessage = dialogMessage;
	dlgCaption = dialogCaption;
	withoutDialog = fastEdit;
	showEdit = false;
	txtFigure = ((wxhdSimpleTextFigure *)this->getFigure());
//666 000		edit = getDrawingEditor()->view()->getSimpleTextToolEdit();
//666 000		okButton = getDrawingEditor()->view()->getOkTxt();
//666 000		cancelButton = getDrawingEditor()->view()->getCancelTxt();
	
//666 000	editor->view()->setSimpleTextToolFigure(NULL);
	ownerView->setSimpleTextToolFigure(NULL);
	
//666 000 calculateSizeEntry(editor->view());
	calculateSizeEntry(ownerView);
}

wxhdSimpleTextTool::~wxhdSimpleTextTool()
{
}

void wxhdSimpleTextTool::calculateSizeEntry(wxhdDrawingView *view)
{
	if(view->getSimpleTextToolEdit())
	{
		wxhdPoint p = txtFigure->displayBox().GetPosition(view->getIdx());
		view->CalcScrolledPosition(p.x, p.y, &p.x, &p.y);
		view->getSimpleTextToolEdit()->SetPosition(p);
		view->getSimpleTextToolEdit()->SetSize(txtFigure->displayBox().GetSize());
		view->getOkTxt()->SetPosition(wxPoint(p.x + view->getSimpleTextToolEdit()->GetSize().GetWidth() + 4, p.y));
		view->getCancelTxt()->SetPosition(wxPoint(view->getOkTxt()->GetPosition().x + view->getOkTxt()->GetSize().GetWidth() + 4, p.y));
		//Right now implemented with a hack (function at main view), but source of bug, probably can be tracked.
	}
}

void wxhdSimpleTextTool::mouseDown(wxhdMouseEvent &event)
{
	setAnchorCoords(event.GetPosition().x, event.GetPosition().y);

	// Right click to get the contextual menu
	if(txtFigure->menuEnabled() && event.RightDown())
	{
		wxMenu menu;
		//666 000 getDrawingEditor()->view()->setSimpleTextToolFigure(txtFigure, true);
		event.getView()->setSimpleTextToolFigure(txtFigure, true);
		txtFigure->createMenu(menu);
		//666 000 getDrawingEditor()->view()->connectPopUpMenu(menu);
		event.getView()->connectPopUpMenu(menu);
		wxhdPoint p = event.GetPosition();
		event.getView()->CalcScrolledPosition(p.x, p.y, &p.x, &p.y);
		//666 000 getDrawingEditor()->view()->PopupMenu(&menu, p);
		event.getView()->PopupMenu(&menu, p);
		return;
	}

	// Double click to rename an object
	if(event.LeftDClick())
	{
		if(withoutDialog)
		{
			//666 000 getDrawingEditor()->view()->setSimpleTextToolFigure(txtFigure);
			event.getView()->setSimpleTextToolFigure(txtFigure);
			showEdit = true;
			event.getView()->getSimpleTextToolEdit()->ChangeValue(txtFigure->getText()); //Same as SetValue but don't generated wxEVT_COMMAND_TEXT_UPDATED event
			calculateSizeEntry(event.getView());
			event.getView()->getSimpleTextToolEdit()->SetFocus();
			event.getView()->getSimpleTextToolEdit()->Show();
			event.getView()->getOkTxt()->Show();
			event.getView()->getCancelTxt()->Show();
		}
		else
		{
			callDialog(event.getView());
		}
		return;
	}
	getDefaultTool()->mouseDown(event);
}

void wxhdSimpleTextTool::activate(wxhdDrawingView *view)
{
	showEdit = false;
	wxhdFigureTool::activate(view);
}

void wxhdSimpleTextTool::deactivate(wxhdDrawingView *view)
{
	if(view->getSimpleTextToolEdit())
	{
		// Can't delete this objects because view is the owner of this objects
		view->getSimpleTextToolEdit()->Hide();
		view->getOkTxt()->Hide();
		view->getCancelTxt()->Hide();
		//666 000 getDrawingEditor()->view()->setSimpleTextToolFigure(NULL);
		view->setSimpleTextToolFigure(NULL);
	}
	wxhdFigureTool::deactivate(view);
}

void wxhdSimpleTextTool::mouseDrag(wxhdMouseEvent &event)
{
	if(!showEdit)
	{
		getDefaultTool()->mouseDrag(event);
	}
}

void wxhdSimpleTextTool::OnGenericPopupClick(wxCommandEvent &event, wxhdDrawingView *view)
{
	txtFigure->OnGenericPopupClick(event, view);
}

bool wxhdSimpleTextTool::callDialog(wxhdDrawingView *view)
{
	wxString sNewValue = wxGetTextFromUser(dlgMessage, dlgCaption, txtFigure->getText(), view);
	if (!sNewValue.IsEmpty())
	{
		txtFigure->setText(sNewValue);
		return true;
	}
	else
		return false;
}