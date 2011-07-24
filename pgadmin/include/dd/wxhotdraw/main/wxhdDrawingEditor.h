//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdDrawingEditor.h - Main class that manages all other classes
//
//////////////////////////////////////////////////////////////////////////

#ifndef WXHDDRAWINGEDITOR_H
#define WXHDDRAWINGEDITOR_H

#include "dd/wxhotdraw/main/wxhdDrawingView.h"
#include "dd/wxhotdraw/tools/wxhdITool.h"

class wxhdDrawingEditor : public wxhdObject
{
public:
	wxhdDrawingEditor(wxWindow *owner, bool defaultView = true );
	~wxhdDrawingEditor();
	wxhdDrawingView *getExistingView(int diagramIndex);
//	wxhdDrawingView *createDiagram();
	wxhdDrawing *getExistingDiagram(int diagramIndex);
	virtual wxhdDrawing* createDiagram(wxWindow *owner);
	virtual void addModelFigure(wxhdIFigure *figure);
	virtual void removeModelFigure(wxhdIFigure *figure);
	virtual bool modelIncludes(wxhdIFigure *figure);
	virtual void deleteSelectedFigures(int diagramIndex);
	int modelCount();


//666 000	wxhdITool *tool();
//666 000	void setTool(wxhdITool *tool);

/*
	//Hack To allow right click menu at canvas without a figure
	virtual void createMenu(wxMenu &mnu); 666 000
	virtual void OnGenericPopupClick(wxCommandEvent &event, wxhdDrawingView *view); 666 000
*/
protected:
	//int index;
	wxhdArrayCollection *_diagrams;
	wxhdArrayCollection *_model;
//666 000	wxhdITool *_tool;
private:
};
#endif
