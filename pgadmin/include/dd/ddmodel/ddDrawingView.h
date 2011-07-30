//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// wxhdDrawingEditor.h - Main class that manages all other classes
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDDRAWINGVIEW_H
#define DDDRAWINGVIEW_H

#include "dd/wxhotdraw/main/wxhdDrawingView.h"

class ddDrawingView : public wxhdDrawingView
{
public:
	ddDrawingView(int diagram, wxWindow *ddParent, wxhdDrawingEditor *editor , wxSize size, wxhdDrawing *drawing);
	//Hack To allow right click menu at canvas without a figure
	virtual void createViewMenu(wxMenu &mnu);
	virtual void OnGenericViewPopupClick(wxCommandEvent &event);
protected:
private:
};

// A drop target that do nothing only accept text, if accept then tree add table to model
class ddDropTarget : public wxTextDropTarget
{
public:
	ddDropTarget(ddDatabaseDesign *sourceDesign, wxhdDrawing *targetDrawing)
	{
		target = targetDrawing;
		source = sourceDesign;

	}
	virtual bool OnDropText(wxCoord x, wxCoord y, const wxString &text)
	{
		ddTableFigure *t = source->getTable(text);
		if(t!=NULL && !target->includes(t))
		{
			target->add(t);
			t->syncInternalsPosAt(target->getView()->getIdx(),x,y);
			source->getEditor()->checkRelationshipsConsistency(target->getView()->getIdx());
			target->getView()->Refresh();
			return true;
		}
		else
		{
			if(target->includes(t))
			{
				wxMessageBox(_("Table exists already at this diagram"),_("Drag and drop warning"), wxICON_EXCLAMATION);
				return true;
			}
			else
				return false;
		}
	}

private:
	wxhdDrawing *target;
	ddDatabaseDesign *source;
};
#endif
