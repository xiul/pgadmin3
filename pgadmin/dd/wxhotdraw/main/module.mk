#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/draw/main/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/draw/main/ddDrawing.cpp \
	$(srcdir)/dd/draw/main/ddDrawingEditor.cpp \
	$(srcdir)/dd/draw/main/ddDrawingView.cpp

EXTRA_DIST += \
	$(srcdir)/dd/draw/main/module.mk
