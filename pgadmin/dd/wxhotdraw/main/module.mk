#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/wxhotdraw/main/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/wxhotdraw/main/ddDrawing.cpp \
	$(srcdir)/dd/wxhotdraw/main/ddDrawingEditor.cpp \
	$(srcdir)/dd/wxhotdraw/main/ddDrawingView.cpp

EXTRA_DIST += \
	$(srcdir)/dd/wxhotdraw/main/module.mk
