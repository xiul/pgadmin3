//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddCompositeFigureTool.cpp 
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/tools/ddCompositeFigureTool.h"
#include "dd/draw/figures/ddCompositeFigure.h"


ddCompositeFigureTool::ddCompositeFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{
	delegateTool = NULL;
}

ddCompositeFigureTool::~ddCompositeFigureTool()
{
	ddITool *tmpDefault=ddFigureTool::getDefaultTool();
	ddFigureTool *tmpDelegateDefault;

	if(delegateTool->ms_classInfo.IsKindOf(&ddFigureTool::ms_classInfo))
		tmpDelegateDefault = (ddFigureTool*)delegateTool;
	else 
		tmpDelegateDefault = NULL;

	if(delegateTool && delegateTool!=tmpDefault)
	{
		//Hack to avoid delete defaultTool (Delegate->defaultTool) of delegate tool 
		// if this is the same as defaultTool (this->defaultTool) of this Object.
		if(tmpDelegateDefault && tmpDelegateDefault->getDefaultTool()==tmpDefault)  
			tmpDelegateDefault->setDefaultTool(NULL);   
		delete delegateTool;
	}
}

void ddCompositeFigureTool::setDefaultTool(ddITool *dt)
{
	ddFigureTool::setDefaultTool(dt);
}

ddITool* ddCompositeFigureTool::getDefaultTool()
{
	if(delegateTool)
	{
		return delegateTool;
	}
	else
	{
		return ddFigureTool::getDefaultTool();
	}
}

void ddCompositeFigureTool::mouseDown(ddMouseEvent& event)
{
	int x=event.GetPosition().x, y=event.GetPosition().y;
	ddCompositeFigure *cfigure = (ddCompositeFigure*) getFigure();
	ddIFigure *figure = cfigure->findFigure(x,y);
	
	if(figure)
	{
		setDelegateTool(figure->CreateFigureTool(getDrawingEditor(),getDefaultTool()));
	}
	else
	{
		setDelegateTool(getDefaultTool());
	}

	if(delegateTool)
	{
		delegateTool->mouseDown(event);
	}
}

void ddCompositeFigureTool::activate()
{
	if(delegateTool)
	{
		delegateTool->activate();
	}
}

void ddCompositeFigureTool::deactivate()
{
	if(delegateTool)
	{
		delegateTool->deactivate();
	}
}

void ddCompositeFigureTool::setDelegateTool(ddITool *tool)
{
	if(delegateTool)
	{
		delegateTool->deactivate();
		delete delegateTool;
		delegateTool = NULL;
	}
	
	delegateTool=tool;
	if(delegateTool)
	{
		delegateTool->activate();
	}
}

ddITool* ddCompositeFigureTool::getDelegateTool()
{
	return delegateTool;
}
