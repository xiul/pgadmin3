//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdDrawingEditor.cpp - Main class that manages all other classes
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/ddmodel/ddDrawingEditor.h"
#include "dd/dditems/utilities/ddTableNameDialog.h"
#include "dd/ddmodel/ddDatabaseDesign.h"
#include "dd/ddmodel/ddDrawingView.h"


ddDrawingEditor::ddDrawingEditor(wxWindow *owner, ddDatabaseDesign *design)
	: wxhdDrawingEditor(owner, true)
{
	databaseDesign = design;
}

wxhdDrawing* ddDrawingEditor::createDiagram(wxWindow *owner)
{

	//quede aqui arreglando el problema del huevo o la gallina debo crear el modelo y luego añadirlo a la vista que lo debe hacer suyo y registrarse

	wxhdDrawing *_tmpModel = new wxhdDrawing(this);

	wxhdDrawingView *_viewTmp = new ddDrawingView(_diagrams->count(), owner, this, wxSize(1200, 1200), _tmpModel);
	
	// Set Scroll Bar & split
	_viewTmp->SetScrollbars( 10, 10, 127, 80 );
	_viewTmp->EnableScrolling(true, true);
	_viewTmp->AdjustScrollbars();

	_tmpModel->registerView(_viewTmp);

	_viewTmp->SetDropTarget(new ddDropTarget(databaseDesign,_tmpModel));

	//Add Diagram
	_diagrams->addItem((wxhdObject *) _tmpModel);
	return _tmpModel;
}


void ddDrawingEditor::deleteSelectedFigures(int diagramIndex)
{
	wxhdIFigure *tmp;
	ddTableFigure *table;
	ddRelationshipFigure *relation;
	int answer;
	int numbTables = 0;
	int numbRelationships = 0;

	if (getExistingDiagram(diagramIndex)->countSelectedFigures() == 1)
	{
		tmp = (wxhdIFigure *) getExistingDiagram(diagramIndex)->selectedFigures()->getItemAt(0);
		if(tmp->getKindId() == DDTABLEFIGURE)
		{
			numbTables = 1;
			table = (ddTableFigure *)tmp;
			answer = wxMessageBox(_("Are you sure you wish to delete table ") + table->getTableName() + wxT("?"), _("Delete table?"), wxYES_NO | wxNO_DEFAULT);
		}
		if(tmp->getKindId() == DDRELATIONSHIPFIGURE)
		{
			numbRelationships = 1;
			relation = (ddRelationshipFigure *)tmp;
			answer = wxMessageBox(_("Are you sure you wish to delete relationship ") + relation->getConstraintName() + wxT("?"), _("Delete relationship?"), wxYES_NO | wxNO_DEFAULT);
		}
	}
	else if (getExistingDiagram(diagramIndex)->countSelectedFigures() > 1)
	{
		numbTables = 0;
		wxhdIteratorBase *iterator = getExistingDiagram(diagramIndex)->selectionFigures(); //666 selection->createIterator();
		while(iterator->HasNext())
		{
			tmp = (wxhdIFigure *)iterator->Next();
			if(tmp->getKindId() == DDTABLEFIGURE)
				numbTables++;
		}
		delete iterator;

		answer = wxMessageBox(
		             wxString::Format(_("Are you sure you wish to delete %d tables?"), numbTables),
		             _("Delete tables?"), wxYES_NO | wxNO_DEFAULT);

		if(numbTables == 0)
		{
			iterator = getExistingDiagram(diagramIndex)->selectionFigures(); //666 selection->createIterator();
			while(iterator->HasNext())
			{
				tmp = (wxhdIFigure *)iterator->Next();
				if(tmp->getKindId() == DDRELATIONSHIPFIGURE)
					numbRelationships++;
			}
			delete iterator;
		}
	}

	if (answer == wxYES)
	{
		while(numbTables > 0)
		{
			tmp = (wxhdIFigure *) getExistingDiagram(diagramIndex)->selectedFigures()->getItemAt(0); //666 (wxhdIFigure *) selection->getItemAt(0);
			if(tmp->getKindId() == DDTABLEFIGURE)
			{
				table = (ddTableFigure *)tmp;
				getExistingDiagram(diagramIndex)->removeFromSelection(table);  //666 removeFromSelection(table);
				table->processDeleteAlert(getExistingDiagram(diagramIndex));
				getExistingDiagram(diagramIndex)->remove(table);
				if(table)
					delete table;
				numbTables--;
			}
			else
			{
				getExistingDiagram(diagramIndex)->removeFromSelection(tmp); //isn't a tables is probably a relationship
			}
		}

		if( numbRelationships > 0 && numbTables == 0 )
		{
			while(numbRelationships > 0)
			{
				tmp = (wxhdIFigure *) getExistingDiagram(diagramIndex)->selectedFigures()->getItemAt(0); //666 selection->getItemAt(0);
				if(tmp->getKindId() == DDRELATIONSHIPFIGURE)
				{
					relation = (ddRelationshipFigure *)tmp;
					relation->removeForeignKeys();
					relation->disconnectEnd();
					relation->disconnectStart();
					getExistingDiagram(diagramIndex)->removeFromSelection(relation);
					getExistingDiagram(diagramIndex)->remove(relation);
					if(relation)
						delete relation;
					numbRelationships--;
				}
				else
				{
					getExistingDiagram(diagramIndex)->removeFromSelection(tmp); //isn't neither a table or relationship
				}
			}
		}

		getExistingDiagram(diagramIndex)->clearSelection();  //after delete all items all relationships remains at selection and should be removed
	}

}

void ddDrawingEditor::checkRelationshipsConsistency(int diagramIndex)
{
	wxhdIFigure *tmp;
	ddRelationshipFigure *relation;
	wxhdDrawing *diagram = getExistingDiagram(diagramIndex);

	// First Step Removel all orphan [relations without source or destination] relationships 
	// from DIAGRAM but NOT from MODEL 
	wxhdIteratorBase *iterator = diagram->figuresEnumerator();
	while(iterator->HasNext())
	{
		tmp = (wxhdIFigure *)iterator->Next();
		if(tmp->getKindId() == DDRELATIONSHIPFIGURE)
		{
			relation = (ddRelationshipFigure *)tmp;
			//test if all tables of a relationship are included if this is not the case then remove relationship from this diagram
			bool sourceExists = diagram->getFiguresCollection()->existsObject(relation->getStartTable());
			bool destinationExists = diagram->getFiguresCollection()->existsObject(relation->getEndTable());
			if(!sourceExists || !destinationExists)
			{
				diagram->remove(relation);
			}

		}
	}
	delete iterator;

	// Now add all existing relationships in MODEL to DIAGRAM if both source and destination
	// tables exists at DIAGRAM
	iterator = _model->createIterator();
	while(iterator->HasNext())
	{
		tmp = (wxhdIFigure *)iterator->Next();
		if(tmp->getKindId() == DDRELATIONSHIPFIGURE)
		{
			relation = (ddRelationshipFigure *)tmp;

			//test if all tables of a relationship are included if this is the case then include relationship at this diagram
			bool sourceExists = diagram->getFiguresCollection()->existsObject(relation->getStartTable());
			bool destinationExists = diagram->getFiguresCollection()->existsObject(relation->getEndTable());
			bool relationExists = diagram->getFiguresCollection()->existsObject(relation);
			if(sourceExists && destinationExists && !relationExists)
			{
				diagram->add(relation);
				relation->updateConnection(diagramIndex);
			}
		}
	}
	delete iterator;
}

void ddDrawingEditor::checkAllDigramsRelConsistency()
{
	int i, size = _diagrams->count();

	for(i=0; i < size ; i++)
	{
		checkRelationshipsConsistency(i);
	}
}



/*
void ddDrawingEditor::createView(int diagramIndex, wxWindow *owner)
{
	wxhdDrawing *_tmpModel = new wxhdDrawing();

	ddDrawingView *_viewTmp = new ddDrawingView(diagramIndex, owner, this, wxSize(1200, 1200), _tmpModel);  //666 change view index to right one
	
	_viewTmp->SetScrollbars( 10, 10, 127, 80 );
	_viewTmp->EnableScrolling(true, true);
	_viewTmp->AdjustScrollbars();

	_tmpModel->registerView(_viewTmp);

	//Add Diagram
	_diagrams->addItem((wxhdObject *) _tmpModel);
}
*/

/* 666 000
void ddDrawingEditor::createMenu(wxMenu &mnu)
{
	mnu.Append(MNU_NEWTABLE, _("Add new Table"));
}

void ddDrawingEditor::OnGenericPopupClick(wxCommandEvent &event, wxhdDrawingView *view)
{
	switch(event.GetId())
	{
		case MNU_NEWTABLE:
			ddTableNameDialog *newTableDialog = new ddTableNameDialog(
			    view,
			    databaseDesign->getNewTableName(),
			    wxEmptyString,
			    NULL
			);
			int answer = newTableDialog->ShowModal();
			if (answer == wxID_OK && !newTableDialog->GetValue1().IsEmpty())
			{
				ddTableFigure *newTable = new ddTableFigure(newTableDialog->GetValue1(),
				        rand() % 90 + 200,
				        rand() % 90 + 140,
				        newTableDialog->GetValue2()
				                                           );
				databaseDesign->addTable(newTable);
				databaseDesign->refreshDraw();
			}
			delete newTableDialog;
			break;
	}
}
*/