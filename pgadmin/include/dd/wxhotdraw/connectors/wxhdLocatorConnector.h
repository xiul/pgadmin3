//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdLocatorConnector.h - class that puts connects at locator position
//
//////////////////////////////////////////////////////////////////////////

#ifndef WXHDLOCATORCONNECTOR_H
#define WXHDLOCATORCONNECTOR_H

#include "dd/wxhotdraw/main/wxhdObject.h"
#include "dd/wxhotdraw/figures/wxhdLineConnection.h"
#include "dd/wxhotdraw/utilities/wxhdPoint.h"
#include "dd/wxhotdraw/utilities/wxhdRect.h"
#include "dd/wxhotdraw/locators/wxhdILocator.h"

class wxhdLocatorConnector : public wxhdIConnector
{
public:
	wxhdLocatorConnector(wxhdIFigure *owner, wxhdILocator *locator);
	~wxhdLocatorConnector();
	virtual wxhdPoint findStart(int posIdx, wxhdLineConnection *connection);
	virtual wxhdPoint findEnd(int posIdx, wxhdLineConnection *connection);
	virtual bool containsPoint(int posIdx, int x, int y);
	virtual void draw(wxBufferedDC &context);
	virtual wxhdPoint locate(int posIdx);
	virtual wxhdRect &getDisplayBox(int posIdx);
protected:
	int size; //standard size connector
	wxhdRect displayBox;
private:
	wxhdILocator *figureLocator;
	wxhdIFigure *figureOwner;

};
#endif
