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

#ifndef DDTEXTTABLEITEMFIGURE_H
#define DDTEXTTABLEITEMFIGURE_H


#include <wx/arrstr.h>

#include "dd/draw/figures/ddSimpleTextFigure.h"
#include "dd/dditems/utilities/ddDataType.h"

enum
{
    MNU_DDADDCOLUMN = 0,
    MNU_DELCOLUMN,
    MNU_RENAMECOLUMN,
    MNU_AUTONAMCOLUMN,
	MNU_NOTNULL,
    MNU_PKEY,
    MNU_UKEY,
    MNU_TYPESERIAL,
    MNU_TYPEBOOLEAN,
    MNU_TYPEINTEGER,
    MNU_TYPEMONEY,
    MNU_TYPEVARCHAR,
    MNU_TYPEOTHER,
    MNU_TYPEPKEY_CONSTRAINTNAME,
    MNU_TYPEUKEY_CONSTRAINTNAME,
    MNU_DELTABLE
};

class ddColumnFigure;

class ddTextTableItemFigure : public ddSimpleTextFigure
{
public:
	ddTextTableItemFigure(wxString& columnName, ddDataType dataType, ddColumnFigure *owner);
    ~ddTextTableItemFigure();
	virtual wxString& getText(bool extended = false);
	wxString getType();
    virtual void setAlias(wxString alias);
	virtual wxString getAlias();
	virtual void setOneTimeNoAlias();
	void generateShortName(wxString longName);
	virtual void createMenu(wxMenu &mnu);
	virtual const wxArrayString dataTypes();
	virtual void OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view);
	virtual void setText(wxString textString);
	virtual ddColumnFigure* getOwnerColumn();
	virtual void setOwnerColumn(ddColumnFigure *column);
	virtual void setShowDataType(bool value);
	ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
	int getTextWidth();
	int getTextHeight();
	ddDataType getDataType();
	void setDataType(ddDataType type);
protected:
	ddColumnFigure *ownerColumn;
	wxString colAlias;
private:
	ddDataType columnType;
	wxString out;
	bool showDataType;
	bool showAlias;
	bool oneTimeNoAlias;
	int precision;
};
#endif
