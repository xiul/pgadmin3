#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/wxhotdraw/connectors/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/wxhotdraw/connectors/ddChopBoxConnector.h \
	$(srcdir)/include/dd/wxhotdraw/connectors/ddIConnector.h \
	$(srcdir)/include/dd/wxhotdraw/connectors/ddLocatorConnector.h \
	$(srcdir)/include/dd/wxhotdraw/connectors/ddStickyRectangleConnector.h

EXTRA_DIST += \
	$(srcdir)/include/dd/wxhotdraw/connectors/module.mk
