//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPolyLineFigureTool.cpp
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/tools/ddPolyLineFigureTool.h"
#include "dd/draw/tools/ddFigureTool.h"
#include "dd/draw/tools/ddHandleTrackerTool.h"
#include "dd/draw/figures/ddPolyLineFigure.h"
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/tools/ddMenuTool.h"

ddPolyLineFigureTool::ddPolyLineFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{

}

ddPolyLineFigureTool::~ddPolyLineFigureTool(){
}

void ddPolyLineFigureTool::mouseDown(ddMouseEvent& event){
	int x=event.GetPosition().x, y=event.GetPosition().y;
	setAnchorCoords(x,y);
	//DD-TODO: middle down or right and left down?
	if(event.LeftDClick()){
		ddPolyLineFigure *connection = (ddPolyLineFigure*) figure;
		connection->splitSegment(x,y);
		getDrawingEditor()->view()->clearSelection();
		getDrawingEditor()->view()->addToSelection(figure);
		ddIHandle *handle = getDrawingEditor()->view()->findHandle(x,y);
		//DD-TODO: set cursor to handle cursor
		getDrawingEditor()->view()->SetCursor(wxCURSOR_CROSS);//Temporary fix delete and change this.
		if(defaultTool)
			delete defaultTool;
		defaultTool = new ddHandleTrackerTool(getDrawingEditor(), handle);
	}
	defaultTool->mouseDown(event);
}