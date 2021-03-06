//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdDrawingView.h - Main canvas where all figures are drawn
//
//////////////////////////////////////////////////////////////////////////

#ifndef WXHDDRAWINGVIEW_H
#define WXHDDRAWINGVIEW_H

#include "dd/wxhotdraw/figures/wxhdIFigure.h"
#include "dd/wxhotdraw/main/wxhdDrawing.h"
#include "dd/wxhotdraw/handles/wxhdIHandle.h"
#include "dd/wxhotdraw/figures/wxhdSimpleTextFigure.h"
#include "dd/wxhotdraw/figures/wxhdAbstractMenuFigure.h"

class wxhdCanvasMenuTool;

// Create View Class for MVC pattern of graphic library of pgAdmin
enum
{
	CTL_TEXTTOOLID = 1979,
	CTL_OKBUTTONID,
	CTL_CANCELBUTTONID
};

class wxhdDrawingView : public wxScrolledWindow
{
public:
	wxhdDrawingView(int diagram, wxWindow *ddParent, wxhdDrawingEditor *editor , wxSize size, wxhdDrawing *drawing);
	~wxhdDrawingView();

	virtual void ScrollToMakeVisible(wxhdPoint p);
	virtual void ScrollToMakeVisible (wxhdRect r);
	virtual wxhdIHandle *findHandle(int posIdx, double x, double y);
	virtual wxhdDrawing *getDrawing();

	void onPaint(wxPaintEvent &event);
	void onEraseBackGround(wxEraseEvent &event);
	virtual void onMouseDown(wxMouseEvent &event);
	virtual void onMouseUp(wxMouseEvent &event);
	virtual void onMotion(wxMouseEvent &event);
	virtual void onKeyDown(wxKeyEvent &event);
	virtual void onKeyUp(wxKeyEvent &event);
	virtual wxhdMultiPosRect getVisibleArea();
	virtual wxhdMultiPosRect getVirtualSize();
	virtual bool AcceptsFocus () const;
	wxhdDrawingEditor *editor();
	wxSize canvasSize;
	
	//Hack To allow right click menu at canvas without a figure
	virtual void createViewMenu(wxMenu &mnu);
	virtual void OnGenericViewPopupClick(wxCommandEvent &event);
	//Hack to allow a different tool for each view
	wxhdITool *tool();
	void setTool(wxhdITool *tool);
	//Hack to avoid selection rectangle drawing bug
	void setSelRect(wxhdRect &selectionRect);
	void disableSelRectDraw();
	//Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event
	void simpleTextToolChangeHandler(wxCommandEvent &event);
	void setSimpleTextToolFigure(wxhdSimpleTextFigure *figure, bool onlySetFigure = false);
	wxTextCtrl *getSimpleTextToolEdit();
	wxBitmapButton *getOkTxt();
	wxBitmapButton *getCancelTxt();
	//Hack to allow use (events) of wxmenu inside a tool Generic Way
	void setMenuToolFigure(wxhdAbstractMenuFigure *figure);
	//Hack to allow use (events) of wxmenu inside a tool like simpletexttool
	void OnGenericPopupClick(wxCommandEvent &event);
	void OnOkTxtButton(wxCommandEvent &event);
	void OnCancelTxtButton(wxCommandEvent &event);
	void connectPopUpMenu(wxMenu &mnu);
	//Hack to allow use (events) of wxmenu inside a tool without a figure, Generic Way
	void setCanvasMenuTool(wxhdCanvasMenuTool *menuTool);
	//Hack to allow use of a figure into multiple diagrams.
	int getIdx() {return diagramIndex;}
	void syncIdx(int newDiagramIndex) {diagramIndex = newDiagramIndex; };
protected:
	int diagramIndex;
private:
	DECLARE_EVENT_TABLE()
	wxhdDrawing *drawing;
	wxhdDrawingEditor *drawingEditor;
	
	//Hack to allow a different tool for each view
	wxhdITool *_tool;

	//Hack to allow auto scrolling when dragging mouse.
	wxhdPoint startDrag;

	//Hack to avoid selection rectangle drawing bug
	wxhdRect selRect;
	wxPoint selPoints[5];
	bool drawSelRect;
	//End Hack to avoid selection rectangle drawing bug

	//Hack to allow use (events) of wxmenu inside a tool with a figure, Generic Way
	wxhdAbstractMenuFigure *menuFigure;
	//End hack to allow use (events) of wxmenu inside a tool with a figure, Generic Way

	//Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event && POPUP EVENT
	wxTextCtrl *simpleTextToolEdit;
	wxBitmapButton *okTxtButton, *cancelTxtButton;
	wxhdSimpleTextFigure *simpleTextFigure;
	wxString oldText;
	//End Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event && POPUP EVENT

	//Hack to allow use (events) of wxmenu inside a tool without a figure, Generic Way
	wxhdCanvasMenuTool *canvasMenu;
	//Hack to allow use (events) of wxmenu inside a tool without a figure, Generic Way
};
#endif
