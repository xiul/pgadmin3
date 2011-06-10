//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddRelationshipTerminal.h - Draw inverse arrows at fk terminal based on kind of relationship.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDRELATIONSHIPTERMINAL_H
#define DDRELATIONSHIPTERMINAL_H
#include "dd/wxhotdraw/figures/wxhdLineTerminal.h"
#include "dd/wxhotdraw/utilities/wxhdPoint.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"



class ddRelationshipTerminal : public ddLineTerminal
{
public:
	ddRelationshipTerminal(ddRelationshipFigure *owner, bool endFigureTerminal);
    ~ddRelationshipTerminal();
	virtual ddPoint& draw (wxBufferedDC& context, ddPoint& a, ddPoint& b, ddDrawingView *view);
protected:
	
private:
	double lastFactor;
	ddRelationshipFigure *ownerFigure;
	bool endTerminal;
	ddPoint value;
};
#endif
