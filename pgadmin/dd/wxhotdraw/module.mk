#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# 
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/draw/ Makefile fragment
#
#######################################################################

include $(srcdir)/dd/draw/connectors/module.mk
include $(srcdir)/dd/draw/figures/module.mk
include $(srcdir)/dd/draw/handles/module.mk
include $(srcdir)/dd/draw/locator/module.mk
include $(srcdir)/dd/draw/main/module.mk
include $(srcdir)/dd/draw/tools/module.mk
include $(srcdir)/dd/draw/utilities/module.mk

EXTRA_DIST += \
	$(srcdir)/dd/draw/module.mk
