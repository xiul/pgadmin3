//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdAbstractFigure.h - Base class for all figures with attributes (line size, fonts and others)
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdSTORAGE_H
#define hdSTORAGE_H

#include "dd/wxhotdraw/main/hdObject.h"
#include "dd/wxhotdraw/figures/hdIFigure.h"

class hdStorage : public hdObject
{
public:
	hdStorage();
	static bool Read(xmlTextReaderPtr reader);
	static bool Write(xmlTextWriterPtr writer, hdIFigure *figure);
};
#endif
