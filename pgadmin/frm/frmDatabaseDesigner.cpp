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
#include "images/file_open.xpm"
#include "images/file_save.xpm"
#include "images/table.xpm"
#include "images/continue.xpm"
#include "images/help.xpm"


BEGIN_EVENT_TABLE(frmDatabaseDesigner, pgFrame)
EVT_CLOSE(                      frmDatabaseDesigner::OnClose)
EVT_MENU(11345,               frmDatabaseDesigner::OnAddTable)
EVT_MENU(11346,               frmDatabaseDesigner::OnModelGeneration)
EVT_MENU(MNU_NEW,               frmDatabaseDesigner::OnNewModel)
END_EVENT_TABLE()

 frmDatabaseDesigner::frmDatabaseDesigner(frmMain *form, const wxString& _title) //DD-TODO: pgConn *_conn, const wxString& query, const wxString& file)
:pgFrame(NULL, _title)
{

	//DD-todo: this is just a development window and SHOULD BE FINISHED IN A FUTURE BUT THIS IS NOT PRIORITY RIGHT NOW
	mainForm=form;

	//RestorePosition(100, 100, 600, 500, 450, 300);
    // notify wxAUI which frame to use
    manager.SetManagedWindow(this);
    manager.SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_TRANSPARENT_DRAG);


	SetMinSize(wxSize(450,300));
	SetSize(wxSize(1024,768));
	wxWindowBase::SetFont(settings->GetSystemFont());


	menuBar = new wxMenuBar();

    wxMenu *fileMenu = new wxMenu();
    wxMenu *recentFileMenu = new wxMenu();
    fileMenu->Append(MNU_NEW, _("&New window\tCtrl-N"), _("Open a new database designer window"));
    fileMenu->Append(MNU_OPEN, _("&Open...\tCtrl-O"),   _("Open a database designer file"));
    fileMenu->Append(MNU_SAVE, _("&Save\tCtrl-S"),      _("Save current file"));
    fileMenu->AppendSeparator();
    fileMenu->Append(MNU_EXPORT, _("&Export..."),  _("Export data to file"));
    fileMenu->AppendSeparator();
    fileMenu->Append(MNU_RECENT, _("&Recent files"), recentFileMenu);
    fileMenu->Append(MNU_EXIT, _("E&xit\tCtrl-W"), _("Exit database designer window"));

    menuBar->Append(fileMenu, _("&File"));

	wxMenu *helpMenu=new wxMenu();
    helpMenu->Append(MNU_CONTENTS, _("&Help"),                 _("Open the helpfile."));
    helpMenu->Append(MNU_HELP, _("&SQL Help\tF1"),                _("Display help on SQL commands."));

    menuBar->Append(helpMenu, _("&Help"));

	SetMenuBar(menuBar);


	int iWidths[6] = {0, -1, 40, 150, 80, 80};
	wxStatusBar *statusBar =CreateStatusBar(6);
    SetStatusBarPane(-1);
    SetStatusWidths(6, iWidths);
    SetStatusText(wxString(wxT("ready")), 1); //STATUSPOS_MSGS

	
    toolBar = new ctlMenuToolbar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);

    toolBar->SetToolBitmapSize(wxSize(16, 16));

	toolBar->AddTool(MNU_NEW, _("New"), wxBitmap(file_new_xpm), _("New database design"), wxITEM_NORMAL);
	toolBar->AddTool(MNU_OPEN, _("Open"), wxBitmap(file_open_xpm), _("Open a database designer file"), wxITEM_NORMAL);
    toolBar->AddTool(MNU_SAVE, _("Save"), wxBitmap(file_save_xpm), _("Save current file"), wxITEM_NORMAL);
	toolBar->AddSeparator();
	toolBar->AddTool(11345, _("Add Table"), wxBitmap(table_xpm), _("Add empty table a current model"), wxITEM_NORMAL);
	toolBar->AddTool(11346, _("Generate Model"), wxBitmap(continue_xpm), _("Generate SQL for current model"), wxITEM_NORMAL);
	toolBar->AddSeparator();
    toolBar->AddTool(MNU_HELP, _("Help"), wxBitmap(help_xpm), _("Display help on SQL commands."), wxITEM_NORMAL);
    toolBar->Realize();

//	wxNotebook *notebook = new wxNotebook(this, CTL_NTBKCENTER, wxDefaultPosition, wxDefaultSize);
//	wxSplitterWindow *ddMainContainer = new wxSplitterWindow(notebook,GQB_HORZ_SASH,wxDefaultPosition,wxDefaultSize,wxSP_3D);	
	wxNotebook *notebook = new wxNotebook(this, 1001, wxDefaultPosition, wxDefaultSize);
	wxSplitterWindow *ddMainContainer = new wxSplitterWindow(notebook,1002,wxDefaultPosition,wxDefaultSize,wxSP_3D);
	wxPanel *pnlQuery = new wxPanel(ddMainContainer);
	wxPanel *pnlQuery2 = new wxPanel(notebook);

	design = NULL;
	design = new ddDatabaseDesign(ddMainContainer);

	ddMainContainer->SplitVertically(pnlQuery,design->getView());
    ddMainContainer->UpdateSize();
    ddMainContainer->SetSashPosition(50,true);
    ddMainContainer->SetMinimumPaneSize(10);
    ddMainContainer->UpdateSize();

	notebook->AddPage(ddMainContainer, _("Database Designer"));
	notebook->AddPage(pnlQuery2, _("Empty"));
	notebook->SetSelection(0);

	manager.AddPane(notebook, wxAuiPaneInfo().Name(wxT("sqlQuery")).Caption(_("Database Designer")).Center().CaptionVisible(false).CloseButton(false).MinSize(wxSize(200,100)).BestSize(wxSize(350,200)));
	manager.AddPane(toolBar, wxAuiPaneInfo().Name(wxT("toolBar")).Caption(_("Tool bar")).ToolbarPane().Top().LeftDockable(false).RightDockable(false));

	manager.Update();
}

 frmDatabaseDesigner::~frmDatabaseDesigner(){
	//DD-TODO: free memory objects
	//closing = true;
	// Uninitialize wxAUIManager
	manager.UnInit();
	
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

	ddTableFigure *newTable = new ddTableFigure(design->getNewTableName(),rand()%90+200,rand()%90+140);
	design->addTable(newTable);
	design->refreshDraw();
}

void frmDatabaseDesigner::OnNewModel(wxCommandEvent& event)
{
	design->eraseModel();
}

void frmDatabaseDesigner::OnModelGeneration(wxCommandEvent& event)
{
	ddTextEditor *editor = new ddTextEditor(design->generateModel());
	editor->Show();
}


 ///////////////////////////////////////////////////////

 bool databaseDesignerBaseFactory::CheckEnable(pgObject *obj)
{
    return obj && obj->GetDatabase() && obj->GetDatabase()->GetConnected();
}

wxWindow *databaseDesignerBaseFactory::StartDialogDesigner(frmMain *form, pgObject *obj, const wxString &sql)
{
    pgDatabase *db=obj->GetDatabase();
    wxString applicationname = wxT("pgAdmin - Database Designer");
    pgConn *conn = db->CreateConn(applicationname);
    if (conn)
    {
        frmDatabaseDesigner *fd= new frmDatabaseDesigner(form, wxEmptyString); //, conn, sql);
        fd->Go();
        return fd;
    }
    return 0;
}

databaseDesignerFactory::databaseDesignerFactory(menuFactoryList *list, wxMenu *mnu, ctlMenuToolbar *toolbar) : databaseDesignerBaseFactory(list)
{
    //TODO: complete this Ctrl-D by example isn't bind with keys.
	mnu->Append(id, _("&Database Designer\tCtrl-D"), _("Create physical database designs."));
    toolbar->AddTool(id, _("Database Designer\tCtrl-D"), wxBitmap(ddmodel_32_xpm), _("Create physical database designs."), wxITEM_NORMAL);
}

wxWindow *databaseDesignerFactory::StartDialog(frmMain *form, pgObject *obj)
{
    wxString qry;
    if (settings->GetStickySql())
        qry = obj->GetSql(form->GetBrowser());
    return StartDialogDesigner(form, obj, qry);
}

