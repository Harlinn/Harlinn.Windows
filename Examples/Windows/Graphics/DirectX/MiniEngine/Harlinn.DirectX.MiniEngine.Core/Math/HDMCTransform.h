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
            : m_rotation( Constants::IdentityR4 ),
              m_translation( Constants::Zero )
#else
            : m_rotation( kIdentity ), 
              m_translation( kZero ) 
#endif
        {}
        INLINE OrthogonalTransform( Quaternion rotate ) 
            : m_rotation( rotate ), 
#ifdef HDMC_USES_HCC_MATH
              m_translation( Constants::Zero )
#else
              m_translation( kZero )
#endif
        {}
        INLINE OrthogonalTransform( Vector3 translate ) 
#ifdef HDMC_USES_HCC_MATH
            : m_rotation( Constants::IdentityR4 ),
#else
            : m_rotation( kIdentity ), 
#endif
              m_translation( translate ) 
        {}
        INLINE OrthogonalTransform( Quaternion rotate, Vector3 translate ) 
            : m_rotation( rotate ), 
              m_translation( translate ) 
        {}
        INLINE OrthogonalTransform( const Matrix3& mat ) 
#ifdef HDMC_USES_HCC_MATH
            : m_rotation( Quaternion::FromMatrix( mat.simd ) ),
              m_translation( Constants::Zero )
#else
            : m_rotation( mat ),
              m_translation( kZero ) 
#endif
        {}
        INLINE OrthogonalTransform( const Matrix3& mat, Vector3 translate ) 
#ifdef HDMC_USES_HCC_MATH
            : m_rotation( Quaternion::FromMatrix( mat.simd ) ),
#else
            : m_rotation( mat ), 
#endif
              m_translation( translate ) 
        {}
        INLINE OrthogonalTransform( EIdentityTag ) 
#ifdef HDMC_USES_HCC_MATH
            : m_rotation( Constants::IdentityR4 ),
              m_translation( Constants::Zero )
#else
            : m_rotation( kIdentity ), 
              m_translation( kZero ) 
#endif
        {}
#ifdef HDMC_USES_HCC_MATH
        template<size_t N>
            requires (N > 3)
        INLINE explicit OrthogonalTransform( const std::array<m::SIMDType,N>& mat ) 
            : m_rotation( Quaternion::FromMatrix( mat ) ),
              m_translation( mat[ 3 ] )
        { }
#else
        INLINE explicit OrthogonalTransform( const XMMATRIX& mat ) { *this = OrthogonalTransform( Matrix3( mat ), Vector3( mat.r[ 3 ] ) ); }
#endif

#ifdef HDMC_USES_HCC_MATH
        INLINE void SetRotation( const Quaternion& q ) 
        { 
            m_rotation = q; 
        }
#else
        INLINE void SetRotation( Quaternion q ) { m_rotation = q; }
#endif

#ifdef HDMC_USES_HCC_MATH
        INLINE void SetTranslation( const Vector3& v ) 
        { 
            m_translation = v; 
        }
#else
        INLINE void SetTranslation( Vector3 v ) { m_translation = v; }
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
#ifdef HDMC_USES_HCC_MATH
            return m::Rotate( vec, m_rotation ) + m_translation;
#else
            return m_rotation * vec + m_translation; 
#endif
        }
        INLINE Vector4 operator* ( Vector4 vec ) const
        {
#ifdef HDMC_USES_HCC_MATH
            return
                Vector4( SetWToZero( m::Rotate( Vector3( vec.simd ), m_rotation ).simd  ) ) +
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
            return OrthogonalTransform( m_rotation * xform.m_rotation, m::Rotate( xform.m_translation, m_rotation ) + m_translation );
#else
            return OrthogonalTransform( m_rotation * xform.m_rotation, m_rotation * xform.m_translation + m_translation );
#endif
        }

        INLINE OrthogonalTransform operator~ ( ) const
        {
#ifdef HDMC_USES_HCC_MATH
            Quaternion invertedRotation = m::Conjugate( m_rotation );
            return OrthogonalTransform( invertedRotation, m::Rotate( -m_translation, invertedRotation ) );
#else
            Quaternion invertedRotation = ~m_rotation;
            return OrthogonalTransform( invertedRotation, invertedRotation * -m_translation );
#endif
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
        INLINE void SetScale( Scalar s ) { m_repr.SetW( s ); }
        INLINE void SetTranslation( Vector3 t ) 
        { 
#ifdef HDMC_USES_HCC_MATH
            m_repr.SetXYZ( t.simd ); 
#else
            m_repr.SetXYZ( t );
#endif
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
            Vector4 scaledSphere = ( Vector4 )sphere * Vector4(  GetScale( ).ToSimd() );
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
#ifdef HDMC_USES_HCC_MATH
            return m::Rotate( ( vec * Vector3( m_translationScale.GetScale( ).ToSimd( ) ) ), m_rotation ) + m_translationScale.GetTranslation( );
#else
            return m_rotation * ( vec * m_translationScale.GetScale( ) ) + m_translationScale.GetTranslation( );
#endif
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
        using Constants = m::Traits::Constants;
#endif
        INLINE AffineTransform( )
        {
        }
        INLINE AffineTransform( Vector3 x, Vector3 y, Vector3 z, Vector3 w )
            : m_basis( x, y, z ), m_translation( w )
        {
        }
        INLINE AffineTransform( Vector3 translate )
            : m_basis( kIdentity ), m_translation( translate )
        {
        }
        INLINE AffineTransform( const Matrix3& mat, Vector3 translate = Vector3( kZero ) )
            : m_basis( mat ), m_translation( translate )
        {
        }
        INLINE AffineTransform( Quaternion rot, Vector3 translate = Vector3( kZero ) )
            : m_basis( rot ), m_translation( translate )
        {
        }
        INLINE AffineTransform( const OrthogonalTransform& xform )
            : m_basis( xform.GetRotation( ) ), m_translation( xform.GetTranslation( ) )
        {
        }
        INLINE AffineTransform( const UniformTransform& xform )
        {
            m_basis = Matrix3( xform.GetRotation( ) ) * xform.GetScale( );
            m_translation = xform.GetTranslation( );
        }
        INLINE AffineTransform( EIdentityTag )
            : m_basis( kIdentity ), m_translation( kZero )
        {
        }
        INLINE explicit AffineTransform( const XMMATRIX& mat )
            : m_basis( mat ), m_translation( mat.r[ 3 ] )
        {
        }

        INLINE operator XMMATRIX( ) const { return ( XMMATRIX& )*this; }

        INLINE void SetX( Vector3 x ) { m_basis.SetX( x ); }
        INLINE void SetY( Vector3 y ) { m_basis.SetY( y ); }
        INLINE void SetZ( Vector3 z ) { m_basis.SetZ( z ); }
        INLINE void SetTranslation( Vector3 w ) { m_translation = w; }
        INLINE void SetBasis( const Matrix3& basis ) { m_basis = basis; }

        INLINE Vector3 GetX( ) const { return m_basis.GetX( ); }
        INLINE Vector3 GetY( ) const { return m_basis.GetY( ); }
        INLINE Vector3 GetZ( ) const { return m_basis.GetZ( ); }
        INLINE Vector3 GetTranslation( ) const { return m_translation; }
        INLINE const Matrix3& GetBasis( ) const { return ( const Matrix3& )*this; }

        static INLINE AffineTransform MakeXRotation( float angle ) { return AffineTransform( Matrix3::MakeXRotation( angle ) ); }
        static INLINE AffineTransform MakeYRotation( float angle ) { return AffineTransform( Matrix3::MakeYRotation( angle ) ); }
        static INLINE AffineTransform MakeZRotation( float angle ) { return AffineTransform( Matrix3::MakeZRotation( angle ) ); }
        static INLINE AffineTransform MakeScale( float scale ) { return AffineTransform( Matrix3::MakeScale( scale ) ); }
        static INLINE AffineTransform MakeScale( Vector3 scale ) { return AffineTransform( Matrix3::MakeScale( scale ) ); }
        static INLINE AffineTransform MakeTranslation( Vector3 translate ) { return AffineTransform( translate ); }

        INLINE Vector3 operator* ( Vector3 vec ) const { return m_basis * vec + m_translation; }
        INLINE AffineTransform operator* ( const AffineTransform& mat ) const
        {
            return AffineTransform( m_basis * mat.m_basis, *this * mat.GetTranslation( ) );
        }

    
        
    };
}