//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddMouseEvent.h - Wrapper Class to integrate conversion CalcUnscrolledPosition in a mouse event.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDMOUSEEVENT_H
#define DDMOUSEEVENT_H
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/main/ddObject.h"

class ddDrawingView;

class ddMouseEvent : public ddObject
{
	public:
		ddMouseEvent(wxMouseEvent& event, ddDrawingView *owner);
		ddPoint& getUnScrolledPosition();
		ddPoint& GetPosition();
		int getUnScrolledPosX();
		int getUnScrolledPosY();
		bool LeftDClick();
		bool LeftDown();
		bool LeftIsDown();
		bool LeftUp();
		bool ShiftDown();
		bool RightDown();
		bool m_shiftDown;
		ddDrawingView* getView();
private:
		ddDrawingView *view;
		wxMouseEvent& mouseEvent;
		ddPoint unScrolled;
};
#endif
