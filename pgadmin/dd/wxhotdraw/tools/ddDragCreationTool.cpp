//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDragCreationTool.cpp - A Tool that allow to move figure around view
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/tools/ddDragCreationTool.h"

ddDragCreationTool::ddDragCreationTool(ddDrawingEditor *editor, ddIFigure *prototype):
ddCreationTool(editor, prototype)
{
}

ddDragCreationTool::~ddDragCreationTool(){
}


void ddDragCreationTool::mouseDrag(ddMouseEvent& event)
{
	if(event.LeftIsDown())
	{
		figurePrototype->displayBox().SetPosition(event.GetPosition());
	}
}
