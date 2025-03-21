//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard 
//

#pragma once

#include "HDMCMatrix3.h"
#include "HDMCBoundingSphere.h"

namespace Harlinn::Windows::DirectX::MiniEngine::Math
{
    // Orthonormal basis (just rotation via quaternion) and translation
    class OrthogonalTransform;

    // A 3x4 matrix that allows for asymmetric skew and scale
    class AffineTransform;

    // Uniform scale and translation that can be compactly represented in a vec4
    class ScaleAndTranslation;

    // Uniform scale, rotation (quaternion), and translation that fits in two vec4s
    class UniformTransform;

    // This transform strictly prohibits non-uniform scale.  Scale itself is barely tolerated.
    class OrthogonalTransform
    {
#ifdef HDMC_USES_HCC_MATH
        using Constants = m::Traits::Constants;
#endif
        Quaternion m_rotation;
        Vector3 m_translation;
    public:
        INLINE OrthogonalTransform( ) 
#ifdef HDMC_USES_HCC_MATH
            : m_rotation( Quaternion::Identity() ),
              m_translation( Constants::Zero )
#else
            : m_rotation( kIdentity ), 
              m_translation( kZero ) 
#endif
        {
            
        }
        INLINE OrthogonalTransform( Quaternion rotate ) 
            : m_rotation( rotate ), 
#ifdef HDMC_USES_HCC_MATH
              m_translation( Constants::Zero )
#else
              m_translation( kZero )
#endif
        {
            
        }
        INLINE OrthogonalTransform( Vector3 translate ) 
#ifdef HDMC_USES_HCC_MATH
            : m_rotation( Quaternion::Identity( ) ),
#else
            : m_rotation( kIdentity ), 
#endif
              m_translation( translate ) 
        {
            
        }
        INLINE OrthogonalTransform( Quaternion rotate, Vector3 translate ) 
            : m_rotation( rotate ), 
              m_translation( translate ) 
        {
            
        }
        INLINE OrthogonalTransform( const Matrix3& mat ) 
#ifdef HDMC_USES_HCC_MATH
            : m_rotation( Quaternion::FromMatrix( mat.simd ) ),
              m_translation( Constants::Zero )
#else
            : m_rotation( mat ),
              m_translation( kZero ) 
#endif
        {
            
        }
        INLINE OrthogonalTransform( const Matrix3& mat, Vector3 translate ) 
#ifdef HDMC_USES_HCC_MATH
            : m_rotation( Quaternion::FromMatrix( mat.simd ) ),
#else
            : m_rotation( mat ), 
#endif
              m_translation( translate ) 
        {
            
        }
        INLINE OrthogonalTransform( EIdentityTag ) 
#ifdef HDMC_USES_HCC_MATH
            : m_rotation( Constants::IdentityR4 ),
              m_translation( Constants::Zero )
#else
            : m_rotation( kIdentity ), 
              m_translation( kZero ) 
#endif
        {
            
        }
#ifdef HDMC_USES_HCC_MATH
        template<size_t N>
            requires (N > 3)
        INLINE explicit OrthogonalTransform( const std::array<m::SIMDType,N>& mat ) 
            : m_rotation( Quaternion::FromMatrix( mat ) ),
              m_translation( mat[ 3 ] )
        {
            
        }
#else
        INLINE explicit OrthogonalTransform( const XMMATRIX& mat ) 
        { 
            *this = OrthogonalTransform( Matrix3( mat ), Vector3( mat.r[ 3 ] ) ); 
        }
#endif

#ifdef HDMC_USES_HCC_MATH
        INLINE void SetRotation( const Quaternion& q ) 
        { 
            m_rotation = q; 
        }
#else
        INLINE void SetRotation( Quaternion q ) 
        { 
            m_rotation = q; 
        }
#endif

#ifdef HDMC_USES_HCC_MATH
        INLINE void SetTranslation( const Vector3& v ) 
        { 
            m_translation = v; 
        }
#else
        INLINE void SetTranslation( Vector3 v ) 
        { 
            m_translation = v; 
        }
#endif

#ifdef HDMC_USES_HCC_MATH
        INLINE const Quaternion& GetRotation( ) const 
        { 
            return m_rotation; 
        }
#else
        INLINE Quaternion GetRotation( ) const { return m_rotation; }
#endif
#ifdef HDMC_USES_HCC_MATH
        INLINE const Vector3& GetTranslation( ) const 
        { 
            return m_translation; 
        }
#else
        INLINE Vector3 GetTranslation( ) const { return m_translation; }
#endif
        static INLINE OrthogonalTransform MakeXRotation( float angle ) 
        { 
#ifdef HDMC_USES_HCC_MATH
            return OrthogonalTransform( Quaternion::FromAxisAndAngle( Vector3( Constants::IdentityR1 ), angle ) );
#else
            return OrthogonalTransform( Quaternion( Vector3( kXUnitVector ), angle ) ); 
#endif
        }
        static INLINE OrthogonalTransform MakeYRotation( float angle ) 
        { 
#ifdef HDMC_USES_HCC_MATH
            return OrthogonalTransform( Quaternion::FromAxisAndAngle( Vector3( Constants::IdentityR2 ), angle ) );
#else
            return OrthogonalTransform( Quaternion( Vector3( kYUnitVector ), angle ) ); 
#endif
        }
        static INLINE OrthogonalTransform MakeZRotation( float angle ) 
        { 
#ifdef HDMC_USES_HCC_MATH
            return OrthogonalTransform( Quaternion::FromAxisAndAngle( Vector3( Constants::IdentityR3 ), angle ) );
#else
            return OrthogonalTransform( Quaternion( Vector3( kZUnitVector ), angle ) ); 
#endif
        }
        static INLINE OrthogonalTransform MakeTranslation( Vector3 translate ) { return OrthogonalTransform( translate ); }

        INLINE Vector3 operator* ( Vector3 vec ) const 
        { 
            return m_rotation * vec + m_translation;
        }
        INLINE Vector4 operator* ( Vector4 vec ) const
        {
#ifdef HDMC_USES_HCC_MATH
            return
                Vector4( SetWToZero( m::Rotate( ToVector3( vec ), m_rotation ).simd  ) ) +
                Vector4( SetWToOne( m_translation.simd ) ) * vec.W( );
#else
            return
                Vector4( SetWToZero( m_rotation * Vector3( ( XMVECTOR )vec ) ) ) +
                Vector4( SetWToOne( m_translation ) ) * vec.GetW( );
#endif
        }
        INLINE BoundingSphere operator* ( BoundingSphere sphere ) const
        {
            return BoundingSphere( *this * sphere.GetCenter( ), sphere.GetRadius( ) );
        }

        INLINE OrthogonalTransform operator* ( const OrthogonalTransform& xform ) const
        {
#ifdef HDMC_USES_HCC_MATH
            return OrthogonalTransform( xform.m_rotation * m_rotation, m_rotation * xform.m_translation + m_translation );
#else
            return OrthogonalTransform( m_rotation * xform.m_rotation, m_rotation * xform.m_translation + m_translation );
#endif
        }

        INLINE OrthogonalTransform operator~ ( ) const
        {
            Quaternion invertedRotation = ~m_rotation;
            return OrthogonalTransform( invertedRotation, invertedRotation * -m_translation );
        }

    private:

        
    };

    //
    // A transform that lacks rotation and has only uniform scale.
    //
    class ScaleAndTranslation
    {
        Vector4 m_repr;
    public:
#ifdef HDMC_USES_HCC_MATH
        using Constants = m::Traits::Constants;
#endif
        INLINE ScaleAndTranslation( )
        {
        }
        INLINE ScaleAndTranslation( EIdentityTag )
#ifdef HDMC_USES_HCC_MATH
            : m_repr( Constants::IdentityR4 )
#else
            : m_repr( kWUnitVector )
#endif
        {
        }
        INLINE ScaleAndTranslation( float tx, float ty, float tz, float scale )
            : m_repr( tx, ty, tz, scale )
        {
        }
        INLINE ScaleAndTranslation( Vector3 translate, Scalar scale )
        {
            m_repr = Vector4( translate );
            m_repr.SetW( scale );
        }
#ifdef HDMC_USES_HCC_MATH
        INLINE explicit ScaleAndTranslation( const Vector4& v )
            : m_repr( v )
        {
        }
        INLINE explicit ScaleAndTranslation( const m::SIMDType& v )
            : m_repr( v )
        {
        }
#else
        INLINE explicit ScaleAndTranslation( const XMVECTOR& v )
            : m_repr( v )
        {
        }
#endif
        INLINE void SetScale( Scalar s ) 
        { 
            m_repr.SetW( s ); 
        }
        INLINE void SetTranslation( Vector3 t ) 
        { 
            m_repr.SetXYZ( t );
        }

        INLINE Scalar GetScale( ) const 
        { 
#ifdef HDMC_USES_HCC_MATH
            return Scalar( m_repr.W( ).simd );
#else
            return m_repr.GetW( ); 
#endif
        }
        INLINE Vector3 GetTranslation( ) const { return ( Vector3 )m_repr; }

        INLINE BoundingSphere operator*( const BoundingSphere& sphere ) const
        {
            
#ifdef HDMC_USES_HCC_MATH
            Vector4 scaledSphere = ( Vector4 )sphere * Vector4(  GetScale( ).simd );
            Vector4 translation = Vector4( SetWToZero( m_repr.simd ) );
#else
            Vector4 scaledSphere = ( Vector4 )sphere * GetScale( );
            Vector4 translation = Vector4( SetWToZero( m_repr ) );
#endif
            return BoundingSphere( scaledSphere + translation );
        }

    
    };

    //
    // This transform allows for rotation, translation, and uniform scale
    // 
    class UniformTransform
    {
        Quaternion m_rotation;
        ScaleAndTranslation m_translationScale;
    public:
#ifdef HDMC_USES_HCC_MATH
        using Constants = m::Traits::Constants;
#endif
        INLINE UniformTransform( )
        {
        }
        INLINE UniformTransform( EIdentityTag )
#ifdef HDMC_USES_HCC_MATH
            : m_rotation( Constants::IdentityR4 ),
#else
            : m_rotation( kIdentity ), 
#endif
              m_translationScale( kIdentity )
        {
        }
        INLINE UniformTransform( Quaternion rotation, ScaleAndTranslation transScale )
            : m_rotation( rotation ), m_translationScale( transScale )
        {
        }
        INLINE UniformTransform( Quaternion rotation, Scalar scale, Vector3 translation )
            : m_rotation( rotation ), m_translationScale( translation, scale )
        {
        }

        INLINE void SetRotation( Quaternion r ) { m_rotation = r; }
        INLINE void SetScale( Scalar s ) { m_translationScale.SetScale( s ); }
        INLINE void SetTranslation( Vector3 t ) { m_translationScale.SetTranslation( t ); }


        INLINE Quaternion GetRotation( ) const { return m_rotation; }
        INLINE Scalar GetScale( ) const { return m_translationScale.GetScale( ); }
        INLINE Vector3 GetTranslation( ) const { return m_translationScale.GetTranslation( ); }


        INLINE Vector3 operator*( Vector3 vec ) const
        {
            return m_rotation * ( vec * m_translationScale.GetScale( ) ) + m_translationScale.GetTranslation( );
        }

        INLINE BoundingSphere operator*( BoundingSphere sphere ) const
        {
            return BoundingSphere( *this * sphere.GetCenter( ), GetScale( ) * sphere.GetRadius( ) );
        }
    };

    // A AffineTransform is a 3x4 matrix with an implicit 4th row = [0,0,0,1].  This is used to perform a change of
    // basis on 3D points.  An affine transformation does not have to have orthonormal basis vectors.
    class AffineTransform
    {
        Matrix3 m_basis;
        Vector3 m_translation;
    public:
#ifdef HDMC_USES_HCC_MATH
        using Traits = m::Traits;
        using Constants = typename Traits::Constants;
#endif
        INLINE AffineTransform( )
        {
        }
#ifdef HDMC_USES_HCC_MATH
        INLINE AffineTransform( Vector3 x, Vector3 y, Vector3 z, Vector3 w )
            : m_basis( ToMatrix3( x, y, z ) ), m_translation( w )
        {
        }
        INLINE AffineTransform( Vector3 translate )
            : m_basis( Matrix3::Identity( ) ), m_translation( translate )
        {
        }
#else
        INLINE AffineTransform( Vector3 x, Vector3 y, Vector3 z, Vector3 w )
            : m_basis( x, y, z ), m_translation( w )
        {
        }
        INLINE AffineTransform( Vector3 translate )
            : m_basis( kIdentity ), m_translation( translate )
        {
        }
#endif
#ifdef HDMC_USES_HCC_MATH
        INLINE AffineTransform( const Matrix3& mat, Vector3 translate = Vector3( ) )
            : m_basis( mat ), m_translation( translate )
        {
        }
#else
        INLINE AffineTransform( const Matrix3& mat, Vector3 translate = Vector3( kZero ) )
            : m_basis( mat ), m_translation( translate )
        {
        }
#endif

#ifdef HDMC_USES_HCC_MATH
        INLINE AffineTransform( Quaternion rot, Vector3 translate = Vector3( ) )
            : m_basis( ToMatrix3( rot ) ), m_translation( translate )
        {
        }
#else
        INLINE AffineTransform( Quaternion rot, Vector3 translate = Vector3( kZero ) )
            : m_basis( rot ), m_translation( translate )
        {
        }
#endif
#ifdef HDMC_USES_HCC_MATH
        INLINE AffineTransform( const OrthogonalTransform& xform )
            : m_basis( ToMatrix3( xform.GetRotation( ) ) ), m_translation( xform.GetTranslation( ) )
        {
        }
#else
        INLINE AffineTransform( const OrthogonalTransform& xform )
            : m_basis( xform.GetRotation( ) ), m_translation( xform.GetTranslation( ) )
        {
        }
#endif
        INLINE AffineTransform( const UniformTransform& xform )
        {
#ifdef HDMC_USES_HCC_MATH
            m_basis = ToMatrix3( xform.GetRotation( ) ) * xform.GetScale( );
#else
            m_basis = Matrix3( xform.GetRotation( ) ) * xform.GetScale( );
#endif

            m_translation = xform.GetTranslation( );
        }
#ifdef HDMC_USES_HCC_MATH
        INLINE AffineTransform( EIdentityTag )
            : m_basis( Matrix3::Identity() ), m_translation( Constants::Zero )
        {
        }
#else
        INLINE AffineTransform( EIdentityTag )
            : m_basis( kIdentity ), m_translation( kZero )
        {
        }
#endif
#ifdef HDMC_USES_HCC_MATH
        template<size_t N>
            requires (N == 3)
        INLINE explicit AffineTransform( const std::array<m::SIMDType,N>& mat )
            : m_basis( mat )
        {
        }

        template<size_t N>
            requires ( N > 3 )
        INLINE explicit AffineTransform( const std::array<m::SIMDType, N>& mat )
            : m_basis( mat ), m_translation( SetWToOne( mat[ 3 ] ) )
        {
        }
#else
        INLINE explicit AffineTransform( const XMMATRIX& mat )
            : m_basis( mat ), m_translation( mat.r[ 3 ] )
        {
        }
#endif

#ifdef HDMC_USES_HCC_MATH
        INLINE operator const Matrix3&( ) const { return m_basis; }
        INLINE const Matrix3& Basis( ) const { return m_basis; }

        INLINE Matrix4 ToMatrix4( ) const 
        { 
            return Matrix4( m_basis.simd[ 0 ], m_basis.simd[ 1 ], m_basis.simd[ 2 ], m_translation.simd );
        }

        INLINE operator Matrix4( ) const 
        { 
            return ToMatrix4( );
        }
        

        INLINE void SetX( Vector3 x ) 
        { 
            m_basis.simd[ 0 ] = x.simd; 
        }
        INLINE void SetY( Vector3 y )
        {
            m_basis.simd[ 1 ] = y.simd;
        }
        INLINE void SetZ( Vector3 z )
        {
            m_basis.simd[ 2 ] = z.simd;
        }
#else
        INLINE operator XMMATRIX( ) const { return ( XMMATRIX& )*this; }

        INLINE void SetX( Vector3 x ) { m_basis.SetX( x ); }
        INLINE void SetY( Vector3 y ) { m_basis.SetY( y ); }
        INLINE void SetZ( Vector3 z ) { m_basis.SetZ( z ); }
#endif
        INLINE void SetTranslation( Vector3 w ) { m_translation = w; }
        INLINE void SetBasis( const Matrix3& basis ) { m_basis = basis; }

#ifdef HDMC_USES_HCC_MATH
        INLINE Vector3 GetX( ) const { return m_basis.simd[ 0 ]; }
        INLINE Vector3 GetY( ) const { return m_basis.simd[ 1 ]; }
        INLINE Vector3 GetZ( ) const { return m_basis.simd[ 2 ]; }
#else
        INLINE Vector3 GetX( ) const { return m_basis.GetX( ); }
        INLINE Vector3 GetY( ) const { return m_basis.GetY( ); }
        INLINE Vector3 GetZ( ) const { return m_basis.GetZ( ); }
#endif
        INLINE Vector3 GetTranslation( ) const { return m_translation; }
        INLINE const Matrix3& GetBasis( ) const { return ( const Matrix3& )*this; }

#ifdef HDMC_USES_HCC_MATH
        static INLINE AffineTransform MakeXRotation( float angle ) 
        { 
            return AffineTransform( Matrix3( m::RotationX( angle ).simd ) );
        }
        static INLINE AffineTransform MakeYRotation( float angle ) 
        { 
            return AffineTransform( Matrix3( m::RotationY( angle ).simd ) );
        }
        static INLINE AffineTransform MakeZRotation( float angle ) 
        { 
            return AffineTransform( Matrix3( m::RotationZ( angle ).simd ) );
        }
        static INLINE AffineTransform MakeScale( float scale ) 
        { 
            return AffineTransform( Matrix3( m::Scaling( scale ).simd ) );
        }
        static INLINE AffineTransform MakeScale( Vector3 scale ) 
        { 
            return AffineTransform( Matrix3( m::Scaling( scale ).simd ) );
        }
#else
        static INLINE AffineTransform MakeXRotation( float angle ) { return AffineTransform( Matrix3::MakeXRotation( angle ) ); }
        static INLINE AffineTransform MakeYRotation( float angle ) { return AffineTransform( Matrix3::MakeYRotation( angle ) ); }
        static INLINE AffineTransform MakeZRotation( float angle ) { return AffineTransform( Matrix3::MakeZRotation( angle ) ); }
        static INLINE AffineTransform MakeScale( float scale ) { return AffineTransform( Matrix3::MakeScale( scale ) ); }
        static INLINE AffineTransform MakeScale( Vector3 scale ) { return AffineTransform( Matrix3::MakeScale( scale ) ); }
#endif
        static INLINE AffineTransform MakeTranslation( Vector3 translate ) { return AffineTransform( translate ); }

        INLINE Vector3 operator* ( Vector3 vec ) const { return m_basis * vec + m_translation; }

        INLINE AffineTransform operator* ( const AffineTransform& mat ) const
        {
            return AffineTransform( m_basis * mat.m_basis, *this * mat.GetTranslation( ) );
        }

    
        
    };


    inline void Dump( const char* name, const OrthogonalTransform& transform, const char* file, int line, const char* function )
    {
        auto r = transform.GetRotation( );
        auto t = transform.GetTranslation( );

#ifdef HDMC_USES_HCC_MATH
        m::Quaternion<float> rotation( r );
        m::Vector<float, 4> translation( Vector4( t.simd ) );
#else
        ::DirectX::XMFLOAT4A rotation;
        ::DirectX::XMStoreFloat4A( &rotation, r );

        ::DirectX::XMFLOAT4A translation;
        ::DirectX::XMStoreFloat4A( &translation, t );
#endif
        PrintLn( "// {}:", name );
#ifdef HDMC_USES_HCC_MATH
        PrintLn( "// Rotation [ {}, {}, {}, {} ]", rotation.v.x, rotation.v.y, rotation.v.z, rotation.w );
#else
        PrintLn( "// Rotation [ {}, {}, {}, {} ]", rotation.x, rotation.y, rotation.z, rotation.w );
#endif
        PrintLn( "// Translation [ {}, {}, {}, {} ]", translation.x, translation.y, translation.z, translation.w );
        PrintLn( "// Function: {} ", function );
        PrintLn( "// Position: {}({})", file, line );
    }

    inline void Dump( const char* name, const ScaleAndTranslation& transform, const char* file, int line, const char* function )
    {

        auto t = transform.GetTranslation( );
#ifdef HDMC_USES_HCC_MATH
        m::Vector<float, 4> translation( Vector4( t.simd ) );
#else
        ::DirectX::XMFLOAT4A translation;
        ::DirectX::XMStoreFloat4A( &translation, t );
#endif
        PrintLn( "// {}:", name );
        PrintLn( "// Translation and Scale [ {}, {}, {}, {} ]", translation.x, translation.y, translation.z, translation.w );
        PrintLn( "// Function: {} ", function );
        PrintLn( "// Position: {}({})", file, line );
    }

    inline void Dump( const char* name, const UniformTransform& transform, const char* file, int line, const char* function )
    {

        auto r = transform.GetRotation( );
        auto t = transform.GetTranslation( );
#ifdef HDMC_USES_HCC_MATH
        m::Quaternion<float> rotation( r );
        m::Vector<float, 4> translation( Vector4( t.simd ) );
#else
        ::DirectX::XMFLOAT4A rotation;
        ::DirectX::XMStoreFloat4A( &rotation, r );

        ::DirectX::XMFLOAT4A translation;
        ::DirectX::XMStoreFloat4A( &translation, t );
#endif
        PrintLn( "// {}:", name );
#ifdef HDMC_USES_HCC_MATH
        PrintLn( "// Rotation [ {}, {}, {}, {} ]", rotation.v.x, rotation.v.y, rotation.v.z, rotation.w );
#else
        PrintLn( "// Rotation [ {}, {}, {}, {} ]", rotation.x, rotation.y, rotation.z, rotation.w );
#endif
        PrintLn( "// Translation and Scale [ {}, {}, {}, {} ]", translation.x, translation.y, translation.z, translation.w );
        PrintLn( "// Function: {} ", function );
        PrintLn( "// Position: {}({})", file, line );
    }

    inline void Dump( const char* name, const AffineTransform& transform, const char* file, int line, const char* function )
    {
        auto m = transform.GetBasis( );
        auto t = transform.GetTranslation( );
#ifdef HDMC_USES_HCC_MATH
        m::Vector<float, 4> matrix[ 3 ]{ Vector4( m.simd[ 0 ] ), Vector4( m.simd[ 1 ] ), Vector4( m.simd[ 2 ] ) };
        m::Vector<float, 4> translation( Vector4( t.simd ) );
#else
        ::DirectX::XMFLOAT4A matrix[ 3 ];
        ::DirectX::XMStoreFloat4A( &matrix[ 0 ], m.GetX( ) );
        ::DirectX::XMStoreFloat4A( &matrix[ 1 ], m.GetY( ) );
        ::DirectX::XMStoreFloat4A( &matrix[ 2 ], m.GetZ( ) );

        ::DirectX::XMFLOAT4A translation;
        ::DirectX::XMStoreFloat4A( &translation, t );
#endif

        PrintLn( "// {}:", name );
        PrintLn( "// Basis" );
        PrintLn( "//   [ {}, {}, {}, {} ]", matrix[ 0 ].x, matrix[ 0 ].y, matrix[ 0 ].z, matrix[ 0 ].w );
        PrintLn( "//   [ {}, {}, {}, {} ]", matrix[ 1 ].x, matrix[ 1 ].y, matrix[ 1 ].z, matrix[ 1 ].w );
        PrintLn( "//   [ {}, {}, {}, {} ]", matrix[ 2 ].x, matrix[ 2 ].y, matrix[ 2 ].z, matrix[ 2 ].w );
        PrintLn( "// Translation" );
        PrintLn( "//   [ {}, {}, {}, {} ]", translation.x, translation.y, translation.z, translation.w );
        PrintLn( "// Function: {} ", function );
        PrintLn( "// Position: {}({})", file, line );
    }


}