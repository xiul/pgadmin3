//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddHandleTrackerTool.cpp 
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/tools/ddHandleTrackerTool.h"
#include "dd/draw/tools/ddAbstractTool.h"

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
