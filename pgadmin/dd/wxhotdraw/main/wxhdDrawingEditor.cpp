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
#include "dd/wxhotdraw/main/wxhdDrawingEditor.h"
#include "dd/wxhotdraw/main/wxhdDrawingView.h"
#include "dd/wxhotdraw/tools/wxhdITool.h"

wxhdDrawingEditor::wxhdDrawingEditor(wxWindow *owner, bool defaultView)
{
	//666 index = 0;
	_diagrams = new wxhdArrayCollection();
	_model = new wxhdArrayCollection();
//666 000	_tool = NULL;
}

wxhdDrawingEditor::~wxhdDrawingEditor()
{
	//Hack: If just delete _diagrams collection an error is raised.
	wxhdDrawing *diagram; 
	while(_diagrams->count() > 0)
	{
		diagram = (wxhdDrawing *) _diagrams->getItemAt(0);
		_diagrams->removeItemAt(0);
		delete diagram;
	}

	//Hack: If just delete _model collection an error is raised.
	wxhdIFigure *tmp;
	while(_model->count() > 0)
	{
		tmp = (wxhdIFigure *) _model->getItemAt(0);
		_model->removeItemAt(0);
		delete tmp;
	}

	if(_model)
		delete _model;

	if(_diagrams)
		delete _diagrams;
/* 666 000	if(_tool)
		delete _tool; */
}

//Hack to allow create different kind of custom _views inside custom editor
wxhdDrawing* wxhdDrawingEditor::createDiagram(wxWindow *owner)
{

	//quede aqui arreglando el problema del huevo o la gallina debo crear el modelo y luego a�adirlo a la vista que lo debe hacer suyo y registrarse

	wxhdDrawing *_tmpModel = new wxhdDrawing(this);

	wxhdDrawingView *_viewTmp = new wxhdDrawingView(_diagrams->count(), owner, this, wxSize(1200, 1200), _tmpModel);
	
	// Set Scroll Bar & split
	_viewTmp->SetScrollbars( 10, 10, 127, 80 );
	_viewTmp->EnableScrolling(true, true);
	_viewTmp->AdjustScrollbars();

	_tmpModel->registerView(_viewTmp);

	//Add a new position inside each figure to allow use of this new diagram existing figures.
	int i;
	wxhdIFigure *tmp;
	for(i=0;i< _model->count();i++)
	{
		tmp = (wxhdIFigure *) _model->getItemAt(i);
		tmp->AddPosForNewDiagram();
	}

	//Add Diagram
	_diagrams->addItem((wxhdObject *) _tmpModel);
	return _tmpModel;
}

void wxhdDrawingEditor::deleteDiagram(int diagramIndex)
{
	wxhdDrawing *_tmpModel = (wxhdDrawing *) _diagrams->getItemAt(diagramIndex);
	_diagrams->removeItemAt(diagramIndex);
	wxhdDrawingView *_viewTmp = _tmpModel->getView();
	_tmpModel->registerView(NULL);
	if(_tmpModel)
		delete _tmpModel;
	if(_viewTmp)
		delete _viewTmp;

	// Fix other diagrams positions
	int i;
	for(i=diagramIndex; i < _diagrams->count(); i++)
	{
		getExistingDiagram(i)->getView()->syncIdx(i);
	}
	
	//Remove this position inside each figure to allow delete that diagram related info from figures.
	wxhdIFigure *tmp;
	for(i=0;i< _model->count();i++)
	{
		tmp = (wxhdIFigure *) _model->getItemAt(i);
		tmp->RemovePosOfDiagram(diagramIndex);
	}
}

wxhdDrawingView *wxhdDrawingEditor::getExistingView(int diagramIndex)
{
	if(diagramIndex >= _diagrams->count() || diagramIndex < 0)
	{
		return NULL;
	}
	
	wxhdDrawing *diagram = (wxhdDrawing *) _diagrams->getItemAt(diagramIndex);
	return diagram->getView();
}

wxhdDrawing *wxhdDrawingEditor::getExistingDiagram(int diagramIndex)
{
	if(diagramIndex >= _diagrams->count() || diagramIndex < 0)
	{
		return NULL;
	}

	return (wxhdDrawing *) _diagrams->getItemAt(diagramIndex);
}

void wxhdDrawingEditor::addModelFigure(wxhdIFigure *figure)
{
	if(_model)
		_model->addItem(figure);
}

void wxhdDrawingEditor::removeFromAllSelections(wxhdIFigure *figure)
{
	if(_model)
	{
		if(_diagrams)
		{
		int i;
			for(i=0;i< _diagrams->count();i++)
			{
				if(getExistingDiagram(i)->isFigureSelected(figure))
					getExistingDiagram(i)->removeFromSelection(figure); 
			}
		}
	}
}

void wxhdDrawingEditor::deleteModelFigure(wxhdIFigure *figure)
{
	if(_model)
	{
		if(_diagrams)
		{
		int i;
			for(i=0;i< _diagrams->count();i++)
			{
				if(getExistingDiagram(i)->includes(figure))
					getExistingDiagram(i)->remove(figure);
			}
		}
		_model->removeItem(figure);	
		delete figure;
		figure=NULL;
	}
}

void wxhdDrawingEditor::addDiagramFigure(int diagramIndex, wxhdIFigure *figure)
{
	//first time figure is used at a diagram then add to it
	if(!modelIncludes(figure))
	{
		//Add figure to model
		addModelFigure(figure);
		//Add needed position(s) to figure to allow their use at new diagram(s).
		int i,start;
		start = figure->displayBox().CountPositions();
		for(i=start; i< _diagrams->count(); i++)
		{
			figure->AddPosForNewDiagram();
		}
	}
	getExistingDiagram(diagramIndex)->add(figure);
}

void wxhdDrawingEditor::removeDiagramFigure(int diagramIndex, wxhdIFigure *figure)
{
	getExistingDiagram(diagramIndex)->remove(figure);
}

bool wxhdDrawingEditor::modelIncludes(wxhdIFigure *figure)
{
	if(_model)
		return _model->existsObject(figure);
	return false;
}

int wxhdDrawingEditor::modelCount()
{
	if(_model)
		return _diagrams->count();
	return 0;
}

wxhdIteratorBase *wxhdDrawingEditor::modelFiguresEnumerator()
{
	return _model->createIterator();
}

//666 right now DELETE always the figure, it should allow to choose between removing or deleting
void wxhdDrawingEditor::remOrDelSelFigures(int diagramIndex)
{
	int answer;
	wxhdIFigure *tmp;
	
	if (getExistingDiagram(diagramIndex)->countSelectedFigures() == 1)
	{
		tmp = (wxhdIFigure *) getExistingDiagram(diagramIndex)->selectedFigures()->getItemAt(0);
		answer = wxMessageBox(_("Are you sure you wish to delete figure ?"), _("Delete figures?"), wxYES_NO | wxNO_DEFAULT);
	}
	else if (getExistingDiagram(diagramIndex)->countSelectedFigures() > 1)
	{
		answer = wxMessageBox(
		             wxString::Format(_("Are you sure you wish to delete %d figures?"), getExistingDiagram(diagramIndex)->countSelectedFigures()),
		             _("Delete figures?"), wxYES_NO | wxNO_DEFAULT);
	}

	if (answer == wxYES)
	{
		while(getExistingDiagram(diagramIndex)->countSelectedFigures() > 0)
		{
			getExistingDiagram(diagramIndex)->removeFromSelection(tmp);
			getExistingDiagram(diagramIndex)->remove(tmp);
			if(tmp)
				delete tmp;
		}
		getExistingDiagram(diagramIndex)->clearSelection();  //reset selection to zero items
	}
}

/* 666 000
wxhdITool *wxhdDrawingEditor::tool()
{
	return _tool;
}

void wxhdDrawingEditor::setTool(wxhdITool *tool)
{
	if(_tool)
		delete _tool;
	_tool = tool;
}
*/

/* 666 000
void wxhdDrawingEditor::createMenu(wxMenu &mnu)
{
	wxMenuItem *item;
	item = mnu.AppendCheckItem(1000, _("Sample Item"));
	item->Check(true);
}

void wxhdDrawingEditor::OnGenericPopupClick(wxCommandEvent &event, wxhdDrawingView *view)
{
	switch(event.GetId())
	{
		case 1000:
			wxMessageBox(_("Sample menu item"), _("Sample"), wxOK, view);
	}
}
*/