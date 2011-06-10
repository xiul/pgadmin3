//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddITool.h - Base class for all tools
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDITOOL_H
#define DDITOOL_H

#include "dd/wxhotdraw/main/ddObject.h"
#include "dd/wxhotdraw/utilities/ddMouseEvent.h"


class ddITool : public ddObject
{
public:
	ddITool();
    ~ddITool();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseMove(ddMouseEvent& event);
	virtual void mouseDrag(ddMouseEvent& event);
	virtual void keyDown(wxKeyEvent& event);
	virtual void keyUp(wxKeyEvent& event);
	virtual void activate();
	virtual void deactivate();
	virtual bool activated();
	virtual bool undoable();

protected:

	bool activatedValue;
	bool undoableValue;

};
#endif
