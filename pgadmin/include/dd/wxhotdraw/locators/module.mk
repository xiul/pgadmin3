#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/wxhotdraw/locator/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/wxhotdraw/locator/ddILocator.h \
	$(srcdir)/include/dd/wxhotdraw/locator/ddPolyLineLocator.h

EXTRA_DIST += \
	$(srcdir)/include/dd/wxhotdraw/locator/module.mk
