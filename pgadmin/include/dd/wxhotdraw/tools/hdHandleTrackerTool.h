//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdHandleTrackerTool.h - A Tool that allow to use multiple handles
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdHANDLETRACKERTOOL_H
#define hdHANDLETRACKERTOOL_H

#include "dd/wxhotdraw/main/hdObject.h"
#include "dd/wxhotdraw/tools/hdITool.h"
#include "dd/wxhotdraw/handles/hdIHandle.h"
#include "dd/wxhotdraw/main/hdDrawingEditor.h"
#include "dd/wxhotdraw/tools/hdAbstractTool.h"


class hdHandleTrackerTool : public hdAbstractTool
{
public:
	hdHandleTrackerTool(hdDrawingView *view, hdIHandle *anchor);
	~hdHandleTrackerTool();

	virtual void mouseDown(hdMouseEvent &event);  //Mouse Right Click
	virtual void mouseUp(hdMouseEvent &event);
	virtual void mouseDrag(hdMouseEvent &event);

protected:
	hdIHandle *anchorHandle;

private:

};
#endif
