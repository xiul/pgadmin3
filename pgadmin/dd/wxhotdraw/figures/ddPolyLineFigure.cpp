//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPolyLineFigure.cpp - A simple line figure that can be split on several lines joined by flexibility points
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/wxhotdraw/figures/ddPolyLineFigure.h"
#include "dd/wxhotdraw/utilities/ddArrayCollection.h"
#include "dd/wxhotdraw/locators/ddILocator.h"
#include "dd/wxhotdraw/handles/ddPolyLineHandle.h"
#include "dd/wxhotdraw/figures/ddLineTerminal.h"
#include "dd/wxhotdraw/locators/ddPolyLineLocator.h"
#include "dd/wxhotdraw/utilities/ddGeometry.h"
#include "dd/wxhotdraw/tools/ddPolyLineFigureTool.h"
#include "dd/wxhotdraw/tools/ddMenuTool.h"

ddPolyLineFigure::ddPolyLineFigure()
{
	points = new ddArrayCollection();
	startTerminal = NULL;
	endTerminal = NULL;
	handlesChanged = false;
	startPoint=ddPoint(0,0);
	endPoint=ddPoint(0,0);
	pointAtPos=ddPoint(0,0);
	linePen = wxPen(wxString(wxT("BLACK")),1,wxSOLID);
}

ddPolyLineFigure::~ddPolyLineFigure()
{
	ddPoint *tmp; //Hack: If just delete points collection an error is raised.
	while(points->count()>0)
	{
		tmp = (ddPoint*) points->getItemAt(0);
		points->removeItemAt(0);
		delete tmp;
	}
	if(points)
		delete points;
	if(startTerminal)
		delete startTerminal;
	if(endTerminal)
		delete endTerminal;
}

ddRect& ddPolyLineFigure::getBasicDisplayBox()
{
	basicDisplayBox.height=0;
	basicDisplayBox.width=0;
	if(points->count() < 2)
	{
		
		return basicDisplayBox;
	}
	if(points->count()>=1)
	{
		basicDisplayBox.SetPosition(pointAt(0));
	}
	else
	{
		basicDisplayBox.SetPosition(wxPoint(0,0));
	}

	ddIteratorBase *iterator=points->createIterator();
	while(iterator->HasNext())
    {
		ddPoint *p = (ddPoint *) iterator->Next();
		ddRect r=ddRect(p->x,p->y,0,0);
		basicDisplayBox.add(r);
	}
	
	delete iterator;

	return basicDisplayBox;
}

int ddPolyLineFigure::pointCount()
{
    return points->count();
}

ddPoint& ddPolyLineFigure::getStartPoint()
{
	startPoint.x = ((ddPoint*)points->getItemAt(0))->x;
	startPoint.y = ((ddPoint*)points->getItemAt(0))->y;
	return startPoint;
}

void ddPolyLineFigure::setStartPoint(ddPoint point)
{
	willChange();
	if(points->count()==0)
		addPoint(point.x,point.y);
	else
	{
		ddPoint *p = (ddPoint *) points->getItemAt(0);
		p->x = point.x;
		p->y = point.y;
	}
		
	changed();
}

ddPoint& ddPolyLineFigure::getEndPoint()
{
	endPoint.x = ((ddPoint*)points->getItemAt(points->count()-1))->x;
	endPoint.y = ((ddPoint*)points->getItemAt(points->count()-1))->y;
	return endPoint;
}

void ddPolyLineFigure::setEndPoint(ddPoint point)
{
	willChange();
	if(points->count() < 2)
		addPoint(point.x,point.y);
	else
    {
		ddPoint *p = (ddPoint *) points->getItemAt(points->count()-1);
		p->x = point.x;
		p->y = point.y;
	}
	changed();
}

void ddPolyLineFigure::setStartTerminal(ddLineTerminal *terminal)
{
	startTerminal=terminal;
}

ddLineTerminal* ddPolyLineFigure::getStartTerminal()
{
	return startTerminal;
}

void ddPolyLineFigure::setEndTerminal(ddLineTerminal *terminal)
{
	endTerminal=terminal;
}

ddLineTerminal* ddPolyLineFigure::getEndTerminal()
{
	return endTerminal;
}

ddCollection* ddPolyLineFigure::handlesEnumerator()
{
	return handles;
}

void ddPolyLineFigure::addPoint (int x, int y)
{
	willChange();
	points->addItem((ddObject *) new ddPoint(x,y) );
	//Update handles
	handles->addItem(new ddPolyLineHandle(this, new ddPolyLineLocator(0), 0));
	updateHandlesIndexes();
	changed();
}

void ddPolyLineFigure::changed()
{
	handlesChanged = true;
}

void ddPolyLineFigure::removePointAt (int index)
{
	willChange();
	ddPoint *p = (ddPoint*) points->getItemAt(index);
	points->removeItemAt(index);
	delete p;
	//Update handles
	handles->removeItemAt(index);
	updateHandlesIndexes();
	changed();
}

void ddPolyLineFigure::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	basicDraw(context,view); 
}

void ddPolyLineFigure::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	if(points->count() < 2)
	{
		return;
	}
	ddPoint start, end;

	if(startTerminal)
	{
		startTerminal->setLinePen(linePen);
		start = startTerminal->draw(context, getStartPoint(), pointAt(1),view);
	}
	else
	{
		start = getStartPoint();
	}

	if(endTerminal)
	{
		endTerminal->setLinePen(linePen);
		end = endTerminal->draw(context, getEndPoint(), pointAt(pointCount() - 2),view);
	}
	else
	{
		end = getEndPoint();
	}

	context.SetPen(linePen);
	for(int i=0;i<points->count()-1;i++)
    {
		ddPoint *p1 = (ddPoint *) points->getItemAt(i);
		ddPoint *p2 = (ddPoint *) points->getItemAt(i+1);

		ddPoint copyP1 = ddPoint (*p1);
		view->CalcScrolledPosition(copyP1.x,copyP1.y,&copyP1.x,&copyP1.y);
		ddPoint copyP2 = ddPoint (*p2);
		view->CalcScrolledPosition(copyP2.x,copyP2.y,&copyP2.x,&copyP2.y);

		context.DrawLine(copyP1,copyP2);
	}
}

void ddPolyLineFigure::basicMoveBy(int x, int y)
{
	ddPoint *movPoint;
	for(int i=0 ; i<points->count() ; i++)
    {
		movPoint = (ddPoint *) points->getItemAt(i);
		movPoint->x += x;
		movPoint->y += y;
	}
}

ddITool* ddPolyLineFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return new ddPolyLineFigureTool(editor,this,new ddMenuTool(editor,this,defaultTool));
}


int ddPolyLineFigure::findSegment (int x, int y)
{
	for(int i=0 ; i<points->count()-1 ; i++)
    {
		ddPoint p1 = pointAt(i);
		ddPoint p2 = pointAt(i+1);
		ddGeometry g;
		if(g.lineContainsPoint(p1.x, p1.y, p2.x, p2.y, x, y))
        {
			return i+1;
		}
	}
	return -1;
}

ddPoint& ddPolyLineFigure::pointAt(int index)
{
	//hack to avoid error with bad indexes calls
	if(index<0)
	{
		pointAtPos.x = 0;
		pointAtPos.y = 0;
	}
	else
	{
		pointAtPos.x = ((ddPoint*)points->getItemAt(index))->x;
		pointAtPos.y = ((ddPoint*)points->getItemAt(index))->y;
	}
	return pointAtPos;
}

bool ddPolyLineFigure::containsPoint (int x, int y)
{
	ddRect rect = ddRect(this->displayBox());
	rect.Inflate(4,4);
	if(!rect.Contains(x,y))
    {
		return false;
	}

	for(int i=0 ; i<points->count()-1 ; i++)
    {
		ddPoint p1 = pointAt(i);
		ddPoint p2 = pointAt(i+1);
		ddGeometry g;
		if(g.lineContainsPoint(p1.x, p1.y, p2.x, p2.y, x, y))
        {
			return true;
		}
	}
	return false;
}

void ddPolyLineFigure::clearPoints()
{
	points->deleteAll();
}

void ddPolyLineFigure::insertPointAt (int index, int x, int y)
{
	willChange();
	points->insertAtIndex((ddObject*) new ddPoint(x,y), index);
	//Update handles
	handles->insertAtIndex(new ddPolyLineHandle(this, new ddPolyLineLocator(index), index),index);
	updateHandlesIndexes();
	changed();
}

void ddPolyLineFigure::setPointAt (int index, int x, int y)
{
	willChange();
	ddPoint *p = (ddPoint *) points->getItemAt(index);
	p->x = x;
	p->y = y;
	changed();
}

void ddPolyLineFigure::splitSegment(int x, int y) 
{
	int index = findSegment(x,y);

	if(index!=-1)
	{
		insertPointAt(index,x,y);
	}
}

void ddPolyLineFigure::updateHandlesIndexes()
{
    ddPolyLineHandle *h = NULL;
    for(int i=0;i<points->count();i++)
    {
        h = (ddPolyLineHandle*) handles->getItemAt(i);
        h->setIndex(i);
	}
}

void ddPolyLineFigure::setLinePen(wxPen pen)
{
	linePen=pen;
}
