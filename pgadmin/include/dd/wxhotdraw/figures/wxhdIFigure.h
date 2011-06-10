//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddIFigure.h - Base class for all figures
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDIFIGURE_H
#define DDIFIGURE_H
#include "dd/wxhotdraw/utilities/wxhdRect.h"
#include "dd/wxhotdraw/main/wxhdObject.h"
#include "dd/wxhotdraw/utilities/wxhdCollection.h"
#include "dd/wxhotdraw/handles/wxhdIHandle.h"

class ddITool;
class ddDrawingEditor;
class ddIConnector;
class ddITool;

class ddIFigure : public ddObject
{
public:
	ddIFigure();
    ~ddIFigure();

	virtual ddRect& displayBox();
	virtual ddRect& getBasicDisplayBox();
	virtual void draw (wxBufferedDC& context, ddDrawingView *view);
	virtual void drawSelected (wxBufferedDC& context, ddDrawingView *view);
	virtual ddCollection* handlesEnumerator();
	virtual void addHandle (ddIHandle *handle);
	virtual void removeHandle (ddIHandle *handle);
	virtual ddIConnector* connectorAt (int x, int y);
	virtual void moveBy(int x, int y);
	virtual void moveTo(int x, int y);
	virtual bool containsPoint(int x, int y);
	virtual bool isSelected();
	virtual void setSelected(bool value);
	virtual bool includes(ddIFigure *figure);
	virtual bool canConnect()=0;
	virtual void onFigureChanged(ddIFigure *figure)=0;
	virtual void addObserver (ddIFigure *observer);
	virtual void removeObserver (ddIFigure *observer);	
	virtual ddIteratorBase* observersEnumerator();
	virtual void setKindId(int objectId=-1);
	virtual int getKindId();
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);

protected:
	ddRect basicDisplayBox;
	ddCollection *handles;
	ddCollection *observers;
	void setDefaultPen(wxPen& pen);
	void setDefaultSelectedPen(wxPen& pen);
	void setDefaultBrush(wxBrush& brush);
	void setDefaultSelectedBrush(wxBrush& brush);
	wxPen defaultPen, defaultSelectedPen;
	wxBrush defaultBrush, defaultSelectedBrush;
	ddIConnector *connector;
private:
	bool selected;
	int kindHiddenId;

};
#endif
