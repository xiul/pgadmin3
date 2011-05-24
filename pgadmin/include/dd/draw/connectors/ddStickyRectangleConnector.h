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

#ifndef DDSTICKYRECTANGLECONNECTOR_H
#define DDSTICKYRECTANGLECONNECTOR_H

#include "dd/draw/main/ddObject.h"
//#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/connectors/ddChopBoxConnector.h"

class ddLineConnection;  //HACK-FIX to circular reference
class ddIFigure;

class ddStickyRectangleConnector : public ddChopBoxConnector
{
public:
	ddStickyRectangleConnector(ddIFigure *owner, ddPoint p);
 	~ddStickyRectangleConnector();
	virtual void setAngle(float newAngle);
	virtual void updateAnchor(ddPoint p);
	virtual ddPoint getAnchor();
	virtual ddPoint chop(ddIFigure *target, ddPoint point);
//	virtual ddPoint findStart(ddLineConnection *connection);
//	virtual ddPoint findEnd(ddLineConnection *connection);
//	virtual bool containsPoint(int x, int y);
	virtual void draw(wxBufferedDC& context);
//	virtual ddRect& getDisplayBox();
protected:
/*	virtual void setOwner(ddIFigure *owner);
	ddRect displayBox;*/
	float angle;
private:
	//ddIFigure *figureOwner; 

};
#endif
