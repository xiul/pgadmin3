//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRelationshipFigure.h - Figure to draw foreign keys between tables.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDRELATIONSHIPFIGURE_H
#define DDRELATIONSHIPFIGURE_H
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddColumnFigure.h"

enum
{
    MNU_FKEYFROMPKEY = 0,
	MNU_FKEYFROMUKEY,
	MNU_MANDATORYRELATIONSHIP,
	MNU_IDENTIFYINGRELATIONSHIP,
	MNU_1MRELATIONSHIP,
	MNU_11RELATIONSHIP,
	MNU_DELETERELATIONSHIP
};

class ddRelationshipItem;

WX_DECLARE_STRING_HASH_MAP( ddRelationshipItem*, columnsHashMap );


class ddRelationshipFigure : public ddLineConnection
{
public:
	ddRelationshipFigure();
	ddRelationshipFigure(ddIFigure *figure1, ddIFigure *figure2);
	~ddRelationshipFigure();
    virtual void createMenu(wxMenu &mnu);
	void updateForeignKey();
	void removeForeignKeys();
	bool getIdentifying();
	bool getOneToMany();
	bool getMandatory();
	void setOptionAtForeignKeys(ddColumnOptionType type);
	void setKindAtForeignKeys(ddColumnType type);
	virtual void connectEnd(ddIConnector *end);
	virtual void connectStart(ddIConnector *start);
	void disconnectStart();
	void disconnectEnd();
	wxString generateSQL();
protected:

private:
	virtual void OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view);
	wxArrayString strings;
	bool fkFromPk;
	bool fkMandatory;
	bool fkOneToMany;
	bool fkIdentifying;
	int ukIndex;
	columnsHashMap chm;
	ddTableFigure *disconnectedEndTable;
};



class ddRelationshipItem : public ddObject
{
public:
	ddRelationshipItem(ddRelationshipFigure *owner, ddColumnFigure *originalColumn, ddTableFigure *destination, ddColumnOptionType type, ddColumnType colType);
	~ddRelationshipItem();
	wxString originalStartColName;
	ddColumnFigure *original;
	ddColumnFigure *fkColumn;
	ddTableFigure *destinationTable;

	wxString autoGenerateNameForFk();
	void syncAutoFkName();
private:
	ddRelationshipFigure *ownerRel;
};

#endif
