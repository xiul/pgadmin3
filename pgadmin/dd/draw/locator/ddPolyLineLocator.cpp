//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPolyLineLocator.cpp - Return multiple location at same time for a PolyLine
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/locators/ddPolyLineLocator.h"
#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/figures/ddPolyLineFigure.h"

ddPolyLineLocator::~ddPolyLineLocator()
{
}

ddPolyLineLocator::ddPolyLineLocator(int index)
{
	indx=index;
}

ddPoint& ddPolyLineLocator::locate(ddIFigure *owner)
{
	if(owner)
	{
		ddPolyLineFigure *figure = (ddPolyLineFigure *) owner;
		locatePoint = figure->pointAt(indx);
		return locatePoint;
	}
	else
	{
		return locatePoint;
	}
}

void ddPolyLineLocator::setIndex(int index)
{
	indx=index;
}
