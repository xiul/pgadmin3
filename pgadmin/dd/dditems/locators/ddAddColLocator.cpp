//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAddColLocator.cpp - Locate table add column button inside a table.
//
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