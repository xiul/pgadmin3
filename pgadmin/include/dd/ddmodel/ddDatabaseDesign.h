//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbObject.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// gqbObject.h - 
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDDATABASEDESIGN_H
#define DDDATABASEDESIGN_H

#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/dditems/figures/ddTableFigure.h"


//WX_DECLARE_STRING_HASH_MAP( int, figureHiddenKindMap );

// Create Array Objects used as base for gqbCollections  DD-TODO fix this comment
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
