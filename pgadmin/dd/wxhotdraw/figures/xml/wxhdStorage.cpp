//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdStorage.cpp - Base class for managing all figures persistence
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// App headers
#include "dd/wxhotdraw/figures/xml/wxhdStorage.h"

wxhdStorage::wxhdStorage():
	wxhdObject()
{
}

wxString wxhdStorage::Read(xmlTextReaderPtr reader)
{
	return wxEmptyString;
}

void wxhdStorage::Write(xmlTextWriterPtr writer, wxhdIFigure *figure)
{

}