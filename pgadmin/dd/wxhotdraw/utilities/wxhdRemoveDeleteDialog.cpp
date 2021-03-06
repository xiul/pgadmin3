//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdRemoveDeleteDialog.cpp - Utility dialog class to allow user to select between delete / remove a figure
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/statline.h>

// App headers
#include "dd/wxhotdraw/utilities/wxhdRemoveDeleteDialog.h"

IMPLEMENT_CLASS( wxhdRemoveDeleteDialog, wxDialog )

BEGIN_EVENT_TABLE(wxhdRemoveDeleteDialog, wxDialog)
        EVT_BUTTON(DD_REMOVE, wxhdRemoveDeleteDialog::OnRemove)
        EVT_BUTTON(DD_DELETE, wxhdRemoveDeleteDialog::OnDelete)
        EVT_BUTTON(wxID_CANCEL, wxhdRemoveDeleteDialog::OnCancel)
END_EVENT_TABLE()

wxhdRemoveDeleteDialog::wxhdRemoveDeleteDialog(	const wxString& message, 
												const wxString& caption, 
												wxWindow *parent
                                              )
{
	wxWindowBase::SetFont(settings->GetSystemFont());
	Init();
	Create(parent, wxID_ANY, message, caption);
	cancelButton->SetFocus();
}

wxhdRemoveDeleteDialog::~wxhdRemoveDeleteDialog()
{
	if(staticText)
		delete staticText;
	if(line)
		delete line;
	if(removeButton)
		delete removeButton;
	if(deleteButton)
		delete deleteButton;
	if(cancelButton)
		delete cancelButton;
}

wxhdRemoveDeleteDialog::wxhdRemoveDeleteDialog()
{
	Init();
}


void wxhdRemoveDeleteDialog::Init( )
{
}

// Creation
bool wxhdRemoveDeleteDialog::Create(	wxWindow *parent,
	                wxWindowID id,
					const wxString& caption,
					const wxString& message
					)
{
	wxWindowBase::SetFont(settings->GetSystemFont());

	if (!wxDialog::Create( parent, id, message, wxDefaultPosition, wxDefaultSize, wxCAPTION))
		return false;

	CreateControls(caption);

	// This fits the dialog to the minimum size dictated by
	// the sizers
	GetSizer()->Fit(this);

	// This ensures that the dialog cannot be sized smaller
	// than the minimum size
	GetSizer()->SetSizeHints(this);

	// Centre the dialog on the parent or (if none) screen

	Centre();

	return true;
}


	// Creates the controls and sizers
void wxhdRemoveDeleteDialog::CreateControls(const wxString& message)
{
	// A top-level sizer
	topSizer = new wxBoxSizer(wxVERTICAL );
	this->SetSizer(topSizer);
	topSizer->AddSpacer(10);
	//Message Sizer
	messageSizer = new wxBoxSizer(wxHORIZONTAL );
	topSizer->Add(messageSizer);
	messageSizer->AddSpacer(25);

	staticText = new wxStaticText(this, wxID_STATIC, message, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	messageSizer->Add(staticText, 0, wxALIGN_CENTER, 5);
	
	messageSizer->AddSpacer(25);

	// A space and a dividing line before the Remove Delete and Cancel buttons
	topSizer->AddSpacer(10);
	line = new wxStaticLine ( this, wxID_STATIC,
	                          wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	topSizer->Add(line, 0, wxGROW | wxALL, 5);

	//Buttons Sizer
	buttonsSizer = new wxBoxSizer(wxHORIZONTAL );

	topSizer->Add(buttonsSizer, 0, wxALIGN_CENTER, 5);

	removeButton = new wxButton ( this, DD_REMOVE, wxT("&Remove"),
	                    wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add(removeButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	deleteButton = new wxButton ( this, DD_DELETE, wxT("&Delete"),
	                    wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add(deleteButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cancelButton = new wxButton ( this, wxID_CANCEL, wxT("&Cancel"),
	                    wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add(cancelButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	topSizer->AddSpacer(10);
}

void wxhdRemoveDeleteDialog::OnRemove(wxCommandEvent& WXUNUSED(event))
{
    EndModal( DD_REMOVE );
}

void wxhdRemoveDeleteDialog::OnDelete(wxCommandEvent& WXUNUSED(event))
{
    EndModal( DD_DELETE );
}

void wxhdRemoveDeleteDialog::OnCancel(wxCommandEvent& WXUNUSED(event))
{
    EndModal( wxID_CANCEL );
}