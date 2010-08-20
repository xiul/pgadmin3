#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/draw/handles/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/draw/handles/ddButtonHandle.h \
	$(srcdir)/include/dd/draw/handles/ddChangeConnectionEndHandle.h \
	$(srcdir)/include/dd/draw/handles/ddChangeConnectionHandle.h \
	$(srcdir)/include/dd/draw/handles/ddChangeConnectionStartHandle.h \
	$(srcdir)/include/dd/draw/handles/ddIHandle.h \
	$(srcdir)/include/dd/draw/handles/ddLineConnectionHandle.h \
	$(srcdir)/include/dd/draw/handles/ddLocatorHandle.h \
	$(srcdir)/include/dd/draw/handles/ddPolyLineHandle.h

EXTRA_DIST += \
	$(srcdir)/include/dd/draw/handles/module.mk
