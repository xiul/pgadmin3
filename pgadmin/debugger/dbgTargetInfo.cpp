//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dbgTargetInfo.cpp - debugger
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"
#include "utils/pgDefs.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/tokenzr.h>
#include <wx/arrimpl.cpp>

// App headers
#include "debugger/dbgTargetInfo.h"
#include "debugger/dbgResultset.h"
#include "debugger/dbgPgConn.h"

#include <stdexcept>

WX_DEFINE_OBJARRAY( wsArgInfoArray );

#define COL_TARGET_NAME    	"targetname"
#define COL_SCHEMA_NAME    	"nspname"
#define COL_LANGUAGE_NAME    "lanname"
#define COL_ARG_NAMES    	"argnames"
#define COL_ARG_MODES    	"argmodes"
#define COL_ARG_TYPES    	"argtypenames"
#define COL_ARG_TYPEOIDS    "argtypeoids"
#define COL_ARG_DEFVALS     "argdefvals"
#define COL_IS_FUNCTION    	"isfunc"
#define COL_TARGET_OID    	"target"
#define COL_PACKAGE_OID    	"pkg"
#define COL_FQ_NAME    	    "fqname"		/* Fully qualified name	*/
#define COL_RETURNS_SET    	"proretset"
#define COL_RETURN_TYPE    	"rettype"

////////////////////////////////////////////////////////////////////////////////
// dbgTargetInfo constructor
//
//    This class implements a container that holds information necessary to invoke
//  a debugger target (a function or procedure).
//
//  When the constructor is called, it sends a query to the server to retreive:
//    	the OID of the target,
//    	the name of the target,
//    	the name of the schema in which the target is defined
//    	the name of the language in which the target is defined
//    	the number of arguments expected by the target
//    	the argument names
//    	the argument types
//    	the argument modes (IN, OUT, or INOUT)
//    	the target type (function or procedure)
//
//    This class offers a number of (inline) member functions that you can call
//  to extract the above information after it's been queried from the server.

dbgTargetInfo::dbgTargetInfo( const wxString &target,  dbgPgConn *conn, char targetType )
{
	wxString query =
	    wxT("select t.*, ")
	    wxT("  pg_catalog.oidvectortypes( t.argtypes ) as argtypenames, t.argtypes as argtypeoids,")
	    wxT("  l.lanname, n.nspname, p.proretset, y.typname AS rettype")
	    wxT(" from")
	    wxT("  pldbg_get_target_info( '%s', '%c' ) t , pg_namespace n, pg_language l, pg_proc p, pg_type y")
	    wxT(" where")
	    wxT("  n.oid = t.schema and ")
	    wxT("  l.oid = t.targetlang and " )
	    wxT("  p.oid = t.target and ")
	    wxT("  y.oid = t.returntype");

	dbgResultset *result = new dbgResultset(conn->waitForCommand(wxString::Format(query, target.c_str(), targetType)));

	if(result->getCommandStatus() != PGRES_TUPLES_OK)
		throw( std::runtime_error( result->getRawErrorMessage()));

	m_name     	 = result->getString( wxString(COL_TARGET_NAME, wxConvUTF8));
	m_schema   	 = result->getString( wxString(COL_SCHEMA_NAME, wxConvUTF8));
	m_language 	 = result->getString( wxString(COL_LANGUAGE_NAME, wxConvUTF8));
	m_argNames 	 = result->getString( wxString(COL_ARG_NAMES, wxConvUTF8));
	m_argModes 	 = result->getString( wxString(COL_ARG_MODES, wxConvUTF8));
	m_argTypes 	 = result->getString( wxString(COL_ARG_TYPES, wxConvUTF8));
	m_argTypeOids = result->getString( wxString(COL_ARG_TYPEOIDS, wxConvUTF8));

	// get arg defvals if they exist
	if (result->columnExists(wxString(COL_ARG_DEFVALS, wxConvUTF8)))
		m_argDefVals = result->getString( wxString(COL_ARG_DEFVALS, wxConvUTF8));

	if (result->columnExists(wxString(COL_PACKAGE_OID, wxConvUTF8)))
		m_isFunction = result->getBool( wxString(COL_IS_FUNCTION, wxConvUTF8));
	else
		m_isFunction = true;

	m_oid      	 = result->getLong( wxString(COL_TARGET_OID, wxConvUTF8));

	if (result->columnExists(wxString(COL_PACKAGE_OID, wxConvUTF8)))
		m_pkgOid = result->getLong( wxString(COL_PACKAGE_OID, wxConvUTF8));
	else
		m_pkgOid = 0;

	m_fqName	 = result->getString( wxString(COL_FQ_NAME, wxConvUTF8));
	m_returnsSet = result->getBool( wxString(COL_RETURNS_SET, wxConvUTF8));
	m_returnType = result->getString( wxString(COL_RETURN_TYPE, wxConvUTF8));

	// Parse out the argument types, names, and modes

	// By creating a tokenizer with wxTOKEN_STRTOK and a delimiter string
	// that contains ",{}", we can parse out PostgreSQL array strings like:
	//	 {int, varchar, numeric}

	wxStringTokenizer names(m_argNames, wxT( ",{}" ), wxTOKEN_STRTOK);
	wxStringTokenizer types(m_argTypes, wxT( ",{}" ), wxTOKEN_STRTOK);
	wxStringTokenizer typeOids(m_argTypeOids, wxT( ",{}" ), wxTOKEN_STRTOK);
	wxStringTokenizer modes(m_argModes, wxT( ",{}" ), wxTOKEN_STRTOK);
	wxStringTokenizer defvals(m_argDefVals, wxT( ",{}" ), wxTOKEN_STRTOK);

	// Create one wsArgInfo for each target argument

	m_argInCount = m_argOutCount = m_argInOutCount = 0;
	int	argCount = 0;

	while( types.HasMoreTokens())
	{
		argCount++;

		wxString	argName = names.GetNextToken();
		wxString    defVal;

		if( argName.IsEmpty())
			argName.Printf( wxT( "$%d" ), argCount );

		// In EDBAS 90, if an SPL-function has both an OUT-parameter
		// and a return value (which is not possible on PostgreSQL otherwise),
		// the return value is transformed into an extra OUT-parameter
		// named "_retval_"
		if (argName == wxT("_retval_") && conn->EdbMinimumVersion(9, 0))
		{
			// this will be the return type for this object
			m_returnType = types.GetNextToken();

			// consume uniformly, mode will definitely be "OUT"
			modes.GetNextToken();

			// ignore OID also..
			typeOids.GetNextToken();
			continue;
		}

		wsArgInfo	argInfo( argName, types.GetNextToken(), modes.GetNextToken(), typeOids.GetNextToken());

		if( argInfo.getMode() == wxT( "i" ))
			m_argInCount++;
		else if( argInfo.getMode() == wxT( "o" ))
			m_argOutCount++;
		else if( argInfo.getMode() == wxT( "b" ))
			m_argInOutCount++;

		// see if this arg has a def value and add if so. If we see an empty
		// string "", what should we do? Infact "" might be a valid default
		// value in some cases, so for now store "" too. Note that we will
		// store the "" only if this is stringlike type and nothing otherwise..
		defVal = (defvals.GetNextToken()).Strip ( wxString::both );
		if (argInfo.isValidDefVal(defVal))
		{
			// remove starting/trailing quotes
			defVal.Replace( wxT( "\"" ), wxT( "" ));
			argInfo.setValue(defVal);
		}

		m_argInfo.Add( argInfo );
	}

	// Get the package initializer function OID. On 8.1 or below, this is
	// assumed to be the same as the package OID. On 8.2, we have an API :-)
	if (conn->EdbMinimumVersion(8, 2))
	{
		PGresult *res;

		m_pkgInitOid = 0;
		res = conn->waitForCommand( wxT( "SELECT pldbg_get_pkg_cons(") + NumToStr(m_pkgOid) + wxT(");"));

		if (PQresultStatus(res) == PGRES_TUPLES_OK)
		{
			// Retrieve the query result and return it.
			m_pkgInitOid = StrToLong(wxString(PQgetvalue(res, 0, 0), wxConvUTF8));

			// Cleanup & exit
			PQclear(res);
		}
	}
	else if (conn->GetIsEdb())
		m_pkgInitOid = m_pkgOid;
	else
		m_pkgInitOid = 0;
}

////////////////////////////////////////////////////////////////////////////////
// operator[]
//
//    This operator function makes it easy to index into the m_argInfo[] array
//    using concise syntax.

wsArgInfo &dbgTargetInfo::operator[]( int index )
{
	return( m_argInfo[index] );
}

////////////////////////////////////////////////////////////////////////////////
// wsArgInfo constructor
//
//    A wsArgInfo object contains information about a function (or procedure)
//  argument.  Inside of each wsArgInfo object, we store the name of the argument,
//    the argument type, and the argument mode (IN (i), OUT (o), or INOUT (b)).
//
//    Once the user has had a chance to enter values for each of the IN and INOUT
//    arguments, we store those values inside of the corresponding wsArgInfo objects

wsArgInfo::wsArgInfo( const wxString &argName, const wxString &argType, const wxString &argMode, const wxString &argTypeOid)
	: m_name( argName.Strip( wxString::both )),
	  m_type( argType.Strip( wxString::both )),
	  m_mode( argMode == wxT( "" ) ? wxT( "i" ) : argMode.Strip( wxString::both )),
	  m_value()
{
	long oid;
	argTypeOid.ToLong(&oid);
	m_typeOid = (Oid)oid;
}

////////////////////////////////////////////////////////////////////////////////
// quoteValue()
//
//    This function will extract the argument value from the given wsArgInfo object
//  and will wrap that value in single quotes (unless the value has already been
//    quoted).  If the argument value (entered by the user) is blank, we return NULL
//    instead of a quoted string.
//
//    NOTE: we quote all value regardless of type - it's perfectly valid to quote a
//        numeric (or boolean) value in PostgreSQL

const wxString wsArgInfo::quoteValue()
{
	if (m_value == wxT(""))
		return (wxT("NULL"));
	else if (m_value == wxT("''"))
		return (wxT("''"));
	else if (m_value == wxT("\\'\\'"))
		return (wxT("'\\'\\''"));
	else if (m_value[0] == '\'' )
		return (m_value);
	else
		return(wxString(wxT("'") + m_value + wxT("'")));
}

////////////////////////////////////////////////////////////////////////////////
// isValidDefVal()
//
//    This function checks if the passed in defvalue is sane or not. If it is
//    empty, nothing needs to be done. However if the backend returns "", then
//    we need to entertain this as valid input only for stringlike types. Else
//    we ignore. Obviously if defval is anything other than "", we need to
//    honor it
//

bool wsArgInfo::isValidDefVal(const wxString defValue)
{
	if (defValue.IsEmpty())
		return false;

	if (defValue != wxT("\"\""))
		return true;
	else
	{
		// return true only if the type is a stringlike type..
		switch (getTypeOid())
		{
			case PGOID_TYPE_CHAR:
			case PGOID_TYPE_NAME:
			case PGOID_TYPE_TEXT:
			case PGOID_TYPE_BPCHAR:
			case PGOID_TYPE_VARCHAR:
			case PGOID_TYPE_CSTRING:
				return true;

			default:
				return false;
		}
	}
}
