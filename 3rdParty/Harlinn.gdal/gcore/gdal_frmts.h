#pragma once
/******************************************************************************
 * $Id$
 *
 * Project:  GDAL
 * Purpose:  Prototypes for all format specific driver initialization.
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *
 ******************************************************************************
 * Copyright (c) 2001, Frank Warmerdam
 * Copyright (c) 2007-2014, Even Rouault <even dot rouault at spatialys.com>
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#ifndef GDAL_FRMTS_H_INCLUDED
#define GDAL_FRMTS_H_INCLUDED

#include "port\cpl_port.h"

CPL_C_START
HGDAL_EXPORT void GDALRegister_GTiff(void);
HGDAL_EXPORT void GDALRegister_GXF(void);
HGDAL_EXPORT void GDALRegister_HFA(void);
HGDAL_EXPORT void GDALRegister_AAIGrid(void);
HGDAL_EXPORT void GDALRegister_GRASSASCIIGrid(void);
HGDAL_EXPORT void GDALRegister_ISG(void);
HGDAL_EXPORT void GDALRegister_AIGrid(void);
// void CPL_DLL GDALRegister_AIGrid2(void);
HGDAL_EXPORT void GDALRegister_CEOS(void);
HGDAL_EXPORT void GDALRegister_SAR_CEOS(void);
HGDAL_EXPORT void GDALRegister_SDTS(void);
HGDAL_EXPORT void GDALRegister_ELAS(void);
HGDAL_EXPORT void GDALRegister_EHdr(void);
HGDAL_EXPORT void GDALRegister_GenBin(void);
HGDAL_EXPORT void GDALRegister_PAux(void);
HGDAL_EXPORT void GDALRegister_ENVI(void);
HGDAL_EXPORT void GDALRegister_DOQ1(void);
HGDAL_EXPORT void GDALRegister_DOQ2(void);
HGDAL_EXPORT void GDALRegister_DTED(void);
HGDAL_EXPORT void GDALRegister_MFF(void);
HGDAL_EXPORT void GDALRegister_HKV(void);
HGDAL_EXPORT void GDALRegister_PNG(void);
HGDAL_EXPORT void GDALRegister_DDS(void);
HGDAL_EXPORT void GDALRegister_GTA(void);
HGDAL_EXPORT void GDALRegister_JPEG(void);
HGDAL_EXPORT void GDALRegister_JPEG2000(void);
HGDAL_EXPORT void GDALRegister_JP2KAK(void);
HGDAL_EXPORT void GDALRegister_JPIPKAK(void);
HGDAL_EXPORT void GDALRegister_MEM(void);
HGDAL_EXPORT void GDALRegister_JDEM(void);
HGDAL_EXPORT void GDALRegister_RASDAMAN(void);
HGDAL_EXPORT void GDALRegister_GRASS(void);
HGDAL_EXPORT void GDALRegister_PNM(void);
HGDAL_EXPORT void GDALRegister_GIF(void);
HGDAL_EXPORT void GDALRegister_BIGGIF(void);
HGDAL_EXPORT void GDALRegister_Envisat(void);
HGDAL_EXPORT void GDALRegister_FITS(void);
HGDAL_EXPORT void GDALRegister_ECW(void);
HGDAL_EXPORT void GDALRegister_JP2ECW(void);
HGDAL_EXPORT void GDALRegister_ECW_JP2ECW();
HGDAL_EXPORT void GDALRegister_FujiBAS(void);
HGDAL_EXPORT void GDALRegister_FIT(void);
HGDAL_EXPORT void GDALRegister_VRT(void);
HGDAL_EXPORT void GDALRegister_USGSDEM(void);
HGDAL_EXPORT void GDALRegister_FAST(void);
HGDAL_EXPORT void GDALRegister_HDF4(void);
HGDAL_EXPORT void GDALRegister_HDF4Image(void);
HGDAL_EXPORT void GDALRegister_L1B(void);
HGDAL_EXPORT void GDALRegister_LDF(void);
HGDAL_EXPORT void GDALRegister_BSB(void);
HGDAL_EXPORT void GDALRegister_XPM(void);
HGDAL_EXPORT void GDALRegister_BMP(void);
HGDAL_EXPORT void GDALRegister_GSC(void);
HGDAL_EXPORT void GDALRegister_NITF(void);
HGDAL_EXPORT void GDALRegister_RPFTOC(void);
HGDAL_EXPORT void GDALRegister_ECRGTOC(void);
HGDAL_EXPORT void GDALRegister_MrSID(void);
HGDAL_EXPORT void GDALRegister_MG4Lidar(void);
HGDAL_EXPORT void GDALRegister_PCIDSK(void);
HGDAL_EXPORT void GDALRegister_BT(void);
HGDAL_EXPORT void GDALRegister_DODS(void);
HGDAL_EXPORT void GDALRegister_GMT(void);
HGDAL_EXPORT void GDALRegister_netCDF(void);
HGDAL_EXPORT void GDALRegister_LAN(void);
HGDAL_EXPORT void GDALRegister_CPG(void);
HGDAL_EXPORT void GDALRegister_AirSAR(void);
HGDAL_EXPORT void GDALRegister_RS2(void);
HGDAL_EXPORT void GDALRegister_ILWIS(void);
HGDAL_EXPORT void GDALRegister_PCRaster(void);
HGDAL_EXPORT void GDALRegister_IDA(void);
HGDAL_EXPORT void GDALRegister_NDF(void);
HGDAL_EXPORT void GDALRegister_RMF(void);
HGDAL_EXPORT void GDALRegister_BAG(void);
HGDAL_EXPORT void GDALRegister_HDF5(void);
HGDAL_EXPORT void GDALRegister_HDF5Image(void);
HGDAL_EXPORT void GDALRegister_MSGN(void);
HGDAL_EXPORT void GDALRegister_MSG(void);
HGDAL_EXPORT void GDALRegister_RIK(void);
HGDAL_EXPORT void GDALRegister_Leveller(void);
HGDAL_EXPORT void GDALRegister_SGI(void);
HGDAL_EXPORT void GDALRegister_SRTMHGT(void);
HGDAL_EXPORT void GDALRegister_DIPEx(void);
HGDAL_EXPORT void GDALRegister_ISIS3(void);
HGDAL_EXPORT void GDALRegister_ISIS2(void);
HGDAL_EXPORT void GDALRegister_PDS(void);
HGDAL_EXPORT void GDALRegister_PDS4(void);
HGDAL_EXPORT void GDALRegister_VICAR(void);
HGDAL_EXPORT void GDALRegister_IDRISI(void);
HGDAL_EXPORT void GDALRegister_Terragen(void);
HGDAL_EXPORT void GDALRegister_WCS(void);
HGDAL_EXPORT void GDALRegister_WMS(void);
HGDAL_EXPORT void GDALRegister_HTTP(void);
HGDAL_EXPORT void GDALRegister_GSAG(void);
HGDAL_EXPORT void GDALRegister_GSBG(void);
HGDAL_EXPORT void GDALRegister_GS7BG(void);
HGDAL_EXPORT void GDALRegister_GRIB(void);
HGDAL_EXPORT void GDALRegister_INGR(void);
HGDAL_EXPORT void GDALRegister_ERS(void);
HGDAL_EXPORT void GDALRegister_PALSARJaxa(void);
HGDAL_EXPORT void GDALRegister_DIMAP();
HGDAL_EXPORT void GDALRegister_GFF(void);
HGDAL_EXPORT void GDALRegister_COSAR(void);
HGDAL_EXPORT void GDALRegister_TSX(void);
HGDAL_EXPORT void GDALRegister_ADRG(void);
HGDAL_EXPORT void GDALRegister_SRP(void);
HGDAL_EXPORT void GDALRegister_COASP(void);
HGDAL_EXPORT void GDALRegister_BLX(void);
HGDAL_EXPORT void GDALRegister_LCP(void);
HGDAL_EXPORT void GDALRegister_TMS(void);
HGDAL_EXPORT void GDALRegister_EIR(void);
HGDAL_EXPORT void GDALRegister_ESRIC(void);
HGDAL_EXPORT void GDALRegister_GEOR(void);
HGDAL_EXPORT void GDALRegister_TIL(void);
HGDAL_EXPORT void GDALRegister_R(void);
HGDAL_EXPORT void GDALRegister_Rasterlite(void);
HGDAL_EXPORT void GDALRegister_PostGISRaster(void);
HGDAL_EXPORT void GDALRegister_NWT_GRD(void);
HGDAL_EXPORT void GDALRegister_NWT_GRC(void);
HGDAL_EXPORT void GDALRegister_SAGA(void);
HGDAL_EXPORT void GDALRegister_KMLSUPEROVERLAY(void);
HGDAL_EXPORT void GDALRegister_GTX(void);
HGDAL_EXPORT void GDALRegister_LOSLAS(void);
HGDAL_EXPORT void GDALRegister_Istar(void);
HGDAL_EXPORT void GDALRegister_NTv2(void);
HGDAL_EXPORT void GDALRegister_CTable2(void);
HGDAL_EXPORT void GDALRegister_JP2OpenJPEG(void);
HGDAL_EXPORT void GDALRegister_XYZ(void);
HGDAL_EXPORT void GDALRegister_HF2(void);
HGDAL_EXPORT void GDALRegister_PDF(void);
HGDAL_EXPORT void GDALRegister_JPEGLS(void);
HGDAL_EXPORT void GDALRegister_MAP(void);
HGDAL_EXPORT void GDALRegister_OZI(void);
HGDAL_EXPORT void GDALRegister_ACE2(void);
HGDAL_EXPORT void GDALRegister_CTG(void);
HGDAL_EXPORT void GDALRegister_SNODAS(void);
HGDAL_EXPORT void GDALRegister_WEBP(void);
HGDAL_EXPORT void GDALRegister_ZMap(void);
HGDAL_EXPORT void GDALRegister_NGSGEOID(void);
HGDAL_EXPORT void GDALRegister_MBTiles(void);
HGDAL_EXPORT void GDALRegister_ARG(void);
HGDAL_EXPORT void GDALRegister_IRIS(void);
HGDAL_EXPORT void GDALRegister_KRO(void);
HGDAL_EXPORT void GDALRegister_KEA(void);
HGDAL_EXPORT void GDALRegister_ROIPAC(void);
HGDAL_EXPORT void GDALRegister_PLMOSAIC(void);
HGDAL_EXPORT void GDALRegister_CALS(void);
HGDAL_EXPORT void GDALRegister_ISCE(void);
HGDAL_EXPORT void GDALRegister_WMTS(void);
HGDAL_EXPORT void GDALRegister_SAFE(void);
HGDAL_EXPORT void GDALRegister_SENTINEL2(void);
HGDAL_EXPORT void GDALRegister_mrf(void);
HGDAL_EXPORT void GDALRegister_RRASTER(void);
HGDAL_EXPORT void GDALRegister_Derived(void);
HGDAL_EXPORT void GDALRegister_JP2Lura(void);
HGDAL_EXPORT void GDALRegister_PRF(void);
HGDAL_EXPORT void GDALRegister_NULL(void);
HGDAL_EXPORT void GDALRegister_RDA(void);
HGDAL_EXPORT void GDALRegister_EEDAI(void);
HGDAL_EXPORT void GDALRegister_EEDA(void);
HGDAL_EXPORT void GDALRegister_SIGDEM(void);
HGDAL_EXPORT void GDALRegister_BYN(void);
HGDAL_EXPORT void GDALRegister_TileDB(void);
HGDAL_EXPORT void GDALRegister_DAAS(void);
HGDAL_EXPORT void GDALRegister_COG(void);
HGDAL_EXPORT void GDALRegister_RDB(void);
HGDAL_EXPORT void GDALRegister_EXR(void);
HGDAL_EXPORT void GDALRegister_HEIF(void);
HGDAL_EXPORT void GDALRegister_TGA(void);
HGDAL_EXPORT void GDALRegister_OGCAPI(void);
HGDAL_EXPORT void GDALRegister_STACTA(void);
HGDAL_EXPORT void GDALRegister_Zarr(void);
HGDAL_EXPORT void GDALRegister_STACIT(void);
CPL_C_END

#endif /* ndef GDAL_FRMTS_H_INCLUDED */
