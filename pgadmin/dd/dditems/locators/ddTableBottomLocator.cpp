//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddTableBottomLocator.cpp 
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/locators/ddTableBottomLocator.h"
#include "dd/dditems/figures/ddTableFigure.h"

ddTableBottomLocator::ddTableBottomLocator()
{
}

ddTableBottomLocator::~ddTableBottomLocator()
{
}

ddPoint& ddTableBottomLocator::locate(ddIFigure *owner)
{
	if(owner)
	{
		ddTableFigure *table = (ddTableFigure*) owner;

		int x = table->getFullSpace().GetLeftBottom().x + table->getFullSpace().width * 0.25; 
		int y = table->getFullSpace().GetLeftBottom().y-2;

		locatePoint.x=x;
		locatePoint.y=y;
		return locatePoint;
	}
	locatePoint.x=0;
	locatePoint.y=0;
	return locatePoint;
}