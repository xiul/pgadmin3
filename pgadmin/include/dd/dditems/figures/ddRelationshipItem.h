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

class ddRelationshipItem : public wxhdObject
{
public:
	ddRelationshipItem(ddRelationshipFigure *owner, ddColumnFigure *originalColumn, ddTableFigure *destination, ddColumnOptionType type, ddColumnType colType, ddColumnFigure *existingColumn = NULL);
	~ddRelationshipItem();
	wxString originalStartColName;
	wxString originalShortName;
	ddColumnFigure *original;
	ddColumnFigure *fkColumn;
	ddTableFigure *destinationTable;

	wxString autoGenerateNameForFk();
	void syncAutoFkName();

	bool isAutomaticallyGenerated();
	bool relationIsIdentifying();
	bool relationIsMandatory();
	bool isForeignKeyFromPk();
	wxString sourceTableName();
	wxString destTableName();


private:
	bool fkIsAutoGenerated;
	ddRelationshipFigure *ownerRel;
	wxString generatedName;   //avoid linux bug
};

#endif