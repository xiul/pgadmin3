//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdITool.h - Base class for all tools
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdITOOL_H
#define hdITOOL_H

#include "dd/wxhotdraw/main/hdObject.h"
#include "dd/wxhotdraw/utilities/hdMouseEvent.h"
#include "dd/wxhotdraw/utilities/hdKeyEvent.h"


class hdITool : public hdObject
{
public:
	hdITool();
	~hdITool();
	virtual void mouseDown(hdMouseEvent &event);  //Mouse Right Click
	virtual void mouseUp(hdMouseEvent &event);
	virtual void mouseMove(hdMouseEvent &event);
	virtual void mouseDrag(hdMouseEvent &event);
	virtual void keyDown(hdKeyEvent &event);
	virtual void keyUp(hdKeyEvent &event);
	virtual void activate(hdDrawingView *view);
	virtual void deactivate(hdDrawingView *view);
	virtual bool activated();
	virtual bool undoable();

protected:

	bool activatedValue;
	bool undoableValue;

};
#endif
