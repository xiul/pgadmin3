//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddChangeConnectionEndHandle.cpp - Handle to allow change connected figure at end of connection figure
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/handles/ddChangeConnectionEndHandle.h"
#include "dd/draw/utilities/ddPoint.h"

ddChangeConnectionEndHandle::ddChangeConnectionEndHandle(ddLineConnection *owner):
ddChangeConnectionHandle(owner)
{
}

ddChangeConnectionEndHandle::~ddChangeConnectionEndHandle()
{
}

ddPoint& ddChangeConnectionEndHandle::locate()
{
	return connection->getEndPoint();
}

ddIConnector* ddChangeConnectionEndHandle::target()
{
	return connection->getEndConnector();
}

void ddChangeConnectionEndHandle::connect(ddIConnector *connector)
{
	connection->connectEnd(connector);
}

void ddChangeConnectionEndHandle::disconnect()
{
	connection->disconnectEnd();
}

bool ddChangeConnectionEndHandle::isConnectionPossible(ddIFigure *figure)
{
	if(!figure->includes(connection) && figure->canConnect() && connection->canConnectEnd(figure))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ddChangeConnectionEndHandle::setPoint(ddPoint p)
{
	connection->setEndPoint(p);
}