//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddTableBottomLocator.h - Locate bottom (south) of table for use of south table size handle.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDTABLEBOTTOMLOCATOR_H
#define DDTABLEBOTTOMLOCATOR_H

#include "dd/wxhotdraw/locators/hdILocator.h"
#include "dd/wxhotdraw/figures/hdIFigure.h"

class ddTableBottomLocator : public hdILocator
{
public:
	ddTableBottomLocator();
	~ddTableBottomLocator();

	virtual hdPoint &locate(int posIdx, hdIFigure *owner);

protected:

private:

};
#endif
