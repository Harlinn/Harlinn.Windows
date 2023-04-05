#pragma once
/******************************************************************************
 * $Id$
 *
 * Project:  GDAL Utilities
 * Purpose:  GDAL Utilities Public Declarations.
 * Author:   Faza Mahamood, fazamhd at gmail dot com
 *
 * ****************************************************************************
 * Copyright (c) 1998, Frank Warmerdam
 * Copyright (c) 2007-2015, Even Rouault <even.rouault at spatialys.com>
 * Copyright (c) 2015, Faza Mahamood
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

#ifndef GDAL_UTILS_H_INCLUDED
#define GDAL_UTILS_H_INCLUDED

/**
 * \file gdal_utils.h
 *
 * Public (C callable) GDAL Utilities entry points.
 *
 * @since GDAL 2.1
 */

#include "..\port\cpl_port.h"
#include "..\gcore\gdal.h"

CPL_C_START

/*! Options for GDALInfo(). Opaque type */
typedef struct GDALInfoOptions GDALInfoOptions;

/** Opaque type */
typedef struct GDALInfoOptionsForBinary GDALInfoOptionsForBinary;

HGDAL_EXPORT GDALInfoOptions *GDALInfoOptionsNew(char** papszArgv, GDALInfoOptionsForBinary* psOptionsForBinary);

HGDAL_EXPORT void GDALInfoOptionsFree( GDALInfoOptions *psOptions );

HGDAL_EXPORT char *GDALInfo( GDALDatasetH hDataset, const GDALInfoOptions *psOptions );

/*! Options for GDALTranslate(). Opaque type */
typedef struct GDALTranslateOptions GDALTranslateOptions;

/** Opaque type */
typedef struct GDALTranslateOptionsForBinary GDALTranslateOptionsForBinary;

HGDAL_EXPORT GDALTranslateOptions *GDALTranslateOptionsNew(char** papszArgv,
                                                      GDALTranslateOptionsForBinary* psOptionsForBinary);

HGDAL_EXPORT void GDALTranslateOptionsFree( GDALTranslateOptions *psOptions );

HGDAL_EXPORT void GDALTranslateOptionsSetProgress( GDALTranslateOptions *psOptions,
                                              GDALProgressFunc pfnProgress,
                                              void *pProgressData );

HGDAL_EXPORT GDALDatasetH GDALTranslate(const char *pszDestFilename,
                                   GDALDatasetH hSrcDataset,
                                   const GDALTranslateOptions *psOptions,
                                   int *pbUsageError);

/*! Options for GDALWarp(). Opaque type */
typedef struct GDALWarpAppOptions GDALWarpAppOptions;

/** Opaque type */
typedef struct GDALWarpAppOptionsForBinary GDALWarpAppOptionsForBinary;

HGDAL_EXPORT GDALWarpAppOptions *GDALWarpAppOptionsNew(char** papszArgv,
                                                      GDALWarpAppOptionsForBinary* psOptionsForBinary);

HGDAL_EXPORT void GDALWarpAppOptionsFree( GDALWarpAppOptions *psOptions );

HGDAL_EXPORT void GDALWarpAppOptionsSetProgress( GDALWarpAppOptions *psOptions,
                                              GDALProgressFunc pfnProgress,
                                              void *pProgressData );
HGDAL_EXPORT void GDALWarpAppOptionsSetQuiet( GDALWarpAppOptions *psOptions,
                                         int bQuiet );
HGDAL_EXPORT void GDALWarpAppOptionsSetWarpOption( GDALWarpAppOptions *psOptions,
                                              const char* pszKey,
                                              const char* pszValue );

HGDAL_EXPORT GDALDatasetH GDALWarp( const char *pszDest, GDALDatasetH hDstDS,
                               int nSrcCount, GDALDatasetH *pahSrcDS,
                               const GDALWarpAppOptions *psOptions, int *pbUsageError );

/*! Options for GDALVectorTranslate(). Opaque type */
typedef struct GDALVectorTranslateOptions GDALVectorTranslateOptions;

/** Opaque type */
typedef struct GDALVectorTranslateOptionsForBinary GDALVectorTranslateOptionsForBinary;

HGDAL_EXPORT GDALVectorTranslateOptions *GDALVectorTranslateOptionsNew(char** papszArgv,
                                                      GDALVectorTranslateOptionsForBinary* psOptionsForBinary);

HGDAL_EXPORT void GDALVectorTranslateOptionsFree( GDALVectorTranslateOptions *psOptions );

HGDAL_EXPORT void GDALVectorTranslateOptionsSetProgress( GDALVectorTranslateOptions *psOptions,
                                              GDALProgressFunc pfnProgress,
                                              void *pProgressData );

HGDAL_EXPORT GDALDatasetH GDALVectorTranslate( const char *pszDest, GDALDatasetH hDstDS, int nSrcCount,
                               GDALDatasetH *pahSrcDS,
                               const GDALVectorTranslateOptions *psOptions, int *pbUsageError );

/*! Options for GDALDEMProcessing(). Opaque type */
typedef struct GDALDEMProcessingOptions GDALDEMProcessingOptions;

/** Opaque type */
typedef struct GDALDEMProcessingOptionsForBinary GDALDEMProcessingOptionsForBinary;

HGDAL_EXPORT GDALDEMProcessingOptions *GDALDEMProcessingOptionsNew(char** papszArgv,
                                                      GDALDEMProcessingOptionsForBinary* psOptionsForBinary);

HGDAL_EXPORT void GDALDEMProcessingOptionsFree( GDALDEMProcessingOptions *psOptions );

HGDAL_EXPORT void GDALDEMProcessingOptionsSetProgress( GDALDEMProcessingOptions *psOptions,
                                              GDALProgressFunc pfnProgress,
                                              void *pProgressData );

HGDAL_EXPORT GDALDatasetH GDALDEMProcessing(const char *pszDestFilename,
                                       GDALDatasetH hSrcDataset,
                                       const char* pszProcessing,
                                       const char* pszColorFilename,
                                       const GDALDEMProcessingOptions *psOptions,
                                       int *pbUsageError);

/*! Options for GDALNearblack(). Opaque type */
typedef struct GDALNearblackOptions GDALNearblackOptions;

/** Opaque type */
typedef struct GDALNearblackOptionsForBinary GDALNearblackOptionsForBinary;

HGDAL_EXPORT GDALNearblackOptions *GDALNearblackOptionsNew(char** papszArgv,
                                                      GDALNearblackOptionsForBinary* psOptionsForBinary);

HGDAL_EXPORT void GDALNearblackOptionsFree( GDALNearblackOptions *psOptions );

HGDAL_EXPORT void GDALNearblackOptionsSetProgress( GDALNearblackOptions *psOptions,
                                              GDALProgressFunc pfnProgress,
                                              void *pProgressData );

HGDAL_EXPORT GDALDatasetH GDALNearblack( const char *pszDest, GDALDatasetH hDstDS,
                                    GDALDatasetH hSrcDS,
                                    const GDALNearblackOptions *psOptions, int *pbUsageError );

/*! Options for GDALGrid(). Opaque type */
typedef struct GDALGridOptions GDALGridOptions;

/** Opaque type */
typedef struct GDALGridOptionsForBinary GDALGridOptionsForBinary;

HGDAL_EXPORT GDALGridOptions *GDALGridOptionsNew(char** papszArgv,
                                                      GDALGridOptionsForBinary* psOptionsForBinary);

HGDAL_EXPORT void GDALGridOptionsFree( GDALGridOptions *psOptions );

HGDAL_EXPORT void GDALGridOptionsSetProgress( GDALGridOptions *psOptions,
                                              GDALProgressFunc pfnProgress,
                                              void *pProgressData );

HGDAL_EXPORT GDALDatasetH GDALGrid( const char *pszDest,
                               GDALDatasetH hSrcDS,
                               const GDALGridOptions *psOptions, int *pbUsageError );

/*! Options for GDALRasterize(). Opaque type */
typedef struct GDALRasterizeOptions GDALRasterizeOptions;

/** Opaque type */
typedef struct GDALRasterizeOptionsForBinary GDALRasterizeOptionsForBinary;

HGDAL_EXPORT GDALRasterizeOptions *GDALRasterizeOptionsNew(char** papszArgv,
                                                      GDALRasterizeOptionsForBinary* psOptionsForBinary);

HGDAL_EXPORT void GDALRasterizeOptionsFree( GDALRasterizeOptions *psOptions );

HGDAL_EXPORT void GDALRasterizeOptionsSetProgress( GDALRasterizeOptions *psOptions,
                                              GDALProgressFunc pfnProgress,
                                              void *pProgressData );

HGDAL_EXPORT GDALDatasetH GDALRasterize( const char *pszDest, GDALDatasetH hDstDS,
                                    GDALDatasetH hSrcDS,
                                    const GDALRasterizeOptions *psOptions, int *pbUsageError );

/*! Options for GDALBuildVRT(). Opaque type */
typedef struct GDALBuildVRTOptions GDALBuildVRTOptions;

/** Opaque type */
typedef struct GDALBuildVRTOptionsForBinary GDALBuildVRTOptionsForBinary;

HGDAL_EXPORT GDALBuildVRTOptions *GDALBuildVRTOptionsNew(char** papszArgv,
                                                      GDALBuildVRTOptionsForBinary* psOptionsForBinary);

HGDAL_EXPORT void GDALBuildVRTOptionsFree( GDALBuildVRTOptions *psOptions );

HGDAL_EXPORT void GDALBuildVRTOptionsSetProgress( GDALBuildVRTOptions *psOptions,
                                              GDALProgressFunc pfnProgress,
                                              void *pProgressData );

HGDAL_EXPORT GDALDatasetH GDALBuildVRT( const char *pszDest,
                                   int nSrcCount, GDALDatasetH *pahSrcDS, const char* const* papszSrcDSNames,
                                   const GDALBuildVRTOptions *psOptions, int *pbUsageError );


/*! Options for GDALMultiDimInfo(). Opaque type */
typedef struct GDALMultiDimInfoOptions GDALMultiDimInfoOptions;

/** Opaque type */
typedef struct GDALMultiDimInfoOptionsForBinary GDALMultiDimInfoOptionsForBinary;

HGDAL_EXPORT GDALMultiDimInfoOptions *GDALMultiDimInfoOptionsNew(char** papszArgv, GDALMultiDimInfoOptionsForBinary* psOptionsForBinary);

HGDAL_EXPORT void GDALMultiDimInfoOptionsFree( GDALMultiDimInfoOptions *psOptions );

HGDAL_EXPORT char *GDALMultiDimInfo( GDALDatasetH hDataset, const GDALMultiDimInfoOptions *psOptions );


/*! Options for GDALMultiDimTranslate(). Opaque type */
typedef struct GDALMultiDimTranslateOptions GDALMultiDimTranslateOptions;

/** Opaque type */
typedef struct GDALMultiDimTranslateOptionsForBinary GDALMultiDimTranslateOptionsForBinary;

HGDAL_EXPORT GDALMultiDimTranslateOptions *GDALMultiDimTranslateOptionsNew(char** papszArgv, GDALMultiDimTranslateOptionsForBinary* psOptionsForBinary);

HGDAL_EXPORT void GDALMultiDimTranslateOptionsFree( GDALMultiDimTranslateOptions *psOptions );

HGDAL_EXPORT void GDALMultiDimTranslateOptionsSetProgress( GDALMultiDimTranslateOptions *psOptions,
                                              GDALProgressFunc pfnProgress,
                                              void *pProgressData );

HGDAL_EXPORT GDALDatasetH GDALMultiDimTranslate( const char* pszDest,
                                            GDALDatasetH hDstDataset,
                                            int nSrcCount, GDALDatasetH *pahSrcDS,
                                            const GDALMultiDimTranslateOptions *psOptions,
                                            int *pbUsageError );

CPL_C_END

#endif /* GDAL_UTILS_H_INCLUDED */
