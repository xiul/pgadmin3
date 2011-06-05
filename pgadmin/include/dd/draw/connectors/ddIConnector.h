//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddIConnector.cpp - Base class for all connectors
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDICONNECTOR_H
#define DDICONNECTOR_H

#include "dd/draw/main/ddObject.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/utilities/ddRect.h"

class ddLineConnection;
class ddIFigure;

class ddIConnector : public ddObject
{
public:
	ddIConnector(ddIFigure *owner);
 	~ddIConnector();
	virtual ddPoint findStart(ddLineConnection *connection);
	virtual ddPoint findEnd(ddLineConnection *connection);
	virtual bool containsPoint(int x, int y);
	virtual void draw(wxBufferedDC& context);
	virtual ddIFigure* getOwner();
	virtual ddRect& getDisplayBox();
protected:
	virtual void setOwner(ddIFigure *owner);
	ddRect displayBox;
private:
	ddIFigure *figureOwner; 

};
#endif
