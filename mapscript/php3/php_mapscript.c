/**********************************************************************
 * $Id$
 *
 * Name:     php_mapscript.c
 * Project:  PHP/MapScript extension for MapServer.
 * Language: ANSI C
 * Purpose:  External interface functions
 * Author:   Daniel Morissette, morissette@dmsolutions.ca
 *
 **********************************************************************
 * Copyright (c) 2000-2003, DM Solutions Group
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 **********************************************************************
 *
 * $Log$
 * Revision 1.194.2.2  2004/04/30 13:03:10  dan
 * OOpps... fixed the fix to pasteImage()
 *
 * Revision 1.194.2.1  2004/04/30 12:57:09  dan
 * Fixed problem with PHP's pasteImage() method when angle=0
 *
 * Revision 1.194  2004/03/27 18:05:58  dan
 * Removed empty RINIT()/RSHUTDOWN() callbacks for performance,
 * removed MS_LAYER_GRATICULE and added MS_LAYER_TILEINDEX constants
 *
 * Revision 1.193  2004/03/19 17:39:04  sean
 * Renamed all occurrances of layerObj member num_processing to numprocessing.
 *
 * Revision 1.192  2004/03/08 17:10:00  dan
 * Added optional angle parameter to pasteImage()
 *
 * Revision 1.191  2004/02/26 15:10:44  assefa
 * Add symbolobject support.
 *
 * Revision 1.190  2004/01/30 17:01:12  assefa
 * Add function deletestyle on a class object.
 *
 * Revision 1.189  2004/01/13 23:52:38  assefa
 * Add functions to move styles up and down.
 * Add function to clone style.
 *
 * Revision 1.188  2004/01/12 19:56:18  assefa
 * Add moveclassup and moveclassdown on a layer object.
 * Add clone function for the class object.
 * Add a 2nd optional argument for function ms_newclassobj to be able
 * to pass a class as argument.
 *
 * Revision 1.187  2004/01/05 21:27:13  assefa
 * applySLDURL and applySLD on a layer object can now take an optional
 * argument which is the name of the NamedLayer to use to style the layer.
 *
 * Revision 1.186  2003/12/12 13:31:24  dan
 * Added layer->dump property
 *
 * Revision 1.185  2003/12/03 18:56:09  assefa
 * Add functions to apply and to generate sld on a layer object.
 *
 * Revision 1.184  2003/12/01 16:12:01  assefa
 * Add applysld and applysldurl on map.
 *
 * Revision 1.183  2003/10/30 22:55:03  assefa
 * getexpression function in Sync with the mapscript.i
 *
 * Revision 1.182  2003/10/30 22:37:27  assefa
 * Add functions executewfsgetfeature on a WFS layer object.
 * Add function getexpression on a class object.
 *
 * Revision 1.181  2003/10/28 16:50:24  assefa
 * Add functions removeMetaData on map and layer.
 *
 * Revision 1.180  2003/10/20 21:46:06  dan
 * Fixed PHP MapScript's pasteImage() to work with GD 2.x.  The transparent
 * color value is now a 0xrrggbb value instead of a color index.
 *
 * Revision 1.179  2003/09/30 05:38:45  dan
 * First round of changes to re-enable php_mapscript to work with PHP DSO
 *
 * Revision 1.178  2003/09/24 12:27:43  dan
 * Added new MAXSIZE mapObj parameter (bug 435)
 *
 * Revision 1.177  2003/07/30 19:01:31  dan
 * Fixed compile warnings
 *
 * Revision 1.176  2003/07/21 16:55:58  assefa
 * Correct bug in function drawLegendIcon (Bug 369).
 *
 * Revision 1.175  2003/07/21 14:43:21  assefa
 * Change prototypes for certain functions (Bug 362).
 *
 * Revision 1.174  2003/07/08 21:53:12  dan
 * Several fixes to the processXxxTemplate() functions to properly report errors
 * and fixed some memory leaks.
 *
 * Revision 1.173  2003/07/03 15:31:47  assefa
 * Add the possibility to generate image for function
 * processquerytemplate (bug 341).
 *
 * Revision 1.172  2003/07/01 03:08:33  dan
 * Use imageObj instead of gdImagePtr in php3_ms_img_free()
 *
 * Revision 1.171  2003/06/27 15:35:16  assefa
 * Modify test in _phpms_build_shape_object (Bug 316).
 *
 * Revision 1.170  2003/06/26 18:32:45  assefa
 * Add layer processing string related function/memeber/doc.
 *
 * Revision 1.169  2003/06/11 17:55:00  dan
 * Modified PHP SAPI test to accept 'cli' as well
 *
 * Revision 1.168  2003/06/04 17:57:12  assefa
 * add initGrid call.
 *
 * Revision 1.167  2003/06/03 14:55:34  assefa
 * Add layer type  MS_LAYER_GRATICULE.
 *
 * Revision 1.166  2003/05/29 13:31:16  assefa
 * Add access to the transparent parameter in the outputformat object.
 *
 * Revision 1.165  2003/05/27 19:36:31  assefa
 * Add labelcaheObj.
 *
 * Revision 1.164  2003/05/27 12:57:17  assefa
 * Set label size to default value (Bug245).
 *
 * Revision 1.163  2003/05/19 16:09:26  assefa
 * Set transparency and interlace in SaveImage.
 *
 * Revision 1.162  2003/04/28 15:34:47  assefa
 * Add setformatoption and getformatoption on the outputformat object.
 *
 * Revision 1.161  2003/04/25 15:32:58  dan
 * Replaced inchesperUnit[] by a msInchesPerUnit() function that provides
 * better scale values for units DD (adjusts the inches/unit based on lat)
 *
 * Revision 1.160  2003/04/23 19:13:29  dan
 * Use class names in the format ms_<classname>_obj for PHP class entry
 * definitions.  (We were getting name collisions with the "error" class.)
 *
 * Revision 1.159  2003/04/23 14:36:46  dan
 * Added error code constants to php mapscript
 *
 * Revision 1.158  2003/04/23 13:47:18  dan
 * Modified error handling to record multiple errors in a chained list, with
 * the first error being the most recent.
 *
 * Revision 1.157  2003/04/22 23:38:58  assefa
 * Use MIN/MAXINTERVAL instead of MIN/MAXINCREMENT for the grid.
 *
 * Revision 1.156  2003/04/22 04:02:17  assefa
 * Add grid object and related functions inside the layer object.
 *
 * Revision 1.155  2003/04/17 20:48:05  assefa
 * Update php object when a select output format is done.
 *
 * Revision 1.154  2003/04/17 13:21:02  assefa
 * Register destructor for outputformat object.
 *
 * Revision 1.153  2003/04/16 15:04:55  assefa
 * the outputformat is now available through the map object.
 *
 * Revision 1.152  2003/04/02 22:36:54  dan
 * Change map->resolution to be of type double instead of integer
 *
 * Revision 1.151  2003/03/26 21:11:34  dan
 * Added debug member in layerObj and mapObj
 *
 * Revision 1.150  2003/03/26 20:23:31  dan
 * msLoadWKTProjectionString() has been renamed msOGCWKT2ProjectionObj()
 *
 * Revision 1.149  2003/03/14 13:43:03  attila
 * Introduce MySQL generic support, enabled with --with-mygis when configuring, imagemap output
 *
 * Revision 1.148  2003/02/24 02:19:43  dan
 * Added map->clone() method
 *
 * Revision 1.147  2003/02/21 16:55:12  assefa
 * Add function querybyindex and freequery.
 *
 * Revision 1.146  2003/02/19 19:37:12  assefa
 * Add an additional argument to function  ms_newLayerObj to be
 * able to create a new layer based on an existing layer.
 *
 * Revision 1.145  2003/02/14 20:17:26  assefa
 * Add savequery and loadquery functions.
 *
 * Revision 1.144  2003/02/12 14:19:48  assefa
 * layer_open does not take any argument.
 *
 * Revision 1.143  2003/02/04 15:39:43  julien
 * Use MS_SUCCESS to validate success in load/save map context
 *
 * Revision 1.142  2003/02/04 14:51:40  assefa
 * Add test on module name "cgi-fcgi".
 *
 * Revision 1.141  2003/01/24 17:01:05  dan
 * Produce a warning instead of an error in getLayerByName() if layer not found
 *
 * Revision 1.140  2003/01/24 00:41:55  dan
 * Make available the latlon projection object of the map object. (Assefa)
 *
 * Revision 1.139  2003/01/16 17:32:23  dan
 * Applied new phpinfo function using PHP4 formatting (from Jeremy G.)
 *
 * Revision 1.138  2003/01/13 20:37:50  dan
 * Set $line->numpoints and $shape->numlines after add() calls (bug 69)
 *
 * Revision 1.137  2003/01/13 14:44:47  assefa
 * Remove setcolor functions from label and style classes. They
 * were redundant since there is a setRGB function on the color object.
 *
 * Revision 1.136  2003/01/11 00:06:40  dan
 * Added setWKTProjection() to mapObj and layerObj
 *
 * Revision 1.135  2003/01/10 19:21:26  dan
 * Removed style->sizescaled from PHP wrappers
 *
 * Revision 1.134  2003/01/08 16:21:25  assefa
 * Bug in ms_newMapObj related to empty filename.
 *
 * Revision 1.133  2003/01/08 15:00:16  assefa
 * Add setsymbolbyname in the style class.
 *
 * Revision 1.132  2003/01/08 01:16:05  assefa
 * Correct bugs on Windows related to paths.
 *
 * ...
 *
 * Revision 1.1  2000/05/09 21:06:11  dan
 * Initial Import
 *
 * Revision 1.1  2000/01/31 08:38:43  daniel
 * First working version - only mapObj implemented with read-only properties
 *
 **********************************************************************/

#include "php_mapscript.h"
#include "php_mapscript_util.h"

#include "php.h"
#include "php_globals.h"
#include "SAPI.h"
#include "ext/standard/info.h"
#include "ext/standard/head.h"

#include "maperror.h"

#include <time.h>

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <process.h>
#else
#include <errno.h>
#endif

#define PHPMS_VERSION "($Revision$ $Date$)"

#ifdef PHP4
#define ZEND_DEBUG 0
#endif

#ifndef DLEXPORT 
#define DLEXPORT ZEND_DLEXPORT
#endif

/*=====================================================================
 *                         Prototypes
 *====================================================================*/

PHP_MINFO_FUNCTION(mapscript);
PHP_MINIT_FUNCTION(phpms);
PHP_MSHUTDOWN_FUNCTION(phpms);
PHP_RINIT_FUNCTION(phpms);
PHP_RSHUTDOWN_FUNCTION(phpms);


static void php_ms_free_map(zend_rsrc_list_entry *rsrc TSRMLS_DC);

static void php_ms_free_image(zend_rsrc_list_entry *rsrc TSRMLS_DC);
DLEXPORT void php3_ms_free_point(pointObj *pPoint);
DLEXPORT void php3_ms_free_line(lineObj *pLine);
DLEXPORT void php3_ms_free_shape(shapeObj *pShape);
DLEXPORT void php3_ms_free_shapefile(shapefileObj *pShapefile);
DLEXPORT void php3_ms_free_rect(rectObj *pRect);
DLEXPORT void php3_ms_free_stub(void *ptr) ;
DLEXPORT void php3_ms_free_projection(projectionObj *pProj);

DLEXPORT void php3_ms_getversion(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_tokenizeMap(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_map_new(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_clone(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_setProperty(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_setProjection(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_getProjection(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_setWKTProjection(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_getSymbolByName(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_getSymbolObjectById(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_draw(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_drawQuery(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_embedScalebar(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_embedLegend(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_drawLabelCache(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_drawLegend(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_drawReferenceMap(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_drawScaleBar(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_getLayer(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_getLayerByName(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_getLayersIndexByGroup(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_getAllLayerNames(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_getAllGroupNames(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_prepareImage(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_prepareQuery(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_nextLabel(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_getColorByIndex(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_map_queryByPoint(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_queryByRect(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_queryByFeatures(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_queryByShape(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_queryByIndex(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_savequery(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_loadquery(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_freequery(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_map_save(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_getMetaData(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_setMetaData(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_removeMetaData(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_map_setExtent(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_zoomPoint(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_zoomRectangle(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_zoomScale(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_map_getLatLongExtent(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_map_moveLayerUp(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_moveLayerDown(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_getLayersDrawingOrder(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_setLayersDrawingOrder(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_map_processTemplate(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_processLegendTemplate(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_processQueryTemplate(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_map_setSymbolSet(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_getNumSymbols(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_setFontSet(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_map_saveMapContext(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_map_loadMapContext(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void  php3_ms_map_selectOutputFormat(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void  php3_ms_map_applySLD(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void  php3_ms_map_applySLDURL(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void  php3_ms_map_generateSLD(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_img_saveImage(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_img_saveWebImage(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_img_pasteImage(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_img_free(INTERNAL_FUNCTION_PARAMETERS);


DLEXPORT void php3_ms_lyr_new(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_setProperty(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_draw(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_drawQuery(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_getClass(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_queryByPoint(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_queryByAttributes(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_queryByRect(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_queryByFeatures(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_queryByShape(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_setProjection(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_getProjection(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_setWKTProjection(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_addFeature(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_getNumResults(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_getResult(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_open(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_close(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_getShape(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_getMetaData(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_setMetaData(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_removeMetaData(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_setFilter(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_getWMSFeatureInfoURL(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_getItems(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void  php3_ms_lyr_setProcessing(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void  php3_ms_lyr_getProcessing(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void  php3_ms_lyr_clearProcessing(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void  php3_ms_lyr_executeWFSGetfeature(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void  php3_ms_lyr_applySLD(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void  php3_ms_lyr_applySLDURL(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void  php3_ms_lyr_generateSLD(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_moveClassUp(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_lyr_moveClassDown(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_class_new(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_class_setProperty(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_class_setExpression(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_class_getExpression(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_class_setText(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_class_drawLegendIcon(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_class_createLegendIcon(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_class_getStyle(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_class_clone(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_class_moveStyleUp(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_class_moveStyleDown(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_class_deleteStyle(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_label_setProperty(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_color_setRGB(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_rect_new(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_rect_project(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_rect_setProperty(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_rect_draw(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_rect_setExtent(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_rect_fit(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_rect_free(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_point_new(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_point_setXY(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_point_project(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_point_draw(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_point_distanceToPoint(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_point_distanceToLine(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_point_distanceToShape(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_point_free(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_line_new(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_line_project(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_line_add(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_line_addXY(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_line_point(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_line_free(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_shape_new(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shape_setProperty(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shape_project(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shape_add(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shape_line(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shape_draw(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shape_contains(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shape_intersects(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shape_getvalue(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shape_getpointusingmeasure(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shape_getmeasureusingpoint(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shape_free(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_shapefile_new(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shapefile_addshape(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shapefile_addpoint(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shapefile_getshape(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shapefile_getpoint(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shapefile_gettransformed(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shapefile_getextent(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_shapefile_free(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_web_setProperty(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_referenceMap_setProperty(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_projection_new(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_projection_free(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_scalebar_setProperty(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_scalebar_setImageColor(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_legend_setProperty(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_style_new(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_style_setProperty(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_style_clone(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_grid_new(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_grid_setProperty(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_get_error_obj(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_error_next(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_reset_error_list(INTERNAL_FUNCTION_PARAMETERS);


DLEXPORT void php_ms_outputformat_setOutputformatoption(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php_ms_outputformat_getOutputformatoption(INTERNAL_FUNCTION_PARAMETERS);

DLEXPORT void php3_ms_symbol_new(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_symbol_setProperty(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_symbol_setPoints(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_symbol_getPoints(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_symbol_setStyle(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_symbol_getStyle(INTERNAL_FUNCTION_PARAMETERS);


static long _phpms_build_img_object(imageObj *im, webObj *pweb,
                                    HashTable *list, pval *return_value);
static long _phpms_build_layer_object(layerObj *player, int parent_map_id,
                                      HashTable *list, pval *return_value TSRMLS_DC);
static long _phpms_build_class_object(classObj *pclass, int parent_map_id, 
                                      int parent_layer_id, HashTable *list, 
                                      pval *return_value TSRMLS_DC);
static long _phpms_build_label_object(labelObj *plabel,
                                      HashTable *list, pval *return_value);

static long _phpms_build_color_object(colorObj *pcolor,
                                      HashTable *list, pval *return_value);
static long _phpms_build_point_object(pointObj *ppoint, int handle_type,
                                      HashTable *list, pval *return_value);
static long _phpms_build_shape_object(shapeObj *pshape, int handle_type,
                                      layerObj *pLayer,
                                      HashTable *list, pval *return_value);
static long _phpms_build_web_object(webObj *pweb,
                                    HashTable *list, pval *return_value);
static long _phpms_build_rect_object(rectObj *prect, int handle_type,
                                     HashTable *list, pval *return_value);
static long _phpms_build_referenceMap_object(referenceMapObj *preferenceMap,
                                          HashTable *list, pval *return_value);
static long _phpms_build_resultcachemember_object(resultCacheMemberObj *pRes,
                                                  HashTable *list TSRMLS_DC, 
                                                  pval *return_value);

static long _phpms_build_projection_object(projectionObj *pproj, 
                                           int handle_type, HashTable *list, 
                                           pval *return_value);
static long _phpms_build_scalebar_object(scalebarObj *pscalebar,
                                         HashTable *list, pval *return_value);
static long _phpms_build_legend_object(legendObj *plegend,
                                       HashTable *list, pval *return_value);

static long _phpms_build_style_object(styleObj *pstyle, int parent_map_id, 
                                      int parent_layer_id, 
                                      int parent_class_id,
                                      HashTable *list, 
                                      pval *return_value TSRMLS_DC);

static long _phpms_build_outputformat_object(outputFormatObj *poutputformat,
                                             HashTable *list, 
                                             pval *return_value);

static long _phpms_build_grid_object(graticuleObj *pgrid, 
                                     int parent_layer_id,
                                     HashTable *list, 
                                     pval *return_value TSRMLS_DC);

static long _phpms_build_labelcache_object(labelCacheObj *plabelcache,
                                           HashTable *list, 
                                           pval *return_value);

static long _phpms_build_symbol_object(symbolObj *psSymbol, 
                                       int parent_map_id, 
                                       HashTable *list, 
                                       pval *return_value TSRMLS_DC);

DLEXPORT void php_ms_labelcache_free(INTERNAL_FUNCTION_PARAMETERS);


/* ==================================================================== */
/*      utility functions prototypes.                                   */
/* ==================================================================== */
DLEXPORT void php3_ms_getcwd(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_getpid(INTERNAL_FUNCTION_PARAMETERS);
DLEXPORT void php3_ms_getscale(INTERNAL_FUNCTION_PARAMETERS);


static double GetDeltaExtentsUsingScale(double dfMinscale, int nUnits, 
                                        double dCenterLat,
                                        int nWidth, double resolution);

/*=====================================================================
 *               PHP Dynamically Loadable Library stuff
 *====================================================================*/

/* True global resources - no need for thread safety here */
#define PHPMS_GLOBAL(a) a
static int le_msmap;
static int le_mslayer;
static int le_msimg;
static int le_msclass;
static int le_mslabel;
static int le_mscolor;
static int le_msrect_new;
static int le_msrect_ref;
static int le_mspoint_new;
static int le_mspoint_ref;
static int le_msline_new;
static int le_msline_ref;
static int le_msshape_new;
static int le_msshape_ref;
static int le_msshapefile;
static int le_msweb;
static int le_msrefmap;
static int le_msprojection_new;
static int le_msprojection_ref;
static int le_msscalebar;
static int le_mslegend;
static int le_msstyle;
static int le_msoutputformat;
static int le_msgrid;
static int le_mserror_ref;
static int le_mslabelcache;
static int le_mssymbol;

/* 
 * Declare any global variables you may need between the BEGIN
 * and END macros here:     
 */
ZEND_BEGIN_MODULE_GLOBALS(phpms)
    /* We'll use tmpId and tmpCount to generate unique filenames */
    char tmpId[128]; /* big enough for time + pid */
    int  tmpCount;
ZEND_END_MODULE_GLOBALS(phpms)

ZEND_DECLARE_MODULE_GLOBALS(phpms)

static void phpms_init_globals(zend_phpms_globals *phpms_globals)
{
    sprintf(phpms_globals->tmpId, "%ld%d",(long)time(NULL),(int)getpid());
    phpms_globals->tmpCount = 0;
}


/* In every utility function you add that needs to use variables 
   in phpms_globals, call TSRM_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as PHPMS_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define PHPMS_G(v) TSRMG(phpms_globals_id, zend_phpms_globals *, v)
#else
#define PHPMS_G(v) (phpms_globals.v)
#endif


/* -------------------------------------------------------------------- */
/*      class entries.                                                  */
/* -------------------------------------------------------------------- */
static zend_class_entry *map_class_entry_ptr;
static zend_class_entry *img_class_entry_ptr;
static zend_class_entry *rect_class_entry_ptr;
static zend_class_entry *color_class_entry_ptr;
static zend_class_entry *web_class_entry_ptr;
static zend_class_entry *reference_class_entry_ptr;
static zend_class_entry *layer_class_entry_ptr;
static zend_class_entry *label_class_entry_ptr;
static zend_class_entry *class_class_entry_ptr;
static zend_class_entry *point_class_entry_ptr;
static zend_class_entry *line_class_entry_ptr;
static zend_class_entry *shape_class_entry_ptr;
static zend_class_entry *shapefile_class_entry_ptr;
static zend_class_entry *projection_class_entry_ptr;
static zend_class_entry *scalebar_class_entry_ptr;
static zend_class_entry *legend_class_entry_ptr;
static zend_class_entry *style_class_entry_ptr;
static zend_class_entry *outputformat_class_entry_ptr;
static zend_class_entry *grid_class_entry_ptr;
static zend_class_entry *error_class_entry_ptr;
static zend_class_entry *labelcache_class_entry_ptr;
static zend_class_entry *symbol_class_entry_ptr;

static unsigned char one_arg_force_ref[] = 
  { 1, BYREF_FORCE};
static unsigned char two_args_first_arg_force_ref[] = 
    { 2, BYREF_FORCE, BYREF_NONE };

function_entry phpms_functions[] = {
    {"ms_getversion",   php3_ms_getversion,     NULL},
    {"ms_newmapobj",    php3_ms_map_new,        NULL},
    {"ms_newlayerobj",  php3_ms_lyr_new,        two_args_first_arg_force_ref},
    {"ms_newclassobj",  php3_ms_class_new,      one_arg_force_ref},
    {"ms_newpointobj",  php3_ms_point_new,      NULL},
    {"ms_newlineobj",   php3_ms_line_new,       NULL},
    {"ms_newshapeobj",  php3_ms_shape_new,      NULL},
    {"ms_newshapefileobj", php3_ms_shapefile_new,  NULL},
    {"ms_newrectobj",   php3_ms_rect_new,       NULL},
    {"ms_getcwd",       php3_ms_getcwd,         NULL},
    {"ms_getpid",       php3_ms_getpid,         NULL},
    {"ms_getscale",     php3_ms_getscale,       NULL},
    {"ms_newprojectionobj", php3_ms_projection_new, NULL},
    {"ms_tokenizemap",  php3_ms_tokenizeMap,    NULL},
    {"ms_newstyleobj",  php3_ms_style_new,      one_arg_force_ref},
    {"ms_newgridobj",   php3_ms_grid_new,       one_arg_force_ref},
    {"ms_geterrorobj",  php3_ms_get_error_obj,  NULL},
    {"ms_reseterrorlist", php3_ms_reset_error_list, NULL},
    {"ms_newsymbolobj", php3_ms_symbol_new, NULL},
    {NULL, NULL, NULL}
};

zend_module_entry php_ms_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "MapScript", 
    phpms_functions,
    /* MINIT()/MSHUTDOWN() are called once only when PHP starts up and 
     * shutdowns.  They're really called only once and *not* when a new Apache
     * child process is created.
     */
    PHP_MINIT(phpms),
    PHP_MSHUTDOWN(phpms),
    /* RINIT()/RSHUTDOWN() are called once per request 
     * We shouldn't really be using them since they are run on every request
     * and can hit performance.
     */
    NULL /* PHP_RINIT(phpms)     */,
    NULL /* PHP_RSHUTDOWN(phpms) */,
    PHP_MINFO(mapscript),
#if ZEND_MODULE_API_NO >= 20010901
    PHPMS_VERSION,          /* extension version number (string) */
#endif
    STANDARD_MODULE_PROPERTIES 
};


#if COMPILE_DL
DLEXPORT zend_module_entry *get_module(void) { return &php_ms_module_entry; }
#endif

/* -------------------------------------------------------------------- */
/*      Class method definitions.                                       */
/*      We use those to initialize objects in both PHP3 and PHP4        */
/*      through _phpms_object_init()                                    */
/* -------------------------------------------------------------------- */
function_entry php_map_class_functions[] = {
    {"clone",           php3_ms_map_clone,              NULL},
    {"set",             php3_ms_map_setProperty,        NULL},
    {"setprojection",   php3_ms_map_setProjection,      NULL},
    {"getprojection",   php3_ms_map_getProjection,      NULL},
    {"setwktprojection",php3_ms_map_setWKTProjection,   NULL},
    {"getsymbolbyname", php3_ms_map_getSymbolByName,    NULL},
    {"getsymbolobjectbyid", php3_ms_map_getSymbolObjectById,    NULL},
    {"draw",            php3_ms_map_draw,               NULL},
    {"drawquery",       php3_ms_map_drawQuery,          NULL},
    {"embedscalebar",   php3_ms_map_embedScalebar,      NULL},
    {"embedlegend",     php3_ms_map_embedLegend,        NULL},
    {"drawlabelcache",  php3_ms_map_drawLabelCache,     NULL},
    {"drawlegend",      php3_ms_map_drawLegend,         NULL},
    {"drawreferencemap",php3_ms_map_drawReferenceMap,   NULL},
    {"drawscalebar",    php3_ms_map_drawScaleBar,       NULL},
    {"getlayer",        php3_ms_map_getLayer,           NULL},
    {"getlayerbyname",  php3_ms_map_getLayerByName,     NULL},
    {"getlayersindexbygroup",  php3_ms_map_getLayersIndexByGroup,     NULL},
    {"getalllayernames",php3_ms_map_getAllLayerNames,   NULL},
    {"getallgroupnames",php3_ms_map_getAllGroupNames,   NULL},
    {"getcolorbyindex", php3_ms_map_getColorByIndex,    NULL},
    {"setextent",       php3_ms_map_setExtent,          NULL},
    {"zoompoint",       php3_ms_map_zoomPoint,          NULL},
    {"zoomrectangle",   php3_ms_map_zoomRectangle,      NULL},
    {"zoomscale",       php3_ms_map_zoomScale,          NULL},
    {"querybypoint",    php3_ms_map_queryByPoint,       NULL},
    {"querybyrect",     php3_ms_map_queryByRect,        NULL},
    {"querybyfeatures", php3_ms_map_queryByFeatures,    NULL},
    {"querybyshape",    php3_ms_map_queryByShape,       NULL},
    {"querybyindex",    php3_ms_map_queryByIndex,       NULL},
    {"savequery",       php3_ms_map_savequery,          NULL},
    {"loadquery",       php3_ms_map_loadquery,          NULL},
    {"freequery",       php3_ms_map_freequery,          NULL},
    {"save",            php3_ms_map_save,               NULL},
    {"getlatlongextent", php3_ms_map_getLatLongExtent,  NULL},
    {"getmetadata",     php3_ms_map_getMetaData,        NULL},
    {"setmetadata",     php3_ms_map_setMetaData,        NULL},
    {"removemetadata",     php3_ms_map_removeMetaData,        NULL},
    {"prepareimage",    php3_ms_map_prepareImage,       NULL},
    {"preparequery",    php3_ms_map_prepareQuery,       NULL},
    {"movelayerup",     php3_ms_map_moveLayerUp,        NULL},
    {"movelayerdown",   php3_ms_map_moveLayerDown,      NULL},
    {"getlayersdrawingorder",   php3_ms_map_getLayersDrawingOrder,  NULL},
    {"setlayersdrawingorder",   php3_ms_map_setLayersDrawingOrder,  NULL},
    {"processtemplate",   php3_ms_map_processTemplate,  NULL},
    {"processlegendtemplate",   php3_ms_map_processLegendTemplate,  NULL},
    {"processquerytemplate",   php3_ms_map_processQueryTemplate,  NULL},
    {"setsymbolset",    php3_ms_map_setSymbolSet,       NULL},
    {"getnumsymbols",   php3_ms_map_getNumSymbols,      NULL},
    {"setfontset",      php3_ms_map_setFontSet,         NULL},
    {"savemapcontext",  php3_ms_map_saveMapContext,     NULL},
    {"loadmapcontext",  php3_ms_map_loadMapContext,     NULL},
    {"selectoutputformat", php3_ms_map_selectOutputFormat, NULL},
    {"applysld",         php3_ms_map_applySLD,           NULL},
    {"applysldurl",         php3_ms_map_applySLDURL,           NULL},
    {"generatesld",      php3_ms_map_generateSLD,           NULL},
    {NULL, NULL, NULL}
};

function_entry php_img_class_functions[] = {
    {"saveimage",       php3_ms_img_saveImage,          NULL},
    {"savewebimage",    php3_ms_img_saveWebImage,       NULL},
    {"pasteimage",      php3_ms_img_pasteImage,         NULL},
    {"free",            php3_ms_img_free,               NULL},    
    {NULL, NULL, NULL}
};

function_entry php_rect_class_functions[] = {
    {"project",         php3_ms_rect_project,           NULL},    
    {"set",             php3_ms_rect_setProperty,       NULL},    
    {"setextent",       php3_ms_rect_setExtent,         NULL},    
    {"draw",            php3_ms_rect_draw,              NULL},
    {"fit",             php3_ms_rect_fit,               NULL},
    {"free",            php3_ms_rect_free,              NULL},    
    {NULL, NULL, NULL}
};

function_entry php_color_class_functions[] = {
    {"setrgb",          php3_ms_color_setRGB,           NULL},    
    {NULL, NULL, NULL}
};

function_entry php_web_class_functions[] = {
    {"set",             php3_ms_web_setProperty,        NULL},    
    {NULL, NULL, NULL}
};

function_entry php_reference_class_functions[] = {
    {"set",             php3_ms_referenceMap_setProperty,NULL},    
    {NULL, NULL, NULL}
};

function_entry php_scalebar_class_functions[] = {
    {"set",             php3_ms_scalebar_setProperty,        NULL},
    {"setimagecolor",   php3_ms_scalebar_setImageColor,      NULL},    
    {NULL, NULL, NULL}
};

function_entry php_legend_class_functions[] = {
    {"set",             php3_ms_legend_setProperty,        NULL},    
    {NULL, NULL, NULL}
};

function_entry php_layer_class_functions[] = {
    {"set",             php3_ms_lyr_setProperty,        NULL},    
    {"draw",            php3_ms_lyr_draw,               NULL},    
    {"drawquery",       php3_ms_lyr_drawQuery,          NULL},    
    {"getclass",        php3_ms_lyr_getClass,           NULL},    
    {"querybyattributes",php3_ms_lyr_queryByAttributes, NULL},    
    {"querybypoint",    php3_ms_lyr_queryByPoint,       NULL},    
    {"querybyrect",     php3_ms_lyr_queryByRect,        NULL},    
    {"querybyfeatures", php3_ms_lyr_queryByFeatures,    NULL},    
    {"querybyshape",    php3_ms_lyr_queryByShape,       NULL},    
    {"setprojection",   php3_ms_lyr_setProjection,      NULL},
    {"getprojection",   php3_ms_lyr_getProjection,      NULL},
    {"setwktprojection",php3_ms_lyr_setWKTProjection,   NULL},
    {"addfeature",      php3_ms_lyr_addFeature,         NULL},
    {"getnumresults",   php3_ms_lyr_getNumResults,      NULL},
    {"getresult",       php3_ms_lyr_getResult,          NULL},
    {"open",            php3_ms_lyr_open,               NULL},
    {"close",           php3_ms_lyr_close,              NULL},
    {"getshape",        php3_ms_lyr_getShape,           NULL},
    {"getmetadata",     php3_ms_lyr_getMetaData,        NULL},
    {"setmetadata",     php3_ms_lyr_setMetaData,        NULL},
    {"removemetadata",     php3_ms_lyr_removeMetaData,        NULL},
    {"setfilter",       php3_ms_lyr_setFilter,          NULL},
    {"getwmsfeatureinfourl", php3_ms_lyr_getWMSFeatureInfoURL, NULL},
    {"getitems",        php3_ms_lyr_getItems,           NULL},
    {"setprocessing",   php3_ms_lyr_setProcessing,           NULL},
    {"getprocessing",   php3_ms_lyr_getProcessing,           NULL},
    {"clearprocessing", php3_ms_lyr_clearProcessing,           NULL},
    {"executewfsgetfeature", php3_ms_lyr_executeWFSGetfeature,           NULL},
    {"applysld",        php3_ms_lyr_applySLD,           NULL},
    {"applysldurl",     php3_ms_lyr_applySLDURL,           NULL},
    {"generatesld",      php3_ms_lyr_generateSLD,           NULL},
    {"moveclassup",     php3_ms_lyr_moveClassUp, NULL},   
    {"moveclassdown",   php3_ms_lyr_moveClassDown, NULL},   
    {NULL, NULL, NULL}
};

function_entry php_label_class_functions[] = {
    {"set",             php3_ms_label_setProperty,      NULL},    
    {NULL, NULL, NULL}
};

function_entry php_class_class_functions[] = {
    {"set",              php3_ms_class_setProperty,      NULL},    
    {"setexpression",    php3_ms_class_setExpression,    NULL},    
    {"getexpression",    php3_ms_class_getExpression,    NULL},    
    {"settext",          php3_ms_class_setText,          NULL},
    {"drawlegendicon",   php3_ms_class_drawLegendIcon,   NULL},
    {"createlegendicon", php3_ms_class_createLegendIcon, NULL},   
    {"getstyle",        php3_ms_class_getStyle, NULL},   
    {"clone",           php3_ms_class_clone, NULL},   
    {"movestyleup",     php3_ms_class_moveStyleUp, NULL},   
    {"movestyledown",   php3_ms_class_moveStyleDown, NULL},   
    {"deletestyle",     php3_ms_class_deleteStyle, NULL},   
    {NULL, NULL, NULL}
};

function_entry php_point_class_functions[] = {
    {"setxy",           php3_ms_point_setXY,            NULL},    
    {"project",         php3_ms_point_project,          NULL},    
    {"draw",            php3_ms_point_draw,             NULL},    
    {"distancetopoint", php3_ms_point_distanceToPoint,  NULL},    
    {"distancetoline",  php3_ms_point_distanceToLine,   NULL},    
    {"distancetoshape", php3_ms_point_distanceToShape,  NULL},    
    {"free",            php3_ms_point_free,             NULL},    
    {NULL, NULL, NULL}
};

function_entry php_line_class_functions[] = {
    {"project",         php3_ms_line_project,           NULL},    
    {"add",             php3_ms_line_add,               NULL},    
    {"addxy",           php3_ms_line_addXY,             NULL},    
    {"point",           php3_ms_line_point,             NULL},    
    {"free",            php3_ms_line_free,              NULL},    
    {NULL, NULL, NULL}
};

function_entry php_shape_class_functions[] = {
    {"set",             php3_ms_shape_setProperty,      NULL},
    {"project",         php3_ms_shape_project,          NULL},
    {"add",             php3_ms_shape_add,              NULL},
    {"line",            php3_ms_shape_line,             NULL},
    {"draw",            php3_ms_shape_draw,             NULL},
    {"contains",        php3_ms_shape_contains,         NULL},
    {"intersects",      php3_ms_shape_intersects,       NULL},
    {"getvalue",        php3_ms_shape_getvalue,         NULL},
    {"getpointusingmeasure", php3_ms_shape_getpointusingmeasure, NULL},
    {"getmeasureusingpoint", php3_ms_shape_getmeasureusingpoint, NULL},
    {"free",            php3_ms_shape_free,             NULL},
    {NULL, NULL, NULL}
};

function_entry php_shapefile_class_functions[] = {
    {"getshape",        php3_ms_shapefile_getshape,     NULL},    
    {"getpoint",        php3_ms_shapefile_getpoint,     NULL},    
    {"gettransformed",  php3_ms_shapefile_gettransformed, NULL},    
    {"getextent",       php3_ms_shapefile_getextent,    NULL},    
    {"addshape",        php3_ms_shapefile_addshape,     NULL},    
    {"addpoint",        php3_ms_shapefile_addpoint,     NULL},    
    {"free",            php3_ms_shapefile_free,         NULL},    
    {NULL, NULL, NULL}
};

function_entry php_projection_class_functions[] = {
    {"free",            php3_ms_projection_free,        NULL},    
    {NULL, NULL, NULL}
};

function_entry php_style_class_functions[] = {
    {"set",             php3_ms_style_setProperty,      NULL},    
    {"clone",           php3_ms_style_clone,      NULL},    
    {NULL, NULL, NULL}
};

function_entry php_outputformat_class_functions[] = {
    {"setformatoption", php_ms_outputformat_setOutputformatoption, NULL},
    {"getformatoption", php_ms_outputformat_getOutputformatoption, NULL},
    {NULL, NULL, NULL}
};

function_entry php_grid_class_functions[] = {
    {"set",             php3_ms_grid_setProperty,        NULL},
    {NULL, NULL, NULL}
};

function_entry php_error_class_functions[] = {
    {"next",            php3_ms_error_next,             NULL},
    {NULL, NULL, NULL}
};


function_entry php_labelcache_class_functions[] = {
    {"free",    php_ms_labelcache_free,      NULL},    
    {NULL, NULL, NULL}
};

function_entry php_symbol_class_functions[] = {
    {"set",             php3_ms_symbol_setProperty,      NULL},    
    {"setpoints",             php3_ms_symbol_setPoints,      NULL},    
    {"getpointsarray",             php3_ms_symbol_getPoints,      NULL},    
    {"setstyle",             php3_ms_symbol_setStyle,      NULL},    
    {"getstylearray",             php3_ms_symbol_getStyle,      NULL},    
    {NULL, NULL, NULL}
};

PHP_MINFO_FUNCTION(mapscript)
{
  php_info_print_table_start();
  php_info_print_table_row(2, "MapServer Version", msGetVersion());
  php_info_print_table_row(2, "PHP MapScript Version", PHPMS_VERSION);
  php_info_print_table_end();

  /* Remove comments if you have entries in php.ini
  DISPLAY_INI_ENTRIES();
  */

}


PHP_MINIT_FUNCTION(phpms)
{
    zend_class_entry tmp_class_entry;

    int const_flag = CONST_CS|CONST_PERSISTENT;

    ZEND_INIT_MODULE_GLOBALS(phpms, phpms_init_globals, NULL);

    /* If you have INI entries, uncomment this line
    REGISTER_INI_ENTRIES();
    */

    PHPMS_GLOBAL(le_msmap)  = 
        zend_register_list_destructors_ex(php_ms_free_map, NULL, 
                                          "mapObj", module_number);
    PHPMS_GLOBAL(le_msimg)  = 
        zend_register_list_destructors_ex(php_ms_free_image, NULL,
                                          "imageObj", module_number);
    PHPMS_GLOBAL(le_mslayer)= 
        zend_register_list_destructors_ex(NULL, NULL,
                                          "layerObj", module_number);

    PHPMS_GLOBAL(le_msclass)= register_list_destructors(php3_ms_free_stub,
                                                        NULL);
    PHPMS_GLOBAL(le_mslabel)= register_list_destructors(php3_ms_free_stub,
                                                        NULL);
    PHPMS_GLOBAL(le_mscolor)= register_list_destructors(php3_ms_free_stub,
                                                        NULL);
    PHPMS_GLOBAL(le_mspoint_new)= register_list_destructors(php3_ms_free_point,
                                                        NULL);
    PHPMS_GLOBAL(le_mspoint_ref)= register_list_destructors(php3_ms_free_stub,
                                                        NULL);
    PHPMS_GLOBAL(le_msline_new)= register_list_destructors(php3_ms_free_line,
                                                        NULL);
    PHPMS_GLOBAL(le_msline_ref)= register_list_destructors(php3_ms_free_stub,
                                                        NULL);
    PHPMS_GLOBAL(le_msshape_new)= register_list_destructors(php3_ms_free_shape,
                                                        NULL);
    PHPMS_GLOBAL(le_msshape_ref)= register_list_destructors(php3_ms_free_stub,
                                                        NULL);
    PHPMS_GLOBAL(le_msshapefile)= 
                              register_list_destructors(php3_ms_free_shapefile,
                                                        NULL);
    PHPMS_GLOBAL(le_msweb)= register_list_destructors(php3_ms_free_stub,
                                                      NULL);
    PHPMS_GLOBAL(le_msrefmap)= register_list_destructors(php3_ms_free_stub,
                                                             NULL);
    PHPMS_GLOBAL(le_msrect_new)= register_list_destructors(php3_ms_free_rect,
                                                           NULL);
    PHPMS_GLOBAL(le_msrect_ref)= register_list_destructors(php3_ms_free_stub,
                                                           NULL);
    PHPMS_GLOBAL(le_msprojection_new)= 
        register_list_destructors(php3_ms_free_projection, NULL);

    PHPMS_GLOBAL(le_msprojection_ref)= 
      register_list_destructors(php3_ms_free_stub,
                                NULL);

    PHPMS_GLOBAL(le_msscalebar)= 
        zend_register_list_destructors_ex(NULL, NULL,
                                          "scalebarObj", module_number);

    PHPMS_GLOBAL(le_mslegend)= 
        zend_register_list_destructors_ex(NULL, NULL,
                                          "legendObj", module_number);

    PHPMS_GLOBAL(le_msstyle)= register_list_destructors(php3_ms_free_stub,
                                                        NULL);

    PHPMS_GLOBAL(le_msoutputformat)= register_list_destructors(php3_ms_free_stub,
                                                               NULL);

    PHPMS_GLOBAL(le_msgrid)= register_list_destructors(php3_ms_free_stub,
                                                       NULL);

    PHPMS_GLOBAL(le_mserror_ref)= register_list_destructors(php3_ms_free_stub,
                                                            NULL);

    PHPMS_GLOBAL(le_mssymbol)= register_list_destructors(php3_ms_free_stub,
                                                         NULL);

    PHPMS_GLOBAL(le_mslabelcache)= 
      register_list_destructors(php3_ms_free_stub, NULL);

    /* boolean constants*/
    REGISTER_LONG_CONSTANT("MS_TRUE",       MS_TRUE,        const_flag);
    REGISTER_LONG_CONSTANT("MS_FALSE",      MS_FALSE,       const_flag);
    REGISTER_LONG_CONSTANT("MS_ON",         MS_ON,          const_flag);
    REGISTER_LONG_CONSTANT("MS_OFF",        MS_OFF,         const_flag);
    REGISTER_LONG_CONSTANT("MS_YES",        MS_YES,         const_flag);
    REGISTER_LONG_CONSTANT("MS_NO",         MS_NO,          const_flag);

    /* map units constants*/
    REGISTER_LONG_CONSTANT("MS_INCHES",     MS_INCHES,      const_flag);
    REGISTER_LONG_CONSTANT("MS_FEET",       MS_FEET,        const_flag);
    REGISTER_LONG_CONSTANT("MS_MILES",      MS_MILES,       const_flag);
    REGISTER_LONG_CONSTANT("MS_METERS",     MS_METERS,      const_flag);
    REGISTER_LONG_CONSTANT("MS_KILOMETERS", MS_KILOMETERS,  const_flag);
    REGISTER_LONG_CONSTANT("MS_DD",         MS_DD,          const_flag);
    REGISTER_LONG_CONSTANT("MS_PIXELS",     MS_PIXELS,      const_flag);

    /* layer type constants*/
    REGISTER_LONG_CONSTANT("MS_LAYER_POINT",MS_LAYER_POINT, const_flag);
    REGISTER_LONG_CONSTANT("MS_LAYER_LINE", MS_LAYER_LINE,  const_flag);
    REGISTER_LONG_CONSTANT("MS_LAYER_POLYGON",MS_LAYER_POLYGON, const_flag);
    REGISTER_LONG_CONSTANT("MS_LAYER_RASTER",MS_LAYER_RASTER, const_flag);
    REGISTER_LONG_CONSTANT("MS_LAYER_ANNOTATION",MS_LAYER_ANNOTATION,const_flag);
    REGISTER_LONG_CONSTANT("MS_LAYER_QUERY",MS_LAYER_QUERY, const_flag);
    REGISTER_LONG_CONSTANT("MS_LAYER_CIRCLE",MS_LAYER_CIRCLE, const_flag);
    REGISTER_LONG_CONSTANT("MS_LAYER_TILEINDEX",MS_LAYER_TILEINDEX, const_flag);

    /* layer status constants (see also MS_ON, MS_OFF) */
    REGISTER_LONG_CONSTANT("MS_DEFAULT",    MS_DEFAULT,     const_flag);
    REGISTER_LONG_CONSTANT("MS_EMBED",      MS_EMBED,       const_flag);
    REGISTER_LONG_CONSTANT("MS_DELETE",     MS_DELETE,       const_flag);

    /* font type constants*/
    REGISTER_LONG_CONSTANT("MS_TRUETYPE",   MS_TRUETYPE,    const_flag);
    REGISTER_LONG_CONSTANT("MS_BITMAP",     MS_BITMAP,      const_flag);

    /* bitmap font style constants */
    REGISTER_LONG_CONSTANT("MS_TINY",       MS_TINY,        const_flag);
    REGISTER_LONG_CONSTANT("MS_SMALL",      MS_SMALL,       const_flag);
    REGISTER_LONG_CONSTANT("MS_MEDIUM",     MS_MEDIUM,      const_flag);
    REGISTER_LONG_CONSTANT("MS_LARGE",      MS_LARGE,       const_flag);
    REGISTER_LONG_CONSTANT("MS_GIANT",      MS_GIANT,       const_flag);

    /* label position constants*/
    REGISTER_LONG_CONSTANT("MS_UL",         MS_UL,          const_flag);
    REGISTER_LONG_CONSTANT("MS_LR",         MS_LR,          const_flag);
    REGISTER_LONG_CONSTANT("MS_UR",         MS_UR,          const_flag);
    REGISTER_LONG_CONSTANT("MS_LL",         MS_LL,          const_flag);
    REGISTER_LONG_CONSTANT("MS_CR",         MS_CR,          const_flag);
    REGISTER_LONG_CONSTANT("MS_CL",         MS_CL,          const_flag);
    REGISTER_LONG_CONSTANT("MS_UC",         MS_UC,          const_flag);
    REGISTER_LONG_CONSTANT("MS_LC",         MS_LC,          const_flag);
    REGISTER_LONG_CONSTANT("MS_CC",         MS_CC,          const_flag);
    REGISTER_LONG_CONSTANT("MS_AUTO",       MS_AUTO,        const_flag);
    REGISTER_LONG_CONSTANT("MS_XY",         MS_XY,          const_flag);

    /* shape type constants*/
    REGISTER_LONG_CONSTANT("MS_SHAPE_POINT",MS_SHAPE_POINT, const_flag);
    REGISTER_LONG_CONSTANT("MS_SHAPE_LINE",  MS_SHAPE_LINE, const_flag);
    REGISTER_LONG_CONSTANT("MS_SHAPE_POLYGON",MS_SHAPE_POLYGON, const_flag);
    REGISTER_LONG_CONSTANT("MS_SHAPE_NULL", MS_SHAPE_NULL,  const_flag);

    /* shapefile type constants*/
    /* Old names ... */
    REGISTER_LONG_CONSTANT("MS_SHP_POINT",  SHP_POINT,      const_flag);
    REGISTER_LONG_CONSTANT("MS_SHP_ARC",    SHP_ARC,        const_flag);
    REGISTER_LONG_CONSTANT("MS_SHP_POLYGON",SHP_POLYGON,    const_flag);
    REGISTER_LONG_CONSTANT("MS_SHP_MULTIPOINT",SHP_MULTIPOINT, const_flag);
    REGISTER_LONG_CONSTANT("MS_SHP_POINTM",  SHP_POINTM,      const_flag);
    REGISTER_LONG_CONSTANT("MS_SHP_ARCM",    SHP_ARCM,        const_flag);
    REGISTER_LONG_CONSTANT("MS_SHP_POLYGONM",SHP_POLYGONM,    const_flag);
    REGISTER_LONG_CONSTANT("MS_SHP_MULTIPOINTM",SHP_MULTIPOINTM, const_flag);
    /* new names??? */
    REGISTER_LONG_CONSTANT("SHP_POINT",     SHP_POINT,      const_flag);
    REGISTER_LONG_CONSTANT("SHP_ARC",       SHP_ARC,        const_flag);
    REGISTER_LONG_CONSTANT("SHP_POLYGON",   SHP_POLYGON,    const_flag);
    REGISTER_LONG_CONSTANT("SHP_MULTIPOINT",SHP_MULTIPOINT, const_flag);
    REGISTER_LONG_CONSTANT("SHP_POINTM",     SHP_POINTM,      const_flag);
    REGISTER_LONG_CONSTANT("SHP_ARCM",       SHP_ARCM,        const_flag);
    REGISTER_LONG_CONSTANT("SHP_POLYGONM",   SHP_POLYGONM,    const_flag);
    REGISTER_LONG_CONSTANT("SHP_MULTIPOINTM",SHP_MULTIPOINTM, const_flag);

    /* query/join type constants*/
    REGISTER_LONG_CONSTANT("MS_SINGLE",     MS_SINGLE,      const_flag);
    REGISTER_LONG_CONSTANT("MS_MULTIPLE",   MS_MULTIPLE,    const_flag);

    /* connection type constants*/
    REGISTER_LONG_CONSTANT("MS_INLINE",     MS_INLINE,      const_flag);
    REGISTER_LONG_CONSTANT("MS_SHAPEFILE",  MS_SHAPEFILE,   const_flag);
    REGISTER_LONG_CONSTANT("MS_TILED_SHAPEFILE",MS_TILED_SHAPEFILE,const_flag);
    REGISTER_LONG_CONSTANT("MS_SDE",        MS_SDE,         const_flag);
    REGISTER_LONG_CONSTANT("MS_OGR",        MS_OGR,         const_flag);
    REGISTER_LONG_CONSTANT("MS_POSTGIS",    MS_POSTGIS,     const_flag);
    REGISTER_LONG_CONSTANT("MS_MYGIS",      MS_MYGIS,       const_flag);
    REGISTER_LONG_CONSTANT("MS_WMS",        MS_WMS,         const_flag);
    REGISTER_LONG_CONSTANT("MS_WFS",        MS_WFS,         const_flag);
    REGISTER_LONG_CONSTANT("MS_ORACLESPATIAL", MS_ORACLESPATIAL,const_flag);
    REGISTER_LONG_CONSTANT("MS_GRATICULE", MS_GRATICULE,const_flag);
 
    /* output image type constants*/
    /*
    REGISTER_LONG_CONSTANT("MS_GIF",        MS_GIF,         const_flag);
    REGISTER_LONG_CONSTANT("MS_PNG",        MS_PNG,         const_flag);
    REGISTER_LONG_CONSTANT("MS_JPEG",       MS_JPEG,        const_flag);
    REGISTER_LONG_CONSTANT("MS_WBMP",       MS_WBMP,        const_flag);
    REGISTER_LONG_CONSTANT("MS_SWF",        MS_SWF,        const_flag);
    */

    /* querymap style constants */
    REGISTER_LONG_CONSTANT("MS_NORMAL",     MS_NORMAL,      const_flag);
    REGISTER_LONG_CONSTANT("MS_HILITE",     MS_HILITE,      const_flag);
    REGISTER_LONG_CONSTANT("MS_SELECTED",   MS_SELECTED,    const_flag);

    /* return value constants */
    REGISTER_LONG_CONSTANT("MS_SUCCESS",    MS_SUCCESS,     const_flag);
    REGISTER_LONG_CONSTANT("MS_FAILURE",    MS_FAILURE,     const_flag);
    REGISTER_LONG_CONSTANT("MS_DONE",       MS_DONE,        const_flag);
   
    /* error code constants */
    REGISTER_LONG_CONSTANT("MS_NOERR",      MS_NOERR,       const_flag);
    REGISTER_LONG_CONSTANT("MS_IOERR",      MS_IOERR,       const_flag);
    REGISTER_LONG_CONSTANT("MS_MEMERR",     MS_MEMERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_TYPEERR",    MS_TYPEERR,     const_flag);
    REGISTER_LONG_CONSTANT("MS_SYMERR",     MS_SYMERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_REGEXERR",   MS_REGEXERR,    const_flag);
    REGISTER_LONG_CONSTANT("MS_TTFERR",     MS_TTFERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_DBFERR",     MS_DBFERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_GDERR",      MS_GDERR,       const_flag);
    REGISTER_LONG_CONSTANT("MS_IDENTERR",   MS_IDENTERR,    const_flag);
    REGISTER_LONG_CONSTANT("MS_EOFERR",     MS_EOFERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_PROJERR",    MS_PROJERR,     const_flag);
    REGISTER_LONG_CONSTANT("MS_MISCERR",    MS_MISCERR,     const_flag);
    REGISTER_LONG_CONSTANT("MS_CGIERR",     MS_CGIERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_WEBERR",     MS_WEBERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_IMGERR",     MS_IMGERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_HASHERR",    MS_HASHERR,     const_flag);
    REGISTER_LONG_CONSTANT("MS_JOINERR",    MS_JOINERR,     const_flag);
    REGISTER_LONG_CONSTANT("MS_NOTFOUND",   MS_NOTFOUND,    const_flag);
    REGISTER_LONG_CONSTANT("MS_SHPERR",     MS_SHPERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_PARSEERR",   MS_PARSEERR,    const_flag);
    REGISTER_LONG_CONSTANT("MS_SDEERR",     MS_SDEERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_OGRERR",     MS_OGRERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_QUERYERR",   MS_QUERYERR,    const_flag);
    REGISTER_LONG_CONSTANT("MS_WMSERR",     MS_WMSERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_WMSCONNERR", MS_WMSCONNERR,  const_flag);
    REGISTER_LONG_CONSTANT("MS_ORACLESPATIALERR", MS_ORACLESPATIALERR, const_flag);
    REGISTER_LONG_CONSTANT("MS_WFSERR",     MS_WFSERR,      const_flag);
    REGISTER_LONG_CONSTANT("MS_WFSCONNERR", MS_WFSCONNERR,  const_flag);
    REGISTER_LONG_CONSTANT("MS_MAPCONTEXTERR", MS_MAPCONTEXTERR, const_flag);
    REGISTER_LONG_CONSTANT("MS_HTTPERR",    MS_HTTPERR,     const_flag);
 
    /*symbol types */
    REGISTER_LONG_CONSTANT("MS_SYMBOL_SIMPLE", MS_SYMBOL_SIMPLE, const_flag);
    REGISTER_LONG_CONSTANT("MS_SYMBOL_VECTOR", MS_SYMBOL_VECTOR, const_flag);
    REGISTER_LONG_CONSTANT("MS_SYMBOL_ELLIPSE", MS_SYMBOL_ELLIPSE, const_flag);
    REGISTER_LONG_CONSTANT("MS_SYMBOL_PIXMAP", MS_SYMBOL_PIXMAP, const_flag);
    REGISTER_LONG_CONSTANT("MS_SYMBOL_TRUETYPE", MS_SYMBOL_TRUETYPE, const_flag);
    REGISTER_LONG_CONSTANT("MS_SYMBOL_CARTOLINE", MS_SYMBOL_CARTOLINE, const_flag);

#ifdef PHP4
    INIT_CLASS_ENTRY(tmp_class_entry, "ms_map_obj", php_map_class_functions);
    map_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);
    
    INIT_CLASS_ENTRY(tmp_class_entry, "ms_img_obj", php_img_class_functions);
    img_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

    INIT_CLASS_ENTRY(tmp_class_entry, "ms_rect_obj", php_rect_class_functions);
    rect_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

    INIT_CLASS_ENTRY(tmp_class_entry, "ms_color_obj", 
                     php_color_class_functions);
    color_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

    INIT_CLASS_ENTRY(tmp_class_entry, "ms_web_obj", php_web_class_functions);
    web_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

    INIT_CLASS_ENTRY(tmp_class_entry, "ms_reference_obj", 
                     php_reference_class_functions);
    reference_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);
    
    INIT_CLASS_ENTRY(tmp_class_entry, "ms_scalebar_obj", 
                     php_scalebar_class_functions);
    scalebar_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

    INIT_CLASS_ENTRY(tmp_class_entry, "ms_legend_obj", 
                     php_legend_class_functions);
    legend_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

    INIT_CLASS_ENTRY(tmp_class_entry, "ms_layer_obj", 
                     php_layer_class_functions);
    layer_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

    INIT_CLASS_ENTRY(tmp_class_entry, "ms_label_obj", 
                     php_label_class_functions);
    label_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

    INIT_CLASS_ENTRY(tmp_class_entry, "ms_class_obj", 
                     php_class_class_functions);
    class_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

    INIT_CLASS_ENTRY(tmp_class_entry, "ms_point_obj", 
                     php_point_class_functions);
    point_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

    INIT_CLASS_ENTRY(tmp_class_entry, "ms_line_obj", 
                     php_line_class_functions);
    line_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

    INIT_CLASS_ENTRY(tmp_class_entry, "ms_shape_obj", 
                     php_shape_class_functions);
    shape_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);
    
    INIT_CLASS_ENTRY(tmp_class_entry, "ms_shapefile_obj", 
                     php_shapefile_class_functions);
    shapefile_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

    INIT_CLASS_ENTRY(tmp_class_entry, "ms_projection_obj", 
                     php_projection_class_functions);
    projection_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

     INIT_CLASS_ENTRY(tmp_class_entry, "ms_style_obj", 
                      php_style_class_functions);
    style_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

     INIT_CLASS_ENTRY(tmp_class_entry, "ms_outputformat_obj", 
                      php_outputformat_class_functions);
     outputformat_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

     INIT_CLASS_ENTRY(tmp_class_entry, "ms_grid_obj", 
                      php_grid_class_functions);
     grid_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

     INIT_CLASS_ENTRY(tmp_class_entry, "ms_error_obj", 
                      php_error_class_functions);
     error_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

     INIT_CLASS_ENTRY(tmp_class_entry, "ms_labelcache_obj", 
                      php_labelcache_class_functions);
     labelcache_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

     INIT_CLASS_ENTRY(tmp_class_entry, "ms_symbol_obj", 
                      php_symbol_class_functions);
     symbol_class_entry_ptr = zend_register_internal_class(&tmp_class_entry TSRMLS_CC);

#endif

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(phpms)
{
    return SUCCESS;
}

PHP_RINIT_FUNCTION(phpms)
{
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(phpms)
{
    return SUCCESS;
}



/**********************************************************************
 *                     resource list destructors
 **********************************************************************/
static void php_ms_free_map(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
    mapObj_destroy((mapObj*)rsrc->ptr);
}

static void php_ms_free_image(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
    imageObj *image = (imageObj *)rsrc->ptr;
    
    msFreeImage(image);
}

DLEXPORT void php3_ms_free_rect(rectObj *pRect) 
{
    rectObj_destroy(pRect);
}

DLEXPORT void php3_ms_free_point(pointObj *pPoint) 
{
    pointObj_destroy(pPoint);
}

DLEXPORT void php3_ms_free_line(lineObj *pLine) 
{
    lineObj_destroy(pLine);
}

DLEXPORT void php3_ms_free_shape(shapeObj *pShape) 
{
    shapeObj_destroy(pShape);
}

DLEXPORT void php3_ms_free_shapefile(shapefileObj *pShapefile) 
{
    shapefileObj_destroy(pShapefile);
}


DLEXPORT void php3_ms_free_stub(void *ptr)
{
    /* nothing to do... map destructor takes care of all objects. */
}

DLEXPORT void php3_ms_free_projection(projectionObj *pProj) 
{
    projectionObj_destroy(pProj);
}

/*=====================================================================
 *                 PHP function wrappers
 *====================================================================*/

/************************************************************************/
/*                         php3_ms_getversion()                         */
/*                                                                      */
/*      Returns a string with MapServer version and configuration       */
/*      params.                                                         */
/************************************************************************/
DLEXPORT void php3_ms_getversion(INTERNAL_FUNCTION_PARAMETERS)
{
    RETURN_STRING(msGetVersion(), 1);
}



/*=====================================================================
 *                 PHP function wrappers - mapObj class
 *====================================================================*/

/**********************************************************************
 *                     _phpms_build_map_object()
 **********************************************************************/
static long _phpms_build_map_object(mapObj *pMap, HashTable *list, 
                                    pval *return_value TSRMLS_DC)
{
    int         map_id;
    pval        *new_obj_ptr;

    if (pMap == NULL)
    {
        return 0;
    }

    map_id = php3_list_insert(pMap, PHPMS_GLOBAL(le_msmap));

    _phpms_object_init(return_value, map_id, php_map_class_functions,
                       PHP4_CLASS_ENTRY(map_class_entry_ptr));

    /* read-only properties */
    add_property_long(return_value, "numlayers", pMap->numlayers);

    /* editable properties */
    PHPMS_ADD_PROP_STR(return_value, "name",      pMap->name);
    add_property_long(return_value,  "status",    pMap->status);
    add_property_long(return_value,  "debug",     pMap->debug);
    add_property_long(return_value,  "width",     pMap->width);
    add_property_long(return_value,  "height",    pMap->height);
    add_property_long(return_value,  "maxsize",   pMap->maxsize);
    add_property_long(return_value,  "transparent", pMap->transparent);
    add_property_long(return_value,  "interlace", pMap->interlace);
    PHPMS_ADD_PROP_STR(return_value,  "imagetype", pMap->imagetype);
    add_property_long(return_value,  "imagequality", pMap->imagequality);

#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
#endif
    _phpms_build_rect_object(&(pMap->extent), PHPMS_GLOBAL(le_msrect_ref),
                             list, new_obj_ptr);
    _phpms_add_property_object(return_value, "extent", new_obj_ptr, E_ERROR);

    add_property_double(return_value,"cellsize",  pMap->cellsize);
    add_property_long(return_value,  "units",     pMap->units);
    add_property_double(return_value,"scale",     pMap->scale);
    add_property_double(return_value,"resolution",pMap->resolution);
    PHPMS_ADD_PROP_STR(return_value, "shapepath", pMap->shapepath);
    add_property_long(return_value,  "keysizex",  pMap->legend.keysizex);
    add_property_long(return_value,  "keysizey",  pMap->legend.keysizey);
    add_property_long(return_value, "keyspacingx",pMap->legend.keyspacingx);
    add_property_long(return_value, "keyspacingy",pMap->legend.keyspacingy);
    
    PHPMS_ADD_PROP_STR(return_value, "symbolsetfilename", 
                                                  pMap->symbolset.filename);
    PHPMS_ADD_PROP_STR(return_value, "fontsetfilename", 
                                                  pMap->fontset.filename);
    PHPMS_ADD_PROP_STR(return_value, "mappath",      pMap->mappath);
    
#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
#endif
    _phpms_build_color_object(&(pMap->imagecolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "imagecolor",new_obj_ptr,E_ERROR);

#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
#endif
    _phpms_build_web_object(&(pMap->web), list, new_obj_ptr);
    _phpms_add_property_object(return_value, "web", new_obj_ptr, E_ERROR);

#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
#endif
    _phpms_build_referenceMap_object(&(pMap->reference), list, 
                                     new_obj_ptr);
    _phpms_add_property_object(return_value, "reference", new_obj_ptr,E_ERROR);

#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
#endif
    _phpms_build_scalebar_object(&(pMap->scalebar), list, new_obj_ptr);
    _phpms_add_property_object(return_value, "scalebar", new_obj_ptr, E_ERROR);

#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
#endif
    _phpms_build_legend_object(&(pMap->legend), list, new_obj_ptr);
    _phpms_add_property_object(return_value, "legend", new_obj_ptr, E_ERROR);

#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
#endif
    _phpms_build_projection_object(&(pMap->latlon), PHPMS_GLOBAL(le_msprojection_ref),
                                   list,  new_obj_ptr);
    _phpms_add_property_object(return_value, "latlon", new_obj_ptr, E_ERROR);

    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_outputformat_object(pMap->outputformat, list, new_obj_ptr);
    _phpms_add_property_object(return_value, "outputformat", new_obj_ptr, E_ERROR);

    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_labelcache_object(&(pMap->labelcache), list, new_obj_ptr);
    _phpms_add_property_object(return_value, "labelcache", new_obj_ptr, E_ERROR);

    return map_id;
}



/**********************************************************************
 *                        ms_newMapObj()
 **********************************************************************/

/* {{{ proto mapObj ms_newMapObj(string filename)
   Returns a new object to deal with a MapServer map file. */

DLEXPORT void php3_ms_map_new(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pFname, *pNewPath;
    mapObj      *pNewMap = NULL;
    int         nArgs;
    char        *pszNewPath = NULL;
    HashTable   *list=NULL;

#if defined(WIN32)
    char        szPath[MS_MAXPATHLEN], szFname[MS_MAXPATHLEN];
    char        szNewPath[MS_MAXPATHLEN];
#endif

    nArgs = ARG_COUNT(ht);
    if ((nArgs != 1 && nArgs != 2) ||
        getParameters(ht, nArgs, &pFname, &pNewPath) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pFname);

    if (nArgs >= 2)
    {
        convert_to_string(pNewPath);
        pszNewPath = pNewPath->value.str.val;
    }

    /* Attempt to open the MAP file 
     */

#if defined(WIN32)
    /* With PHP4, we have to use the virtual_cwd API... for now we'll
     * just make sure that the .map file path is absolute, but what we
     * should really do is make all of MapServer use the V_* macros and
     * avoid calling setcwd() from anywhere.
     */

    virtual_getcwd(szFname, MS_MAXPATHLEN TSRMLS_CC);
    msBuildPath(szPath, szFname, pFname->value.str.val);
    if (strlen(pFname->value.str.val) == 0)
      szPath[0] = '\0';

    if (pszNewPath)
    {
        msBuildPath(szNewPath, szFname, pszNewPath);
        pNewMap = mapObj_new(szPath, szNewPath);
    }
    else
       pNewMap = mapObj_new(szPath, pszNewPath);
   
#else
    pNewMap = mapObj_new(pFname->value.str.val, pszNewPath);
#endif
    if (pNewMap == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_WARNING, "Failed to open map file %s", 
                            pFname->value.str.val);
        RETURN_FALSE;
    }

    /* Return map object */
    _phpms_build_map_object(pNewMap, list, return_value TSRMLS_CC);

}
/* }}} */


/**********************************************************************
 *                        map->clone()
 **********************************************************************/

/* {{{ proto int map.clone()
   Make a copy of this mapObj and returne a refrence to it. Returns NULL(0) on error. */

DLEXPORT void php3_ms_map_clone(INTERNAL_FUNCTION_PARAMETERS)
{
    mapObj *self, *pNewMap;
    pval   *pThis;
    HashTable   *list=NULL;

    pThis = getThis();

    if (pThis == NULL || ARG_COUNT(ht) != 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_FALSE;
    }

    /* Make a copy of current map object */
    if ((pNewMap = mapObj_clone(self)) == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        RETURN_FALSE;
    }

    /* Return new map object */
    _phpms_build_map_object(pNewMap, list, return_value TSRMLS_CC);

}
/* }}} */


/**********************************************************************
 *                        map->set()
 **********************************************************************/

/* {{{ proto int map.set(string property_name, new_value)
   Set map object property to new value. Returns -1 on error. */

DLEXPORT void php3_ms_map_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    mapObj *self;
    pval   *pPropertyName, *pNewValue;
    pval *pThis;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);


    IF_SET_STRING(     "name",        self->name)
    else IF_SET_LONG(  "status",      self->status)
    else IF_SET_LONG(  "debug",       self->debug)
    else IF_SET_LONG(  "width",       self->width)
    else IF_SET_LONG(  "height",      self->height)
    else IF_SET_LONG(  "maxsize",     self->maxsize)
    else IF_SET_LONG(  "transparent", self->transparent)
    else IF_SET_LONG(  "interlace",   self->interlace)
    else IF_SET_LONG(  "imagequality",self->imagequality)
    else IF_SET_DOUBLE("cellsize",    self->cellsize)
    else IF_SET_LONG(  "units",       self->units)
    else IF_SET_DOUBLE("scale",       self->scale)
    else IF_SET_DOUBLE("resolution",  self->resolution)
    else IF_SET_STRING("shapepath",   self->shapepath)
    else IF_SET_LONG(  "keysizex",    self->legend.keysizex)
    else IF_SET_LONG(  "keysizey",    self->legend.keysizey)
    else IF_SET_LONG(  "keyspacingx", self->legend.keyspacingx)
    else IF_SET_LONG(  "keyspacingy", self->legend.keyspacingy)
    else if (strcmp( "numlayers", pPropertyName->value.str.val) == 0 ||
             strcmp( "extent", pPropertyName->value.str.val) == 0 ||
             strcmp( "symbolsetfilename", pPropertyName->value.str.val) == 0 ||
             strcmp( "fontsetfilename", pPropertyName->value.str.val) == 0 ||
             strcmp( "imagetype", pPropertyName->value.str.val) == 0)
    {
        php3_error(E_ERROR,"Property '%s' is read-only and cannot be set.", 
                            pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }
    else
    {
        php3_error(E_ERROR,"Property '%s' does not exist in this object.", 
                            pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }

    RETURN_LONG(0);
}
/* }}} */

/**********************************************************************
 *                        map->setExtent()
 **********************************************************************/

/* {{{ proto int map.setextent(string property_name, new_value)
   Set map extent property to new value. Returns -1 on error. */

DLEXPORT void php3_ms_map_setExtent(INTERNAL_FUNCTION_PARAMETERS)
{
    mapObj *self;
#ifdef PHP4
    pval   **pExtent;
#else
    pval   *pExtent;
#endif

    pval   *pMinX, *pMinY, *pMaxX, *pMaxY;
    pval *pThis;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif
    

    if (pThis == NULL ||
        getParameters(ht, 4, &pMinX, &pMinY, &pMaxX, &pMaxY) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_double(pMinX);
    convert_to_double(pMinY);
    convert_to_double(pMaxX);
    convert_to_double(pMaxY);

    self->extent.minx = pMinX->value.dval;
    self->extent.miny = pMinY->value.dval;
    self->extent.maxx = pMaxX->value.dval;
    self->extent.maxy = pMaxY->value.dval;
    
    self->cellsize = msAdjustExtent(&(self->extent), self->width, 
                                    self->height);      
    if (msCalculateScale(self->extent, self->units, self->width, self->height, 
                         self->resolution, &(self->scale)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    _phpms_set_property_double(pThis,"cellsize", self->cellsize, E_ERROR); 
    _phpms_set_property_double(pThis,"scale", self->scale, E_ERROR); 

#ifdef PHP4
    if (zend_hash_find(pThis->value.obj.properties, "extent", sizeof("extent"), 
                       (void **)&pExtent) == SUCCESS)
    {
        _phpms_set_property_double((*pExtent),"minx", self->extent.minx, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"miny", self->extent.miny, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"maxx", self->extent.maxx, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"maxy", self->extent.maxy, 
                                   E_ERROR);
    }
#else
    if (_php3_hash_find(pThis->value.ht, "extent", sizeof("extent"), 
                        (void **)&pExtent) == SUCCESS)
    {
        _phpms_set_property_double(pExtent,"minx", self->extent.minx, 
                                   E_ERROR);
        _phpms_set_property_double(pExtent,"miny", self->extent.miny, 
                                   E_ERROR);
        _phpms_set_property_double(pExtent,"maxx", self->extent.maxx, 
                                   E_ERROR);
        _phpms_set_property_double(pExtent,"maxy", self->extent.maxy, 
                                   E_ERROR);
    }
#endif

}

/**********************************************************************
 *        map->setProjection() and map->setWKTProjection()
 **********************************************************************/

static int _php3_ms_map_setProjection(int bWKTProj, mapObj *self, pval *pThis,
                                      int nArgs, pval *pProjString, 
                                      pval *pSetUnitsAndExtents)
{
#ifdef USE_PROJ
    int                 nStatus = 0;
    int                 nUnits =   MS_METERS;  
    projectionObj       in;
    projectionObj       out;
    rectObj             sRect;
    int                 bSetNewExtents = 0; 
    int                 bSetUnitsAndExtents = 0;
    pval                **pExtent;
    

    convert_to_string(pProjString);
    if (nArgs == 2)
    {
        convert_to_long(pSetUnitsAndExtents);
        bSetUnitsAndExtents = pSetUnitsAndExtents->value.lval;
    }

    
    msInitProjection(&in);
    in = self->projection;
    msInitProjection(&out);
    if (bWKTProj)
        msOGCWKT2ProjectionObj(pProjString->value.str.val, &(out),self->debug);
    else
        msLoadProjectionString(&(out),  pProjString->value.str.val);
    sRect = self->extent;
    
    if (in.proj!= NULL && out.proj!=NULL)
    {
        if (msProjectionsDiffer(&in, &out))
        {
            if (msProjectRect(&in, &out, &sRect) == MS_SUCCESS)
              bSetNewExtents =1;
        }
    }

    if (bWKTProj) 
        nStatus = mapObj_setWKTProjection(self, pProjString->value.str.val);
    else
        nStatus = mapObj_setProjection(self, pProjString->value.str.val);

    if (nStatus == -1)
        _phpms_report_mapserver_error(E_ERROR);

    
    nUnits = GetMapserverUnitUsingProj(&(self->projection));
    if (nUnits != -1 && bSetUnitsAndExtents)
    {
/* -------------------------------------------------------------------- 
      set the units and map extents.                                  
 -------------------------------------------------------------------- */
        self->units = nUnits;

        if (bSetNewExtents)
        {
            self->extent = sRect;

            self->cellsize = msAdjustExtent(&(self->extent), self->width, 
                                            self->height); 
            msCalculateScale(self->extent, self->units, self->width, self->height, 
                             self->resolution, &(self->scale));

            _phpms_set_property_double(pThis,"cellsize", self->cellsize, E_ERROR); 
            _phpms_set_property_double(pThis,"scale", self->scale, E_ERROR); 
            _phpms_set_property_long(pThis,"units", self->units, E_ERROR); 

            if (zend_hash_find(pThis->value.obj.properties, "extent", 
                               sizeof("extent"),  (void **)&pExtent) == SUCCESS)
            {
                _phpms_set_property_double((*pExtent),"minx", self->extent.minx, 
                                           E_ERROR);
                _phpms_set_property_double((*pExtent),"miny", self->extent.miny, 
                                           E_ERROR);
                _phpms_set_property_double((*pExtent),"maxx", self->extent.maxx, 
                                           E_ERROR);
                _phpms_set_property_double((*pExtent),"maxy", self->extent.maxy, 
                                           E_ERROR);
            }
        }
    }

    return nStatus;
#else
    php3_error(E_ERROR, 
               "setProjection() available only with PROJ.4 support.");
    return -1;
#endif
}

/**********************************************************************
 *                        map->setProjection()
 **********************************************************************/
/* {{{ proto int map.setProjection(string projection)
   Set projection and coord. system for the map. Returns -1 on error. */

DLEXPORT void php3_ms_map_setProjection(INTERNAL_FUNCTION_PARAMETERS)
{
    mapObj              *self;
    pval                *pProjString, *pSetUnitsAndExtents;
    pval                *pThis;
    int                 nStatus = 0;
    int                 nArgs = ARG_COUNT(ht);

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

 
    if (pThis == NULL ||
        (nArgs != 1 && nArgs != 2))
    {
        WRONG_PARAM_COUNT;
    }
        
    if (getParameters(ht, nArgs, &pProjString, &pSetUnitsAndExtents) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    nStatus = _php3_ms_map_setProjection(MS_FALSE, self, pThis, 
                                         nArgs, pProjString, 
                                         pSetUnitsAndExtents);

    RETURN_LONG(nStatus);
}

/* }}} */

/**********************************************************************
 *                        map->setWKTProjection()
 **********************************************************************/
/* {{{ proto int map.setWKTProjection(string projection)
   Set projection and coord. system for the map. Returns -1 on error. */

DLEXPORT void php3_ms_map_setWKTProjection(INTERNAL_FUNCTION_PARAMETERS)
{
    mapObj              *self;
    pval                *pProjString, *pSetUnitsAndExtents;
    pval                *pThis;
    int                 nStatus = 0;
    int                 nArgs = ARG_COUNT(ht);
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

 
    if (pThis == NULL ||
        (nArgs != 1 && nArgs != 2))
    {
        WRONG_PARAM_COUNT;
    }
        
    if (getParameters(ht, nArgs, &pProjString, &pSetUnitsAndExtents) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    nStatus = _php3_ms_map_setProjection(MS_TRUE, self, pThis, 
                                         nArgs, pProjString, 
                                         pSetUnitsAndExtents);

    RETURN_LONG(nStatus);
}

/* }}} */


/**********************************************************************
 *                        map->getProjection()
 **********************************************************************/

/* {{{ proto int map.getProjection()
   Return the projection string of the map. Returns FALSE on error. */
DLEXPORT void php3_ms_map_getProjection(INTERNAL_FUNCTION_PARAMETERS)
{
    mapObj      *self;
    pval        *pThis = NULL;
    char        *pszPojString = NULL;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif


    if (pThis == NULL)
    {
        RETURN_FALSE;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_FALSE;
    }

    pszPojString = mapObj_getProjection(self);
    if (pszPojString == NULL)
    {
        RETURN_FALSE;
    }
    else
    {
        RETVAL_STRING(pszPojString, 1);
        free(pszPojString);
    }
}
    
/* ==================================================================== */
/*      Zoom related functions.                                         */
/* ==================================================================== */

/************************************************************************/
/*    static double Pix2Georef(int nPixPos, int nPixMin, double nPixMax,*/
/*                              double dfGeoMin, double dfGeoMax,       */
/*                              bool bULisYOrig)                        */
/*                                                                      */
/*        Utility function to convert a pixel pos to georef pos. If     */
/*      bULisYOrig parameter is set to true then the upper left is      */
/*      considered to be the Y origin.                                  */
/*                                                                      */
/************************************************************************/
static double Pix2Georef(int nPixPos, int nPixMin, int nPixMax, 
                         double dfGeoMin, double dfGeoMax, int bULisYOrig)

{
    double      dfWidthGeo = 0.0;
    int         nWidthPix = 0;
    double      dfPixToGeo = 0.0;
    double      dfPosGeo = 0.0;
    double      dfDeltaGeo = 0.0;
    int         nDeltaPix = 0;

    dfWidthGeo = dfGeoMax - dfGeoMin;
    nWidthPix = nPixMax - nPixMin;
   
    if (dfWidthGeo > 0.0 && nWidthPix > 0)
    {
        dfPixToGeo = dfWidthGeo / (double)nWidthPix;

        if (!bULisYOrig)
            nDeltaPix = nPixPos - nPixMin;
        else
            nDeltaPix = nPixMax - nPixPos;
        
        dfDeltaGeo = nDeltaPix * dfPixToGeo;

        dfPosGeo = dfGeoMin + dfDeltaGeo;
    }
    return (dfPosGeo);
}

/************************************************************************/
/*                           map->zoomPoint()                           */
/*                                                                      */
/*      Parmeters are :                                                 */
/*                                                                      */
/*       - Zoom factor : positive values do zoom in, negative values    */
/*                      zoom out. Factor of 1 will recenter.            */
/*                                                                      */
/*       - Pixel position (pointObj) : x, y coordinates of the click.   */
/*       - Width : width in pixel of the current image.                 */
/*       - Height : Height in pixel of the current image.               */
/*       - Georef extent (rectObj) : current georef extents.            */
/*       - MaxGeoref extent (rectObj) : (optional) maximum georef       */
/*                                      extents.                        */
/*                                                                      */
/************************************************************************/
DLEXPORT void php3_ms_map_zoomPoint(INTERNAL_FUNCTION_PARAMETERS)
{
    mapObj      *self;
    pval        *pThis;
#ifdef PHP4
    pval   **pExtent;
#else
    pval   *pExtent;
#endif
    pval        *pZoomFactor;
    pval        *pPixelPos;
    pval        *pWidth, *pHeight;
    pval        *pGeorefExt;
    pval        *pMaxGeorefExt;
    rectObj     *poGeorefExt = NULL;
    rectObj     *poMaxGeorefExt = NULL;
    pointObj    *poPixPos = NULL;
    double      dfGeoPosX, dfGeoPosY;
    double      dfDeltaX, dfDeltaY;
    rectObj     oNewGeorefExt;    
    double      dfNewScale = 0.0;
    int         bMaxExtSet = 0;
    int         nArgs = ARG_COUNT(ht);
    double      dfDeltaExt = -1.0;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||   
        (nArgs != 5 && nArgs != 6))
    {
        WRONG_PARAM_COUNT;
    }
    
    if (getParameters(ht, nArgs, 
                      &pZoomFactor, &pPixelPos, &pWidth, &pHeight,
                      &pGeorefExt, &pMaxGeorefExt) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }



    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_FALSE;
    }

    if (nArgs == 6)
        bMaxExtSet =1;

    convert_to_long(pZoomFactor);
    convert_to_long(pWidth);
    convert_to_long(pHeight);
         
    poGeorefExt = (rectObj *)_phpms_fetch_handle2(pGeorefExt, 
                                                  PHPMS_GLOBAL(le_msrect_ref),
                                                  PHPMS_GLOBAL(le_msrect_new),
                                                  list TSRMLS_CC);
    poPixPos = (pointObj *)_phpms_fetch_handle2(pPixelPos, 
                                                PHPMS_GLOBAL(le_mspoint_new), 
                                                PHPMS_GLOBAL(le_mspoint_ref),
                                                list TSRMLS_CC);
    
    if (bMaxExtSet)
        poMaxGeorefExt = 
            (rectObj *)_phpms_fetch_handle2(pMaxGeorefExt, 
                                            PHPMS_GLOBAL(le_msrect_ref),
                                            PHPMS_GLOBAL(le_msrect_new),
                                            list TSRMLS_CC);

/* -------------------------------------------------------------------- */
/*      check the validity of the parameters.                           */
/* -------------------------------------------------------------------- */
    if (pZoomFactor->value.lval == 0 || 
        pWidth->value.lval <= 0 ||
        pHeight->value.lval <= 0 ||
        poGeorefExt == NULL ||
        poPixPos == NULL ||
        (bMaxExtSet && poMaxGeorefExt == NULL))
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "zoomPoint failed : incorrect parameters\n");
        RETURN_FALSE;
    }

/* -------------------------------------------------------------------- */
/*      check if the values passed are consistent min > max.             */
/* -------------------------------------------------------------------- */
    if (poGeorefExt->minx >= poGeorefExt->maxx)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "zoomPoint failed : Georeferenced coordinates minx >= maxx\n");
    }
    if (poGeorefExt->miny >= poGeorefExt->maxy)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "zoomPoint failed : Georeferenced coordinates miny >= maxy\n");
    }
    if (bMaxExtSet)
    {
        if (poMaxGeorefExt->minx >= poMaxGeorefExt->maxx)
        {
            _phpms_report_mapserver_error(E_WARNING);
            php3_error(E_ERROR, "zoomPoint failed : Max Georeferenced coordinates minx >= maxx\n");
        }
        if (poMaxGeorefExt->miny >= poMaxGeorefExt->maxy)
        {
            _phpms_report_mapserver_error(E_WARNING);
            php3_error(E_ERROR, "zoomPoint failed : Max Georeferenced coordinates miny >= maxy\n");
        }
    }

    
    dfGeoPosX = Pix2Georef((int)poPixPos->x, 0, (int)pWidth->value.lval, 
                           poGeorefExt->minx, poGeorefExt->maxx, 0); 
    dfGeoPosY = Pix2Georef((int)poPixPos->y, 0, (int)pHeight->value.lval, 
                           poGeorefExt->miny, poGeorefExt->maxy, 1); 
    dfDeltaX = poGeorefExt->maxx - poGeorefExt->minx;
    dfDeltaY = poGeorefExt->maxy - poGeorefExt->miny;

   
/* -------------------------------------------------------------------- */
/*      zoom in                                                         */
/* -------------------------------------------------------------------- */
    if (pZoomFactor->value.lval > 1)
    {
        oNewGeorefExt.minx = 
            dfGeoPosX - (dfDeltaX/(2*pZoomFactor->value.lval));        
         oNewGeorefExt.miny = 
             dfGeoPosY - (dfDeltaY/(2*pZoomFactor->value.lval));        
         oNewGeorefExt.maxx = 
             dfGeoPosX + (dfDeltaX/(2*pZoomFactor->value.lval));        
         oNewGeorefExt.maxy = 
             dfGeoPosY + (dfDeltaY/(2*pZoomFactor->value.lval));
    }

    if (pZoomFactor->value.lval < 0)
    {
        oNewGeorefExt.minx = 
            dfGeoPosX - (dfDeltaX/2)*(abs(pZoomFactor->value.lval));    
        oNewGeorefExt.miny = 
            dfGeoPosY - (dfDeltaY/2)*(abs(pZoomFactor->value.lval));    
        oNewGeorefExt.maxx = 
            dfGeoPosX + (dfDeltaX/2)*(abs(pZoomFactor->value.lval));    
        oNewGeorefExt.maxy = 
            dfGeoPosY + (dfDeltaY/2)*(abs(pZoomFactor->value.lval));
    }
    if (pZoomFactor->value.lval == 1)
    {
        oNewGeorefExt.minx = dfGeoPosX - (dfDeltaX/2);
        oNewGeorefExt.miny = dfGeoPosY - (dfDeltaY/2);
        oNewGeorefExt.maxx = dfGeoPosX + (dfDeltaX/2);
        oNewGeorefExt.maxy = dfGeoPosY + (dfDeltaY/2);
    }

/* -------------------------------------------------------------------- */
/*      if the min and max scale are set in the map file, we will       */
/*      use them to test before zooming.                                */
/* -------------------------------------------------------------------- */
    msAdjustExtent(&oNewGeorefExt, self->width, self->height);
    if (msCalculateScale(oNewGeorefExt, self->units, 
                         self->width, self->height, 
                         self->resolution, &dfNewScale) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    if (self->web.maxscale > 0)
    {
        if (pZoomFactor->value.lval < 0 && dfNewScale >  self->web.maxscale)
        {
            RETURN_FALSE;
        }
    }

/* ==================================================================== */
/*      we do a spcial case for zoom in : we try to zoom as much as     */
/*      possible using the mincale set in the .map.                     */
/* ==================================================================== */
    if (self->web.minscale > 0 && dfNewScale <  self->web.minscale &&
        pZoomFactor->value.lval > 1)
    {
        dfDeltaExt = 
            GetDeltaExtentsUsingScale(self->web.minscale, self->units,
                                      dfGeoPosY, self->width, 
                                      self->resolution);
        if (dfDeltaExt > 0.0)
        {
            oNewGeorefExt.minx = dfGeoPosX - (dfDeltaExt/2);
            oNewGeorefExt.miny = dfGeoPosY - (dfDeltaExt/2);
            oNewGeorefExt.maxx = dfGeoPosX + (dfDeltaExt/2);
            oNewGeorefExt.maxy = dfGeoPosY + (dfDeltaExt/2);
        }
        else
          RETURN_FALSE;
    }
/* -------------------------------------------------------------------- */
/*      If the buffer is set, make sure that the extents do not go      */
/*      beyond the buffer.                                              */
/* -------------------------------------------------------------------- */
    if (bMaxExtSet)
    {
        dfDeltaX = oNewGeorefExt.maxx - oNewGeorefExt.minx;
        dfDeltaY = oNewGeorefExt.maxy - oNewGeorefExt.miny;
        
        /* Make sure Current georef extents is not bigger than max extents */
        if (dfDeltaX > (poMaxGeorefExt->maxx-poMaxGeorefExt->minx))
            dfDeltaX = poMaxGeorefExt->maxx-poMaxGeorefExt->minx;
        if (dfDeltaY > (poMaxGeorefExt->maxy-poMaxGeorefExt->miny))
            dfDeltaY = poMaxGeorefExt->maxy-poMaxGeorefExt->miny;

        if (oNewGeorefExt.minx < poMaxGeorefExt->minx)
        {
            oNewGeorefExt.minx = poMaxGeorefExt->minx;
            oNewGeorefExt.maxx =  oNewGeorefExt.minx + dfDeltaX;
        }
        if (oNewGeorefExt.maxx > poMaxGeorefExt->maxx)
        {
            oNewGeorefExt.maxx = poMaxGeorefExt->maxx;
            oNewGeorefExt.minx = oNewGeorefExt.maxx - dfDeltaX;
        }
        if (oNewGeorefExt.miny < poMaxGeorefExt->miny)
        {
            oNewGeorefExt.miny = poMaxGeorefExt->miny;
            oNewGeorefExt.maxy =  oNewGeorefExt.miny + dfDeltaY;
        }
        if (oNewGeorefExt.maxy > poMaxGeorefExt->maxy)
        {
            oNewGeorefExt.maxy = poMaxGeorefExt->maxy;
            oNewGeorefExt.miny = oNewGeorefExt.maxy - dfDeltaY;
        }
    }
    
/* -------------------------------------------------------------------- */
/*      set the map extents with new values.                            */
/* -------------------------------------------------------------------- */
    self->extent.minx = oNewGeorefExt.minx;
    self->extent.miny = oNewGeorefExt.miny;
    self->extent.maxx = oNewGeorefExt.maxx;
    self->extent.maxy = oNewGeorefExt.maxy;
    
    self->cellsize = msAdjustExtent(&(self->extent), self->width, 
                                    self->height);      
    dfDeltaX = self->extent.maxx - self->extent.minx;
    dfDeltaY = self->extent.maxy - self->extent.miny; 

    if (bMaxExtSet)
    {
        if (self->extent.minx < poMaxGeorefExt->minx)
        {
            self->extent.minx = poMaxGeorefExt->minx;
            self->extent.maxx = self->extent.minx + dfDeltaX;
        }
        if (self->extent.maxx > poMaxGeorefExt->maxx)
        {
            self->extent.maxx = poMaxGeorefExt->maxx;
            oNewGeorefExt.minx = oNewGeorefExt.maxx - dfDeltaX;
        }
        if (self->extent.miny < poMaxGeorefExt->miny)
        {
            self->extent.miny = poMaxGeorefExt->miny;
            self->extent.maxy =  self->extent.miny + dfDeltaY;
        }
        if (self->extent.maxy > poMaxGeorefExt->maxy)
        {
            self->extent.maxy = poMaxGeorefExt->maxy;
            oNewGeorefExt.miny = oNewGeorefExt.maxy - dfDeltaY;
        }
    }
    
    if (msCalculateScale(self->extent, self->units, self->width, self->height, 
                         self->resolution, &(self->scale)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    _phpms_set_property_double(pThis,"cellsize", self->cellsize, E_ERROR); 
    _phpms_set_property_double(pThis,"scale", self->scale, E_ERROR); 

#ifdef PHP4
    if (zend_hash_find(pThis->value.obj.properties, "extent", sizeof("extent"), 
                       (void **)&pExtent) == SUCCESS)
    {
        _phpms_set_property_double((*pExtent),"minx", self->extent.minx, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"miny", self->extent.miny, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"maxx", self->extent.maxx, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"maxy", self->extent.maxy, 
                                   E_ERROR);
    }
#else
    if (_php3_hash_find(pThis->value.ht, "extent", sizeof("extent"), 
                        (void **)&pExtent) == SUCCESS)
    {
        _phpms_set_property_double(pExtent,"minx", self->extent.minx, 
                                   E_ERROR);
        _phpms_set_property_double(pExtent,"miny", self->extent.miny, 
                                   E_ERROR);
        _phpms_set_property_double(pExtent,"maxx", self->extent.maxx, 
                                   E_ERROR);
        _phpms_set_property_double(pExtent,"maxy", self->extent.maxy, 
                                   E_ERROR);
    }
#endif

     RETURN_TRUE;

}

/************************************************************************/
/*                           map->zoomRectange()                        */
/*                                                                      */
/*      Parmeters are :                                                 */
/*                                                                      */
/*       - Pixel position (rectObj) : extents in pixels.                */
/*       - Width : width in pixel of the current image.                 */
/*       - Height : Height in pixel of the current image.               */
/*       - Georef extent (rectObj) : current georef extents.            */
/*       - MaxGeoref extent (rectObj) : (optional) maximum georef       */
/*                                      extents.                        */
/*                                                                      */
/************************************************************************/
DLEXPORT void php3_ms_map_zoomRectangle(INTERNAL_FUNCTION_PARAMETERS)
{
    mapObj      *self;
    pval        *pThis;
#ifdef PHP4
    pval   **pExtent;
#else
    pval   *pExtent;
#endif

    pval        *pPixelExt;
    pval        *pWidth, *pHeight;
    pval        *pGeorefExt;
    pval        *pMaxGeorefExt;
    rectObj     *poGeorefExt = NULL;
    rectObj     *poPixExt = NULL;
    rectObj     *poMaxGeorefExt = NULL;
    double      dfNewScale = 0.0;
    rectObj     oNewGeorefExt;    
    double      dfMiddleX =0.0;
    double      dfMiddleY =0.0;
    double      dfDeltaExt =0.0;
    int         bMaxExtSet = 0;
    int         nArgs = ARG_COUNT(ht);
    double      dfDeltaX = 0;
    double      dfDeltaY = 0;

#ifdef PHP4
    HashTable   *list=NULL;
#endif
    
#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        (nArgs != 4 && nArgs != 5))
    {
        WRONG_PARAM_COUNT;
    }
    if (getParameters(ht, nArgs, &pPixelExt, &pWidth, &pHeight,
                      &pGeorefExt, &pMaxGeorefExt) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_FALSE;
    }

    if (nArgs == 5)
      bMaxExtSet =1;

    convert_to_long(pWidth);
    convert_to_long(pHeight);
    
    poGeorefExt = (rectObj *)_phpms_fetch_handle2(pGeorefExt, 
                                                  PHPMS_GLOBAL(le_msrect_ref),
                                                  PHPMS_GLOBAL(le_msrect_new),
                                                  list TSRMLS_CC);
    poPixExt = (rectObj *)_phpms_fetch_handle2(pPixelExt, 
                                               PHPMS_GLOBAL(le_msrect_ref), 
                                               PHPMS_GLOBAL(le_msrect_new),
                                               list TSRMLS_CC);

    if (bMaxExtSet)
        poMaxGeorefExt = 
            (rectObj *)_phpms_fetch_handle2(pMaxGeorefExt, 
                                            PHPMS_GLOBAL(le_msrect_ref),
                                            PHPMS_GLOBAL(le_msrect_new),
                                            list TSRMLS_CC);
/* -------------------------------------------------------------------- */
/*      check the validity of the parameters.                           */
/* -------------------------------------------------------------------- */
    if (pWidth->value.lval <= 0 ||
        pHeight->value.lval <= 0 ||
        poGeorefExt == NULL ||
        poPixExt == NULL ||
        (bMaxExtSet && poMaxGeorefExt == NULL))
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "zoomRectangle failed : incorrect parameters\n");
            /*RETURN_FALSE;*/
    }

/* -------------------------------------------------------------------- */
/*      check if the values passed are consistent min > max.            */
/* -------------------------------------------------------------------- */
    if (poGeorefExt->minx >= poGeorefExt->maxx)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "zoomRectangle failed : Georeferenced coordinates minx >= maxx\n");
    }
    if (poGeorefExt->miny >= poGeorefExt->maxy)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "zoomRectangle failed : Georeferenced coordinates miny >= maxy\n");
    }
    if (bMaxExtSet)
    {
        if (poMaxGeorefExt->minx >= poMaxGeorefExt->maxx)
        {
            _phpms_report_mapserver_error(E_WARNING);
            php3_error(E_ERROR, "zoomRectangle failed : Max Georeferenced coordinates minx >= maxx\n");
        }
        if (poMaxGeorefExt->miny >= poMaxGeorefExt->maxy)
        {
            _phpms_report_mapserver_error(E_WARNING);
            php3_error(E_ERROR, "zoomRectangle failed : Max Georeferenced coordinates miny >= maxy\n");
        }
    }


    oNewGeorefExt.minx = Pix2Georef((int)poPixExt->minx, 0, 
                                    (int)pWidth->value.lval, 
                                    poGeorefExt->minx, poGeorefExt->maxx, 0); 
    oNewGeorefExt.maxx = Pix2Georef((int)poPixExt->maxx, 0, 
                                    (int)pWidth->value.lval, 
                                    poGeorefExt->minx, poGeorefExt->maxx, 0); 
    oNewGeorefExt.miny = Pix2Georef((int)poPixExt->miny, 0, 
                                    (int)pHeight->value.lval, 
                                    poGeorefExt->miny, poGeorefExt->maxy, 1); 
    oNewGeorefExt.maxy = Pix2Georef((int)poPixExt->maxy, 0, 
                                    (int)pHeight->value.lval, 
                                    poGeorefExt->miny, poGeorefExt->maxy, 1); 
    

    msAdjustExtent(&oNewGeorefExt, self->width, self->height);

/* -------------------------------------------------------------------- */
/*      if the min and max scale are set in the map file, we will       */
/*      use them to test before setting extents.                        */
/* -------------------------------------------------------------------- */
    if (msCalculateScale(oNewGeorefExt, self->units, 
                         self->width, self->height, 
                         self->resolution, &dfNewScale) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    if (self->web.maxscale > 0 &&  dfNewScale > self->web.maxscale)
    {
        RETURN_FALSE;
    }

    if (self->web.minscale > 0 && dfNewScale <  self->web.minscale)
    {
        dfMiddleX = oNewGeorefExt.minx + 
            ((oNewGeorefExt.maxx - oNewGeorefExt.minx)/2);
        dfMiddleY = oNewGeorefExt.miny + 
            ((oNewGeorefExt.maxy - oNewGeorefExt.miny)/2);
        
        dfDeltaExt = 
            GetDeltaExtentsUsingScale(self->web.minscale, self->units, 
                                      dfMiddleY, self->width, 
                                      self->resolution);

        if (dfDeltaExt > 0.0)
        {
            oNewGeorefExt.minx = dfMiddleX - (dfDeltaExt/2);
            oNewGeorefExt.miny = dfMiddleY - (dfDeltaExt/2);
            oNewGeorefExt.maxx = dfMiddleX + (dfDeltaExt/2);
            oNewGeorefExt.maxy = dfMiddleY + (dfDeltaExt/2);
        }
        else
          RETURN_FALSE;
    }

/* -------------------------------------------------------------------- */
/*      If the buffer is set, make sure that the extents do not go      */
/*      beyond the buffer.                                              */
/* -------------------------------------------------------------------- */
    if (bMaxExtSet)
    {
        dfDeltaX = oNewGeorefExt.maxx - oNewGeorefExt.minx;
        dfDeltaY = oNewGeorefExt.maxy - oNewGeorefExt.miny;
        
        /* Make sure Current georef extents is not bigger than max extents */
        if (dfDeltaX > (poMaxGeorefExt->maxx-poMaxGeorefExt->minx))
            dfDeltaX = poMaxGeorefExt->maxx-poMaxGeorefExt->minx;
        if (dfDeltaY > (poMaxGeorefExt->maxy-poMaxGeorefExt->miny))
            dfDeltaY = poMaxGeorefExt->maxy-poMaxGeorefExt->miny;

        if (oNewGeorefExt.minx < poMaxGeorefExt->minx)
        {
            oNewGeorefExt.minx = poMaxGeorefExt->minx;
            oNewGeorefExt.maxx =  oNewGeorefExt.minx + dfDeltaX;
        }
        if (oNewGeorefExt.maxx > poMaxGeorefExt->maxx)
        {
            oNewGeorefExt.maxx = poMaxGeorefExt->maxx;
            oNewGeorefExt.minx = oNewGeorefExt.maxx - dfDeltaX;
        }
        if (oNewGeorefExt.miny < poMaxGeorefExt->miny)
        {
            oNewGeorefExt.miny = poMaxGeorefExt->miny;
            oNewGeorefExt.maxy =  oNewGeorefExt.miny + dfDeltaY;
        }
        if (oNewGeorefExt.maxy > poMaxGeorefExt->maxy)
        {
            oNewGeorefExt.maxy = poMaxGeorefExt->maxy;
            oNewGeorefExt.miny = oNewGeorefExt.maxy - dfDeltaY;
        }
    }

    self->extent.minx = oNewGeorefExt.minx;
    self->extent.miny = oNewGeorefExt.miny;
    self->extent.maxx = oNewGeorefExt.maxx;
    self->extent.maxy = oNewGeorefExt.maxy;
    
    self->cellsize = msAdjustExtent(&(self->extent), self->width, 
                                    self->height);    
    dfDeltaX = self->extent.maxx - self->extent.minx;
    dfDeltaY = self->extent.maxy - self->extent.miny; 

    if (bMaxExtSet)
    {
        if (self->extent.minx < poMaxGeorefExt->minx)
        {
            self->extent.minx = poMaxGeorefExt->minx;
            self->extent.maxx = self->extent.minx + dfDeltaX;
        }
        if (self->extent.maxx > poMaxGeorefExt->maxx)
        {
            self->extent.maxx = poMaxGeorefExt->maxx;
            oNewGeorefExt.minx = oNewGeorefExt.maxx - dfDeltaX;
        }
        if (self->extent.miny < poMaxGeorefExt->miny)
        {
            self->extent.miny = poMaxGeorefExt->miny;
            self->extent.maxy =  self->extent.miny + dfDeltaY;
        }
        if (self->extent.maxy > poMaxGeorefExt->maxy)
        {
            self->extent.maxy = poMaxGeorefExt->maxy;
            oNewGeorefExt.miny = oNewGeorefExt.maxy - dfDeltaY;
        }
    }

    if (msCalculateScale(self->extent, self->units, self->width, self->height, 
                         self->resolution, &(self->scale)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    _phpms_set_property_double(pThis,"cellsize", self->cellsize, E_ERROR); 
    _phpms_set_property_double(pThis,"scale", self->scale, E_ERROR); 

#ifdef PHP4
    if (zend_hash_find(pThis->value.obj.properties, "extent", sizeof("extent"), 
                        (void **)&pExtent) == SUCCESS)
    {
        _phpms_set_property_double((*pExtent),"minx", self->extent.minx, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"miny", self->extent.miny, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"maxx", self->extent.maxx, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"maxy", self->extent.maxy, 
                                   E_ERROR);
    }
#else
    if (_php3_hash_find(pThis->value.ht, "extent", sizeof("extent"), 
                        (void **)&pExtent) == SUCCESS)
    {
        _phpms_set_property_double(pExtent,"minx", self->extent.minx, 
                                   E_ERROR);
        _phpms_set_property_double(pExtent,"miny", self->extent.miny, 
                                   E_ERROR);
        _phpms_set_property_double(pExtent,"maxx", self->extent.maxx, 
                                   E_ERROR);
        _phpms_set_property_double(pExtent,"maxy", self->extent.maxy, 
                                   E_ERROR);
    }
#endif

    RETURN_TRUE;
}

/************************************************************************/
/*                             map->zoomScale()                         */
/*                                                                      */
/*      Parmeters are :                                                 */
/*                                                                      */
/*       - Scale : Scale at which to see the map. Must be a positive    */
/*                 value. Ex : for a scale to 1/250000, the value of    */
/*                 this parameter is 250000.                            */
/*       - Pixel position (pointObj) : x, y coordinates of the click.   */
/*       - Width : width in pixel of the current image.                 */
/*       - Height : Height in pixel of the current image.               */
/*       - Georef extent (rectObj) : current georef extents.            */
/*       - MaxGeoref extent (rectObj) : (optional) maximum georef       */
/*                                      extents.                        */
/************************************************************************/
DLEXPORT void php3_ms_map_zoomScale(INTERNAL_FUNCTION_PARAMETERS)
{
    mapObj      *self;
    pval        *pThis;
#ifdef PHP4
    pval   **pExtent;
#else
    pval   *pExtent;
#endif
    pval        *pScale;
    pval        *pPixelPos;
    pval        *pWidth, *pHeight;
    pval        *pGeorefExt;
    pval        *pMaxGeorefExt;
    rectObj     *poGeorefExt = NULL;
    rectObj     *poMaxGeorefExt = NULL;
    pointObj    *poPixPos = NULL;
    double      dfGeoPosX, dfGeoPosY;
    double      dfDeltaX, dfDeltaY;
    rectObj     oNewGeorefExt;    
    double      dfNewScale = 0.0;
    int         bMaxExtSet = 0;
    int         nArgs = ARG_COUNT(ht);
    double      dfDeltaExt = -1.0;
    double      dfCurrentScale = 0.0;
    int         nTmp = 0;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||   
        (nArgs != 5 && nArgs != 6))
    {
        WRONG_PARAM_COUNT;
    }
    
    if (getParameters(ht, nArgs, 
                      &pScale, &pPixelPos, &pWidth, &pHeight,
                      &pGeorefExt, &pMaxGeorefExt) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_FALSE;
    }

    if (nArgs == 6)
        bMaxExtSet =1;

    convert_to_double(pScale);
    convert_to_long(pWidth);
    convert_to_long(pHeight);
         
    poGeorefExt = (rectObj *)_phpms_fetch_handle2(pGeorefExt, 
                                                  PHPMS_GLOBAL(le_msrect_ref),
                                                  PHPMS_GLOBAL(le_msrect_new),
                                                  list TSRMLS_CC);
    poPixPos = (pointObj *)_phpms_fetch_handle2(pPixelPos, 
                                                PHPMS_GLOBAL(le_mspoint_new), 
                                                PHPMS_GLOBAL(le_mspoint_ref),
                                                list TSRMLS_CC);
    
    if (bMaxExtSet)
        poMaxGeorefExt = 
            (rectObj *)_phpms_fetch_handle2(pMaxGeorefExt, 
                                            PHPMS_GLOBAL(le_msrect_ref),
                                            PHPMS_GLOBAL(le_msrect_new),
                                            list TSRMLS_CC);

/* -------------------------------------------------------------------- */
/*      check the validity of the parameters.                           */
/* -------------------------------------------------------------------- */
    if (pScale->value.dval <= 0.0 || 
        pWidth->value.lval <= 0 ||
        pHeight->value.lval <= 0 ||
        poGeorefExt == NULL ||
        poPixPos == NULL ||
        (bMaxExtSet && poMaxGeorefExt == NULL))
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "zoomScale failed : incorrect parameters\n");
        RETURN_FALSE;
    }

/* -------------------------------------------------------------------- */
/*      check if the values passed are consistent min > max.             */
/* -------------------------------------------------------------------- */
    if (poGeorefExt->minx >= poGeorefExt->maxx)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "zoomScale failed : Georeferenced coordinates minx >= maxx\n");
    }
    if (poGeorefExt->miny >= poGeorefExt->maxy)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "zoomScale failed : Georeferenced coordinates miny >= maxy\n");
    }
    if (bMaxExtSet)
    {
        if (poMaxGeorefExt->minx >= poMaxGeorefExt->maxx)
        {
            _phpms_report_mapserver_error(E_WARNING);
            php3_error(E_ERROR, "zoomScale failed : Max Georeferenced coordinates minx >= maxx\n");
        }
        if (poMaxGeorefExt->miny >= poMaxGeorefExt->maxy)
        {
            _phpms_report_mapserver_error(E_WARNING);
            php3_error(E_ERROR, "zoomScale failed : Max Georeferenced coordinates miny >= maxy\n");
        }
    }
    

    dfGeoPosX = Pix2Georef((int)poPixPos->x, 0, (int)pWidth->value.lval, 
                           poGeorefExt->minx, poGeorefExt->maxx, 0); 
    dfGeoPosY = Pix2Georef((int)poPixPos->y, 0, (int)pHeight->value.lval, 
                           poGeorefExt->miny, poGeorefExt->maxy, 1); 
    dfDeltaX = poGeorefExt->maxx - poGeorefExt->minx;
    dfDeltaY = poGeorefExt->maxy - poGeorefExt->miny;

   
/* -------------------------------------------------------------------- */
/*      Calculate new extents based on the sacle.                       */
/* -------------------------------------------------------------------- */

/* ==================================================================== */
/*      make sure to take the smallest size because this is the one     */
/*      that will be used to ajust the scale.                           */
/* ==================================================================== */

    if (self->width <  self->height)
      nTmp = self->width;
    else
      nTmp = self->height;

    dfDeltaExt = 
        GetDeltaExtentsUsingScale(pScale->value.dval, self->units, dfGeoPosY,
                                  nTmp, self->resolution);
                                  
    if (dfDeltaExt > 0.0)
    {
        oNewGeorefExt.minx = dfGeoPosX - (dfDeltaExt/2);
        oNewGeorefExt.miny = dfGeoPosY - (dfDeltaExt/2);
        oNewGeorefExt.maxx = dfGeoPosX + (dfDeltaExt/2);
        oNewGeorefExt.maxy = dfGeoPosY + (dfDeltaExt/2);
    }
    else
      RETURN_FALSE;

/* -------------------------------------------------------------------- */
/*      get current scale.                                              */
/* -------------------------------------------------------------------- */
    if (msCalculateScale(*poGeorefExt, self->units, 
                         self->width, self->height,
                         self->resolution, &dfCurrentScale) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

/* -------------------------------------------------------------------- */
/*      if the min and max scale are set in the map file, we will       */
/*      use them to test before zooming.                                */
/*                                                                      */
/*       This function has the same effect as zoomin or zoom out. If    */
/*      the current scale is > newscale we zoom in; else it is a        */
/*      zoom out.                                                       */
/* -------------------------------------------------------------------- */
    msAdjustExtent(&oNewGeorefExt, self->width, self->height);
    if (msCalculateScale(oNewGeorefExt, self->units, 
                         self->width, self->height,
                         self->resolution, &dfNewScale) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    if (self->web.maxscale > 0)
    {
        if (dfCurrentScale < dfNewScale && dfNewScale >  self->web.maxscale)
        {
            RETURN_FALSE;
        }
    }

/* ==================================================================== */
/*      we do a special case for zoom in : we try to zoom as much as    */
/*      possible using the mincale set in the .map.                     */
/* ==================================================================== */
    if (self->web.minscale > 0 && dfNewScale <  self->web.minscale &&
        dfCurrentScale > dfNewScale)
    {
        dfDeltaExt = 
            GetDeltaExtentsUsingScale(self->web.minscale, self->units, 
                                      dfGeoPosY, self->width, 
                                      self->resolution);
        if (dfDeltaExt > 0.0)
        {
            oNewGeorefExt.minx = dfGeoPosX - (dfDeltaExt/2);
            oNewGeorefExt.miny = dfGeoPosY - (dfDeltaExt/2);
            oNewGeorefExt.maxx = dfGeoPosX + (dfDeltaExt/2);
            oNewGeorefExt.maxy = dfGeoPosY + (dfDeltaExt/2);
        }
        else
          RETURN_FALSE;
    }
/* -------------------------------------------------------------------- */
/*      If the buffer is set, make sure that the extents do not go      */
/*      beyond the buffer.                                              */
/* -------------------------------------------------------------------- */
    if (bMaxExtSet)
    {
        dfDeltaX = oNewGeorefExt.maxx - oNewGeorefExt.minx;
        dfDeltaY = oNewGeorefExt.maxy - oNewGeorefExt.miny;
        
        /* Make sure Current georef extents is not bigger than max extents */
        if (dfDeltaX > (poMaxGeorefExt->maxx-poMaxGeorefExt->minx))
            dfDeltaX = poMaxGeorefExt->maxx-poMaxGeorefExt->minx;
        if (dfDeltaY > (poMaxGeorefExt->maxy-poMaxGeorefExt->miny))
            dfDeltaY = poMaxGeorefExt->maxy-poMaxGeorefExt->miny;

        if (oNewGeorefExt.minx < poMaxGeorefExt->minx)
        {
            oNewGeorefExt.minx = poMaxGeorefExt->minx;
            oNewGeorefExt.maxx =  oNewGeorefExt.minx + dfDeltaX;
        }
        if (oNewGeorefExt.maxx > poMaxGeorefExt->maxx)
        {
            oNewGeorefExt.maxx = poMaxGeorefExt->maxx;
            oNewGeorefExt.minx = oNewGeorefExt.maxx - dfDeltaX;
        }
        if (oNewGeorefExt.miny < poMaxGeorefExt->miny)
        {
            oNewGeorefExt.miny = poMaxGeorefExt->miny;
            oNewGeorefExt.maxy =  oNewGeorefExt.miny + dfDeltaY;
        }
        if (oNewGeorefExt.maxy > poMaxGeorefExt->maxy)
        {
            oNewGeorefExt.maxy = poMaxGeorefExt->maxy;
            oNewGeorefExt.miny = oNewGeorefExt.maxy - dfDeltaY;
        }
    }
    
/* -------------------------------------------------------------------- */
/*      set the map extents with new values.                            */
/* -------------------------------------------------------------------- */
    self->extent.minx = oNewGeorefExt.minx;
    self->extent.miny = oNewGeorefExt.miny;
    self->extent.maxx = oNewGeorefExt.maxx;
    self->extent.maxy = oNewGeorefExt.maxy;
    

    self->cellsize = msAdjustExtent(&(self->extent), self->width, 
                                    self->height);      
    dfDeltaX = self->extent.maxx - self->extent.minx;
    dfDeltaY = self->extent.maxy - self->extent.miny; 
    
    if (bMaxExtSet)
    {
        if (self->extent.minx < poMaxGeorefExt->minx)
        {
            self->extent.minx = poMaxGeorefExt->minx;
            self->extent.maxx = self->extent.minx + dfDeltaX;
        }
        if (self->extent.maxx > poMaxGeorefExt->maxx)
        {
            self->extent.maxx = poMaxGeorefExt->maxx;
            oNewGeorefExt.minx = oNewGeorefExt.maxx - dfDeltaX;
        }
        if (self->extent.miny < poMaxGeorefExt->miny)
        {
            self->extent.miny = poMaxGeorefExt->miny;
            self->extent.maxy =  self->extent.miny + dfDeltaY;
        }
        if (self->extent.maxy > poMaxGeorefExt->maxy)
        {
            self->extent.miny = poMaxGeorefExt->maxy;
            oNewGeorefExt.miny = oNewGeorefExt.maxy - dfDeltaY;
        }
    }
    
    if (msCalculateScale(self->extent, self->units, self->width, self->height, 
                         self->resolution, &(self->scale)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    _phpms_set_property_double(pThis,"cellsize", self->cellsize, E_ERROR); 
    _phpms_set_property_double(pThis,"scale", self->scale, E_ERROR); 

#ifdef PHP4
    if (zend_hash_find(pThis->value.obj.properties, "extent", sizeof("extent"), 
                       (void **)&pExtent) == SUCCESS)
    {
        _phpms_set_property_double((*pExtent),"minx", self->extent.minx, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"miny", self->extent.miny, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"maxx", self->extent.maxx, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"maxy", self->extent.maxy, 
                                   E_ERROR);
    }
#else
    if (_php3_hash_find(pThis->value.ht, "extent", sizeof("extent"), 
                        (void **)&pExtent) == SUCCESS)
    {
        _phpms_set_property_double(pExtent,"minx", self->extent.minx, 
                                   E_ERROR);
        _phpms_set_property_double(pExtent,"miny", self->extent.miny, 
                                   E_ERROR);
        _phpms_set_property_double(pExtent,"maxx", self->extent.maxx, 
                                   E_ERROR);
        _phpms_set_property_double(pExtent,"maxy", self->extent.maxy, 
                                   E_ERROR);
    }
#endif

     RETURN_TRUE;

}
    


/************************************************************************/
/*                              DLEXPORT void                           */
/*        php3_ms_map_getSymbolByName(INTERNAL_FUNCTION_PARAMETERS)     */
/*                                                                      */
/*       Get the symbol id using it's name. Parameters are :            */
/*                                                                      */
/*        - symbol name                                                 */
/************************************************************************/
DLEXPORT void php3_ms_map_getSymbolByName(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis;
    pval        *pSymName;
    mapObj      *self=NULL;
    int         nSymbolId = -1;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pSymName) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pSymName);


    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self != NULL)
    {
        nSymbolId = 
            mapObj_getSymbolByName(self, pSymName->value.str.val);
    }

    RETURN_LONG(nSymbolId);
}


/************************************************************************/
/*                              DLEXPORT void                           */
/*        php3_ms_map_getSymbolByName(INTERNAL_FUNCTION_PARAMETERS)     */
/*                                                                      */
/*       Get the symbol id using it's name. Parameters are :            */
/*                                                                      */
/*        - symbol name                                                 */
/************************************************************************/
DLEXPORT void php3_ms_map_getSymbolObjectById(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis;
    pval        *pSymId;
    mapObj      *self=NULL;
    symbolObj *psSymbol = NULL;
    int map_id;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pSymId) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pSymId);


    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);

    if (self == NULL)
      php3_error(E_ERROR, "Invalid map object.");

    if ( pSymId->value.lval < 0 ||  
         pSymId->value.lval >= self->symbolset.numsymbols)
      php3_error(E_ERROR, "Invalid symbol index.");

    map_id = _phpms_fetch_property_resource(pThis, "_handle_", E_ERROR);

    psSymbol = &self->symbolset.symbol[pSymId->value.lval];
    /* Return style object */
    _phpms_build_symbol_object(psSymbol, map_id,  list, return_value TSRMLS_CC);
}

/* }}} */


/**********************************************************************
 *                        map->prepareImage()
 **********************************************************************/

/* {{{ proto int map.prepareImage()
   Return handle on blank image object. */

DLEXPORT void php3_ms_map_prepareImage(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    mapObj *self;
    imageObj *im = NULL;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL || (im = mapObj_prepareImage(self)) == NULL)
        _phpms_report_mapserver_error(E_ERROR);

    /* Return an image object */
    _phpms_build_img_object(im, &(self->web), list, return_value);
}
/* }}} */

/**********************************************************************
 *                        map->prepareQuery()
 **********************************************************************/

/* {{{ proto int map.prepareQuery()
   Calculate the scale of the map and assign it to the map->scale */

DLEXPORT void php3_ms_map_prepareQuery(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    mapObj *self;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self != NULL)
      mapObj_prepareQuery(self);
    
}
/**********************************************************************
 *                        map->draw()
 **********************************************************************/

/* {{{ proto int map.draw()
   Render map and return handle on image object. */

DLEXPORT void php3_ms_map_draw(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    mapObj *self;
    imageObj *im = NULL;


#ifdef PHP4
    pval   **pExtent;
#else
    pval   *pExtent;
#endif

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL || (im = mapObj_draw(self)) == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        RETURN_FALSE;
    }
    else
    {
        /* Return an image object */
/* -------------------------------------------------------------------- */
/*      since the darwmap forces the scale and cellsize calculation,    */
/*      we also update the php object with the latest values.           */
/* -------------------------------------------------------------------- */
         _phpms_set_property_double(pThis,"cellsize", self->cellsize, 
                                    E_ERROR); 
         _phpms_set_property_double(pThis,"scale", self->scale, E_ERROR); 

#ifdef PHP4
         if (zend_hash_find(pThis->value.obj.properties, "extent", 
                            sizeof("extent"), (void **)&pExtent) == SUCCESS)
         {
             _phpms_set_property_double((*pExtent),"minx", 
                                        self->extent.minx, 
                                        E_ERROR);
             _phpms_set_property_double((*pExtent),"miny", 
                                        self->extent.miny, 
                                        E_ERROR);
             _phpms_set_property_double((*pExtent),"maxx", 
                                        self->extent.maxx, 
                                        E_ERROR);
             _phpms_set_property_double((*pExtent),"maxy", 
                                        self->extent.maxy, 
                                        E_ERROR);
         }
#else
         if (_php3_hash_find(pThis->value.ht, "extent", sizeof("extent"), 
                             (void **)&pExtent) == SUCCESS)
         {
             _phpms_set_property_double(pExtent,"minx", self->extent.minx, 
                                        E_ERROR);
             _phpms_set_property_double(pExtent,"miny", self->extent.miny, 
                                        E_ERROR);
             _phpms_set_property_double(pExtent,"maxx", self->extent.maxx, 
                                        E_ERROR);
             _phpms_set_property_double(pExtent,"maxy", self->extent.maxy, 
                                        E_ERROR);
         }
#endif
         
         _phpms_build_img_object(im, &(self->web), list, return_value);
    }
}
/* }}} */



/**********************************************************************
 *                        map->drawQuery()
 **********************************************************************/

/* {{{ proto int map.drawQuery()
   Renders a query map, returns an image.. */
DLEXPORT void php3_ms_map_drawQuery(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis;
    mapObj      *self;
    imageObj *im = NULL;


#ifdef PHP4
    pval   **pExtent;
#else
    pval   *pExtent;
#endif

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL || ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL || (im =  mapObj_drawQuery(self)) == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        RETURN_FALSE;
    }
    else
    {
/* -------------------------------------------------------------------- */
/*      since the darwmap forces the scale and cellsize calculation,    */
/*      we also update the php object with the latest values.           */
/* -------------------------------------------------------------------- */
         _phpms_set_property_double(pThis,"cellsize", self->cellsize, 
                                    E_ERROR); 
         _phpms_set_property_double(pThis,"scale", self->scale, E_ERROR); 

#ifdef PHP4
         if (zend_hash_find(pThis->value.obj.properties, "extent", 
                            sizeof("extent"), (void **)&pExtent) == SUCCESS)
         {
             _phpms_set_property_double((*pExtent),"minx", 
                                        self->extent.minx, 
                                        E_ERROR);
             _phpms_set_property_double((*pExtent),"miny", 
                                        self->extent.miny, 
                                        E_ERROR);
             _phpms_set_property_double((*pExtent),"maxx", 
                                        self->extent.maxx, 
                                        E_ERROR);
             _phpms_set_property_double((*pExtent),"maxy", 
                                        self->extent.maxy, 
                                        E_ERROR);
         }
#else
         if (_php3_hash_find(pThis->value.ht, "extent", sizeof("extent"), 
                             (void **)&pExtent) == SUCCESS)
         {
             _phpms_set_property_double(pExtent,"minx", self->extent.minx, 
                                        E_ERROR);
             _phpms_set_property_double(pExtent,"miny", self->extent.miny, 
                                        E_ERROR);
             _phpms_set_property_double(pExtent,"maxx", self->extent.maxx, 
                                        E_ERROR);
             _phpms_set_property_double(pExtent,"maxy", self->extent.maxy, 
                                        E_ERROR);
         }
#endif

        /* Return an image object */
         _phpms_build_img_object(im, &(self->web), list, return_value);
    }
}
     
/* }}} */

/**********************************************************************
 *                        map->drawLegend()
 **********************************************************************/

/* {{{ proto int map.drawLegend()
   Render legend and return handle on image object. */

DLEXPORT void php3_ms_map_drawLegend(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    mapObj *self;
    imageObj *im = NULL;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL || (im = mapObj_drawLegend(self)) == NULL)
        _phpms_report_mapserver_error(E_ERROR);

    /* Return an image object */
    _phpms_build_img_object(im, &(self->web), list, return_value);
}
/* }}} */

/**********************************************************************
 *                        map->drawReferenceMap()
 **********************************************************************/

/* {{{ proto int map.drawReferenceMap()
   Render reference map and return handle on image object. */

DLEXPORT void php3_ms_map_drawReferenceMap(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    mapObj *self;
    imageObj *im = NULL;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL || (im = mapObj_drawReferenceMap(self)) == NULL)
        _phpms_report_mapserver_error(E_ERROR);

    /* Return an image object */
    _phpms_build_img_object(im, &(self->web), list, return_value);
}
/* }}} */

/**********************************************************************
 *                        map->drawScaleBar()
 **********************************************************************/

/* {{{ proto int map.drawScaleBar()
   Render scale bar and return handle on image object. */

DLEXPORT void php3_ms_map_drawScaleBar(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    mapObj *self;
    imageObj *im = NULL;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL || (im = mapObj_drawScalebar(self)) == NULL)
        _phpms_report_mapserver_error(E_ERROR);

    /* Return an image object */
    _phpms_build_img_object(im, &(self->web), list, return_value);
}
/* }}} */

/**********************************************************************
 *                        map->embedScalebar()
 **********************************************************************/

/* {{{ proto int map.embedScalebar(image img)
   Renders the scalebar within the map. Returns -1 on error. */

DLEXPORT void php3_ms_map_embedScalebar(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *imgObj, *pThis;
    mapObj *self;
    imageObj *im = NULL;
    int    retVal=0;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &imgObj) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }
        
    im = (imageObj *)_phpms_fetch_handle(imgObj, 
                                         PHPMS_GLOBAL(le_msimg), list TSRMLS_CC);

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL || (retVal = mapObj_embedScalebar(self, im)) == -1)
        _phpms_report_mapserver_error(E_ERROR);

    RETURN_LONG(retVal);
}
/* }}} */

/**********************************************************************
 *                        map->embedLegend()
 **********************************************************************/

/* {{{ proto int map.embedLegend(image img)
   Renders the legend within the map. Returns -1 on error. */

DLEXPORT void php3_ms_map_embedLegend(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *imgObj, *pThis;
    mapObj *self;
    imageObj *im = NULL;
    int    retVal=0;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &imgObj) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }
        
    im = (imageObj *)_phpms_fetch_handle(imgObj, 
                                         PHPMS_GLOBAL(le_msimg), list TSRMLS_CC);

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL || (retVal = mapObj_embedLegend(self, im)) == -1)
        _phpms_report_mapserver_error(E_ERROR);

    RETURN_LONG(retVal);
}
/* }}} */


/**********************************************************************
 *                        map->drawLabelCache()
 **********************************************************************/

/* {{{ proto int map.drawLabelCache(image img)
   Renders the labels for a map. Returns -1 on error. */

DLEXPORT void php3_ms_map_drawLabelCache(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *imgObj, *pThis;
    mapObj *self;
    imageObj *im = NULL;
    int    retVal=0;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &imgObj) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }
        
    im = (imageObj *)_phpms_fetch_handle(imgObj, 
                                         PHPMS_GLOBAL(le_msimg), list TSRMLS_CC);

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL || (retVal = mapObj_drawLabelCache(self, im)) == -1)
        _phpms_report_mapserver_error(E_ERROR);

    RETURN_LONG(retVal);
}
/* }}} */


/**********************************************************************
 *                        map->getLayer()
 *
 * Note: Multiple calls to getlayer() will return multiple instances
 * of PHP objects pointing to the same layerObj... this is safe but is a
 * waste of resources.
 **********************************************************************/

/* {{{ proto int map.getLayer(int i)
   Returns a layerObj from the map given an index value (0=first layer, etc.) */

DLEXPORT void php3_ms_map_getLayer(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *pLyrIndex, *pThis;
    mapObj *self=NULL;
    layerObj *newLayer=NULL;
    int map_id;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pLyrIndex) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    /* pLyrIndex is the 0-based index of the requested layer */
    convert_to_long(pLyrIndex);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL || 
        (newLayer = mapObj_getLayer(self, pLyrIndex->value.lval)) == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    /* We will store a reference to the parent object id (this) inside
     * the layer obj.
     */
    map_id = _phpms_fetch_property_resource(pThis, "_handle_", E_ERROR);

    /* Return layer object */
    _phpms_build_layer_object(newLayer, map_id, list, return_value TSRMLS_CC);
}
/* }}} */

/**********************************************************************
 *                        map->getLayerByName()
 *
 * Note: Multiple calls to getlayer() will return multiple instances
 * of PHP objects pointing to the same layerObj... this is safe but is a
 * waste of resources.
 **********************************************************************/

/* {{{ proto int map.getLayerByName(string layer_name)
   Returns a layerObj from the map given a layer name */

DLEXPORT void php3_ms_map_getLayerByName(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *pLyrName, *pThis;
    mapObj *self=NULL;
    layerObj *newLayer=NULL;
    int map_id;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pLyrName) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pLyrName);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL ||
        (newLayer=mapObj_getLayerByName(self, pLyrName->value.str.val))==NULL )
    {
        // No MapServer error to report.  Just produce a PHP warning.
        php3_error(E_WARNING, "getLayerByName failed for : %s\n",
                   pLyrName->value.str.val);
        RETURN_FALSE;
    }

    /* We will store a reference to the parent object id (this) inside
     * the layer obj.
     */
    map_id = _phpms_fetch_property_resource(pThis, "_handle_", E_ERROR);

    /* Return layer object */
    _phpms_build_layer_object(newLayer, map_id, list, return_value TSRMLS_CC);
}
/* }}} */


/**********************************************************************
 *                        map->getLayersIndexByGroup()
 *
 * Return an array of layer's index given a group name.
 **********************************************************************/

/* {{{ proto int map.getLayersIndexByGroup(string groupname)
   Return an array of layer's index given a group name. */

DLEXPORT void php3_ms_map_getLayersIndexByGroup(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pGrpName, *pThis;
    mapObj      *self=NULL;
    int         *aiIndex = NULL;
    int         nCount = 0;
    int         i = 0;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pGrpName) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pGrpName);

    if (array_init(return_value) == FAILURE) 
    {
        RETURN_FALSE;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self != NULL)
    {
        aiIndex = 
            mapObj_getLayersIndexByGroup(self, pGrpName->value.str.val,
                                         &nCount);

        if (aiIndex && nCount > 0)
        {
            for (i=0; i<nCount; i++)
            {
                add_next_index_long(return_value, aiIndex[i]);
            }
            free (aiIndex);
        }
        else
            RETURN_FALSE; 
    }
    else
    {
        RETURN_FALSE;
    }
}
/* }}} */

/**********************************************************************
 *                        map->getAllLayerNames()
 *
 * Return an array conating all the layers name.
 **********************************************************************/

/* {{{ proto int map.getAllLayerNames()
   Return an array conating all the layers name.*/

DLEXPORT void php3_ms_map_getAllLayerNames(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis;
    mapObj      *self=NULL;
    int         nCount = 0;
    int         i = 0;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL)
    {
        WRONG_PARAM_COUNT;
    }

    if (array_init(return_value) == FAILURE) 
    {
        RETURN_FALSE;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self != NULL)
    {
        nCount = self->numlayers;
        for (i=0; i<nCount; i++)
        {
            add_next_index_string(return_value,  self->layers[i].name, 1);
        }
    }
    else
    {
        RETURN_FALSE;
    }
}
/* }}} */

/**********************************************************************
 *                        map->getAllGroupNames()
 *
 * Return an array containing all the group names
 **********************************************************************/

/* {{{ proto int map.getAllGroupNames()
   Return an array containing all the group names.*/

DLEXPORT void php3_ms_map_getAllGroupNames(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis;
    mapObj      *self=NULL;
    int         i = 0;
    char        **papszGroups = NULL;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL)
    {
        WRONG_PARAM_COUNT;
    }

    if (array_init(return_value) == FAILURE)
    {
        RETURN_FALSE;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self != NULL && self->numlayers > 0)
    {
       int numTok;
       papszGroups = msGetAllGroupNames(self, &numTok);
       
       for (i=0; i<numTok; i++)
       {
         /* add a copy of the group name to the PHP array */
          add_next_index_string(return_value, papszGroups[i], 1);
          
          free(papszGroups[i]);
       }
       free(papszGroups);
    }
    else
    {
        RETURN_FALSE;
    }
}
/* }}} */

/************************************************************************/
/*                         map->getColorByIndex                         */
/*                                                                      */
/*      Returns a color object (r,g,b values) using the color index     */
/*      given in argument.                                              */
/*      The color index corresponds to the index in the internal        */
/*      palette array used by the map to store the colors.              */
/************************************************************************/
/* {{{ proto int map.getColorByIndex(int nColorIndex)
   Returns a colorObj from the map given a color index */

DLEXPORT void php3_ms_map_getColorByIndex(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pColorIndex, *pThis;
    mapObj      *self=NULL;
    paletteObj  palette;
    colorObj    oColor;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pColorIndex) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pColorIndex);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self != NULL)
    {
        palette = self->palette;
        
        if (pColorIndex->value.lval < palette.numcolors)
        {
            oColor.red = palette.colors[(int)pColorIndex->value.lval].red;
            oColor.green = palette.colors[(int)pColorIndex->value.lval].green;
            oColor.blue = palette.colors[(int)pColorIndex->value.lval].blue;

        }
        else
        {
            _phpms_report_mapserver_error(E_WARNING);
            php3_error(E_ERROR, "getColorByIndex failed"
                       "Index shoud not be higher than %d\n",
                       palette.numcolors-1);
        }
    }
    else
    {
        RETURN_FALSE;
    }

    /* Return color object */
    _phpms_build_color_object(&oColor, list, return_value);
}
/* }}} */

/**********************************************************************
 *                        map->queryByPoint()
 *
 * Type is MS_SINGLE or MS_MULTIPLE depending on number of results
 * you want. Passing buffer <=0 defaults to tolerances set in the map 
 * file (in pixels) but you can use a constant buffer (specified in 
 * ground units) instead.
 **********************************************************************/

/* {{{ proto int map.queryByPoint(pointObj point, int type, double buffer)
   Query at point location. */

DLEXPORT void php3_ms_map_queryByPoint(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval   *pThis, *pPoint, *pType, *pBuffer;
    mapObj *self=NULL;
    pointObj *poPoint=NULL;
    int      nStatus = MS_FAILURE;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 3, &pPoint, &pType, &pBuffer) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pType);
    convert_to_double(pBuffer);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    poPoint = (pointObj *)_phpms_fetch_handle2(pPoint,
                                               PHPMS_GLOBAL(le_mspoint_ref),
                                               PHPMS_GLOBAL(le_mspoint_new),
                                               list TSRMLS_CC);

    if (self && poPoint && 
        (nStatus=mapObj_queryByPoint(self, poPoint, pType->value.lval, 
                                      pBuffer->value.dval)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }

    RETURN_LONG(nStatus);
}
/* }}} */


/************************************************************************/
/*                          map->queryByRect()                          */
/*                                                                      */
/*      Parmeters :                                                     */
/*                                                                      */
/*       rectObj : poRect : extents used to make the query.             */
/************************************************************************/


/* {{{ proto int map.queryByRect(rectObj poRect) */
 

DLEXPORT void php3_ms_map_queryByRect(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval   *pThis, *pRect;
    mapObj *self=NULL;
    rectObj *poRect=NULL;
    int      nStatus = MS_FAILURE;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif


    if (pThis == NULL ||
        getParameters(ht, 1, &pRect) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }


    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    poRect = (rectObj *)_phpms_fetch_handle2(pRect,
                                             PHPMS_GLOBAL(le_msrect_ref),
                                             PHPMS_GLOBAL(le_msrect_new),
                                             list TSRMLS_CC);

    if (self && poRect && 
        (nStatus=mapObj_queryByRect(self, *poRect)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }

    RETURN_LONG(nStatus);
}
/* }}} */


/**********************************************************************
 *                    map->queryByFeatures(int slayer)
 **********************************************************************/
DLEXPORT void php3_ms_map_queryByFeatures(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval   *pThis, *pSLayer;
    mapObj *self=NULL;
    int      nStatus = MS_FAILURE;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pSLayer) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pSLayer);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);

    if (self &&
        (nStatus=mapObj_queryByFeatures(self, 
                                        pSLayer->value.lval)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }

    RETURN_LONG(nStatus);
}

/**********************************************************************
 *                    map->queryByShape(shape)
 *
 * Generates a result set based on a single shape, the shape is
 * assumed to be a polygon at this point.
 **********************************************************************/

/* {{{ proto int map.queryByShape(shapeObj poShape) */
DLEXPORT void php3_ms_map_queryByShape(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis, *pShape;
    mapObj      *self=NULL;
    shapeObj    *poShape=NULL;
    int         nStatus = MS_FAILURE;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pShape) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }


    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);

    poShape = 
        (shapeObj *)_phpms_fetch_handle2(pShape, 
                                         PHPMS_GLOBAL(le_msshape_ref),
                                         PHPMS_GLOBAL(le_msshape_new),
                                         list TSRMLS_CC);
    
    if (self && poShape && 
        (nStatus = mapObj_queryByShape(self, poShape))!= MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }

    RETURN_LONG(nStatus);
}

 
/**********************************************************************
 *     map->queryByIndex(qlayer, tileindex, shapeindex, bAddtoQuery)
 *
 *
 * Add a shape into the query result on a specific layer.
 * if bAddtoQuery (not mandatory) isset to true, the sahpe will be added to 
 * the existing query result. Else the query result is cleared before adding 
 * the sahpe (which is the default behavior).
 **********************************************************************/
DLEXPORT void php3_ms_map_queryByIndex(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis, *pQlayer, *pTileIndex, *pShapeIndex, *pAddToQuery;
    mapObj      *self=NULL;
    int         nStatus = MS_FAILURE;
    int         bAddToQuery = -1;
    int         nArgs = ARG_COUNT(ht);

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        (nArgs != 3 && nArgs != 4))
    {
        WRONG_PARAM_COUNT;
    }

    if (pThis == NULL ||
        getParameters(ht, nArgs, &pQlayer, &pTileIndex, &pShapeIndex,
                      &pAddToQuery) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pQlayer);
    convert_to_long(pTileIndex);
    convert_to_long(pShapeIndex);
    
    if (nArgs == 4)
    {
      convert_to_long(pAddToQuery);
      bAddToQuery = pAddToQuery->value.lval;
    }


    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);

    
    if (self && 
        (nStatus = mapObj_queryByIndex(self, pQlayer->value.lval,
                                       pTileIndex->value.lval, 
                                       pShapeIndex->value.lval,
                                       bAddToQuery))!= MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }

    RETURN_LONG(nStatus);
}

 

/**********************************************************************
 *                    map->savequery(filename)
 *
 * Save the current query to a specfied file. Cal be used with loadquery
 **********************************************************************/

/* {{{ proto int map.savequery(filename) */
DLEXPORT void php3_ms_map_savequery(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis, *pFileName;
    mapObj      *self=NULL;
    int         nStatus = MS_FAILURE;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pFileName) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pFileName);
    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);

    
    nStatus = mapObj_saveQuery(self, pFileName->value.str.val);

    RETURN_LONG(nStatus);
}


/**********************************************************************
 *                    map->loadquery(filename)
 *
 * Load the query from a specfied file. Used with savequery
 **********************************************************************/

/* {{{ proto int map.loadquery(filename) */
DLEXPORT void php3_ms_map_loadquery(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis, *pFileName;
    mapObj      *self=NULL;
    int         nStatus = MS_FAILURE;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pFileName) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pFileName);
    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);

    
    nStatus = mapObj_loadQuery(self, pFileName->value.str.val);

    RETURN_LONG(nStatus);
}


/**********************************************************************
 *                    map->freequery(qlayer)
 *
 * Free the query on a specified layer. If qlayer is set to -1
 * all queries on all layers will be freed.
 **********************************************************************/

/* {{{ proto int map->freequery(qlayer) */
DLEXPORT void php3_ms_map_freequery(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis, *pQlayer;
    mapObj      *self=NULL;
    int         nStatus = MS_SUCCESS;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pQlayer) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pQlayer);
    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);

    
    mapObj_freeQuery(self, pQlayer->value.lval);

    RETURN_LONG(nStatus);
}

  
  
   
/**********************************************************************
 *                        map->save()
 **********************************************************************/

/* {{{ proto int map.save(string filename)
   Write map object to a file. */

DLEXPORT void php3_ms_map_save(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *pThis, *pFname;
    mapObj *self;
    int    retVal=0;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif


    if (pThis == NULL ||
        getParameters(ht, 1, &pFname) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pFname);

    self = (mapObj *)_phpms_fetch_handle(pThis, le_msmap, list TSRMLS_CC);
    if (self == NULL || 
        (retVal = mapObj_save(self, pFname->value.str.val)) != 0)
        _phpms_report_mapserver_error(E_ERROR);

    RETURN_LONG(retVal);
}
/* }}} */


/************************************************************************/
/*                    php3_ms_map_getLatLongExtent()                    */
/*                                                                      */
/*      Utility function (not documented) to get the lat/long           */
/*      extents of the current map. We assume here that the map has     */
/*      it's projection (ex LCC or UTM defined).                        */
/*                                                                      */
/*      Available only with PROJ support.                               */
/************************************************************************/
DLEXPORT void php3_ms_map_getLatLongExtent(INTERNAL_FUNCTION_PARAMETERS)
{ 
#ifdef USE_PROJ
    pval        *pThis;
    mapObj      *self=NULL;
    rectObj     oGeorefExt;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL)
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self != NULL)
    {
        oGeorefExt.minx = self->extent.minx;
        oGeorefExt.miny = self->extent.miny;
        oGeorefExt.maxx = self->extent.maxx;
        oGeorefExt.maxy = self->extent.maxy;
        
        if (self->projection.proj != NULL)
        {
            msProjectRect(&(self->projection), NULL, &oGeorefExt);
        }
        
    }
    /* Return rectObj */
    _phpms_build_rect_object(&oGeorefExt, PHPMS_GLOBAL(le_msrect_new), 
                             list, return_value);
#else
    php3_error(E_ERROR, 
               "getLatLongExtent() available only with PROJ.4 support.");
#endif
}

/**********************************************************************
 *                        map->getMetaData()
 **********************************************************************/

/* {{{ proto string map.getMetaData(string name)
   Return MetaData entry by name, or empty string if not found. */

DLEXPORT void php3_ms_map_getMetaData(INTERNAL_FUNCTION_PARAMETERS)
{
    mapObj *self;
    pval   *pThis, *pName;
    char   *pszValue = NULL;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pName) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pName);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap),
                                           list TSRMLS_CC);
    if (self == NULL || 
        (pszValue = mapObj_getMetaData(self, pName->value.str.val)) == NULL)
    {
        pszValue = "";
    }

    RETURN_STRING(pszValue, 1);
}
/* }}} */

/**********************************************************************
 *                        map->setMetaData()
 **********************************************************************/

/* {{{ proto int map.setMetaData(string name, string value)
   Set MetaData entry by name.  Returns MS_SUCCESS/MS_FAILURE */

DLEXPORT void php3_ms_map_setMetaData(INTERNAL_FUNCTION_PARAMETERS)
{
    mapObj *self;
    pval   *pThis, *pName, *pValue;
    int    nStatus = MS_FAILURE;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pName, &pValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pName);
    convert_to_string(pValue);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap),
                                           list TSRMLS_CC);
    if (self == NULL || 
        (nStatus = mapObj_setMetaData(self, 
                                      pName->value.str.val,  
                                      pValue->value.str.val)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    RETURN_LONG(nStatus);
}
/* }}} */



/**********************************************************************
 *                        map->removeMetaData()
 **********************************************************************/

/* {{{ proto int map.removeMetaData(string name)
   Remove MetaData entry using by name.  Returns MS_SUCCESS/MS_FAILURE */

DLEXPORT void php3_ms_map_removeMetaData(INTERNAL_FUNCTION_PARAMETERS)
{
    mapObj *self;
    pval   *pThis, *pName;
    int    nStatus = MS_FAILURE;
    HashTable   *list=NULL;
    pThis = getThis();

    if (pThis == NULL ||
        getParameters(ht, 1, &pName) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pName);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap),
                                           list TSRMLS_CC);
    if (self == NULL || 
        (nStatus = mapObj_removeMetaData(self, 
                                         pName->value.str.val)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    RETURN_LONG(nStatus);
}
/* }}} */


/**********************************************************************
 *                        map->movelayerup()
 *
 * Move layer up in the list of layers (for drawing purposes).
 * The layer in this case is drawn earlier.
 **********************************************************************/

/* {{{ proto int map.movelayerup(int layer_index)
   Returns true on sucess, else false. */

DLEXPORT void php3_ms_map_moveLayerUp(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *pLyrIdx, *pThis;
    mapObj *self=NULL;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pLyrIdx) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pLyrIdx);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self != NULL)
    {
        if (mapObj_moveLayerup(self, pLyrIdx->value.lval) == 0)
            RETURN_TRUE;       
    }

    RETURN_FALSE;
}
/* }}} */

/**********************************************************************
 *                        map->movelayerdown()
 *
 * Move layer down in the list of layers (for drawing purposes).
 * The layer in this case is drawn later.
 **********************************************************************/

/* {{{ proto int map.movelayerdown(int layer_index)
   Returns true on sucess, else false. */

DLEXPORT void php3_ms_map_moveLayerDown(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *pLyrIdx, *pThis;
    mapObj *self=NULL;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pLyrIdx) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pLyrIdx);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self != NULL)
    {
        if (mapObj_moveLayerdown(self, pLyrIdx->value.lval) == 0)
            RETURN_TRUE;       
    }

    RETURN_FALSE;
}
/* }}} */


/**********************************************************************
 *                        map->getLayersDrawingOrder()
 *
 * Return an array conating all the layers name.
 **********************************************************************/

/* {{{ proto int map.php3_ms_map_getLayersDrawingOrder()
   Return an array conating all the layers index sorted by drawing order.
   Note : the first element in the array is the one drawn first.*/
DLEXPORT void php3_ms_map_getLayersDrawingOrder(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis;
    mapObj      *self=NULL;
    int         nCount = 0;
    int         i = 0;
    int         *panLayers = NULL;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL)
    {
        WRONG_PARAM_COUNT;
    }

    if (array_init(return_value) == FAILURE) 
    {
        RETURN_FALSE;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    panLayers = mapObj_getLayersdrawingOrder(self);
    if (self != NULL)
    {
        nCount = self->numlayers;

/* -------------------------------------------------------------------- */
/*      Go through the prioriy list and return the layers index. If     */
/*      the priority list is not set, it will return the layer          */
/*      indexs as they were at the load time.                           */
/* -------------------------------------------------------------------- */
        for (i=0; i<nCount; i++)
        {
            if (panLayers)
            {
                add_next_index_long(return_value,  panLayers[i]);
            }
            else
                add_next_index_long(return_value, i);
        }
    }
    else
    {
        RETURN_FALSE;
    }
}

/**********************************************************************
 *                        map->setLayersDrawingOrder()
 *
 * Set the array used for the drawing order. 
 **********************************************************************/

/* {{{ proto int map.php3_ms_map_getLayersDrawingOrder(array_layer_index)
   array_layers_index : an array containing all the layer's index ordered
                        by the drawing priority.
                        Ex : for 3 layers in the map file, if 
                            array[0] = 2
                            array[1] = 0
                            array[2] = 1
                            will set the darwing order to layer 2, layer 0,
                            and then layer 1.
   Return TRUE on success or FALSE.
   Note : the first element in the array is the one drawn first.*/
DLEXPORT void php3_ms_map_setLayersDrawingOrder(INTERNAL_FUNCTION_PARAMETERS)
{
#ifdef PHP4
    pval        *pThis, *pArrayIndexes;
    mapObj      *self=NULL;
    int         nElements = 0;
    int         i = 0;

    int         *panIndexes = NULL;

#ifdef PHP4
    HashTable   *list=NULL;
    pval        **pValue = NULL;
#else
    pval        *pValue = NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL)
    {
        RETURN_FALSE;
    }


    if (ZEND_NUM_ARGS() != 1 || getParameters(ht,1,&pArrayIndexes)==FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }
    
        
    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), list TSRMLS_CC);
    if (self == NULL)
      RETURN_FALSE;

    if (pArrayIndexes->type != IS_ARRAY) 
    {
        php_error(E_WARNING, 
                  "setLayersDrawingOrder : expected array as parameter");
        RETURN_FALSE;
    }

    nElements = zend_hash_num_elements(pArrayIndexes->value.ht);

/* -------------------------------------------------------------------- */
/*      validate that the array of index given has the same size as     */
/*      the number of layers and also the the indexs are valid.         */
/* -------------------------------------------------------------------- */
    if (self->numlayers != nElements)
    {
        RETURN_FALSE;
    }
    panIndexes = (int *)malloc(sizeof(int)*nElements);
    for (i=0; i<nElements; i++)
    {
        if (zend_hash_index_find(pArrayIndexes->value.ht, i, 
                                 (void **)&pValue) == FAILURE)
        {
            RETURN_FALSE;
        }
        convert_to_long((*pValue));
        panIndexes[i] = (*pValue)->value.lval;
    }
    
    if (!mapObj_setLayersdrawingOrder(self, panIndexes))
    {
        free(panIndexes);
        RETURN_FALSE;
    }
    free(panIndexes);
#endif
    RETURN_TRUE;
}       



/**********************************************************************
 *                        map->processTemplate()
 *
 * Process a template  
 **********************************************************************/

/* {{{ proto int map.php3_ms_map_processTemplate(array_layer_index)*/

DLEXPORT void php3_ms_map_processTemplate(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis;
    pval        *pParamValue, *pGenerateImage;
    mapObj      *self=NULL;
    char        *pszBuffer = NULL;
    int         i, iIndice = 0;
    HashTable   *ar;
    int         numelems=0,  size;
    char        **papszNameValue = NULL;
    char        **papszName = NULL;
    char        **papszValue = NULL;

    HashTable   *list=NULL;

    pThis = getThis();

    if (pThis == NULL)
    {
        RETURN_FALSE;
    }

    if (ZEND_NUM_ARGS() != 2 || 
        getParameters(ht,2,&pParamValue, &pGenerateImage)==FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }
    
    convert_to_long(pGenerateImage);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL)
        RETURN_FALSE;

/* -------------------------------------------------------------------- */
/*      build the parm and value arrays.                                */
/*      Note : code extacted from sablot.c (functions related to        */
/*      xslt)                                                           */
/* -------------------------------------------------------------------- */
    ar = HASH_OF(pParamValue);
    if (ar)
    {
        /**
         * Allocate 2 times the number of elements in
         * the array, since with associative arrays in PHP
         * keys are not counted.
         */

        numelems = zend_hash_num_elements(ar);
        size = (numelems * 2 + 1) * sizeof(char *);
            
        papszNameValue = (char **)emalloc(size+1);
        memset((char *)papszNameValue, 0, size);
        
        /**
         * Translate a PHP array (HashTable *) into a 
         * Sablotron array (char **).
         */
        if (_php_extract_associative_array(ar, papszNameValue))
        {
            papszName = (char **)malloc(sizeof(char *)*numelems);
            papszValue = (char **)malloc(sizeof(char *)*numelems);
            
            
            for (i=0; i<numelems; i++)
            {
                iIndice = i*2;
                papszName[i] = papszNameValue[iIndice];
                papszValue[i] = papszNameValue[iIndice+1];
            }

        }
        else
        {
            // Failed for some reason
            php_error(E_WARNING, 
                      "processLegendTemplate: failed reading array");
            RETURN_FALSE;
        }
        efree(papszNameValue);
    }

    pszBuffer = mapObj_processTemplate(self, pGenerateImage->value.lval,
                                       papszName, papszValue, numelems);
            
    msFree(papszName);  // The strings inside the array are just refs
    msFree(papszValue);

    if (pszBuffer)
    {
        RETVAL_STRING(pszBuffer, 1);
        free(pszBuffer);
    }
    else
    {
        _phpms_report_mapserver_error(E_WARNING);
        RETURN_STRING("", 0);
    }

}

/**********************************************************************
 *                        map->processLegendTemplate()
 *
 * Process the legend template.
 **********************************************************************/

/* {{{ proto int map.php3_ms_map_processLegendTemplate(array_layer_index)*/

DLEXPORT void php3_ms_map_processLegendTemplate(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis;
    pval        *pParamValue;
    mapObj      *self=NULL;
    char        *pszBuffer = NULL;
    int         i, iIndice = 0;
    HashTable   *ar;
    int         numelems=0,  size;
    char        **papszNameValue = NULL;
    char        **papszName = NULL;
    char        **papszValue = NULL;

    
    HashTable   *list=NULL;


    pThis = getThis();

    if (pThis == NULL)
    {
        RETURN_FALSE;
    }

    if (ZEND_NUM_ARGS() != 1 || 
        getParameters(ht,1,&pParamValue)==FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }
    
    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL)
        RETURN_FALSE;

/* -------------------------------------------------------------------- */
/*      build the parm and value arrays.                                */
/*      Note : code extacted from sablot.c (functions related to        */
/*      xslt)                                                           */
/* -------------------------------------------------------------------- */
    ar = HASH_OF(pParamValue);
    if (ar)
    {
        /**
         * Allocate 2 times the number of elements in
         * the array, since with associative arrays in PHP
         * keys are not counted.
         */

        numelems = zend_hash_num_elements(ar);
        size = (numelems * 2 + 1) * sizeof(char *);
            
        papszNameValue = (char **)emalloc(size+1);
        memset((char *)papszNameValue, 0, size);
        
        /**
         * Translate a PHP array (HashTable *) into a 
         * Sablotron array (char **).
         */
        if (_php_extract_associative_array(ar, papszNameValue))
        {
            papszName = (char **)malloc(sizeof(char *)*numelems);
            papszValue = (char **)malloc(sizeof(char *)*numelems);

            for (i=0; i<numelems; i++)
            {
                iIndice = i*2;
                papszName[i] = papszNameValue[iIndice];
                papszValue[i] = papszNameValue[iIndice+1];
            }
        }
        else
        {
            // Failed for some reason
            php_error(E_WARNING, 
                      "processLegendTemplate: failed reading array");
            RETURN_FALSE;
        }
        efree(papszNameValue);
    }

    pszBuffer = mapObj_processLegendTemplate(self, papszName, 
                                             papszValue, numelems);

    msFree(papszName);  // The strings inside the array are just refs
    msFree(papszValue);

    if (pszBuffer)
    {
        RETVAL_STRING(pszBuffer, 1);
        free(pszBuffer);
    }
    else
    {
        _phpms_report_mapserver_error(E_WARNING);
        RETURN_STRING("", 0);
    }
}


/**********************************************************************
 *                        map->processQueryTemplate()
 *
 * Process a template  
 **********************************************************************/

/* {{{ proto int map.php3_ms_map_processQueryTemplate(array_layer_index)*/

DLEXPORT void php3_ms_map_processQueryTemplate(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis;
    pval        *pParamValue, *pGenerateImage;
    mapObj      *self=NULL;
    char        *pszBuffer = NULL;
    int         i, iIndice = 0;
    HashTable   *ar;
    int         numelems=0,  size;
    char        **papszNameValue = NULL;
    char        **papszName = NULL;
    char        **papszValue = NULL;
    int         nGenerateImage = 1;
    int         nArgs = ARG_COUNT(ht);
          

    HashTable   *list=NULL;

    pThis = getThis();

    if (pThis == NULL)
    {
        RETURN_FALSE;
    }

    if (pThis == NULL ||
        (nArgs != 1 && nArgs != 2))
    {
        WRONG_PARAM_COUNT;
    }

    if (getParameters(ht,nArgs,&pParamValue, &pGenerateImage)==FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }
    
    if (nArgs == 2)
    {
        convert_to_long(pGenerateImage);
        nGenerateImage = pGenerateImage->value.lval;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL)
        RETURN_FALSE;

/* -------------------------------------------------------------------- */
/*      build the parm and value arrays.                                */
/*      Note : code extacted from sablot.c (functions related to        */
/*      xslt)                                                           */
/* -------------------------------------------------------------------- */
    ar = HASH_OF(pParamValue);
    if (ar)
    {
        /**
         * Allocate 2 times the number of elements in
         * the array, since with associative arrays in PHP
         * keys are not counted.
         */

        numelems = zend_hash_num_elements(ar);
        size = (numelems * 2 + 1) * sizeof(char *);
            
        papszNameValue = (char **)emalloc(size+1);
        memset((char *)papszNameValue, 0, size);
        
        /**
         * Translate a PHP array (HashTable *) into a 
         * Sablotron array (char **).
         */
        if (_php_extract_associative_array(ar, papszNameValue))
        {
            papszName = (char **)malloc(sizeof(char *)*numelems);
            papszValue = (char **)malloc(sizeof(char *)*numelems);
            
            
            for (i=0; i<numelems; i++)
            {
                iIndice = i*2;
                papszName[i] = papszNameValue[iIndice];
                papszValue[i] = papszNameValue[iIndice+1];
            }

        }
        else
        {
            // Failed for some reason
            php_error(E_WARNING, 
                      "processLegendTemplate: failed reading array");
            RETURN_FALSE;
        }
        efree(papszNameValue);
    }
    pszBuffer = mapObj_processQueryTemplate(self, nGenerateImage,
                                            papszName, 
                                            papszValue, numelems);

    msFree(papszName);  // The strings inside the array are just refs
    msFree(papszValue);

    if (pszBuffer)
    {
        RETVAL_STRING(pszBuffer, 1);
        free(pszBuffer);
    }
    else
    {
        _phpms_report_mapserver_error(E_WARNING);
        RETURN_STRING("", 0);
    }


}

/**********************************************************************
 *                        map->setSymbolSet(szFileName)
 *
 * Load a symbol file.
 **********************************************************************/

/* {{{ proto int map.php3_ms_map_setSymbolSet(fileName)*/

DLEXPORT void php3_ms_map_setSymbolSet(INTERNAL_FUNCTION_PARAMETERS)
{
#ifdef PHP4
    pval        *pThis;
    pval        *pParamFileName;
    mapObj      *self=NULL;
    int         retVal=0;

#ifdef PHP4
    HashTable   *list=NULL;

#else
    pval        *pValue = NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL)
    {
        RETURN_FALSE;
    }

    if (getParameters(ht,1,&pParamFileName) == FAILURE)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pParamFileName);
   
    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL)
        RETURN_FALSE;

    if(pParamFileName->value.str.val != NULL && 
       strlen(pParamFileName->value.str.val) > 0)
    {
        if ((retVal = mapObj_setSymbolSet(self, 
                                          pParamFileName->value.str.val)) != 0)
        {
            _phpms_report_mapserver_error(E_WARNING);
            php3_error(E_ERROR, "Failed loading symbolset from %s",
                       pParamFileName->value.str.val);
        }
    }

    if (self->symbolset.filename)
        _phpms_set_property_string(pThis, "symbolsetfilename", 
                                   self->symbolset.filename?
                                       self->symbolset.filename:"", E_ERROR); 

    RETURN_LONG(retVal);
#endif
}

/**********************************************************************
 *                        map->getNumSymbols()
 **********************************************************************/

/* {{{ proto int layer.getNumSymbols()
   Returns the number of sumbols from this map. */

DLEXPORT void php3_ms_map_getNumSymbols(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *pThis;
    mapObj *self=NULL;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        ARG_COUNT(ht) > 0) 
    {
        WRONG_PARAM_COUNT;
    }

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), list TSRMLS_CC);
    if (self == NULL)
        RETURN_FALSE;
   
    RETURN_LONG(self->symbolset.numsymbols);
}
/* }}} */

/**********************************************************************
 *                        map->setFontSet(szFileName)
 *
 * Load a new fontset
 **********************************************************************/

/* {{{ proto int map.php3_ms_map_setFontSet(fileName)*/

DLEXPORT void php3_ms_map_setFontSet(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis;
    pval        *pParamFileName;
    mapObj      *self=NULL;
    int         retVal=0;

#ifdef PHP4
    HashTable   *list=NULL;

#else
    pval        *pValue = NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL)
    {
        RETURN_FALSE;
    }

    if (getParameters(ht,1,&pParamFileName) == FAILURE)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pParamFileName);
   
    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL)
        RETURN_FALSE;

    if(pParamFileName->value.str.val != NULL && 
       strlen(pParamFileName->value.str.val) > 0)
    {
        if ((retVal = mapObj_setFontSet(self, 
                                        pParamFileName->value.str.val)) != 0)
        {
            _phpms_report_mapserver_error(E_WARNING);
            php3_error(E_ERROR, "Failed loading fontset from %s",
                       pParamFileName->value.str.val);
        }
    }


    if (self->fontset.filename)
        _phpms_set_property_string(pThis, "fontsetfilename", 
                                   self->fontset.filename?
                                       self->fontset.filename:"", E_ERROR);

    RETURN_LONG(retVal);
}
/* }}} */

/**********************************************************************
 *                        map->saveMapContext(szFileName)
 *
 * Save mapfile under the Map Context format
 **********************************************************************/

/* {{{ proto int map.php3_ms_map_saveMapContext(fileName)*/

DLEXPORT void php3_ms_map_saveMapContext(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis;
    pval        *pParamFileName;
    mapObj      *self=NULL;
    int         retVal=0;

#ifdef PHP4
    HashTable   *list=NULL;

#else
    pval        *pValue = NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    if (getParameters(ht,1,&pParamFileName) == FAILURE)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pParamFileName);
   
    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    if(pParamFileName->value.str.val != NULL && 
       strlen(pParamFileName->value.str.val) > 0)
    {
        if ((retVal = mapObj_saveMapContext(self, 
                                pParamFileName->value.str.val)) != MS_SUCCESS)
        {
            _phpms_report_mapserver_error(E_WARNING);
            php3_error(E_WARNING, "Failed saving map context from %s",
                       pParamFileName->value.str.val);
            RETURN_LONG(MS_FAILURE);
        }
    }

    RETURN_LONG(retVal);
}
/* }}} */

/**********************************************************************
 *                        map->loadMapContext(szFileName)
 *
 * Save mapfile under the Map Context format
 **********************************************************************/

/* {{{ proto int map.php3_ms_map_loadMapContext(fileName)*/

DLEXPORT void php3_ms_map_loadMapContext(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis;
    pval        *pParamFileName;
    mapObj      *self=NULL;
    int         retVal=0;

#ifdef PHP4
    HashTable   *list=NULL;
    pval        **pExtent;
#else
    pval        *pValue = NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    if (getParameters(ht,1,&pParamFileName) == FAILURE)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pParamFileName);
   
    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    if(pParamFileName->value.str.val != NULL && 
       strlen(pParamFileName->value.str.val) > 0)
    {
        if ((retVal = mapObj_loadMapContext(self, 
                                 pParamFileName->value.str.val)) != MS_SUCCESS)
        {
            _phpms_report_mapserver_error(E_WARNING);
            php3_error(E_WARNING, "Failed loading map context from %s",
                       pParamFileName->value.str.val);
            RETURN_LONG(MS_FAILURE);
        }
    }

    /* read-only properties */
    _phpms_set_property_long(pThis, "numlayers", self->numlayers, E_ERROR);

    /* editable properties */
    if(self->name)
        _phpms_set_property_string(pThis, "name",      self->name, E_ERROR);
    _phpms_set_property_long(pThis,  "status",    self->status, E_ERROR);
    _phpms_set_property_long(pThis,  "width",     self->width, E_ERROR);
    _phpms_set_property_long(pThis,  "height",    self->height, E_ERROR);
    _phpms_set_property_long(pThis,  "transparent", self->transparent, E_ERROR);
    _phpms_set_property_long(pThis,  "interlace", self->interlace, E_ERROR);
    if(self->imagetype)
        _phpms_set_property_string(pThis,"imagetype", self->imagetype,E_ERROR);
    _phpms_set_property_long(pThis,"imagequality", self->imagequality, E_ERROR);

#ifdef PHP4
    if (zend_hash_find(pThis->value.obj.properties, "extent", sizeof("extent"), 
                       (void **)&pExtent) == SUCCESS)
    {
        _phpms_set_property_double((*pExtent),"minx", self->extent.minx, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"miny", self->extent.miny, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"maxx", self->extent.maxx, 
                                   E_ERROR);
        _phpms_set_property_double((*pExtent),"maxy", self->extent.maxy, 
                                   E_ERROR);
    }
#else
    /* Not supported for php3 */
#endif

    _phpms_set_property_double(pThis,"cellsize",  self->cellsize, E_ERROR);
    _phpms_set_property_long(pThis,  "units",     self->units, E_ERROR);
    _phpms_set_property_double(pThis,"scale",     self->scale, E_ERROR);
    _phpms_set_property_double(pThis,  "resolution",self->resolution, E_ERROR);
    if(self->shapepath)
        _phpms_set_property_string(pThis, "shapepath",self->shapepath,E_ERROR);


    RETURN_LONG(retVal);
}
/* }}} */


/**********************************************************************
 *                        map->selectoutputformat(type)
 *
 * Selects the output format (to be used in the map given) by giving
 * the type.
 **********************************************************************/
DLEXPORT void php3_ms_map_selectOutputFormat(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis;
    pval        *pImageType;
    mapObj      *self=NULL;
    HashTable   *list=NULL;
    int         nStatus = MS_SUCCESS;
    pval       **pOutputformat;

    pThis = getThis();

    if (pThis == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    if (getParameters(ht,1,&pImageType) == FAILURE)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pImageType);
   
    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    if ((nStatus = mapObj_selectOutputFormat(self, 
                                 pImageType->value.str.val)) != MS_SUCCESS)

    {
        php3_error(E_WARNING, "Unable to set output format to '%s'", 
                   pImageType->value.str.val);
    }
    else
    {
        if(self->imagetype)
          _phpms_set_property_string(pThis,"imagetype", self->imagetype,E_ERROR);
        
        if (zend_hash_find(pThis->value.obj.properties, "outputformat", 
                           sizeof("outputformat"), 
                           (void **)&pOutputformat) == SUCCESS)
        {
            _phpms_set_property_string((*pOutputformat),"name", 
                                       self->outputformat->name,
                                       E_ERROR);
            _phpms_set_property_string((*pOutputformat),"mimetype", 
                                       self->outputformat->mimetype,
                                        E_ERROR);
            _phpms_set_property_string((*pOutputformat),"driver", 
                                       self->outputformat->driver,
                                       E_ERROR);
            _phpms_set_property_string((*pOutputformat),"extension", 
                                       self->outputformat->extension,
                                       E_ERROR);
            _phpms_set_property_long((*pOutputformat),"renderer", 
                                     self->outputformat->renderer, E_ERROR); 
            _phpms_set_property_long((*pOutputformat),"imagemode", 
                                     self->outputformat->imagemode, E_ERROR);
            _phpms_set_property_long((*pOutputformat),"transparent", 
                                     self->outputformat->transparent, E_ERROR);
        }
    }

    RETURN_LONG(nStatus);
}

/**********************************************************************
 *                        map->applySLD(szSLDString)
 *
 * Apply an XML SLD string to the map file
 **********************************************************************/
DLEXPORT void php3_ms_map_applySLD(INTERNAL_FUNCTION_PARAMETERS)
{
     pval        *pThis;
     pval        *pSLDString;
     mapObj      *self=NULL;
      HashTable   *list=NULL;
     int         nStatus = MS_SUCCESS;

     pThis = getThis();

     if (pThis == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    if (getParameters(ht,1,&pSLDString) == FAILURE)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pSLDString);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    nStatus = mapObj_applySLD(self, pSLDString->value.str.val);

    RETURN_LONG(nStatus);
}


/**********************************************************************
 *                        map->applySLD(szSLDURL)
 *
 * Apply an SLD to map. The SLD is given as an URL.
 **********************************************************************/
DLEXPORT void php3_ms_map_applySLDURL(INTERNAL_FUNCTION_PARAMETERS)
{
     pval        *pThis;
     pval        *pSLDString;
     mapObj      *self=NULL;
     HashTable   *list=NULL;
     int         nStatus = MS_SUCCESS;

     pThis = getThis();

     if (pThis == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    if (getParameters(ht,1,&pSLDString) == FAILURE)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pSLDString);

    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    nStatus = mapObj_applySLDURL(self, pSLDString->value.str.val);

    RETURN_LONG(nStatus);
}


DLEXPORT void php3_ms_map_generateSLD(INTERNAL_FUNCTION_PARAMETERS)
{
     pval        *pThis;
     mapObj      *self=NULL;
     HashTable   *list=NULL;
     char       *pszBuffer = NULL;

     pThis = getThis();

     if (pThis == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }


    self = (mapObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msmap), 
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    pszBuffer = mapObj_generateSLD(self);

    if (pszBuffer)
    {
        RETVAL_STRING(pszBuffer, 1);
        free(pszBuffer);
    }
    else
    {
        _phpms_report_mapserver_error(E_WARNING);
        RETURN_STRING("", 0);
    }
}

/* }}} */



/*=====================================================================
 *                 PHP function wrappers - image class
 *====================================================================*/

/**********************************************************************
 *                     _phpms_build_img_object()
 **********************************************************************/
static long _phpms_build_img_object(imageObj *im, webObj *pweb,
                                    HashTable *list, pval *return_value)
{
    int img_id;

    if (im == NULL)
        return 0;

    img_id = php3_list_insert(im, PHPMS_GLOBAL(le_msimg));

    _phpms_object_init(return_value, img_id, php_img_class_functions,
                       PHP4_CLASS_ENTRY(img_class_entry_ptr));

    /* width/height params are read-only */
    add_property_long(return_value, "width", im->width);
    add_property_long(return_value, "height", im->height);
    
    PHPMS_ADD_PROP_STR(return_value, "imagepath", im->imagepath);
    PHPMS_ADD_PROP_STR(return_value, "imageurl", im->imageurl);
    

    PHPMS_ADD_PROP_STR(return_value, "imagetype", im->format->name);

/* php3_printf("Create image: id=%d, ptr=0x%x<P>\n", img_id, im);*/

    return img_id;
}

/**********************************************************************
 *                        image->saveImage()
 *
 *       saveImage(string filename)
 **********************************************************************/

/* {{{ proto int img.saveImage(string filename, int type, int transparent, int interlace, int quality)
   Writes image object to specifed filename.  If filename is empty then write to stdout.  Returns -1 on error. */

DLEXPORT void php3_ms_img_saveImage(INTERNAL_FUNCTION_PARAMETERS)
{
    pval   *pFname, *pThis;
    imageObj *im = NULL;
    int retVal = 0;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pFname) != SUCCESS  )
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pFname);

    im = (imageObj *)_phpms_fetch_handle(pThis, le_msimg, list TSRMLS_CC);

    if(pFname->value.str.val != NULL && strlen(pFname->value.str.val) > 0)
    {
        if (im == NULL ||
            (retVal = msSaveImage(NULL, im, pFname->value.str.val) != 0))
        {
          _phpms_report_mapserver_error(E_WARNING);
          php3_error(E_ERROR, "Failed writing image to %s", 
                     pFname->value.str.val);
        }
    }
    else
    {           /* no filename - stdout */
        int size=0;
#if !defined(USE_GD_GIF) || defined(GD_HAS_GDIMAGEGIFPTR)
        void *iptr=NULL;
#else
        int   b;
        FILE *tmp;
        char  buf[4096];
#endif

        retVal = 0;

#ifdef PHP4
        php_header();
#else
        php3_header();
#endif

        if( MS_DRIVER_GD(im->format) )
          //if ((strncasecmp((im->format)->driver,"gd/",3)==0))
        {
            if(strcasecmp("ON",
                          msGetOutputFormatOption(im->format, 
                                                  "INTERLACE", "ON" ))
                == 0 )
              gdImageInterlace(im->img.gd, 1);

            if(im->format->transparent)
              gdImageColorTransparent(im->img.gd, 0);
        }

        if(im->format->name && strcasecmp(im->format->name, "imagemap")==0){ 
            iptr = im->img.imagemap;
	    size = strlen(im->img.imagemap); //TODO
	} else
#if !defined(USE_GD_GIF) || defined(GD_HAS_GDIMAGEGIFPTR)

#ifdef USE_GD_GIF
        if(im->format->name && strcasecmp(im->format->driver, "gd/gif")==0)
            iptr = gdImageGifPtr(im->img.gd, &size); //TODO
        else
#endif
#ifdef USE_GD_PNG
        if(im->format->name && strcasecmp(im->format->driver, "gd/png")==0) 
            iptr = gdImagePngPtr(im->img.gd, &size); //TODO
        else
#endif
#ifdef USE_GD_JPEG
        if(im->format->name && strcasecmp(im->format->driver, "gd/jpeg")==0) 
            iptr = 
              gdImageJpegPtr(im->img.gd, &size, 
                             atoi(msGetOutputFormatOption(im->format, "QUALITY",
                                                           "75" )));
        else
#endif
#ifdef USE_GD_WBMP
          if(im->format->name && strcasecmp(im->format->driver, "gd/wbmp")==0)
            iptr = gdImageWBMPPtr(im->img.gd, &size, 1); //TODO
        else
#endif
        {
            php3_error(E_ERROR, 
                       "Output to '%s' not available via this method.", 
                       im->format->name);
        }
        if (size == 0) {
            _phpms_report_mapserver_error(E_WARNING);
            php3_error(E_ERROR, "Failed writing image to stdout");
            retVal = -1;
        } 
        else
        {
#ifdef PHP4
            php_write(iptr, size TSRMLS_CC);
#else
            php3_write(iptr, size);
#endif
            retVal = size;
            free(iptr);
        }

#else  /* No gdImageGifPtr(): GD 1.2/1.3 */

        /* there is no gdImageGifPtr function */

        tmp = tmpfile(); /* temporary file */
        if (tmp == NULL) 
        {
            php3_error(E_WARNING, "Unable to open temporary file");
            retVal = -1;
        } 
        else
        {
            gdImageGif (im->img.gd, tmp); //TODO
            size = ftell(tmp);
            fseek(tmp, 0, SEEK_SET);

#if APACHE && defined(CHARSET_EBCDIC)
            /* This is a binary file already: avoid EBCDIC->ASCII conversion */
            ap_bsetflag(php3_rqst->connection->client, B_EBCDIC2ASCII, 0);
#endif

            while ((b = fread(buf, 1, sizeof(buf), tmp)) > 0) 
            {
#ifdef PHP4
                php_write(buf, b TSRMLS_CC);
#else
                php3_write(buf, b);
#endif
            }

            fclose(tmp); /* the temporary file is automatically deleted */
            retVal = size;
        }
#endif

    }

    RETURN_LONG(retVal);
}
/* }}} */


/**********************************************************************
 *                        image->saveWebImage()
 *       saveWebImage()
 **********************************************************************/

/* {{{ proto int img.saveWebImage(int type, int transparent, int interlace, int quality)
   Writes image to temp directory.  Returns image URL. */

DLEXPORT void php3_ms_img_saveWebImage(INTERNAL_FUNCTION_PARAMETERS)
{
    pval   *pThis;

    imageObj *im = NULL;

    char *pImagepath, *pImageurl, *pBuf;
    int nBufSize, nLen1, nLen2, nTmpCount;
    const char *pszImageExt;

    HashTable   *list=NULL;
    pThis = getThis();

    if (pThis == NULL)
    {
        WRONG_PARAM_COUNT;
    }

    im = (imageObj *)_phpms_fetch_handle(pThis, le_msimg, list TSRMLS_CC);
    pImagepath = _phpms_fetch_property_string(pThis, "imagepath", E_ERROR);
    pImageurl = _phpms_fetch_property_string(pThis, "imageurl", E_ERROR);

    pszImageExt = im->format->extension;

    /* Build a unique filename in the IMAGEPATH directory 
     */
    nLen1 = strlen(pImagepath);
    nLen2 = strlen(pImageurl);
    nBufSize = (nLen1>nLen2 ? nLen1:nLen2) + strlen(PHPMS_G(tmpId)) + 30;
    pBuf = (char*)emalloc(nBufSize);
    nTmpCount = ++(PHPMS_G(tmpCount));
    sprintf(pBuf, "%s%s%d.%s", 
            pImagepath, PHPMS_G(tmpId), nTmpCount, pszImageExt);


    /* Save the image... 
     */
    if (im == NULL || 
        msSaveImage(NULL, im, pBuf) != 0 )
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "Failed writing image to %s", 
                   pBuf);
    }

    /* ... and return the corresponding URL
     */
    sprintf(pBuf, "%s%s%d.%s", 
            pImageurl, PHPMS_G(tmpId), nTmpCount, pszImageExt);
    RETURN_STRING(pBuf, 0);
}
/* }}} */


/**********************************************************************
 *                        image->pasteImage()
 **********************************************************************/

/* {{{ proto void img.pasteImage(imageObj Src, int transparentColor [[,int dstx, int dsty], int angle])
   Pastes another imageObj on top of this imageObj. transparentColor is
   the color (0xrrggbb) from srcImg that should be considered transparent.
   Pass transparentColor=-1 if you don't want any transparent color.
   If optional dstx,dsty are provided then they define the position where the
   image should be copied (dstx,dsty = top-left corner position).
   The optional angle is a value between 0 and 360 degrees to rotate the
   source image counterclockwise.  Note that if a rotation is requested then
   the dstx and dsty coordinates specify the CENTER of the destination area.
   NOTE : this function only works for 8 bits GD images.
*/

DLEXPORT void php3_ms_img_pasteImage(INTERNAL_FUNCTION_PARAMETERS)
{
    pval   *pSrcImg, *pTransparent, *pThis, *pDstX, *pDstY, *pAngle;
    imageObj *imgDst = NULL, *imgSrc = NULL;
    int         nDstX=0, nDstY=0, nAngle=0, bAngleSet=MS_FALSE;
    int         nArgs = ARG_COUNT(ht);
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        (nArgs != 2 && nArgs != 4 && nArgs != 5))
    {
        WRONG_PARAM_COUNT;
    }
    if (pThis == NULL ||
        getParameters(ht, nArgs, &pSrcImg, &pTransparent, 
                      &pDstX, &pDstY, &pAngle) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    imgDst = (imageObj *)_phpms_fetch_handle(pThis, le_msimg, list TSRMLS_CC);

    imgSrc = (imageObj *)_phpms_fetch_handle(pSrcImg, PHPMS_GLOBAL(le_msimg), 
                                             list TSRMLS_CC);
    
    if( !MS_DRIVER_GD(imgSrc->format) || !MS_DRIVER_GD(imgDst->format))
    {
        php3_error(E_ERROR, "PasteImage function should only be used with GD images.");
        RETURN_LONG(-1);
    }
      
    convert_to_long(pTransparent);

    if (nArgs >= 4)
    {
        convert_to_long(pDstX);
        convert_to_long(pDstY);
        nDstX = pDstX->value.lval;
        nDstY = pDstY->value.lval;
    }

    if (nArgs == 5)
    {
        convert_to_long(pAngle);
        nAngle = pAngle->value.lval;
        bAngleSet = MS_TRUE;
    }

    if (imgSrc != NULL && imgDst != NULL)
    {
        int    nOldTransparentColor, nNewTransparentColor=-1, nR, nG, nB;

        /* Look for r,g,b in color table and make it transparent.
         * will return -1 if there is no exact match which will result in
         * no transparent color in the call to gdImageColorTransparent().
         */
        if (pTransparent->value.lval != -1)
        {
            nR = (pTransparent->value.lval / 0x010000) & 0xff;
            nG = (pTransparent->value.lval / 0x0100) & 0xff;
            nB = pTransparent->value.lval & 0xff;
            nNewTransparentColor = gdImageColorExact(imgSrc->img.gd, nR,nG,nB);
        }

        nOldTransparentColor = gdImageGetTransparent(imgSrc->img.gd);
        gdImageColorTransparent(imgSrc->img.gd, nNewTransparentColor);

        if (!bAngleSet)
            gdImageCopy(imgDst->img.gd, imgSrc->img.gd, nDstX, nDstY, 
                        0, 0, imgSrc->img.gd->sx, imgSrc->img.gd->sy);
        else
            gdImageCopyRotated(imgDst->img.gd, imgSrc->img.gd, nDstX, nDstY, 
                               0, 0, imgSrc->img.gd->sx, imgSrc->img.gd->sy,
                               nAngle);

        gdImageColorTransparent(imgSrc->img.gd, nOldTransparentColor);
    }
    else
    {
        php3_error(E_ERROR, "Source or destination image is invalid.");
    }

    RETURN_LONG(0);
}
/* }}} */



/**********************************************************************
 *                        image->free()
 **********************************************************************/

/* {{{ proto int img.free()
   Destroys resources used by an image object */

DLEXPORT void php3_ms_img_free(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    imageObj *self;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif


    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (imageObj*)_phpms_fetch_handle(pThis, le_msimg, list TSRMLS_CC);
    if (self)
    {
        /* Note: we do not have to call the object destructor...
         * removing the object from the resource list using php3_list_delete()
         * will also call the object destructor through the list destructor.
         */
#ifdef PHP4
        pval **phandle;
        if (zend_hash_find(pThis->value.obj.properties, "_handle_", 
                           sizeof("_handle_"), 
                           (void **)&phandle) == SUCCESS)
        {
            php3_list_delete((*phandle)->value.lval);
        }
#else
        pval *phandle;
        if (_php3_hash_find(pThis->value.ht, "_handle_", sizeof("_handle_"), 
                            (void **)&phandle) == SUCCESS)

        {
            php3_list_delete(phandle->value.lval);
        }
#endif
    }

}
/* }}} */


/*=====================================================================
 *                 PHP function wrappers - layerObj class
 *====================================================================*/

/**********************************************************************
 *                     _phpms_build_layer_object()
 **********************************************************************/
static long _phpms_build_layer_object(layerObj *player, int parent_map_id,
                                      HashTable *list, pval *return_value TSRMLS_DC)
{
    int         layer_id;
    pval        *new_obj_ptr;

    if (player == NULL)
    {
        return 0;
    }

    layer_id = php3_list_insert(player, PHPMS_GLOBAL(le_mslayer));

    _phpms_object_init(return_value, layer_id, php_layer_class_functions,
                       PHP4_CLASS_ENTRY(layer_class_entry_ptr));

#ifdef PHP4
    zend_list_addref(parent_map_id);
    add_property_resource(return_value, "_map_handle_", parent_map_id);
#else
    add_property_long(return_value, "_map_handle_", parent_map_id);
#endif

    /* read-only properties */
    add_property_long(return_value,   "numclasses", player->numclasses);
    add_property_long(return_value,   "index",      player->index);

    /* editable properties */
    add_property_long(return_value,   "status",     player->status);
    add_property_long(return_value,   "debug",      player->debug);
    PHPMS_ADD_PROP_STR(return_value,  "classitem",  player->classitem);
    PHPMS_ADD_PROP_STR(return_value,  "name",       player->name);
    PHPMS_ADD_PROP_STR(return_value,  "group",      player->group);
    PHPMS_ADD_PROP_STR(return_value,  "data",       player->data);
    add_property_long(return_value,   "type",       player->type);
    add_property_long(return_value,   "dump",       player->dump);
    add_property_double(return_value, "tolerance",  player->tolerance);
    add_property_long(return_value,   "toleranceunits",player->toleranceunits);
    add_property_double(return_value, "symbolscale",player->symbolscale);
    add_property_double(return_value, "minscale",   player->minscale);
    add_property_double(return_value, "maxscale",   player->maxscale);
    add_property_double(return_value, "labelminscale",player->labelminscale);
    add_property_double(return_value, "labelmaxscale",player->labelmaxscale);
    add_property_long(return_value,   "maxfeatures",player->maxfeatures);
    add_property_long(return_value,   "transform",  player->transform);
    add_property_long(return_value,   "labelcache", player->labelcache);
    add_property_long(return_value,   "postlabelcache",player->postlabelcache);
    PHPMS_ADD_PROP_STR(return_value,  "labelitem",  player->labelitem);
    PHPMS_ADD_PROP_STR(return_value,  "labelsizeitem",player->labelsizeitem);
    PHPMS_ADD_PROP_STR(return_value,  "labelangleitem",player->labelangleitem);
    PHPMS_ADD_PROP_STR(return_value,  "tileitem",   player->tileitem);
    PHPMS_ADD_PROP_STR(return_value,  "tileindex",  player->tileindex);
    PHPMS_ADD_PROP_STR(return_value,  "header",     player->header);
    PHPMS_ADD_PROP_STR(return_value,  "footer",     player->footer);
    PHPMS_ADD_PROP_STR(return_value,  "connection", player->connection);
    add_property_long(return_value,   "connectiontype",player->connectiontype);
    PHPMS_ADD_PROP_STR(return_value,  "filteritem", player->filteritem);
    PHPMS_ADD_PROP_STR(return_value,  "template",   player->template);
    add_property_long(return_value,   "transparency",player->transparency);
    PHPMS_ADD_PROP_STR(return_value,  "styleitem",  player->styleitem);
    add_property_long(return_value,   "num_processing",player->numprocessing);
    
    MAKE_STD_ZVAL(new_obj_ptr);
    _phpms_build_color_object(&(player->offsite),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "offsite", new_obj_ptr, E_ERROR);

    if (player->connectiontype == MS_GRATICULE && 
        player->layerinfo != NULL)
    {
        MAKE_STD_ZVAL(new_obj_ptr);
         _phpms_build_grid_object((graticuleObj *)(player->layerinfo),
                                  layer_id,
                                  list, new_obj_ptr TSRMLS_CC);
         _phpms_add_property_object(return_value, "grid", new_obj_ptr, E_ERROR);

    }
    return layer_id;
}


/**********************************************************************
 *                        ms_newLayerObj()
 **********************************************************************/

/* {{{ proto layerObj ms_newLayerObj(mapObj map)
   Create a new layer in the specified map. */

DLEXPORT void php3_ms_lyr_new(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pMapObj, *pSrcLayer;
    mapObj      *parent_map;
    layerObj    *pNewLayer;
    layerObj    *poSrcLayer = NULL;
    int         map_id;
    int         nArgs;
    int         nOrigIndex = 0;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

    nArgs = ARG_COUNT(ht);
    if ((nArgs != 1 && nArgs != 2) ||
        getParameters(ht, nArgs, &pMapObj, &pSrcLayer) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    parent_map = (mapObj*)_phpms_fetch_handle(pMapObj, 
                                              PHPMS_GLOBAL(le_msmap),
                                              list TSRMLS_CC);

    if (nArgs == 2)
    {
        poSrcLayer = (layerObj *)_phpms_fetch_handle(pSrcLayer, 
                                                     PHPMS_GLOBAL(le_mslayer),
                                                     list TSRMLS_CC);
    }
        
    if (parent_map == NULL ||
        (pNewLayer = layerObj_new(parent_map)) == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
        RETURN_FALSE;
    }
    /* if a layer is passed as argument, copy the layer into
       the new one */
    if (poSrcLayer)
    {
        nOrigIndex = pNewLayer->index;
        msCopyLayer(pNewLayer, poSrcLayer);
        pNewLayer->index = nOrigIndex;
    }

    /* Update mapObj members */
    _phpms_set_property_long(pMapObj, "numlayers",
                             parent_map->numlayers, E_ERROR); 

    /* We will store a reference to the parent_map object id inside
     * the layer obj.
     */
    map_id = _phpms_fetch_property_resource(pMapObj, "_handle_", E_ERROR);

    /* Return layer object */
    _phpms_build_layer_object(pNewLayer, map_id, list, return_value TSRMLS_CC);
}
/* }}} */


/**********************************************************************
 *                        layer->set()
 **********************************************************************/

/* {{{ proto int layer.set(string property_name, new_value)
   Set layer object property to new value. Returns -1 on error. */

DLEXPORT void php3_ms_lyr_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    layerObj *self;
    pval   *pPropertyName, *pNewValue, *pThis;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (layerObj *)_phpms_fetch_handle(pThis, le_mslayer, list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    IF_SET_LONG(       "status",     self->status)
    else IF_SET_LONG(  "debug",      self->debug)
    else IF_SET_STRING("classitem",  self->classitem)
    else IF_SET_STRING("name",       self->name)
    else IF_SET_STRING("group",      self->group)
    else IF_SET_STRING("data",       self->data)
    else IF_SET_LONG(  "type",       self->type)
    else IF_SET_LONG(  "dump",       self->dump)
    else IF_SET_DOUBLE("tolerance",  self->tolerance)
    else IF_SET_LONG(  "toleranceunits",self->toleranceunits)
    else IF_SET_DOUBLE("symbolscale",self->symbolscale)
    else IF_SET_DOUBLE("minscale",   self->minscale)
    else IF_SET_DOUBLE("maxscale",   self->maxscale)
    else IF_SET_DOUBLE("labelminscale",self->labelminscale)
    else IF_SET_DOUBLE("labelmaxscale",self->labelmaxscale)
    else IF_SET_LONG(  "maxfeatures",self->maxfeatures)
    else IF_SET_LONG(  "transform",  self->transform)
    else IF_SET_LONG(  "labelcache", self->labelcache)
    else IF_SET_LONG(  "postlabelcache", self->postlabelcache)
    else IF_SET_STRING("labelitem",  self->labelitem)
    else IF_SET_STRING("labelsizeitem",self->labelsizeitem)
    else IF_SET_STRING("labelangleitem",self->labelangleitem)
    else IF_SET_STRING("tileitem",   self->tileitem)
    else IF_SET_STRING("tileindex",  self->tileindex)
    else IF_SET_STRING("header",     self->header)
    else IF_SET_STRING("footer",     self->footer)
    else IF_SET_STRING("connection", self->connection)
    else IF_SET_LONG(  "connectiontype", self->connectiontype)
    else IF_SET_STRING("filteritem", self->filteritem)
    else IF_SET_STRING("template",   self->template)
    else IF_SET_LONG(  "transparency", self->transparency)
    else IF_SET_STRING("styleitem",  self->styleitem)
    else if (strcmp( "numclasses", pPropertyName->value.str.val) == 0 ||
             strcmp( "index",      pPropertyName->value.str.val) == 0 )
    {
        php3_error(E_ERROR,"Property '%s' is read-only and cannot be set.", 
                            pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }
    else
    {
        php3_error(E_ERROR,"Property '%s' does not exist in this object.", 
                            pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }

    RETURN_LONG(0);
}
/* }}} */

/**********************************************************************
 *                        layer->draw()
 **********************************************************************/

/* {{{ proto int layer.draw(image img)
   Draw a single layer, add labels to cache if required. Returns -1 on error. */

DLEXPORT void php3_ms_lyr_draw(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *imgObj, *pThis;
    mapObj *parent_map;
    layerObj *self;
    imageObj *im = NULL;
    int    retVal=0;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif


    if (pThis == NULL ||
        getParameters(ht, 1, &imgObj) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    im = (imageObj *)_phpms_fetch_handle(imgObj, 
                                         PHPMS_GLOBAL(le_msimg), list TSRMLS_CC);
   
    self = (layerObj *)_phpms_fetch_handle(pThis, 
                                           PHPMS_GLOBAL(le_mslayer),list TSRMLS_CC);
    parent_map = (mapObj*)_phpms_fetch_property_handle(pThis, "_map_handle_", 
                                                       PHPMS_GLOBAL(le_msmap),
                                                       list TSRMLS_CC, E_ERROR);

    if (im == NULL || self == NULL || parent_map == NULL ||
        (retVal = layerObj_draw(self, parent_map, im)) == -1)
        _phpms_report_mapserver_error(E_WARNING);

    RETURN_LONG(retVal);
}
/* }}} */

/**********************************************************************
 *                        layer->drawQuery()
 **********************************************************************/

/* {{{ proto int layer.drawQuery(image img)
   Draw query results for a layer. */

DLEXPORT void php3_ms_lyr_drawQuery(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *imgObj, *pThis;
    mapObj *parent_map;
    layerObj *self;
    imageObj *im = NULL;
    int    retVal=0;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &imgObj) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    im = (imageObj *)_phpms_fetch_handle(imgObj, 
                                         PHPMS_GLOBAL(le_msimg), list TSRMLS_CC);
   
    self = (layerObj *)_phpms_fetch_handle(pThis, 
                                           PHPMS_GLOBAL(le_mslayer),list TSRMLS_CC);
    parent_map = (mapObj*)_phpms_fetch_property_handle(pThis, "_map_handle_", 
                                                       PHPMS_GLOBAL(le_msmap),
                                                       list TSRMLS_CC, E_ERROR);

    if (im == NULL || self == NULL || parent_map == NULL ||
        (retVal = layerObj_drawQuery(self, parent_map, im)) == -1)
        _phpms_report_mapserver_error(E_WARNING);

    RETURN_LONG(retVal);
}
/* }}} */


/**********************************************************************
 *                        layer->getClass()
 *
 * Note: Multiple calls to getClass() will return multiple instances
 * of PHP objects pointing to the same classObj... this is safe but is a
 * waste of resources.
 **********************************************************************/

/* {{{ proto int layer.getClass(int i)
   Returns a classObj from the layer given an index value (0=first class) */

DLEXPORT void php3_ms_lyr_getClass(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *pClassIndex, *pThis;
    layerObj *self=NULL;
    classObj *newClass=NULL;
    int layer_id, map_id;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pClassIndex) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    /* pClassIndex is the 0-based index of the requested class */
    convert_to_long(pClassIndex);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    if (self == NULL || 
        (newClass = layerObj_getClass(self, pClassIndex->value.lval)) == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    /* We will store a reference to the parent object id (this) inside
     * the class obj.
     */
    layer_id = _phpms_fetch_property_resource(pThis, "_handle_", E_ERROR);

    /* We will store a reference to the map parent object id (this) inside
     * the class obj.
     */
    map_id = _phpms_fetch_property_resource(pThis, "_map_handle_", E_ERROR);

    /* Return layer object */
    _phpms_build_class_object(newClass, map_id, layer_id, list, 
                              return_value TSRMLS_CC);
}
/* }}} */


/**********************************************************************
 *                        layer->queryByAttributes()
 *
 * Mode is MS_SINGLE or MS_MULTIPLE depending on number of results
 * you want. 
 **********************************************************************/

/* {{{ proto int layer.queryAttributes(int mode)
   Query at point location. */

DLEXPORT void php3_ms_lyr_queryByAttributes(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval   *pThis, *pType, *pQItem, *pQString;
    layerObj *self=NULL;
    mapObj   *parent_map;
    int      nStatus = MS_FAILURE;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 3, &pQItem, &pQString, &pType) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pType);
    convert_to_string(pQItem);
    convert_to_string(pQString);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    parent_map = (mapObj*)_phpms_fetch_property_handle(pThis, "_map_handle_", 
                                                       PHPMS_GLOBAL(le_msmap),
                                                       list TSRMLS_CC,E_ERROR);

    if (self && parent_map &&
        (nStatus=layerObj_queryByAttributes(self, parent_map,
                                            pQItem->value.str.val,
                                            pQString->value.str.val,
                                            pType->value.lval)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }

    RETURN_LONG(nStatus);
}
/* }}} */

/**********************************************************************
 *                        layer->queryByPoint()
 *
 * Type is MS_SINGLE or MS_MULTIPLE depending on number of results
 * you want. Passing buffer <=0 defaults to tolerances set in the map 
 * file (in pixels) but you can use a constant buffer (specified in 
 * ground units) instead.
 **********************************************************************/

/* {{{ proto int layer.queryByPoint(pointObj point, int type, double buffer)
   Query at point location. */

DLEXPORT void php3_ms_lyr_queryByPoint(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval   *pThis, *pPoint, *pType, *pBuffer;
    layerObj *self=NULL;
    mapObj   *parent_map;
    pointObj *poPoint=NULL;
    int      nStatus = MS_FAILURE;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 3, &pPoint, &pType, &pBuffer) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pType);
    convert_to_double(pBuffer);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    poPoint = (pointObj *)_phpms_fetch_handle2(pPoint,
                                               PHPMS_GLOBAL(le_mspoint_ref),
                                               PHPMS_GLOBAL(le_mspoint_new),
                                               list TSRMLS_CC);
    parent_map = (mapObj*)_phpms_fetch_property_handle(pThis, "_map_handle_", 
                                                       PHPMS_GLOBAL(le_msmap),
                                                       list TSRMLS_CC, E_ERROR);

    if (self && poPoint && parent_map &&
        (nStatus=layerObj_queryByPoint(self, parent_map, poPoint, 
                                       pType->value.lval, 
                                       pBuffer->value.dval)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }

    RETURN_LONG(nStatus);
}
/* }}} */

/************************************************************************/
/*                         layer->queryByRect()                         */
/*                                                                      */
/*      Query on a layer using rectangular extents.                     */
/************************************************************************/

/* {{{ proto int layer.queryByRect(rectObj poRect)
   Query using rectangular extent. */

DLEXPORT void php3_ms_lyr_queryByRect(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval   *pThis, *pRect;
    layerObj *self=NULL;
    mapObj   *parent_map;
    rectObj *poRect=NULL;
    int      nStatus = MS_FAILURE;
    
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pRect) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    poRect = (rectObj *)_phpms_fetch_handle2(pRect,
                                             PHPMS_GLOBAL(le_msrect_ref),
                                             PHPMS_GLOBAL(le_msrect_new),
                                             list TSRMLS_CC);
    parent_map = (mapObj*)_phpms_fetch_property_handle(pThis, "_map_handle_", 
                                                       PHPMS_GLOBAL(le_msmap),
                                                       list TSRMLS_CC, E_ERROR);

    if (self && poRect && parent_map &&
        (nStatus=layerObj_queryByRect(self, parent_map, 
                                      *poRect)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }

    RETURN_LONG(nStatus);
}
/* }}} */

/************************************************************************/
/*                       layer->queryByFeatures()                       */
/*                                                                      */
/*      Query on a layer using query object.                            */
/************************************************************************/
DLEXPORT void php3_ms_lyr_queryByFeatures(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval   *pThis, *pSLayer;
    layerObj *self=NULL;
    mapObj   *parent_map;
    int      nStatus = MS_FAILURE;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pSLayer) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pSLayer);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    parent_map = (mapObj*)_phpms_fetch_property_handle(pThis, "_map_handle_", 
                                                       PHPMS_GLOBAL(le_msmap),
                                                       list TSRMLS_CC, E_ERROR);

    if (self && parent_map &&
        (nStatus=layerObj_queryByFeatures(self, parent_map, 
                                          pSLayer->value.lval)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }

    RETURN_LONG(nStatus);
}
/* }}} */

/************************************************************************/
/*                        layer->queryByShape()                         */
/*                                                                      */
/*      Query on a layer using a shape object.                          */
/************************************************************************/

/* {{{ proto int layer.queryByRect(ShapeObj poShape)
   Query using a shape */

DLEXPORT void php3_ms_lyr_queryByShape(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval   *pThis, *pShape;
    layerObj *self=NULL;
    mapObj   *parent_map;
    shapeObj *poShape=NULL;
    int      nStatus = MS_FAILURE;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pShape) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    poShape = 
        (shapeObj *)_phpms_fetch_handle2(pShape, 
                                         PHPMS_GLOBAL(le_msshape_ref),
                                         PHPMS_GLOBAL(le_msshape_new),
                                         list TSRMLS_CC);

    parent_map = (mapObj*)_phpms_fetch_property_handle(pThis, "_map_handle_", 
                                                       PHPMS_GLOBAL(le_msmap),
                                                       list TSRMLS_CC, E_ERROR);

    if (self && poShape && parent_map &&
        (nStatus=layerObj_queryByShape(self, parent_map, 
                                       poShape)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }

    RETURN_LONG(nStatus);
}
/* }}} */


/**********************************************************************
 *                        layer->setFilter()
 **********************************************************************/

/* {{{ proto int layer.setFilter(string filter)
   Set layer filter expression.  Returns 0 on success, -1 in error. */

DLEXPORT void php3_ms_lyr_setFilter(INTERNAL_FUNCTION_PARAMETERS)
{
    layerObj *self;
    pval   *pFilterString;
    pval   *pThis;
    int     nStatus = -1;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pFilterString) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }
    convert_to_string(pFilterString);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    if (self == NULL || 
        (nStatus = layerObj_setFilter(self, 
                                      pFilterString->value.str.val)) != 0)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    RETURN_LONG(nStatus);
}
/* }}} */

/**********************************************************************
 *                        layer->setProjection()
 **********************************************************************/

/* {{{ proto int layer.setProjection(string projection)
   Set projection and coord. system for the layer. Returns -1 on error. */

DLEXPORT void php3_ms_lyr_setProjection(INTERNAL_FUNCTION_PARAMETERS)
{
    layerObj *self;
    pval   *pProjString;
    pval   *pThis;
    int     nStatus = 0;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pProjString) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pProjString);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    if (self == NULL || 
        (nStatus = layerObj_setProjection(self, 
                                          pProjString->value.str.val)) == -1)
        _phpms_report_mapserver_error(E_ERROR);

    RETURN_LONG(nStatus);
}
/* }}} */


/**********************************************************************
 *                        layer->setWKTProjection()
 **********************************************************************/

/* {{{ proto int layer.setWKTProjection(string projection)
   Set projection and coord. system for the layer. Returns -1 on error. */

DLEXPORT void php3_ms_lyr_setWKTProjection(INTERNAL_FUNCTION_PARAMETERS)
{
    layerObj *self;
    pval   *pProjString;
    pval   *pThis;
    int     nStatus = 0;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pProjString) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pProjString);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    if (self == NULL || 
        (nStatus = layerObj_setWKTProjection(self, 
                                          pProjString->value.str.val)) == -1)
        _phpms_report_mapserver_error(E_ERROR);

    RETURN_LONG(nStatus);
}
/* }}} */


/**********************************************************************
 *                        layer->getProjection()
 **********************************************************************/

/* {{{ proto int layer.getProjection()
    Return the projection string of the layer. Returns FALSE on error. */

DLEXPORT void php3_ms_lyr_getProjection(INTERNAL_FUNCTION_PARAMETERS)
{
    layerObj    *self;
    pval        *pThis = NULL;
    char        *pszPojString = NULL;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL)
    {
        RETURN_FALSE;
    }

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_FALSE;
    }

    if (self == NULL)
    {
        RETURN_FALSE;
    }

    pszPojString = layerObj_getProjection(self);
    if (pszPojString == NULL)
    {
        RETURN_FALSE;
    }
    else
    {
        RETVAL_STRING(pszPojString, 1);
        free(pszPojString);
    }
}

/************************************************************************/
/*                        layer->addFeature                             */
/*                                                                      */
/*      Add a new feature in a layer.                                   */
/************************************************************************/

/* {{{ proto int layer.addFeature(ShapeObj poShape)
   Add a shape */
DLEXPORT void php3_ms_lyr_addFeature(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis, *pShape;
    layerObj    *self=NULL;
    shapeObj    *poShape=NULL;
    int         nResult = -1;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pShape) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    poShape = 
        (shapeObj *)_phpms_fetch_handle2(pShape, 
                                         PHPMS_GLOBAL(le_msshape_ref),
                                         PHPMS_GLOBAL(le_msshape_new),
                                         list TSRMLS_CC);

    if (self && poShape)
    {
        nResult = layerObj_addFeature(self, poShape);
    }

    RETURN_LONG(nResult);
}

/* }}} */

/**********************************************************************
 *                        layer->getNumResults()
 **********************************************************************/

/* {{{ proto int layer.getNumResults()
   Returns the number of results from this layer in the last query. */

DLEXPORT void php3_ms_lyr_getNumResults(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *pThis;
    layerObj *self=NULL;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        ARG_COUNT(ht) > 0) 
    {
        WRONG_PARAM_COUNT;
    }

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    if (self && self->resultcache) 
    {
        RETURN_LONG(self->resultcache->numresults);
    }

    RETURN_LONG(0);
}
/* }}} */

/**********************************************************************
 *                        layer->getResult(i)
 **********************************************************************/

/* {{{ proto int layer.getResult(int i)
   Returns a resultCacheMemberObj by index from a layer object.  Returns a valid object or FALSE(0) if index is invalid. */

DLEXPORT void php3_ms_lyr_getResult(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pIndex;
    layerObj *self;
    resultCacheMemberObj *poResult;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pIndex) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pIndex);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);

    if (self== NULL ||
        (poResult = layerObj_getResult(self, pIndex->value.lval)) == NULL)
    {
        /* Invalid result index. */
        RETURN_FALSE;
    }

    /* Return a resultCacheMemberObj object */
    _phpms_build_resultcachemember_object(&(self->resultcache->
                                            results[pIndex->value.lval]),
                                          list TSRMLS_CC, return_value);
}
/* }}} */



/**********************************************************************
 *                        layer->open()
 **********************************************************************/

/* {{{ proto int layer.open()
   Open the layer for use with getShape().  Returns MS_SUCCESS/MS_FAILURE. */

DLEXPORT void php3_ms_lyr_open(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *pThis;
    layerObj *self=NULL;
    int         nStatus = MS_FAILURE;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL || ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }


    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    if (self == NULL || 
        (nStatus = layerObj_open(self)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }
    else
    {
        // Until we implement selection of fields, default to selecting
        // all fields
        msLayerGetItems(self);
    }

    RETURN_LONG(nStatus);
}
/* }}} */

/**********************************************************************
 *                        layer->close()
 **********************************************************************/

/* {{{ proto int layer.close()
   Close layer previously opened with open(). */

DLEXPORT void php3_ms_lyr_close(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *pThis;
    layerObj *self=NULL;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    if (self)
        layerObj_close(self);

}
/* }}} */

/**********************************************************************
 *                        layer->getShape()
 **********************************************************************/

/* {{{ proto shapeObj layer.getShape(tileindex, shapeindex)
   Retrieve shapeObj from a layer by index. */

DLEXPORT void php3_ms_lyr_getShape(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval  *pThis, *pTileId, *pShapeId ;
    layerObj *self=NULL;
    shapeObj    *poShape;
 
    
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pTileId, &pShapeId) != SUCCESS) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pTileId);
    convert_to_long(pShapeId);

    /* Create a new shapeObj to hold the result 
     * Note that the type used to create the shape (MS_NULL) does not matter
     * at this point since it will be set by SHPReadShape().
     */
    if ((poShape = shapeObj_new(MS_SHAPE_NULL)) == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "Failed creating new shape (out of memory?)");
        RETURN_FALSE;
    }

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);

    if (self == NULL || 
        layerObj_getShape(self, poShape, pTileId->value.lval, 
                          pShapeId->value.lval) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
        shapeObj_destroy(poShape);
        RETURN_FALSE; 
    }

    /* Return valid object */
    _phpms_build_shape_object(poShape, PHPMS_GLOBAL(le_msshape_new), self,
                              list, return_value);
}
/* }}} */


/**********************************************************************
 *                        layer->getMetaData()
 **********************************************************************/

/* {{{ proto string layer.getMetaData(string name)
   Return MetaData entry by name, or empty string if not found. */

DLEXPORT void php3_ms_lyr_getMetaData(INTERNAL_FUNCTION_PARAMETERS)
{
    layerObj *self;
    pval   *pThis, *pName;
    char   *pszValue = NULL;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pName) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pName);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    if (self == NULL || 
        (pszValue = layerObj_getMetaData(self, pName->value.str.val)) == NULL)
    {
        pszValue = "";
    }

    RETURN_STRING(pszValue, 1);
}
/* }}} */

/**********************************************************************
 *                        layer->setMetaData()
 **********************************************************************/

/* {{{ proto int layer.setMetaData(string name, string value)
   Set MetaData entry by name.  Returns MS_SUCCESS/MS_FAILURE */

DLEXPORT void php3_ms_lyr_setMetaData(INTERNAL_FUNCTION_PARAMETERS)
{
    layerObj *self;
    pval   *pThis, *pName, *pValue;
    int    nStatus = MS_FAILURE;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pName, &pValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pName);
    convert_to_string(pValue);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    if (self == NULL || 
        (nStatus = layerObj_setMetaData(self, 
                                        pName->value.str.val,  
                                        pValue->value.str.val)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    RETURN_LONG(nStatus);
}
/* }}} */


/**********************************************************************
 *                        layer->removeMetaData()
 **********************************************************************/

/* {{{ proto int layer.removeMetaData(string name)
   Remove MetaData entry by name.  Returns MS_SUCCESS/MS_FAILURE */

DLEXPORT void php3_ms_lyr_removeMetaData(INTERNAL_FUNCTION_PARAMETERS)
{
    layerObj *self;
    pval   *pThis, *pName;
    int    nStatus = MS_FAILURE;
    HashTable   *list=NULL;
    pThis = getThis();


    if (pThis == NULL ||
        getParameters(ht, 1, &pName) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pName);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    if (self == NULL || 
        (nStatus = layerObj_removeMetaData(self, 
                                        pName->value.str.val)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    RETURN_LONG(nStatus);
}
/* }}} */

/**********************************************************************
 *                        layer->getWMSFeatureInfoURL()
 **********************************************************************/

/* {{{ proto string layer.getWMSFeatureInfoURL(int clickX, int clickY, int featureCount, string infoFormat)
   Return a WMS GetFeatureInfo URL (only for WMS layers). */

DLEXPORT void php3_ms_lyr_getWMSFeatureInfoURL(INTERNAL_FUNCTION_PARAMETERS)
{
    layerObj *self;
    pval   *pThis, *pX, *pY, *pCount, *pFormat;
    char   *pszValue = NULL;
    mapObj *parent_map;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 4, &pX, &pY, &pCount, &pFormat) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pX);
    convert_to_long(pY);
    convert_to_long(pCount);
    convert_to_string(pFormat);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);

    parent_map = (mapObj*)_phpms_fetch_property_handle(pThis, "_map_handle_", 
                                                       PHPMS_GLOBAL(le_msmap),
                                                       list TSRMLS_CC, E_ERROR);


    if (self == NULL || parent_map == NULL ||
        (pszValue = layerObj_getWMSFeatureInfoURL(self, parent_map, 
                                                  pX->value.lval,
                                                  pY->value.lval,
                                                  pCount->value.lval,
                                                  pFormat->value.str.val)) == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        RETURN_STRING("", 1);
    }

    RETVAL_STRING(pszValue, 1);
    free(pszValue);
}
/* }}} */

/**********************************************************************
 *                        layer->getItems()
 *
 * Return an array of string containing all the layer items
 **********************************************************************/

/* {{{ proto char** layer.getItems()
   Return an array containing all the layer items.*/

DLEXPORT void php3_ms_lyr_getItems(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis;
    layerObj    *self=NULL;
    int         i = 0;
    int         res = 0;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL)
    {
        WRONG_PARAM_COUNT;
    }

    if (array_init(return_value) == FAILURE)
    {
        RETURN_FALSE;
    }

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                         list TSRMLS_CC);
   
    if (self != NULL)
     res = msLayerGetItems(self);
   
    if (res != MS_FAILURE &&  self->numitems > 0)
    {
       for (i=0; i<self->numitems; i++)
       {
         /* add a copy of the group name to the PHP array */
          add_next_index_string(return_value, self->items[i], 1);
       }
    }
    else
    {
        RETURN_FALSE;
    }
}

/**********************************************************************
 *                        layer->setProcessing()
 *
 * set a processing string to the layer
 **********************************************************************/

/* {{{ boolean layer.setProcessing(string)
  set a processing string to the layer*/

DLEXPORT void php3_ms_lyr_setProcessing(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis, *pString;
    layerObj    *layer=NULL;

    HashTable   *list=NULL;
    pThis = getThis();
    

    if (pThis == NULL ||
        getParameters(ht, 1, &pString) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pString);

    layer = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
    
    if (!layer)
      RETURN_FALSE;

    layer->numprocessing++;
    if(layer->numprocessing == 1)
      layer->processing = (char **) malloc(2*sizeof(char *));
    else
      layer->processing = (char **) realloc(layer->processing, sizeof(char*) * (layer->numprocessing+1));
    layer->processing[layer->numprocessing-1] = strdup(pString->value.str.val);
    layer->processing[layer->numprocessing] = NULL;
    
    _phpms_set_property_long(pThis, "num_processing", layer->numprocessing, E_ERROR);

    RETURN_TRUE;
}    

/**********************************************************************
 *                        layer->getProcessing()
 *
 * Return an array of string containing all the layer items
 **********************************************************************/

/* {{{ proto char** layer.getProcessing()
   Return an array containing all the processing strings.*/
DLEXPORT void php3_ms_lyr_getProcessing(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis;
    layerObj    *self=NULL;
    int         i = 0;

    HashTable   *list=NULL;
    pThis = getThis();


    if (pThis == NULL)
    {
        WRONG_PARAM_COUNT;
    }

    if (array_init(return_value) == FAILURE)
      RETURN_FALSE;
    

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                           list TSRMLS_CC);
   
    if (self == NULL || self->numprocessing <= 0)
      RETURN_FALSE;

   
    for (i=0; i<self->numprocessing; i++)
    {
          add_next_index_string(return_value, self->processing[i], 1);
    }
}

/**********************************************************************
 *                        layer->clearProcessing()
 *
 * clear the processing strings in the layer
 **********************************************************************/

/* {{{ boolean layer.clearProcessing()
  clear the processing strings in the layer*/

DLEXPORT void php3_ms_lyr_clearProcessing(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis;
    layerObj    *layer=NULL;
    int         i = 0;

    HashTable   *list=NULL;
    pThis = getThis();
    

    if (pThis == NULL)
        WRONG_PARAM_COUNT;

    layer = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                            list TSRMLS_CC);
    
    if (!layer)
      RETURN_FALSE;
    
    if (layer->numprocessing > 0)
    {
        for(i=0; i<layer->numprocessing; i++)
          free(layer->processing[i]);

        layer->numprocessing = 0;
        free(layer->processing);

        _phpms_set_property_long(pThis, "num_processing", layer->numprocessing, E_ERROR);

    }
}        


/**********************************************************************
 *                        layer->executewfsgetfeature()
 *
 * Execute a GetFeature request on a wfs layer and return the name
 * of the temporary GML file created.
 **********************************************************************/

/* {{{ string layer.executewfsgetfeature()*/

DLEXPORT void php3_ms_lyr_executeWFSGetfeature(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis;
    layerObj    *layer=NULL;
    char        *pszValue = NULL;

    HashTable   *list=NULL;
    pThis = getThis();
    

    if (pThis == NULL)
        WRONG_PARAM_COUNT;

    layer = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer),
                                            list TSRMLS_CC);
    
    if (layer == NULL || (pszValue=layerObj_executeWFSGetFeature(layer)) == NULL)
       RETURN_STRING("", 1);

    RETVAL_STRING(pszValue, 1);
    free(pszValue);
}
 
/**********************************************************************
 *                        layer->applySLD(szSLDString)
 *
 * Apply an XML SLD string to the layer
 **********************************************************************/
DLEXPORT void php3_ms_lyr_applySLD(INTERNAL_FUNCTION_PARAMETERS)
{
     pval        *pThis;
     pval        *pSLDString=NULL, *pStyleLayer=NULL;
     layerObj      *self=NULL;
     HashTable   *list=NULL;
     int         nStatus = MS_SUCCESS;
     int         nArgs = ARG_COUNT(ht);

     pThis = getThis();

     if (pThis == NULL)
     {
         RETURN_LONG(MS_FAILURE);
    }

     if (nArgs != 1 && nArgs != 2)
     {
        WRONG_PARAM_COUNT;
     }
     if (getParameters(ht,nArgs,&pSLDString, &pStyleLayer) == FAILURE)
     {
        WRONG_PARAM_COUNT;
     }

    convert_to_string(pSLDString);
    if (nArgs == 2)
      convert_to_string(pStyleLayer);
    
    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer), 
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    if (nArgs == 2)
      nStatus = layerObj_applySLD(self, pSLDString->value.str.val,
                                  pStyleLayer->value.str.val);
    else
      nStatus = layerObj_applySLD(self, pSLDString->value.str.val, NULL);

    RETURN_LONG(nStatus);
}


/**********************************************************************
 *                        layer->applySLD(szSLDURL)
 *
 * Apply an SLD to a layer. The SLD is given as an URL.
 **********************************************************************/
DLEXPORT void php3_ms_lyr_applySLDURL(INTERNAL_FUNCTION_PARAMETERS)
{
     pval        *pThis;
     pval        *pSLDString=NULL, *pStyleLayer=NULL;
     layerObj      *self=NULL;
     HashTable   *list=NULL;
     int         nStatus = MS_SUCCESS;
     int         nArgs = ARG_COUNT(ht);

     pThis = getThis();

     if (pThis == NULL)
     {
         RETURN_LONG(MS_FAILURE);
     }
     if (nArgs != 1 && nArgs != 2)
     {
        WRONG_PARAM_COUNT;
     }
     
    if (getParameters(ht,nArgs,&pSLDString, &pStyleLayer) == FAILURE)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pSLDString);
    if (nArgs == 2)
      convert_to_string(pStyleLayer);

    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer), 
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    if (nArgs == 2)
      nStatus = layerObj_applySLDURL(self, pSLDString->value.str.val,
                                      pStyleLayer->value.str.val);
    else
      nStatus = layerObj_applySLDURL(self, pSLDString->value.str.val, NULL);

    RETURN_LONG(nStatus);
}


DLEXPORT void php3_ms_lyr_generateSLD(INTERNAL_FUNCTION_PARAMETERS)
{
     pval        *pThis;
     layerObj      *self=NULL;
     HashTable   *list=NULL;
     char       *pszBuffer = NULL;

     pThis = getThis();

     if (pThis == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }


    self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer), 
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(MS_FAILURE);
    }

    pszBuffer = layerObj_generateSLD(self);

    if (pszBuffer)
    {
        RETVAL_STRING(pszBuffer, 1);
        free(pszBuffer);
    }
    else
    {
        _phpms_report_mapserver_error(E_WARNING);
        RETURN_STRING("", 0);
    }
}


DLEXPORT void  php3_ms_lyr_moveClassUp(INTERNAL_FUNCTION_PARAMETERS)
{
     pval        *pThis, *pClassIdx;
     layerObj      *self=NULL;
     HashTable   *list=NULL;
     int         nStatus = MS_FAILURE;

     pThis = getThis();

     if (pThis == NULL ||
        getParameters(ht, 1, &pClassIdx) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

     convert_to_long(pClassIdx);

     self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer), 
                                            list TSRMLS_CC);

     if (self != NULL)
     {
         nStatus = layerObj_moveClassUp(self, pClassIdx->value.lval);
     }

      RETURN_LONG(nStatus);
}

DLEXPORT void  php3_ms_lyr_moveClassDown(INTERNAL_FUNCTION_PARAMETERS)
{
     pval        *pThis, *pClassIdx;
     layerObj      *self=NULL;
     HashTable   *list=NULL;
     int         nStatus = MS_FAILURE;


     pThis = getThis();

     if (pThis == NULL ||
        getParameters(ht, 1, &pClassIdx) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

     convert_to_long(pClassIdx);

     self = (layerObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslayer), 
                                            list TSRMLS_CC);

     if (self != NULL)
     {
         nStatus = layerObj_moveClassDown(self, pClassIdx->value.lval);
     }

     RETURN_LONG(nStatus);
}
/* }}} */

/*=====================================================================
 *                 PHP function wrappers - labelObj class
 *====================================================================*/

/**********************************************************************
 *                     _phpms_build_label_object()
 **********************************************************************/
static long _phpms_build_label_object(labelObj *plabel,
                                      HashTable *list, pval *return_value)
{
    int         label_id;
    pval        *new_obj_ptr;

    if (plabel == NULL)
        return 0;

    label_id = php3_list_insert(plabel, PHPMS_GLOBAL(le_mslabel));

    _phpms_object_init(return_value, label_id, php_label_class_functions,
                       PHP4_CLASS_ENTRY(label_class_entry_ptr));

    /* editable properties */
    PHPMS_ADD_PROP_STR(return_value,  "font",       plabel->font);
    add_property_long(return_value,   "type",       plabel->type);
    add_property_long(return_value,   "shadowsizex",plabel->shadowsizex);
    add_property_long(return_value,   "shadowsizey",plabel->shadowsizey);
    add_property_long(return_value,   "backgroundshadowsizex",
                                                plabel->backgroundshadowsizex);
    add_property_long(return_value,   "backgroundshadowsizey",
                                                plabel->backgroundshadowsizey);
    add_property_long(return_value,   "size",       plabel->size);
    add_property_long(return_value,   "minsize",    plabel->minsize);
    add_property_long(return_value,   "maxsize",    plabel->maxsize);
    add_property_long(return_value,   "position",   plabel->position);
    add_property_long(return_value,   "offsetx",    plabel->offsetx);
    add_property_long(return_value,   "offsety",    plabel->offsety);
    add_property_double(return_value, "angle",      plabel->angle);
    add_property_long(return_value,   "autoangle",  plabel->autoangle);
    add_property_long(return_value,   "buffer",     plabel->buffer);
    add_property_long(return_value,   "antialias",  plabel->antialias);
    add_property_long(return_value,   "wrap",       plabel->wrap);
    add_property_long(return_value,   "minfeaturesize",plabel->minfeaturesize);
    add_property_long(return_value,   "autominfeaturesize",plabel->autominfeaturesize);
    add_property_long(return_value,   "mindistance",plabel->mindistance);
    add_property_long(return_value,   "partials",   plabel->partials);
    add_property_long(return_value,   "force",      plabel->force);

    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_color_object(&(plabel->color),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "color",new_obj_ptr,E_ERROR);

    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_color_object(&(plabel->outlinecolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "outlinecolor",new_obj_ptr,E_ERROR);

    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_color_object(&(plabel->shadowcolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "shadowcolor",new_obj_ptr,E_ERROR);
 

    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_color_object(&(plabel->backgroundcolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "backgroundcolor",new_obj_ptr,E_ERROR);

    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_color_object(&(plabel->backgroundshadowcolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "backgroundshadowcolor",new_obj_ptr,E_ERROR);


    return label_id;
}


/**********************************************************************
 *                        label->set()
 **********************************************************************/

/* {{{ proto int label.set(string property_name, new_value)
   Set object property to a new value. Returns -1 on error. */

DLEXPORT void php3_ms_label_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    labelObj *self;
    pval   *pPropertyName, *pNewValue, *pThis;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (labelObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslabel),
                                           list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    IF_SET_STRING(     "font",         self->font)
    else IF_SET_LONG(  "type",         self->type)
    else IF_SET_LONG(  "shadowsizex",  self->shadowsizex)
    else IF_SET_LONG(  "shadowsizey",  self->shadowsizey)
    else IF_SET_LONG(  "backgroundshadowsizex", self->backgroundshadowsizex)
    else IF_SET_LONG(  "backgroundshadowsizey", self->backgroundshadowsizey)
    else IF_SET_LONG(  "size",         self->size)
    else IF_SET_LONG(  "minsize",      self->minsize)
    else IF_SET_LONG(  "maxsize",      self->maxsize)
    else IF_SET_LONG(  "position",     self->position)
    else IF_SET_LONG(  "offsetx",      self->offsetx)
    else IF_SET_LONG(  "offsety",      self->offsety)
    else IF_SET_DOUBLE("angle",        self->angle)
    else IF_SET_LONG(  "autoangle",    self->autoangle)
    else IF_SET_LONG(  "buffer",       self->buffer)
    else IF_SET_LONG(  "antialias",    self->antialias)
    else IF_SET_BYTE(  "wrap",         self->wrap)
    else IF_SET_LONG(  "minfeaturesize", self->minfeaturesize)
    else IF_SET_LONG(  "autominfeaturesize", self->autominfeaturesize)
    else IF_SET_LONG(  "mindistance",  self->mindistance)
    else IF_SET_LONG(  "partials",     self->partials)
    else IF_SET_LONG(  "force",        self->force)
    else
    {
        php3_error(E_ERROR,"Property '%s' does not exist in this object.", 
                            pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }

    if (self->size == -1)
    {
        _phpms_set_property_long(pThis,"size", MS_MEDIUM, E_ERROR);
        self->size =  MS_MEDIUM;
        self->sizescaled =  MS_MEDIUM;
    }

    RETURN_LONG(0);
}


/*=====================================================================
 *                 PHP function wrappers - classObj class
 *====================================================================*/

/**********************************************************************
 *                     _phpms_build_class_object()
 **********************************************************************/
static long _phpms_build_class_object(classObj *pclass, int parent_map_id, 
                                      int parent_layer_id,
                                      HashTable *list, 
                                      pval *return_value TSRMLS_DC)
{
    int class_id;
#ifdef PHP4
    pval        *new_obj_ptr;
#else
    pval        new_obj_param;  /* No, it's not a pval * !!! */
    pval        *new_obj_ptr;
    new_obj_ptr = &new_obj_param;
#endif

    if (pclass == NULL)
        return 0;

    class_id = php3_list_insert(pclass, PHPMS_GLOBAL(le_msclass));

    _phpms_object_init(return_value, class_id, php_class_class_functions,
                       PHP4_CLASS_ENTRY(class_class_entry_ptr));

#ifdef PHP4
    add_property_resource(return_value, "_layer_handle_", parent_layer_id);
    zend_list_addref(parent_layer_id);
#else
    add_property_long(return_value, "_layer_handle_", parent_layer_id);
#endif
   
#ifdef PHP4
    add_property_resource(return_value, "_map_handle_", parent_map_id);
    zend_list_addref(parent_map_id);
#else
    add_property_long(return_value, "_map_handle_", parent_map_id);
#endif   

    /* editable properties */
    PHPMS_ADD_PROP_STR(return_value,  "name",       pclass->name);
    PHPMS_ADD_PROP_STR(return_value,  "title",       pclass->title);
    add_property_long(return_value,   "type",       pclass->type);
    add_property_long(return_value,   "status",     pclass->status);
    PHPMS_ADD_PROP_STR(return_value,  "template",   pclass->template);
    add_property_long(return_value,   "numstyles",  pclass->numstyles);
    
#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);
#endif
    _phpms_build_label_object(&(pclass->label), list, new_obj_ptr);
    _phpms_add_property_object(return_value, "label", new_obj_ptr,E_ERROR);

    add_property_double(return_value,  "minscale", pclass->minscale);
    add_property_double(return_value,  "maxscale", pclass->maxscale);
    
    return class_id;
}


/**********************************************************************
 *                        ms_newClassObj()
 **********************************************************************/

/* {{{ proto layerObj ms_newClassObj(layerObj layer)
   Create a new class in the specified layer. */

DLEXPORT void php3_ms_class_new(INTERNAL_FUNCTION_PARAMETERS)
{
    pval  *pLayerObj,*pClassObj;
    layerObj *parent_layer;
    classObj *pNewClass;
    classObj *class_obj = NULL;
    int layer_id, map_id;
    int         nArgs = ARG_COUNT(ht);

#ifdef PHP4
    HashTable   *list=NULL;
#endif


    if (nArgs != 1 && nArgs != 2)
    {
        WRONG_PARAM_COUNT;
    }


    if (getParameters(ht, nArgs, &pLayerObj, &pClassObj) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    parent_layer = (layerObj*)_phpms_fetch_handle(pLayerObj, 
                                                  PHPMS_GLOBAL(le_mslayer),
                                                  list TSRMLS_CC);

    if (nArgs == 2)
    {
        class_obj = (classObj*)_phpms_fetch_handle(pClassObj, 
                                                   PHPMS_GLOBAL(le_msclass),
                                                   list TSRMLS_CC);
    }

    if (parent_layer == NULL ||
        (pNewClass = classObj_new(parent_layer, class_obj)) == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
        RETURN_FALSE;
    }

     _phpms_set_property_long(pLayerObj,"numclasses", parent_layer->numclasses, 
                              E_ERROR); 

    /* We will store a reference to the parent_layer object id inside
     * the class obj.
     */
    layer_id = _phpms_fetch_property_resource(pLayerObj, "_handle_", E_ERROR);

    /* We will store a reference to the parent_map object id inside
     * the class obj.
     */
    map_id = _phpms_fetch_property_resource(pLayerObj, "_map_handle_", E_ERROR);
   
    /* Return class object */
    _phpms_build_class_object(pNewClass, map_id, layer_id, list, 
                              return_value TSRMLS_CC);
}
/* }}} */


/**********************************************************************
 *                        class->set()
 **********************************************************************/

/* {{{ proto int class.set(string property_name, new_value)
   Set object property to a new value. Returns -1 on error. */

DLEXPORT void php3_ms_class_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    classObj *self;
    mapObj *parent_map;
    pval   *pPropertyName, *pNewValue, *pThis;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (classObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msclass),
                                           list TSRMLS_CC);
   
    parent_map = (mapObj*)_phpms_fetch_property_handle(pThis, "_map_handle_",
                                                       PHPMS_GLOBAL(le_msmap),
                                                       list TSRMLS_CC, E_ERROR);

    if (self == NULL || parent_map == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    IF_SET_STRING(     "name",         self->name)
    else IF_SET_STRING("title",         self->title)
    else IF_SET_LONG(  "type",         self->type)
    else IF_SET_LONG(  "status",       self->status)
    else IF_SET_DOUBLE("minscale", self->minscale)
    else IF_SET_DOUBLE("maxscale", self->maxscale)
    else IF_SET_STRING("template",      self->template)
    else if (strcmp( "numstyles", pPropertyName->value.str.val) == 0)
    {
        php3_error(E_ERROR,"Property '%s' is read-only and cannot be set.", 
                            pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }
    else
    {
        php3_error(E_ERROR,"Property '%s' does not exist in this object.",
                            pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }


    RETURN_LONG(0);
}
/* }}} */

/************************************************************************/
/*                          class->setExpression()                      */
/*                                                                      */
/*      Set the expression string for a class object.                   */
/*                                                                      */
/*      Returns 0 on success, -1 on error.                              */
/************************************************************************/

/* {{{ proto int class.setExpression(string exression)
   Set the expression string for a class object. */

DLEXPORT void php3_ms_class_setExpression(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval   *pThis, *pString;
    classObj *self=NULL;
    int     nStatus=-1;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pString) == FAILURE)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pString);

    self = (classObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msclass),
                                           list TSRMLS_CC);

    if (self == NULL || 
        (nStatus = classObj_setExpression(self, pString->value.str.val)) != 0)
    {
        _phpms_report_mapserver_error(E_ERROR);
        RETURN_LONG(nStatus);
    }

    RETURN_LONG(0);
}
/* }}} */


/************************************************************************/
/*                          class->getExpression()                      */
/*                                                                      */
/*      Returns the expression string for a class object.               */
/*                                                                      */
/************************************************************************/

/* {{{ proto int class.getExpression(string exression)
   Set the expression string for a class object. */

DLEXPORT void php3_ms_class_getExpression(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval   *pThis;
    classObj *self=NULL;
    HashTable   *list=NULL;
     char   *pszValue = NULL;

    pThis = getThis();

    if (pThis == NULL)
    {
        WRONG_PARAM_COUNT;
    }

    self = (classObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msclass),
                                           list TSRMLS_CC);
    if (self == NULL || 
        (pszValue = classObj_getExpressionString(self)) == NULL)
    {
      RETURN_STRING("", 1);
    }
    else
    {
      RETURN_STRING(pszValue, 1);
      free(pszValue);
    }
}
/* }}} */


/************************************************************************/
/*                          class->setText()                            */
/*                                                                      */
/*      Set the expression string for a class object.                   */
/*                                                                      */
/*      Returns 0 on success, -1 on error.                              */
/************************************************************************/

/* {{{ proto int class.setText(string text)
   Set the text string for a class object. */

DLEXPORT void php3_ms_class_setText(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pThis, *pString, *pLayerObj;
    classObj    *self=NULL;
    layerObj    *parent_layer;
    int         nStatus=-1;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pLayerObj, &pString) == FAILURE)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pString);

    self = (classObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msclass),
                                           list TSRMLS_CC);

    parent_layer = (layerObj*)_phpms_fetch_handle(pLayerObj, 
                                                  PHPMS_GLOBAL(le_mslayer),
                                                  list TSRMLS_CC);

    if (self == NULL || parent_layer == NULL ||
        (nStatus = classObj_setText(self, parent_layer, pString->value.str.val)) != 0)
    {
        _phpms_report_mapserver_error(E_ERROR);
        RETURN_LONG(nStatus);
    }

    RETURN_LONG(0);
}
/* }}} */


/************************************************************************/
/*                          class->drawLegendIcon()                     */
/*                                                                      */
/*      return the legend icon related to this class.                   */
/*                                                                      */
/*      Returns 0 on success, -1 on error.                              */
/************************************************************************/

/* {{{ proto int class.drawLegendIcon(int width, int height, image img, int dstX, int dstY)
   set the lengend icon in img. */

/* SFO */

DLEXPORT void php3_ms_class_drawLegendIcon(INTERNAL_FUNCTION_PARAMETERS)
{
    pval  *pWidth, *pHeight, *imgObj, *pDstX, *pDstY, *pThis;
    mapObj *parent_map;
    classObj *self;
    layerObj *parent_layer;
    imageObj *im = NULL;
    int    retVal=0;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 5, &pWidth, &pHeight, &imgObj, &pDstX, &pDstY) == FAILURE)
    {
        WRONG_PARAM_COUNT;
    }

    im = (imageObj *)_phpms_fetch_handle(imgObj,
                                         PHPMS_GLOBAL(le_msimg), list TSRMLS_CC);

    convert_to_long(pWidth);
    convert_to_long(pHeight);
    convert_to_long(pDstX);
    convert_to_long(pDstY);   

    self = (classObj *)_phpms_fetch_handle(pThis, 
                                           PHPMS_GLOBAL(le_msclass),
                                           list TSRMLS_CC);

    parent_layer = (layerObj*)_phpms_fetch_property_handle(pThis, "_layer_handle_",
                                                           PHPMS_GLOBAL(le_mslayer),
                                                           list TSRMLS_CC, E_ERROR);

    parent_map = (mapObj*)_phpms_fetch_property_handle(pThis, "_map_handle_",
                                                       PHPMS_GLOBAL(le_msmap),
                                                       list TSRMLS_CC, E_ERROR);
    if (im != NULL && !MS_DRIVER_GD(im->format))
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_WARNING, "DrawLegendicon function is only available for GD dirvers");
        RETURN_FALSE;
    }
    if (self == NULL || parent_map == NULL || parent_layer == NULL ||
        (retVal = classObj_drawLegendIcon(self, 
                                          parent_map, 
                                          parent_layer, 
                                          pWidth->value.lval, pHeight->value.lval, 
                                          im->img.gd, 
                                          pDstX->value.lval, pDstY->value.lval)) == -1)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }
   
    RETURN_LONG(retVal);   
}

/************************************************************************/
/*                          class->createLegendIcon()                   */
/*                                                                      */
/*      return the legend icon related to this class.                   */
/*                                                                      */
/*      Returns image object.                                           */
/************************************************************************/

/* {{{ proto int class.createLegendIcon(int width, int height)
   return the lengend icon. */

DLEXPORT void php3_ms_class_createLegendIcon(INTERNAL_FUNCTION_PARAMETERS)
{
    pval  *pWidth, *pHeight, *pThis;
    mapObj *parent_map;
    classObj *self;
    layerObj *parent_layer;
    imageObj *im = NULL;
   
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pWidth, &pHeight) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pWidth);
    convert_to_long(pHeight);

    self = (classObj *)_phpms_fetch_handle(pThis,
                                           PHPMS_GLOBAL(le_msclass),
                                           list TSRMLS_CC);

    parent_layer = (layerObj*)_phpms_fetch_property_handle(pThis, "_layer_handle_",
                                                           PHPMS_GLOBAL(le_mslayer),
                                                           list TSRMLS_CC, E_ERROR);

    parent_map = (mapObj*)_phpms_fetch_property_handle(pThis, "_map_handle_",
                                                       PHPMS_GLOBAL(le_msmap),
                                                       list TSRMLS_CC, E_ERROR);

    if (self == NULL || parent_map == NULL || parent_layer == NULL ||
        (im = classObj_createLegendIcon(self, 
                                        parent_map, 
                                        parent_layer, 
                                        pWidth->value.lval, pHeight->value.lval)) == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
       
        RETURN_FALSE;
    }

    /* Return an image object */
    _phpms_build_img_object(im, &(parent_map->web), list, return_value);
}


/************************************************************************/
/*                      class->getstyle(index)                          */
/*                                                                      */
/*      return the style object referneced by the index. The index      */
/*      should be from 0 to class->numstyles.                           */
/*                                                                      */
/*                                                                      */
/*      Returns a style object.                                         */
/************************************************************************/

/* {{{ proto int class.getstyle(int index)
   return the style object. */

DLEXPORT void php3_ms_class_getStyle(INTERNAL_FUNCTION_PARAMETERS)
{
    pval  *pIndex,  *pThis;
    classObj *self;
    int layer_id, map_id, class_id;
    styleObj *psStyle;

    HashTable   *list=NULL;

    pThis = getThis();


    if (pThis == NULL ||
        getParameters(ht, 1, &pIndex) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pIndex);

    self = (classObj *)_phpms_fetch_handle(pThis,
                                           PHPMS_GLOBAL(le_msclass),
                                           list TSRMLS_CC);
    if (self == NULL)
       php3_error(E_ERROR, "Invalid class object.");

    if (pIndex->value.lval < 0 || pIndex->value.lval >= self->numstyles)
    {
        php3_error(E_ERROR, "Invalid style index.");
    }

    psStyle = &(self->styles[ pIndex->value.lval]);
    
    class_id = _phpms_fetch_property_resource(pThis, "_handle_", E_ERROR);
    layer_id = _phpms_fetch_property_resource(pThis, "_layer_handle_", 
                                               E_ERROR);
    map_id = _phpms_fetch_property_resource(pThis, "_map_handle_", E_ERROR);
      
    /* Return style object */
    _phpms_build_style_object(psStyle, map_id, layer_id, class_id, list, 
                              return_value TSRMLS_CC);
}
    

DLEXPORT void php3_ms_class_clone(INTERNAL_FUNCTION_PARAMETERS)
{
    pval  *pThis = NULL;
    classObj *self = NULL, *pNewClass = NULL;
    layerObj *parent_layer = NULL;
    int layer_id, map_id;
    HashTable   *list=NULL;
    pThis = getThis();



    if (pThis == NULL)
      php3_error(E_ERROR, "Invalid class object.");

    self = (classObj *)_phpms_fetch_handle(pThis,
                                           PHPMS_GLOBAL(le_msclass),
                                           list TSRMLS_CC);
    if (self == NULL)
       php3_error(E_ERROR, "Invalid class object.");

    parent_layer = (layerObj*)_phpms_fetch_property_handle(pThis, "_layer_handle_",
                                                           PHPMS_GLOBAL(le_mslayer),
                                                           list TSRMLS_CC, E_ERROR);

    if ((pNewClass = classObj_clone(self, parent_layer)) == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        RETURN_FALSE;
    }

    layer_id = _phpms_fetch_property_resource(pThis, "_layer_handle_", E_ERROR);
    map_id = _phpms_fetch_property_resource(pThis, "_map_handle_", E_ERROR);

     /* Return class object */
    _phpms_build_class_object(pNewClass, map_id, layer_id, list, 
                              return_value TSRMLS_CC);
}

DLEXPORT void  php3_ms_class_moveStyleUp(INTERNAL_FUNCTION_PARAMETERS)
{
     pval        *pThis, *pIdx;
     classObj      *self=NULL;
     HashTable   *list=NULL;
     int         nStatus = MS_FAILURE;

     pThis = getThis();

     if (pThis == NULL ||
        getParameters(ht, 1, &pIdx) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

     convert_to_long(pIdx);

     self = (classObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msclass), 
                                            list TSRMLS_CC);

     if (self != NULL)
     {
         nStatus = classObj_moveStyleUp(self, pIdx->value.lval);
     }

      RETURN_LONG(nStatus);
}

DLEXPORT void  php3_ms_class_moveStyleDown(INTERNAL_FUNCTION_PARAMETERS)
{
     pval        *pThis, *pIdx;
     classObj      *self=NULL;
     HashTable   *list=NULL;
     int         nStatus = MS_FAILURE;

     pThis = getThis();

     if (pThis == NULL ||
        getParameters(ht, 1, &pIdx) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

     convert_to_long(pIdx);

     self = (classObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msclass), 
                                            list TSRMLS_CC);

     if (self != NULL)
     {
         nStatus = classObj_moveStyleDown(self, pIdx->value.lval);
     }

      RETURN_LONG(nStatus);
}

DLEXPORT void  php3_ms_class_deleteStyle(INTERNAL_FUNCTION_PARAMETERS)
{
     pval        *pThis, *pIdx;
     classObj      *self=NULL;
     HashTable   *list=NULL;
     int         nStatus = MS_FAILURE;

     pThis = getThis();

     if (pThis == NULL ||
        getParameters(ht, 1, &pIdx) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

     convert_to_long(pIdx);

     self = (classObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msclass), 
                                            list TSRMLS_CC);

     if (self != NULL)
     {
         nStatus = classObj_deleteStyle(self, pIdx->value.lval);

         if (nStatus == MS_TRUE)
           _phpms_set_property_long(pThis,"numstyles", self->numstyles, E_ERROR); 
     }

     RETURN_LONG(nStatus);
}


/* }}} */


/*=====================================================================
 *                 PHP function wrappers - colorObj class
 *====================================================================*/

/**********************************************************************
 *                     _phpms_build_color_object()
 **********************************************************************/
static long _phpms_build_color_object(colorObj *pcolor,
                                      HashTable *list, pval *return_value)
{
    int color_id;

    if (pcolor == NULL)
      return 0;

    color_id = php3_list_insert(pcolor, PHPMS_GLOBAL(le_mscolor));

    _phpms_object_init(return_value, color_id, php_color_class_functions,
                       PHP4_CLASS_ENTRY(color_class_entry_ptr));

    /* editable properties */
    add_property_long(return_value,   "red",   pcolor->red);
    add_property_long(return_value,   "green", pcolor->green);
    add_property_long(return_value,   "blue",  pcolor->blue);

    return color_id;
}


/**********************************************************************
 *                        color->setRGB()
 **********************************************************************/

/* {{{ proto int color.setRGB(int R, int G, int B)
   Set new RGB color. Returns -1 on error. */

DLEXPORT void php3_ms_color_setRGB(INTERNAL_FUNCTION_PARAMETERS)
{
    colorObj *self;
    pval   *pR, *pG, *pB, *pThis;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 3, &pR, &pG, &pB) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (colorObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mscolor),
                                           list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_long(pR);
    convert_to_long(pG);
    convert_to_long(pB);

    self->red =   pR->value.lval;
    self->green = pG->value.lval;
    self->blue =  pB->value.lval;

    _phpms_set_property_long(pThis, "red",   self->red, E_ERROR);
    _phpms_set_property_long(pThis, "green", self->green, E_ERROR);
    _phpms_set_property_long(pThis, "blue",  self->blue, E_ERROR);

    RETURN_LONG(0);
}
/* }}} */


/*=====================================================================
 *                 PHP function wrappers - pointObj class
 *====================================================================*/

/**********************************************************************
 *                     _phpms_build_point_object()
 *
 * handle_type is either le_mspoint_ref for an embedded object or
 * le_mspoint_new for a newly allocated object
 **********************************************************************/
static long _phpms_build_point_object(pointObj *ppoint, int handle_type,
                                      HashTable *list, pval *return_value)
{
    int point_id;

    if (ppoint == NULL)
        return 0;

    point_id = php3_list_insert(ppoint, handle_type);

    _phpms_object_init(return_value, point_id, php_point_class_functions,
                       PHP4_CLASS_ENTRY(point_class_entry_ptr));

    /* editable properties */
    add_property_double(return_value,   "x",   ppoint->x);
    add_property_double(return_value,   "y",   ppoint->y);
    add_property_double(return_value,   "m",   ppoint->m);

    return point_id;
}


/**********************************************************************
 *                        ms_newPointObj()
 **********************************************************************/

/* {{{ proto pointObj ms_newPointObj()
   Create a new pointObj instance. */

DLEXPORT void php3_ms_point_new(INTERNAL_FUNCTION_PARAMETERS)
{
    pointObj *pNewPoint;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

    if (ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    if ((pNewPoint = pointObj_new()) == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
        RETURN_FALSE;
    }

    /* Return point object */
    _phpms_build_point_object(pNewPoint, PHPMS_GLOBAL(le_mspoint_new), 
                              list, return_value);
}
/* }}} */

/**********************************************************************
 *                        point->setXY()
 **********************************************************************/

/* {{{ proto int point.setXY(double x, double y, double m)
 3rd argument m is used for Measured shape files. It is not mandatory.
   Set new point. Returns -1 on error. */

DLEXPORT void php3_ms_point_setXY(INTERNAL_FUNCTION_PARAMETERS)
{
    pointObj    *self;
    pval        *pX, *pY, *pM, *pThis;
    int         nArgs = ARG_COUNT(ht);

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        (nArgs != 2 && nArgs != 3))
    {
        WRONG_PARAM_COUNT;
    }

    if (getParameters(ht, nArgs, &pX, &pY, &pM) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (pointObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_mspoint_ref),
                                            PHPMS_GLOBAL(le_mspoint_new),
                                            list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_double(pX);
    convert_to_double(pY);

    

    self->x = pX->value.dval;
    self->y = pY->value.dval;

    if (nArgs == 3)
    {
        convert_to_double(pM); 
        self->m = pM->value.dval;
    }
    else
      self->m = 0.0; 

    _phpms_set_property_double(pThis, "x", self->x, E_ERROR);
    _phpms_set_property_double(pThis, "y", self->y, E_ERROR);
    _phpms_set_property_double(pThis, "m", self->y, E_ERROR);


    RETURN_LONG(0);
}
/* }}} */

/**********************************************************************
 *                        point->project()
 **********************************************************************/

/* {{{ proto int point.project(projectionObj in, projectionObj out)
   Project the point. returns MS_SUCCESS/MS_FAILURE */

DLEXPORT void php3_ms_point_project(INTERNAL_FUNCTION_PARAMETERS)
{
    pval                *pThis, *pIn, *pOut;
    pointObj            *self;
    projectionObj       *poInProj;
    projectionObj       *poOutProj;
    int                 status=MS_FAILURE;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pIn, &pOut) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (pointObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_mspoint_ref),
                                            PHPMS_GLOBAL(le_mspoint_new),
                                            list TSRMLS_CC);
    poInProj = 
        (projectionObj*)_phpms_fetch_handle(pIn, 
                                            PHPMS_GLOBAL(le_msprojection_new), 
                                            list TSRMLS_CC);
    poOutProj = 
        (projectionObj*)_phpms_fetch_handle(pOut, 
                                            PHPMS_GLOBAL(le_msprojection_new), 
                                            list TSRMLS_CC);

    if (self && poInProj && poOutProj &&
        (status = pointObj_project(self, poInProj, poOutProj)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }
    else
    {
        // Update the members of the PHP wrapper object.
        _phpms_set_property_double(pThis, "x", self->x, E_ERROR);
        _phpms_set_property_double(pThis, "y", self->y, E_ERROR);
    }

    RETURN_LONG(status);
}
/* }}} */


/**********************************************************************
 *                        point->draw()
 **********************************************************************/

/* {{{ proto int point.draw(mapObj map, layerObj layer, imageObj img, string class_name, string text)
   Draws the individual point using layer. Returns MS_SUCCESS/MS_FAILURE */

DLEXPORT void php3_ms_point_draw(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pMap, *pLayer, *pImg, *pClass, *pText;
    pointObj    *self;
    mapObj      *poMap;
    layerObj    *poLayer;
    imageObj    *im;
    int         nRetVal=MS_FAILURE;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 5, &pMap, &pLayer, &pImg, &pClass, &pText) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pClass);
    convert_to_string(pText);

    self = (pointObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_mspoint_ref),
                                            PHPMS_GLOBAL(le_mspoint_new),
                                            list TSRMLS_CC);

    poMap = (mapObj*)_phpms_fetch_handle(pMap, PHPMS_GLOBAL(le_msmap), list TSRMLS_CC);
    poLayer = (layerObj*)_phpms_fetch_handle(pLayer, PHPMS_GLOBAL(le_mslayer),
                                             list TSRMLS_CC);
    im = (imageObj *)_phpms_fetch_handle(pImg, PHPMS_GLOBAL(le_msimg), list TSRMLS_CC);

    if (self &&
        (nRetVal = pointObj_draw(self, poMap, poLayer, im, 
                                 pClass->value.lval, 
                                 pText->value.str.val)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    RETURN_LONG(nRetVal)
}
/* }}} */

/**********************************************************************
 *                        point->distanceToPoint()
 **********************************************************************/

/* {{{ proto int point.distanceToPoint(pointObj)
   Calculates distance between two points. */

DLEXPORT void php3_ms_point_distanceToPoint(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pPoint;
    pointObj    *self;
    pointObj    *poPoint;
    double         dfDist=-1.0;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pPoint) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (pointObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_mspoint_ref),
                                            PHPMS_GLOBAL(le_mspoint_new),
                                            list TSRMLS_CC);

    poPoint = (pointObj *)_phpms_fetch_handle2(pPoint, 
                                               PHPMS_GLOBAL(le_mspoint_new), 
                                               PHPMS_GLOBAL(le_mspoint_ref),
                                               list TSRMLS_CC);
    if (self != NULL && poPoint != NULL)
        dfDist = pointObj_distanceToPoint(self, poPoint);

    RETURN_DOUBLE(dfDist)
}
/* }}} */

/**********************************************************************
 *                        point->distanceToLine()
 **********************************************************************/

/* {{{ proto int point.distanceToLine(pointObj p1, (pointObj p2)
   Calculates distance between a point ad a lined defined by the
   two points passed in argument. */

DLEXPORT void php3_ms_point_distanceToLine(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pPoint1, *pPoint2;
    pointObj    *self;
    pointObj    *poPoint1;
    pointObj    *poPoint2;
    double         dfDist=-1.0;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pPoint1, &pPoint2) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }


    self = (pointObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_mspoint_ref),
                                            PHPMS_GLOBAL(le_mspoint_new),
                                            list TSRMLS_CC);

    poPoint1 = (pointObj *)_phpms_fetch_handle2(pPoint1, 
                                                PHPMS_GLOBAL(le_mspoint_new), 
                                                PHPMS_GLOBAL(le_mspoint_ref),
                                                list TSRMLS_CC);

    poPoint2 = (pointObj *)_phpms_fetch_handle2(pPoint2, 
                                                PHPMS_GLOBAL(le_mspoint_new), 
                                                PHPMS_GLOBAL(le_mspoint_ref),
                                                list TSRMLS_CC);
    if (self != NULL && poPoint1 != NULL && poPoint2 != NULL)
        dfDist = pointObj_distanceToLine(self, poPoint1, poPoint2);

    RETURN_DOUBLE(dfDist);
}
/* }}} */

/**********************************************************************
 *                        point->distanceToPoint()
 **********************************************************************/

/* {{{ proto int point.distanceToShape(shapeObj shape)
   Calculates the minimum distance between a point and a shape. */
DLEXPORT void php3_ms_point_distanceToShape(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pShape;
    pointObj    *self;
    shapeObj    *poShape;
    double         dfDist=-1.0;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pShape) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }


    self = (pointObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_mspoint_ref),
                                            PHPMS_GLOBAL(le_mspoint_new),
                                            list TSRMLS_CC);

    poShape = (shapeObj *)_phpms_fetch_handle2(pShape, 
                                               PHPMS_GLOBAL(le_msshape_ref),
                                               PHPMS_GLOBAL(le_msshape_new),
                                               list TSRMLS_CC);
    if (self != NULL && poShape != NULL)
        dfDist = pointObj_distanceToShape(self, poShape);

    RETURN_DOUBLE(dfDist)
}
/* }}} */


/**********************************************************************
 *                        point->free()
 **********************************************************************/

/* {{{ proto int point.free()
   Destroys resources used by a point object */
DLEXPORT void php3_ms_point_free(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    pointObj *self;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif


    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (pointObj *)_phpms_fetch_handle(pThis, le_mspoint_new, list TSRMLS_CC);

    if (self)
    {
        /* Note: we do not have to call the object destructor...
         * removing the object from the resource list using php3_list_delete()
         * will also call the object destructor through the list destructor.
         */
#ifdef PHP4
        pval **phandle;
        if (zend_hash_find(pThis->value.obj.properties, "_handle_", 
                           sizeof("_handle_"), 
                           (void **)&phandle) == SUCCESS)
        {
            php3_list_delete((*phandle)->value.lval);
        }
#else
        pval *phandle;
        if (_php3_hash_find(pThis->value.ht, "_handle_", sizeof("_handle_"), 
                            (void **)&phandle) == SUCCESS)

        {
            php3_list_delete(phandle->value.lval);
        }
#endif
    }

}
/* }}} */


/*=====================================================================
 *                 PHP function wrappers - lineObj class
 *====================================================================*/

/**********************************************************************
 *                     _phpms_build_line_object()
 *
 * handle_type is either le_msline_ref for an embedded object or
 * le_msline_new for a newly allocated object
 **********************************************************************/
static long _phpms_build_line_object(lineObj *pline, int handle_type,
                                      HashTable *list, pval *return_value)
{
    int line_id;

    if (pline == NULL)
        return 0;

    line_id = php3_list_insert(pline, handle_type);

    _phpms_object_init(return_value, line_id, php_line_class_functions,
                       PHP4_CLASS_ENTRY(line_class_entry_ptr));

    /* read-only properties */
    add_property_long(return_value, "numpoints", pline->numpoints);

    return line_id;
}


/**********************************************************************
 *                        ms_newLineObj()
 **********************************************************************/

/* {{{ proto lineObj ms_newLineObj()
   Create a new lineObj instance. */

DLEXPORT void php3_ms_line_new(INTERNAL_FUNCTION_PARAMETERS)
{
    lineObj *pNewLine;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

    if (ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    if ((pNewLine = lineObj_new()) == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
        RETURN_FALSE;
    }

    /* Return line object */
    _phpms_build_line_object(pNewLine, PHPMS_GLOBAL(le_msline_new), 
                              list, return_value);
}
/* }}} */

/**********************************************************************
 *                        line->project()
 **********************************************************************/

/* {{{ proto int line.project(projectionObj in, projectionObj out)
   Project the point. returns MS_SUCCESS/MS_FAILURE */

DLEXPORT void php3_ms_line_project(INTERNAL_FUNCTION_PARAMETERS)
{
    pval                *pThis, *pIn, *pOut;
    lineObj             *self;
    projectionObj       *poInProj;
    projectionObj       *poOutProj;
    int                 status=MS_FAILURE;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

     if (pThis == NULL ||
        getParameters(ht, 2, &pIn, &pOut) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (lineObj *)_phpms_fetch_handle2(pThis, 
                                           PHPMS_GLOBAL(le_msline_ref),
                                           PHPMS_GLOBAL(le_msline_new),
                                           list TSRMLS_CC);

    poInProj = 
        (projectionObj*)_phpms_fetch_handle(pIn, 
                                            PHPMS_GLOBAL(le_msprojection_new), 
                                            list TSRMLS_CC);
    poOutProj = 
        (projectionObj*)_phpms_fetch_handle(pOut, 
                                            PHPMS_GLOBAL(le_msprojection_new), 
                                            list TSRMLS_CC);
    if (self && poInProj && poOutProj &&
        (status = lineObj_project(self, poInProj, poOutProj)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }

    RETURN_LONG(status);
}
/* }}} */



/**********************************************************************
 *                        line->add()
 **********************************************************************/

/* {{{ proto int line.add(pointObj point)
   Adds a point to the end of a line */

DLEXPORT void php3_ms_line_add(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pPoint;
    lineObj     *self;
    pointObj    *poPoint;
    int         nRetVal=0;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif


    if (pThis == NULL ||
        getParameters(ht, 1, &pPoint) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (lineObj *)_phpms_fetch_handle2(pThis, 
                                           PHPMS_GLOBAL(le_msline_ref),
                                           PHPMS_GLOBAL(le_msline_new),
                                           list TSRMLS_CC);

    poPoint = (pointObj*)_phpms_fetch_handle2(pPoint,
                                              PHPMS_GLOBAL(le_mspoint_ref),
                                              PHPMS_GLOBAL(le_mspoint_new),
                                              list TSRMLS_CC);

    if (self && poPoint)
    {
        nRetVal = lineObj_add(self, poPoint);
        _phpms_set_property_long(pThis, "numpoints", self->numpoints, E_ERROR);
    }

    RETURN_LONG(nRetVal)
}
/* }}} */


/**********************************************************************
 *                        line->addXY()
 **********************************************************************/

/* {{{ proto int line.addXY(double x, double y, double m)
3rd argument m is used for Measured shape files. It is not mandatory.
   Adds a point to the end of a line */

DLEXPORT void php3_ms_line_addXY(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pX, *pY, *pM;
    lineObj     *self;
    pointObj    oPoint;
    int         nRetVal=0;
    int         nArgs = ARG_COUNT(ht);

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

     if (pThis == NULL ||
         (nArgs != 2 && nArgs != 3))
     {
         WRONG_PARAM_COUNT;
     }

    if (pThis == NULL ||
        getParameters(ht, nArgs, &pX, &pY, &pM) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_double(pX);
    convert_to_double(pY);

    oPoint.x = pX->value.dval;
    oPoint.y = pY->value.dval;
    if (nArgs == 3)
    {
        convert_to_double(pM); 
        oPoint.m = pM->value.dval;
    }
    else
      oPoint.m = 0.0;
 
    self = (lineObj *)_phpms_fetch_handle2(pThis, 
                                           PHPMS_GLOBAL(le_msline_ref),
                                           PHPMS_GLOBAL(le_msline_new),
                                           list TSRMLS_CC);

    if (self)
    {
        nRetVal = lineObj_add(self, &oPoint);
        _phpms_set_property_long(pThis, "numpoints", self->numpoints, E_ERROR);
    }

    RETURN_LONG(nRetVal)
}
/* }}} */



/**********************************************************************
 *                        line->point()
 **********************************************************************/

/* {{{ proto int line.point(int i)
   Returns point number i.  First point is number 0. */

DLEXPORT void php3_ms_line_point(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pIndex;
    lineObj     *self;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pIndex) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pIndex);

    self = (lineObj *)_phpms_fetch_handle2(pThis, 
                                           PHPMS_GLOBAL(le_msline_ref),
                                           PHPMS_GLOBAL(le_msline_new),
                                           list TSRMLS_CC);

    if (self==NULL || 
        pIndex->value.lval < 0 || pIndex->value.lval >= self->numpoints)
    {
        RETURN_FALSE;
    }

    /* Return reference to the specified point.  Reference is valid only
     * during the life of the lineObj that contains the point.
     */
    _phpms_build_point_object(&(self->point[pIndex->value.lval]), 
                                PHPMS_GLOBAL(le_mspoint_ref), 
                                list, return_value);
}
/* }}} */


/**********************************************************************
 *                        line->free()
 **********************************************************************/

/* {{{ proto int line.free()
   Destroys resources used by a line object */
DLEXPORT void php3_ms_line_free(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    lineObj *self;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif


    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (lineObj *)_phpms_fetch_handle(pThis, le_msline_new, list TSRMLS_CC);

    if (self)
    {
        /* Note: we do not have to call the object destructor...
         * removing the object from the resource list using php3_list_delete()
         * will also call the object destructor through the list destructor.
         */
#ifdef PHP4
        pval **phandle;
        if (zend_hash_find(pThis->value.obj.properties, "_handle_", 
                           sizeof("_handle_"), 
                           (void **)&phandle) == SUCCESS)
        {
            php3_list_delete((*phandle)->value.lval);
        }
#else
        pval *phandle;
        if (_php3_hash_find(pThis->value.ht, "_handle_", sizeof("_handle_"), 
                            (void **)&phandle) == SUCCESS)

        {
            php3_list_delete(phandle->value.lval);
        }
#endif
    }

}
/* }}} */

/*=====================================================================
 *                 PHP function wrappers - shapeObj class
 *====================================================================*/

/**********************************************************************
 *                     _phpms_build_shape_object()
 *
 * handle_type is either le_msshape_ref for an embedded object or
 * le_msshape_new for a newly allocated object
 **********************************************************************/
static long _phpms_build_shape_object(shapeObj *pshape, int handle_type,
                                      layerObj *pLayer,
                                      HashTable *list, pval *return_value)
{
    int     shape_id;
#ifdef PHP4
    pval        *new_obj_ptr;
#else
    pval        new_obj_param;  /* No, it's not a pval * !!! */
    pval        *new_obj_ptr;
    new_obj_ptr = &new_obj_param;
#endif

    if (pshape == NULL)
        return 0;

    shape_id = php3_list_insert(pshape, handle_type);

    _phpms_object_init(return_value, shape_id, php_shape_class_functions,
                       PHP4_CLASS_ENTRY(shape_class_entry_ptr));

    /* read-only properties */
    add_property_long(return_value, "numlines", pshape->numlines);
    add_property_long(return_value, "type",     pshape->type);
    add_property_long(return_value, "index",    pshape->index);
    add_property_long(return_value, "tileindex", pshape->tileindex);
    add_property_long(return_value, "classindex", pshape->classindex);
    add_property_long(return_value, "numvalues", pshape->numvalues);
    PHPMS_ADD_PROP_STR(return_value,"text",     pshape->text);

#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);
#endif
    _phpms_build_rect_object(&(pshape->bounds), PHPMS_GLOBAL(le_msrect_ref), 
                             list, new_obj_ptr);
    _phpms_add_property_object(return_value, "bounds", new_obj_ptr,E_ERROR);

    /* Package values as an associative array
     * For now we do this only for shapes returned from map layers, and not
     * for those from shapefileObj.
     */
    if (pLayer && 
        ((pshape->numvalues == pLayer->numitems) ||
         (pshape->numvalues == 0 && pLayer->numitems == -1)))
    {
        int i;
#ifdef PHP4
        MAKE_STD_ZVAL(new_obj_ptr);
#endif
        array_init(new_obj_ptr);
        for(i=0; i<pshape->numvalues; i++)
        {
            add_assoc_string(new_obj_ptr, 
                             pLayer->items[i], pshape->values[i], 1);
        }
        _phpms_add_property_object(return_value, "values", 
                                   new_obj_ptr, E_ERROR);
    }
    else if (pLayer)
    {
        php3_error(E_ERROR,
                   "Assertion failed, Could not set shape values: %d, %d",
                   pshape->numvalues, pLayer->numitems);
    }

    return shape_id;
}


/**********************************************************************
 *                        ms_newShapeObj()
 **********************************************************************/

/* {{{ proto shapeObj ms_newShapeObj()
   Create a new shapeObj instance. */

DLEXPORT void php3_ms_shape_new(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pType;
    shapeObj *pNewShape;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

    if (getParameters(ht, 1, &pType) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pType);

    if ((pNewShape = shapeObj_new(pType->value.lval)) == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
        RETURN_FALSE;
    }

    /* Return shape object */
    _phpms_build_shape_object(pNewShape, PHPMS_GLOBAL(le_msshape_new), NULL,
                              list, return_value);
}
/* }}} */


/**********************************************************************
 *                        shape->set()
 **********************************************************************/

/* {{{ proto int shape.set(string property_name, new_value)
   Set object property to a new value. Returns -1 on error. */

DLEXPORT void php3_ms_shape_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    shapeObj *self;
    pval   *pPropertyName, *pNewValue, *pThis;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (shapeObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_msshape_ref),
                                            PHPMS_GLOBAL(le_msshape_new),
                                            list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    IF_SET_STRING(     "text",         self->text)
    else IF_SET_LONG(  "classindex",   self->classindex)
    else if (strcmp( "numlines",  pPropertyName->value.str.val) == 0 ||
             strcmp( "type",      pPropertyName->value.str.val) == 0 ||
             strcmp( "index",     pPropertyName->value.str.val) == 0 ||
             strcmp( "tileindex", pPropertyName->value.str.val) == 0 ||
             strcmp( "numvalues", pPropertyName->value.str.val) == 0)
    {
        php3_error(E_ERROR,"Property '%s' is read-only and cannot be set.", 
                            pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }         
    else
    {
        php3_error(E_ERROR,"Property '%s' does not exist in this object.", 
                            pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }

    RETURN_LONG(0);
}
/* }}} */


/**********************************************************************
 *                        shape->project()
 **********************************************************************/

/* {{{ proto int shape.project(projectionObj in, projectionObj out)
   Project a Shape. Returns MS_SUCCESS/MS_FAILURE */

DLEXPORT void php3_ms_shape_project(INTERNAL_FUNCTION_PARAMETERS)
{
    pval                *pThis, *pIn, *pOut;
    shapeObj            *self;
    projectionObj       *poInProj;
    projectionObj       *poOutProj;
    int                 status=MS_FAILURE;

#ifdef PHP4
    HashTable   *list=NULL;
    pval   **pBounds;
#else
    pval   *pBounds;
#endif


#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pIn, &pOut) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

     self = (shapeObj *)_phpms_fetch_handle2(pThis, 
                                           PHPMS_GLOBAL(le_msshape_ref),
                                           PHPMS_GLOBAL(le_msshape_new),
                                           list TSRMLS_CC);
     poInProj = 
        (projectionObj*)_phpms_fetch_handle(pIn, 
                                            PHPMS_GLOBAL(le_msprojection_new), 
                                            list TSRMLS_CC);
    poOutProj = 
        (projectionObj*)_phpms_fetch_handle(pOut, 
                                            PHPMS_GLOBAL(le_msprojection_new), 
                                            list TSRMLS_CC);

    if (self && poInProj && poOutProj &&
        (status = shapeObj_project(self, poInProj, poOutProj)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }
    else
    {
#ifdef PHP4
         if (zend_hash_find(pThis->value.obj.properties, "bounds", 
                            sizeof("bounds"), (void **)&pBounds) == SUCCESS)
         {
             _phpms_set_property_double((*pBounds),"minx", self->bounds.minx, 
                                        E_ERROR);
             _phpms_set_property_double((*pBounds),"miny", self->bounds.miny, 
                                        E_ERROR);
             _phpms_set_property_double((*pBounds),"maxx", self->bounds.maxx, 
                                        E_ERROR);
             _phpms_set_property_double((*pBounds),"maxy", self->bounds.maxy, 
                                        E_ERROR);
         }
#else
         if (_php3_hash_find(pThis->value.ht, "bounds", sizeof("bounds"), 
                             (void **)&pBounds) == SUCCESS)
         {
             _phpms_set_property_double(pBounds,"minx", self->bounds.minx, 
                                        E_ERROR);
             _phpms_set_property_double(pBounds,"miny", self->bounds.miny, 
                                        E_ERROR);
             _phpms_set_property_double(pBounds,"maxx", self->bounds.maxx, 
                                        E_ERROR);
             _phpms_set_property_double(pBounds,"maxy", self->bounds.maxy, 
                                        E_ERROR);
         }
#endif
    }

    RETURN_LONG(status);
}
/* }}} */

/**********************************************************************
 *                        shape->add()
 **********************************************************************/

/* {{{ proto int shape.add(lineObj line)
   Adds a line (i.e. a part) to a shape */

DLEXPORT void php3_ms_shape_add(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pLine;
    shapeObj     *self;
    lineObj    *poLine;
    int         nRetVal=0;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pLine) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (shapeObj *)_phpms_fetch_handle2(pThis, 
                                           PHPMS_GLOBAL(le_msshape_ref),
                                           PHPMS_GLOBAL(le_msshape_new),
                                           list TSRMLS_CC);

    poLine = (lineObj*)_phpms_fetch_handle2(pLine,
                                            PHPMS_GLOBAL(le_msline_ref),
                                            PHPMS_GLOBAL(le_msline_new),
                                            list TSRMLS_CC);

    if (self && poLine)
    {
        nRetVal = shapeObj_add(self, poLine);
        _phpms_set_property_long(pThis, "numlines", self->numlines, E_ERROR);
    }

    RETURN_LONG(nRetVal)
}
/* }}} */


/**********************************************************************
 *                        shape->line()
 **********************************************************************/

/* {{{ proto int shape.line(int i)
   Returns line (part) number i.  First line is number 0. */

DLEXPORT void php3_ms_shape_line(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pIndex;
    shapeObj     *self;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pIndex) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pIndex);

    self = (shapeObj *)_phpms_fetch_handle2(pThis, 
                                           PHPMS_GLOBAL(le_msshape_ref),
                                           PHPMS_GLOBAL(le_msshape_new),
                                           list TSRMLS_CC);

    if (self==NULL || 
        pIndex->value.lval < 0 || pIndex->value.lval >= self->numlines)
    {
        RETURN_FALSE;
    }

    /* Return reference to the specified line.  Reference is valid only
     * during the life of the shapeObj that contains the line.
     */
    _phpms_build_line_object(&(self->line[pIndex->value.lval]), 
                                PHPMS_GLOBAL(le_msline_ref), 
                                list, return_value);
}
/* }}} */

/**********************************************************************
 *                        shape->draw()
 **********************************************************************/

/* {{{ proto int shape.draw(mapObj map, layerObj layer, imageObj img)
   Draws the individual shape using layer. Returns MS_SUCCESS/MS_FAILURE*/

DLEXPORT void php3_ms_shape_draw(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pMap, *pLayer, *pImg;
    shapeObj    *self;
    mapObj      *poMap;
    layerObj    *poLayer;
    imageObj    *im;
    int         nRetVal=MS_FAILURE;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 3, &pMap, &pLayer, &pImg) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (shapeObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_msshape_ref),
                                            PHPMS_GLOBAL(le_msshape_new),
                                            list TSRMLS_CC);

    poMap = (mapObj*)_phpms_fetch_handle(pMap, PHPMS_GLOBAL(le_msmap), list TSRMLS_CC);
    poLayer = (layerObj*)_phpms_fetch_handle(pLayer, PHPMS_GLOBAL(le_mslayer),
                                             list TSRMLS_CC);
    im = (imageObj *)_phpms_fetch_handle(pImg, PHPMS_GLOBAL(le_msimg), list TSRMLS_CC);

    if (self && 
        (nRetVal = shapeObj_draw(self, poMap, poLayer, im)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    RETURN_LONG(nRetVal);
}
/* }}} */


/**********************************************************************
 *                        shape->contains()
 **********************************************************************/
/* {{{ proto int shape.contains(pointObj pPoint)
   Returns true or false if the the point is in a polygone shape.*/

DLEXPORT void php3_ms_shape_contains(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pPoint;
    shapeObj     *self;
    pointObj    *poPoint;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pPoint) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (shapeObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_msshape_ref),
                                            PHPMS_GLOBAL(le_msshape_new),
                                            list TSRMLS_CC);
     poPoint = (pointObj *)_phpms_fetch_handle2(pPoint,
                                               PHPMS_GLOBAL(le_mspoint_ref),
                                               PHPMS_GLOBAL(le_mspoint_new),
                                               list TSRMLS_CC);
    if (self==NULL || poPoint == NULL || !shapeObj_contains(self, poPoint))
      RETURN_FALSE;

    RETURN_TRUE;
}
/* }}} */

/**********************************************************************
 *                        shape->intersects()
 **********************************************************************/
/* {{{ proto int shape.intersects(shapeObj pShape)
   Returns true if the two shapes intersect. Else false.*/

DLEXPORT void php3_ms_shape_intersects(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pShape;
    shapeObj     *self;
    shapeObj    *poShape;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pShape) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (shapeObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_msshape_ref),
                                            PHPMS_GLOBAL(le_msshape_new),
                                            list TSRMLS_CC);
    poShape = 
    (shapeObj *)_phpms_fetch_handle2(pShape, 
                                     PHPMS_GLOBAL(le_msshape_ref),
                                     PHPMS_GLOBAL(le_msshape_new),
                                     list TSRMLS_CC);
    
    if (self==NULL || poShape == NULL || !shapeObj_intersects(self, poShape))
      RETURN_FALSE;

    RETURN_TRUE;
}
/* }}} */

/**********************************************************************
 *                        shape->getValue()
 **********************************************************************/
/* {{{ proto string shape.getValue(layerObj layer, string fieldName)
   Returns value for specified field name. */

DLEXPORT void php3_ms_shape_getvalue(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis, *pLayer, *pFieldName;
    shapeObj    *self;
    layerObj    *poLayer;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pLayer, &pFieldName) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (shapeObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_msshape_ref),
                                            PHPMS_GLOBAL(le_msshape_new),
                                            list TSRMLS_CC);

    poLayer = (layerObj*)_phpms_fetch_handle(pLayer, PHPMS_GLOBAL(le_mslayer),
                                             list TSRMLS_CC);
    
    if (self && poLayer && self->numvalues == poLayer->numitems)
    {
        int i;
        for(i=0; i<poLayer->numitems; i++)
        {
            if (strcasecmp(poLayer->items[i], pFieldName->value.str.val)==0)
            {
                RETURN_STRING(self->values[i], 1);
            }
        }
    }

    RETURN_STRING("", 1);
}
/* }}} */


/**********************************************************************
 *                        shape->getpointusingmeasure()
 **********************************************************************/
/* {{{ proto int shape.getpointusingmeasure(double m)
   Given a shape and a nmesure, return a point object containing the XY
   location corresponding to the measure */

DLEXPORT void php3_ms_shape_getpointusingmeasure(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis, *pMeasure;
    shapeObj     *self = NULL;
    pointObj    *point = NULL;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pMeasure) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_double(pMeasure);

    self = (shapeObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_msshape_ref),
                                            PHPMS_GLOBAL(le_msshape_new),
                                            list TSRMLS_CC);
    if (self == NULL)
      RETURN_FALSE;

    point = shapeObj_getpointusingmeasure(self, pMeasure->value.dval);
    if (point == NULL)
       RETURN_FALSE;
        
    _phpms_build_point_object(point, 
                              PHPMS_GLOBAL(le_mspoint_ref), 
                              list, return_value);
}


/**********************************************************************
 *                        shape->getmeasureusingpoint()
 **********************************************************************/
/* {{{ proto int shape.getpointusingmeasure(pointObject point)
   Given a shape and a point object, return a point object containing the XY
   location of the intersection between the point and the shape. The point
   return contains also the extrapolated M value at the intersection. */

DLEXPORT void php3_ms_shape_getmeasureusingpoint(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis, *pPoint;
    shapeObj     *self = NULL;
    pointObj    *point = NULL;
    pointObj    *intersection = NULL;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pPoint) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    point = (pointObj *)_phpms_fetch_handle2(pPoint,
                                             PHPMS_GLOBAL(le_mspoint_ref),
                                             PHPMS_GLOBAL(le_mspoint_new),
                                             list TSRMLS_CC);
    if (point == NULL)
      RETURN_FALSE;


    self = (shapeObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_msshape_ref),
                                            PHPMS_GLOBAL(le_msshape_new),
                                            list TSRMLS_CC);
    if (self == NULL)
      RETURN_FALSE;

    intersection = shapeObj_getmeasureusingpoint(self, point);
    if (intersection == NULL)
      RETURN_FALSE;

     _phpms_build_point_object(intersection, 
                              PHPMS_GLOBAL(le_mspoint_ref), 
                              list, return_value);
}
     
/**********************************************************************
 *                        shape->free()
 **********************************************************************/

/* {{{ proto int point.free()
   Destroys resources used by a point object */
DLEXPORT void php3_ms_shape_free(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    shapeObj *self;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif


    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (shapeObj *)_phpms_fetch_handle(pThis, le_msshape_new, list TSRMLS_CC);

    if (self)
    {
        /* Note: we do not have to call the object destructor...
         * removing the object from the resource list using php3_list_delete()
         * will also call the object destructor through the list destructor.
         */
#ifdef PHP4
        pval **phandle;
        if (zend_hash_find(pThis->value.obj.properties, "_handle_", 
                           sizeof("_handle_"), 
                           (void **)&phandle) == SUCCESS)
        {
            php3_list_delete((*phandle)->value.lval);
        }
#else
        pval *phandle;
        if (_php3_hash_find(pThis->value.ht, "_handle_", sizeof("_handle_"), 
                            (void **)&phandle) == SUCCESS)

        {
            php3_list_delete(phandle->value.lval);
        }
#endif
    }

}
/* }}} */


/*=====================================================================
 *                 PHP function wrappers - webObj class
 *====================================================================*/
/**********************************************************************
 *                     _phpms_build_web_object()
 **********************************************************************/
static long _phpms_build_web_object(webObj *pweb, 
                                    HashTable *list, pval *return_value)
{
    int         web_id;
#ifdef PHP4
    pval        *new_obj_ptr;
#else
    pval        new_obj_param;  /* No, it's not a pval * !!! */
    pval        *new_obj_ptr;
    new_obj_ptr = &new_obj_param;
#endif

    if (pweb == NULL)
        return 0;

    web_id = php3_list_insert(pweb, PHPMS_GLOBAL(le_msweb));

    _phpms_object_init(return_value, web_id, php_web_class_functions,
                       PHP4_CLASS_ENTRY(web_class_entry_ptr));

    PHPMS_ADD_PROP_STR(return_value,  "log",            pweb->log);
    PHPMS_ADD_PROP_STR(return_value,  "imagepath",      pweb->imagepath);
    PHPMS_ADD_PROP_STR(return_value,  "template",       pweb->template);
    PHPMS_ADD_PROP_STR(return_value,  "imageurl",       pweb->imageurl);
    PHPMS_ADD_PROP_STR(return_value,  "header",         pweb->header);
    PHPMS_ADD_PROP_STR(return_value,  "footer",         pweb->footer);
    PHPMS_ADD_PROP_STR(return_value,  "empty",          pweb->empty);
    PHPMS_ADD_PROP_STR(return_value,  "error",          pweb->error);
    PHPMS_ADD_PROP_STR(return_value,  "mintemplate",    pweb->mintemplate);
    PHPMS_ADD_PROP_STR(return_value,  "maxtemplate",    pweb->maxtemplate);
    add_property_double(return_value,   "minscale",       pweb->minscale);
    add_property_double(return_value,   "maxscale",       pweb->maxscale);
    
#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);
#endif
    _phpms_build_rect_object(&(pweb->extent), PHPMS_GLOBAL(le_msrect_ref), 
                             list, new_obj_ptr);
    _phpms_add_property_object(return_value, "extent", new_obj_ptr,E_ERROR);

    return web_id;
}

/**********************************************************************
 *                        web->set()
 **********************************************************************/

/* {{{ proto int web.set(string property_name, new_value)
   Set object property to a new value. Returns -1 on error. */


DLEXPORT void php3_ms_web_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    webObj *self;
    pval   *pPropertyName, *pNewValue, *pThis;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (webObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msweb),
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    
    IF_SET_STRING(       "log",         self->log)
    else IF_SET_STRING(  "imagepath",   self->imagepath)
    else IF_SET_STRING(  "template",   self->template) 
    else IF_SET_STRING(  "imageurl",   self->imageurl)
    else IF_SET_STRING(  "header",   self->header)
    else IF_SET_STRING(  "footer",   self->footer)
    else IF_SET_STRING(  "mintemplate",   self->mintemplate) 
    else IF_SET_STRING(  "maxtemplate",   self->maxtemplate) 
    else IF_SET_LONG(    "minscale",   self->minscale)
    else IF_SET_LONG(    "maxscale",   self->maxscale)  
    else if (strcmp( "empty", pPropertyName->value.str.val) == 0 ||
             strcmp( "error",  pPropertyName->value.str.val) == 0 ||
             strcmp( "extent", pPropertyName->value.str.val) == 0)
    {
        php3_error(E_ERROR,"Property '%s' is read-only and cannot be set.", 
                            pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }         
    else
    {
        php3_error(E_ERROR,"Property '%s' does not exist in this object.", 
                   pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }

    RETURN_LONG(0);
}           



/*=====================================================================
 *                 PHP function wrappers - rectObj class
 *====================================================================*/
/**********************************************************************
 *                     _phpms_build_rect_object()
 * handle_type is either le_msrect_ref for an embedded object or
 * le_msrect_new for a newly allocated object
 **********************************************************************/
static long _phpms_build_rect_object(rectObj *prect, int handle_type, 
                                     HashTable *list, pval *return_value)
{
    int rect_id;

    if (prect == NULL)
      return 0;

    rect_id = php3_list_insert(prect, handle_type);

    _phpms_object_init(return_value, rect_id, php_rect_class_functions,
                       PHP4_CLASS_ENTRY(rect_class_entry_ptr));

    add_property_double(return_value,   "minx",       prect->minx);
    add_property_double(return_value,   "miny",       prect->miny);
    add_property_double(return_value,   "maxx",       prect->maxx);
    add_property_double(return_value,   "maxy",       prect->maxy);

    return rect_id;
}


/**********************************************************************
 *                        ms_newRectObj()
 **********************************************************************/

/* {{{ proto rectObj ms_newRectObj()
   Create a new rectObj instance. */

DLEXPORT void php3_ms_rect_new(INTERNAL_FUNCTION_PARAMETERS)
{
    rectObj *pNewRect;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

    if (ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    if ((pNewRect = rectObj_new()) == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
        RETURN_FALSE;
    }

    /* Return rect object */
    _phpms_build_rect_object(pNewRect, PHPMS_GLOBAL(le_msrect_new), 
                             list, return_value);
}
/* }}} */


/**********************************************************************
 *                        rect->project()
 **********************************************************************/

/* {{{ proto int rect.project(projectionObj in, projectionObj out)
   Project a Rect object Returns MS_SUCCESS/MS_FAILURE */

DLEXPORT void php3_ms_rect_project(INTERNAL_FUNCTION_PARAMETERS)
{
    pval                *pThis, *pIn, *pOut;
    rectObj             *self;
    projectionObj       *poInProj;
    projectionObj       *poOutProj;
    int                 status=MS_FAILURE;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pIn, &pOut) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (rectObj *)_phpms_fetch_handle2(pThis, PHPMS_GLOBAL(le_msrect_ref),
                                           PHPMS_GLOBAL(le_msrect_new), list TSRMLS_CC);
    poInProj = 
        (projectionObj*)_phpms_fetch_handle(pIn, 
                                            PHPMS_GLOBAL(le_msprojection_new), 
                                            list TSRMLS_CC);
    poOutProj = 
        (projectionObj*)_phpms_fetch_handle(pOut, 
                                            PHPMS_GLOBAL(le_msprojection_new), 
                                            list TSRMLS_CC);

    if (self && poInProj && poOutProj &&
        (status = rectObj_project(self, poInProj, poOutProj)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_WARNING);
    }
    else
    {
        // Update the members of the PHP wrapper object.
        _phpms_set_property_double(pThis, "minx", self->minx, E_ERROR);
        _phpms_set_property_double(pThis, "miny", self->miny, E_ERROR);
        _phpms_set_property_double(pThis, "maxx", self->maxx, E_ERROR);
        _phpms_set_property_double(pThis, "maxy", self->maxy, E_ERROR);
    }

    RETURN_LONG(status);
}
/* }}} */

/**********************************************************************
 *                        rect->set()
 **********************************************************************/

/* {{{ proto int rect.set(string property_name, new_value)
   Set object property to a new value. Returns -1 on error. */

DLEXPORT void php3_ms_rect_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    rectObj *self;
    pval   *pPropertyName, *pNewValue, *pThis;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (rectObj *)_phpms_fetch_handle2(pThis, PHPMS_GLOBAL(le_msrect_ref),
                                           PHPMS_GLOBAL(le_msrect_new), list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    IF_SET_DOUBLE(        "minx",   self->minx)
    else IF_SET_DOUBLE(   "miny",   self->miny)  
    else IF_SET_DOUBLE(   "maxx",   self->maxx) 
    else IF_SET_DOUBLE(   "maxy",   self->maxy)           
    else
    {
        php3_error(E_ERROR,"Property '%s' does not exist in this object.", 
                            pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }
         
    RETURN_LONG(0);
}           

/**********************************************************************
 *                        rect->setextent()
 **********************************************************************/

/* {{{ proto int rect.setextent(xmin, ymin, xmax, ymax)
   Set object property using four values.
*/
DLEXPORT void php3_ms_rect_setExtent(INTERNAL_FUNCTION_PARAMETERS)
{
    rectObj *self;
    pval   *pXMin, *pYMin, *pXMax, *pYMax, *pThis;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 4, &pXMin, &pYMin, &pXMax, &pYMax) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (rectObj *)_phpms_fetch_handle2(pThis, 
                                           PHPMS_GLOBAL(le_msrect_ref),
                                           PHPMS_GLOBAL(le_msrect_new),
                                           list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_double(pXMin);
    convert_to_double(pYMin);
    convert_to_double(pXMax);
    convert_to_double(pYMax);
    
    self->minx = pXMin->value.dval;
    self->miny = pYMin->value.dval;
    self->maxx = pXMax->value.dval;
    self->maxy = pYMax->value.dval;

    _phpms_set_property_double(pThis, "minx", self->minx, E_ERROR);
    _phpms_set_property_double(pThis, "miny", self->miny, E_ERROR);
    _phpms_set_property_double(pThis, "maxx", self->maxx, E_ERROR);
    _phpms_set_property_double(pThis, "maxy", self->maxy, E_ERROR);

    RETURN_LONG(0);
}
/* }}} */


/**********************************************************************
 *                        rect->draw()
 **********************************************************************/

/* {{{ proto int rect.draw(mapObj map, layerObj layer, imageObj img, string class_name, string text)
   Draws the individual rect using layer. Returns MS_SUCCESS/MS_FAILURE. */

DLEXPORT void php3_ms_rect_draw(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pMap, *pLayer, *pImg, *pClass, *pText;
    rectObj    *self;
    mapObj      *poMap;
    layerObj    *poLayer;
    imageObj    *im;
    int         nRetVal=MS_FAILURE;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif


    if (pThis == NULL ||
        getParameters(ht, 5, &pMap, &pLayer, &pImg, &pClass, &pText) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pClass);
    convert_to_string(pText);

    self = (rectObj *)_phpms_fetch_handle2(pThis, 
                                            PHPMS_GLOBAL(le_msrect_ref),
                                            PHPMS_GLOBAL(le_msrect_new),
                                            list TSRMLS_CC);

    poMap = (mapObj*)_phpms_fetch_handle(pMap, PHPMS_GLOBAL(le_msmap), list TSRMLS_CC);
    poLayer = (layerObj*)_phpms_fetch_handle(pLayer, PHPMS_GLOBAL(le_mslayer),
                                             list TSRMLS_CC);
    im = (imageObj *)_phpms_fetch_handle(pImg, PHPMS_GLOBAL(le_msimg), list TSRMLS_CC);

    if (self &&
        (nRetVal = rectObj_draw(self, poMap, poLayer, im, 
                                pClass->value.lval, 
                                pText->value.str.val)) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }

    RETURN_LONG(nRetVal)
}
/* }}} */


/**********************************************************************
 *                        rect->fit()
 **********************************************************************/

/* {{{ proto int rect.fit(int nWidth, int nHeight)
   Adjust extents of the rectangle to fit the width/height specified. */

DLEXPORT void php3_ms_rect_fit(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis, *pWidth, *pHeight;
    rectObj     *self;
    double      dfRetVal=0.0;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pWidth, &pHeight) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pWidth);
    convert_to_long(pHeight);

    self = (rectObj *)_phpms_fetch_handle2(pThis, 
                                           PHPMS_GLOBAL(le_msrect_ref),
                                           PHPMS_GLOBAL(le_msrect_new),
                                           list TSRMLS_CC);

    if (self != NULL)
      dfRetVal = rectObj_fit(self, pWidth->value.lval, pHeight->value.lval);

    RETURN_DOUBLE(dfRetVal)
}
/* }}} */

/**********************************************************************
 *                        rect->free()
 **********************************************************************/

/* {{{ proto int rect.free()
   Destroys resources used by a rect object */
DLEXPORT void php3_ms_rect_free(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    rectObj *self;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif


    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (rectObj *)_phpms_fetch_handle(pThis, le_msrect_new, list TSRMLS_CC);

    if (self)
    {
        /* Note: we do not have to call the object destructor...
         * removing the object from the resource list using php3_list_delete()
         * will also call the object destructor through the list destructor.
         */
#ifdef PHP4
        pval **phandle;
        if (zend_hash_find(pThis->value.obj.properties, "_handle_", 
                           sizeof("_handle_"), 
                           (void **)&phandle) == SUCCESS)
        {
            php3_list_delete((*phandle)->value.lval);
        }
#else
        pval *phandle;
        if (_php3_hash_find(pThis->value.ht, "_handle_", sizeof("_handle_"), 
                            (void **)&phandle) == SUCCESS)

        {
            php3_list_delete(phandle->value.lval);
        }
#endif
    }

}
/* }}} */


/*=====================================================================
 *                 PHP function wrappers - referneceMapObj class
 *====================================================================*/
/**********************************************************************
 *                     _phpms_build_referenceMap_object()
 **********************************************************************/
static long _phpms_build_referenceMap_object(referenceMapObj *preference, 
                                    HashTable *list, pval *return_value)
{
    int         reference_id;
#ifdef PHP4
    pval        *new_obj_ptr;
#else
    pval        new_obj_param;  /* No, it's not a pval * !!! */
    pval        *new_obj_ptr;
    new_obj_ptr = &new_obj_param;
#endif

    if (preference == NULL)
        return 0;

    reference_id = php3_list_insert(preference, PHPMS_GLOBAL(le_msrefmap));

    _phpms_object_init(return_value, reference_id, 
                       php_reference_class_functions,
                       PHP4_CLASS_ENTRY(reference_class_entry_ptr));

    PHPMS_ADD_PROP_STR(return_value,  "image",   preference->image);
    add_property_long(return_value,   "width",  preference->width);
    add_property_long(return_value,   "height",  preference->height);
    add_property_long(return_value,   "status",  preference->status);
    
#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);
#endif
    _phpms_build_rect_object(&(preference->extent), 
                             PHPMS_GLOBAL(le_msrect_ref),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "extent", new_obj_ptr, E_ERROR);

#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);
#endif
    _phpms_build_color_object(&(preference->color),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "color", new_obj_ptr, E_ERROR);

#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);
#endif
    _phpms_build_color_object(&(preference->outlinecolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "outlinecolor", 
                               new_obj_ptr, E_ERROR);

    return reference_id;
}


/**********************************************************************
 *                        referenceMap->set()
 **********************************************************************/

/* {{{ proto int web.set(string property_name, new_value)
   Set object property to a new value. Returns -1 on error. */

DLEXPORT void php3_ms_referenceMap_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    referenceMapObj *self;
    pval   *pPropertyName, *pNewValue, *pThis;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (referenceMapObj *)_phpms_fetch_handle(pThis, 
                                                  PHPMS_GLOBAL(le_msrefmap),
                                                  list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    
    IF_SET_STRING(       "image",    self->image)
    else IF_SET_LONG(    "width",    self->width)
    else IF_SET_LONG(    "height",   self->height)
    else IF_SET_LONG(    "status",   self->status) 
    else if (strcmp( "extent", pPropertyName->value.str.val) == 0 ||
             strcmp( "color",  pPropertyName->value.str.val) == 0 ||
             strcmp( "outlinecolor", pPropertyName->value.str.val) == 0)
    {
        php3_error(E_ERROR,"Property '%s' is an object and cannot be set using set().  Use the %s object's methods instead.", 
                            pPropertyName->value.str.val, 
                            pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }                  
    else
    {
        php3_error(E_ERROR,"Property '%s' does not exist in this object.", 
                   pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }

    RETURN_LONG(0);
}           
/* }}} */


/*=====================================================================
 *                 PHP function wrappers - shapefileObj class
 *====================================================================*/


/**********************************************************************
 *                     _phpms_build_shapefile_object()
 **********************************************************************/
static long _phpms_build_shapefile_object(shapefileObj *pshapefile,
                                          HashTable *list, pval *return_value)
{
    int shapefile_id;
#ifdef PHP4
    pval        *new_obj_ptr;
#else
    pval        new_obj_param;  /* No, it's not a pval * !!! */
    pval        *new_obj_ptr;
    new_obj_ptr = &new_obj_param;
#endif

    if (pshapefile == NULL)
        return 0;

    shapefile_id = php3_list_insert(pshapefile, PHPMS_GLOBAL(le_msshapefile));

    _phpms_object_init(return_value, shapefile_id, 
                       php_shapefile_class_functions,
                       PHP4_CLASS_ENTRY(shapefile_class_entry_ptr));

    /* read-only properties */
    add_property_long(return_value, "numshapes",  pshapefile->numshapes);
    add_property_long(return_value, "type",       pshapefile->type);
    PHPMS_ADD_PROP_STR(return_value,"source",     pshapefile->source);

#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);
#endif
    _phpms_build_rect_object(&(pshapefile->bounds), 
                             PHPMS_GLOBAL(le_msrect_ref), list, new_obj_ptr);
    _phpms_add_property_object(return_value, "bounds", new_obj_ptr,E_ERROR);

    return shapefile_id;
}

/**********************************************************************
 *                        ms_newShapefileObj()
 **********************************************************************/

/* {{{ proto shapefileObj ms_newShapefileObj(string filename, int type)
   Opens a shapefile and returns a new object to deal with it. Filename should be passed with no extension. */

DLEXPORT void php3_ms_shapefile_new(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pFname, *pType;
    shapefileObj *pNewObj = NULL;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

    if (getParameters(ht, 2, &pFname, &pType) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    /* Attempt to open the file 
     */
    convert_to_string(pFname);
    convert_to_long(pType);
    pNewObj = shapefileObj_new(pFname->value.str.val, pType->value.lval);
    if (pNewObj == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "Failed to open shapefile %s", 
                            pFname->value.str.val);
        RETURN_FALSE;
    }

    /* Create a PHP object, add all shapefileObj methods, etc.
     */
    _phpms_build_shapefile_object(pNewObj, list, return_value);
}
/* }}} */


/**********************************************************************
 *                        shapefile->addShape()
 **********************************************************************/

/* {{{ proto int shapefile.addShape(shapeObj shape)
   Appends a shape to an open shapefile. */

DLEXPORT void php3_ms_shapefile_addshape(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pShape;
    shapefileObj *self;
    shapeObj    *poShape;
    int         nRetVal=0;
    
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pShape) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (shapefileObj *)_phpms_fetch_handle(pThis, 
                                               PHPMS_GLOBAL(le_msshapefile),
                                               list TSRMLS_CC);

    poShape = (shapeObj*)_phpms_fetch_handle2(pShape,
                                              PHPMS_GLOBAL(le_msshape_ref),
                                              PHPMS_GLOBAL(le_msshape_new),
                                              list TSRMLS_CC);

    if (self && poShape)
        nRetVal = shapefileObj_add(self, poShape);

    RETURN_LONG(nRetVal)
}
/* }}} */


/**********************************************************************
 *                        shapefile->addPoint()
 **********************************************************************/

/* {{{ proto int shapefile.addPoint(pointObj point)
   Appends a point to a poin layer. */

DLEXPORT void php3_ms_shapefile_addpoint(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pPoint;
    shapefileObj *self;
    pointObj    *poPoint;
    int         nRetVal=0;
    
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pPoint) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (shapefileObj *)_phpms_fetch_handle(pThis, 
                                               PHPMS_GLOBAL(le_msshapefile),
                                               list TSRMLS_CC);

    poPoint = (pointObj*)_phpms_fetch_handle2(pPoint,
                                              PHPMS_GLOBAL(le_mspoint_ref),
                                              PHPMS_GLOBAL(le_mspoint_new),
                                              list TSRMLS_CC);

    if (self && poPoint)
        nRetVal = shapefileObj_addPoint(self, poPoint);

    RETURN_LONG(nRetVal)
}
/* }}} */


/**********************************************************************
 *                        shapefile->getShape()
 **********************************************************************/

/* {{{ proto int shapefile.getShape(int i)
   Retrieve shape by index. */

DLEXPORT void php3_ms_shapefile_getshape(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pIndex;
    shapefileObj *self;
    shapeObj    *poShape;

#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pIndex) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pIndex);

    self = (shapefileObj *)_phpms_fetch_handle(pThis, 
                                               PHPMS_GLOBAL(le_msshapefile),
                                               list TSRMLS_CC);

    /* Create a new shapeObj to hold the result 
     * Note that the type used to create the shape (MS_NULL) does not matter
     * at this point since it will be set by SHPReadShape().
     */
    if ((poShape = shapeObj_new(MS_SHAPE_NULL)) == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "Failed creating new shape (out of memory?)");
        RETURN_FALSE;
    }

    /* Read from the file */
    if (self == NULL || 
        shapefileObj_get(self, pIndex->value.lval, poShape) != 0)
    {
        shapeObj_destroy(poShape);
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "Failed reading shape %d.", pIndex->value.lval);
        RETURN_FALSE;
    }

    /* Return shape object */
    _phpms_build_shape_object(poShape, PHPMS_GLOBAL(le_msshape_new), NULL,
                              list, return_value);
}
/* }}} */


/**********************************************************************
 *                        shapefile->getShape()
 **********************************************************************/

/* {{{ proto int shapefile.getPoint(int i)
   Retrieve a point by index. */

DLEXPORT void php3_ms_shapefile_getpoint(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pIndex;
    shapefileObj *self;
    pointObj    *poPoint;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pIndex) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pIndex);

    self = (shapefileObj *)_phpms_fetch_handle(pThis, 
                                               PHPMS_GLOBAL(le_msshapefile),
                                               list TSRMLS_CC);

    /* Create a new PointObj to hold the result */
    if ((poPoint = pointObj_new()) == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "Failed creating new point (out of memory?)");
        RETURN_FALSE;
    }

    /* Read from the file */
    if (self == NULL || 
        shapefileObj_getPoint(self, pIndex->value.lval, poPoint) != 0)
    {
        pointObj_destroy(poPoint);
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "Failed reading point %d.", pIndex->value.lval);
        RETURN_FALSE;
    }

    /* Return point object */
    _phpms_build_point_object(poPoint, PHPMS_GLOBAL(le_mspoint_new),
                              list, return_value);
}
/* }}} */

/**********************************************************************
 *                        shapefile->gettransformed()
 **********************************************************************/

/* {{{ proto int shapefile.getTransformed(mapObj map, int i)
   Retrieve shape by index. */

DLEXPORT void php3_ms_shapefile_gettransformed(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pIndex, *pMap;
    shapefileObj *self;
    shapeObj    *poShape;
    mapObj      *poMap;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pMap, &pIndex) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pIndex);

    self = (shapefileObj *)_phpms_fetch_handle(pThis, 
                                               PHPMS_GLOBAL(le_msshapefile),
                                               list TSRMLS_CC);

    poMap = (mapObj*)_phpms_fetch_handle(pMap, PHPMS_GLOBAL(le_msmap), list TSRMLS_CC);

    /* Create a new shapeObj to hold the result 
     * Note that the type used to create the shape (MS_NULL) does not matter
     * at this point since it will be set by SHPReadShape().
     */
    if ((poShape = shapeObj_new(MS_SHAPE_NULL)) == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "Failed creating new shape (out of memory?)");
        RETURN_FALSE;
    }

    /* Read from the file */
    if (self == NULL || 
        shapefileObj_getTransformed(self, poMap, 
                                    pIndex->value.lval, poShape) != 0)
    {
        shapeObj_destroy(poShape);
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "Failed reading shape %d.", pIndex->value.lval);
        RETURN_FALSE;
    }

    /* Return shape object */
    _phpms_build_shape_object(poShape, PHPMS_GLOBAL(le_msshape_new), NULL,
                              list, return_value);
}
/* }}} */

/**********************************************************************
 *                        shapefile->getExtent()
 **********************************************************************/

/* {{{ proto int shapefile.getExtent(int i)
   Retrieve a shape's bounding box by index. */

DLEXPORT void php3_ms_shapefile_getextent(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis, *pIndex;
    shapefileObj *self;
    rectObj      *poRect;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 1, &pIndex) !=SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_long(pIndex);

    self = (shapefileObj *)_phpms_fetch_handle(pThis, 
                                               PHPMS_GLOBAL(le_msshapefile),
                                               list TSRMLS_CC);

    if (self == NULL)
    {
        RETURN_FALSE;
    }

    /* Create a new rectObj to hold the result */
    if ((poRect = rectObj_new()) == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "Failed creating new rectObj (out of memory?)");
        RETURN_FALSE;
    }

    /* Read from the file 
     * shapefileObj_getExtent() has no return value!  How do we catch errors?
     */
    shapefileObj_getExtent(self, pIndex->value.lval, poRect);

    /* Return rectObj */
    _phpms_build_rect_object(poRect, PHPMS_GLOBAL(le_msrect_new), 
                              list, return_value);
}
/* }}} */

/**********************************************************************
 *                        shapeFileObj->free()
 **********************************************************************/

/* {{{ proto int shapefile.free()
   Destroys resources used by a shapeFileObj object */

DLEXPORT void php3_ms_shapefile_free(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    shapefileObj *self;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (shapefileObj*)_phpms_fetch_handle(pThis, le_msshapefile, list TSRMLS_CC);
    if (self)
    {
        /* Note: we do not have to call the object destructor...
         * removing the object from the resource list using php3_list_delete()
         * will also call the object destructor through the list destructor.
         */
#ifdef PHP4
        pval **phandle;
        if (zend_hash_find(pThis->value.obj.properties, "_handle_", 
                           sizeof("_handle_"), 
                           (void **)&phandle) == SUCCESS)
        {
            php3_list_delete((*phandle)->value.lval);
        }
#else
        pval *phandle;
        if (_php3_hash_find(pThis->value.ht, "_handle_", sizeof("_handle_"), 
                            (void **)&phandle) == SUCCESS)

        {
            php3_list_delete(phandle->value.lval);
        }
#endif
    }
}
/* }}} */


/*=====================================================================
 *                 PHP function wrappers - resultCacheMemberObj class
 *====================================================================*/

/**********************************************************************
 *                     _phpms_build_resultCacheMember_object()
 **********************************************************************/
static long _phpms_build_resultcachemember_object(resultCacheMemberObj *pRes,
                                                  HashTable *list TSRMLS_DC, 
                                                  pval *return_value)
{
    if (pRes == NULL)
        return 0;

    object_init(return_value);

    /* Note: Contrary to most other object classes, this one does not
     *       need to keep a handle on the internal structure since all
     *       members are read-only and thus there is no set() method.
     */

    /* read-only properties */
    add_property_long(return_value,   "shapeindex", pRes->shapeindex);
    add_property_long(return_value,   "tileindex",  pRes->tileindex);
    add_property_long(return_value,   "classindex", pRes->classindex);

    return 0;
}


/*=====================================================================
 *                 PHP function wrappers - projection class
 *====================================================================*/
/**********************************************************************
 *                     _phpms_build_projection_object()
**********************************************************************/
static long _phpms_build_projection_object(projectionObj *pproj, 
                                           int handle_type, 
                                           HashTable *list, pval *return_value)
{
    int projection_id;

    if (pproj == NULL)
      return 0;

    projection_id = php3_list_insert(pproj, handle_type);

    _phpms_object_init(return_value, projection_id, 
                       php_projection_class_functions,
                       PHP4_CLASS_ENTRY(projection_class_entry_ptr));

    return projection_id;
}
 
/**********************************************************************
 *                        ms_newProjectionObj()
 **********************************************************************/

/* {{{ proto projectionObj ms_newProjectionObj()
   Create a new projectionObj instance. */

DLEXPORT void php3_ms_projection_new(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pString;
    projectionObj *pNewProj = NULL;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

    if (getParameters(ht, 1, &pString) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pString);

    if ((pNewProj = projectionObj_new(pString->value.str.val)) == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
        RETURN_FALSE;
    }

    /* Return rect object */
    _phpms_build_projection_object(pNewProj, 
                                   PHPMS_GLOBAL(le_msprojection_new), 
                                   list, return_value);
}
/* }}} */

/**********************************************************************
 *                        projection->free()
 **********************************************************************/

/* {{{ proto int projection.free()
   Destroys resources used by a projection object */
DLEXPORT void php3_ms_projection_free(INTERNAL_FUNCTION_PARAMETERS)
{
    pval *pThis;
    projectionObj *self;


#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif


    if (pThis == NULL ||
        ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (projectionObj *)_phpms_fetch_handle(pThis, 
                                                le_msprojection_new, list TSRMLS_CC);

    if (self)
    {
        /* Note: we do not have to call the object destructor...
         * removing the object from the resource list using php3_list_delete()
         * will also call the object destructor through the list destructor.
         */
#ifdef PHP4
        pval **phandle;
        if (zend_hash_find(pThis->value.obj.properties, "_handle_", 
                           sizeof("_handle_"), 
                           (void **)&phandle) == SUCCESS)
        {
            php3_list_delete((*phandle)->value.lval);
        }
#else
        pval *phandle;
        if (_php3_hash_find(pThis->value.ht, "_handle_", sizeof("_handle_"), 
                            (void **)&phandle) == SUCCESS)

        {
            php3_list_delete(phandle->value.lval);
        }
#endif
    }

}
/* }}} */


/*=====================================================================
 *                 PHP function wrappers - scalebarObj class
 *====================================================================*/
/**********************************************************************
 *                     _phpms_build_scalebar_object()
 **********************************************************************/
static long _phpms_build_scalebar_object(scalebarObj *pscalebar, 
                                         HashTable *list, pval *return_value)
{
    int         scalebar_id;
#ifdef PHP4
    pval        *new_obj_ptr;
#else
    pval        new_obj_param;  /* No, it's not a pval * !!! */
    pval        *new_obj_ptr;
    new_obj_ptr = &new_obj_param;
#endif

    if (pscalebar == NULL)
        return 0;

    scalebar_id = php3_list_insert(pscalebar, PHPMS_GLOBAL(le_msscalebar));

    _phpms_object_init(return_value, scalebar_id, php_scalebar_class_functions,
                       PHP4_CLASS_ENTRY(scalebar_class_entry_ptr));

    add_property_long(return_value,  "height",          pscalebar->height);
    add_property_long(return_value,  "width",           pscalebar->width);
    add_property_long(return_value,  "style",           pscalebar->style);
    add_property_long(return_value,  "intervals",       pscalebar->intervals);

    add_property_long(return_value,  "units",           pscalebar->units);
    add_property_long(return_value,  "status",          pscalebar->status);
    add_property_long(return_value,  "position",        pscalebar->position);
    add_property_long(return_value,  "transparent",     pscalebar->transparent);
    add_property_long(return_value,  "interlace",       pscalebar->interlace);
    add_property_long(return_value,  "postlabelcache",  
                      pscalebar->postlabelcache);
    
    
#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);
#endif
    _phpms_build_label_object(&(pscalebar->label), list, new_obj_ptr);
    _phpms_add_property_object(return_value, "label", new_obj_ptr,E_ERROR);

#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
#endif
    _phpms_build_color_object(&(pscalebar->imagecolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "imagecolor",new_obj_ptr,E_ERROR);


    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_color_object(&(pscalebar->color),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "color",new_obj_ptr,E_ERROR);


    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_color_object(&(pscalebar->backgroundcolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "backgroundcolor",new_obj_ptr,E_ERROR);

  
    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_color_object(&(pscalebar->outlinecolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "outlinecolor",new_obj_ptr,E_ERROR);
    
    return scalebar_id;
}

/**********************************************************************
 *                        scalebar->set()
 **********************************************************************/

/* {{{ proto int scalebar.set(string property_name, new_value)
   Set object property to a new value. Returns -1 on error. */


DLEXPORT void php3_ms_scalebar_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    scalebarObj *self;
    pval   *pPropertyName, *pNewValue, *pThis;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = 
        (scalebarObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msscalebar),
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    
    IF_SET_LONG(       "height",         self->height)
    else IF_SET_LONG(  "width",   self->width)
    else IF_SET_LONG(  "style",   self->style)
    else IF_SET_LONG(  "intervals",   self->intervals)
    else IF_SET_LONG(  "units",   self->units)
    else IF_SET_LONG(  "status",   self->status)
    else IF_SET_LONG(  "position",   self->position)
    else IF_SET_LONG(  "transparent",   self->transparent)
    else IF_SET_LONG(  "interlace",   self->interlace)
    else IF_SET_LONG(  "postlabelcache",   self->postlabelcache)
    else
    {
        php3_error(E_ERROR,"Property '%s' does not exist in this object.", 
                   pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }

    RETURN_LONG(0);
}           


/**********************************************************************
 *                        scalebar->setimagecolor()
 **********************************************************************/

/* {{{ proto int scalebar.set(int red, int green, int blue)
   Set the imagecolor property of the scalebar. Returns -1 on error. */
DLEXPORT void php3_ms_scalebar_setImageColor(INTERNAL_FUNCTION_PARAMETERS)
{
    scalebarObj *self;
    pval        *pThis, *pR, *pG, *pB;
    int         r, g, b = 0;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 3, &pR, &pG, &pB) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = 
        (scalebarObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msscalebar),
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_FALSE;
    }
    
    convert_to_long(pR);
    convert_to_long(pG);
    convert_to_long(pB);

    r = pR->value.lval;
    g = pG->value.lval;
    b = pB->value.lval;

/* -------------------------------------------------------------------- */
/*      validate values                                                 */
/* -------------------------------------------------------------------- */
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        RETURN_FALSE;
    }
    
    self->imagecolor.red = r;
    self->imagecolor.green = g;
    self->imagecolor.blue = b;

    RETURN_TRUE;
}           

/*=====================================================================
 *                 PHP function wrappers - legendObj class
 *====================================================================*/
/**********************************************************************
 *                     _phpms_build_legend_object()
 **********************************************************************/
static long _phpms_build_legend_object(legendObj *plegend, 
                                       HashTable *list, pval *return_value)
{
    int         legend_id;
#ifdef PHP4
    pval        *new_obj_ptr;
#else
    pval        new_obj_param;  /* No, it's not a pval * !!! */
    pval        *new_obj_ptr;
    new_obj_ptr = &new_obj_param;
#endif

    if (plegend == NULL)
        return 0;

    legend_id = php3_list_insert(plegend, PHPMS_GLOBAL(le_mslegend));

    _phpms_object_init(return_value, legend_id, php_legend_class_functions,
                       PHP4_CLASS_ENTRY(legend_class_entry_ptr));

    add_property_long(return_value,  "height",          plegend->height);
    add_property_long(return_value,  "width",           plegend->width);
    add_property_long(return_value,  "keysizex",        plegend->keysizex);
    add_property_long(return_value,  "keysizey",        plegend->keysizey);
    add_property_long(return_value,  "keyspacingx",     plegend->keyspacingx);
    add_property_long(return_value,  "keyspacingy",     plegend->keyspacingy);
    add_property_long(return_value,  "status",          plegend->status);
    add_property_long(return_value,  "position",        plegend->position);
    add_property_long(return_value,  "transparent",     plegend->transparent);
    add_property_long(return_value,  "interlace",       plegend->interlace);
    add_property_long(return_value,  "postlabelcache",  
                      plegend->postlabelcache);
    PHPMS_ADD_PROP_STR(return_value, "template", plegend->template);
    
    
#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);
#endif
    _phpms_build_label_object(&(plegend->label), list, new_obj_ptr);
    _phpms_add_property_object(return_value, "label", new_obj_ptr,E_ERROR);

#ifdef PHP4
    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
#endif
    _phpms_build_color_object(&(plegend->imagecolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "imagecolor",new_obj_ptr,E_ERROR);

    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_color_object(&(plegend->outlinecolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "outlinecolor",new_obj_ptr,E_ERROR);

    return legend_id;
}

/**********************************************************************
 *                        legend->set()
 **********************************************************************/

/* {{{ proto int legend.set(string property_name, new_value)
   Set object property to a new value. Returns -1 on error. */


DLEXPORT void php3_ms_legend_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    legendObj *self;
    pval   *pPropertyName, *pNewValue, *pThis;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = 
        (legendObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslegend),
                                         list TSRMLS_CC);
    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    if (self == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    
    IF_SET_LONG(       "height",        self->height)
    else IF_SET_LONG(  "width",         self->width)
    else IF_SET_LONG(  "keysizex",      self->keysizex)
    else IF_SET_LONG(  "keysizey",      self->keysizey)
    else IF_SET_LONG(  "keyspacingx",   self->keyspacingx)
    else IF_SET_LONG(  "keyspacingy",   self->keyspacingy)
    else IF_SET_LONG(  "status",        self->status)
    else IF_SET_LONG(  "position",      self->position)
    else IF_SET_LONG(  "transparent",   self->transparent)
    else IF_SET_LONG(  "interlace",     self->interlace)
    else IF_SET_LONG(  "postlabelcache",self->postlabelcache)
    else IF_SET_STRING( "template",     self->template)
    else
    {
        php3_error(E_ERROR,"Property '%s' does not exist in legend object.", 
                   pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }

    RETURN_LONG(0);
}           

/*=====================================================================
 *                 PHP function wrappers - styleObj class
 *====================================================================*/

/**********************************************************************
 *                     _phpms_build_style_object()
 **********************************************************************/
static long _phpms_build_style_object(styleObj *pstyle, int parent_map_id, 
                                      int parent_layer_id, 
                                      int parent_class_id,
                                      HashTable *list, 
                                      pval *return_value TSRMLS_DC)
{
    int style_id;

    pval        *new_obj_ptr;


    if (pstyle == NULL)
        return 0;

    style_id = php3_list_insert(pstyle, PHPMS_GLOBAL(le_msstyle));

    _phpms_object_init(return_value, style_id, php_style_class_functions,
                       PHP4_CLASS_ENTRY(style_class_entry_ptr));

    add_property_resource(return_value, "_class_handle_", parent_class_id);
    zend_list_addref(parent_class_id);

    add_property_resource(return_value, "_layer_handle_", parent_layer_id);
    zend_list_addref(parent_layer_id);

    add_property_resource(return_value, "_map_handle_", parent_map_id);
    zend_list_addref(parent_map_id);


    /* editable properties */
    add_property_long(return_value,   "symbol",     pstyle->symbol);
    PHPMS_ADD_PROP_STR(return_value,  "symbolname", pstyle->symbolname);
    add_property_long(return_value,   "size",       pstyle->size);
    add_property_long(return_value,   "minsize",       pstyle->minsize);
    add_property_long(return_value,   "maxsize",       pstyle->maxsize);
    add_property_long(return_value,   "offsetx",       pstyle->offsetx);
    add_property_long(return_value,   "offsety",       pstyle->offsety);
    
    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_color_object(&(pstyle->color),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "color",new_obj_ptr,E_ERROR);

    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_color_object(&(pstyle->backgroundcolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "backgroundcolor",new_obj_ptr,E_ERROR);

    MAKE_STD_ZVAL(new_obj_ptr);  /* Alloc and Init a ZVAL for new object */
    _phpms_build_color_object(&(pstyle->outlinecolor),list, new_obj_ptr);
    _phpms_add_property_object(return_value, "outlinecolor",new_obj_ptr,E_ERROR);

    return style_id;
}


/**********************************************************************
 *                        ms_newStyleObj()
 **********************************************************************/

/* {{{ proto ms_newStyleObj(classObj class)
   Create a new style in the specified class. */

DLEXPORT void php3_ms_style_new(INTERNAL_FUNCTION_PARAMETERS)
{
    pval  *pClassObj, *pStyleObj=NULL;
    classObj *parent_class;
    styleObj *pNewStyle, *style_obj=NULL;
    int layer_id, map_id, class_id;
    HashTable   *list=NULL;
    int         nArgs = ARG_COUNT(ht);

    if (nArgs != 1 && nArgs != 2)
    {
        WRONG_PARAM_COUNT;
    }
    if (getParameters(ht, nArgs, &pClassObj, &pStyleObj) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    parent_class = (classObj*)_phpms_fetch_handle(pClassObj, 
                                                  PHPMS_GLOBAL(le_msclass),
                                                  list TSRMLS_CC);

    if (nArgs == 2)
    {
        style_obj = (styleObj*)_phpms_fetch_handle(pStyleObj, 
                                                   PHPMS_GLOBAL(le_msstyle),
                                                   list TSRMLS_CC);
    }

    if (parent_class == NULL ||
        (pNewStyle = styleObj_new(parent_class, style_obj)) == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
        RETURN_FALSE;
    }

     _phpms_set_property_long(pClassObj,"numstyles", parent_class->numstyles, 
                              E_ERROR); 

     
    /* We will store a reference to the parent_class object id inside
     * the obj.
     */
    class_id = _phpms_fetch_property_resource(pClassObj, "_handle_", E_ERROR);

    /* We will store a reference to the parent_layer object id inside
     * the obj.
     */
    layer_id = _phpms_fetch_property_resource(pClassObj, "_layer_handle_", E_ERROR);

    /* We will store a reference to the parent_map object id inside
     * the obj.
     */
    map_id = _phpms_fetch_property_resource(pClassObj, "_map_handle_", E_ERROR);
   
    /* Return style object */
    _phpms_build_style_object(pNewStyle, map_id, layer_id, class_id, list, 
                              return_value TSRMLS_CC);
}
/* }}} */


/**********************************************************************
 *                        style->set()
 **********************************************************************/

/* {{{ proto int style.set(string property_name, new_value)
   Set object property to a new value. Returns -1 on error. */

DLEXPORT void php3_ms_style_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    styleObj *self;
    mapObj *parent_map;
    pval   *pPropertyName, *pNewValue, *pThis;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

#ifdef PHP4
    pThis = getThis();
#else
    getThis(&pThis);
#endif

    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (styleObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msstyle),
                                           list TSRMLS_CC);
   
    parent_map = (mapObj*)_phpms_fetch_property_handle(pThis, "_map_handle_",
                                                       PHPMS_GLOBAL(le_msmap),
                                                       list TSRMLS_CC, E_ERROR);

    if (self == NULL || parent_map == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pPropertyName);

    IF_SET_LONG(  "symbol",             self->symbol)
    else IF_SET_STRING( "symbolname",   self->symbolname)
    else IF_SET_LONG( "size",           self->size)
    else IF_SET_LONG( "minsize",        self->minsize)
    else IF_SET_LONG( "maxsize",        self->maxsize)
    else IF_SET_LONG( "offsetx",        self->offsetx)
    else IF_SET_LONG( "offsety",        self->offsety)
    else
    {
        php3_error(E_ERROR,"Property '%s' does not exist in this object.",
                   pPropertyName->value.str.val);
        RETURN_LONG(-1);
    }

    if (strcmp(pPropertyName->value.str.val, "symbolname") == 0)
    {
        if (styleObj_setSymbolByName(self,
                                     parent_map,
                                     self->symbolname) == -1)
        {
            RETURN_LONG(-1);
        }
        _phpms_set_property_long(pThis,"symbol", self->symbol, E_ERROR); 
    }

    RETURN_LONG(0);
}

DLEXPORT void php3_ms_style_clone(INTERNAL_FUNCTION_PARAMETERS)
{
    pval  *pThis = NULL;
    styleObj *self = NULL, *pNewStyle = NULL;
    HashTable   *list=NULL;
    int map_id, layer_id, class_id;
    pThis = getThis();

    if (pThis == NULL)
      php3_error(E_ERROR, "Invalid style object.");

    self = (styleObj *)_phpms_fetch_handle(pThis,
                                           PHPMS_GLOBAL(le_msstyle),
                                           list TSRMLS_CC);
    if (self == NULL)
       php3_error(E_ERROR, "Invalid style object.");

    if ((pNewStyle = styleObj_clone(self)) == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        RETURN_FALSE;
    }

    class_id = _phpms_fetch_property_resource(pThis, "_class_handle_", E_ERROR);
    layer_id = _phpms_fetch_property_resource(pThis, "_layer_handle_", E_ERROR);
    map_id = _phpms_fetch_property_resource(pThis, "_map_handle_", E_ERROR);

     /* Return style object */
    _phpms_build_style_object(pNewStyle, map_id, layer_id, class_id, list, 
                              return_value TSRMLS_CC);
}


/* }}} */



/*=====================================================================
 *                 PHP function wrappers - outputformat class
 *====================================================================*/
/**********************************************************************
 *                     _phpms_build_outputformat_object()
 **********************************************************************/
static long _phpms_build_outputformat_object(outputFormatObj *poutputformat, 
                                             HashTable *list, 
                                             pval *return_value)
{
    int         outputformat_id;

    if (poutputformat == NULL)
        return 0;

    outputformat_id = 
      php3_list_insert(poutputformat, PHPMS_GLOBAL(le_msoutputformat));

    _phpms_object_init(return_value, outputformat_id, 
                       php_outputformat_class_functions,
                       PHP4_CLASS_ENTRY(outputformat_class_entry_ptr));

    PHPMS_ADD_PROP_STR(return_value, "name", poutputformat->name);
    PHPMS_ADD_PROP_STR(return_value, "mimetype", poutputformat->mimetype);
    PHPMS_ADD_PROP_STR(return_value, "driver", poutputformat->driver);
    PHPMS_ADD_PROP_STR(return_value, "extension", poutputformat->extension);
    add_property_long(return_value,  "renderer", poutputformat->renderer);
    add_property_long(return_value,  "imagemode", poutputformat->imagemode);
    add_property_long(return_value,  "transparent", poutputformat->transparent);

    return outputformat_id;
}

DLEXPORT void php_ms_outputformat_setOutputformatoption(INTERNAL_FUNCTION_PARAMETERS)
{
    outputFormatObj *self;
    pval   *pPropertyName, *pNewValue, *pThis;
    HashTable   *list=NULL;

    pThis = getThis();


    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pPropertyName);
    convert_to_string(pNewValue);
     
    self = (outputFormatObj *)
      _phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msoutputformat),
                          list TSRMLS_CC);

    if (self == NULL)
      RETURN_FALSE;

    msSetOutputFormatOption(self, pPropertyName->value.str.val,
                            pNewValue->value.str.val);

     RETURN_TRUE;
}

DLEXPORT void php_ms_outputformat_getOutputformatoption(INTERNAL_FUNCTION_PARAMETERS)
{
    outputFormatObj *self;
    const char *szRetrun = NULL;
    pval   *pPropertyName, *pThis;
    HashTable   *list=NULL;

    pThis = getThis();


    if (pThis == NULL ||
        getParameters(ht, 1, &pPropertyName) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pPropertyName);
     
    self = (outputFormatObj *)
      _phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msoutputformat),
                          list TSRMLS_CC);

    if (self == NULL)
      RETURN_FALSE;

    szRetrun = msGetOutputFormatOption(self, pPropertyName->value.str.val, "");

    RETVAL_STRING((char*)szRetrun, 1);

    //RETURN_STRING("", 0);  

}


/*=====================================================================
 *                 PHP function wrappers - grid class
 *====================================================================*/
/**********************************************************************
 *                     _phpms_build_grid_object()
 **********************************************************************/
static long _phpms_build_grid_object(graticuleObj *pgrid, 
                                     int parent_layer_id, 
                                     HashTable *list, 
                                     pval *return_value TSRMLS_DC)
{
    int         grid_id;

    if (pgrid == NULL)
        return 0;

    grid_id = 
      php3_list_insert(pgrid, PHPMS_GLOBAL(le_msgrid));

    _phpms_object_init(return_value, grid_id, 
                       php_grid_class_functions,
                       PHP4_CLASS_ENTRY(grid_class_entry_ptr));

    add_property_resource(return_value, "_layer_handle_", parent_layer_id);
    zend_list_addref(parent_layer_id);

    add_property_double(return_value,  "minsubdivide", pgrid->minsubdivides);
    add_property_double(return_value,  "maxsubdivide", pgrid->maxsubdivides);
    add_property_double(return_value,  "minarcs", pgrid->minarcs);
    add_property_double(return_value,  "maxarcs", pgrid->maxarcs);
    add_property_double(return_value,  "mininterval", pgrid->minincrement);
    add_property_double(return_value,  "maxinterval", pgrid->maxincrement);
    PHPMS_ADD_PROP_STR(return_value, "labelformat", pgrid->labelformat);
    
    return grid_id;
}


DLEXPORT void php3_ms_grid_new(INTERNAL_FUNCTION_PARAMETERS)
{
    pval  *pLayerObj;
    layerObj *parent_class;
    int layer_id;
    HashTable   *list=NULL;
    pval        *new_obj_ptr;

    if (getParameters(ht, 1, &pLayerObj) == FAILURE) 
    {
        WRONG_PARAM_COUNT;
    }

    parent_class = (layerObj*)_phpms_fetch_handle(pLayerObj, 
                                                  PHPMS_GLOBAL(le_mslayer),
                                                  list TSRMLS_CC);

    layer_id = _phpms_fetch_property_resource(pLayerObj, "_handle_", E_ERROR);

    if (parent_class == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
        RETURN_FALSE;
    }

    parent_class->connectiontype = MS_GRATICULE;

    /* Update layerObj members */
    _phpms_set_property_long(pLayerObj, "connectiontype",
                             parent_class->connectiontype, E_ERROR); 

    if (parent_class->layerinfo != NULL)
      free(parent_class->layerinfo);

    parent_class->layerinfo = (graticuleObj *)malloc( sizeof( graticuleObj ) );
    initGrid((graticuleObj *)parent_class->layerinfo );

    MAKE_STD_ZVAL(new_obj_ptr);
    _phpms_build_grid_object((graticuleObj *)(parent_class->layerinfo),
                             layer_id,
                             list, new_obj_ptr TSRMLS_CC);
    _phpms_add_property_object(pLayerObj, "grid", new_obj_ptr, E_ERROR);
    
}
/* }}} */


/**********************************************************************
 *                        grid->set()
 **********************************************************************/

/* {{{ proto int grid.set(string property_name, new_value)
   Set object property to a new value. Returns -1 on error. */

DLEXPORT void php3_ms_grid_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    graticuleObj *self;
    layerObj *parent_layer;
    pval   *pPropertyName, *pNewValue, *pThis;
    HashTable   *list=NULL;

    pThis = getThis();


    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (graticuleObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_msgrid),
                                           list TSRMLS_CC);
   
    parent_layer = (layerObj*)_phpms_fetch_property_handle(pThis, "_layer_handle_",
                                                       PHPMS_GLOBAL(le_mslayer),
                                                       list TSRMLS_CC, E_ERROR);

    if (self == NULL || parent_layer == NULL)
    {
        RETURN_LONG(-1);
    }

    if (parent_layer->connectiontype == MS_GRATICULE &&
        parent_layer->layerinfo != NULL)
    {
        convert_to_string(pPropertyName);

        IF_SET_DOUBLE(  "minsubdivide",             self->minsubdivides)
        else IF_SET_DOUBLE(  "maxsubdivide",             self->maxsubdivides)
        else IF_SET_DOUBLE(  "minarcs",             self->minarcs)
        else IF_SET_DOUBLE(  "maxarcs",             self->maxarcs)
        else IF_SET_DOUBLE(  "mininterval",             self->minincrement)
        else IF_SET_DOUBLE(  "maxinterval",             self->maxincrement)
        else IF_SET_STRING( "labelformat",   self->labelformat)
        else
        {
            php3_error(E_ERROR,"Property '%s' does not exist in this object.",
                   pPropertyName->value.str.val);
            RETURN_LONG(-1);
        }

    }

    RETURN_LONG(0);
}
/* }}} */


/*=====================================================================
 *                 PHP function wrappers - errorObj class
 *====================================================================*/
/**********************************************************************
 *                     _phpms_build_error_object()
 **********************************************************************/
static long _phpms_build_error_object(errorObj *perror, 
                                     HashTable *list, pval *return_value)
{
    int error_id;

    if (perror == NULL)
      return 0;

    error_id = php3_list_insert(perror, PHPMS_GLOBAL(le_mserror_ref) );

    _phpms_object_init(return_value, error_id, php_error_class_functions,
                       PHP4_CLASS_ENTRY(error_class_entry_ptr));

    add_property_long(return_value,     "code",         perror->code);
    PHPMS_ADD_PROP_STR(return_value,    "routine",      perror->routine);
    PHPMS_ADD_PROP_STR(return_value,    "message",      perror->message);

    return error_id;
}


/**********************************************************************
 *                        ms_GetErrorObj()
 **********************************************************************/

/* {{{ proto errorObj ms_GetErrorObj()
   Return the head of the MapServer errorObj list. */

DLEXPORT void php3_ms_get_error_obj(INTERNAL_FUNCTION_PARAMETERS)
{
    errorObj *pError;
    HashTable   *list=NULL;

    if (ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    if ((pError = msGetErrorObj()) == NULL)
    {
        _phpms_report_mapserver_error(E_ERROR);
        RETURN_FALSE;
    }

    /* Return error object */
    _phpms_build_error_object(pError, list, return_value);
}
/* }}} */


/**********************************************************************
 *                        error->next()
 **********************************************************************/

/* {{{ proto int error.next()
   Returns a ref to the next errorObj in the list, or NULL if we reached the last one */

DLEXPORT void php3_ms_error_next(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pThis;
    errorObj    *self, *error_ptr;
    HashTable   *list=NULL;

    pThis = getThis();

    if (pThis == NULL || ARG_COUNT(ht) > 0)
    {
        WRONG_PARAM_COUNT;
    }

    self = (errorObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mserror_ref),
                                           list TSRMLS_CC);

    if (self == NULL || self->next == NULL)
    {
        RETURN_NULL();
    }

    /* Make sure 'self' is still valid.  It may have been deleted by 
     * msResetErrorList() 
     */
    error_ptr = msGetErrorObj();
    while(error_ptr != self)
    {
        if (error_ptr->next == NULL)
        {
            /* We reached end of list of active errorObj and didn't find the
             * errorObj... thisis bad!
             */
            php_error(E_WARNING, 
                      "ERROR: Trying to access an errorObj that has expired.");
            RETURN_NULL();
        }
        error_ptr = error_ptr->next;
    }

    /* Return error object */
    _phpms_build_error_object(self->next, list, return_value);
}
/* }}} */


/**********************************************************************
 *                        ms_ResetErrorList()
 **********************************************************************/

/* {{{ proto errorObj ms_ResetErrorList()
   Clear the MapServer errorObj list. */

DLEXPORT void php3_ms_reset_error_list(INTERNAL_FUNCTION_PARAMETERS)
{
    msResetErrorList();
}
/* }}} */


/*=====================================================================
 *                 PHP function wrappers - labelcache class
 *====================================================================*/
/**********************************************************************
 *                     _phpms_build_labelcache_object()
 **********************************************************************/
static long _phpms_build_labelcache_object(labelCacheObj *plabelcache, 
                                           HashTable *list, 
                                           pval *return_value)
{
    int         labelcache_id;

    if (plabelcache == NULL)
        return 0;

    labelcache_id = 
      php3_list_insert(plabelcache, PHPMS_GLOBAL(le_mslabelcache));

    _phpms_object_init(return_value, labelcache_id, 
                       php_labelcache_class_functions,
                       PHP4_CLASS_ENTRY(labelcache_class_entry_ptr));

    return labelcache_id;
}

/**********************************************************************
 *                        labelcache->free()
 **********************************************************************/

/* {{{ proto int labelcache->free(()
   Free the labelcache object in the map. Returns true on success or false if
   an error occurs. */

DLEXPORT void php_ms_labelcache_free(INTERNAL_FUNCTION_PARAMETERS)
{
    labelCacheObj *self;
    HashTable   *list=NULL;
    pval  *pThis;

    pThis = getThis();


    if (pThis == NULL)
      RETURN_FALSE;

     
    self = (labelCacheObj *)
      _phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mslabelcache),
                          list TSRMLS_CC);

    if (self == NULL)
      RETURN_FALSE;

    labelCacheObj_freeCache(self);

     RETURN_TRUE;
}


/*=====================================================================
 *                 PHP function wrappers - symbol object
 *====================================================================*/

DLEXPORT void php3_ms_symbol_new(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pMapObj, *pName;
    mapObj      *parent_map;
    HashTable   *list=NULL;
    int         nReturn = -1;

    if ( getParameters(ht, 2, &pMapObj, &pName) == FAILURE)
    {
        WRONG_PARAM_COUNT;
    }

    parent_map = (mapObj*)_phpms_fetch_handle(pMapObj, 
                                              PHPMS_GLOBAL(le_msmap),
                                              list TSRMLS_CC);
    if (parent_map == NULL)
    {
        RETURN_LONG(-1);
    }

    convert_to_string(pName);

    nReturn = msAddNewSymbol(parent_map, pName->value.str.val);

    RETURN_LONG(nReturn);
}
 

/**********************************************************************
 *                     _phpms_build_symbol_object()
 **********************************************************************/
static long _phpms_build_symbol_object(symbolObj *psSymbol, 
                                       int parent_map_id, 
                                       HashTable *list, 
                                       pval *return_value TSRMLS_DC)
{
    int symbol_id;



    if (psSymbol == NULL)
        return 0;

    symbol_id = php3_list_insert(psSymbol, PHPMS_GLOBAL(le_mssymbol));

    _phpms_object_init(return_value, symbol_id, php_symbol_class_functions,
                       PHP4_CLASS_ENTRY(symbol_class_entry_ptr));

    add_property_resource(return_value, "_map_handle_", parent_map_id);
    zend_list_addref(parent_map_id);

    PHPMS_ADD_PROP_STR(return_value,  "name", psSymbol->name);
    add_property_long(return_value,   "type",     psSymbol->type);
    add_property_long(return_value,   "inmapfile",     psSymbol->inmapfile);
    add_property_double(return_value,   "sizex",     psSymbol->sizex);
    add_property_double(return_value,   "sizey",     psSymbol->sizey);
    add_property_long(return_value,   "numpoints",     psSymbol->numpoints);
    add_property_long(return_value,   "filled",     psSymbol->filled);
    add_property_long(return_value,   "stylelength",     psSymbol->stylelength);
    //PHPMS_ADD_PROP_STR(return_value,  "imagepath", psSymbol->imagepath);
    //add_property_long(return_value,   "transparent",     psSymbol->transparent);
    //add_property_long(return_value,   "transparentcolor", 
    //                 psSymbol->transparentcolor);
    //TODO : true type and cartoline parameters to add.

    return symbol_id;
}
    
/**********************************************************************
 *                        symbol->set()
 **********************************************************************/

/* {{{ proto int symbol.set(string property_name, new_value)
   Set object property to a new value. Returns -1 on error. */

DLEXPORT void php3_ms_symbol_setProperty(INTERNAL_FUNCTION_PARAMETERS)
{
    symbolObj *self;
    pval   *pPropertyName, *pNewValue, *pThis;
    HashTable   *list=NULL;

    pThis = getThis();

    if (pThis == NULL ||
        getParameters(ht, 2, &pPropertyName, &pNewValue) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (symbolObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mssymbol),
                                            list TSRMLS_CC);
    
    if (self == NULL)
      RETURN_FALSE;

    convert_to_string(pPropertyName);

    IF_SET_STRING( "name",   self->name)
    else IF_SET_LONG(  "type",             self->type)
    else IF_SET_LONG(  "inmapfile",             self->inmapfile)
    else IF_SET_DOUBLE(  "sizex",             self->sizex)
    else IF_SET_DOUBLE(  "sizey",             self->sizey)
    else IF_SET_LONG(  "filled",             self->filled)
    else if (strcmp( "numpoints", pPropertyName->value.str.val) == 0 ||
             strcmp( "stylelength", pPropertyName->value.str.val) == 0)
    {
        php3_error(E_ERROR,"Property '%s' is read-only and cannot be set.", 
                            pPropertyName->value.str.val);
         RETURN_FALSE;
    }
    else
    {
        php3_error(E_ERROR,"Property '%s' does not exist in this object.",
                   pPropertyName->value.str.val);
         RETURN_FALSE;
    }

    RETURN_TRUE;
}


/**********************************************************************
 *                        symbol->setpoints()
 **********************************************************************/

/* {{{ proto int symbol.setpoints(array points, int numpoints)
   Set the points of the symbol ) */ 

DLEXPORT void php3_ms_symbol_setPoints(INTERNAL_FUNCTION_PARAMETERS)
{
    symbolObj *self;
    pval   *pPoints, *pThis;
    HashTable   *list=NULL;
     pval        **pValue = NULL;
    int i=0, nElements = 0, iSymbol=0;

    pThis = getThis();

    if (pThis == NULL ||
        getParameters(ht, 1, &pPoints) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (symbolObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mssymbol),
                                            list TSRMLS_CC);
    
    if (self == NULL)
      RETURN_FALSE;

    if (pPoints->type != IS_ARRAY) 
    {
        php_error(E_WARNING, 
                  "symbol->setpoints : expected array as parameter");
        RETURN_FALSE;
    }

    nElements = zend_hash_num_elements(pPoints->value.ht);

    if (nElements <=0)
    {
        php_error(E_WARNING, 
                  "symbol->setpoints : invalid array as parameter. Array sould have at least two points.");
        RETURN_FALSE;
    }
    
    i= 0;
    iSymbol = 0;
    while (i<nElements)
    {
        if (zend_hash_index_find(pPoints->value.ht, i, 
                                 (void **)&pValue) == FAILURE)
        {
            RETURN_FALSE;
        }
        convert_to_long((*pValue));
        self->points[iSymbol].x = (*pValue)->value.lval;
        i++;

         if (zend_hash_index_find(pPoints->value.ht, i, 
                                 (void **)&pValue) == FAILURE)
        {
            RETURN_FALSE;
        }
        convert_to_long((*pValue));
        self->points[iSymbol].y = (*pValue)->value.lval;
        i++;

        iSymbol++;
    }
    
    self->numpoints = (nElements/2);

    RETURN_TRUE;
}

/**********************************************************************
 *                        symbol->getpointsarray()
 **********************************************************************/
DLEXPORT void php3_ms_symbol_getPoints(INTERNAL_FUNCTION_PARAMETERS)
{
    symbolObj *self;
    pval        *pThis;
    HashTable   *list=NULL;
    int i=0;

     pThis = getThis();

     if (pThis == NULL)
        RETURN_FALSE;

     if (array_init(return_value) == FAILURE) 
     {
         RETURN_FALSE;
     }

     self = (symbolObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mssymbol), 
                                             list TSRMLS_CC);

     if (self == NULL)
       RETURN_FALSE;

     if (self->numpoints > 0)
     {
         for (i=0; i<self->numpoints; i++)
         {
             add_next_index_double(return_value, self->points[i].x);
             add_next_index_double(return_value, self->points[i].y);
         }
     }
     else
       RETURN_FALSE;
}


/**********************************************************************
 *                        symbol->getstylearray()
 **********************************************************************/
DLEXPORT void php3_ms_symbol_getStyle(INTERNAL_FUNCTION_PARAMETERS)
{
    symbolObj *self;
    pval        *pThis;
    HashTable   *list=NULL;
    int i=0;

     pThis = getThis();

     if (pThis == NULL)
        RETURN_FALSE;

     if (array_init(return_value) == FAILURE) 
     {
         RETURN_FALSE;
     }

     self = (symbolObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mssymbol), 
                                             list TSRMLS_CC);

     if (self == NULL)
       RETURN_FALSE;

     if (self->stylelength > 0)
     {
         for (i=0; i<self->stylelength; i++)
         {
             add_next_index_double(return_value, self->style[i]);
         }
     }
     else
       RETURN_FALSE;
}
         
         

/**********************************************************************
 *                        symbol->setstyle()
 **********************************************************************/

/* {{{ proto int symbol.setstyle(array points, int numpoints)
   Set the style of the symbol ) */ 

DLEXPORT void php3_ms_symbol_setStyle(INTERNAL_FUNCTION_PARAMETERS)
{
    symbolObj *self;
    pval   *pPoints, *pThis;
    HashTable   *list=NULL;
     pval        **pValue = NULL;
    int i=0, nElements = 0;
 

    pThis = getThis();

    if (pThis == NULL ||
        getParameters(ht, 1, &pPoints) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    self = (symbolObj *)_phpms_fetch_handle(pThis, PHPMS_GLOBAL(le_mssymbol),
                                            list TSRMLS_CC);
    
    if (self == NULL)
      RETURN_FALSE;

    if (pPoints->type != IS_ARRAY) 
    {
        php_error(E_WARNING, 
                  "symbol->setstyle : expected array as parameter");
        RETURN_FALSE;
    }

    nElements = zend_hash_num_elements(pPoints->value.ht);

    if (nElements <=0)
    {
        php_error(E_WARNING, 
                  "symbol->setpoints : invalid array as parameter. Array sould have at least two entries.");
        RETURN_FALSE;
    }
    
    i= 0;
    while (i<nElements)
    {
        if (zend_hash_index_find(pPoints->value.ht, i, 
                                 (void **)&pValue) == FAILURE)
        {
            RETURN_FALSE;
        }
        convert_to_long((*pValue));
        self->style[i] = (*pValue)->value.lval;
        i++;
    }
    
    self->stylelength = nElements;

    RETURN_TRUE;
}


/* ==================================================================== */
/*      utility functions                                               */
/* ==================================================================== */


/************************************************************************/
/*      DLEXPORT void php3_ms_getcwd(INTERNAL_FUNCTION_PARAMETERS)      */
/*                                                                      */
/*      This function is a copy of the                                  */
/*      vod php3_posix_getcwd(INTERNAL_FUNCTION_PARAMETERS)             */
/*      (./php/functions/posix.c).                                      */
/*                                                                      */
/*       Since posix functions seems to not be standard in php, It has been*/
/*      added here.                                                     */
/************************************************************************/
/* OS/2's gcc defines _POSIX_PATH_MAX but not PATH_MAX */
#if !defined(PATH_MAX) && defined(_POSIX_PATH_MAX)
#define PATH_MAX _POSIX_PATH_MAX
#endif

#if !defined(PATH_MAX) && defined(MAX_PATH)
#define PATH_MAX MAX_PATH
#endif

#if !defined(PATH_MAX)
#define PATH_MAX 512
#endif

DLEXPORT void php3_ms_getcwd(INTERNAL_FUNCTION_PARAMETERS)
{
    char  buffer[PATH_MAX];
    char *p;
   
    p = getcwd(buffer, PATH_MAX);
    if (!p) {
        php3_error(E_WARNING, "posix_getcwd() failed with '%s'",
                   strerror(errno));
        RETURN_FALSE;
    }

    RETURN_STRING(buffer, 1);
}

/************************************************************************/
/*                           php3_ms_getpid()                           */
/************************************************************************/
DLEXPORT void php3_ms_getpid(INTERNAL_FUNCTION_PARAMETERS)
{
    RETURN_LONG(getpid());
}


/************************************************************************/
/*       DLEXPORT void php3_ms_getscale(INTERNAL_FUNCTION_PARAMETERS)   */
/*                                                                      */
/*      Utility function to get the scale based on the width/height     */
/*      of the pixmap, the georeference and the units of the data.      */
/*                                                                      */
/*       Parameters are :                                               */
/*                                                                      */
/*            - Georefernce extents (rectObj)                           */
/*            - Width : width in pixel                                  */
/*            - Height : Height in pixel                                */
/*            - Units of the data (int)                                 */
/*                                                                      */
/*                                                                      */
/************************************************************************/
DLEXPORT void php3_ms_getscale(INTERNAL_FUNCTION_PARAMETERS)
{
    pval        *pGeorefExt = NULL;
    pval        *pWidth = NULL;
    pval        *pHeight;
    pval        *pUnit, *pResolution;
    rectObj     *poGeorefExt = NULL;
    double      dfScale = 0.0;
#ifdef PHP4
    HashTable   *list=NULL;
#endif

    if (getParameters(ht, 5, 
                      &pGeorefExt, &pWidth, &pHeight, 
                      &pUnit, &pResolution) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }
    
    convert_to_long(pWidth);
    convert_to_long(pHeight);
    convert_to_long(pUnit);
    convert_to_double(pResolution);

    poGeorefExt = 
        (rectObj *)_phpms_fetch_handle2(pGeorefExt, 
                                        PHPMS_GLOBAL(le_msrect_ref),
                                        PHPMS_GLOBAL(le_msrect_new),
                                        list TSRMLS_CC);

    if (msCalculateScale(*poGeorefExt, pUnit->value.lval, 
                         pWidth->value.lval, pHeight->value.lval,
                         pResolution->value.dval, &dfScale) != MS_SUCCESS)
    {
        _phpms_report_mapserver_error(E_ERROR);
    }
    
    RETURN_DOUBLE(dfScale);
}

/************************************************************************/
/*  static double GetDeltaExtentsUsingScale(double dfMinscale, int nUnits,*/
/*                                              int nWidth)             */
/*                                                                      */
/*      Utility function to return the maximum extent using the         */
/*      scale and the width of the image.                               */
/*                                                                      */
/*      Base on the function msCalculateScale (mapscale.c)              */
/************************************************************************/
static double GetDeltaExtentsUsingScale(double dfScale, int nUnits, 
                                        double dCenterLat,
                                        int nWidth, double resolution)
{
    double md = 0.0;
    double dfDelta = -1.0;

    if (dfScale <= 0 || nWidth <=0)
      return -1;

    switch (nUnits) 
    {
      case(MS_DD):
      case(MS_METERS):    
      case(MS_KILOMETERS):
      case(MS_MILES):
      case(MS_INCHES):  
      case(MS_FEET):
        md = nWidth/(resolution*msInchesPerUnit(nUnits,dCenterLat));
        dfDelta = md * dfScale;
        break;
          
      default:
        break;
    }

    return dfDelta;
}

/**********************************************************************
 *                        ms_tokenizeMap()
 *
 * Preparse mapfile and return an array containg one item for each 
 * token in the map.
 **********************************************************************/

/* {{{ proto array ms_tokenizeMap(string filename)
   Preparse mapfile and return an array containg one item for each token in the map.*/

DLEXPORT void php3_ms_tokenizeMap(INTERNAL_FUNCTION_PARAMETERS)
{ 
    pval        *pFname;
    char        **tokens;
    int         i, numtokens=0;

    if (getParameters(ht, 1, &pFname) != SUCCESS)
    {
        WRONG_PARAM_COUNT;
    }

    convert_to_string(pFname);

    if ((tokens = msTokenizeMap(pFname->value.str.val, &numtokens)) == NULL)
    {
        _phpms_report_mapserver_error(E_WARNING);
        php3_error(E_ERROR, "Failed tokenizing map file %s", 
                            pFname->value.str.val);
        RETURN_FALSE;
    }
    else
    {
        if (array_init(return_value) == FAILURE) 
        {
            RETURN_FALSE;
        }

        for (i=0; i<numtokens; i++)
        {
            add_next_index_string(return_value,  tokens[i], 1);
        }

        msFreeCharArray(tokens, numtokens);
    }


}
