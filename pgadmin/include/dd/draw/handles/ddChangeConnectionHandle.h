//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddChangeConnectionHandle.h - Base Handle to allow change connected figures at connection figures 
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCHANGECONNECTIONHANDLE_H
#define DDCHANGECONNECTIONHANDLE_H

#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/connectors/ddIConnector.h"
#include "dd/draw/main/ddDrawing.h"

class ddChangeConnectionHandle : public ddIHandle
{
public:
	ddChangeConnectionHandle(ddLineConnection *owner);
    ~ddChangeConnectionHandle();
	
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual wxCursor createCursor();
	virtual void invokeStart(ddMouseEvent& event, ddDrawingView *view);
	virtual void invokeStep(ddMouseEvent& event, ddDrawingView *view);
	virtual void invokeEnd(ddMouseEvent& event, ddDrawingView *view);
	virtual ddIConnector* target()=0;
	virtual void disconnect()=0;
	virtual void connect(ddIConnector *connector)=0;
	virtual void setPoint(ddPoint p)=0;
	virtual bool isConnectionPossible(ddIFigure *figure)=0;
	ddIFigure* findConnectableFigure(int x, int y, ddDrawing *drawing);
	ddIConnector* findConnectionTarget(int x, int y, ddDrawing *drawing);
protected:
	ddLineConnection *connection;
	ddIFigure *targetFigure;
private:
	ddIConnector *originalTarget;
};
#endif
