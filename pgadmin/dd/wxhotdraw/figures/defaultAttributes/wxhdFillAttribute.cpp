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
#include "dd/wxhotdraw/figures/defaultAttributes/wxhdFillAttribute.h"
#include "dd/wxhotdraw/figures/wxhdAttribute.h"

wxhdFillAttribute::wxhdFillAttribute():
wxhdAttribute()
{
	fillAttributes = wxBrush(*wxBLACK);
}

void wxhdFillAttribute::apply(wxBufferedDC& context)
{
	context.SetBackground(fillAttributes);
}

void wxhdFillAttribute::callDefaultChangeDialog(wxWindow *owner)
{
	//create brush dialog
	wxColour color = wxGetColourFromUser(owner, fillAttributes.GetColour(),wxT("Select a color for fill color..."));
	fillAttributes = wxBrush(color);
}

wxBrush& wxhdFillAttribute::brush()
{
	return fillAttributes;
}