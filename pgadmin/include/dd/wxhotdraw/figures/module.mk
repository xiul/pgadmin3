#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/wxhotdraw/figures/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/wxhotdraw/figures/ddAbstractFigure.h \
	$(srcdir)/include/dd/wxhotdraw/figures/ddAbstractMenuFigure.h \
	$(srcdir)/include/dd/wxhotdraw/figures/ddAttribute.h \
	$(srcdir)/include/dd/wxhotdraw/figures/ddAttributeFigure.h \
	$(srcdir)/include/dd/wxhotdraw/figures/ddBitmapFigure.h \
	$(srcdir)/include/dd/wxhotdraw/figures/ddCompositeFigure.h \
	$(srcdir)/include/dd/wxhotdraw/figures/ddIConnectionFigure.h \
	$(srcdir)/include/dd/wxhotdraw/figures/ddIFigure.h \
	$(srcdir)/include/dd/wxhotdraw/figures/ddLineConnection.h \
	$(srcdir)/include/dd/wxhotdraw/figures/ddLineTerminal.h \
	$(srcdir)/include/dd/wxhotdraw/figures/ddPolyLineFigure.h \
	$(srcdir)/include/dd/wxhotdraw/figures/ddRectangleFigure.h \
	$(srcdir)/include/dd/wxhotdraw/figures/ddSimpleTextFigure.h

EXTRA_DIST += \
	$(srcdir)/include/dd/wxhotdraw/figures/module.mk
