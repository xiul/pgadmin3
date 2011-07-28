//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDatabaseDesign.cpp - Manages all design related info and contains all model(s) and tables.
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// libxml2 headers
#include <libxml/xmlwriter.h>
#include <libxml/xmlreader.h>

// App headers
#include "dd/ddmodel/ddDatabaseDesign.h"
#include "dd/wxhotdraw/tools/wxhdSelectionTool.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/ddmodel/ddDrawingEditor.h"
#include "dd/dditems/figures/xml/ddXmlStorage.h"


ddDatabaseDesign::ddDatabaseDesign(wxWindow *parent)
{
	editor = new ddDrawingEditor(parent, this);
//666 000	tool = new wxhdSelectionTool(draw);
//666 000	draw->setTool(tool);
}

ddDatabaseDesign::~ddDatabaseDesign()
{
	if(editor)
		delete editor;
}

wxhdDrawingEditor *ddDatabaseDesign::getEditor()
{
	return editor;
}

wxhdDrawingView *ddDatabaseDesign::getView(int diagramIndex)
{
	return editor->getExistingView(diagramIndex);
}

/*//666 borrar esto cuando se borre la segunda vista...
wxhdDrawingView *ddDatabaseDesign::getView2()
{
	return draw->view2();
}
*/

void ddDatabaseDesign::addTableToView(int diagramIndex, wxhdIFigure *figure)
{
	editor->getExistingDiagram(diagramIndex)->add(figure);
}

/*
//666 borrar esto tambien
void ddDatabaseDesign::addTable2(wxhdIFigure *figure)
{
	draw->view2()->add(figure);
}
*/


void ddDatabaseDesign::removeTable(int diagramIndex, wxhdIFigure *figure)
{
	editor->getExistingDiagram(diagramIndex)->remove(figure);
}

/* 666 000
void ddDatabaseDesign::setTool(wxhdITool *tool)
{
	editor->setTool(tool);
}
*/

void ddDatabaseDesign::refreshDraw(int diagramIndex)
{
	editor->getExistingView(diagramIndex)->Refresh();
//	draw->view2()->Refresh(); //666 borrar
}

void ddDatabaseDesign::eraseDiagram(int diagramIndex)
{
	editor->getExistingDiagram(diagramIndex)->removeAllFigures();
}

bool ddDatabaseDesign::validateModel(wxString &errors, int diagramIndex)
{
	bool out = true;

	wxhdIteratorBase *iterator = editor->getExistingDiagram(diagramIndex)->figuresEnumerator();
	wxhdIFigure *tmpFigure;
	ddTableFigure *table;

	while(iterator->HasNext())
	{
		tmpFigure = (wxhdIFigure *)iterator->Next();
		if(tmpFigure->getKindId() == DDTABLEFIGURE)
		{
			table = (ddTableFigure *)tmpFigure;
			if(!table->validateTable(errors))
			{
				out = false;
			}
		}
	}
	delete iterator;

	return out;
}

wxString ddDatabaseDesign::generateDiagram(int diagramIndex)
{
	wxString out;
	wxhdIteratorBase *iterator = editor->getExistingDiagram(diagramIndex)->figuresEnumerator();
	wxhdIFigure *tmp;
	ddTableFigure *table;
	while(iterator->HasNext())
	{
		tmp = (wxhdIFigure *)iterator->Next();
		if(tmp->getKindId() == DDTABLEFIGURE)
		{
			out += wxT(" \n");
			table = (ddTableFigure *)tmp;
			out += wxT("--\n-- ");
			out += _("Generating SQL for table: ");
			out += table->getTableName();
			out += wxT(" \n--\n");
			out += table->generateSQL();
			out += wxT(" \n");
			out += wxT(" \n");
		}
	}
	delete iterator;
	return out;
}

wxString ddDatabaseDesign::getNewTableName()
{
	wxString out, tmpStr;
	//666 change this to look at all tables no just from one model fixed in 0 right now
	wxhdIteratorBase *iterator = editor->getExistingDiagram(0)->figuresEnumerator();
	wxhdIFigure *tmp;
	ddTableFigure *table;
	int indx = 0;
	bool repeat;
	do
	{
		repeat = false;
		iterator->ResetIterator();
		while(iterator->HasNext())
		{
			tmp = (wxhdIFigure *)iterator->Next();
			if(tmp->getKindId() == DDTABLEFIGURE)
			{
				table = (ddTableFigure *)tmp;
				if(indx == 0)
					tmpStr = _("NewTable");
				else
					tmpStr = wxString::Format(_("NewTable%d"), indx);

				if(table->getTableName().Contains(tmpStr))
				{
					indx++;
					repeat = true;
					break;
				}
			}
		}
	}
	while(repeat);
	delete iterator;
	out = wxString::Format(_("NewTable%d"), indx);
	return out;
}

ddTableFigure *ddDatabaseDesign::getSelectedTable(int diagramIndex)
{
	wxhdIteratorBase *iterator = editor->getExistingDiagram(diagramIndex)->figuresEnumerator();
	wxhdIFigure *tmp;
	ddTableFigure *table = NULL;
	while(iterator->HasNext())
	{
		tmp = (wxhdIFigure *)iterator->Next();
		if (tmp->isSelected(diagramIndex) && tmp->getKindId() == DDTABLEFIGURE)
			table = (ddTableFigure *)tmp;
	}
	delete iterator;
	return table;
}

ddTableFigure* ddDatabaseDesign::getTable(wxString tableName)
{
	ddTableFigure *out = NULL;
	//666 change this to look at all tables no just from one model fixed in 0 right now
	wxhdIteratorBase *iterator = editor->getExistingDiagram(0)->figuresEnumerator();
	wxhdIFigure *tmp;
	ddTableFigure *table;
	while(iterator->HasNext())
	{
		tmp = (wxhdIFigure *)iterator->Next();
		if(tmp->getKindId() == DDTABLEFIGURE)
		{
			table = (ddTableFigure *)tmp;
			if(table->getTableName().Contains(tableName))
			{
				out = table;
			}
		}
	}
	delete iterator;
	return out;
}

#define XML_FROM_WXSTRING(s) ((xmlChar *)(const char *)s.mb_str(wxConvUTF8))
#define WXSTRING_FROM_XML(s) wxString((char *)s, wxConvUTF8)

bool ddDatabaseDesign::writeXmlModel(wxString file)
{
		int rc;

		xmlWriter = xmlNewTextWriterFilename(file.mb_str(wxConvUTF8),0);
		if (xmlWriter == NULL) {
			wxMessageBox(_("XmlwriterMemory: Error creating the xml writer\n"));
			return false;
		}
		rc = xmlTextWriterStartDocument(xmlWriter, NULL, "UTF-8" , NULL);
		if(rc < 0)
		{
			wxMessageBox(_("Fatal Error at libxml when creating memory buffer figure persistency"));
			return false;
		}
		else
		{
			ddXmlStorage::StartModel(xmlWriter,this);
			//initialize IDs of tables
			mappingNameToId.clear();
			//666 change this to look at all tables no just from one model fixed in 0 right now
			wxhdIteratorBase *iterator = editor->getExistingDiagram(0)->figuresEnumerator();
			wxhdIFigure *tmp;
			ddTableFigure *table;
			int nextID=10;
			
			while(iterator->HasNext())
			{
				tmp = (wxhdIFigure *)iterator->Next();
				if(tmp->getKindId() == DDTABLEFIGURE)
				{
					table = (ddTableFigure *)tmp;
					mappingNameToId[table->getTableName()]=wxString::Format(wxT("TID%d"),nextID);
					nextID+=10;
				}
			}
			delete iterator;
			

			//Create table xml info
			//666 change this to look at all tables no just from one model fixed in 0 right now
			iterator = editor->getExistingDiagram(0)->figuresEnumerator();
			while(iterator->HasNext())
			{
				tmp = (wxhdIFigure *)iterator->Next();
				if(tmp->getKindId() == DDTABLEFIGURE)
				{
					table = (ddTableFigure *)tmp;
					ddXmlStorage::Write(xmlWriter,table);
				}
			}
			delete iterator;


			//Create relationships xml info
			ddRelationshipFigure *relationship;
			//666 change this to look at all tables no just from one model fixed in 0 right now
			iterator = editor->getExistingDiagram(0)->figuresEnumerator();
			while(iterator->HasNext())
			{
				tmp = (wxhdIFigure *)iterator->Next();
				if(tmp->getKindId() == DDRELATIONSHIPFIGURE)
				{
					relationship = (ddRelationshipFigure *)tmp;
					ddXmlStorage::Write(xmlWriter,relationship);
				}
			}
			delete iterator;

			ddXmlStorage::EndModel(xmlWriter);
			xmlTextWriterEndDocument(xmlWriter);
			xmlFreeTextWriter(xmlWriter);
			return true;
		}
	return false;
}

bool ddDatabaseDesign::readXmlModel(wxString file)
{
	
	//666 esto deberia BORRAR todo el modelo no solamente un diagrama asi que debe ser arreglado luego
	eraseDiagram(0);




	mappingIdToName.clear();
	//Initial Parse Model
	xmlTextReaderPtr reader = xmlReaderForFile(file.mb_str(wxConvUTF8), NULL, 0);
	ddXmlStorage::setModel(this);
	ddXmlStorage::initialModelParse(reader);
	
	//Parse Model
	xmlReaderNewFile(reader,file.mb_str(wxConvUTF8),NULL,0);
	ddXmlStorage::setModel(this);
	if(!ddXmlStorage::Read(reader))
	{
		return false;
	}
	xmlFreeTextReader(reader);
	return true;
}

wxString ddDatabaseDesign::getTableId(wxString tableName)
{
	return mappingNameToId[tableName];
}

void ddDatabaseDesign::addTableToMapping(wxString IdKey, wxString tableName)
{
	mappingIdToName[IdKey]=tableName;
}

wxString ddDatabaseDesign::getTableName(wxString Id)
{
	wxString tableName = wxEmptyString;
	
	tablesMappingHashMap::iterator it;
	for (it = mappingIdToName.begin(); it != mappingIdToName.end(); ++it)
	{
		wxString key = it->first;
		if(key.IsSameAs(Id,false))
		{
			tableName = it->second;
			break;
		}
	}
	return tableName;
}

wxhdDrawing* ddDatabaseDesign::createDiagram(wxWindow *owner)
{
	return editor->createDiagram(owner);
}