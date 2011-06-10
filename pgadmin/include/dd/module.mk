#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/ Makefile fragment
#
#######################################################################

include $(srcdir)/include/dd/dditems/module.mk
include $(srcdir)/include/dd/ddmodel/module.mk
include $(srcdir)/include/dd/wxhotdraw/module.mk


EXTRA_DIST += \
	$(srcdir)/include/dd/module.mk
