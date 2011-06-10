#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/draw/connectors/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/draw/connectors/ddChopBoxConnector.h \
	$(srcdir)/include/dd/draw/connectors/ddIConnector.h \
	$(srcdir)/include/dd/draw/connectors/ddLocatorConnector.h \
	$(srcdir)/include/dd/draw/connectors/ddStickyRectangleConnector.h

EXTRA_DIST += \
	$(srcdir)/include/dd/draw/connectors/module.mk
