//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbObject.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// gqbObject.h - 
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDLOCATORCONNECTOR_H
#define DDLOCATORCONNECTOR_H

#include "dd/draw/main/ddObject.h"
//#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/locators/ddILocator.h"

class ddLineConnection;  //HACK-FIX to circular reference
class ddIFigure;

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
	//	virtual ddIFigure* getOwner();
	virtual ddRect& getDisplayBox();
protected:
//	virtual void setOwner(ddIFigure *owner);
	int size; //standard size connector
	ddRect displayBox;
private:
	ddILocator *figureLocator; 
	ddIFigure *figureOwner; 

};
#endif
