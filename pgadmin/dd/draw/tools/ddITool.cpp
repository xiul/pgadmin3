//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddITool.cpp 
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/utilities/ddMouseEvent.h"

ddITool::ddITool()
{
	activatedValue=false;
	undoableValue=false;
}

ddITool::~ddITool()
{
}

void ddITool::mouseDown(ddMouseEvent& event)
{
/*
EVT_LEFT_DOWN(func)
EVT_MIDDLE_DOWN(func)
EVT_RIGHT_DOWN(func)
EVT_LEFT_DCLICK(func)
*/
}

void ddITool::mouseUp(ddMouseEvent& event)
{
/*
EVT_LEFT_UP(func)
EVT_MIDDLE_UP(func)
EVT_RIGHT_UP(func)
EVT_RIGHT_DCLICK(func)
*/
}

void ddITool::mouseMove(ddMouseEvent& event)
{
/*
EVT_MOTION(func)
*/
}

void ddITool::mouseDrag(ddMouseEvent& event)
{
/*
When a mouse is dragged this returns true: event.Dragging()
*/
}

void ddITool::keyDown(wxKeyEvent& event)
{
	//setAnchorCoords(event.GetPosition().x,event.GetPosition().y);
}

void ddITool::keyUp(wxKeyEvent& event)
{
}

void ddITool::activate()
{
	activatedValue=true;
}

void ddITool::deactivate()
{
	activatedValue=false;
}

bool ddITool::activated()
{
	return activatedValue;
}

bool ddITool::undoable()
{
	return undoableValue;
}
