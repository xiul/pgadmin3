//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdIFigure.cpp - Base class for all figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/wxhotdraw/figures/wxhdIFigure.h"
#include "dd/wxhotdraw/handles/wxhdIHandle.h"
#include "dd/wxhotdraw/utilities/wxhdArrayCollection.h"
#include "dd/wxhotdraw/tools/wxhdITool.h"
#include "dd/wxhotdraw/connectors/wxhdIConnector.h"
#include "dd/wxhotdraw/connectors/wxhdChopBoxConnector.h"

wxhdIFigure::wxhdIFigure()
{
	handles=new wxhdCollection(new wxhdArrayCollection());
	observers=new wxhdCollection(new wxhdArrayCollection());
	selected=false;
	connector=NULL;
	basicDisplayBox.SetSize(wxSize(0,0));

	//Default color and pen defined
	defaultPen = wxPen(wxColour(0, 0, 0),1,wxSOLID);
	defaultBrush = wxBrush (wxColour(255, 255, 255),wxSOLID);
	defaultSelectedPen = wxPen(wxColour(255, 0, 0),1,wxSOLID);
	defaultSelectedBrush = wxBrush (wxColour(225, 225, 225),wxSOLID);
}

wxhdIFigure::~wxhdIFigure()
{
	if(connector)
		delete connector;
	if(handles)
		delete handles;
	if(observers){
		observers->removeAll();
		delete observers;
	}
}

wxhdRect& wxhdIFigure::displayBox()
{
	return getBasicDisplayBox();
}

wxhdRect& wxhdIFigure::getBasicDisplayBox()
{
	return basicDisplayBox;
}

bool wxhdIFigure::containsPoint (int x, int y)
{
	return false;
}

void wxhdIFigure::draw (wxBufferedDC& context, wxhdDrawingView *view)
{
	context.SetPen(defaultPen);
	context.SetBrush(defaultBrush);
}

void wxhdIFigure::drawSelected (wxBufferedDC& context, wxhdDrawingView *view)
{
	context.SetPen(defaultSelectedPen);
	context.SetBrush(defaultSelectedBrush);
}

wxhdCollection* wxhdIFigure::handlesEnumerator()
{
	return handles;
}

void wxhdIFigure::addHandle (wxhdIHandle *handle)
{
	if(!handles)
    {
		handles  = new wxhdCollection(new wxhdArrayCollection());
	}
	handles->addItem(handle);	
}

void wxhdIFigure::removeHandle (wxhdIHandle *handle)
{
	if(handles)
    {
		handles->removeItem(handle);		
	}
}

void wxhdIFigure::moveBy (int x, int y)
{
}

void wxhdIFigure::moveTo(int x, int y)
{
}

wxhdITool* wxhdIFigure::CreateFigureTool(wxhdDrawingEditor *editor, wxhdITool *defaultTool)
{
	return defaultTool;
}

bool wxhdIFigure::isSelected()
{
	return selected;
}

void wxhdIFigure::setSelected(bool value)
{
	selected=value;
}

wxhdIConnector* wxhdIFigure::connectorAt (int x, int y)
{
	if(!connector)
		connector = new wxhdChopBoxConnector(this);
	return connector;
}

bool wxhdIFigure::includes(wxhdIFigure *figure)
{
	return (this == figure);
}

void wxhdIFigure::onFigureChanged(wxhdIFigure *figure)
{

	wxhdIteratorBase *iterator=observers->createIterator();
	while(iterator->HasNext())
    {
		wxhdIFigure *o = (wxhdIFigure*) iterator->Next();
		o->onFigureChanged(this);
	}
	delete iterator;
}

void wxhdIFigure::addObserver(wxhdIFigure *observer)
{
	if(!observers)
    {
		observers  = new wxhdCollection(new wxhdArrayCollection());
	}
	observers->addItem(observer);	
}

void wxhdIFigure::removeObserver(wxhdIFigure *observer)
{
	if(observers){
		observers->removeItem(observer);
	}
}

void wxhdIFigure::setDefaultPen(wxPen& pen)
{
	defaultPen=pen;
}

void wxhdIFigure::setDefaultSelectedPen(wxPen& pen)
{
	defaultSelectedPen=pen;
}

void wxhdIFigure::setDefaultBrush(wxBrush& brush)
{
	defaultBrush=brush;
}

void wxhdIFigure::setDefaultSelectedBrush(wxBrush& brush)
{
	defaultSelectedBrush=brush;
}

wxhdIteratorBase* wxhdIFigure::observersEnumerator()
{
	return observers->createIterator();
}

void wxhdIFigure::setKindId(int hiddenId)
{
	kindHiddenId=hiddenId;
}

//Hack because is kindof in not powerful as it should be
int wxhdIFigure::getKindId()  
{
	return kindHiddenId;
}
