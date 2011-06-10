#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/wxhotdraw/figures/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/wxhotdraw/figures/ddAbstractFigure.cpp \
	$(srcdir)/dd/wxhotdraw/figures/ddAbstractMenuFigure.cpp \
	$(srcdir)/dd/wxhotdraw/figures/ddAttribute.cpp \
	$(srcdir)/dd/wxhotdraw/figures/ddAttributeFigure.cpp \
	$(srcdir)/dd/wxhotdraw/figures/ddBitmapFigure.cpp \
	$(srcdir)/dd/wxhotdraw/figures/ddCompositeFigure.cpp \
	$(srcdir)/dd/wxhotdraw/figures/ddIConnectionFigure.cpp \
	$(srcdir)/dd/wxhotdraw/figures/ddIFigure.cpp \
	$(srcdir)/dd/wxhotdraw/figures/ddLineConnection.cpp \
	$(srcdir)/dd/wxhotdraw/figures/ddLineTerminal.cpp \
	$(srcdir)/dd/wxhotdraw/figures/ddPolyLineFigure.cpp \
	$(srcdir)/dd/wxhotdraw/figures/ddRectangleFigure.cpp \
	$(srcdir)/dd/wxhotdraw/figures/ddSimpleTextFigure.cpp

EXTRA_DIST += \
	$(srcdir)/dd/wxhotdraw/figures/module.mk
