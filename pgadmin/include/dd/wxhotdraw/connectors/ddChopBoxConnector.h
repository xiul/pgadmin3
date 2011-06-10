//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddChopBoxConnector.h - Connector for center of figure to line crossing one limit line of rect
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCHOPBOXCONNECTOR_H
#define DDCHOPBOXCONNECTOR_H


#include "dd/wxhotdraw/connectors/ddIConnector.h"
#include "dd/wxhotdraw/figures/ddIFigure.h"

class ddChopBoxConnector : public ddIConnector
{
public:
	ddChopBoxConnector(ddIFigure *owner);
    ~ddChopBoxConnector();
	virtual ddPoint findStart(ddLineConnection *connFigure);
	virtual ddPoint findEnd(ddLineConnection *connFigure);
protected:
	virtual ddPoint chop(ddIFigure *target, ddPoint point);
private:
	ddPoint point;
	ddRect rect;

};
#endif
