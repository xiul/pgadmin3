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

wxhdAttributeFigure::wxhdAttributeFigure()
{
	initializeDefaultAttributes();
}

wxhdAttributeFigure::~wxhdAttributeFigure()
{
	//before delete all items inside to free memory
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

void wxhdAttributeFigure::initializeDefaultAttributes()
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