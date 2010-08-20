#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/draw/utilities/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/draw/utilities/ddArrayCollection.cpp \
	$(srcdir)/dd/draw/utilities/ddCollection.cpp \
	$(srcdir)/dd/draw/utilities/ddGeometry.cpp \
	$(srcdir)/dd/draw/utilities/ddMouseEvent.cpp \
	$(srcdir)/dd/draw/utilities/ddPoint.cpp \
	$(srcdir)/dd/draw/utilities/ddRect.cpp

EXTRA_DIST += \
	$(srcdir)/dd/draw/utilities/module.mk
