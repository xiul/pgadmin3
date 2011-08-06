//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdSimpleTextTool.h - Tool to allow edition of textTool with a double click or show a menu with a right click.
//
//////////////////////////////////////////////////////////////////////////

#ifndef WXHDSIMPLETEXTTOOL_H
#define WXHDSIMPLETEXTTOOL_H

#include "dd/wxhotdraw/tools/wxhdFigureTool.h"
#include "dd/wxhotdraw/figures/wxhdSimpleTextFigure.h"

class wxhdSimpleTextTool : public wxhdFigureTool
{

public:
	wxhdSimpleTextTool(wxhdDrawingView *view, wxhdIFigure *fig, wxhdITool *dt, bool fastEdit = true, wxString dialogCaption = wxEmptyString, wxString dialogMessage = wxEmptyString);
	~wxhdSimpleTextTool();
	virtual void mouseDown(wxhdMouseEvent &event);  //Mouse Right Click
	virtual void activate(wxhdDrawingView *view);
	virtual void deactivate(wxhdDrawingView *view);
	virtual void mouseDrag(wxhdMouseEvent &event);
	virtual void OnGenericPopupClick(wxCommandEvent &event, wxhdDrawingView *view);
	virtual bool callDialog(wxhdDrawingView *view);
	//Because a bug it was move to main View class instance as a hack. virtual void changeHandler(wxCommandEvent& event);
protected:
	bool withoutDialog;
	wxString dlgMessage, dlgCaption;
private:
	wxhdSimpleTextFigure *txtFigure;
	void calculateSizeEntry(wxhdDrawingView *view);
	bool showEdit;
//666 000	wxTextCtrl *edit;
//666 000	wxBitmapButton *okButton, *cancelButton;
	//Because a bug in the way wxwidgets connect events I can't declare it here, wxTextCtrl *edit, instead I do it on the view instance.
};

#endif
