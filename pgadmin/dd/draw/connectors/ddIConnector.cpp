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

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/connectors/ddIConnector.h"

class ddLineConnection;
class ddIFigure;

ddIConnector::ddIConnector(ddIFigure *owner):
ddObject()
{
	figureOwner = owner;
}

ddIConnector::~ddIConnector()
{
}

ddIFigure* ddIConnector::getOwner()
{
	return figureOwner;

}

void ddIConnector::setOwner(ddIFigure *owner)
{
	figureOwner=owner;
}

void ddIConnector::draw(wxBufferedDC& context)
{
}

ddRect& ddIConnector::getDisplayBox()
{
	return figureOwner->displayBox();
}

bool ddIConnector::containsPoint(int x, int y)
{
	return figureOwner->containsPoint(x,y);
}

ddPoint ddIConnector::findStart(ddLineConnection *connection)
{
	return getDisplayBox().center();
}

ddPoint ddIConnector::findEnd(ddLineConnection *connection)
{
	return getDisplayBox().center();
}
