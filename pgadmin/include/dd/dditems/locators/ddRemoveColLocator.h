//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRemoveColLocator.h - Locate table remove column button inside a table.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDREMOVECOLLOCATOR_H
#define DDREMOVECOLLOCATOR_H

#include "dd/wxhotdraw/locators/wxhdILocator.h"
#include "dd/wxhotdraw/figures/wxhdIFigure.h"

class ddRemoveColLocator : public ddILocator
{
public:
	ddRemoveColLocator();
    ~ddRemoveColLocator();

	virtual ddPoint& locate(ddIFigure *owner);

protected:

private:
};
#endif
