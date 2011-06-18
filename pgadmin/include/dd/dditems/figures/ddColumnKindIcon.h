//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddColumnKindIcon.h - Figure container for kind of Column Images
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCOLUMNKINDICON_H
#define DDCOLUMNKINDICON_H

#include "dd/wxhotdraw/figures/wxhdAbstractMenuFigure.h"

class ddColumnFigure;

enum ddColumnType {
	pk=0,
	uk,
	fk,
	pkuk,
	none
};

enum
{
    MNU_DDCTPKEY = 0,
    MNU_DDCTUKEY
};

class ddColumnKindIcon : public wxhdAbstractMenuFigure
{
public:
	ddColumnKindIcon(ddColumnFigure *owner);
    ~ddColumnKindIcon();
	virtual void OnGenericPopupClick(wxCommandEvent& event, wxhdDrawingView *view=NULL);
    virtual void createMenu(wxMenu &mnu);
	virtual void basicDraw(wxBufferedDC& context, wxhdDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC& context, wxhdDrawingView *view);		
	virtual void changeIcon(ddColumnType type, wxhdDrawingView *view=NULL, bool interaction=true);
	virtual int getWidth();
	virtual int getHeight();
	ddColumnType getKind();
	ddColumnFigure* getOwnerColumn();
	virtual int getUniqueConstraintIndex();
	virtual void setUniqueConstraintIndex(int i);
	virtual void checkConsistencyOfKind();
	

protected:

private:
	ddColumnFigure *ownerColumn;
	ddColumnType colType;
	wxBitmap *iconToDraw;
	wxBitmap icon;
	int ukIndex;

	//multiple Uk management at table
	void syncUkIndexes();
	void uniqueConstraintManager(bool ukCol, wxhdDrawingView *view=NULL, bool interaction=true);
};
#endif
