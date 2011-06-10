#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/wxhotdraw/utilities/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/wxhotdraw/utilities/ddArrayCollection.cpp \
	$(srcdir)/dd/wxhotdraw/utilities/ddCollection.cpp \
	$(srcdir)/dd/wxhotdraw/utilities/ddGeometry.cpp \
	$(srcdir)/dd/wxhotdraw/utilities/ddMouseEvent.cpp \
	$(srcdir)/dd/wxhotdraw/utilities/ddPoint.cpp \
	$(srcdir)/dd/wxhotdraw/utilities/ddRect.cpp

EXTRA_DIST += \
	$(srcdir)/dd/wxhotdraw/utilities/module.mk
