//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddTableFigure.cpp - Draw table figure of a model
//
//////////////////////////////////////////////////////////////////////////// 


#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddTextTableItemFigure.h"
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/draw/main/ddDrawingView.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/dditems/handles/ddAddColButtonHandle.h"
#include "dd/dditems/locators/ddAddColLocator.h"
#include "dd/dditems/handles/ddRemoveColButtonHandle.h"
#include "dd/dditems/locators/ddRemoveColLocator.h"
#include "dd/dditems/handles/ddAddFkButtonHandle.h"
#include "dd/dditems/locators/ddAddFkLocator.h"
#include "dd/dditems/handles/ddRemoveTableButtonHandle.h"
#include "dd/dditems/locators/ddRemoveTableLocator.h"
#include "dd/dditems/handles/ddMinMaxTableButtonHandle.h"
#include "dd/dditems/locators/ddMinMaxTableLocator.h"
#include "dd/dditems/handles/ddScrollBarHandle.h"
#include "dd/dditems/locators/ddScrollBarTableLocator.h"
#include "dd/dditems/handles/ddSouthTableSizeHandle.h"
#include "dd/dditems/locators/ddTableBottomLocator.h"
#include "dd/draw/utilities/ddGeometry.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"
#include "dd/draw/connectors/ddLocatorConnector.h"

//Images
#include "images/ddAddColumn.xpm"
#include "images/ddRemoveColumn.xpm"
#include "images/ddAddForeignKey.xpm"
#include "images/ddMaximizeTable.xpm"
#include "images/ddMinimizeTable.xpm"
#include "images/ddRemoveTable.xpm"

/*
All figures title, colums, indexes are store at same array to improve performance in the following order:
	[0] = table border rect
	[1] = table title
	[2] = first column index
	[maxColIndex] = last column index
	[minIdxIndex] = first index index
	[maxIdxIndex] = last index index
*/

ddTableFigure::ddTableFigure(wxString tableName, int x, int y, wxString shortName):
ddCompositeFigure()
{
	setKindId(ddTableFig);
	internalPadding = 2;
	externalPadding = 4;
	deleteColumnMode=false;

	//Set table size, width and position
	rectangleFigure = new ddRectangleFigure();
	rectangleFigure->moveTo(x,y);
	add(rectangleFigure);
	
	tableTitle = new ddTextTableItemFigure(tableName,dt_null,NULL);
	tableTitle->setOwnerTable(this);
	tableTitle->setEditable(true);
	tableTitle->moveTo(x,y);
	tableTitle->disablePopUp();
	tableTitle->setShowDataType(false);
	add(tableTitle);
	tableTitle->setAlias(shortName);  //Should be here to avoid a null pointer bug
	tableTitle->moveTo(rectangleFigure->getBasicDisplayBox().x+internalPadding*2,rectangleFigure->getBasicDisplayBox().y+internalPadding/2);

	//Intialize handles
	wxBitmap image=wxBitmap(ddAddColumn_xpm);
	wxSize valueSize=wxSize(8,8);
	figureHandles->addItem(new ddAddColButtonHandle((ddIFigure *)this,(ddILocator *)new ddAddColLocator(), image, valueSize));
	image=wxBitmap(ddRemoveColumn_xpm);
	figureHandles->addItem(new ddRemoveColButtonHandle((ddIFigure *)this,(ddILocator *)new ddRemoveColLocator(), image,valueSize));
	image=wxBitmap(ddAddForeignKey_xpm);
	figureHandles->addItem(new ddAddFkButtonHandle((ddIFigure *)this,(ddILocator *)new ddAddFkLocator(), image,valueSize));
	image=wxBitmap(ddRemoveTable_xpm);
	figureHandles->addItem(new ddRemoveTableButtonHandle((ddIFigure *)this,(ddILocator *)new ddRemoveTableLocator(), image,valueSize));
	image=wxBitmap(ddMinimizeTable_xpm);
	wxBitmap image2=wxBitmap(ddMaximizeTable_xpm);
	figureHandles->addItem(new ddMinMaxTableButtonHandle((ddIFigure *)this,(ddILocator *)new ddMinMaxTableLocator(), image, image2,valueSize));
	figureHandles->addItem(new ddSouthTableSizeHandle(this,(ddILocator *)new ddTableBottomLocator()));

	//Intialize special handle
	valueSize=wxSize(10,colsRect.GetSize().GetHeight());
	scrollbar=new ddScrollBarHandle(this,(ddILocator *)new ddScrollBarTableLocator(),valueSize);

	fromSelToNOSel=false;
	
	//Intialize columns window (min is always 1 in both, with or without cols & indxs)
	colsRowsSize = 0;
	colsWindow = 0;
	idxsRowsSize = 0;
	idxsWindow = 0;
	
	//Initialize indexes (pointers to array segments)
	maxColIndex=2;
	minIdxIndex=2;  
	maxIdxIndex=2;

	//Initialize position where start to draw columns & indexes, this is the value to allow scrollbars
	beginDrawCols=2;
	beginDrawIdxs=2;

	//Initialize
	pkName=wxT("NewTable_pk");
	ukNames.clear();

	updateTableSize();
}

ddTableFigure::~ddTableFigure()
{
	if(scrollbar)
	{
		if(figureHandles->existsObject(scrollbar))
			figureHandles->removeItem(scrollbar);
		delete scrollbar;
	}
}

bool ddTableFigure::colNameAvailable(wxString name)
{
	bool out = true;
	ddColumnFigure *f;

	ddIteratorBase *iterator=figuresEnumerator();
	iterator->Next(); //First figure is main rect
	iterator->Next(); //Second figure is main title

	while(iterator->HasNext()){
		f = (ddColumnFigure *) iterator->Next();
		if(f->getColumnName(false).IsSameAs(name))
		{
			out=false;
			break;
		}
	}
	delete iterator;

	return out;
}

//WARNING: Columns SHOULD BE ADDED only using this function to avoid strange behaviors
void ddTableFigure::addColumn(ddColumnFigure *column)
{
	column->setOwnerTable(this);
	add(column);
	//Update Indexes
	if(maxColIndex == minIdxIndex) //maxColIndex == minIdxIndex means not indexes at this table, then update too
	{	
		minIdxIndex++;
		maxIdxIndex++;
	}
	maxColIndex++;
	colsWindow++;  //by default add a column increase initial window
	colsRowsSize++;
	calcRectsAreas();
	recalculateColsPos();
}

void ddTableFigure::removeColumn(ddColumnFigure *column)
{
	//Hack to allow to remove Fk before delete it.
	if(column->isPrimaryKey() || column->isUniqueKey())
	{
		column->setColumnKind(none);
	}

	column->setOwnerTable(NULL);
	remove(column);

	if(column)
		delete column;
	//Update Indexes
	if(maxColIndex == minIdxIndex) //means not indexes at this table, then update too
	{	
		minIdxIndex--;
		maxIdxIndex--;
	}
	maxColIndex--;
	if(colsRowsSize==colsWindow)  //only decrease if size of window and columns is the same
		colsWindow--;
	colsRowsSize--;
	if(beginDrawCols > 2)
		beginDrawCols--;
	calcRectsAreas();
	recalculateColsPos();
	if(colsWindow==colsRowsSize)   //if handle need to be removed, remove it
	{
		if(figureHandles->existsObject(scrollbar))
			figureHandles->removeItem(scrollbar);
	}
	//hack to update relationship position when table size change
	moveBy(-1,0);
	moveBy(1,0);
	column = NULL;
}

void ddTableFigure::recalculateColsPos()
{
	wxFont font = settings->GetSystemFont();
	int defaultHeight = getColDefaultHeight(font);

	ddIFigure *f = (ddIFigure *) figureFigures->getItemAt(0); //first figure is always Rect
	int horizontalPos = f->displayBox().x+2;
	int verticalPos = 0;

	for(int i = 2; i < maxColIndex ; i++)
	{
		f = (ddIFigure *) figureFigures->getItemAt(i); //table title
		if( (i >= beginDrawCols) && (i <= (colsWindow+beginDrawCols)) )  //Visible to draw
		{
			verticalPos = colsRect.y + (defaultHeight * (i-beginDrawCols) + ((i-beginDrawCols) * internalPadding));
			f->moveTo(horizontalPos,verticalPos);
		}
		else
			f->moveTo(-65000,-65000);  //any figure outside canvas (x<0 || y<0) is not draw & not used to calculate displaybox
	}
}



void ddTableFigure::draw(wxBufferedDC& context, ddDrawingView *view)
{

	context.SetPen(defaultPen);
	context.SetBrush(defaultBrush);

	//Hack to disable delete column mode when the figure pass from selected to no selected.
	if(fromSelToNOSel)
	{
		toggleColumnDeleteMode(true);
		fromSelToNOSel=false;
	}
	
	calcRectsAreas();
	context.SetPen(*wxBLACK_PEN);
	context.SetBrush(wxBrush (wxColour(255, 255, 224),wxSOLID));

	if(calcScrolled) //Hack to avoid pass view as parameter to calcRectsAreas() because is sometimes called outside a paint event
	{
		view->CalcScrolledPosition(fullSizeRect.x,fullSizeRect.y,&fullSizeRect.x,&fullSizeRect.y);
		view->CalcScrolledPosition(titleRect.x,titleRect.y,&titleRect.x,&titleRect.y);
		view->CalcScrolledPosition(titleColsRect.x,titleColsRect.y,&titleColsRect.x,&titleColsRect.y);
		view->CalcScrolledPosition(colsRect.x,colsRect.y,&colsRect.x,&colsRect.y);
		view->CalcScrolledPosition(titleIndxsRect.x,titleIndxsRect.y,&titleIndxsRect.x,&titleIndxsRect.y);
		view->CalcScrolledPosition(indxsRect.x,indxsRect.y,&indxsRect.x,&indxsRect.y);
		calcScrolled=false;
	}

	ddIFigure *f = (ddIFigure *) figureFigures->getItemAt(0); //table rectangle
	f->draw(context,view);
	f = (ddIFigure *) figureFigures->getItemAt(1); //table title
	f->draw(context,view);

	for(int i=beginDrawCols; i < (colsWindow+beginDrawCols); i++)
	{
		f = (ddIFigure *) figureFigures->getItemAt(i); //table title
		if(f->displayBox().GetPosition().x > 0 && f->displayBox().GetPosition().y > 0)
		{
			f->draw(context,view);
		}
	}

	wxFont font = settings->GetSystemFont();
	font.SetPointSize(7);
	context.SetFont(font);

	//Draw Columns Title Line 1
	context.DrawLine(titleColsRect.GetTopLeft(),titleColsRect.GetTopRight());
	//Draw Columns Title
	context.DrawText(wxT("Columns"),titleColsRect.x+3,titleColsRect.y);
	//Draw Columns Title Line 2
	context.DrawLine(titleColsRect.GetBottomLeft(),titleColsRect.GetBottomRight());
	//DrawVertical Lines
	context.DrawLine(titleColsRect.GetBottomLeft().x+11,titleColsRect.GetBottomLeft().y,titleColsRect.GetBottomLeft().x+11,titleIndxsRect.GetTopLeft().y);
	context.DrawLine(titleColsRect.GetBottomLeft().x+22,titleColsRect.GetBottomLeft().y,titleColsRect.GetBottomLeft().x+22,titleIndxsRect.GetTopLeft().y);
	//Draw Indexes Title Line 1
	context.DrawLine(titleIndxsRect.GetTopLeft(),titleIndxsRect.GetTopRight());
	//Draw Indexes Title	
	context.DrawText(wxT("Indexes"),titleIndxsRect.x+3,titleIndxsRect.y);
	//Draw Indexes Title Line 2
	context.DrawLine(titleIndxsRect.GetBottomLeft(),titleIndxsRect.GetBottomRight());

	//Draw scrollbar is needed
	if(scrollbar && figureHandles->existsObject(scrollbar))
		scrollbar->draw(context,view);
}

void ddTableFigure::drawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	context.SetPen(defaultSelectedPen);
	context.SetBrush(defaultSelectedBrush);

	//Hack to unselect any table
	if(!fromSelToNOSel)
		fromSelToNOSel=true;

	calcRectsAreas();
	context.SetPen(wxPen(wxColour(70, 130, 180),2,wxSOLID));
	context.SetBrush(wxBrush (wxColour(224, 248, 255),wxSOLID));

	if(calcScrolled) //Hack to avoid pass view as parameter to calcRectsAreas() because is sometimes called outside a paint event
	{
		view->CalcScrolledPosition(fullSizeRect.x,fullSizeRect.y,&fullSizeRect.x,&fullSizeRect.y);
		view->CalcScrolledPosition(titleRect.x,titleRect.y,&titleRect.x,&titleRect.y);
		view->CalcScrolledPosition(titleColsRect.x,titleColsRect.y,&titleColsRect.x,&titleColsRect.y);
		view->CalcScrolledPosition(colsRect.x,colsRect.y,&colsRect.x,&colsRect.y);
		view->CalcScrolledPosition(titleIndxsRect.x,titleIndxsRect.y,&titleIndxsRect.x,&titleIndxsRect.y);
		view->CalcScrolledPosition(indxsRect.x,indxsRect.y,&indxsRect.x,&indxsRect.y);
		calcScrolled=false;
	}

	ddIFigure *f = (ddIFigure *) figureFigures->getItemAt(0); //table rectangle
	f->drawSelected(context,view);
	f = (ddIFigure *) figureFigures->getItemAt(1); //table title
	f->drawSelected(context,view);

	for(int i=beginDrawCols; i < (colsWindow+beginDrawCols); i++)
	{
		f = (ddIFigure *) figureFigures->getItemAt(i); //table title
		if(f->displayBox().GetPosition().x > 0 && f->displayBox().GetPosition().y > 0)
		{
			f->drawSelected(context,view);
		}
	}

	wxFont font = settings->GetSystemFont();
	font.SetPointSize(7);
	context.SetFont(font);

	//Draw Columns Title Line 1
	context.DrawLine(titleColsRect.GetTopLeft(),titleColsRect.GetTopRight());
	//Draw Columns Title
	context.DrawText(wxT("Columns"),titleColsRect.x+3,titleColsRect.y);
	//Draw Columns Title Line 2
	context.DrawLine(titleColsRect.GetBottomLeft(),titleColsRect.GetBottomRight());
	//DrawVertical Lines
	context.DrawLine(titleColsRect.GetBottomLeft().x+11,titleColsRect.GetBottomLeft().y,titleColsRect.GetBottomLeft().x+11,titleIndxsRect.GetTopLeft().y);
	context.DrawLine(titleColsRect.GetBottomLeft().x+22,titleColsRect.GetBottomLeft().y,titleColsRect.GetBottomLeft().x+22,titleIndxsRect.GetTopLeft().y);
	//Draw Indexes Title Line 1
	context.DrawLine(titleIndxsRect.GetTopLeft(),titleIndxsRect.GetTopRight());
	//Draw Indexes Title	
	context.DrawText(wxT("Indexes"),titleIndxsRect.x+3,titleIndxsRect.y);
	//Draw Indexes Title Line 2
	context.DrawLine(titleIndxsRect.GetBottomLeft(),titleIndxsRect.GetBottomRight());

	if(deleteColumnMode)
	{
		context.SetTextForeground(*wxRED);
		wxBrush old=context.GetBrush();
		context.SetBrush(*wxGREEN_BRUSH);

		int w,h,x,y;
		context.GetTextExtent(wxString(wxT("Select Column to delete")),&w,&h);
		x=fullSizeRect.GetTopLeft().x+(((fullSizeRect.GetTopRight().x-fullSizeRect.GetTopLeft().x)-w)/2);
		y=fullSizeRect.GetTopLeft().y-h-2;
		context.DrawRectangle(wxRect(x,y,w,h));
		context.DrawText(wxString(wxT("Select Column to delete")),x,y);
		
		context.SetBrush(old);
		context.SetTextForeground(*wxBLACK);
		context.SetBackground(*wxWHITE);
		
	}
}

void ddTableFigure::setColsRowsWindow(int num)
{
	if(num > 0)
	{
		colsWindow = num;
		wxFont font = settings->GetSystemFont();
		colsRect.height = getColDefaultHeight(font) * colsWindow;
		colsRect.width = getFiguresMaxWidth();
	}
}

int ddTableFigure::getHeightFontMetric(wxString text, wxFont font)
{
	int width, height;
	wxBitmap emptyBitmap(ddAddColumn_xpm);	
	wxMemoryDC temp_dc;
	temp_dc.SelectObject(emptyBitmap);
	temp_dc.SetFont(font);
	temp_dc.GetTextExtent(text,&width,&height);
	return height;
}

int ddTableFigure::getColDefaultHeight(wxFont font)
{
	if(figureFigures->count()<=0)
	{
		int width, height;
		wxBitmap emptyBitmap(ddAddColumn_xpm);	
		wxMemoryDC temp_dc;
		temp_dc.SelectObject(emptyBitmap);
		temp_dc.SetFont(font);
		temp_dc.GetTextExtent(wxT("NewColumn"),&width,&height);
		return height;
	}
	else
	{
		ddIFigure *f = (ddIFigure *) figureFigures->getItemAt(1); //table title
		return f->displayBox().height; 
	}
}

//Delete Column Hack
bool ddTableFigure::deleteColumnActivated()
{
	return deleteColumnMode;
}

//Delete Column Hack
void ddTableFigure::toggleColumnDeleteMode(bool disable)
{
	if(disable)
		deleteColumnMode = false;
	else
		deleteColumnMode = !deleteColumnMode;
}

int ddTableFigure::getFiguresMaxWidth()
{
	ddColumnFigure *cf;
	ddGeometry g;

	ddIteratorBase *iterator=figuresEnumerator();
	iterator->Next(); //First figure is main rect
	int maxWidth=0;
	cf = (ddColumnFigure *) iterator->Next(); //Second figure is main title
	maxWidth = g.max(maxWidth,cf->displayBox().width+20);
	while(iterator->HasNext()){
		cf = (ddColumnFigure *) iterator->Next();
		maxWidth = g.max(maxWidth,cf->displayBox().width);
	}
	delete iterator;
	if(figureHandles->existsObject(scrollbar))
		return maxWidth + 11;  //as defined at locator
	else
		return maxWidth;
}


void ddTableFigure::calcRectsAreas()
{
	calcScrolled=true;

	int maxWidth = getFiguresMaxWidth() + externalPadding;
	if(maxWidth < 100)
		maxWidth = 100;
	wxFont font = settings->GetSystemFont();
	int defaultHeight = getColDefaultHeight(font);

	//cache displayBox()
	ddRect db = displayBox();

	//*** titleRect
	font.SetPointSize(7);
	int colsTitleHeight=getHeightFontMetric(wxT("Columns"),font);
	titleRect.x = db.x;
	titleRect.y = db.y;
	titleRect.width=maxWidth;
	titleRect.height=defaultHeight;

	titleColsRect.x = db.x;
	titleColsRect.y = titleRect.y+titleRect.height;
	titleColsRect.width=maxWidth;
	titleColsRect.height=colsTitleHeight;
	unScrolledTitleRect=titleColsRect;
	
	//*** colsRect
	colsRect.width=maxWidth;
	if(colsWindow>0)
		colsRect.height = defaultHeight * colsWindow + (colsWindow * internalPadding);
	else
		colsRect.height = defaultHeight;
	colsRect.x=db.x;
	colsRect.y=titleRect.y+titleRect.height+titleColsRect.height;
	unScrolledColsRect=colsRect;

	//*** idxTitleRect
	titleIndxsRect.width=maxWidth;
	titleIndxsRect.height=colsTitleHeight;
	titleIndxsRect.x=db.x;
	titleIndxsRect.y=colsRect.y+colsRect.height;

	//*** indexesRect
	indxsRect.width=maxWidth;
	indxsRect.height = defaultHeight * idxsWindow + (idxsWindow * internalPadding);
	indxsRect.x=db.x;
	indxsRect.y=titleIndxsRect.y+titleIndxsRect.height;

	//*** FullTable Size
	fullSizeRect.width = maxWidth;
	fullSizeRect.height = titleRect.height + titleColsRect.height + colsRect.height + titleIndxsRect.height + indxsRect.height;
	fullSizeRect.x=db.x;
	fullSizeRect.y=titleRect.y;
	unScrolledFullSizeRect=fullSizeRect;

	//Update sizes
	wxSize value=fullSizeRect.GetSize();
	rectangleFigure->setSize(value);
}

void ddTableFigure::updateTableSize()
{
	//Step 0: Recalculate displaybox size, in case of an external modification as change of datatype in a fk from a source (data is stored in original table)
	ddColumnFigure *cf;
	ddIteratorBase *iterator=figuresEnumerator();
	iterator->Next(); //First figure is main rect
	cf = (ddColumnFigure *) iterator->Next(); //Second figure is main title
	while(iterator->HasNext()){
		cf = (ddColumnFigure *) iterator->Next();
		cf->displayBoxUpdate();
	}
	delete iterator;

	//Step 1: Update table size
	calcRectsAreas();
	wxSize value=fullSizeRect.GetSize();
	rectangleFigure->setSize(value);
	//hack to update relationship position when table size change
	moveBy(-1,0);
	moveBy(1,0);
}

ddRect& ddTableFigure::getColsSpace()
{
	return unScrolledColsRect;
}

ddRect& ddTableFigure::getFullSpace()
{
	return unScrolledFullSizeRect;
}

ddRect& ddTableFigure::getTitleRect()
{
	return unScrolledTitleRect;
}


int ddTableFigure::getTotalColumns()
{
	return colsRowsSize;
}

int ddTableFigure::getColumnsWindow()
{
	return colsWindow;
}

void ddTableFigure::setColumnsWindow(int value, bool maximize)
{

	if(!maximize)
	{

		//if value >0 && <= max size table && table+offset < maxColIndex with window
		if( (value > 0) && (value <= colsRowsSize) && (maxColIndex >= ( beginDrawCols + value ) ) )   
		{
			colsWindow = value;
			calcRectsAreas();
			recalculateColsPos();
		}

		//if special case of needing to modify beginDrawCols then do it
		if( (value > 0) && (value <= colsRowsSize) && (maxColIndex < ( beginDrawCols + value ) ) ) 
		{
			if( (beginDrawCols + colsWindow)==maxColIndex)  //if index is at max
			{
				int diff = value-colsWindow;  // value should be always higher tan colsWindows
				if(diff > 0 && (beginDrawCols-diff)>=0 )
				{
					beginDrawCols-=diff;
					colsWindow = value;
					calcRectsAreas();
					recalculateColsPos();

				}
			}
		}
	}
	else
	{
		beginDrawCols = 2;
		colsWindow = value;
		calcRectsAreas();
		recalculateColsPos();
	}


	//Hide Scrollbar if needed
	if(colsWindow==colsRowsSize) 
	{
		if(figureHandles->existsObject(scrollbar))
			figureHandles->removeItem(scrollbar);
	}
	else 
	{
		if (!figureHandles->existsObject(scrollbar))
			figureHandles->addItem(scrollbar);
	}

}

void ddTableFigure::columnsWindowUp()  //move window from number to zero
{
	if( beginDrawCols > 2 )
	{
		beginDrawCols--;
		calcRectsAreas();
		recalculateColsPos();
	}
}

void ddTableFigure::columnsWindowDown()  //move window from number to maxcolumns
{
	if( (beginDrawCols+colsWindow) < maxColIndex)
	{
		beginDrawCols++;
		calcRectsAreas();
		recalculateColsPos();
	}
}

int ddTableFigure::getTopColWindowIndex()
{
	return (beginDrawCols-2);
}

void ddTableFigure::setPkConstraintName(wxString name)
{
	pkName = name;
}

wxString ddTableFigure::getPkConstraintName()
{
	return pkName;	
}

wxArrayString& ddTableFigure::getUkConstraintsNames()
{
	return ukNames;
}

/*
Rules to auto generate short names:
0. Table name delimiters are white space (quoted names) or _
1. if last char in a word is "s" is ignored, ex: employees -> last char will be e not s.
2. for quoted table names, quotes are ignored for short name purposes.
4. first word of a syllabe will be defined as first letter before vowels (a,e,i,o,u).
3. Tables with only one word:
		1st char of first syllabe + 2nd char of second syllabe + last char.
		ex: EMPLOYEES will be EPE
			PRODUCT	will be PDT
4. Tables with more than one words:
		1st char of first word, first char of second word, last char of last word.
		ex: ITEM DESCRIPTIONS will be IDN
			ITEMS FOR SALE will be IFE
5. Tables with one word but in non latin characters as vowels (a,e,i,o,u) o less than 2 vowels
		first 3 letters of the word
*/

wxString ddTableFigure::generateShortName(wxString longName)
{
	wxString nameT = longName;
	//filter not desiree characters
	nameT.Replace(wxT("\""),wxT(""),true);
	//start to build short name based on rules
	wxStringTokenizer tokens(nameT,wxT(" _"),wxTOKEN_DEFAULT);
	wxChar f,s,l;
	int num=tokens.CountTokens(),c=0;

	if(num > 1)
	{
		while( tokens.HasMoreTokens() )
		{
			wxString token = tokens.GetNextToken();
			if(c==0)
				f = token.GetChar(0);
			if(c==1)
				s = token.GetChar(0);
			if(((c+1)-num)==0)
			{	l = token.GetChar(token.length()-1);
				if(l=='s')
					l = token.GetChar(token.length()-2);
			}
			c++;
		}
	}
	else
	{
		//Look for vowels
		wxStringTokenizer vowelsTokens(nameT,wxT("aeiou"),wxTOKEN_DEFAULT);
		int numVowels = vowelsTokens.CountTokens();
		c=0;
		if(numVowels >= 3)
		{
			//word have at least 3 vowels tokens
			while( vowelsTokens.HasMoreTokens() )
			{
				wxString token = vowelsTokens.GetNextToken();
				if(c==0)
					f = token.GetChar(0);
				if(c==1)
					s = token.GetChar(0);
				if(((c+1)-numVowels)==0)
				{
					l = token.GetChar(token.length()-1);
					if(l=='s')
						l = token.GetChar(token.length()-2);
				}
				c++;
			}
		}
		else
		{
			//Less than two vowels languages or non latin languages
			if(nameT.length()>=3) // but a least 3 letters
			{
				f = nameT.GetChar(0);
				s = nameT.GetChar(1);
				l = nameT.GetChar(2);
			}
			else  //less three letters
			{
				f = nameT.GetChar(0);
				if(nameT.length()==2)
					s=nameT.GetChar(1);
				else
					s=' ';
				l=' ';
			}

		}
	}
	wxString out=wxString::Format(wxT("%c%c%c"),f,s,l); 
	out.UpperCase();
	return out;
}

wxString ddTableFigure::getShortTableName()
{
	ddTextTableItemFigure *c = (ddTextTableItemFigure*) figureFigures->getItemAt(1);
	return c->getAlias();
}

void ddTableFigure::setShortTableName(wxString shortName)
{
	ddTextTableItemFigure *c = (ddTextTableItemFigure*) figureFigures->getItemAt(1);
	c->setAlias(shortName);
}

wxString ddTableFigure::getTableName()
{
	ddTextTableItemFigure *c = (ddTextTableItemFigure*) figureFigures->getItemAt(1);
	c->setOneTimeNoAlias();
	return c->getText(false);
}

//set Null on all relationship items with a fk column to be delete
void ddTableFigure::prepareForDeleteFkColumn(ddColumnFigure *column)
{
	ddIteratorBase *iterator = observersEnumerator();
	while(iterator->HasNext()){
	ddRelationshipFigure *r = (ddRelationshipFigure*) iterator->Next();
	if(r->getStartFigure()==this)	//Only update FK of connection with this table as source. source ---<| destination
		r->prepareFkForDelete(column);
	}
	delete iterator;

}

//	Note about observers:
//	A table is observed by several relationships at same time, where that observers
//	are just looking for changes that will affect relationship behavior.
//	Ex: if I delete a pk on observed table (source) all observers (destination)
//		should modify their columns to remove that fk created from that pk column.
// Warning: when a relationship is created an observer is added to both sides of relationship
// because this behavior (needed for update connection) to identify if is an observer
// of source table or destination table, should be check end figure, start!=end and end=this is end figure
// If start = and is recursive
void ddTableFigure::updateFkObservers()
{
	ddIteratorBase *iterator = observersEnumerator();
	while(iterator->HasNext()){
	ddRelationshipFigure *r = (ddRelationshipFigure*) iterator->Next();
		if(r->getStartFigure()==this)	//Only update FK of connection with this table as source. source ---<| destination
		{
			r->updateForeignKey();
		}
	}
	delete iterator;
}

//If a column change datatype, should alert all others table to adjust their size with new values
void ddTableFigure::updateSizeOfObservers()
{
	//For all tables that are observing this table, update their size
	ddIteratorBase *iterator = observersEnumerator();
	while(iterator->HasNext()){
		ddRelationshipFigure *r = (ddRelationshipFigure*) iterator->Next();
		ddTableFigure *destFkTable=(ddTableFigure*) r->getEndFigure();
		destFkTable->updateTableSize();
	}
	delete iterator;
}

//drop foreign keys with this table as origin or destination
void ddTableFigure::processDeleteAlert(ddDrawingView *view)
{
	ddIteratorBase *iterator = observersEnumerator();
	bool repeatFlag;
	do {
		repeatFlag=false;
		iterator->ResetIterator();
		while(iterator->HasNext()){
			ddRelationshipFigure *rel = (ddRelationshipFigure*) iterator->Next();
			rel->disconnectStart();
			rel->disconnectEnd();
			view->remove(rel);
			repeatFlag=true;
			delete rel;
			break;
		}
	} while(repeatFlag);
	
	delete iterator;
}

void ddTableFigure::basicMoveBy(int x, int y)
{

ddIFigure *f = (ddIFigure *) figureFigures->getItemAt(0);
if((f->displayBox().x+x) > 0 && (f->displayBox().y+y) > 0)
ddCompositeFigure::basicMoveBy(x,y);

}

//DD-TODO: fix all model to allow all options from http://www.postgresql.org/docs/8.1/static/sql-createtable.html
wxString ddTableFigure::generateSQL()
{
	//Columns and table
	wxString tmp(wxT("CREATE TABLE "));
	tmp+=getTableName() + wxT(" (\n");
	ddIteratorBase *iterator = figuresEnumerator();
	iterator->Next(); //Fixed Position for table rectangle
	iterator->Next(); //Fixed Position for table name
	while(iterator->HasNext())
    {
		ddColumnFigure *column = (ddColumnFigure*) iterator->Next();
		tmp+=column->generateSQL();
		if(column->isNotNull())
		{
			tmp+=wxT(" NOT NULL");
		}
		if(iterator->HasNext())
		{
			tmp+=wxT(" , \n");
		}
	}
	//Pk, Uk Constraints
	iterator->ResetIterator();
	iterator->Next(); //Fixed Position for table rectangle
	iterator->Next(); //Fixed Position for table name
	int contPk=0;
	while(iterator->HasNext())
    {
		ddColumnFigure *column = (ddColumnFigure*) iterator->Next();
		if(column->isPrimaryKey())
			contPk++;
	}
	if(contPk>0)
	{
		tmp += wxT(", \nPRIMARY KEY ( ");
		iterator->ResetIterator();
		iterator->Next(); //Fixed Position for table rectangle
		iterator->Next(); //Fixed Position for table name

		while(iterator->HasNext())
        {
			ddColumnFigure *column = (ddColumnFigure*) iterator->Next();
			if(column->isPrimaryKey())
            {
				tmp+=column->getColumnName();
				contPk--;
				if(contPk>0)
				{
					tmp+=wxT(" , ");
				}
				else
				{
					tmp+=wxT(" ) ");
				}
			}
		}
	}
	delete iterator;
	//Fk Constraint
	iterator = observersEnumerator();
	if(!iterator->HasNext())
	{
		tmp+=wxT("\n ); ");
	}
	else
	{  
		while(iterator->HasNext())
        {
			ddRelationshipFigure *rel = (ddRelationshipFigure*) iterator->Next();
			if(rel->getStartFigure()!=this)
			{
				wxString tmp2=rel->generateSQL();
				if(tmp2.length()>0)
				{
					tmp+=wxT(" , \n");
					tmp+=tmp2;
				}
			}
		}
		tmp+=wxT("\n ); ");
	}
	delete iterator;
	return tmp;
}
