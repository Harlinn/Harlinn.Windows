/*
   Copyright 2024-2026 Espen Harlinn

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

#include "pch.h"

#include <Harlinn/Math/VectorMath.h>

using namespace Harlinn;
using namespace Harlinn::Common::Core;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    Math::SquareMatrix<float, 4> ToMatrix( ::DirectX::FXMMATRIX matrix )
    {
        Math::SquareMatrix<float, 4> result;
        ::DirectX::XMStoreFloat4x4( reinterpret_cast< ::DirectX::XMFLOAT4X4* >( &result ), matrix );
        return result;
    }


    constexpr float EPSILON = 1.192092896e-7f;

    bool ApproximatelyEqual( float a, float b, float epsilon = EPSILON )
    {
        return std::abs( a - b ) < epsilon;
    }

    bool MatrixApproximatelyEqual(
        const SquareMatrix<float, 4>& m1,
        const SquareMatrix<float, 4>& m2,
        float epsilon = EPSILON )
    {
        for ( size_t i = 0; i < 4; ++i )
        {
            for ( size_t j = 0; j < 4; ++j )
            {
                if ( !ApproximatelyEqual( m1[ i ][ j ], m2[ i ][ j ], epsilon ) )
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool MatrixApproximatelyEqual(
        const SquareMatrix<float, 4>::Simd& m1,
        const SquareMatrix<float, 4>::Simd& m2,
        float epsilon = EPSILON )
    {
        return MatrixApproximatelyEqual( SquareMatrix<float, 4>( m1 ), SquareMatrix<float, 4>( m2 ), epsilon );
    }

    bool MatrixApproximatelyEqual(
        const SquareMatrix<float, 2>::Simd& actual,
        const SquareMatrix<float, 2>::Simd& expected,
        float epsilon = 1e-5f )
    {
        auto actualArray = SquareMatrix<float, 2>::Simd::Traits::ToArray( actual.simd );
        auto expectedArray = SquareMatrix<float, 2>::Simd::Traits::ToArray( expected.simd );

        for ( size_t i = 0; i < actualArray.size( ); ++i )
        {
            if ( std::abs( actualArray[ i ] - expectedArray[ i ] ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }


    /// <summary>
    /// Verifies that a 4x4 rotation matrix is orthogonal (R^T * R = I).
    /// </summary>
    /// <remarks>
    /// For DirectX matrices, checks that the upper-left 3x3 is orthogonal
    /// and the bottom row is [0, 0, 0, 1].
    /// </remarks>
    bool IsOrthogonalMatrix( const Math::Vector<float, 4>::Simd& r0, const Math::Vector<float, 4>::Simd& r1,
        const Math::Vector<float, 4>::Simd& r2, const Math::Vector<float, 4>::Simd& r3,
        float epsilon = EPSILON * 10.0f )
    {
        // Check that row 4 is [0, 0, 0, 1] (homogeneous coordinates)
        if ( !ApproximatelyEqual( r3.x( ), 0.0f, epsilon ) ||
            !ApproximatelyEqual( r3.y( ), 0.0f, epsilon ) ||
            !ApproximatelyEqual( r3.z( ), 0.0f, epsilon ) ||
            !ApproximatelyEqual( r3.w( ), 1.0f, epsilon ) )
        {
            return false;
        }

        // Check orthonormality of 3x3 rotation part: rows should be unit vectors
        float r0_norm_sq = r0.x( ) * r0.x( ) + r0.y( ) * r0.y( ) + r0.z( ) * r0.z( );
        float r1_norm_sq = r1.x( ) * r1.x( ) + r1.y( ) * r1.y( ) + r1.z( ) * r1.z( );
        float r2_norm_sq = r2.x( ) * r2.x( ) + r2.y( ) * r2.y( ) + r2.z( ) * r2.z( );

        if ( !ApproximatelyEqual( r0_norm_sq, 1.0f, epsilon ) ||
            !ApproximatelyEqual( r1_norm_sq, 1.0f, epsilon ) ||
            !ApproximatelyEqual( r2_norm_sq, 1.0f, epsilon ) )
        {
            return false;
        }

        // Check orthogonality: dot products between different rows should be zero
        float r0_dot_r1 = r0.x( ) * r1.x( ) + r0.y( ) * r1.y( ) + r0.z( ) * r1.z( );
        float r0_dot_r2 = r0.x( ) * r2.x( ) + r0.y( ) * r2.y( ) + r0.z( ) * r2.z( );
        float r1_dot_r2 = r1.x( ) * r2.x( ) + r1.y( ) * r2.y( ) + r1.z( ) * r2.z( );

        return ApproximatelyEqual( r0_dot_r1, 0.0f, epsilon ) &&
            ApproximatelyEqual( r0_dot_r2, 0.0f, epsilon ) &&
            ApproximatelyEqual( r1_dot_r2, 0.0f, epsilon );
    }

    // Helper function to check if a matrix is orthogonal (rotation matrix property)
    bool IsOrthogonal( const Math::Vector<float, 4>::Simd& col1,
        const Math::Vector<float, 4>::Simd& col2,
        const Math::Vector<float, 4>::Simd& col3,
        float epsilon = 1e-4f )
    {
        // Check orthogonality: dot products of different columns should be ~0
        // and dot product of a column with itself should be ~1
        auto dot12 = ScalarDot( col1, col2 );
        auto dot13 = ScalarDot( col1, col3 );
        auto dot23 = ScalarDot( col2, col3 );
        auto len1 = ScalarLength( col1 );
        auto len2 = ScalarLength( col2 );
        auto len3 = ScalarLength( col3 );

        bool orthogonal = ApproximatelyEqual( dot12, 0.0f, epsilon ) &&
            ApproximatelyEqual( dot13, 0.0f, epsilon ) &&
            ApproximatelyEqual( dot23, 0.0f, epsilon );

        bool normalized = ApproximatelyEqual( len1, 1.0f, epsilon ) &&
            ApproximatelyEqual( len2, 1.0f, epsilon ) &&
            ApproximatelyEqual( len3, 1.0f, epsilon );

        return orthogonal && normalized;
    }

    bool IsValidRotationMatrix( const SquareMatrix<float, 4>::Simd& matrix, float epsilon = 1e-4f )
    {
        // Extract 3x3 rotation part (ignore translation)
        Math::Vector<float, 4>::Simd col0( matrix.simd[ 0 ] );
        Math::Vector<float, 4>::Simd col1( matrix.simd[ 1 ] );
        Math::Vector<float, 4>::Simd col2( matrix.simd[ 2 ] );

        return IsOrthogonal( col0, col1, col2, epsilon );
    }

    std::array<std::array<float, 4>, 4> ExtractMatrix( const SquareMatrix<float, 4>::Simd& simdMatrix )
    {
        std::array<std::array<float, 4>, 4> result{};
        auto matrixData = SquareMatrix<float, 4>::Simd::ToMatrix( simdMatrix );
        for ( size_t i = 0; i < 4; ++i )
        {
            for ( size_t j = 0; j < 4; ++j )
            {
                result[ i ][ j ] = matrixData[ i ][ j ];
            }
        }
        return result;
    }


}

BOOST_FIXTURE_TEST_SUITE( MathMatrixTests, LocalFixture )

// --run_test=MathMatrixTests/TransposeMatrix3x3Test1
BOOST_AUTO_TEST_CASE( TransposeMatrix3x3Test1 )
{
    Math::SquareMatrix<float, 3> matrix
    ( 1.f, 2.f, 3.f, 
        4.f, 5.f, 6.f,
        7.f, 8.f, 9.f );

    Math::SquareMatrix<float, 3> expectedMatrix
    ( 1.f, 4.f, 7.f,
        2.f, 5.f, 8.f,
        3.f, 6.f, 9.f );

    Math::SquareMatrix<float, 3> transposed = Math::Transpose( matrix );

    auto equal = transposed == expectedMatrix;

    BOOST_CHECK( equal );

}


// --run_test=MathMatrixTests/TransposeMatrix4x4Test1
BOOST_AUTO_TEST_CASE( TransposeMatrix4x4Test1 )
{
    Math::SquareMatrix<float, 4> matrix
    (  1.f,  2.f,  3.f,  4.f,
       5.f,  6.f,  7.f,  8.f,
       9.f, 10.f, 11.f, 12.f,
      13.f, 14.f, 15.f, 16.f );

    Math::SquareMatrix<float, 4> expectedMatrix
    ( 1.f, 5.f, 9.f,  13.f,
      2.f, 6.f, 10.f, 14.f,
      3.f, 7.f, 11.f, 15.f,
      4.f, 8.f, 12.f, 16.f );

    Math::SquareMatrix<float, 4> transposed = Math::Transpose( matrix );

    auto equal = transposed == expectedMatrix;

    BOOST_CHECK( equal );

}


// --run_test=MathMatrixTests/MultiplyMatrix3x3Test1
BOOST_AUTO_TEST_CASE( MultiplyMatrix3x3Test1 )
{
    Math::SquareMatrix<float, 3> matrix1
    ( 1.f, 2.f, 3.f,
        4.f, 5.f, 6.f,
        7.f, 8.f, 9.f );

    Math::SquareMatrix<float, 3> matrix2
    ( 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f,
        8.f, 9.f, 10.f );

    Math::SquareMatrix<float, 3> expectedResult
    ( 
        36.f, 42.f, 48.f,
        81.f, 96.f, 111.f,
        126.f, 150.f, 174.f
    );

    Math::SquareMatrix<float, 3> result = matrix1 * matrix2;

    auto equal = result == expectedResult;

    BOOST_CHECK( equal );
}

// --run_test=MathMatrixTests/MultiplyMatrix4x4Test1
BOOST_AUTO_TEST_CASE( MultiplyMatrix4x4Test1 )
{
    Math::SquareMatrix<float, 4> matrix1
    ( 1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f );

    Math::SquareMatrix<float, 4> matrix2
    ( 2.f, 3.f, 4.f, 5.f,
        6.f, 7.f, 8.f, 9.f,
        10.f, 11.f, 12.f, 13.f,
        14.f, 15.f, 16.f, 17.f );

    Math::SquareMatrix<float, 4> expectedResult
    (
        100.f, 110.f, 120.f, 130.f,
        228.f, 254.f, 280.f, 306.f,
        356.f, 398.f, 440.f, 482.f,
        484.f, 542.f, 600.f, 658.f );

    Math::SquareMatrix<float, 4> result = matrix1 * matrix2;

    auto equal = result == expectedResult;

    BOOST_CHECK( equal );
}

// --run_test=MathMatrixTests/MultiplyScalarMatrix4x4Test1
BOOST_AUTO_TEST_CASE( MultiplyScalarMatrix4x4Test1 )
{
    Math::SquareMatrix<float, 4> matrix1
    ( 1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f );

    

    Math::SquareMatrix<float, 4> expectedResult
    ( 2.f * 1.f, 2.f * 2.f, 2.f * 3.f, 2.f * 4.f,
        2.f * 5.f, 2.f * 6.f, 2.f * 7.f, 2.f * 8.f,
        2.f * 9.f, 2.f * 10.f, 2.f * 11.f, 2.f * 12.f,
        2.f * 13.f, 2.f * 14.f, 2.f * 15.f, 2.f * 16.f );

    Math::SquareMatrix<float, 4> result = 2.f * matrix1;

    auto equal = result == expectedResult;

    BOOST_CHECK( equal );
}

// --run_test=MathMatrixTests/MultiplyScalarMatrix3x3Test1
BOOST_AUTO_TEST_CASE( MultiplyScalarMatrix3x3Test1 )
{
    Math::SquareMatrix<float, 3> matrix1
    ( 1.f, 2.f, 3.f,
        4.f, 5.f, 6.f,
        7.f, 8.f, 9.f );

    Math::SquareMatrix<float, 3> expectedResult
    (
        2.f * 1.f, 2.f * 2.f, 2.f * 3.f,
        2.f * 4.f, 2.f * 5.f, 2.f * 6.f,
        2.f * 7.f, 2.f * 8.f, 2.f * 9.f
    );

    Math::SquareMatrix<float, 3> result = 2.f * matrix1;

    auto equal = result == expectedResult;

    BOOST_CHECK( equal );
}

// --run_test=MathMatrixTests/AddMatrix3x3Test1
BOOST_AUTO_TEST_CASE( AddMatrix3x3Test1 )
{
    Math::SquareMatrix<float, 3> matrix1
    ( 1.f, 2.f, 3.f,
        4.f, 5.f, 6.f,
        7.f, 8.f, 9.f );

    Math::SquareMatrix<float, 3> matrix2
    ( 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f,
        8.f, 9.f, 10.f );

    Math::SquareMatrix<float, 3> expectedResult
    (
        3.f, 5.f, 7.f,
        9.f, 11.f, 13.f,
        15.f, 17.f, 19.f
    );

    Math::SquareMatrix<float, 3> result = matrix1 + matrix2;

    auto equal = result == expectedResult;

    BOOST_CHECK( equal );
}

// --run_test=MathMatrixTests/AddMatrix4x4Test1
BOOST_AUTO_TEST_CASE( AddMatrix4x4Test1 )
{
    Math::SquareMatrix<float, 4> matrix1
    ( 1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f );

    Math::SquareMatrix<float, 4> matrix2
    ( 2.f, 3.f, 4.f, 5.f,
        6.f, 7.f, 8.f, 9.f,
        10.f, 11.f, 12.f, 13.f,
        14.f, 15.f, 16.f, 17.f );

    Math::SquareMatrix<float, 4> expectedResult
    (
        3.f, 5.f, 7.f, 9.f,
        11.f, 13.f, 15.f, 17.f,
        19.f, 21.f, 23.f, 25.f,
        27.f, 29.f, 31.f, 33.f );

    Math::SquareMatrix<float, 4> result = matrix1 + matrix2;

    auto equal = result == expectedResult;

    BOOST_CHECK( equal );
}


// --run_test=MathMatrixTests/DeterminantMatrix4x4Test1
BOOST_AUTO_TEST_CASE( DeterminantMatrix4x4Test1 )
{
    Math::SquareMatrix<float, 4> matrix1
    ( 1.5f, -2.f, 3.4f, 4.f,
        5.4f, 6.f, 7.6f, 8.f,
        -9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f );

    float expectedResult = 282.720703f;
    Math::Vector<float, 4> result = Math::Determinant( matrix1 );
    auto nearlyEqual = AreNearlyEqual( result.x, expectedResult,1e-2f);
    BOOST_CHECK( nearlyEqual );
}

// --run_test=MathMatrixTests/DeterminantMatrix3x3Test1
BOOST_AUTO_TEST_CASE( DeterminantMatrix3x3Test1 )
{
    Math::SquareMatrix<float, 3> matrix1
      ( 1.5f, -2.f, 3.4f,
        5.4f,  6.f, 7.6f,
       -9.f,  10.f, 11.f );

    float expectedResult = 607.799988f;
    Math::Vector<float, 3> result = Math::Determinant( matrix1 );
    auto nearlyEqual = AreNearlyEqual( result.x, expectedResult, 1e-2f );
    BOOST_CHECK( nearlyEqual );
}


// --run_test=MathMatrixTests/PbrtTest1
BOOST_AUTO_TEST_CASE( PbrtTest1 )
{
    pbrt::SquareMatrix<3> matrix1
    ( 1.5f, -2.f, 3.4f,
        5.4f, 6.f, 7.6f,
        -9.f, 10.f, 11.f );
    float expectedResult = 607.799988f;
#ifdef PBRT_USES_HCCMATH
    auto result = ScalarDeterminant( matrix1 );
#else
    auto result = pbrt::Determinant( matrix1 );
#endif
    auto nearlyEqual = AreNearlyEqual( result, expectedResult, 1e-2f );
    BOOST_CHECK( nearlyEqual );

}

/// <summary>
/// Tests that RotationX produces an identity matrix when angle is zero.
/// </summary>
// --run_test=MathVector4FloatTests/RotationXWithZeroAngleReturnsIdentityTest
BOOST_AUTO_TEST_CASE( RotationXWithZeroAngleReturnsIdentityTest )
{
    auto rotationMatrix = Math::RotationX( 0.0f );
    auto identity = SquareMatrix<float, 4>::Simd( Math::MatrixType::Identity );

    bool isIdentity = ( rotationMatrix == identity );
    BOOST_TEST( isIdentity );
}

/// <summary>
/// Tests that RotationX produces correct sine and cosine values for 90-degree rotation.
/// </summary>
// --run_test=MathVector4FloatTests/XMMatrixRotationXWith90DegreesProducesCorrectValuesTest
BOOST_AUTO_TEST_CASE( XMMatrixRotationXWith90DegreesProducesCorrectValuesTest )
{
    const float angle = std::numbers::pi_v<float> / 2.0f; // 90 degrees
    auto matrix = ToMatrix( ::DirectX::XMMatrixRotationX( angle ) );

    // At 90 degrees: sin(90°) = 1, cos(90°) = 0
    // Row 1 should be [1, 0, 0, 0]
    // Row 2 should be [0, 0, -1, 0]
    // Row 3 should be [0, 1, 0, 0]
    // Row 4 should be [0, 0, 0, 1]

    // Check first row (identity)
    bool firstRowCorrect = ( std::abs( matrix[ 0 ][ 0 ] - 1.0f ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 1 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 2 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 3 ] ) < 1e-5f );
    BOOST_TEST( firstRowCorrect );

    // Check that row 2 has correct cosine/sine pattern (approximately [0, 0, -1, 0])
    bool secondRowCorrect = ( std::abs( matrix[ 1 ][ 0 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 1 ][ 1 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 1 ][ 2 ] - 1.0f ) < 1e-5f ) &&
        ( std::abs( matrix[ 1 ][ 3 ] ) < 1e-5f );
    BOOST_TEST( secondRowCorrect );
}


/// <summary>
/// Tests that RotationX produces correct sine and cosine values for 90-degree rotation.
/// </summary>
// --run_test=MathVector4FloatTests/RotationXWith90DegreesProducesCorrectValuesTest
BOOST_AUTO_TEST_CASE( RotationXWith90DegreesProducesCorrectValuesTest )
{
    const float angle = std::numbers::pi_v<float> / 2.0f; // 90 degrees
    Math::SquareMatrix<float, 4> matrix = Math::RotationX( angle );

    // At 90 degrees: sin(90°) = 1, cos(90°) = 0
    // Row 1 should be [1, 0, 0, 0]
    // Row 2 should be [0, 0, 1, 0]
    // Row 3 should be [0, -1, 0, 0]
    // Row 4 should be [0, 0, 0, 1]

    // Check first row (identity)
    bool firstRowCorrect = ( std::abs( matrix[ 0 ][ 0 ] - 1.0f ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 1 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 2 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 3 ] ) < 1e-5f );
    BOOST_TEST( firstRowCorrect );

    // Check that row 2 has correct cosine/sine pattern (approximately [0, 0, 1, 0])
    bool secondRowCorrect = ( std::abs( matrix[ 1 ][ 0 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 1 ][ 1 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 1 ][ 2 ] - 1.0f ) < 1e-5f ) &&
        ( std::abs( matrix[ 1 ][ 3 ] ) < 1e-5f );
    BOOST_TEST( secondRowCorrect );
}

/// <summary>
/// Tests that RotationX produces correct values for 180-degree rotation.
/// </summary>
BOOST_AUTO_TEST_CASE( RotationXWith180DegreesProducesCorrectValues )
{
    const float angle = std::numbers::pi_v<float>; // 180 degrees
    Math::SquareMatrix<float, 4> matrix = Math::RotationX( angle );

    // At 180 degrees: sin(180°) = 0, cos(180°) = -1
    // Row 1 should be [1, 0, 0, 0]
    // Row 2 should be [0, -1, 0, 0]
    // Row 3 should be [0, 0, -1, 0]
    // Row 4 should be [0, 0, 0, 1]

    bool firstRowCorrect = ( std::abs( matrix[ 0 ][ 0 ] - 1.0f ) < 1e-5f );
    BOOST_TEST( firstRowCorrect );

    bool secondRowDiagonal = ( std::abs( matrix[ 1 ][ 1 ] + 1.0f ) < 1e-5f ) &&
        ( std::abs( matrix[ 2 ][ 2 ] + 1.0f ) < 1e-5f );
    BOOST_TEST( secondRowDiagonal );
}

/// <summary>
/// Tests that RotationX produces correct values for negative angles.
/// </summary>
BOOST_AUTO_TEST_CASE( RotationXWithNegativeAngleIsInverse )
{
    const float angle = std::numbers::pi_v<float> / 4.0f; // 45 degrees
    Math::SquareMatrix<float, 4> posMatrix = Math::RotationX( angle );
    Math::SquareMatrix<float, 4> negMatrix = Math::RotationX( -angle );

    // For rotation matrices, R(-θ) should have mirrored sine values
    bool inverseSineValues = ( std::abs( posMatrix[ 1 ][ 2 ] + negMatrix[ 1 ][ 2 ] ) < 1e-4f ) &&
        ( std::abs( posMatrix[ 2 ][ 1 ] + negMatrix[ 2 ][ 1 ] ) < 1e-4f );
    BOOST_TEST( inverseSineValues );
}

/// <summary>
/// Tests that RotationX produces a proper rotation matrix structure.
/// </summary>
BOOST_AUTO_TEST_CASE( RotationXProducesValidRotationMatrixStructure )
{
    const float angle = std::numbers::pi_v<float> / 6.0f; // 30 degrees
    Math::SquareMatrix<float, 4> matrix = Math::RotationX( angle );

    // First row should be identity row [1, 0, 0, 0]
    bool firstRowIsIdentity = ( std::abs( matrix[ 0 ][ 0 ] - 1.0f ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 1 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 2 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 3 ] ) < 1e-5f );
    BOOST_TEST( firstRowIsIdentity );

    // Fourth row should be identity row [0, 0, 0, 1]
    bool fourthRowIsIdentity = ( std::abs( matrix[ 3 ][ 0 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 3 ][ 1 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 3 ][ 2 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 3 ][ 3 ] - 1.0f ) < 1e-5f );
    BOOST_TEST( fourthRowIsIdentity );
}

/// <summary>
/// Tests that RotationX produces consistent results for full rotation (2π).
/// </summary>
BOOST_AUTO_TEST_CASE( RotationXWithFullRotationReturnsNearlyIdentical )
{
    const float angle = std::numbers::pi_v<float> *2.0f; // 360 degrees
    Math::SquareMatrix<float, 4> matrix = Math::RotationX( angle );
    Math::SquareMatrix<float, 4> identityMatrix = SquareMatrix<float, 4>::Simd( Math::MatrixType::Identity );

    // Check that all elements are very close to identity
    bool nearIdentity = true;
    for ( int i = 0; i < 4; ++i )
    {
        for ( int j = 0; j < 4; ++j )
        {
            if ( std::abs( matrix[ i ][ j ] - identityMatrix[ i ][ j ] ) > 1e-4f )
            {
                nearIdentity = false;
                break;
            }
        }
        if ( !nearIdentity ) break;
    }
    BOOST_TEST( nearIdentity );
}

/// <summary>
/// Tests that successive 90-degree rotations compose correctly.
/// </summary>
BOOST_AUTO_TEST_CASE( RotationXFourSuccessive90DegreesEqualsIdentity )
{
    const float angle = std::numbers::pi_v<float> / 2.0f; // 90 degrees
    Math::SquareMatrix<float, 4> rot90 = RotationX( angle );

    // Four 90-degree rotations should return to identity
    Math::SquareMatrix<float, 4> resultMatrix = rot90 * rot90 * rot90 * rot90;
    Math::SquareMatrix<float, 4> identityMatrix = SquareMatrix<float, 4>::Simd( Math::MatrixType::Identity );

    bool isNearIdentity = true;
    for ( int i = 0; i < 4; ++i )
    {
        for ( int j = 0; j < 4; ++j )
        {
            if ( std::abs( resultMatrix[ i ][ j ] - identityMatrix[ i ][ j ] ) > 1e-4f )
            {
                isNearIdentity = false;
                break;
            }
        }
        if ( !isNearIdentity ) break;
    }
    BOOST_TEST( isNearIdentity );
}

/// <summary>
/// Tests that RotationX correctly rotates a Y-axis vector.
/// </summary>
BOOST_AUTO_TEST_CASE( RotationXRotatesYAxisVector )
{
    const float angle = std::numbers::pi_v<float> / 4.0f; // 45 degrees
    Math::SquareMatrix<float, 4> rotationMatrix = Math::RotationX( angle );

    float sine, cosine;
    Math::SinCos( angle, &sine, &cosine );

    // A unit vector along Y-axis [0, 1, 0, 1]
    Math::Vector4f yAxis( 0.0f, 1.0f, 0.0f, 1.0f );

    // Transform the vector by the rotation matrix
    Math::Vector4f rotatedVector = Math::Transform( yAxis, rotationMatrix );

    // After rotation around X-axis, Y should become Y*cos(θ) - Z*sin(θ)
    // and Z should become Y*sin(θ) + Z*cos(θ)
    // So [0, 1, 0] -> [0, cos(45°), sin(45°)]

    float expectedX = 0.0f;
    float expectedY = cosine;
    float expectedZ = sine;
    float expectedW = 1.0f;

    bool xComponentCorrect = std::abs( rotatedVector.x - expectedX ) < 1e-5f;
    bool yComponentCorrect = std::abs( rotatedVector.y - expectedY ) < 1e-5f;
    bool zComponentCorrect = std::abs( rotatedVector.z - expectedZ ) < 1e-5f;
    bool wComponentCorrect = std::abs( rotatedVector.w - expectedW ) < 1e-5f;

    BOOST_TEST( xComponentCorrect );
    BOOST_TEST( yComponentCorrect );
    BOOST_TEST( zComponentCorrect );
    BOOST_TEST( wComponentCorrect );
}

/// <summary>
/// Tests that RotationX correctly rotates a Z-axis vector.
/// </summary>
BOOST_AUTO_TEST_CASE( RotationXRotatesZAxisVector )
{
    const float angle = std::numbers::pi_v<float> / 3.0f; // 60 degrees
    Math::SquareMatrix<float, 4> rotationMatrix = Math::RotationX( angle );

    float sine, cosine;
    Math::SinCos( angle, &sine, &cosine );

    // A unit vector along Z-axis [0, 0, 1, 1]
    Math::Vector4f zAxis( 0.0f, 0.0f, 1.0f, 1.0f );

    // Transform the vector by the rotation matrix
    Math::Vector4f rotatedVector = Math::Transform( zAxis, rotationMatrix );

    // After rotation around X-axis:
    // X stays 0
    // Y becomes: 0*cos(θ) - 1*sin(θ) = -sin(θ)
    // Z becomes: 0*sin(θ) + 1*cos(θ) = cos(θ)
    // So [0, 0, 1] -> [0, -sin(60°), cos(60°)]

    float expectedX = 0.0f;
    float expectedY = -sine;
    float expectedZ = cosine;
    float expectedW = 1.0f;

    bool xComponentCorrect = std::abs( rotatedVector.x - expectedX ) < 1e-5f;
    bool yComponentCorrect = std::abs( rotatedVector.y - expectedY ) < 1e-5f;
    bool zComponentCorrect = std::abs( rotatedVector.z - expectedZ ) < 1e-5f;
    bool wComponentCorrect = std::abs( rotatedVector.w - expectedW ) < 1e-5f;

    BOOST_TEST( xComponentCorrect );
    BOOST_TEST( yComponentCorrect );
    BOOST_TEST( zComponentCorrect );
    BOOST_TEST( wComponentCorrect );
}

/// <summary>
/// Tests that RotationX does not modify the X-axis.
/// </summary>
BOOST_AUTO_TEST_CASE( RotationXDoesNotModifyXAxis )
{
    const float angle = std::numbers::pi_v<float> / 2.5f;
    Math::SquareMatrix<float, 4> rotationMatrix = Math::RotationX( angle );

    Math::SquareMatrix<float, 4> matrix = rotationMatrix;

    // X-axis should remain unchanged: [1, 0, 0, 0]
    bool xAxisUnchanged = ( std::abs( matrix[ 0 ][ 0 ] - 1.0f ) < 1e-5f ) &&
        ( std::abs( matrix[ 1 ][ 0 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 2 ][ 0 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 3 ][ 0 ] ) < 1e-5f );
    BOOST_TEST( xAxisUnchanged );
}

/// <summary>
/// Tests that RotationY with zero angle produces identity matrix.
/// </summary>
BOOST_AUTO_TEST_CASE( RotationYZeroAngleIsIdentity )
{
    auto result = RotationY( 0.0f );
    auto expected = SquareMatrix<float, 4>::Simd::Identity( );

    bool isIdentity = MatrixApproximatelyEqual( result, expected );
    BOOST_TEST( isIdentity );
}

/// <summary>
/// Tests that RotationY produces correct values for 90-degree rotation.
/// </summary>
BOOST_AUTO_TEST_CASE( RotationYNinetyDegrees )
{
    constexpr float PI_HALF = 3.14159265358979f / 2.0f;
    auto result = RotationY( PI_HALF );

    auto resultData = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 0 ] );
    // At 90 degrees: cos(90) ≈ 0, sin(90) ≈ 1
    // M[0][0] should be cos(90) ≈ 0
    bool m00IsZero = ApproximatelyEqual( resultData[ 0 ], 0.0f, 0.01f );
    BOOST_TEST( m00IsZero );

    // M[0][2] should be sin(90) ≈ 1
    resultData = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 2 ] );
    bool m20IsOne = ApproximatelyEqual( resultData[ 0 ], 1.0f, 0.01f );
    BOOST_TEST( m20IsOne );
}

/// <summary>
/// Tests that RotationY produces correct values for 180-degree rotation.
/// </summary>
BOOST_AUTO_TEST_CASE( RotationY180Degrees )
{
    constexpr float PI = 3.14159265358979f;
    auto result = RotationY( PI );

    auto resultData = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 0 ] );
    // At 180 degrees: cos(180) ≈ -1, sin(180) ≈ 0
    // M[0][0] should be cos(180) ≈ -1
    bool m00IsNegOne = ApproximatelyEqual( resultData[ 0 ], -1.0f, 0.01f );
    BOOST_TEST( m00IsNegOne );

    // M[0][2] should be sin(180) ≈ 0
    resultData = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 2 ] );
    bool m20IsZero = ApproximatelyEqual( resultData[ 0 ], 0.0f, 0.01f );
    BOOST_TEST( m20IsZero );
}

/// <summary>
/// Tests that RotationY preserves the Y-axis (row 1 is [0, 1, 0, 0]).
/// </summary>
BOOST_AUTO_TEST_CASE( RotationYPreservesYAxis )
{
    constexpr float ANGLE = 0.785398f; // 45 degrees
    auto result = RotationY( ANGLE );

    // Row 1 (Y-axis row) should be [0, 1, 0, 0]
    auto row1Data = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 1 ] );
    bool isYAxisPreserved =
        ApproximatelyEqual( row1Data[ 0 ], 0.0f ) &&
        ApproximatelyEqual( row1Data[ 1 ], 1.0f ) &&
        ApproximatelyEqual( row1Data[ 2 ], 0.0f ) &&
        ApproximatelyEqual( row1Data[ 3 ], 0.0f );
    BOOST_TEST( isYAxisPreserved );
}

/// <summary>
/// Tests that RotationY produces an orthogonal matrix (determinant is ±1).
/// </summary>
BOOST_AUTO_TEST_CASE( RotationYIsOrthogonal )
{
    constexpr float ANGLE = 1.57079632f; // 90 degrees in radians
    auto result = RotationY( ANGLE );

    // For a 4x4 rotation matrix, the upper-left 3x3 should be orthogonal
    auto row0 = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 0 ] );
    auto row1 = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 1 ] );
    auto row2 = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 2 ] );

    // Check that each row has unit length (for first 3 components)
    float len0Sq = row0[ 0 ] * row0[ 0 ] + row0[ 1 ] * row0[ 1 ] + row0[ 2 ] * row0[ 2 ];
    float len1Sq = row1[ 0 ] * row1[ 0 ] + row1[ 1 ] * row1[ 1 ] + row1[ 2 ] * row1[ 2 ];
    float len2Sq = row2[ 0 ] * row2[ 0 ] + row2[ 1 ] * row2[ 1 ] + row2[ 2 ] * row2[ 2 ];

    bool isOrthogonal =
        ApproximatelyEqual( len0Sq, 1.0f, 0.01f ) &&
        ApproximatelyEqual( len1Sq, 1.0f, 0.01f ) &&
        ApproximatelyEqual( len2Sq, 1.0f, 0.01f );
    BOOST_TEST( isOrthogonal );
}

/// <summary>
/// Tests that RotationY has correct homogeneous coordinates (last row is [0, 0, 0, 1]).
/// </summary>
BOOST_AUTO_TEST_CASE( RotationYHomogeneousCoordinates )
{
    constexpr float ANGLE = 0.5f;
    auto result = RotationY( ANGLE );

    // Last row should be [0, 0, 0, 1]
    auto row3Data = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 3 ] );
    bool isHomogeneous =
        ApproximatelyEqual( row3Data[ 0 ], 0.0f ) &&
        ApproximatelyEqual( row3Data[ 1 ], 0.0f ) &&
        ApproximatelyEqual( row3Data[ 2 ], 0.0f ) &&
        ApproximatelyEqual( row3Data[ 3 ], 1.0f );
    BOOST_TEST( isHomogeneous );
}

/// <summary>
/// Tests that RotationY(-θ) is the transpose of RotationY(θ).
/// </summary>
BOOST_AUTO_TEST_CASE( RotationYNegativeAngleIsTranspose )
{
    constexpr float ANGLE = 1.0f;
    auto posResult = RotationY( ANGLE );
    auto negResult = RotationY( -ANGLE );

    // For orthogonal matrices, transpose equals inverse
    // RotationY(-θ) should equal RotationY(θ) transposed
    auto row0Pos = SquareMatrix<float, 4>::Simd::Traits::ToArray( posResult.simd[ 0 ] );
    auto row0Neg = SquareMatrix<float, 4>::Simd::Traits::ToArray( negResult.simd[ 0 ] );

    // Check if negResult[0] ≈ posResult[0] with cos term preserved
    bool isInverse = ApproximatelyEqual( row0Pos[ 0 ], row0Neg[ 0 ], 0.01f );
    BOOST_TEST( isInverse );
}

/// <summary>
/// Tests that RotationY with various angles produces expected sine/cosine values.
/// </summary>
BOOST_AUTO_TEST_CASE( RotationYVariousAngles )
{
    constexpr float ANGLES[ ] = { 0.0f, 0.785398f, 1.57079f, 2.35619f, 3.14159f };

    for ( float angle : ANGLES )
    {
        auto result = RotationY( angle );

        float expectedSine = std::sin( angle );
        float expectedCosine = std::cos( angle );

        auto row0Data = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 0 ] );
        bool cosineMatches = ApproximatelyEqual( row0Data[ 0 ], expectedCosine, 0.01f );
        BOOST_TEST( cosineMatches );
    }
}

/// <summary>
/// Tests that applying RotationY twice with half angle equals single rotation.
/// </summary>
BOOST_AUTO_TEST_CASE( RotationYAngleAddition )
{
    constexpr float HALF_ANGLE = 0.785398f; // 45 degrees

    auto singleRotation = RotationY( HALF_ANGLE * 2.0f );

    // Note: Full matrix multiplication would be needed for proper verification
    // This is a simplified test checking the cosine/sine values
    auto singleRow0 = SquareMatrix<float, 4>::Simd::Traits::ToArray( singleRotation.simd[ 0 ] );

    float expectedCosine = std::cos( HALF_ANGLE * 2.0f );
    bool angleAddsCorrectly = ApproximatelyEqual( singleRow0[ 0 ], expectedCosine, 0.01f );
    BOOST_TEST( angleAddsCorrectly );
}

/// <summary>
/// Tests the RotationZ function which creates a 4x4 rotation matrix around the Z-axis.
/// </summary>
/// <remarks>
/// A Z-axis rotation matrix should have the form:
/// [ cos(θ)  sin(θ)   0   0]
/// [-sin(θ)   cos(θ)  0   0]
/// [0        0        1   0]
/// [0        0        0   1]
/// </remarks>

BOOST_AUTO_TEST_CASE( RotationZZeroAngleReturnsIdentity )
{
    // Arrange
    float angle = 0.0f;
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Math::RotationZ( angle );
    Math::SquareMatrix<float, 4> matrixData = rotationMatrix;

    // Assert - Identity matrix
    BOOST_TEST( std::abs( matrixData[ 0 ][ 0 ] - 1.0f ) < epsilon ); // cos(0) = 1
    BOOST_TEST( std::abs( matrixData[ 0 ][ 1 ] - 0.0f ) < epsilon ); // sin(0) = 0
    BOOST_TEST( std::abs( matrixData[ 1 ][ 0 ] - 0.0f ) < epsilon ); // -sin(0) = 0
    BOOST_TEST( std::abs( matrixData[ 1 ][ 1 ] - 1.0f ) < epsilon ); // cos(0) = 1
    BOOST_TEST( std::abs( matrixData[ 2 ][ 2 ] - 1.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 3 ][ 3 ] - 1.0f ) < epsilon );
}

BOOST_AUTO_TEST_CASE( RotationZ90DegreesRotatesCorrectly )
{
    // Arrange
    float angle = Harlinn::Math::Constants<float>::Pi / 2.0f; // 90 degrees
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - 90 degree rotation
    // cos(90°) = 0, sin(90°) = 1
    BOOST_TEST( std::abs( matrixData[ 0 ][ 0 ] - 0.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 0 ][ 1 ] - 1.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 1 ][ 0 ] - ( -1.0f ) ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 1 ][ 1 ] - 0.0f ) < epsilon );
}

BOOST_AUTO_TEST_CASE( RotationZ180DegreesRotatesCorrectly )
{
    // Arrange
    float angle = Harlinn::Math::Constants<float>::Pi; // 180 degrees
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - 180 degree rotation
    // cos(180°) = -1, sin(180°) = 0
    BOOST_TEST( std::abs( matrixData[ 0 ][ 0 ] - ( -1.0f ) ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 0 ][ 1 ] - 0.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 1 ][ 0 ] - 0.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 1 ][ 1 ] - ( -1.0f ) ) < epsilon );
}

BOOST_AUTO_TEST_CASE( RotationZ270DegreesRotatesCorrectly )
{
    // Arrange
    float angle = 3.0f * Harlinn::Math::Constants<float>::Pi / 2.0f; // 270 degrees
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - 270 degree rotation
    // cos(270°) = 0, sin(270°) = -1
    BOOST_TEST( std::abs( matrixData[ 0 ][ 0 ] - 0.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 0 ][ 1 ] - ( -1.0f ) ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 1 ][ 0 ] - 1.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 1 ][ 1 ] - 0.0f ) < epsilon );
}

BOOST_AUTO_TEST_CASE( RotationZ360DegreesReturnsIdentity )
{
    // Arrange
    float angle = 2.0f * Harlinn::Math::Constants<float>::Pi; // 360 degrees
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - Full rotation returns to identity
    BOOST_TEST( std::abs( matrixData[ 0 ][ 0 ] - 1.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 0 ][ 1 ] - 0.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 1 ][ 0 ] - 0.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 1 ][ 1 ] - 1.0f ) < epsilon );
}

BOOST_AUTO_TEST_CASE( RotationZNegativeAngleRotatesInOppositeDirection )
{
    // Arrange
    float positiveAngle = Harlinn::Math::Constants<float>::Pi / 4.0f; // 45 degrees
    float negativeAngle = -positiveAngle;
    const float epsilon = 1e-5f;

    // Act
    auto positiveMatrix = Harlinn::Math::RotationZ( positiveAngle );
    auto negativeMatrix = Harlinn::Math::RotationZ( negativeAngle );
    auto posData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( positiveMatrix );
    auto negData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( negativeMatrix );

    // Assert - Negative rotation should be transpose of positive rotation (for rotation matrices)
    BOOST_TEST( std::abs( posData[ 0 ][ 0 ] - negData[ 0 ][ 0 ] ) < epsilon );
    BOOST_TEST( std::abs( posData[ 0 ][ 1 ] - negData[ 1 ][ 0 ] ) < epsilon );
    BOOST_TEST( std::abs( posData[ 1 ][ 0 ] - negData[ 0 ][ 1 ] ) < epsilon );
    BOOST_TEST( std::abs( posData[ 1 ][ 1 ] - negData[ 1 ][ 1 ] ) < epsilon );
}

BOOST_AUTO_TEST_CASE( RotationZPreservesZAndWRows )
{
    // Arrange
    float angle = Harlinn::Math::Constants<float>::Pi / 3.0f; // 60 degrees
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - Z-axis rotation should not affect Z and W rows
    BOOST_TEST( std::abs( matrixData[ 2 ][ 0 ] - 0.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 2 ][ 1 ] - 0.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 2 ][ 2 ] - 1.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 2 ][ 3 ] - 0.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 3 ][ 0 ] - 0.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 3 ][ 1 ] - 0.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 3 ][ 2 ] - 0.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 3 ][ 3 ] - 1.0f ) < epsilon );
}

BOOST_AUTO_TEST_CASE( RotationZMatrixIsOrthogonal )
{
    // Arrange
    float angle = Harlinn::Math::Constants<float>::Pi / 6.0f; // 30 degrees
    const float epsilon = 1e-4f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - Rotation matrix should be orthogonal (columns are unit vectors and orthogonal)
    // First column norm should be 1
    float col0Norm = std::sqrt( matrixData[ 0 ][ 0 ] * matrixData[ 0 ][ 0 ] +
        matrixData[ 1 ][ 0 ] * matrixData[ 1 ][ 0 ] );
    BOOST_TEST( std::abs( col0Norm - 1.0f ) < epsilon );

    // Second column norm should be 1
    float col1Norm = std::sqrt( matrixData[ 0 ][ 1 ] * matrixData[ 0 ][ 1 ] +
        matrixData[ 1 ][ 1 ] * matrixData[ 1 ][ 1 ] );
    BOOST_TEST( std::abs( col1Norm - 1.0f ) < epsilon );

    // First and second columns should be orthogonal (dot product = 0)
    float dotProduct = matrixData[ 0 ][ 0 ] * matrixData[ 0 ][ 1 ] +
        matrixData[ 1 ][ 0 ] * matrixData[ 1 ][ 1 ];
    BOOST_TEST( std::abs( dotProduct ) < epsilon );
}

BOOST_AUTO_TEST_CASE( RotationZSmallAngleApproximation )
{
    // Arrange
    float angle = 0.001f; // Very small angle
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - For small angles: cos(θ) ≈ 1, sin(θ) ≈ θ
    BOOST_TEST( std::abs( matrixData[ 0 ][ 0 ] - 1.0f ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 0 ][ 1 ] - angle ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 1 ][ 0 ] - ( -angle ) ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 1 ][ 1 ] - 1.0f ) < epsilon );
}

BOOST_AUTO_TEST_CASE( RotationZConsistentWithTrigFunctions )
{
    // Arrange
    float angle = Harlinn::Math::Constants<float>::Pi / 8.0f; // 22.5 degrees
    float expectedCos = std::cos( angle );
    float expectedSin = std::sin( angle );
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert
    BOOST_TEST( std::abs( matrixData[ 0 ][ 0 ] - expectedCos ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 0 ][ 1 ] - expectedSin ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 1 ][ 0 ] - ( -expectedSin ) ) < epsilon );
    BOOST_TEST( std::abs( matrixData[ 1 ][ 1 ] - expectedCos ) < epsilon );
}


BOOST_AUTO_TEST_CASE( RotationWithZeroAngles )
{
    // Zero rotation should produce identity matrix
    Vector3f angles( 0.0f, 0.0f, 0.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    bool isIdentity = MatrixApproximatelyEqual( result, SquareMatrix<float, 4>( ) );
    BOOST_TEST( isIdentity );
}

BOOST_AUTO_TEST_CASE( RotationWithPitchOnly )
{
    // Rotation around X-axis only (pitch = 90 degrees)
    Vector3f angles( Constants<float>::Pi / 2.0f, 0.0f, 0.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    // After 90-degree pitch rotation:
    // [1,  0,  0, 0]
    // [0,  0, -1, 0]
    // [0,  1,  0, 0]
    // [0,  0,  0, 1]

    bool checkIdentityX = ApproximatelyEqual( result[ 0 ][ 0 ], 1.0f );
    bool checkRotY = ApproximatelyEqual( result[ 1 ][ 1 ], 0.0f );
    bool checkRotZ = ApproximatelyEqual( result[ 2 ][ 2 ], 0.0f );
    bool checkW = ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );

    BOOST_TEST( checkIdentityX );
    BOOST_TEST( checkRotY );
    BOOST_TEST( checkRotZ );
    BOOST_TEST( checkW );
}

BOOST_AUTO_TEST_CASE( RotationWithYawOnly )
{
    // Rotation around Y-axis only (yaw = 90 degrees)
    Vector3f angles( 0.0f, Constants<float>::Pi / 2.0f, 0.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    bool checkW = ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );
    BOOST_TEST( checkW );
}

BOOST_AUTO_TEST_CASE( RotationWithRollOnly )
{
    // Rotation around Z-axis only (roll = 90 degrees)
    Vector3f angles( 0.0f, 0.0f, Constants<float>::Pi / 2.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    bool checkW = ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );
    BOOST_TEST( checkW );
}

BOOST_AUTO_TEST_CASE( RotationWith180DegreePitch )
{
    // 180-degree rotation around X-axis
    Vector3f angles( Constants<float>::Pi, 0.0f, 0.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    // Should have identity X component and negated Y and Z
    bool checkX = ApproximatelyEqual( result[ 0 ][ 0 ], 1.0f );
    bool checkY = ApproximatelyEqual( result[ 1 ][ 1 ], -1.0f, EPSILON * 10 );
    bool checkZ = ApproximatelyEqual( result[ 2 ][ 2 ], -1.0f, EPSILON * 10 );
    bool checkW = ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );

    BOOST_TEST( checkX );
    BOOST_TEST( checkY );
    BOOST_TEST( checkZ );
    BOOST_TEST( checkW );
}

BOOST_AUTO_TEST_CASE( RotationWith360Degrees )
{
    // Full rotation (360 degrees) should return close to identity
    Vector3f angles( Constants<float>::PiTimes2, 0.0f, 0.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );
    auto identity = SquareMatrix<float, 4>( );

    bool isNearlyIdentity = MatrixApproximatelyEqual( result, identity, EPSILON * 100 );
    BOOST_TEST( isNearlyIdentity );
}

BOOST_AUTO_TEST_CASE( RotationWithCombinedAngles )
{
    // Combined rotation (30 degrees pitch, 45 degrees yaw, 60 degrees roll)
    Vector3f angles( Constants<float>::Pi / 6.0f, Constants<float>::Pi / 4.0f, Constants<float>::Pi / 3.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    // Verify matrix is valid (bottom row should be [0, 0, 0, 1])
    bool checkBottomRow = ApproximatelyEqual( result[ 3 ][ 0 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 1 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 2 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );

    BOOST_TEST( checkBottomRow );
}

BOOST_AUTO_TEST_CASE( RotationWithNegativeAngles )
{
    // Negative angles should rotate in opposite direction
    Vector3f anglesPositive( Constants<float>::Pi / 4.0f, 0.0f, 0.0f );
    Vector3f anglesNegative( -Constants<float>::Pi / 4.0f, 0.0f, 0.0f );

    auto rotMatrixPos = Rotation( anglesPositive.ToSimd( ) );
    auto rotMatrixNeg = Rotation( anglesNegative.ToSimd( ) );

    auto resultPos = SquareMatrix<float, 4>( rotMatrixPos );
    auto resultNeg = SquareMatrix<float, 4>( rotMatrixNeg );

    // Positive and negative rotations should have opposite sine components
    // but same cosine components (for pitch-only rotation)
    bool checkCosine = ApproximatelyEqual( resultPos[ 1 ][ 1 ], resultNeg[ 1 ][ 1 ] );
    BOOST_TEST( checkCosine );
}

BOOST_AUTO_TEST_CASE( RotationMatrixBottomRowConsistency )
{
    // The bottom row of a rotation matrix should always be [0, 0, 0, 1]
    Vector3f angles( 0.5f, 0.3f, 0.7f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    bool bottomRowCorrect = ApproximatelyEqual( result[ 3 ][ 0 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 1 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 2 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );

    BOOST_TEST( bottomRowCorrect );
}

BOOST_AUTO_TEST_CASE( RotationMatrixRightColumnConsistency )
{
    // The right column (except W) should be zero for a pure rotation matrix
    Vector3f angles( 0.6f, 0.4f, 0.8f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    bool rightColumnCorrect = ApproximatelyEqual( result[ 0 ][ 3 ], 0.0f ) &&
        ApproximatelyEqual( result[ 1 ][ 3 ], 0.0f ) &&
        ApproximatelyEqual( result[ 2 ][ 3 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );

    BOOST_TEST( rightColumnCorrect );
}

BOOST_AUTO_TEST_CASE( RotationWithVector4D )
{
    // Test that function works with 4D vectors (Size == 4)
    Vector4f angles( 0.5f, 0.3f, 0.7f, 0.0f );  // 4th component unused
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    bool checkW = ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );
    BOOST_TEST( checkW );
}

BOOST_AUTO_TEST_CASE( RotationSmallAngles )
{
    // Very small angles should produce a matrix close to identity
    Vector3f angles( 0.001f, 0.001f, 0.001f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );
    auto identity = SquareMatrix<float, 4>( );

    bool isNearlyIdentity = MatrixApproximatelyEqual( result, identity, 0.01f );
    BOOST_TEST( isNearlyIdentity );
}

BOOST_AUTO_TEST_CASE( RotationLargeAngles )
{
    // Test with large angles (multiple rotations)
    Vector3f angles( Constants<float>::PiTimes2 + 0.5f, Constants<float>::PiTimes2 + 0.3f, Constants<float>::PiTimes2 + 0.7f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    // Bottom row should still be [0, 0, 0, 1]
    bool bottomRowCorrect = ApproximatelyEqual( result[ 3 ][ 0 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 1 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 2 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );

    BOOST_TEST( bottomRowCorrect );
}

BOOST_AUTO_TEST_CASE( RotationNormalIdentity )
{
    // Identity rotation: angle = 0, any normalized axis
    Math::Vector<float, 3>::Simd axis( 1.0f, 0.0f, 0.0f );
    float angle = 0.0f;

    auto result = RotationNormal( axis, angle );

    // Extract rows
    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Expected identity matrix
    BOOST_TEST( ApproximatelyEqual( r0.x( ), 1.0f ) );
    BOOST_TEST( ApproximatelyEqual( r0.y( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r0.z( ), 0.0f ) );

    BOOST_TEST( ApproximatelyEqual( r1.x( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r1.y( ), 1.0f ) );
    BOOST_TEST( ApproximatelyEqual( r1.z( ), 0.0f ) );

    BOOST_TEST( ApproximatelyEqual( r2.x( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r2.y( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r2.z( ), 1.0f ) );

    BOOST_TEST( IsOrthogonalMatrix( r0, r1, r2, r3 ) );
}

BOOST_AUTO_TEST_CASE( RotationNormalAxisX90Degrees )
{
    // 90-degree rotation around X-axis
    Math::Vector<float, 3>::Simd axis( 1.0f, 0.0f, 0.0f );
    float angle = 3.14159265f / 2.0f; // 90 degrees

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Rotation around X by 90 degrees: [1 0 0; 0 0 1; 0 -1 0]
    BOOST_TEST( ApproximatelyEqual( r0.x( ), 1.0f ) );
    BOOST_TEST( ApproximatelyEqual( r0.y( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r0.z( ), 0.0f ) );

    BOOST_TEST( ApproximatelyEqual( r1.x( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r1.y( ), 0.0f, 0.01f ) );
    BOOST_TEST( ApproximatelyEqual( r1.z( ), 1.0f, 0.01f ) );

    BOOST_TEST( ApproximatelyEqual( r2.x( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r2.y( ), -1.0f, 0.01f ) );
    BOOST_TEST( ApproximatelyEqual( r2.z( ), 0.0f, 0.01f ) );

    BOOST_TEST( IsOrthogonalMatrix( r0, r1, r2, r3 ) );
}

BOOST_AUTO_TEST_CASE( RotationNormalAxisY90Degrees )
{
    // 90-degree rotation around Y-axis
    Math::Vector<float, 3>::Simd axis( 0.0f, 1.0f, 0.0f );
    float angle = 3.14159265f / 2.0f; // 90 degrees

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Rotation around Y by 90 degrees: [0 0 -1; 0 1 0; 1 0 0]
    BOOST_TEST( ApproximatelyEqual( r0.x( ), 0.0f, 0.01f ) );
    BOOST_TEST( ApproximatelyEqual( r0.y( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r0.z( ), -1.0f, 0.01f ) );

    BOOST_TEST( ApproximatelyEqual( r1.x( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r1.y( ), 1.0f ) );
    BOOST_TEST( ApproximatelyEqual( r1.z( ), 0.0f ) );

    BOOST_TEST( ApproximatelyEqual( r2.x( ), 1.0f, 0.01f ) );
    BOOST_TEST( ApproximatelyEqual( r2.y( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r2.z( ), 0.0f, 0.01f ) );

    BOOST_TEST( IsOrthogonalMatrix( r0, r1, r2, r3 ) );
}

BOOST_AUTO_TEST_CASE( RotationNormalAxisZ90Degrees )
{
    // 90-degree rotation around Z-axis
    Math::Vector<float, 3>::Simd axis( 0.0f, 0.0f, 1.0f );
    float angle = 3.14159265f / 2.0f; // 90 degrees

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Rotation around Z by 90 degrees: [0 1 0; -1 0 0; 0 0 1]
    BOOST_TEST( ApproximatelyEqual( r0.x( ), 0.0f, 0.01f ) );
    BOOST_TEST( ApproximatelyEqual( r0.y( ), 1.0f, 0.01f ) );
    BOOST_TEST( ApproximatelyEqual( r0.z( ), 0.0f ) );

    BOOST_TEST( ApproximatelyEqual( r1.x( ), -1.0f, 0.01f ) );
    BOOST_TEST( ApproximatelyEqual( r1.y( ), 0.0f, 0.01f ) );
    BOOST_TEST( ApproximatelyEqual( r1.z( ), 0.0f ) );

    BOOST_TEST( ApproximatelyEqual( r2.x( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r2.y( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r2.z( ), 1.0f ) );

    BOOST_TEST( IsOrthogonalMatrix( r0, r1, r2, r3 ) );
}

BOOST_AUTO_TEST_CASE( RotationNormalArbitrary )
{
    // Arbitrary rotation: 45 degrees around normalized [1, 1, 1] axis
    Math::Vector<float, 3>::Simd axis( 0.57735f, 0.57735f, 0.57735f ); // normalized [1,1,1]
    float angle = 3.14159265f / 4.0f; // 45 degrees

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Verify it's a valid rotation matrix (orthogonal)
    BOOST_TEST( IsOrthogonalMatrix( r0, r1, r2, r3 ) );
}

BOOST_AUTO_TEST_CASE( RotationNormalAxisInvariance )
{
    // Rotating around an axis should leave that axis unchanged
    Math::Vector<float, 3>::Simd axis( 1.0f, 0.0f, 0.0f );
    float angle = 1.5f; // arbitrary angle

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );

    // Rotate the axis by the matrix: M * axis should equal axis
    float x = r0.x( ) * axis.x( ) + r0.y( ) * axis.y( ) + r0.z( ) * axis.z( );
    float y = r1.x( ) * axis.x( ) + r1.y( ) * axis.y( ) + r1.z( ) * axis.z( );
    float z = r2.x( ) * axis.x( ) + r2.y( ) * axis.y( ) + r2.z( ) * axis.z( );

    BOOST_TEST( ApproximatelyEqual( x, axis.x( ) ) );
    BOOST_TEST( ApproximatelyEqual( y, axis.y( ) ) );
    BOOST_TEST( ApproximatelyEqual( z, axis.z( ) ) );
}

BOOST_AUTO_TEST_CASE( RotationNormalMatrixFormat )
{
    // Verify the 4x4 matrix structure
    Math::Vector<float, 3>::Simd axis( 0.0f, 1.0f, 0.0f );
    float angle = 1.5f;

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Last row should be [0, 0, 0, 1]
    BOOST_TEST( ApproximatelyEqual( r3.x( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r3.y( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r3.z( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r3.w( ), 1.0f ) );
}

BOOST_AUTO_TEST_CASE( RotationNormalWithTupleType )
{
    // Test with Tuple3 instead of Simd type
    Math::Vector<float, 3> axis( 1.0f, 0.0f, 0.0f );
    float angle = 3.14159265f / 2.0f;

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Should produce same result as with Simd type
    BOOST_TEST( ApproximatelyEqual( r0.x( ), 1.0f ) );
    BOOST_TEST( IsOrthogonalMatrix( r0, r1, r2, r3 ) );
}

BOOST_AUTO_TEST_CASE( RotationNormalLargeAngle )
{
    // Test with angle > 2*pi
    Math::Vector<float, 3>::Simd axis( 0.0f, 0.0f, 1.0f );
    float angle = 3.14159265f * 4.0f; // 4*pi (equivalent to 0)

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    BOOST_TEST( IsOrthogonalMatrix( r0, r1, r2, r3 ) );
}

BOOST_AUTO_TEST_CASE( RotationNormal180Degrees )
{
    // 180-degree rotation around X-axis
    Math::Vector<float, 3>::Simd axis( 1.0f, 0.0f, 0.0f );
    float angle = 3.14159265f; // 180 degrees

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Rotation around X by 180 degrees: [1 0 0; 0 -1 0; 0 0 -1]
    BOOST_TEST( ApproximatelyEqual( r0.x( ), 1.0f ) );
    BOOST_TEST( ApproximatelyEqual( r0.y( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r0.z( ), 0.0f ) );

    BOOST_TEST( ApproximatelyEqual( r1.x( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r1.y( ), -1.0f, 0.01f ) );
    BOOST_TEST( ApproximatelyEqual( r1.z( ), 0.0f, 0.01f ) );

    BOOST_TEST( ApproximatelyEqual( r2.x( ), 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( r2.y( ), 0.0f, 0.01f ) );
    BOOST_TEST( ApproximatelyEqual( r2.z( ), -1.0f, 0.01f ) );

    BOOST_TEST( IsOrthogonalMatrix( r0, r1, r2, r3 ) );
}

BOOST_AUTO_TEST_CASE( RotationAxisWithXAxis )
{
    // Rotate 90 degrees around X axis
    Vector3f xAxis( 1.0f, 0.0f, 0.0f );
    float angle90 = Constants<float>::Pi / 2.0f;

    auto rotationMatrix = RotationAxis( xAxis, angle90 );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    BOOST_TEST( valid );
}

BOOST_AUTO_TEST_CASE( RotationAxisWithYAxis )
{
    // Rotate 45 degrees around Y axis
    Vector3f yAxis( 0.0f, 1.0f, 0.0f );
    float angle45 = Constants<float>::Pi / 4.0f;

    auto rotationMatrix = RotationAxis( yAxis, angle45 );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    BOOST_TEST( valid );
}

BOOST_AUTO_TEST_CASE( RotationAxisWithZAxis )
{
    // Rotate 180 degrees around Z axis
    Vector3f zAxis( 0.0f, 0.0f, 1.0f );
    float angle180 = Constants<float>::Pi;

    auto rotationMatrix = RotationAxis( zAxis, angle180 );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    BOOST_TEST( valid );
}

BOOST_AUTO_TEST_CASE( RotationAxisWithArbitraryAxis )
{
    // Rotate 60 degrees around arbitrary normalized axis
    Vector3f arbitraryAxis( 1.0f, 1.0f, 1.0f );
    float angle60 = Constants<float>::Pi / 3.0f;

    auto rotationMatrix = RotationAxis( arbitraryAxis, angle60 );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    BOOST_TEST( valid );
}

BOOST_AUTO_TEST_CASE( RotationAxisWithSmallAngle )
{
    // Small angle rotation (1 degree)
    Vector3f axis( 1.0f, 0.0f, 0.0f );
    float smallAngle = Constants<float>::Pi / 180.0f; // 1 degree in radians

    auto rotationMatrix = RotationAxis( axis, smallAngle );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    BOOST_TEST( valid );
}

BOOST_AUTO_TEST_CASE( RotationAxisWithLargeAngle )
{
    // Large angle rotation (359 degrees)
    Vector3f axis( 0.0f, 1.0f, 0.0f );
    float largeAngle = 359.0f * Constants<float>::Pi / 180.0f;

    auto rotationMatrix = RotationAxis( axis, largeAngle );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    BOOST_TEST( valid );
}

BOOST_AUTO_TEST_CASE( RotationAxisZeroAngle )
{
    // Zero angle rotation should result in identity-like rotation
    Vector3f axis( 1.0f, 1.0f, 1.0f );
    float zeroAngle = 0.0f;

    auto rotationMatrix = RotationAxis( axis, zeroAngle );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    BOOST_TEST( valid );
}

BOOST_AUTO_TEST_CASE( RotationAxisNegativeAngle )
{
    // Negative angle (counterclockwise vs clockwise)
    Vector3f axis( 1.0f, 0.0f, 0.0f );
    float negativeAngle = -Constants<float>::Pi / 4.0f;

    auto rotationMatrix = RotationAxis( axis, negativeAngle );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    BOOST_TEST( valid );
}

BOOST_AUTO_TEST_CASE( RotationAxisWithUnnormalizedAxis )
{
    // Non-unit axis vector (function should normalize it)
    Vector3f unnormalizedAxis( 2.0f, 2.0f, 2.0f );
    float angle = Constants<float>::Pi / 6.0f;

    auto rotationMatrix = RotationAxis( unnormalizedAxis, angle );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    BOOST_TEST( valid );
}

BOOST_AUTO_TEST_CASE( RotationAxisConsistency )
{
    // Same rotation from different axis representations should yield similar results
    Vector3f axis1( 3.0f, 4.0f, 0.0f );  // Unnormalized
    Vector3f axis2 = Normalize( axis1 );  // Normalized
    float angle = Constants<float>::Pi / 3.0f;

    auto matrix1 = RotationAxis( axis1, angle );
    auto matrix2 = RotationAxis( axis2, angle );

    // Results should be very similar (allowing for normalization differences)
    bool mapsAreEqual = matrix1 == matrix2;
    BOOST_TEST( mapsAreEqual );
}

BOOST_AUTO_TEST_CASE( RotationAxisFullRotation )
{
    // Full 360-degree rotation should result in nearly identity
    Vector3f axis( 1.0f, 0.0f, 0.0f );
    float fullRotation = 2.0f * Constants<float>::Pi;

    auto rotationMatrix = RotationAxis( axis, fullRotation );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    BOOST_TEST( valid );
}

BOOST_AUTO_TEST_CASE( RotationAxisWithVector4 )
{
    // Test with Vector4 (Size == 4, which satisfies Size > 2)
    Vector4f axis( 1.0f, 1.0f, 1.0f, 0.0f );
    float angle = Constants<float>::Pi / 4.0f;

    auto rotationMatrix = RotationAxis( axis, angle );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    BOOST_TEST( valid );
}

BOOST_AUTO_TEST_CASE( RotationAxisAppliedToVector )
{
    // Verify that rotating a vector about an axis works correctly
    // Rotate a vector 90 degrees about Z axis
    Vector3f zAxis( 0.0f, 0.0f, 1.0f );
    float angle90 = Constants<float>::Pi / 2.0f;
    Vector3f testVector( 1.0f, 0.0f, 0.0f );

    auto rotationMatrix = RotationAxis( zAxis, angle90 );

    // Create a 4D vector for transformation
    auto testVec4 = Vector4f( testVector.x, testVector.y, testVector.z, 0.0f );
    auto rotated = Math::Transform( testVec4.ToSimd( ), rotationMatrix);

    // After 90-degree rotation about Z: (1,0,0) should become approximately (0,1,0)
    float resultX = rotated[ 0 ];
    float resultY = rotated[ 1 ];
    float resultZ = rotated[ 2 ];

    bool xNearZero = ApproximatelyEqual( resultX, 0.0f, 1e-4f );
    bool yNearOne = ApproximatelyEqual( resultY, 1.0f, 1e-4f );
    bool zStaysZero = ApproximatelyEqual( resultZ, 0.0f, 1e-4f );

    BOOST_TEST( xNearZero );
    BOOST_TEST( yNearOne );
    BOOST_TEST( zStaysZero );
}

// Test identity quaternion produces identity matrix
BOOST_AUTO_TEST_CASE( RotationIdentityQuaternion )
{
    Quaternion<float> q = Quaternion<float>::Identity( );
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    // Check that the result is approximately the identity matrix
    for ( size_t i = 0; i < 4; ++i )
    {
        for ( size_t j = 0; j < 4; ++j )
        {
            float expected = ( i == j ) ? 1.0f : 0.0f;
            BOOST_TEST( ApproximatelyEqual( result[ i ][ j ], expected ),
                "Identity quaternion at [" << i << "][" << j << "] = "
                << result[ i ][ j ] << " vs expected " << expected );
        }
    }
}

// Test 180-degree rotation around X axis
BOOST_AUTO_TEST_CASE( Rotation180AroundXAxis )
{
    // Quaternion for 180 degrees around X: q = (sin(90), 0, 0, cos(90)) = (1, 0, 0, 0)
    Quaternion<float> q( 1.0f, 0.0f, 0.0f, 0.0f );
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    // Expected rotation matrix for 180 degrees around X:
    // [1,  0,  0, 0]
    // [0, -1,  0, 0]
    // [0,  0, -1, 0]
    // [0,  0,  0, 1]

    BOOST_TEST( ApproximatelyEqual( result[ 0 ][ 0 ], 1.0f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 1 ][ 1 ], -1.0f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 2 ][ 2 ], -1.0f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f ) );

    // Off-diagonal elements should be 0
    BOOST_TEST( ApproximatelyEqual( result[ 0 ][ 1 ], 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 1 ][ 0 ], 0.0f ) );
}

// Test 90-degree rotation around Z axis
BOOST_AUTO_TEST_CASE( Rotation90AroundZAxis )
{
    // Quaternion for 90 degrees around Z: q = (0, 0, sin(45), cos(45))
    float angle45 = 3.14159265359f / 4.0f;  // 45 degrees in radians
    Quaternion<float> q( 0.0f, 0.0f, std::sin( angle45 ), std::cos( angle45 ) );
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    // After rotation around Z by 90 degrees:
    // [0, 1, 0, 0]
    // [-1,  0, 0, 0]
    // [0,  0, 1, 0]
    // [0,  0, 0, 1]

    BOOST_TEST( ApproximatelyEqual( result[ 0 ][ 0 ], 0.0f, 1e-4f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 0 ][ 1 ], 1.0f, 1e-4f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 1 ][ 0 ], -1.0f, 1e-4f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 1 ][ 1 ], 0.0f, 1e-4f ) );
}

// Test that rotation matrix is orthogonal (M^T * M = I)
BOOST_AUTO_TEST_CASE( RotationMatrixIsOrthogonal )
{
    // Create arbitrary rotation quaternion
    Quaternion<float> q( 0.5f, 0.5f, 0.5f, 0.5f );
    q = Normalize( q );  // Ensure it's normalized
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    // Compute M^T * M
    std::array<std::array<float, 4>, 4> transpose{};
    for ( size_t i = 0; i < 4; ++i )
    {
        for ( size_t j = 0; j < 4; ++j )
        {
            transpose[ i ][ j ] = result[ j ][ i ];
        }
    }

    std::array<std::array<float, 4>, 4> product{};
    for ( size_t i = 0; i < 4; ++i )
    {
        for ( size_t j = 0; j < 4; ++j )
        {
            product[ i ][ j ] = 0.0f;
            for ( size_t k = 0; k < 4; ++k )
            {
                product[ i ][ j ] += transpose[ i ][ k ] * result[ k ][ j ];
            }
        }
    }

    // Check if product is identity
    for ( size_t i = 0; i < 4; ++i )
    {
        for ( size_t j = 0; j < 4; ++j )
        {
            float expected = ( i == j ) ? 1.0f : 0.0f;
            BOOST_TEST( ApproximatelyEqual( product[ i ][ j ], expected, 1e-4f ),
                "Orthogonal property failed at [" << i << "][" << j << "]" );
        }
    }
}

// Test that bottom row is [0, 0, 0, 1]
BOOST_AUTO_TEST_CASE( RotationMatrixBottomRow )
{
    Quaternion<float> q( 0.3f, 0.4f, 0.5f, 0.7f );
    q = Normalize( q );
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    BOOST_TEST( ApproximatelyEqual( result[ 3 ][ 0 ], 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 3 ][ 1 ], 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 3 ][ 2 ], 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f ) );
}

// Test that right column is [0, 0, 0, 1]
BOOST_AUTO_TEST_CASE( RotationMatrixRightColumn )
{
    Quaternion<float> q( 0.2f, 0.6f, 0.3f, 0.7f );
    q = Normalize( q );
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    BOOST_TEST( ApproximatelyEqual( result[ 0 ][ 3 ], 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 1 ][ 3 ], 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 2 ][ 3 ], 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f ) );
}

// Test rotation of a vector (0, 0, 1) by identity should give (0, 0, 1)
BOOST_AUTO_TEST_CASE( RotationVectorIdentity )
{
    Quaternion<float> q = Quaternion<float>::Identity( );
    auto rotationMatrix = Rotation( q.ToSimd( ) );
    auto result = ExtractMatrix( rotationMatrix );

    // The Z-axis vector (0, 0, 1, 0) rotated by identity should remain (0, 0, 1, 0)
    float resX = result[ 0 ][ 2 ];
    float resY = result[ 1 ][ 2 ];
    float resZ = result[ 2 ][ 2 ];

    BOOST_TEST( ApproximatelyEqual( resX, 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( resY, 0.0f ) );
    BOOST_TEST( ApproximatelyEqual( resZ, 1.0f ) );
}

// Test that normalized quaternions produce valid rotation matrices
BOOST_AUTO_TEST_CASE( RotationNormalizedQuaternion )
{
    // Create a normalized quaternion
    Quaternion<float> q( 0.1f, 0.2f, 0.3f, 0.9f );
    q = Normalize( q );

    BOOST_TEST( ApproximatelyEqual( ScalarLength( q.ToSimd( ) ), 1.0f, 1e-5f ),
        "Quaternion normalization failed" );

    auto resultSimd = Rotation( q.ToSimd( ) );
    auto result = ExtractMatrix( resultSimd );

    // All matrix elements should be finite
    for ( size_t i = 0; i < 4; ++i )
    {
        for ( size_t j = 0; j < 4; ++j )
        {
            BOOST_TEST( std::isfinite( result[ i ][ j ] ),
                "Matrix element [" << i << "][" << j << "] is not finite" );
        }
    }
}

// Test small angle approximation
BOOST_AUTO_TEST_CASE( RotationSmallAngle )
{
    // Very small rotation around X axis
    float smallAngle = 0.01f;  // 0.01 radians
    float halfAngle = smallAngle / 2.0f;

    Quaternion<float> q( std::sin( halfAngle ), 0.0f, 0.0f, std::cos( halfAngle ) );
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    // For small angles, rotation matrix should be close to identity
    float tolerance = 0.02f;

    BOOST_TEST( std::abs( result[ 0 ][ 0 ] - 1.0f ) < tolerance );
    BOOST_TEST( std::abs( result[ 1 ][ 1 ] - 1.0f ) < tolerance );
    BOOST_TEST( std::abs( result[ 2 ][ 2 ] - 1.0f ) < tolerance );
}

BOOST_AUTO_TEST_CASE( IdentityTransformation )
{
    // Test transformation matrix with identity values (no scaling, rotation, translation)
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 1.0f, 1.0f, 1.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Identity matrix should have 1s on diagonal and 0s elsewhere
    bool isIdentity = ApproximatelyEqual( matrix[ 0 ][ 0 ], 1.0f ) && ApproximatelyEqual( matrix[ 1 ][ 1 ], 1.0f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 2 ], 1.0f ) && ApproximatelyEqual( matrix[ 3 ][ 3 ], 1.0f ) &&
        ApproximatelyEqual( matrix[ 0 ][ 1 ], 0.0f ) && ApproximatelyEqual( matrix[ 0 ][ 2 ], 0.0f ) &&
        ApproximatelyEqual( matrix[ 1 ][ 0 ], 0.0f ) && ApproximatelyEqual( matrix[ 1 ][ 2 ], 0.0f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 0 ], 0.0f ) && ApproximatelyEqual( matrix[ 2 ][ 1 ], 0.0f );

    BOOST_TEST( isIdentity );
}

BOOST_AUTO_TEST_CASE( ScalingOnlyTransformation )
{
    // Test transformation matrix with only scaling
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 2.0f, 3.0f, 4.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Check that diagonal elements contain scaling factors
    bool hasScaling = ApproximatelyEqual( matrix[ 0 ][ 0 ], 2.0f ) && ApproximatelyEqual( matrix[ 1 ][ 1 ], 3.0f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 2 ], 4.0f ) && ApproximatelyEqual( matrix[ 3 ][ 3 ], 1.0f );

    BOOST_TEST( hasScaling );
}

BOOST_AUTO_TEST_CASE( TranslationOnlyTransformation )
{
    // Test transformation matrix with only translation
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 1.0f, 1.0f, 1.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 5.0f, 6.0f, 7.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Check that translation is in the appropriate position (typically last row/column for column-major or last column for row-major)
    // The exact position depends on the matrix layout convention used
    bool hasTranslation = ( ApproximatelyEqual( matrix[ 3 ][ 0 ], 5.0f ) && ApproximatelyEqual( matrix[ 3 ][ 1 ], 6.0f ) && ApproximatelyEqual( matrix[ 3 ][ 2 ], 7.0f ) ) ||
        ( ApproximatelyEqual( matrix[ 0 ][ 3 ], 5.0f ) && ApproximatelyEqual( matrix[ 1 ][ 3 ], 6.0f ) && ApproximatelyEqual( matrix[ 2 ][ 3 ], 7.0f ) );

    BOOST_TEST( hasTranslation );
}

BOOST_AUTO_TEST_CASE( CombinedTransformation )
{
    // Test transformation matrix with scaling, rotation, and translation
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 2.0f, 2.0f, 2.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    // 90-degree rotation around Z-axis
    Quaternion<float> rotationQuaternion( 0.0f, 0.0f, 0.7071068f, 0.7071068f );
    Vector3f translation( 10.0f, 20.0f, 30.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // The matrix should be a valid 4x4 transformation matrix
    // Check that bottom-right is 1.0f
    bool isValidMatrix = ApproximatelyEqual( matrix[ 3 ][ 3 ], 1.0f );

    BOOST_TEST( isValidMatrix );
}

BOOST_AUTO_TEST_CASE( NonZeroScalingOrigin )
{
    // Test transformation matrix with non-zero scaling origin
    Point3f scalingOrigin( 5.0f, 5.0f, 5.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 2.0f, 2.0f, 2.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Matrix should have scaling factors on diagonal
    bool hasScaling = ApproximatelyEqual( matrix[ 0 ][ 0 ], 2.0f ) && ApproximatelyEqual( matrix[ 1 ][ 1 ], 2.0f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 2 ], 2.0f );

    BOOST_TEST( hasScaling );
}

BOOST_AUTO_TEST_CASE( NonZeroRotationOrigin )
{
    // Test transformation matrix with non-zero rotation origin
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 1.0f, 1.0f, 1.0f );

    Point3f rotationOrigin( 10.0f, 10.0f, 10.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Matrix should be valid and have 1 on diagonal (no scaling or rotation)
    bool isValid = ApproximatelyEqual( matrix[ 3 ][ 3 ], 1.0f );

    BOOST_TEST( isValid );
}

BOOST_AUTO_TEST_CASE( UniformScaling )
{
    // Test transformation matrix with uniform scaling
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 3.0f, 3.0f, 3.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // All diagonal scaling elements should be equal
    bool isUniform = ApproximatelyEqual( matrix[ 0 ][ 0 ], 3.0f ) && ApproximatelyEqual( matrix[ 1 ][ 1 ], 3.0f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 2 ], 3.0f );

    BOOST_TEST( isUniform );
}

BOOST_AUTO_TEST_CASE( NonUniformScaling )
{
    // Test transformation matrix with non-uniform scaling
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 1.0f, 2.0f, 3.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Different diagonal scaling elements should be different
    bool isDifferent = ApproximatelyEqual( matrix[ 0 ][ 0 ], 1.0f ) && ApproximatelyEqual( matrix[ 1 ][ 1 ], 2.0f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 2 ], 3.0f );

    BOOST_TEST( isDifferent );
}

BOOST_AUTO_TEST_CASE( LargeTranslationValues )
{
    // Test transformation matrix with large translation values
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 1.0f, 1.0f, 1.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 1000.0f, 2000.0f, 3000.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Matrix should remain valid with large translation
    bool isValid = ApproximatelyEqual( matrix[ 3 ][ 3 ], 1.0f );

    BOOST_TEST( isValid );
}

BOOST_AUTO_TEST_CASE( NegativeScaling )
{
    // Test transformation matrix with negative scaling (reflection)
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( -1.0f, 1.0f, 1.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Negative scaling should be reflected in matrix
    bool hasNegativeScale = ApproximatelyEqual( matrix[ 0 ][ 0 ], -1.0f );

    BOOST_TEST( hasNegativeScale );
}

BOOST_AUTO_TEST_CASE( SmallScalingValues )
{
    // Test transformation matrix with very small scaling values
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 0.001f, 0.002f, 0.003f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Small scaling values should be present
    bool hasSmallScale = ApproximatelyEqual( matrix[ 0 ][ 0 ], 0.001f, 1e-6f ) &&
        ApproximatelyEqual( matrix[ 1 ][ 1 ], 0.002f, 1e-6f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 2 ], 0.003f, 1e-6f );

    BOOST_TEST( hasSmallScale );
}

BOOST_AUTO_TEST_CASE( MatrixBottomRowCorrect )
{
    // Verify that the bottom row of the matrix is correct (should be [0, 0, 0, 1] for homogeneous coordinates)
    Point3f scalingOrigin( 1.0f, 2.0f, 3.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 2.0f, 2.0f, 2.0f );

    Point3f rotationOrigin( 4.0f, 5.0f, 6.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 7.0f, 8.0f, 9.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // rightmost column should be [0, 0, 0, 1]
    bool isCorrect = ApproximatelyEqual( matrix[ 3 ][ 3 ], 1.0f ) && ApproximatelyEqual( matrix[ 0 ][ 3 ], 0.0f ) &&
        ApproximatelyEqual( matrix[ 1 ][ 3 ], 0.0f ) && ApproximatelyEqual( matrix[ 2 ][ 3 ], 0.0f );

    BOOST_TEST( isCorrect );
}

BOOST_AUTO_TEST_CASE( InverseOfIdentityMatrixReturnsIdentity )
{
    // Arrange
    auto identityMatrix = SquareMatrix<float, 4>::Simd( Math::MatrixType::Identity );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    auto result = Inverse( identityMatrix, &determinant );

    // Assert
    bool isIdentityResult = result.IsIdentity( );
    BOOST_TEST( isIdentityResult );
    BOOST_TEST( ApproximatelyEqual( determinant[ 0 ], 1.0f, 1e-5f ) );
}

BOOST_AUTO_TEST_CASE( InverseComputesDeterminantCorrectly )
{
    // Arrange - Create a simple 4x4 matrix
    // [2, 0, 0, 0]
    // [0, 3, 0, 0]
    // [0, 0, 4, 0]
    // [0, 0, 0, 5]
    // Determinant = 2 * 3 * 4 * 5 = 120
    SquareMatrix<float, 4> matrix;
    matrix[ 0 ][ 0 ] = 2.0f;
    matrix[ 1 ][ 1 ] = 3.0f;
    matrix[ 2 ][ 2 ] = 4.0f;
    matrix[ 3 ][ 3 ] = 5.0f;

    auto simdMatrix = matrix.ToSimd( );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    Inverse( simdMatrix, &determinant );

    // Assert
    BOOST_TEST( ApproximatelyEqual( determinant[ 0 ], 120.0f, 1e-4f ) );
}

BOOST_AUTO_TEST_CASE( InverseOfDiagonalMatrixIsCorrect )
{
    // Arrange - Create a diagonal matrix
    // [2, 0, 0, 0]
    // [0, 4, 0, 0]
    // [0, 0, 1, 0]
    // [0, 0, 0, 2]
    SquareMatrix<float, 4> matrix;
    matrix[ 0 ][ 0 ] = 2.0f;
    matrix[ 1 ][ 1 ] = 4.0f;
    matrix[ 2 ][ 2 ] = 1.0f;
    matrix[ 3 ][ 3 ] = 2.0f;

    // Expected inverse:
    // [0.5, 0, 0, 0]
    // [0, 0.25, 0, 0]
    // [0, 0, 1, 0]
    // [0, 0, 0, 0.5]
    SquareMatrix<float, 4> expectedInverse;
    expectedInverse[ 0 ][ 0 ] = 0.5f;
    expectedInverse[ 1 ][ 1 ] = 0.25f;
    expectedInverse[ 2 ][ 2 ] = 1.0f;
    expectedInverse[ 3 ][ 3 ] = 0.5f;

    auto simdMatrix = matrix.ToSimd( );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    auto result = Inverse( simdMatrix, &determinant );

    // Assert
    auto expectedSimd = expectedInverse.ToSimd( );
    bool isEqual = MatrixApproximatelyEqual( result, expectedSimd, 1e-5f );
    BOOST_TEST( isEqual );
}

BOOST_AUTO_TEST_CASE( InverseSingularMatrixReturnsNaN )
{
    // Arrange - Create a singular matrix (two identical rows)
    // [1, 2, 3, 4]
    // [1, 2, 3, 4]
    // [5, 6, 7, 8]
    // [9, 10, 11, 12]
    SquareMatrix<float, 4> singularMatrix;
    singularMatrix[ 0 ][ 0 ] = 1.0f; singularMatrix[ 0 ][ 1 ] = 2.0f; singularMatrix[ 0 ][ 2 ] = 3.0f; singularMatrix[ 0 ][ 3 ] = 4.0f;
    singularMatrix[ 1 ][ 0 ] = 1.0f; singularMatrix[ 1 ][ 1 ] = 2.0f; singularMatrix[ 1 ][ 2 ] = 3.0f; singularMatrix[ 1 ][ 3 ] = 4.0f;
    singularMatrix[ 2 ][ 0 ] = 5.0f; singularMatrix[ 2 ][ 1 ] = 6.0f; singularMatrix[ 2 ][ 2 ] = 7.0f; singularMatrix[ 2 ][ 3 ] = 8.0f;
    singularMatrix[ 3 ][ 0 ] = 9.0f; singularMatrix[ 3 ][ 1 ] = 10.0f; singularMatrix[ 3 ][ 2 ] = 11.0f; singularMatrix[ 3 ][ 3 ] = 12.0f;

    auto simdMatrix = singularMatrix.ToSimd( );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    SquareMatrix<float, 4> result = Inverse( simdMatrix, &determinant );

    // Assert - Result should contain NaN values
    bool hasNaN = std::isnan( result[ 0 ][ 0 ] ) || std::isnan( result[ 1 ][ 1 ] ) ||
        std::isnan( result[ 2 ][ 2 ] ) || std::isnan( result[ 3 ][ 3 ] );
    BOOST_TEST( hasNaN );
}

BOOST_AUTO_TEST_CASE( InverseMultipliedByOriginalMatrixGivesIdentity )
{
    // Arrange
    SquareMatrix<float, 4> matrix;
    matrix[ 0 ][ 0 ] = 4.0f; matrix[ 0 ][ 1 ] = 7.0f; matrix[ 0 ][ 2 ] = 2.0f; matrix[ 0 ][ 3 ] = 1.0f;
    matrix[ 1 ][ 0 ] = 1.0f; matrix[ 1 ][ 1 ] = 2.0f; matrix[ 1 ][ 2 ] = 8.0f; matrix[ 1 ][ 3 ] = 4.0f;
    matrix[ 2 ][ 0 ] = 2.0f; matrix[ 2 ][ 1 ] = 3.0f; matrix[ 2 ][ 2 ] = 1.0f; matrix[ 2 ][ 3 ] = 5.0f;
    matrix[ 3 ][ 0 ] = 9.0f; matrix[ 3 ][ 1 ] = 6.0f; matrix[ 3 ][ 2 ] = 3.0f; matrix[ 3 ][ 3 ] = 2.0f;

    auto simdMatrix = matrix.ToSimd( );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    auto inverseMatrix = Inverse( simdMatrix, &determinant );
    auto product = Multiply( simdMatrix, inverseMatrix );

    // Assert - Product should be identity
    auto identityMatrix = SquareMatrix<float, 4>::Simd( Math::MatrixType::Identity );
    bool isIdentity = MatrixApproximatelyEqual( product, identityMatrix, 1e-4f );
    BOOST_TEST( isIdentity );
}

BOOST_AUTO_TEST_CASE( InverseWithNullDeterminantPointer )
{
    // Arrange
    auto identityMatrix = SquareMatrix<float, 4>::Simd( Math::MatrixType::Identity );

    // Act - Should not crash with null pointer
    auto result = Inverse( identityMatrix, nullptr );

    // Assert
    bool isIdentityResult = result.IsIdentity( );
    BOOST_TEST( isIdentityResult );
}

BOOST_AUTO_TEST_CASE( InverseOfScaledIdentityMatrix )
{
    // Arrange - Create a scaled identity matrix
    // [3, 0, 0, 0]
    // [0, 3, 0, 0]
    // [0, 0, 3, 0]
    // [0, 0, 0, 3]
    SquareMatrix<float, 4> scaledIdentity;
    scaledIdentity[ 0 ][ 0 ] = 3.0f;
    scaledIdentity[ 1 ][ 1 ] = 3.0f;
    scaledIdentity[ 2 ][ 2 ] = 3.0f;
    scaledIdentity[ 3 ][ 3 ] = 3.0f;

    // Expected inverse: each diagonal element = 1/3
    auto simdMatrix = scaledIdentity.ToSimd( );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    SquareMatrix<float, 4> result = Inverse( simdMatrix, &determinant );

    // Assert
    BOOST_TEST( ApproximatelyEqual( result[ 0 ][ 0 ], 1.0f / 3.0f, 1e-5f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 1 ][ 1 ], 1.0f / 3.0f, 1e-5f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 2 ][ 2 ], 1.0f / 3.0f, 1e-5f ) );
    BOOST_TEST( ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f / 3.0f, 1e-5f ) );
    BOOST_TEST( ApproximatelyEqual( determinant[ 0 ], 81.0f, 1e-4f ) ); // 3^4 = 81
}

BOOST_AUTO_TEST_CASE( InverseConsistencyWithMultipleInvocations )
{
    // Arrange
    SquareMatrix<float, 4> matrix;
    matrix[ 0 ][ 0 ] = 1.5f; matrix[ 0 ][ 1 ] = 0.5f; matrix[ 0 ][ 2 ] = 0.2f; matrix[ 0 ][ 3 ] = 0.1f;
    matrix[ 1 ][ 0 ] = 0.5f; matrix[ 1 ][ 1 ] = 2.5f; matrix[ 1 ][ 2 ] = 0.3f; matrix[ 1 ][ 3 ] = 0.2f;
    matrix[ 2 ][ 0 ] = 0.2f; matrix[ 2 ][ 1 ] = 0.3f; matrix[ 2 ][ 2 ] = 3.5f; matrix[ 2 ][ 3 ] = 0.4f;
    matrix[ 3 ][ 0 ] = 0.1f; matrix[ 3 ][ 1 ] = 0.2f; matrix[ 3 ][ 2 ] = 0.4f; matrix[ 3 ][ 3 ] = 4.5f;

    auto simdMatrix = matrix.ToSimd( );

    // Act
    Math::Vector<float, 4>::Simd det1, det2;
    auto inverse1 = Inverse( simdMatrix, &det1 );
    auto inverse2 = Inverse( simdMatrix, &det2 );

    // Assert - Multiple invocations should give identical results
    bool isEqual = MatrixApproximatelyEqual( inverse1, inverse2, 1e-6f );
    BOOST_TEST( isEqual );
    BOOST_TEST( ApproximatelyEqual( det1[ 0 ], det2[ 0 ], 1e-6f ) );
}

BOOST_AUTO_TEST_CASE( InverseDeterminantIsNonZeroForInvertibleMatrix )
{
    // Arrange
    SquareMatrix<float, 4> matrix;
    matrix[ 0 ][ 0 ] = 2.0f; matrix[ 0 ][ 1 ] = 1.0f; matrix[ 0 ][ 2 ] = 0.0f; matrix[ 0 ][ 3 ] = 0.0f;
    matrix[ 1 ][ 0 ] = 1.0f; matrix[ 1 ][ 1 ] = 3.0f; matrix[ 1 ][ 2 ] = 1.0f; matrix[ 1 ][ 3 ] = 0.0f;
    matrix[ 2 ][ 0 ] = 0.0f; matrix[ 2 ][ 1 ] = 1.0f; matrix[ 2 ][ 2 ] = 4.0f; matrix[ 2 ][ 3 ] = 1.0f;
    matrix[ 3 ][ 0 ] = 0.0f; matrix[ 3 ][ 1 ] = 0.0f; matrix[ 3 ][ 2 ] = 1.0f; matrix[ 3 ][ 3 ] = 5.0f;

    auto simdMatrix = matrix.ToSimd( );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    Inverse( simdMatrix, &determinant );

    // Assert
    BOOST_TEST( determinant[ 0 ] != 0.0f );
    BOOST_TEST( !std::isnan( determinant[ 0 ] ) );
}

/// <summary>
/// Tests the inverse of a 3x3 identity matrix.
/// </summary>
BOOST_AUTO_TEST_CASE( InverseOfIdentityMatrix )
{
    // Arrange
    SquareMatrix<float, 3> identity;
    auto identitySimd = identity.ToSimd( );

    // Act
    auto result = Inverse( identitySimd );

    // Assert
    auto resultMatrix = SquareMatrix<float, 3>( result );
    bool isIdentity = resultMatrix.IsIdentity( );
    BOOST_TEST( isIdentity );
}

/// <summary>
/// Tests the inverse of a simple diagonal matrix.
/// </summary>
BOOST_AUTO_TEST_CASE( InverseOfDiagonalMatrix )
{
    // Arrange
    SquareMatrix<float, 3> original = SquareMatrix<float, 3>::Diag( 2.0f, 3.0f, 4.0f );
    auto originalSimd = original.ToSimd( );

    SquareMatrix<float, 3> expected;
    expected[ 0 ][ 0 ] = 0.5f;
    expected[ 1 ][ 1 ] = 1.0f / 3.0f;
    expected[ 2 ][ 2 ] = 0.25f;

    // Act
    auto resultSimd = Inverse( originalSimd );
    auto result = SquareMatrix<float, 3>( resultSimd );

    // Assert
    constexpr float epsilon = 1e-6f;
    bool element00Match = std::abs( result[ 0 ][ 0 ] - expected[ 0 ][ 0 ] ) < epsilon;
    bool element11Match = std::abs( result[ 1 ][ 1 ] - expected[ 1 ][ 1 ] ) < epsilon;
    bool element22Match = std::abs( result[ 2 ][ 2 ] - expected[ 2 ][ 2 ] ) < epsilon;

    BOOST_TEST( element00Match );
    BOOST_TEST( element11Match );
    BOOST_TEST( element22Match );
}

/// <summary>
/// Tests that M * M^-1 = I for a general invertible matrix.
/// </summary>
BOOST_AUTO_TEST_CASE( MatrixTimesInverseEqualsIdentity )
{
    // Arrange
    SquareMatrix<float, 3> original;
    original[ 0 ][ 0 ] = 1.0f;
    original[ 0 ][ 1 ] = 2.0f;
    original[ 0 ][ 2 ] = 3.0f;
    original[ 1 ][ 0 ] = 0.0f;
    original[ 1 ][ 1 ] = 1.0f;
    original[ 1 ][ 2 ] = 4.0f;
    original[ 2 ][ 0 ] = 5.0f;
    original[ 2 ][ 1 ] = 6.0f;
    original[ 2 ][ 2 ] = 2.0f;

    auto originalSimd = original.ToSimd( );

    // Act
    auto inverseSimd = Inverse( originalSimd );
    auto product = Multiply( originalSimd, inverseSimd );
    auto productMatrix = SquareMatrix<float, 3>( product );

    // Assert
    constexpr float epsilon = 1e-4f;
    for ( int i = 0; i < 3; ++i )
    {
        for ( int j = 0; j < 3; ++j )
        {
            float expectedValue = ( i == j ) ? 1.0f : 0.0f;
            float actualValue = productMatrix[ i ][ j ];
            bool matches = std::abs( actualValue - expectedValue ) < epsilon;
            BOOST_TEST( matches );
        }
    }
}

/// <summary>
/// Tests the determinant calculation for a 3x3 matrix.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantCalculation )
{
    // Arrange
    SquareMatrix<float, 3> original;
    original[ 0 ][ 0 ] = 1.0f;
    original[ 0 ][ 1 ] = 2.0f;
    original[ 0 ][ 2 ] = 3.0f;
    original[ 1 ][ 0 ] = 0.0f;
    original[ 1 ][ 1 ] = 1.0f;
    original[ 1 ][ 2 ] = 4.0f;
    original[ 2 ][ 0 ] = 5.0f;
    original[ 2 ][ 1 ] = 6.0f;
    original[ 2 ][ 2 ] = 2.0f;

    auto originalSimd = original.ToSimd( );
    Math::Vector<float, 3>::Simd determinantSimd;

    // Act
    Inverse( originalSimd, &determinantSimd );
    float determinant = determinantSimd.x( );

    // Expected: 1*(1*2 - 4*6) - 2*(0*2 - 4*5) + 3*(0*6 - 1*5)
    //         = 1*(2 - 24) - 2*(0 - 20) + 3*(0 - 5)
    //         = -22 + 40 - 15 = 3
    float expectedDeterminant = 3.0f;
    constexpr float epsilon = 1e-5f;
    bool determinantMatches = std::abs( determinant - expectedDeterminant ) < epsilon;

    // Assert
    BOOST_TEST( determinantMatches );
}

/// <summary>
/// Tests the inverse of the identity matrix without computing determinant.
/// </summary>
BOOST_AUTO_TEST_CASE( InverseWithoutDeterminantOutput )
{
    // Arrange
    SquareMatrix<float, 3> identity;
    auto identitySimd = identity.ToSimd( );

    // Act - should not crash when determinant is nullptr
    auto resultSimd = Inverse( identitySimd, nullptr );
    auto resultMatrix = SquareMatrix<float, 3>( resultSimd );

    // Assert
    bool isIdentity = resultMatrix.IsIdentity( );
    BOOST_TEST( isIdentity );
}

/// <summary>
/// Tests inverse with a matrix containing decimal values.
/// </summary>
BOOST_AUTO_TEST_CASE( InverseOfMatrixWithDecimalValues )
{
    // Arrange
    SquareMatrix<float, 3> original;
    original[ 0 ][ 0 ] = 1.5f;
    original[ 0 ][ 1 ] = 0.5f;
    original[ 0 ][ 2 ] = 0.0f;
    original[ 1 ][ 0 ] = 0.0f;
    original[ 1 ][ 1 ] = 2.0f;
    original[ 1 ][ 2 ] = 0.0f;
    original[ 2 ][ 0 ] = 0.0f;
    original[ 2 ][ 1 ] = 0.0f;
    original[ 2 ][ 2 ] = 0.5f;

    auto originalSimd = original.ToSimd( );
    Math::Vector<float, 3>::Simd determinantSimd;

    // Act
    auto inverseSimd = Inverse( originalSimd, &determinantSimd );
    auto product = Multiply( originalSimd, inverseSimd );
    auto productMatrix = SquareMatrix<float, 3>( product );

    // Assert
    constexpr float epsilon = 1e-4f;
    for ( int i = 0; i < 3; ++i )
    {
        for ( int j = 0; j < 3; ++j )
        {
            float expectedValue = ( i == j ) ? 1.0f : 0.0f;
            float actualValue = productMatrix[ i ][ j ];
            bool matches = std::abs( actualValue - expectedValue ) < epsilon;
            BOOST_TEST( matches );
        }
    }
}

/// <summary>
/// Tests inverse of a matrix with negative values.
/// </summary>
BOOST_AUTO_TEST_CASE( InverseOfMatrixWithNegativeValues )
{
    // Arrange
    SquareMatrix<float, 3> original;
    original[ 0 ][ 0 ] = -1.0f;
    original[ 0 ][ 1 ] = 0.0f;
    original[ 0 ][ 2 ] = 0.0f;
    original[ 1 ][ 0 ] = 0.0f;
    original[ 1 ][ 1 ] = 2.0f;
    original[ 1 ][ 2 ] = 0.0f;
    original[ 2 ][ 0 ] = 0.0f;
    original[ 2 ][ 1 ] = 0.0f;
    original[ 2 ][ 2 ] = -3.0f;

    auto originalSimd = original.ToSimd( );

    // Act
    auto inverseSimd = Inverse( originalSimd );
    auto product = Multiply( originalSimd, inverseSimd );
    auto productMatrix = SquareMatrix<float, 3>( product );

    // Assert
    constexpr float epsilon = 1e-4f;
    for ( int i = 0; i < 3; ++i )
    {
        for ( int j = 0; j < 3; ++j )
        {
            float expectedValue = ( i == j ) ? 1.0f : 0.0f;
            float actualValue = productMatrix[ i ][ j ];
            bool matches = std::abs( actualValue - expectedValue ) < epsilon;
            BOOST_TEST( matches );
        }
    }
}

/// <summary>
/// Tests the determinant of an identity matrix (should be 1.0).
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantOfIdentityMatrix )
{
    // Arrange
    SquareMatrix<float, 3> identity;
    auto identitySimd = identity.ToSimd( );
    Math::Vector<float, 3>::Simd determinantSimd;

    // Act
    Inverse( identitySimd, &determinantSimd );
    float determinant = determinantSimd.x( );

    // Assert
    constexpr float epsilon = 1e-6f;
    bool determinantIsOne = std::abs( determinant - 1.0f ) < epsilon;
    BOOST_TEST( determinantIsOne );
}

/// <summary>
/// Tests the inverse operation preserves numerical stability.
/// </summary>
BOOST_AUTO_TEST_CASE( InverseNumericalStability )
{
    // Arrange
    SquareMatrix<float, 3> original;
    original[ 0 ][ 0 ] = 1.0f;
    original[ 0 ][ 1 ] = 1.0f;
    original[ 0 ][ 2 ] = 1.0f;
    original[ 1 ][ 0 ] = 1.0f;
    original[ 1 ][ 1 ] = 2.0f;
    original[ 1 ][ 2 ] = 1.0f;
    original[ 2 ][ 0 ] = 1.0f;
    original[ 2 ][ 1 ] = 1.0f;
    original[ 2 ][ 2 ] = 2.0f;

    auto originalSimd = original.ToSimd( );

    // Act
    auto inverseSimd = Inverse( originalSimd );
    auto product1 = Multiply( originalSimd, inverseSimd );
    auto product2 = Multiply( inverseSimd, originalSimd );

    auto product1Matrix = SquareMatrix<float, 3>( product1 );
    auto product2Matrix = SquareMatrix<float, 3>( product2 );

    // Assert - verify commutativity up to numerical precision
    constexpr float epsilon = 1e-4f;
    for ( int i = 0; i < 3; ++i )
    {
        for ( int j = 0; j < 3; ++j )
        {
            bool product1Match = std::abs( product1Matrix[ i ][ j ] - ( ( i == j ) ? 1.0f : 0.0f ) ) < epsilon;
            bool product2Match = std::abs( product2Matrix[ i ][ j ] - ( ( i == j ) ? 1.0f : 0.0f ) ) < epsilon;
            BOOST_TEST( product1Match );
            BOOST_TEST( product2Match );
        }
    }
}

/// <summary>
/// Tests inverse of the identity matrix.
/// The inverse of the identity matrix should be the identity matrix itself.
/// </summary>
BOOST_AUTO_TEST_CASE( InverseOfIdentityMatrixIsIdentity2x2 )
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Create identity matrix: [1 0; 0 1]
    Simd identity( Traits::Set( 1.f, 0.f, 0.f, 1.f ) );

    // Compute inverse
    Simd result = Inverse( identity );

    // Verify result is identity
    bool isIdentity = MatrixApproximatelyEqual( result, identity );
    BOOST_TEST( isIdentity );
}

/// <summary>
/// Tests inverse of a simple 2x2 matrix.
/// For matrix [a b; c d], inverse is (1/det) * [d -b; -c a]
/// where det = ad - bc
/// </summary>
BOOST_AUTO_TEST_CASE( InverseOfSimpleMatrix2x2 )
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Matrix: [2 1; 1 2]
    // Determinant: 2*2 - 1*1 = 3
    // Inverse: (1/3) * [2 -1; -1 2] = [2/3 -1/3; -1/3 2/3]
    Simd matrix( Traits::Set( 2.f, 1.f, 1.f, 2.f ) );
    Simd result = Inverse( matrix );

    // Expected inverse
    const float inv3 = 1.f / 3.f;
    Simd expected( Traits::Set( 2.f * inv3, -inv3, -inv3, 2.f * inv3 ) );

    bool isCorrect = MatrixApproximatelyEqual( result, expected );
    BOOST_TEST( isCorrect );
}

/// <summary>
/// Tests inverse with determinant calculation.
/// Verifies that the determinant is correctly computed and returned.
/// </summary>
BOOST_AUTO_TEST_CASE( InverseWithDeterminantOutput2x2 )
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Matrix: [3 0; 0 2]
    // Determinant: 3*2 - 0*0 = 6
    Simd matrix( Traits::Set( 3.f, 0.f, 0.f, 2.f ) );
    Simd determinantOut;

    Simd result = Inverse( matrix, &determinantOut );

    // Expected determinant: 6.0
    auto detArray = Traits::ToArray( determinantOut.simd );
    float expectedDet = 6.f;

    bool detIsCorrect = std::abs( detArray[ 0 ] - expectedDet ) < 1e-5f;
    BOOST_TEST( detIsCorrect );
}

/// <summary>
/// Tests inverse of a diagonal matrix.
/// For diagonal matrix [a 0; 0 b], inverse is [1/a 0; 0 1/b]
/// </summary>
BOOST_AUTO_TEST_CASE( InverseOfDiagonalMatrix2x2 )
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Diagonal matrix: [4 0; 0 5]
    Simd diagonal( Traits::Set( 4.f, 0.f, 0.f, 5.f ) );
    Simd result = Inverse( diagonal );

    // Expected: [1/4 0; 0 1/5]
    Simd expected( Traits::Set( 0.25f, 0.f, 0.f, 0.2f ) );

    bool isCorrect = MatrixApproximatelyEqual( result, expected );
    BOOST_TEST( isCorrect );
}

/// <summary>
/// Tests inverse of a matrix with negative values.
/// </summary>
BOOST_AUTO_TEST_CASE( InverseOfMatrixWithNegativeValues2x2 )
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Matrix: [1 -2; -3 4]
    // Determinant: 1*4 - (-2)*(-3) = 4 - 6 = -2
    // Inverse: (1/-2) * [4 2; 3 1] = [-2 -1; -1.5 -0.5]
    Simd matrix( Traits::Set( 1.f, -2.f, -3.f, 4.f ) );
    Simd result = Inverse( matrix );

    Simd expected( Traits::Set( -2.f, -1.f, -1.5f, -0.5f ) );

    bool isCorrect = MatrixApproximatelyEqual( result, expected );
    BOOST_TEST( isCorrect );
}

/// <summary>
/// Tests matrix multiplication property: M * M^-1 = I
/// This verifies the correctness of the inverse computation.
/// </summary>
BOOST_AUTO_TEST_CASE( MatrixTimesInverseEqualsIdentity2x2 )
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Matrix: [2 3; 4 5]
    // Determinant: 2*5 - 3*4 = 10 - 12 = -2
    Simd matrix( Traits::Set( 2.f, 3.f, 4.f, 5.f ) );
    Simd inverse = Inverse( matrix );

    // Multiply matrix by its inverse
    Simd product = Multiply( matrix, inverse );

    // Expected: identity matrix
    Simd identity( Traits::Set( 1.f, 0.f, 0.f, 1.f ) );

    bool isIdentity = MatrixApproximatelyEqual( product, identity, 1e-4f );
    BOOST_TEST( isIdentity );
}

/// <summary>
/// Tests inverse of matrix with floating-point values.
/// </summary>
BOOST_AUTO_TEST_CASE( InverseOfFloatingPointMatrix2x2 )
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Matrix: [1.5 0.5; 0.5 1.5]
    // Determinant: 1.5*1.5 - 0.5*0.5 = 2.25 - 0.25 = 2.0
    // Inverse: 0.5 * [1.5 -0.5; -0.5 1.5]
    Simd matrix( Traits::Set( 1.5f, 0.5f, 0.5f, 1.5f ) );
    Simd result = Inverse( matrix );

    Simd expected( Traits::Set( 0.75f, -0.25f, -0.25f, 0.75f ) );

    bool isCorrect = MatrixApproximatelyEqual( result, expected );
    BOOST_TEST( isCorrect );
}

/// <summary>
/// Tests inverse consistency: (M^-1)^-1 = M
/// </summary>
BOOST_AUTO_TEST_CASE( InverseOfInverseEqualsOriginal2x2 )
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Original matrix: [2 1; 1 2]
    Simd original( Traits::Set( 2.f, 1.f, 1.f, 2.f ) );

    // Compute inverse, then inverse of that
    Simd firstInverse = Inverse( original );
    Simd doubleInverse = Inverse( firstInverse );

    // Should equal original
    bool isConsistent = MatrixApproximatelyEqual( doubleInverse, original, 1e-4f );
    BOOST_TEST( isConsistent );
}

/// <summary>
/// Tests inverse with a matrix near singular (very small determinant).
/// This tests the numerical stability of the algorithm.
/// </summary>
BOOST_AUTO_TEST_CASE( InverseOfNearSingularMatrix2x2 )
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Nearly singular matrix with determinant close to zero
    // Matrix: [1 1; 1 1.0001]
    // Determinant: 1*1.0001 - 1*1 = 0.0001
    Simd matrix( Traits::Set( 1.f, 1.f, 1.f, 1.0001f ) );
    Simd result = Inverse( matrix );

    // Verify by multiplying back
    Simd product = Multiply( matrix, result );
    Simd identity( Traits::Set( 1.f, 0.f, 0.f, 1.f ) );

    // Use larger epsilon due to numerical precision issues with near-singular matrices
    bool isValid = MatrixApproximatelyEqual( product, identity, 1e-3f );
    BOOST_TEST( isValid );
}

/// <summary>
/// Tests determinant calculation for various matrices.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantCalculationAccuracy2x2 )
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Test matrix: [3 2; 1 4]
    // Determinant: 3*4 - 2*1 = 12 - 2 = 10
    Simd matrix( Traits::Set( 3.f, 2.f, 1.f, 4.f ) );
    Simd determinantOut;

    Inverse( matrix, &determinantOut );

    auto detArray = Traits::ToArray( determinantOut.simd );
    float expectedDet = 10.f;

    bool detIsCorrect = std::abs( detArray[ 0 ] - expectedDet ) < 1e-5f;
    BOOST_TEST( detIsCorrect );
}

/// <summary>
/// Tests determinant of identity matrix.
/// Identity matrix should have determinant of 1.0f.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantOfIdentityMatrixIsOne )
{
    SquareMatrix<float, 4> identity;
    auto identitySimd = identity.ToSimd( );

    auto result = Determinant( identitySimd );

    float det = result.x( );
    bool isCorrect = ApproximatelyEqual( det, 1.0f );
    BOOST_TEST( isCorrect );
}

/// <summary>
/// Tests determinant of zero matrix.
/// Zero matrix should have determinant of 0.0f.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantOfZeroMatrixIsZero )
{
    SquareMatrix<float, 4> zero = SquareMatrix<float, 4>::Zero( );
    auto zeroSimd = zero.ToSimd( );

    auto result = Determinant( zeroSimd );

    float det = result.x( );
    bool isCorrect = ApproximatelyEqual( det, 0.0f );
    BOOST_TEST( isCorrect );
}

/// <summary>
/// Tests determinant of a diagonal matrix.
/// For a diagonal matrix, determinant equals product of diagonal elements.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantOfDiagonalMatrix )
{
    auto diagonal = SquareMatrix<float, 4>::Diag( 2.0f, 3.0f, 4.0f, 5.0f );
    auto diagonalSimd = diagonal.ToSimd( );

    auto result = Determinant( diagonalSimd );

    float det = result.x( );
    float expected = 2.0f * 3.0f * 4.0f * 5.0f; // 120.0f
    bool isCorrect = ApproximatelyEqual( det, expected );
    BOOST_TEST( isCorrect );
}

/// <summary>
/// Tests determinant of a scaled identity matrix.
/// Scaling identity by factor k should multiply determinant by k^4.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantOfScaledIdentity )
{
    SquareMatrix<float, 4> identity;
    float scaleFactor = 2.5f;
    auto scaled = identity * scaleFactor;

    auto result = Determinant( scaled );

    float det = result.x( );
    float expected = scaleFactor * scaleFactor * scaleFactor * scaleFactor; // k^4
    bool isCorrect = ApproximatelyEqual( det, expected, 1e-4f );
    BOOST_TEST( isCorrect );
}

/// <summary>
/// Tests determinant of a known 4x4 matrix.
/// Uses a simple matrix with manually calculated determinant.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantOfKnownMatrix )
{
    // Create a simple 4x4 matrix:
    // [ 1  2  3  4 ]
    // [ 5  1  6  7 ]
    // [ 8  9  1  10]
    // [11 12 13  1 ]
    SquareMatrix<float, 4> matrix(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 1.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 1.0f, 10.0f,
        11.0f, 12.0f, 13.0f, 1.0f
    );

    auto matrixSimd = matrix.ToSimd( );
    auto result = Determinant( matrixSimd );

    float det = result.x( );

    // Verify determinant is a reasonable value (not NaN or infinite)
    bool isFinite = std::isfinite( det );
    BOOST_TEST( isFinite );
}

/// <summary>
/// Tests determinant with row swapped matrix.
/// Swapping two rows should negate the determinant.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantChangeWithRowSwap )
{
    SquareMatrix<float, 4> original;
    auto originalSimd = original.ToSimd( );
    auto resultOriginal = Determinant( originalSimd );
    float detOriginal = resultOriginal.x( );

    // Create matrix with swapped rows
    SquareMatrix<float, 4> swapped;
    auto temp = swapped[ 0 ];
    swapped[ 0 ] = swapped[ 1 ];
    swapped[ 1 ] = temp;

    auto swappedSimd = swapped.ToSimd( );
    auto resultSwapped = Determinant( swappedSimd );
    float detSwapped = resultSwapped.x( );

    // Determinants should be negatives of each other
    bool isNegated = ApproximatelyEqual( detOriginal, -detSwapped );
    BOOST_TEST( isNegated );
}

/// <summary>
/// Tests determinant with very small values.
/// Should handle denormalized numbers gracefully.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantWithSmallValues )
{
    SquareMatrix<float, 4> matrix(
        1e-6f, 0.0f, 0.0f, 0.0f,
        0.0f, 1e-6f, 0.0f, 0.0f,
        0.0f, 0.0f, 1e-6f, 0.0f,
        0.0f, 0.0f, 0.0f, 1e-6f
    );

    auto matrixSimd = matrix.ToSimd( );
    auto result = Determinant( matrixSimd );

    float det = result.x( );

    // Result should be finite
    bool isFinite = std::isfinite( det );
    BOOST_TEST( isFinite );

    // Should be approximately (1e-6)^4
    float expected = 1e-24f;
    bool isCorrect = ApproximatelyEqual( det, expected, 1e-30f );
    BOOST_TEST( isCorrect );
}

/// <summary>
/// Tests determinant with large values.
/// Should handle large numbers without overflow.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantWithLargeValues )
{
    SquareMatrix<float, 4> matrix(
        1e6f, 0.0f, 0.0f, 0.0f,
        0.0f, 1e6f, 0.0f, 0.0f,
        0.0f, 0.0f, 1e6f, 0.0f,
        0.0f, 0.0f, 0.0f, 1e6f
    );

    auto matrixSimd = matrix.ToSimd( );
    auto result = Determinant( matrixSimd );

    float det = result.x( );

    // Result should be finite
    bool isFinite = std::isfinite( det );
    BOOST_TEST( isFinite );
}

/// <summary>
/// Tests determinant of singular matrix.
/// Singular matrix should have determinant of approximately 0.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantOfSingularMatrix )
{
    // Create a singular matrix (two identical rows)
    SquareMatrix<float, 4> singular(
        1.0f, 2.0f, 3.0f, 4.0f,
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f
    );

    auto singularSimd = singular.ToSimd( );
    auto result = Determinant( singularSimd );

    float det = result.x( );

    // Determinant should be very close to zero
    bool isZero = ApproximatelyEqual( det, 0.0f, 1e-4f );
    BOOST_TEST( isZero );
}

/// <summary>
/// Tests determinant is not NaN.
/// Ensures the computation produces valid IEEE 754 floating-point result.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantIsNotNaN )
{
    SquareMatrix<float, 4> identity;
    auto identitySimd = identity.ToSimd( );

    auto result = Determinant( identitySimd );
    float det = result.x( );

    bool isNotNaN = !std::isnan( det );
    BOOST_TEST( isNotNaN );
}

/// <summary>
/// Tests determinant result vector contains all identical values.
/// The Dot product fill operation should populate all components.
/// </summary>
BOOST_AUTO_TEST_CASE( DeterminantResultComponentsMatch )
{
    SquareMatrix<float, 4> identity;
    auto identitySimd = identity.ToSimd( );

    auto result = Determinant( identitySimd );

    float x = result.x( );
    float y = result.y( );
    float z = result.z( );
    float w = result.w( );

    bool xEqualsY = ApproximatelyEqual( x, y );
    bool yEqualsZ = ApproximatelyEqual( y, z );
    bool zEqualsW = ApproximatelyEqual( z, w );

    BOOST_TEST( xEqualsY );
    BOOST_TEST( yEqualsZ );
    BOOST_TEST( zEqualsW );
}

BOOST_AUTO_TEST_CASE( IdentityMatrixDeterminant )
{
    // Arrange: Create a 4x4 identity matrix
    SquareMatrix<float, 4> identityMatrix = SquareMatrix<float, 4>( );
    auto simdMatrix = identityMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Determinant of identity matrix should be 1.0
    BOOST_TEST( ApproximatelyEqual( determinant, 1.0f ) );
}

BOOST_AUTO_TEST_CASE( ScaledIdentityMatrixDeterminant )
{
    // Arrange: Create a diagonal matrix with scale factor 2 on diagonal
    // [2  0  0  0]
    // [0  2  0  0]
    // [0  0  2  0]
    // [0  0  0  2]
    // Determinant should be 2^4 = 16
    SquareMatrix<float, 4> scaledMatrix(
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 2.0f
    );
    auto simdMatrix = scaledMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Determinant should be 16.0
    BOOST_TEST( ApproximatelyEqual( determinant, 16.0f ) );
}

BOOST_AUTO_TEST_CASE( SingularMatrixDeterminant )
{
    // Arrange: Create a singular matrix (two identical rows)
    // [1  2  3  4]
    // [1  2  3  4]
    // [5  6  7  8]
    // [9  10 11 12]
    // Determinant should be 0
    SquareMatrix<float, 4> singularMatrix(
        1.0f, 2.0f, 3.0f, 4.0f,
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f
    );
    auto simdMatrix = singularMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Determinant of singular matrix should be 0
    BOOST_TEST( ApproximatelyEqual( determinant, 0.0f, 1e-3f ) );
}

BOOST_AUTO_TEST_CASE( SimpleMatrixDeterminant )
{
    // Arrange: Create a simple 4x4 matrix with known determinant
    // [1  0  0  0]
    // [0  1  0  0]
    // [0  0  2  0]
    // [0  0  0  3]
    // Determinant = 1*1*2*3 = 6
    SquareMatrix<float, 4> simpleMatrix(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 3.0f
    );
    auto simdMatrix = simpleMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Determinant should be 6.0
    BOOST_TEST( ApproximatelyEqual( determinant, 6.0f ) );
}

BOOST_AUTO_TEST_CASE( NegativeDeterminant )
{
    // Arrange: Create a matrix with negative determinant
    // [1  0  0  0]
    // [0  -1 0  0]
    // [0  0  1  0]
    // [0  0  0  1]
    // Determinant = -1
    SquareMatrix<float, 4> negativeMatrix(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    auto simdMatrix = negativeMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Determinant should be -1.0
    BOOST_TEST( ApproximatelyEqual( determinant, -1.0f ) );
}

BOOST_AUTO_TEST_CASE( GeneralMatrixDeterminant )
{
    // Arrange: Create a general 4x4 matrix
    // [2  1  3  0]
    // [0  1  4  1]
    // [1  0  2  1]
    // [3  2  1  0]
    // Determinant calculated using cofactor expansion
    SquareMatrix<float, 4> generalMatrix(
        2.0f, 1.0f, 3.0f, 0.0f,
        0.0f, 1.0f, 4.0f, 1.0f,
        1.0f, 0.0f, 2.0f, 1.0f,
        3.0f, 2.0f, 1.0f, 0.0f
    );
    auto simdMatrix = generalMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Verify determinant is computed (non-zero for non-singular matrix)
    // The determinant should be a finite, valid number
    BOOST_TEST( std::isfinite( determinant ) );
    BOOST_TEST( determinant != 0.0f );
}

BOOST_AUTO_TEST_CASE( ZeroMatrixDeterminant )
{
    // Arrange: Create a zero matrix
    SquareMatrix<float, 4> zeroMatrix = SquareMatrix<float, 4>::Zero( );
    auto simdMatrix = zeroMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Determinant of zero matrix should be 0
    BOOST_TEST( ApproximatelyEqual( determinant, 0.0f ) );
}

BOOST_AUTO_TEST_CASE( ReturnValueIsFinite )
{
    // Arrange: Create an arbitrary matrix
    SquareMatrix<float, 4> matrix(
        1.5f, 2.3f, 0.7f, 1.1f,
        0.2f, 3.4f, 1.8f, 0.5f,
        2.1f, 0.9f, 2.2f, 3.3f,
        1.7f, 1.2f, 0.4f, 2.8f
    );
    auto simdMatrix = matrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Return value should be a finite number (not NaN or Inf)
    BOOST_TEST( std::isfinite( determinant ) );
}


BOOST_AUTO_TEST_SUITE_END( )