//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddPrecisionScaleDialog.h - Utility dialog class to allow user input of precision and scale
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdREMOVEDELETEDIALOG_H
#define hdREMOVEDELETEDIALOG_H

#include <wx/statline.h>
#include <wx/stattext.h>

enum ddSelectSchemaDialogCtrls
{
	DD_SCHEMASTREE = 31000
};

enum ddSchemeBrowserImages
{
	DD_IMG_FIG_SCHEMES = 0,
	DD_IMG_FIG_SCHEMA = 1
};

class ddSchemaBrowser;

class ddSelectSchemaDialog : public wxDialog
{
	DECLARE_CLASS( hdRemoveDeleteDialog )
	DECLARE_EVENT_TABLE()
public:
	ddSelectSchemaDialog();
	ddSelectSchemaDialog(	const wxString& message, 
							const wxString& caption = _("Title"), 
							wxWindow *parent = NULL
	                      );
	~ddSelectSchemaDialog();

	// Member initialization
	void Init();

	// Creation
	bool Create(	wxWindow *parent,
	                wxWindowID id,
					const wxString& message,
					const wxString& caption
					);

	// Creates the controls and sizers
	void CreateControls(const wxString& message);

	//Buttons Events
	void OnRemove(wxCommandEvent& WXUNUSED(event));
	void OnDelete(wxCommandEvent& WXUNUSED(event));
	void OnCancel(wxCommandEvent& WXUNUSED(event));

private:
	wxBoxSizer *topSizer;
	wxStaticLine *line;
	ddSchemaBrowser *schemaBrowser;
	wxButton *okButton, *cancelButton;
};

class ddSchemaBrowser : public wxTreeCtrl
{
public:
	ddSchemaBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);
	~ddSchemaBrowser();
	wxTreeItemId &createRoot(wxString Name);
	void refreshFromModel();

private:

	wxTreeItemId rootNode;
	wxImageList *imageList;

	DECLARE_EVENT_TABLE()
};

#endif

