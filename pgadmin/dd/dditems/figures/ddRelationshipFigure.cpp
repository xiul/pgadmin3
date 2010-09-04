//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRelationshipFigure.cpp

//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/dditems/figures/ddRelationshipFigure.h"
#include "dd/draw/main/ddDrawingView.h"

ddRelationshipFigure::ddRelationshipFigure():
ddLineConnection()
{
	setKindId(200);  //DD-TODO: improve this
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

//DD-TODO: this function is execute two times at least each time because observers store in & out foreign key, fix this behavior
void ddRelationshipFigure::updateForeignKey()
{
	if(getEndFigure() && getStartFigure() && getStartFigure()->ms_classInfo.IsKindOf(&ddTableFigure::ms_classInfo) && getEndFigure()->ms_classInfo.IsKindOf(&ddTableFigure::ms_classInfo))
	{
		ddTableFigure *startTable = (ddTableFigure*) getStartFigure();
		ddTableFigure *endTable = (ddTableFigure*) getEndFigure();
		ddColumnFigure *col;
		ddRelationshipItem *NewFkColumn;

		ddIteratorBase *iterator = startTable->figuresEnumerator();
		iterator->Next(); //First Figure is Main Rect
		iterator->Next(); //Second Figure is Table Title
		while(iterator->HasNext())
		{
			col = (ddColumnFigure*) iterator->Next();
			if(fkFromPk)  //RELATIONSHIP KIND IS USING A PK (PRIMARY KEY) AS FOREIGN KEYS
			{
				//Add new pk columns from source fk table to destination
				columnsHashMap::iterator it = chm.find(col->getColumnName());
				bool NotFound = it == chm.end(); // will be true if not found

				if( col->isPrimaryKey() && NotFound )
				{
					NewFkColumn = new ddRelationshipItem(col,endTable, (fkMandatory?notnull:null), (fkIdentifying?pk:fk) );
					chm[col->getColumnName()]=NewFkColumn; //key will be original table name always
					endTable->addColumn(NewFkColumn->fkColumn);
					//hack to update relationship position when table size change
					endTable->moveBy(-1,0);
					endTable->moveBy(1,0);
				}

				//Delete old Fk columns now not pk or deleted from source fk table.
				//DD-TODO: optimize this later  and add deletes when needed

				//Hack to repeat for every time a column is elimite because hashmap is modified inside a for and now is invalid that for loop
				bool repeat;   
				do
                {
					repeat=false;
					for (it = chm.begin(); it != chm.end(); ++it)
					{
						wxString key = it->first;
						NewFkColumn = it->second;
						if( !NewFkColumn->original->isPrimaryKey() || !startTable->includes(NewFkColumn->original) )
						{
							ddTableFigure *tmpTable=NewFkColumn->destinationTable;
							NewFkColumn->destinationTable->removeColumn(NewFkColumn->fkColumn);
							chm.erase(it);
							delete NewFkColumn;
							repeat=true;
							//hack to update relationship position when table size change
							tmpTable->moveBy(-1,0);
							tmpTable->moveBy(1,0);
						}
						if (repeat)
							break;
					}
				} while(repeat);
			}
			else   //RELATIONSHIP KIND IS USING A UK (UNIQUE KEY) AS FOREIGN KEYS
			{
				//DD-TODO: Add this functionality.
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
	switch(event.GetId())
	{
		case MNU_FKEYFROMPKEY:
		case MNU_FKEYFROMUKEY:
			wxMessageBox(wxT("To be implemented soon..."), wxT("To be implemented soon..."), wxICON_INFORMATION, (wxScrolledWindow*) view);
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
		ddRelationshipItem *NewFkColumn;

		//Hack to repeat for every time a column is elimite because hashmap is modified inside a for and now is invalid that for loop
		bool repeat;   
		do
        {
            repeat=false;
			for( it = chm.begin(); it != chm.end(); ++it )
			{
				wxString key = it->first;
				NewFkColumn = it->second;
				if(NewFkColumn->destinationTable->includes(NewFkColumn->fkColumn) )
				{
					NewFkColumn->destinationTable->removeColumn(NewFkColumn->fkColumn);
					chm.erase(it);
					delete NewFkColumn;
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

ddRelationshipItem::ddRelationshipItem(ddColumnFigure *originalColumn, ddTableFigure *destination, ddColumnOptionType type, ddColumnType colType)
{
	original = originalColumn;
	destinationTable = destination;
	wxString newName = originalColumn->getOwnerTable()->getTableName();
	newName.append(wxT("_"));
	newName.append(originalColumn->getColumnName(false));
	//DD-TODO: improve fk name
	fkColumn = new ddColumnFigure(newName,destinationTable,this);
	fkColumn->setColumnOption(type);
	fkColumn->setColumnKind(colType);
}

ddRelationshipItem::~ddRelationshipItem()
{
}

