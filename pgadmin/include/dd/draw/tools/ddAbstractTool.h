//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractTool.h - An abstract tool to allow creation of all tools
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDABSTRACTTOOL_H
#define DDABSTRACTTOOL_H

#include "dd/draw/main/ddObject.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/main/ddDrawingEditor.h"


class ddAbstractTool : public ddITool
{
public:
	ddAbstractTool(ddDrawingEditor *editor);
    ~ddAbstractTool();

	void setAnchorCoords(int x, int y);
	
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseMove(ddMouseEvent& event);
	virtual void mouseDrag(ddMouseEvent& event);
	virtual void keyDown(wxKeyEvent& event);
	virtual void keyUp(wxKeyEvent& event);
	ddDrawingEditor* getDrawingEditor();

protected:
	int anchorX, anchorY;
private:
	ddDrawingEditor *ownerEditor;

};
#endif
