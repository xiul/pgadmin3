//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddScrollBarHandle.cpp - A handle for a table figure that allow to scroll it when table is not in full size
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/handles/ddScrollBarHandle.h"
#include "dd/wxhotdraw/utilities/wxhdPoint.h"
#include "dd/wxhotdraw/main/wxhdDrawingView.h"
#include "dd/wxhotdraw/utilities/wxhdGeometry.h"

//Images
#include "images/ddUp.xpm"
#include "images/ddDown.xpm"

ddScrollBarHandle::ddScrollBarHandle(ddTableFigure *owner, ddILocator *scrollBarLocator , wxSize &size):
ddLocatorHandle(owner,scrollBarLocator)
{
	table=owner;
	scrollLocator = scrollBarLocator;
	displayBox.SetSize(size);
	upBitmap=wxBitmap(ddUp_xpm);
	downBitmap=wxBitmap(ddDown_xpm);
}

ddScrollBarHandle::~ddScrollBarHandle()
{
}


wxCursor ddScrollBarHandle::createCursor()
{
	return wxCursor(wxCURSOR_HAND);
}

//avoid to use inflate on this handle
ddRect& ddScrollBarHandle::getDisplayBox()
{
	ddPoint p = locate();
	displayBox.width=11;  //as defined at locator
	displayBox.height=table->getColsSpace().height;
	displayBox.SetPosition(p);
	return displayBox;
}

void ddScrollBarHandle::draw(wxBufferedDC& context, ddDrawingView *view)
{
	context.SetBrush(*wxWHITE_BRUSH);
	wxPoint copy = getDisplayBox().GetPosition();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	context.DrawRectangle(copy.x,copy.y,getDisplayBox().width,getDisplayBox().height);
	context.DrawBitmap(upBitmap,copy.x+1,copy.y+2,true);
	context.DrawBitmap(downBitmap,copy.x+1,copy.y+getDisplayBox().height-2-downBitmap.GetHeight(),true);
	
	barSize.SetHeight((getDisplayBox().height-12)*0.45); 
	barSize.SetWidth(getDisplayBox().width-4);

	int divBy = (table->getTotalColumns() - table->getColumnsWindow());
	if(divBy<=0)
		divBy = table->getColumnsWindow();
	int colOffset = barSize.GetHeight() / divBy;
	int verticalPosBar=3+copy.y+downBitmap.GetHeight()+ colOffset*table->getTopColWindowIndex();
	if(table->getColumnsWindow()>1)
		context.DrawRectangle(wxPoint(copy.x+2,verticalPosBar),barSize);

}

void ddScrollBarHandle::invokeStart(ddMouseEvent &event, ddDrawingView *view)
{
	int y=event.GetPosition().y;
	anchorY=y;
	if( (y > (getDisplayBox().GetPosition().y + 2)) && (y <  (getDisplayBox().GetPosition().y + 2 + 6)) )  //6 image height
		table->columnsWindowUp();

	if( (y > (getDisplayBox().GetPosition().y+getDisplayBox().height-2-downBitmap.GetHeight()) ) && (y < (getDisplayBox().GetPosition().y+getDisplayBox().height-2) ) )
		table->columnsWindowDown();
}

void ddScrollBarHandle::invokeStep(ddMouseEvent &event, ddDrawingView *view)
{
	int y=event.GetPosition().y;
	int divBy = (table->getTotalColumns() - table->getColumnsWindow());
	if(divBy<=0)
		divBy = table->getColumnsWindow();
	int colOffset = barSize.GetHeight() / divBy;

	ddGeometry g;
	if ( g.ddabs(anchorY-y) > colOffset)
	{
		if((anchorY-y)>0)
		{
			table->columnsWindowUp();
		}
		else
		{
			table->columnsWindowDown();
		}
		anchorY=y;
	}
}

void ddScrollBarHandle::invokeEnd(ddMouseEvent &event, ddDrawingView *view)
{
}

ddPoint& ddScrollBarHandle::locate()
{
	if(scrollLocator)
	{
		pointLocate=scrollLocator->locate(getOwner());	
		return pointLocate;
	}
	else
		pointLocate=ddPoint(0,0);
		return pointLocate;
}
