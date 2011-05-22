//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbObject.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// gqbObject.h - 
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
