#pragma once
/******************************************************************************
 * $Id$
 *
 * Project:  GDAL
 * Purpose:  JP2 Box Reader (and GMLJP2 Interpreter)
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *
 ******************************************************************************
 * Copyright (c) 2005, Frank Warmerdam <warmerdam@pobox.com>
 * Copyright (c) 2010-2013, Even Rouault <even dot rouault at spatialys.com>
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

#ifndef GDAL_JP2READER_H_INCLUDED
#define GDAL_JP2READER_H_INCLUDED

#ifndef DOXYGEN_SKIP

#include "../port/cpl_conv.h"
#include "../port/cpl_minixml.h"
#include "../port/cpl_vsi.h"
#include <gcore/gdal.h>
#include <gcore/gdal_priv.h>

/************************************************************************/
/*                              GDALJP2Box                              */
/************************************************************************/

class GDALJP2Box
{

    VSILFILE   *fpVSIL;

    char        szBoxType[5];

    GIntBig     nBoxOffset;
    GIntBig     nBoxLength;

    GIntBig     nDataOffset;

    GByte       abyUUID[16];

    GByte      *pabyData;

    CPL_DISALLOW_COPY_ASSIGN(GDALJP2Box)

public:
    HGDAL_EXPORT explicit    GDALJP2Box( VSILFILE * = nullptr );
    HGDAL_EXPORT             ~GDALJP2Box();

    HGDAL_EXPORT int         SetOffset( GIntBig nNewOffset );
    HGDAL_EXPORT int         ReadBox();

    HGDAL_EXPORT int         ReadFirst();
    HGDAL_EXPORT int         ReadNext();

    HGDAL_EXPORT int         ReadFirstChild( GDALJP2Box *poSuperBox );
    HGDAL_EXPORT int         ReadNextChild( GDALJP2Box *poSuperBox );

    GIntBig     GetBoxOffset() const { return nBoxOffset; }
    GIntBig     GetBoxLength() const { return nBoxLength; }

    GIntBig     GetDataOffset() const { return nDataOffset; }
    HGDAL_EXPORT GIntBig     GetDataLength();

    const char *GetType() { return szBoxType; }

    HGDAL_EXPORT GByte      *ReadBoxData();

    HGDAL_EXPORT int         IsSuperBox();

    HGDAL_EXPORT int         DumpReadable( FILE *, int nIndentLevel = 0 );

    VSILFILE   *GetFILE() { return fpVSIL; }

    const GByte *GetUUID() { return abyUUID; }

    // write support
    HGDAL_EXPORT void        SetType( const char * );
    HGDAL_EXPORT void        SetWritableData( int nLength, const GByte *pabyData );
    HGDAL_EXPORT void        AppendWritableData( int nLength, const void *pabyDataIn );
    HGDAL_EXPORT void        AppendUInt32( GUInt32 nVal );
    HGDAL_EXPORT void        AppendUInt16( GUInt16 nVal );
    HGDAL_EXPORT void        AppendUInt8( GByte nVal );
    const GByte*GetWritableData() { return pabyData; }

    // factory methods.
    HGDAL_EXPORT static GDALJP2Box *CreateSuperBox( const char* pszType,
                                       int nCount, GDALJP2Box **papoBoxes );
    HGDAL_EXPORT static GDALJP2Box *CreateAsocBox( int nCount, GDALJP2Box **papoBoxes );
    HGDAL_EXPORT static GDALJP2Box *CreateLblBox( const char *pszLabel );
    HGDAL_EXPORT static GDALJP2Box *CreateLabelledXMLAssoc( const char *pszLabel,
                                               const char *pszXML );
    HGDAL_EXPORT static GDALJP2Box *CreateUUIDBox( const GByte *pabyUUID,
                                      int nDataSize, const GByte *pabyData );
};

/************************************************************************/
/*                           GDALJP2Metadata                            */
/************************************************************************/

typedef struct _GDALJP2GeoTIFFBox GDALJP2GeoTIFFBox;

class GDALJP2Metadata

{
private:
    HGDAL_EXPORT void    CollectGMLData( GDALJP2Box * );
    HGDAL_EXPORT int     GMLSRSLookup( const char *pszURN );

    int    nGeoTIFFBoxesCount;
    GDALJP2GeoTIFFBox  *pasGeoTIFFBoxes;

    int    nMSIGSize;
    GByte  *pabyMSIGData;

    HGDAL_EXPORT int      GetGMLJP2GeoreferencingInfo( int& nEPSGCode,
                                          double adfOrigin[2],
                                          double adfXVector[2],
                                          double adfYVector[2],
                                          const char*& pszComment,
                                          CPLString& osDictBox,
                                          int& bNeedAxisFlip );
    HGDAL_EXPORT static CPLXMLNode* CreateGDALMultiDomainMetadataXML(
                                       GDALDataset* poSrcDS,
                                       int bMainMDDomainOnly );

    CPL_DISALLOW_COPY_ASSIGN(GDALJP2Metadata)

public:
    char  **papszGMLMetadata;

    bool    bHaveGeoTransform;
    double  adfGeoTransform[6];
    bool    bPixelIsPoint;

    OGRSpatialReference m_oSRS{};

    int         nGCPCount;
    GDAL_GCP    *pasGCPList;

    char **papszRPCMD;

    char  **papszMetadata; /* TIFFTAG_?RESOLUTION* for now from resd box */
    char   *pszXMPMetadata;
    char   *pszGDALMultiDomainMetadata; /* as serialized XML */
    char   *pszXMLIPR; /* if an IPR box with XML content has been found */

public:
    HGDAL_EXPORT         GDALJP2Metadata();
    HGDAL_EXPORT         ~GDALJP2Metadata();

    HGDAL_EXPORT int     ReadBoxes( VSILFILE * fpVSIL );

    HGDAL_EXPORT int     ParseJP2GeoTIFF();
    HGDAL_EXPORT int     ParseMSIG();
    HGDAL_EXPORT int     ParseGMLCoverageDesc();

    HGDAL_EXPORT int     ReadAndParse( VSILFILE * fpVSIL,
                          int nGEOJP2Index = 0, int nGMLJP2Index = 1,
                          int nMSIGIndex = 2, int *pnIndexUsed = nullptr );
    HGDAL_EXPORT int     ReadAndParse( const char *pszFilename, int nGEOJP2Index = 0,
                          int nGMLJP2Index = 1, int nMSIGIndex = 2,
                          int nWorldFileIndex = 3, int *pnIndexUsed = nullptr );

    // Write oriented.
    HGDAL_EXPORT void    SetSpatialRef( const OGRSpatialReference *poSRS );
    HGDAL_EXPORT void    SetGeoTransform( double * );
    HGDAL_EXPORT void    SetGCPs( int, const GDAL_GCP * );
    HGDAL_EXPORT void    SetRPCMD( char** papszRPCMDIn );

    HGDAL_EXPORT GDALJP2Box *CreateJP2GeoTIFF();
    HGDAL_EXPORT GDALJP2Box *CreateGMLJP2( int nXSize, int nYSize );
    HGDAL_EXPORT GDALJP2Box *CreateGMLJP2V2( int nXSize, int nYSize,
                                const char* pszDefFilename,
                                GDALDataset* poSrcDS );

    HGDAL_EXPORT static GDALJP2Box* CreateGDALMultiDomainMetadataXMLBox(
                                       GDALDataset* poSrcDS,
                                       int bMainMDDomainOnly );
    HGDAL_EXPORT static GDALJP2Box** CreateXMLBoxes( GDALDataset* poSrcDS,
                                        int* pnBoxes );
    HGDAL_EXPORT static GDALJP2Box *CreateXMPBox ( GDALDataset* poSrcDS );
    HGDAL_EXPORT static GDALJP2Box *CreateIPRBox ( GDALDataset* poSrcDS );
    HGDAL_EXPORT static int   IsUUID_MSI(const GByte *abyUUID);
    HGDAL_EXPORT static int   IsUUID_XMP(const GByte *abyUUID);
};

#endif /* #ifndef DOXYGEN_SKIP */

#endif /* ndef GDAL_JP2READER_H_INCLUDED */
