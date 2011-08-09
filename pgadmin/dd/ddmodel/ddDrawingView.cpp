//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawingView.cpp - Main canvas where all tables and relationships are drawn
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/ddmodel/ddDrawingView.h"
#include "dd/wxhotdraw/utilities/wxhdArrayCollection.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/dditems/utilities/ddTableNameDialog.h"

ddDrawingView::ddDrawingView(int diagram, wxWindow *ddParent, ddDrawingEditor *editor , wxSize size, wxhdDrawing *drawing)
	: wxhdDrawingView(diagram, ddParent, editor, size, drawing)
{
}

void ddDrawingView::createViewMenu(wxMenu &mnu)
{
	mnu.Append(MNU_NEWTABLE, _("Add new Table"));
}

void ddDrawingView::OnGenericViewPopupClick(wxCommandEvent &event)
{
	 ddDrawingEditor *ed = (ddDrawingEditor*) editor();	
	switch(event.GetId())
	{
	case MNU_NEWTABLE:
			ddTableNameDialog *newTableDialog = new ddTableNameDialog(
			    this,
			    ed->getDesign()->getNewTableName(),
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
				ed->getDesign()->addTableToView(this->getIdx(), newTable);
				ed->getDesign()->refreshDraw(this->getIdx());
			}
			delete newTableDialog;
			break;
	}
}

ddDropTarget::ddDropTarget(ddDatabaseDesign *sourceDesign, wxhdDrawing *targetDrawing)
{
	target = targetDrawing;
	source = sourceDesign;

}

bool ddDropTarget::OnDropText(wxCoord x, wxCoord y, const wxString &text)
{
	ddTableFigure *t = source->getTable(text);
	if(t!=NULL && !target->includes(t))
	{
		target->add(t);
		t->syncInternalsPosAt(target->getView()->getIdx(),x,y);
		source->getEditor()->checkRelationshipsConsistency(target->getView()->getIdx());
		target->getView()->Refresh();
		return true;
	}
	else
	{
		if(target->includes(t))
		{
			wxMessageBox(_("Table exists already at this diagram"),_("Drag and drop warning"), wxICON_EXCLAMATION);
			return true;
		}
		else
			return false;
	}
}
