//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddMenuTool.h - Allow Edition of textTool (double click) or show a menu to modifiy in someway text (right click).
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDBITMAPTOOL_H
#define DDMENUTOOL_H

#include "dd/draw/tools/ddFigureTool.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"


class ddMenuTool : public ddFigureTool
{

public:
	ddMenuTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt);
    ~ddMenuTool();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void activate();
	virtual void deactivate();
	virtual void mouseDrag(ddMouseEvent& event);
	virtual void OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view);
	//Because a bug it was move to main View class as a hack. virtual void changeHandler(wxCommandEvent& event);
protected:
private:
	ddAbstractMenuFigure *menuFigure;
	//Because a bug in the way wxwidgets connect events I can't declare it here, wxTextCtrl *edit, instead I do it on the view.
};
#endif
