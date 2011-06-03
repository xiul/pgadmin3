//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractTool.cpp - An abstract tool to allow creation of all tools
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/tools/ddAbstractTool.h"

ddAbstractTool::ddAbstractTool(ddDrawingEditor *editor)
{
	anchorX=0;
	anchorY=0;
	ownerEditor=editor;
}

ddAbstractTool::~ddAbstractTool()
{
}

void ddAbstractTool::mouseDown(ddMouseEvent& event)
{
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);
}

void ddAbstractTool::mouseUp(ddMouseEvent& event)
{
}

void ddAbstractTool::mouseMove(ddMouseEvent& event)
{
}

void ddAbstractTool::mouseDrag(ddMouseEvent& event)
{
}

void ddAbstractTool::keyDown(wxKeyEvent& event)
{
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);
}

void ddAbstractTool::keyUp(wxKeyEvent& event)
{
}

void ddAbstractTool::setAnchorCoords(int x, int y)
{
	anchorX=x;
	anchorY=y;
}

ddDrawingEditor* ddAbstractTool::getDrawingEditor(){
	return ownerEditor;
}

