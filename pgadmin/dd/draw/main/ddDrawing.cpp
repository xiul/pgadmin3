//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawing.cpp - Main storage class for all objects of the model
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
}

void ddDrawing::bringToFront(ddIFigure *figure)
{
	//To bring to front this figure need to be at last position when is draw
	//because this reason sendToBack (last position) is used.
	figures->sendToBack(figure);
}

void ddDrawing::sendToBack(ddIFigure *figure)
{
	//To send to back this figure need to be at first position when is draw
	//because this reason bringToFront (1st position) is used.
	figures->bringToFront(figure);
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

void ddDrawing::deleteFigures()
{
	ddIFigure *tmp;
	while(figures->count()>0)
	{
		tmp = (ddIFigure*) figures->getItemAt(0);
		figures->removeItemAt(0);
		delete tmp;
	}
	//handles delete it together with figures
}
