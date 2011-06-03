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

#include "dd/draw/main/ddObject.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/tools/ddAbstractTool.h"


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
