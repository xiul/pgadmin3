//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractFigure.cpp
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/draw/figures/ddAttributeFigure.h"

ddAttribute::ddAttribute():
ddObject()
{
}

ddAttribute::ddAttribute(wxString val, wxString defaultVal):
ddObject()
{
	value = val;
	defaultValue = defaultVal;
}

void ddAttribute::apply(wxBufferedDC& context)
{
	//DD-TODO: do it for default attributtes below
}


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

void ddAttributeFigure::addAttribute(wxString name, wxString value)
{
	attributes[name]=ddAttribute(name,value);
}

bool ddAttributeFigure::removeAttribute(wxString name)
{
	if(defaultAttributes.Index(name)==wxNOT_FOUND)
		return attributes.erase(name) ? true:false;
	else
		return false;
}

void ddAttributeFigure::modifyValueAttribute(wxString name, wxString newValue)
{
	ddAttribute &temp=attributes[name];
	temp.value=newValue;
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

	addAttribute(wxT("FontAlignment"),wxT("LEFT"));
	addAttribute(wxT("FontFamily"),wxT("San Serif"));
	addAttribute(wxT("FontSize"),wxT("10"));
	addAttribute(wxT("FontStyle"),wxT("Normal")); //wxFONTSTYLE_NORMAL,
	addAttribute(wxT("FontColor"),wxT(""));  //SetTextForeground
	addAttribute(wxT("FillColor"),wxT(""));  //SetTextBackground
	addAttribute(wxT("LineColor"),wxT(""));
	addAttribute(wxT("LineWidth"),wxT("1.0"));
}