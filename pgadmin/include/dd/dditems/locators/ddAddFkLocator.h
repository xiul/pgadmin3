//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAddFkLocator.h - Locate table add fk relationship button inside a table.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDADDFKLOCATOR_H
#define DDADDFKLOCATOR_H

#include "dd/wxhotdraw/locators/wxhdILocator.h"
#include "dd/wxhotdraw/figures/wxhdIFigure.h"

class ddAddFkLocator : public ddILocator
{
public:
	ddAddFkLocator();
    ~ddAddFkLocator();

	virtual ddPoint& locate(ddIFigure *owner);

protected:

private:
};
#endif
