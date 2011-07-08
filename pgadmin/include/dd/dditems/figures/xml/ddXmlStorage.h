//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdAbstractFigure.h - Base class for all figures with attributes (line size, fonts and others)
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDXMLSTORAGE_H
#define DDXMLSTORAGE_H

#include "dd/wxhotdraw/figures/xml/wxhdStorage.h"
#include "dd/ddmodel/ddDatabaseDesign.h"

class ddXmlStorage : public wxhdStorage
{
public:
	ddXmlStorage();
	
	//Generic part
	static wxString Read(xmlTextReaderPtr reader);
	static void Write(xmlTextWriterPtr writer, wxhdIFigure *figure);
	static void setModel(ddDatabaseDesign *sourceDesign);
	static wxString getModelDTD();

	//Write xml info Database Designer Related
	static void WriteLocal( xmlTextWriterPtr writer, ddColumnOptionIcon *figure);
	static void WriteLocal( xmlTextWriterPtr writer, ddColumnKindIcon *figure);
	static void WriteLocal( xmlTextWriterPtr writer, ddTextTableItemFigure *figure);
	static void WriteLocal( xmlTextWriterPtr writer, ddColumnFigure *figure);
	static void WriteLocal( xmlTextWriterPtr writer, ddTableFigure *figure);
	static void StartModel( xmlTextWriterPtr writer, ddDatabaseDesign *design);
	static void EndModel( xmlTextWriterPtr writer);
	static void processResult(int value);
	
	//Read xml info Database Designer Related
	static wxString getNodeName(xmlTextReaderPtr reader);
	static int getNodeType(xmlTextReaderPtr reader);
	static wxString getNodeValue(xmlTextReaderPtr reader);
	static void selectReader(xmlTextReaderPtr reader);
	static ddTableFigure* getTABLE(xmlTextReaderPtr reader);
	static ddColumnFigure* getColumn(xmlTextReaderPtr reader, ddTableFigure *colOwner);
	static void initialModelParse(xmlTextReaderPtr reader);
	

private:

	static ddDatabaseDesign *design;
};
#endif
