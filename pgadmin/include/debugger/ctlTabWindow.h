//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ctlTabWindow.h - debugger
//
//////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//	class ctlTabWindow
//
//	The ctlTabWindow class implements the tab control that displays at the
//	bottom of the debugger window.
//
//	A ctlTabWindow object holds a notebook control, a result window (a window
//  that displays the result set generated by a query), and a varWindow (a
//  window that displays the local variables when debugging a PL function).
//
////////////////////////////////////////////////////////////////////////////////

#ifndef CTLTABWINDOW_H
#define CTLTABWINDOW_H

#include <wx/notebook.h>
#include <wx/aui/aui.h>

#include "debugger/ctlVarWindow.h"
#include "debugger/ctlMessageWindow.h"
#include "debugger/ctlStackWindow.h"
#include "debugger/ctlResultGrid.h"

WX_DECLARE_HASH_MAP( int, int, wxIntegerHash, wxIntegerEqual, wsTabHash );

class ctlTabWindow : public ctlAuiNotebook
{
	DECLARE_CLASS( ctlTabWindow )

public:

	ctlTabWindow(wxWindow *parent, wxWindowID id, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxCLIP_CHILDREN | wxSW_3D, const wxString &name = wxT( "layoutWindow" ));

	ctlVarWindow	*getVarWindow( bool create = true );		// Returns a pointer to the local-variables window (creates it if requested)
	ctlVarWindow	*getPkgVarWindow( bool create = true );	// Returns a pointer to the package-variables window (creates it if requested)
	ctlVarWindow	*getParamWindow( bool create = true );		// Returns a pointer to the parameters window (creates it if requested)

	ctlResultGrid	*getResultWindow( void );					// Returns a pointer to the result window (creates it if necessary)
	ctlStackWindow	*getStackWindow( void );					// Returns a pointer to the stack-trace window (creates it if necessary)
	ctlMessageWindow *getMessageWindow( void );					// Returns a pointer to the DBMS messages window (creates it if necessary)
	void	selectTab( wxWindowID id );

private:
	ctlResultGrid	*m_resultWindow;	// Displays the result set from a query
	ctlVarWindow	*m_varWindow;		// Displays the local variables when debugging a PL function
	ctlVarWindow	*m_pkgVarWindow;	// Displays the package variables when debugging a PL function
	ctlStackWindow	*m_stackWindow;		// Displays the current call stack
	ctlVarWindow	*m_paramWindow;		// Displays the parameters when debugging a PL function
	ctlMessageWindow	*m_messageWindow;	// Displays the DBMS messages when debugging a PL function

	wsTabHash	*m_tabMap;		// Map window ID's to tab numbers;
};

#endif
