#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/draw/locator/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/draw/locator/ddILocator.h \
	$(srcdir)/include/dd/draw/locator/ddPolyLineLocator.h

EXTRA_DIST += \
	$(srcdir)/include/dd/draw/locator/module.mk
