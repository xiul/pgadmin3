//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// 
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// frmDatabaseDesigner.cpp - The database designer form
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/aui/aui.h>
#include <wx/splitter.h>

// App headers
#include "frm/frmMain.h"
#include "frm/frmDatabaseDesigner.h"
#include "ctl/ctlMenuToolbar.h"
#include "schema/pgObject.h"
#include "schema/pgDatabase.h"

// Designer headers
#include "dd/dditems/figures/ddColumnKindIcon.h"
#include "dd/draw/figures/ddPolyLineFigure.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/draw/figures/ddRectangleFigure.h"
#include "dd/draw/figures/ddBitmapFigure.h"
#include "dd/draw/tools/ddConnectionCreationTool.h"

#include "dd/ddmodel/ddDatabaseDesign.h"
#include "dd/ddmodel/ddTextEditor.h"

#include "dd/dditems/figures/ddTextColumnFigure.h"
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/dditems/figures/ddTableFigure.h"

// Icons
#include "images/ddmodel-32.xpm"
#include "images/file_new.xpm"
#include "images/table.xpm"
#include "images/continue.xpm"
#include "images/help.xpm"

BEGIN_EVENT_TABLE(frmDatabaseDesigner, pgFrame)
EVT_MENU(MNU_NEW,               frmDatabaseDesigner::OnNewModel)
EVT_MENU(MNU_ADDTABLE,          frmDatabaseDesigner::OnAddTable)
EVT_MENU(MNU_GENERATEMODEL,     frmDatabaseDesigner::OnModelGeneration)
EVT_CLOSE(                      frmDatabaseDesigner::OnClose)
END_EVENT_TABLE()

 frmDatabaseDesigner::frmDatabaseDesigner(frmMain *form, const wxString& _title)
:pgFrame(NULL, _title)
{
	mainForm=form;
    SetTitle(wxT("Database Designer"));

	RestorePosition(100, 100, 600, 500, 450, 300);
	SetMinSize(wxSize(450,300));
    
    // notify wxAUI which frame to use
    manager.SetManagedWindow(this);
    manager.SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_TRANSPARENT_DRAG);

	wxWindowBase::SetFont(settings->GetSystemFont());

    // Set File menu
    wxMenu *fileMenu = new wxMenu();
    fileMenu->Append(MNU_NEW, _("&New database design\tCtrl-N"), _("Create a new database design"));
    fileMenu->AppendSeparator();
    fileMenu->Append(MNU_EXIT, _("E&xit\tCtrl-W"), _("Exit database designer window"));

    // Set Help menu
	wxMenu *helpMenu=new wxMenu();
    helpMenu->Append(MNU_CONTENTS, _("&Help"),                 _("Open the helpfile."));
    helpMenu->Append(MNU_HELP, _("&SQL Help\tF1"),                _("Display help on SQL commands."));

	// Set menu bar
    menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _("&File"));
    menuBar->Append(helpMenu, _("&Help"));
	SetMenuBar(menuBar);

    // Set status bar
	int iWidths[6] = {0, -1, 40, 150, 80, 80};
	CreateStatusBar(6);
    SetStatusBarPane(-1);
    SetStatusWidths(6, iWidths);

    // Set toolbar
    toolBar = new ctlMenuToolbar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);
    toolBar->SetToolBitmapSize(wxSize(16, 16));
    toolBar->AddTool(MNU_NEW, _("New"), wxBitmap(file_new_xpm), _("New database design"), wxITEM_NORMAL);
    toolBar->AddTool(MNU_ADDTABLE, _("Add Table"), wxBitmap(table_xpm), _("Add empty table to the current model"), wxITEM_NORMAL);
	toolBar->AddTool(MNU_GENERATEMODEL, _("Generate Model"), wxBitmap(continue_xpm), _("Generate SQL for the current model"), wxITEM_NORMAL);
	toolBar->AddSeparator();
    toolBar->AddTool(MNU_HELP, _("Help"), wxBitmap(help_xpm), _("Display help"), wxITEM_NORMAL);
    toolBar->Realize();

    // Add the notebook with database designer
	wxNotebook *notebook = new wxNotebook(this, CTL_DDNOTEBOOK, wxDefaultPosition, wxDefaultSize);
	wxSplitterWindow *ddMainContainer = new wxSplitterWindow(notebook, CTL_DDSPLITTER, wxDefaultPosition, wxDefaultSize, wxSP_3D);
	wxPanel *pnlQuery = new wxPanel(ddMainContainer);
	design = new ddDatabaseDesign(ddMainContainer);
	ddMainContainer->SplitVertically(pnlQuery,design->getView());
    ddMainContainer->UpdateSize();
    ddMainContainer->SetSashPosition(10, true);
    ddMainContainer->SetMinimumPaneSize(10);
    ddMainContainer->UpdateSize();
	notebook->AddPage(ddMainContainer, _("Database Designer"));
	notebook->SetSelection(0);

    // Now, the scratchpad
    sqltext = new wxTextCtrl(this, -1, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxHSCROLL);

    // Add the panes
    manager.AddPane(notebook,
      wxAuiPaneInfo().Center().
      Name(wxT("sqlQuery")).Caption(_("Database Designer")).
      CaptionVisible(true).CloseButton(true).MaximizeButton(true).
      Dockable(true).Movable(true));
	manager.AddPane(sqltext,
      wxAuiPaneInfo().Right().
      Name(wxT("sqlText")).Caption(_("SQL query")).
      CaptionVisible(true).CloseButton(true).
      MinSize(wxSize(200,100)).BestSize(wxSize(350,200)));
	manager.AddPane(toolBar, wxAuiPaneInfo().Name(wxT("toolBar")).Caption(_("Tool bar")).ToolbarPane().Top().LeftDockable(false).RightDockable(false));

    // Update the AUI manager
	manager.Update();
    
    SetStatusText(wxString(wxT("Ready")), 1);
}


frmDatabaseDesigner::~frmDatabaseDesigner(){
    // Save form's position
	SavePosition();
    
	// Uninitialize wxAUIManager
	manager.UnInit();
	
    // Delete current design
	if(design)
		delete design;
    
	if (mainForm)
		mainForm->RemoveFrame(this);
}


void frmDatabaseDesigner::Go()
{
    Show(true);
}


void frmDatabaseDesigner::OnClose(wxCloseEvent& event)
{
	Hide();
	Destroy();
}


void frmDatabaseDesigner::OnAddTable(wxCommandEvent& event)
{
	ddTableFigure *newTable = new ddTableFigure(design->getNewTableName(),
        rand()%90+200, rand()%90+140);
	design->addTable(newTable);
	design->refreshDraw();
}

void frmDatabaseDesigner::OnNewModel(wxCommandEvent& event)
{
	design->eraseModel();
}


void frmDatabaseDesigner::OnModelGeneration(wxCommandEvent& event)
{
	sqltext->SetValue(design->generateModel());
}


///////////////////////////////////////////////////////


bool databaseDesignerBaseFactory::CheckEnable(pgObject *obj)
{
    return obj && obj->GetDatabase() && obj->GetDatabase()->GetConnected();
}


wxWindow *databaseDesignerBaseFactory::StartDialogDesigner(frmMain *form, pgObject *obj, const wxString &sql)
{
    frmDatabaseDesigner *fd = new frmDatabaseDesigner(form, wxEmptyString);
    fd->Go();
    return fd;
}


databaseDesignerFactory::databaseDesignerFactory(menuFactoryList *list, wxMenu *mnu, ctlMenuToolbar *toolbar) : databaseDesignerBaseFactory(list)
{
	mnu->Append(id, _("&Database Designer\tCtrl-F"), _("Create database designs"));
    toolbar->AddTool(id, _("Database Designer\tCtrl-F"), wxBitmap(ddmodel_32_xpm), _("Create database designs."), wxITEM_NORMAL);
}


wxWindow *databaseDesignerFactory::StartDialog(frmMain *form, pgObject *obj)
{
    wxString qry;
    if (settings->GetStickySql())
        qry = obj->GetSql(form->GetBrowser());
    return StartDialogDesigner(form, obj, qry);
}
