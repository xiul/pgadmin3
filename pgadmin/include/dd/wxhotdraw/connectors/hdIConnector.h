//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdIConnector.cpp - Base class for all connectors
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdICONNECTOR_H
#define hdICONNECTOR_H

#include "dd/wxhotdraw/main/hdObject.h"
#include "dd/wxhotdraw/figures/hdLineConnection.h"
#include "dd/wxhotdraw/utilities/hdPoint.h"
#include "dd/wxhotdraw/utilities/hdRect.h"

class hdLineConnection;
class hdIFigure;

class hdIConnector : public hdObject
{
public:
	hdIConnector(hdIFigure *owner);
	~hdIConnector();
	virtual hdPoint findStart(int posIdx, hdLineConnection *connection);
	virtual hdPoint findEnd(int posIdx, hdLineConnection *connection);
	virtual bool containsPoint(int posIdx, int x, int y);
	virtual void draw(wxBufferedDC &context);
	virtual hdIFigure *getOwner();
	virtual hdMultiPosRect &getDisplayBox();
protected:
	virtual void setOwner(hdIFigure *owner);
private:
	hdIFigure *figureOwner;

};
#endif
