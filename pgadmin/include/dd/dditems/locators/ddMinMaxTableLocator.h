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

#include "dd/wxhotdraw/locators/hdILocator.h"
#include "dd/wxhotdraw/figures/hdIFigure.h"

class ddMinMaxTableLocator : public hdILocator
{
public:
	ddMinMaxTableLocator();
	~ddMinMaxTableLocator();

	virtual hdPoint &locate(int posIdx, hdIFigure *owner);

protected:

private:
};
#endif
