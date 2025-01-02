/*
   Copyright 2024 Espen Harlinn

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

using namespace Harlinn::Common::Core;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
    inline bool Equal( const Math::SquareMatrix<float, 4>& m1, const Math::SquareMatrix<float, 4>& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            for ( size_t j = 0; j < 4; j++ )
            {
                auto v1 = m1[ i ][ j ];
                float v2 = m2[ i ][ j ];
                auto delta = v1 - v2;
                if ( std::abs( delta ) > epsilon )
                {
                    return false;
                }
            }
        }
        return true;
    }

    inline bool Equal( const pbrt::SquareMatrix<4>& m1, const pbrt::SquareMatrix<4>& m2, float epsilon = 0.0001f )
    {
        for ( int i = 0; i < 4; i++ )
        {
            for ( int j = 0; j < 4; j++ )
            {
                auto v1 = m1[ i ][ j ];
                float v2 = m2[ i ][ j ];
                auto delta = v1 - v2;
                if ( std::abs( delta ) > epsilon )
                {
                    return false;
                }
            }
        }
        return true;
    }

}

BOOST_FIXTURE_TEST_SUITE( SquareMatrix4FloatTests, LocalFixture )

// --run_test=SquareMatrix4FloatTests/InverseTest1
BOOST_AUTO_TEST_CASE( InverseTest1 )
{
    using namespace Harlinn::Common::Core::Math;
    SquareMatrix<float, 4> matrix( 0.285714f,  0.857143f, -0.428571f, 0.0f,
                                        -0.857143f, 0.428571f, 0.285714f, 0.0f,
                                        0.428571f, 0.285714f, 0.857143f, 0.0f,
                                        1.0f, 2.0f, 3.0f, 1.0f );

    SquareMatrix<float, 4> expected( 0.285714f, -0.857143f, 0.428571f, 0.0f,
                                        0.857143f, 0.428571f, 0.285714f, 0.0f,
                                        -0.428571f, 0.285714f, 0.857143f, 0.0f,
                                        -0.714286f, -0.857143f, -3.57143f, 1.0f );

    SquareMatrix<float, 4> inverse = Math::Inverse( matrix );

    bool equal = Equal( inverse, expected );

    BOOST_CHECK( equal );
}

// --run_test=SquareMatrix4FloatTests/PbrtInverseTest1
BOOST_AUTO_TEST_CASE( PbrtInverseTest1 )
{
    pbrt::SquareMatrix<4> matrix( 0.285714f, 0.857143f, -0.428571f, 0.0f,
        -0.857143f, 0.428571f, 0.285714f, 0.0f,
        0.428571f, 0.285714f, 0.857143f, 0.0f,
        1.0f, 2.0f, 3.0f, 1.0f );

    pbrt::SquareMatrix<4> expected( 0.285714f, -0.857143f, 0.428571f, 0.0f,
        0.857143f, 0.428571f, 0.285714f, 0.0f,
        -0.428571f, 0.285714f, 0.857143f, 0.0f,
        -0.714286f, -0.857143f, -3.57143f, 1.0f );

    auto inverse = pbrt::Inverse( matrix );

    BOOST_CHECK( inverse.has_value( ) );

    pbrt::SquareMatrix<4> inverseMatrix = inverse.value( );

    bool equal = Equal( inverseMatrix, expected );

    BOOST_CHECK( equal );
}


// --run_test=SquareMatrix4FloatTests/DeterminantTest1
BOOST_AUTO_TEST_CASE( DeterminantTest1 )
{
    using namespace Harlinn::Common::Core::Math;
    SquareMatrix<float, 4> matrix( 0.285714f, 0.857143f, -0.428571f, 0.0f,
        -0.857143f, 0.428571f, 0.285714f, 0.0f,
        0.428571f, 0.285714f, 0.857143f, 0.0f,
        1.0f, 2.0f, 3.0f, 1.0f );

    auto expected = 1.f;

    auto determinant = Math::ScalarDeterminant( matrix );

    BOOST_CHECK_CLOSE( determinant, expected, 0.01f );
}

// --run_test=SquareMatrix4FloatTests/DeterminantTest2
BOOST_AUTO_TEST_CASE( DeterminantTest2 )
{
    using namespace Harlinn::Common::Core::Math;
    using namespace DirectX;
    XMFLOAT4X4 matrix( 0.285714f, 0.857143f, -0.428571f, 0.0f,
        -0.857143f, 0.428571f, 0.285714f, 0.0f,
        0.428571f, 0.285714f, 0.857143f, 0.0f,
        1.0f, 2.0f, 3.0f, 1.0f );

    auto expected = 1.f;
    auto loaded = XMLoadFloat4x4( &matrix );
    auto determinantVector = XMMatrixDeterminant( loaded );
    auto determinant = _mm_cvtss_f32( determinantVector );
    

    BOOST_CHECK_CLOSE( determinant, expected, 0.01f );
}


BOOST_AUTO_TEST_SUITE_END( )