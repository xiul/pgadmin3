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

#include "hotdraw/main/hdObject.h"
#include "hotdraw/tools/hdITool.h"
#include "hotdraw/handles/hdIHandle.h"
#include "hotdraw/main/hdDrawingEditor.h"
#include "hotdraw/tools/hdAbstractTool.h"


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
