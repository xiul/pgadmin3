//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddSimpleTextFigure.h - A simple rectangle  figure with text inside it
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDSIMPLETEXTFIGURE_H
#define DDSIMPLETEXTFIGURE_H
#include "dd/draw/figures/ddAbstractFigure.h"

class ddDrawingView;

class ddSimpleTextFigure : public ddAbstractFigure
{
public:
	ddSimpleTextFigure(wxString textString);
    ~ddSimpleTextFigure();
	virtual void setText(wxString textString);
	virtual wxString& getText(bool extended = false);
	virtual void setEditable(bool value);
	virtual bool getEditable();
	virtual void setFont(wxFont textFont);
	virtual void setForeground(wxColour colour);
	virtual void setBackground(wxBrush background);
	virtual int getPadding();
	void basicMoveBy(int x, int y);
	virtual void basicDraw(wxBufferedDC& context, ddDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
	virtual void createMenu(wxMenu &mnu) {}
	virtual void enablePopUp();
	virtual void disablePopUp();
	virtual bool menuEnabled();
	virtual void OnGenericPopupClick(wxCommandEvent& event, ddDrawingView *view);
protected:
	virtual void getFontMetrics(int &width, int &height);
	virtual void recalculateDisplayBox();
	virtual void setupLayout(wxBufferedDC& context);
	wxArrayString strings;
	bool showMenu;
	bool textEditable;
private:
	int padding;
	wxString text;
	wxFont font;
	wxColour textForeground;
	wxBrush textBackground;
	

};
#endif
