#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/wxhotdraw/tools/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/wxhotdraw/tools/ddAbstractTool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddCompositeFigureTool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddConnectionCreationTool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddCreationTool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddDragCreationTool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddDragTrackerTool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddFigureTool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddHandleTrackerTool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddITool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddMenuTool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddPolyLineFigureTool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddSelectAreaTool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddSelectionTool.h \
	$(srcdir)/include/dd/wxhotdraw/tools/ddSimpleTextTool.h

EXTRA_DIST += \
	$(srcdir)/include/dd/wxhotdraw/tools/module.mk
