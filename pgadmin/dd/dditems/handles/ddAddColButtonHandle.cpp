//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAddColButtonHandle.cpp - A handle for a table figure that allow to graphically add columns
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/dditems/handles/ddAddColButtonHandle.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/wxhotdraw/main/hdDrawingView.h"

//Images
#include "images/ddAddColumnCursor.pngc"

ddAddColButtonHandle::ddAddColButtonHandle(hdIFigure *owner, hdILocator *buttonLocator , wxBitmap &buttonImage, wxSize &size):
	hdButtonHandle(owner, buttonLocator, buttonImage, size)
{
	handleCursorImage = wxBitmap(*ddAddColumnCursor_png_img).ConvertToImage();
	handleCursor = wxCursor(handleCursorImage);
}

ddAddColButtonHandle::~ddAddColButtonHandle()
{
}

void ddAddColButtonHandle::invokeStart(hdMouseEvent &event, hdDrawingView *view)
{
	ddTableFigure *table = (ddTableFigure *) getOwner();
	wxTextEntryDialog nameDialog(view, wxT("New column name"), wxT("Add a column"), wxT("NewColumn"));
	bool again;
	do
	{
		again = false;
		int answer = nameDialog.ShowModal();
		if (answer == wxID_OK)
		{
			wxString name = nameDialog.GetValue();
			if(table->getColByName(name)==NULL)
				table->addColumn(view->getIdx(), new ddColumnFigure(name, table));
			else
			{
				wxString msg(wxT("Error trying to add new column '"));
				msg.Append(name);
				msg.Append(wxT("' column name already in use"));
				wxMessageDialog info( view, msg ,
				                      wxT("Column name already in use"),
				                      wxNO_DEFAULT | wxOK | wxICON_EXCLAMATION);
				again = true;
				info.ShowModal();
			}
		}

	}
	while(again);
	view->Refresh();
}

void ddAddColButtonHandle::invokeStep(hdMouseEvent &event, hdDrawingView *view)
{
}

void ddAddColButtonHandle::invokeEnd(hdMouseEvent &event, hdDrawingView *view)
{
}

wxCursor ddAddColButtonHandle::createCursor()
{
	return handleCursor;
}
