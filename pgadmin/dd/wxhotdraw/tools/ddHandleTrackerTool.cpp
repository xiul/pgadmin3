//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddHandleTrackerTool.cpp - A Tool that allow to use multiple handles
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/tools/ddHandleTrackerTool.h"
#include "dd/wxhotdraw/tools/ddAbstractTool.h"

ddHandleTrackerTool::ddHandleTrackerTool(ddDrawingEditor *editor, ddIHandle *anchor)
:ddAbstractTool(editor)
{
	view = editor->view();
	anchorHandle = anchor;
}

ddHandleTrackerTool::~ddHandleTrackerTool()
{
}

void ddHandleTrackerTool::mouseDown(ddMouseEvent& event)
{
	ddAbstractTool::mouseDown(event);
	anchorHandle->invokeStart(event,view);
}

void ddHandleTrackerTool::mouseUp(ddMouseEvent& event)
{
	anchorHandle->invokeEnd(event,view);
}

void ddHandleTrackerTool::mouseDrag(ddMouseEvent& event)
{
	anchorHandle->invokeStep(event,view);
}
