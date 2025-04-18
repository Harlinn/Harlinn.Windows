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


#include <pbrto/util/NewTransform.h>

#include <pbrto/NewInteraction.h>
#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewError.h>
#include <pbrto/util/NewMath.h>

#include <algorithm>
#include <cmath>
#include <memory>

namespace pbrto
{

    // Transform Function Definitions
    // clang-format off
    PBRTO_EXPORT
    Transform Translate( const Vector3f delta )
    {
        SquareMatrix<4> m( 1, 0, 0, delta.x,
            0, 1, 0, delta.y,
            0, 0, 1, delta.z,
            0, 0, 0, 1 );
        SquareMatrix<4> minv( 1, 0, 0, -delta.x,
            0, 1, 0, -delta.y,
            0, 0, 1, -delta.z,
            0, 0, 0, 1 );
        return Transform( m, minv );
    }
    // clang-format on

    // clang-format off
    PBRTO_EXPORT
    Transform Scale( Float x, Float y, Float z )
    {
        SquareMatrix<4> m( x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, 0,
            0, 0, 0, 1 );
        SquareMatrix<4> minv( 1 / x, 0, 0, 0,
            0, 1 / y, 0, 0,
            0, 0, 1 / z, 0,
            0, 0, 0, 1 );
        return Transform( m, minv );
    }
    // clang-format on

    // clang-format off
    PBRTO_EXPORT
    Transform RotateX( Float theta )
    {
        Float sinTheta;
        Float cosTheta;
        SinCos( Deg2Rad( theta ), &sinTheta, &cosTheta );

        SquareMatrix<4> m( 1, 0, 0, 0,
            0, cosTheta, -sinTheta, 0,
            0, sinTheta, cosTheta, 0,
            0, 0, 0, 1 );
        return Transform( m, Transpose( m ) );
    }
    // clang-format on

    // clang-format off
    PBRTO_EXPORT
    Transform RotateY( Float theta )
    {
        Float sinTheta;
        Float cosTheta;
        SinCos( Deg2Rad( theta ), &sinTheta, &cosTheta );

        SquareMatrix<4> m( cosTheta, 0, sinTheta, 0,
            0, 1, 0, 0,
            -sinTheta, 0, cosTheta, 0,
            0, 0, 0, 1 );
        return Transform( m, Transpose( m ) );
    }
    PBRTO_EXPORT
    Transform RotateZ( Float theta )
    {
        Float sinTheta;
        Float cosTheta;
        SinCos( Deg2Rad( theta ), &sinTheta, &cosTheta );

        SquareMatrix<4> m( cosTheta, -sinTheta, 0, 0,
            sinTheta, cosTheta, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1 );
        return Transform( m, Transpose( m ) );
    }
    // clang-format on

    PBRTO_EXPORT
    Transform LookAt( Point3f pos, Point3f look, Vector3f up )
    {
        SquareMatrix<4> worldFromCamera;
        // Initialize fourth column of viewing matrix
        worldFromCamera[ 0 ][ 3 ] = pos.x;
        worldFromCamera[ 1 ][ 3 ] = pos.y;
        worldFromCamera[ 2 ][ 3 ] = pos.z;
        worldFromCamera[ 3 ][ 3 ] = 1;

        // Initialize first three columns of viewing matrix
        Vector3f dir = Normalize( look - pos );
        if ( ScalarLength( Cross( Normalize( up ), dir ) ) == 0 )
            NLOG_FATAL( "LookAt: \"up\" vector (%f, %f, %f) and viewing direction "
                "(%f, %f, %f) "
                "passed to LookAt are pointing in the same direction.",
                up.x, up.y, up.z, dir.x, dir.y, dir.z );
        Vector3f right = Normalize( Cross( Normalize( up ), dir ) );
        Vector3f newUp = Cross( dir, right );
        worldFromCamera[ 0 ][ 0 ] = right.x;
        worldFromCamera[ 1 ][ 0 ] = right.y;
        worldFromCamera[ 2 ][ 0 ] = right.z;
        worldFromCamera[ 3 ][ 0 ] = 0.;
        worldFromCamera[ 0 ][ 1 ] = newUp.x;
        worldFromCamera[ 1 ][ 1 ] = newUp.y;
        worldFromCamera[ 2 ][ 1 ] = newUp.z;
        worldFromCamera[ 3 ][ 1 ] = 0.;
        worldFromCamera[ 0 ][ 2 ] = dir.x;
        worldFromCamera[ 1 ][ 2 ] = dir.y;
        worldFromCamera[ 2 ][ 2 ] = dir.z;
        worldFromCamera[ 3 ][ 2 ] = 0.;

        SquareMatrix<4> cameraFromWorld = Inverse( worldFromCamera );
        return Transform( cameraFromWorld, worldFromCamera );
    }

    PBRTO_EXPORT
    Transform Orthographic( Float zNear, Float zFar )
    {
        return Scale( 1, 1, 1 / ( zFar - zNear ) ) * Translate( Vector3f( 0, 0, -zNear ) );
    }

    PBRTO_EXPORT
    Transform Perspective( Float fov, Float n, Float f )
    {
        // Perform projective divide for perspective projection
        // clang-format off
        SquareMatrix<4> persp( 1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, f / ( f - n ), -f * n / ( f - n ),
            0, 0, 1, 0 );
        // clang-format on

        // Scale canonical perspective view to specified field of view
        Float invTanAng = 1 / Math::Tan( Radians( fov ) / 2 );
        return Scale( invTanAng, invTanAng, 1 ) * Transform( persp );
    }

    // Transform Method Definitions
    Bounds3f Transform::operator()( const Bounds3f& b ) const
    {
        Bounds3f bt;
        for ( int i = 0; i < 8; ++i )
            bt = Union( bt, ( *this )( b.Corner( i ) ) );
        return bt;
    }

    bool Transform::SwapsHandedness( ) const
    {
        SquareMatrix<3>::Simd s( m_.simd );
        s = Transpose( s );
        return ScalarDeterminant( s ) < 0;
    }

    Transform::operator Quaternion( ) const
    {
        Quaternion quat = Quaternion::FromMatrix( m_ );
        return quat;
    }

    void Transform::Decompose( Vector3f* T, SquareMatrix<4>* R, SquareMatrix<4>* S ) const
    {
        SquareMatrix<4> M = Transpose( m_ );

        // Extract translation _T_ from transformation matrix
        T->x = M[ 0 ][ 3 ];
        T->y = M[ 1 ][ 3 ];
        T->z = M[ 2 ][ 3 ];

        // Compute new transformation matrix _M_ without translation
        
        for ( int i = 0; i < 3; ++i )
            M[ i ][ 3 ] = M[ 3 ][ i ] = 0.f;
        M[ 3 ][ 3 ] = 1.f;

        // Extract rotation _R_ from transformation matrix
        Float norm;
        int count = 0;
        *R = M;
        do
        {
            // Compute next matrix _Rnext_ in series
            SquareMatrix<4> Rit = Inverse( Transpose( *R ) );
            SquareMatrix<4> Rnext = ( *R + Rit ) / 2;

            // Compute norm of difference between _R_ and _Rnext_
            norm = 0;
            for ( int i = 0; i < 3; ++i )
            {
                Float n = std::abs( ( *R )[ i ][ 0 ] - Rnext[ i ][ 0 ] ) +
                    std::abs( ( *R )[ i ][ 1 ] - Rnext[ i ][ 1 ] ) +
                    std::abs( ( *R )[ i ][ 2 ] - Rnext[ i ][ 2 ] );
                norm = std::max( norm, n );
            }

            *R = Rnext;
        } while ( ++count < 100 && norm > .0001 );
        // XXX TODO FIXME deal with flip...

        // Compute scale _S_ using rotation and original matrix
        *S = Inverse( *R ) * M;
    }

    SurfaceInteraction Transform::operator()( const SurfaceInteraction& si ) const
    {
        SurfaceInteraction ret;
        const Transform& t = *this;
        ret.pi = t( si.pi );
        // Transform remaining members of _SurfaceInteraction_
        ret.n = Normalize( t( si.n ) );
        ret.wo = Normalize( t( si.wo ) );
        ret.time = si.time;
        ret.mediumInterface = si.mediumInterface;
        ret.uv = si.uv;
        ret.dpdu = t( si.dpdu );
        ret.dpdv = t( si.dpdv );
        ret.dndu = t( si.dndu );
        ret.dndv = t( si.dndv );
        ret.shading.n = Normalize( t( si.shading.n ) );
        ret.shading.dpdu = t( si.shading.dpdu );
        ret.shading.dpdv = t( si.shading.dpdv );
        ret.shading.dndu = t( si.shading.dndu );
        ret.shading.dndv = t( si.shading.dndv );
        ret.dudx = si.dudx;
        ret.dvdx = si.dvdx;
        ret.dudy = si.dudy;
        ret.dvdy = si.dvdy;
        ret.dpdx = t( si.dpdx );
        ret.dpdy = t( si.dpdy );
        ret.material = si.material;
        ret.areaLight = si.areaLight;
        //    ret.n = FaceForward(ret.n, ret.shading.n);
        ret.shading.n = FaceForward( ret.shading.n, ret.n );
        ret.faceIndex = si.faceIndex;

        return ret;
    }

    Point3fi Transform::ApplyInverse( const Point3fi& p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;
        using Point3Traits = Point3<float>::Traits;

        constexpr Float gammaValue = gamma( 3 );
        constexpr Float gammaPlusOneValue = gammaValue + 1.f;

        Traits::SIMDType gammaVector = Point3Traits::Set( gammaValue, gammaValue, gammaValue );
        Traits::SIMDType gammaVectorPlussOne = Point3Traits::Set( gammaPlusOneValue, gammaPlusOneValue, gammaPlusOneValue );

        Point3Simd point( static_cast< Point3<float> >( p ) );

        const auto& matrix = mInv_;

        Point3Simd result = Traits::TransformPoint( point.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] );

        Point3Simd vOutError;
        if ( p.IsExact( ) )
        {
            vOutError.simd = Traits::Mul( gammaVector, Traits::Abs( result.simd ) );
        }
        else
        {
            Traits::SIMDType vInError = Point3Traits::Load( p.Error( ).values );
            vOutError.simd = Traits::Add( Traits::Mul( gammaVectorPlussOne, Traits::Abs( Traits::TransformPoint( vInError, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] ) ) ),
                Traits::Mul( gammaVector, Traits::Abs( result.simd ) ) );
        }

        return Point3fi( Point3f( result ), Point3f( vOutError ) );

    }

    Interaction Transform::operator()( const Interaction& in ) const
    {
        Interaction ret;
        ret.pi = ( *this )( in.pi );
        ret.n = ( *this )( in.n );
        if ( ScalarLengthSquared( ret.n ) > 0 )
            ret.n = Normalize( ret.n );
        ret.uv = in.uv;
        ret.wo = ( *this )( in.wo );
        if ( ScalarLengthSquared( ret.wo ) > 0 )
            ret.wo = Normalize( ret.wo );
        ret.time = in.time;
        ret.mediumInterface = in.mediumInterface;
        return ret;
    }

    Interaction Transform::ApplyInverse( const Interaction& in ) const
    {
        Interaction ret;
        Transform t = Inverse( *this );
        ret.pi = t( in.pi );
        ret.n = t( in.n );
        if ( ScalarLengthSquared( ret.n ) > 0 )
            ret.n = Normalize( ret.n );
        ret.uv = in.uv;
        ret.wo = t( in.wo );
        if ( ScalarLengthSquared( ret.wo ) > 0 )
            ret.wo = Normalize( ret.wo );
        ret.time = in.time;
        ret.mediumInterface = in.mediumInterface;
        return ret;
    }

    SurfaceInteraction Transform::ApplyInverse( const SurfaceInteraction& si ) const
    {
        SurfaceInteraction ret;
        ret.pi = ( *this )( si.pi );

        // Transform remaining members of _SurfaceInteraction_
        Transform t = Inverse( *this );
        ret.n = Normalize( t( si.n ) );
        ret.wo = Normalize( t( si.wo ) );
        ret.time = si.time;
        ret.mediumInterface = si.mediumInterface;
        ret.uv = si.uv;
        ret.dpdu = t( si.dpdu );
        ret.dpdv = t( si.dpdv );
        ret.dndu = t( si.dndu );
        ret.dndv = t( si.dndv );
        ret.shading.n = Normalize( t( si.shading.n ) );
        ret.shading.dpdu = t( si.shading.dpdu );
        ret.shading.dpdv = t( si.shading.dpdv );
        ret.shading.dndu = t( si.shading.dndu );
        ret.shading.dndv = t( si.shading.dndv );
        ret.dudx = si.dudx;
        ret.dvdx = si.dvdx;
        ret.dudy = si.dudy;
        ret.dvdy = si.dvdy;
        ret.dpdx = t( si.dpdx );
        ret.dpdy = t( si.dpdy );
        ret.material = si.material;
        ret.areaLight = si.areaLight;
        //    ret.n = FaceForward(ret.n, ret.shading.n);
        ret.shading.n = FaceForward( ret.shading.n, ret.n );
        ret.faceIndex = si.faceIndex;
        return ret;
    }

    std::string Transform::ToString( ) const
    {
        SquareMatrix<4> m( Transpose( m_ ) );
        SquareMatrix<4> mInv( Transpose( mInv_ ) );

        return StringPrintf( "[ m: %s mInv: %s ]", m, mInv );
    }

    // AnimatedTransform Method Definitions
    AnimatedTransform::AnimatedTransform( const Transform& startTransform, Float startTime,
        const Transform& endTransform, Float endTime )
        : startTransform( startTransform ),
        endTransform( endTransform ),
        startTime( startTime ),
        endTime( endTime ),
        actuallyAnimated( startTransform != endTransform )
    {
        if ( !actuallyAnimated )
            return;
        // Decompose start and end transformations
        SquareMatrix<4> Rm;
        startTransform.Decompose( &T[ 0 ], &Rm, &S[ 0 ] );
        R[ 0 ] = Quaternion( Transform( Rm ) );
        endTransform.Decompose( &T[ 1 ], &Rm, &S[ 1 ] );
        R[ 1 ] = Quaternion( Transform( Rm ) );
        // Flip _R[1]_ if needed to select shortest path
        if ( ScalarDot( R[ 0 ], R[ 1 ] ) < 0 )
            R[ 1 ] = -R[ 1 ];

        hasRotation = ScalarDot( R[ 0 ], R[ 1 ] ) < 0.9995f;
        // Compute terms of motion derivative function
        if ( hasRotation )
        {
            Float cosTheta = ScalarDot( R[ 0 ], R[ 1 ] );
            Float theta = SafeACos( cosTheta );
            Quaternion qperp = Normalize( R[ 1 ] - R[ 0 ] * cosTheta );

            Float t0x = T[ 0 ].x;
            Float t0y = T[ 0 ].y;
            Float t0z = T[ 0 ].z;
            Float t1x = T[ 1 ].x;
            Float t1y = T[ 1 ].y;
            Float t1z = T[ 1 ].z;
            Float q0x = R[ 0 ].v.x;
            Float q0y = R[ 0 ].v.y;
            Float q0z = R[ 0 ].v.z;
            Float q0w = R[ 0 ].w;
            Float qperpx = qperp.v.x;
            Float qperpy = qperp.v.y;
            Float qperpz = qperp.v.z;
            Float qperpw = qperp.w;
            Float s000 = S[ 0 ][ 0 ][ 0 ];
            Float s001 = S[ 0 ][ 0 ][ 1 ];
            Float s002 = S[ 0 ][ 0 ][ 2 ];
            Float s010 = S[ 0 ][ 1 ][ 0 ];
            Float s011 = S[ 0 ][ 1 ][ 1 ];
            Float s012 = S[ 0 ][ 1 ][ 2 ];
            Float s020 = S[ 0 ][ 2 ][ 0 ];
            Float s021 = S[ 0 ][ 2 ][ 1 ];
            Float s022 = S[ 0 ][ 2 ][ 2 ];
            Float s100 = S[ 1 ][ 0 ][ 0 ];
            Float s101 = S[ 1 ][ 0 ][ 1 ];
            Float s102 = S[ 1 ][ 0 ][ 2 ];
            Float s110 = S[ 1 ][ 1 ][ 0 ];
            Float s111 = S[ 1 ][ 1 ][ 1 ];
            Float s112 = S[ 1 ][ 1 ][ 2 ];
            Float s120 = S[ 1 ][ 2 ][ 0 ];
            Float s121 = S[ 1 ][ 2 ][ 1 ];
            Float s122 = S[ 1 ][ 2 ][ 2 ];

            c1[ 0 ] = DerivativeTerm(
                -t0x + t1x,
                ( -1 + q0y * q0y + q0z * q0z + qperpy * qperpy + qperpz * qperpz ) * s000 +
                q0w * q0z * s010 - qperpx * qperpy * s010 + qperpw * qperpz * s010 -
                q0w * q0y * s020 - qperpw * qperpy * s020 - qperpx * qperpz * s020 +
                s100 - q0y * q0y * s100 - q0z * q0z * s100 - qperpy * qperpy * s100 -
                qperpz * qperpz * s100 - q0w * q0z * s110 + qperpx * qperpy * s110 -
                qperpw * qperpz * s110 + q0w * q0y * s120 + qperpw * qperpy * s120 +
                qperpx * qperpz * s120 +
                q0x * ( -( q0y * s010 ) - q0z * s020 + q0y * s110 + q0z * s120 ),
                ( -1 + q0y * q0y + q0z * q0z + qperpy * qperpy + qperpz * qperpz ) * s001 +
                q0w * q0z * s011 - qperpx * qperpy * s011 + qperpw * qperpz * s011 -
                q0w * q0y * s021 - qperpw * qperpy * s021 - qperpx * qperpz * s021 +
                s101 - q0y * q0y * s101 - q0z * q0z * s101 - qperpy * qperpy * s101 -
                qperpz * qperpz * s101 - q0w * q0z * s111 + qperpx * qperpy * s111 -
                qperpw * qperpz * s111 + q0w * q0y * s121 + qperpw * qperpy * s121 +
                qperpx * qperpz * s121 +
                q0x * ( -( q0y * s011 ) - q0z * s021 + q0y * s111 + q0z * s121 ),
                ( -1 + q0y * q0y + q0z * q0z + qperpy * qperpy + qperpz * qperpz ) * s002 +
                q0w * q0z * s012 - qperpx * qperpy * s012 + qperpw * qperpz * s012 -
                q0w * q0y * s022 - qperpw * qperpy * s022 - qperpx * qperpz * s022 +
                s102 - q0y * q0y * s102 - q0z * q0z * s102 - qperpy * qperpy * s102 -
                qperpz * qperpz * s102 - q0w * q0z * s112 + qperpx * qperpy * s112 -
                qperpw * qperpz * s112 + q0w * q0y * s122 + qperpw * qperpy * s122 +
                qperpx * qperpz * s122 +
                q0x * ( -( q0y * s012 ) - q0z * s022 + q0y * s112 + q0z * s122 ) );

            c2[ 0 ] = DerivativeTerm(
                0.,
                -( qperpy * qperpy * s000 ) - qperpz * qperpz * s000 + qperpx * qperpy * s010 -
                qperpw * qperpz * s010 + qperpw * qperpy * s020 + qperpx * qperpz * s020 +
                q0y * q0y * ( s000 - s100 ) + q0z * q0z * ( s000 - s100 ) +
                qperpy * qperpy * s100 + qperpz * qperpz * s100 - qperpx * qperpy * s110 +
                qperpw * qperpz * s110 - qperpw * qperpy * s120 - qperpx * qperpz * s120 +
                2 * q0x * qperpy * s010 * theta - 2 * q0w * qperpz * s010 * theta +
                2 * q0w * qperpy * s020 * theta + 2 * q0x * qperpz * s020 * theta +
                q0y * ( q0x * ( -s010 + s110 ) + q0w * ( -s020 + s120 ) +
                    2 * ( -2 * qperpy * s000 + qperpx * s010 + qperpw * s020 ) * theta ) +
                q0z * ( q0w * ( s010 - s110 ) + q0x * ( -s020 + s120 ) -
                    2 * ( 2 * qperpz * s000 + qperpw * s010 - qperpx * s020 ) * theta ),
                -( qperpy * qperpy * s001 ) - qperpz * qperpz * s001 + qperpx * qperpy * s011 -
                qperpw * qperpz * s011 + qperpw * qperpy * s021 + qperpx * qperpz * s021 +
                q0y * q0y * ( s001 - s101 ) + q0z * q0z * ( s001 - s101 ) +
                qperpy * qperpy * s101 + qperpz * qperpz * s101 - qperpx * qperpy * s111 +
                qperpw * qperpz * s111 - qperpw * qperpy * s121 - qperpx * qperpz * s121 +
                2 * q0x * qperpy * s011 * theta - 2 * q0w * qperpz * s011 * theta +
                2 * q0w * qperpy * s021 * theta + 2 * q0x * qperpz * s021 * theta +
                q0y * ( q0x * ( -s011 + s111 ) + q0w * ( -s021 + s121 ) +
                    2 * ( -2 * qperpy * s001 + qperpx * s011 + qperpw * s021 ) * theta ) +
                q0z * ( q0w * ( s011 - s111 ) + q0x * ( -s021 + s121 ) -
                    2 * ( 2 * qperpz * s001 + qperpw * s011 - qperpx * s021 ) * theta ),
                -( qperpy * qperpy * s002 ) - qperpz * qperpz * s002 + qperpx * qperpy * s012 -
                qperpw * qperpz * s012 + qperpw * qperpy * s022 + qperpx * qperpz * s022 +
                q0y * q0y * ( s002 - s102 ) + q0z * q0z * ( s002 - s102 ) +
                qperpy * qperpy * s102 + qperpz * qperpz * s102 - qperpx * qperpy * s112 +
                qperpw * qperpz * s112 - qperpw * qperpy * s122 - qperpx * qperpz * s122 +
                2 * q0x * qperpy * s012 * theta - 2 * q0w * qperpz * s012 * theta +
                2 * q0w * qperpy * s022 * theta + 2 * q0x * qperpz * s022 * theta +
                q0y * ( q0x * ( -s012 + s112 ) + q0w * ( -s022 + s122 ) +
                    2 * ( -2 * qperpy * s002 + qperpx * s012 + qperpw * s022 ) * theta ) +
                q0z * ( q0w * ( s012 - s112 ) + q0x * ( -s022 + s122 ) -
                    2 * ( 2 * qperpz * s002 + qperpw * s012 - qperpx * s022 ) * theta ) );

            c3[ 0 ] = DerivativeTerm(
                0.,
                -2 *
                ( q0x * qperpy * s010 - q0w * qperpz * s010 + q0w * qperpy * s020 +
                    q0x * qperpz * s020 - q0x * qperpy * s110 + q0w * qperpz * s110 -
                    q0w * qperpy * s120 - q0x * qperpz * s120 +
                    q0y * ( -2 * qperpy * s000 + qperpx * s010 + qperpw * s020 +
                        2 * qperpy * s100 - qperpx * s110 - qperpw * s120 ) +
                    q0z * ( -2 * qperpz * s000 - qperpw * s010 + qperpx * s020 +
                        2 * qperpz * s100 + qperpw * s110 - qperpx * s120 ) ) *
                theta,
                -2 *
                ( q0x * qperpy * s011 - q0w * qperpz * s011 + q0w * qperpy * s021 +
                    q0x * qperpz * s021 - q0x * qperpy * s111 + q0w * qperpz * s111 -
                    q0w * qperpy * s121 - q0x * qperpz * s121 +
                    q0y * ( -2 * qperpy * s001 + qperpx * s011 + qperpw * s021 +
                        2 * qperpy * s101 - qperpx * s111 - qperpw * s121 ) +
                    q0z * ( -2 * qperpz * s001 - qperpw * s011 + qperpx * s021 +
                        2 * qperpz * s101 + qperpw * s111 - qperpx * s121 ) ) *
                theta,
                -2 *
                ( q0x * qperpy * s012 - q0w * qperpz * s012 + q0w * qperpy * s022 +
                    q0x * qperpz * s022 - q0x * qperpy * s112 + q0w * qperpz * s112 -
                    q0w * qperpy * s122 - q0x * qperpz * s122 +
                    q0y * ( -2 * qperpy * s002 + qperpx * s012 + qperpw * s022 +
                        2 * qperpy * s102 - qperpx * s112 - qperpw * s122 ) +
                    q0z * ( -2 * qperpz * s002 - qperpw * s012 + qperpx * s022 +
                        2 * qperpz * s102 + qperpw * s112 - qperpx * s122 ) ) *
                theta );

            c4[ 0 ] = DerivativeTerm(
                0.,
                -( q0x * qperpy * s010 ) + q0w * qperpz * s010 - q0w * qperpy * s020 -
                q0x * qperpz * s020 + q0x * qperpy * s110 - q0w * qperpz * s110 +
                q0w * qperpy * s120 + q0x * qperpz * s120 + 2 * q0y * q0y * s000 * theta +
                2 * q0z * q0z * s000 * theta - 2 * qperpy * qperpy * s000 * theta -
                2 * qperpz * qperpz * s000 * theta + 2 * qperpx * qperpy * s010 * theta -
                2 * qperpw * qperpz * s010 * theta + 2 * qperpw * qperpy * s020 * theta +
                2 * qperpx * qperpz * s020 * theta +
                q0y * ( -( qperpx * s010 ) - qperpw * s020 + 2 * qperpy * ( s000 - s100 ) +
                    qperpx * s110 + qperpw * s120 - 2 * q0x * s010 * theta -
                    2 * q0w * s020 * theta ) +
                q0z * ( 2 * qperpz * s000 + qperpw * s010 - qperpx * s020 -
                    2 * qperpz * s100 - qperpw * s110 + qperpx * s120 +
                    2 * q0w * s010 * theta - 2 * q0x * s020 * theta ),
                -( q0x * qperpy * s011 ) + q0w * qperpz * s011 - q0w * qperpy * s021 -
                q0x * qperpz * s021 + q0x * qperpy * s111 - q0w * qperpz * s111 +
                q0w * qperpy * s121 + q0x * qperpz * s121 + 2 * q0y * q0y * s001 * theta +
                2 * q0z * q0z * s001 * theta - 2 * qperpy * qperpy * s001 * theta -
                2 * qperpz * qperpz * s001 * theta + 2 * qperpx * qperpy * s011 * theta -
                2 * qperpw * qperpz * s011 * theta + 2 * qperpw * qperpy * s021 * theta +
                2 * qperpx * qperpz * s021 * theta +
                q0y * ( -( qperpx * s011 ) - qperpw * s021 + 2 * qperpy * ( s001 - s101 ) +
                    qperpx * s111 + qperpw * s121 - 2 * q0x * s011 * theta -
                    2 * q0w * s021 * theta ) +
                q0z * ( 2 * qperpz * s001 + qperpw * s011 - qperpx * s021 -
                    2 * qperpz * s101 - qperpw * s111 + qperpx * s121 +
                    2 * q0w * s011 * theta - 2 * q0x * s021 * theta ),
                -( q0x * qperpy * s012 ) + q0w * qperpz * s012 - q0w * qperpy * s022 -
                q0x * qperpz * s022 + q0x * qperpy * s112 - q0w * qperpz * s112 +
                q0w * qperpy * s122 + q0x * qperpz * s122 + 2 * q0y * q0y * s002 * theta +
                2 * q0z * q0z * s002 * theta - 2 * qperpy * qperpy * s002 * theta -
                2 * qperpz * qperpz * s002 * theta + 2 * qperpx * qperpy * s012 * theta -
                2 * qperpw * qperpz * s012 * theta + 2 * qperpw * qperpy * s022 * theta +
                2 * qperpx * qperpz * s022 * theta +
                q0y * ( -( qperpx * s012 ) - qperpw * s022 + 2 * qperpy * ( s002 - s102 ) +
                    qperpx * s112 + qperpw * s122 - 2 * q0x * s012 * theta -
                    2 * q0w * s022 * theta ) +
                q0z * ( 2 * qperpz * s002 + qperpw * s012 - qperpx * s022 -
                    2 * qperpz * s102 - qperpw * s112 + qperpx * s122 +
                    2 * q0w * s012 * theta - 2 * q0x * s022 * theta ) );

            c5[ 0 ] = DerivativeTerm(
                0.,
                2 *
                ( qperpy * qperpy * s000 + qperpz * qperpz * s000 -
                    qperpx * qperpy * s010 + qperpw * qperpz * s010 -
                    qperpw * qperpy * s020 - qperpx * qperpz * s020 -
                    qperpy * qperpy * s100 - qperpz * qperpz * s100 +
                    q0y * q0y * ( -s000 + s100 ) + q0z * q0z * ( -s000 + s100 ) +
                    qperpx * qperpy * s110 - qperpw * qperpz * s110 +
                    q0y * ( q0x * ( s010 - s110 ) + q0w * ( s020 - s120 ) ) +
                    qperpw * qperpy * s120 + qperpx * qperpz * s120 +
                    q0z * ( -( q0w * s010 ) + q0x * s020 + q0w * s110 - q0x * s120 ) ) *
                theta,
                2 *
                ( qperpy * qperpy * s001 + qperpz * qperpz * s001 -
                    qperpx * qperpy * s011 + qperpw * qperpz * s011 -
                    qperpw * qperpy * s021 - qperpx * qperpz * s021 -
                    qperpy * qperpy * s101 - qperpz * qperpz * s101 +
                    q0y * q0y * ( -s001 + s101 ) + q0z * q0z * ( -s001 + s101 ) +
                    qperpx * qperpy * s111 - qperpw * qperpz * s111 +
                    q0y * ( q0x * ( s011 - s111 ) + q0w * ( s021 - s121 ) ) +
                    qperpw * qperpy * s121 + qperpx * qperpz * s121 +
                    q0z * ( -( q0w * s011 ) + q0x * s021 + q0w * s111 - q0x * s121 ) ) *
                theta,
                2 *
                ( qperpy * qperpy * s002 + qperpz * qperpz * s002 -
                    qperpx * qperpy * s012 + qperpw * qperpz * s012 -
                    qperpw * qperpy * s022 - qperpx * qperpz * s022 -
                    qperpy * qperpy * s102 - qperpz * qperpz * s102 +
                    q0y * q0y * ( -s002 + s102 ) + q0z * q0z * ( -s002 + s102 ) +
                    qperpx * qperpy * s112 - qperpw * qperpz * s112 +
                    q0y * ( q0x * ( s012 - s112 ) + q0w * ( s022 - s122 ) ) +
                    qperpw * qperpy * s122 + qperpx * qperpz * s122 +
                    q0z * ( -( q0w * s012 ) + q0x * s022 + q0w * s112 - q0x * s122 ) ) *
                theta );

            c1[ 1 ] = DerivativeTerm(
                -t0y + t1y,
                -( qperpx * qperpy * s000 ) - qperpw * qperpz * s000 - s010 + q0z * q0z * s010 +
                qperpx * qperpx * s010 + qperpz * qperpz * s010 - q0y * q0z * s020 +
                qperpw * qperpx * s020 - qperpy * qperpz * s020 + qperpx * qperpy * s100 +
                qperpw * qperpz * s100 + q0w * q0z * ( -s000 + s100 ) +
                q0x * q0x * ( s010 - s110 ) + s110 - q0z * q0z * s110 -
                qperpx * qperpx * s110 - qperpz * qperpz * s110 +
                q0x * ( q0y * ( -s000 + s100 ) + q0w * ( s020 - s120 ) ) + q0y * q0z * s120 -
                qperpw * qperpx * s120 + qperpy * qperpz * s120,
                -( qperpx * qperpy * s001 ) - qperpw * qperpz * s001 - s011 + q0z * q0z * s011 +
                qperpx * qperpx * s011 + qperpz * qperpz * s011 - q0y * q0z * s021 +
                qperpw * qperpx * s021 - qperpy * qperpz * s021 + qperpx * qperpy * s101 +
                qperpw * qperpz * s101 + q0w * q0z * ( -s001 + s101 ) +
                q0x * q0x * ( s011 - s111 ) + s111 - q0z * q0z * s111 -
                qperpx * qperpx * s111 - qperpz * qperpz * s111 +
                q0x * ( q0y * ( -s001 + s101 ) + q0w * ( s021 - s121 ) ) + q0y * q0z * s121 -
                qperpw * qperpx * s121 + qperpy * qperpz * s121,
                -( qperpx * qperpy * s002 ) - qperpw * qperpz * s002 - s012 + q0z * q0z * s012 +
                qperpx * qperpx * s012 + qperpz * qperpz * s012 - q0y * q0z * s022 +
                qperpw * qperpx * s022 - qperpy * qperpz * s022 + qperpx * qperpy * s102 +
                qperpw * qperpz * s102 + q0w * q0z * ( -s002 + s102 ) +
                q0x * q0x * ( s012 - s112 ) + s112 - q0z * q0z * s112 -
                qperpx * qperpx * s112 - qperpz * qperpz * s112 +
                q0x * ( q0y * ( -s002 + s102 ) + q0w * ( s022 - s122 ) ) + q0y * q0z * s122 -
                qperpw * qperpx * s122 + qperpy * qperpz * s122 );

            c2[ 1 ] = DerivativeTerm(
                0.,
                qperpx * qperpy * s000 + qperpw * qperpz * s000 + q0z * q0z * s010 -
                qperpx * qperpx * s010 - qperpz * qperpz * s010 - q0y * q0z * s020 -
                qperpw * qperpx * s020 + qperpy * qperpz * s020 - qperpx * qperpy * s100 -
                qperpw * qperpz * s100 + q0x * q0x * ( s010 - s110 ) - q0z * q0z * s110 +
                qperpx * qperpx * s110 + qperpz * qperpz * s110 + q0y * q0z * s120 +
                qperpw * qperpx * s120 - qperpy * qperpz * s120 +
                2 * q0z * qperpw * s000 * theta + 2 * q0y * qperpx * s000 * theta -
                4 * q0z * qperpz * s010 * theta + 2 * q0z * qperpy * s020 * theta +
                2 * q0y * qperpz * s020 * theta +
                q0x * ( q0w * s020 + q0y * ( -s000 + s100 ) - q0w * s120 +
                    2 * qperpy * s000 * theta - 4 * qperpx * s010 * theta -
                    2 * qperpw * s020 * theta ) +
                q0w * ( -( q0z * s000 ) + q0z * s100 + 2 * qperpz * s000 * theta -
                    2 * qperpx * s020 * theta ),
                qperpx * qperpy * s001 + qperpw * qperpz * s001 + q0z * q0z * s011 -
                qperpx * qperpx * s011 - qperpz * qperpz * s011 - q0y * q0z * s021 -
                qperpw * qperpx * s021 + qperpy * qperpz * s021 - qperpx * qperpy * s101 -
                qperpw * qperpz * s101 + q0x * q0x * ( s011 - s111 ) - q0z * q0z * s111 +
                qperpx * qperpx * s111 + qperpz * qperpz * s111 + q0y * q0z * s121 +
                qperpw * qperpx * s121 - qperpy * qperpz * s121 +
                2 * q0z * qperpw * s001 * theta + 2 * q0y * qperpx * s001 * theta -
                4 * q0z * qperpz * s011 * theta + 2 * q0z * qperpy * s021 * theta +
                2 * q0y * qperpz * s021 * theta +
                q0x * ( q0w * s021 + q0y * ( -s001 + s101 ) - q0w * s121 +
                    2 * qperpy * s001 * theta - 4 * qperpx * s011 * theta -
                    2 * qperpw * s021 * theta ) +
                q0w * ( -( q0z * s001 ) + q0z * s101 + 2 * qperpz * s001 * theta -
                    2 * qperpx * s021 * theta ),
                qperpx * qperpy * s002 + qperpw * qperpz * s002 + q0z * q0z * s012 -
                qperpx * qperpx * s012 - qperpz * qperpz * s012 - q0y * q0z * s022 -
                qperpw * qperpx * s022 + qperpy * qperpz * s022 - qperpx * qperpy * s102 -
                qperpw * qperpz * s102 + q0x * q0x * ( s012 - s112 ) - q0z * q0z * s112 +
                qperpx * qperpx * s112 + qperpz * qperpz * s112 + q0y * q0z * s122 +
                qperpw * qperpx * s122 - qperpy * qperpz * s122 +
                2 * q0z * qperpw * s002 * theta + 2 * q0y * qperpx * s002 * theta -
                4 * q0z * qperpz * s012 * theta + 2 * q0z * qperpy * s022 * theta +
                2 * q0y * qperpz * s022 * theta +
                q0x * ( q0w * s022 + q0y * ( -s002 + s102 ) - q0w * s122 +
                    2 * qperpy * s002 * theta - 4 * qperpx * s012 * theta -
                    2 * qperpw * s022 * theta ) +
                q0w * ( -( q0z * s002 ) + q0z * s102 + 2 * qperpz * s002 * theta -
                    2 * qperpx * s022 * theta ) );

            c3[ 1 ] = DerivativeTerm(
                0.,
                2 *
                ( -( q0x * qperpy * s000 ) - q0w * qperpz * s000 + 2 * q0x * qperpx * s010 +
                    q0x * qperpw * s020 + q0w * qperpx * s020 + q0x * qperpy * s100 +
                    q0w * qperpz * s100 - 2 * q0x * qperpx * s110 - q0x * qperpw * s120 -
                    q0w * qperpx * s120 +
                    q0z * ( 2 * qperpz * s010 - qperpy * s020 + qperpw * ( -s000 + s100 ) -
                        2 * qperpz * s110 + qperpy * s120 ) +
                    q0y *
                    ( -( qperpx * s000 ) - qperpz * s020 + qperpx * s100 + qperpz * s120 ) ) *
                theta,
                2 *
                ( -( q0x * qperpy * s001 ) - q0w * qperpz * s001 + 2 * q0x * qperpx * s011 +
                    q0x * qperpw * s021 + q0w * qperpx * s021 + q0x * qperpy * s101 +
                    q0w * qperpz * s101 - 2 * q0x * qperpx * s111 - q0x * qperpw * s121 -
                    q0w * qperpx * s121 +
                    q0z * ( 2 * qperpz * s011 - qperpy * s021 + qperpw * ( -s001 + s101 ) -
                        2 * qperpz * s111 + qperpy * s121 ) +
                    q0y *
                    ( -( qperpx * s001 ) - qperpz * s021 + qperpx * s101 + qperpz * s121 ) ) *
                theta,
                2 *
                ( -( q0x * qperpy * s002 ) - q0w * qperpz * s002 + 2 * q0x * qperpx * s012 +
                    q0x * qperpw * s022 + q0w * qperpx * s022 + q0x * qperpy * s102 +
                    q0w * qperpz * s102 - 2 * q0x * qperpx * s112 - q0x * qperpw * s122 -
                    q0w * qperpx * s122 +
                    q0z * ( 2 * qperpz * s012 - qperpy * s022 + qperpw * ( -s002 + s102 ) -
                        2 * qperpz * s112 + qperpy * s122 ) +
                    q0y *
                    ( -( qperpx * s002 ) - qperpz * s022 + qperpx * s102 + qperpz * s122 ) ) *
                theta );

            c4[ 1 ] = DerivativeTerm(
                0.,
                -( q0x * qperpy * s000 ) - q0w * qperpz * s000 + 2 * q0x * qperpx * s010 +
                q0x * qperpw * s020 + q0w * qperpx * s020 + q0x * qperpy * s100 +
                q0w * qperpz * s100 - 2 * q0x * qperpx * s110 - q0x * qperpw * s120 -
                q0w * qperpx * s120 + 2 * qperpx * qperpy * s000 * theta +
                2 * qperpw * qperpz * s000 * theta + 2 * q0x * q0x * s010 * theta +
                2 * q0z * q0z * s010 * theta - 2 * qperpx * qperpx * s010 * theta -
                2 * qperpz * qperpz * s010 * theta + 2 * q0w * q0x * s020 * theta -
                2 * qperpw * qperpx * s020 * theta + 2 * qperpy * qperpz * s020 * theta +
                q0y * ( -( qperpx * s000 ) - qperpz * s020 + qperpx * s100 + qperpz * s120 -
                    2 * q0x * s000 * theta ) +
                q0z * ( 2 * qperpz * s010 - qperpy * s020 + qperpw * ( -s000 + s100 ) -
                    2 * qperpz * s110 + qperpy * s120 - 2 * q0w * s000 * theta -
                    2 * q0y * s020 * theta ),
                -( q0x * qperpy * s001 ) - q0w * qperpz * s001 + 2 * q0x * qperpx * s011 +
                q0x * qperpw * s021 + q0w * qperpx * s021 + q0x * qperpy * s101 +
                q0w * qperpz * s101 - 2 * q0x * qperpx * s111 - q0x * qperpw * s121 -
                q0w * qperpx * s121 + 2 * qperpx * qperpy * s001 * theta +
                2 * qperpw * qperpz * s001 * theta + 2 * q0x * q0x * s011 * theta +
                2 * q0z * q0z * s011 * theta - 2 * qperpx * qperpx * s011 * theta -
                2 * qperpz * qperpz * s011 * theta + 2 * q0w * q0x * s021 * theta -
                2 * qperpw * qperpx * s021 * theta + 2 * qperpy * qperpz * s021 * theta +
                q0y * ( -( qperpx * s001 ) - qperpz * s021 + qperpx * s101 + qperpz * s121 -
                    2 * q0x * s001 * theta ) +
                q0z * ( 2 * qperpz * s011 - qperpy * s021 + qperpw * ( -s001 + s101 ) -
                    2 * qperpz * s111 + qperpy * s121 - 2 * q0w * s001 * theta -
                    2 * q0y * s021 * theta ),
                -( q0x * qperpy * s002 ) - q0w * qperpz * s002 + 2 * q0x * qperpx * s012 +
                q0x * qperpw * s022 + q0w * qperpx * s022 + q0x * qperpy * s102 +
                q0w * qperpz * s102 - 2 * q0x * qperpx * s112 - q0x * qperpw * s122 -
                q0w * qperpx * s122 + 2 * qperpx * qperpy * s002 * theta +
                2 * qperpw * qperpz * s002 * theta + 2 * q0x * q0x * s012 * theta +
                2 * q0z * q0z * s012 * theta - 2 * qperpx * qperpx * s012 * theta -
                2 * qperpz * qperpz * s012 * theta + 2 * q0w * q0x * s022 * theta -
                2 * qperpw * qperpx * s022 * theta + 2 * qperpy * qperpz * s022 * theta +
                q0y * ( -( qperpx * s002 ) - qperpz * s022 + qperpx * s102 + qperpz * s122 -
                    2 * q0x * s002 * theta ) +
                q0z * ( 2 * qperpz * s012 - qperpy * s022 + qperpw * ( -s002 + s102 ) -
                    2 * qperpz * s112 + qperpy * s122 - 2 * q0w * s002 * theta -
                    2 * q0y * s022 * theta ) );

            c5[ 1 ] = DerivativeTerm(
                0.,
                -2 *
                ( qperpx * qperpy * s000 + qperpw * qperpz * s000 + q0z * q0z * s010 -
                    qperpx * qperpx * s010 - qperpz * qperpz * s010 - q0y * q0z * s020 -
                    qperpw * qperpx * s020 + qperpy * qperpz * s020 -
                    qperpx * qperpy * s100 - qperpw * qperpz * s100 +
                    q0w * q0z * ( -s000 + s100 ) + q0x * q0x * ( s010 - s110 ) -
                    q0z * q0z * s110 + qperpx * qperpx * s110 + qperpz * qperpz * s110 +
                    q0x * ( q0y * ( -s000 + s100 ) + q0w * ( s020 - s120 ) ) + q0y * q0z * s120 +
                    qperpw * qperpx * s120 - qperpy * qperpz * s120 ) *
                theta,
                -2 *
                ( qperpx * qperpy * s001 + qperpw * qperpz * s001 + q0z * q0z * s011 -
                    qperpx * qperpx * s011 - qperpz * qperpz * s011 - q0y * q0z * s021 -
                    qperpw * qperpx * s021 + qperpy * qperpz * s021 -
                    qperpx * qperpy * s101 - qperpw * qperpz * s101 +
                    q0w * q0z * ( -s001 + s101 ) + q0x * q0x * ( s011 - s111 ) -
                    q0z * q0z * s111 + qperpx * qperpx * s111 + qperpz * qperpz * s111 +
                    q0x * ( q0y * ( -s001 + s101 ) + q0w * ( s021 - s121 ) ) + q0y * q0z * s121 +
                    qperpw * qperpx * s121 - qperpy * qperpz * s121 ) *
                theta,
                -2 *
                ( qperpx * qperpy * s002 + qperpw * qperpz * s002 + q0z * q0z * s012 -
                    qperpx * qperpx * s012 - qperpz * qperpz * s012 - q0y * q0z * s022 -
                    qperpw * qperpx * s022 + qperpy * qperpz * s022 -
                    qperpx * qperpy * s102 - qperpw * qperpz * s102 +
                    q0w * q0z * ( -s002 + s102 ) + q0x * q0x * ( s012 - s112 ) -
                    q0z * q0z * s112 + qperpx * qperpx * s112 + qperpz * qperpz * s112 +
                    q0x * ( q0y * ( -s002 + s102 ) + q0w * ( s022 - s122 ) ) + q0y * q0z * s122 +
                    qperpw * qperpx * s122 - qperpy * qperpz * s122 ) *
                theta );

            c1[ 2 ] = DerivativeTerm(
                -t0z + t1z,
                ( qperpw * qperpy * s000 - qperpx * qperpz * s000 - q0y * q0z * s010 -
                    qperpw * qperpx * s010 - qperpy * qperpz * s010 - s020 + q0y * q0y * s020 +
                    qperpx * qperpx * s020 + qperpy * qperpy * s020 - qperpw * qperpy * s100 +
                    qperpx * qperpz * s100 + q0x * q0z * ( -s000 + s100 ) + q0y * q0z * s110 +
                    qperpw * qperpx * s110 + qperpy * qperpz * s110 +
                    q0w * ( q0y * ( s000 - s100 ) + q0x * ( -s010 + s110 ) ) +
                    q0x * q0x * ( s020 - s120 ) + s120 - q0y * q0y * s120 -
                    qperpx * qperpx * s120 - qperpy * qperpy * s120 ),
                ( qperpw * qperpy * s001 - qperpx * qperpz * s001 - q0y * q0z * s011 -
                    qperpw * qperpx * s011 - qperpy * qperpz * s011 - s021 + q0y * q0y * s021 +
                    qperpx * qperpx * s021 + qperpy * qperpy * s021 - qperpw * qperpy * s101 +
                    qperpx * qperpz * s101 + q0x * q0z * ( -s001 + s101 ) + q0y * q0z * s111 +
                    qperpw * qperpx * s111 + qperpy * qperpz * s111 +
                    q0w * ( q0y * ( s001 - s101 ) + q0x * ( -s011 + s111 ) ) +
                    q0x * q0x * ( s021 - s121 ) + s121 - q0y * q0y * s121 -
                    qperpx * qperpx * s121 - qperpy * qperpy * s121 ),
                ( qperpw * qperpy * s002 - qperpx * qperpz * s002 - q0y * q0z * s012 -
                    qperpw * qperpx * s012 - qperpy * qperpz * s012 - s022 + q0y * q0y * s022 +
                    qperpx * qperpx * s022 + qperpy * qperpy * s022 - qperpw * qperpy * s102 +
                    qperpx * qperpz * s102 + q0x * q0z * ( -s002 + s102 ) + q0y * q0z * s112 +
                    qperpw * qperpx * s112 + qperpy * qperpz * s112 +
                    q0w * ( q0y * ( s002 - s102 ) + q0x * ( -s012 + s112 ) ) +
                    q0x * q0x * ( s022 - s122 ) + s122 - q0y * q0y * s122 -
                    qperpx * qperpx * s122 - qperpy * qperpy * s122 ) );

            c2[ 2 ] = DerivativeTerm(
                0.,
                ( q0w * q0y * s000 - q0x * q0z * s000 - qperpw * qperpy * s000 +
                    qperpx * qperpz * s000 - q0w * q0x * s010 - q0y * q0z * s010 +
                    qperpw * qperpx * s010 + qperpy * qperpz * s010 + q0x * q0x * s020 +
                    q0y * q0y * s020 - qperpx * qperpx * s020 - qperpy * qperpy * s020 -
                    q0w * q0y * s100 + q0x * q0z * s100 + qperpw * qperpy * s100 -
                    qperpx * qperpz * s100 + q0w * q0x * s110 + q0y * q0z * s110 -
                    qperpw * qperpx * s110 - qperpy * qperpz * s110 - q0x * q0x * s120 -
                    q0y * q0y * s120 + qperpx * qperpx * s120 + qperpy * qperpy * s120 -
                    2 * q0y * qperpw * s000 * theta + 2 * q0z * qperpx * s000 * theta -
                    2 * q0w * qperpy * s000 * theta + 2 * q0x * qperpz * s000 * theta +
                    2 * q0x * qperpw * s010 * theta + 2 * q0w * qperpx * s010 * theta +
                    2 * q0z * qperpy * s010 * theta + 2 * q0y * qperpz * s010 * theta -
                    4 * q0x * qperpx * s020 * theta - 4 * q0y * qperpy * s020 * theta ),
                ( q0w * q0y * s001 - q0x * q0z * s001 - qperpw * qperpy * s001 +
                    qperpx * qperpz * s001 - q0w * q0x * s011 - q0y * q0z * s011 +
                    qperpw * qperpx * s011 + qperpy * qperpz * s011 + q0x * q0x * s021 +
                    q0y * q0y * s021 - qperpx * qperpx * s021 - qperpy * qperpy * s021 -
                    q0w * q0y * s101 + q0x * q0z * s101 + qperpw * qperpy * s101 -
                    qperpx * qperpz * s101 + q0w * q0x * s111 + q0y * q0z * s111 -
                    qperpw * qperpx * s111 - qperpy * qperpz * s111 - q0x * q0x * s121 -
                    q0y * q0y * s121 + qperpx * qperpx * s121 + qperpy * qperpy * s121 -
                    2 * q0y * qperpw * s001 * theta + 2 * q0z * qperpx * s001 * theta -
                    2 * q0w * qperpy * s001 * theta + 2 * q0x * qperpz * s001 * theta +
                    2 * q0x * qperpw * s011 * theta + 2 * q0w * qperpx * s011 * theta +
                    2 * q0z * qperpy * s011 * theta + 2 * q0y * qperpz * s011 * theta -
                    4 * q0x * qperpx * s021 * theta - 4 * q0y * qperpy * s021 * theta ),
                ( q0w * q0y * s002 - q0x * q0z * s002 - qperpw * qperpy * s002 +
                    qperpx * qperpz * s002 - q0w * q0x * s012 - q0y * q0z * s012 +
                    qperpw * qperpx * s012 + qperpy * qperpz * s012 + q0x * q0x * s022 +
                    q0y * q0y * s022 - qperpx * qperpx * s022 - qperpy * qperpy * s022 -
                    q0w * q0y * s102 + q0x * q0z * s102 + qperpw * qperpy * s102 -
                    qperpx * qperpz * s102 + q0w * q0x * s112 + q0y * q0z * s112 -
                    qperpw * qperpx * s112 - qperpy * qperpz * s112 - q0x * q0x * s122 -
                    q0y * q0y * s122 + qperpx * qperpx * s122 + qperpy * qperpy * s122 -
                    2 * q0y * qperpw * s002 * theta + 2 * q0z * qperpx * s002 * theta -
                    2 * q0w * qperpy * s002 * theta + 2 * q0x * qperpz * s002 * theta +
                    2 * q0x * qperpw * s012 * theta + 2 * q0w * qperpx * s012 * theta +
                    2 * q0z * qperpy * s012 * theta + 2 * q0y * qperpz * s012 * theta -
                    4 * q0x * qperpx * s022 * theta - 4 * q0y * qperpy * s022 * theta ) );

            c3[ 2 ] = DerivativeTerm(
                0.,
                -2 *
                ( -( q0w * qperpy * s000 ) + q0x * qperpz * s000 + q0x * qperpw * s010 +
                    q0w * qperpx * s010 - 2 * q0x * qperpx * s020 + q0w * qperpy * s100 -
                    q0x * qperpz * s100 - q0x * qperpw * s110 - q0w * qperpx * s110 +
                    q0z * ( qperpx * s000 + qperpy * s010 - qperpx * s100 - qperpy * s110 ) +
                    2 * q0x * qperpx * s120 +
                    q0y * ( qperpz * s010 - 2 * qperpy * s020 + qperpw * ( -s000 + s100 ) -
                        qperpz * s110 + 2 * qperpy * s120 ) ) *
                theta,
                -2 *
                ( -( q0w * qperpy * s001 ) + q0x * qperpz * s001 + q0x * qperpw * s011 +
                    q0w * qperpx * s011 - 2 * q0x * qperpx * s021 + q0w * qperpy * s101 -
                    q0x * qperpz * s101 - q0x * qperpw * s111 - q0w * qperpx * s111 +
                    q0z * ( qperpx * s001 + qperpy * s011 - qperpx * s101 - qperpy * s111 ) +
                    2 * q0x * qperpx * s121 +
                    q0y * ( qperpz * s011 - 2 * qperpy * s021 + qperpw * ( -s001 + s101 ) -
                        qperpz * s111 + 2 * qperpy * s121 ) ) *
                theta,
                -2 *
                ( -( q0w * qperpy * s002 ) + q0x * qperpz * s002 + q0x * qperpw * s012 +
                    q0w * qperpx * s012 - 2 * q0x * qperpx * s022 + q0w * qperpy * s102 -
                    q0x * qperpz * s102 - q0x * qperpw * s112 - q0w * qperpx * s112 +
                    q0z * ( qperpx * s002 + qperpy * s012 - qperpx * s102 - qperpy * s112 ) +
                    2 * q0x * qperpx * s122 +
                    q0y * ( qperpz * s012 - 2 * qperpy * s022 + qperpw * ( -s002 + s102 ) -
                        qperpz * s112 + 2 * qperpy * s122 ) ) *
                theta );

            c4[ 2 ] = DerivativeTerm(
                0.,
                q0w * qperpy * s000 - q0x * qperpz * s000 - q0x * qperpw * s010 -
                q0w * qperpx * s010 + 2 * q0x * qperpx * s020 - q0w * qperpy * s100 +
                q0x * qperpz * s100 + q0x * qperpw * s110 + q0w * qperpx * s110 -
                2 * q0x * qperpx * s120 - 2 * qperpw * qperpy * s000 * theta +
                2 * qperpx * qperpz * s000 * theta - 2 * q0w * q0x * s010 * theta +
                2 * qperpw * qperpx * s010 * theta + 2 * qperpy * qperpz * s010 * theta +
                2 * q0x * q0x * s020 * theta + 2 * q0y * q0y * s020 * theta -
                2 * qperpx * qperpx * s020 * theta - 2 * qperpy * qperpy * s020 * theta +
                q0z * ( -( qperpx * s000 ) - qperpy * s010 + qperpx * s100 + qperpy * s110 -
                    2 * q0x * s000 * theta ) +
                q0y * ( -( qperpz * s010 ) + 2 * qperpy * s020 + qperpw * ( s000 - s100 ) +
                    qperpz * s110 - 2 * qperpy * s120 + 2 * q0w * s000 * theta -
                    2 * q0z * s010 * theta ),
                q0w * qperpy * s001 - q0x * qperpz * s001 - q0x * qperpw * s011 -
                q0w * qperpx * s011 + 2 * q0x * qperpx * s021 - q0w * qperpy * s101 +
                q0x * qperpz * s101 + q0x * qperpw * s111 + q0w * qperpx * s111 -
                2 * q0x * qperpx * s121 - 2 * qperpw * qperpy * s001 * theta +
                2 * qperpx * qperpz * s001 * theta - 2 * q0w * q0x * s011 * theta +
                2 * qperpw * qperpx * s011 * theta + 2 * qperpy * qperpz * s011 * theta +
                2 * q0x * q0x * s021 * theta + 2 * q0y * q0y * s021 * theta -
                2 * qperpx * qperpx * s021 * theta - 2 * qperpy * qperpy * s021 * theta +
                q0z * ( -( qperpx * s001 ) - qperpy * s011 + qperpx * s101 + qperpy * s111 -
                    2 * q0x * s001 * theta ) +
                q0y * ( -( qperpz * s011 ) + 2 * qperpy * s021 + qperpw * ( s001 - s101 ) +
                    qperpz * s111 - 2 * qperpy * s121 + 2 * q0w * s001 * theta -
                    2 * q0z * s011 * theta ),
                q0w * qperpy * s002 - q0x * qperpz * s002 - q0x * qperpw * s012 -
                q0w * qperpx * s012 + 2 * q0x * qperpx * s022 - q0w * qperpy * s102 +
                q0x * qperpz * s102 + q0x * qperpw * s112 + q0w * qperpx * s112 -
                2 * q0x * qperpx * s122 - 2 * qperpw * qperpy * s002 * theta +
                2 * qperpx * qperpz * s002 * theta - 2 * q0w * q0x * s012 * theta +
                2 * qperpw * qperpx * s012 * theta + 2 * qperpy * qperpz * s012 * theta +
                2 * q0x * q0x * s022 * theta + 2 * q0y * q0y * s022 * theta -
                2 * qperpx * qperpx * s022 * theta - 2 * qperpy * qperpy * s022 * theta +
                q0z * ( -( qperpx * s002 ) - qperpy * s012 + qperpx * s102 + qperpy * s112 -
                    2 * q0x * s002 * theta ) +
                q0y * ( -( qperpz * s012 ) + 2 * qperpy * s022 + qperpw * ( s002 - s102 ) +
                    qperpz * s112 - 2 * qperpy * s122 + 2 * q0w * s002 * theta -
                    2 * q0z * s012 * theta ) );

            c5[ 2 ] = DerivativeTerm(
                0.,
                2 *
                ( qperpw * qperpy * s000 - qperpx * qperpz * s000 + q0y * q0z * s010 -
                    qperpw * qperpx * s010 - qperpy * qperpz * s010 - q0y * q0y * s020 +
                    qperpx * qperpx * s020 + qperpy * qperpy * s020 +
                    q0x * q0z * ( s000 - s100 ) - qperpw * qperpy * s100 +
                    qperpx * qperpz * s100 +
                    q0w * ( q0y * ( -s000 + s100 ) + q0x * ( s010 - s110 ) ) - q0y * q0z * s110 +
                    qperpw * qperpx * s110 + qperpy * qperpz * s110 + q0y * q0y * s120 -
                    qperpx * qperpx * s120 - qperpy * qperpy * s120 +
                    q0x * q0x * ( -s020 + s120 ) ) *
                theta,
                2 *
                ( qperpw * qperpy * s001 - qperpx * qperpz * s001 + q0y * q0z * s011 -
                    qperpw * qperpx * s011 - qperpy * qperpz * s011 - q0y * q0y * s021 +
                    qperpx * qperpx * s021 + qperpy * qperpy * s021 +
                    q0x * q0z * ( s001 - s101 ) - qperpw * qperpy * s101 +
                    qperpx * qperpz * s101 +
                    q0w * ( q0y * ( -s001 + s101 ) + q0x * ( s011 - s111 ) ) - q0y * q0z * s111 +
                    qperpw * qperpx * s111 + qperpy * qperpz * s111 + q0y * q0y * s121 -
                    qperpx * qperpx * s121 - qperpy * qperpy * s121 +
                    q0x * q0x * ( -s021 + s121 ) ) *
                theta,
                2 *
                ( qperpw * qperpy * s002 - qperpx * qperpz * s002 + q0y * q0z * s012 -
                    qperpw * qperpx * s012 - qperpy * qperpz * s012 - q0y * q0y * s022 +
                    qperpx * qperpx * s022 + qperpy * qperpy * s022 +
                    q0x * q0z * ( s002 - s102 ) - qperpw * qperpy * s102 +
                    qperpx * qperpz * s102 +
                    q0w * ( q0y * ( -s002 + s102 ) + q0x * ( s012 - s112 ) ) - q0y * q0z * s112 +
                    qperpw * qperpx * s112 + qperpy * qperpz * s112 + q0y * q0y * s122 -
                    qperpx * qperpx * s122 - qperpy * qperpy * s122 +
                    q0x * q0x * ( -s022 + s122 ) ) *
                theta );
        }
    }

    PBRT_CPU_GPU Ray AnimatedTransform::operator()( const Ray& r, Float* tMax ) const
    {
        if ( !actuallyAnimated || r.time <= startTime )
            return startTransform( r, tMax );
        else if ( r.time >= endTime )
            return endTransform( r, tMax );
        else
        {
            Transform t = Interpolate( r.time );
            return t( r, tMax );
        }
    }

    PBRT_CPU_GPU Ray AnimatedTransform::ApplyInverse( const Ray& r, Float* tMax ) const
    {
        if ( !actuallyAnimated || r.time <= startTime )
            return startTransform.ApplyInverse( r, tMax );
        else if ( r.time >= endTime )
            return endTransform.ApplyInverse( r, tMax );
        else
        {
            Transform t = Interpolate( r.time );
            return t.ApplyInverse( r, tMax );
        }
    }

    PBRT_CPU_GPU RayDifferential AnimatedTransform::operator()( const RayDifferential& r,
        Float* tMax ) const
    {
        if ( !actuallyAnimated || r.time <= startTime )
            return startTransform( r, tMax );
        else if ( r.time >= endTime )
            return endTransform( r, tMax );
        else
        {
            Transform t = Interpolate( r.time );
            return t( r, tMax );
        }
    }

    PBRT_CPU_GPU Point3f AnimatedTransform::operator()( Point3f p, Float time ) const
    {
        if ( !actuallyAnimated || time <= startTime )
            return startTransform( p );
        else if ( time >= endTime )
            return endTransform( p );
        Transform t = Interpolate( time );
        return t( p );
    }

    Point3f::Simd AnimatedTransform::operator()( const Point3f::Simd& p, Float time ) const
    {
        if ( !actuallyAnimated || time <= startTime )
            return startTransform( p );
        else if ( time >= endTime )
            return endTransform( p );
        Transform t = Interpolate( time );
        return t( p );
    }

    PBRT_CPU_GPU Vector3f AnimatedTransform::operator()( Vector3f v, Float time ) const
    {
        if ( !actuallyAnimated || time <= startTime )
            return startTransform( v );
        else if ( time >= endTime )
            return endTransform( v );
        Transform t = Interpolate( time );
        return t( v );
    }

    Vector3f::Simd AnimatedTransform::operator()( const Vector3f::Simd& v, Float time ) const
    {
        if ( !actuallyAnimated || time <= startTime )
            return startTransform( v );
        else if ( time >= endTime )
            return endTransform( v );
        Transform t = Interpolate( time );
        return t( v );
    }

    Normal3f AnimatedTransform::operator()( Normal3f n, Float time ) const
    {
        if ( !actuallyAnimated || time <= startTime )
            return startTransform( n );
        else if ( time >= endTime )
            return endTransform( n );
        Transform t = Interpolate( time );
        return t( n );
    }
    Normal3f::Simd AnimatedTransform::operator()( const Normal3f::Simd& n, Float time ) const
    {
        if ( !actuallyAnimated || time <= startTime )
            return startTransform( n );
        else if ( time >= endTime )
            return endTransform( n );
        Transform t = Interpolate( time );
        return t( n );
    }

    PBRT_CPU_GPU Interaction AnimatedTransform::operator()( const Interaction& it ) const
    {
        if ( !actuallyAnimated )
            return startTransform( it );
        Transform t = Interpolate( it.time );
        return t( it );
    }

    PBRT_CPU_GPU Interaction AnimatedTransform::ApplyInverse( const Interaction& it ) const
    {
        if ( !actuallyAnimated )
            return startTransform.ApplyInverse( it );
        Transform t = Interpolate( it.time );
        return t.ApplyInverse( it );
    }

    PBRT_CPU_GPU SurfaceInteraction AnimatedTransform::operator()( const SurfaceInteraction& it ) const
    {
        if ( !actuallyAnimated )
            return startTransform( it );
        Transform t = Interpolate( it.time );
        return t( it );
    }

    PBRT_CPU_GPU SurfaceInteraction AnimatedTransform::ApplyInverse( const SurfaceInteraction& it ) const
    {
        if ( !actuallyAnimated )
            return startTransform.ApplyInverse( it );
        Transform t = Interpolate( it.time );
        return t.ApplyInverse( it );
    }

    std::string AnimatedTransform::ToString( ) const
    {
        return StringPrintf( "[ AnimatedTransform startTransform: %s endTransform: %s "
            "startTime: %f endTime: %f actuallyAnimated: %s T: [ %s %s ] "
            "R: [ %s %s ] S: [ %s %s ] hasRotation: %s ]",
            startTransform, endTransform, startTime, endTime,
            actuallyAnimated, T[ 0 ], T[ 1 ], R[ 0 ], R[ 1 ], S[ 0 ], S[ 1 ],
            hasRotation );
    }

    PBRT_CPU_GPU Transform AnimatedTransform::Interpolate( Float time ) const
    {
        // Handle boundary conditions for matrix interpolation
        if ( !actuallyAnimated || time <= startTime )
            return startTransform;
        if ( time >= endTime )
            return endTransform;

        Float dt = ( time - startTime ) / ( endTime - startTime );
        // Interpolate translation at _dt_
        Vector3f trans = ( 1 - dt ) * T[ 0 ] + dt * T[ 1 ];

        // Interpolate rotation at _dt_
        Quaternion rotate = Slerp( dt, R[ 0 ], R[ 1 ] );

        // Interpolate scale at _dt_
        SquareMatrix<4> scale = ( 1 - dt ) * S[ 0 ] + dt * S[ 1 ];

        // Return interpolated matrix as product of interpolated components
        return Translate( trans ) * Transform( rotate ) * Transform( scale );
    }

    PBRT_CPU_GPU Bounds3f AnimatedTransform::MotionBounds( const Bounds3f& b ) const
    {
        // Handle easy cases for _Bounds3f_ motion bounds
        if ( !actuallyAnimated )
            return startTransform( b );
        if ( !hasRotation )
            return Union( startTransform( b ), endTransform( b ) );

        // Return motion bounds accounting for animated rotation
        Bounds3f bounds;
        for ( int corner = 0; corner < 8; ++corner )
            bounds = Union( bounds, BoundPointMotion( b.Corner( corner ) ) );
        return bounds;
    }

    PBRT_CPU_GPU Bounds3f AnimatedTransform::BoundPointMotion( Point3f p ) const
    {
        if ( !actuallyAnimated )
            return Bounds3f( startTransform( p ) );
        Bounds3f bounds( startTransform( p ), endTransform( p ) );
        Float cosTheta = ScalarDot( R[ 0 ], R[ 1 ] );
        Float theta = SafeACos( cosTheta );
        for ( int c = 0; c < 3; ++c )
        {
            // Find any motion derivative zeros for the component _c_
            Float zeros[ 8 ];
            int nZeros = 0;
            FindZeros( c1[ c ].Eval( p ), c2[ c ].Eval( p ), c3[ c ].Eval( p ), c4[ c ].Eval( p ),
                c5[ c ].Eval( p ), theta, Interval( 0., 1. ), zeros, &nZeros );
            NCHECK_LE( nZeros, PBRT_ARRAYSIZE( zeros ) );

            // Expand bounding box for any motion derivative zeros found
            for ( int i = 0; i < nZeros; ++i )
            {
                Point3f pz = ( *this )( p, Lerp( zeros[ i ], startTime, endTime ) );
                bounds = Union( bounds, pz );
            }
        }
        return bounds;
    }

    PBRT_CPU_GPU void AnimatedTransform::FindZeros( Float c1, Float c2, Float c3, Float c4, Float c5,
        Float theta, Interval tInterval,
        pstdo::span<Float> zeros, int* nZeros, int depth )
    {
        Interval sinV;
        Interval cosV;
        SinCos( Interval( 2 * theta ) * tInterval, &sinV, &cosV );

        // Evaluate motion derivative in interval form, return if no zeros
        Interval dadt =
            Interval( c1 ) +
            ( Interval( c2 ) + Interval( c3 ) * tInterval ) * cosV +
            ( Interval( c4 ) + Interval( c5 ) * tInterval ) * sinV;
        if ( dadt.LowerBound( ) > 0 || dadt.UpperBound( ) < 0 ||
            dadt.LowerBound( ) == dadt.UpperBound( ) )
            return;

        // Either split range and recurse or report a zero
        if ( depth > 0 && dadt.Width( ) > 1e-3 )
        {
            // Split _tInterval_ and check both resulting intervals
            Float mid = tInterval.Midpoint( );
            FindZeros( c1, c2, c3, c4, c5, theta, Interval( tInterval.LowerBound( ), mid ), zeros,
                nZeros, depth - 1 );
            FindZeros( c1, c2, c3, c4, c5, theta, Interval( mid, tInterval.UpperBound( ) ), zeros,
                nZeros, depth - 1 );

        }
        else
        {
            // Use Newton's method to refine zero
            Float tNewton = tInterval.Midpoint( );
            for ( int i = 0; i < 4; ++i )
            {
                // Evaluate motion function derivative and its derivative at _tNewton_
                Float sinV;
                Float cosV;
                SinCos( 2 * theta * tNewton, &sinV, &cosV );

                Float fNewton = c1 + ( c2 + c3 * tNewton ) * cosV +
                    ( c4 + c5 * tNewton ) * sinV;
                Float fPrimeNewton =
                    ( c3 + 2 * ( c4 + c5 * tNewton ) * theta ) * cosV +
                    ( c5 - 2 * ( c2 + c3 * tNewton ) * theta ) * sinV;

                if ( fNewton == 0 || fPrimeNewton == 0 )
                    break;
                tNewton = tNewton - fNewton / fPrimeNewton;
            }

            // Record zero if refined zero is in interval
            if ( tNewton >= tInterval.LowerBound( ) - 1e-3f &&
                tNewton < tInterval.UpperBound( ) + 1e-3f )
            {
                zeros[ *nZeros ] = tNewton;
                ( *nZeros )++;
            }
        }
    }
}


