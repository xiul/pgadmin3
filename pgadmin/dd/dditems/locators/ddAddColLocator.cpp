//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAddColLocator.cpp 
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/locators/ddAddColLocator.h"
#include "dd/dditems/figures/ddTableFigure.h"

ddAddColLocator::ddAddColLocator()
{
}

ddAddColLocator::~ddAddColLocator()
{
}

ddPoint& ddAddColLocator::locate(ddIFigure *owner)
{
	if(owner)
	{
		ddTableFigure *table = (ddTableFigure*) owner;
		locatePoint.x=table->getTitleRect().GetBottomRight().x-30;
		locatePoint.y=table->getTitleRect().GetBottomRight().y-9;
		return locatePoint;
	}
	locatePoint.x=0;
	locatePoint.y=0;
	return locatePoint;
}