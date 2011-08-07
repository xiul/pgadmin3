//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddTextEditor.cpp - class used to show generate SQL from model
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/ddmodel/ddTextEditor.h"

BEGIN_EVENT_TABLE(ddTextEditor, wxFrame)
	EVT_MENU(idSave, ddTextEditor::OnSave)
	EVT_MENU(idOpen, ddTextEditor::OnOpen)
	EVT_MENU(idExit, ddTextEditor::OnExit)
END_EVENT_TABLE()

ddTextEditor::ddTextEditor(wxString initialText) : wxFrame(NULL, wxID_ANY, wxT("wxddTextEditor"), wxDefaultPosition, wxSize(650, 500))
{
	menu = new wxMenuBar();
	file = new wxMenu();
	file->Append(idSave, wxT("&Save File\tCtrl-S"));
	file->Append(idOpen, wxT("&Open File\tCtrl-O"));
	file->AppendSeparator();
	file->Append(idExit, wxT("E&xit\tCtrl-F4"));
	menu->Append(file, wxT("&File"));
	SetMenuBar(menu);

	text = new ctlSQLBox(this, CTL_SQLQUERY, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxSIMPLE_BORDER | wxTE_RICH2);
	text->SetText(initialText);
}

void ddTextEditor::OnSave(wxCommandEvent &event)
{
	wxFileDialog *saveDialog = new wxFileDialog(this, wxT("Save File~"), wxT(""), wxT(""),
	        wxT("Text Files (*.txt)|*.txt|C++ Files (*.cpp)|*.cpp"), wxFD_SAVE);
	int response = saveDialog->ShowModal();
	if (response == wxID_OK)
	{
		text->SaveFile(saveDialog->GetPath());
	}
}

void ddTextEditor::OnOpen(wxCommandEvent &event)
{
	wxFileDialog *openDialog = new wxFileDialog(this, wxT("Open File~"), wxT(""), wxT(""),
	        wxT("Text Files (*.txt)|*.txt|C++ Files (*.cpp)|*.cpp"), wxFD_OPEN);
	int response = openDialog->ShowModal();
	if (response == wxID_OK)
	{
		text->LoadFile(openDialog->GetPath());
	}
}

void ddTextEditor::OnExit(wxCommandEvent &event)
{
	Destroy();
}
