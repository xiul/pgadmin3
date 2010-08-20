#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/draw/tools/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/draw/tools/ddAbstractTool.h \
	$(srcdir)/include/dd/draw/tools/ddCompositeFigureTool.h \
	$(srcdir)/include/dd/draw/tools/ddConnectionCreationTool.h \
	$(srcdir)/include/dd/draw/tools/ddCreationTool.h \
	$(srcdir)/include/dd/draw/tools/ddDragCreationTool.h \
	$(srcdir)/include/dd/draw/tools/ddDragTrackerTool.h \
	$(srcdir)/include/dd/draw/tools/ddFigureTool.h \
	$(srcdir)/include/dd/draw/tools/ddHandleTrackerTool.h \
	$(srcdir)/include/dd/draw/tools/ddITool.h \
	$(srcdir)/include/dd/draw/tools/ddMenuTool.h \
	$(srcdir)/include/dd/draw/tools/ddPolyLineFigureTool.h \
	$(srcdir)/include/dd/draw/tools/ddSelectAreaTool.h \
	$(srcdir)/include/dd/draw/tools/ddSelectionTool.h \
	$(srcdir)/include/dd/draw/tools/ddSimpleTextTool.h

EXTRA_DIST += \
	$(srcdir)/include/dd/draw/tools/module.mk
