//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdFontAttribute.h - Default attribute for attributes of fonts
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdFONTATTRIBUTE_H
#define hdFONTATTRIBUTE_H

#include "dd/wxhotdraw/figures/hdAttribute.h"

class hdFontAttribute : public hdAttribute
{
public:
	hdFontAttribute();
	virtual void callDefaultChangeDialog(wxWindow *owner = NULL);
	virtual void apply(wxBufferedDC &context);
	wxFont &font();
	static wxFont defaultFont;
protected:
	wxFont fontAttributes;
};
#endif
