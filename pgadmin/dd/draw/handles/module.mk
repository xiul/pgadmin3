#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/draw/handles/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/draw/handles/ddButtonHandle.cpp \
	$(srcdir)/dd/draw/handles/ddChangeConnectionEndHandle.cpp \
	$(srcdir)/dd/draw/handles/ddChangeConnectionHandle.cpp \
	$(srcdir)/dd/draw/handles/ddChangeConnectionStartHandle.cpp \
	$(srcdir)/dd/draw/handles/ddIHandle.cpp \
	$(srcdir)/dd/draw/handles/ddLineConnectionHandle.cpp \
	$(srcdir)/dd/draw/handles/ddLocatorHandle.cpp \
	$(srcdir)/dd/draw/handles/ddPolyLineHandle.cpp

EXTRA_DIST += \
	$(srcdir)/dd/draw/handles/module.mk
