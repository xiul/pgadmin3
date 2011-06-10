//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPolyLineFigureTool.h - Tool to allow creation of flexibility points at polylines figures
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDPOLYLINEFIGURETOOL_H
#define DDPOLYLINEFIGURETOOL_H

#include "dd/wxhotdraw/tools/wxhdFigureTool.h"


class ddPolyLineFigureTool : public ddFigureTool
{
public:
	ddPolyLineFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt);
    ~ddPolyLineFigureTool();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
protected:
private:
};
#endif
