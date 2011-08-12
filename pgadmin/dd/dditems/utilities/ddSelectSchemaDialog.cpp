//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddSelectSchemaDialog.cpp - Utility dialog class to allow user to select between delete / remove a figure
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/statline.h>

// App headers
#include "dd/dditems/utilities/ddSelectSchemaDialog.h"
#include "images/namespace-sm.pngc"
#include "images/namespaces.pngc"

IMPLEMENT_CLASS( ddSelectSchemaDialog, wxDialog )
BEGIN_EVENT_TABLE(ddSelectSchemaDialog, wxDialog)
        EVT_BUTTON(wxID_CANCEL, ddSelectSchemaDialog::OnCancel)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(ddSchemaBrowser, wxTreeCtrl)
/*	EVT_TREE_ITEM_ACTIVATED(DD_BROWSER, ddModelBrowser::OnItemActivated) 
	EVT_TREE_BEGIN_DRAG(DD_BROWSER, ddModelBrowser::OnBeginDrag)*/
END_EVENT_TABLE()

ddSelectSchemaDialog::ddSelectSchemaDialog(	const wxString& message, 
												const wxString& caption, 
												wxWindow *parent
                                              )
{
	wxWindowBase::SetFont(settings->GetSystemFont());
	Init();
	Create(parent, wxID_ANY, message, caption);
//666	cancelButton->SetFocus();
}

ddSelectSchemaDialog::~ddSelectSchemaDialog()
{
	if(schemaBrowser)
		delete schemaBrowser;
/*666	if(line)
		delete line;
	if(okButton)
		delete okButton;
	if(cancelButton)
		delete cancelButton;
		*/
}

ddSelectSchemaDialog::ddSelectSchemaDialog()
{
	Init();
}


void ddSelectSchemaDialog::Init( )
{
}

// Creation
bool ddSelectSchemaDialog::Create(	wxWindow *parent,
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
void ddSelectSchemaDialog::CreateControls(const wxString& message)
{
	// A top-level sizer
	topSizer = new wxBoxSizer(wxVERTICAL );
	this->SetSizer(topSizer);
	topSizer->AddSpacer(10);

	schemaBrowser = new ddSchemaBrowser(this,DD_SCHEMASTREE,wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

/*	//Message Sizer
	messageSizer = new wxBoxSizer(wxHORIZONTAL );
	topSizer->Add(messageSizer);
	messageSizer->AddSpacer(25);

	staticText = new wxStaticText(this, wxID_STATIC, message, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	messageSizer->Add(staticText, 0, wxALIGN_CENTER, 5);
	
	messageSizer->AddSpacer(45);

	// Add important user info
	wxString info = _("     Choose Remove from Diagram to remove only from current diagram.     ");
	wxString info2 = _("     Choose Remove from Model to delete permanently.     ");
		
	this->SetForegroundColour(wxColour(wxT("GREY")));
	staticText2 = new wxStaticText(this, wxID_STATIC, info, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	topSizer->Add(staticText2, 0, wxALIGN_LEFT, 5);

	staticText3 = new wxStaticText(this, wxID_STATIC, info2, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	topSizer->Add(staticText3, 0, wxALIGN_LEFT, 5);

	// A space and a dividing line before the Remove Delete and Cancel buttons
	topSizer->AddSpacer(10);
	line = new wxStaticLine ( this, wxID_STATIC,
	                          wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	topSizer->Add(line, 0, wxGROW | wxALL, 5);

	//Buttons Sizer
	buttonsSizer = new wxBoxSizer(wxHORIZONTAL );

	topSizer->Add(buttonsSizer, 0, wxALIGN_CENTER, 5);

	removeButton = new wxButton ( this, DD_REMOVE, wxT("&Remove from Diagram"),
	                    wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add(removeButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	deleteButton = new wxButton ( this, DD_DELETE, wxT("&Remove from Model"),
	                    wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add(deleteButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cancelButton = new wxButton ( this, wxID_CANCEL, wxT("&Cancel"),
	                    wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add(cancelButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	topSizer->AddSpacer(10);
*/
}

/*
void ddSelectSchemaDialog::OnRemove(wxCommandEvent& WXUNUSED(event))
{
    EndModal( DD_REMOVE );
}

void ddSelectSchemaDialog::OnDelete(wxCommandEvent& WXUNUSED(event))
{
    EndModal( DD_DELETE );
}
*/

void ddSelectSchemaDialog::OnCancel(wxCommandEvent& WXUNUSED(event))
{
    EndModal( wxID_CANCEL );
}

//
// ddSchemaBrowser
//

ddSchemaBrowser::ddSchemaBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
	: wxTreeCtrl(parent, id, pos, size, style)
{
	rootNode = (wxTreeItemId *)NULL;
	createRoot(_("Available Schemas"));

	// Create normal images list of browser
	// Remember to update enum gqbImages in ddModelBrowser.h if changing the images!!
	imageList = new wxImageList(16, 16);
	imageList->Add(*namespace_sm_png_ico);
	imageList->Add(*namespaces_png_ico);
	this->AssignImageList(imageList);
}

// Destructor
ddSchemaBrowser::~ddSchemaBrowser()
{
	this->DeleteAllItems();        // This remove and delete data inside tree's node
}

// Create root node
wxTreeItemId &ddSchemaBrowser::createRoot(wxString Name)
{
	rootNode = this->AddRoot(Name,DD_IMG_FIG_SCHEMES, DD_IMG_FIG_SCHEMES);
	return rootNode;
}



