//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRelationshipFigure.h - Figure to draw foreign keys between tables.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDRELATIONSHIPITEM_H
#define DDRELATIONSHIPITEM_H
#include "dd/wxhotdraw/figures/wxhdLineConnection.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddColumnFigure.h"

class ddRelationshipItem : public ddObject
{
public:
	ddRelationshipItem(ddRelationshipFigure *owner, ddColumnFigure *originalColumn, ddTableFigure *destination, ddColumnOptionType type, ddColumnType colType);
	~ddRelationshipItem();
	wxString originalStartColName;
	wxString originalShortName;
	ddColumnFigure *original;
	ddColumnFigure *fkColumn;
	ddTableFigure *destinationTable;

	wxString autoGenerateNameForFk();
	void syncAutoFkName();
private:
	ddRelationshipFigure *ownerRel;
	wxString generatedName;   //avoid linux bug
};

#endif
