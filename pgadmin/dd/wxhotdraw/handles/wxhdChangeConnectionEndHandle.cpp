//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdChangeConnectionEndHandle.cpp - Handle to allow change connected figure at end of connection figure
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/wxhotdraw/handles/wxhdChangeConnectionEndHandle.h"
#include "dd/wxhotdraw/utilities/wxhdPoint.h"

wxhdChangeConnectionEndHandle::wxhdChangeConnectionEndHandle(wxhdLineConnection *owner):
wxhdChangeConnectionHandle(owner)
{
}

wxhdChangeConnectionEndHandle::~wxhdChangeConnectionEndHandle()
{
}

wxhdPoint& wxhdChangeConnectionEndHandle::locate()
{
	return connection->getEndPoint();
}

wxhdIConnector* wxhdChangeConnectionEndHandle::target()
{
	return connection->getEndConnector();
}

void wxhdChangeConnectionEndHandle::connect(wxhdIConnector *connector)
{
	connection->connectEnd(connector);
}

void wxhdChangeConnectionEndHandle::disconnect()
{
	connection->disconnectEnd();
}

bool wxhdChangeConnectionEndHandle::isConnectionPossible(wxhdIFigure *figure)
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

void wxhdChangeConnectionEndHandle::setPoint(wxhdPoint p)
{
	connection->setEndPoint(p);
}