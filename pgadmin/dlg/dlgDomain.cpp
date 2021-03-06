//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dlgDomain.cpp - PostgreSQL Domain Property
//
//////////////////////////////////////////////////////////////////////////

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "pgAdmin3.h"
#include "utils/misc.h"
#include "utils/pgDefs.h"

#include "dlg/dlgDomain.h"
#include "schema/pgSchema.h"
#include "schema/pgDomain.h"
#include "schema/pgDatatype.h"


// pointer to controls
#define chkNotNull          CTRL_CHECKBOX("chkNotNull")
#define txtDefault          CTRL_TEXT("txtDefault")
#define txtCheck            CTRL_TEXT("txtCheck")
#define cbCollation         CTRL_COMBOBOX("cbCollation")

BEGIN_EVENT_TABLE(dlgDomain, dlgTypeProperty)
	EVT_TEXT(XRCID("txtLength"),                    dlgProperty::OnChange)
	EVT_TEXT(XRCID("txtPrecision"),                 dlgProperty::OnChange)
	EVT_TEXT(XRCID("cbDatatype"),                   dlgDomain::OnSelChangeTyp)
	EVT_COMBOBOX(XRCID("cbDatatype"),               dlgDomain::OnSelChangeTyp)
	EVT_TEXT(XRCID("txLength"),                     dlgProperty::OnChange)
	EVT_TEXT(XRCID("txtDefault"),                   dlgProperty::OnChange)
	EVT_CHECKBOX(XRCID("chkNotNull"),               dlgProperty::OnChange)
END_EVENT_TABLE();


dlgProperty *pgDomainFactory::CreateDialog(frmMain *frame, pgObject *node, pgObject *parent)
{
	return new dlgDomain(this, frame, (pgDomain *)node, (pgSchema *)parent);
}


dlgDomain::dlgDomain(pgaFactory *f, frmMain *frame, pgDomain *node, pgSchema *sch)
	: dlgTypeProperty(f, frame, wxT("dlgDomain"))
{
	schema = sch;
	domain = node;

	txtLength->Disable();
	txtPrecision->Disable();
}


pgObject *dlgDomain::GetObject()
{
	return domain;
}


int dlgDomain::Go(bool modal)
{
	if (domain)
	{
		// edit mode
		cbSchema->Enable(connection->BackendMinimumVersion(8, 1));
		cbDatatype->Append(domain->GetBasetype());
		AddType(wxT(" "), 0, domain->GetBasetype());
		cbDatatype->SetSelection(0);
		if (domain->GetLength() >= 0)
		{
			txtLength->SetValue(NumToStr(domain->GetLength()));
			if (domain->GetPrecision() >= 0)
				txtPrecision->SetValue(NumToStr(domain->GetPrecision()));
		}
		chkNotNull->SetValue(domain->GetNotNull());
		txtDefault->SetValue(domain->GetDefault());
		txtCheck->SetValue(domain->GetCheck());

		txtName->Disable();
		cbDatatype->Disable();
		txtCheck->Disable();

		cbCollation->SetValue(domain->GetQuotedCollation());
		cbCollation->Disable();

		if (!connection->BackendMinimumVersion(7, 4))
		{
			cbOwner->Disable();
			txtDefault->Disable();
			chkNotNull->Disable();
		}
	}
	else
	{
		// create mode
		if (!connection->BackendMinimumVersion(7, 4))
			txtCheck->Disable();
		FillDatatype(cbDatatype, false);

		cbCollation->Enable(connection->BackendMinimumVersion(9, 1));
		if (connection->BackendMinimumVersion(9, 1))
		{
			// fill collation combobox
			cbCollation->Append(wxEmptyString);
			pgSet *set = connection->ExecuteSet(
			                 wxT("SELECT nspname, collname\n")
			                 wxT("  FROM pg_collation c, pg_namespace n\n")
			                 wxT("  WHERE c.collnamespace=n.oid\n")
			                 wxT("  ORDER BY nspname, collname"));
			if (set)
			{
				while (!set->Eof())
				{
					wxString name = qtIdent(set->GetVal(wxT("nspname"))) + wxT(".") + qtIdent(set->GetVal(wxT("collname")));
					cbCollation->Append(name);
					set->MoveNext();
				}
				delete set;
			}
			cbCollation->SetSelection(0);
		}
	}

	return dlgProperty::Go(modal);
}


pgObject *dlgDomain::CreateObject(pgCollection *collection)
{
	wxString name = GetName();

	pgObject *obj = domainFactory.CreateObjects(collection, 0,
	                wxT("   AND d.typname=") + qtDbString(name) +
	                wxT("\n   AND d.typnamespace=") + schema->GetOidStr() +
	                wxT("\n"));
	return obj;
}


void dlgDomain::CheckChange()
{
	if (domain)
	{
		EnableOK(txtDefault->GetValue() != domain->GetDefault()
		         || cbSchema->GetValue() != domain->GetSchema()->GetName()
		         || chkNotNull->GetValue() != domain->GetNotNull()
		         || cbOwner->GetValue() != domain->GetOwner()
		         || txtComment->GetValue() != domain->GetComment());
	}
	else
	{
		wxString name = GetName();
		long varlen = StrToLong(txtLength->GetValue()),
		     varprec = StrToLong(txtPrecision->GetValue());

		txtPrecision->Enable(isVarPrec && varlen > 0);

		bool enable = true;
		CheckValid(enable, !name.IsEmpty(), _("Please specify name."));
		CheckValid(enable, cbDatatype->GetGuessedSelection() >= 0, _("Please select a datatype."));
		CheckValid(enable, !isVarLen || txtLength->GetValue().IsEmpty()
		           || (varlen >= minVarLen && varlen <= maxVarLen && NumToStr(varlen) == txtLength->GetValue()),
		           _("Please specify valid length."));
		CheckValid(enable, !txtPrecision->IsEnabled()
		           || (varprec >= 0 && varprec <= varlen && NumToStr(varprec) == txtPrecision->GetValue()),
		           _("Please specify valid numeric precision (0..") + NumToStr(varlen) + wxT(")."));

		EnableOK(enable);
	}
}



void dlgDomain::OnSelChangeTyp(wxCommandEvent &ev)
{
	if (!domain)
	{
		cbDatatype->GuessSelection(ev);
		CheckLenEnable();
		txtLength->Enable(isVarLen);
		CheckChange();
	}
}


wxString dlgDomain::GetSql()
{
	wxString sql, name;

	if (domain)
	{
		// edit mode
		name = GetName();

		if (chkNotNull->GetValue() != domain->GetNotNull())
		{
			sql += wxT("ALTER DOMAIN ") + domain->GetQuotedFullIdentifier();
			if (chkNotNull->GetValue())
				sql += wxT("\n  SET NOT NULL;\n");
			else
				sql += wxT("\n  DROP NOT NULL;\n");
		}
		if (txtDefault->GetValue() != domain->GetDefault())
		{
			sql += wxT("ALTER DOMAIN ") + domain->GetQuotedFullIdentifier();
			if (txtDefault->GetValue().IsEmpty())
				sql += wxT("\n  DROP DEFAULT;\n");
			else
				sql += wxT("\n  SET DEFAULT ") + txtDefault->GetValue() + wxT(";\n");
		}
		AppendOwnerChange(sql, wxT("DOMAIN ") + domain->GetQuotedFullIdentifier());
		AppendSchemaChange(sql, wxT("DOMAIN ") + domain->GetQuotedFullIdentifier());
	}
	else
	{
		// create mode
		name = qtIdent(cbSchema->GetValue()) + wxT(".") + qtIdent(GetName());
		sql = wxT("CREATE DOMAIN ") + name
		      + wxT("\n   AS ") + GetQuotedTypename(cbDatatype->GetGuessedSelection());

		if (!cbCollation->GetValue().IsEmpty() && cbCollation->GetValue() != wxT("pg_catalog.\"default\""))
			sql += wxT("\n   COLLATE ") + cbCollation->GetValue();

		AppendIfFilled(sql, wxT("\n   DEFAULT "), txtDefault->GetValue());
		if (chkNotNull->GetValue())
			sql += wxT("\n   NOT NULL");
		if (!txtCheck->GetValue().IsEmpty())
			sql += wxT("\n   CHECK (") + txtCheck->GetValue() + wxT(")");
		sql += wxT(";\n");

		AppendOwnerNew(sql, wxT("DOMAIN ") + name);
	}
	AppendComment(sql, wxT("DOMAIN ") + qtIdent(cbSchema->GetValue()) + wxT(".") + qtIdent(GetName()), domain);

	return sql;
}

