//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRect.cpp 
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/statline.h>
// App headers
#include "dd/draw/utilities/ddDialogs.h"

IMPLEMENT_CLASS( ddTwoInputsDialog, wxDialog )

BEGIN_EVENT_TABLE( ddTwoInputsDialog, wxDialog )
END_EVENT_TABLE()

ddTwoInputsDialog::ddTwoInputsDialog(	wxWindow* parent,
										wxWindowID id,
										const wxString& caption,
										const wxString& captionLabel1,
										const wxString& defaultValue1,
										const wxString& captionLabel2,
										const wxString& defaultValue2,
										const wxPoint& pos,
										const wxSize& size,
										long style 
										)
{	
	Init();
	label1=captionLabel1;
	SetValue1(defaultValue1);
	label2=captionLabel2;
	SetValue2(defaultValue2);
    Create(parent, id, caption, pos, size, style);    
}

ddTwoInputsDialog::ddTwoInputsDialog()
{
	Init();
}

void ddTwoInputsDialog::Init( )
{
    m_value1 = wxEmptyString;
    m_value2 = wxEmptyString;
}

bool ddTwoInputsDialog::Create(	wxWindow* parent,
					wxWindowID id = DDTWODIALOGSINPUT,
					const wxString& caption = wxT("Input Dialog"),
					const wxPoint& pos = wxDefaultPosition,
					const wxSize& size = wxDefaultSize,
					long style = wxCAPTION )
{
    if (!wxDialog::Create( parent, id, caption, pos, size, style ))
        return false;

    CreateControls();
    //SetDialogValidators();

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

void ddTwoInputsDialog::CreateControls()
{
    // A top-level sizer

    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL );
    this->SetSizer(topSizer);

    // A second box sizer to give more space around the controls

    wxBoxSizer* boxSizer = new wxBoxSizer(wxHORIZONTAL );
    topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    // Label for the Value 1
    wxStaticText* value1Label = new wxStaticText ( this, wxID_STATIC,
        label1, wxDefaultPosition, wxDefaultSize, 0 );
    boxSizer->Add(value1Label, 0, wxALIGN_LEFT|wxALL, 5);

    // A text control for Value 1
   wxTextCtrl* value1Ctrl = new wxTextCtrl ( this, DDVALUE1, m_value1 , wxDefaultPosition,
 wxDefaultSize, 0 );
    boxSizer->Add(value1Ctrl, 0, wxGROW|wxALL, 5);

    // Label for the Value 2
    wxStaticText* value2Label = new wxStaticText ( this, wxID_STATIC,
        label2, wxDefaultPosition, wxDefaultSize, 0 );
    boxSizer->Add(value2Label, 0, wxALIGN_LEFT|wxALL, 5);

    // A text control for Value 2
   wxTextCtrl* value2Ctrl = new wxTextCtrl ( this, DDVALUE2, m_value2, wxDefaultPosition,
 wxDefaultSize, 0 );
    boxSizer->Add(value2Ctrl, 0, wxGROW|wxALL, 5);

    // A dividing line before the OK and Cancel buttons

    wxStaticLine* line = new wxStaticLine ( this, wxID_STATIC,
        wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    boxSizer->Add(line, 0, wxGROW|wxALL, 5);
    // A horizontal box sizer to contain Reset, OK, Cancel and Help

    wxBoxSizer* okCancelBox = new wxBoxSizer(wxHORIZONTAL);
    boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    // The OK button

    wxButton* ok = new wxButton ( this, wxID_OK, wxT("&OK"),
        wxDefaultPosition, wxDefaultSize, 0 );
    okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // The Cancel button

    wxButton* cancel = new wxButton ( this, wxID_CANCEL,
        wxT("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);



}

//Transfer data to the window
bool ddTwoInputsDialog::TransferDataToWindow()
{
    wxTextCtrl* val1Ctrl = (wxTextCtrl*) FindWindow(DDVALUE1);
	wxTextCtrl* val2Ctrl = (wxTextCtrl*) FindWindow(DDVALUE2);

    val1Ctrl->SetValue(m_value1);
	val2Ctrl->SetValue(m_value2);

    return true;
}

//Transfer data from the window
bool ddTwoInputsDialog::TransferDataFromWindow()
{
    wxTextCtrl* val1Ctrl = (wxTextCtrl*) FindWindow(DDVALUE1);
	wxTextCtrl* val2Ctrl = (wxTextCtrl*) FindWindow(DDVALUE2);

    m_value1 = val1Ctrl->GetValue();
	m_value2 = val2Ctrl->GetValue();

    return true;
}


/*
// Set the validators for the dialog controls
void ddTwoInputsDialog::SetDialogValidators()
{
    FindWindow(DDVALUE1)->SetValidator(
        wxTextValidator(wxFILTER_NONE, & m_value1));
    FindWindow(DDVALUE2)->SetValidator(
        wxTextValidator(wxFILTER_ALPHANUMERIC, & m_value2));
}
*/