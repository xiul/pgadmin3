//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddChangeConnectionStartHandle.cpp - Handle to allow change connected figure at start of connection figure
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/handles/ddChangeConnectionStartHandle.h"
#include "dd/wxhotdraw/utilities/ddPoint.h"

ddChangeConnectionStartHandle::ddChangeConnectionStartHandle(ddLineConnection *owner):
ddChangeConnectionHandle(owner)
{
}

ddChangeConnectionStartHandle::~ddChangeConnectionStartHandle()
{
}

ddPoint& ddChangeConnectionStartHandle::locate()
{
	return connection->getStartPoint();
}

ddIConnector* ddChangeConnectionStartHandle::target()
{
	return connection->getStartConnector();
}

void ddChangeConnectionStartHandle::connect(ddIConnector *connector)
{
	connection->connectStart(connector);
}

void ddChangeConnectionStartHandle::disconnect()
{
	connection->disconnectStart();
}

bool ddChangeConnectionStartHandle::isConnectionPossible(ddIFigure *figure)
{
	if(!figure->includes(connection) && figure->canConnect() && connection->canConnectStart(figure))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ddChangeConnectionStartHandle::setPoint(ddPoint p)
{
	connection->setStartPoint(p);
}