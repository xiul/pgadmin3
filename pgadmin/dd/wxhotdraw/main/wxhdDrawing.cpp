//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdDrawing.cpp - Main storage class for all objects of the diagram, 
// their functions are used by model and shouldn't be called directly
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/main/wxhdDrawing.h"
#include "dd/wxhotdraw/utilities/wxhdArrayCollection.h"
#include "dd/wxhotdraw/utilities/wxhdRect.h"
#include "dd/wxhotdraw/figures/wxhdIFigure.h"


wxhdDrawing::wxhdDrawing(wxhdDrawingEditor *owner)
{
	figures = new wxhdCollection(new wxhdArrayCollection());
	selection =  new wxhdCollection(new wxhdArrayCollection());
	usedView = NULL;
	ownerEditor = owner;
}

wxhdDrawing::~wxhdDrawing()
{
	//clear selection
	if(selection)
	{
		selection->removeAll();
		delete selection;
	}

	//Cannot delete figures, because they belong to model not to diagram
	wxhdIFigure *tmp;
	while(figures->count() > 0)
	{
		tmp = (wxhdIFigure *) figures->getItemAt(0);
		figures->removeItemAt(0);
	}

	if(figures)
		delete figures;
	if(usedView)
		delete usedView;
}

void wxhdDrawing::add(wxhdIFigure *figure)
{
	if(figures)
		figures->addItem(figure);
}

void wxhdDrawing::remove(wxhdIFigure *figure)
{
	if(figures)
		figures->removeItem(figure);
}

bool wxhdDrawing::includes(wxhdIFigure *figure)
{
	if(figures)
		return figures->existsObject(figure);
	return false;
}

wxhdIFigure *wxhdDrawing::findFigure(int posIdx, int x, int y)   //6666 mejorar interaccion view draws... el draw sabe a que vista le pertenece por favor...
{
	wxhdIFigure *tmp = NULL, *out = NULL;
	wxhdIteratorBase *iterator = figures->createIterator();
	while(iterator->HasNext())
	{
		tmp = (wxhdIFigure *)iterator->Next();
		if(tmp->containsPoint(posIdx, x, y))
		{
			out = tmp;
			break;
		}
	}

	delete iterator;;

	return out;
}

void wxhdDrawing::recalculateDisplayBox(int posIdx)
{
	bool first = true;
	wxhdIFigure *figure = NULL;

	wxhdIteratorBase *iterator = figures->createIterator();
	while(iterator->HasNext())
	{
		figure = (wxhdIFigure *)iterator->Next();
		if(first)
		{
			displayBox = figure->displayBox().getwxhdRect(posIdx);
			first = false;
		}
		else
		{
			displayBox.add(figure->displayBox().getwxhdRect(posIdx));
		}
	}

	delete iterator;
}

void wxhdDrawing::bringToFront(wxhdIFigure *figure)
{
	//To bring to front this figure need to be at last position when is draw
	//because this reason sendToBack (last position) is used.
	figures->sendToBack(figure);
}

void wxhdDrawing::sendToBack(wxhdIFigure *figure)
{
	//To send to back this figure need to be at first position when is draw
	//because this reason bringToFront (1st position) is used.
	figures->bringToFront(figure);
}

wxhdRect &wxhdDrawing::DisplayBox()
{
	return displayBox;
}

wxhdIteratorBase *wxhdDrawing::figuresEnumerator()
{
	return figures->createIterator();
}

wxhdIteratorBase *wxhdDrawing::figuresInverseEnumerator()
{
	return figures->createDownIterator();
}

void wxhdDrawing::deleteAllFigures()
{
	selection->removeAll();

	wxhdIFigure *tmp;
	while(figures->count() > 0)
	{
		tmp = (wxhdIFigure *) figures->getItemAt(0);
		figures->removeItemAt(0);
		delete tmp;
	}
	//handles delete it together with figures
}

void wxhdDrawing::removeAllFigures()
{
	selection->removeAll();

	wxhdIFigure *tmp;
	while(figures->count() > 0)
	{
		tmp = (wxhdIFigure *) figures->getItemAt(0);
		figures->removeItemAt(0);
		delete tmp;
	}
}

void wxhdDrawing::deleteSelectedFigures()
{
	 //Allow to customize delete dialog at Editor
	ownerEditor->deleteSelectedFigures(usedView->getIdx());
}

void wxhdDrawing::addToSelection(wxhdIFigure *figure)
{
	if(!selection)
	{
		selection = new wxhdCollection(new wxhdArrayCollection());
	}
	if(figure)
	{
		figure->setSelected(true);
		selection->addItem(figure);
	}
}

void wxhdDrawing::addToSelection(wxhdCollection *figures)
{
}

void wxhdDrawing::removeFromSelection(wxhdIFigure *figure)
{
	figure->setSelected(false);
	if(selection)
		selection->removeItem(figure);
}


void wxhdDrawing::toggleSelection(wxhdIFigure *figure)
{
	if(figure->isSelected() &&	selection->existsObject(figure))
		selection->removeItem(figure);
	else if(!figure->isSelected() && this->includes(figure))
		selection->addItem(figure);

	figure->setSelected(!figure->isSelected());
}

void wxhdDrawing::clearSelection()
{
	wxhdIFigure *tmp = NULL;
	wxhdIteratorBase *iterator = selection->createIterator();
	while(iterator->HasNext())
	{
		tmp = (wxhdIFigure *)iterator->Next();
		tmp->setSelected(false);
	}
	selection->removeAll();
	delete iterator;
}

bool wxhdDrawing::isFigureSelected(wxhdIFigure *figure)
{
	return selection->existsObject(figure);
}

wxhdIteratorBase *wxhdDrawing::selectionFigures()
{
	return selection->createIterator();
}

int wxhdDrawing::countSelectedFigures()
{
	return selection->count();
}