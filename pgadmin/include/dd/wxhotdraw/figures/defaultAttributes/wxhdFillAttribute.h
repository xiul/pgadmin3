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

#ifndef WXHDFILLCOLORATTRIBUTE_H
#define WXHDFILLCOLORATTRIBUTE_H

#include "dd/wxhotdraw/figures/wxhdAttribute.h"

class wxhdFillAttribute : public wxhdAttribute
{
public:
	wxhdFillAttribute();
	virtual void callDefaultChangeDialog(wxWindow *owner=NULL);
	virtual void apply(wxBufferedDC& context);
	wxBrush& brush();
protected:
	wxBrush fillAttributes;
};
#endif
