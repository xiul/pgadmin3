//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDragCreationTool.cpp 
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/tools/ddDragCreationTool.h"

ddDragCreationTool::ddDragCreationTool(ddDrawingEditor *editor, ddIFigure *prototype):
ddCreationTool(editor, prototype)
{
}

ddDragCreationTool::~ddDragCreationTool(){
}


void ddDragCreationTool::mouseDrag(ddMouseEvent& event){
	if(event.LeftIsDown())
	{
		figurePrototype->displayBox().SetPosition(event.GetPosition());
	}
}
