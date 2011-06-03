//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddCompositeFigureTool.h - A Tool that allow to change between all tools in a composite figure
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCOMPOSITEFIGURETOOL_H
#define DDCOMPOSITEFIGURETOOL_H

#include "dd/draw/tools/ddFigureTool.h"


class ddCompositeFigureTool : public ddFigureTool
{
public:
	ddCompositeFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt);
    ~ddCompositeFigureTool();
	virtual void setDefaultTool(ddITool *dt);
	virtual ddITool* getDefaultTool();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void activate();
	virtual void deactivate();
	virtual void setDelegateTool(ddITool *tool);
	virtual ddITool* getDelegateTool();
protected:
	ddITool *delegateTool;
private:
};
#endif
