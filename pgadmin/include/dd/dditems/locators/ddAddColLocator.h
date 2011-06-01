//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAddColLocator.h - Locate table add column button inside a table.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDADDCOLLOCATOR_H
#define DDADDCOLLOCATOR_H

#include "dd/draw/locators/ddILocator.h"
#include "dd/draw/figures/ddIFigure.h"

class ddAddColLocator : public ddILocator
{
public:
	ddAddColLocator();
    ~ddAddColLocator();

	virtual ddPoint& locate(ddIFigure *owner);

protected:

private:
};
#endif
