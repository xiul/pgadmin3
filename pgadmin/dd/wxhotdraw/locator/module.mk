#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/wxhotdraw/locator/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/wxhotdraw/locator/ddILocator.cpp \
	$(srcdir)/dd/wxhotdraw/locator/ddPolyLineLocator.cpp

EXTRA_DIST += \
	$(srcdir)/dd/wxhotdraw/locator/module.mk
