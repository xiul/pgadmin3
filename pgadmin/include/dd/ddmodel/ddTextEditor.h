//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbObject.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddTextEditor.h - 
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDTEXTEDITOR_H
#define DDTEXTEDITOR_H


class ddTextEditor : public wxFrame {
    public:
        ddTextEditor(wxString initialText);

    private:
        wxMenuBar *menu;
        wxMenu *file;
        wxTextCtrl *text;
        void OnSave(wxCommandEvent &event); 
        void OnOpen(wxCommandEvent &event); 
        void OnExit(wxCommandEvent &event); 

        enum MenuControls {
            idSave = 7590,
            idOpen, 
			idExit
        };
        DECLARE_EVENT_TABLE()
};
#endif