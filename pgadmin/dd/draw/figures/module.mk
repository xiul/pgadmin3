#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/draw/figures/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/draw/figures/ddAbstractFigure.cpp \
	$(srcdir)/dd/draw/figures/ddAbstractMenuFigure.cpp \
	$(srcdir)/dd/draw/figures/ddBitmapFigure.cpp \
	$(srcdir)/dd/draw/figures/ddCompositeFigure.cpp \
	$(srcdir)/dd/draw/figures/ddIConnectionFigure.cpp \
	$(srcdir)/dd/draw/figures/ddIFigure.cpp \
	$(srcdir)/dd/draw/figures/ddLineConnection.cpp \
	$(srcdir)/dd/draw/figures/ddLineTerminal.cpp \
	$(srcdir)/dd/draw/figures/ddPolyLineFigure.cpp \
	$(srcdir)/dd/draw/figures/ddRectangleFigure.cpp \
	$(srcdir)/dd/draw/figures/ddSimpleTextFigure.cpp

EXTRA_DIST += \
	$(srcdir)/dd/draw/figures/module.mk
