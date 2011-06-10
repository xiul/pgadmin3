//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddLineConnection.h - Base class for line connection figure
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDLINECONNECTION_H
#define DDLINECONNECTION_H
#include "dd/wxhotdraw/figures/wxhdPolyLineFigure.h"
#include "dd/wxhotdraw/connectors/wxhdIConnector.h"
#include "dd/wxhotdraw/utilities/wxhdPoint.h"
#include "dd/wxhotdraw/handles/wxhdIHandle.h"

class ddLineConnection : public ddPolyLineFigure
{
public:
	ddLineConnection();
	ddLineConnection(ddIFigure *figure1, ddIFigure *figure2);
	~ddLineConnection();

	virtual void connectStart(ddIConnector *start);
	virtual void connectEnd(ddIConnector *end);
	virtual void disconnectStart();
	virtual void disconnectEnd();
	virtual void updateConnection();
	virtual bool canConnectStart(ddIFigure *figure);
	virtual bool canConnectEnd(ddIFigure *figure);
	virtual bool canConnect();
	virtual void setPointAt (int index, int x, int y);
	virtual ddCollection* handlesEnumerator();
	virtual void basicMoveBy(int x, int y);
	
	virtual void onFigureChanged(ddIFigure *figure);

	virtual ddIConnector* getStartConnector();
	virtual ddIConnector* getEndConnector();
	virtual void setStartConnector(ddIConnector* connector);
	virtual void setEndConnector(ddIConnector* connector);
	virtual ddIFigure* getStartFigure();
	virtual ddIFigure* getEndFigure();
	virtual ddIHandle* getStartHandle();
	virtual ddIHandle* getEndHandle();
	virtual void addPoint (int x, int y);
	virtual void insertPointAt (int index, int x, int y);

protected:
	virtual void updateHandlesIndexes();
	virtual void connectFigure (ddIConnector *connector);
	virtual void disconnectFigure (ddIConnector *connector);
	ddIConnector *startConnector;
	ddIConnector *endConnector;

private:
	ddIHandle *changeConnStartHandle;
	ddIHandle *changeConnEndHandle; 
};
#endif
