#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/draw/tools/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/draw/tools/ddAbstractTool.cpp \
	$(srcdir)/dd/draw/tools/ddCompositeFigureTool.cpp \
	$(srcdir)/dd/draw/tools/ddConnectionCreationTool.cpp \
	$(srcdir)/dd/draw/tools/ddCreationTool.cpp \
	$(srcdir)/dd/draw/tools/ddDragCreationTool.cpp \
	$(srcdir)/dd/draw/tools/ddDragTrackerTool.cpp \
	$(srcdir)/dd/draw/tools/ddFigureTool.cpp \
	$(srcdir)/dd/draw/tools/ddHandleTrackerTool.cpp \
	$(srcdir)/dd/draw/tools/ddITool.cpp \
	$(srcdir)/dd/draw/tools/ddMenuTool.cpp \
	$(srcdir)/dd/draw/tools/ddPolyLineFigureTool.cpp \
	$(srcdir)/dd/draw/tools/ddSelectAreaTool.cpp \
	$(srcdir)/dd/draw/tools/ddSelectionTool.cpp \
	$(srcdir)/dd/draw/tools/ddSimpleTextTool.cpp

EXTRA_DIST += \
	$(srcdir)/dd/draw/tools/module.mk
