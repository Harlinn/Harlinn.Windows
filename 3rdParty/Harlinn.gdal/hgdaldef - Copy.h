#pragma once
#ifndef __HGDALDEF_H__
#define __HGDALDEF_H__

#ifdef BUILDING_HARLINN_GDAL
#define HGDAL_EXPORT __declspec(dllexport)
#else
#define HGDAL_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.gdal.lib")
#endif

#ifndef HAVE_LIBZ
#define HAVE_LIBZ 1
#endif

#ifndef HAVE_CURL
#define HAVE_CURL 1
#endif

#ifndef HAVE_SSE_AT_COMPILE_TIME
#define HAVE_SSE_AT_COMPILE_TIME 1
#endif

#ifndef HAVE_SSSE3_AT_COMPILE_TIME
#define HAVE_SSSE3_AT_COMPILE_TIME 1
#endif

#ifndef HAVE_AVX_AT_COMPILE_TIME
#define HAVE_AVX_AT_COMPILE_TIME 1
#endif

#ifndef HAVE_EXPAT
#define HAVE_EXPAT 1
#endif

#ifndef HAVE_GEOS
#define HAVE_GEOS 1
#endif

#ifndef HAVE_HDF5
#define HAVE_HDF5 1
#endif

#ifndef HAVE_HDF4
#define HAVE_HDF4
#endif


#ifndef HAVE_XERCES
#define HAVE_XERCES 1
#endif

#ifndef HAVE_ARMADILLO
#define HAVE_ARMADILLO 1
#endif

#ifndef HAVE_LIBJPEG
#define HAVE_LIBJPEG 1
#endif

#ifndef HAVE_LIBXML2
#define HAVE_LIBXML2 1
#endif

#ifndef HAVE_SQLITE
#define HAVE_SQLITE 1
#endif

#ifndef ZSTD_SUPPORT
#define ZSTD_SUPPORT 1
#endif

#ifndef HAVE_LZMA
#define HAVE_LZMA 1
#endif

#ifndef HAVE_ZSTD
#define HAVE_ZSTD 1
#endif

#ifndef HAVE_LZ4
#define HAVE_LZ4 1
#endif


#ifndef SHAPE_ENABLED
#define SHAPE_ENABLED 1
#endif

#ifndef MITAB_ENABLED
#define MITAB_ENABLED 1
#endif

#ifndef NTF_ENABLED
#define NTF_ENABLED 1
#endif

#ifndef LVBAG_ENABLED
#define LVBAG_ENABLED 1
#endif

#ifndef SDTS_ENABLED
#define SDTS_ENABLED 1
#endif

#ifndef S57_ENABLED
#define S57_ENABLED 1
#endif

#ifndef DGN_ENABLED
#define DGN_ENABLED 1
#endif

#ifndef VRT_ENABLED
#define VRT_ENABLED 1
#endif

#ifndef REC_ENABLED
#define REC_ENABLED 1
#endif

#ifndef MEM_ENABLED
#define MEM_ENABLED 1
#endif

#ifndef CSV_ENABLED
#define CSV_ENABLED 1
#endif

#ifndef NAS_ENABLED
#define NAS_ENABLED 1
#endif

#ifndef GML_ENABLED
#define GML_ENABLED 1
#endif

#ifndef GPX_ENABLED
#define GPX_ENABLED 1
#endif

#ifndef LIBKML_ENABLED
#define LIBKML_ENABLED 1
#endif

#ifndef KML_ENABLED
#define KML_ENABLED 1
#endif

#ifndef GEOJSON_ENABLED
#define GEOJSON_ENABLED 1
#endif

#ifndef ILI_ENABLED
#define ILI_ENABLED 1
#endif

#ifndef GMT_ENABLED
#define GMT_ENABLED 1
#endif

#ifndef GPKG_ENABLED
#define GPKG_ENABLED 1
#endif

#ifndef SQLITE_ENABLED
#define SQLITE_ENABLED 1
#endif

//#ifndef DODS_ENABLED
//#define DODS_ENABLED 1
//#endif

#ifndef ODBC_ENABLED
#define ODBC_ENABLED 1
#endif

#ifndef WASP_ENABLED
#define WASP_ENABLED 1
#endif

#ifndef MDB_ENABLED
#define MDB_ENABLED 1
#endif

#ifndef PGEO_ENABLED
#define PGEO_ENABLED 1
#endif

#ifndef MSSQLSPATIAL_ENABLED
#define MSSQLSPATIAL_ENABLED 1
#endif

//#ifndef OGDI_ENABLED
//#define OGDI_ENABLED 1
//#endif

//#ifndef PG_ENABLED
//#define PG_ENABLED 1
//#endif

//#ifndef MYSQL_ENABLED
//#define MYSQL_ENABLED 1
//#endif

#ifndef OCI_ENABLED
#define OCI_ENABLED 1
#endif

//#ifndef INGRES_ENABLED
//#define INGRES_ENABLED 1
//#endif

#ifndef OPENFILEGDB_ENABLED
#define OPENFILEGDB_ENABLED 1
#endif

//#ifndef FGDB_ENABLED
//#define FGDB_ENABLED 1
//#endif

//#ifndef DWG_ENABLED
//#define DWG_ENABLED 1
//#endif

//#ifndef DGNV8_ENABLED
//#define DGNV8_ENABLED 1
//#endif

#ifndef DXF_ENABLED
#define DXF_ENABLED 1
#endif

#ifndef CAD_ENABLED
#define CAD_ENABLED 1
#endif

//#ifndef GRASS_ENABLED
//#define GRASS_ENABLED 1
//#endif

#ifndef FLATGEOBUF_ENABLED
#define FLATGEOBUF_ENABLED 1
#endif

//#ifndef FME_ENABLED
//#define FME_ENABLED 1
//#endif

//#ifndef IDB_ENABLED
//#define IDB_ENABLED 1
//#endif

#ifndef GEOCONCEPT_ENABLED
#define GEOCONCEPT_ENABLED 1
#endif

#ifndef GEORSS_ENABLED
#define GEORSS_ENABLED 1
#endif

#ifndef GTM_ENABLED
#define GTM_ENABLED 1
#endif

#ifndef VFK_ENABLED
#define VFK_ENABLED 1
#endif

#ifndef PGDUMP_ENABLED
#define PGDUMP_ENABLED 1
#endif

#ifndef OSM_ENABLED
#define OSM_ENABLED 1
#endif

#ifndef GPSBABEL_ENABLED
#define GPSBABEL_ENABLED 1
#endif

#ifndef PDS_ENABLED
#define PDS_ENABLED 1
#endif

#ifndef WFS_ENABLED
#define WFS_ENABLED 1
#endif

#ifndef SOSI_ENABLED
#define SOSI_ENABLED 1
#endif

//#ifndef GEOMEDIA_ENABLED
//#define GEOMEDIA_ENABLED 1
//#endif

#ifndef EDIGEO_ENABLED
#define EDIGEO_ENABLED 1
#endif

#ifndef SVG_ENABLED
#define SVG_ENABLED 1
#endif

#ifndef COUCHDB_ENABLED
#define COUCHDB_ENABLED 1
#endif

#ifndef CLOUDANT_ENABLED
#define CLOUDANT_ENABLED 1
#endif

//#ifndef IDRISI_ENABLED
//#define IDRISI_ENABLED 1
//#endif

#ifndef ARCGEN_ENABLED
#define ARCGEN_ENABLED 1
#endif

//#ifndef XLS_ENABLED
//#define XLS_ENABLED 1
//#endif

#ifndef ODS_ENABLED
#define ODS_ENABLED 1
#endif

#ifndef XLSX_ENABLED
#define XLSX_ENABLED 1
#endif

#ifndef ELASTIC_ENABLED
#define ELASTIC_ENABLED 1
#endif

//#ifndef WALK_ENABLED
//#define WALK_ENABLED 1
//#endif

#ifndef CARTO_ENABLED
#define CARTO_ENABLED 1
#endif

#ifndef AMIGOCLOUD_ENABLED
#define AMIGOCLOUD_ENABLED 1
#endif

#ifndef SXF_ENABLED
#define SXF_ENABLED 1
#endif

#ifndef SELAFIN_ENABLED
#define SELAFIN_ENABLED 1
#endif

#ifndef JML_ENABLED
#define JML_ENABLED 1
#endif

#ifndef PLSCENES_ENABLED
#define PLSCENES_ENABLED 1
#endif

#ifndef CSW_ENABLED
#define CSW_ENABLED 1
#endif

//#ifndef MONGODBV3_ENABLED
//#define MONGODBV3_ENABLED 1
//#endif

//#ifndef MONGODB_ENABLED
//#define MONGODB_ENABLED 1
//#endif

#ifndef VDV_ENABLED
#define VDV_ENABLED 1
#endif

#ifndef GMLAS_ENABLED
#define GMLAS_ENABLED 1
#endif

#ifndef MVT_ENABLED
#define MVT_ENABLED 1
#endif

#ifndef NGW_ENABLED
#define NGW_ENABLED 1
#endif

#ifndef MAPML_ENABLED
#define MAPML_ENABLED 1
#endif

#ifndef TIGER_ENABLED
#define TIGER_ENABLED 1
#endif

#ifndef AVC_ENABLED
#define AVC_ENABLED 1
#endif

#ifndef FRMT_vrt
#define FRMT_vrt 1
#endif

#ifndef FRMT_gtiff
#define FRMT_gtiff 1
#endif

#ifndef FRMT_nitf
#define FRMT_nitf 1
#endif

#ifndef FRMT_hfa
#define FRMT_hfa 1
#endif

#ifndef FRMT_ceos2
#define FRMT_ceos2 1
#endif

#ifndef FRMT_ceos
#define FRMT_ceos 1
#endif

#ifndef FRMT_jaxapalsar
#define FRMT_jaxapalsar 1
#endif

#ifndef FRMT_gff
#define FRMT_gff 1
#endif

#ifndef FRMT_elas
#define FRMT_elas 1
#endif

#ifndef FRMT_esric
#define FRMT_esric 1
#endif

#ifndef FRMT_aigrid
#define FRMT_aigrid 1
#endif

#ifndef FRMT_aaigrid
#define FRMT_aaigrid 1
#endif

#ifndef FRMT_sdts
#define FRMT_sdts 1
#endif

#ifndef FRMT_dted
#define FRMT_dted 1
#endif

#ifndef FRMT_png
#define FRMT_png 1
#endif

#ifndef FRMT_dds
#define FRMT_dds 1
#endif

#ifndef FRMT_gta
#define FRMT_gta 1
#endif

#ifndef FRMT_jpeg
#define FRMT_jpeg 1
#endif

#ifndef FRMT_mem
#define FRMT_mem 1
#endif

#ifndef FRMT_jdem
#define FRMT_jdem 1
#endif

//#ifndef FRMT_rasdaman
//#define FRMT_rasdaman 1
//#endif

#ifndef FRMT_gif
#define FRMT_gif 1
#endif

#ifndef FRMT_envisat
#define FRMT_envisat 1
#endif

#ifndef FRMT_fits
#define FRMT_fits 1
#endif

#ifndef FRMT_bsb
#define FRMT_bsb 1
#endif

#ifndef FRMT_xpm
#define FRMT_xpm 1
#endif

#ifndef FRMT_bmp
#define FRMT_bmp 1
#endif

#ifndef FRMT_dimap
#define FRMT_dimap 1
#endif

#ifndef FRMT_airsar
#define FRMT_airsar 1
#endif

#ifndef FRMT_rs2
#define FRMT_rs2 1
#endif

#ifndef FRMT_safe
#define FRMT_safe 1
#endif

#ifndef FRMT_pcidsk
#define FRMT_pcidsk 1
#endif

#ifndef FRMT_pcraster
#define FRMT_pcraster 1
#endif

#ifndef FRMT_ilwis
#define FRMT_ilwis 1
#endif

#ifndef FRMT_sgi
#define FRMT_sgi 1
#endif

#ifndef FRMT_srtmhgt
#define FRMT_srtmhgt 1
#endif

#ifndef FRMT_leveller
#define FRMT_leveller 1
#endif

#ifndef FRMT_terragen
#define FRMT_terragen 1
#endif

//#ifndef FRMT_netcdf
//#define FRMT_netcdf 1
//#endif

#ifndef FRMT_hdf4
#define FRMT_hdf4 1
#endif

#ifndef FRMT_pds
#define FRMT_pds 1
#endif

#ifndef FRMT_til
#define FRMT_til 1
#endif

#ifndef FRMT_ers
#define FRMT_ers 1
#endif

//#ifndef FRMT_jp2kak
//#define FRMT_jp2kak 1
//#endif

//#ifndef FRMT_jpipkak
//#define FRMT_jpipkak 1
//#endif

//#ifndef FRMT_jp2lura
//#define FRMT_jp2lura 1
//#endif

//#ifndef FRMT_ecw
//#define FRMT_ecw 1
//#endif

//#ifndef FRMT_openjpeg
//#define FRMT_openjpeg 1
//#endif

#ifndef FRMT_l1b
#define FRMT_l1b 1
#endif

#ifndef FRMT_fit
#define FRMT_fit 1
#endif

#ifndef FRMT_grib
#define FRMT_grib 1
#endif

//#ifndef FRMT_mrsid
//#define FRMT_mrsid 1
//#endif

#ifndef FRMT_jpeg2000
#define FRMT_jpeg2000 1
#endif

//#ifndef FRMT_mrsid_lidar
//#define FRMT_mrsid_lidar 1
//#endif

#ifndef FRMT_rmf
#define FRMT_rmf 1
#endif

#ifndef FRMT_wcs
#define FRMT_wcs 1
#endif

#ifndef FRMT_wms
#define FRMT_wms 1
#endif

#ifndef FRMT_msgn
#define FRMT_msgn 1
#endif

//#ifndef FRMT_msg
//#define FRMT_msg 1
//#endif

#ifndef FRMT_idrisi
#define FRMT_idrisi 1
#endif

#ifndef FRMT_ingr
#define FRMT_ingr 1
#endif

#ifndef FRMT_gsg
#define FRMT_gsg 1
#endif

#ifndef FRMT_cosar
#define FRMT_cosar 1
#endif

#ifndef FRMT_tsx
#define FRMT_tsx 1
#endif

#ifndef FRMT_coasp
#define FRMT_coasp 1
#endif

//#ifndef FRMT_tms
//#define FRMT_tms 1
//#endif

#ifndef FRMT_r
#define FRMT_r 1
#endif

#ifndef FRMT_map
#define FRMT_map 1
#endif

#ifndef FRMT_kmlsuperoverlay
#define FRMT_kmlsuperoverlay 1
#endif

#ifndef FRMT_webp
#define FRMT_webp 1
#endif

//#ifndef FRMT_pdf
//#define FRMT_pdf 1
//#endif

#ifndef FRMT_rasterlite
#define FRMT_rasterlite 1
#endif

//#ifndef FRMT_mbtiles
//#define FRMT_mbtiles 1
//#endif

#ifndef FRMT_plmosaic
#define FRMT_plmosaic 1
#endif

#ifndef FRMT_cals
#define FRMT_cals 1
#endif

#ifndef FRMT_wmts
#define FRMT_wmts 1
#endif

#ifndef FRMT_sentinel2
#define FRMT_sentinel2 1
#endif

#ifndef FRMT_mrf
#define FRMT_mrf 1
#endif

//#ifndef FRMT_tiledb
//#define FRMT_tiledb 1
//#endif

//#ifndef FRMT_rdb
//#define FRMT_rdb 1
//#endif

#ifndef FRMT_raw
#define FRMT_raw 1
#endif

#ifndef FRMT_arg
#define FRMT_arg 1
#endif

#ifndef FRMT_rik
#define FRMT_rik 1
#endif

#ifndef FRMT_usgsdem
#define FRMT_usgsdem 1
#endif

#ifndef FRMT_gxf
#define FRMT_gxf 1
#endif

//#ifndef FRMT_grass
//#define FRMT_grass 1
//#endif

//#ifndef FRMT_dods
//#define FRMT_dods 1
//#endif

//#ifndef FRMT_kea
//#define FRMT_kea 1
//#endif

#ifndef FRMT_hdf5
#define FRMT_hdf5 1
#endif

#ifndef FRMT_northwood
#define FRMT_northwood 1
#endif

#ifndef FRMT_adrg
#define FRMT_adrg 1
#endif

#ifndef FRMT_blx
#define FRMT_blx 1
#endif

#ifndef FRMT_georaster
#define FRMT_georaster 1
#endif

//#ifndef FRMT_postgisraster
//#define FRMT_postgisraster 1
//#endif

#ifndef FRMT_saga
#define FRMT_saga 1
#endif

#ifndef FRMT_xyz
#define FRMT_xyz 1
#endif

#ifndef FRMT_hf2
#define FRMT_hf2 1
#endif

//#ifndef FRMT_jpegls
//#define FRMT_jpegls 1
//#endif

#ifndef FRMT_ozi
#define FRMT_ozi 1
#endif

#ifndef FRMT_ctg
#define FRMT_ctg 1
#endif

#ifndef FRMT_zmap
#define FRMT_zmap 1
#endif

#ifndef FRMT_ngsgeoid
#define FRMT_ngsgeoid 1
#endif

#ifndef FRMT_iris
#define FRMT_iris 1
#endif

#ifndef FRMT_prf
#define FRMT_prf 1
#endif

#ifndef FRMT_rda
#define FRMT_rda 1
#endif

#ifndef FRMT_eeda
#define FRMT_eeda 1
#endif

#ifndef FRMT_daas
#define FRMT_daas 1
#endif

#ifndef FRMT_null
#define FRMT_null 1
#endif

#ifndef FRMT_sigdem
#define FRMT_sigdem 1
#endif

#ifndef FRMT_exr
#define FRMT_exr 1
#endif

#ifndef FRMT_heif
#define FRMT_heif 1
#endif

#ifndef FRMT_tga
#define FRMT_tga 1
#endif

#ifndef FRMT_ogcapi
#define FRMT_ogcapi 1
#endif

#ifndef FRMT_stacta
#define FRMT_stacta 1
#endif

#ifndef FRMT_stacit
#define FRMT_stacit 1
#endif




#endif
