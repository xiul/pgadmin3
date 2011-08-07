//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddColumnTextTool.cpp - Modification of simple text tool for editing composite figure columns
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/choicdlg.h>

// App headers
#include "dd/dditems/tools/ddColumnTextTool.h"
#include "dd/dditems/figures/ddTextTableItemFigure.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/utilities/ddTableNameDialog.h"

class hdDrawingEditor;


ddColumnTextTool::ddColumnTextTool(hdDrawingView *view, hdIFigure *fig, hdITool *dt, bool fastEdit , wxString dialogCaption, wxString dialogMessage):
	hdSimpleTextTool(view, fig, dt, fastEdit, dialogCaption, dialogMessage)
{
	if(colTextFigure->ms_classInfo.IsKindOf(&ddTextTableItemFigure::ms_classInfo))
		colTextFigure = (ddTextTableItemFigure *) fig;
	else
		colTextFigure = NULL;
}

ddColumnTextTool::~ddColumnTextTool()
{
}

void ddColumnTextTool::mouseDown(hdMouseEvent &event)
{
	hdSimpleTextTool::mouseDown(event);
}

bool ddColumnTextTool::callDialog(hdDrawingView *view)
{
	if(colTextFigure->getOwnerColumn() == NULL)
	{
		wxString colName = colTextFigure->getText();
		wxString colShortName = colTextFigure->getAlias();
		ddTableNameDialog *nameAliasDialog = new ddTableNameDialog(
		    view,
		    colName,
		    colShortName,
		    colTextFigure
		);
		nameAliasDialog->ShowModal();

		colTextFigure->setText(nameAliasDialog->GetValue1());
		colTextFigure->setAlias(nameAliasDialog->GetValue2());

		//check if names changed
		bool noChange = colShortName.IsSameAs(nameAliasDialog->GetValue1()) && colShortName.IsSameAs(nameAliasDialog->GetValue2());

		delete nameAliasDialog;

		return !noChange;
	}
	else
	{
		bool change = hdSimpleTextTool::callDialog(view);
		if(  change && colTextFigure->getOwnerColumn()->isGeneratedForeignKey()) //after a manual user column rename, deactivated automatic generation of fk name.
			colTextFigure->getOwnerColumn()->deactivateGenFkName();
		return change;
	}
}
