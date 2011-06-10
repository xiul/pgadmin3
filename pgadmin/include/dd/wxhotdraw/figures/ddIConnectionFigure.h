//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddIConnectionFigure.h - Base class for all connection figures
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDICONNECTIONFIGURE_H
#define DDICONNECTIONFIGURE_H
#include "dd/wxhotdraw/figures/ddIFigure.h"
#include "dd/wxhotdraw/connectors/ddIConnector.h"
#include "dd/wxhotdraw/utilities/ddPoint.h"
#include "dd/wxhotdraw/handles/ddIHandle.h"


class ddIConnector;

class ddIConnectionFigure : public ddIFigure
{
public:

	virtual void connectStart(ddIConnector *start)=0;
	virtual void connectEnd(ddIConnector *end)=0;
	virtual void updateConnection()=0;
	virtual void disconnectStart()=0;
	virtual void disconnectEnd()=0;
	virtual bool canConnectStart(ddIFigure *figure)=0;
	virtual bool canConnectEnd(ddIFigure *figure)=0;
	virtual ddPoint* pointAt(int index)=0;
	virtual void splitSegment(int x, int y)=0;

	virtual int pointCount()=0;
	virtual ddIConnector* getStartConnector()=0;
	virtual ddIConnector* getEndConnector()=0;
	virtual void setStartConnector(ddIConnector* connector)=0;
	virtual void setEndConnector(ddIConnector* connector)=0;
	virtual ddPoint* getStartPoint()=0;
	virtual void setStartPoint(ddPoint *point)=0;
	virtual ddPoint* getEndPoint()=0;
	virtual void setEndPoint(ddPoint *point)=0;
	virtual ddIFigure* getStartFigure()=0;
	virtual ddIFigure* getEndFigure()=0;
	virtual ddIHandle* getStartHandle()=0;
	virtual ddIHandle* getEndHandle()=0;

protected:

private:

};
#endif
