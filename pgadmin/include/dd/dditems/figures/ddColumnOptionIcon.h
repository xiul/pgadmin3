//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddColumnOptionIcon.h -
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCOLUMNOPTIONICON_H
#define DDCOLUMNOPTIONICON_H

#include "dd/wxhotdraw/figures/wxhdAbstractMenuFigure.h"

class ddColumnFigure;

enum ddColumnOptionType
{
	null=0,
	notnull
};

enum
{
    MNU_COLNULL = 0,
    MNU_COLNOTNULL
};

class ddColumnOptionIcon : public ddAbstractMenuFigure
{
public:
	ddColumnOptionIcon(ddColumnFigure *owner);
    ~ddColumnOptionIcon();
	virtual void OnGenericPopupClick(wxCommandEvent& event, ddDrawingView *view=NULL);
    virtual void createMenu(wxMenu &mnu);
	virtual void basicDraw(wxBufferedDC& context, ddDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);		
	virtual void changeIcon(ddColumnOptionType type);
	virtual int getWidth();
	virtual int getHeight();
	ddColumnOptionType getOption();
	ddColumnFigure* getOwnerColumn();

protected:

private:
	ddColumnOptionType colOption;
	ddColumnFigure *ownerColumn;
	wxBitmap *iconToDraw;
	wxBitmap icon;
};
#endif
