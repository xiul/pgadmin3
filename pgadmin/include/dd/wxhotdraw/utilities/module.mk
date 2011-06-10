#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/wxhotdraw/utilities/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/wxhotdraw/utilities/ddArrayCollection.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/ddCollection.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/ddCollectionBase.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/ddGeometry.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/ddMouseEvent.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/ddPoint.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/ddRect.h

EXTRA_DIST += \
	$(srcdir)/include/dd/wxhotdraw/utilities/module.mk
