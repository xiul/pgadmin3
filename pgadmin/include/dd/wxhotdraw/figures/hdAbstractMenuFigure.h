//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdAbstractMenuFigure.h - Base class for figures that show a menu with right click
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdABSTRACTMENUFIGURE_H
#define hdABSTRACTMENUFIGURE_H
#include "dd/wxhotdraw/utilities/hdRect.h"
#include "dd/wxhotdraw/figures/hdAttributeFigure.h"
#include "dd/wxhotdraw/tools/hdITool.h"
#include "dd/wxhotdraw/handles/hdIHandle.h"
#include "dd/wxhotdraw/utilities/hdCollection.h"

class hdAbstractMenuFigure : public hdAttributeFigure
{
public:
	hdAbstractMenuFigure();
	~hdAbstractMenuFigure();
	virtual hdITool *CreateFigureTool(hdDrawingView *view, hdITool *defaultTool);
	virtual void createMenu(wxMenu &mnu) {}
	virtual void enablePopUp();
	virtual void disablePopUp();
	virtual bool menuEnabled();
	virtual void OnGenericPopupClick(wxCommandEvent &event, hdDrawingView *view = NULL);
protected:
	wxArrayString strings;
	bool showMenu;
private:

};
#endif
