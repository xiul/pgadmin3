//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddConnectionCreationTool.h - A Tool that allow to create a connection figure between two figures
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCONNECTIONCREATIONTOOL_H
#define DDCONNECTIONCREATIONTOOL_H

#include "dd/wxhotdraw/tools/wxhdAbstractTool.h"
#include "dd/wxhotdraw/main/wxhdDrawingEditor.h"
#include "dd/wxhotdraw/figures/wxhdLineConnection.h"

class ddConnectionCreationTool : public ddAbstractTool
{
public:
	ddConnectionCreationTool(ddDrawingEditor *editor, ddLineConnection *figure);
    ~ddConnectionCreationTool();

	virtual void mouseDrag(ddMouseEvent& event);
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseMove(ddMouseEvent& event);
protected:

private:
	ddLineConnection *toolConnection;
	ddIHandle *handle;
	int numClicks;
	bool dragged;

};
#endif
