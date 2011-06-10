//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddMinMaxTableLocator.h - Locate table minimize/maximize button inside a table.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDMINMAXTABLELOCATOR_H
#define DDMINMAXTABLELOCATOR_H

#include "dd/wxhotdraw/locators/wxhdILocator.h"
#include "dd/wxhotdraw/figures/wxhdIFigure.h"

class ddMinMaxTableLocator : public ddILocator
{
public:
	ddMinMaxTableLocator();
    ~ddMinMaxTableLocator();

	virtual ddPoint& locate(ddIFigure *owner);

protected:

private:
};
#endif
