//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddColumnFigure.cpp - Minimal Composite Figure for a column of a table
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/dditems/figures/ddTextTableItemFigure.h"
#include "dd/dditems/tools/ddColumnFigureTool.h"
#include "dd/dditems/figures/ddColumnKindIcon.h"
#include "dd/dditems/figures/ddColumnOptionIcon.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddRelationshipItem.h"

void ddColumnFigure::Init(wxString &columnName, ddTableFigure *owner, ddRelationshipItem *sourceFk)
{
	setKindId(DDCOLUMNFIGURE);
	fkSource = sourceFk;
	usedAsFkDestFor = NULL;
	setOwnerTable(owner);
	deactivateGenFkName(); //initializae by default at not generate auto fk name
	columnText = new ddTextTableItemFigure(columnName, dt_null, this);
	kindImage = new ddColumnKindIcon(this);
	optionImage = new ddColumnOptionIcon(this);


	//Initialize displaybox and image coords
	basicDisplayBox.SetPosition(0, wxPoint(0, 0));    
	basicDisplayBox.SetSize( columnText->displayBox().GetSize());
	if(kindImage && optionImage)
	{
		basicDisplayBox.width += kindImage->displayBox().GetSize().GetWidth() + 3;
		basicDisplayBox.width += optionImage->displayBox().GetSize().GetWidth() + 3;
		columnText->displayBox().x[0] += kindImage->displayBox().GetSize().GetWidth() + 2;
		columnText->displayBox().x[0] += optionImage->displayBox().GetSize().GetWidth() + 3;
	}
	else
	{
		basicDisplayBox.width += 22; //default value = 1 + 8 + 3 + 8 + 2
		columnText->displayBox().x[0] += 22;
	}

	//Set Value default Attributes
	fontAttribute->font().SetPointSize(owner->fontAttribute->font().GetPointSize());

}

ddColumnFigure::ddColumnFigure(wxString &columnName, ddTableFigure *owner, ddRelationshipItem *sourceFk)
{
	Init(columnName, owner, sourceFk);
}

//Constructor for creation of existing column from storage
ddColumnFigure::ddColumnFigure(wxString &columnName, ddTableFigure *owner, ddColumnOptionType option, bool isGenFk, bool isPkColumn, wxString colDataType, int p, int s, int ukIdx, ddRelationshipItem *srcFk, ddRelationshipItem *usedAsFk )
{
	Init(columnName, owner, srcFk);
	setColumnOption(option);
	generateFkName = isGenFk;
	kindImage->setPrimaryKey(isPkColumn);

	int dtype = columnText->dataTypes().Index(colDataType,false);
	if(dtype != wxNOT_FOUND)
	{
		setDataType((ddDataType)dtype);
	}
	else
	{
		wxMessageBox(_("Not compatible data type for column found"));
	}

	columnText->setPrecision(p);
	columnText->setScale(s);
	kindImage->setUkIndex(ukIdx);

	usedAsFkDestFor = usedAsFk;
	if(ownerTable)
		ownerTable->updateTableSize();

}

ddColumnFigure::~ddColumnFigure()
{
	if(columnText)
		delete columnText;
	if(kindImage)
		delete kindImage;
	if(optionImage)
		delete optionImage;
}

void ddColumnFigure::AddPosForNewDiagram()
{
	//Add position for new displaybox at new diagram
	wxhdAttributeFigure::AddPosForNewDiagram();
	//Add position to each figure inside this composite figure
	if(kindImage)
		kindImage->AddPosForNewDiagram();
	if(optionImage)
		optionImage->AddPosForNewDiagram();
	if(columnText)
		columnText->AddPosForNewDiagram();
}

void ddColumnFigure::RemovePosOfDiagram(int posIdx)
{
	//Remove this position at displaybox of this figure
	wxhdAttributeFigure::RemovePosOfDiagram(posIdx);
	//Remove this position at each figure inside this composite figure
	if(kindImage)
		kindImage->RemovePosOfDiagram(posIdx);
	if(optionImage)
		optionImage->RemovePosOfDiagram(posIdx);
	if(columnText)
		columnText->RemovePosOfDiagram(posIdx);

}

void ddColumnFigure::basicMoveBy(int posIdx, int x, int y)
{
	wxhdAbstractFigure::basicMoveBy(posIdx, x, y);
	if(kindImage)
		kindImage->moveBy(posIdx, x, y);
	if(optionImage)
		optionImage->moveBy(posIdx, x, y);
	columnText->moveBy(posIdx, x, y);
}

void ddColumnFigure::moveTo(int posIdx, int x, int y)
{
	wxhdAbstractFigure::moveTo(posIdx, x, y);
	int distance = 0;

	if(kindImage)
	{
		kindImage->moveTo(posIdx, x, y);
		distance += kindImage->displayBox().GetSize().GetWidth() + 3;
	}
	else
	{
		distance += 11; //value = 8 + 3
	}

	if(optionImage)
	{
		optionImage->moveTo(posIdx, x + distance, y);
		distance += optionImage->displayBox().GetSize().GetWidth() + 3;
	}
	else
	{
		distance += 11; //value = 8 + 3
	}

	columnText->moveTo(posIdx, x + distance, y);
}


bool ddColumnFigure::containsPoint(int posIdx, int x, int y)
{
	bool out = false;

	if(columnText->containsPoint(posIdx, x, y))
		out = true;
	else if(kindImage->containsPoint(posIdx, x, y))
		out = true;
	else if(optionImage->containsPoint(posIdx, x, y))
		out = true;

	return out;
}

wxhdMultiPosRect &ddColumnFigure::getBasicDisplayBox()
{
	return basicDisplayBox;
}

void ddColumnFigure::basicDraw(wxBufferedDC &context, wxhdDrawingView *view)
{
	columnText->draw(context, view);
	if(kindImage)
		kindImage->draw(context, view);
	if(optionImage)
		optionImage->draw(context, view);
}

void ddColumnFigure::basicDrawSelected(wxBufferedDC &context, wxhdDrawingView *view)
{
	columnText->drawSelected(context, view);
	if(kindImage)
		kindImage->drawSelected(context, view);
	if(optionImage)
		optionImage->drawSelected(context, view);
}

wxhdIFigure *ddColumnFigure::findFigure(int posIdx, int x, int y)
{
	wxhdIFigure *out = NULL;

	if(columnText->containsPoint(posIdx, x, y))
		out = columnText;

	if(kindImage && kindImage->containsPoint(posIdx, x, y))
		out = kindImage;

	if(optionImage && optionImage->containsPoint(posIdx, x, y))
		out = optionImage;

	return out;
}

wxhdITool *ddColumnFigure::CreateFigureTool(wxhdDrawingView *view, wxhdITool *defaultTool)
{
	return new ddColumnFigureTool(view, this, defaultTool);
}

wxhdIFigure *ddColumnFigure::getFigureAt(int pos)
{
	if(pos == 0)
		return (wxhdIFigure *) kindImage;

	if(pos == 1)
		return (wxhdIFigure *) optionImage;

	if(pos == 2)
		return (wxhdIFigure *) columnText;

	return NULL;
}

ddTableFigure *ddColumnFigure::getOwnerTable()
{
	return ownerTable;
}

void ddColumnFigure::setOwnerTable(ddTableFigure *table)
{
	ownerTable = table;
}

void ddColumnFigure::displayBoxUpdate()
{
	if(kindImage && optionImage)
	{
		columnText->displayBoxUpdate();
		basicDisplayBox.width = columnText->displayBox().GetSize().GetWidth();
		basicDisplayBox.width += kindImage->displayBox().GetSize().GetWidth() + 3;
		basicDisplayBox.width += optionImage->displayBox().GetSize().GetWidth() + 3;
	}
	else
	{
		columnText->displayBoxUpdate();
		basicDisplayBox.width += 22; //default value = 1 + 8 + 3 + 8 +2
	}
}

bool ddColumnFigure::isNull()
{
	return optionImage->getOption() == null;
}

bool ddColumnFigure::isNotNull()
{
	return optionImage->getOption() == notnull;
}

bool ddColumnFigure::isNone()
{
	return kindImage->isNone();
}

bool ddColumnFigure::isPrimaryKey()
{
	return kindImage->isPrimaryKey();
}

void ddColumnFigure::disablePrimaryKey()
{
	kindImage->disablePrimaryKey();
}

void ddColumnFigure::enablePrimaryKey()
{
	kindImage->enablePrimaryKey();
}

bool ddColumnFigure::isUniqueKey()
{
	return kindImage->isUniqueKey();
}

bool ddColumnFigure::isUniqueKey(int uniqueIndex)
{
	return kindImage->isUniqueKey(uniqueIndex);
}

bool ddColumnFigure::isPlain()
{
	return kindImage->isNone();
}

void ddColumnFigure::setColumnKindToNone()
{
	kindImage->disablePrimaryKey();
	kindImage->disableUniqueKey();
	//Foreign key cannot be changed by set / toggle functions
}

void ddColumnFigure::setRightIconForColumn()
{
	kindImage->setRightIconForColumn();
}

void ddColumnFigure::toggleColumnKind(ddColumnType type, wxhdDrawingView *view)
{
	kindImage->toggleColumnKind(type, view);
}

void ddColumnFigure::setColumnOption(ddColumnOptionType type)
{
	optionImage->changeIcon(type);
}

wxString &ddColumnFigure::getColumnName(bool datatype)
{
	return columnText->getText(datatype);
}

int ddColumnFigure::getPrecision()
{
	return columnText->getPrecision();
}

int ddColumnFigure::getScale()
{
	return columnText->getScale();
}

int ddColumnFigure::getUniqueConstraintIndex()
{
	return kindImage->getUniqueConstraintIndex();
}

void ddColumnFigure::setUniqueConstraintIndex(int i)
{
	kindImage->setUniqueConstraintIndex(i);
}

ddColumnOptionType ddColumnFigure::getColumnOption()
{
	return optionImage->getOption();
}

ddDataType ddColumnFigure::getDataType()
{
	return columnText->getDataType();
}

void ddColumnFigure::setDataType(ddDataType type)
{
	columnText->setDataType(type);
}

void ddColumnFigure::setColumnName(wxString name)
{
	columnText->setText(name);
}

bool ddColumnFigure::isForeignKeyFromPk()
{
	if(fkSource)
	{
		return fkSource->isForeignKeyFromPk();
	}
	else if(usedAsFkDestFor)
	{
		return usedAsFkDestFor->isForeignKeyFromPk();
	}
	return false;
}

bool ddColumnFigure::isForeignKey()
{
	bool a = isUserCreatedForeignKey();
	bool b = isGeneratedForeignKey();
	return (a || b);
}

bool ddColumnFigure::isGeneratedForeignKey()
{
	return fkSource != NULL;
}

bool ddColumnFigure::isUserCreatedForeignKey()
{
	return usedAsFkDestFor != NULL;
}

ddRelationshipItem *ddColumnFigure::getRelatedFkItem()
{
	return usedAsFkDestFor;
}

void ddColumnFigure::setAsUserCreatedFk(ddRelationshipItem *relatedFkItem)
{
	usedAsFkDestFor = relatedFkItem;
	//Now fix icons of kind of column
	if(relatedFkItem == NULL)
	{
		kindImage->setRightIconForColumn();
	}
}

bool ddColumnFigure::isFkNameGenerated()
{
	return generateFkName;
}

void ddColumnFigure::activateGenFkName()
{
	generateFkName = true;
}

void ddColumnFigure::deactivateGenFkName()
{
	generateFkName = false;
}

wxString ddColumnFigure::generateSQL()
{
	wxString tmp;
	tmp = getColumnName();
	tmp += wxT(" ");
	tmp += columnText->getType();
	return tmp;
}

ddRelationshipItem *ddColumnFigure::getFkSource()
{
	return fkSource;
}

void ddColumnFigure::setTextColour(wxColour colour)
{
	columnText->fontColorAttribute->fontColor = colour;
}


//Validate status of column for SQL DDL generation
bool ddColumnFigure::validateColumn(wxString &errors)
{
	bool out = true;
	wxString tmp;

	if(usedAsFkDestFor)
	{
		//Validate if relationship is marked as identifying but column isn't marked as primary key
		wxString sourceTableName = usedAsFkDestFor->sourceTableName();
		wxString destTableName = usedAsFkDestFor->destTableName();
		wxString fkColName = usedAsFkDestFor->fkColumn->getColumnName(false);
		wxString sourceColName = usedAsFkDestFor->original->getColumnName(false);

		if(usedAsFkDestFor->relationIsIdentifying() && !this->isPrimaryKey())
		{
			out = false;
			tmp =  _("relation between table: ") + sourceTableName + _(" and table: ") + destTableName;
			tmp += _(" is marked as identifying but user created foreign key column: ") + fkColName;
			tmp += _(" isn't set as primary key \n");
			errors.Append(tmp);
		}
		//Validate if relationship is marked as optional but column is mandatory
		if( !usedAsFkDestFor->relationIsMandatory() && this->isNotNull())
		{
			out = false;
			tmp =  _("relation between table:") + sourceTableName + _(" and table: ") + destTableName;
			tmp += _("is marked as optional but user created foreign key column: ") + fkColName;
			tmp += _("is set as mandatory \n");
			errors.Append(tmp);
		}
		//Validate if relationship is marked as mandatory buy column is optional
		if( usedAsFkDestFor->relationIsMandatory() && this->isNull())
		{
			out = false;
			tmp =   _("relation between table:") + sourceTableName + _(" and table: ") + destTableName +
			        tmp +=  _(" is marked as mandatory but user created foreign key column: ") + fkColName;
			tmp += _("is set as optional \n");
			errors.Append(tmp);
		}

		//Validate datatype compatibility (right now only exactly same datatype)
		if(this->getDataType() != usedAsFkDestFor->original->getDataType())
		{
			out = false;
			tmp =  _("User created foreign key column: ") + fkColName + _("have different datatype from source column of relationship: ");
			tmp += sourceColName + _(" \n");
			errors.Append(tmp);
		}
	}

	return out;
}

//Used by persistence classes
void ddColumnFigure::setFkSource(ddRelationshipItem *newColumn)
{
	fkSource = newColumn;
}