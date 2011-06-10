//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractFigure.cpp - Base class for all figures with attributes (line size, fonts and others)
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/wxhotdraw/figures/wxhdAttributeFigure.h"

ddAttributeFigure::ddAttributeFigure()
{
	initializeDefaultAttributes();
}

ddAttributeFigure::~ddAttributeFigure()
{
	attributes.clear();	
}
ddAttribute& ddAttributeFigure::getAttribute(wxString name)
{
	return attributes[name];
}

void ddAttributeFigure::addAttribute(wxString name, ddAttribute attribute)
{
	attributes[name]=attribute;
}

bool ddAttributeFigure::removeAttribute(wxString name)
{
	if(defaultAttributes.Index(name)==wxNOT_FOUND)
		return attributes.erase(name) ? true:false;
	else
		return false;
}

void ddAttributeFigure::modifyValueAttribute(wxString name, ddAttribute attribute)
{
	attributes[name]=attribute;

}

void ddAttributeFigure::initializeDefaultAttributes()
{
	defaultAttributes.Clear();
	defaultAttributes.Add(wxT("FontAlignment"));
	defaultAttributes.Add(wxT("FontFamily"));
	defaultAttributes.Add(wxT("FontSize"));
	defaultAttributes.Add(wxT("FontStyle"));
	defaultAttributes.Add(wxT("FontColor"));
	defaultAttributes.Add(wxT("FillColor"));
	defaultAttributes.Add(wxT("LineColor"));
	defaultAttributes.Add(wxT("LineWidth"));

/*  Should be removed and changed by new class hierarchy

	addAttribute(wxT("FontAlignment"),wxT("LEFT"));
	addAttribute(wxT("FontFamily"),wxT("San Serif"));
	addAttribute(wxT("FontSize"),wxT("10"));
	addAttribute(wxT("FontStyle"),wxT("Normal")); //wxFONTSTYLE_NORMAL,
	addAttribute(wxT("FontColor"),wxT(""));  //SetTextForeground
	addAttribute(wxT("FillColor"),wxT(""));  //SetTextBackground
	addAttribute(wxT("LineColor"),wxT(""));
	addAttribute(wxT("LineWidth"),wxT("1.0"));*/
}