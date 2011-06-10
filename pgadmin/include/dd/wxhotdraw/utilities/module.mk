#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/draw/utilities/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/draw/utilities/ddArrayCollection.h \
	$(srcdir)/include/dd/draw/utilities/ddCollection.h \
	$(srcdir)/include/dd/draw/utilities/ddCollectionBase.h \
	$(srcdir)/include/dd/draw/utilities/ddGeometry.h \
	$(srcdir)/include/dd/draw/utilities/ddMouseEvent.h \
	$(srcdir)/include/dd/draw/utilities/ddPoint.h \
	$(srcdir)/include/dd/draw/utilities/ddRect.h

EXTRA_DIST += \
	$(srcdir)/include/dd/draw/utilities/module.mk
