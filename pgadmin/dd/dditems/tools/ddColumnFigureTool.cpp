//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddColumnFigureTool.cpp - Improvement to wxhdFigureTool to work with composite table figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/tools/ddColumnFigureTool.h"
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/wxhotdraw/tools/wxhdDragTrackerTool.h"


ddColumnFigureTool::ddColumnFigureTool(wxhdDrawingView *view, wxhdIFigure *fig, wxhdITool *dt):
	wxhdFigureTool(view, fig, dt)
{
	delegateTool = NULL;
}

ddColumnFigureTool::~ddColumnFigureTool()
{
	//This tool destructor is at compositeTool, because this is only a selection tool and neither tool belongs to it.
	wxhdITool *tmpDefault = wxhdFigureTool::getDefaultTool();
	wxhdFigureTool *tmpDelegateDefault;

	if(delegateTool->ms_classInfo.IsKindOf(&wxhdFigureTool::ms_classInfo))
		tmpDelegateDefault = (wxhdFigureTool *)delegateTool;
	else
		tmpDelegateDefault = NULL;

	if(delegateTool && delegateTool != tmpDefault)
	{
		//Hack to avoid delete defaultTool (Delegate->defaultTool) of delegate tool
		// if this is the same as defaultTool (this->defaultTool) of this Object.
		if(tmpDelegateDefault && tmpDelegateDefault->getDefaultTool() == tmpDefault)
			tmpDelegateDefault->setDefaultTool(NULL);

		//Hack to avoid delete wxhdDragTrackerTool Default twice because this figure is only used inside
		//a table, and then create a compositeTool and default in both tools is wxhdDragTrackerTool
		//but I can't hard code this is Composite because that class should remain generic
		if(tmpDelegateDefault->getDefaultTool()->ms_classInfo.IsKindOf(&wxhdDragTrackerTool::ms_classInfo))
			tmpDelegateDefault->setDefaultTool(NULL);
		delete delegateTool;
	}

}

void ddColumnFigureTool::setDefaultTool(wxhdITool *dt)
{
	wxhdFigureTool::setDefaultTool(dt);
}

wxhdITool *ddColumnFigureTool::getDefaultTool()
{
	if(delegateTool)
	{
		return delegateTool;
	}
	else
	{
		return wxhdFigureTool::getDefaultTool();
	}
}

void ddColumnFigureTool::mouseDown(wxhdMouseEvent &event)
{
	int x = event.GetPosition().x, y = event.GetPosition().y;
	ddColumnFigure *cfigure = (ddColumnFigure *) getFigure();
	wxhdIFigure *figure = cfigure->findFigure(event.getView()->getIdx(), x, y);

	if(figure)
	{
		setDelegateTool(event.getView(), figure->CreateFigureTool(event.getView(), getDefaultTool()));
	}
	else
	{
		setDelegateTool(event.getView(), getDefaultTool());
	}

	if(delegateTool)
	{
		delegateTool->mouseDown(event);
	}
}

void ddColumnFigureTool::activate(wxhdDrawingView *view)
{
	if(delegateTool)
	{
		delegateTool->activate(view);
	}
}

void ddColumnFigureTool::deactivate(wxhdDrawingView *view)
{
	if(delegateTool)
	{
		delegateTool->deactivate(view);
	}
}

void ddColumnFigureTool::setDelegateTool(wxhdDrawingView *view, wxhdITool *tool)
{
	if(delegateTool)
	{
		delegateTool->deactivate(view);
		delete delegateTool;
		delegateTool = NULL;
	}

	delegateTool = tool;
	if(delegateTool)
	{
		delegateTool->activate(view);
	}
}

wxhdITool *ddColumnFigureTool::getDelegateTool()
{
	return delegateTool;
}
