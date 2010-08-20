//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// 
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// frmDatabaseDesigner.h - The database designer form
//
//////////////////////////////////////////////////////////////////////////

#ifndef __FRM_DATABASEDESIGNER_H
#define __FRM_DATABASEDESIGNER_H

// Designer headers
#include "dd/draw/figures/ddAbstractFigure.h"
#include "dd/draw/figures/ddPolyLineFigure.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/ddmodel/ddDatabaseDesign.h"


enum
{
    CTL_DDNOTEBOOK = 1001,
    CTL_DDSPLITTER
};


class frmDatabaseDesigner : public pgFrame
{
public:
	frmDatabaseDesigner(frmMain *form, const wxString& _title);
    //DD-TODO: future include need from this parameters: pgConn *conn, const wxString& qry, const wxString& file = wxEmptyString);
	~frmDatabaseDesigner();
	void Go();
private:
	frmMain *mainForm;
	ddDatabaseDesign *design;
    wxTextCtrl *sqltext;
	void OnClose(wxCloseEvent& event);
	void OnAddTable(wxCommandEvent& event);
	void OnNewModel(wxCommandEvent& event);
	void OnModelGeneration(wxCommandEvent& event);
	wxAuiManager manager;
	DECLARE_EVENT_TABLE()
};

///////////////////////////////////////////////////////

class databaseDesignerBaseFactory : public actionFactory
{
protected:
    databaseDesignerBaseFactory(menuFactoryList *list) : actionFactory(list) {}
    wxWindow *StartDialogDesigner(frmMain *form, pgObject *obj, const wxString &sql);
public:
    bool CheckEnable(pgObject *obj);
};

class databaseDesignerFactory : public databaseDesignerBaseFactory
{
public:
    databaseDesignerFactory(menuFactoryList *list, wxMenu *mnu, ctlMenuToolbar *toolbar);
    wxWindow *StartDialog(frmMain *form, pgObject *obj);
};

#endif // __FRM_DATABASEDESIGNER_H
