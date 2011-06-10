//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdChangeConnectionEndHandle.h - Handle to allow change connected figure at end of connection figure
//
//////////////////////////////////////////////////////////////////////////

#ifndef WXHDCHANGECONNECTIONENDHANDLE_H
#define WXHDCHANGECONNECTIONENDHANDLE_H

#include "dd/wxhotdraw/handles/wxhdChangeConnectionHandle.h"
#include "dd/wxhotdraw/figures/wxhdLineConnection.h"

class wxhdChangeConnectionEndHandle : public wxhdChangeConnectionHandle
{
public:
	wxhdChangeConnectionEndHandle(wxhdLineConnection *owner);
    ~wxhdChangeConnectionEndHandle();
	virtual wxhdPoint& locate();
	virtual wxhdIConnector* target();
	virtual void disconnect();
	virtual void connect(wxhdIConnector *connector);
	virtual bool isConnectionPossible(wxhdIFigure *figure);
	virtual void setPoint(wxhdPoint p);
};
#endif
