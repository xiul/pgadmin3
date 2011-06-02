//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddCollection.h - Generic implementation of a Collection used by dd
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCOLLECTION_H
#define DDCOLLECTION_H

// App headers
#include "dd/draw/main/ddObject.h"
#include "dd/draw/utilities/ddCollectionBase.h"

class ddCollection : public wxObject
{
public:
    ddCollection(ddCollectionBase *collectionBase);
    virtual ~ddCollection();
    void addItem(ddObject *item);
    void removeItem(ddObject *item);
	void removeItemAt(int index);
    void deleteAll();
    void removeAll();
    int count();
    bool existsObject(ddObject *item);
    int getIndex(ddObject *item);
    ddObject* getItemAt(int index);
    void insertAtIndex(ddObject *item, int index);
	void replaceAtIndex(ddObject *item, int index);
	void bringToFront(ddObject *item);
	void bringToBack(ddObject *item);
    ddIteratorBase* createIterator();
	ddIteratorBase* createDownIterator();

private:
    ddCollectionBase *collection;
};
#endif
