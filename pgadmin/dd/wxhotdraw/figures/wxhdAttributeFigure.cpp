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

// App headers
#include "dd/wxhotdraw/figures/wxhdAttributeFigure.h"
#include "dd/wxhotdraw/figures/wxhdAttribute.h"
#include "dd/wxhotdraw/figures/defaultAttributes/wxhdFillAttribute.h"
#include "dd/wxhotdraw/figures/defaultAttributes/wxhdFontAttribute.h"
#include "dd/wxhotdraw/figures/defaultAttributes/wxhdFontColorAttribute.h"
#include "dd/wxhotdraw/figures/defaultAttributes/wxhdLineAttribute.h"

wxhdAttributeFigure::wxhdAttributeFigure()
{
	initializeDefaultAttributes();
}

wxhdAttributeFigure::~wxhdAttributeFigure()
{
	attributes.clear();	
}
wxhdAttribute& wxhdAttributeFigure::getAttribute(wxString name)
{
	return attributes[name];
}

void wxhdAttributeFigure::addAttribute(wxString name, wxhdAttribute attribute)
{
	attributes[name]=attribute;
}

bool wxhdAttributeFigure::removeAttribute(wxString name)
{
	if(defaultAttributes.Index(name)==wxNOT_FOUND)
		return attributes.erase(name) ? true:false;
	else
		return false;
}

void wxhdAttributeFigure::modifyValueAttribute(wxString name, wxhdAttribute attribute)
{
	attributes[name]=attribute;

}

void wxhdAttributeFigure::draw(wxBufferedDC& context, wxhdDrawingView *view)
{
	
	wxhdAbstractFigure::draw(context, view);
}

void wxhdAttributeFigure::drawSelected(wxBufferedDC& context, wxhdDrawingView *view)
{
	wxhdAbstractFigure::drawSelected(context, view);

	attributesHashMap::iterator it;
	wxhdAttribute attribute;
	for (it = attributes.begin(); it != attributes.end(); ++it)
	{
		wxString key = it->first;
		attribute = it->second;
		attribute.apply(context);
	}
}

void wxhdAttributeFigure::initializeDefaultAttributes()
{
	defaultAttributes.Clear();
	defaultAttributes.Add(wxT("Font"));
	addAttribute(wxT("Font"),fontAttribute);
	defaultAttributes.Add(wxT("FontColor"));
	addAttribute(wxT("FontColor"),fontColorAttribute);
	defaultAttributes.Add(wxT("Line"));
	addAttribute(wxT("Line"),lineAttribute);
	defaultAttributes.Add(wxT("Fill"));
	addAttribute(wxT("Fill"),fillAttribute);
}