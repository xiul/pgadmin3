//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractFigure.h - A StickyRectangleConnector locates connection points by choping
// the connection between the centers of the two figures at the display box. The location 
// of the connection point is computed once, when the user connects the figure. 
// Moving the figure around will not change the location.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDSTICKYRECTANGLECONNECTOR_H
#define DDSTICKYRECTANGLECONNECTOR_H

#include "dd/draw/main/ddObject.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/connectors/ddChopBoxConnector.h"

class ddLineConnection;
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
	virtual void draw(wxBufferedDC& context);
protected:
	float angle;
private:

};
#endif
