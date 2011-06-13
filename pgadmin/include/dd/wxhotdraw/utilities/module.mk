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
	$(srcdir)/include/dd/wxhotdraw/utilities/wxhdArrayCollection.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/wxhdCollection.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/wxhdCollectionBase.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/wxhdGeometry.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/wxhdKeyEvent.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/wxhdMouseEvent.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/wxhdPoint.h \
	$(srcdir)/include/dd/wxhotdraw/utilities/wxhdRect.h

EXTRA_DIST += \
	$(srcdir)/include/dd/wxhotdraw/utilities/module.mk
