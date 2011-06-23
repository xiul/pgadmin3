//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdAbstractFigure.cpp - Base class for all figures with attributes (line size, fonts and others)
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>
#include <wx/fontdlg.h>

// App headers
#include "dd/wxhotdraw/figures/defaultAttributes/wxhdFontAttribute.h"
#include "dd/wxhotdraw/figures/wxhdAttribute.h"

wxhdFontAttribute::wxhdFontAttribute():
wxhdAttribute()
{
	fontAttributes = settings->GetSystemFont();
}

void wxhdFontAttribute::apply(wxBufferedDC& context)
{
	context.SetFont(fontAttributes);
}

void wxhdFontAttribute::callDefaultChangeDialog(wxWindow *owner)
{
	fontAttributes = wxGetFontFromUser(owner, fontAttributes,wxT("Select a font..."));
}

wxFont& wxhdFontAttribute::font()
{
	return fontAttributes;
}