//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddColumnFigureTool.cpp - Improvement to ddFigureTool to work with composite table figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/tools/ddColumnFigureTool.h"
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/wxhotdraw/tools/wxhdDragTrackerTool.h"


ddColumnFigureTool::ddColumnFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{
	delegateTool = NULL;
}

ddColumnFigureTool::~ddColumnFigureTool()
{
	//This tool destructor is at compositeTool, because this is only a selection tool and neither tool belongs to it.
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
		
		//Hack to avoid delete ddDragTrackerTool Default twice because this figure is only used inside 
		//a table, and then create a compositeTool and default in both tools is ddDragTrackerTool
		//but I can't hard code this is Composite because that class should remain generic
		if(tmpDelegateDefault->getDefaultTool()->ms_classInfo.IsKindOf(&ddDragTrackerTool::ms_classInfo))
			tmpDelegateDefault->setDefaultTool(NULL);
		delete delegateTool;
	}
	
}

void ddColumnFigureTool::setDefaultTool(ddITool *dt)
{
	ddFigureTool::setDefaultTool(dt);
}

ddITool* ddColumnFigureTool::getDefaultTool()
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

void ddColumnFigureTool::mouseDown(ddMouseEvent& event)
{
	int x=event.GetPosition().x, y=event.GetPosition().y;
	ddColumnFigure *cfigure = (ddColumnFigure*) getFigure();
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

void ddColumnFigureTool::activate()
{
	if(delegateTool)
	{
		delegateTool->activate();
	}
}

void ddColumnFigureTool::deactivate()
{
	if(delegateTool)
	{
		delegateTool->deactivate();
	}
}

void ddColumnFigureTool::setDelegateTool(ddITool *tool)
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

ddITool* ddColumnFigureTool::getDelegateTool()
{
	return delegateTool;
}
