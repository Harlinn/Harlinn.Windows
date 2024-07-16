
#ifdef BUILDING_HARLINN_GDAL
#define HGDAL_EXPORT __declspec(dllexport)
#else
#define HGDAL_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.gdal.lib")
#endif

/* Define if gdal used libz*/
#define GDAL_USE_ZLIB

/* Define if gdal used internal libz*/
/* #undef GDAL_USE_ZLIB_INTERNAL */

/* Define if gdal used libcurl */
#define GDAL_USE_CURL

/* Define if gdal used odbc */
/* #undef GDAL_USE_ODBC */

/* Define if gdal used odbc-cpp */
/* #undef GDAL_USE_ODBCCPP */

/* Define if pam enable in gdal */
#define ENABLE_PAM

/* Define if gdal use geos*/
#define GDAL_USE_GEOS

/* Define if gdal use opencl*/
/* #undef GDAL_USE_OPENCL */

/* Define if gdal use armadillo*/
/* #undef GDAL_USE_ARMADILLO */

/* Define if gdal use iconv*/
/* #undef GDAL_USE_ICONV*/

/* Define if gdal use internal libtiff*/
/* #undef GDAL_USE_LIBTIFF_INTERNAL */
#define GDAL_USE_TIFF

/* Define if gdal use internal libjpeg*/
/* #undef GDAL_USE_LIBJPEG_INTERNAL */
#define GDAL_USE_JPEG

/* Define if gdal use internal libpng*/
/* #undef GDAL_USE_LIBPNG_INTERNAL */
#define GDAL_USE_PNG

/* Define if gdal use internal libgif*/
/* #undef GDAL_USE_LIBGIF_INTERNAL */
#define GDAL_USE_GIF

#define GDAL_USE_EXPAT
#define GDAL_USE_POSTGRESQL
#define GDAL_USE_SQLITE3
/* #undef GDAL_USE_MYSQL */
#define GDAL_USE_LIBKML

/* #undef GDAL_USE_LIBJSONC_INTERNAL */

/*** RASTER FORMATS ***/
#define GDAL_ENABLE_DRIVER_GTIFF
#define GDAL_ENABLE_DRIVER_JPEG
#define GDAL_ENABLE_DRIVER_HFA
#define GDAL_ENABLE_DRIVER_BMP
#define GDAL_ENABLE_DRIVER_DIMAP
#define GDAL_ENABLE_DRIVER_MEM
#define GDAL_ENABLE_DRIVER_RAW
#define GDAL_ENABLE_DRIVER_VRT
#define GDAL_ENABLE_DRIVER_PNG
#define GDAL_ENABLE_DRIVER_GIF
#define GDAL_ENABLE_DRIVER_TIL

/*** VECTOR FORMATS ***/
/* #undef OGR_ENABLE_DRIVER_MITAB */
#define OGR_ENABLE_DRIVER_CSV
#define OGR_ENABLE_DRIVER_DXF
#define OGR_ENABLE_DRIVER_GEOJSON
#define OGR_ENABLE_DRIVER_MEM
#define OGR_ENABLE_DRIVER_VRT
#define OGR_ENABLE_DRIVER_GPX
#define OGR_ENABLE_DRIVER_SHAPE
#define OGR_ENABLE_DRIVER_WFS
#define OGR_ENABLE_DRIVER_PG
#define OGR_ENABLE_DRIVER_SQLITE
/* #undef OGR_ENABLE_DRIVER_MYSQL */
#define OGR_ENABLE_DRIVER_LIBKML
#define OGR_ENABLE_DRIVER_GML
#define OGR_ENABLE_DRIVER_KML
