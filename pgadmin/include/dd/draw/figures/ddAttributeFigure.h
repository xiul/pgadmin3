//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractFigure.h - Base class for all figures with attributes (line size, fonts and others)
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDATTRIBUTEFIGURE_H
#define DDATTRIBUTEFIGURE_H
#include "dd/draw/figures/ddAbstractFigure.h"
#include "dd/draw/main/ddObject.h"
#include <wx/arrstr.h>

class ddAttribute : public ddObject
{
public:
	ddAttribute();
	ddAttribute(wxString val, wxString defaultVal);
	
	virtual void apply(wxBufferedDC& context);
	wxString defaultValue;
	wxString value;
};

WX_DECLARE_STRING_HASH_MAP( ddAttribute, attributesHashMap );

class ddAttributeFigure : public ddAbstractFigure
{
public:
	ddAttributeFigure();
    ~ddAttributeFigure();
	
	attributesHashMap attributes;

	ddAttribute& getAttribute(wxString name);
	void addAttribute(wxString name, wxString value);
	void modifyValueAttribute(wxString name, wxString newValue);
	bool removeAttribute(wxString name);
	void initializeDefaultAttributes();

protected:
	
private:
	wxArrayString defaultAttributes;
};
#endif
