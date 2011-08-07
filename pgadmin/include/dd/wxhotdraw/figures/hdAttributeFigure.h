//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// hdAbstractFigure.h - Base class for all figures with attributes (line size, fonts and others)
//
//////////////////////////////////////////////////////////////////////////

#ifndef hdATTRIBUTEFIGURE_H
#define hdATTRIBUTEFIGURE_H

// wxWindows headers
#include "dd/wxhotdraw/figures/hdAbstractFigure.h"
#include "dd/wxhotdraw/figures/hdAttribute.h"
#include "dd/wxhotdraw/main/hdObject.h"
#include <wx/arrstr.h>

// App headers
#include "dd/wxhotdraw/figures/defaultAttributes/hdFillAttribute.h"
#include "dd/wxhotdraw/figures/defaultAttributes/hdFontAttribute.h"
#include "dd/wxhotdraw/figures/defaultAttributes/hdFontColorAttribute.h"
#include "dd/wxhotdraw/figures/defaultAttributes/hdLineAttribute.h"

class hdAttributeFigure : public hdAbstractFigure
{
public:
	hdAttributeFigure();
	~hdAttributeFigure();

	void draw(wxBufferedDC &context, hdDrawingView *view);
	void drawSelected(wxBufferedDC &context, hdDrawingView *view);
	void reapplyAttributes(wxBufferedDC &context, hdDrawingView *view);
	void reapplySelAttributes(wxBufferedDC &context, hdDrawingView *view);

	void initializeDefaultAttributes();

	//Draw attributes
	hdFontAttribute *fontAttribute;
	hdFontColorAttribute *fontColorAttribute;
	hdFillAttribute *fillAttribute;
	hdLineAttribute *lineAttribute;
	//Draw selected attributes
	hdFontAttribute *fontSelAttribute;
	hdFontColorAttribute *fontSelColorAttribute;
	hdFillAttribute *fillSelAttribute;
	hdLineAttribute *lineSelAttribute;
protected:

private:

};
#endif
