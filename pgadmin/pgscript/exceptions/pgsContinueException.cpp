//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#include "pgAdmin3.h"
#include "pgscript/exceptions/pgsContinueException.h"

pgsContinueException::pgsContinueException() :
	pgsException()
{

}

pgsContinueException::~pgsContinueException()
{

}

const wxString pgsContinueException::message() const
{
	return wxT("CONTINUE");
}
