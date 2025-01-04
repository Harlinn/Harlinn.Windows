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

    inline bool Equal( const Math::SquareMatrix<float, 3>& m1, const Math::SquareMatrix<float, 3>& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            for ( size_t j = 0; j < 3; j++ )
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

    inline bool Equal( const pbrt::SquareMatrix<3>& m1, const pbrt::SquareMatrix<3>& m2, float epsilon = 0.0001f )
    {
        for ( int i = 0; i < 3; i++ )
        {
            for ( int j = 0; j < 3; j++ )
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

BOOST_FIXTURE_TEST_SUITE( SquareMatrix3FloatTests, LocalFixture )


// --run_test=SquareMatrix3FloatTests/AddTest1
BOOST_AUTO_TEST_CASE( AddTest1 )
{
    using namespace Harlinn::Common::Core::Math;
    SquareMatrix<float, 3> matrix1( 1.f, 2.f, 3.f, 
                                    4.f, 5.f, 6.f,
                                    7.f, 8.f, 9.f);
    SquareMatrix<float, 3> matrix2( 2.f, 3.f, 4.f,
                                    5.f, 6.f, 7.f,
                                    8.f, 9.f, 10.f );

    SquareMatrix<float, 3> expected( 3.f, 5.f, 7.f,
                                    9.f, 11.f, 13.f,
                                    15.f, 17.f, 19.f );

    SquareMatrix<float, 3> result = matrix1 + matrix2;

    bool equal = Equal( result, expected );

    BOOST_CHECK( equal );
}


// --run_test=SquareMatrix3FloatTests/SubTest1
BOOST_AUTO_TEST_CASE( SubTest1 )
{
    using namespace Harlinn::Common::Core::Math;
    SquareMatrix<float, 3> matrix1( 2.f, 3.f, 4.f,
                                    5.f, 6.f, 7.f,
                                    8.f, 9.f, 10.f );
    SquareMatrix<float, 3> matrix2( 1.f, 2.f, 3.f,
                                    4.f, 5.f, 6.f,
                                    7.f, 8.f, 9.f );


    SquareMatrix<float, 3> expected( 1.f, 1.f, 1.f,
                                    1.f, 1.f, 1.f,
                                    1.f, 1.f, 1.f );

    SquareMatrix<float, 3> result = matrix1 - matrix2;

    bool equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=SquareMatrix3FloatTests/MulTest1
BOOST_AUTO_TEST_CASE( MulTest1 )
{
    using namespace Harlinn::Common::Core::Math;
    SquareMatrix<float, 3> matrix1( 1.f, 2.f, 3.f,
                                    4.f, 5.f, 6.f,
                                    7.f, 8.f, 9.f );
    SquareMatrix<float, 3> matrix2( 2.f, 3.f, 4.f,
                                    5.f, 6.f, 7.f,
                                    8.f, 9.f, 10.f );


    SquareMatrix<float, 3> expected( 36.f, 42.f, 48.f,
                                    81.f, 96.f, 111.f,
                                    126.f, 150.f, 174.f );

    SquareMatrix<float, 3> result = matrix1 * matrix2;

    bool equal = Equal( result, expected );

    BOOST_CHECK( equal );
}


// --run_test=SquareMatrix3FloatTests/TransposeTest1
BOOST_AUTO_TEST_CASE( TransposeTest1 )
{
    using namespace Harlinn::Common::Core::Math;
    SquareMatrix<float, 3> matrix1( 1.f, 2.f, 3.f,
                                    4.f, 5.f, 6.f,
                                    7.f, 8.f, 9.f );

    SquareMatrix<float, 3> expected( 1.f, 4.f, 7.f,
                                    2.f, 5.f, 8.f,
                                    3.f, 6.f, 9.f );

    SquareMatrix<float, 3> result = Transpose( matrix1 );

    bool equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=SquareMatrix3FloatTests/DeterminantTest1
BOOST_AUTO_TEST_CASE( DeterminantTest1 )
{
    using namespace Harlinn::Common::Core::Math;
    SquareMatrix<float, 3> matrix1( 3.f, 2.f, 3.f,
                            4.f, 2.f, 4.f,
                            8.f, 2.f, 2.f );

    Math::Vector<float, 3> result = Determinant( matrix1 );

    bool equal = result.x == 12.f;

    BOOST_CHECK( equal );
}



// --run_test=SquareMatrix3FloatTests/InverseTest1
BOOST_AUTO_TEST_CASE( InverseTest1 )
{
    using namespace Harlinn::Common::Core::Math;
    SquareMatrix<float, 3> matrix( 3.f, 2.f, 3.f,
                                4.f, 2.f, 4.f,
                                8.f, 2.f, 2.f );

    SquareMatrix<float, 3> expected( -0.333333f, 0.166667f, 0.166667f,
                                    2.0f, -1.5f, 0.0f,
                                    -0.666667f, 0.833333f, -0.166667f );

    SquareMatrix<float, 3> inverse = Math::Inverse( matrix );

    bool equal = Equal( inverse, expected );

    BOOST_CHECK( equal );
}


BOOST_AUTO_TEST_SUITE_END( )