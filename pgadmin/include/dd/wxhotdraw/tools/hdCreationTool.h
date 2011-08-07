//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdCreationTool.h - A Tool that create a figure by just click on view
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdCREATIONTOOL_H
#define hdCREATIONTOOL_H

#include "dd/wxhotdraw/tools/hdAbstractTool.h"
#include "dd/wxhotdraw/figures/hdIFigure.h"


class hdCreationTool : public hdAbstractTool
{
public:
	hdCreationTool(hdDrawingView *view, hdIFigure *prototype);
	~hdCreationTool();
	virtual void mouseDown(hdMouseEvent &event);  //Mouse Right Click
	virtual void mouseUp(hdMouseEvent &event);
	virtual void activate(hdDrawingView *view);
	virtual void deactivate(hdDrawingView *view);
	virtual void setPrototype(hdIFigure *prototype);
	virtual hdIFigure *getPrototype();

protected:
	hdIFigure *figurePrototype;


};
#endif
