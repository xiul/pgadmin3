//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ctlResultGrid.h - debugger
//
//////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// class ctlResultGrid
//
//	A ctlResultGrid is a grid control that knows how to display that result set
//	generated by a PostgreSQL query. In the workstation application, a ctlResultGrid
//	is a child of the notebook owned by a ctlTabWindow.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef CTLRESULTGRID_H
#define CTLRESULTGRID_H

#include <wx/grid.h>

class ctlResultGrid : public wxGrid
{
	DECLARE_CLASS( ctlResultGrid )

public:
	ctlResultGrid( wxWindow *parent, wxWindowID id );

	void	fillGrid( PGresult *result );	// Copy a result set into the grid
};

#endif
