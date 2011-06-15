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
#include "dd/wxhotdraw/figures/wxhdLineConnection.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddColumnFigure.h"

enum
{
	MNU_MANDATORYRELATIONSHIP = 0,
	MNU_IDENTIFYINGRELATIONSHIP,
	MNU_1MRELATIONSHIP,
	MNU_DELETERELATIONSHIP,
	MNU_FKCONSTRAINTNAME,
	MNU_FKMATCHTYPESIMPLE,
	MNU_FKMATCHTYPEFULL,
	MNU_FKONDELETENOACTION,
	MNU_FKONDELETERESTRICT,
	MNU_FKONDELETECASCADE,
	MNU_FKONDELETESETNULL,
	MNU_FKONDELETESETDEFAULT,
	MNU_FKONUPDATENOACTION,
	MNU_FKONUPDATERESTRICT,
	MNU_FKONUPDATECASCADE,
	MNU_FKONUPDATESETNULL,
	MNU_FKONUPDATESETDEFAULT,
	MNU_FKEYFROMPKEY,
	MNU_FKEYFROMUKEYBASE  //This constant should be always the last one to allow hack of multiple uk selection in submenu
};

enum actionKind
{
	FK_ACTION_NO = 600,
	FK_RESTRICT,
	FK_CASCADE,
	FK_SETNULL,
	FK_SETDEFAULT
};
class ddRelationshipItem;

WX_DECLARE_STRING_HASH_MAP( ddRelationshipItem*, columnsHashMap );


class ddRelationshipFigure : public wxhdLineConnection
{
public:
	ddRelationshipFigure();
	ddRelationshipFigure(wxhdIFigure *figure1, wxhdIFigure *figure2);
	~ddRelationshipFigure();
    virtual void createMenu(wxMenu &mnu);
	
	void prepareFkForDelete(ddColumnFigure *column);
	void updateForeignKey();
	void removeForeignKeys();
	bool getIdentifying();
	bool getOneToMany();
	bool getMandatory();
	void setOptionAtForeignKeys(ddColumnOptionType type);
	void setKindAtForeignKeys(ddColumnType type);
	virtual void connectEnd(wxhdIConnector *end);
	virtual void connectStart(wxhdIConnector *start);
	void disconnectStart();
	void disconnectEnd();
	wxString generateSQL();
protected:

private:
	virtual void OnGenericPopupClick(wxCommandEvent& event, wxhdDrawingView *view);
	wxArrayString strings;
	bool firstTimeConnectEnd;
	bool fkFromPk;
	bool fkMandatory;
	bool fkOneToMany;
	bool fkIdentifying;
	bool matchSimple;
	actionKind onUpdateAction, onDeleteAction;
	wxString constraintName;

	int ukIndex;
	columnsHashMap chm;
	ddTableFigure *disconnectedEndTable;
};

#endif
