//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddColumnFigure.h - Minimal Composite Figure for a column of a table
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCOLUMNFIGURE_H
#define DDCOLUMNFIGURE_H
#include "dd/wxhotdraw/figures/ddAbstractFigure.h"
#include "dd/dditems/figures/ddColumnKindIcon.h"
#include "dd/dditems/figures/ddColumnOptionIcon.h"
#include "dd/dditems/figures/ddTextTableItemFigure.h"

class ddTableFigure;
class ddRelationshipItem;

//Minimal overhead composite figure
class ddColumnFigure : public ddAbstractFigure
{
public:
	ddColumnFigure(wxString& columnName, ddTableFigure *owner, ddRelationshipItem *sourceFk=NULL);
    ~ddColumnFigure();
	virtual void basicMoveBy(int x, int y);
	virtual void moveTo(int x, int y);
	virtual void setOwnerTable(ddTableFigure *table);
	virtual bool containsPoint(int x, int y);
	virtual ddRect& getBasicDisplayBox();
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual void drawSelected(wxBufferedDC& context, ddDrawingView *view);
	virtual ddIFigure* findFigure(int x, int y);
	virtual ddIFigure* getFigureAt(int pos);
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
	virtual ddTableFigure* getOwnerTable();
	void displayBoxUpdate();
	bool isNull();
	bool isNotNull();
	bool isPrimaryKey();
	bool isUniqueKey();
	bool isUniqueKey(int ukIndex);
	int getUniqueConstraintIndex();
	void setUniqueConstraintIndex(int i);
	bool isPlain();
	void setColumnKind(ddColumnType type, ddDrawingView *view=NULL);
	void setColumnOption(ddColumnOptionType type);
	ddColumnType getColumnKind();
	ddColumnOptionType getColumnOption();
	ddDataType getDataType();
	void setDataType(ddDataType type);
	wxString& getColumnName(bool datatype=false);
	void setColumnName(wxString name);
	bool isForeignKey();
	wxString generateSQL();
	bool isFkNameGenerated();
	void activateGenFkName();
	void deactivateGenFkName();
	ddRelationshipItem* getFkSource();
	int getPrecision();

protected:
	ddColumnKindIcon *leftImage;
	ddColumnOptionIcon *centerImage;
	ddTextTableItemFigure *columnText;
	ddTableFigure *ownerTable;
	bool generateFkName;

private:
	ddRelationshipItem *fkSource;

	
};
#endif
