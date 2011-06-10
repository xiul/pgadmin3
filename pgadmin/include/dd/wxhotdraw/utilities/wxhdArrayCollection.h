//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddArrayCollection.h - Implementation of Collection Using Arrays
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDARRAYCOLLECTION_H
#define DDARRAYCOLLECTION_H

// App headers
#include "dd/wxhotdraw/utilities/wxhdCollectionBase.h"
#include "dd/wxhotdraw/main/wxhdObject.h"


WX_DEFINE_ARRAY_PTR(ddObject *, ddObjsArray);

class ddArrayIterator : public ddIteratorBase
{
public:
    ddArrayIterator(ddObjsArray *ddPtrsArray);
    ddObject* Next();
    ddObject* Current();
    bool HasNext();
    void ResetIterator();

private:
    int position;
    ddObjsArray *internalArray;
};

class ddArrayDownIterator : public ddIteratorBase
{
public:
    ddArrayDownIterator(ddObjsArray *ddPtrsArray);
    ddObject* Next();
    ddObject* Current();
    bool HasNext();
    void ResetIterator();

private:
    int position;
    ddObjsArray *internalArray;
};

//Create Array Objects used as base for ddCollections
class ddArrayCollection : public ddCollectionBase
{
public:
    ~ddArrayCollection();
    void addItem(ddObject *item);
    void removeItem(ddObject *item);
	virtual void removeItemAt(int index);
    ddIteratorBase* createIterator();
	ddIteratorBase* createDownIterator();
    ddObject* getItemAt(int index);
	void bringToFront(ddObject *item);
	void sendToBack(ddObject *item);
    int count();
    bool existsObject(ddObject *item);
    int getIndex(ddObject *item);
    void insertAtIndex(ddObject *item, int index);
	void replaceAtIndex(ddObject *item, int index);
    void deleteAll();
    void removeAll();
    ddObject *& operator[](size_t index) { return ddArray[index]; }
private:
	ddObjsArray ddArray;
};
#endif
