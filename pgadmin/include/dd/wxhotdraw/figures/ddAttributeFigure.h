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
#include "dd/wxhotdraw/figures/ddAbstractFigure.h"
#include "dd/wxhotdraw/figures/ddAttribute.h"
#include "dd/wxhotdraw/main/ddObject.h"
#include <wx/arrstr.h>

WX_DECLARE_STRING_HASH_MAP( ddAttribute, attributesHashMap );

class ddAttributeFigure : public ddAbstractFigure
{
public:
	ddAttributeFigure();
    ~ddAttributeFigure();
	
	attributesHashMap attributes;

	ddAttribute& getAttribute(wxString name);
	void addAttribute(wxString name, ddAttribute attribute);
	void modifyValueAttribute(wxString name, ddAttribute attribute);
	bool removeAttribute(wxString name);
	void initializeDefaultAttributes();

protected:
	
private:
	wxArrayString defaultAttributes;
};
#endif
