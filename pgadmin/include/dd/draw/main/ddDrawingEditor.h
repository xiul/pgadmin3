//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawingEditor.h - Main class that manages all other classes
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDDRAWINGEDITOR_H
#define DDDRAWINGEDITOR_H

#include "dd/draw/main/ddDrawingView.h"
#include "dd/draw/tools/ddITool.h"

class ddDrawingEditor : public ddObject
{
public:
	ddDrawingEditor(wxWindow *owner);
    ~ddDrawingEditor();
	ddDrawingView* view();
	ddDrawing* model();
	ddITool* tool();
	void setTool(ddITool* tool);

protected:

private:
	ddDrawing *_model;
	ddDrawingView *_view;
	ddITool *_tool;
};
#endif
