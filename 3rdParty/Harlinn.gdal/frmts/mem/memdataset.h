#pragma once
/******************************************************************************
 * $Id$
 *
 * Project:  Memory Array Translator
 * Purpose:  Declaration of MEMDataset, and MEMRasterBand.
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *
 ******************************************************************************
 * Copyright (c) 2000, Frank Warmerdam
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

#ifndef MEMDATASET_H_INCLUDED
#define MEMDATASET_H_INCLUDED

#include <gcore/gdal_pam.h>
#include <gcore/gdal_priv.h>
#include <gcore/gdal_rat.h>

#include <memory>

CPL_C_START
/* Caution: if changing this prototype, also change in swig/include/gdal_python.i
   where it is redefined */
    HGDAL_EXPORT GDALRasterBandH MEMCreateRasterBand( GDALDataset *, int, GByte *,
                                             GDALDataType, int, int, int );
HGDAL_EXPORT GDALRasterBandH MEMCreateRasterBandEx( GDALDataset *, int, GByte *,
                                               GDALDataType, GSpacing, GSpacing,
                                               int );
CPL_C_END

/************************************************************************/
/*                            MEMDataset                                */
/************************************************************************/

class MEMRasterBand;

class MEMDataset CPL_NON_FINAL: public GDALDataset
{
    CPL_DISALLOW_COPY_ASSIGN(MEMDataset)

    friend class MEMRasterBand;

    int         bGeoTransformSet;
    double      adfGeoTransform[6];

    OGRSpatialReference m_oSRS{};

    int          m_nGCPCount;
    GDAL_GCP    *m_pasGCPs;
    CPLString    osGCPProjection;

    int          m_nOverviewDSCount;
    GDALDataset  **m_papoOverviewDS;

    struct Private;
    std::unique_ptr<Private> m_poPrivate;

#if 0
  protected:
    virtual int                 EnterReadWrite(GDALRWFlag eRWFlag);
    virtual void                LeaveReadWrite();
#endif

  public:
    HGDAL_EXPORT              MEMDataset();
    HGDAL_EXPORT virtual      ~MEMDataset();

    HGDAL_EXPORT const OGRSpatialReference* GetSpatialRef() const override;
    HGDAL_EXPORT CPLErr SetSpatialRef(const OGRSpatialReference* poSRS) override;

    HGDAL_EXPORT virtual CPLErr GetGeoTransform( double * ) override;
    HGDAL_EXPORT virtual CPLErr SetGeoTransform( double * ) override;

    HGDAL_EXPORT virtual void *GetInternalHandle( const char * ) override;

    HGDAL_EXPORT virtual int    GetGCPCount() override;
    HGDAL_EXPORT const char *_GetGCPProjection() override;
    const OGRSpatialReference* GetGCPSpatialRef() const override {
        return GetGCPSpatialRefFromOldGetGCPProjection();
    }
    HGDAL_EXPORT virtual const GDAL_GCP *GetGCPs() override;
    HGDAL_EXPORT CPLErr _SetGCPs( int nGCPCount, const GDAL_GCP *pasGCPList,
                    const char *pszGCPProjection ) override;
    using GDALDataset::SetGCPs;
    CPLErr SetGCPs( int nGCPCount, const GDAL_GCP *pasGCPList,
                    const OGRSpatialReference* poSRS ) override {
        return OldSetGCPsFromNew(nGCPCount, pasGCPList, poSRS);
    }
    HGDAL_EXPORT virtual CPLErr        AddBand( GDALDataType eType,
                                   char **papszOptions=nullptr ) override;
    HGDAL_EXPORT virtual CPLErr  IRasterIO( GDALRWFlag eRWFlag,
                               int nXOff, int nYOff, int nXSize, int nYSize,
                               void * pData, int nBufXSize, int nBufYSize,
                               GDALDataType eBufType,
                               int nBandCount, int *panBandMap,
                               GSpacing nPixelSpaceBuf,
                               GSpacing nLineSpaceBuf,
                               GSpacing nBandSpaceBuf,
                               GDALRasterIOExtraArg* psExtraArg) override;
    HGDAL_EXPORT virtual CPLErr  IBuildOverviews( const char *pszResampling,
                                     int nOverviews, int *panOverviewList,
                                     int nListBands, int *panBandList,
                                     GDALProgressFunc pfnProgress,
                                     void * pProgressData ) override;

    HGDAL_EXPORT virtual CPLErr          CreateMaskBand( int nFlagsIn ) override;

    HGDAL_EXPORT std::shared_ptr<GDALGroup> GetRootGroup() const override;

    HGDAL_EXPORT static GDALDataset *Open( GDALOpenInfo * );
    HGDAL_EXPORT static GDALDataset *Create( const char * pszFilename,
                                int nXSize, int nYSize, int nBands,
                                GDALDataType eType, char ** papszParamList );
    HGDAL_EXPORT static GDALDataset *CreateMultiDimensional( const char * pszFilename,
                                                CSLConstList papszRootGroupOptions,
                                                CSLConstList papszOptions );
};

/************************************************************************/
/*                            MEMRasterBand                             */
/************************************************************************/

class MEMRasterBand CPL_NON_FINAL: public GDALPamRasterBand
{
  private:
                MEMRasterBand( GByte *pabyDataIn, GDALDataType eTypeIn,
                               int nXSizeIn, int nYSizeIn );

    CPL_DISALLOW_COPY_ASSIGN(MEMRasterBand)

  protected:
    friend      class MEMDataset;

    GByte      *pabyData;
    GSpacing    nPixelOffset;
    GSpacing    nLineOffset;
    int         bOwnData;

    int         bNoDataSet;
    double      dfNoData;

    std::unique_ptr<GDALColorTable> m_poColorTable;
    GDALColorInterp eColorInterp;

    CPLString      m_osUnitType;
    CPLStringList  m_aosCategoryNames;

    double         dfOffset;
    double         dfScale;

    CPLXMLNode    *psSavedHistograms;

    std::unique_ptr<GDALRasterAttributeTable> m_poRAT;

  public:
    HGDAL_EXPORT                MEMRasterBand( GDALDataset *poDS, int nBand,
                                  GByte *pabyData, GDALDataType eType,
                                  GSpacing nPixelOffset, GSpacing nLineOffset,
                                  int bAssumeOwnership,
                                  const char * pszPixelType = nullptr );
    HGDAL_EXPORT virtual        ~MEMRasterBand();

    HGDAL_EXPORT virtual CPLErr IReadBlock( int, int, void * ) override;
    HGDAL_EXPORT virtual CPLErr IWriteBlock( int, int, void * ) override;
    HGDAL_EXPORT virtual CPLErr IRasterIO( GDALRWFlag eRWFlag,
                                  int nXOff, int nYOff, int nXSize, int nYSize,
                                  void * pData, int nBufXSize, int nBufYSize,
                                  GDALDataType eBufType,
                                  GSpacing nPixelSpaceBuf,
                                  GSpacing nLineSpaceBuf,
                                  GDALRasterIOExtraArg* psExtraArg ) override;
    HGDAL_EXPORT virtual double GetNoDataValue( int *pbSuccess = nullptr ) override;
    HGDAL_EXPORT virtual CPLErr SetNoDataValue( double ) override;
    HGDAL_EXPORT virtual CPLErr DeleteNoDataValue() override;

    HGDAL_EXPORT virtual GDALColorInterp GetColorInterpretation() override;
    HGDAL_EXPORT virtual GDALColorTable *GetColorTable() override;
    HGDAL_EXPORT virtual CPLErr SetColorTable( GDALColorTable * ) override;

    HGDAL_EXPORT virtual GDALRasterAttributeTable *GetDefaultRAT() override;
    HGDAL_EXPORT virtual CPLErr SetDefaultRAT( const GDALRasterAttributeTable * poRAT ) override;

    HGDAL_EXPORT virtual CPLErr SetColorInterpretation( GDALColorInterp ) override;

    HGDAL_EXPORT virtual const char *GetUnitType() override;
    HGDAL_EXPORT CPLErr SetUnitType( const char * ) override;

    HGDAL_EXPORT virtual char **GetCategoryNames() override;
    HGDAL_EXPORT virtual CPLErr SetCategoryNames( char ** ) override;

    HGDAL_EXPORT virtual double GetOffset( int *pbSuccess = nullptr ) override;
    HGDAL_EXPORT CPLErr SetOffset( double ) override;
    HGDAL_EXPORT virtual double GetScale( int *pbSuccess = nullptr ) override;
    HGDAL_EXPORT CPLErr SetScale( double ) override;

    HGDAL_EXPORT virtual CPLErr SetDefaultHistogram( double dfMin, double dfMax,
                                        int nBuckets, GUIntBig *panHistogram ) override;
    HGDAL_EXPORT virtual CPLErr GetDefaultHistogram( double *pdfMin, double *pdfMax,
                                        int *pnBuckets,
                                        GUIntBig ** ppanHistogram,
                                        int bForce,
                                        GDALProgressFunc, void *pProgressData) override;

    HGDAL_EXPORT virtual int GetOverviewCount() override;
    HGDAL_EXPORT virtual GDALRasterBand *GetOverview(int) override;

    HGDAL_EXPORT virtual CPLErr          CreateMaskBand( int nFlagsIn ) override;

    // Allow access to MEM driver's private internal memory buffer.
    GByte *GetData() const { return(pabyData); }
};

#endif /* ndef MEMDATASET_H_INCLUDED */
