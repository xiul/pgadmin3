#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/wxhotdraw/main/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/wxhotdraw/main/ddDrawing.h \
	$(srcdir)/include/dd/wxhotdraw/main/ddDrawingEditor.h \
	$(srcdir)/include/dd/wxhotdraw/main/ddDrawingView.h \
	$(srcdir)/include/dd/wxhotdraw/main/ddObject.h

EXTRA_DIST += \
	$(srcdir)/include/dd/wxhotdraw/main/module.mk
