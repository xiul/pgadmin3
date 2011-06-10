#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/wxhotdraw/handles/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dd/wxhotdraw/handles/ddButtonHandle.h \
	$(srcdir)/include/dd/wxhotdraw/handles/ddChangeConnectionEndHandle.h \
	$(srcdir)/include/dd/wxhotdraw/handles/ddChangeConnectionHandle.h \
	$(srcdir)/include/dd/wxhotdraw/handles/ddChangeConnectionStartHandle.h \
	$(srcdir)/include/dd/wxhotdraw/handles/ddIHandle.h \
	$(srcdir)/include/dd/wxhotdraw/handles/ddLineConnectionHandle.h \
	$(srcdir)/include/dd/wxhotdraw/handles/ddLocatorHandle.h \
	$(srcdir)/include/dd/wxhotdraw/handles/ddPolyLineHandle.h

EXTRA_DIST += \
	$(srcdir)/include/dd/wxhotdraw/handles/module.mk
