//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdLocatorConnector.h - class that puts connects at locator position
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdLOCATORCONNECTOR_H
#define hdLOCATORCONNECTOR_H

#include "dd/wxhotdraw/main/hdObject.h"
#include "dd/wxhotdraw/figures/hdLineConnection.h"
#include "dd/wxhotdraw/utilities/hdPoint.h"
#include "dd/wxhotdraw/utilities/hdRect.h"
#include "dd/wxhotdraw/locators/hdILocator.h"

class hdLocatorConnector : public hdIConnector
{
public:
	hdLocatorConnector(hdIFigure *owner, hdILocator *locator);
	~hdLocatorConnector();
	virtual hdPoint findStart(int posIdx, hdLineConnection *connection);
	virtual hdPoint findEnd(int posIdx, hdLineConnection *connection);
	virtual bool containsPoint(int posIdx, int x, int y);
	virtual void draw(wxBufferedDC &context);
	virtual hdPoint locate(int posIdx);
	virtual hdRect &getDisplayBox(int posIdx);
protected:
	int size; //standard size connector
	hdRect displayBox;
private:
	hdILocator *figureLocator;
	hdIFigure *figureOwner;

};
#endif
