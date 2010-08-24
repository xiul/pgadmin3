//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddMouseEvent.cpp
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/utilities/ddMouseEvent.h"
#include "dd/draw/main/ddDrawingView.h"

//This allow only to use selected functions from event and for conversion reason as main goal (unscrolled points)
ddMouseEvent::ddMouseEvent(wxMouseEvent& event, ddDrawingView *owner):
mouseEvent(event)
{
    // mouseEvent is a private reference that should be initialized in constructor
	view=owner;
	m_shiftDown = event.m_shiftDown;
}

ddPoint& ddMouseEvent::GetPosition()
{
	return getUnScrolledPosition();
}

ddPoint& ddMouseEvent::getUnScrolledPosition()
{
	unScrolled = mouseEvent.GetPosition();
	view->CalcUnscrolledPosition(unScrolled.x,unScrolled.y,&unScrolled.x,&unScrolled.y);
	return unScrolled;
}

int ddMouseEvent::getUnScrolledPosX()
{
	return getUnScrolledPosition().x;
}

int ddMouseEvent::getUnScrolledPosY()
{
	return getUnScrolledPosition().y;
}

bool ddMouseEvent::LeftDClick()
{
	return mouseEvent.LeftDClick();
}

bool ddMouseEvent::ShiftDown()
{
	return mouseEvent.ShiftDown();
}

bool ddMouseEvent::RightDown()
{
	return mouseEvent.RightDown();
}

bool ddMouseEvent::LeftDown()
{
	return mouseEvent.LeftDown();
}

bool ddMouseEvent::LeftUp()
{
	return mouseEvent.LeftUp();
}

bool ddMouseEvent::LeftIsDown()
{
	return mouseEvent.LeftIsDown();
}

ddDrawingView* ddMouseEvent::getView()
{
	return view;
}