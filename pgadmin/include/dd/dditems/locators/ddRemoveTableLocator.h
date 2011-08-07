//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRemoveColLocator.cpp - Locate table delete button inside a table.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDREMOVETABLELOCATOR_H
#define DDREMOVETABLELOCATOR_H

#include "dd/wxhotdraw/locators/hdILocator.h"
#include "dd/wxhotdraw/figures/hdIFigure.h"

class ddRemoveTableLocator : public hdILocator
{
public:
	ddRemoveTableLocator();
	~ddRemoveTableLocator();

	virtual hdPoint &locate(int posIdx, hdIFigure *owner);

protected:

private:
};
#endif
