//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRelationshipFigure.cpp - Figure to draw foreign keys between tables.
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/dditems/figures/ddRelationshipFigure.h"
#include "dd/draw/main/ddDrawingView.h"
#include "dd/dditems/utilities/ddDataType.h"

ddRelationshipFigure::ddRelationshipFigure():
ddLineConnection()
{
	setKindId(ddRelFig);
	fkFromPk = true;
	fkMandatory = true;
	fkOneToMany = true;
	fkIdentifying = false;
	ukIndex = -1;
	disconnectedEndTable = NULL;
	enablePopUp();

}

ddRelationshipFigure::ddRelationshipFigure(ddIFigure *figure1, ddIFigure *figure2):
ddLineConnection(figure1,figure2)
{
	enablePopUp();
}

ddRelationshipFigure::~ddRelationshipFigure()
{
	columnsHashMap::iterator it;
	ddRelationshipItem *item;
	for (it = chm.begin(); it != chm.end(); ++it)
	{
		wxString key = it->first;
		item = it->second;
		delete item;
	}
	chm.clear();
}

void ddRelationshipFigure::updateForeignKey()
{
	if(getEndFigure() && getStartFigure() && getStartFigure()->ms_classInfo.IsKindOf(&ddTableFigure::ms_classInfo) && getEndFigure()->ms_classInfo.IsKindOf(&ddTableFigure::ms_classInfo))
	{
		ddTableFigure *startTable = (ddTableFigure*) getStartFigure();
		ddTableFigure *endTable = (ddTableFigure*) getEndFigure();
		ddColumnFigure *col;
		ddRelationshipItem *fkColumnRelItem;



		ddIteratorBase *iterator = startTable->figuresEnumerator();
		iterator->Next(); //first figure is main rect
		iterator->Next(); //second figure is table title
		
		//STEP 0: Before iterate over all columns of source table look if any column used at relationship, changed their name and updated it when needed
		columnsHashMap::iterator it;
		for (it = chm.begin(); it != chm.end(); ++it)
		{
			wxString key = it->first;
			fkColumnRelItem = it->second;
			if(!fkColumnRelItem->original->getColumnName(false).IsSameAs(fkColumnRelItem->originalStartColName,false))
			{
				//DD-TODO: update key of hashmap with new value because key changed
				chm[fkColumnRelItem->original->getColumnName(false)]=fkColumnRelItem;
				chm[fkColumnRelItem->originalStartColName]=NULL;
				chm.erase(it);
				fkColumnRelItem->syncAutoFkName();
				break;
			}
		}

		//STEP 1: Look at all source table columns
		while(iterator->HasNext())
		{
			col = (ddColumnFigure*) iterator->Next();
			if(fkFromPk)  //fk is generated from a pk column: add new fk/pk(s) column(s) from source fk table to destination
			{
				//STEP 1.1a: Add fk columns from table source pk if not exists using same name
				it = chm.find(col->getColumnName());
				bool NotFound = it == chm.end();

				if( col->isPrimaryKey() && NotFound )
				{
					fkColumnRelItem = new ddRelationshipItem(this,col,endTable, (fkMandatory?notnull:null), (fkIdentifying?pk:fk) );
					chm[col->getColumnName()]=fkColumnRelItem; //hashmap key will be original table name always
					endTable->addColumn(fkColumnRelItem->fkColumn);
					updateConnection();
				}

				//STEP 1.2a: Delete old Fk columns not pk now or deleted from source fk table.
				//This part of code (repeat) is a hack cause every time a column is delete hashmap is modified inside and becomes invalid iterator at that loop
				bool repeat;   
				do
                {
					repeat=false;
					for (it = chm.begin(); it != chm.end(); ++it)
					{
						wxString key = it->first;
						fkColumnRelItem = it->second;
						if( !fkColumnRelItem->original->isPrimaryKey() || !startTable->includes(fkColumnRelItem->original) )
						{
							ddTableFigure *tmpTable=fkColumnRelItem->destinationTable;
							fkColumnRelItem->destinationTable->removeColumn(fkColumnRelItem->fkColumn);
							chm.erase(it);
							delete fkColumnRelItem;
							repeat=true;
							updateConnection();
						}
						if (repeat)
							break;
					}
				} while(repeat);
			}
			else   //fk is generated from a uk column: add new fk/pk(s) column(s) from source fk table to destination
			{
				//STEP 1.1b: Add fk columns from table source uk if not exists
				columnsHashMap::iterator it = chm.find(col->getColumnName());
				bool NotFound = it == chm.end();

				if( col->isUniqueKey(ukIndex) && NotFound )
				{
					fkColumnRelItem = new ddRelationshipItem(this,col,endTable, (fkMandatory?notnull:null), fk );
					chm[col->getColumnName()]=fkColumnRelItem; //hashmap key will be original table name always
					endTable->addColumn(fkColumnRelItem->fkColumn);
					updateConnection();
				}

				//STEP 1.2b: Delete old Fk columns not pk now or deleted from source fk table.
				//This part of code (repeat) is a hack cause every time a column is delete hashmap is modified inside and becomes invalid iterator at that loop
				bool repeat;   
				do
                {
					repeat=false;
					for (it = chm.begin(); it != chm.end(); ++it)
					{
						wxString key = it->first;
						fkColumnRelItem = it->second;
						if( !fkColumnRelItem->original->isUniqueKey(ukIndex) || !startTable->includes(fkColumnRelItem->original) )
						{
							ddTableFigure *tmpTable=fkColumnRelItem->destinationTable;
							fkColumnRelItem->destinationTable->removeColumn(fkColumnRelItem->fkColumn);
							chm.erase(it);
							delete fkColumnRelItem;
							repeat=true;
							updateConnection();
						}
						if (repeat)
							break;
					}
				} while(repeat);

			}
		}
		delete iterator;
	}
	else 
	{
		wxMessageBox(wxT("Error invalid kind of start figure at relationship"),wxT("Error invalid kind of start figure at relationship"),wxICON_ERROR);
	}
}

void ddRelationshipFigure::createMenu(wxMenu &mnu)
{
    wxMenuItem *item;
    
	item = mnu.AppendCheckItem(MNU_FKEYFROMPKEY, _("Foreign Key from Primary Key"));
	item->Check(fkFromPk);
	item = mnu.AppendCheckItem(MNU_FKEYFROMUKEY, _("Foreign Key from Unique Key"));
	item->Check(!fkFromPk);
	mnu.AppendSeparator();
	item = mnu.AppendCheckItem(MNU_MANDATORYRELATIONSHIP, _("Mandatory relationship kind"));
	item->Check(fkMandatory);
	item = mnu.AppendCheckItem(MNU_IDENTIFYINGRELATIONSHIP, _("Identifying relationship"));
	item->Check(fkIdentifying);
	mnu.AppendSeparator();
	item = mnu.AppendCheckItem(MNU_1MRELATIONSHIP, _("1:M"));
	item->Check(fkOneToMany);
	item = mnu.AppendCheckItem(MNU_11RELATIONSHIP, _("1:1"));
	item->Check(!fkOneToMany);
	mnu.AppendSeparator();
    mnu.Append(MNU_DELETERELATIONSHIP, _("Delete Relationship..."));
};

void ddRelationshipFigure::OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view)
{
	int answer;
	ddTableFigure *startTable = NULL;
	switch(event.GetId())
	{
		case MNU_FKEYFROMPKEY:
			fkFromPk = true;
			updateForeignKey();
			break;
		case MNU_FKEYFROMUKEY:
			fkFromPk = false;
			startTable = (ddTableFigure*) getStartFigure();
			if(startTable)
				ukIndex = wxGetSingleChoiceIndex(wxT("Select Unique Key to usea as foreign Key Source"),wxT("Select Unique Key to add Column:"),startTable->getUkConstraintsNames(),view);
			else
				wxMessageBox(wxT("Error trying to get start table of foreign key connection"), wxT("Error trying to get start table of foreign key connection"),wxICON_ERROR, (wxScrolledWindow*)view);	
			if(ukIndex == -1)
			{
				fkFromPk = true;
			}
			updateForeignKey();
			break;
		case MNU_MANDATORYRELATIONSHIP:
			fkMandatory=!fkMandatory;
			if(fkMandatory)
			{
				setLinePen(wxPen(*wxBLACK_PEN));
				setOptionAtForeignKeys(notnull);
			}
			else
			{
				fkIdentifying=false;
				setLinePen(wxPen(*wxBLACK,1,wxSHORT_DASH));		
				setOptionAtForeignKeys(null);
			}
			break;
		case MNU_IDENTIFYINGRELATIONSHIP:
			fkMandatory = true;
			setLinePen(wxPen(*wxBLACK_PEN));
			fkIdentifying=!fkIdentifying;
			fkOneToMany = true;
			if(fkIdentifying)
			{
				setKindAtForeignKeys(pk);
			}
			else
			{
				setKindAtForeignKeys(fk);
			}
			break;
		case MNU_1MRELATIONSHIP:
		case MNU_11RELATIONSHIP:
			fkOneToMany=!fkOneToMany;
			break;
		case MNU_DELETERELATIONSHIP:
			if(getStartFigure() && getEndFigure())
			{
				ddTableFigure *t1=(ddTableFigure*)getStartFigure();
				ddTableFigure *t2=(ddTableFigure*)getEndFigure();
				answer = wxMessageBox(wxT("Are you sure you wish to delete relationship between tables ") + t1->getTableName() + wxT(" and ")+ t2->getTableName() + wxT("?"), wxT("Delete relationship?"), wxYES_NO|wxNO_DEFAULT, (wxScrolledWindow*)view);
				if (answer == wxYES)
				{
					if(view->isFigureSelected(this))
						view->removeFromSelection(this);
					disconnectStart();
					disconnectEnd();
					//Hack to autodelete relationship
					ddRelationshipFigure *r=this;
					view->remove(this);
					if(r)
						delete r;
				}
			}
			break;
	}
}

bool ddRelationshipFigure::getIdentifying()
{
	return fkIdentifying;
}

bool ddRelationshipFigure::getOneToMany()
{
	return fkOneToMany;
}

bool ddRelationshipFigure::getMandatory()
{
	return fkMandatory;
}

/*
	relationship is observed by several tables at same time, one is the
	owner (start connector table) others are just observers of that 
	relationship (end connectors table)

	because this we don't need to register rel at 
*/

void ddRelationshipFigure::connectEnd(ddIConnector *end)
{
	ddLineConnection::connectEnd(end);
	if(getEndFigure() && getStartFigure())
		updateForeignKey();
}

void ddRelationshipFigure::connectStart(ddIConnector *start)
{
	ddLineConnection::connectStart(start);
	if(getEndFigure() && getStartFigure())
		updateForeignKey();
}

void ddRelationshipFigure::disconnectStart()
{
	disconnectedEndTable = (ddTableFigure*) getEndFigure();
	removeForeignKeys();
	ddLineConnection::disconnectStart();
}

void ddRelationshipFigure::disconnectEnd()
{
	disconnectedEndTable = (ddTableFigure*) getEndFigure();
	ddLineConnection::disconnectEnd();
	removeForeignKeys();

}

void ddRelationshipFigure::removeForeignKeys()
{
	if(disconnectedEndTable)
	{
		columnsHashMap::iterator it;
		ddRelationshipItem *fkColumnRelItem;

		//This part of code (repeat) is a hack cause every time a column is delete hashmap is modified inside and becomes invalid iterator at that loop
		bool repeat;   
		do
        {
            repeat=false;
			for( it = chm.begin(); it != chm.end(); ++it )
			{
				wxString key = it->first;
				fkColumnRelItem = it->second;
				if(fkColumnRelItem->destinationTable->includes(fkColumnRelItem->fkColumn) )
				{
					fkColumnRelItem->destinationTable->removeColumn(fkColumnRelItem->fkColumn);
					chm.erase(it);
					delete fkColumnRelItem;
					repeat = true;
					break;
				}
			}
		} while(repeat);
		chm.clear();
		disconnectedEndTable=NULL;
	}
}

void ddRelationshipFigure::setOptionAtForeignKeys(ddColumnOptionType type)
{
	columnsHashMap::iterator it;
	ddRelationshipItem *item;
	for (it = chm.begin(); it != chm.end(); ++it)
	{
		wxString key = it->first;
		item = it->second;
		item->fkColumn->setColumnOption(type);
	}
}

void ddRelationshipFigure::setKindAtForeignKeys(ddColumnType type)
{
	columnsHashMap::iterator it;
	ddRelationshipItem *item;
	for (it = chm.begin(); it != chm.end(); ++it)
	{
		wxString key = it->first;
		item = it->second;
		item->fkColumn->setColumnKind(type);
	}
	if(type==pk || type==fk) //set as identifying relationship (hierarchy)
	{
		ddTableFigure *table = (ddTableFigure*) getEndFigure();
		table->updateFkObservers();
	}
}
wxString ddRelationshipFigure::generateSQL()
{
	wxString tmp;
	if(chm.size() > 0)
	{
		tmp=wxT("FOREIGN KEY ( ");
		columnsHashMap::iterator it, end;
		ddRelationshipItem *item;
		for( it = chm.begin(); it != chm.end(); ++it )
		{
			wxString key = it->first;
			item = it->second;
			tmp += item->fkColumn->getColumnName();
			end=it;
			end++;
			if(end!=chm.end())
			{
				tmp+=wxT(" , ");
			}
			else
			{
				tmp+=wxT(" )");
			}
		}	
		
		tmp += wxT(" REFERENCES ") + ((ddTableFigure*)getStartFigure())->getTableName() + wxT(" ( ");
		for( it = chm.begin(); it != chm.end(); ++it )
		{
			wxString key = it->first;
			item = it->second;
			tmp += item->original->getColumnName();
			end=it;
			end++;			
			if(end!=chm.end())
			{
				tmp+=wxT(" , ");
			}
			else
			{
				tmp+=wxT(" )");
			}
		}
	}
	return tmp;
}

/************************
Items at hash map table
*************************/

ddRelationshipItem::ddRelationshipItem(ddRelationshipFigure *owner, ddColumnFigure *originalColumn, ddTableFigure *destination, ddColumnOptionType type, ddColumnType colType)
{
	ownerRel=owner;
	original = originalColumn;
	originalStartColName = original->getColumnName(false);
	destinationTable = destination;
	fkColumn = new ddColumnFigure(autoGenerateNameForFk(),destinationTable,this);
	fkColumn->setColumnOption(type);
	fkColumn->setColumnKind(colType);
	fkColumn->activateGenFkName();
}

wxString ddRelationshipItem::autoGenerateNameForFk()
{
	//DD-TODO: improve auto fk name
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
	if(fkColumn->isForeignKey() && fkColumn->isFkNameGenerated() ) 
	{
		fkColumn->setColumnName(autoGenerateNameForFk());
		ownerRel->updateConnection();
	}
}

ddRelationshipItem::~ddRelationshipItem()
{
}

