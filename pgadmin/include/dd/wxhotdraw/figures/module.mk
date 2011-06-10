#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/draw/figures/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/draw/figures/ddAbstractFigure.h \
	$(srcdir)/include/dd/draw/figures/ddAbstractMenuFigure.h \
	$(srcdir)/include/dd/draw/figures/ddAttribute.h \
	$(srcdir)/include/dd/draw/figures/ddAttributeFigure.h \
	$(srcdir)/include/dd/draw/figures/ddBitmapFigure.h \
	$(srcdir)/include/dd/draw/figures/ddCompositeFigure.h \
	$(srcdir)/include/dd/draw/figures/ddIConnectionFigure.h \
	$(srcdir)/include/dd/draw/figures/ddIFigure.h \
	$(srcdir)/include/dd/draw/figures/ddLineConnection.h \
	$(srcdir)/include/dd/draw/figures/ddLineTerminal.h \
	$(srcdir)/include/dd/draw/figures/ddPolyLineFigure.h \
	$(srcdir)/include/dd/draw/figures/ddRectangleFigure.h \
	$(srcdir)/include/dd/draw/figures/ddSimpleTextFigure.h

EXTRA_DIST += \
	$(srcdir)/include/dd/draw/figures/module.mk
