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

ddDrawingView::ddDrawingView(int diagram, wxWindow *ddParent, wxhdDrawingEditor *editor , wxSize size, wxhdDrawing *drawing)
	: wxhdDrawingView(diagram, ddParent, editor, size, drawing)
{
}

/*
*/

void ddDrawingView::createViewMenu(wxMenu &mnu)
{
	mnu.Append(MNU_NEWTABLE, _("Add new Table"));
}

void ddDrawingView::OnGenericViewPopupClick(wxCommandEvent &event)
{
/*777 666
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
			*/
}