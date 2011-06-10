#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/wxhotdraw/handles/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dd/wxhotdraw/handles/ddButtonHandle.cpp \
	$(srcdir)/dd/wxhotdraw/handles/ddChangeConnectionEndHandle.cpp \
	$(srcdir)/dd/wxhotdraw/handles/ddChangeConnectionHandle.cpp \
	$(srcdir)/dd/wxhotdraw/handles/ddChangeConnectionStartHandle.cpp \
	$(srcdir)/dd/wxhotdraw/handles/ddIHandle.cpp \
	$(srcdir)/dd/wxhotdraw/handles/ddLineConnectionHandle.cpp \
	$(srcdir)/dd/wxhotdraw/handles/ddLocatorHandle.cpp \
	$(srcdir)/dd/wxhotdraw/handles/ddPolyLineHandle.cpp

EXTRA_DIST += \
	$(srcdir)/dd/wxhotdraw/handles/module.mk
