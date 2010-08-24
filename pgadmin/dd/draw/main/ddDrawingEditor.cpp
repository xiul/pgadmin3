//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawingEditor.cpp 
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/main/ddDrawingView.h"
#include "dd/draw/tools/ddITool.h"

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
