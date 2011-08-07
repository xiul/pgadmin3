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

#include "dd/wxhotdraw/locators/hdILocator.h"
#include "dd/wxhotdraw/figures/hdIFigure.h"

class ddScrollBarTableLocator : public hdILocator
{
public:
	ddScrollBarTableLocator();
	~ddScrollBarTableLocator();

	virtual hdPoint &locate(int posIdx, hdIFigure *owner);

protected:

private:

};
#endif
