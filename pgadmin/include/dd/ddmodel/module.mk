#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2011, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/ddmodel/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/ddmodel/ddBrowserDataContainer.h \
	$(srcdir)/include/dd/ddmodel/ddDatabaseDesign.h \
	$(srcdir)/include/dd/ddmodel/ddDrawingEditor.h \
	$(srcdir)/include/dd/ddmodel/ddDrawingView.h \
	$(srcdir)/include/dd/ddmodel/ddModelBrowser.h \
	$(srcdir)/include/dd/ddmodel/ddTextEditor.h
	
EXTRA_DIST += \
	$(srcdir)/include/dd/ddmodel/module.mk
