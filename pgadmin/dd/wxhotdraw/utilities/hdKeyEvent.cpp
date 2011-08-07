//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdKeyEvent.h - Wrapper Class to integrate wxKeyEvent inside library.
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/utilities/hdKeyEvent.h"
#include "dd/wxhotdraw/main/hdDrawingView.h"

hdKeyEvent::hdKeyEvent(wxKeyEvent &event, hdDrawingView *owner):
	keyEvent(event)
{
	view = owner;
	keyCode = event.GetKeyCode();
}

int hdKeyEvent::GetKeyCode()
{
	return keyCode;
}

hdDrawingView *hdKeyEvent::getView()
{
	return view;
}
