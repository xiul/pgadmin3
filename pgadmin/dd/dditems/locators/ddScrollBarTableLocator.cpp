//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddScrollBarTableLocator.cpp 
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/locators/ddScrollBarTableLocator.h"
#include "dd/dditems/figures/ddTableFigure.h"

ddScrollBarTableLocator::ddScrollBarTableLocator()
{
}

ddScrollBarTableLocator::~ddScrollBarTableLocator()
{
}

ddPoint& ddScrollBarTableLocator::locate(ddIFigure *owner)
{
	if(owner)
	{
		ddTableFigure *table = (ddTableFigure*) owner;
		;
		int x = table->getColsSpace().GetTopRight().x - 11; //scrollwidth
		int y = table->getColsSpace().y;

		locatePoint.x=x;
		locatePoint.y=y;
		return locatePoint;
	}
	locatePoint.x=0;
	locatePoint.y=0;
	return locatePoint;
}