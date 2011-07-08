//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdAttributeFigure.cpp - Base class for all figure attributes
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"


#include <libxml/xmlwriter.h>

// App headers
#include "dd/dditems/figures/xml/ddXmlStorage.h"
#include "dd/dditems/utilities/ddDataType.h"

#include "dd/dditems/figures/ddColumnKindIcon.h"
#include "dd/dditems/figures/ddColumnOptionIcon.h"
#include "dd/ddmodel/ddDatabaseDesign.h"

ddDatabaseDesign* ddXmlStorage::design = NULL;

ddXmlStorage::ddXmlStorage():
	wxhdStorage()
{
	design = NULL;
}

#define XML_FROM_WXSTRING(s) ((xmlChar *)(const char *)s.mb_str(wxConvUTF8))
#define WXSTRING_FROM_XML(s) wxString((char *)s, wxConvUTF8)

void ddXmlStorage::setModel(ddDatabaseDesign *sourceDesign)
{
	design = sourceDesign;
}

void ddXmlStorage::StartModel(xmlTextWriterPtr writer, ddDatabaseDesign *sourceDesign)
{
	int tmp;
	design = sourceDesign;
	//<!DOCTYPE MODEL ...pgRelationModel.dtd> but add all dtd to doc instead url
	wxString name = _("MODEL");
	wxString pubid = _("pgrm");
	wxString uri = _("pgrm");

	xmlTextWriterWriteDTD(writer,XML_FROM_WXSTRING(name),NULL,NULL,XML_FROM_WXSTRING(getModelDTD()));
	//<!ELEMENT MODEL (TABLE+)>
	tmp = xmlTextWriterStartElement(writer, BAD_CAST "MODEL");
	processResult(tmp);

}

void ddXmlStorage::EndModel( xmlTextWriterPtr writer)
{
	//Close MODEL Element
	xmlTextWriterEndElement(writer);
	design = NULL;
}

void ddXmlStorage::Write(xmlTextWriterPtr writer, wxhdIFigure *figure)
{
	if(design==NULL)
	{
		wxMessageBox(_("Error saving model: not source model have been set"));
		return;
	}

	switch(figure->getKindId())
	{
		case DDCOLUMNOPTIONICON:
			WriteLocal(writer,(ddColumnOptionIcon *)figure);
			break;
		case DDCOLUMNKINDICON:
			WriteLocal(writer,(ddColumnKindIcon *)figure);
			break;
		case DDTEXTTABLEITEMFIGURE:
			WriteLocal(writer,(ddTextTableItemFigure *)figure);
			break;
		case DDCOLUMNFIGURE:
			WriteLocal(writer,(ddColumnFigure *)figure);
			break;
		case DDTABLEFIGURE:
			WriteLocal(writer,(ddTableFigure *)figure);
			break;
	}
}

void ddXmlStorage::processResult(int value)
{
    if (value < 0) {
        wxMessageBox(_("Fatal Error at libxml for figure persistency"));
    }
}

void ddXmlStorage::WriteLocal(xmlTextWriterPtr writer, ddColumnOptionIcon *figure)
{
    int tmp;

	//At COLUMN Element
	//<!ELEMENT OPTION (#PCDATA)>
    tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "OPTION","%d", figure->getOption() );
	processResult(tmp);
}

void ddXmlStorage::WriteLocal(xmlTextWriterPtr writer, ddColumnKindIcon *figure)
{
    int tmp;

	//At COLUMN Element
	//<!ELEMENT UKINDEX (#PCDATA)>
    tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "UKINDEX","%d", figure->getUniqueConstraintIndex());
	processResult(tmp);

	//<!ELEMENT ISPK (#PCDATA)>
    tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "ISPK","%c", figure->isPrimaryKey() ? 'T' : 'F' );
	processResult(tmp);
}

void ddXmlStorage::WriteLocal( xmlTextWriterPtr writer, ddTextTableItemFigure *figure)
{
	int tmp;

	//<!ELEMENT COLUMNTYPE (#PCDATA)> 
	wxString ddType = figure->dataTypes()[figure->getDataType()];
    tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "COLUMNTYPE","%s",XML_FROM_WXSTRING(ddType));
	processResult(tmp);	

	if(figure->getPrecision() != -1)
	{
		//<!ELEMENT PRECISION (#PCDATA)>
		tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "PRECISION","%d", figure->getPrecision());
		processResult(tmp);	
	}

	if(figure->getScale() != -1)
	{
		//<!ELEMENT SCALE (#PCDATA)>
		tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "SCALE","%d", figure->getScale());
		processResult(tmp);	
	}

}

void ddXmlStorage::WriteLocal( xmlTextWriterPtr writer, ddColumnFigure *figure)
{
	int tmp;
	
	//At TABLE Element
	//<!ELEMENT COLUMN (Attribute+,OPTION,UKINDEX,ISPK,SHOWDATATYPE,SHOWALIAS,COLUMNTYPE,PRECISION?,SCALE?,GENERATEFKNAME)>	
	tmp = xmlTextWriterStartElement(writer, BAD_CAST "COLUMN");
	
	//<!ELEMENT NAME (#PCDATA)>
	tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "NAME","%s", figure->getColumnName(false).mb_str(wxConvUTF8));
	processResult(tmp);	

	//At Column Element
	Write(writer, figure->getOptionImage());
	Write(writer, figure->getKindImage());
	Write(writer, figure->getColumnText());
	
	//At Column Element
	//<!ELEMENT GENERATEFKNAME (#PCDATA)>
	tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "GENERATEFKNAME","%c",figure->isFkNameGenerated() ?  'T' : 'F' );
	processResult(tmp);	

	//Close COLUMN Element
	xmlTextWriterEndElement(writer);
	processResult(tmp);	
}

void ddXmlStorage::WriteLocal( xmlTextWriterPtr writer, ddTableFigure *figure)
{
	int tmp;
	
	//At TABLES ELEMENT
	//<!ELEMENT TABLE (Attribute+,COLUMNS,UKNAMES?, PKNAME, BEGINDRAWCOLS, BEGINDRAWIDXS, MAXCOLINDEX, MINIDXINDEX, MAXIDXINDEX, COLSROWSSIZE, COLSWINDOW,  IDXSROWSSIZE, IDXSWINDOW )>
	tmp = xmlTextWriterStartElement(writer, BAD_CAST "TABLE");
	processResult(tmp);	
	
	//<!ATTLIST TABLE	TableID ID #REQUIRED > --> ddTableFigure ID
	wxString TableId = design->getTableId(figure->getTableName());
	tmp = xmlTextWriterWriteAttribute(writer, BAD_CAST "TableID", XML_FROM_WXSTRING(TableId) );
	processResult(tmp);

		//Add Columns
		ddColumnFigure *f;
		wxhdIteratorBase *iterator = figure->figuresEnumerator();
		iterator->Next(); //First figure is main rect

		//<!ELEMENT TITLE (NAME,ALIAS)>
		tmp = xmlTextWriterStartElement(writer, BAD_CAST "TITLE");
		processResult(tmp);	
		f = (ddColumnFigure *) iterator->Next();

		//<!ELEMENT NAME (#PCDATA)>
		tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "NAME","%s",XML_FROM_WXSTRING(figure->getTableName()));
		processResult(tmp);	

		//<!ELEMENT ALIAS (#PCDATA)>
		if(figure->getShortTableName().Length()>0)
		{
			//<!ELEMENT ALIAS (#PCDATA)>
			tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "ALIAS","%s", XML_FROM_WXSTRING(figure->getShortTableName()));
			processResult(tmp);	
		}

		//Close TITLE Element
		xmlTextWriterEndElement(writer);

		if(figure->getUkConstraintsNames().Count()>0)
		{
			//<!ELEMENT UKNAMES (UKNAME+)>
			tmp = xmlTextWriterStartElement(writer, BAD_CAST "UKNAMES");
			processResult(tmp);	

			//<!ELEMENT UKNAME (#PCDATA)>  one for each name
			int i, last = figure->getUkConstraintsNames().Count();
			for(i = 0; i < last; i++)
			{
				tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "UKNAME","%s", figure->getUkConstraintsNames()[i].mb_str(wxConvUTF8));
				processResult(tmp);	
			}
			
			//Close UKNAMES Element
			xmlTextWriterEndElement(writer);
		}

		//<!ELEMENT PKNAME (#PCDATA)>
		tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "PKNAME","%s",XML_FROM_WXSTRING(figure->getPkConstraintName()));
		processResult(tmp);
			
	//<!ELEMENT BEGINDRAWCOLS (#PCDATA)>
	tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "BEGINDRAWCOLS","%d",figure->getBeginDrawCols());
	processResult(tmp);

	//<!ELEMENT BEGINDRAWIDXS (#PCDATA)>
	tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "BEGINDRAWIDXS","%d",figure->getBeginDrawIdxs());
	processResult(tmp);

	//<!ELEMENT MAXCOLINDEX (#PCDATA)>
	tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "MAXCOLINDEX","%d",figure->getMaxColIndex());
	processResult(tmp);

	//<!ELEMENT MINIDXINDEX (#PCDATA)>
	tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "MINIDXINDEX","%d",figure->getMinIdxIndex());
	processResult(tmp);

	//<!ELEMENT MAXIDXINDEX (#PCDATA)>
	tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "MAXIDXINDEX","%d",figure->getMaxIdxIndex());
	processResult(tmp);

	//<!ELEMENT COLSROWSSIZE (#PCDATA)>
	tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "COLSROWSSIZE","%d",figure->getColsRowsSize());
	processResult(tmp);

	//<!ELEMENT COLSWINDOW (#PCDATA)>
	tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "COLSWINDOW","%d",figure->getColsWindow());
	processResult(tmp);

	//<!ELEMENT IDXSROWSSIZE (#PCDATA)>
	tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "IDXSROWSSIZE","%d",figure->getIdxsRowsSize());
	processResult(tmp);

	//<!ELEMENT IDXSWINDOW (#PCDATA)>
	tmp = xmlTextWriterWriteFormatElement(writer, BAD_CAST "IDXSWINDOW","%d",figure->getIdxsWindow());
	processResult(tmp);

	//<!ELEMENT COLUMNS (COLUMN*)>
	tmp = xmlTextWriterStartElement(writer, BAD_CAST "COLUMNS");
	processResult(tmp);	

	//ALL COLUMN ELEMENT
	while(iterator->HasNext())
	{
		f = (ddColumnFigure *) iterator->Next();
		Write(writer,f);
	}
	delete iterator;
	
	//Close COLUMNS Element
	xmlTextWriterEndElement(writer);

	//Close TABLE Element
	xmlTextWriterEndElement(writer);

}


//This is needed because table doesn't have any explicit order when stored then I created all first
void ddXmlStorage::initialModelParse(xmlTextReaderPtr reader)
{
	int ret,tmp;
	xmlChar *value;	

	if(reader!=NULL)
	{
		wxString tableName=wxEmptyString, tableAlias=wxEmptyString, TableID;
		xmlTextReaderSetParserProp( reader, XML_PARSER_VALIDATE, 1 );     
		ret = xmlTextReaderRead(reader);
        while (ret == 1)
		{
			if(getNodeType(reader)==1 && getNodeName(reader).IsSameAs(_("TABLE"),false)) //libxml 1 for start element
			{
				//Look for table ID
				tmp = xmlTextReaderHasAttributes(reader);
				TableID=_("TableID");
				if(tmp)
				{
					value = xmlTextReaderGetAttribute(reader,XML_FROM_WXSTRING(TableID));
				}
				
				if(value)
				{
						TableID = WXSTRING_FROM_XML(value);
						xmlFree(value);
				}

				//Look for table Name
				if(value!=NULL)
					xmlFree(value);
				
				tmp = xmlTextReaderRead(reader);	//go to TITLE
				tmp = xmlTextReaderRead(reader);	//go to NAME
				tmp = xmlTextReaderRead(reader);	//go to NAME Value
				value = xmlTextReaderValue(reader);  //Value of NAME
				if(value)
				{
					tableName = WXSTRING_FROM_XML(value);
					design->addTableToMapping(TableID,tableName); 
					xmlFree(value);
				}
				tmp = xmlTextReaderRead(reader);	//go to /NAME

				tmp = xmlTextReaderRead(reader);	//go to ALIAS or /TITLE
				if(getNodeName(reader).IsSameAs(_("ALIAS"),false))
				{
					tmp = xmlTextReaderRead(reader);	//go to ALIAS Value	
					value = xmlTextReaderValue(reader);  //Value of ALIAS
					if(value)
					{
						tableAlias = WXSTRING_FROM_XML(value);
						xmlFree(value);
					}
					tmp = xmlTextReaderRead(reader);	//go to /ALIAS
					tmp = xmlTextReaderRead(reader);	//go to /TITLE
				}
				ddTableFigure *t = new ddTableFigure(tableName, 300, 300, tableAlias);
				design->addTable(t);
			}
		 ret = xmlTextReaderRead(reader);			
		}

		//Once the document has been fully parsed check the validation results
		if (xmlTextReaderIsValid(reader) != 1)
		{
			wxMessageBox(_("Model is not following embedded DTD definition, check it.\n"));
			return;
		}
	}
	//reset reader to begining of stream
}



wxString ddXmlStorage::Read(xmlTextReaderPtr reader)
{
	int ret;
	wxString salida = wxEmptyString;




	if(reader!=NULL)
	{
		xmlTextReaderSetParserProp( reader, XML_PARSER_VALIDATE, 1 );     
		ret = xmlTextReaderRead(reader);
        while (ret == 1) 
		{
            //salida += processNode(reader);
			selectReader(reader);
            ret = xmlTextReaderRead(reader);
        }

		//Once the document has been fully parsed check the validation results
		if (xmlTextReaderIsValid(reader) != 1)
		{
			wxMessageBox(_("Model is not following embedded DTD definition, check it.\n"));
			return wxEmptyString;
		}

		if (ret != 0) {
            wxMessageBox(_("Failed to load document from memory"));
		}
		else
		{
			return salida;
		}
	}
	return wxEmptyString;
}

wxString ddXmlStorage::getNodeName(xmlTextReaderPtr reader)
{
	xmlChar *name;
	wxString out = wxEmptyString;
	name = xmlTextReaderName(reader);
    if (name == NULL)
        name = xmlStrdup(BAD_CAST "--");
	out = WXSTRING_FROM_XML(name);
	xmlFree(name);
	return out;
}
int ddXmlStorage::getNodeType(xmlTextReaderPtr reader)
{
	return xmlTextReaderNodeType(reader);
}

wxString ddXmlStorage::getNodeValue(xmlTextReaderPtr reader)
{
	wxString out = wxEmptyString;
	xmlChar *value;	
	value = xmlTextReaderValue(reader);
	if (value != NULL)
	{
		out=WXSTRING_FROM_XML(value);
		xmlFree(value);
	}
	return out;
}


void ddXmlStorage::selectReader(xmlTextReaderPtr reader)
{
	if(getNodeType(reader)==1) //libxml 1 for start element
	{
		if(getNodeName(reader).IsSameAs(_("MODEL"),false))
		{
			//<!ELEMENT MODEL (TABLE+)>
		}

		if(getNodeName(reader).IsSameAs(_("TABLE"),false))
		{
			design->addTable(getTABLE(reader));
			design->refreshDraw();		
		}
	}
}

//Table isn't create here because fk needs all tables created before assign it
ddTableFigure* ddXmlStorage::getTABLE(xmlTextReaderPtr reader)
{
/*
<!ELEMENT TABLE (Attribute*,TITLE,UKNAMES?, PKNAME, COLUMNS, BEGINDRAWCOLS, BEGINDRAWIDXS, MAXCOLINDEX, MINIDXINDEX, MAXIDXINDEX, COLSROWSSIZE, COLSWINDOW,  IDXSROWSSIZE, IDXSWINDOW )>
<!ELEMENT COLUMNS (COLUMN*)>
<!ELEMENT UKNAMES (UKNAME+)>
<!ELEMENT UKNAME (#PCDATA)>
<!ELEMENT PKNAME (#PCDATA)>
<!ELEMENT BEGINDRAWCOLS (#PCDATA)>
<!ELEMENT BEGINDRAWIDXS (#PCDATA)>
<!ELEMENT MAXCOLINDEX (#PCDATA)>
<!ELEMENT MINIDXINDEX (#PCDATA)>
<!ELEMENT MAXIDXINDEX (#PCDATA)>
<!ELEMENT COLSROWSSIZE (#PCDATA)>
<!ELEMENT COLSWINDOW (#PCDATA)>
<!ELEMENT IDXSROWSSIZE (#PCDATA)>
<!ELEMENT IDXSWINDOW (#PCDATA)>

<!ATTLIST TABLE	TableID ID #REQUIRED >
*/

int tmp;
wxString TableID,node;
xmlChar *value;

	//<!ATTLIST TABLE	TableID ID #REQUIRED >
	tmp = xmlTextReaderHasAttributes(reader);
	TableID=_("TableID");
	if(tmp)
	{
		value = xmlTextReaderGetAttribute(reader,XML_FROM_WXSTRING(TableID));
	}
	
	if(value)
	{
			TableID = WXSTRING_FROM_XML(value);
			xmlFree(value);
	}

	if(value!=NULL)
		xmlFree(value);


	// --> ATTRIBUTE*
	//Element(s) Attribute*
	// NEED TO IMPLEMENT THIS

	// --> TITLE
	//<!ELEMENT TITLE (NAME,ALIAS?)>
	//<!ELEMENT NAME (#PCDATA)>
	//<!ELEMENT ALIAS (#PCDATA)>
	wxString tableName = wxEmptyString;
	wxString tableAlias = wxEmptyString;

	tmp = xmlTextReaderRead(reader);	//go to TITLE
	tmp = xmlTextReaderRead(reader);	//go to NAME
	tmp = xmlTextReaderRead(reader);	//go to NAME Value
	value = xmlTextReaderValue(reader);  //Value of NAME
	if(value)
	{
		tableName = WXSTRING_FROM_XML(value);
		xmlFree(value);
	}
	tmp = xmlTextReaderRead(reader);	//go to /NAME
	tmp = xmlTextReaderRead(reader);	//go to ALIAS or /TITLE
	if(getNodeName(reader).IsSameAs(_("ALIAS"),false))
	{
		tmp = xmlTextReaderRead(reader);	//go to ALIAS Value	
		value = xmlTextReaderValue(reader);  //Value of ALIAS
		if(value)
		{
			tableAlias = WXSTRING_FROM_XML(value);
			xmlFree(value);
		}
		tmp = xmlTextReaderRead(reader);	//go to /ALIAS
		tmp = xmlTextReaderRead(reader);	//go to /TITLE
	}
	
	// --> UKNAMES?
	//<!ELEMENT UKNAMES (UKNAME+)>
	//<!ELEMENT UKNAME (#PCDATA)>
	tmp = xmlTextReaderRead(reader);	//go to UKNAMES or PKNAMES?
	wxArrayString ukNames;
	if(getNodeName(reader).IsSameAs(_("UKNAMES"),false))
	{
		do{
			tmp = xmlTextReaderRead(reader);	//go UKNAME
			tmp = xmlTextReaderRead(reader);	//go UKNAME Value
			value = xmlTextReaderValue(reader);  //Value of UKNAME
			if(value)
			{
				ukNames.Add(WXSTRING_FROM_XML(value));
				xmlFree(value);
			}
			tmp = xmlTextReaderRead(reader);	//go to /UKNAME
			tmp = xmlTextReaderRead(reader);	//go to UKNAME or /UKNAMES ?
		}while(getNodeName(reader).IsSameAs(_("UKNAME"),false));
		tmp = xmlTextReaderRead(reader);	//go to PKNAME
	}

	// --> PKNAME
	//<!ELEMENT PKNAME (#PCDATA)>
	wxString pkName;
	if(getNodeName(reader).IsSameAs(_("PKNAME")))
	{
		tmp = xmlTextReaderRead(reader);	//go to PKNAME Value
		value = xmlTextReaderValue(reader);  //Value of PKNAME
			if(value)
			{
				pkName = WXSTRING_FROM_XML(value);
				xmlFree(value);
			}
		tmp = xmlTextReaderRead(reader);	//go to /PKNAME
	}
	
	int beginDrawCols, beginDrawIdxs, maxColIndex, minIdxIndex, maxIdxIndex, colsRowsSize, colsWindow, idxsRowsSize, idxsWindow;
	wxString tmpInt;
	// --> BEGINDRAWCOLS
	//<!ELEMENT BEGINDRAWCOLS (#PCDATA)>
	tmp = xmlTextReaderRead(reader);	//go to BEGINDRAWCOLS
	tmp = xmlTextReaderRead(reader);	//go to BEGINDRAWCOLS Value	
	value = xmlTextReaderValue(reader);  //Value
	if(value)
	{
		tmpInt = WXSTRING_FROM_XML(value);
		beginDrawCols = wxAtoi(tmpInt);
		xmlFree(value);
	}
	tmp = xmlTextReaderRead(reader);	//go to /BEGINDRAWCOLS	
	tmp = xmlTextReaderRead(reader);	//go to BEGINDRAWIDXS	

	// --> BEGINDRAWIDXS
	//<!ELEMENT BEGINDRAWIDXS (#PCDATA)>
	tmp = xmlTextReaderRead(reader);	//go to BEGINDRAWIDXS Value	
	value = xmlTextReaderValue(reader);  //Value
	if(value)
	{
		tmpInt = WXSTRING_FROM_XML(value);
		beginDrawIdxs = wxAtoi(tmpInt);
		xmlFree(value);
	}
	tmp = xmlTextReaderRead(reader);	//go to /BEGINDRAWIDXS	
	tmp = xmlTextReaderRead(reader);	//go to MAXCOLINDEX

	// --> MAXCOLINDEX
	//<!ELEMENT MAXCOLINDEX (#PCDATA)>
	tmp = xmlTextReaderRead(reader);	//go to MAXCOLINDEX Value	
	value = xmlTextReaderValue(reader);  //Value
	if(value)
	{
		tmpInt = WXSTRING_FROM_XML(value);
		maxColIndex = wxAtoi(tmpInt);
		xmlFree(value);
	}
	tmp = xmlTextReaderRead(reader);	//go to /MAXCOLINDEX	
	tmp = xmlTextReaderRead(reader);	//go to MINIDXINDEX
	
	// --> MINIDXINDEX
	//<!ELEMENT MINIDXINDEX (#PCDATA)>
	tmp = xmlTextReaderRead(reader);	//go to MINIDXINDEX Value	
	value = xmlTextReaderValue(reader);  //Value
	if(value)
	{
		tmpInt = WXSTRING_FROM_XML(value);
		minIdxIndex = wxAtoi(tmpInt);
		xmlFree(value);
	}
	tmp = xmlTextReaderRead(reader);	//go to /MINIDXINDEX	
	tmp = xmlTextReaderRead(reader);	//go to MAXIDXINDEX
	
	// --> MAXIDXINDEX
	//<!ELEMENT MAXIDXINDEX (#PCDATA)>
	tmp = xmlTextReaderRead(reader);	//go to MAXIDXINDEX Value	
	value = xmlTextReaderValue(reader);  //Value
	if(value)
	{
		tmpInt = WXSTRING_FROM_XML(value);
		maxIdxIndex = wxAtoi(tmpInt);
		xmlFree(value);
	}
	tmp = xmlTextReaderRead(reader);	//go to /MAXIDXINDEX	
	tmp = xmlTextReaderRead(reader);	//go to COLSROWSSIZE
	
	// --> COLSROWSSIZE
	//<!ELEMENT COLSROWSSIZE (#PCDATA)>
	tmp = xmlTextReaderRead(reader);	//go to COLSROWSSIZE Value	
	value = xmlTextReaderValue(reader);  //Value
	if(value)
	{
		tmpInt = WXSTRING_FROM_XML(value);
		colsRowsSize = wxAtoi(tmpInt);
		xmlFree(value);
	}
	tmp = xmlTextReaderRead(reader);	//go to /COLSROWSSIZE	
	tmp = xmlTextReaderRead(reader);	//go to COLSWINDOW
	
	// --> COLSWINDOW
	//<!ELEMENT COLSWINDOW (#PCDATA)>
	tmp = xmlTextReaderRead(reader);	//go to COLSWINDOW Value	
	value = xmlTextReaderValue(reader);  //Value
	if(value)
	{
		tmpInt = WXSTRING_FROM_XML(value);
		colsWindow = wxAtoi(tmpInt);
		xmlFree(value);
	}
	tmp = xmlTextReaderRead(reader);	//go to /COLSWINDOW	
	tmp = xmlTextReaderRead(reader);	//go to IDXSROWSSIZE
	
	// --> IDXSROWSSIZE
	//<!ELEMENT IDXSROWSSIZE (#PCDATA)>
	tmp = xmlTextReaderRead(reader);	//go to IDXSROWSSIZE Value	
	value = xmlTextReaderValue(reader);  //Value
	if(value)
	{
		tmpInt = WXSTRING_FROM_XML(value);
		idxsRowsSize = wxAtoi(tmpInt);
		xmlFree(value);
	}
	tmp = xmlTextReaderRead(reader);	//go to /IDXSROWSSIZE	
	tmp = xmlTextReaderRead(reader);	//go to IDXSWINDOW
	
	// --> IDXSWINDOW
	//<!ELEMENT IDXSWINDOW (#PCDATA)>*/
	tmp = xmlTextReaderRead(reader);	//go to IDXSWINDOW Value	
	value = xmlTextReaderValue(reader);  //Value
	if(value)
	{
		tmpInt = WXSTRING_FROM_XML(value);
		idxsWindow = wxAtoi(tmpInt);
		xmlFree(value);
	}
	tmp = xmlTextReaderRead(reader);	//go to /IDXSWINDOW	
	// --> COLUMNS
	//<!ELEMENT COLUMNS (COLUMN*)>

	tmp = xmlTextReaderRead(reader);	//go to COLUMNS
	
	//Use empty table without columns created at preparsing to fill it with metadata
	
	ddTableFigure *t = design->getTable(tableName);
	t->InitTableValues(ukNames, pkName, beginDrawCols, beginDrawIdxs, maxColIndex, minIdxIndex, maxIdxIndex, colsRowsSize, colsWindow, idxsRowsSize, idxsWindow);

		//CHANGE 300,300 for right value when displaybox metadata will be added


	//COLUMNS node have COLUMN children?
	if(getNodeName(reader).IsSameAs(_("COLUMNS"))&& getNodeType(reader) == 1 && !xmlTextReaderIsEmptyElement(reader) )	
	{
		ddColumnFigure *c;
		do{
			c = getColumn(reader, t); 
			if(c)
			{
				t->addColumnFromStorage(c);
			}
		}while(c!=NULL);
		//now at </COLUMNS>
	} 

	tmp = xmlTextReaderRead(reader);	//go to </TABLE>
	t->syncPositionsAfterLoad();  //synchronize positions
	return t;
}

ddColumnFigure* ddXmlStorage::getColumn(xmlTextReaderPtr reader, ddTableFigure *colOwner)
{
/*
<!ELEMENT COLUMN (Attribute*,NAME,OPTION,UKINDEX,ISPK,COLUMNTYPE,PRECISION?,SCALE?,GENERATEFKNAME)>
<!ELEMENT NAME (#PCDATA)>
<!ELEMENT OPTION (#PCDATA)>
<!ELEMENT UKINDEX (#PCDATA)>
<!ELEMENT ISPK (#PCDATA)>
<!ELEMENT COLUMNTYPE (#PCDATA)>
<!ELEMENT PRECISION (#PCDATA)>
<!ELEMENT SCALE (#PCDATA)>
<!ELEMENT GENERATEFKNAME (#PCDATA)>
*/

	xmlChar *value;	
	int tmp;
	tmp = xmlTextReaderRead(reader);	//go to COLUMN
	if(getNodeName(reader).IsSameAs(_("COLUMN"))&& getNodeType(reader) == 1 && !xmlTextReaderIsEmptyElement(reader) )
	{
		// --> ATTRIBUTE*
		//Element(s) Attribute*
		// NEED TO IMPLEMENT THIS

		// --> NAME
		//<!ELEMENT NAME (#PCDATA)>
		wxString columnName;
		tmp = xmlTextReaderRead(reader);	//go to NAME
		tmp = xmlTextReaderRead(reader);	//go to NAME Value
		value = xmlTextReaderValue(reader);  //Value of NAME
			if(value)
			{
				columnName = WXSTRING_FROM_XML(value);
				xmlFree(value);
			}
		tmp = xmlTextReaderRead(reader);	//go to /NAME
		tmp = xmlTextReaderRead(reader);	//go to OPTION

		// --> OPTION
		//<!ELEMENT OPTION (#PCDATA)>
		int option;
		wxString tmpInt;
		tmp = xmlTextReaderRead(reader);	//go to OPTION Value	
		value = xmlTextReaderValue(reader);  //Value
		if(value)
		{
			tmpInt = WXSTRING_FROM_XML(value);
			option = wxAtoi(tmpInt);
			xmlFree(value);
		}
		tmp = xmlTextReaderRead(reader);	//go to /OPTION	
		tmp = xmlTextReaderRead(reader);	//go to UKINDEX

		// --> UKINDEX
		//<!ELEMENT UKINDEX (#PCDATA)>
		int ukindex;
		tmp = xmlTextReaderRead(reader);	//go to UKINDEX Value	
		value = xmlTextReaderValue(reader);  //Value
		if(value)
		{
			tmpInt = WXSTRING_FROM_XML(value);
			ukindex = wxAtoi(tmpInt);
			xmlFree(value);
		}
		tmp = xmlTextReaderRead(reader);	//go to /UKINDEX	
		tmp = xmlTextReaderRead(reader);	//go to ISPK

		// --> ISPK
		//<!ELEMENT ISPK (#PCDATA)>
		bool isPk=false;
		tmp = xmlTextReaderRead(reader);	//go to ISPK Value
		value = xmlTextReaderValue(reader);  //Value of ISPK
			if(value)
			{
				tmpInt = WXSTRING_FROM_XML(value);
				isPk = tmpInt.IsSameAs(_("T"));
				xmlFree(value);
			}
		tmp = xmlTextReaderRead(reader);	//go to /ISPK

		// --> COLUMNTYPE
		//<!ELEMENT COLUMNTYPE (#PCDATA)>
		wxString columnType;
		tmp = xmlTextReaderRead(reader);	//go to COLUMNTYPE
		tmp = xmlTextReaderRead(reader);	//go to COLUMNTYPE Value
		value = xmlTextReaderValue(reader);  //Value of COLUMNTYPE
			if(value)
			{
				columnType = WXSTRING_FROM_XML(value);
				xmlFree(value);
			}
		tmp = xmlTextReaderRead(reader);	//go to /COLUMNTYPE

		// --> PRECISION?
		//<!ELEMENT PRECISION (#PCDATA)>
		tmp = xmlTextReaderRead(reader);	//go to PRECISION? or SCALE? or ALIAS? or GENERATEFKNAME
		int precision = -1;
		if(getNodeName(reader).IsSameAs(_("PRECISION")))
		{
			tmp = xmlTextReaderRead(reader);	//go to PRECISION Value
			value = xmlTextReaderValue(reader);  //Value of PRECISION
				if(value)
				{
					tmpInt = WXSTRING_FROM_XML(value);
					precision = wxAtoi(tmpInt);
					xmlFree(value);
				}
			tmp = xmlTextReaderRead(reader);	//go to /PRECISION
			tmp = xmlTextReaderRead(reader);	//go to SCALE? or ALIAS? or GENERATEFKNAME
		}

		// --> 	SCALE?
		//<!ELEMENT SCALE (#PCDATA)>

		int scale = -1;
		if(getNodeName(reader).IsSameAs(_("SCALE")))
		{
			tmp = xmlTextReaderRead(reader);	//go to SCALE Value
			value = xmlTextReaderValue(reader);  //Value of SCALE
				if(value)
				{
					tmpInt = WXSTRING_FROM_XML(value);
					scale = wxAtoi(tmpInt);
					xmlFree(value);
				}
			tmp = xmlTextReaderRead(reader);	//go to /SCALE
			tmp = xmlTextReaderRead(reader);	//go to ALIAS? or GENERATEFKNAME
		}

		// --> GENERATEFKNAME
		//<!ELEMENT GENERATEFKNAME (#PCDATA)>
		bool generateFkName=false;
		tmp = xmlTextReaderRead(reader);	//go to GENERATEFKNAME Value
		value = xmlTextReaderValue(reader);  //Value of GENERATEFKNAME
			if(value)
			{
				tmpInt = WXSTRING_FROM_XML(value);
				generateFkName = tmpInt.IsSameAs(_("T"));
				xmlFree(value);
			}
		tmp = xmlTextReaderRead(reader);	//go to /GENERATEFKNAME
		tmp = xmlTextReaderRead(reader);	//go to /COLUMN
		
		return new ddColumnFigure(columnName,colOwner,(ddColumnOptionType)option,generateFkName,isPk,columnType,precision,scale,ukindex,NULL,NULL);
	}
	return NULL;   //found /COLUMNS node
}

//Temporary DTD will change later
wxString ddXmlStorage::getModelDTD()
{
	wxString dtd = wxEmptyString;
dtd += _("<!ELEMENT MODEL (TABLE+)>");
dtd += _("<!--Atribute Element-->");
dtd += _("<!ELEMENT Attribute (#PCDATA)>");
dtd += _(" ");
dtd += _("<!ATTLIST Attribute");
dtd += _("	Name CDATA #REQUIRED");
dtd += _("	Kind (normal | selected) #REQUIRED");
dtd += _(">");
dtd += _("<!--Rectangle Element-->");
dtd += _("<!ELEMENT Rect (x,y,w,h)>");
dtd += _("<!ATTLIST Name");
dtd += _("	Name CDATA #REQUIRED");
dtd += _(">");
dtd += _("<!ELEMENT 	x (#PCDATA)>");
dtd += _("<!ELEMENT 	y (#PCDATA)>");
dtd += _("<!ELEMENT 	w (#PCDATA)>");
dtd += _("<!ELEMENT 	h (#PCDATA)>");
dtd += _(" ");
dtd += _("<!--Column Element-->");
dtd += _("<!ELEMENT COLUMN (Attribute*,NAME,OPTION,UKINDEX,ISPK,COLUMNTYPE,PRECISION?,SCALE?,GENERATEFKNAME)>");
dtd += _("<!ELEMENT NAME (#PCDATA)>");
dtd += _("<!ELEMENT OPTION (#PCDATA)>");
dtd += _("<!ELEMENT UKINDEX (#PCDATA)>");
dtd += _("<!ELEMENT ISPK (#PCDATA)>");
dtd += _("<!ELEMENT COLUMNTYPE (#PCDATA)>");
dtd += _("<!ELEMENT PRECISION (#PCDATA)>");
dtd += _("<!ELEMENT SCALE (#PCDATA)>");
dtd += _("<!ELEMENT GENERATEFKNAME (#PCDATA)>");
dtd += _(" ");
dtd += _(" ");
dtd += _("<!ELEMENT TITLE (NAME,ALIAS?)>");
dtd += _("<!ELEMENT ALIAS (#PCDATA)>");
dtd += _(" ");
dtd += _("<!-- Table Element -->");
dtd += _("<!ELEMENT TABLE (Attribute*,TITLE,UKNAMES?, PKNAME, BEGINDRAWCOLS, BEGINDRAWIDXS, MAXCOLINDEX, MINIDXINDEX, MAXIDXINDEX, COLSROWSSIZE,");
dtd += _("COLSWINDOW,IDXSROWSSIZE, IDXSWINDOW, COLUMNS )>");
dtd += _("<!ELEMENT COLUMNS (COLUMN*)>");
dtd += _("<!ELEMENT UKNAMES (UKNAME+)>");
dtd += _("<!ELEMENT UKNAME (#PCDATA)>");
dtd += _("<!ELEMENT PKNAME (#PCDATA)>");
dtd += _("<!ELEMENT BEGINDRAWCOLS (#PCDATA)>");
dtd += _("<!ELEMENT BEGINDRAWIDXS (#PCDATA)>");
dtd += _("<!ELEMENT MAXCOLINDEX (#PCDATA)>");
dtd += _("<!ELEMENT MINIDXINDEX (#PCDATA)>");
dtd += _("<!ELEMENT MAXIDXINDEX (#PCDATA)>");
dtd += _("<!ELEMENT COLSROWSSIZE (#PCDATA)>");
dtd += _("<!ELEMENT COLSWINDOW (#PCDATA)>");
dtd += _("<!ELEMENT IDXSROWSSIZE (#PCDATA)>");
dtd += _("<!ELEMENT IDXSWINDOW (#PCDATA)>");
dtd += _(" ");
dtd += _("<!ATTLIST TABLE");
dtd += _("	TableID ID #REQUIRED");
dtd += _("	>");
	return dtd;
}