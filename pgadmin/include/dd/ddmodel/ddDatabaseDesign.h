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
#include <ctl/ctlAuiNotebook.h>

#include "dd/ddmodel/ddDrawingEditor.h"
#include "hotdraw/tools/hdITool.h"
#include "dd/dditems/figures/ddTableFigure.h"

class ddModelBrowser;

WX_DECLARE_STRING_HASH_MAP( wxString , tablesMappingHashMap );

class ddDatabaseDesign : public wxObject
{
public:
	ddDatabaseDesign(wxWindow *parent);
	~ddDatabaseDesign();
	hdDrawingView *getView(int diagramIndex);
	ddDrawingEditor *getEditor();
	void addTableToModel(hdIFigure *figure);
	void addTableToView(int diagramIndex, hdIFigure *figure);
	void removeTable(int diagramIndex, hdIFigure *figure);
	hdDrawing* createDiagram(wxWindow *owner, wxString name, bool fromXml);
	void deleteDiagram(int diagramIndex, bool deleteView=true);
	void refreshDraw(int diagramIndex);
	void eraseDiagram(int diagramIndex);
	void emptyModel();
	wxString generateDiagram(int diagramIndex);
	wxString generateModel();
	bool validateModel(wxString &errors);
	wxString getNewTableName();
	ddTableFigure *getSelectedTable(int diagramIndex);
	ddTableFigure *getTable(wxString tableName);
	bool writeXmlModel(wxString file);
	bool readXmlModel(wxString file, ctlAuiNotebook *notebook);

	wxString getTableId(wxString tableName);
	void addTableToMapping(wxString IdKey, wxString tableName);
	wxString getTableName(wxString Id);
	void registerBrowser(ddModelBrowser *browser);
	void refreshBrowser();
	static wxString getVersionXML();
protected:
	tablesMappingHashMap mappingNameToId;
	tablesMappingHashMap mappingIdToName;
private:
	ddModelBrowser *attachedBrowser;
	int diagramCounter;
	ddDrawingEditor *editor;
	hdITool *tool;
	xmlTextWriterPtr xmlWriter;

};
#endif
