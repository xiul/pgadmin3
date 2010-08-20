#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/draw/connectors/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/draw/connectors/ddChopBoxConnector.cpp \
	$(srcdir)/dd/draw/connectors/ddIConnector.cpp

EXTRA_DIST += \
	$(srcdir)/dd/draw/connectors/module.mk
