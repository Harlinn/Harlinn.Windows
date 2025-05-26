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

#include <HCCMath.h>


using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Math;
namespace OpenLibM = Harlinn::Common::Core::Math::Internal::OpenLibM;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( ConstexprMathTests, LocalFixture )

// --run_test=ConstexprMathTests/ConstexprMathTest1
BOOST_AUTO_TEST_CASE( ConstexprMathTest1 )
{
    constexpr double absResult = Abs( -1.0 );
    BOOST_CHECK( absResult == 1.0 );
    constexpr double absResult2 = Math::Internal::OpenLibM::fabs( -1.0 );
    BOOST_CHECK( absResult2 == 1.0 );
}

// --run_test=ConstexprMathTests/FloatConstantsTest1
BOOST_AUTO_TEST_CASE( FloatConstantsTest1 )
{
    using C = Constants<float>;

    // Verify basic constexpr float value classification properties.

    constexpr auto falseExpected1 = IsSameValue( C::Infinity, C::NegativeInfinity );
    BOOST_CHECK( falseExpected1 == false );
    constexpr auto falseExpected2 = IsSameValue( C::NaN, C::NegativeNaN );
    BOOST_CHECK( falseExpected2 == false );

    constexpr auto trueExpected1 = IsNaN( C::NaN );
    BOOST_CHECK( trueExpected1 );

    constexpr auto trueExpected2 = IsNaN( C::NegativeNaN );
    BOOST_CHECK( trueExpected2 );

    constexpr auto trueExpected3 = IsInf( C::Infinity );
    BOOST_CHECK( trueExpected3 );

    constexpr auto trueExpected4 = IsInf( C::NegativeInfinity );
    BOOST_CHECK( trueExpected4 );

    constexpr auto falseExpected3 = IsNaN( C::Max );
    BOOST_CHECK( falseExpected3 == false );

    constexpr auto falseExpected4 = IsNaN( C::Min );
    BOOST_CHECK( falseExpected4 == false );

    constexpr auto falseExpected5 = IsNaN( C::Lowest );
    BOOST_CHECK( falseExpected5 == false );

    constexpr auto falseExpected6 = IsInf( C::Max );
    BOOST_CHECK( falseExpected6 == false );

    constexpr auto falseExpected7 = IsInf( C::Min );
    BOOST_CHECK( falseExpected7 == false );

    constexpr auto falseExpected8 = IsInf( C::Lowest );
    BOOST_CHECK( falseExpected8 == false );


}

// --run_test=ConstexprMathTests/DoubleConstantsTest1
BOOST_AUTO_TEST_CASE( DoubleConstantsTest1 )
{
    using C = Constants<double>;

    // Verify basic constexpr double value classification properties.

    constexpr auto falseExpected1 = IsSameValue( C::Infinity, C::NegativeInfinity );
    BOOST_CHECK( falseExpected1 == false );
    constexpr auto falseExpected2 = IsSameValue( C::NaN, C::NegativeNaN );
    BOOST_CHECK( falseExpected2 == false );

    constexpr auto trueExpected1 = IsNaN( C::NaN );
    BOOST_CHECK( trueExpected1 );

    constexpr auto trueExpected2 = IsNaN( C::NegativeNaN );
    BOOST_CHECK( trueExpected2 );

    constexpr auto trueExpected3 = IsInf( C::Infinity );
    BOOST_CHECK( trueExpected3 );

    constexpr auto trueExpected4 = IsInf( C::NegativeInfinity );
    BOOST_CHECK( trueExpected4 );

    constexpr auto falseExpected3 = IsNaN( C::Max );
    BOOST_CHECK( falseExpected3 == false );

    constexpr auto falseExpected4 = IsNaN( C::Min );
    BOOST_CHECK( falseExpected4 == false );

    constexpr auto falseExpected5 = IsNaN( C::Lowest );
    BOOST_CHECK( falseExpected5 == false );

    constexpr auto falseExpected6 = IsInf( C::Max );
    BOOST_CHECK( falseExpected6 == false );

    constexpr auto falseExpected7 = IsInf( C::Min );
    BOOST_CHECK( falseExpected7 == false );

    constexpr auto falseExpected8 = IsInf( C::Lowest );
    BOOST_CHECK( falseExpected8 == false );

}



// --run_test=ConstexprMathTests/boolSignumTest1
BOOST_AUTO_TEST_CASE( boolSignumTest1 )
{
    constexpr auto falseBoolVal = signum( static_cast< bool >( false ) );
    BOOST_CHECK( falseBoolVal == false );
    constexpr auto trueBoolVal = signum( static_cast< bool >( true ) );
    BOOST_CHECK( trueBoolVal == true );
}

// --run_test=ConstexprMathTests/SByteSignumTest1
BOOST_AUTO_TEST_CASE( SByteSignumTest1 )
{
    constexpr auto negativeValue = signum( static_cast< SByte >( -2 ) );
    BOOST_CHECK( negativeValue == -1 );
    constexpr auto zeroValue = signum( static_cast< SByte >( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast< SByte >( 2 ) );
    BOOST_CHECK( positiveValue == 1 );
}

// --run_test=ConstexprMathTests/ByteSignumTest1
BOOST_AUTO_TEST_CASE( ByteSignumTest1 )
{
    constexpr auto positiveValue1 = signum( static_cast< Byte >( -2 ) );
    BOOST_CHECK( positiveValue1 == 1 );
    constexpr auto zeroValue = signum( static_cast< Byte >( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue2 = signum( static_cast< Byte >( 2 ) );
    BOOST_CHECK( positiveValue2 == 1 );
}

// --run_test=ConstexprMathTests/Int16SignumTest1
BOOST_AUTO_TEST_CASE( Int16SignumTest1 )
{
    constexpr auto negativeValue = signum( static_cast< Int16 >( -2 ) );
    BOOST_CHECK( negativeValue == -1 );
    constexpr auto zeroValue = signum( static_cast< Int16 >( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast< Int16 >( 2 ) );
    BOOST_CHECK( positiveValue == 1 );
}
// --run_test=ConstexprMathTests/UInt16SignumTest1
BOOST_AUTO_TEST_CASE( UInt16SignumTest1 )
{
    constexpr auto positiveValue1 = signum( static_cast< UInt16 >( -2 ) );
    BOOST_CHECK( positiveValue1 == 1 );
    constexpr auto zeroValue = signum( static_cast< UInt16 >( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue2 = signum( static_cast< UInt16 >( 2 ) );
    BOOST_CHECK( positiveValue2 == 1 );
}

// --run_test=ConstexprMathTests/Int32SignumTest1
BOOST_AUTO_TEST_CASE( Int32SignumTest1 )
{
    constexpr auto negativeValue = signum( static_cast< Int32 >( -2 ) );
    BOOST_CHECK( negativeValue == -1 );
    constexpr auto zeroValue = signum( static_cast< Int32 >( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast< Int32 >( 2 ) );
    BOOST_CHECK( positiveValue == 1 );
}
// --run_test=ConstexprMathTests/UInt32SignumTest1
BOOST_AUTO_TEST_CASE( UInt32SignumTest1 )
{
    constexpr auto positiveValue1 = signum( static_cast< UInt32 >( -2 ) );
    BOOST_CHECK( positiveValue1 == 1 );
    constexpr auto zeroValue = signum( static_cast< UInt32 >( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue2 = signum( static_cast< UInt32 >( 2 ) );
    BOOST_CHECK( positiveValue2 == 1 );
}

// --run_test=ConstexprMathTests/Int64SignumTest1
BOOST_AUTO_TEST_CASE( Int64SignumTest1 )
{
    constexpr auto negativeValue = signum( static_cast< Int64 >( -2 ) );
    BOOST_CHECK( negativeValue == -1 );
    constexpr auto zeroValue = signum( static_cast< Int64 >( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast< Int64 >( 2 ) );
    BOOST_CHECK( positiveValue == 1 );
}
// --run_test=ConstexprMathTests/UInt64SignumTest1
BOOST_AUTO_TEST_CASE( UInt64SignumTest1 )
{
    constexpr auto positiveValue1 = signum( static_cast< UInt64 >( -2 ) );
    BOOST_CHECK( positiveValue1 == 1 );
    constexpr auto zeroValue = signum( static_cast< UInt64 >( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue2 = signum( static_cast< UInt64 >( 2 ) );
    BOOST_CHECK( positiveValue2 == 1 );
}

// --run_test=ConstexprMathTests/wchar_tSignumTest1
BOOST_AUTO_TEST_CASE( wchar_tSignumTest1 )
{
    constexpr auto positiveValue1 = signum( static_cast< wchar_t >( -2 ) );
    BOOST_CHECK( positiveValue1 == 1 );
    constexpr auto zeroValue = signum( static_cast< wchar_t >( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue2 = signum( static_cast< wchar_t >( 2 ) );
    BOOST_CHECK( positiveValue2 == 1 );
}

// --run_test=ConstexprMathTests/SingleSignumTest1
BOOST_AUTO_TEST_CASE( SingleSignumTest1 )
{
    constexpr auto negativeValue = signum( static_cast< float >( -2 ) );
    BOOST_CHECK( negativeValue == -1 );
    constexpr auto zeroValue = signum( static_cast< float >( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast< float >( 2 ) );
    BOOST_CHECK( positiveValue == 1 );
}

// --run_test=ConstexprMathTests/DoubleSignumTest1
BOOST_AUTO_TEST_CASE( DoubleSignumTest1 )
{
    constexpr auto negativeValue = signum( static_cast< double >( -2 ) );
    BOOST_CHECK( negativeValue == -1 );
    constexpr auto zeroValue = signum( static_cast< double >( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast< double >( 2 ) );
    BOOST_CHECK( positiveValue == 1 );
}


// --run_test=ConstexprMathTests/FloatNextAfterTest1
BOOST_AUTO_TEST_CASE( FloatNextAfterTest1 )
{
    using C = Constants<float>;
    constexpr auto result1 = NextAfter( C::Zero, C::Infinity );
    auto expected1 = std::nextafter( C::Zero, C::Infinity );
    BOOST_CHECK( result1 == expected1 );

    constexpr auto result2 = NextAfter( C::Zero, C::NegativeInfinity );
    auto expected2 = std::nextafter( C::Zero, C::NegativeInfinity );
    BOOST_CHECK( result2 == expected2 );

    constexpr auto result3 = NextAfter( C::Max, C::Infinity );
    auto expected3 = std::nextafter( C::Max, C::Infinity );
    BOOST_CHECK( result3 == expected3 );

    constexpr auto result4 = NextAfter( C::Max, C::NegativeInfinity );
    auto expected4 = std::nextafter( C::Max, C::NegativeInfinity );
    BOOST_CHECK( result4 == expected4 );

    constexpr auto result5 = NextAfter( C::Min, C::Infinity );
    auto expected5 = std::nextafter( C::Min, C::Infinity );
    BOOST_CHECK( result5 == expected5 );

    constexpr auto result6 = NextAfter( C::Min, C::NegativeInfinity );
    auto expected6 = std::nextafter( C::Min, C::NegativeInfinity );
    BOOST_CHECK( result6 == expected6 );

    constexpr auto result7 = NextAfter( C::Lowest, C::Infinity );
    auto expected7 = std::nextafter( C::Lowest, C::Infinity );
    BOOST_CHECK( result7 == expected7 );

    constexpr auto result8 = NextAfter( C::Lowest, C::NegativeInfinity );
    auto expected8 = std::nextafter( C::Lowest, C::NegativeInfinity );
    BOOST_CHECK( result8 == expected8 );
}

// --run_test=ConstexprMathTests/DoubleNextAfterTest1
BOOST_AUTO_TEST_CASE( DoubleNextAfterTest1 )
{
    using C = Constants<double>;
    constexpr auto result1 = NextAfter( C::Zero, C::Infinity );
    auto expected1 = std::nextafter( C::Zero, C::Infinity );
    BOOST_CHECK( result1 == expected1 );

    constexpr auto result2 = NextAfter( C::Zero, C::NegativeInfinity );
    auto expected2 = std::nextafter( C::Zero, C::NegativeInfinity );
    BOOST_CHECK( result2 == expected2 );

    constexpr auto result3 = NextAfter( C::Max, C::Infinity );
    auto expected3 = std::nextafter( C::Max, C::Infinity );
    BOOST_CHECK( result3 == expected3 );

    constexpr auto result4 = NextAfter( C::Max, C::NegativeInfinity );
    auto expected4 = std::nextafter( C::Max, C::NegativeInfinity );
    BOOST_CHECK( result4 == expected4 );

    constexpr auto result5 = NextAfter( C::Min, C::Infinity );
    auto expected5 = std::nextafter( C::Min, C::Infinity );
    BOOST_CHECK( result5 == expected5 );

    constexpr auto result6 = NextAfter( C::Min, C::NegativeInfinity );
    auto expected6 = std::nextafter( C::Min, C::NegativeInfinity );
    BOOST_CHECK( result6 == expected6 );

    constexpr auto result7 = NextAfter( C::Lowest, C::Infinity );
    auto expected7 = std::nextafter( C::Lowest, C::Infinity );
    BOOST_CHECK( result7 == expected7 );

    constexpr auto result8 = NextAfter( C::Lowest, C::NegativeInfinity );
    auto expected8 = std::nextafter( C::Lowest, C::NegativeInfinity );
    BOOST_CHECK( result8 == expected8 );

}

// --run_test=ConstexprMathTests/FloatSqrtTest1
BOOST_AUTO_TEST_CASE( FloatSqrtTest1 )
{
    using C = Constants<float>;
    constexpr auto result1 = Sqrt( C::NaN );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = Sqrt( C::NegativeNaN );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = Sqrt( C::Infinity );
    BOOST_CHECK( IsInf( result3 ) );

    constexpr auto result4 = Sqrt( C::NegativeInfinity );
    BOOST_CHECK( IsNaN( result4 ) );

    constexpr auto result5 = Sqrt( -C::Min );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Sqrt( C::Zero );
    BOOST_CHECK( result6 == C::Zero );

    constexpr auto result7 = Sqrt( C::Min );
    auto expected7 = std::sqrt( C::Min );
    BOOST_CHECK( result7 == expected7 );

    constexpr auto result8 = Sqrt( C::Max );
    auto expected8 = std::sqrt( C::Max );
    BOOST_CHECK( result8 == expected8 );
}


// --run_test=ConstexprMathTests/DoubleSqrtTest1
BOOST_AUTO_TEST_CASE( DoubleSqrtTest1 )
{
    using C = Constants<double>;
    constexpr auto result1 = Sqrt( C::NaN );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = Sqrt( C::NegativeNaN );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = Sqrt( C::Infinity );
    BOOST_CHECK( IsInf( result3 ) );

    constexpr auto result4 = Sqrt( C::NegativeInfinity );
    BOOST_CHECK( IsNaN( result4 ) );

    constexpr auto result5 = Sqrt( -C::Min );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Sqrt( C::Zero );
    BOOST_CHECK( result6 == C::Zero );

    constexpr auto result7 = Sqrt( C::Min );
    auto expected7 = std::sqrt( C::Min );
    BOOST_CHECK( result7 == expected7 );

    constexpr auto result8 = Sqrt( C::Max );
    auto expected8 = std::sqrt( C::Max );
    BOOST_CHECK( result8 == expected8 );
}

// --run_test=ConstexprMathTests/FloatReciprocalSqrtTest1
BOOST_AUTO_TEST_CASE( FloatReciprocalSqrtTest1 )
{
    using C = Constants<float>;
    constexpr auto result1 = ReciprocalSqrt( C::NaN );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = ReciprocalSqrt( C::NegativeNaN );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = ReciprocalSqrt( C::Infinity );
    BOOST_CHECK( result3 == C::Zero );

    constexpr auto result4 = ReciprocalSqrt( C::NegativeInfinity );
    BOOST_CHECK( IsNaN( result4 ) );

    constexpr auto result5 = ReciprocalSqrt( -C::Min );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = ReciprocalSqrt( C::Zero );
    BOOST_CHECK( IsInf( result6 ) );

    constexpr auto result7 = ReciprocalSqrt( C::Min );
    auto expected7 = C::One / std::sqrt( C::Min );
    BOOST_CHECK( result7 == expected7 );

    constexpr auto result8 = ReciprocalSqrt( C::Max );
    auto expected8 = C::One / std::sqrt( C::Max );
    BOOST_CHECK( result8 == expected8 );
}

// --run_test=ConstexprMathTests/DoubleReciprocalSqrtTest1
BOOST_AUTO_TEST_CASE( DoubleReciprocalSqrtTest1 )
{
    using C = Constants<double>;
    constexpr auto result1 = ReciprocalSqrt( C::NaN );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = ReciprocalSqrt( C::NegativeNaN );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = ReciprocalSqrt( C::Infinity );
    BOOST_CHECK( result3 == C::Zero );

    constexpr auto result4 = ReciprocalSqrt( C::NegativeInfinity );
    BOOST_CHECK( IsNaN( result4 ) );

    constexpr auto result5 = ReciprocalSqrt( -C::Min );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = ReciprocalSqrt( C::Zero );
    BOOST_CHECK( IsInf( result6 ) );

    constexpr auto result7 = ReciprocalSqrt( C::Min );
    auto expected7 = C::One / std::sqrt( C::Min );
    BOOST_CHECK( result7 == expected7 );

    constexpr auto result8 = ReciprocalSqrt( C::Max );
    auto expected8 = C::One / std::sqrt( C::Max );
    BOOST_CHECK( result8 == expected8 );
}


// --run_test=ConstexprMathTests/FloatCbrtTest1
BOOST_AUTO_TEST_CASE( FloatCbrtTest1 )
{
    using C = Constants<float>;
    constexpr auto result1 = Cbrt( C::NaN );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = Cbrt( C::NegativeNaN );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = Cbrt( C::Infinity );
    BOOST_CHECK( IsInf( result3 ) );

    constexpr auto result4 = Cbrt( C::NegativeInfinity );
    auto expected4 = std::cbrt( C::NegativeInfinity );
    BOOST_CHECK( result4 == expected4 );

    constexpr auto result5 = Cbrt( -C::Min );
    auto expected5 = std::cbrt( -C::Min );
    BOOST_CHECK( result5 == expected5 );

    constexpr auto result6 = Cbrt( C::Zero );
    BOOST_CHECK( result6 == C::Zero );

    constexpr auto result7 = Cbrt( C::Min );
    auto expected7 = std::cbrt( C::Min );
    BOOST_CHECK( result7 == expected7 );

    constexpr auto result8 = Cbrt( C::Max );
    auto expected8 = std::cbrt( C::Max );
    auto v = result8 / expected8;
    BOOST_CHECK( AreNearlyEqual( v, 1.f ) );
}




// --run_test=ConstexprMathTests/IsNaNTest1
BOOST_AUTO_TEST_CASE( IsNaNTest1 )
{
    constexpr float nanValue = std::numeric_limits<float>::quiet_NaN( );
    constexpr bool result = IsNaN( 1, nanValue );
    BOOST_CHECK( result );

    constexpr bool result2 = IsNaN( 1, 2.0 );
    BOOST_CHECK( result2 == false );
#if 0
    // Not expected to compile:
    constexpr bool result3 = IsNaN( 1, 2.0, true );
    BOOST_CHECK( result3 == false );
#endif
}

// --run_test=MathTests/InternalMinImplFloatTest1
BOOST_AUTO_TEST_CASE( InternalMinImplFloatTest1 )
{
    constexpr auto minValue = Math::Min( 5.f, 4.f, 3.f, 4.f, 4.f );
    constexpr bool equal = minValue == 3.f;
    BOOST_CHECK( equal );
}

// --run_test=MathTests/InternalMaxImplFloatTest1
BOOST_AUTO_TEST_CASE( InternalMaxImplFloatTest1 )
{
    constexpr auto minValue = Math::Max( 5.f, 4.f, 3.f, 4.f, 4.f );
    constexpr bool equal = minValue == 5.f;
    BOOST_CHECK( equal );
}

// --run_test=MathTests/MinDoubleTest1
BOOST_AUTO_TEST_CASE( MinDoubleTest1 )
{
    constexpr double val1 = 1.0;
    constexpr double val2 = 2.0;

    constexpr double result = Min( val1, val2 );

    constexpr bool equal = AreNearlyEqual( val1, result );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/MaxDoubleTest1
BOOST_AUTO_TEST_CASE( MaxDoubleTest1 )
{
    constexpr double val1 = 2.0;
    constexpr double val2 = 1.0;

    constexpr double result = Max( val1, val2 );

    constexpr bool equal = AreNearlyEqual( val1, result );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/FloorDoubleTest1
BOOST_AUTO_TEST_CASE( FloorDoubleTest1 )
{
    constexpr double value1 = -1.5;
    constexpr double value2 = -0.5;
    constexpr double value3 = -0.0;
    constexpr double value4 = 0.0;
    constexpr double value5 = 0.5;
    constexpr double value6 = 1.5;

    constexpr double result1 = Floor( value1 );
    BOOST_CHECK( result1 == -2. );
    constexpr double result2 = Floor( value2 );
    BOOST_CHECK( result2 == -1. );
    constexpr double result3 = Floor( value3 );
    BOOST_CHECK( result3 == -0. );
    constexpr double result4 = Floor( value4 );
    BOOST_CHECK( result4 == 0. );
    constexpr double result5 = Floor( value5 );
    BOOST_CHECK( result5 == 0. );
    constexpr double result6 = Floor( value6 );
    BOOST_CHECK( result6 == 1. );

}

// --run_test=MathTests/OpenLibMFloorDoubleTest1
BOOST_AUTO_TEST_CASE( OpenLibMFloorDoubleTest1 )
{
    constexpr double value1 = -1.5;
    constexpr double value2 = -0.5;
    constexpr double value3 = -0.0;
    constexpr double value4 = 0.0;
    constexpr double value5 = 0.5;
    constexpr double value6 = 1.5;

    constexpr double result1 = OpenLibM::floor( value1 );
    BOOST_CHECK( result1 == -2. );
    constexpr double result2 = OpenLibM::floor( value2 );
    BOOST_CHECK( result2 == -1. );
    constexpr double result3 = OpenLibM::floor( value3 );
    BOOST_CHECK( result3 == -0. );
    constexpr double result4 = OpenLibM::floor( value4 );
    BOOST_CHECK( result4 == 0. );
    constexpr double result5 = OpenLibM::floor( value5 );
    BOOST_CHECK( result5 == 0. );
    constexpr double result6 = OpenLibM::floor( value6 );
    BOOST_CHECK( result6 == 1. );
}

// --run_test=MathTests/CeilDoubleTest1
BOOST_AUTO_TEST_CASE( CeilDoubleTest1 )
{
    constexpr double value1 = -1.5;
    constexpr double value2 = -0.5;
    constexpr double value3 = -0.0;
    constexpr double value4 = 0.0;
    constexpr double value5 = 0.5;
    constexpr double value6 = 1.5;

    constexpr double result1 = Ceil( value1 );
    BOOST_CHECK( result1 == -1. );
    constexpr double result2 = Ceil( value2 );
    BOOST_CHECK( result2 == -0. );
    constexpr double result3 = Ceil( value3 );
    BOOST_CHECK( result3 == -0. );
    constexpr double result4 = Ceil( value4 );
    BOOST_CHECK( result4 == 0. );
    constexpr double result5 = Ceil( value5 );
    BOOST_CHECK( result5 == 1. );
    constexpr double result6 = Ceil( value6 );
    BOOST_CHECK( result6 == 2. );

}

// --run_test=MathTests/OpenLibMCeilDoubleTest1
BOOST_AUTO_TEST_CASE( OpenLibMCeilDoubleTest1 )
{
    constexpr double value1 = -1.5;
    constexpr double value2 = -0.5;
    constexpr double value3 = -0.0;
    constexpr double value4 = 0.0;
    constexpr double value5 = 0.5;
    constexpr double value6 = 1.5;

    constexpr double result1 = OpenLibM::ceil( value1 );
    BOOST_CHECK( result1 == -1. );
    constexpr double result2 = OpenLibM::ceil( value2 );
    BOOST_CHECK( result2 == -0. );
    constexpr double result3 = OpenLibM::ceil( value3 );
    BOOST_CHECK( result3 == -0. );
    constexpr double result4 = OpenLibM::ceil( value4 );
    BOOST_CHECK( result4 == 0. );
    constexpr double result5 = OpenLibM::ceil( value5 );
    BOOST_CHECK( result5 == 1. );
    constexpr double result6 = OpenLibM::ceil( value6 );
    BOOST_CHECK( result6 == 2. );

}

// --run_test=MathTests/Deg2RadDoubleTest1
BOOST_AUTO_TEST_CASE( Deg2RadDoubleTest1 )
{
    constexpr auto result1 = Deg2Rad( 0.001 );
    BOOST_CHECK( result1 == 1.7453292519943296e-5 );
}


// --run_test=MathTests/SinDoubleTest1
BOOST_AUTO_TEST_CASE( SinDoubleTest1 )
{
    constexpr auto rM20000 = Deg2Rad( -20000. );
    constexpr auto rM720 = Deg2Rad( -720. );
    constexpr auto rM360 = Deg2Rad( -360. );
    constexpr auto rM180 = Deg2Rad( -180. );
    constexpr auto rM135 = Deg2Rad( 135. );
    constexpr auto rM90 = Deg2Rad( -90. );
    constexpr auto rM45 = Deg2Rad( -45. );
    constexpr auto r0 = Deg2Rad( 0. );
    constexpr auto r45 = Deg2Rad( 45. );
    constexpr auto r90 = Deg2Rad( 90. );
    constexpr auto r135 = Deg2Rad( 135. );
    constexpr auto r180 = Deg2Rad( 180. );
    constexpr auto r360 = Deg2Rad( 360. );
    constexpr auto r720 = Deg2Rad( 720. );
    constexpr auto r20000 = Deg2Rad( 20000. );

    constexpr auto sineRM20000 = Sin( rM20000 );
    constexpr auto sineRM720 = Sin( rM720 );
    constexpr auto sineRM360 = Sin( rM360 );
    constexpr auto sineRM180 = Sin( rM180 );
    constexpr auto sineRM135 = Sin( rM135 );
    constexpr auto sineRM90 = Sin( rM90 );
    constexpr auto sineRM45 = Sin( rM45 );
    constexpr auto sineR0 = Sin( r0 );
    constexpr auto sineR45 = Sin( r45 );
    constexpr auto sineR90 = Sin( r90 );
    constexpr auto sineR135 = Sin( r135 );
    constexpr auto sineR180 = Sin( r180 );
    constexpr auto sineR360 = Sin( r360 );
    constexpr auto sineR720 = Sin( r720 );
    constexpr auto sineR20000 = Sin( r20000 );

    auto expectedSineRM20000 = std::sin( rM20000 );
    auto expectedSineRM720 = std::sin( rM720 );
    auto expectedSineRM360 = std::sin( rM360 );
    auto expectedSineRM180 = std::sin( rM180 );
    auto expectedSineRM135 = std::sin( rM135 );
    auto expectedSineRM90 = std::sin( rM90 );
    auto expectedSineRM45 = std::sin( rM45 );
    auto expectedSineR0 = std::sin( r0 );
    auto expectedSineR45 = std::sin( r45 );
    auto expectedSineR90 = std::sin( r90 );
    auto expectedSineR135 = std::sin( r135 );
    auto expectedSineR180 = std::sin( r180 );
    auto expectedSineR360 = std::sin( r360 );
    auto expectedSineR720 = std::sin( r720 );
    auto expectedSineR20000 = std::sin( r20000 );

    BOOST_CHECK( expectedSineRM20000 == sineRM20000 );
    BOOST_CHECK( expectedSineRM720 == sineRM720 );
    BOOST_CHECK( expectedSineRM360 == sineRM360 );
    BOOST_CHECK( expectedSineRM180 == sineRM180 );
    BOOST_CHECK( expectedSineRM135 == sineRM135 );
    BOOST_CHECK( expectedSineRM90 == sineRM90 );
    BOOST_CHECK_CLOSE( expectedSineRM45, sineRM45, 0.0000000000001 );
    BOOST_CHECK( expectedSineR0 == sineR0 );
    BOOST_CHECK_CLOSE( expectedSineR45, sineR45, 0.0000000000001 );
    BOOST_CHECK( expectedSineR90 == sineR90 );
    BOOST_CHECK( expectedSineR135 == sineR135 );
    BOOST_CHECK( expectedSineR180 == sineR180 );
    BOOST_CHECK( expectedSineR360 == sineR360 );
    BOOST_CHECK( expectedSineR720 == sineR720 );
    BOOST_CHECK( expectedSineR20000 == sineR20000 );


    constexpr auto radians = Deg2Rad( 0.001 );
    constexpr auto result1a = Sin( radians );
    auto result1b = std::sin( radians );
    auto result1Diff = result1a - result1b;
    BOOST_CHECK( result1a == result1b );
    BOOST_CHECK( result1a == 1.7453292519057202e-5 );
    BOOST_CHECK( result1b == 1.7453292519057202e-5 );
}

// --run_test=MathTests/OpenLibMSinDoubleTest1
BOOST_AUTO_TEST_CASE( OpenLibMSinDoubleTest1 )
{
    constexpr auto radians = Deg2Rad( 0.001 );
    constexpr auto result1a = OpenLibM::sin( radians );
    auto result1b = std::sin( radians );
    auto result1Diff = result1a - result1b;
    BOOST_CHECK( result1a == result1b );
    BOOST_CHECK( result1a == 1.7453292519057202e-5 );
    BOOST_CHECK( result1b == 1.7453292519057202e-5 );
}



BOOST_AUTO_TEST_SUITE_END( )
