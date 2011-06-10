//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPolyLineLocator.h - Return multiple location at same time for a PolyLine
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDPOLYLINELOCATOR_H
#define DDPOLYLINELOCATOR_H

#include "dd/wxhotdraw/locators/wxhdILocator.h"

class ddPolyLineLocator : public ddILocator
{
public:
	ddPolyLineLocator(int index);
    ~ddPolyLineLocator();

	virtual ddPoint& locate(ddIFigure *owner);
	virtual void setIndex(int index);

protected:

private:
	int indx;
};
#endif
