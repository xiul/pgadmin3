#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/draw/ Makefile fragment
#
#######################################################################

include $(srcdir)/include/dd/draw/connectors/module.mk
include $(srcdir)/include/dd/draw/figures/module.mk
include $(srcdir)/include/dd/draw/handles/module.mk
include $(srcdir)/include/dd/draw/locators/module.mk
include $(srcdir)/include/dd/draw/main/module.mk
include $(srcdir)/include/dd/draw/tools/module.mk
include $(srcdir)/include/dd/draw/utilities/module.mk

EXTRA_DIST += \
	$(srcdir)/include/dd/draw/module.mk
