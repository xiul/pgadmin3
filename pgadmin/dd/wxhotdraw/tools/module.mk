#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/wxhotdraw/tools/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/wxhotdraw/tools/ddAbstractTool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddCompositeFigureTool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddConnectionCreationTool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddCreationTool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddDragCreationTool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddDragTrackerTool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddFigureTool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddHandleTrackerTool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddITool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddMenuTool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddPolyLineFigureTool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddSelectAreaTool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddSelectionTool.cpp \
	$(srcdir)/dd/wxhotdraw/tools/ddSimpleTextTool.cpp

EXTRA_DIST += \
	$(srcdir)/dd/wxhotdraw/tools/module.mk
