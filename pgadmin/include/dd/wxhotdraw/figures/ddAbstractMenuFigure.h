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
#include "dd/wxhotdraw/utilities/ddRect.h"
#include "dd/wxhotdraw/figures/ddAbstractFigure.h"
#include "dd/wxhotdraw/tools/ddITool.h"
#include "dd/wxhotdraw/handles/ddIHandle.h"
#include "dd/wxhotdraw/utilities/ddCollection.h"

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
