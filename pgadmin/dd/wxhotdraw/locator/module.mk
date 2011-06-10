#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/draw/locator/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/draw/locator/ddILocator.cpp \
	$(srcdir)/dd/draw/locator/ddPolyLineLocator.cpp

EXTRA_DIST += \
	$(srcdir)/dd/draw/locator/module.mk
