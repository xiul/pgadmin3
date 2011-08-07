//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdChopBoxConnector.h - Connector for center of figure to line crossing one limit line of rect
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdCHOPBOXCONNECTOR_H
#define hdCHOPBOXCONNECTOR_H


#include "hotdraw/connectors/hdIConnector.h"
#include "hotdraw/figures/hdIFigure.h"

class hdChopBoxConnector : public hdIConnector
{
public:
	hdChopBoxConnector(hdIFigure *owner);
	~hdChopBoxConnector();
	virtual hdPoint findStart(int posIdx, hdLineConnection *connFigure);
	virtual hdPoint findEnd(int posIdx, hdLineConnection *connFigure);
protected:
	virtual hdPoint chop(int posIdx, hdIFigure *target, hdPoint point);
private:
	hdPoint point;
	hdRect rect;

};
#endif
