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

#ifndef WXHDDRAWINGEDITOR_H
#define WXHDDRAWINGEDITOR_H

#include "dd/wxhotdraw/main/wxhdDrawingView.h"
#include "dd/wxhotdraw/tools/wxhdITool.h"

class wxhdDrawingEditor : public wxhdObject
{
public:
	wxhdDrawingEditor(wxWindow *owner);
    ~wxhdDrawingEditor();
	wxhdDrawingView* view();
	wxhdDrawing* model();
	wxhdITool* tool();
	void setTool(wxhdITool* tool);

protected:

private:
	wxhdDrawing *_model;
	wxhdDrawingView *_view;
	wxhdITool *_tool;
};
#endif
