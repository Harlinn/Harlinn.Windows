#pragma once
#ifndef HARLINN_COMMON_CORE_HCCTRANSFORMATIONS_H_
#define HARLINN_COMMON_CORE_HCCTRANSFORMATIONS_H_

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

#include "HCCVectorMath.h"

namespace Harlinn::Common::Core::Math
{

    class AffineTransformation
    {
    public:
        using value_type = float;
        using ValueType = float;
        using MatrixType = Math::SquareMatrix<ValueType, 3>;
        using MatrixSimd = typename MatrixType::Simd;
        using Matrix4Type = Math::SquareMatrix<ValueType, 4>;
        using Matrix4Simd = typename Matrix4Type::Simd;

        using Traits = typename MatrixSimd::Traits;
        using Constants = typename Traits::Constants;

        using Vector = Math::Vector3f;
        using VectorSimd = typename Vector::Simd;
        using Point = Math::Point3f;
        using PointSimd = typename Point::Simd;
        using Normal = Math::Normal3f;
        using NormalSimd = typename Normal::Simd;
    private:
        MatrixSimd matrix_;
        MatrixSimd inverseMatrix_;
        VectorSimd translation_;
    public:
        AffineTransformation( ) noexcept
            : matrix_( MatrixSimd::Identity( ) ), inverseMatrix_( MatrixSimd::Identity( ) ), translation_( Constants::Zero )
        { }

        explicit AffineTransformation( const MatrixType& matrix )
            : matrix_( matrix ), translation_( Constants::Zero )
        {
            inverseMatrix_ = Math::Inverse( matrix_ );
        }

        explicit AffineTransformation( const MatrixSimd& matrix )
            : matrix_( matrix ), translation_( Constants::Zero )
        {
            inverseMatrix_ = Math::Inverse( matrix_ );
        }

        explicit AffineTransformation( const Matrix4Type& matrix )
            : AffineTransformation( Matrix4Simd( matrix ) )
        { }

        explicit AffineTransformation( const Matrix4Simd& matrix )
            : matrix_( matrix.simd ), translation_( Traits::SetW( matrix.simd[3], 0.f) )
        {
            inverseMatrix_ = Math::Inverse( matrix_ );
        }

        AffineTransformation( const MatrixType& matrix, const Vector& translation )
            : matrix_( matrix ), translation_( translation )
        {
            inverseMatrix_ = Math::Inverse( matrix_ );
        }

        AffineTransformation( const MatrixSimd& matrix, const VectorSimd& translation )
            : matrix_( matrix ), translation_( translation )
        {
            inverseMatrix_ = Math::Inverse( matrix_ );
        }

        AffineTransformation( const MatrixType& matrix, const MatrixType& inverseMatrix )
            : matrix_( matrix ), inverseMatrix_( inverseMatrix ), translation_( Constants::Zero )
        { }
        AffineTransformation( const MatrixSimd& matrix, const MatrixSimd& inverseMatrix )
            : matrix_( matrix ), inverseMatrix_( inverseMatrix ), translation_( Constants::Zero )
        { }

        AffineTransformation( const MatrixType& matrix, const MatrixType& inverseMatrix, const Vector& translation )
            : matrix_( matrix ), inverseMatrix_( inverseMatrix ), translation_( translation )
        { }
        AffineTransformation( const MatrixSimd& matrix, const MatrixSimd& inverseMatrix, const VectorSimd& translation )
            : matrix_( matrix ), inverseMatrix_( inverseMatrix ), translation_( translation )
        { }

        explicit AffineTransformation( const Vector& translation ) noexcept
            : matrix_( MatrixSimd::Identity( ) ), inverseMatrix_( MatrixSimd::Identity( ) ), translation_( translation )
        { }

        explicit AffineTransformation( const VectorSimd& translation ) noexcept
            : matrix_( MatrixSimd::Identity( ) ), inverseMatrix_( MatrixSimd::Identity( ) ), translation_( translation )
        { }


        const MatrixSimd& Matrix( ) const noexcept
        { 
            return matrix_; 
        }
        const MatrixSimd& InverseMatrix( ) const noexcept
        { 
            return inverseMatrix_;
        }
        
        const VectorSimd& Translation( ) const noexcept
        {
            return translation_;
        }

        Matrix4Simd ToMatrix4( ) const noexcept
        {
            return Matrix4Simd( matrix_.simd[ 0 ], matrix_.simd[ 1 ], matrix_.simd[ 2 ], Traits::SetW( translation_.simd, 1.f ) );
        }
        Matrix4Simd InverseToMatrix4( ) const noexcept
        {
            return Matrix4Simd( inverseMatrix_.simd[ 0 ], inverseMatrix_.simd[ 1 ], inverseMatrix_.simd[ 2 ], Traits::SetW( (-translation_).simd, 1.f ) );
        }


        AffineTransformation Apply( const AffineTransformation& affineTransformation ) const noexcept
        {
            return AffineTransformation( matrix_ * affineTransformation.matrix_, 
                inverseMatrix_ * affineTransformation.inverseMatrix_, 
                Apply( affineTransformation.Translation() ) );
        }

        AffineTransformation ApplyInverse( const AffineTransformation& affineTransformation ) const noexcept
        {
            return AffineTransformation( inverseMatrix_ * affineTransformation.matrix_, 
                matrix_ * affineTransformation.inverseMatrix_, 
                ApplyInverse( affineTransformation.Translation( ) ) );
        }

        AffineTransformation operator()( const AffineTransformation& affineTransformation ) const noexcept
        {
            return Apply( affineTransformation );
        }


        VectorSimd Apply( const VectorSimd& v ) const noexcept
        {
            return VectorSimd(Traits::TransformNormal( v.simd, matrix_.simd[ 0 ], matrix_.simd[ 1 ], matrix_.simd[ 2 ] ));
        }

        VectorSimd Apply( const Vector& v ) const noexcept
        {
            return Apply( VectorSimd( v ) );
        }

        VectorSimd ApplyInverse( const VectorSimd& v ) const noexcept
        {
            return VectorSimd( Traits::TransformNormal( v.simd, inverseMatrix_.simd[ 0 ], inverseMatrix_.simd[ 1 ], inverseMatrix_.simd[ 2 ] ) );
        }

        VectorSimd ApplyInverse( const Vector& v ) const noexcept
        {
            return ApplyInverse( VectorSimd( v ) );
        }


        VectorSimd operator()( const VectorSimd& v ) const noexcept
        {
            return Apply( v );
        }
        VectorSimd operator()( const Vector& v ) const noexcept
        {
            return Apply( VectorSimd( v ) );
        }

        PointSimd Apply( const PointSimd& p ) const noexcept
        {
            return VectorSimd( Traits::Add( Traits::TransformNormal( p.simd, matrix_.simd[ 0 ], matrix_.simd[ 1 ], matrix_.simd[ 2 ] ), translation_.simd ) );
        }

        PointSimd Apply( const Point& p ) const noexcept
        {
            return Apply( PointSimd( p ) );
        }


        PointSimd ApplyInverse( const PointSimd& p ) const noexcept
        {
            return VectorSimd( Traits::TransformNormal( Traits::Sub(p.simd, translation_.simd), inverseMatrix_.simd[ 0 ], inverseMatrix_.simd[ 1 ], inverseMatrix_.simd[ 2 ] )  );
        }

        PointSimd ApplyInverse( const Point& p ) const noexcept
        {
            return ApplyInverse( PointSimd( p ) );
        }


        PointSimd operator()( const PointSimd& p ) const noexcept
        {
            return Apply( p );
        }
        PointSimd operator()( const Point& p ) const noexcept
        {
            return Apply( p );
        }

        NormalSimd Apply( const NormalSimd& n ) const noexcept
        {
            auto imt = Math::Transpose( inverseMatrix_ );
            return VectorSimd( Traits::TransformNormal( n.simd, imt.simd[ 0 ], imt.simd[ 1 ], imt.simd[ 2 ] ) );
        }

        NormalSimd Apply( const Normal& n ) const noexcept
        {
            return Apply( NormalSimd( n ) );
        }

        NormalSimd ApplyInverse( const NormalSimd& n ) const noexcept
        {
            auto imt = Math::Transpose( matrix_ );
            return VectorSimd( Traits::TransformNormal( n.simd, imt.simd[ 0 ], imt.simd[ 1 ], imt.simd[ 2 ] ) );
        }

        NormalSimd ApplyInverse( const Normal& n ) const noexcept
        {
            return ApplyInverse( NormalSimd( n ) );
        }


        NormalSimd operator()( const NormalSimd& n ) const noexcept
        {
            return Apply( n );
        }
        NormalSimd operator()( const Normal& n ) const noexcept
        {
            return Apply( n );
        }

        AffineTransformation Inverse( ) const noexcept
        {
            return AffineTransformation( inverseMatrix_, matrix_, -translation_ );
        }

        static AffineTransformation Translate( const VectorSimd& delta ) noexcept
        {
            return AffineTransformation( delta );
        }

        static AffineTransformation Translate( const Vector& delta ) noexcept
        {
            return Translate( VectorSimd( delta ) );
        }

        static AffineTransformation Translate( float deltaX, float deltaY, float deltaZ ) noexcept
        {
            return Translate( Vector( deltaX, deltaY, deltaZ ) );
        }


        static AffineTransformation RotateX( float angle ) noexcept
        {
            return AffineTransformation( MatrixSimd( Math::RotationX( angle ).simd ) );
        }
        static AffineTransformation RotateY( float angle ) noexcept
        {
            return AffineTransformation( MatrixSimd( Math::RotationY( angle ).simd ) );
        }
        static AffineTransformation RotateZ( float angle ) noexcept
        {
            return AffineTransformation( MatrixSimd( Math::RotationZ( angle ).simd ) );
        }

        static AffineTransformation Scale( float scale ) noexcept
        {
            return AffineTransformation( MatrixSimd( Math::Scaling( scale ).simd ) );
        }
        static AffineTransformation Scale( const VectorSimd& scale ) noexcept
        {
            return AffineTransformation( MatrixSimd( Math::Scaling( scale ).simd ) );
        }

        static AffineTransformation Scale( const Vector& scale ) noexcept
        {
            return Scale( VectorSimd( scale ) );
        }

        static AffineTransformation Scale( float scaleX, float scaleY, float scaleZ ) noexcept
        {
            return Scale( Vector( scaleX, scaleY, scaleZ ) );
        }


        static AffineTransformation LookAt( const PointSimd& cameraPosition, const PointSimd& focusPosition, const VectorSimd& upDirection ) noexcept
        {
            return AffineTransformation( Math::LookAt( cameraPosition, focusPosition, upDirection ) );
        }
        static AffineTransformation LookAt( const Point& cameraPosition, const Point& focusPosition, const Vector& upDirection ) noexcept
        {
            return AffineTransformation( Math::LookAt( cameraPosition, focusPosition, upDirection ) );
        }


    };

    



}

#endif
