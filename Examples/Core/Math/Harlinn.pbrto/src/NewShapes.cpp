#include "pch.h"

/*
   Copyright 2024-2025 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0
#include <pbrto/NewShapes.h>

#include <pbrto/NewTextures.h>

#include <pbrto/NewInteraction.h>
#include <pbrto/NewOptions.h>
#include <pbrto/NewParamdict.h>
#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewError.h>
#include <pbrto/util/NewFile.h>
#include <pbrto/util/NewFloat.h>
#include <pbrto/util/NewImage.h>
#include <pbrto/util/NewLoopSubDiv.h>
#include <pbrto/util/NewLowDiscrepancy.h>
#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewMemory.h>
#include <pbrto/util/NewSampling.h>
#include <pbrto/util/NewSplines.h>
#include <pbrto/util/NewStats.h>

#include <algorithm>

namespace pbrto
{

    // Sphere Method Definitions
    Bounds3f Sphere::Bounds( ) const
    {
        return ( *renderFromObject )( Bounds3f( Point3f( -radius, -radius, zMin ), Point3f( radius, radius, zMax ) ) );
    }

    pstdo::optional<ShapeSample> Sphere::Sample( Point2f u ) const
    {
        Point3f pObj = Point3f( 0, 0, 0 ) + radius * SampleUniformSphere( u );
        // Reproject _pObj_ to sphere surface and compute _pObjError_
        pObj *= radius / ScalarDistance( pObj, Point3f( 0, 0, 0 ) );
        Vector3f pObjError = gamma( 5 ) * Abs( ( Vector3f )pObj );

        // Compute surface normal for sphere sample and return _ShapeSample_
        Normal3f nObj( pObj.x, pObj.y, pObj.z );
        Normal3f n = Normalize( ( *renderFromObject )( nObj ) );
        if ( reverseOrientation )
            n *= -1;
        // Compute $(u, v)$ coordinates for sphere sample
        Float theta = SafeACos( pObj.z / radius );
        Float phi = Math::ATan2( pObj.y, pObj.x );
        if ( phi < 0 )
            phi += 2 * Pi;
        Point2f uv( phi / phiMax, ( theta - thetaZMin ) / ( thetaZMax - thetaZMin ) );

        Point3fi pi = ( *renderFromObject )( Point3fi( pObj, pObjError ) );
        return ShapeSample{ Interaction( pi, n, uv ), 1 / Area( ) };
    }

    std::string Sphere::ToString( ) const
    {
        return StringPrintf( "[ Sphere renderFromObject: %s "
            "objectFromRender: %s reverseOrientation: %s "
            "transformSwapsHandedness: %s radius: %f zMin: %f "
            "zMax: %f thetaMin: %f "
            "thetaMax: %f phiMax: %f ]",
            *renderFromObject, *objectFromRender, reverseOrientation,
            transformSwapsHandedness, radius, zMin, zMax, thetaZMin,
            thetaZMax, phiMax );
    }

    Sphere* Sphere::Create( const Transform* renderFromObject,
        const Transform* objectFromRender, bool reverseOrientation,
        const ParameterDictionary& parameters, const FileLoc* loc,
        Allocator alloc )
    {
        Float radius = parameters.GetOneFloat( "radius", 1.f );
        Float zmin = parameters.GetOneFloat( "zmin", -radius );
        Float zmax = parameters.GetOneFloat( "zmax", radius );
        Float phimax = parameters.GetOneFloat( "phimax", 360.f );
        return alloc.new_object<Sphere>( renderFromObject, objectFromRender,
            reverseOrientation, radius, zmin, zmax, phimax );
    }

    // Disk Method Definitions
    Bounds3f Disk::Bounds( ) const
    {
        return ( *renderFromObject )(
            Bounds3f( Point3f( -radius, -radius, height ), Point3f( radius, radius, height ) ) );
    }

    DirectionCone Disk::NormalBounds( ) const
    {
        Normal3f::Simd n = ( *renderFromObject )( Normal3f::Simd( 0, 0, 1 ) );
        if ( reverseOrientation )
            n = -n;
        return DirectionCone( Vector3f::Simd( n ) );
    }

    std::string Disk::ToString( ) const
    {
        return StringPrintf(
            "[ Disk renderFromObject: %s objectFromRender: %s "
            "reverseOrientation: %s "
            "transformSwapsHandedness: %s height: %f radius: %f innerRadius: %f "
            "phiMax: %f ]",
            *renderFromObject, *objectFromRender, reverseOrientation,
            transformSwapsHandedness, height, radius, innerRadius, phiMax );
    }

    Disk* Disk::Create( const Transform* renderFromObject, const Transform* objectFromRender,
        bool reverseOrientation, const ParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        Float height = parameters.GetOneFloat( "height", 0. );
        Float radius = parameters.GetOneFloat( "radius", 1 );
        Float innerRadius = parameters.GetOneFloat( "innerradius", 0 );
        Float phimax = parameters.GetOneFloat( "phimax", 360 );
        return alloc.new_object<Disk>( renderFromObject, objectFromRender, reverseOrientation, height, radius, innerRadius, phimax );
    }

    // Cylinder Method Definitions
    Bounds3f Cylinder::Bounds( ) const
    {
        return ( *renderFromObject )( Bounds3f( { -radius, -radius, zMin }, { radius, radius, zMax } ) );
    }

    std::string Cylinder::ToString( ) const
    {
        return StringPrintf( "[ Cylinder renderFromObject: %s objectFromRender: %s "
            "reverseOrientation: %s "
            "transformSwapsHandedness: %s radius: %f zMin: %f zMax: %f "
            "phiMax: %f ]",
            *renderFromObject, *objectFromRender, reverseOrientation,
            transformSwapsHandedness, radius, zMin, zMax, phiMax );
    }

    Cylinder* Cylinder::Create( const Transform* renderFromObject,
        const Transform* objectFromRender, bool reverseOrientation,
        const ParameterDictionary& parameters, const FileLoc* loc,
        Allocator alloc )
    {
        Float radius = parameters.GetOneFloat( "radius", 1 );
        Float zmin = parameters.GetOneFloat( "zmin", -1 );
        Float zmax = parameters.GetOneFloat( "zmax", 1 );
        Float phimax = parameters.GetOneFloat( "phimax", 360 );
        return alloc.new_object<Cylinder>( renderFromObject, objectFromRender,
            reverseOrientation, radius, zmin, zmax, phimax );
    }

    NSTAT_PIXEL_RATIO( "Intersections/Ray-Triangle intersection tests", nTriHits, nTriTests );

    std::string TriangleIntersection::ToString( ) const
    {
        return StringPrintf( "[ TriangleIntersection b0: %f b1: %f b2: %f t: %f ]", b0, b1, b2,
            t );
    }

    pstdo::vector<const TriangleMesh*>* Triangle::allMeshes;
#if defined(PBRT_BUILD_GPU_RENDERER)
    PBRT_GPU pstdo::vector<const TriangleMesh*>* allTriangleMeshesGPU;
#endif

    void Triangle::Init( Allocator alloc )
    {
        allMeshes = alloc.new_object<pstdo::vector<const TriangleMesh*>>( alloc );
#if defined(PBRT_BUILD_GPU_RENDERER)
        if ( Options->useGPU )
            CUDA_CHECK( cudaMemcpyToSymbol( ( const void* )&allTriangleMeshesGPU,
                ( const void* )&allMeshes, sizeof( allMeshes ) ) );
#endif
    }

    NSTAT_MEMORY_COUNTER( "Memory/Triangles", triangleBytes );

    // Triangle Functions
    PBRTO_EXPORT pstdo::optional<TriangleIntersection> IntersectTriangle( const Ray& ray, Float tMax, Point3f::Simd p0, Point3f::Simd p1, Point3f::Simd p2 )
    {
        // Return no intersection if triangle is degenerate
        if ( ScalarLengthSquared( Cross( p2 - p0, p1 - p0 ) ) == 0 )
            return {};

        // Transform triangle vertices to ray coordinate space
        // Translate vertices based on ray origin
        Point3f p0t = p0 - Vector3f::Simd( ray.o );
        Point3f p1t = p1 - Vector3f::Simd( ray.o );
        Point3f p2t = p2 - Vector3f::Simd( ray.o );

        // Permute components of triangle vertices and ray direction
        int kz = MaxComponentIndex( Abs( ray.d ) );
        int kx = kz + 1;
        if ( kx == 3 )
            kx = 0;
        int ky = kx + 1;
        if ( ky == 3 )
            ky = 0;
        Vector3f d = Permute( ray.d, { kx, ky, kz } );
        p0t = Permute( p0t, { kx, ky, kz } );
        p1t = Permute( p1t, { kx, ky, kz } );
        p2t = Permute( p2t, { kx, ky, kz } );

        // Apply shear transformation to translated vertex positions
        Float Sx = -d.x / d.z;
        Float Sy = -d.y / d.z;
        Float Sz = 1 / d.z;
        p0t.x += Sx * p0t.z;
        p0t.y += Sy * p0t.z;
        p1t.x += Sx * p1t.z;
        p1t.y += Sy * p1t.z;
        p2t.x += Sx * p2t.z;
        p2t.y += Sy * p2t.z;

        // Compute edge function coefficients _e0_, _e1_, and _e2_
        Float e0 = DifferenceOfProducts( p1t.x, p2t.y, p1t.y, p2t.x );
        Float e1 = DifferenceOfProducts( p2t.x, p0t.y, p2t.y, p0t.x );
        Float e2 = DifferenceOfProducts( p0t.x, p1t.y, p0t.y, p1t.x );

        // Fall back to double-precision test at triangle edges
        if ( sizeof( Float ) == sizeof( float ) && ( e0 == 0.0f || e1 == 0.0f || e2 == 0.0f ) )
        {
            double p2txp1ty = ( double )p2t.x * ( double )p1t.y;
            double p2typ1tx = ( double )p2t.y * ( double )p1t.x;
            e0 = ( float )( p2typ1tx - p2txp1ty );
            double p0txp2ty = ( double )p0t.x * ( double )p2t.y;
            double p0typ2tx = ( double )p0t.y * ( double )p2t.x;
            e1 = ( float )( p0typ2tx - p0txp2ty );
            double p1txp0ty = ( double )p1t.x * ( double )p0t.y;
            double p1typ0tx = ( double )p1t.y * ( double )p0t.x;
            e2 = ( float )( p1typ0tx - p1txp0ty );
        }

        // Perform triangle edge and determinant tests
        if ( ( e0 < 0 || e1 < 0 || e2 < 0 ) && ( e0 > 0 || e1 > 0 || e2 > 0 ) )
            return {};
        Float det = e0 + e1 + e2;
        if ( det == 0 )
            return {};

        // Compute scaled hit distance to triangle and test against ray $t$ range
        p0t.z *= Sz;
        p1t.z *= Sz;
        p2t.z *= Sz;
        Float tScaled = e0 * p0t.z + e1 * p1t.z + e2 * p2t.z;
        if ( det < 0 && ( tScaled >= 0 || tScaled < tMax * det ) )
            return {};
        else if ( det > 0 && ( tScaled <= 0 || tScaled > tMax * det ) )
            return {};

        // Compute barycentric coordinates and $t$ value for triangle intersection
        Float invDet = 1 / det;
        Float b0 = e0 * invDet, b1 = e1 * invDet, b2 = e2 * invDet;
        Float t = tScaled * invDet;
        NDCHECK( !IsNaN( t ) );

        // Ensure that computed triangle $t$ is conservatively greater than zero
        // Compute $\delta_z$ term for triangle $t$ error bounds
        Float maxZt = MaxComponentValue( Abs( Vector3f( p0t.z, p1t.z, p2t.z ) ) );
        Float deltaZ = gamma( 3 ) * maxZt;

        // Compute $\delta_x$ and $\delta_y$ terms for triangle $t$ error bounds
        Float maxXt = MaxComponentValue( Abs( Vector3f( p0t.x, p1t.x, p2t.x ) ) );
        Float maxYt = MaxComponentValue( Abs( Vector3f( p0t.y, p1t.y, p2t.y ) ) );
        Float deltaX = gamma( 5 ) * ( maxXt + maxZt );
        Float deltaY = gamma( 5 ) * ( maxYt + maxZt );

        // Compute $\delta_e$ term for triangle $t$ error bounds
        Float deltaE = 2 * ( gamma( 2 ) * maxXt * maxYt + deltaY * maxXt + deltaX * maxYt );

        // Compute $\delta_t$ term for triangle $t$ error bounds and check _t_
        Float maxE = MaxComponentValue( Abs( Vector3f( e0, e1, e2 ) ) );
        Float deltaT =
            3 * ( gamma( 3 ) * maxE * maxZt + deltaE * maxZt + deltaZ * maxE ) * Math::FastAbs( invDet );
        if ( t <= deltaT )
            return {};

        // Return _TriangleIntersection_ for intersection
        return TriangleIntersection{ b0, b1, b2, t };
    }

    // Triangle Method Definitions
    pstdo::vector<Shape> Triangle::CreateTriangles( const TriangleMesh* mesh, Allocator alloc )
    {
        static std::mutex allMeshesLock;
        allMeshesLock.lock( );
        NCHECK_LT( allMeshes->size( ), 1 << 31 );
        int meshIndex = int( allMeshes->size( ) );
        allMeshes->push_back( mesh );
        allMeshesLock.unlock( );

        pstdo::vector<Shape> tris( mesh->nTriangles, alloc );
        Triangle* t = alloc.allocate_object<Triangle>( mesh->nTriangles );
        for ( int i = 0; i < mesh->nTriangles; ++i )
        {
            alloc.construct( &t[ i ], meshIndex, i );
            tris[ i ] = &t[ i ];
        }
        triangleBytes += mesh->nTriangles * sizeof( Triangle );
        return tris;
    }

    Bounds3f Triangle::Bounds( ) const
    {
        // Get triangle vertices in _p0_, _p1_, and _p2_
        const TriangleMesh* mesh = GetMesh( );
        const int* v = &mesh->vertexIndices[ 3 * triIndex ];
        Point3f::Simd p0 = mesh->p[ v[ 0 ] ], p1 = mesh->p[ v[ 1 ] ], p2 = mesh->p[ v[ 2 ] ];

        return Union( Bounds3f( p0, p1 ), p2 );
    }

    DirectionCone Triangle::NormalBounds( ) const
    {
        // Get triangle vertices in _p0_, _p1_, and _p2_
        const TriangleMesh* mesh = GetMesh( );
        const int* v = &mesh->vertexIndices[ 3 * triIndex ];
        Point3f::Simd p0 = mesh->p[ v[ 0 ] ], p1 = mesh->p[ v[ 1 ] ], p2 = mesh->p[ v[ 2 ] ];

        Normal3f::Simd n = Normalize( Normal3f::Simd( Cross( p1 - p0, p2 - p0 ) ) );
        // Ensure correct orientation of geometric normal for normal bounds
        if ( mesh->n )
        {
            Normal3f::Simd ns( mesh->n[ v[ 0 ] ] + mesh->n[ v[ 1 ] ] + mesh->n[ v[ 2 ] ] );
            n = FaceForward( n, ns );
        }
        else if ( mesh->reverseOrientation ^ mesh->transformSwapsHandedness )
            n *= -1;

        return DirectionCone( Vector3f::Simd( n ) );
    }

    pstdo::optional<ShapeIntersection> Triangle::Intersect( const Ray& ray, Float tMax ) const
    {
#ifndef PBRT_IS_GPU_CODE
        ++nTriTests;
#endif
        // Get triangle vertices in _p0_, _p1_, and _p2_
        const TriangleMesh* mesh = GetMesh( );
        const int* v = &mesh->vertexIndices[ 3 * triIndex ];
        Point3f::Simd p0 = mesh->p[ v[ 0 ] ], p1 = mesh->p[ v[ 1 ] ], p2 = mesh->p[ v[ 2 ] ];

        pstdo::optional<TriangleIntersection> triIsect =
            IntersectTriangle( ray, tMax, p0, p1, p2 );
        if ( !triIsect )
            return {};
        SurfaceInteraction intr =
            InteractionFromIntersection( mesh, triIndex, *triIsect, ray.time, -ray.d );
#ifndef PBRT_IS_GPU_CODE
        ++nTriHits;
#endif
        return ShapeIntersection{ intr, triIsect->t };
    }

    bool Triangle::IntersectP( const Ray& ray, Float tMax ) const
    {
#ifndef PBRT_IS_GPU_CODE
        ++nTriTests;
#endif
        // Get triangle vertices in _p0_, _p1_, and _p2_
        const TriangleMesh* mesh = GetMesh( );
        const int* v = &mesh->vertexIndices[ 3 * triIndex ];
        Point3f::Simd p0 = mesh->p[ v[ 0 ] ], p1 = mesh->p[ v[ 1 ] ], p2 = mesh->p[ v[ 2 ] ];

        pstdo::optional<TriangleIntersection> isect = IntersectTriangle( ray, tMax, p0, p1, p2 );
        if ( isect )
        {
#ifndef PBRT_IS_GPU_CODE
            ++nTriHits;
#endif
            return true;
        }
        else
            return false;
    }

    std::string Triangle::ToString( ) const
    {
        // Get triangle vertices in _p0_, _p1_, and _p2_
        auto mesh = GetMesh( );
        const int* v = &mesh->vertexIndices[ 3 * triIndex ];
        const Point3f& p0 = mesh->p[ v[ 0 ] ];
        const Point3f& p1 = mesh->p[ v[ 1 ] ];
        const Point3f& p2 = mesh->p[ v[ 2 ] ];

        return StringPrintf( "[ Triangle meshIndex: %d triIndex: %d -> p [ %s %s %s ] ]",
            meshIndex, triIndex, p0, p1, p2 );
    }

    TriangleMesh* Triangle::CreateMesh( const Transform* renderFromObject,
        bool reverseOrientation,
        const ParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        std::vector<int> vi = parameters.GetIntArray( "indices" );
        std::vector<Point3f> P = parameters.GetPoint3fArray( "P" );
        std::vector<Point2f> uvs = parameters.GetPoint2fArray( "uv" );

        if ( vi.empty( ) )
        {
            if ( P.size( ) == 3 )
                vi = { 0, 1, 2 };
            else
            {
                Error( loc, "Vertex indices \"indices\" must be provided with "
                    "triangle mesh." );
                return {};
            }
        }
        else if ( ( vi.size( ) % 3 ) != 0u )
        {
            Error( loc,
                "Number of vertex indices %d not a multiple of 3. Discarding %d "
                "excess.",
                int( vi.size( ) ), int( vi.size( ) % 3 ) );
            while ( ( vi.size( ) % 3 ) != 0u )
                vi.pop_back( );
        }

        if ( P.empty( ) )
        {
            Error( loc, "Vertex positions \"P\" must be provided with triangle mesh." );
            return {};
        }

        if ( !uvs.empty( ) && uvs.size( ) != P.size( ) )
        {
            Error( loc, "Number of \"uv\"s for triangle mesh must match \"P\"s. "
                "Discarding uvs." );
            uvs = {};
        }

        std::vector<Vector3f> S = parameters.GetVector3fArray( "S" );
        if ( !S.empty( ) && S.size( ) != P.size( ) )
        {
            Error( loc, "Number of \"S\"s for triangle mesh must match \"P\"s. "
                "Discarding \"S\"s." );
            S = {};
        }
        std::vector<Normal3f> N = parameters.GetNormal3fArray( "N" );
        if ( !N.empty( ) && N.size( ) != P.size( ) )
        {
            Error( loc, "Number of \"N\"s for triangle mesh must match \"P\"s. "
                "Discarding \"N\"s." );
            N = {};
        }

        for ( size_t i = 0; i < vi.size( ); ++i )
            if ( vi[ i ] >= P.size( ) )
            {
                Error( loc,
                    "trianglemesh has out of-bounds vertex index %d (%d \"P\" "
                    "values were given. Discarding this mesh.",
                    vi[ i ], ( int )P.size( ) );
                return {};
            }

        std::vector<int> faceIndices = parameters.GetIntArray( "faceIndices" );
        if ( !faceIndices.empty( ) && faceIndices.size( ) != vi.size( ) / 3 )
        {
            Error( loc,
                "Number of face indices %d does not match number of triangles %d. "
                "Discarding face indices.",
                int( faceIndices.size( ) ), int( vi.size( ) / 3 ) );
            faceIndices = {};
        }

        return alloc.new_object<TriangleMesh>(
            *renderFromObject, reverseOrientation, std::move( vi ), std::move( P ), std::move( S ),
            std::move( N ), std::move( uvs ), std::move( faceIndices ), alloc );
    }

    NSTAT_MEMORY_COUNTER( "Memory/Curves", curveBytes );
    NSTAT_PERCENT( "Intersections/Ray-curve intersection tests", nCurveHits, nCurveTests );
    NSTAT_COUNTER( "Geometry/Curves", nCurves );
    NSTAT_COUNTER( "Geometry/Split curves", nSplitCurves );

    std::string ToString( CurveType type )
    {
        switch ( type )
        {
            case CurveType::Flat:
                return "Flat";
            case CurveType::Cylinder:
                return "Cylinder";
            case CurveType::Ribbon:
                return "Ribbon";
            default:
                NLOG_FATAL( "Unhandled case" );
                return "";
        }
    }

    // CurveCommon Method Definitions
    CurveCommon::CurveCommon( const std::array<Point3f, 4>& c, Float width0, Float width1, CurveType type, const boost::container::small_vector<Normal3f, 2>& norm, const Transform* renderFromObject, const Transform* objectFromRender, bool reverseOrientation )
        : cpObj( c ), width { width0, width1 }, type( type ),
          renderFromObject( renderFromObject ),
          objectFromRender( objectFromRender ),
          reverseOrientation( reverseOrientation ),
          transformSwapsHandedness( renderFromObject->SwapsHandedness( ) )
    {
        if ( norm.size( ) == 2 )
        {
            n[ 0 ] = Normalize( norm[ 0 ] );
            n[ 1 ] = Normalize( norm[ 1 ] );
            normalAngle = ScalarAngleBetween( n[ 0 ], n[ 1 ] );
            invSinNormalAngle = 1.f / Math::Sin( normalAngle );
        }
        ++nCurves;
    }

    std::string CurveCommon::ToString( ) const
    {
        return StringPrintf(
            "[ CurveCommon type: %s cpObj: %s width: %s n: %s normalAngle: %f "
            "invSinNormalAngle: %f renderFromObject: %s "
            "objectFromRender: %s "
            "reverseOrientation: %s transformSwapsHandedness: %s ]",
            type, pstdo::MakeSpan( cpObj ), pstdo::MakeSpan( width ), pstdo::MakeSpan( n ),
            normalAngle, invSinNormalAngle, *renderFromObject, *objectFromRender,
            reverseOrientation, transformSwapsHandedness );
    }

    pstdo::vector<Shape> CreateCurve( const Transform* renderFromObject,
        const Transform* objectFromRender,
        bool reverseOrientation, const std::array<Point3f, 4>& c,
        Float w0, Float w1, CurveType type,
        const boost::container::small_vector<Normal3f, 2>& norm, int splitDepth,
        Allocator alloc )
    {
        CurveCommon* common = alloc.new_object<CurveCommon>(
            c, w0, w1, type, norm, renderFromObject, objectFromRender, reverseOrientation );

        const int nSegments = 1 << splitDepth;
        pstdo::vector<Shape> segments( nSegments, alloc );
        Curve* curves = alloc.allocate_object<Curve>( nSegments );
        for ( int i = 0; i < nSegments; ++i )
        {
            Float uMin = i / ( Float )nSegments;
            Float uMax = ( i + 1 ) / ( Float )nSegments;
            alloc.construct( &curves[ i ], common, uMin, uMax );
            segments[ i ] = &curves[ i ];
            ++nSplitCurves;
        }

        curveBytes += sizeof( CurveCommon ) + nSegments * sizeof( Curve );
        return segments;
    }

    // Curve Method Definitions
    Bounds3f Curve::Bounds( ) const
    {
        Bounds3f objBounds = BoundCubicBezier( common->cpObj, uMin, uMax );
        // Expand _objBounds_ by maximum curve width over $u$ range
        Float width[ 2 ] = { Lerp2( uMin, common->width[ 0 ], common->width[ 1 ] ),
                          Lerp2( uMax, common->width[ 0 ], common->width[ 1 ] ) };
        objBounds = Expand( objBounds, std::max( width[ 0 ], width[ 1 ] ) * 0.5f );

        return ( *common->renderFromObject )( objBounds );
    }

    PBRT_CPU_GPU Float Curve::Area( ) const
    {
        std::array<Point3f, 4> cpObj = CubicBezierControlPoints( common->cpObj, uMin, uMax );
        Float width0 = Lerp2( uMin, common->width[ 0 ], common->width[ 1 ] );
        Float width1 = Lerp2( uMax, common->width[ 0 ], common->width[ 1 ] );
        Float avgWidth = ( width0 + width1 ) * 0.5f;
        Float approxLength = 0.f;
        for ( int i = 0; i < 3; ++i )
        {
            approxLength += ScalarDistance( cpObj[ i ], cpObj[ i + 1 ] );
        }
        return approxLength * avgWidth;
    }

    pstdo::optional<ShapeIntersection> Curve::Intersect( const Ray& ray, Float tMax ) const
    {
        pstdo::optional<ShapeIntersection> si;
        IntersectRay( ray, tMax, &si );
        return si;
    }

    bool Curve::IntersectP( const Ray& ray, Float tMax ) const
    {
        return IntersectRay( ray, tMax, nullptr );
    }

    bool Curve::IntersectRay( const Ray& r, Float tMax, pstdo::optional<ShapeIntersection>* si ) const
    {
#ifndef PBRT_IS_GPU_CODE
        ++nCurveTests;
#endif
        // Transform _Ray_ to curve's object space
        Ray ray = ( *common->objectFromRender )( r );

        // Get object-space control points for curve segment, _cpObj_
        std::array<Point3f, 4> cpObj = CubicBezierControlPoints( common->cpObj, uMin, uMax );

        // Project curve control points to plane perpendicular to ray
        Vector3f::Simd dx = Cross( ray.d, cpObj[ 3 ] - cpObj[ 0 ] );
        if ( ScalarLengthSquared( dx ) == 0 )
        {
            Vector3f dy;
            Vector3f dxTmp;
            CoordinateSystem( Vector3f( ray.d ), &dxTmp, &dy );
            dx = dxTmp;
        }
        Transform rayFromObject = pbrto::LookAt( ray.o, ray.o + ray.d, dx );
        std::array<Point3f, 4> cp = { rayFromObject( Point3f::Simd( cpObj[ 0 ] ) ), rayFromObject( Point3f::Simd( cpObj[ 1 ] ) ),
                                      rayFromObject( Point3f::Simd( cpObj[ 2 ] ) ), rayFromObject( Point3f::Simd( cpObj[ 3 ] ) ) };

        // Test ray against bound of projected control points
        Float maxWidth = std::max( Lerp2( uMin, common->width[ 0 ], common->width[ 1 ] ),
            Lerp2( uMax, common->width[ 0 ], common->width[ 1 ] ) );
        Bounds3f curveBounds = Union( Bounds3f( cp[ 0 ], cp[ 1 ] ), Bounds3f( cp[ 2 ], cp[ 3 ] ) );
        curveBounds = Expand( curveBounds, 0.5f * maxWidth );
        Bounds3f rayBounds( Point3f( 0, 0, 0 ), Point3f( 0, 0, ScalarLength( ray.d ) * tMax ) );
        if ( !Overlaps( rayBounds, curveBounds ) )
            return false;

        // Compute refinement depth for curve, _maxDepth_
        Float L0 = 0;
        for ( int i = 0; i < 2; ++i )
            L0 = std::max(
                L0, std::max( 
                    std::max( Math::FastAbs( cp[ i ].x - 2 * cp[ i + 1 ].x + cp[ i + 2 ].x ),
                    Math::FastAbs( cp[ i ].y - 2 * cp[ i + 1 ].y + cp[ i + 2 ].y ) ),
                    Math::FastAbs( cp[ i ].z - 2 * cp[ i + 1 ].z + cp[ i + 2 ].z ) ) );
        int maxDepth = 0;
        if ( L0 > 0 )
        {
            Float eps = std::max( common->width[ 0 ], common->width[ 1 ] ) * .05f;  // width / 20
            // Compute log base 4 by dividing log2 in half.
            int r0 = Log2Int( 1.41421356237f * 6.f * L0 / ( 8.f * eps ) ) / 2;
            maxDepth = Clamp( r0, 0, 10 );
        }

        // Recursively test for ray--curve intersection
        
        return RecursiveIntersect( ray, tMax, cp, Inverse( rayFromObject ), uMin, uMax, maxDepth, si );
    }

    bool Curve::RecursiveIntersect( const Ray& ray, Float tMax, std::span<const Point3f, 4> cp,
        const Transform& objectFromRay, Float u0, Float u1,
        int depth, pstdo::optional<ShapeIntersection>* si ) const
    {
        Float rayLength = ScalarLength( ray.d );
        if ( depth > 0 )
        {
            // Split curve segment into subsegments and test for intersection
            std::array<Point3f, 7> cpSplit = SubdivideCubicBezier( cp );
            Float u[ 3 ] = { u0, ( u0 + u1 ) / 2, u1 };
            for ( int seg = 0; seg < 2; ++seg )
            {
                // Check ray against curve segment's bounding box
                Float maxWidth =
                    std::max( Lerp2( u[ seg ], common->width[ 0 ], common->width[ 1 ] ),
                        Lerp2( u[ seg + 1 ], common->width[ 0 ], common->width[ 1 ] ) );
                std::span<const Point3f,4> cps( &cpSplit[ 3 * seg ], 4 );
                Bounds3f curveBounds = Union( Bounds3f( cps[ 0 ], cps[ 1 ] ), Bounds3f( cps[ 2 ], cps[ 3 ] ) );
                curveBounds = Expand( curveBounds, 0.5f * maxWidth );
                Bounds3f rayBounds( Point3f( 0, 0, 0 ), Point3f( 0, 0, ScalarLength( ray.d ) * tMax ) );
                if ( !Overlaps( rayBounds, curveBounds ) )
                    continue;

                // Recursively test ray-segment intersection
                bool hit = RecursiveIntersect( ray, tMax, cps, objectFromRay, u[ seg ],
                    u[ seg + 1 ], depth - 1, si );
                if ( hit && !si )
                    return true;
            }
            return si ? si->has_value( ) : false;

        }
        else
        {
            // Intersect ray with curve segment
            // Test ray against segment endpoint boundaries
            // Test sample point against tangent perpendicular at curve start
            Float edge = ( cp[ 1 ].y - cp[ 0 ].y ) * -cp[ 0 ].y + cp[ 0 ].x * ( cp[ 0 ].x - cp[ 1 ].x );
            if ( edge < 0 )
                return false;

            // Test sample point against tangent perpendicular at curve end
            edge = ( cp[ 2 ].y - cp[ 3 ].y ) * -cp[ 3 ].y + cp[ 3 ].x * ( cp[ 3 ].x - cp[ 2 ].x );
            if ( edge < 0 )
                return false;

            // Find line $w$ that gives minimum distance to sample point
            Vector2f segmentDir = Point2f( cp[ 3 ].x, cp[ 3 ].y ) - Point2f( cp[ 0 ].x, cp[ 0 ].y );
            Float denom = ScalarLengthSquared( segmentDir );
            if ( denom == 0 )
                return false;
            Float w = ScalarDot( -Vector2f( cp[ 0 ].x, cp[ 0 ].y ), segmentDir ) / denom;

            // Compute $u$ coordinate of curve intersection point and _hitWidth_
            Float u = Clamp( Lerp2( w, u0, u1 ), u0, u1 );
            Float hitWidth = Lerp2( u, common->width[ 0 ], common->width[ 1 ] );
            Normal3f nHit;
            if ( common->type == CurveType::Ribbon )
            {
                // Scale _hitWidth_ based on ribbon orientation
                if ( common->normalAngle == 0 )
                    nHit = common->n[ 0 ];
                else
                {
                    Float sin0 = Math::Sin( ( 1 - u ) * common->normalAngle ) * common->invSinNormalAngle;
                    Float sin1 = Math::Sin( u * common->normalAngle ) * common->invSinNormalAngle;
                    nHit = sin0 * common->n[ 0 ] + sin1 * common->n[ 1 ];
                }
                hitWidth *= ScalarAbsDot( nHit, ray.d ) / rayLength;
            }

            // Test intersection point against curve width
            Vector3f dpcdw;
            Point3f pc = EvaluateCubicBezier( cp, Clamp( w, 0, 1 ), &dpcdw );
            Float ptCurveDist2 = Sqr( pc.x ) + Sqr( pc.y );

            if ( ptCurveDist2 > Sqr( hitWidth ) * 0.25f )
                return false;
            if ( pc.z < 0 || pc.z > rayLength * tMax )
                return false;

            if ( si )
            {
                // Initialize _ShapeIntersection_ for curve intersection
                // Compute _tHit_ for curve intersection
                // FIXME: this tHit isn't quite right for ribbons...
                Float tHit = pc.z / rayLength;
                if ( si->has_value( ) && tHit > si->value( ).tHit )
                    return false;

                // Initialize _SurfaceInteraction_ _intr_ for curve intersection
                // Compute $v$ coordinate of curve intersection point
                Float ptCurveDist = Math::Sqrt( ptCurveDist2 );
                Float edgeFunc = dpcdw.x * -pc.y + pc.x * dpcdw.y;
                Float v = ( edgeFunc > 0 ) ? 0.5f + ptCurveDist / hitWidth
                    : 0.5f - ptCurveDist / hitWidth;

                // Compute $\dpdu$ and $\dpdv$ for curve intersection
                Vector3f dpdu, dpdv;
                EvaluateCubicBezier( common->cpObj, u, &dpdu );
                NCHECK_NE( Vector3f( 0, 0, 0 ), dpdu );
                if ( common->type == CurveType::Ribbon )
                    dpdv = Normalize( Cross( nHit, dpdu ) ) * hitWidth;
                else
                {
                    // Compute curve $\dpdv$ for flat and cylinder curves
                    Vector3f dpduPlane = objectFromRay.ApplyInverse( dpdu );
                    Vector3f::Simd dpdvPlane =
                        Normalize( Vector3f( -dpduPlane.y, dpduPlane.x, 0 ) ) * hitWidth;
                    if ( common->type == CurveType::Cylinder )
                    {
                        // Rotate _dpdvPlane_ to give cylindrical appearance
                        Float theta = Lerp2( v, -90, 90 );
                        Transform rot = Rotate( -theta, dpduPlane );
                        dpdvPlane = rot( dpdvPlane );
                    }
                    dpdv = objectFromRay( dpdvPlane );
                }

                // Compute error bounds for curve intersection
                Vector3f pError( hitWidth, hitWidth, hitWidth );

                bool flipNormal =
                    common->reverseOrientation ^ common->transformSwapsHandedness;
                Point3fi pi( ray( tHit ), pError );
                SurfaceInteraction intr( pi, { u, v }, -ray.d, dpdu, dpdv, Normal3f( ),
                    Normal3f( ), ray.time, flipNormal );
                intr = ( *common->renderFromObject )( intr );

                *si = ShapeIntersection{ intr, tHit };
            }
#ifndef PBRT_IS_GPU_CODE
            ++nCurveHits;
#endif
            return true;
        }
    }

    PBRT_CPU_GPU pstdo::optional<ShapeSample> Curve::Sample( Point2f u ) const
    {
        NLOG_FATAL( "Curve::Sample not implemented." );
        return {};
    }

    PBRT_CPU_GPU Float Curve::PDF( const Interaction& ) const
    {
        NLOG_FATAL( "Curve::PDF not implemented." );
        return {};
    }

    PBRT_CPU_GPU pstdo::optional<ShapeSample> Curve::Sample( const ShapeSampleContext& ctx,
        Point2f u ) const
    {
        NLOG_FATAL( "Curve::Sample not implemented." );
        return {};
    }

    PBRT_CPU_GPU Float Curve::PDF( const ShapeSampleContext& ctx, Vector3f::Simd wi ) const
    {
        NLOG_FATAL( "Curve::PDF not implemented." );
        return {};
    }

    std::string Curve::ToString( ) const
    {
        return StringPrintf( "[ Curve common: %s uMin: %f uMax: %f ]", *common, uMin, uMax );
    }

    pstdo::vector<Shape> Curve::Create( const Transform* renderFromObject,
        const Transform* objectFromRender,
        bool reverseOrientation,
        const ParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        Float width = parameters.GetOneFloat( "width", 1.f );
        Float width0 = parameters.GetOneFloat( "width0", width );
        Float width1 = parameters.GetOneFloat( "width1", width );

        int degree = parameters.GetOneInt( "degree", 3 );
        if ( degree != 2 && degree != 3 )
        {
            Error( loc, "Invalid degree %d: only degree 2 and 3 curves are supported.",
                degree );
            return {};
        }

        std::string basis = parameters.GetOneString( "basis", "bezier" );
        if ( basis != "bezier" && basis != "bspline" )
        {
            Error( loc,
                "Invalid basis \"%s\": only \"bezier\" and \"bspline\" are "
                "supported.",
                basis );
            return {};
        }

        int nSegments;
        std::vector<Point3f> cp = parameters.GetPoint3fArray( "P" );
        if ( basis == "bezier" )
        {
            // After the first segment, which uses degree+1 control points,
            // subsequent segments reuse the last control point of the previous
            // one and then use degree more control points.
            if ( ( ( cp.size( ) - 1 - degree ) % degree ) != 0 )
            {
                Error( loc,
                    "Invalid number of control points %d: for the degree %d "
                    "Bezier basis %d + n * %d are required, for n >= 0.",
                    ( int )cp.size( ), degree, degree + 1, degree );
                return {};
            }
            nSegments = ( cp.size( ) - 1 ) / degree;
        }
        else
        {
            if ( cp.size( ) < degree + 1 )
            {
                Error( loc,
                    "Invalid number of control points %d: for the degree %d "
                    "b-spline basis, must have >= %d.",
                    int( cp.size( ) ), degree, degree + 1 );
                return {};
            }
            nSegments = cp.size( ) - degree;
        }

        CurveType type;
        std::string curveType = parameters.GetOneString( "type", "flat" );
        if ( curveType == "flat" )
            type = CurveType::Flat;
        else if ( curveType == "ribbon" )
            type = CurveType::Ribbon;
        else if ( curveType == "cylinder" )
            type = CurveType::Cylinder;
        else
        {
            Error( loc, R"(Unknown curve type "%s".  Using "cylinder".)", curveType );
            type = CurveType::Cylinder;
        }

        std::vector<Normal3f> n = parameters.GetNormal3fArray( "N" );
        if ( !n.empty( ) )
        {
            if ( type != CurveType::Ribbon )
            {
                Warning( "Curve normals are only used with \"ribbon\" type curves." );
                n = {};
            }
            else if ( n.size( ) != nSegments + 1 )
            {
                Error( loc,
                    "Invalid number of normals %d: must provide %d normals for "
                    "ribbon "
                    "curves with %d segments.",
                    int( n.size( ) ), nSegments + 1, nSegments );
                return {};
            }
        }
        else if ( type == CurveType::Ribbon )
        {
            Error( loc, "Must provide normals \"N\" at curve endpoints with ribbon "
                "curves." );
            return {};
        }

        // This is kind of a hack, but since we dice curves on the GPU we
        // really don't want to have them split here.
        int sd = Options->useGPU ? 0 : parameters.GetOneInt( "splitdepth", 3 );

        if ( type == CurveType::Ribbon && n.empty( ) )
        {
            Error( loc, "Must provide normals \"N\" at curve endpoints with ribbon "
                "curves." );
            return {};
        }

        pstdo::vector<Shape> curves( alloc );
        // Pointer to the first control point for the current segment. This is
        // updated after each loop iteration depending on the current basis.
        int cpOffset = 0;
        for ( int seg = 0; seg < nSegments; ++seg )
        {
            std::array<Point3f, 4> segCpBezier;

            // First, compute the cubic Bezier control points for the current
            // segment and store them in segCpBezier. (It is admittedly
            // wasteful storage-wise to turn b-splines into Bezier segments and
            // wasteful computationally to turn quadratic curves into cubics,
            // but yolo.)
            if ( basis == "bezier" )
            {
                if ( degree == 2 )
                {
                    // Elevate to degree 3.
                    segCpBezier = ElevateQuadraticBezierToCubic(
                        std::span<const Point3f,3>(cp.data( ) + cpOffset, 3 ) );
                }
                else
                {
                    // All set.
                    for ( int i = 0; i < 4; ++i )
                        segCpBezier[ i ] = cp[ cpOffset + i ];
                }
                cpOffset += degree;
            }
            else
            {
                // Uniform b-spline.
                if ( degree == 2 )
                {
                    std::array<Point3f, 3> bezCp = QuadraticBSplineToBezier(
                        std::span<const Point3f, 3>( cp.data( ) + cpOffset, 3 ) );
                    segCpBezier = ElevateQuadraticBezierToCubic( bezCp );
                }
                else
                {
                    segCpBezier =
                        CubicBSplineToBezier( std::span<const Point3f, 4>( cp.data( ) + cpOffset, 4 ) );
                }
                ++cpOffset;
            }

            //pstdo::span<const Normal3f> nspan;
            boost::container::small_vector<Normal3f, 2> normals;
            if ( !n.empty( ) )
            {
                //nspan = pstdo::MakeSpan( &n[ seg ], 2 );
                normals.assign( &n[ seg ], &n[ seg + 2 ] );
            }
                
            auto c =
                CreateCurve( renderFromObject, objectFromRender, reverseOrientation,
                    segCpBezier, Lerp2( Float( seg ) / Float( nSegments ), width0, width1 ),
                    Lerp2( Float( seg + 1 ) / Float( nSegments ), width0, width1 ), type,
                    normals, sd, alloc );
            curves.insert( curves.end( ), c.begin( ), c.end( ) );
        }
        return curves;
    }

    NSTAT_PIXEL_RATIO( "Intersections/Ray-bilinear patch intersection tests", nBLPHits,
        nBLPTests );

    // BilinearPatch Method Definitions
    std::string BilinearIntersection::ToString( ) const
    {
        return StringPrintf( "[ BilinearIntersection uv: %s t: %f", uv, t );
    }

    BilinearPatchMesh* BilinearPatch::CreateMesh( const Transform* renderFromObject,
        bool reverseOrientation,
        const ParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        std::vector<int> vertexIndices = parameters.GetIntArray( "indices" );
        std::vector<Point3f> P = parameters.GetPoint3fArray( "P" );
        std::vector<Point2f> uv = parameters.GetPoint2fArray( "uv" );

        if ( vertexIndices.empty( ) )
        {
            if ( P.size( ) == 4 )
                // single patch
                vertexIndices = { 0, 1, 2, 3 };
            else
            {
                Error( loc, "Vertex indices \"indices\" must be provided with "
                    "bilinear patch mesh shape." );
                return {};
            }
        }
        else if ( ( vertexIndices.size( ) % 4 ) != 0u )
        {
            Error( loc,
                "Number of vertex indices %d not a multiple of 4. Discarding %d "
                "excess.",
                int( vertexIndices.size( ) ), int( vertexIndices.size( ) % 4 ) );
            while ( ( vertexIndices.size( ) % 4 ) != 0u )
                vertexIndices.pop_back( );
        }

        if ( P.empty( ) )
        {
            Error( loc, "Vertex positions \"P\" must be provided with bilinear "
                "patch mesh shape." );
            return {};
        }

        if ( !uv.empty( ) && uv.size( ) != P.size( ) )
        {
            Error( loc, "Number of \"uv\"s for bilinear patch mesh must match \"P\"s. "
                "Discarding uvs." );
            uv = {};
        }

        std::vector<Normal3f> N = parameters.GetNormal3fArray( "N" );
        if ( !N.empty( ) && N.size( ) != P.size( ) )
        {
            Error( loc, "Number of \"N\"s for bilinear patch mesh must match \"P\"s. "
                "Discarding \"N\"s." );
            N = {};
        }

        for ( size_t i = 0; i < vertexIndices.size( ); ++i )
            if ( vertexIndices[ i ] >= P.size( ) )
            {
                Error( loc,
                    "Bilinear patch mesh has out of-bounds vertex index %d (%d "
                    "\"P\" "
                    "values were given. Discarding this mesh.",
                    vertexIndices[ i ], ( int )P.size( ) );
                return {};
            }

        std::vector<int> faceIndices = parameters.GetIntArray( "faceIndices" );
        if ( !faceIndices.empty( ) && faceIndices.size( ) != vertexIndices.size( ) / 4 )
        {
            Error( loc,
                "Number of face indices %d does not match number of bilinear "
                "patches %d. "
                "Discarding face indices.",
                int( faceIndices.size( ) ), int( vertexIndices.size( ) / 4 ) );
            faceIndices = {};
        }

        // Grab this before the vertexIndices are std::moved...
        size_t nBlps = vertexIndices.size( ) / 4;

        std::string filename =
            ResolveFilename( parameters.GetOneString( "emissionfilename", "" ) );
        PiecewiseConstant2D* imageDist = nullptr;
        if ( !filename.empty( ) )
        {
            if ( !uv.empty( ) )
                Error( loc, "\"emissionfilename\" is currently ignored for bilinear patches "
                    "if \"uv\" coordinates have been provided--sorry!" );
            else
            {
                ImageAndMetadata im = Image::Read( filename, alloc );
                // Account for v inversion in DiffuseAreaLight lookup, which in turn is there
                // to match ImageTexture...
                im.image.FlipY( );
                Bounds2f domain = Bounds2f( Point2f( 0, 0 ), Point2f( 1, 1 ) );
                Array2D<Float> d = im.image.GetSamplingDistribution( );
                imageDist = alloc.new_object<PiecewiseConstant2D>( d, domain, alloc );
            }
        }

        return alloc.new_object<BilinearPatchMesh>(
            *renderFromObject, reverseOrientation, std::move( vertexIndices ), std::move( P ),
            std::move( N ), std::move( uv ), std::move( faceIndices ), imageDist, alloc );
    }

    pstdo::vector<Shape> BilinearPatch::CreatePatches( const BilinearPatchMesh* mesh,
        Allocator alloc )
    {
        static std::mutex allMeshesLock;
        allMeshesLock.lock( );
        NCHECK_LT( allMeshes->size( ), 1 << 31 );
        int meshIndex = int( allMeshes->size( ) );
        allMeshes->push_back( mesh );
        allMeshesLock.unlock( );

        pstdo::vector<Shape> blps( mesh->nPatches, alloc );
        BilinearPatch* patches = alloc.allocate_object<BilinearPatch>( mesh->nPatches );
        for ( int i = 0; i < mesh->nPatches; ++i )
        {
            alloc.construct( &patches[ i ], mesh, meshIndex, i );
            blps[ i ] = &patches[ i ];
        }

        return blps;
    }

    pstdo::vector<const BilinearPatchMesh*>* BilinearPatch::allMeshes;
#if defined(PBRT_BUILD_GPU_RENDERER)
    PBRT_GPU pstdo::vector<const BilinearPatchMesh*>* allBilinearMeshesGPU;
#endif

    void BilinearPatch::Init( Allocator alloc )
    {
        allMeshes = alloc.new_object<pstdo::vector<const BilinearPatchMesh*>>( alloc );
#if defined(PBRT_BUILD_GPU_RENDERER)
        if ( Options->useGPU )
            CUDA_CHECK( cudaMemcpyToSymbol( ( const void* )&allBilinearMeshesGPU,
                ( const void* )&allMeshes,
                sizeof( allMeshes ) ) );
#endif
    }

    NSTAT_MEMORY_COUNTER( "Memory/Bilinear patches", blpBytes );

    // BilinearPatch Method Definitions
    BilinearPatch::BilinearPatch( const BilinearPatchMesh* mesh, int meshIndex, int blpIndex )
        : meshIndex( meshIndex ), blpIndex( blpIndex )
    {
        blpBytes += sizeof( *this );
        // Store area of bilinear patch in _area_
        // Get bilinear patch vertices in _p00_, _p01_, _p10_, and _p11_
        const int* v = &mesh->vertexIndices[ 4 * blpIndex ];
        Point3f::Simd p00 = mesh->p[ v[ 0 ] ], p10 = mesh->p[ v[ 1 ] ];
        Point3f::Simd p01 = mesh->p[ v[ 2 ] ], p11 = mesh->p[ v[ 3 ] ];

        if ( IsRectangle( mesh ) )
            area = ScalarDistance( p00, p01 ) * ScalarDistance( p00, p10 );
        else
        {
            // Compute approximate area of bilinear patch
            // FIXME: it would be good to skip this for flat patches, or to
            // be adaptive based on curvature in some manner
            constexpr int na = 3;
            Point3f::Simd p[ na + 1 ][ na + 1 ];
            for ( int i = 0; i <= na; ++i )
            {
                Float u = Float( i ) / Float( na );
                for ( int j = 0; j <= na; ++j )
                {
                    Float v = Float( j ) / Float( na );
                    p[ i ][ j ] = Lerp2( u, Lerp2( v, p00, p01 ), Lerp2( v, p10, p11 ) );
                }
            }
            area = 0;
            for ( int i = 0; i < na; ++i )
                for ( int j = 0; j < na; ++j )
                    area += 0.5f * ScalarLength( Cross( p[ i + 1 ][ j + 1 ] - p[ i ][ j ],
                        p[ i + 1 ][ j ] - p[ i ][ j + 1 ] ) );
        }
    }

    PBRT_CPU_GPU Bounds3f BilinearPatch::Bounds( ) const
    {
        const BilinearPatchMesh* mesh = GetMesh( );
        // Get bilinear patch vertices in _p00_, _p01_, _p10_, and _p11_
        const int* v = &mesh->vertexIndices[ 4 * blpIndex ];
        Point3f::Simd p00 = mesh->p[ v[ 0 ] ], p10 = mesh->p[ v[ 1 ] ];
        Point3f::Simd p01 = mesh->p[ v[ 2 ] ], p11 = mesh->p[ v[ 3 ] ];

        return Union( Bounds3f( p00, p01 ), Bounds3f( p10, p11 ) );
    }

    PBRT_CPU_GPU DirectionCone BilinearPatch::NormalBounds( ) const
    {
        const BilinearPatchMesh* mesh = GetMesh( );
        // Get bilinear patch vertices in _p00_, _p01_, _p10_, and _p11_
        const int* v = &mesh->vertexIndices[ 4 * blpIndex ];
        Point3f::Simd p00 = mesh->p[ v[ 0 ] ], p10 = mesh->p[ v[ 1 ] ];
        Point3f::Simd p01 = mesh->p[ v[ 2 ] ], p11 = mesh->p[ v[ 3 ] ];

        // If patch is a triangle, return bounds for single surface normal
        if ( p00 == p10 || p10 == p11 || p11 == p01 || p01 == p00 )
        {
            Vector3f::Simd dpdu = Lerp2( 0.5f, p10, p11 ) - Lerp2( 0.5f, p00, p01 );
            Vector3f::Simd dpdv = Lerp2( 0.5f, p01, p11 ) - Lerp2( 0.5f, p00, p10 );
            Vector3f::Simd n = Normalize( Cross( dpdu, dpdv ) );
            if ( mesh->n )
            {
                Normal3f::Simd ns =
                    ( mesh->n[ v[ 0 ] ] + mesh->n[ v[ 1 ] ] + mesh->n[ v[ 2 ] ] + mesh->n[ v[ 3 ] ] ) / 4;
                n = FaceForward( n, ns );
            }
            else if ( mesh->reverseOrientation ^ mesh->transformSwapsHandedness )
                n = -n;
            return DirectionCone( n );
        }

        // Compute bilinear patch normal _n00_ at $(0,0)$
        Vector3f::Simd n00 = Normalize( Cross( p10 - p00, p01 - p00 ) );
        if ( mesh->n )
            n00 = FaceForward( n00, mesh->n[ v[ 0 ] ] );
        else if ( mesh->reverseOrientation ^ mesh->transformSwapsHandedness )
            n00 = -n00;

        // Compute bilinear patch normals _n10_, _n01_, and _n11_
        Vector3f::Simd n10 = Normalize( Cross( p11 - p10, p00 - p10 ) );
        Vector3f::Simd n01 = Normalize( Cross( p00 - p01, p11 - p01 ) );
        Vector3f::Simd n11 = Normalize( Cross( p01 - p11, p10 - p11 ) );
        if ( mesh->n )
        {
            n10 = FaceForward( n10, mesh->n[ v[ 1 ] ] );
            n01 = FaceForward( n01, mesh->n[ v[ 2 ] ] );
            n11 = FaceForward( n11, mesh->n[ v[ 3 ] ] );
        }
        else if ( mesh->reverseOrientation ^ mesh->transformSwapsHandedness )
        {
            n10 = -n10;
            n01 = -n01;
            n11 = -n11;
        }

        // Compute average normal and return normal bounds for patch
        Vector3f::Simd n = Normalize( n00 + n10 + n01 + n11 );
        Float cosTheta = std::min( { ScalarDot( n, n00 ), ScalarDot( n, n01 ), ScalarDot( n, n10 ), ScalarDot( n, n11 ) } );
        return DirectionCone( n, Clamp( cosTheta, -1, 1 ) );
    }

    pstdo::optional<ShapeIntersection> BilinearPatch::Intersect( const Ray& ray, Float tMax ) const
    {
        const BilinearPatchMesh* mesh = GetMesh( );
        // Get bilinear patch vertices in _p00_, _p01_, _p10_, and _p11_
        const int* v = &mesh->vertexIndices[ 4 * blpIndex ];
        Point3f::Simd p00 = mesh->p[ v[ 0 ] ], p10 = mesh->p[ v[ 1 ] ];
        Point3f::Simd p01 = mesh->p[ v[ 2 ] ], p11 = mesh->p[ v[ 3 ] ];

        pstdo::optional<BilinearIntersection> blpIsect =
            IntersectBilinearPatch( ray, tMax, p00, p10, p01, p11 );
        if ( !blpIsect )
            return {};
        SurfaceInteraction intr =
            InteractionFromIntersection( mesh, blpIndex, blpIsect->uv, ray.time, -ray.d );
        return ShapeIntersection{ intr, blpIsect->t };
    }

    PBRT_CPU_GPU bool BilinearPatch::IntersectP( const Ray& ray, Float tMax ) const
    {
        const BilinearPatchMesh* mesh = GetMesh( );
        // Get bilinear patch vertices in _p00_, _p01_, _p10_, and _p11_
        const int* v = &mesh->vertexIndices[ 4 * blpIndex ];
        Point3f::Simd p00 = mesh->p[ v[ 0 ] ], p10 = mesh->p[ v[ 1 ] ];
        Point3f::Simd p01 = mesh->p[ v[ 2 ] ], p11 = mesh->p[ v[ 3 ] ];

        return IntersectBilinearPatch( ray, tMax, p00, p10, p01, p11 ).has_value( );
    }

    pstdo::optional<ShapeSample> BilinearPatch::Sample( Point2f u ) const
    {
        const BilinearPatchMesh* mesh = GetMesh( );
        // Get bilinear patch vertices in _p00_, _p01_, _p10_, and _p11_
        const int* v = &mesh->vertexIndices[ 4 * blpIndex ];
        Point3f::Simd p00 = mesh->p[ v[ 0 ] ], p10 = mesh->p[ v[ 1 ] ];
        Point3f::Simd p01 = mesh->p[ v[ 2 ] ], p11 = mesh->p[ v[ 3 ] ];

        // Sample bilinear patch parametric $(u,v)$ coordinates
        Float pdf = 1;
        Point2f uv;
        if ( mesh->imageDistribution )
            uv = mesh->imageDistribution->Sample( u, &pdf );
        else if ( !IsRectangle( mesh ) )
        {
            // Sample patch $(u,v)$ with approximate uniform area sampling
            // Initialize _w_ array with differential area at bilinear patch corners
            pstdo::array<Float, 4> w = {
                ScalarLength( Cross( p10 - p00, p01 - p00 ) ), ScalarLength( Cross( p10 - p00, p11 - p10 ) ),
                ScalarLength( Cross( p01 - p00, p11 - p01 ) ), ScalarLength( Cross( p11 - p10, p11 - p01 ) ) };

            uv = SampleBilinear( u, w );
            pdf = BilinearPDF( uv, w );

        }
        else
            uv = u;

        // Compute bilinear patch geometric quantities at sampled $(u,v)$
        // Compute $\pt{}$, $\dpdu$, and $\dpdv$ for sampled $(u,v)$
        Point3f::Simd pu0 = Lerp2( uv[ 1 ], p00, p01 ), pu1 = Lerp2( uv[ 1 ], p10, p11 );
        Point3f::Simd p = Lerp2( uv[ 0 ], pu0, pu1 );
        Vector3f::Simd dpdu = pu1 - pu0;
        Vector3f::Simd dpdv = Lerp2( uv[ 0 ], p01, p11 ) - Lerp2( uv[ 0 ], p00, p10 );
        if ( ScalarLengthSquared( dpdu ) == 0 || ScalarLengthSquared( dpdv ) == 0 )
            return {};

        Point2f st = uv;
        if ( mesh->uv )
        {
            // Compute texture coordinates for bilinear patch intersection point
            Point2f uv00 = mesh->uv[ v[ 0 ] ], uv10 = mesh->uv[ v[ 1 ] ];
            Point2f uv01 = mesh->uv[ v[ 2 ] ], uv11 = mesh->uv[ v[ 3 ] ];
            st = Lerp2( uv[ 0 ], Lerp2( uv[ 1 ], uv00, uv01 ), Lerp2( uv[ 1 ], uv10, uv11 ) );
        }
        // Compute surface normal for sampled bilinear patch $(u,v)$
        Normal3f::Simd n = Normal3f::Simd( Normalize( Cross( dpdu, dpdv ) ) );
        // Flip normal at sampled $(u,v)$ if necessary
        if ( mesh->n )
        {
            Normal3f::Simd n00 = mesh->n[ v[ 0 ] ], n10 = mesh->n[ v[ 1 ] ];
            Normal3f::Simd n01 = mesh->n[ v[ 2 ] ], n11 = mesh->n[ v[ 3 ] ];
            Normal3f::Simd ns = Lerp2( uv[ 0 ], Lerp2( uv[ 1 ], n00, n01 ), Lerp2( uv[ 1 ], n10, n11 ) );
            n = FaceForward( n, ns );
        }
        else if ( mesh->reverseOrientation ^ mesh->transformSwapsHandedness )
            n = -n;

        // Compute _pError_ for sampled bilinear patch $(u,v)$
        Point3f::Simd pAbsSum = Abs( p00 ) + Abs( p01 ) + Abs( p10 ) + Abs( p11 );
        Vector3f pError = gamma( 6 ) * Vector3f::Simd( pAbsSum );

        // Return _ShapeSample_ for sampled bilinear patch point
        return ShapeSample{ Interaction( Point3fi( p, pError ), n, st ),
                           pdf / ScalarLength( Cross( dpdu, dpdv ) ) };
    }

    Float BilinearPatch::PDF( const Interaction& intr ) const
    {
        const BilinearPatchMesh* mesh = GetMesh( );
        // Get bilinear patch vertices in _p00_, _p01_, _p10_, and _p11_
        const int* v = &mesh->vertexIndices[ 4 * blpIndex ];
        Point3f::Simd p00 = mesh->p[ v[ 0 ] ], p10 = mesh->p[ v[ 1 ] ];
        Point3f::Simd p01 = mesh->p[ v[ 2 ] ], p11 = mesh->p[ v[ 3 ] ];

        // Compute parametric $(u,v)$ of point on bilinear patch
        Point2f uv = intr.uv;
        if ( mesh->uv )
        {
            Point2f uv00 = mesh->uv[ v[ 0 ] ], uv10 = mesh->uv[ v[ 1 ] ];
            Point2f uv01 = mesh->uv[ v[ 2 ] ], uv11 = mesh->uv[ v[ 3 ] ];
            uv = InvertBilinear( uv, { uv00, uv10, uv01, uv11 } );
        }

        // Compute PDF for sampling the $(u,v)$ coordinates given by _intr.uv_
        Float pdf;
        if ( mesh->imageDistribution )
            pdf = mesh->imageDistribution->PDF( uv );
        else if ( !IsRectangle( mesh ) )
        {
            // Initialize _w_ array with differential area at bilinear patch corners
            pstdo::array<Float, 4> w = {
                ScalarLength( Cross( p10 - p00, p01 - p00 ) ), ScalarLength( Cross( p10 - p00, p11 - p10 ) ),
                ScalarLength( Cross( p01 - p00, p11 - p01 ) ), ScalarLength( Cross( p11 - p10, p11 - p01 ) ) };

            pdf = BilinearPDF( uv, w );
        }
        else
            pdf = 1;

        // Find $\dpdu$ and $\dpdv$ at bilinear patch $(u,v)$
        Point3f::Simd pu0 = Lerp2( uv[ 1 ], p00, p01 ), pu1 = Lerp2( uv[ 1 ], p10, p11 );
        Vector3f::Simd dpdu = pu1 - pu0;
        Vector3f::Simd dpdv = Lerp2( uv[ 0 ], p01, p11 ) - Lerp2( uv[ 0 ], p00, p10 );

        // Return final bilinear patch area sampling PDF
        return pdf / ScalarLength( Cross( dpdu, dpdv ) );
    }

    pstdo::optional<ShapeSample> BilinearPatch::Sample( const ShapeSampleContext& ctx, Point2f u ) const
    {
        const BilinearPatchMesh* mesh = GetMesh( );
        // Get bilinear patch vertices in _p00_, _p01_, _p10_, and _p11_
        const int* v = &mesh->vertexIndices[ 4 * blpIndex ];
        Point3f::Simd p00 = mesh->p[ v[ 0 ] ], p10 = mesh->p[ v[ 1 ] ];
        Point3f::Simd p01 = mesh->p[ v[ 2 ] ], p11 = mesh->p[ v[ 3 ] ];

        // Sample bilinear patch with respect to solid angle from reference point
        Vector3f::Simd v00 = Normalize( p00 - ctx.p( ) ), v10 = Normalize( p10 - ctx.p( ) );
        Vector3f::Simd v01 = Normalize( p01 - ctx.p( ) ), v11 = Normalize( p11 - ctx.p( ) );
        if ( !IsRectangle( mesh ) || mesh->imageDistribution ||
            SphericalQuadArea( v00, v10, v11, v01 ) <= MinSphericalSampleArea )
        {
            // Sample shape by area and compute incident direction _wi_
            pstdo::optional<ShapeSample> ss = Sample( u );
            NDCHECK( ss.has_value( ) );
            ss->intr.time = ctx.time;
            Vector3f::Simd wi = ss->intr.p( ) - ctx.p( );
            if ( ScalarLengthSquared( wi ) == 0 )
                return {};
            wi = Normalize( wi );

            // Convert area sampling PDF in _ss_ to solid angle measure
            ss->pdf /= ScalarAbsDot( ss->intr.n, -wi ) / ScalarDistanceSquared( ctx.p( ), ss->intr.p( ) );
            if ( IsInf( ss->pdf ) )
                return {};

            return ss;
        }
        // Sample direction to rectangular bilinear patch
        Float pdf = 1;
        // Warp uniform sample _u_ to account for incident $\cos\theta$ factor
        if ( ctx.ns != Normal3f( 0, 0, 0 ) )
        {
            // Compute $\cos\theta$ weights for rectangle seen from reference point
            pstdo::array<Float, 4> w =
                pstdo::array<Float, 4>{std::max<Float>( 0.01, ScalarAbsDot( v00, ctx.ns ) ),
                std::max<Float>( 0.01, ScalarAbsDot( v10, ctx.ns ) ),
                std::max<Float>( 0.01, ScalarAbsDot( v01, ctx.ns ) ),
                std::max<Float>( 0.01, ScalarAbsDot( v11, ctx.ns ) )};

            u = SampleBilinear( u, w );
            pdf *= BilinearPDF( u, w );
        }

        // Sample spherical rectangle at reference point
        Vector3f::Simd eu = p10 - p00, ev = p01 - p00;
        Float quadPDF;
        Point3f::Simd p = SampleSphericalRectangle( ctx.p( ), p00, eu, ev, u, &quadPDF );
        pdf *= quadPDF;

        // Compute $(u,v)$ and surface normal for sampled point on rectangle
        Point2f uv( ScalarDot( p - p00, eu ) / ScalarDistanceSquared( p10, p00 ),
            ScalarDot( p - p00, ev ) / ScalarDistanceSquared( p01, p00 ) );
        Normal3f::Simd n = Normal3f::Simd( Normalize( Cross( eu, ev ) ) );
        // Flip normal at sampled $(u,v)$ if necessary
        if ( mesh->n )
        {
            Normal3f::Simd n00 = mesh->n[ v[ 0 ] ], n10 = mesh->n[ v[ 1 ] ];
            Normal3f::Simd n01 = mesh->n[ v[ 2 ] ], n11 = mesh->n[ v[ 3 ] ];
            Normal3f::Simd ns = Lerp2( uv[ 0 ], Lerp2( uv[ 1 ], n00, n01 ), Lerp2( uv[ 1 ], n10, n11 ) );
            n = FaceForward( n, ns );
        }
        else if ( mesh->reverseOrientation ^ mesh->transformSwapsHandedness )
            n = -n;

        // Compute $(s,t)$ texture coordinates for sampled $(u,v)$
        Point2f st = uv;
        if ( mesh->uv )
        {
            // Compute texture coordinates for bilinear patch intersection point
            Point2f uv00 = mesh->uv[ v[ 0 ] ], uv10 = mesh->uv[ v[ 1 ] ];
            Point2f uv01 = mesh->uv[ v[ 2 ] ], uv11 = mesh->uv[ v[ 3 ] ];
            st = Lerp2( uv[ 0 ], Lerp2( uv[ 1 ], uv00, uv01 ), Lerp2( uv[ 1 ], uv10, uv11 ) );
        }

        return ShapeSample{ Interaction( p, n, ctx.time, st ), pdf };
    }

    Float BilinearPatch::PDF( const ShapeSampleContext& ctx, Vector3f::Simd wi ) const
    {
        const BilinearPatchMesh* mesh = GetMesh( );
        // Get bilinear patch vertices in _p00_, _p01_, _p10_, and _p11_
        const int* v = &mesh->vertexIndices[ 4 * blpIndex ];
        Point3f::Simd p00 = mesh->p[ v[ 0 ] ], p10 = mesh->p[ v[ 1 ] ];
        Point3f::Simd p01 = mesh->p[ v[ 2 ] ], p11 = mesh->p[ v[ 3 ] ];

        // Compute solid angle PDF for sampling bilinear patch from _ctx_
        // Intersect sample ray with shape geometry
        Ray ray = ctx.SpawnRay( wi );
        pstdo::optional<ShapeIntersection> isect = Intersect( ray );
        if ( !isect )
            return 0;

        Vector3f::Simd v00 = Normalize( p00 - ctx.p( ) ), v10 = Normalize( p10 - ctx.p( ) );
        Vector3f::Simd v01 = Normalize( p01 - ctx.p( ) ), v11 = Normalize( p11 - ctx.p( ) );
        if ( !IsRectangle( mesh ) || mesh->imageDistribution ||
            SphericalQuadArea( v00, v10, v11, v01 ) <= MinSphericalSampleArea )
        {
            // Return solid angle PDF for area-sampled bilinear patch
            Float pdf = PDF( isect->intr ) * ( ScalarDistanceSquared( ctx.p( ), isect->intr.p( ) ) /
                ScalarAbsDot( isect->intr.n, -wi ) );
            return IsInf( pdf ) ? 0 : pdf;

        }
        else
        {
            // Return PDF for sample in spherical rectangle
            Float pdf = 1 / SphericalQuadArea( v00, v10, v11, v01 );
            if ( ctx.ns != Normal3f::Simd( 0, 0, 0 ) )
            {
                // Compute $\cos\theta$ weights for rectangle seen from reference point
                pstdo::array<Float, 4> w =
                    pstdo::array<Float, 4>{std::max<Float>( 0.01, ScalarAbsDot( v00, ctx.ns ) ),
                    std::max<Float>( 0.01, ScalarAbsDot( v10, ctx.ns ) ),
                    std::max<Float>( 0.01, ScalarAbsDot( v01, ctx.ns ) ),
                    std::max<Float>( 0.01, ScalarAbsDot( v11, ctx.ns ) )};

                Point2f u = InvertSphericalRectangleSample( ctx.p( ), p00, p10 - p00, p01 - p00,
                    isect->intr.p( ) );
                return BilinearPDF( u, w ) * pdf;
            }
            else
                return pdf;
        }
    }

    std::string BilinearPatch::ToString( ) const
    {
        return StringPrintf( "[ BilinearPatch meshIndex: %d blpIndex: %d area: %f ]",
            meshIndex, blpIndex, area );
    }

    NSTAT_COUNTER( "Geometry/Spheres", nSpheres );
    NSTAT_COUNTER( "Geometry/Cylinders", nCylinders );
    NSTAT_COUNTER( "Geometry/Disks", nDisks );
    NSTAT_COUNTER( "Geometry/Triangles added from displacement mapping", displacedTrisDelta );

    pstdo::vector<Shape> Shape::Create(
        const std::string& name, const Transform* renderFromObject,
        const Transform* objectFromRender, bool reverseOrientation,
        const ParameterDictionary& parameters,
        const std::map<std::string, FloatTexture>& floatTextures, const FileLoc* loc,
        Allocator alloc )
    {
        pstdo::vector<Shape> shapes( alloc );
        if ( name == "sphere" )
        {
            shapes = { Sphere::Create( renderFromObject, objectFromRender, reverseOrientation,
                                     parameters, loc, alloc ) };
            ++nSpheres;
        }
        // Create remaining single _Shape_ types
        else if ( name == "cylinder" )
        {
            shapes = { Cylinder::Create( renderFromObject, objectFromRender, reverseOrientation,
                                       parameters, loc, alloc ) };
            ++nCylinders;
        }
        else if ( name == "disk" )
        {
            shapes = { Disk::Create( renderFromObject, objectFromRender, reverseOrientation,
                                   parameters, loc, alloc ) };
            ++nDisks;
        }
        else if ( name == "bilinearmesh" )
        {
            BilinearPatchMesh* mesh = BilinearPatch::CreateMesh(
                renderFromObject, reverseOrientation, parameters, loc, alloc );
            shapes = BilinearPatch::CreatePatches( mesh, alloc );
        }
        // Create multiple-_Shape_ types
        else if ( name == "curve" )
            shapes = Curve::Create( renderFromObject, objectFromRender, reverseOrientation,
                parameters, loc, alloc );
        else if ( name == "trianglemesh" )
        {
            TriangleMesh* mesh = Triangle::CreateMesh( renderFromObject, reverseOrientation,
                parameters, loc, alloc );
            shapes = Triangle::CreateTriangles( mesh, alloc );
        }
        else if ( name == "plymesh" )
        {
            std::string filename = ResolveFilename( parameters.GetOneString( "filename", "" ) );
            TriQuadMesh plyMesh = TriQuadMesh::ReadPLY( filename );

            Float edgeLength = parameters.GetOneFloat( "edgelength", 1.f );
            edgeLength *= Options->displacementEdgeScale;

            std::string displacementTexName = parameters.GetTexture( "displacement" );
            if ( !displacementTexName.empty( ) )
            {
                auto iter = floatTextures.find( displacementTexName );
                if ( iter == floatTextures.end( ) )
                    ErrorExit( loc, "%s: no such texture defined.", displacementTexName );
                FloatTexture displacement = iter->second;

                NLOG_VERBOSE( "Starting to displace mesh \"%s\" with \"%s\"", filename,
                    displacementTexName );

                int origTriCount = plyMesh.triIndices.size( ) / 3;
                plyMesh = plyMesh.Displace(
                    [ & ]( Point3f::Simd v0, Point3f::Simd v1 ) {
                        v0 = ( *renderFromObject )( v0 );
                        v1 = ( *renderFromObject )( v1 );
                        return ScalarDistance( v0, v1 );
                    },
                    edgeLength,
                    [ & ]( Point3f* p, const Normal3f* n, const Point2f* uv, int nVertices ) {
                        ParallelFor( 0, nVertices, [ = ]( int i ) {
                            TextureEvalContext ctx;
                            ctx.p = p[ i ];
                            ctx.uv = uv[ i ];
                            Float d = UniversalTextureEvaluator( )( displacement, ctx );
                            p[ i ] += Vector3f( d * n[ i ] );
                            } );
                    },
                    loc );

                NLOG_VERBOSE( "Finished displacing mesh \"%s\" with \"%s\" -> %d tris",
                    filename, displacementTexName, plyMesh.triIndices.size( ) / 3 );

                displacedTrisDelta += plyMesh.triIndices.size( ) / 3 - origTriCount;
            }

            if ( !plyMesh.triIndices.empty( ) )
            {
                TriangleMesh* mesh = alloc.new_object<TriangleMesh>(
                    *renderFromObject, reverseOrientation, plyMesh.triIndices, plyMesh.p,
                    std::vector<Vector3f>( ), plyMesh.n, plyMesh.uv, plyMesh.faceIndices,
                    alloc );
                shapes = Triangle::CreateTriangles( mesh, alloc );
            }

            if ( !plyMesh.quadIndices.empty( ) )
            {
                BilinearPatchMesh* mesh = alloc.new_object<BilinearPatchMesh>(
                    *renderFromObject, reverseOrientation, plyMesh.quadIndices, plyMesh.p,
                    plyMesh.n, plyMesh.uv, plyMesh.faceIndices, nullptr /* image dist */,
                    alloc );
                pstdo::vector<Shape> quadMesh = BilinearPatch::CreatePatches( mesh, alloc );
                shapes.insert( shapes.end( ), quadMesh.begin( ), quadMesh.end( ) );
            }
        }
        else if ( name == "loopsubdiv" )
        {
            int nLevels = parameters.GetOneInt( "levels", 3 );
            std::vector<int> vertexIndices = parameters.GetIntArray( "indices" );
            if ( vertexIndices.empty( ) )
                ErrorExit( loc, "Vertex indices \"indices\" not provided for "
                    "LoopSubdiv shape." );

            std::vector<Point3f> P = parameters.GetPoint3fArray( "P" );
            if ( P.empty( ) )
                ErrorExit( loc, "Vertex positions \"P\" not provided for LoopSubdiv shape." );

            // don't actually use this for now...
            std::string scheme = parameters.GetOneString( "scheme", "loop" );

            TriangleMesh* mesh = LoopSubdivide( renderFromObject, reverseOrientation, nLevels,
                vertexIndices, P, alloc );

            shapes = Triangle::CreateTriangles( mesh, alloc );
        }
        else
            ErrorExit( loc, "%s: shape type unknown.", name );

        if ( shapes.empty( ) )
            ErrorExit( loc, "%s: unable to create shape.", name );

        return shapes;
    }

    std::string Shape::ToString( ) const
    {
        if ( !ptr( ) )
            return "(nullptr)";

        auto tostr = [ & ]( auto ptr ) { return ptr->ToString( ); };
        return DispatchCPU( tostr );
    }

    // Shape Method Definitions
    std::string ShapeSample::ToString( ) const
    {
        return StringPrintf( "[ ShapeSample intr: %s pdf: %f ]", intr, pdf );
    }

    std::string ShapeIntersection::ToString( ) const
    {
        return StringPrintf( "[ ShapeIntersection intr: %s tHit: %f ]", intr, tHit );
    }

}