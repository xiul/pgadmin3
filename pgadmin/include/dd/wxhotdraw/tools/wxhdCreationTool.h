//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddCreationTool.h - A Tool that create a figure by just click on view
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCREATIONTOOL_H
#define DDCREATIONTOOL_H

#include "dd/wxhotdraw/tools/wxhdAbstractTool.h"
#include "dd/wxhotdraw/figures/wxhdIFigure.h"


class ddCreationTool : public ddAbstractTool
{
public:
	ddCreationTool(ddDrawingEditor *editor, ddIFigure *prototype);
    ~ddCreationTool();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void activate();
	virtual void deactivate();
	virtual void setPrototype(ddIFigure *prototype);
	virtual ddIFigure* getPrototype();

protected:
	ddIFigure *figurePrototype;


};
#endif
