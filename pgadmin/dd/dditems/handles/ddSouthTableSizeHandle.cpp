//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddSouthTableSizeHandle.cpp 
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/handles/ddSouthTableSizeHandle.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/draw/utilities/ddGeometry.h"

ddSouthTableSizeHandle::ddSouthTableSizeHandle(ddTableFigure *owner, ddILocator *locator):
ddLocatorHandle(owner,locator)
{
	//drawTempRect=false;
}

ddRect& ddSouthTableSizeHandle::getDisplayBox()
{
	ddPoint p = locate();
	ddTableFigure *table = (ddTableFigure*) getOwner();
	displayBox.width=table->getFullSpace().width * 0.5;  //as defined at locator
	displayBox.height=3;
	displayBox.SetPosition(p);
	return displayBox;
}


wxCursor ddSouthTableSizeHandle::createCursor()
{
	return wxCursor(wxCURSOR_SIZENS);
}

void ddSouthTableSizeHandle::draw(wxBufferedDC& context, ddDrawingView *view)
{
}

ddSouthTableSizeHandle::~ddSouthTableSizeHandle()
{
}

void ddSouthTableSizeHandle::invokeStart(ddMouseEvent& event, ddDrawingView *view)
{
	anchorY=event.GetPosition().y;
}

void ddSouthTableSizeHandle::invokeStep(ddMouseEvent& event, ddDrawingView *view)
{
	int y=event.GetPosition().y;
	ddTableFigure *table = (ddTableFigure*) getOwner();
	wxFont font = settings->GetSystemFont();
	int colOffset = table->getColDefaultHeight(font);

	int divBy = (table->getTotalColumns() - table->getColumnsWindow());
	if(divBy<=0)
		divBy = table->getColumnsWindow();
	
	ddGeometry g;
	if ( g.ddabs(anchorY-y) > colOffset)
	{
		if((anchorY-y)>0)
		{
			table->setColumnsWindow(table->getColumnsWindow()-1);   //validated at table that dont't bypass max & min indexes
			//startPoint.y=y-10;
		}
		else
		{
			table->setColumnsWindow(table->getColumnsWindow()+1);   //validated at table that dont't bypass max & min indexes
		}
		anchorY=y;
	}

/*	endPoint.x=table->getFullSpace().x+table->getFullSpace().width;
	endPoint.y=y;
	*/
	//hack to update relationship position when table size change
	table->moveBy(-1,0);
	table->moveBy(1,0);
}

void ddSouthTableSizeHandle::invokeEnd(ddMouseEvent& event, ddDrawingView *view)
{
	//drawTempRect=false;

	//hack to update relationship position when table size change
	ddTableFigure *table = (ddTableFigure*) getOwner();
	table->moveBy(-1,0);
	table->moveBy(1,0);
}
