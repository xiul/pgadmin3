//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdCompositeFigure.cpp - Base class for all figures composite with figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/wxhotdraw/figures/wxhdCompositeFigure.h"
#include "dd/wxhotdraw/figures/wxhdIFigure.h"
#include "dd/wxhotdraw/utilities/wxhdArrayCollection.h"
#include "dd/wxhotdraw/tools/wxhdCompositeFigureTool.h"

wxhdCompositeFigure::wxhdCompositeFigure()
{
	figureFigures = new wxhdCollection(new wxhdArrayCollection());
	figureHandles = new wxhdCollection(new wxhdArrayCollection());
}

void wxhdCompositeFigure::AddPosForNewDiagram()
{
	//Add position for new displaybox at new diagram
	wxhdAttributeFigure::AddPosForNewDiagram();
	//Add position to each figure inside this composite figure
	wxhdIteratorBase *iterator = figuresEnumerator();
	while(iterator->HasNext())
	{
		wxhdIFigure *f = (wxhdIFigure *) iterator->Next();
		f->AddPosForNewDiagram();
	}
	delete iterator;
}

void wxhdCompositeFigure::RemovePosOfDiagram(int posIdx)
{
	wxhdAttributeFigure::RemovePosOfDiagram(posIdx);
	wxhdIteratorBase *iterator = figuresEnumerator();
	while(iterator->HasNext())
	{
		wxhdIFigure *f = (wxhdIFigure *) iterator->Next();
		f->RemovePosOfDiagram(posIdx);
	}
	delete iterator;
}

wxhdCompositeFigure::~wxhdCompositeFigure()
{
	wxhdIHandle *tmpH;
	//Handles should be delete by their owner (figure)
	while(figureHandles->count() > 0)
	{
		tmpH = (wxhdIHandle *) figureHandles->getItemAt(0);
		figureHandles->removeItemAt(0);
		delete tmpH;
	}
	if(figureHandles)
		delete figureHandles;

	wxhdIFigure *tmp;
	while(figureFigures->count() > 0)
	{
		tmp = (wxhdIFigure *) figureFigures->getItemAt(0);
		figureFigures->removeItemAt(0);
		delete tmp;
	}
	if(figureFigures)
		delete figureFigures;
}

void wxhdCompositeFigure::basicMoveBy(int posIdx, int x, int y)
{
	wxhdIteratorBase *iterator = figuresEnumerator();
	while(iterator->HasNext())
	{
		wxhdIFigure *f = (wxhdIFigure *) iterator->Next();
		f->moveBy(posIdx, x, y);
	}

	basicDisplayBox.x[posIdx] += x;
	basicDisplayBox.y[posIdx] += y;
	delete iterator;
}

bool wxhdCompositeFigure::containsPoint(int posIdx, int x, int y)
{
	bool out = false;
	wxhdIteratorBase *iterator = figuresEnumerator();
	while(iterator->HasNext())
	{
		wxhdIFigure *f = (wxhdIFigure *) iterator->Next();
		if(f->containsPoint(posIdx, x, y))
		{
			out = true; //avoid memory leak
		}
	}
	delete iterator;
	return out;
}

wxhdIteratorBase *wxhdCompositeFigure::figuresEnumerator()
{
	return figureFigures->createIterator();
}

wxhdIteratorBase *wxhdCompositeFigure::figuresInverseEnumerator()
{
	return figureFigures->createDownIterator();
}

//Ignore figures at negative positions
wxhdMultiPosRect &wxhdCompositeFigure::getBasicDisplayBox()
{
	basicDisplayBox.SetSize(wxSize(0, 0));

	int posIdx;
	wxhdIteratorBase *iterator = figuresEnumerator();
	for(posIdx=0; posIdx < basicDisplayBox.CountPositions(); posIdx++)
	{
		basicDisplayBox.SetPosition(posIdx, wxPoint(0, 0));
		bool firstFigure = true;

		while(iterator->HasNext())
		{
			wxhdIFigure *f = (wxhdIFigure *) iterator->Next();
			if(firstFigure)
			{
				basicDisplayBox.SetPosition(posIdx, f->displayBox().GetPosition(posIdx));
				basicDisplayBox.SetSize( f->displayBox().GetSize());
				if(f->displayBox().GetPosition(posIdx).x > 0 && f->displayBox().GetPosition(posIdx).y > 0)
					firstFigure = false;
			}
			else
			{
				if(f->displayBox().GetPosition(posIdx).x > 0 && f->displayBox().GetPosition(posIdx).y > 0)
					basicDisplayBox.add(posIdx, f->displayBox().getwxhdRect(posIdx) );
			}
		}
		iterator->ResetIterator();
	}
	delete iterator;
	return basicDisplayBox;

}

wxhdCollection *wxhdCompositeFigure::handlesEnumerator()
{
	return figureHandles;
}

void wxhdCompositeFigure::add(wxhdIFigure *figure)
{
	if(includes(figure))
		return;

	//Add figure
	figureFigures->addItem(figure);
	//Check figure available positions for diagrams.
	int i,start;
	start = figure->displayBox().CountPositions();
	for(i=start; i < basicDisplayBox.CountPositions(); i++)
	{
			figure->AddPosForNewDiagram(); 
	}
	//Add figure handles
	wxhdIteratorBase *handlesIterator = figure->handlesEnumerator()->createIterator();
	while(handlesIterator->HasNext())
	{
		wxhdIHandle *h = (wxhdIHandle *) handlesIterator->Next();
		figureHandles->addItem(h);
	}
	delete handlesIterator;
}

void wxhdCompositeFigure::remove(wxhdIFigure *figure)
{
	if(!includes(figure))
		return;

	//Remove figure handles
	wxhdIteratorBase *handlesIterator = figure->handlesEnumerator()->createIterator();
	while(handlesIterator->HasNext())
	{
		wxhdIHandle *h = (wxhdIHandle *) handlesIterator->Next();
		figureHandles->removeItem(h);
	}
	delete handlesIterator;
	//Remove figure
	figureFigures->removeItem(figure);
}

bool wxhdCompositeFigure::includes(wxhdIFigure *figure)
{
	if(wxhdAbstractFigure::includes(figure))
		return true;

	bool out = false;

	wxhdIteratorBase *iterator = figuresEnumerator();
	while(iterator->HasNext())
	{
		wxhdIFigure *f = (wxhdIFigure *) iterator->Next();
		if(f->includes(figure))
			out = true;
	}
	delete iterator;
	return out;
}

void wxhdCompositeFigure::basicDraw(wxBufferedDC &context, wxhdDrawingView *view)
{
	wxhdIteratorBase *iterator = figuresEnumerator();
	wxhdIFigure *f = NULL;
	while(iterator->HasNext())
	{
		f = (wxhdIFigure *) iterator->Next();
		f->draw(context, view);
	}
	delete iterator;
}

void wxhdCompositeFigure::basicDrawSelected(wxBufferedDC &context, wxhdDrawingView *view)
{
	wxhdIteratorBase *iterator = figuresEnumerator();
	wxhdIFigure *f = NULL;
	while(iterator->HasNext())
	{
		f = (wxhdIFigure *) iterator->Next();
		f->drawSelected(context, view);
	}
	delete iterator;
}

wxhdIFigure *wxhdCompositeFigure::findFigure(int posIdx, int x, int y)
{
	wxhdIFigure *tmp = NULL, *out = NULL;
	wxhdIteratorBase *iterator = figuresInverseEnumerator();
	while(iterator->HasNext())
	{
		tmp = (wxhdIFigure *)iterator->Next();
		if(tmp->containsPoint(posIdx, x, y))
		{
			out = tmp;
			break;
		}
	}

	delete iterator;

	return out;
}

wxhdITool *wxhdCompositeFigure::CreateFigureTool(wxhdDrawingView *view, wxhdITool *defaultTool)
{
	return new wxhdCompositeFigureTool(view, this, defaultTool);
}

wxhdIFigure *wxhdCompositeFigure::getFigureAt(int indexOfCollection)
{
	return (wxhdIFigure *) figureFigures->getItemAt(indexOfCollection);
}
