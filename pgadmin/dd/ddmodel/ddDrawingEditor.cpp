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


ddDrawingEditor::ddDrawingEditor(wxWindow *owner, ddDatabaseDesign *design)
:wxhdDrawingEditor(owner)
{
	databaseDesign = design;
}

void ddDrawingEditor::createMenu(wxMenu &mnu)
{
	mnu.Append(MNU_NEWTABLE, _("Add new Table"));
}

void ddDrawingEditor::OnGenericPopupClick(wxCommandEvent& event, wxhdDrawingView *view)
{
	switch(event.GetId())
	{
	case MNU_NEWTABLE:
		ddTableNameDialog *newTableDialog = new ddTableNameDialog(
												view,
												DDTABLENAMEDIALOG,
												wxT("New Table Name"),
												wxT("Table Name"),
												databaseDesign->getNewTableName(),
												wxT("Short Name"),
												wxEmptyString,
												wxDefaultPosition,
												wxDefaultSize,
												wxCAPTION,
												NULL
												);
		int answer = newTableDialog->ShowModal();
		if (answer == wxID_OK && !newTableDialog->GetValue1().IsEmpty())
		{
			ddTableFigure *newTable = new ddTableFigure(newTableDialog->GetValue1(),
														rand()%90+200,
														rand()%90+140,
														newTableDialog->GetValue2()
														);
			databaseDesign->addTable(newTable);
			databaseDesign->refreshDraw();
		}
		delete newTableDialog;	
	break;
	}
}