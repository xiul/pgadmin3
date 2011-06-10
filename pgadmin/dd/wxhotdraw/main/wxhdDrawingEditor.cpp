//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawingEditor.cpp - Main class that manages all other classes
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/wxhotdraw/main/wxhdDrawingEditor.h"
#include "dd/wxhotdraw/main/wxhdDrawingView.h"
#include "dd/wxhotdraw/tools/wxhdITool.h"

ddDrawingEditor::ddDrawingEditor(wxWindow *owner)
{
	_model=new ddDrawing();
	_view = new ddDrawingView(owner,this,wxSize(1200, 1200),_model);
    // Set Scroll Bar & split
    _view->SetScrollbars( 10, 10, 127, 80 );
	_view->EnableScrolling(true,true);
	_view->AdjustScrollbars();
	_tool=NULL;
}

ddDrawingEditor::~ddDrawingEditor()
{
	if(_view)
		delete _view;
	if(_model)
		delete _model;
	if(_tool)
		delete _tool;
}

ddDrawingView* ddDrawingEditor::view()
{
	return _view;
}

ddDrawing* ddDrawingEditor::model()
{
	return _model;
}

ddITool* ddDrawingEditor::tool()
{
	return _tool;
}

void ddDrawingEditor::setTool(ddITool* tool)
{
	if(_tool)
		delete _tool;
	_tool=tool;
}
