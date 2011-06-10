#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/draw/main/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/draw/main/ddDrawing.h \
	$(srcdir)/include/dd/draw/main/ddDrawingEditor.h \
	$(srcdir)/include/dd/draw/main/ddDrawingView.h \
	$(srcdir)/include/dd/draw/main/ddObject.h

EXTRA_DIST += \
	$(srcdir)/include/dd/draw/main/module.mk
