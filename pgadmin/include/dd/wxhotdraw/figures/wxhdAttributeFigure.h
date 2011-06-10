//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdAbstractFigure.h - Base class for all figures with attributes (line size, fonts and others)
//
//////////////////////////////////////////////////////////////////////////

#ifndef WXHDATTRIBUTEFIGURE_H
#define WXHDATTRIBUTEFIGURE_H
#include "dd/wxhotdraw/figures/wxhdAbstractFigure.h"
#include "dd/wxhotdraw/figures/wxhdAttribute.h"
#include "dd/wxhotdraw/main/wxhdObject.h"
#include <wx/arrstr.h>

WX_DECLARE_STRING_HASH_MAP( wxhdAttribute, attributesHashMap );

class wxhdAttributeFigure : public wxhdAbstractFigure
{
public:
	wxhdAttributeFigure();
    ~wxhdAttributeFigure();
	
	attributesHashMap attributes;

	wxhdAttribute& getAttribute(wxString name);
	void addAttribute(wxString name, wxhdAttribute attribute);
	void modifyValueAttribute(wxString name, wxhdAttribute attribute);
	bool removeAttribute(wxString name);
	void initializeDefaultAttributes();

protected:
	
private:
	wxArrayString defaultAttributes;
};
#endif
