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
#include <wx/colordlg.h>

// App headers
#include "dd/wxhotdraw/figures/defaultAttributes/wxhdFontColorAttribute.h"
#include "dd/wxhotdraw/figures/wxhdAttribute.h"

wxhdFontColorAttribute::wxhdFontColorAttribute():
wxhdAttribute()
{
	fontColorAttribute = *wxBLACK;
}

void wxhdFontColorAttribute::apply(wxBufferedDC& context)
{
	context.SetTextForeground(fontColorAttribute);
}

void wxhdFontColorAttribute::callDefaultChangeDialog(wxWindow *owner)
{
	fontColorAttribute = wxGetColourFromUser(owner, fontColorAttribute,wxT("Select a color for font..."));
}

wxColor& wxhdFontColorAttribute::fontColor()
{
	return fontColorAttribute;
}