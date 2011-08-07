//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdPolyLineFigureTool.h - Tool to allow creation of flexibility points at polylines figures
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdPOLYLINEFIGURETOOL_H
#define hdPOLYLINEFIGURETOOL_H

#include "dd/wxhotdraw/tools/hdFigureTool.h"


class hdPolyLineFigureTool : public hdFigureTool
{
public:
	hdPolyLineFigureTool(hdDrawingView *view, hdIFigure *fig, hdITool *dt);
	~hdPolyLineFigureTool();
	virtual void mouseDown(hdMouseEvent &event);  //Mouse Right Click
protected:
private:
};
#endif
