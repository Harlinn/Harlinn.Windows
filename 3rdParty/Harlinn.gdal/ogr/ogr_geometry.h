#pragma once
/******************************************************************************
 * $Id$
 *
 * Project:  OpenGIS Simple Features Reference Implementation
 * Purpose:  Classes for manipulating simple features that is not specific
 *           to a particular interface technology.
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *
 ******************************************************************************
 * Copyright (c) 1999, Frank Warmerdam
 * Copyright (c) 2008-2014, Even Rouault <even dot rouault at spatialys.com>
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

#ifndef OGR_GEOMETRY_H_INCLUDED
#define OGR_GEOMETRY_H_INCLUDED

#include "../port/cpl_conv.h"
#include "../port/cpl_json.h"
#include <ogr/ogr_core.h>
#include <ogr/ogr_spatialref.h>

#include <cmath>
#include <memory>

/**
 * \file ogr_geometry.h
 *
 * Simple feature geometry classes.
 */

/*! @cond Doxygen_Suppress */
#ifndef DEFINEH_OGRGeometryH
#define DEFINEH_OGRGeometryH
#ifdef DEBUG
typedef struct OGRGeometryHS *OGRGeometryH;
#else
typedef void *OGRGeometryH;
#endif
#endif /* DEFINEH_OGRGeometryH */
/*! @endcond */

/// WKT Output formatting options.
enum class OGRWktFormat
{
    F,        ///< F-type formatting.
    G,        ///< G-type formatting.
    Default   ///< Format as F when abs(value) < 1, otherwise as G.
};

/// Options for formatting WKT output
struct OGRWktOptions
{
public:
    /// Type of WKT output to produce.
    OGRwkbVariant variant;
    /// Precision of output.  Interpretation depends on \c format.
    int precision;
    /// Whether GDAL-special rounding should be applied.
    bool round;
    /// Formatting type.
    OGRWktFormat format;

    /// Constructor.
    OGRWktOptions() : variant(wkbVariantOldOgc), precision(15), round(true),
        format(OGRWktFormat::Default)
    {
        static int defPrecision = getDefaultPrecision();
        static bool defRound = getDefaultRound();

        precision = defPrecision;
        round = defRound;
    }

    /// Copy constructor
    OGRWktOptions(const OGRWktOptions&) = default;

private:
    HGDAL_EXPORT static int getDefaultPrecision();
    HGDAL_EXPORT static bool getDefaultRound();
};

/**
 * Simple container for a position.
 */
class OGRRawPoint
{
  public:
          /** Constructor */
          OGRRawPoint() : x(0.0), y(0.0) {}

          /** Constructor */
          OGRRawPoint(double xIn, double yIn) : x(xIn), y(yIn) {}

    /** x */
    double      x;
    /** y */
    double      y;
};

/** GEOS geometry type */
typedef struct GEOSGeom_t *GEOSGeom;
/** GEOS context handle type */
typedef struct GEOSContextHandle_HS *GEOSContextHandle_t;
/** SFCGAL geometry type */
typedef void sfcgal_geometry_t;

class OGRPoint;
class OGRCurve;
class OGRCompoundCurve;
class OGRSimpleCurve;
class OGRLinearRing;
class OGRLineString;
class OGRCircularString;
class OGRSurface;
class OGRCurvePolygon;
class OGRPolygon;
class OGRMultiPoint;
class OGRMultiSurface;
class OGRMultiPolygon;
class OGRMultiCurve;
class OGRMultiLineString;
class OGRGeometryCollection;
class OGRTriangle;
class OGRPolyhedralSurface;
class OGRTriangulatedSurface;

//! @cond Doxygen_Suppress
typedef OGRLineString* (*OGRCurveCasterToLineString)(OGRCurve*);
typedef OGRLinearRing* (*OGRCurveCasterToLinearRing)(OGRCurve*);

typedef OGRPolygon*      (*OGRSurfaceCasterToPolygon)(OGRSurface*);
typedef OGRCurvePolygon* (*OGRSurfaceCasterToCurvePolygon)(OGRSurface*);
typedef OGRMultiPolygon* (*OGRPolyhedralSurfaceCastToMultiPolygon)(OGRPolyhedralSurface*);
//! @endcond

/** OGRGeometry visitor interface.
 * @since GDAL 2.3
 */
class IOGRGeometryVisitor
{
    public:
        /** Destructor/ */
        virtual ~IOGRGeometryVisitor() = default;

        /** Visit OGRPoint. */
        virtual void visit(OGRPoint*) = 0;
        /** Visit OGRLineString. */
        virtual void visit(OGRLineString*) = 0;
        /** Visit OGRLinearRing. */
        virtual void visit(OGRLinearRing*) = 0;
        /** Visit OGRPolygon. */
        virtual void visit(OGRPolygon*) = 0;
        /** Visit OGRMultiPoint. */
        virtual void visit(OGRMultiPoint*) = 0;
        /** Visit OGRMultiLineString. */
        virtual void visit(OGRMultiLineString*) = 0;
        /** Visit OGRMultiPolygon. */
        virtual void visit(OGRMultiPolygon*) = 0;
        /** Visit OGRGeometryCollection. */
        virtual void visit(OGRGeometryCollection*) = 0;
        /** Visit OGRCircularString. */
        virtual void visit(OGRCircularString*) = 0;
        /** Visit OGRCompoundCurve. */
        virtual void visit(OGRCompoundCurve*) = 0;
        /** Visit OGRCurvePolygon. */
        virtual void visit(OGRCurvePolygon*) = 0;
        /** Visit OGRMultiCurve. */
        virtual void visit(OGRMultiCurve*) = 0;
        /** Visit OGRMultiSurface. */
        virtual void visit(OGRMultiSurface*) = 0;
        /** Visit OGRTriangle. */
        virtual void visit(OGRTriangle*) = 0;
        /** Visit OGRPolyhedralSurface. */
        virtual void visit(OGRPolyhedralSurface*) = 0;
        /** Visit OGRTriangulatedSurface. */
        virtual void visit(OGRTriangulatedSurface*) = 0;
};

/** OGRGeometry visitor default implementation.
 *
 * This default implementation will recurse down to calling
 * visit(OGRPoint*) on each point.
 *
 * @since GDAL 2.3
 */
class OGRDefaultGeometryVisitor: public IOGRGeometryVisitor
{
        void _visit(OGRSimpleCurve* poGeom);

    public:

        void visit(OGRPoint*) override {}
        HGDAL_EXPORT void visit(OGRLineString*) override;
        HGDAL_EXPORT void visit(OGRLinearRing*) override;
        HGDAL_EXPORT void visit(OGRPolygon*) override;
        HGDAL_EXPORT void visit(OGRMultiPoint*) override;
        HGDAL_EXPORT void visit(OGRMultiLineString*) override;
        HGDAL_EXPORT void visit(OGRMultiPolygon*) override;
        HGDAL_EXPORT void visit(OGRGeometryCollection*) override;
        HGDAL_EXPORT void visit(OGRCircularString*) override;
        HGDAL_EXPORT void visit(OGRCompoundCurve*) override;
        HGDAL_EXPORT void visit(OGRCurvePolygon*) override;
        HGDAL_EXPORT void visit(OGRMultiCurve*) override;
        HGDAL_EXPORT void visit(OGRMultiSurface*) override;
        HGDAL_EXPORT void visit(OGRTriangle*) override;
        HGDAL_EXPORT void visit(OGRPolyhedralSurface*) override;
        HGDAL_EXPORT void visit(OGRTriangulatedSurface*) override;
};

/** OGRGeometry visitor interface.
 * @since GDAL 2.3
 */
class IOGRConstGeometryVisitor
{
    public:
        /** Destructor/ */
        virtual ~IOGRConstGeometryVisitor() = default;

        /** Visit OGRPoint. */
        virtual void visit(const OGRPoint*) = 0;
        /** Visit OGRLineString. */
        virtual void visit(const OGRLineString*) = 0;
        /** Visit OGRLinearRing. */
        virtual void visit(const OGRLinearRing*) = 0;
        /** Visit OGRPolygon. */
        virtual void visit(const OGRPolygon*) = 0;
        /** Visit OGRMultiPoint. */
        virtual void visit(const OGRMultiPoint*) = 0;
        /** Visit OGRMultiLineString. */
        virtual void visit(const OGRMultiLineString*) = 0;
        /** Visit OGRMultiPolygon. */
        virtual void visit(const OGRMultiPolygon*) = 0;
        /** Visit OGRGeometryCollection. */
        virtual void visit(const OGRGeometryCollection*) = 0;
        /** Visit OGRCircularString. */
        virtual void visit(const OGRCircularString*) = 0;
        /** Visit OGRCompoundCurve. */
        virtual void visit(const OGRCompoundCurve*) = 0;
        /** Visit OGRCurvePolygon. */
        virtual void visit(const OGRCurvePolygon*) = 0;
        /** Visit OGRMultiCurve. */
        virtual void visit(const OGRMultiCurve*) = 0;
        /** Visit OGRMultiSurface. */
        virtual void visit(const OGRMultiSurface*) = 0;
        /** Visit OGRTriangle. */
        virtual void visit(const OGRTriangle*) = 0;
        /** Visit OGRPolyhedralSurface. */
        virtual void visit(const OGRPolyhedralSurface*) = 0;
        /** Visit OGRTriangulatedSurface. */
        virtual void visit(const OGRTriangulatedSurface*) = 0;
};

/** OGRGeometry visitor default implementation.
 *
 * This default implementation will recurse down to calling
 * visit(const OGRPoint*) on each point.
 *
 * @since GDAL 2.3
 */
class OGRDefaultConstGeometryVisitor: public IOGRConstGeometryVisitor
{
        void _visit(const OGRSimpleCurve* poGeom);

    public:

        void visit(const OGRPoint*) override {}
        HGDAL_EXPORT void visit(const OGRLineString*) override;
        HGDAL_EXPORT void visit(const OGRLinearRing*) override;
        HGDAL_EXPORT void visit(const OGRPolygon*) override;
        HGDAL_EXPORT void visit(const OGRMultiPoint*) override;
        HGDAL_EXPORT void visit(const OGRMultiLineString*) override;
        HGDAL_EXPORT void visit(const OGRMultiPolygon*) override;
        HGDAL_EXPORT void visit(const OGRGeometryCollection*) override;
        HGDAL_EXPORT void visit(const OGRCircularString*) override;
        HGDAL_EXPORT void visit(const OGRCompoundCurve*) override;
        HGDAL_EXPORT void visit(const OGRCurvePolygon*) override;
        HGDAL_EXPORT void visit(const OGRMultiCurve*) override;
        HGDAL_EXPORT void visit(const OGRMultiSurface*) override;
        HGDAL_EXPORT void visit(const OGRTriangle*) override;
        HGDAL_EXPORT void visit(const OGRPolyhedralSurface*) override;
        HGDAL_EXPORT void visit(const OGRTriangulatedSurface*) override;
};

/************************************************************************/
/*                             OGRGeometry                              */
/************************************************************************/

/**
 * Abstract base class for all geometry classes.
 *
 * Some spatial analysis methods require that OGR is built on the GEOS library
 * to work properly. The precise meaning of methods that describe spatial
 * relationships between geometries is described in the SFCOM, or other simple
 * features interface specifications, like "OpenGIS® Implementation
 * Specification for Geographic information - Simple feature access - Part 1:
 * Common architecture":
 * <a href="http://www.opengeospatial.org/standards/sfa">OGC 06-103r4</a>
 *
 * In GDAL 2.0, the hierarchy of classes has been extended with
 * <a href="https://portal.opengeospatial.org/files/?artifact_id=32024">
 * (working draft) ISO SQL/MM Part 3 (ISO/IEC 13249-3)</a> curve geometries :
 * CIRCULARSTRING (OGRCircularString), COMPOUNDCURVE (OGRCompoundCurve),
 * CURVEPOLYGON (OGRCurvePolygon), MULTICURVE (OGRMultiCurve) and
 * MULTISURFACE (OGRMultiSurface).
 *
 */

class OGRGeometry
{
  private:
    OGRSpatialReference * poSRS = nullptr;                // may be NULL

  protected:
//! @cond Doxygen_Suppress
    friend class OGRCurveCollection;

    unsigned int flags = 0;

    HGDAL_EXPORT OGRErr       importPreambleFromWkt( const char ** ppszInput,
                                         int* pbHasZ, int* pbHasM,
                                         bool* pbIsEmpty );
    HGDAL_EXPORT OGRErr       importCurveCollectionFromWkt(
                     const char ** ppszInput,
                     int bAllowEmptyComponent,
                     int bAllowLineString,
                     int bAllowCurve,
                     int bAllowCompoundCurve,
                     OGRErr (*pfnAddCurveDirectly)(OGRGeometry* poSelf,
                                                   OGRCurve* poCurve) );
    HGDAL_EXPORT OGRErr       importPreambleFromWkb( const unsigned char * pabyData,
                                         size_t nSize,
                                         OGRwkbByteOrder& eByteOrder,
                                         OGRwkbVariant eWkbVariant );
    HGDAL_EXPORT OGRErr       importPreambleOfCollectionFromWkb(
                     const unsigned char * pabyData,
                     size_t& nSize,
                     size_t& nDataOffset,
                     OGRwkbByteOrder& eByteOrder,
                     size_t nMinSubGeomSize,
                     int& nGeomCount,
                     OGRwkbVariant eWkbVariant );
    HGDAL_EXPORT OGRErr       PointOnSurfaceInternal( OGRPoint * poPoint ) const;
    HGDAL_EXPORT OGRBoolean   IsSFCGALCompatible() const;

    HGDAL_EXPORT void         HomogenizeDimensionalityWith( OGRGeometry* poOtherGeom );
    HGDAL_EXPORT std::string  wktTypeString(OGRwkbVariant variant) const;

//! @endcond

  public:

/************************************************************************/
/*                   Bit flags for OGRGeometry                          */
/*          The OGR_G_NOT_EMPTY_POINT is used *only* for points.        */
/*          Do not use these outside of the core.                       */
/*          Use Is3D, IsMeasured, set3D, and setMeasured instead        */
/************************************************************************/

//! @cond Doxygen_Suppress
    static constexpr unsigned int OGR_G_NOT_EMPTY_POINT = 0x1;
    static constexpr unsigned int OGR_G_3D = 0x2;
    static constexpr unsigned int OGR_G_MEASURED = 0x4;
//! @endcond

    HGDAL_EXPORT             OGRGeometry();
    HGDAL_EXPORT             OGRGeometry( const OGRGeometry& other );
    HGDAL_EXPORT virtual     ~OGRGeometry();

    HGDAL_EXPORT OGRGeometry& operator=( const OGRGeometry& other );

    /** Returns if two geometries are equal. */
    bool operator==( const OGRGeometry& other ) const { return CPL_TO_BOOL(Equals(&other)); }

    /** Returns if two geometries are different. */
    bool operator!=( const OGRGeometry& other ) const { return !CPL_TO_BOOL(Equals(&other)); }

    // Standard IGeometry.
    virtual int getDimension() const = 0;
    HGDAL_EXPORT virtual int getCoordinateDimension() const;
    HGDAL_EXPORT int CoordinateDimension() const;
    virtual OGRBoolean  IsEmpty() const = 0;
    HGDAL_EXPORT virtual OGRBoolean  IsValid() const;
    HGDAL_EXPORT virtual OGRGeometry* MakeValid(CSLConstList papszOptions = nullptr) const;
    HGDAL_EXPORT virtual OGRGeometry* Normalize() const;
    HGDAL_EXPORT virtual OGRBoolean  IsSimple() const;
    /*! Returns whether the geometry has a Z component. */
    OGRBoolean  Is3D() const { return flags & OGR_G_3D; }
    /*! Returns whether the geometry has a M component. */
    OGRBoolean  IsMeasured() const { return flags & OGR_G_MEASURED; }
    HGDAL_EXPORT virtual OGRBoolean  IsRing() const;
    virtual void        empty() = 0;
    virtual OGRGeometry *clone() const CPL_WARN_UNUSED_RESULT = 0;
    virtual void getEnvelope( OGREnvelope * psEnvelope ) const = 0;
    virtual void getEnvelope( OGREnvelope3D * psEnvelope ) const = 0;

    // IWks Interface.
    virtual size_t WkbSize() const = 0;
    HGDAL_EXPORT OGRErr importFromWkb( const GByte*, size_t=static_cast<size_t>(-1),
                                  OGRwkbVariant=wkbVariantOldOgc );
    virtual OGRErr importFromWkb( const unsigned char *,
                                  size_t,
                                  OGRwkbVariant,
                                  size_t& nBytesConsumedOut ) = 0;
    virtual OGRErr exportToWkb( OGRwkbByteOrder, unsigned char *,
                                OGRwkbVariant=wkbVariantOldOgc ) const = 0;
    virtual OGRErr importFromWkt( const char ** ppszInput ) = 0;

#ifndef DOXYGEN_XML
    /** Deprecated.
     * @deprecated in GDAL 2.3
     */
    OGRErr importFromWkt( char ** ppszInput )
/*! @cond Doxygen_Suppress */
        CPL_WARN_DEPRECATED("Use importFromWkt(const char**) instead")
/*! @endcond */
    {
        return importFromWkt( const_cast<const char**>(ppszInput) );
    }
#endif

    HGDAL_EXPORT OGRErr exportToWkt( char ** ppszDstText,
        OGRwkbVariant=wkbVariantOldOgc ) const;

    /// Export a WKT geometry.
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return  WKT string representing this geometry.
    virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const = 0;

    // Non-standard.
    virtual OGRwkbGeometryType getGeometryType() const = 0;
    HGDAL_EXPORT OGRwkbGeometryType    getIsoGeometryType() const;
    virtual const char *getGeometryName() const = 0;
    HGDAL_EXPORT virtual void   dumpReadable( FILE *, const char * = nullptr
                                 , char** papszOptions = nullptr ) const;
    virtual void   flattenTo2D() = 0;
    HGDAL_EXPORT virtual char * exportToGML( const char* const * papszOptions = nullptr ) const;
    HGDAL_EXPORT virtual char * exportToKML() const;
    HGDAL_EXPORT virtual char * exportToJson() const;

    /** Accept a visitor. */
    virtual void accept(IOGRGeometryVisitor* visitor) = 0;

    /** Accept a visitor. */
    virtual void accept(IOGRConstGeometryVisitor* visitor) const = 0;

    HGDAL_EXPORT static GEOSContextHandle_t createGEOSContext();
    HGDAL_EXPORT static void freeGEOSContext( GEOSContextHandle_t hGEOSCtxt );
    HGDAL_EXPORT virtual GEOSGeom exportToGEOS( GEOSContextHandle_t hGEOSCtxt )
        const CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRBoolean hasCurveGeometry(int bLookForNonLinear = FALSE) const;
    HGDAL_EXPORT virtual OGRGeometry* getCurveGeometry(
        const char* const* papszOptions = nullptr ) const CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRGeometry* getLinearGeometry(
        double dfMaxAngleStepSizeDegrees = 0,
        const char* const* papszOptions = nullptr ) const CPL_WARN_UNUSED_RESULT;

    // SFCGAL interfacing methods.
//! @cond Doxygen_Suppress
    HGDAL_EXPORT static sfcgal_geometry_t* OGRexportToSFCGAL( const OGRGeometry *poGeom );
    HGDAL_EXPORT static OGRGeometry* SFCGALexportToOGR( const sfcgal_geometry_t* _geometry );
//! @endcond
    HGDAL_EXPORT virtual void closeRings();

    HGDAL_EXPORT virtual void setCoordinateDimension( int nDimension );
    HGDAL_EXPORT virtual void set3D( OGRBoolean bIs3D );
    HGDAL_EXPORT virtual void setMeasured( OGRBoolean bIsMeasured );

    HGDAL_EXPORT virtual void    assignSpatialReference( OGRSpatialReference * poSR );
    OGRSpatialReference *getSpatialReference( void ) const { return poSRS; }

    virtual OGRErr  transform( OGRCoordinateTransformation *poCT ) = 0;
    HGDAL_EXPORT OGRErr  transformTo( OGRSpatialReference *poSR );

    HGDAL_EXPORT virtual void segmentize(double dfMaxLength);

    // ISpatialRelation
    HGDAL_EXPORT virtual OGRBoolean  Intersects( const OGRGeometry * ) const;
    virtual OGRBoolean  Equals( const OGRGeometry * ) const = 0;
    HGDAL_EXPORT virtual OGRBoolean  Disjoint( const OGRGeometry * ) const;
    HGDAL_EXPORT virtual OGRBoolean  Touches( const OGRGeometry * ) const;
    HGDAL_EXPORT virtual OGRBoolean  Crosses( const OGRGeometry * ) const;
    HGDAL_EXPORT virtual OGRBoolean  Within( const OGRGeometry * ) const;
    HGDAL_EXPORT virtual OGRBoolean  Contains( const OGRGeometry * ) const;
    HGDAL_EXPORT virtual OGRBoolean  Overlaps( const OGRGeometry * ) const;
//    virtual OGRBoolean  Relate( const OGRGeometry *, const char * ) const;
//    virtual OGRGeometry *LocateAlong( double mValue ) const;
//    virtual OGRGeometry *LocateBetween( double mStart, double mEnd ) const;

    HGDAL_EXPORT virtual OGRGeometry *Boundary() const CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual double  Distance( const OGRGeometry * ) const ;
    HGDAL_EXPORT virtual OGRGeometry *ConvexHull() const CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRGeometry *Buffer( double dfDist, int nQuadSegs = 30 )
        const CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRGeometry *Intersection( const OGRGeometry *)
        const CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRGeometry *Union( const OGRGeometry * )
        const CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRGeometry *UnionCascaded() const CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRGeometry *Difference( const OGRGeometry * )
        const CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRGeometry *SymDifference( const OGRGeometry * )
        const CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRErr       Centroid( OGRPoint * poPoint ) const;
    HGDAL_EXPORT virtual OGRGeometry *Simplify(double dTolerance)
        const CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT OGRGeometry *SimplifyPreserveTopology(double dTolerance)
        const CPL_WARN_UNUSED_RESULT;
    HGDAL_EXPORT virtual OGRGeometry *DelaunayTriangulation(
        double dfTolerance, int bOnlyEdges ) const CPL_WARN_UNUSED_RESULT;

    HGDAL_EXPORT virtual OGRGeometry *Polygonize() const CPL_WARN_UNUSED_RESULT;

    HGDAL_EXPORT virtual double Distance3D( const OGRGeometry *poOtherGeom ) const;

//! @cond Doxygen_Suppress
    // backward compatibility to non-standard method names.
    HGDAL_EXPORT OGRBoolean  Intersect( OGRGeometry * )
        const CPL_WARN_DEPRECATED("Non standard method. "
                                  "Use Intersects() instead");
    HGDAL_EXPORT OGRBoolean  Equal( OGRGeometry * )
        const CPL_WARN_DEPRECATED("Non standard method. "
                                  "Use Equals() instead");
    HGDAL_EXPORT OGRGeometry *SymmetricDifference( const OGRGeometry * )
        const CPL_WARN_DEPRECATED("Non standard method. "
                                  "Use SymDifference() instead");
    HGDAL_EXPORT OGRGeometry *getBoundary()
        const CPL_WARN_DEPRECATED("Non standard method. "
                                  "Use Boundary() instead");
//! @endcond

//! @cond Doxygen_Suppress
    // Special HACK for DB2 7.2 support
    static int bGenerate_DB2_V72_BYTE_ORDER;
//! @endcond

    HGDAL_EXPORT virtual void        swapXY();
//! @cond Doxygen_Suppress
    HGDAL_EXPORT static OGRGeometry* CastToIdentity( OGRGeometry* poGeom ) { return poGeom; }
    HGDAL_EXPORT static OGRGeometry* CastToError( OGRGeometry* poGeom );
//! @endcond

    /** Convert a OGRGeometry* to a OGRGeometryH.
     * @since GDAL 2.3
     */
    static inline OGRGeometryH ToHandle(OGRGeometry* poGeom)
        { return reinterpret_cast<OGRGeometryH>(poGeom); }

    /** Convert a OGRGeometryH to a OGRGeometry*.
     * @since GDAL 2.3
     */
    static inline OGRGeometry* FromHandle(OGRGeometryH hGeom)
        { return reinterpret_cast<OGRGeometry*>(hGeom); }

    /** Down-cast to OGRPoint*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbPoint.
     * @since GDAL 2.3
     */
    inline OGRPoint* toPoint()
        { return cpl::down_cast<OGRPoint*>(this); }

    /** Down-cast to OGRPoint*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbPoint.
     * @since GDAL 2.3
     */
    inline const OGRPoint* toPoint() const
        { return cpl::down_cast<const OGRPoint*>(this); }

    /** Down-cast to OGRCurve*.
     * Implies prior checking that OGR_GT_IsSubClass(getGeometryType(), wkbCurve).
     * @since GDAL 2.3
     */
    inline OGRCurve* toCurve()
        { return cpl::down_cast<OGRCurve*>(this); }

    /** Down-cast to OGRCurve*.
     * Implies prior checking that OGR_GT_IsSubClass(getGeometryType(), wkbCurve).
     * @since GDAL 2.3
     */
    inline const OGRCurve* toCurve() const
        { return cpl::down_cast<const OGRCurve*>(this); }

    /** Down-cast to OGRSimpleCurve*.
     * Implies prior checking that getGeometryType() is wkbLineString, wkbCircularString or a derived type.
     * @since GDAL 2.3
     */
    inline OGRSimpleCurve* toSimpleCurve()
        { return cpl::down_cast<OGRSimpleCurve*>(this); }

    /** Down-cast to OGRSimpleCurve*.
     * Implies prior checking that getGeometryType() is wkbLineString, wkbCircularString or a derived type.
     * @since GDAL 2.3
     */
    inline const OGRSimpleCurve* toSimpleCurve() const
        { return cpl::down_cast<const OGRSimpleCurve*>(this); }

    /** Down-cast to OGRLineString*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbLineString.
     * @since GDAL 2.3
     */
    inline OGRLineString* toLineString()
        { return cpl::down_cast<OGRLineString*>(this); }

    /** Down-cast to OGRLineString*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbLineString.
     * @since GDAL 2.3
     */
    inline const OGRLineString* toLineString() const
        { return cpl::down_cast<const OGRLineString*>(this); }

    /** Down-cast to OGRLinearRing*.
     * Implies prior checking that EQUAL(getGeometryName(), "LINEARRING").
     * @since GDAL 2.3
     */
    inline OGRLinearRing* toLinearRing()
        { return cpl::down_cast<OGRLinearRing*>(this); }

    /** Down-cast to OGRLinearRing*.
     * Implies prior checking that EQUAL(getGeometryName(), "LINEARRING").
     * @since GDAL 2.3
     */
    inline const OGRLinearRing* toLinearRing() const
        { return cpl::down_cast<const OGRLinearRing*>(this); }

    /** Down-cast to OGRCircularString*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbCircularString.
     * @since GDAL 2.3
     */
    inline OGRCircularString* toCircularString()
        { return cpl::down_cast<OGRCircularString*>(this); }

    /** Down-cast to OGRCircularString*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbCircularString.
     * @since GDAL 2.3
     */
    inline const OGRCircularString* toCircularString() const
        { return cpl::down_cast<const OGRCircularString*>(this); }

    /** Down-cast to OGRCompoundCurve*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbCompoundCurve.
     * @since GDAL 2.3
     */
    inline OGRCompoundCurve* toCompoundCurve()
        { return cpl::down_cast<OGRCompoundCurve*>(this); }

    /** Down-cast to OGRCompoundCurve*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbCompoundCurve.
     * @since GDAL 2.3
     */
    inline const OGRCompoundCurve* toCompoundCurve() const
        { return cpl::down_cast<const OGRCompoundCurve*>(this); }

    /** Down-cast to OGRSurface*.
     * Implies prior checking that OGR_GT_IsSubClass(getGeometryType(), wkbSurface).
     * @since GDAL 2.3
     */
    inline OGRSurface* toSurface()
        { return cpl::down_cast<OGRSurface*>(this); }

    /** Down-cast to OGRSurface*.
     * Implies prior checking that OGR_GT_IsSubClass(getGeometryType(), wkbSurface).
     * @since GDAL 2.3
     */
    inline const OGRSurface* toSurface() const
        { return cpl::down_cast<const OGRSurface*>(this); }

    /** Down-cast to OGRPolygon*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbPolygon or wkbTriangle.
     * @since GDAL 2.3
     */
    inline OGRPolygon* toPolygon()
        { return cpl::down_cast<OGRPolygon*>(this); }

    /** Down-cast to OGRPolygon*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbPolygon or wkbTriangle.
     * @since GDAL 2.3
     */
    inline const OGRPolygon* toPolygon() const
        { return cpl::down_cast<const OGRPolygon*>(this); }

    /** Down-cast to OGRTriangle*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbTriangle.
     * @since GDAL 2.3
     */
    inline OGRTriangle* toTriangle()
        { return cpl::down_cast<OGRTriangle*>(this); }

    /** Down-cast to OGRTriangle*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbTriangle.
     * @since GDAL 2.3
     */
    inline const OGRTriangle* toTriangle() const
        { return cpl::down_cast<const OGRTriangle*>(this); }

    /** Down-cast to OGRCurvePolygon*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbCurvePolygon or wkbPolygon or wkbTriangle.
     * @since GDAL 2.3
     */
    inline OGRCurvePolygon* toCurvePolygon()
        { return cpl::down_cast<OGRCurvePolygon*>(this); }

    /** Down-cast to OGRCurvePolygon*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbCurvePolygon or wkbPolygon or wkbTriangle.
     * @since GDAL 2.3
     */
    inline const OGRCurvePolygon* toCurvePolygon() const
        { return cpl::down_cast<const OGRCurvePolygon*>(this); }

    /** Down-cast to OGRGeometryCollection*.
     * Implies prior checking that OGR_GT_IsSubClass(getGeometryType(), wkbGeometryCollection).
     * @since GDAL 2.3
     */
    inline OGRGeometryCollection* toGeometryCollection()
        { return cpl::down_cast<OGRGeometryCollection*>(this); }

    /** Down-cast to OGRGeometryCollection*.
     * Implies prior checking that OGR_GT_IsSubClass(getGeometryType(), wkbGeometryCollection).
     * @since GDAL 2.3
     */
    inline const OGRGeometryCollection* toGeometryCollection() const
        { return cpl::down_cast<const OGRGeometryCollection*>(this); }

    /** Down-cast to OGRMultiPoint*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbMultiPoint.
     * @since GDAL 2.3
     */
    inline OGRMultiPoint* toMultiPoint()
        { return cpl::down_cast<OGRMultiPoint*>(this); }

    /** Down-cast to OGRMultiPoint*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbMultiPoint.
     * @since GDAL 2.3
     */
    inline const OGRMultiPoint* toMultiPoint() const
        { return cpl::down_cast<const OGRMultiPoint*>(this); }

    /** Down-cast to OGRMultiLineString*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbMultiLineString.
     * @since GDAL 2.3
     */
    inline OGRMultiLineString* toMultiLineString()
        { return cpl::down_cast<OGRMultiLineString*>(this); }

    /** Down-cast to OGRMultiLineString*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbMultiLineString.
     * @since GDAL 2.3
     */
    inline const OGRMultiLineString* toMultiLineString() const
        { return cpl::down_cast<const OGRMultiLineString*>(this); }

    /** Down-cast to OGRMultiPolygon*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbMultiPolygon.
     * @since GDAL 2.3
     */
    inline OGRMultiPolygon* toMultiPolygon()
        { return cpl::down_cast<OGRMultiPolygon*>(this); }

    /** Down-cast to OGRMultiPolygon*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbMultiPolygon.
     * @since GDAL 2.3
     */
    inline const OGRMultiPolygon* toMultiPolygon() const
        { return cpl::down_cast<const OGRMultiPolygon*>(this); }

    /** Down-cast to OGRMultiCurve*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbMultiCurve and derived types.
     * @since GDAL 2.3
     */
    inline OGRMultiCurve* toMultiCurve()
        { return cpl::down_cast<OGRMultiCurve*>(this); }

    /** Down-cast to OGRMultiCurve*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbMultiCurve and derived types.
     * @since GDAL 2.3
     */
    inline const OGRMultiCurve* toMultiCurve() const
        { return cpl::down_cast<const OGRMultiCurve*>(this); }

    /** Down-cast to OGRMultiSurface*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbMultiSurface and derived types.
     * @since GDAL 2.3
     */
    inline OGRMultiSurface* toMultiSurface()
        { return cpl::down_cast<OGRMultiSurface*>(this); }

    /** Down-cast to OGRMultiSurface*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbMultiSurface and derived types.
     * @since GDAL 2.3
     */
    inline const OGRMultiSurface* toMultiSurface() const
        { return cpl::down_cast<const OGRMultiSurface*>(this); }

    /** Down-cast to OGRPolyhedralSurface*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbPolyhedralSurface or wkbTIN.
     * @since GDAL 2.3
     */
    inline OGRPolyhedralSurface* toPolyhedralSurface()
        { return cpl::down_cast<OGRPolyhedralSurface*>(this); }

    /** Down-cast to OGRPolyhedralSurface*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbPolyhedralSurface or wkbTIN.
     * @since GDAL 2.3
     */
    inline const OGRPolyhedralSurface* toPolyhedralSurface() const
        { return cpl::down_cast<const OGRPolyhedralSurface*>(this); }

    /** Down-cast to OGRTriangulatedSurface*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbTIN.
     * @since GDAL 2.3
     */
    inline OGRTriangulatedSurface* toTriangulatedSurface()
        { return cpl::down_cast<OGRTriangulatedSurface*>(this); }

    /** Down-cast to OGRTriangulatedSurface*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbTIN.
     * @since GDAL 2.3
     */
    inline const OGRTriangulatedSurface* toTriangulatedSurface() const
        { return cpl::down_cast<const OGRTriangulatedSurface*>(this); }

};

//! @cond Doxygen_Suppress
struct OGRGeometryUniquePtrDeleter
{
    HGDAL_EXPORT void operator()(OGRGeometry*) const;
};
//! @endcond

/** Unique pointer type for OGRGeometry.
 * @since GDAL 2.3
 */
typedef std::unique_ptr<OGRGeometry, OGRGeometryUniquePtrDeleter> OGRGeometryUniquePtr;


//! @cond Doxygen_Suppress
#define OGR_FORBID_DOWNCAST_TO(name) \
    inline OGR ## name * to ## name() = delete; \
    inline const OGR ## name * to ## name() const = delete;

#define OGR_FORBID_DOWNCAST_TO_POINT              OGR_FORBID_DOWNCAST_TO(Point)
#define OGR_FORBID_DOWNCAST_TO_CURVE              OGR_FORBID_DOWNCAST_TO(Curve)
#define OGR_FORBID_DOWNCAST_TO_SIMPLE_CURVE       OGR_FORBID_DOWNCAST_TO(SimpleCurve)
#define OGR_FORBID_DOWNCAST_TO_LINESTRING         OGR_FORBID_DOWNCAST_TO(LineString)
#define OGR_FORBID_DOWNCAST_TO_LINEARRING         OGR_FORBID_DOWNCAST_TO(LinearRing)
#define OGR_FORBID_DOWNCAST_TO_CIRCULARSTRING     OGR_FORBID_DOWNCAST_TO(CircularString)
#define OGR_FORBID_DOWNCAST_TO_COMPOUNDCURVE      OGR_FORBID_DOWNCAST_TO(CompoundCurve)
#define OGR_FORBID_DOWNCAST_TO_SURFACE            OGR_FORBID_DOWNCAST_TO(Surface)
#define OGR_FORBID_DOWNCAST_TO_CURVEPOLYGON       OGR_FORBID_DOWNCAST_TO(CurvePolygon)
#define OGR_FORBID_DOWNCAST_TO_POLYGON            OGR_FORBID_DOWNCAST_TO(Polygon)
#define OGR_FORBID_DOWNCAST_TO_TRIANGLE           OGR_FORBID_DOWNCAST_TO(Triangle)
#define OGR_FORBID_DOWNCAST_TO_MULTIPOINT         OGR_FORBID_DOWNCAST_TO(MultiPoint)
#define OGR_FORBID_DOWNCAST_TO_MULTICURVE         OGR_FORBID_DOWNCAST_TO(MultiCurve)
#define OGR_FORBID_DOWNCAST_TO_MULTILINESTRING    OGR_FORBID_DOWNCAST_TO(MultiLineString)
#define OGR_FORBID_DOWNCAST_TO_MULTISURFACE       OGR_FORBID_DOWNCAST_TO(MultiSurface)
#define OGR_FORBID_DOWNCAST_TO_MULTIPOLYGON       OGR_FORBID_DOWNCAST_TO(MultiPolygon)
#define OGR_FORBID_DOWNCAST_TO_GEOMETRYCOLLECTION OGR_FORBID_DOWNCAST_TO(GeometryCollection)
#define OGR_FORBID_DOWNCAST_TO_POLYHEDRALSURFACE  OGR_FORBID_DOWNCAST_TO(PolyhedralSurface)
#define OGR_FORBID_DOWNCAST_TO_TIN                OGR_FORBID_DOWNCAST_TO(TriangulatedSurface)

#define OGR_ALLOW_UPCAST_TO(name) \
    inline OGR ## name * to ## name() { return this; } \
    inline const OGR ## name * to ## name() const { return this; }

#ifndef SUPPRESS_OGR_ALLOW_CAST_TO_THIS_WARNING
#define CAST_TO_THIS_WARNING CPL_WARN_DEPRECATED("Casting to this is useless")
#else
#define CAST_TO_THIS_WARNING
#endif

#define OGR_ALLOW_CAST_TO_THIS(name) \
    inline OGR ## name * to ## name() CAST_TO_THIS_WARNING { return this; } \
    inline const OGR ## name * to ## name() const CAST_TO_THIS_WARNING { return this; }

#define OGR_FORBID_DOWNCAST_TO_ALL_CURVES \
    OGR_FORBID_DOWNCAST_TO_CURVE \
    OGR_FORBID_DOWNCAST_TO_SIMPLE_CURVE \
    OGR_FORBID_DOWNCAST_TO_LINESTRING \
    OGR_FORBID_DOWNCAST_TO_LINEARRING \
    OGR_FORBID_DOWNCAST_TO_CIRCULARSTRING \
    OGR_FORBID_DOWNCAST_TO_COMPOUNDCURVE

#define OGR_FORBID_DOWNCAST_TO_ALL_SURFACES \
    OGR_FORBID_DOWNCAST_TO_SURFACE \
    OGR_FORBID_DOWNCAST_TO_CURVEPOLYGON \
    OGR_FORBID_DOWNCAST_TO_POLYGON \
    OGR_FORBID_DOWNCAST_TO_TRIANGLE \
    OGR_FORBID_DOWNCAST_TO_POLYHEDRALSURFACE \
    OGR_FORBID_DOWNCAST_TO_TIN

#define OGR_FORBID_DOWNCAST_TO_ALL_SINGLES \
    OGR_FORBID_DOWNCAST_TO_POINT \
    OGR_FORBID_DOWNCAST_TO_ALL_CURVES \
    OGR_FORBID_DOWNCAST_TO_ALL_SURFACES

#define OGR_FORBID_DOWNCAST_TO_ALL_MULTI \
    OGR_FORBID_DOWNCAST_TO_GEOMETRYCOLLECTION \
    OGR_FORBID_DOWNCAST_TO_MULTIPOINT \
    OGR_FORBID_DOWNCAST_TO_MULTICURVE \
    OGR_FORBID_DOWNCAST_TO_MULTILINESTRING \
    OGR_FORBID_DOWNCAST_TO_MULTISURFACE \
    OGR_FORBID_DOWNCAST_TO_MULTIPOLYGON

//! @endcond

/************************************************************************/
/*                               OGRPoint                               */
/************************************************************************/

/**
 * Point class.
 *
 * Implements SFCOM IPoint methods.
 */

class OGRPoint : public OGRGeometry
{
    double      x;
    double      y;
    double      z;
    double      m;

  public:
    HGDAL_EXPORT OGRPoint();
    HGDAL_EXPORT OGRPoint( double x, double y );
    HGDAL_EXPORT OGRPoint( double x, double y, double z );
    HGDAL_EXPORT OGRPoint( double x, double y, double z, double m );
    HGDAL_EXPORT OGRPoint( const OGRPoint& other );
    HGDAL_EXPORT static OGRPoint* createXYM( double x, double y, double m );
    HGDAL_EXPORT ~OGRPoint() override;

    HGDAL_EXPORT OGRPoint& operator=( const OGRPoint& other );

    // IWks Interface
    HGDAL_EXPORT size_t WkbSize() const override;
    HGDAL_EXPORT OGRErr importFromWkb( const unsigned char *,
                          size_t,
                          OGRwkbVariant,
                          size_t& nBytesConsumedOut ) override;
    HGDAL_EXPORT OGRErr exportToWkb( OGRwkbByteOrder, unsigned char *,
                        OGRwkbVariant=wkbVariantOldOgc )
        const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::importFromWkt; /** deprecated */
#endif

    HGDAL_EXPORT OGRErr importFromWkt( const char ** ) override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a point to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return  WKT string representing this point.
    HGDAL_EXPORT virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    // IGeometry
    HGDAL_EXPORT virtual int getDimension() const override;
    HGDAL_EXPORT virtual OGRPoint *clone() const override;
    HGDAL_EXPORT virtual void empty() override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope * psEnvelope ) const override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope3D * psEnvelope ) const override;
    virtual OGRBoolean  IsEmpty() const override
        { return !(flags & OGR_G_NOT_EMPTY_POINT); }

    // IPoint
    /** Return x */
    double      getX() const { return x; }
    /** Return y */
    double      getY() const { return y; }
    /** Return z */
    double      getZ() const { return z; }
    /** Return m */
    double      getM() const { return m; }

    // Non standard
    HGDAL_EXPORT virtual void setCoordinateDimension( int nDimension ) override;
    /** Set x
     * @param xIn x
     */
    void        setX( double xIn ) { x = xIn; if( std::isnan(x) || std::isnan(y) ) flags &= ~OGR_G_NOT_EMPTY_POINT; else flags |= OGR_G_NOT_EMPTY_POINT; }
    /** Set y
     * @param yIn y
     */
    void        setY( double yIn ) { y = yIn; if( std::isnan(x) || std::isnan(y) ) flags &= ~OGR_G_NOT_EMPTY_POINT; else flags |= OGR_G_NOT_EMPTY_POINT; }
    /** Set z
     * @param zIn z
     */
    void        setZ( double zIn )
        { z = zIn; flags |= OGR_G_3D; }
    /** Set m
     * @param mIn m
     */
    void        setM( double mIn )
        { m = mIn; flags |= OGR_G_MEASURED; }

    // ISpatialRelation
    HGDAL_EXPORT virtual OGRBoolean  Equals( const OGRGeometry * ) const override;
    HGDAL_EXPORT virtual OGRBoolean  Intersects( const OGRGeometry * ) const override;
    HGDAL_EXPORT virtual OGRBoolean  Within( const OGRGeometry * ) const override;

    // Non standard from OGRGeometry
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual OGRErr  transform( OGRCoordinateTransformation *poCT ) override;
    HGDAL_EXPORT virtual void flattenTo2D() override;
    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    HGDAL_EXPORT virtual void        swapXY() override;

    OGR_ALLOW_CAST_TO_THIS(Point)
    OGR_FORBID_DOWNCAST_TO_ALL_CURVES
    OGR_FORBID_DOWNCAST_TO_ALL_SURFACES
    OGR_FORBID_DOWNCAST_TO_ALL_MULTI
};

/************************************************************************/
/*                            OGRPointIterator                          */
/************************************************************************/

/**
 * Interface for a point iterator.
 *
 * @since GDAL 2.0
 */

class OGRPointIterator
{
    public:
        HGDAL_EXPORT virtual ~OGRPointIterator();
        HGDAL_EXPORT virtual OGRBoolean getNextPoint( OGRPoint* p ) = 0;

        HGDAL_EXPORT static void destroy( OGRPointIterator* );
};

/************************************************************************/
/*                               OGRCurve                               */
/************************************************************************/

/**
 * Abstract curve base class for OGRLineString, OGRCircularString and
 * OGRCompoundCurve
 */

class OGRCurve : public OGRGeometry
{
  protected:
//! @cond Doxygen_Suppress
    HGDAL_EXPORT         OGRCurve();
    HGDAL_EXPORT         OGRCurve( const OGRCurve& other );

    virtual OGRCurveCasterToLineString GetCasterToLineString() const = 0;
    virtual OGRCurveCasterToLinearRing GetCasterToLinearRing() const = 0;

    friend class OGRCurvePolygon;
    friend class OGRCompoundCurve;
//! @endcond
    HGDAL_EXPORT virtual int ContainsPoint( const OGRPoint* p ) const;
    HGDAL_EXPORT virtual int IntersectsPoint( const OGRPoint* p ) const;
    HGDAL_EXPORT virtual double get_AreaOfCurveSegments() const = 0;

    private:

        class ConstIterator
        {
                struct Private;
                std::unique_ptr<Private> m_poPrivate;
            public:
                HGDAL_EXPORT ConstIterator(const OGRCurve* poSelf, bool bStart);
                HGDAL_EXPORT ConstIterator(ConstIterator&& oOther) noexcept; // declared but not defined. Needed for gcc 5.4 at least
                HGDAL_EXPORT ~ConstIterator();
                HGDAL_EXPORT const OGRPoint& operator*() const;
                HGDAL_EXPORT ConstIterator& operator++();
                HGDAL_EXPORT bool operator!=(const ConstIterator& it) const;
        };

        friend inline ConstIterator begin(const OGRCurve*);
        friend inline ConstIterator end(const OGRCurve*);

  public:
      HGDAL_EXPORT ~OGRCurve() override;

//! @cond Doxygen_Suppress
      HGDAL_EXPORT OGRCurve& operator=( const OGRCurve& other );
//! @endcond

    /** Type of child elements. */
    typedef OGRPoint ChildType;

    /** Return begin of a point iterator.
     *
     * Using this iterator for standard range-based loops is safe, but
     * due to implementation limitations, you shouldn't try to access
     * (dereference) more than one iterator step at a time, since you will get
     * a reference to the same OGRPoint& object.
     * @since GDAL 2.3
     */
    HGDAL_EXPORT ConstIterator begin() const;
    /** Return end of a point iterator. */
    HGDAL_EXPORT ConstIterator end() const;

    // IGeometry
    virtual OGRCurve *clone() const override = 0;

    // ICurve methods
    virtual double get_Length() const = 0;
    virtual void StartPoint( OGRPoint * ) const = 0;
    virtual void EndPoint( OGRPoint * ) const = 0;
    HGDAL_EXPORT virtual int  get_IsClosed() const;
    virtual void Value( double, OGRPoint * ) const = 0;
    virtual OGRLineString* CurveToLine( double dfMaxAngleStepSizeDegrees = 0,
                                        const char* const* papszOptions = nullptr)
        const = 0;
    HGDAL_EXPORT virtual int getDimension() const override;

    // non standard
    virtual int getNumPoints() const = 0;
    virtual OGRPointIterator* getPointIterator() const = 0;
    HGDAL_EXPORT virtual OGRBoolean IsConvex() const;
    virtual double get_Area() const = 0;

    /** Down-cast to OGRSimpleCurve*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbLineString or wkbCircularString. */
    inline OGRSimpleCurve* toSimpleCurve()
        { return cpl::down_cast<OGRSimpleCurve*>(this); }

    /** Down-cast to OGRSimpleCurve*.
     * Implies prior checking that wkbFlatten(getGeometryType()) == wkbLineString or wkbCircularString. */
    inline const OGRSimpleCurve* toSimpleCurve() const
        { return cpl::down_cast<const OGRSimpleCurve*>(this); }

    HGDAL_EXPORT static OGRCompoundCurve* CastToCompoundCurve( OGRCurve* puCurve );
    HGDAL_EXPORT static OGRLineString*    CastToLineString( OGRCurve* poCurve );
    HGDAL_EXPORT static OGRLinearRing*    CastToLinearRing( OGRCurve* poCurve );

    OGR_FORBID_DOWNCAST_TO_POINT
    OGR_ALLOW_CAST_TO_THIS(Curve)
    OGR_FORBID_DOWNCAST_TO_ALL_SURFACES
    OGR_FORBID_DOWNCAST_TO_ALL_MULTI
};

//! @cond Doxygen_Suppress
/** @see OGRCurve::begin() const */
inline OGRCurve::ConstIterator begin(const OGRCurve* poCurve) { return poCurve->begin(); }
/** @see OGRCurve::end() const */
inline OGRCurve::ConstIterator end(const OGRCurve* poCurve) { return poCurve->end(); }
//! @endcond

/************************************************************************/
/*                             OGRSimpleCurve                           */
/************************************************************************/

/**
 * Abstract curve base class for OGRLineString and OGRCircularString
 *
 * Note: this class does not exist in SQL/MM standard and exists for
 * implementation convenience.
 *
 * @since GDAL 2.0
 */

class OGRSimpleCurve: public OGRCurve
{
  protected:
//! @cond Doxygen_Suppress
    friend class OGRGeometry;

    int         nPointCount;
    OGRRawPoint *paoPoints;
    double      *padfZ;
    double      *padfM;

    HGDAL_EXPORT void        Make3D();
    HGDAL_EXPORT void        Make2D();
    HGDAL_EXPORT void        RemoveM();
    HGDAL_EXPORT void        AddM();

    HGDAL_EXPORT OGRErr      importFromWKTListOnly( const char ** ppszInput, int bHasZ, int bHasM,
                                       OGRRawPoint*& paoPointsIn,
                                       int& nMaxPoints,
                                       double*& padfZIn );
//! @endcond

    HGDAL_EXPORT virtual double get_LinearArea() const;

    HGDAL_EXPORT             OGRSimpleCurve();
    HGDAL_EXPORT             OGRSimpleCurve( const OGRSimpleCurve& other );

  private:
        class Iterator
        {
                struct Private;
                std::unique_ptr<Private> m_poPrivate;
                HGDAL_EXPORT void update();
            public:
                HGDAL_EXPORT Iterator(OGRSimpleCurve* poSelf, int nPos);
                HGDAL_EXPORT Iterator(Iterator&& oOther) noexcept; // declared but not defined. Needed for gcc 5.4 at least
                HGDAL_EXPORT ~Iterator();
                HGDAL_EXPORT OGRPoint& operator*();
                HGDAL_EXPORT Iterator& operator++();
                HGDAL_EXPORT bool operator!=(const Iterator& it) const;
        };

        friend inline Iterator begin(OGRSimpleCurve*);
        friend inline Iterator end(OGRSimpleCurve*);

        class ConstIterator
        {
                struct Private;
                std::unique_ptr<Private> m_poPrivate;
            public:
                HGDAL_EXPORT ConstIterator(const OGRSimpleCurve* poSelf, int nPos);
                HGDAL_EXPORT ConstIterator(ConstIterator&& oOther) noexcept; // declared but not defined. Needed for gcc 5.4 at least
                HGDAL_EXPORT ~ConstIterator();
                HGDAL_EXPORT const OGRPoint& operator*() const;
                HGDAL_EXPORT ConstIterator& operator++();
                HGDAL_EXPORT bool operator!=(const ConstIterator& it) const;
        };

        friend inline ConstIterator begin(const OGRSimpleCurve*);
        friend inline ConstIterator end(const OGRSimpleCurve*);

  public:
    HGDAL_EXPORT ~OGRSimpleCurve() override;

    HGDAL_EXPORT OGRSimpleCurve& operator=( const OGRSimpleCurve& other );

    /** Type of child elements. */
    typedef OGRPoint ChildType;

    /** Return begin of point iterator.
     *
     * Using this iterator for standard range-based loops is safe, but
     * due to implementation limitations, you shouldn't try to access
     * (dereference) more than one iterator step at a time, since you will get
     * a reference to the same OGRPoint& object.
     * @since GDAL 2.3
     */
    HGDAL_EXPORT Iterator begin();
    /** Return end of point iterator. */
    HGDAL_EXPORT Iterator end();
    /** Return begin of point iterator.
     *
     * Using this iterator for standard range-based loops is safe, but
     * due to implementation limitations, you shouldn't try to access
     * (dereference) more than one iterator step at a time, since you will get
     * a reference to the same OGRPoint& object.
     * @since GDAL 2.3
     */
    HGDAL_EXPORT ConstIterator begin() const;
    /** Return end of point iterator. */
    HGDAL_EXPORT ConstIterator end() const;

    // IWks Interface.
    HGDAL_EXPORT virtual size_t WkbSize() const override;
    HGDAL_EXPORT virtual OGRErr importFromWkb( const unsigned char *,
                                  size_t,
                                  OGRwkbVariant,
                                  size_t& nBytesConsumedOut ) override;
    HGDAL_EXPORT virtual OGRErr exportToWkb( OGRwkbByteOrder, unsigned char *,
                                OGRwkbVariant=wkbVariantOldOgc )
        const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::importFromWkt; /** deprecated */
#endif

    HGDAL_EXPORT OGRErr importFromWkt( const char ** ) override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a simple curve to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return  WKT string representing this simple curve.
    HGDAL_EXPORT virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    // IGeometry interface.
    HGDAL_EXPORT virtual void empty() override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope * psEnvelope ) const override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope3D * psEnvelope ) const override;
    HGDAL_EXPORT virtual OGRBoolean  IsEmpty() const override;
    virtual OGRSimpleCurve *clone() const override = 0;

    // ICurve methods.
    HGDAL_EXPORT virtual double get_Length() const override;
    HGDAL_EXPORT virtual void StartPoint( OGRPoint * ) const override;
    HGDAL_EXPORT virtual void EndPoint( OGRPoint * ) const override;
    HGDAL_EXPORT virtual void Value( double, OGRPoint * ) const override;
    HGDAL_EXPORT virtual double Project( const OGRPoint * ) const;
    HGDAL_EXPORT virtual OGRLineString* getSubLine( double, double, int ) const;

    // ILineString methods.
    virtual int getNumPoints() const override { return nPointCount; }
    HGDAL_EXPORT void        getPoint( int, OGRPoint * ) const;
    double      getX( int i ) const { return paoPoints[i].x; }
    double      getY( int i ) const { return paoPoints[i].y; }
    HGDAL_EXPORT double      getZ( int i ) const;
    HGDAL_EXPORT double      getM( int i ) const;

    // ISpatialRelation
    HGDAL_EXPORT virtual OGRBoolean  Equals( const OGRGeometry * ) const override;

    // non standard.
    HGDAL_EXPORT virtual void setCoordinateDimension( int nDimension ) override;
    HGDAL_EXPORT virtual void set3D( OGRBoolean bIs3D ) override;
    HGDAL_EXPORT virtual void setMeasured( OGRBoolean bIsMeasured ) override;
    HGDAL_EXPORT void        setNumPoints( int nNewPointCount,
                              int bZeroizeNewContent = TRUE );
    HGDAL_EXPORT void        setPoint( int, OGRPoint * );
    HGDAL_EXPORT void        setPoint( int, double, double );
    HGDAL_EXPORT void        setZ( int, double );
    HGDAL_EXPORT void        setM( int, double );
    HGDAL_EXPORT void        setPoint( int, double, double, double );
    HGDAL_EXPORT void        setPointM( int, double, double, double );
    HGDAL_EXPORT void        setPoint( int, double, double, double, double );
    HGDAL_EXPORT void        setPoints( int, const OGRRawPoint *, const double * = nullptr );
    HGDAL_EXPORT void        setPointsM( int, const OGRRawPoint *, const double * );
    HGDAL_EXPORT void        setPoints( int, const OGRRawPoint *, const double *, const double * );
    HGDAL_EXPORT void        setPoints( int, const double * padfX, const double * padfY,
                           const double *padfZIn = nullptr );
    HGDAL_EXPORT void        setPointsM( int, const double * padfX, const double * padfY,
                            const double *padfMIn = nullptr );
    HGDAL_EXPORT void        setPoints( int, const double * padfX, const double * padfY,
                           const double *padfZIn, const double *padfMIn );
    HGDAL_EXPORT void        addPoint( const OGRPoint * );
    HGDAL_EXPORT void        addPoint( double, double );
    HGDAL_EXPORT void        addPoint( double, double, double );
    HGDAL_EXPORT void        addPointM( double, double, double );
    HGDAL_EXPORT void        addPoint( double, double, double, double );

    HGDAL_EXPORT bool        removePoint( int );

    HGDAL_EXPORT void        getPoints( OGRRawPoint *, double * = nullptr ) const;
    HGDAL_EXPORT void        getPoints( void* pabyX, int nXStride,
                           void* pabyY, int nYStride,
                           void* pabyZ = nullptr, int nZStride = 0,
                           void* pabyM = nullptr, int nMStride = 0 ) const;

    HGDAL_EXPORT void        addSubLineString( const OGRLineString *,
                                  int nStartVertex = 0, int nEndVertex = -1 );
    HGDAL_EXPORT void        reversePoints( void );
    HGDAL_EXPORT virtual OGRPointIterator* getPointIterator() const override;

    // non-standard from OGRGeometry
    HGDAL_EXPORT virtual OGRErr  transform( OGRCoordinateTransformation *poCT ) override;
    HGDAL_EXPORT virtual void flattenTo2D() override;
    HGDAL_EXPORT virtual void segmentize(double dfMaxLength) override;

    HGDAL_EXPORT virtual void        swapXY() override;

    OGR_ALLOW_UPCAST_TO(Curve)
    OGR_ALLOW_CAST_TO_THIS(SimpleCurve)
};

//! @cond Doxygen_Suppress
/** @see OGRSimpleCurve::begin() */
inline OGRSimpleCurve::Iterator begin(OGRSimpleCurve* poCurve) { return poCurve->begin(); }
/** @see OGRSimpleCurve::end() */
inline OGRSimpleCurve::Iterator end(OGRSimpleCurve* poCurve) { return poCurve->end(); }

/** @see OGRSimpleCurve::begin() const */
inline OGRSimpleCurve::ConstIterator begin(const OGRSimpleCurve* poCurve) { return poCurve->begin(); }
/** @see OGRSimpleCurve::end() const */
inline OGRSimpleCurve::ConstIterator end(const OGRSimpleCurve* poCurve) { return poCurve->end(); }
//! @endcond

/************************************************************************/
/*                            OGRLineString                             */
/************************************************************************/

/**
 * Concrete representation of a multi-vertex line.
 *
 * Note: for implementation convenience, we make it inherit from OGRSimpleCurve
 * whereas SFSQL and SQL/MM only make it inherits from OGRCurve.
 */

class OGRLineString : public OGRSimpleCurve
{
    // cppcheck-suppress unusedPrivateFunction
    HGDAL_EXPORT static OGRLinearRing*          CasterToLinearRing(OGRCurve* poCurve);

  protected:
//! @cond Doxygen_Suppress
    HGDAL_EXPORT static OGRLineString* TransferMembersAndDestroy(
                                            OGRLineString* poSrc,
                                            OGRLineString* poDst);

    HGDAL_EXPORT virtual OGRCurveCasterToLineString GetCasterToLineString()
        const override;
    HGDAL_EXPORT virtual OGRCurveCasterToLinearRing GetCasterToLinearRing()
        const override;

    HGDAL_EXPORT virtual double get_AreaOfCurveSegments() const override;
//! @endcond

    HGDAL_EXPORT static OGRLinearRing* CastToLinearRing( OGRLineString* poLS );

  public:
    HGDAL_EXPORT OGRLineString();
    HGDAL_EXPORT OGRLineString( const OGRLineString& other );
    HGDAL_EXPORT ~OGRLineString() override;

    HGDAL_EXPORT OGRLineString& operator=(const OGRLineString& other);

    HGDAL_EXPORT virtual OGRLineString *clone() const override;
    HGDAL_EXPORT virtual OGRLineString* CurveToLine( double dfMaxAngleStepSizeDegrees = 0,
                                        const char* const* papszOptions = nullptr )
        const override;
    HGDAL_EXPORT virtual OGRGeometry* getCurveGeometry(
        const char* const* papszOptions = nullptr ) const override;
    HGDAL_EXPORT virtual double get_Area() const override;

    // Non-standard from OGRGeometry.
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual const char *getGeometryName() const override;

    /** Return pointer of this in upper class */
    HGDAL_EXPORT inline OGRSimpleCurve* toUpperClass() { return this; }
    /** Return pointer of this in upper class */
    HGDAL_EXPORT inline const OGRSimpleCurve* toUpperClass() const { return this; }

    HGDAL_EXPORT virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    HGDAL_EXPORT virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    OGR_ALLOW_UPCAST_TO(SimpleCurve)
    OGR_ALLOW_CAST_TO_THIS(LineString)
};

/************************************************************************/
/*                            OGRLinearRing                             */
/************************************************************************/

/**
 * Concrete representation of a closed ring.
 *
 * This class is functionally equivalent to an OGRLineString, but has a
 * separate identity to maintain alignment with the OpenGIS simple feature
 * data model.  It exists to serve as a component of an OGRPolygon.
 *
 * The OGRLinearRing has no corresponding free standing well known binary
 * representation, so importFromWkb() and exportToWkb() will not actually
 * work.  There is a non-standard GDAL WKT representation though.
 *
 * Because OGRLinearRing is not a "proper" free standing simple features
 * object, it cannot be directly used on a feature via SetGeometry(), and
 * cannot generally be used with GEOS for operations like Intersects().
 * Instead the polygon should be used, or the OGRLinearRing should be
 * converted to an OGRLineString for such operations.
 *
 * Note: this class exists in SFSQL 1.2, but not in ISO SQL/MM Part 3.
 */

class OGRLinearRing : public OGRLineString
{
    HGDAL_EXPORT static OGRLineString*       CasterToLineString( OGRCurve* poCurve );

    // IWks Interface - Note this isn't really a first class object
    // for the purposes of WKB form.  These methods always fail since this
    // object can't be serialized on its own.
    HGDAL_EXPORT virtual size_t WkbSize() const override;
    HGDAL_EXPORT virtual OGRErr importFromWkb( const unsigned char *,
                                  size_t,
                                  OGRwkbVariant,
                                  size_t& nBytesConsumedOut ) override;
    HGDAL_EXPORT virtual OGRErr exportToWkb( OGRwkbByteOrder, unsigned char *,
                                OGRwkbVariant=wkbVariantOldOgc )
        const override;

  protected:
//! @cond Doxygen_Suppress
    friend class OGRPolygon;
    friend class OGRTriangle;

    // These are not IWks compatible ... just a convenience for OGRPolygon.
    HGDAL_EXPORT virtual size_t _WkbSize( int _flags ) const;
    HGDAL_EXPORT virtual OGRErr _importFromWkb( OGRwkbByteOrder, int _flags,
                                   const unsigned char *, size_t,
                                   size_t& nBytesConsumedOut );
    HGDAL_EXPORT virtual OGRErr _exportToWkb( OGRwkbByteOrder, int _flags,
                                 unsigned char * ) const;

    HGDAL_EXPORT virtual OGRCurveCasterToLineString GetCasterToLineString()
        const override;
    HGDAL_EXPORT virtual OGRCurveCasterToLinearRing GetCasterToLinearRing()
        const override;
//! @endcond

    HGDAL_EXPORT static OGRLineString* CastToLineString( OGRLinearRing* poLR );

  public:
    HGDAL_EXPORT OGRLinearRing();
    HGDAL_EXPORT OGRLinearRing( const OGRLinearRing& other );
    HGDAL_EXPORT explicit OGRLinearRing( OGRLinearRing * );
    HGDAL_EXPORT ~OGRLinearRing() override;

    HGDAL_EXPORT OGRLinearRing& operator=( const OGRLinearRing& other );

    // Non standard.
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRLinearRing *clone() const override;
    HGDAL_EXPORT virtual int isClockwise() const;
    HGDAL_EXPORT virtual void reverseWindingOrder();
    HGDAL_EXPORT virtual void closeRings() override;
    HGDAL_EXPORT OGRBoolean isPointInRing( const OGRPoint* pt,
                              int bTestEnvelope = TRUE ) const;
    HGDAL_EXPORT OGRBoolean isPointOnRingBoundary( const OGRPoint* pt,
                                      int bTestEnvelope = TRUE ) const;
    HGDAL_EXPORT virtual OGRErr  transform( OGRCoordinateTransformation *poCT ) override;

    /** Return pointer of this in upper class */
    inline OGRLineString* toUpperClass() { return this; }
    /** Return pointer of this in upper class */
    inline const OGRLineString* toUpperClass() const { return this; }

    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    OGR_ALLOW_UPCAST_TO(LineString)
    OGR_ALLOW_CAST_TO_THIS(LinearRing)
};

/************************************************************************/
/*                         OGRCircularString                            */
/************************************************************************/

/**
 * Concrete representation of a circular string, that is to say a curve made
 * of one or several arc circles.
 *
 * Note: for implementation convenience, we make it inherit from OGRSimpleCurve
 * whereas SQL/MM only makes it inherits from OGRCurve.
 *
 * Compatibility: ISO SQL/MM Part 3.
 *
 * @since GDAL 2.0
 */

class OGRCircularString : public OGRSimpleCurve
{
  private:
    HGDAL_EXPORT void        ExtendEnvelopeWithCircular( OGREnvelope * psEnvelope ) const;
    HGDAL_EXPORT OGRBoolean  IsValidFast() const;
    HGDAL_EXPORT int         IsFullCircle( double& cx, double& cy, double& square_R ) const;

  protected:
//! @cond Doxygen_Suppress
    HGDAL_EXPORT virtual OGRCurveCasterToLineString GetCasterToLineString()
        const override;
    HGDAL_EXPORT virtual OGRCurveCasterToLinearRing GetCasterToLinearRing()
        const override;
    HGDAL_EXPORT virtual int    IntersectsPoint( const OGRPoint* p ) const override;
    HGDAL_EXPORT virtual int    ContainsPoint( const OGRPoint* p ) const override;
    HGDAL_EXPORT virtual double get_AreaOfCurveSegments() const override;
//! @endcond

  public:
    HGDAL_EXPORT OGRCircularString();
    HGDAL_EXPORT OGRCircularString( const OGRCircularString& other );
    HGDAL_EXPORT ~OGRCircularString() override;

    HGDAL_EXPORT OGRCircularString& operator=(const OGRCircularString& other);

    // IWks Interface.
    HGDAL_EXPORT virtual OGRErr importFromWkb( const unsigned char *,
                                  size_t,
                                  OGRwkbVariant,
                                  size_t& nBytesConsumedOut ) override;
    HGDAL_EXPORT virtual OGRErr exportToWkb( OGRwkbByteOrder, unsigned char *,
                                OGRwkbVariant=wkbVariantOldOgc )
        const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::importFromWkt; /** deprecated */
#endif

    HGDAL_EXPORT OGRErr importFromWkt( const char ** ) override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a circular string to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return  WKT string representing this circular string.
    HGDAL_EXPORT virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    // IGeometry interface.
    HGDAL_EXPORT virtual OGRBoolean  IsValid() const override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope * psEnvelope ) const override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope3D * psEnvelope ) const override;
    HGDAL_EXPORT virtual OGRCircularString *clone() const override;

    // ICurve methods.
    HGDAL_EXPORT virtual double get_Length() const override;
    HGDAL_EXPORT virtual OGRLineString* CurveToLine( double dfMaxAngleStepSizeDegrees = 0,
                                        const char* const* papszOptions = nullptr )
        const override;
    HGDAL_EXPORT virtual void Value( double, OGRPoint * ) const override;
    HGDAL_EXPORT virtual double get_Area() const override;

    // Non-standard from OGRGeometry.
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual void segmentize( double dfMaxLength ) override;
    HGDAL_EXPORT virtual OGRBoolean hasCurveGeometry( int bLookForNonLinear = FALSE )
        const override;
    HGDAL_EXPORT virtual OGRGeometry* getLinearGeometry(
        double dfMaxAngleStepSizeDegrees = 0,
        const char* const* papszOptions = nullptr) const override;

    /** Return pointer of this in upper class */
    inline OGRSimpleCurve* toUpperClass() { return this; }
    /** Return pointer of this in upper class */
    inline const OGRSimpleCurve* toUpperClass() const { return this; }

    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    OGR_ALLOW_UPCAST_TO(SimpleCurve)
    OGR_ALLOW_CAST_TO_THIS(CircularString)
};

/************************************************************************/
/*                           OGRCurveCollection                         */
/************************************************************************/

/**
 * Utility class to store a collection of curves. Used as a member of
 * OGRCompoundCurve and OGRCurvePolygon.
 *
 * This class is only exported because of linking issues. It should never
 * be directly used.
 *
 * @since GDAL 2.0
 */

//! @cond Doxygen_Suppress
class OGRCurveCollection
{
  protected:
    friend class OGRCompoundCurve;
    friend class OGRCurvePolygon;
    friend class OGRPolygon;
    friend class OGRTriangle;

    int         nCurveCount = 0;
    OGRCurve  **papoCurves = nullptr;

  public:
    HGDAL_EXPORT             OGRCurveCollection();
    HGDAL_EXPORT             OGRCurveCollection(const OGRCurveCollection& other);
    HGDAL_EXPORT            ~OGRCurveCollection();

    HGDAL_EXPORT OGRCurveCollection& operator=(const OGRCurveCollection& other);

    /** Type of child elements. */
    typedef OGRCurve ChildType;

    /** Return begin of curve iterator.
     * @since GDAL 2.3
     */
    OGRCurve** begin() { return papoCurves; }
    /** Return end of curve iterator. */
    OGRCurve** end() { return papoCurves + nCurveCount; }
    /** Return begin of curve iterator.
     * @since GDAL 2.3
     */
    const OGRCurve* const* begin() const { return papoCurves; }
    /** Return end of curve iterator. */
    const OGRCurve* const* end() const { return papoCurves + nCurveCount; }

    HGDAL_EXPORT void            empty(OGRGeometry* poGeom);
    HGDAL_EXPORT OGRBoolean      IsEmpty() const;
    HGDAL_EXPORT void            getEnvelope( OGREnvelope * psEnvelope ) const;
    HGDAL_EXPORT void            getEnvelope( OGREnvelope3D * psEnvelope ) const;

    HGDAL_EXPORT OGRErr          addCurveDirectly( OGRGeometry* poGeom, OGRCurve* poCurve,
                                      int bNeedRealloc );
    HGDAL_EXPORT size_t          WkbSize() const;
    HGDAL_EXPORT OGRErr          importPreambleFromWkb( OGRGeometry* poGeom,
                                            const unsigned char * pabyData,
                                            size_t& nSize,
                                            size_t& nDataOffset,
                                            OGRwkbByteOrder& eByteOrder,
                                            size_t nMinSubGeomSize,
                                            OGRwkbVariant eWkbVariant );
    HGDAL_EXPORT OGRErr      importBodyFromWkb(
                    OGRGeometry* poGeom,
                    const unsigned char * pabyData,
                    size_t nSize,
                    bool bAcceptCompoundCurve,
                    OGRErr (*pfnAddCurveDirectlyFromWkb)( OGRGeometry* poGeom,
                                                          OGRCurve* poCurve ),
                    OGRwkbVariant eWkbVariant,
                    size_t& nBytesConsumedOut );
    HGDAL_EXPORT std::string     exportToWkt(const OGRGeometry *geom, const OGRWktOptions& opts,
                                OGRErr *err) const;
    HGDAL_EXPORT OGRErr          exportToWkb( const OGRGeometry* poGeom, OGRwkbByteOrder,
                                 unsigned char *,
                                 OGRwkbVariant eWkbVariant ) const;
    HGDAL_EXPORT OGRBoolean      Equals(const OGRCurveCollection *poOCC) const;
    HGDAL_EXPORT void            setCoordinateDimension( OGRGeometry* poGeom,
                                            int nNewDimension );
    HGDAL_EXPORT void            set3D( OGRGeometry* poGeom, OGRBoolean bIs3D );
    HGDAL_EXPORT void            setMeasured( OGRGeometry* poGeom, OGRBoolean bIsMeasured );
    HGDAL_EXPORT void            assignSpatialReference( OGRGeometry* poGeom, OGRSpatialReference * poSR );
    HGDAL_EXPORT int             getNumCurves() const;
    HGDAL_EXPORT OGRCurve       *getCurve( int );
    HGDAL_EXPORT const OGRCurve *getCurve( int ) const;
    HGDAL_EXPORT OGRCurve       *stealCurve( int );

    HGDAL_EXPORT OGRErr          removeCurve( int iIndex, bool bDelete = true );

    HGDAL_EXPORT OGRErr          transform( OGRGeometry* poGeom,
                               OGRCoordinateTransformation *poCT );
    HGDAL_EXPORT void            flattenTo2D( OGRGeometry* poGeom );
    HGDAL_EXPORT void            segmentize( double dfMaxLength );
    HGDAL_EXPORT void            swapXY();
    HGDAL_EXPORT OGRBoolean      hasCurveGeometry(int bLookForNonLinear) const;
};
//! @endcond

/************************************************************************/
/*                            OGRCompoundCurve                          */
/************************************************************************/

/**
 * Concrete representation of a compound curve, made of curves: OGRLineString
 * and OGRCircularString. Each curve is connected by its first point to
 * the last point of the previous curve.
 *
 * Compatibility: ISO SQL/MM Part 3.
 *
 * @since GDAL 2.0
 */

class OGRCompoundCurve : public OGRCurve
{
  private:
    OGRCurveCollection oCC{};

    HGDAL_EXPORT OGRErr      addCurveDirectlyInternal( OGRCurve* poCurve,
                                          double dfToleranceEps,
                                          int bNeedRealloc );
    HGDAL_EXPORT static OGRErr addCurveDirectlyFromWkt( OGRGeometry* poSelf,
                                           OGRCurve* poCurve );
    HGDAL_EXPORT static OGRErr addCurveDirectlyFromWkb( OGRGeometry* poSelf,
                                           OGRCurve* poCurve );
    HGDAL_EXPORT OGRLineString* CurveToLineInternal( double dfMaxAngleStepSizeDegrees,
                                        const char* const* papszOptions,
                                        int bIsLinearRing ) const;
    // cppcheck-suppress unusedPrivateFunction
    HGDAL_EXPORT static OGRLineString* CasterToLineString( OGRCurve* poCurve );
    // cppcheck-suppress unusedPrivateFunction
    HGDAL_EXPORT static OGRLinearRing* CasterToLinearRing( OGRCurve* poCurve );

  protected:
//! @cond Doxygen_Suppress
    HGDAL_EXPORT static OGRLineString* CastToLineString( OGRCompoundCurve* poCC );
    HGDAL_EXPORT static OGRLinearRing* CastToLinearRing( OGRCompoundCurve* poCC );

    HGDAL_EXPORT virtual OGRCurveCasterToLineString GetCasterToLineString()
        const override;
    HGDAL_EXPORT virtual OGRCurveCasterToLinearRing GetCasterToLinearRing()
        const override;
//! @endcond

  public:
    HGDAL_EXPORT OGRCompoundCurve();
    HGDAL_EXPORT OGRCompoundCurve( const OGRCompoundCurve& other );
    HGDAL_EXPORT ~OGRCompoundCurve() override;

    HGDAL_EXPORT OGRCompoundCurve& operator=( const OGRCompoundCurve& other );

    /** Type of child elements. */
    typedef OGRCurve ChildType;

    /** Return begin of curve iterator.
     * @since GDAL 2.3
     */
    ChildType** begin() { return oCC.begin(); }
    /** Return end of curve iterator. */
    ChildType** end() { return oCC.end(); }
    /** Return begin of curve iterator.
     * @since GDAL 2.3
     */
    const ChildType* const * begin() const { return oCC.begin(); }
    /** Return end of curve iterator. */
    const ChildType* const * end() const { return oCC.end(); }

    // IWks Interface
    HGDAL_EXPORT virtual size_t WkbSize() const override;
    HGDAL_EXPORT virtual OGRErr importFromWkb( const unsigned char *,
                                  size_t,
                                  OGRwkbVariant,
                                  size_t& nBytesConsumedOut ) override;
    HGDAL_EXPORT virtual OGRErr exportToWkb( OGRwkbByteOrder, unsigned char *,
                                OGRwkbVariant=wkbVariantOldOgc )
        const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::importFromWkt; /** deprecated */
#endif

    HGDAL_EXPORT OGRErr importFromWkt( const char ** ) override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a compound curve to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return      WKT representation of the compound curve.
    HGDAL_EXPORT virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    // IGeometry interface.
    HGDAL_EXPORT virtual OGRCompoundCurve *clone() const override;
    HGDAL_EXPORT virtual void empty() override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope * psEnvelope ) const override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope3D * psEnvelope ) const override;
    HGDAL_EXPORT virtual OGRBoolean  IsEmpty() const override;

    // ICurve methods.
    HGDAL_EXPORT virtual double get_Length() const override;
    HGDAL_EXPORT virtual void StartPoint( OGRPoint * ) const override;
    HGDAL_EXPORT virtual void EndPoint( OGRPoint * ) const override;
    HGDAL_EXPORT virtual void Value( double, OGRPoint * ) const override;
    HGDAL_EXPORT virtual OGRLineString* CurveToLine( double dfMaxAngleStepSizeDegrees = 0,
                                        const char* const* papszOptions = nullptr )
        const override;

    HGDAL_EXPORT virtual int getNumPoints() const override;
    HGDAL_EXPORT virtual double get_AreaOfCurveSegments() const override;
    HGDAL_EXPORT virtual double get_Area() const override;

    // ISpatialRelation.
    HGDAL_EXPORT virtual OGRBoolean  Equals( const OGRGeometry * ) const override;

    // ICompoundCurve method.
    HGDAL_EXPORT int             getNumCurves() const;
    HGDAL_EXPORT OGRCurve       *getCurve( int );
    HGDAL_EXPORT const OGRCurve *getCurve( int ) const;

    // Non-standard.
    HGDAL_EXPORT virtual void setCoordinateDimension( int nDimension ) override;
    HGDAL_EXPORT virtual void set3D( OGRBoolean bIs3D ) override;
    HGDAL_EXPORT virtual void setMeasured( OGRBoolean bIsMeasured ) override;

    HGDAL_EXPORT virtual void    assignSpatialReference( OGRSpatialReference * poSR ) override;

    HGDAL_EXPORT OGRErr         addCurve( OGRCurve*, double dfToleranceEps = 1e-14  );
    HGDAL_EXPORT OGRErr         addCurveDirectly( OGRCurve*, double dfToleranceEps = 1e-14 );
    HGDAL_EXPORT OGRCurve      *stealCurve( int );
    HGDAL_EXPORT virtual OGRPointIterator* getPointIterator() const override;

    // Non-standard from OGRGeometry.
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRErr  transform( OGRCoordinateTransformation *poCT ) override;
    HGDAL_EXPORT virtual void flattenTo2D() override;
    HGDAL_EXPORT virtual void segmentize(double dfMaxLength) override;
    HGDAL_EXPORT virtual OGRBoolean hasCurveGeometry(int bLookForNonLinear = FALSE)
        const override;
    HGDAL_EXPORT virtual OGRGeometry* getLinearGeometry(
        double dfMaxAngleStepSizeDegrees = 0,
        const char* const* papszOptions = nullptr) const override;
    HGDAL_EXPORT virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    HGDAL_EXPORT virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    HGDAL_EXPORT virtual void        swapXY() override;

    OGR_ALLOW_UPCAST_TO(Curve)
    OGR_ALLOW_CAST_TO_THIS(CompoundCurve)
};

//! @cond Doxygen_Suppress
/** @see OGRCompoundCurve::begin() const */
inline const OGRCompoundCurve::ChildType* const * begin(const OGRCompoundCurve* poCurve) { return poCurve->begin(); }
/** @see OGRCompoundCurve::end() const */
inline const OGRCompoundCurve::ChildType* const * end(const OGRCompoundCurve* poCurve) { return poCurve->end(); }

/** @see OGRCompoundCurve::begin() */
inline OGRCompoundCurve::ChildType** begin(OGRCompoundCurve* poCurve) { return poCurve->begin(); }
/** @see OGRCompoundCurve::end() */
inline OGRCompoundCurve::ChildType** end(OGRCompoundCurve* poCurve) { return poCurve->end(); }
//! @endcond

/************************************************************************/
/*                              OGRSurface                              */
/************************************************************************/

/**
 * Abstract base class for 2 dimensional objects like polygons or curve
 * polygons.
 */

class OGRSurface : public OGRGeometry
{
  protected:
//! @cond Doxygen_Suppress
    HGDAL_EXPORT virtual OGRSurfaceCasterToPolygon      GetCasterToPolygon() const = 0;
    HGDAL_EXPORT virtual OGRSurfaceCasterToCurvePolygon GetCasterToCurvePolygon() const = 0;
//! @endcond

  public:
    HGDAL_EXPORT virtual double      get_Area() const = 0;
    HGDAL_EXPORT virtual OGRErr      PointOnSurface( OGRPoint * poPoint ) const
                                { return PointOnSurfaceInternal(poPoint); }
    virtual OGRSurface *clone() const override = 0;

//! @cond Doxygen_Suppress
    HGDAL_EXPORT static OGRPolygon*      CastToPolygon(OGRSurface* poSurface);
    HGDAL_EXPORT static OGRCurvePolygon* CastToCurvePolygon(OGRSurface* poSurface);
//! @endcond

    OGR_FORBID_DOWNCAST_TO_POINT
    OGR_FORBID_DOWNCAST_TO_ALL_CURVES
    OGR_ALLOW_CAST_TO_THIS(Surface)
    OGR_FORBID_DOWNCAST_TO_ALL_MULTI
};

/************************************************************************/
/*                          OGRCurvePolygon                             */
/************************************************************************/

/**
 * Concrete class representing curve polygons.
 *
 * Note that curve polygons consist of one outer (curve) ring, and zero or
 * more inner rings.  A curve polygon cannot represent disconnected
 * regions (such as multiple islands in a political body).  The
 * OGRMultiSurface must be used for this.
 *
 * Compatibility: ISO SQL/MM Part 3.
 *
 * @since GDAL 2.0
 */

class OGRCurvePolygon : public OGRSurface
{
    static OGRPolygon*      CasterToPolygon(OGRSurface* poSurface);

  private:
    HGDAL_EXPORT OGRBoolean      IntersectsPoint( const OGRPoint* p ) const;
    HGDAL_EXPORT OGRBoolean      ContainsPoint( const OGRPoint* p ) const;
    HGDAL_EXPORT virtual int   checkRing( OGRCurve * poNewRing ) const;
    HGDAL_EXPORT OGRErr        addRingDirectlyInternal( OGRCurve* poCurve,
                                           int bNeedRealloc );
    HGDAL_EXPORT static OGRErr addCurveDirectlyFromWkt( OGRGeometry* poSelf,
                                           OGRCurve* poCurve );
    HGDAL_EXPORT static OGRErr addCurveDirectlyFromWkb( OGRGeometry* poSelf,
                                           OGRCurve* poCurve );

  protected:
//! @cond Doxygen_Suppress
    friend class OGRPolygon;
    friend class OGRTriangle;
    OGRCurveCollection oCC{};

    HGDAL_EXPORT virtual OGRSurfaceCasterToPolygon      GetCasterToPolygon()
        const override;
    HGDAL_EXPORT virtual OGRSurfaceCasterToCurvePolygon GetCasterToCurvePolygon()
        const override;

//! @endcond

    HGDAL_EXPORT static OGRPolygon* CastToPolygon( OGRCurvePolygon* poCP );

  public:
    HGDAL_EXPORT OGRCurvePolygon();
    HGDAL_EXPORT OGRCurvePolygon( const OGRCurvePolygon& );
    HGDAL_EXPORT ~OGRCurvePolygon() override;

    HGDAL_EXPORT OGRCurvePolygon& operator=( const OGRCurvePolygon& other );

    /** Type of child elements. */
    typedef OGRCurve ChildType;

    /** Return begin of curve iterator.
     * @since GDAL 2.3
     */
    ChildType** begin() { return oCC.begin(); }
    /** Return end of curve iterator. */
    ChildType** end() { return oCC.end(); }
    /** Return begin of curve iterator.
     * @since GDAL 2.3
     */
    const ChildType* const * begin() const { return oCC.begin(); }
    /** Return end of curve iterator. */
    const ChildType* const * end() const { return oCC.end(); }

    // Non standard (OGRGeometry).
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual OGRCurvePolygon *clone() const override;
    HGDAL_EXPORT virtual void empty() override;
    HGDAL_EXPORT virtual OGRErr  transform( OGRCoordinateTransformation *poCT ) override;
    HGDAL_EXPORT virtual void flattenTo2D() override;
    HGDAL_EXPORT virtual OGRBoolean  IsEmpty() const override;
    HGDAL_EXPORT virtual void segmentize( double dfMaxLength ) override;
    HGDAL_EXPORT virtual OGRBoolean hasCurveGeometry( int bLookForNonLinear = FALSE )
        const override;
    HGDAL_EXPORT virtual OGRGeometry* getLinearGeometry(
        double dfMaxAngleStepSizeDegrees = 0,
        const char* const* papszOptions = nullptr ) const override;

    // ISurface Interface
    HGDAL_EXPORT virtual double      get_Area() const override;

    // IWks Interface
    HGDAL_EXPORT virtual size_t WkbSize() const override;
    HGDAL_EXPORT virtual OGRErr importFromWkb( const unsigned char *,
                                  size_t,
                                  OGRwkbVariant,
                                  size_t& nBytesConsumedOut ) override;
    HGDAL_EXPORT virtual OGRErr exportToWkb( OGRwkbByteOrder, unsigned char *,
                                OGRwkbVariant=wkbVariantOldOgc )
        const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::importFromWkt; /** deprecated */
#endif

    OGRErr importFromWkt( const char ** ) override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a curve polygon to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return      WKT representation of the curve polygon.
    HGDAL_EXPORT virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    // IGeometry
    HGDAL_EXPORT virtual int getDimension() const override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope * psEnvelope ) const override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope3D * psEnvelope ) const override;

    // ICurvePolygon
    HGDAL_EXPORT virtual OGRPolygon* CurvePolyToPoly(
        double dfMaxAngleStepSizeDegrees = 0,
        const char* const* papszOptions = nullptr ) const;

    // ISpatialRelation
    HGDAL_EXPORT virtual OGRBoolean  Equals( const OGRGeometry * ) const override;
    HGDAL_EXPORT virtual OGRBoolean  Intersects( const OGRGeometry * ) const override;
    HGDAL_EXPORT virtual OGRBoolean  Contains( const OGRGeometry * ) const override;

    // Non standard
    HGDAL_EXPORT virtual void setCoordinateDimension( int nDimension ) override;
    HGDAL_EXPORT virtual void set3D( OGRBoolean bIs3D ) override;
    HGDAL_EXPORT virtual void setMeasured( OGRBoolean bIsMeasured ) override;

    HGDAL_EXPORT virtual void    assignSpatialReference( OGRSpatialReference * poSR ) override;

    HGDAL_EXPORT virtual OGRErr addRing( OGRCurve * );
    HGDAL_EXPORT virtual OGRErr addRingDirectly( OGRCurve * );

    HGDAL_EXPORT OGRCurve *getExteriorRingCurve();
    HGDAL_EXPORT const OGRCurve *getExteriorRingCurve() const;
    HGDAL_EXPORT int         getNumInteriorRings() const;
    HGDAL_EXPORT OGRCurve *getInteriorRingCurve( int );
    HGDAL_EXPORT const OGRCurve *getInteriorRingCurve( int ) const;

    HGDAL_EXPORT OGRCurve *stealExteriorRingCurve();

    HGDAL_EXPORT OGRErr removeRing( int iIndex, bool bDelete = true );
    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    HGDAL_EXPORT virtual void        swapXY() override;

    OGR_ALLOW_UPCAST_TO(Surface)
    OGR_ALLOW_CAST_TO_THIS(CurvePolygon)
};

//! @cond Doxygen_Suppress
/** @see OGRCurvePolygon::begin() const */
inline const OGRCurvePolygon::ChildType* const * begin(const OGRCurvePolygon* poGeom) { return poGeom->begin(); }
/** @see OGRCurvePolygon::end() const */
inline const OGRCurvePolygon::ChildType* const * end(const OGRCurvePolygon* poGeom) { return poGeom->end(); }

/** @see OGRCurvePolygon::begin() */
inline OGRCurvePolygon::ChildType** begin(OGRCurvePolygon* poGeom) { return poGeom->begin(); }
/** @see OGRCurvePolygon::end() */
inline OGRCurvePolygon::ChildType** end(OGRCurvePolygon* poGeom) { return poGeom->end(); }
//! @endcond

/************************************************************************/
/*                              OGRPolygon                              */
/************************************************************************/

/**
 * Concrete class representing polygons.
 *
 * Note that the OpenGIS simple features polygons consist of one outer ring
 * (linearring), and zero or more inner rings.  A polygon cannot represent
 * disconnected regions (such as multiple islands in a political body).  The
 * OGRMultiPolygon must be used for this.
 */

class OGRPolygon : public OGRCurvePolygon
{
    static OGRCurvePolygon*     CasterToCurvePolygon(OGRSurface* poSurface);

  protected:
//! @cond Doxygen_Suppress
    friend class OGRMultiSurface;
    friend class OGRPolyhedralSurface;
    friend class OGRTriangulatedSurface;

    HGDAL_EXPORT virtual int checkRing( OGRCurve * poNewRing ) const override;
    HGDAL_EXPORT virtual OGRErr importFromWKTListOnly( const char ** ppszInput,
                                          int bHasZ, int bHasM,
                                          OGRRawPoint*& paoPoints,
                                          int& nMaxPoints,
                                          double*& padfZ );

    HGDAL_EXPORT static OGRCurvePolygon* CastToCurvePolygon(OGRPolygon* poPoly);

    HGDAL_EXPORT virtual OGRSurfaceCasterToPolygon      GetCasterToPolygon()
        const override;
    HGDAL_EXPORT virtual OGRSurfaceCasterToCurvePolygon GetCasterToCurvePolygon()
        const override;
//! @endcond

  public:
    HGDAL_EXPORT OGRPolygon();
    HGDAL_EXPORT OGRPolygon(const OGRPolygon& other);
    HGDAL_EXPORT ~OGRPolygon() override;

    HGDAL_EXPORT OGRPolygon& operator=(const OGRPolygon& other);

    /** Type of child elements. */
    typedef OGRLinearRing ChildType;

    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    ChildType** begin() { return reinterpret_cast<ChildType**>(oCC.begin()); }
    /** Return end of iterator */
    ChildType** end() { return reinterpret_cast<ChildType**>(oCC.end()); }
    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    const ChildType* const* begin() const { return reinterpret_cast<const ChildType* const*>(oCC.begin()); }
    /** Return end of iterator */
    const ChildType* const* end() const { return reinterpret_cast<const ChildType* const*>(oCC.end()); }

    // Non-standard (OGRGeometry).
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual OGRPolygon *clone() const override;
    HGDAL_EXPORT virtual OGRBoolean hasCurveGeometry( int bLookForNonLinear = FALSE )
        const override;
    HGDAL_EXPORT virtual OGRGeometry* getCurveGeometry( const char* const* papszOptions = nullptr ) const override;
    HGDAL_EXPORT virtual OGRGeometry* getLinearGeometry(
        double dfMaxAngleStepSizeDegrees = 0,
        const char* const* papszOptions = nullptr) const override;

    // IWks Interface.
    HGDAL_EXPORT virtual size_t WkbSize() const override;
    HGDAL_EXPORT virtual OGRErr importFromWkb( const unsigned char *,
                                  size_t,
                                  OGRwkbVariant,
                                  size_t& nBytesConsumedOut ) override;
    HGDAL_EXPORT virtual OGRErr exportToWkb( OGRwkbByteOrder, unsigned char *,
                                OGRwkbVariant=wkbVariantOldOgc )
        const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::importFromWkt; /** deprecated */
#endif

    HGDAL_EXPORT OGRErr importFromWkt( const char ** ) override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a polygon to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return      WKT representation of the polygon.
    HGDAL_EXPORT virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    // ICurvePolygon.
    HGDAL_EXPORT virtual OGRPolygon* CurvePolyToPoly(
        double dfMaxAngleStepSizeDegrees = 0,
        const char* const* papszOptions = nullptr ) const override;

    HGDAL_EXPORT OGRLinearRing *getExteriorRing();
    HGDAL_EXPORT const OGRLinearRing *getExteriorRing() const;
    HGDAL_EXPORT virtual OGRLinearRing *getInteriorRing( int );
    HGDAL_EXPORT virtual const OGRLinearRing *getInteriorRing( int ) const;

    HGDAL_EXPORT OGRLinearRing *stealExteriorRing();
    HGDAL_EXPORT virtual OGRLinearRing *stealInteriorRing(int);

    HGDAL_EXPORT OGRBoolean IsPointOnSurface( const OGRPoint * ) const;

    /** Return pointer of this in upper class */
    inline OGRCurvePolygon* toUpperClass() { return this; }
    /** Return pointer of this in upper class */
    inline const OGRCurvePolygon* toUpperClass() const { return this; }

    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    HGDAL_EXPORT virtual void closeRings() override;

    OGR_ALLOW_UPCAST_TO(CurvePolygon)
    OGR_ALLOW_CAST_TO_THIS(Polygon)
};

//! @cond Doxygen_Suppress
/** @see OGRPolygon::begin() const */
inline const OGRPolygon::ChildType* const * begin(const OGRPolygon* poGeom) { return poGeom->begin(); }
/** @see OGRPolygon::end() const */
inline const OGRPolygon::ChildType* const * end(const OGRPolygon* poGeom) { return poGeom->end(); }

/** @see OGRPolygon::begin() */
inline OGRPolygon::ChildType** begin(OGRPolygon* poGeom) { return poGeom->begin(); }
/** @see OGRPolygon::end() */
inline OGRPolygon::ChildType** end(OGRPolygon* poGeom) { return poGeom->end(); }
//! @endcond

/************************************************************************/
/*                              OGRTriangle                             */
/************************************************************************/

/**
 * Triangle class.
 *
 * @since GDAL 2.2
 */

class OGRTriangle : public OGRPolygon
{
  private:
    // cppcheck-suppress unusedPrivateFunction
    HGDAL_EXPORT static OGRPolygon*          CasterToPolygon(OGRSurface* poSurface);
    HGDAL_EXPORT bool quickValidityCheck() const;

  protected:
//! @cond Doxygen_Suppress
    HGDAL_EXPORT virtual OGRSurfaceCasterToPolygon   GetCasterToPolygon() const override;
    HGDAL_EXPORT virtual OGRErr importFromWKTListOnly( const char ** ppszInput,
                                          int bHasZ, int bHasM,
                                          OGRRawPoint*& paoPoints,
                                          int& nMaxPoints,
                                          double*& padfZ ) override;
//! @endcond

  public:
    HGDAL_EXPORT OGRTriangle();
    HGDAL_EXPORT OGRTriangle( const OGRPoint &p, const OGRPoint &q, const OGRPoint &r );
    HGDAL_EXPORT OGRTriangle( const OGRTriangle &other );
    HGDAL_EXPORT OGRTriangle( const OGRPolygon &other, OGRErr &eErr );
    HGDAL_EXPORT OGRTriangle& operator=( const OGRTriangle& other );
    HGDAL_EXPORT ~OGRTriangle() override;
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual OGRTriangle *clone() const override;

    // IWks Interface.
    HGDAL_EXPORT virtual OGRErr importFromWkb( const unsigned char *,
                                  size_t,
                                  OGRwkbVariant,
                                  size_t& nBytesConsumedOut ) override;

    // New methods rewritten from OGRPolygon/OGRCurvePolygon/OGRGeometry.
    HGDAL_EXPORT virtual OGRErr addRingDirectly( OGRCurve * poNewRing ) override;

    /** Return pointer of this in upper class */
    inline OGRPolygon* toUpperClass() { return this; }
    /** Return pointer of this in upper class */
    inline const OGRPolygon* toUpperClass() const { return this; }

    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

//! @cond Doxygen_Suppress
    HGDAL_EXPORT static OGRGeometry* CastToPolygon( OGRGeometry* poGeom );
//! @endcond

    OGR_ALLOW_UPCAST_TO(Polygon)
    OGR_ALLOW_CAST_TO_THIS(Triangle)
};

/************************************************************************/
/*                        OGRGeometryCollection                         */
/************************************************************************/

/**
 * A collection of 1 or more geometry objects.
 *
 * All geometries must share a common spatial reference system, and
 * Subclasses may impose additional restrictions on the contents.
 */

class OGRGeometryCollection : public OGRGeometry
{
    HGDAL_EXPORT OGRErr      importFromWkbInternal( const unsigned char * pabyData,
                                       size_t nSize,
                                       int nRecLevel,
                                       OGRwkbVariant, size_t& nBytesConsumedOut );
    HGDAL_EXPORT OGRErr      importFromWktInternal( const char **ppszInput, int nRecLevel );

  protected:
//! @cond Doxygen_Suppress
    int         nGeomCount = 0;
    OGRGeometry **papoGeoms = nullptr;

    HGDAL_EXPORT std::string exportToWktInternal(const OGRWktOptions& opts, OGRErr *err, std::string exclude = std::string()) const;
    HGDAL_EXPORT static OGRGeometryCollection* TransferMembersAndDestroy( OGRGeometryCollection* poSrc, OGRGeometryCollection* poDst );
//! @endcond
    HGDAL_EXPORT virtual OGRBoolean         isCompatibleSubType( OGRwkbGeometryType ) const;

  public:
    HGDAL_EXPORT OGRGeometryCollection();
    HGDAL_EXPORT OGRGeometryCollection( const OGRGeometryCollection& other );
    HGDAL_EXPORT ~OGRGeometryCollection() override;

    HGDAL_EXPORT OGRGeometryCollection& operator=( const OGRGeometryCollection& other );

    /** Type of child elements. */
    typedef OGRGeometry ChildType;

    /** Return begin of sub-geometry iterator.
     * @since GDAL 2.3
     */
    ChildType** begin() { return papoGeoms; }
    /** Return end of sub-geometry iterator. */
    ChildType** end() { return papoGeoms + nGeomCount; }
    /** Return begin of sub-geometry iterator.
     * @since GDAL 2.3
     */
    const ChildType* const* begin() const { return papoGeoms; }
    /** Return end of sub-geometry iterator. */
    const ChildType* const* end() const { return papoGeoms + nGeomCount; }

    // Non standard (OGRGeometry).
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual OGRGeometryCollection *clone() const override;
    HGDAL_EXPORT virtual void empty() override;
    HGDAL_EXPORT virtual OGRErr  transform( OGRCoordinateTransformation *poCT ) override;
    HGDAL_EXPORT virtual void flattenTo2D() override;
    HGDAL_EXPORT virtual OGRBoolean  IsEmpty() const override;
    HGDAL_EXPORT virtual void segmentize(double dfMaxLength) override;
    HGDAL_EXPORT virtual OGRBoolean hasCurveGeometry( int bLookForNonLinear = FALSE )
        const override;
    HGDAL_EXPORT virtual OGRGeometry* getCurveGeometry(
        const char* const* papszOptions = nullptr ) const override;
    HGDAL_EXPORT virtual OGRGeometry* getLinearGeometry(
        double dfMaxAngleStepSizeDegrees = 0,
        const char* const* papszOptions = nullptr ) const override;

    // IWks Interface
    HGDAL_EXPORT virtual size_t WkbSize() const override;
    HGDAL_EXPORT virtual OGRErr importFromWkb( const unsigned char *,
                                  size_t,
                                  OGRwkbVariant,
                                  size_t& nBytesConsumedOut ) override;
    HGDAL_EXPORT virtual OGRErr exportToWkb( OGRwkbByteOrder, unsigned char *,
                                OGRwkbVariant=wkbVariantOldOgc )
        const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::importFromWkt; /** deprecated */
#endif

    HGDAL_EXPORT OGRErr importFromWkt( const char ** ) override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a geometry collection to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return      WKT representation of the geometry collection.
    HGDAL_EXPORT virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    HGDAL_EXPORT virtual double get_Length() const;
    HGDAL_EXPORT virtual double get_Area() const;

    // IGeometry methods
    HGDAL_EXPORT virtual int getDimension() const override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope * psEnvelope ) const override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope3D * psEnvelope ) const override;

    // IGeometryCollection
    HGDAL_EXPORT int         getNumGeometries() const;
    HGDAL_EXPORT OGRGeometry *getGeometryRef( int );
    HGDAL_EXPORT const OGRGeometry *getGeometryRef( int ) const;

    // ISpatialRelation
    HGDAL_EXPORT virtual OGRBoolean  Equals( const OGRGeometry * ) const override;

    // Non standard
    HGDAL_EXPORT virtual void setCoordinateDimension( int nDimension ) override;
    HGDAL_EXPORT virtual void set3D( OGRBoolean bIs3D ) override;
    HGDAL_EXPORT virtual void setMeasured( OGRBoolean bIsMeasured ) override;
    HGDAL_EXPORT virtual OGRErr addGeometry( const OGRGeometry * );
    HGDAL_EXPORT virtual OGRErr addGeometryDirectly( OGRGeometry * );
    HGDAL_EXPORT virtual OGRErr removeGeometry( int iIndex, int bDelete = TRUE );

    HGDAL_EXPORT virtual void    assignSpatialReference( OGRSpatialReference * poSR ) override;

    HGDAL_EXPORT void closeRings() override;

    HGDAL_EXPORT virtual void swapXY() override;

    HGDAL_EXPORT virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    HGDAL_EXPORT virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    HGDAL_EXPORT static OGRGeometryCollection* CastToGeometryCollection( OGRGeometryCollection* poSrc );

    OGR_FORBID_DOWNCAST_TO_POINT
    OGR_FORBID_DOWNCAST_TO_ALL_CURVES
    OGR_FORBID_DOWNCAST_TO_ALL_SURFACES
    OGR_ALLOW_CAST_TO_THIS(GeometryCollection)
};

//! @cond Doxygen_Suppress
/** @see OGRGeometryCollection::begin() const */
inline const OGRGeometryCollection::ChildType* const * begin(const OGRGeometryCollection* poGeom) { return poGeom->begin(); }
/** @see OGRGeometryCollection::end() const */
inline const OGRGeometryCollection::ChildType* const * end(const OGRGeometryCollection* poGeom) { return poGeom->end(); }

/** @see OGRGeometryCollection::begin() */
inline OGRGeometryCollection::ChildType** begin(OGRGeometryCollection* poGeom) { return poGeom->begin(); }
/** @see OGRGeometryCollection::end() */
inline OGRGeometryCollection::ChildType** end(OGRGeometryCollection* poGeom) { return poGeom->end(); }
//! @endcond

/************************************************************************/
/*                          OGRMultiSurface                             */
/************************************************************************/

/**
 * A collection of non-overlapping OGRSurface.
 *
 * @since GDAL 2.0
 */

class OGRMultiSurface : public OGRGeometryCollection
{
  protected:
    HGDAL_EXPORT virtual OGRBoolean isCompatibleSubType( OGRwkbGeometryType ) const override;

  public:
    HGDAL_EXPORT OGRMultiSurface();
    HGDAL_EXPORT OGRMultiSurface( const OGRMultiSurface& other );
    HGDAL_EXPORT ~OGRMultiSurface() override;

    HGDAL_EXPORT OGRMultiSurface& operator=( const OGRMultiSurface& other );

    /** Type of child elements. */
    typedef OGRSurface ChildType;

    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    ChildType** begin() { return reinterpret_cast<ChildType**>(papoGeoms); }
    /** Return end of iterator */
    ChildType** end() { return reinterpret_cast<ChildType**>(papoGeoms + nGeomCount); }
    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    const ChildType* const* begin() const { return reinterpret_cast<const ChildType* const*>(papoGeoms); }
    /** Return end of iterator */
    const ChildType* const* end() const { return reinterpret_cast<const ChildType* const*>(papoGeoms + nGeomCount); }

    // Non standard (OGRGeometry).
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual OGRMultiSurface *clone() const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::importFromWkt; /** deprecated */
#endif

    HGDAL_EXPORT OGRErr importFromWkt( const char ** ) override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a geometry collection to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return      WKT representation of the geometry collection.
    HGDAL_EXPORT virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    // IMultiSurface methods
    HGDAL_EXPORT virtual OGRErr PointOnSurface( OGRPoint * poPoint ) const;

    // IGeometry methods
    HGDAL_EXPORT virtual int getDimension() const override;

    // IGeometryCollection
    /** See OGRGeometryCollection::getGeometryRef() */
    OGRSurface *getGeometryRef( int i) { return OGRGeometryCollection::getGeometryRef(i)->toSurface(); }
    /** See OGRGeometryCollection::getGeometryRef() */
    const OGRSurface *getGeometryRef( int i ) const { return OGRGeometryCollection::getGeometryRef(i)->toSurface(); }

    // Non standard
    HGDAL_EXPORT virtual OGRBoolean hasCurveGeometry( int bLookForNonLinear = FALSE )
        const override;

    /** Return pointer of this in upper class */
    inline OGRGeometryCollection* toUpperClass() { return this; }
    /** Return pointer of this in upper class */
    inline const OGRGeometryCollection* toUpperClass() const { return this; }

    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    HGDAL_EXPORT static OGRMultiPolygon* CastToMultiPolygon( OGRMultiSurface* poMS );

    OGR_ALLOW_CAST_TO_THIS(MultiSurface)
    OGR_ALLOW_UPCAST_TO(GeometryCollection)
    OGR_FORBID_DOWNCAST_TO_MULTIPOINT
    OGR_FORBID_DOWNCAST_TO_MULTILINESTRING
    OGR_FORBID_DOWNCAST_TO_MULTICURVE
};

//! @cond Doxygen_Suppress
/** @see OGRMultiSurface::begin() const */
inline const OGRMultiSurface::ChildType* const * begin(const OGRMultiSurface* poGeom) { return poGeom->begin(); }
/** @see OGRMultiSurface::end() const */
inline const OGRMultiSurface::ChildType* const * end(const OGRMultiSurface* poGeom) { return poGeom->end(); }

/** @see OGRMultiSurface::begin() */
inline OGRMultiSurface::ChildType** begin(OGRMultiSurface* poGeom) { return poGeom->begin(); }
/** @see OGRMultiSurface::end() */
inline OGRMultiSurface::ChildType** end(OGRMultiSurface* poGeom) { return poGeom->end(); }
//! @endcond

/************************************************************************/
/*                           OGRMultiPolygon                            */
/************************************************************************/

/**
 * A collection of non-overlapping OGRPolygon.
 */

class OGRMultiPolygon : public OGRMultiSurface
{
  protected:
    HGDAL_EXPORT virtual OGRBoolean isCompatibleSubType( OGRwkbGeometryType )
        const override;
    friend class OGRPolyhedralSurface;
    friend class OGRTriangulatedSurface;

  private:
//! @cond Doxygen_Suppress
    HGDAL_EXPORT         OGRErr _addGeometryWithExpectedSubGeometryType(
                const OGRGeometry * poNewGeom,
                OGRwkbGeometryType eSubGeometryType );
    HGDAL_EXPORT         OGRErr _addGeometryDirectlyWithExpectedSubGeometryType(
                OGRGeometry * poNewGeom,
                OGRwkbGeometryType eSubGeometryType );
//! @endcond


  public:
    HGDAL_EXPORT OGRMultiPolygon();
    HGDAL_EXPORT OGRMultiPolygon( const OGRMultiPolygon& other );
    HGDAL_EXPORT ~OGRMultiPolygon() override;

    HGDAL_EXPORT OGRMultiPolygon& operator=(const OGRMultiPolygon& other);

    /** Type of child elements. */
    typedef OGRPolygon ChildType;

    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    ChildType** begin() { return reinterpret_cast<ChildType**>(papoGeoms); }
    /** Return end of iterator */
    ChildType** end() { return reinterpret_cast<ChildType**>(papoGeoms + nGeomCount); }
    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    const ChildType* const* begin() const { return reinterpret_cast<const ChildType* const*>(papoGeoms); }
    /** Return end of iterator */
    const ChildType* const* end() const { return reinterpret_cast<const ChildType* const*>(papoGeoms + nGeomCount); }

    // IGeometryCollection
    /** See OGRGeometryCollection::getGeometryRef() */
    OGRPolygon *getGeometryRef( int i) { return OGRGeometryCollection::getGeometryRef(i)->toPolygon(); }
    /** See OGRGeometryCollection::getGeometryRef() */
    const OGRPolygon *getGeometryRef( int i ) const { return OGRGeometryCollection::getGeometryRef(i)->toPolygon(); }

    // Non-standard (OGRGeometry).
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual OGRMultiPolygon *clone() const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a multipolygon to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return      WKT representation of the multipolygon.
    virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    // Non standard
    HGDAL_EXPORT virtual OGRBoolean hasCurveGeometry( int bLookForNonLinear = FALSE )
        const override;

        /** Return pointer of this in upper class */
    inline OGRGeometryCollection* toUpperClass() { return this; }
    /** Return pointer of this in upper class */
    inline const OGRGeometryCollection* toUpperClass() const { return this; }

    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    HGDAL_EXPORT static OGRMultiSurface* CastToMultiSurface( OGRMultiPolygon* poMP );

    OGR_ALLOW_CAST_TO_THIS(MultiPolygon)
    OGR_ALLOW_UPCAST_TO(MultiSurface)
};

//! @cond Doxygen_Suppress
/** @see OGRMultiPolygon::begin() const */
inline const OGRMultiPolygon::ChildType* const * begin(const OGRMultiPolygon* poGeom) { return poGeom->begin(); }
/** @see OGRMultiPolygon::end() const */
inline const OGRMultiPolygon::ChildType* const * end(const OGRMultiPolygon* poGeom) { return poGeom->end(); }

/** @see OGRMultiPolygon::begin() */
inline OGRMultiPolygon::ChildType** begin(OGRMultiPolygon* poGeom) { return poGeom->begin(); }
/** @see OGRMultiPolygon::end() */
inline OGRMultiPolygon::ChildType** end(OGRMultiPolygon* poGeom) { return poGeom->end(); }
//! @endcond

/************************************************************************/
/*                         OGRPolyhedralSurface                         */
/************************************************************************/

/**
 * PolyhedralSurface class.
 *
 * @since GDAL 2.2
 */

class OGRPolyhedralSurface : public OGRSurface
{
  protected:
//! @cond Doxygen_Suppress
    friend class OGRTriangulatedSurface;
    OGRMultiPolygon oMP{};
    HGDAL_EXPORT virtual OGRSurfaceCasterToPolygon      GetCasterToPolygon()
        const override;
    HGDAL_EXPORT virtual OGRSurfaceCasterToCurvePolygon GetCasterToCurvePolygon()
      const override;
    HGDAL_EXPORT virtual OGRBoolean         isCompatibleSubType( OGRwkbGeometryType ) const;
    HGDAL_EXPORT virtual const char*        getSubGeometryName() const;
    HGDAL_EXPORT virtual OGRwkbGeometryType getSubGeometryType() const;
    HGDAL_EXPORT std::string exportToWktInternal (const OGRWktOptions& opts, OGRErr *err) const;

    HGDAL_EXPORT virtual OGRPolyhedralSurfaceCastToMultiPolygon GetCasterToMultiPolygon()
        const;
    HGDAL_EXPORT static OGRMultiPolygon* CastToMultiPolygonImpl(OGRPolyhedralSurface* poPS);
//! @endcond

  public:
    HGDAL_EXPORT OGRPolyhedralSurface();
    HGDAL_EXPORT OGRPolyhedralSurface( const OGRPolyhedralSurface &poGeom );
    HGDAL_EXPORT ~OGRPolyhedralSurface() override;
    HGDAL_EXPORT OGRPolyhedralSurface& operator=(const OGRPolyhedralSurface& other);

    /** Type of child elements. */
    typedef OGRPolygon ChildType;

    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    ChildType** begin() { return oMP.begin(); }
    /** Return end of iterator */
    ChildType** end() { return oMP.end(); }
    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    const ChildType* const* begin() const { return oMP.begin(); }
    /** Return end of iterator */
    const ChildType* const* end() const { return oMP.end(); }

    // IWks Interface.
    HGDAL_EXPORT virtual size_t WkbSize() const override;
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const  override;
    HGDAL_EXPORT virtual OGRErr importFromWkb( const unsigned char *,
                                  size_t,
                                  OGRwkbVariant,
                                  size_t& nBytesConsumedOut ) override;
    HGDAL_EXPORT virtual OGRErr exportToWkb( OGRwkbByteOrder, unsigned char *,
                                OGRwkbVariant=wkbVariantOldOgc )
        const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::importFromWkt; /** deprecated */
#endif

    HGDAL_EXPORT OGRErr importFromWkt( const char ** ) override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a polyhedral surface to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return      WKT representation of the polyhedral surface.
    HGDAL_EXPORT virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    // IGeometry methods.
    HGDAL_EXPORT virtual int getDimension() const override;

    HGDAL_EXPORT virtual void empty() override;

    HGDAL_EXPORT virtual OGRPolyhedralSurface *clone() const override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope * psEnvelope ) const override;
    HGDAL_EXPORT virtual void getEnvelope( OGREnvelope3D * psEnvelope ) const override;

    HGDAL_EXPORT virtual void flattenTo2D() override;
    HGDAL_EXPORT virtual OGRErr transform( OGRCoordinateTransformation* ) override;
    HGDAL_EXPORT virtual OGRBoolean Equals( const OGRGeometry* ) const override;
    HGDAL_EXPORT virtual double get_Area() const override;
    HGDAL_EXPORT virtual OGRErr PointOnSurface( OGRPoint* ) const override;

    HGDAL_EXPORT static OGRMultiPolygon* CastToMultiPolygon( OGRPolyhedralSurface* poPS );
    HGDAL_EXPORT virtual OGRBoolean hasCurveGeometry( int bLookForNonLinear = FALSE )
        const override;
    HGDAL_EXPORT virtual OGRErr addGeometry( const OGRGeometry * );
    HGDAL_EXPORT OGRErr addGeometryDirectly( OGRGeometry *poNewGeom );
    HGDAL_EXPORT int getNumGeometries() const;
    HGDAL_EXPORT OGRPolygon* getGeometryRef(int i);
    HGDAL_EXPORT const OGRPolygon* getGeometryRef(int i) const;

    HGDAL_EXPORT virtual OGRBoolean  IsEmpty() const override;
    HGDAL_EXPORT virtual void setCoordinateDimension( int nDimension ) override;
    HGDAL_EXPORT virtual void set3D( OGRBoolean bIs3D ) override;
    HGDAL_EXPORT virtual void setMeasured( OGRBoolean bIsMeasured ) override;
    HGDAL_EXPORT virtual void swapXY() override;
    HGDAL_EXPORT OGRErr removeGeometry( int iIndex, int bDelete = TRUE );

    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    HGDAL_EXPORT virtual void    assignSpatialReference( OGRSpatialReference * poSR ) override;

    OGR_ALLOW_CAST_TO_THIS(PolyhedralSurface)
    OGR_ALLOW_UPCAST_TO(Surface)
};

//! @cond Doxygen_Suppress
/** @see OGRPolyhedralSurface::begin() const */
inline const OGRPolyhedralSurface::ChildType* const * begin(const OGRPolyhedralSurface* poGeom) { return poGeom->begin(); }
/** @see OGRPolyhedralSurface::end() const */
inline const OGRPolyhedralSurface::ChildType* const * end(const OGRPolyhedralSurface* poGeom) { return poGeom->end(); }

/** @see OGRPolyhedralSurface::begin() */
inline OGRPolyhedralSurface::ChildType** begin(OGRPolyhedralSurface* poGeom) { return poGeom->begin(); }
/** @see OGRPolyhedralSurface::end() */
inline OGRPolyhedralSurface::ChildType** end(OGRPolyhedralSurface* poGeom) { return poGeom->end(); }
//! @endcond

/************************************************************************/
/*                        OGRTriangulatedSurface                        */
/************************************************************************/

/**
 * TriangulatedSurface class.
 *
 * @since GDAL 2.2
 */

class OGRTriangulatedSurface : public OGRPolyhedralSurface
{
  protected:
//! @cond Doxygen_Suppress
    HGDAL_EXPORT virtual OGRBoolean         isCompatibleSubType( OGRwkbGeometryType )
        const override;
    HGDAL_EXPORT virtual const char*        getSubGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getSubGeometryType() const override;

    HGDAL_EXPORT virtual OGRPolyhedralSurfaceCastToMultiPolygon GetCasterToMultiPolygon()
        const override;
    HGDAL_EXPORT static OGRMultiPolygon *
        CastToMultiPolygonImpl( OGRPolyhedralSurface* poPS );
//! @endcond

  public:
    HGDAL_EXPORT OGRTriangulatedSurface();
    HGDAL_EXPORT OGRTriangulatedSurface( const OGRTriangulatedSurface &other );
    HGDAL_EXPORT ~OGRTriangulatedSurface();

    /** Type of child elements. */
    typedef OGRTriangle ChildType;

    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    ChildType** begin() { return reinterpret_cast<ChildType**>(oMP.begin()); }
    /** Return end of iterator */
    ChildType** end() { return reinterpret_cast<ChildType**>(oMP.end()); }
    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    const ChildType* const* begin() const { return reinterpret_cast<const ChildType* const*>(oMP.begin()); }
    /** Return end of iterator */
    const ChildType* const* end() const { return reinterpret_cast<const ChildType* const*>(oMP.end()); }

    HGDAL_EXPORT OGRTriangulatedSurface& operator=( const OGRTriangulatedSurface& other );
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual OGRTriangulatedSurface *clone() const override;

    /** See OGRPolyhedralSurface::getGeometryRef() */
    OGRTriangle* getGeometryRef(int i) { return OGRPolyhedralSurface::getGeometryRef(i)->toTriangle(); }
    /** See OGRPolyhedralSurface::getGeometryRef() */
    const OGRTriangle* getGeometryRef(int i) const { return OGRPolyhedralSurface::getGeometryRef(i)->toTriangle(); }

    // IWks Interface.
    HGDAL_EXPORT virtual OGRErr addGeometry( const OGRGeometry * ) override;

    /** Return pointer of this in upper class */
    inline OGRPolyhedralSurface* toUpperClass() { return this; }
    /** Return pointer of this in upper class */
    inline const OGRPolyhedralSurface* toUpperClass() const { return this; }

    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    HGDAL_EXPORT static OGRPolyhedralSurface *
        CastToPolyhedralSurface( OGRTriangulatedSurface* poTS );

    OGR_ALLOW_CAST_TO_THIS(TriangulatedSurface)
    OGR_ALLOW_UPCAST_TO(PolyhedralSurface)
};

//! @cond Doxygen_Suppress
/** @see OGRTriangulatedSurface::begin() const */
inline const OGRTriangulatedSurface::ChildType* const * begin(const OGRTriangulatedSurface* poGeom) { return poGeom->begin(); }
/** @see OGRTriangulatedSurface::end() const */
inline const OGRTriangulatedSurface::ChildType* const * end(const OGRTriangulatedSurface* poGeom) { return poGeom->end(); }

/** @see OGRTriangulatedSurface::begin() */
inline OGRTriangulatedSurface::ChildType** begin(OGRTriangulatedSurface* poGeom) { return poGeom->begin(); }
/** @see OGRTriangulatedSurface::end() */
inline OGRTriangulatedSurface::ChildType** end(OGRTriangulatedSurface* poGeom) { return poGeom->end(); }
//! @endcond

/************************************************************************/
/*                            OGRMultiPoint                             */
/************************************************************************/

/**
 * A collection of OGRPoint.
 */

class OGRMultiPoint : public OGRGeometryCollection
{
  private:
    HGDAL_EXPORT OGRErr  importFromWkt_Bracketed( const char **, int bHasM, int bHasZ );

  protected:
    HGDAL_EXPORT virtual OGRBoolean  isCompatibleSubType( OGRwkbGeometryType )
        const override;

  public:
    HGDAL_EXPORT OGRMultiPoint();
    HGDAL_EXPORT OGRMultiPoint(const OGRMultiPoint& other);
    HGDAL_EXPORT ~OGRMultiPoint() override;

    HGDAL_EXPORT OGRMultiPoint& operator=(const OGRMultiPoint& other);

    /** Type of child elements. */
    typedef OGRPoint ChildType;

    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    ChildType** begin() { return reinterpret_cast<ChildType**>(papoGeoms); }
    /** Return end of iterator */
    ChildType** end() { return reinterpret_cast<ChildType**>(papoGeoms + nGeomCount); }
    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    const ChildType* const* begin() const { return reinterpret_cast<const ChildType* const*>(papoGeoms); }
    /** Return end of iterator */
    const ChildType* const* end() const { return reinterpret_cast<const ChildType* const*>(papoGeoms + nGeomCount); }

    // IGeometryCollection
    /** See OGRGeometryCollection::getGeometryRef() */
    OGRPoint *getGeometryRef( int i) { return OGRGeometryCollection::getGeometryRef(i)->toPoint(); }
    /** See OGRGeometryCollection::getGeometryRef() */
    const OGRPoint *getGeometryRef( int i ) const { return OGRGeometryCollection::getGeometryRef(i)->toPoint(); }

    // Non-standard (OGRGeometry).
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual OGRMultiPoint *clone() const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::importFromWkt; /** deprecated */
#endif

    HGDAL_EXPORT OGRErr importFromWkt( const char ** ) override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a multipoint to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return      WKT representation of the multipoint.
    HGDAL_EXPORT virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    // IGeometry methods.
    HGDAL_EXPORT virtual int getDimension() const override;

    /** Return pointer of this in upper class */
    inline OGRGeometryCollection* toUpperClass() { return this; }
    /** Return pointer of this in upper class */
    inline const OGRGeometryCollection* toUpperClass() const { return this; }

    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    // Non-standard.
    HGDAL_EXPORT virtual OGRBoolean hasCurveGeometry( int bLookForNonLinear = FALSE )
        const override;

    OGR_ALLOW_CAST_TO_THIS(MultiPoint)
    OGR_ALLOW_UPCAST_TO(GeometryCollection)
    OGR_FORBID_DOWNCAST_TO_MULTILINESTRING
    OGR_FORBID_DOWNCAST_TO_MULTICURVE
    OGR_FORBID_DOWNCAST_TO_MULTISURFACE
    OGR_FORBID_DOWNCAST_TO_MULTIPOLYGON
};

//! @cond Doxygen_Suppress
/** @see OGRMultiPoint::begin() const */
inline const OGRMultiPoint::ChildType* const * begin(const OGRMultiPoint* poGeom) { return poGeom->begin(); }
/** @see OGRMultiPoint::end() const */
inline const OGRMultiPoint::ChildType* const * end(const OGRMultiPoint* poGeom) { return poGeom->end(); }

/** @see OGRMultiPoint::begin() */
inline OGRMultiPoint::ChildType** begin(OGRMultiPoint* poGeom) { return poGeom->begin(); }
/** @see OGRMultiPoint::end() */
inline OGRMultiPoint::ChildType** end(OGRMultiPoint* poGeom) { return poGeom->end(); }
//! @endcond

/************************************************************************/
/*                          OGRMultiCurve                               */
/************************************************************************/

/**
 * A collection of OGRCurve.
 *
 * @since GDAL 2.0
 */

class OGRMultiCurve : public OGRGeometryCollection
{
  protected:
//! @cond Doxygen_Suppress
    HGDAL_EXPORT static OGRErr addCurveDirectlyFromWkt( OGRGeometry* poSelf,
                                           OGRCurve* poCurve );
//! @endcond
    HGDAL_EXPORT virtual OGRBoolean isCompatibleSubType( OGRwkbGeometryType )
        const override;

  public:
    HGDAL_EXPORT OGRMultiCurve();
    HGDAL_EXPORT OGRMultiCurve( const OGRMultiCurve& other );
    HGDAL_EXPORT ~OGRMultiCurve() override;

    HGDAL_EXPORT OGRMultiCurve& operator=( const OGRMultiCurve& other );

    /** Type of child elements. */
    typedef OGRCurve ChildType;

    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    ChildType** begin() { return reinterpret_cast<ChildType**>(papoGeoms); }
    /** Return end of iterator */
    ChildType** end() { return reinterpret_cast<ChildType**>(papoGeoms + nGeomCount); }
    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    const ChildType* const* begin() const { return reinterpret_cast<const ChildType* const*>(papoGeoms); }
    /** Return end of iterator */
    const ChildType* const* end() const { return reinterpret_cast<const ChildType* const*>(papoGeoms + nGeomCount); }

    // IGeometryCollection
    /** See OGRGeometryCollection::getGeometryRef() */
    OGRCurve *getGeometryRef( int i) { return OGRGeometryCollection::getGeometryRef(i)->toCurve(); }
    /** See OGRGeometryCollection::getGeometryRef() */
    const OGRCurve *getGeometryRef( int i ) const { return OGRGeometryCollection::getGeometryRef(i)->toCurve(); }

    // Non standard (OGRGeometry).
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual OGRMultiCurve *clone() const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::importFromWkt; /** deprecated */
#endif

    HGDAL_EXPORT OGRErr importFromWkt( const char ** ) override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a multicurve to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return      WKT representation of the multicurve.
    HGDAL_EXPORT virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    // IGeometry methods.
    HGDAL_EXPORT virtual int getDimension() const override;

    // Non-standard.
    HGDAL_EXPORT virtual OGRBoolean hasCurveGeometry( int bLookForNonLinear = FALSE )
        const override;

    /** Return pointer of this in upper class */
    inline OGRGeometryCollection* toUpperClass() { return this; }
    /** Return pointer of this in upper class */
    inline const OGRGeometryCollection* toUpperClass() const { return this; }

    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    HGDAL_EXPORT static OGRMultiLineString* CastToMultiLineString(OGRMultiCurve* poMC);

    OGR_ALLOW_CAST_TO_THIS(MultiCurve)
    OGR_ALLOW_UPCAST_TO(GeometryCollection)
    OGR_FORBID_DOWNCAST_TO_MULTIPOINT
    OGR_FORBID_DOWNCAST_TO_MULTISURFACE
    OGR_FORBID_DOWNCAST_TO_MULTIPOLYGON
};

//! @cond Doxygen_Suppress
/** @see OGRMultiCurve::begin() const */
inline const OGRMultiCurve::ChildType* const * begin(const OGRMultiCurve* poGeom) { return poGeom->begin(); }
/** @see OGRMultiCurve::end() const */
inline const OGRMultiCurve::ChildType* const * end(const OGRMultiCurve* poGeom) { return poGeom->end(); }

/** @see OGRMultiCurve::begin() */
inline OGRMultiCurve::ChildType** begin(OGRMultiCurve* poGeom) { return poGeom->begin(); }
/** @see OGRMultiCurve::end() */
inline OGRMultiCurve::ChildType** end(OGRMultiCurve* poGeom) { return poGeom->end(); }
//! @endcond

/************************************************************************/
/*                          OGRMultiLineString                          */
/************************************************************************/

/**
 * A collection of OGRLineString.
 */

class OGRMultiLineString : public OGRMultiCurve
{
  protected:
    HGDAL_EXPORT virtual OGRBoolean  isCompatibleSubType( OGRwkbGeometryType )
        const override;

  public:
    HGDAL_EXPORT OGRMultiLineString();
    HGDAL_EXPORT OGRMultiLineString( const OGRMultiLineString& other );
    HGDAL_EXPORT ~OGRMultiLineString() override;

    HGDAL_EXPORT OGRMultiLineString& operator=( const OGRMultiLineString& other );

    /** Type of child elements. */
    typedef OGRLineString ChildType;

    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    ChildType** begin() { return reinterpret_cast<ChildType**>(papoGeoms); }
    /** Return end of iterator */
    ChildType** end() { return reinterpret_cast<ChildType**>(papoGeoms + nGeomCount); }
    /** Return begin of iterator.
     * @since GDAL 2.3
     */
    const ChildType* const* begin() const { return reinterpret_cast<const ChildType* const*>(papoGeoms); }
    /** Return end of iterator */
    const ChildType* const* end() const { return reinterpret_cast<const ChildType* const*>(papoGeoms + nGeomCount); }

    // IGeometryCollection
    /** See OGRGeometryCollection::getGeometryRef() */
    OGRLineString *getGeometryRef( int i) { return OGRGeometryCollection::getGeometryRef(i)->toLineString(); }
    /** See OGRGeometryCollection::getGeometryRef() */
    const OGRLineString *getGeometryRef( int i ) const { return OGRGeometryCollection::getGeometryRef(i)->toLineString(); }

    // Non standard (OGRGeometry).
    HGDAL_EXPORT virtual const char *getGeometryName() const override;
    HGDAL_EXPORT virtual OGRwkbGeometryType getGeometryType() const override;
    HGDAL_EXPORT virtual OGRMultiLineString *clone() const override;

#ifndef DOXYGEN_XML
    using OGRGeometry::exportToWkt;
#endif

    /// Export a multilinestring to WKT
    /// \param opts  Output options.
    /// \param err   Pointer to error code, if desired.
    /// \return      WKT representation of the multilinestring.
    HGDAL_EXPORT virtual std::string exportToWkt(const OGRWktOptions& opts = OGRWktOptions(),
                                    OGRErr *err = nullptr) const override;

    // Non standard
    HGDAL_EXPORT virtual OGRBoolean hasCurveGeometry( int bLookForNonLinear = FALSE )
        const override;

    /** Return pointer of this in upper class */
    inline OGRGeometryCollection* toUpperClass() { return this; }
    /** Return pointer of this in upper class */
    inline const OGRGeometryCollection* toUpperClass() const { return this; }

    virtual void accept(IOGRGeometryVisitor* visitor) override { visitor->visit(this); }
    virtual void accept(IOGRConstGeometryVisitor* visitor) const override { visitor->visit(this); }

    HGDAL_EXPORT static OGRMultiCurve* CastToMultiCurve( OGRMultiLineString* poMLS );

    OGR_ALLOW_CAST_TO_THIS(MultiLineString)
    OGR_ALLOW_UPCAST_TO(MultiCurve)
    OGR_FORBID_DOWNCAST_TO_MULTIPOINT
    OGR_FORBID_DOWNCAST_TO_MULTISURFACE
    OGR_FORBID_DOWNCAST_TO_MULTIPOLYGON
};

//! @cond Doxygen_Suppress
/** @see OGRMultiLineString::begin() const */
inline const OGRMultiLineString::ChildType* const * begin(const OGRMultiLineString* poGeom) { return poGeom->begin(); }
/** @see OGRMultiLineString::end() const */
inline const OGRMultiLineString::ChildType* const * end(const OGRMultiLineString* poGeom) { return poGeom->end(); }

/** @see OGRMultiLineString::begin() */
inline OGRMultiLineString::ChildType** begin(OGRMultiLineString* poGeom) { return poGeom->begin(); }
/** @see OGRMultiLineString::end() */
inline OGRMultiLineString::ChildType** end(OGRMultiLineString* poGeom) { return poGeom->end(); }
//! @endcond

/************************************************************************/
/*                          OGRGeometryFactory                          */
/************************************************************************/

/**
 * Create geometry objects from well known text/binary.
 */

class OGRGeometryFactory
{
    HGDAL_EXPORT static OGRErr createFromFgfInternal( const unsigned char *pabyData,
                                         OGRSpatialReference * poSR,
                                         OGRGeometry **ppoReturn,
                                         int nBytes,
                                         int *pnBytesConsumed,
                                         int nRecLevel );
  public:
    HGDAL_EXPORT static OGRErr createFromWkb( const void *, OGRSpatialReference *,
                                 OGRGeometry **, size_t = static_cast<size_t>(-1),
                                 OGRwkbVariant=wkbVariantOldOgc );
    HGDAL_EXPORT static OGRErr createFromWkb( const void * pabyData,
                                 OGRSpatialReference *,
                                 OGRGeometry **,
                                 size_t nSize,
                                 OGRwkbVariant eVariant,
                                 size_t& nBytesConsumedOut );
    HGDAL_EXPORT static OGRErr createFromWkt( const char* , OGRSpatialReference *,
                                 OGRGeometry ** );
    HGDAL_EXPORT static OGRErr createFromWkt( const char **, OGRSpatialReference *,
                                 OGRGeometry ** );
    /** Deprecated.
     * @deprecated in GDAL 2.3
     */
    static OGRErr createFromWkt( char ** ppszInput, OGRSpatialReference * poSRS,
                                 OGRGeometry ** ppoGeom )
                                CPL_WARN_DEPRECATED("Use createFromWkt(const char**, ...) instead")
    {
        return createFromWkt( const_cast<const char**>(ppszInput), poSRS, ppoGeom);
    }

    HGDAL_EXPORT static OGRErr createFromFgf( const void*, OGRSpatialReference *,
                                 OGRGeometry **, int = -1, int * = nullptr );
    HGDAL_EXPORT static OGRGeometry *createFromGML( const char * );
    HGDAL_EXPORT static OGRGeometry *createFromGEOS( GEOSContextHandle_t hGEOSCtxt,
                                        GEOSGeom );
    HGDAL_EXPORT static OGRGeometry *createFromGeoJson( const char *, int = -1 );
    HGDAL_EXPORT static OGRGeometry *createFromGeoJson( const CPLJSONObject &oJSONObject );

    HGDAL_EXPORT static void   destroyGeometry( OGRGeometry * );
    HGDAL_EXPORT static OGRGeometry *createGeometry( OGRwkbGeometryType );

    HGDAL_EXPORT static OGRGeometry * forceToPolygon( OGRGeometry * );
    HGDAL_EXPORT static OGRGeometry * forceToLineString( OGRGeometry *,
                                            bool bOnlyInOrder = true );
    HGDAL_EXPORT static OGRGeometry * forceToMultiPolygon( OGRGeometry * );
    HGDAL_EXPORT static OGRGeometry * forceToMultiPoint( OGRGeometry * );
    HGDAL_EXPORT static OGRGeometry * forceToMultiLineString( OGRGeometry * );

    HGDAL_EXPORT static OGRGeometry * forceTo( OGRGeometry* poGeom,
                                  OGRwkbGeometryType eTargetType,
                                  const char*const* papszOptions = nullptr );

    HGDAL_EXPORT static OGRGeometry * removeLowerDimensionSubGeoms( const OGRGeometry* poGeom );

    HGDAL_EXPORT static OGRGeometry * organizePolygons( OGRGeometry **papoPolygons,
                                           int nPolygonCount,
                                           int *pbResultValidGeometry,
                                           const char **papszOptions = nullptr);
    HGDAL_EXPORT static bool haveGEOS();

    /** Opaque class used as argument to transformWithOptions() */
    class TransformWithOptionsCache
    {
        friend class OGRGeometryFactory;
        struct Private;
        std::unique_ptr<Private> d;

    public:
        HGDAL_EXPORT TransformWithOptionsCache();
        HGDAL_EXPORT ~TransformWithOptionsCache();
    };

    HGDAL_EXPORT static OGRGeometry* transformWithOptions( const OGRGeometry* poSrcGeom,
                                              OGRCoordinateTransformation *poCT,
                                              char** papszOptions,
                                              const TransformWithOptionsCache& cache = TransformWithOptionsCache() );

    HGDAL_EXPORT static OGRGeometry*
        approximateArcAngles( double dfX, double dfY, double dfZ,
                              double dfPrimaryRadius, double dfSecondaryAxis,
                              double dfRotation,
                              double dfStartAngle, double dfEndAngle,
                              double dfMaxAngleStepSizeDegrees,
                              const bool bUseMaxGap = false );

    HGDAL_EXPORT static int GetCurveParameters( double x0, double y0,
                                  double x1, double y1,
                                  double x2, double y2,
                                  double& R, double& cx, double& cy,
                                  double& alpha0, double& alpha1,
                                  double& alpha2 );
    HGDAL_EXPORT static OGRLineString* curveToLineString(
        double x0, double y0, double z0,
        double x1, double y1, double z1,
        double x2, double y2, double z2,
        int bHasZ,
        double dfMaxAngleStepSizeDegrees,
        const char* const * papszOptions = nullptr );
    HGDAL_EXPORT static OGRCurve* curveFromLineString(
        const OGRLineString* poLS,
        const char* const * papszOptions = nullptr);
};

HGDAL_EXPORT OGRwkbGeometryType OGRFromOGCGeomType( const char *pszGeomType );
HGDAL_EXPORT const char * OGRToOGCGeomType( OGRwkbGeometryType eGeomType );

//! @cond Doxygen_Suppress
typedef struct _OGRPreparedGeometry OGRPreparedGeometry;

struct OGRPreparedGeometryUniquePtrDeleter
{
    HGDAL_EXPORT void operator()(OGRPreparedGeometry*) const;
};
//! @endcond

/** Unique pointer type for OGRPreparedGeometry.
 * @since GDAL 2.3
 */
typedef std::unique_ptr<OGRPreparedGeometry, OGRPreparedGeometryUniquePtrDeleter> OGRPreparedGeometryUniquePtr;

#endif /* ndef OGR_GEOMETRY_H_INCLUDED */
