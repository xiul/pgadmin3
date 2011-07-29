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

#include <libxml/xmlwriter.h>

#include "dd/ddmodel/ddDrawingEditor.h"
#include "dd/ddmodel/ddModelBrowser.h"
#include "dd/wxhotdraw/tools/wxhdITool.h"
#include "dd/dditems/figures/ddTableFigure.h"

WX_DECLARE_STRING_HASH_MAP( wxString , tablesMappingHashMap );

class ddDatabaseDesign : public wxObject
{
public:
	ddDatabaseDesign(wxWindow *parent);
	~ddDatabaseDesign();
	wxhdDrawingView *getView(int diagramIndex);
	wxhdDrawingEditor *getEditor();
	void addTableToModel(wxhdIFigure *figure);
	void addTableToView(int diagramIndex, wxhdIFigure *figure);
	void removeTable(int diagramIndex, wxhdIFigure *figure);
	wxhdDrawing* createDiagram(wxWindow *owner);
//666 000	void setTool(wxhdITool *tool);
	void refreshDraw(int diagramIndex);
	void eraseDiagram(int diagramIndex);
	wxString generateDiagram(int diagramIndex);
	bool validateModel(wxString &errors, int diagramIndex);
	wxString getNewTableName();
	ddTableFigure *getSelectedTable(int diagramIndex);
	ddTableFigure *getTable(wxString tableName);
	bool writeXmlModel(wxString file);
	bool readXmlModel(wxString file);

	wxString getTableId(wxString tableName);
	void addTableToMapping(wxString IdKey, wxString tableName);
	wxString getTableName(wxString Id);
	void registerBrowser(ddModelBrowser *browser);

protected:
	tablesMappingHashMap mappingNameToId;
	tablesMappingHashMap mappingIdToName;
private:
	ddModelBrowser *attachedBrowser;
	int diagramCounter;
	ddDrawingEditor *editor;
	wxhdITool *tool;
	xmlTextWriterPtr xmlWriter;

};
#endif
