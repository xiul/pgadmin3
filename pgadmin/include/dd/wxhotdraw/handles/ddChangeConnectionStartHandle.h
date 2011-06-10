//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddChangeConnectionStartHandle.h - Handle to allow change connected figure at start of connection figure
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCHANGECONNECTIONSTARTHANDLE_H
#define DDCHANGECONNECTIONSTARTHANDLE_H

#include "dd/wxhotdraw/handles/ddChangeConnectionHandle.h"
#include "dd/wxhotdraw/figures/ddLineConnection.h"

class ddChangeConnectionStartHandle : public ddChangeConnectionHandle
{
public:
	ddChangeConnectionStartHandle(ddLineConnection *owner);
    ~ddChangeConnectionStartHandle();
	virtual ddPoint& locate();
	virtual ddIConnector* target();
	virtual void disconnect();
	virtual void connect(ddIConnector *connector);
	virtual bool isConnectionPossible(ddIFigure *figure);
	virtual void setPoint(ddPoint p);
};
#endif
