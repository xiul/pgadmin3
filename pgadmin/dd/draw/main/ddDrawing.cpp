//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawing.cpp 
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/main/ddDrawing.h"
#include "dd/draw/utilities/ddArrayCollection.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/figures/ddIFigure.h"


ddDrawing::ddDrawing()
{
	figures = new ddCollection(new ddArrayCollection());
}

ddDrawing::~ddDrawing()
{
	ddIFigure *tmp;
	while(figures->count()>0)
	{
		tmp = (ddIFigure*) figures->getItemAt(0);
		figures->removeItemAt(0);
		delete tmp;
	}
	if(figures)
		delete figures;
}

void ddDrawing::add(ddIFigure *figure)
{
	if(figures)
		figures->addItem(figure);	
}

void ddDrawing::remove(ddIFigure *figure)
{
    if(figures)
		figures->removeItem(figure);
}

bool ddDrawing::includes(ddIFigure *figure)
{
	if(figures)
		return figures->existsObject(figure);
	return false;
}

ddIFigure* ddDrawing::findFigure(int x, int y)
{
	ddIFigure *tmp=NULL, *out=NULL;
	ddIteratorBase *iterator=figures->createIterator();
	while(iterator->HasNext())
    {
		 tmp=(ddIFigure *)iterator->Next();
		 if(tmp->containsPoint(x,y))
         {
			out=tmp;
			break;
		 }
	}

	delete iterator;;

	return out;
}

void ddDrawing::recalculateDisplayBox(){
	bool first=true;
	ddIFigure *figure=NULL;

	ddIteratorBase *iterator = figures->createIterator();
	while(iterator->HasNext())
	{
		figure=(ddIFigure *)iterator->Next();
		if(first)
		{
			displayBox=figure->displayBox();
			first=false;
		}
		else
		{
			displayBox.add(figure->displayBox());
		}
	}

	delete iterator;	
	/*
    //DD-TODO: generate this event
    OnSizeAllocated ();
    */
}

void ddDrawing::bringToFront(ddIFigure *figure)
{
	figures->bringToFront(figure);
}

void ddDrawing::sendToBack(ddIFigure *figure)
{
	figures->bringToBack(figure);
}

ddRect& ddDrawing::DisplayBox()
{
	return displayBox;
}

ddIteratorBase* ddDrawing::figuresEnumerator()
{
	return figures->createIterator();
}

ddIteratorBase* ddDrawing::figuresInverseEnumerator()
{
	return figures->createDownIterator();
}

//DD-TODO: need to do this delete to handles too?
void ddDrawing::deleteFigures()
{
	//figures->deleteAll();
	ddIFigure *tmp;
	while(figures->count()>0)
	{
		tmp = (ddIFigure*) figures->getItemAt(0);
		figures->removeItemAt(0);
		delete tmp;
	}
}
