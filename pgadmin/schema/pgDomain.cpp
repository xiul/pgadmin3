//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// pgDomain.cpp - Domain class
//
//////////////////////////////////////////////////////////////////////////

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "pgAdmin3.h"
#include "utils/misc.h"
#include "schema/pgDomain.h"
#include "schema/pgDatatype.h"


pgDomain::pgDomain(pgSchema *newSchema, const wxString &newName)
	: pgSchemaObject(newSchema, domainFactory, newName)
{
}

pgDomain::~pgDomain()
{
}

wxString pgDomain::GetTranslatedMessage(int kindOfMessage) const
{
	wxString message = wxEmptyString;

	switch (kindOfMessage)
	{
		case RETRIEVINGDETAILS:
			message = _("Retrieving details on domain");
			message += wxT(" ") + GetName();
			break;
		case REFRESHINGDETAILS:
			message = _("Refreshing domain");
			message += wxT(" ") + GetName();
			break;
		case DROPINCLUDINGDEPS:
			message = wxString::Format(_("Are you sure you wish to drop domain \"%s\" including all objects that depend on it?"),
			                           GetFullIdentifier().c_str());
			break;
		case DROPEXCLUDINGDEPS:
			message = wxString::Format(_("Are you sure you wish to drop domain \"%s\"?"),
			                           GetFullIdentifier().c_str());
			break;
		case DROPCASCADETITLE:
			message = _("Drop domain cascaded?");
			break;
		case DROPTITLE:
			message = _("Drop domain?");
			break;
		case PROPERTIESREPORT:
			message = _("Domain properties report");
			message += wxT(" - ") + GetName();
			break;
		case PROPERTIES:
			message = _("Domain properties");
			break;
		case DDLREPORT:
			message = _("Domain DDL report");
			message += wxT(" - ") + GetName();
			break;
		case DDL:
			message = _("Domain DDL");
			break;
		case DEPENDENCIESREPORT:
			message = _("Domain dependencies report");
			message += wxT(" - ") + GetName();
			break;
		case DEPENDENCIES:
			message = _("Domain dependencies");
			break;
		case DEPENDENTSREPORT:
			message = _("Domain dependents report");
			message += wxT(" - ") + GetName();
			break;
		case DEPENDENTS:
			message = _("Domain dependents");
			break;
	}

	return message;
}


bool pgDomain::DropObject(wxFrame *frame, ctlTree *browser, bool cascaded)
{
	wxString sql = wxT("DROP DOMAIN ") + this->GetSchema()->GetQuotedIdentifier() + wxT(".") + this->GetQuotedIdentifier();
	if (cascaded)
		sql += wxT(" CASCADE");
	return GetDatabase()->ExecuteVoid(sql);
}

wxString pgDomain::GetSql(ctlTree *browser)
{
	if (sql.IsNull())
	{
		sql = wxT("-- Domain: ") + GetQuotedFullIdentifier() + wxT("\n\n")
		      + wxT("-- DROP DOMAIN ") + GetQuotedFullIdentifier() + wxT(";")
		      + wxT("\n\nCREATE DOMAIN ") + GetQuotedFullIdentifier()
		      + wxT("\n  AS ") + GetQuotedBasetype();
		if (GetCollationOid() > 0)
			sql += wxT("\n  COLLATE ") + GetQuotedCollation();
		AppendIfFilled(sql, wxT("\n  DEFAULT "), GetDefault());
		// CONSTRAINT Name Dont know where it's stored, may be omitted anyway
		if (notNull)
			sql += wxT("\n  NOT NULL");
		AppendIfFilled(sql, wxT("\n   "), GetCheck());

		sql += wxT(";\n")
		       + GetOwnerSql(7, 4)
		       + GetCommentSql();
	}

	return sql;
}



void pgDomain::ShowTreeDetail(ctlTree *browser, frmMain *form, ctlListView *properties, ctlSQLBox *sqlPane)
{
	if (!expandedKids)
	{
		expandedKids = true;
		if (GetConnection()->BackendMinimumVersion(7, 4))
		{
			pgSet *set = ExecuteSet(
			                 wxT("SELECT conname, pg_get_constraintdef(oid) AS consrc FROM pg_constraint WHERE contypid=") + GetOidStr());
			if (set)
			{
				while (!set->Eof())
				{
					if (!check.IsEmpty())
					{
						check += wxT(" ");
					}
					wxString conname = set->GetVal(wxT("conname"));
					if (!conname.StartsWith(wxT("$")))
						check += wxT("CONSTRAINT ") + qtIdent(conname) + wxT(" ");
					check += set->GetVal(wxT("consrc"));

					set->MoveNext();
				}
				delete set;
			}
		}
	}
	if (properties)
	{
		CreateListColumns(properties);

		properties->AppendItem(_("Name"), GetName());
		properties->AppendItem(_("OID"), GetOid());
		properties->AppendItem(_("Owner"), GetOwner());
		properties->AppendItem(_("Base type"), GetBasetype());
		if (GetDimensions())
			properties->AppendItem(_("Dimensions"), GetDimensions());
		if (GetCollationOid() > 0)
			properties->AppendItem(_("Collation"), GetQuotedCollation());
		properties->AppendItem(_("Default"), GetDefault());
		properties->AppendItem(_("Check"), GetCheck());
		properties->AppendYesNoItem(_("Not NULL?"), GetNotNull());
		properties->AppendYesNoItem(_("System domain?"), GetSystemObject());
		properties->AppendItem(_("Comment"), firstLineOnly(GetComment()));
	}
}



pgObject *pgDomain::Refresh(ctlTree *browser, const wxTreeItemId item)
{
	pgObject *domain = 0;

	pgCollection *coll = browser->GetParentCollection(item);
	if (coll)
		domain = domainFactory.CreateObjects(coll, 0, wxT("   AND d.oid=") + GetOidStr() + wxT("\n"));

	return domain;
}


////////////////////////////////////////////////////



pgObject *pgDomainFactory::CreateObjects(pgCollection *collection, ctlTree *browser, const wxString &restriction)
{
	wxString sql;
	pgDomain *domain = 0;

	pgDatabase *db = collection->GetDatabase();

	sql = wxT("SELECT d.oid, d.typname as domname, d.typbasetype, format_type(b.oid,NULL) as basetype, pg_get_userbyid(d.typowner) as domainowner, \n");
	if (collection->GetDatabase()->BackendMinimumVersion(9, 1))
		sql += wxT("c.oid AS colloid, c.collname, cn.nspname as collnspname, \n");
	sql += wxT("       d.typlen, d.typtypmod, d.typnotnull, d.typdefault, d.typndims, d.typdelim, bn.nspname as basensp,\n")
	       wxT("       description, (SELECT COUNT(1) FROM pg_type t2 WHERE t2.typname=d.typname) > 1 AS domisdup,\n")
	       wxT("       (SELECT COUNT(1) FROM pg_type t3 WHERE t3.typname=b.typname) > 1 AS baseisdup\n")
	       wxT("  FROM pg_type d\n")
	       wxT("  JOIN pg_type b ON b.oid = CASE WHEN d.typndims>0 then d.typelem ELSE d.typbasetype END\n")
	       wxT("  JOIN pg_namespace bn ON bn.oid=b.typnamespace\n")
	       wxT("  LEFT OUTER JOIN pg_description des ON des.objoid=d.oid\n");
	if (collection->GetDatabase()->BackendMinimumVersion(9, 1))
		sql += wxT("  LEFT OUTER JOIN pg_collation c ON d.typcollation=c.oid\n")
		       wxT("  LEFT OUTER JOIN pg_namespace cn ON c.collnamespace=cn.oid\n");
	sql += wxT(" WHERE d.typtype = 'd' AND d.typnamespace = ") + NumToStr(collection->GetSchema()->GetOid()) + wxT("::oid\n")
	       + restriction +
	       wxT(" ORDER BY d.typname");
	pgSet *domains = db->ExecuteSet(sql);

	if (domains)
	{
		while (!domains->Eof())
		{
			domain = new pgDomain(collection->GetSchema(), domains->GetVal(wxT("domname")));

			domain->iSetOid(domains->GetOid(wxT("oid")));
			domain->iSetOwner(domains->GetVal(wxT("domainowner")));
			domain->iSetBasetype(domains->GetVal(wxT("basetype")));
			domain->iSetBasetypeOid(domains->GetOid(wxT("typbasetype")));
			domain->iSetComment(domains->GetVal(wxT("description")));
			long typmod = domains->GetLong(wxT("typtypmod"));

			pgDatatype dt(domains->GetVal(wxT("basensp")), domains->GetVal(wxT("basetype")),
			              domains->GetBool(wxT("baseisdup")), domains->GetLong(wxT("typndims")), typmod);

			domain->iSetTyplen(domains->GetLong(wxT("typlen")));
			domain->iSetTypmod(typmod);
			domain->iSetLength(dt.Length());
			domain->iSetPrecision(dt.Precision());
			domain->iSetBasetype(dt.GetSchemaPrefix(db) + dt.FullName());
			domain->iSetQuotedBasetype(dt.GetQuotedSchemaPrefix(db) + dt.QuotedFullName());
			domain->iSetDefault(domains->GetVal(wxT("typdefault")));
			domain->iSetNotNull(domains->GetBool(wxT("typnotnull")));
			domain->iSetDimensions(domains->GetLong(wxT("typndims")));
			domain->iSetDelimiter(domains->GetVal(wxT("typdelim")));
			domain->iSetIsDup(domains->GetBool(wxT("domisdup")));
			if (collection->GetDatabase()->BackendMinimumVersion(9, 1))
			{
				domain->iSetCollation(domains->GetVal(wxT("collname")));
				domain->iSetQuotedCollation(qtIdent(domains->GetVal(wxT("collnspname"))) + wxT(".") + qtIdent(domains->GetVal(wxT("collname"))));
				domain->iSetCollationOid(domains->GetOid(wxT("colloid")));
			}
			else
				domain->iSetCollationOid(0);

			if (browser)
			{
				browser->AppendObject(collection, domain);
				domains->MoveNext();
			}
			else
				break;
		}

		delete domains;
	}
	return domain;
}

/////////////////////////////

pgDomainCollection::pgDomainCollection(pgaFactory *factory, pgSchema *sch)
	: pgSchemaObjCollection(factory, sch)
{
}


wxString pgDomainCollection::GetTranslatedMessage(int kindOfMessage) const
{
	wxString message = wxEmptyString;

	switch (kindOfMessage)
	{
		case RETRIEVINGDETAILS:
			message = _("Retrieving details on domains");
			break;
		case REFRESHINGDETAILS:
			message = _("Refreshing domains");
			break;
		case OBJECTSLISTREPORT:
			message = _("Domains list report");
			break;
	}

	return message;
}

/////////////////////////////

#include "images/domain.pngc"
#include "images/domain-sm.pngc"
#include "images/domains.pngc"

pgDomainFactory::pgDomainFactory()
	: pgSchemaObjFactory(__("Domain"), __("New Domain..."), __("Create a new Domain."), domain_png_img, domain_sm_png_img)
{
}


pgCollection *pgDomainFactory::CreateCollection(pgObject *obj)
{
	return new pgDomainCollection(GetCollectionFactory(), (pgSchema *)obj);
}

pgDomainFactory domainFactory;
static pgaCollectionFactory cf(&domainFactory, __("Domains"), domains_png_img);
