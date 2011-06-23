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

#ifndef WXHDFONTCOLORATTRIBUTE_H
#define WXHDFONTCOLORATTRIBUTE_H

#include "dd/wxhotdraw/figures/wxhdAttribute.h"

class wxhdFontColorAttribute : public wxhdAttribute
{
public:
	wxhdFontColorAttribute();
	virtual void callDefaultChangeDialog(wxWindow *owner=NULL);
	virtual void apply(wxBufferedDC& context);
	wxColor& fontColor();
protected:
	wxColor fontColorAttribute;
};
#endif
