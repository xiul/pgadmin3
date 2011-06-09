//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractFigure.h - Base class for all figures with attributes (line size, fonts and others)
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDATTRIBUTE_H
#define DDATTRIBUTE_H
#include "dd/draw/main/ddObject.h"

class ddAttribute : public ddObject
{
public:
	ddAttribute();
	virtual void apply(wxBufferedDC& context);
};
#endif
