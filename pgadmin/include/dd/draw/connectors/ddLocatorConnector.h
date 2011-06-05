//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddLocatorConnector.h - class that puts connects at locator position
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDLOCATORCONNECTOR_H
#define DDLOCATORCONNECTOR_H

#include "dd/draw/main/ddObject.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/locators/ddILocator.h"

class ddLocatorConnector : public ddIConnector
{
public:
	ddLocatorConnector(ddIFigure *owner, ddILocator *locator);
 	~ddLocatorConnector();
	virtual ddPoint findStart(ddLineConnection *connection);
	virtual ddPoint findEnd(ddLineConnection *connection);
	virtual bool containsPoint(int x, int y);
	virtual void draw(wxBufferedDC& context);
	virtual ddPoint locate();
	virtual ddRect& getDisplayBox();
protected:
	int size; //standard size connector
	ddRect displayBox;
private:
	ddILocator *figureLocator; 
	ddIFigure *figureOwner; 

};
#endif
