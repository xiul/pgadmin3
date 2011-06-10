//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddSimpleTextTool.h - Tool to allow edition of textTool with a double click or show a menu with a right click.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDSIMPLETEXTTOOL_H
#define DDSIMPLETEXTTOOL_H

#include "dd/wxhotdraw/tools/ddFigureTool.h"
#include "dd/wxhotdraw/figures/ddSimpleTextFigure.h"

class ddSimpleTextTool : public ddFigureTool
{

public:
	ddSimpleTextTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt, bool fastEdit = true, wxString dialogCaption = wxEmptyString, wxString dialogMessage = wxEmptyString);
    ~ddSimpleTextTool();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void activate();
	virtual void deactivate();
	virtual void mouseDrag(ddMouseEvent& event);
	virtual void OnGenericPopupClick(wxCommandEvent& event, ddDrawingView *view);
	virtual bool callDialog();
	//Because a bug it was move to main View class instance as a hack. virtual void changeHandler(wxCommandEvent& event);
protected:
	bool withoutDialog;
	wxString dlgMessage, dlgCaption;
private:
	ddSimpleTextFigure *txtFigure;
	void calculateSizeEntry(ddDrawingView *view);
	bool showEdit;
	wxTextCtrl *edit;
	wxBitmapButton *okButton, *cancelButton;
	//Because a bug in the way wxwidgets connect events I can't declare it here, wxTextCtrl *edit, instead I do it on the view instance.
};

#endif
