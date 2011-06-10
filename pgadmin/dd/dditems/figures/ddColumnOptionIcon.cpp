//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddColumnOptionIcon.cpp - Part of composite column figure, allow to choose between: not null and null
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/dditems/figures/ddColumnOptionIcon.h"
#include "dd/wxhotdraw/main/ddDrawingView.h"
#include "dd/dditems/figures/ddColumnFigure.h"

//Images
#include "images/ddnull.xpm"
#include "images/ddnotnull.xpm"

ddColumnOptionIcon::ddColumnOptionIcon(ddColumnFigure *owner)
{
	ownerColumn=owner; 
	colOption=null;
	icon = wxBitmap(ddnull_xpm);
	iconToDraw = &icon;
	getBasicDisplayBox().SetSize(wxSize(getWidth(),getHeight()));
}

ddColumnOptionIcon::~ddColumnOptionIcon()
{
}

void ddColumnOptionIcon::createMenu(wxMenu &mnu)
{
    wxMenuItem *item;
    
	item = mnu.AppendCheckItem(MNU_COLNULL, _("NULL"));
	item->Check(colOption==null);
	item->Enable(!getOwnerColumn()->isForeignKey());
	item = mnu.AppendCheckItem(MNU_COLNOTNULL, _("Not NULL"));
	item->Check(colOption==notnull);
	item->Enable(!getOwnerColumn()->isForeignKey());
}

void ddColumnOptionIcon::OnGenericPopupClick(wxCommandEvent& event, ddDrawingView *view)
{
	changeIcon((ddColumnOptionType)event.GetId());
}

void ddColumnOptionIcon::changeIcon(ddColumnOptionType type)
{
	colOption=type;
	switch(type)
	{
		case MNU_COLNULL:
            icon = wxBitmap(ddnull_xpm);
            if(getOwnerColumn()->isPrimaryKey())
            {
                if(getOwnerColumn()->isForeignKey())
                    getOwnerColumn()->setColumnKind(fk);
                else
                    getOwnerColumn()->setColumnKind(none);
            }
            break;
		case MNU_COLNOTNULL:
            icon = wxBitmap(ddnotnull_xpm);
            break;
	}
	getBasicDisplayBox().SetSize(wxSize(getWidth(),getHeight()));
}

void ddColumnOptionIcon::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	if(iconToDraw)
	{
		ddRect copy = displayBox();
		view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
		context.DrawBitmap(*iconToDraw,copy.GetPosition(),true);
	}
}

void ddColumnOptionIcon::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	basicDraw(context,view);
}

int ddColumnOptionIcon::getWidth()
{
	if(iconToDraw)
		return iconToDraw->GetWidth();
	else
		return 8;
}

int ddColumnOptionIcon::getHeight()
{
	if(iconToDraw)
		return iconToDraw->GetHeight();
	else
		return 10;
}

ddColumnOptionType ddColumnOptionIcon::getOption()
{
	return colOption;
}

ddColumnFigure* ddColumnOptionIcon::getOwnerColumn()
{
	return ownerColumn;
}
