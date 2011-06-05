//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractMenuFigure.h - Base class for figures that show a menu with right click
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDABSTRACTMENUFIGURE_H
#define DDABSTRACTMENUFIGURE_H
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/figures/ddAbstractFigure.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/utilities/ddCollection.h"

class ddAbstractMenuFigure : public ddAbstractFigure
{
public:
	ddAbstractMenuFigure();
    ~ddAbstractMenuFigure();
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
	virtual void createMenu(wxMenu &mnu) {}
	virtual void enablePopUp();
	virtual void disablePopUp();
	virtual bool menuEnabled();
	virtual void OnGenericPopupClick(wxCommandEvent& event, ddDrawingView *view=NULL);
protected:
	wxArrayString strings;
	bool showMenu;
private:

};
#endif
