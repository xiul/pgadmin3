//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddScrollBarTableLocator.h - Locate table scrollbar inside a table.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDSCROLLBARTABLELOCATOR_H
#define DDSCROLLBARTABLELOCATOR_H

#include "dd/wxhotdraw/locators/ddILocator.h"
#include "dd/wxhotdraw/figures/ddIFigure.h"

class ddScrollBarTableLocator : public ddILocator
{
public:
	ddScrollBarTableLocator();
    ~ddScrollBarTableLocator();

	virtual ddPoint& locate(ddIFigure *owner);

protected:

private:

};
#endif
