//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddModeBrowser.h - Tables Tree of Database Designer.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDMODELBROWSER_H
#define DDMODELBROWSER_H

enum ddBrowserImages
{
	DD_IMG_FIG_DATABASE = 0,
	DD_IMG_FIG_TABLE = 1
};

class ddModelBrowser : public wxTreeCtrl
{
public:
	ddModelBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, ddDatabaseDesign *design);
	~ddModelBrowser();
	wxTreeItemId &createRoot(wxString Name);
	void refreshFromModel();
	
	//	void refreshTables(pgConn *connection);
/*	void setDnDPoint(int x, int y)
	{
		xx = x;
		yy = y;
	};
*/
private:
	void OnItemActivated(wxTreeEvent &event);
	void OnBeginDrag(wxTreeEvent &event);

/*	enum ddTypeSchema	
	{
		DD_CATALOG,
		DD_OTHER
	};
*/
	wxTreeItemId rootNode;
//	void OnItemActivated(wxTreeEvent &event);
//	void OnBeginDrag(wxTreeEvent &event);
//	wxString NumToStr(OID value);
	ddDatabaseDesign *ownerDesign;
	wxImageList *imageList;
//	int xx, yy;

	DECLARE_EVENT_TABLE()
};
#endif
