
#ifndef __FRM_DATABASEDESIGNER_H
#define __FRM_DATABASEDESIGNER_H

// Designer headers
#include "dd/draw/figures/ddAbstractFigure.h"
#include "dd/draw/figures/ddPolyLineFigure.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/ddmodel/ddDatabaseDesign.h"

class frmDatabaseDesigner : public pgFrame
{
public:
	frmDatabaseDesigner(frmMain *form, const wxString& _title); //DD-TODO: future include need from this parameters: pgConn *conn, const wxString& qry, const wxString& file = wxEmptyString);
	~frmDatabaseDesigner();
	void Go();
private:
	frmMain *mainForm;
	ddDatabaseDesign *design;
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