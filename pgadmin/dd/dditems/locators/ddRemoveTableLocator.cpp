//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRemoveTableLocator.cpp
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/locators/ddRemoveTableLocator.h"
#include "dd/dditems/figures/ddTableFigure.h"

ddRemoveTableLocator::ddRemoveTableLocator()
{
}

ddRemoveTableLocator::~ddRemoveTableLocator()
{
}

ddPoint& ddRemoveTableLocator::locate(ddIFigure *owner)
{
	if(owner)
	{
		ddTableFigure *table = (ddTableFigure*) owner;
		int x = table->displayBox().x + table->displayBox().width - 10; //(8+2)
		int y = table->displayBox().y + 6;

		locatePoint.x=x;
		locatePoint.y=y;
		return locatePoint;
	}
	locatePoint.x=0;
	locatePoint.y=0;
	return locatePoint;
}