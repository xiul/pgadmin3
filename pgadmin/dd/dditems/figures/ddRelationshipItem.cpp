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
#include "dd/wxhotdraw/main/wxhdDrawingView.h"
#include "dd/dditems/utilities/ddDataType.h"

ddRelationshipItem::ddRelationshipItem(ddRelationshipFigure *owner, ddColumnFigure *originalColumn, ddTableFigure *destination, ddColumnOptionType type, ddColumnType colType, ddColumnFigure *existingColumn)
{
	ownerRel=owner;
	original = originalColumn;
	originalShortName = original->getOwnerTable()->getShortTableName();
	originalStartColName = original->getColumnName(false);
	destinationTable = destination;
	
	if(existingColumn == NULL)   //Fk destination column will be automatically generated
	{
		generatedName = autoGenerateNameForFk();	
		fkColumn = new ddColumnFigure( generatedName,destinationTable,this);
		fkColumn->setColumnOption(type);
		fkColumn->setColumnKind(colType);
		fkColumn->activateGenFkName(); //By default fk name is generate by using ( alias | tableName) . ColumnName combination
		fkIsAutoGenerated = true;
	} 
	else //using existing column as fk destination (Validation Required at user choices compatibility of types, precision and scale)
	{
		generatedName = wxEmptyString;
		fkColumn = existingColumn;
		fkColumn->setAsUserCreatedFk(this);
		fkColumn->setColumnKind(fkadjust);
		fkColumn->deactivateGenFkName();
		fkIsAutoGenerated = false;
	}
}

ddRelationshipItem::~ddRelationshipItem()
{
}

bool ddRelationshipItem::isAutomaticallyGenerated()
{
	return fkIsAutoGenerated;
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
	if(fkColumn->isGeneratedForeignKey() && fkColumn->isFkNameGenerated() ) 
	{
		fkColumn->setColumnName(autoGenerateNameForFk());
		ownerRel->updateConnection();
	}
}

bool ddRelationshipItem::relationIsIdentifying()
{
	return ownerRel->getIdentifying();
}

bool ddRelationshipItem::relationIsMandatory()
{
	return ownerRel->getMandatory();
}

wxString ddRelationshipItem::sourceTableName()
{
	return original->getOwnerTable()->getTableName();
}

wxString ddRelationshipItem::destTableName()
{
	return destinationTable->getTableName();
}