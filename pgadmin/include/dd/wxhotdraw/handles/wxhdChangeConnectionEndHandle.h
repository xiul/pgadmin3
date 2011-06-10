//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddChangeConnectionEndHandle.h - Handle to allow change connected figure at end of connection figure
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCHANGECONNECTIONENDHANDLE_H
#define DDCHANGECONNECTIONENDHANDLE_H

#include "dd/wxhotdraw/handles/wxhdChangeConnectionHandle.h"
#include "dd/wxhotdraw/figures/wxhdLineConnection.h"

class ddChangeConnectionEndHandle : public ddChangeConnectionHandle
{
public:
	ddChangeConnectionEndHandle(ddLineConnection *owner);
    ~ddChangeConnectionEndHandle();
	virtual ddPoint& locate();
	virtual ddIConnector* target();
	virtual void disconnect();
	virtual void connect(ddIConnector *connector);
	virtual bool isConnectionPossible(ddIFigure *figure);
	virtual void setPoint(ddPoint p);
};
#endif
