//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdCompositeFigureTool.h - A Tool that allow to change between all tools in a composite figure
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdCOMPOSITEFIGURETOOL_H
#define hdCOMPOSITEFIGURETOOL_H

#include "dd/wxhotdraw/tools/hdFigureTool.h"


class hdCompositeFigureTool : public hdFigureTool
{
public:
	hdCompositeFigureTool(hdDrawingView *view, hdIFigure *fig, hdITool *dt);
	~hdCompositeFigureTool();
	virtual void setDefaultTool(hdITool *dt);
	virtual hdITool *getDefaultTool();
	virtual void mouseDown(hdMouseEvent &event);  //Mouse Right Click
	virtual void activate(hdDrawingView *view);
	virtual void deactivate(hdDrawingView *view);
	virtual void setDelegateTool(hdDrawingView *view, hdITool *tool);
	virtual hdITool *getDelegateTool();
protected:
	hdITool *delegateTool;
private:
};
#endif
