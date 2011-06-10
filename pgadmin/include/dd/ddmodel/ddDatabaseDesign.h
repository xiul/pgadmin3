//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDatabaseDesign.h - Manages all design related info and contains all model(s) and tables.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDDATABASEDESIGN_H
#define DDDATABASEDESIGN_H

#include "dd/wxhotdraw/main/ddDrawingEditor.h"
#include "dd/wxhotdraw/tools/ddITool.h"
#include "dd/dditems/figures/ddTableFigure.h"

class ddDatabaseDesign : public wxObject
{
public:
	ddDatabaseDesign(wxWindow *parent);
	~ddDatabaseDesign();
	ddDrawingView* getView();
	ddDrawingEditor* getEditor();
	void addTable(ddIFigure *figure);
	void removeTable(ddIFigure *figure);
    void removeSelectedObjects(int kind = 0);
	void setTool(ddITool* tool);
	void refreshDraw();
	void eraseModel();
	wxString generateModel();
	wxString getNewTableName();
    ddTableFigure* getSelectedTable();
	bool containsTable(wxString tableName);


protected:

private:
	ddDrawingEditor *draw;
	ddITool *tool;
};
#endif
