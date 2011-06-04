//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddColumnKindIcon.cpp - Figure container for kind of Column Images
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/dditems/figures/ddColumnKindIcon.h"
#include "dd/draw/main/ddDrawingView.h"
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/dditems/figures/ddTableFigure.h"

//Images
#include "images/ddforeignkey.xpm"
#include "images/ddprimarykey.xpm"
#include "images/ddunique.xpm"
#include "images/ddprimaryforeignkey.xpm"

ddColumnKindIcon::ddColumnKindIcon(ddColumnFigure *owner)
{
	ownerColumn=owner;
	colType = none;
	// Initialize with an image to allow initial size calculations
	icon = wxBitmap(ddprimarykey_xpm);
    iconToDraw = NULL;
	getBasicDisplayBox().SetSize(wxSize(getWidth(),getHeight()));
	ukIndex=-1;
}

ddColumnKindIcon::~ddColumnKindIcon()
{
}

void ddColumnKindIcon::createMenu(wxMenu &mnu)
{
    wxMenuItem *item;
    
	item = mnu.AppendCheckItem(MNU_DDCTPKEY, _("Primary key"));
    item->Check(colType==pk);
    item->Enable(!getOwnerColumn()->isForeignKey());
	item = mnu.AppendCheckItem(MNU_DDCTUKEY, _("Unique key"));
    item->Check(colType==uk);
}

void ddColumnKindIcon::OnGenericPopupClick(wxCommandEvent& event, ddDrawingView *view)
{
	changeIcon((ddColumnType)event.GetId(),view);
}

ddColumnFigure* ddColumnKindIcon::getOwnerColumn()
{
	return ownerColumn;
}

void ddColumnKindIcon::changeIcon(ddColumnType type, ddDrawingView *view, bool interaction) 
{
	bool ukCol = colType==uk;
	
	wxString tmpString;
	switch(type)
	{
		case pk:	
				if(getOwnerColumn()->isForeignKey())
				{
					icon = wxBitmap(ddprimaryforeignkey_xpm);
				}
				else
				{
					icon = wxBitmap(ddprimarykey_xpm);
				}

				if(colType==pk){
					getOwnerColumn()->getOwnerTable()->prepareForDeleteFkColumn(getOwnerColumn());
					colType=none;
				}
				else
				{
					if(colType==uk)
					{
						syncUkIndexes();
						ukIndex=-1;
					}
					colType=pk;
				}
//				if(!getOwnerColumn()->isForeignKey())
//				{
					getOwnerColumn()->getOwnerTable()->updateFkObservers();
//				}
				break;
		case uk:
				uniqueConstraintManager(ukCol,view,interaction);
				icon = wxBitmap(ddunique_xpm);
				getOwnerColumn()->getOwnerTable()->updateFkObservers();					
				break;
		case fk:
				icon = wxBitmap(ddforeignkey_xpm);
				colType=fk;
				break;
		case pkuk:
				break;
		case none: 
			    colType=none;
				if(colType==uk || fk)
					getOwnerColumn()->getOwnerTable()->prepareForDeleteFkColumn(getOwnerColumn());
				break;
	}
    if(colType!=none)
    {
		iconToDraw = &icon;
	}
	else
	{
		iconToDraw = NULL;
		ukIndex=-1;
/*		if(!getOwnerColumn()->isForeignKey())  //this is not fk column
		{*/
			//getOwnerColumn()->getOwnerTable()->prepareForDeleteFkColumn(getOwnerColumn());
			getOwnerColumn()->getOwnerTable()->updateFkObservers();
		//}
	}
	getBasicDisplayBox().SetSize(wxSize(getWidth(),getHeight()));
}

void ddColumnKindIcon::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	if(iconToDraw)
	{
		ddRect copy = displayBox();
		view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
		//Adding a yellow circle to increase visibility of uk index
		if(colType==uk)
		{
			context.SetBrush(wxBrush(wxColour(wxT("YELLOW")), wxSOLID));
			context.SetPen(wxPen(wxColour(wxT("YELLOW"))));
			context.DrawCircle(copy.x+6,copy.y+7,4);
		}
		//Draw icon
		context.DrawBitmap(*iconToDraw,copy.GetPosition(),true);
		//Draw Uk index if needed
		if(colType==uk && ukIndex>0)
		{
			wxFont font = settings->GetSystemFont();
			font.SetPointSize(6);
			context.SetFont(font);
			wxString inumber = wxString::Format(wxT("%d"), (int)ukIndex+1);
			context.DrawText(inumber,copy.x+4,copy.y+2);
		}
	}
}

void ddColumnKindIcon::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	basicDraw(context,view);
}

int ddColumnKindIcon::getWidth()
{
	if(iconToDraw)
		return iconToDraw->GetWidth();
	else
		return 8;
}

int ddColumnKindIcon::getHeight()
{
	if(iconToDraw)
		return iconToDraw->GetHeight();
	else
		return 10;
}

ddColumnType ddColumnKindIcon::getKind()
{
	return colType;
}

int ddColumnKindIcon::getUniqueConstraintIndex()
{
	return ukIndex;
}

void ddColumnKindIcon::setUniqueConstraintIndex(int i)
{
	ukIndex=i;
}

void ddColumnKindIcon::uniqueConstraintManager(bool ukCol, ddDrawingView *view, bool interaction)
{
    wxString tmpString;
    colType=uk;
    if(ukCol) //if already this column kind is Unique Key then convert in a normal column
    {
        syncUkIndexes();
        getOwnerColumn()->setUniqueConstraintIndex(-1);
        colType=none;
    }
    else //colType!=uk
    {
        if(interaction)
		{
            if(ownerColumn->getOwnerTable()->getUkConstraintsNames().Count()==0)
            {
                tmpString = getOwnerColumn()->getOwnerTable()->getTableName();
                tmpString.append(wxT("_uk"));
                tmpString=wxGetTextFromUser(wxT("Name of new Unique Key constraint:"),tmpString,tmpString,view);
                if(tmpString.length()>0)
                {
                    getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Add(tmpString);						
                    ukIndex=0;
                }
                else
                {
                    colType=none;
                    ukIndex=-1;
                }
            }
            else  //>0
            {
                getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Add(wxString(wxT("Add new Unique Constraint...")));
                unsigned int i = wxGetSingleChoiceIndex(wxT("Select Unique Key to add Column"),wxT("Select Unique Key to add Column:"),getOwnerColumn()->getOwnerTable()->getUkConstraintsNames(),view);
                getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().RemoveAt(getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Count()-1);
                if(i>=0)
                {
                    if(i==getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Count())
                    {
                        tmpString = getOwnerColumn()->getOwnerTable()->getTableName();
                        tmpString.append(wxT("_uk"));
                        
                        int newIndex=i+1;
                        wxString inumber = wxString::Format(wxT("%s%d"), tmpString.c_str(),(int)newIndex);
                        //Validate new name of uk doesn't exists
                        while(getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Index(inumber,false)!=-1){
                            newIndex++;
                            inumber = wxString::Format(wxT("%s%d"), tmpString.c_str(),(int)newIndex);
                        }
                        inumber = wxString::Format(wxT("%d"), (int)newIndex);
                        tmpString.append(inumber);
                        tmpString=wxGetTextFromUser(wxT("Name of new Unique Key constraint:"),tmpString,tmpString,view);
                        if(tmpString.length()>0)
                        {
                            getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Add(tmpString);						
                            ukIndex=i;
                        }
                        else
                        {
                            colType=none;
                            ukIndex=-1;
                        }
                    }
                    else
                    {
                        ukIndex=i;
                    }
                }
                else
                {
                    colType=none;
                    ukIndex=-1;
                }
            }
        }
		else //without user interaction for
		{
			//DD-TODO: solve problem of setting values without user interaction for model persistence
		}
    }
}

//synchronize uk indexes when an uk is change kind from uk to other and other index should be update with that info
void ddColumnKindIcon::syncUkIndexes()
{
	ddColumnFigure *col;
	bool lastUk=true;
	ddIteratorBase *iterator = getOwnerColumn()->getOwnerTable()->figuresEnumerator();
    iterator->Next(); //First Figure is Main Rect
    iterator->Next(); //Second Figure is Table Title
    while(iterator->HasNext())
    {
        col = (ddColumnFigure*) iterator->Next();
        
        if(col!=getOwnerColumn() && (col->getUniqueConstraintIndex() == getOwnerColumn()->getUniqueConstraintIndex()))
		{ 
		  lastUk=false;
		  break;
		}
    }
	if(lastUk)
	{
		//here uks indexes are fixed
		iterator->ResetIterator();
		iterator->Next(); //First Figure is Main Rect
		iterator->Next(); //Second Figure is Table Title
		while(iterator->HasNext())
		{
			col = (ddColumnFigure*) iterator->Next();
			if( col->getUniqueConstraintIndex() > getOwnerColumn()->getUniqueConstraintIndex() ) 
				col->setUniqueConstraintIndex(col->getUniqueConstraintIndex()-1);
		}
		getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().RemoveAt(getOwnerColumn()->getUniqueConstraintIndex());
		getOwnerColumn()->setUniqueConstraintIndex(-1);
	}
	delete iterator;
}
