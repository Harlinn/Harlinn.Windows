#pragma once
/******************************************************************************
 * $Id$
 *
 * Project:  OpenGIS Simple Features Reference Implementation
 * Purpose:  Classes related to format registration, and file opening.
 * Author:   Frank Warmerdam, warmerda@home.com
 *
 ******************************************************************************
 * Copyright (c) 1999,  Les Technologies SoftMap Inc.
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

#ifndef OGRSF_FRMTS_H_INCLUDED
#define OGRSF_FRMTS_H_INCLUDED

#include "../../port/cpl_progress.h"
#include "../../ogr/ogr_feature.h"
#include "../../ogr/ogr_featurestyle.h"
#include "../../gcore/gdal_priv.h"

#include <memory>

/**
 * \file ogrsf_frmts.h
 *
 * Classes related to registration of format support, and opening datasets.
 */

//! @cond Doxygen_Suppress
#if !defined(GDAL_COMPILATION) && !defined(SUPPRESS_DEPRECATION_WARNINGS)
#define OGR_DEPRECATED(x) CPL_WARN_DEPRECATED(x)
#else
#define OGR_DEPRECATED(x)
#endif
//! @endcond

class OGRLayerAttrIndex;
class OGRSFDriver;

/************************************************************************/
/*                               OGRLayer                               */
/************************************************************************/

/**
 * This class represents a layer of simple features, with access methods.
 *
 */

/* Note: any virtual method added to this class must also be added in the */
/* OGRLayerDecorator and OGRMutexedLayer classes. */

class OGRLayer : public GDALMajorObject
{
  private:
    struct Private;
    std::unique_ptr<Private> m_poPrivate;

    HGDAL_EXPORT void         ConvertGeomsIfNecessary( OGRFeature *poFeature );

    class FeatureIterator
    {
            struct Private;
            std::unique_ptr<Private> m_poPrivate;
        public:
            HGDAL_EXPORT FeatureIterator(OGRLayer* poLayer, bool bStart);
            HGDAL_EXPORT FeatureIterator(FeatureIterator&& oOther) noexcept; // declared but not defined. Needed for gcc 5.4 at least
            HGDAL_EXPORT ~FeatureIterator();
            HGDAL_EXPORT OGRFeatureUniquePtr& operator*();
            HGDAL_EXPORT FeatureIterator& operator++();
            HGDAL_EXPORT bool operator!=(const FeatureIterator& it) const;
    };

    friend inline FeatureIterator begin(OGRLayer* poLayer);
    friend inline FeatureIterator end(OGRLayer* poLayer);

    CPL_DISALLOW_COPY_ASSIGN(OGRLayer)

  protected:
//! @cond Doxygen_Suppress
    int          m_bFilterIsEnvelope;
    OGRGeometry *m_poFilterGeom;
    OGRPreparedGeometry *m_pPreparedFilterGeom; /* m_poFilterGeom compiled as a prepared geometry */
    OGREnvelope  m_sFilterEnvelope;
    int          m_iGeomFieldFilter; // specify the index on which the spatial
                                     // filter is active.

    HGDAL_EXPORT int          FilterGeometry( OGRGeometry * );
    //int          FilterGeometry( OGRGeometry *, OGREnvelope* psGeometryEnvelope);
    HGDAL_EXPORT int          InstallFilter( OGRGeometry * );

    HGDAL_EXPORT OGRErr       GetExtentInternal(int iGeomField, OGREnvelope *psExtent, int bForce );
//! @endcond

    HGDAL_EXPORT virtual OGRErr      ISetFeature( OGRFeature *poFeature ) CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRErr      ICreateFeature( OGRFeature *poFeature )  CPL_WARN_UNUSED_RESULT;

  public:
    HGDAL_EXPORT OGRLayer();
    HGDAL_EXPORT virtual     ~OGRLayer();

    /** Return begin of feature iterator.
     *
     * Using this iterator for standard range-based loops is safe, but
     * due to implementation limitations, you shouldn't try to access
     * (dereference) more than one iterator step at a time, since the
     * OGRFeatureUniquePtr reference is reused.
     *
     * Only one iterator per layer can be active at a time.
     * @since GDAL 2.3
     */
    HGDAL_EXPORT FeatureIterator begin();

    /** Return end of feature iterator. */
    HGDAL_EXPORT FeatureIterator end();

    HGDAL_EXPORT virtual OGRGeometry *GetSpatialFilter();
    HGDAL_EXPORT virtual void        SetSpatialFilter( OGRGeometry * );
    HGDAL_EXPORT virtual void        SetSpatialFilterRect( double dfMinX, double dfMinY,
                                              double dfMaxX, double dfMaxY );

    HGDAL_EXPORT virtual void        SetSpatialFilter( int iGeomField, OGRGeometry * );
    HGDAL_EXPORT virtual void        SetSpatialFilterRect( int iGeomField,
                                            double dfMinX, double dfMinY,
                                            double dfMaxX, double dfMaxY );

    HGDAL_EXPORT virtual OGRErr      SetAttributeFilter( const char * );

    HGDAL_EXPORT virtual void        ResetReading() = 0;
    HGDAL_EXPORT virtual OGRFeature *GetNextFeature() CPL_WARN_UNUSED_RESULT = 0;
    HGDAL_EXPORT virtual OGRErr      SetNextByIndex( GIntBig nIndex );
    HGDAL_EXPORT virtual OGRFeature *GetFeature( GIntBig nFID )  CPL_WARN_UNUSED_RESULT;

    HGDAL_EXPORT OGRErr      SetFeature( OGRFeature *poFeature )  CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT OGRErr      CreateFeature( OGRFeature *poFeature ) CPL_WARN_UNUSED_RESULT;

    HGDAL_EXPORT virtual OGRErr      DeleteFeature( GIntBig nFID )  CPL_WARN_UNUSED_RESULT;

    HGDAL_EXPORT virtual const char *GetName();
    HGDAL_EXPORT virtual OGRwkbGeometryType GetGeomType();
    HGDAL_EXPORT virtual OGRFeatureDefn *GetLayerDefn() = 0;
    HGDAL_EXPORT virtual int         FindFieldIndex( const char *pszFieldName, int bExactMatch );

    HGDAL_EXPORT virtual OGRSpatialReference *GetSpatialRef();

    HGDAL_EXPORT virtual GIntBig     GetFeatureCount( int bForce = TRUE );
    HGDAL_EXPORT virtual OGRErr      GetExtent(OGREnvelope *psExtent, int bForce = TRUE)  CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRErr      GetExtent(int iGeomField, OGREnvelope *psExtent,
                                  int bForce = TRUE)  CPL_WARN_UNUSED_RESULT;

    HGDAL_EXPORT virtual int         TestCapability( const char * ) = 0;

    HGDAL_EXPORT virtual OGRErr      CreateField( OGRFieldDefn *poField,
                                     int bApproxOK = TRUE );
    HGDAL_EXPORT virtual OGRErr      DeleteField( int iField );
    HGDAL_EXPORT virtual OGRErr      ReorderFields( int* panMap );
    HGDAL_EXPORT virtual OGRErr      AlterFieldDefn( int iField, OGRFieldDefn* poNewFieldDefn, int nFlagsIn );

    HGDAL_EXPORT virtual OGRErr      CreateGeomField( OGRGeomFieldDefn *poField,
                                     int bApproxOK = TRUE );

    HGDAL_EXPORT virtual OGRErr      SyncToDisk();

    HGDAL_EXPORT virtual OGRStyleTable *GetStyleTable();
    HGDAL_EXPORT virtual void        SetStyleTableDirectly( OGRStyleTable *poStyleTable );

    HGDAL_EXPORT virtual void        SetStyleTable(OGRStyleTable *poStyleTable);

    HGDAL_EXPORT virtual OGRErr      StartTransaction() CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRErr      CommitTransaction() CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRErr      RollbackTransaction();

    HGDAL_EXPORT virtual const char *GetFIDColumn();
    HGDAL_EXPORT virtual const char *GetGeometryColumn();

    HGDAL_EXPORT virtual OGRErr      SetIgnoredFields( const char **papszFields );

    HGDAL_EXPORT OGRErr              Intersection( OGRLayer *pLayerMethod,
                                      OGRLayer *pLayerResult,
                                      char** papszOptions = nullptr,
                                      GDALProgressFunc pfnProgress = nullptr,
                                      void * pProgressArg = nullptr );
    HGDAL_EXPORT OGRErr              Union( OGRLayer *pLayerMethod,
                               OGRLayer *pLayerResult,
                               char** papszOptions = nullptr,
                               GDALProgressFunc pfnProgress = nullptr,
                               void * pProgressArg = nullptr );
    HGDAL_EXPORT OGRErr              SymDifference( OGRLayer *pLayerMethod,
                                       OGRLayer *pLayerResult,
                                       char** papszOptions,
                                       GDALProgressFunc pfnProgress,
                                       void * pProgressArg );
    HGDAL_EXPORT OGRErr              Identity( OGRLayer *pLayerMethod,
                                  OGRLayer *pLayerResult,
                                  char** papszOptions = nullptr,
                                  GDALProgressFunc pfnProgress = nullptr,
                                  void * pProgressArg = nullptr );
    HGDAL_EXPORT OGRErr              Update( OGRLayer *pLayerMethod,
                                OGRLayer *pLayerResult,
                                char** papszOptions = nullptr,
                                GDALProgressFunc pfnProgress = nullptr,
                                void * pProgressArg = nullptr );
    HGDAL_EXPORT OGRErr              Clip( OGRLayer *pLayerMethod,
                              OGRLayer *pLayerResult,
                              char** papszOptions = nullptr,
                              GDALProgressFunc pfnProgress = nullptr,
                              void * pProgressArg = nullptr );
    HGDAL_EXPORT OGRErr              Erase( OGRLayer *pLayerMethod,
                               OGRLayer *pLayerResult,
                               char** papszOptions = nullptr,
                               GDALProgressFunc pfnProgress = nullptr,
                               void * pProgressArg = nullptr );

    HGDAL_EXPORT int                 Reference();
    HGDAL_EXPORT int                 Dereference();
    HGDAL_EXPORT int                 GetRefCount() const;
//! @cond Doxygen_Suppress
    HGDAL_EXPORT GIntBig             GetFeaturesRead();
//! @endcond

    /* non virtual : convenience wrapper for ReorderFields() */
    HGDAL_EXPORT OGRErr              ReorderField( int iOldFieldPos, int iNewFieldPos );

//! @cond Doxygen_Suppress
    HGDAL_EXPORT int                 AttributeFilterEvaluationNeedsGeometry();

    /* consider these private */
    HGDAL_EXPORT OGRErr               InitializeIndexSupport( const char * );
    OGRLayerAttrIndex   *GetIndex() { return m_poAttrIndex; }
    int                 GetGeomFieldFilter() const { return m_iGeomFieldFilter; }
    const char          *GetAttrQueryString() const { return m_pszAttrQueryString; }
//! @endcond

    /** Convert a OGRLayer* to a OGRLayerH.
     * @since GDAL 2.3
     */
    static inline OGRLayerH ToHandle(OGRLayer* poLayer)
        { return reinterpret_cast<OGRLayerH>(poLayer); }

    /** Convert a OGRLayerH to a OGRLayer*.
     * @since GDAL 2.3
     */
    static inline OGRLayer* FromHandle(OGRLayerH hLayer)
        { return reinterpret_cast<OGRLayer*>(hLayer); }

 protected:
//! @cond Doxygen_Suppress
    OGRStyleTable       *m_poStyleTable;
    OGRFeatureQuery     *m_poAttrQuery;
    char                *m_pszAttrQueryString;
    OGRLayerAttrIndex   *m_poAttrIndex;

    int                  m_nRefCount;

    GIntBig              m_nFeaturesRead;
//! @endcond
};

/** Return begin of feature iterator.
 *
 * Using this iterator for standard range-based loops is safe, but
 * due to implementation limitations, you shouldn't try to access
 * (dereference) more than one iterator step at a time, since the
 * std::unique_ptr&lt;OGRFeature&gt; reference is reused.
 *
 * Only one iterator per layer can be active at a time.
 * @since GDAL 2.3
 * @see OGRLayer::begin()
 */
inline OGRLayer::FeatureIterator begin(OGRLayer* poLayer) { return poLayer->begin(); }

/** Return end of feature iterator.
 * @see OGRLayer::end()
 */
inline OGRLayer::FeatureIterator end(OGRLayer* poLayer) { return poLayer->end(); }

/** Unique pointer type for OGRLayer.
 * @since GDAL 3.2
 */
using OGRLayerUniquePtr = std::unique_ptr<OGRLayer>;

/************************************************************************/
/*                     OGRGetNextFeatureThroughRaw                      */
/************************************************************************/

/** Template class offering a GetNextFeature() implementation relying on
 * GetNextRawFeature()
 *
 * @since GDAL 3.2
 */
template<class BaseLayer> class OGRGetNextFeatureThroughRaw
{
public:

    /** Implement OGRLayer::GetNextFeature(), relying on BaseLayer::GetNextRawFeature() */
    OGRFeature* GetNextFeature()
    {
        const auto poThis = static_cast<BaseLayer*>(this);
        while( true )
        {
            OGRFeature *poFeature = poThis->GetNextRawFeature();
            if (poFeature == nullptr)
                return nullptr;

            if((poThis->m_poFilterGeom == nullptr
                || poThis->FilterGeometry( poFeature->GetGeometryRef() ) )
            && (poThis->m_poAttrQuery == nullptr
                || poThis->m_poAttrQuery->Evaluate( poFeature )) )
            {
                return poFeature;
            }
            else
                delete poFeature;
        }
    }
};

/** Utility macro to define GetNextFeature() through GetNextRawFeature() */
#define DEFINE_GET_NEXT_FEATURE_THROUGH_RAW(BaseLayer) \
    private: \
        friend class OGRGetNextFeatureThroughRaw<BaseLayer>; \
    public: \
        OGRFeature* GetNextFeature() override { return OGRGetNextFeatureThroughRaw<BaseLayer>::GetNextFeature(); }


/************************************************************************/
/*                            OGRDataSource                             */
/************************************************************************/

/**
 * LEGACY class. Use GDALDataset in your new code ! This class may be
 * removed in a later release.
 *
 * This class represents a data source.  A data source potentially
 * consists of many layers (OGRLayer).  A data source normally consists
 * of one, or a related set of files, though the name doesn't have to be
 * a real item in the file system.
 *
 * When an OGRDataSource is destroyed, all its associated OGRLayers objects
 * are also destroyed.
 *
 * NOTE: Starting with GDAL 2.0, it is *NOT* safe to cast the handle of
 * a C function that returns a OGRDataSourceH to a OGRDataSource*. If a C++ object
 * is needed, the handle should be cast to GDALDataset*.
 *
 * @deprecated
 */

class OGRDataSource : public GDALDataset
{
public:
    HGDAL_EXPORT                     OGRDataSource();
//! @cond Doxygen_Suppress
    HGDAL_EXPORT virtual const char  *GetName() OGR_DEPRECATED("Use GDALDataset class instead") = 0;

    HGDAL_EXPORT static void         DestroyDataSource( OGRDataSource * ) OGR_DEPRECATED("Use GDALDataset class instead");
//! @endcond
};

/************************************************************************/
/*                             OGRSFDriver                              */
/************************************************************************/

/**
 * LEGACY class. Use GDALDriver in your new code ! This class may be
 * removed in a later release.
 *
 * Represents an operational format driver.
 *
 * One OGRSFDriver derived class will normally exist for each file format
 * registered for use, regardless of whether a file has or will be opened.
 * The list of available drivers is normally managed by the
 * OGRSFDriverRegistrar.
 *
 * NOTE: Starting with GDAL 2.0, it is *NOT* safe to cast the handle of
 * a C function that returns a OGRSFDriverH to a OGRSFDriver*. If a C++ object
 * is needed, the handle should be cast to GDALDriver*.
 *
 * @deprecated
 */

class OGRSFDriver : public GDALDriver
{
  public:
//! @cond Doxygen_Suppress
    HGDAL_EXPORT virtual     ~OGRSFDriver();

    HGDAL_EXPORT virtual const char  *GetName() OGR_DEPRECATED("Use GDALDriver class instead") = 0;

    HGDAL_EXPORT virtual OGRDataSource *Open( const char *pszName, int bUpdate=FALSE ) OGR_DEPRECATED("Use GDALDriver class instead") = 0;

    HGDAL_EXPORT virtual int            TestCapability( const char *pszCap ) OGR_DEPRECATED("Use GDALDriver class instead") = 0;

    HGDAL_EXPORT virtual OGRDataSource *CreateDataSource( const char *pszName,
                                             char ** = nullptr ) OGR_DEPRECATED("Use GDALDriver class instead");
    HGDAL_EXPORT virtual OGRErr      DeleteDataSource( const char *pszName ) OGR_DEPRECATED("Use GDALDriver class instead");
//! @endcond
};

/************************************************************************/
/*                         OGRSFDriverRegistrar                         */
/************************************************************************/

/**
 * LEGACY class. Use GDALDriverManager in your new code ! This class may be
 * removed in a later release.
 *
 * Singleton manager for OGRSFDriver instances that will be used to try
 * and open datasources.  Normally the registrar is populated with
 * standard drivers using the OGRRegisterAll() function and does not need
 * to be directly accessed.  The driver registrar and all registered drivers
 * may be cleaned up on shutdown using OGRCleanupAll().
 *
 * @deprecated
 */

class OGRSFDriverRegistrar
{

    HGDAL_EXPORT             OGRSFDriverRegistrar();
    HGDAL_EXPORT             ~OGRSFDriverRegistrar();

    HGDAL_EXPORT static GDALDataset* OpenWithDriverArg(GDALDriver* poDriver,
                                                 GDALOpenInfo* poOpenInfo);
    HGDAL_EXPORT static GDALDataset* CreateVectorOnly( GDALDriver* poDriver,
                                          const char * pszName,
                                          char ** papszOptions );
    HGDAL_EXPORT static CPLErr       DeleteDataSource( GDALDriver* poDriver,
                                          const char * pszName );

  public:
//! @cond Doxygen_Suppress
    HGDAL_EXPORT static OGRSFDriverRegistrar *GetRegistrar() OGR_DEPRECATED("Use GDALDriverManager class instead");

    // cppcheck-suppress functionStatic
    HGDAL_EXPORT void        RegisterDriver( OGRSFDriver * poDriver ) OGR_DEPRECATED("Use GDALDriverManager class instead");

    // cppcheck-suppress functionStatic
    HGDAL_EXPORT int         GetDriverCount( void ) OGR_DEPRECATED("Use GDALDriverManager class instead");
    // cppcheck-suppress functionStatic
    HGDAL_EXPORT GDALDriver *GetDriver( int iDriver ) OGR_DEPRECATED("Use GDALDriverManager class instead");
    // cppcheck-suppress functionStatic
    HGDAL_EXPORT GDALDriver *GetDriverByName( const char * ) OGR_DEPRECATED("Use GDALDriverManager class instead");

    // cppcheck-suppress functionStatic
    HGDAL_EXPORT int         GetOpenDSCount() OGR_DEPRECATED("Use GDALDriverManager class instead");
    // cppcheck-suppress functionStatic
    HGDAL_EXPORT OGRDataSource *GetOpenDS( int ) OGR_DEPRECATED("Use GDALDriverManager class instead");
//! @endcond
};

/* -------------------------------------------------------------------- */
/*      Various available registration methods.                         */
/* -------------------------------------------------------------------- */
CPL_C_START

//! @cond Doxygen_Suppress
HGDAL_EXPORT void OGRRegisterAllInternal();

HGDAL_EXPORT void RegisterOGRFileGDB();
HGDAL_EXPORT void RegisterOGRShape();
HGDAL_EXPORT void RegisterOGRDB2();
HGDAL_EXPORT void RegisterOGRNTF();
HGDAL_EXPORT void RegisterOGRFME();
HGDAL_EXPORT void RegisterOGRSDTS();
HGDAL_EXPORT void RegisterOGRTiger();
HGDAL_EXPORT void RegisterOGRS57();
HGDAL_EXPORT void RegisterOGRTAB();
HGDAL_EXPORT void RegisterOGRMIF();
HGDAL_EXPORT void RegisterOGROGDI();
HGDAL_EXPORT void RegisterOGRODBC();
HGDAL_EXPORT void RegisterOGRWAsP();
HGDAL_EXPORT void RegisterOGRPG();
HGDAL_EXPORT void RegisterOGRMSSQLSpatial();
HGDAL_EXPORT void RegisterOGRMySQL();
HGDAL_EXPORT void RegisterOGROCI();
HGDAL_EXPORT void RegisterOGRDGN();
HGDAL_EXPORT void RegisterOGRGML();
HGDAL_EXPORT void RegisterOGRLIBKML();
HGDAL_EXPORT void RegisterOGRKML();
HGDAL_EXPORT void RegisterOGRFlatGeobuf();
HGDAL_EXPORT void RegisterOGRGeoJSON();
HGDAL_EXPORT void RegisterOGRGeoJSONSeq();
HGDAL_EXPORT void RegisterOGRESRIJSON();
HGDAL_EXPORT void RegisterOGRTopoJSON();
HGDAL_EXPORT void RegisterOGRAVCBin();
HGDAL_EXPORT void RegisterOGRAVCE00();
HGDAL_EXPORT void RegisterOGRREC();
HGDAL_EXPORT void RegisterOGRMEM();
HGDAL_EXPORT void RegisterOGRVRT();
HGDAL_EXPORT void RegisterOGRDODS();
HGDAL_EXPORT void RegisterOGRSQLite();
HGDAL_EXPORT void RegisterOGRCSV();
HGDAL_EXPORT void RegisterOGRILI1();
HGDAL_EXPORT void RegisterOGRILI2();
HGDAL_EXPORT void RegisterOGRGRASS();
HGDAL_EXPORT void RegisterOGRPGeo();
HGDAL_EXPORT void RegisterOGRDXF();
HGDAL_EXPORT void RegisterOGRCAD();
HGDAL_EXPORT void RegisterOGRDWG();
HGDAL_EXPORT void RegisterOGRDGNV8();
HGDAL_EXPORT void RegisterOGRIDB();
HGDAL_EXPORT void RegisterOGRGMT();
HGDAL_EXPORT void RegisterOGRGPX();
HGDAL_EXPORT void RegisterOGRGeoconcept();
HGDAL_EXPORT void RegisterOGRIngres();
HGDAL_EXPORT void RegisterOGRNAS();
HGDAL_EXPORT void RegisterOGRGeoRSS();
HGDAL_EXPORT void RegisterOGRGTM();
HGDAL_EXPORT void RegisterOGRVFK();
HGDAL_EXPORT void RegisterOGRPGDump();
HGDAL_EXPORT void RegisterOGROSM();
HGDAL_EXPORT void RegisterOGRGPSBabel();
HGDAL_EXPORT void RegisterOGRPDS();
HGDAL_EXPORT void RegisterOGRWFS();
HGDAL_EXPORT void RegisterOGROAPIF();
HGDAL_EXPORT void RegisterOGRSOSI();
HGDAL_EXPORT void RegisterOGRGeomedia();
HGDAL_EXPORT void RegisterOGRMDB();
HGDAL_EXPORT void RegisterOGREDIGEO();
HGDAL_EXPORT void RegisterOGRSVG();
HGDAL_EXPORT void RegisterOGRCouchDB();
HGDAL_EXPORT void RegisterOGRCloudant();
HGDAL_EXPORT void RegisterOGRIdrisi();
HGDAL_EXPORT void RegisterOGRARCGEN();
HGDAL_EXPORT void RegisterOGRXLS();
HGDAL_EXPORT void RegisterOGRODS();
HGDAL_EXPORT void RegisterOGRXLSX();
HGDAL_EXPORT void RegisterOGRElastic();
HGDAL_EXPORT void RegisterOGRGeoPackage();
HGDAL_EXPORT void RegisterOGRWalk();
HGDAL_EXPORT void RegisterOGRCarto();
HGDAL_EXPORT void RegisterOGRAmigoCloud();
HGDAL_EXPORT void RegisterOGRSXF();
HGDAL_EXPORT void RegisterOGROpenFileGDB();
HGDAL_EXPORT void RegisterOGRSelafin();
HGDAL_EXPORT void RegisterOGRJML();
HGDAL_EXPORT void RegisterOGRPLSCENES();
HGDAL_EXPORT void RegisterOGRCSW();
HGDAL_EXPORT void RegisterOGRMongoDBv3();
HGDAL_EXPORT void RegisterOGRMongoDB();
HGDAL_EXPORT void RegisterOGRVDV();
HGDAL_EXPORT void RegisterOGRGMLAS();
HGDAL_EXPORT void RegisterOGRMVT();
HGDAL_EXPORT void RegisterOGRNGW();
HGDAL_EXPORT void RegisterOGRMapML();
HGDAL_EXPORT void RegisterOGRLVBAG();
// @endcond

CPL_C_END

#endif /* ndef OGRSF_FRMTS_H_INCLUDED */
