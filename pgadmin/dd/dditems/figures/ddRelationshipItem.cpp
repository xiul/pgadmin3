//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRelationshipItem.cpp - Items (fk columns) inside a relationship figure hashmap
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/dditems/figures/ddRelationshipItem.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"
#include "dd/wxhotdraw/main/ddDrawingView.h"
#include "dd/dditems/utilities/ddDataType.h"

ddRelationshipItem::ddRelationshipItem(ddRelationshipFigure *owner, ddColumnFigure *originalColumn, ddTableFigure *destination, ddColumnOptionType type, ddColumnType colType)
{
	ownerRel=owner;
	original = originalColumn;
	originalShortName = original->getOwnerTable()->getShortTableName();
	originalStartColName = original->getColumnName(false);
	destinationTable = destination;
	generatedName = autoGenerateNameForFk();
	fkColumn = new ddColumnFigure( generatedName,destinationTable,this);
	fkColumn->setColumnOption(type);
	fkColumn->setColumnKind(colType);
	fkColumn->activateGenFkName();
}

wxString ddRelationshipItem::autoGenerateNameForFk()
{
	wxString newName;
	if(original->getOwnerTable()->getShortTableName().IsEmpty())
		newName = original->getOwnerTable()->getTableName();
	else
		newName = original->getOwnerTable()->getShortTableName();
	newName.append(wxT("_"));
	newName.append(originalStartColName);
	return newName;
}

void ddRelationshipItem::syncAutoFkName()
{
	originalStartColName = original->getColumnName(false);  //Because original name was probably changed, now I should update it.
	originalShortName = original->getOwnerTable()->getShortTableName(); //Because original short name was probably changed, now I should update it.
	if(fkColumn->isForeignKey() && fkColumn->isFkNameGenerated() ) 
	{
		fkColumn->setColumnName(autoGenerateNameForFk());
		ownerRel->updateConnection();
	}
}

ddRelationshipItem::~ddRelationshipItem()
{
}

