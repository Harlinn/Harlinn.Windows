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





BOOST_AUTO_TEST_SUITE_END( )