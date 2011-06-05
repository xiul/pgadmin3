//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddIFigure.cpp - Base class for all figures
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/utilities/ddArrayCollection.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/connectors/ddIConnector.h"
#include "dd/draw/connectors/ddChopBoxConnector.h"

ddIFigure::ddIFigure()
{
	handles=new ddCollection(new ddArrayCollection());
	observers=new ddCollection(new ddArrayCollection());
	selected=false;
	connector=NULL;
	basicDisplayBox.SetSize(wxSize(0,0));
	//DD-TODO: this should be initialize here

	//Default color and pen defined
	defaultPen = wxPen(wxColour(0, 0, 0),1,wxSOLID);
	defaultBrush = wxBrush (wxColour(255, 255, 255),wxSOLID);
	defaultSelectedPen = wxPen(wxColour(255, 0, 0),1,wxSOLID);
	defaultSelectedBrush = wxBrush (wxColour(225, 225, 225),wxSOLID);
}

ddIFigure::~ddIFigure()
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

ddRect& ddIFigure::displayBox()
{
	return getBasicDisplayBox();
}

ddRect& ddIFigure::getBasicDisplayBox()
{
	return basicDisplayBox;
}

bool ddIFigure::containsPoint (int x, int y)
{
	return false;
}

void ddIFigure::draw (wxBufferedDC& context, ddDrawingView *view)
{
	context.SetPen(defaultPen);
	context.SetBrush(defaultBrush);
}

void ddIFigure::drawSelected (wxBufferedDC& context, ddDrawingView *view)
{
	context.SetPen(defaultSelectedPen);
	context.SetBrush(defaultSelectedBrush);
}

ddCollection* ddIFigure::handlesEnumerator()
{
	return handles;
}

void ddIFigure::addHandle (ddIHandle *handle)
{
	if(!handles)
    {
		handles  = new ddCollection(new ddArrayCollection());
	}
	handles->addItem(handle);	
}

void ddIFigure::removeHandle (ddIHandle *handle)
{
	if(handles)
    {
		handles->removeItem(handle);		
	}
}

void ddIFigure::moveBy (int x, int y)
{
}

void ddIFigure::moveTo(int x, int y)
{
}

ddITool* ddIFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return defaultTool;
}

bool ddIFigure::isSelected()
{
	return selected;
}

void ddIFigure::setSelected(bool value)
{
	selected=value;
}

ddIConnector* ddIFigure::connectorAt (int x, int y)
{
	if(!connector)
		connector = new ddChopBoxConnector(this);
	return connector;
}

bool ddIFigure::includes(ddIFigure *figure)
{
	return (this == figure);
}

void ddIFigure::onFigureChanged(ddIFigure *figure)
{

	ddIteratorBase *iterator=observers->createIterator();
	while(iterator->HasNext())
    {
		ddIFigure *o = (ddIFigure*) iterator->Next();
		o->onFigureChanged(this);
	}
	delete iterator;
}

void ddIFigure::addObserver(ddIFigure *observer)
{
	if(!observers)
    {
		observers  = new ddCollection(new ddArrayCollection());
	}
	observers->addItem(observer);	
}

void ddIFigure::removeObserver(ddIFigure *observer)
{
	if(observers){
		observers->removeItem(observer);
	}
}

void ddIFigure::setDefaultPen(wxPen& pen)
{
	defaultPen=pen;
}

void ddIFigure::setDefaultSelectedPen(wxPen& pen)
{
	defaultSelectedPen=pen;
}

void ddIFigure::setDefaultBrush(wxBrush& brush)
{
	defaultBrush=brush;
}

void ddIFigure::setDefaultSelectedBrush(wxBrush& brush)
{
	defaultSelectedBrush=brush;
}

ddIteratorBase* ddIFigure::observersEnumerator()
{
	return observers->createIterator();
}

void ddIFigure::setKindId(int hiddenId)
{
	kindHiddenId=hiddenId;
}

//Hack because is kindof in not powerful as it should be
int ddIFigure::getKindId()  
{
	return kindHiddenId;
}
