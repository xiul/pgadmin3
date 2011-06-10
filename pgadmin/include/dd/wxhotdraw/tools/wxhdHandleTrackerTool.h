//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddHandleTrackerTool.h - A Tool that allow to use multiple handles
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDHANDLETRACKERTOOL_H
#define DDHANDLETRACKERTOOL_H

#include "dd/wxhotdraw/main/wxhdObject.h"
#include "dd/wxhotdraw/tools/wxhdITool.h"
#include "dd/wxhotdraw/handles/wxhdIHandle.h"
#include "dd/wxhotdraw/main/wxhdDrawingEditor.h"
#include "dd/wxhotdraw/tools/wxhdAbstractTool.h"


class ddHandleTrackerTool : public ddAbstractTool
{
public:
	ddHandleTrackerTool(ddDrawingEditor *editor, ddIHandle *anchor);
    ~ddHandleTrackerTool();

	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseDrag(ddMouseEvent& event);

protected:
	ddIHandle *anchorHandle;

private:

	ddDrawingView *view;

};
#endif
