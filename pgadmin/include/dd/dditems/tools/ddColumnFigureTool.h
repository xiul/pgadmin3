//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddColumnFigureTool.h - Improvement to ddFigureTool to work with composite table figures
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCOLUMNFIGURETOOL_H
#define DDCOLUMNFIGURETOOL_H

#include "dd/draw/tools/ddFigureTool.h"


class ddColumnFigureTool : public ddFigureTool
{
public:
	ddColumnFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt);
    ~ddColumnFigureTool();
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
