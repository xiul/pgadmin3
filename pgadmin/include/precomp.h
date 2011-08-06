//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// precomp.h - All header files for compilers supporting precompiled headers
//
//////////////////////////////////////////////////////////////////////////

#ifdef WX_PRECOMP

#include "copyright.h"
#include "pgAdmin3.h"
#include "version.h"

#include "agent/dlgJob.h"
#include "agent/dlgSchedule.h"
#include "agent/dlgStep.h"
#include "agent/pgaJob.h"
#include "agent/pgaSchedule.h"
#include "agent/pgaStep.h"

#include "ctl/calbox.h"
#include "ctl/ctlAuiNotebook.h"
#include "ctl/ctlCheckTreeView.h"
#include "ctl/ctlColourPicker.h"
#include "ctl/ctlComboBox.h"
#include "ctl/ctlListView.h"
#include "ctl/ctlSecurityPanel.h"
#include "ctl/ctlSQLBox.h"
#include "ctl/ctlSQLGrid.h"
#include "ctl/ctlSQLResult.h"
#include "ctl/ctlTree.h"
#include "ctl/explainCanvas.h"
#include "ctl/timespin.h"
#include "ctl/wxgridsel.h"
#include "ctl/xh_calb.h"
#include "ctl/xh_ctlcombo.h"
#include "ctl/xh_ctlchecktreeview.h"
#include "ctl/xh_ctlcolourpicker.h"
#include "ctl/xh_ctltree.h"
#include "ctl/xh_sqlbox.h"
#include "ctl/xh_timespin.h"

#include "db/pgConn.h"
#include "db/pgQueryThread.h"
#include "db/pgSet.h"

#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/dditems/figures/ddColumnKindIcon.h"
#include "dd/dditems/figures/ddColumnOptionIcon.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"
#include "dd/dditems/figures/ddRelationshipItem.h"
#include "dd/dditems/figures/ddRelationshipTerminal.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddTextTableItemFigure.h"
#include "dd/dditems/handles/ddAddColButtonHandle.h"
#include "dd/dditems/handles/ddAddFkButtonHandle.h"
#include "dd/dditems/handles/ddMinMaxTableButtonHandle.h"
#include "dd/dditems/handles/ddRemoveTableButtonHandle.h"
#include "dd/dditems/handles/ddScrollBarHandle.h"
#include "dd/dditems/handles/ddSouthTableSizeHandle.h"
#include "dd/dditems/locators/ddAddColLocator.h"
#include "dd/dditems/locators/ddAddFkLocator.h"
#include "dd/dditems/locators/ddMinMaxTableLocator.h"
#include "dd/dditems/locators/ddRemoveTableLocator.h"
#include "dd/dditems/locators/ddScrollBarTableLocator.h"
#include "dd/dditems/locators/ddTableBottomLocator.h"
#include "dd/dditems/tools/ddColumnFigureTool.h"
#include "dd/dditems/tools/ddColumnTextTool.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/dditems/utilities/ddPrecisionScaleDialog.h"
#include "dd/dditems/utilities/ddSelectKindFksDialog.h"
#include "dd/dditems/utilities/ddTableNameDialog.h"
#include "dd/ddmodel/ddDatabaseDesign.h"
#include "dd/ddmodel/ddDrawingEditor.h"
#include "dd/ddmodel/ddDrawingView.h"
#include "dd/ddmodel/ddBrowserDataContainer.h"
#include "dd/ddmodel/ddModelBrowser.h"
#include "dd/ddmodel/ddTextEditor.h"
#include "dd/wxhotdraw/connectors/wxhdChopBoxConnector.h"
#include "dd/wxhotdraw/connectors/wxhdIConnector.h"
#include "dd/wxhotdraw/connectors/wxhdLocatorConnector.h"
#include "dd/wxhotdraw/connectors/wxhdStickyRectangleConnector.h"
#include "dd/wxhotdraw/figures/wxhdAbstractFigure.h"
#include "dd/wxhotdraw/figures/wxhdAbstractMenuFigure.h"
#include "dd/wxhotdraw/figures/wxhdAttribute.h"
#include "dd/wxhotdraw/figures/wxhdAttributeFigure.h"
#include "dd/wxhotdraw/figures/wxhdBitmapFigure.h"
#include "dd/wxhotdraw/figures/wxhdCompositeFigure.h"
#include "dd/wxhotdraw/figures/wxhdIConnectionFigure.h"
#include "dd/wxhotdraw/figures/wxhdIFigure.h"
#include "dd/wxhotdraw/figures/wxhdLineConnection.h"
#include "dd/wxhotdraw/figures/wxhdLineTerminal.h"
#include "dd/wxhotdraw/figures/wxhdPolyLineFigure.h"
#include "dd/wxhotdraw/figures/wxhdRectangleFigure.h"
#include "dd/wxhotdraw/figures/wxhdSimpleTextFigure.h"
#include "dd/wxhotdraw/figures/defaultAttributes/wxhdFillAttribute.h"
#include "dd/wxhotdraw/figures/defaultAttributes/wxhdFontAttribute.h"
#include "dd/wxhotdraw/figures/defaultAttributes/wxhdFontColorAttribute.h"
#include "dd/wxhotdraw/figures/defaultAttributes/wxhdLineAttribute.h"
#include "dd/wxhotdraw/handles/wxhdButtonHandle.h"
#include "dd/wxhotdraw/handles/wxhdChangeConnectionEndHandle.h"
#include "dd/wxhotdraw/handles/wxhdChangeConnectionHandle.h"
#include "dd/wxhotdraw/handles/wxhdChangeConnectionStartHandle.h"
#include "dd/wxhotdraw/handles/wxhdIHandle.h"
#include "dd/wxhotdraw/handles/wxhdLineConnectionHandle.h"
#include "dd/wxhotdraw/handles/wxhdLocatorHandle.h"
#include "dd/wxhotdraw/handles/wxhdPolyLineHandle.h"
#include "dd/wxhotdraw/locators/wxhdILocator.h"
#include "dd/wxhotdraw/locators/wxhdPolyLineLocator.h"
#include "dd/wxhotdraw/main/wxhdDrawing.h"
#include "dd/wxhotdraw/main/wxhdDrawingEditor.h"
#include "dd/wxhotdraw/main/wxhdDrawingView.h"
#include "dd/wxhotdraw/main/wxhdObject.h"
#include "dd/wxhotdraw/tools/wxhdAbstractTool.h"
#include "dd/wxhotdraw/tools/wxhdCanvasMenuTool.h"
#include "dd/wxhotdraw/tools/wxhdCompositeFigureTool.h"
#include "dd/wxhotdraw/tools/wxhdConnectionCreationTool.h"
#include "dd/wxhotdraw/tools/wxhdCreationTool.h"
#include "dd/wxhotdraw/tools/wxhdDragCreationTool.h"
#include "dd/wxhotdraw/tools/wxhdDragTrackerTool.h"
#include "dd/wxhotdraw/tools/wxhdFigureTool.h"
#include "dd/wxhotdraw/tools/wxhdHandleTrackerTool.h"
#include "dd/wxhotdraw/tools/wxhdITool.h"
#include "dd/wxhotdraw/tools/wxhdMenuTool.h"
#include "dd/wxhotdraw/tools/wxhdPolyLineFigureTool.h"
#include "dd/wxhotdraw/tools/wxhdSelectAreaTool.h"
#include "dd/wxhotdraw/tools/wxhdSelectionTool.h"
#include "dd/wxhotdraw/tools/wxhdSimpleTextTool.h"
#include "dd/wxhotdraw/utilities/wxhdArrayCollection.h"
#include "dd/wxhotdraw/utilities/wxhdCollection.h"
#include "dd/wxhotdraw/utilities/wxhdCollectionBase.h"
#include "dd/wxhotdraw/utilities/wxhdGeometry.h"
#include "dd/wxhotdraw/utilities/wxhdKeyEvent.h"
#include "dd/wxhotdraw/utilities/wxhdMouseEvent.h"
#include "dd/wxhotdraw/utilities/wxhdPoint.h"
#include "dd/wxhotdraw/utilities/wxhdMultiPosRect.h"
#include "dd/wxhotdraw/utilities/wxhdRemoveDeleteDialog.h"
#include "dd/wxhotdraw/utilities/wxhdRect.h"

#include "debugger/ctlCodeWindow.h"
#include "debugger/ctlMessageWindow.h"
#include "debugger/ctlResultGrid.h"
#include "debugger/ctlStackWindow.h"
#include "debugger/ctlTabWindow.h"
#include "debugger/ctlVarWindow.h"
#include "debugger/dbgBreakPoint.h"
#include "debugger/dbgConnProp.h"
#include "debugger/dbgConst.h"
#include "debugger/dbgDbResult.h"
#include "debugger/dbgPgConn.h"
#include "debugger/dbgPgThread.h"
#include "debugger/dbgResultset.h"
#include "debugger/dbgTargetInfo.h"
#include "debugger/debugger.h"
#include "debugger/dlgDirectDbg.h"
#include "debugger/frmDebugger.h"

#include "dlg/dlgAddFavourite.h"
#include "dlg/dlgAggregate.h"
#include "dlg/dlgCast.h"
#include "dlg/dlgCheck.h"
#include "dlg/dlgClasses.h"
#include "dlg/dlgColumn.h"
#include "dlg/dlgConnect.h"
#include "dlg/dlgConversion.h"
#include "dlg/dlgDatabase.h"
#include "dlg/dlgDomain.h"
#include "dlg/dlgEditGridOptions.h"
#include "dlg/dlgFindReplace.h"
#include "dlg/dlgForeignDataWrapper.h"
#include "dlg/dlgForeignKey.h"
#include "dlg/dlgForeignServer.h"
#include "dlg/dlgFunction.h"
#include "dlg/dlgGroup.h"
#include "dlg/dlgHbaConfig.h"
#include "dlg/dlgIndex.h"
#include "dlg/dlgIndexConstraint.h"
#include "dlg/dlgLanguage.h"
#include "dlg/dlgMainConfig.h"
#include "dlg/dlgManageFavourites.h"
#include "dlg/dlgManageMacros.h"
#include "dlg/dlgOperator.h"
#include "dlg/dlgPackage.h"
#include "dlg/dlgPgpassConfig.h"
#include "dlg/dlgProperty.h"
#include "dlg/dlgRole.h"
#include "dlg/dlgRule.h"
#include "dlg/dlgSchema.h"
#include "dlg/dlgSelectConnection.h"
#include "dlg/dlgSelectDatabase.h"
#include "dlg/dlgSequence.h"
#include "dlg/dlgServer.h"
#include "dlg/dlgSynonym.h"
#include "dlg/dlgTable.h"
#include "dlg/dlgTablespace.h"
#include "dlg/dlgTextSearchConfiguration.h"
#include "dlg/dlgTextSearchDictionary.h"
#include "dlg/dlgTextSearchTemplate.h"
#include "dlg/dlgTextSearchParser.h"
#include "dlg/dlgTrigger.h"
#include "dlg/dlgType.h"
#include "dlg/dlgUser.h"
#include "dlg/dlgUserMapping.h"
#include "dlg/dlgView.h"
#include "dlg/dlgExtTable.h"

#include "frm/frmAbout.h"
#include "frm/frmBackup.h"
#include "frm/frmConfig.h"
#include "frm/frmEditGrid.h"
#include "frm/frmExport.h"
#include "frm/frmGrantWizard.h"
#include "frm/frmHbaConfig.h"
#include "frm/frmHint.h"
#include "frm/frmMain.h"
#include "frm/frmMainConfig.h"
#include "frm/frmMaintenance.h"
#include "frm/frmOptions.h"
#include "frm/frmPassword.h"
#include "frm/frmPgpassConfig.h"
#include "frm/frmQuery.h"
#include "frm/frmReport.h"
#include "frm/frmRestore.h"
#include "frm/frmSplash.h"
#include "frm/frmStatus.h"
#include "frm/menu.h"

#include "ogl/basic.h"
#include "ogl/basicp.h"
#include "ogl/bmpshape.h"
#include "ogl/canvas.h"
#include "ogl/composit.h"
#include "ogl/constrnt.h"
#include "ogl/divided.h"
#include "ogl/drawn.h"
#include "ogl/drawnp.h"
#include "ogl/lines.h"
#include "ogl/linesp.h"
#include "ogl/mfutils.h"
#include "ogl/misc.h"
#include "ogl/ogl.h"
#include "ogl/ogldiag.h"

#include "gqb/gqbArrayCollection.h"
#include "gqb/gqbBrowser.h"
#include "gqb/gqbCollection.h"
#include "gqb/gqbCollectionBase.h"
#include "gqb/gqbColumn.h"
#include "gqb/gqbDatabase.h"
#include "gqb/gqbEvents.h"
#include "gqb/gqbGraphBehavior.h"
#include "gqb/gqbGraphSimple.h"
#include "gqb/gqbGridOrderTable.h"
#include "gqb/gqbGridProjTable.h"
#include "gqb/gqbGridRestTable.h"
#include "gqb/gqbModel.h"
#include "gqb/gqbObject.h"
#include "gqb/gqbObjectCollection.h"
#include "gqb/gqbQueryObjs.h"
#include "gqb/gqbSchema.h"
#include "gqb/gqbTable.h"
#include "gqb/gqbViewController.h"
#include "gqb/gqbViewPanels.h"

#include "schema/edbPackage.h"
#include "schema/edbPackageFunction.h"
#include "schema/edbPackageVariable.h"
#include "schema/edbSynonym.h"
#include "schema/pgAggregate.h"
#include "schema/pgCast.h"
#include "schema/pgCatalogObject.h"
#include "schema/pgCheck.h"
#include "schema/pgCollection.h"
#include "schema/pgColumn.h"
#include "schema/pgConstraints.h"
#include "schema/pgConversion.h"
#include "schema/pgDatabase.h"
#include "schema/pgDatatype.h"
#include "schema/pgDomain.h"
#include "schema/pgForeignDataWrapper.h"
#include "schema/pgForeignKey.h"
#include "schema/pgForeignServer.h"
#include "schema/pgFunction.h"
#include "schema/pgGroup.h"
#include "schema/pgIndex.h"
#include "schema/pgIndexConstraint.h"
#include "schema/pgLanguage.h"
#include "schema/pgObject.h"
#include "schema/pgOperator.h"
#include "schema/pgOperatorClass.h"
#include "schema/pgRole.h"
#include "schema/pgRule.h"
#include "schema/pgSchema.h"
#include "schema/pgSequence.h"
#include "schema/pgServer.h"
#include "schema/pgTable.h"
#include "schema/pgTablespace.h"
#include "schema/pgTextSearchConfiguration.h"
#include "schema/pgTextSearchDictionary.h"
#include "schema/pgTextSearchTemplate.h"
#include "schema/pgTextSearchParser.h"
#include "schema/pgTrigger.h"
#include "schema/pgType.h"
#include "schema/pgUser.h"
#include "schema/pgUserMapping.h"
#include "schema/pgView.h"
#include "schema/gpExtTable.h"
#include "schema/gpPartition.h"
#include "schema/gpResQueue.h"

#include "slony/dlgRepCluster.h"
#include "slony/dlgRepListen.h"
#include "slony/dlgRepNode.h"
#include "slony/dlgRepPath.h"
#include "slony/dlgRepProperty.h"
#include "slony/dlgRepSequence.h"
#include "slony/dlgRepSet.h"
#include "slony/dlgRepSubscription.h"
#include "slony/dlgRepTable.h"
#include "slony/slCluster.h"
#include "slony/slListen.h"
#include "slony/slNode.h"
#include "slony/slPath.h"
#include "slony/slSequence.h"
#include "slony/slSet.h"
#include "slony/slSubscription.h"
#include "slony/slTable.h"

#include "utils/csvfiles.h"
#include "utils/factory.h"
#include "utils/favourites.h"
#include "utils/macros.h"
#include "utils/misc.h"
#include "utils/pgDefs.h"
#include "utils/pgconfig.h"
#include "utils/pgfeatures.h"
#include "utils/sysLogger.h"
#include "utils/sysProcess.h"
#include "utils/sysSettings.h"
#include "utils/utffile.h"

#endif
