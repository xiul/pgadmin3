//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddILocator.h - Base class for creation of a location for a ddHandle
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDILOCATOR_H
#define DDILOCATOR_H

#include "dd/draw/main/ddObject.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/figures/ddIFigure.h"

class ddILocator : public ddObject
{
public:
	ddILocator();
    ~ddILocator();

	virtual ddPoint& locate(ddIFigure *owner)=0;

protected:
	ddPoint locatePoint;
private:

};
#endif
