//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdAbstractFigure.h - Base class for all figures with attributes (line size, fonts and others)
//
//////////////////////////////////////////////////////////////////////////

#ifndef WXHDFONTATTRIBUTE_H
#define WXHDFONTATTRIBUTE_H

#include "dd/wxhotdraw/figures/wxhdAttribute.h"

class wxhdFontAttribute : public wxhdAttribute
{
public:
	wxhdFontAttribute();
	virtual void callDefaultChangeDialog(wxWindow *owner=NULL);
	virtual void apply(wxBufferedDC& context);
	wxFont& font();
protected:
	wxFont fontAttributes;
};
#endif
