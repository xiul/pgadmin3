//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddAbstractTool.cpp 
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/tools/ddAbstractTool.h"

ddAbstractTool::ddAbstractTool(ddDrawingEditor *editor){
	anchorX=0;
	anchorY=0;
	ownerEditor=editor;
}

ddAbstractTool::~ddAbstractTool(){
}

void ddAbstractTool::mouseDown(ddMouseEvent& event){
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);
}

void ddAbstractTool::mouseUp(ddMouseEvent& event){
}

void ddAbstractTool::mouseMove(ddMouseEvent& event){
}

void ddAbstractTool::mouseDrag(ddMouseEvent& event){
}

void ddAbstractTool::keyDown(wxKeyEvent& event){
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);
}

void ddAbstractTool::keyUp(wxKeyEvent& event)
{
}

void ddAbstractTool::setAnchorCoords(int x, int y){
	anchorX=x;
	anchorY=y;
}

ddDrawingEditor* ddAbstractTool::getDrawingEditor(){
	return ownerEditor;
}

/*
void ddITool::mouseDown(ddMouseEvent& event){
}

void ddITool::mouseUp(ddMouseEvent& event){
}

void ddITool::mouseMove(ddMouseEvent& event){
}

void ddITool::mouseDrag(ddMouseEvent& event){
}

void ddITool::keyDown(wxKeyEvent& event){
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);
}

void ddITool::keyUp(wxKeyEvent& event)
{
}

void ddITool::activate()
{
	activatedValue=true;
}

void ddITool::deactivate()
{
	activatedValue=false;
}

bool ddITool::activated()
{
	return activatedValue;
}

bool ddITool::undoable(){
	return undoableValue;
}

void ddITool::setAnchorCoords(int x, int y){
	anchorX=x;
	anchorY=y;
}*/