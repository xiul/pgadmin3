//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDragCreationTool.h - A Tool that allow to move figure around view
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDDRAGCREATIONTOOL_H
#define DDDRAGCREATIONTOOL_H

#include "dd/wxhotdraw/tools/ddCreationTool.h"
#include "dd/wxhotdraw/main/ddDrawingEditor.h"


class ddDragCreationTool : public ddCreationTool
{
public:
	ddDragCreationTool(ddDrawingEditor *editor, ddIFigure *prototype);
    ~ddDragCreationTool();
	virtual void mouseDrag(ddMouseEvent& event);
};
#endif
