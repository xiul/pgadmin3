//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdDrawingEditor.h - Main class that manages all other classes
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDDRAWINGVIEW_H
#define DDDRAWINGVIEW_H

#include "dd/wxhotdraw/main/wxhdDrawingView.h"

class ddDrawingView : public wxhdDrawingView
{
public:
	ddDrawingView(int diagram, wxWindow *ddParent, wxhdDrawingEditor *editor , wxSize size, wxhdDrawing *drawing);
	//Hack To allow right click menu at canvas without a figure
	virtual void createViewMenu(wxMenu &mnu);
	virtual void OnGenericViewPopupClick(wxCommandEvent &event);
protected:
private:
};
#endif
