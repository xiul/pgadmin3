//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdILocator.h - Base class for creation of a location for a ddHandle
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdILocator_H
#define hdILocator_H

#include "dd/wxhotdraw/main/hdObject.h"
#include "dd/wxhotdraw/utilities/hdRect.h"
#include "dd/wxhotdraw/figures/hdIFigure.h"

class hdILocator : public hdObject
{
public:
	hdILocator();
	~hdILocator();

	virtual hdPoint &locate(int posIdx, hdIFigure *owner) = 0;

protected:
	hdPoint locatePoint;
private:

};
#endif
