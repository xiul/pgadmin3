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

#include "dd/dditems/figures/ddTextTableItemFigure.h"
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/dditems/figures/ddTableFigure.h"

// Icons
#include "images/ddmodel-32.xpm"
#include "images/file_new.pngc"
#include "images/table.pngc"
#include "images/ddRemoveTable2.xpm"
#include "images/continue.pngc"
#include "images/help.pngc"

BEGIN_EVENT_TABLE(frmDatabaseDesigner, pgFrame)
EVT_MENU(MNU_NEW,               frmDatabaseDesigner::OnNewModel)
EVT_MENU(MNU_ADDTABLE,          frmDatabaseDesigner::OnAddTable)
EVT_MENU(MNU_DELETETABLE,       frmDatabaseDesigner::OnDeleteTable)
EVT_MENU(MNU_ADDCOLUMN,         frmDatabaseDesigner::OnAddColumn)
EVT_MENU(MNU_GENERATEMODEL,     frmDatabaseDesigner::OnModelGeneration)
EVT_CLOSE(                      frmDatabaseDesigner::OnClose)
END_EVENT_TABLE()

 frmDatabaseDesigner::frmDatabaseDesigner(frmMain *form, const wxString& _title, pgConn *conn)
:pgFrame(NULL, _title)
{
	mainForm=form;
    SetTitle(wxT("Database Designer"));
    SetIcon(wxIcon(ddmodel_32_xpm));

	RestorePosition(100, 100, 600, 500, 450, 300);
	SetMinSize(wxSize(450,300));
    
    // connection
    connection = conn;

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
    toolBar->AddTool(MNU_NEW, _("New"), *file_new_png_bmp, _("New database design"), wxITEM_NORMAL);
    toolBar->AddTool(MNU_ADDTABLE, _("Add Table"), *table_png_bmp, _("Add empty table to the current model"), wxITEM_NORMAL);
    toolBar->AddTool(MNU_DELETETABLE, _("Delete Table"), wxBitmap(ddRemoveTable2_xpm), _("Delete selected table"), wxITEM_NORMAL);
    toolBar->AddTool(MNU_ADDCOLUMN, _("Add Column"), *table_png_bmp, _("Add new column to the selected table"), wxITEM_NORMAL);
	toolBar->AddTool(MNU_GENERATEMODEL, _("Generate Model"), *continue_png_bmp, _("Generate SQL for the current model"), wxITEM_NORMAL);
	toolBar->AddSeparator();
    toolBar->AddTool(MNU_HELP, _("Help"), *help_png_bmp, _("Display help"), wxITEM_NORMAL);
    toolBar->Realize();

    // Add the database designer
	design = new ddDatabaseDesign(this);

    // Now, the scratchpad
    sqltext = new wxTextCtrl(this, -1, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxHSCROLL);

    // Add the panes
    manager.AddPane(design->getView(),
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
	
	if (mainForm)
		mainForm->RemoveFrame(this);

    if (connection)
    {
        if (connection->IsAlive())
            delete connection;
    }
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
    wxTextEntryDialog *nameDialog = new wxTextEntryDialog(this,
        wxT("New table name"), wxT("Add table"), design->getNewTableName());
    int answer = nameDialog->ShowModal();
	if (answer == wxID_OK)
    {
        ddTableFigure *newTable = new ddTableFigure(nameDialog->GetValue(),
            rand()%90+200, rand()%90+140);
        design->addTable(newTable);
        design->refreshDraw();
    }
    delete nameDialog;
}

void frmDatabaseDesigner::OnDeleteTable(wxCommandEvent& event)
{
    design->removeSelectedObjects(100);
}

void frmDatabaseDesigner::OnAddColumn(wxCommandEvent& event)
{
    ddTableFigure *table = design->getSelectedTable();
    wxTextEntryDialog *nameDialog;
    int answer;
    wxString tmpString;
    
    if (table)
    {
        nameDialog = new wxTextEntryDialog(this, wxT("New column name"), wxT("Add a column"), wxT("NewColumn"));
        answer = nameDialog->ShowModal();
        if (answer == wxID_OK)
        {
            tmpString = nameDialog->GetValue();
            table->addColumn(new ddColumnFigure(tmpString, table));
        }
        delete nameDialog;
    }
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
    frmDatabaseDesigner *fd = new frmDatabaseDesigner(form, wxEmptyString, NULL);
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
