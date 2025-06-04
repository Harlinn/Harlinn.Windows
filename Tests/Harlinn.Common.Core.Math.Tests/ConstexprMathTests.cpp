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

// --run_test=ConstexprMathTests/DoubleCbrtTest1
BOOST_AUTO_TEST_CASE( DoubleCbrtTest1 )
{
    using C = Constants<double>;
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
    BOOST_CHECK( AreNearlyEqual( result5, expected5 ) );

    constexpr auto result6 = Cbrt( C::Zero );
    BOOST_CHECK( result6 == C::Zero );

    constexpr auto result7 = Cbrt( C::Min );
    auto expected7 = std::cbrt( C::Min );
    BOOST_CHECK( AreNearlyEqual( result7, expected7) );

    constexpr auto result8 = Cbrt( C::Max );
    auto expected8 = std::cbrt( C::Max );
    auto v = result8 / expected8;
    BOOST_CHECK( AreNearlyEqual( v, 1. ) );
}

// --run_test=ConstexprMathTests/FloatNextDownTest1
BOOST_AUTO_TEST_CASE( FloatNextDownTest1 )
{
    using C = Constants<float>;
    
    constexpr auto result1 = NextDown( C::NaN );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = NextDown( C::Infinity );
    constexpr auto expected2 = C::Max;
    BOOST_CHECK( result2 == expected2 );

    constexpr auto result3 = NextDown( C::Min );
    auto expected3 = std::nextafter( C::Min, 0.f );
    BOOST_CHECK( result3 == expected3 );

    constexpr auto result4 = NextDown( C::Zero );
    auto expected4 = std::nextafter( C::Zero, C::NegativeInfinity );
    BOOST_CHECK( result4 == expected4 );

    constexpr auto result5 = NextDown( C::Lowest );
    BOOST_CHECK( IsInf( result5 ) );
}

// --run_test=ConstexprMathTests/DoubleNextDownTest1
BOOST_AUTO_TEST_CASE( DoubleNextDownTest1 )
{
    using C = Constants<double>;

    constexpr auto result1 = NextDown( C::NaN );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = NextDown( C::Infinity );
    constexpr auto expected2 = C::Max;
    BOOST_CHECK( result2 == expected2 );

    constexpr auto result3 = NextDown( C::Min );
    auto expected3 = std::nextafter( C::Min, 0.f );
    BOOST_CHECK( result3 == expected3 );

    constexpr auto result4 = NextDown( C::Zero );
    auto expected4 = std::nextafter( C::Zero, C::NegativeInfinity );
    BOOST_CHECK( result4 == expected4 );

    constexpr auto result5 = NextDown( C::Lowest );
    BOOST_CHECK( IsInf( result5 ) );
}

// --run_test=ConstexprMathTests/FloatNextUpTest1
BOOST_AUTO_TEST_CASE( FloatNextUpTest1 )
{
    using C = Constants<float>;

    constexpr auto result1 = NextUp( C::NaN );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = NextUp( C::NegativeInfinity );
    constexpr auto expected2 = C::Lowest;
    BOOST_CHECK( result2 == expected2 );

    constexpr auto result3 = NextUp( -C::Min );
    auto expected3 = std::nextafter( -C::Min, C::Zero );
    BOOST_CHECK( result3 == expected3 );

    constexpr auto result4 = NextUp( C::Zero );
    auto expected4 = std::nextafter( C::Zero, C::Infinity );
    BOOST_CHECK( result4 == expected4 );

    constexpr auto result5 = NextUp( C::Max );
    BOOST_CHECK( IsInf( result5 ) );
}

// --run_test=ConstexprMathTests/DoubleNextUpTest1
BOOST_AUTO_TEST_CASE( DoubleNextUpTest1 )
{
    using C = Constants<double>;

    constexpr auto result1 = NextUp( C::NaN );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = NextUp( C::NegativeInfinity );
    constexpr auto expected2 = C::Lowest;
    BOOST_CHECK( result2 == expected2 );

    constexpr auto result3 = NextUp( -C::Min );
    auto expected3 = std::nextafter( -C::Min, C::Zero );
    BOOST_CHECK( result3 == expected3 );

    constexpr auto result4 = NextUp( C::Zero );
    auto expected4 = std::nextafter( C::Zero, C::Infinity );
    BOOST_CHECK( result4 == expected4 );

    constexpr auto result5 = NextUp( C::Max );
    BOOST_CHECK( IsInf( result5 ) );
}


// --run_test=ConstexprMathTests/FloatIsSameValueTest1
BOOST_AUTO_TEST_CASE( FloatIsSameValueTest1 )
{
    using C = Constants<float>;

    auto constexpr result1 = IsSameValue( C::NaN, C::NaN );
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsSameValue( C::NegativeNaN, C::NegativeNaN );
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsSameValue( C::sNaN, C::sNaN );
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsSameValue( C::sNegativeNaN, C::sNegativeNaN );
    BOOST_CHECK( result4 );
    auto constexpr result5 = IsSameValue( C::NegativeInfinity, C::NegativeInfinity );
    BOOST_CHECK( result5 );
    auto constexpr result6 = IsSameValue( C::Lowest, C::Lowest );
    BOOST_CHECK( result6 );
    auto constexpr result7 = IsSameValue( -C::Min, -C::Min );
    BOOST_CHECK( result7 );
    auto constexpr result8 = IsSameValue( -C::DenormalMin, -C::DenormalMin );
    BOOST_CHECK( result8 );
    auto constexpr result9 = IsSameValue( -C::Zero, -C::Zero );
    BOOST_CHECK( result9 );
    auto constexpr result10 = IsSameValue( C::Zero, C::Zero );
    BOOST_CHECK( result10 );
    auto constexpr result11 = IsSameValue( C::DenormalMin, C::DenormalMin );
    BOOST_CHECK( result11 );
    auto constexpr result12 = IsSameValue( C::Min, C::Min );
    BOOST_CHECK( result12 );
    auto constexpr result13 = IsSameValue( C::Max, C::Max );
    BOOST_CHECK( result13 );
    auto constexpr result14 = IsSameValue( C::Infinity, C::Infinity );
    BOOST_CHECK( result14 );

    auto constexpr result15 = IsSameValue( C::NaN, C::sNaN );
    BOOST_CHECK( result15 );
    auto constexpr result16 = IsSameValue( C::NegativeNaN, C::NaN ) == false;
    BOOST_CHECK( result16 );
    auto constexpr result17 = IsSameValue( C::sNaN, C::sNegativeNaN ) == false;
    BOOST_CHECK( result17 );
    auto constexpr result18 = IsSameValue( C::Zero, -C::Zero ) == false;
    BOOST_CHECK( result18 );

}


// --run_test=ConstexprMathTests/DoubleIsSameValueTest1
BOOST_AUTO_TEST_CASE( DoubleIsSameValueTest1 )
{
    using C = Constants<double>;

    auto constexpr result1 = IsSameValue( C::NaN, C::NaN );
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsSameValue( C::NegativeNaN, C::NegativeNaN );
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsSameValue( C::sNaN, C::sNaN );
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsSameValue( C::sNegativeNaN, C::sNegativeNaN );
    BOOST_CHECK( result4 );
    auto constexpr result5 = IsSameValue( C::NegativeInfinity, C::NegativeInfinity );
    BOOST_CHECK( result5 );
    auto constexpr result6 = IsSameValue( C::Lowest, C::Lowest );
    BOOST_CHECK( result6 );
    auto constexpr result7 = IsSameValue( -C::Min, -C::Min );
    BOOST_CHECK( result7 );
    auto constexpr result8 = IsSameValue( -C::DenormalMin, -C::DenormalMin );
    BOOST_CHECK( result8 );
    auto constexpr result9 = IsSameValue( -C::Zero, -C::Zero );
    BOOST_CHECK( result9 );
    auto constexpr result10 = IsSameValue( C::Zero, C::Zero );
    BOOST_CHECK( result10 );
    auto constexpr result11 = IsSameValue( C::DenormalMin, C::DenormalMin );
    BOOST_CHECK( result11 );
    auto constexpr result12 = IsSameValue( C::Min, C::Min );
    BOOST_CHECK( result12 );
    auto constexpr result13 = IsSameValue( C::Max, C::Max );
    BOOST_CHECK( result13 );
    auto constexpr result14 = IsSameValue( C::Infinity, C::Infinity );
    BOOST_CHECK( result14 );
}

// --run_test=ConstexprMathTests/FloatIsZeroTest1
BOOST_AUTO_TEST_CASE( FloatIsZeroTest1 )
{
    using C = Constants<float>;

    auto constexpr result1 = IsZero( C::NaN ) == false;
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsZero( C::NegativeNaN ) == false;
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsZero( C::sNaN ) == false;
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsZero( C::sNegativeNaN ) == false;
    BOOST_CHECK( result4 );
    auto constexpr result5 = IsZero( C::NegativeInfinity ) == false;
    BOOST_CHECK( result5 );
    auto constexpr result6 = IsZero( C::Lowest ) == false;
    BOOST_CHECK( result6 );
    auto constexpr result7 = IsZero( -C::Min ) == false;
    BOOST_CHECK( result7 );
    auto constexpr result8 = IsZero( -C::DenormalMin ) == false;
    BOOST_CHECK( result8 );
    auto constexpr result9 = IsZero( -C::Zero );
    BOOST_CHECK( result9 );
    auto constexpr result10 = IsZero( C::Zero );
    BOOST_CHECK( result10 );
    auto constexpr result11 = IsZero( C::DenormalMin ) == false;
    BOOST_CHECK( result11 );
    auto constexpr result12 = IsZero( C::Min ) == false;
    BOOST_CHECK( result12 );
    auto constexpr result13 = IsZero( C::Max ) == false;
    BOOST_CHECK( result13 );
    auto constexpr result14 = IsZero( C::Infinity ) == false;
    BOOST_CHECK( result14 );
    auto constexpr result15 = IsZero( 0 );
    BOOST_CHECK( result15 );
}

// --run_test=ConstexprMathTests/DoubleIsZeroTest1
BOOST_AUTO_TEST_CASE( DoubleIsZeroTest1 )
{
    using C = Constants<double>;

    auto constexpr result1 = IsZero( C::NaN ) == false;
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsZero( C::NegativeNaN ) == false;
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsZero( C::sNaN ) == false;
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsZero( C::sNegativeNaN ) == false;
    BOOST_CHECK( result4 );
    auto constexpr result5 = IsZero( C::NegativeInfinity ) == false;
    BOOST_CHECK( result5 );
    auto constexpr result6 = IsZero( C::Lowest ) == false;
    BOOST_CHECK( result6 );
    auto constexpr result7 = IsZero( -C::Min ) == false;
    BOOST_CHECK( result7 );
    auto constexpr result8 = IsZero( -C::DenormalMin ) == false;
    BOOST_CHECK( result8 );
    auto constexpr result9 = IsZero( -C::Zero );
    BOOST_CHECK( result9 );
    auto constexpr result10 = IsZero( C::Zero );
    BOOST_CHECK( result10 );
    auto constexpr result11 = IsZero( C::DenormalMin ) == false;
    BOOST_CHECK( result11 );
    auto constexpr result12 = IsZero( C::Min ) == false;
    BOOST_CHECK( result12 );
    auto constexpr result13 = IsZero( C::Max ) == false;
    BOOST_CHECK( result13 );
    auto constexpr result14 = IsZero( C::Infinity ) == false;
    BOOST_CHECK( result14 );
    auto constexpr result15 = IsZero( 0 );
    BOOST_CHECK( result15 );
}


// --run_test=ConstexprMathTests/FloatIsNaNTest1
BOOST_AUTO_TEST_CASE( FloatIsNaNTest1 )
{
    using C = Constants<float>;

    auto constexpr result1 = IsNaN( C::NaN );
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsNaN( C::NegativeNaN );
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsNaN( C::sNaN );
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsNaN( C::sNegativeNaN );
    BOOST_CHECK( result4 );
    auto constexpr result5 = IsNaN( C::NegativeInfinity ) == false;
    BOOST_CHECK( result5 );
    auto constexpr result6 = IsNaN( C::Lowest ) == false;
    BOOST_CHECK( result6 );
    auto constexpr result7 = IsNaN( -C::Min ) == false;
    BOOST_CHECK( result7 );
    auto constexpr result8 = IsNaN( -C::DenormalMin ) == false;
    BOOST_CHECK( result8 );
    auto constexpr result9 = IsNaN( -C::Zero ) == false;
    BOOST_CHECK( result9 );
    auto constexpr result10 = IsNaN( C::Zero ) == false;
    BOOST_CHECK( result10 );
    auto constexpr result11 = IsNaN( C::DenormalMin ) == false;
    BOOST_CHECK( result11 );
    auto constexpr result12 = IsNaN( C::Min ) == false;
    BOOST_CHECK( result12 );
    auto constexpr result13 = IsNaN( C::Max ) == false;
    BOOST_CHECK( result13 );
    auto constexpr result14 = IsNaN( C::Infinity ) == false;
    BOOST_CHECK( result14 );

    auto constexpr result15 = IsNaN( C::Max, C::NaN, C::Zero, 4, 0.3 );
    BOOST_CHECK( result15 );

}

// --run_test=ConstexprMathTests/DoubleIsNaNTest1
BOOST_AUTO_TEST_CASE( DoubleIsNaNTest1 )
{
    using C = Constants<double>;

    auto constexpr result1 = IsNaN( C::NaN );
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsNaN( C::NegativeNaN );
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsNaN( C::sNaN );
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsNaN( C::sNegativeNaN );
    BOOST_CHECK( result4 );
    auto constexpr result5 = IsNaN( C::NegativeInfinity ) == false;
    BOOST_CHECK( result5 );
    auto constexpr result6 = IsNaN( C::Lowest ) == false;
    BOOST_CHECK( result6 );
    auto constexpr result7 = IsNaN( -C::Min ) == false;
    BOOST_CHECK( result7 );
    auto constexpr result8 = IsNaN( -C::DenormalMin ) == false;
    BOOST_CHECK( result8 );
    auto constexpr result9 = IsNaN( -C::Zero ) == false;
    BOOST_CHECK( result9 );
    auto constexpr result10 = IsNaN( C::Zero ) == false;
    BOOST_CHECK( result10 );
    auto constexpr result11 = IsNaN( C::DenormalMin ) == false;
    BOOST_CHECK( result11 );
    auto constexpr result12 = IsNaN( C::Min ) == false;
    BOOST_CHECK( result12 );
    auto constexpr result13 = IsNaN( C::Max ) == false;
    BOOST_CHECK( result13 );
    auto constexpr result14 = IsNaN( C::Infinity ) == false;
    BOOST_CHECK( result14 );

    auto constexpr result15 = IsNaN( C::Max, C::NaN, C::Zero, 4, 0.3f );
    BOOST_CHECK( result15 );
}

// --run_test=ConstexprMathTests/FloatIsInfTest1
BOOST_AUTO_TEST_CASE( FloatIsInfTest1 )
{
    using C = Constants<float>;

    auto constexpr result1 = IsInf( C::NaN ) == false;
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsInf( C::NegativeNaN ) == false;
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsInf( C::sNaN ) == false;
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsInf( C::sNegativeNaN ) == false;
    BOOST_CHECK( result4 );
    auto constexpr result5 = IsInf( C::NegativeInfinity );
    BOOST_CHECK( result5 );
    auto constexpr result6 = IsInf( C::Lowest ) == false;
    BOOST_CHECK( result6 );
    auto constexpr result7 = IsInf( -C::Min ) == false;
    BOOST_CHECK( result7 );
    auto constexpr result8 = IsInf( -C::DenormalMin ) == false;
    BOOST_CHECK( result8 );
    auto constexpr result9 = IsInf( -C::Zero ) == false;
    BOOST_CHECK( result9 );
    auto constexpr result10 = IsInf( C::Zero ) == false;
    BOOST_CHECK( result10 );
    auto constexpr result11 = IsInf( C::DenormalMin ) == false;
    BOOST_CHECK( result11 );
    auto constexpr result12 = IsInf( C::Min ) == false;
    BOOST_CHECK( result12 );
    auto constexpr result13 = IsInf( C::Max ) == false;
    BOOST_CHECK( result13 );
    auto constexpr result14 = IsInf( C::Infinity );
    BOOST_CHECK( result14 );

    auto constexpr result15 = IsInf( C::Max, C::Infinity, C::Zero, 4, 0.3 );
    BOOST_CHECK( result15 );

}

// --run_test=ConstexprMathTests/DoubleIsInfTest1
BOOST_AUTO_TEST_CASE( DoubleIsInfTest1 )
{
    using C = Constants<double>;

    auto constexpr result1 = IsInf( C::NaN ) == false;
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsInf( C::NegativeNaN ) == false;
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsInf( C::sNaN ) == false;
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsInf( C::sNegativeNaN ) == false;
    BOOST_CHECK( result4 );
    auto constexpr result5 = IsInf( C::NegativeInfinity );
    BOOST_CHECK( result5 );
    auto constexpr result6 = IsInf( C::Lowest ) == false;
    BOOST_CHECK( result6 );
    auto constexpr result7 = IsInf( -C::Min ) == false;
    BOOST_CHECK( result7 );
    auto constexpr result8 = IsInf( -C::DenormalMin ) == false;
    BOOST_CHECK( result8 );
    auto constexpr result9 = IsInf( -C::Zero ) == false;
    BOOST_CHECK( result9 );
    auto constexpr result10 = IsInf( C::Zero ) == false;
    BOOST_CHECK( result10 );
    auto constexpr result11 = IsInf( C::DenormalMin ) == false;
    BOOST_CHECK( result11 );
    auto constexpr result12 = IsInf( C::Min ) == false;
    BOOST_CHECK( result12 );
    auto constexpr result13 = IsInf( C::Max ) == false;
    BOOST_CHECK( result13 );
    auto constexpr result14 = IsInf( C::Infinity );
    BOOST_CHECK( result14 );

    auto constexpr result15 = IsInf( C::Max, C::Infinity, C::Zero, 4, 0.3 );
    BOOST_CHECK( result15 );

}

// --run_test=ConstexprMathTests/FloatIsFiniteTest1
BOOST_AUTO_TEST_CASE( FloatIsFiniteTest1 )
{
    using C = Constants<float>;

    auto constexpr result1 = IsFinite( C::NaN ) == false;
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsFinite( C::NegativeNaN ) == false;
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsFinite( C::sNaN ) == false;
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsFinite( C::sNegativeNaN ) == false;
    BOOST_CHECK( result4 );
    auto constexpr result5 = IsFinite( C::NegativeInfinity ) == false;
    BOOST_CHECK( result5 );
    auto constexpr result6 = IsFinite( C::Lowest );
    BOOST_CHECK( result6 );
    auto constexpr result7 = IsFinite( -C::Min );
    BOOST_CHECK( result7 );
    auto constexpr result8 = IsFinite( -C::DenormalMin );
    BOOST_CHECK( result8 );
    auto constexpr result9 = IsFinite( -C::Zero );
    BOOST_CHECK( result9 );
    auto constexpr result10 = IsFinite( C::Zero );
    BOOST_CHECK( result10 );
    auto constexpr result11 = IsFinite( C::DenormalMin );
    BOOST_CHECK( result11 );
    auto constexpr result12 = IsFinite( C::Min );
    BOOST_CHECK( result12 );
    auto constexpr result13 = IsFinite( C::Max );
    BOOST_CHECK( result13 );
    auto constexpr result14 = IsFinite( C::Infinity ) == false;
    BOOST_CHECK( result14 );

    auto constexpr result15 = IsFinite( C::Lowest, -C::Min );
    BOOST_CHECK( result15 );

    auto constexpr result16 = IsFinite( C::Lowest, -C::Min, -C::DenormalMin, -C::Zero, C::Zero, C::DenormalMin, C::Min, C::Max );
    BOOST_CHECK( result16 );

    auto constexpr result17 = IsFinite( C::Lowest, -C::Min, -C::DenormalMin, C::NaN, -C::Zero, C::Zero, C::DenormalMin, C::Min, C::Max ) == false;
    BOOST_CHECK( result17 );

    auto constexpr result18 = IsFinite( C::Lowest, 4 ,-C::Min, 0.3 );
    BOOST_CHECK( result18 );

    auto constexpr result19 = IsFinite( C::Lowest, C::NaN ) == false;
    BOOST_CHECK( result19 );
}

// --run_test=ConstexprMathTests/DoubleIsFiniteTest1
BOOST_AUTO_TEST_CASE( DoubleIsFiniteTest1 )
{
    using C = Constants<double>;

    auto constexpr result1 = IsFinite( C::NaN ) == false;
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsFinite( C::NegativeNaN ) == false;
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsFinite( C::sNaN ) == false;
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsFinite( C::sNegativeNaN ) == false;
    BOOST_CHECK( result4 );
    auto constexpr result5 = IsFinite( C::NegativeInfinity ) == false;
    BOOST_CHECK( result5 );
    auto constexpr result6 = IsFinite( C::Lowest );
    BOOST_CHECK( result6 );
    auto constexpr result7 = IsFinite( -C::Min );
    BOOST_CHECK( result7 );
    auto constexpr result8 = IsFinite( -C::DenormalMin );
    BOOST_CHECK( result8 );
    auto constexpr result9 = IsFinite( -C::Zero );
    BOOST_CHECK( result9 );
    auto constexpr result10 = IsFinite( C::Zero );
    BOOST_CHECK( result10 );
    auto constexpr result11 = IsFinite( C::DenormalMin );
    BOOST_CHECK( result11 );
    auto constexpr result12 = IsFinite( C::Min );
    BOOST_CHECK( result12 );
    auto constexpr result13 = IsFinite( C::Max );
    BOOST_CHECK( result13 );
    auto constexpr result14 = IsFinite( C::Infinity ) == false;
    BOOST_CHECK( result14 );

    auto constexpr result15 = IsFinite( C::Lowest, -C::Min );
    BOOST_CHECK( result15 );

    auto constexpr result16 = IsFinite( C::Lowest, -C::Min, -C::DenormalMin, -C::Zero, C::Zero, C::DenormalMin, C::Min, C::Max );
    BOOST_CHECK( result16 );

    auto constexpr result17 = IsFinite( C::Lowest, -C::Min, -C::DenormalMin, C::NaN, -C::Zero, C::Zero, C::DenormalMin, C::Min, C::Max ) == false;
    BOOST_CHECK( result17 );

    auto constexpr result18 = IsFinite( C::Lowest, 4, -C::Min, 0.3f );
    BOOST_CHECK( result18 );

    auto constexpr result19 = IsFinite( C::Lowest, C::NaN ) == false;
    BOOST_CHECK( result19 );
}

// --run_test=ConstexprMathTests/FloatIsNormalTest1
BOOST_AUTO_TEST_CASE( FloatIsNormalTest1 )
{
    using C = Constants<float>;

    auto constexpr result1 = IsNormal( C::NaN ) == false;
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsNormal( C::NegativeNaN ) == false;
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsNormal( C::sNaN ) == false;
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsNormal( C::sNegativeNaN ) == false;
    BOOST_CHECK( result4 );
    auto constexpr result5 = IsNormal( C::NegativeInfinity ) == false;
    BOOST_CHECK( result5 );
    auto constexpr result6 = IsNormal( C::Lowest );
    BOOST_CHECK( result6 );
    auto constexpr result7 = IsNormal( -C::Min );
    BOOST_CHECK( result7 );
    auto constexpr result8 = IsNormal( -C::DenormalMin ) == false;
    BOOST_CHECK( result8 );
    auto constexpr result9 = IsNormal( -C::Zero ) == false;
    BOOST_CHECK( result9 );
    auto constexpr result10 = IsNormal( C::Zero ) == false;
    BOOST_CHECK( result10 );
    auto constexpr result11 = IsNormal( C::DenormalMin ) == false;
    BOOST_CHECK( result11 );
    auto constexpr result12 = IsNormal( C::Min );
    BOOST_CHECK( result12 );
    auto constexpr result13 = IsNormal( C::Max );
    BOOST_CHECK( result13 );
    auto constexpr result14 = IsNormal( C::Infinity ) == false;
    BOOST_CHECK( result14 );

    auto constexpr result15 = IsNormal( C::Lowest, -C::Min );
    BOOST_CHECK( result15 );

    auto constexpr result16 = IsNormal( C::Lowest, 0 ,C::Min ) == false;
    BOOST_CHECK( result16 );


}

// --run_test=ConstexprMathTests/DoubleIsNormalTest1
BOOST_AUTO_TEST_CASE( DoubleIsNormalTest1 )
{
    using C = Constants<double>;

    auto constexpr result1 = IsNormal( C::NaN ) == false;
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsNormal( C::NegativeNaN ) == false;
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsNormal( C::sNaN ) == false;
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsNormal( C::sNegativeNaN ) == false;
    BOOST_CHECK( result4 );
    auto constexpr result5 = IsNormal( C::NegativeInfinity ) == false;
    BOOST_CHECK( result5 );
    auto constexpr result6 = IsNormal( C::Lowest );
    BOOST_CHECK( result6 );
    auto constexpr result7 = IsNormal( -C::Min );
    BOOST_CHECK( result7 );
    auto constexpr result8 = IsNormal( -C::DenormalMin ) == false;
    BOOST_CHECK( result8 );
    auto constexpr result9 = IsNormal( -C::Zero ) == false;
    BOOST_CHECK( result9 );
    auto constexpr result10 = IsNormal( C::Zero ) == false;
    BOOST_CHECK( result10 );
    auto constexpr result11 = IsNormal( C::DenormalMin ) == false;
    BOOST_CHECK( result11 );
    auto constexpr result12 = IsNormal( C::Min );
    BOOST_CHECK( result12 );
    auto constexpr result13 = IsNormal( C::Max );
    BOOST_CHECK( result13 );
    auto constexpr result14 = IsNormal( C::Infinity ) == false;
    BOOST_CHECK( result14 );
}


// --run_test=ConstexprMathTests/FloatAbsTest1
BOOST_AUTO_TEST_CASE( FloatAbsTest1 )
{
    using C = Constants<float>;
    
    auto constexpr result1 = IsNaN( Abs( C::NaN ) );
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsNaN( Abs( C::NegativeNaN ) );
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsNaN( Abs( C::sNaN ) );
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsNaN( Abs( C::sNegativeNaN ) );
    BOOST_CHECK( result4 );

    auto constexpr result5 = Abs( C::NegativeInfinity );
    BOOST_CHECK( IsSameValue( result5, C::Infinity ) );
    auto constexpr result6 = Abs( C::Lowest );
    BOOST_CHECK( IsSameValue( result6, C::Max ) );
    auto constexpr result7 = Abs( -C::Min );
    BOOST_CHECK( IsSameValue( result7, C::Min ) );
    auto constexpr result8 = Abs( -C::DenormalMin );
    BOOST_CHECK( IsSameValue( result8, C::DenormalMin ) );
    auto constexpr result9 = Abs( -C::Zero );
    BOOST_CHECK( IsSameValue( result9, C::Zero ) );
}

// --run_test=ConstexprMathTests/DoubleAbsTest1
BOOST_AUTO_TEST_CASE( DoubleAbsTest1 )
{
    using C = Constants<double>;

    auto constexpr result1 = IsNaN( Abs( C::NaN ) );
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsNaN( Abs( C::NegativeNaN ) );
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsNaN( Abs( C::sNaN ) );
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsNaN( Abs( C::sNegativeNaN ) );
    BOOST_CHECK( result4 );

    auto constexpr result5 = Abs( C::NegativeInfinity );
    BOOST_CHECK( IsSameValue( result5, C::Infinity ) );
    auto constexpr result6 = Abs( C::Lowest );
    BOOST_CHECK( IsSameValue( result6, C::Max ) );
    auto constexpr result7 = Abs( -C::Min );
    BOOST_CHECK( IsSameValue( result7, C::Min ) );
    auto constexpr result8 = Abs( -C::DenormalMin );
    BOOST_CHECK( IsSameValue( result8, C::DenormalMin ) );
    auto constexpr result9 = Abs( -C::Zero );
    BOOST_CHECK( IsSameValue( result9, C::Zero ) );
}

// --run_test=ConstexprMathTests/FloatFastAbsTest1
BOOST_AUTO_TEST_CASE( FloatFastAbsTest1 )
{
    using C = Constants<float>;

    auto constexpr result1 = IsNaN( FastAbs( C::NaN ) );
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsNaN( FastAbs( C::NegativeNaN ) );
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsNaN( FastAbs( C::sNaN ) );
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsNaN( FastAbs( C::sNegativeNaN ) );
    BOOST_CHECK( result4 );

    auto constexpr result5 = FastAbs( C::NegativeInfinity );
    BOOST_CHECK( IsSameValue( result5, C::Infinity ) );
    auto constexpr result6 = FastAbs( C::Lowest );
    BOOST_CHECK( IsSameValue( result6, C::Max ) );
    auto constexpr result7 = FastAbs( -C::Min );
    BOOST_CHECK( IsSameValue( result7, C::Min ) );
    auto constexpr result8 = FastAbs( -C::DenormalMin );
    BOOST_CHECK( IsSameValue( result8, C::DenormalMin ) );
    auto constexpr result9 = FastAbs( -C::Zero );
    BOOST_CHECK( IsSameValue( result9, C::Zero ) );
}

// --run_test=ConstexprMathTests/DoubleFastAbsTest1
BOOST_AUTO_TEST_CASE( DoubleFastAbsTest1 )
{
    using C = Constants<double>;

    auto constexpr result1 = IsNaN( FastAbs( C::NaN ) );
    BOOST_CHECK( result1 );
    auto constexpr result2 = IsNaN( FastAbs( C::NegativeNaN ) );
    BOOST_CHECK( result2 );
    auto constexpr result3 = IsNaN( FastAbs( C::sNaN ) );
    BOOST_CHECK( result3 );
    auto constexpr result4 = IsNaN( FastAbs( C::sNegativeNaN ) );
    BOOST_CHECK( result4 );

    auto constexpr result5 = FastAbs( C::NegativeInfinity );
    BOOST_CHECK( IsSameValue( result5, C::Infinity ) );
    auto constexpr result6 = FastAbs( C::Lowest );
    BOOST_CHECK( IsSameValue( result6, C::Max ) );
    auto constexpr result7 = FastAbs( -C::Min );
    BOOST_CHECK( IsSameValue( result7, C::Min ) );
    auto constexpr result8 = FastAbs( -C::DenormalMin );
    BOOST_CHECK( IsSameValue( result8, C::DenormalMin ) );
    auto constexpr result9 = FastAbs( -C::Zero );
    BOOST_CHECK( IsSameValue( result9, C::Zero ) );
}

// --run_test=ConstexprMathTests/FloatSignBitTest1
BOOST_AUTO_TEST_CASE( FloatSignBitTest1 )
{
    using C = Constants<float>;

    auto constexpr result1 = Math::SignBit( C::NaN ) == false;
    BOOST_CHECK( result1 );
    auto constexpr result2 = Math::SignBit( C::NegativeNaN );
    BOOST_CHECK( result2 );
    auto constexpr result3 = Math::SignBit( C::sNaN ) == false;
    BOOST_CHECK( result3 );
    auto constexpr result4 = Math::SignBit( C::sNegativeNaN );
    BOOST_CHECK( result4 );
    auto constexpr result5 = Math::SignBit( C::NegativeInfinity );
    BOOST_CHECK( result5 );
    auto constexpr result6 = Math::SignBit( C::Lowest );
    BOOST_CHECK( result6 );
    auto constexpr result7 = Math::SignBit( -C::Min );
    BOOST_CHECK( result7 );
    auto constexpr result8 = Math::SignBit( -C::DenormalMin );
    BOOST_CHECK( result8 );
    auto constexpr result9 = Math::SignBit( -C::Zero );
    BOOST_CHECK( result9 );
    auto constexpr result10 = Math::SignBit( C::Zero ) == false;
    BOOST_CHECK( result10 );
    auto constexpr result11 = Math::SignBit( C::DenormalMin ) == false;
    BOOST_CHECK( result11 );
    auto constexpr result12 = Math::SignBit( C::Min ) == false;
    BOOST_CHECK( result12 );
    auto constexpr result13 = Math::SignBit( C::Max ) == false;
    BOOST_CHECK( result13 );
    auto constexpr result14 = Math::SignBit( C::Infinity ) == false;
    BOOST_CHECK( result14 );
}

// --run_test=ConstexprMathTests/DoubleSignBitTest1
BOOST_AUTO_TEST_CASE( DoubleSignBitTest1 )
{
    using C = Constants<double>;

    auto constexpr result1 = Math::SignBit( C::NaN ) == false;
    BOOST_CHECK( result1 );
    auto constexpr result2 = Math::SignBit( C::NegativeNaN );
    BOOST_CHECK( result2 );
    auto constexpr result3 = Math::SignBit( C::sNaN ) == false;
    BOOST_CHECK( result3 );
    auto constexpr result4 = Math::SignBit( C::sNegativeNaN );
    BOOST_CHECK( result4 );
    auto constexpr result5 = Math::SignBit( C::NegativeInfinity );
    BOOST_CHECK( result5 );
    auto constexpr result6 = Math::SignBit( C::Lowest );
    BOOST_CHECK( result6 );
    auto constexpr result7 = Math::SignBit( -C::Min );
    BOOST_CHECK( result7 );
    auto constexpr result8 = Math::SignBit( -C::DenormalMin );
    BOOST_CHECK( result8 );
    auto constexpr result9 = Math::SignBit( -C::Zero );
    BOOST_CHECK( result9 );
    auto constexpr result10 = Math::SignBit( C::Zero ) == false;
    BOOST_CHECK( result10 );
    auto constexpr result11 = Math::SignBit( C::DenormalMin ) == false;
    BOOST_CHECK( result11 );
    auto constexpr result12 = Math::SignBit( C::Min ) == false;
    BOOST_CHECK( result12 );
    auto constexpr result13 = Math::SignBit( C::Max ) == false;
    BOOST_CHECK( result13 );
    auto constexpr result14 = Math::SignBit( C::Infinity ) == false;
    BOOST_CHECK( result14 );
}

// --run_test=ConstexprMathTests/FloatFRExpTest1
BOOST_AUTO_TEST_CASE( FloatFRExpTest1 )
{
    using C = Constants<float>;

    auto Check = []( const std::pair<C::ValueType, int> result, C::ValueType first, int second ) -> bool
        {
            return IsSameValue( result.first, first ) && IsSameValue( result.second, second );
        };


    auto constexpr result1 = FRExp( C::NaN );
    BOOST_CHECK( Check(result1, C::NaN, 0 ) );
    auto constexpr result2 = FRExp( C::NegativeNaN );
    BOOST_CHECK( Check( result2, C::NegativeNaN, 0 ) );
    auto constexpr result3 = FRExp( C::sNaN );
    BOOST_CHECK( Check( result3, C::sNaN, 0 ) );
    auto constexpr result4 = FRExp( C::sNegativeNaN );
    BOOST_CHECK( Check( result4, C::sNegativeNaN, 0 ) );
    auto constexpr result5 = FRExp( C::NegativeInfinity );
    BOOST_CHECK( Check( result5, C::NegativeInfinity, 0 ) );
    auto constexpr result6 = FRExp( C::Lowest );
    BOOST_CHECK( Check( result6, -0.99999994f, 128 ) );
    auto constexpr result7 = FRExp( -C::Min );
    BOOST_CHECK( Check( result7, -0.5f, -125 ) );
    auto constexpr result8 = FRExp( -C::DenormalMin );
    BOOST_CHECK( Check( result8, -0.5f, -148 ) );
    auto constexpr result9 = FRExp( -C::Zero );
    BOOST_CHECK( Check( result9, -0.f, 0 ) );
    auto constexpr result10 = FRExp( C::Zero );
    BOOST_CHECK( Check( result10, 0.f, 0 ) );
    auto constexpr result11 = FRExp( C::DenormalMin );
    BOOST_CHECK( Check( result11, 0.5f, -148 ) );
    auto constexpr result12 = FRExp( C::Min );
    BOOST_CHECK( Check( result12, 0.5f, -125 ) );
    auto constexpr result13 = FRExp( C::Max );
    BOOST_CHECK( Check( result13, 0.99999994f, 128 ) );
    auto constexpr result14 = FRExp( C::Infinity );
    BOOST_CHECK( Check( result14, C::Infinity, 0 ) );
}

// --run_test=ConstexprMathTests/DoubleFRExpTest1
BOOST_AUTO_TEST_CASE( DoubleFRExpTest1 )
{
    using C = Constants<double>;

    auto Check = []( const std::pair<C::ValueType, int> result, C::ValueType first, int second ) -> bool
        {
            return IsSameValue( result.first, first ) && IsSameValue( result.second, second );
        };


    auto constexpr result1 = FRExp( C::NaN );
    BOOST_CHECK( Check( result1, C::NaN, 0 ) );
    auto constexpr result2 = FRExp( C::NegativeNaN );
    BOOST_CHECK( Check( result2, C::NegativeNaN, 0 ) );
    auto constexpr result3 = FRExp( C::sNaN );
    BOOST_CHECK( Check( result3, C::sNaN, 0 ) );
    auto constexpr result4 = FRExp( C::sNegativeNaN );
    BOOST_CHECK( Check( result4, C::sNegativeNaN, 0 ) );
    auto constexpr result5 = FRExp( C::NegativeInfinity );
    BOOST_CHECK( Check( result5, C::NegativeInfinity, 0 ) );
    auto constexpr result6 = FRExp( C::Lowest );
    BOOST_CHECK( Check( result6, -0.99999999999999989, 1024 ) );
    auto constexpr result7 = FRExp( -C::Min );
    BOOST_CHECK( Check( result7, -0.5, -1021 ) );
    auto constexpr result8 = FRExp( -C::DenormalMin );
    BOOST_CHECK( Check( result8, -0.5, -1073 ) );
    auto constexpr result9 = FRExp( -C::Zero );
    BOOST_CHECK( Check( result9, -0., 0 ) );
    auto constexpr result10 = FRExp( C::Zero );
    BOOST_CHECK( Check( result10, 0., 0 ) );
    auto constexpr result11 = FRExp( C::DenormalMin );
    BOOST_CHECK( Check( result11, 0.5, -1073 ) );
    auto constexpr result12 = FRExp( C::Min );
    BOOST_CHECK( Check( result12, 0.5, -1021 ) );
    auto constexpr result13 = FRExp( C::Max );
    BOOST_CHECK( Check( result13, 0.99999999999999989, 1024 ) );
    auto constexpr result14 = FRExp( C::Infinity );
    BOOST_CHECK( Check( result14, C::Infinity, 0 ) );
}


// --run_test=ConstexprMathTests/FloatModFTest1
BOOST_AUTO_TEST_CASE( FloatModFTest1 )
{
    using C = Constants<float>;

    auto Check = []( const std::pair<C::ValueType, C::ValueType > result, C::ValueType first, C::ValueType second ) -> bool
        {
            return IsSameValue( result.first, first ) && IsSameValue( result.second, second );
        };

    auto CheckIsNaN = []( const std::pair<C::ValueType, C::ValueType > result ) -> bool
        {
            return IsNaN( result.first ) && IsNaN( result.second );
        };


    auto constexpr result1 = ModF( C::NaN );
    BOOST_CHECK( CheckIsNaN( result1 ) );
    auto constexpr result2 = ModF( C::NegativeNaN );
    BOOST_CHECK( CheckIsNaN( result2 ) );
    auto constexpr result3 = ModF( C::sNaN );
    BOOST_CHECK( CheckIsNaN( result3 ) );
    auto constexpr result4 = ModF( C::sNegativeNaN );
    BOOST_CHECK( CheckIsNaN( result4 ) );

    auto constexpr result5 = ModF( C::NegativeInfinity );
    BOOST_CHECK( Check( result5, C::NegativeInfinity, -0.f ) );
    auto constexpr result6 = ModF( C::Lowest );
    BOOST_CHECK( Check( result6, -3.40282347e+38f, -0.f ) );
    auto constexpr result7 = ModF( -C::Min );
    BOOST_CHECK( Check( result7, -0.f, -1.17549435e-38f ) );
    auto constexpr result8 = ModF( -C::DenormalMin );
    BOOST_CHECK( Check( result8, -0.f, -1.401e-45f ) );
    auto constexpr result9 = ModF( -C::Zero );
    BOOST_CHECK( Check( result9, -0.f, -0.f ) );
    auto constexpr result10 = ModF( C::Zero );
    BOOST_CHECK( Check( result10, 0.f, 0.f ) );
    auto constexpr result11 = ModF( C::DenormalMin );
    BOOST_CHECK( Check( result11, 0.f, 1.401e-45f ) );
    auto constexpr result12 = ModF( C::Min );
    BOOST_CHECK( Check( result12, 0.f, 1.17549435e-38f ) );
    auto constexpr result13 = ModF( C::Max );
    BOOST_CHECK( Check( result13, 3.40282347e+38f, 0.f ) );
    auto constexpr result14 = ModF( C::Infinity );
    BOOST_CHECK( Check( result14, C::Infinity, 0.f ) );
}

// --run_test=ConstexprMathTests/DoubleModFTest1
BOOST_AUTO_TEST_CASE( DoubleModFTest1 )
{
    using C = Constants<double>;

    auto Check = []( const std::pair<C::ValueType, C::ValueType > result, C::ValueType first, C::ValueType second ) -> bool
        {
            return IsSameValue( result.first, first ) && IsSameValue( result.second, second );
        };

    auto CheckIsNaN = []( const std::pair<C::ValueType, C::ValueType > result ) -> bool
        {
            return IsNaN( result.first ) && IsNaN( result.second );
        };


    auto constexpr result1 = ModF( C::NaN );
    BOOST_CHECK( CheckIsNaN( result1 ) );
    auto constexpr result2 = ModF( C::NegativeNaN );
    BOOST_CHECK( CheckIsNaN( result2 ) );
    auto constexpr result3 = ModF( C::sNaN );
    BOOST_CHECK( CheckIsNaN( result3 ) );
    auto constexpr result4 = ModF( C::sNegativeNaN );
    BOOST_CHECK( CheckIsNaN( result4 ) );

    auto constexpr result5 = ModF( C::NegativeInfinity );
    BOOST_CHECK( Check( result5, C::NegativeInfinity, -0.f ) );
    auto constexpr result6 = ModF( C::Lowest );
    BOOST_CHECK( Check( result6, -1.7976931348623157e+308, -0. ) );
    auto constexpr result7 = ModF( -C::Min );
    BOOST_CHECK( Check( result7, -0., -2.2250738585072014e-308 ) );
    auto constexpr result8 = ModF( -C::DenormalMin );
    BOOST_CHECK( Check( result8, -0., -4.940656458412e-324 ) );
    auto constexpr result9 = ModF( -C::Zero );
    BOOST_CHECK( Check( result9, -0., -0. ) );
    auto constexpr result10 = ModF( C::Zero );
    BOOST_CHECK( Check( result10, 0., 0. ) );
    auto constexpr result11 = ModF( C::DenormalMin );
    BOOST_CHECK( Check( result11, 0.f, 4.940656458412e-324 ) );
    auto constexpr result12 = ModF( C::Min );
    BOOST_CHECK( Check( result12, 0.f, 2.2250738585072014e-308 ) );
    auto constexpr result13 = ModF( C::Max );
    BOOST_CHECK( Check( result13, 1.7976931348623157e+308, 0.f ) );
    auto constexpr result14 = ModF( C::Infinity );
    BOOST_CHECK( Check( result14, C::Infinity, 0. ) );
}




// --run_test=ConstexprMathTests/FloatMinTest1
BOOST_AUTO_TEST_CASE( FloatMinTest1 )
{
    using C = Constants<float>;

    constexpr auto minValue = Math::Min( 5.f, 4.f, 3.f, 4.f, 4.f );
    constexpr bool equal = minValue == 3.f;
    BOOST_CHECK( equal );

    constexpr auto check1 = Min( C::Infinity, C::NegativeInfinity ) == C::NegativeInfinity;
    BOOST_CHECK( check1 );

    constexpr auto check2 = Min( C::NaN, C::NegativeInfinity ) == C::NegativeInfinity;
    BOOST_CHECK( check2 );

    constexpr auto check3 = Min( C::NegativeInfinity, C::NaN ) == C::NegativeInfinity;
    BOOST_CHECK( check3 );

    constexpr auto check4 = IsSameValue( Min( C::Zero, -C::Zero ), -C::Zero );
    BOOST_CHECK( check4 );

    constexpr auto check5 = IsSameValue( Min( -C::Zero, C::Zero ), -C::Zero );
    BOOST_CHECK( check5 );

}

// --run_test=ConstexprMathTests/DoubleMinTest1
BOOST_AUTO_TEST_CASE( DoubleMinTest1 )
{
    constexpr auto minValue = Math::Min( 5., 4., 3., 4., 4. );
    constexpr bool equal = minValue == 3.;
    BOOST_CHECK( equal );
}


// --run_test=ConstexprMathTests/FloatMaxTest1
BOOST_AUTO_TEST_CASE( FloatMaxTest1 )
{
    using C = Constants<float>;
    constexpr auto minValue = Math::Max( 5.f, 4.f, 3.f, 4.f, 4.f );
    constexpr bool equal = minValue == 5.f;
    BOOST_CHECK( equal );

    constexpr auto check1 = Max( C::Infinity, C::NegativeInfinity ) == C::Infinity;
    BOOST_CHECK( check1 );

    constexpr auto check2 = Max( C::NaN, C::NegativeInfinity ) == C::NegativeInfinity;
    BOOST_CHECK( check2 );

    constexpr auto check3 = Max( C::NegativeInfinity, C::NaN  ) == C::NegativeInfinity;
    BOOST_CHECK( check3 );

    constexpr auto check4 = IsSameValue(Max( C::Zero, -C::Zero ), C::Zero );
    BOOST_CHECK( check4 );

    constexpr auto check5 = IsSameValue( Max( -C::Zero, C::Zero ), C::Zero );
    BOOST_CHECK( check5 );


}

// --run_test=ConstexprMathTests/DoubleMaxTest1
BOOST_AUTO_TEST_CASE( DoubleMaxTest1 )
{
    constexpr auto minValue = Math::Max( 5., 4., 3., 4., 4. );
    constexpr bool equal = minValue == 5.;
    BOOST_CHECK( equal );
}


// --run_test=ConstexprMathTests/FloatFloorTest1
BOOST_AUTO_TEST_CASE( FloatFloorTest1 )
{
    constexpr float value1 = -1.5f;
    constexpr float value2 = -0.5f;
    constexpr float value3 = -0.0f;
    constexpr float value4 = 0.0f;
    constexpr float value5 = 0.5f;
    constexpr float value6 = 1.5f;

    constexpr double result1 = Floor( value1 );
    BOOST_CHECK( result1 == -2.f );
    constexpr double result2 = Floor( value2 );
    BOOST_CHECK( result2 == -1.f );
    constexpr double result3 = Floor( value3 );
    BOOST_CHECK( result3 == -0.f );
    constexpr double result4 = Floor( value4 );
    BOOST_CHECK( result4 == 0.f );
    constexpr double result5 = Floor( value5 );
    BOOST_CHECK( result5 == 0.f );
    constexpr double result6 = Floor( value6 );
    BOOST_CHECK( result6 == 1.f );
}

// --run_test=ConstexprMathTests/DoubleFloorTest1
BOOST_AUTO_TEST_CASE( DoubleFloorTest1 )
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

// --run_test=ConstexprMathTests/OpenLibMFloorDoubleTest1
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

// --run_test=ConstexprMathTests/FloatCeilTest1
BOOST_AUTO_TEST_CASE( FloatCeilTest1 )
{
    constexpr float value1 = -1.5f;
    constexpr float value2 = -0.5f;
    constexpr float value3 = -0.0f;
    constexpr float value4 = 0.0f;
    constexpr float value5 = 0.5f;
    constexpr float value6 = 1.5f;

    constexpr double result1 = Ceil( value1 );
    BOOST_CHECK( result1 == -1.f );
    constexpr double result2 = Ceil( value2 );
    BOOST_CHECK( result2 == -0.f );
    constexpr double result3 = Ceil( value3 );
    BOOST_CHECK( result3 == -0.f );
    constexpr double result4 = Ceil( value4 );
    BOOST_CHECK( result4 == 0.f );
    constexpr double result5 = Ceil( value5 );
    BOOST_CHECK( result5 == 1.f );
    constexpr double result6 = Ceil( value6 );
    BOOST_CHECK( result6 == 2.f );
}


// --run_test=ConstexprMathTests/DoubleCeilTest1
BOOST_AUTO_TEST_CASE( DoubleCeilTest1 )
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

// --run_test=ConstexprMathTests/OpenLibMCeilDoubleTest1
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

// --run_test=ConstexprMathTests/FloatTruncTest1
BOOST_AUTO_TEST_CASE( FloatTruncTest1 )
{
    constexpr float value1 = -1.5f;
    constexpr float value2 = -0.5f;
    constexpr float value3 = -0.0f;
    constexpr float value4 = 0.0f;
    constexpr float value5 = 0.5f;
    constexpr float value6 = 1.5f;

    constexpr double result1 = Trunc( value1 );
    BOOST_CHECK( result1 == -1.f );
    constexpr double result2 = Trunc( value2 );
    BOOST_CHECK( result2 == -0.f );
    constexpr double result3 = Trunc( value3 );
    BOOST_CHECK( result3 == -0.f );
    constexpr double result4 = Trunc( value4 );
    BOOST_CHECK( result4 == 0.f );
    constexpr double result5 = Trunc( value5 );
    BOOST_CHECK( result5 == 0.f );
    constexpr double result6 = Trunc( value6 );
    BOOST_CHECK( result6 == 1.f );
}

// --run_test=ConstexprMathTests/DoubleTruncTest1
BOOST_AUTO_TEST_CASE( DoubleTruncTest1 )
{
    constexpr double value1 = -1.5;
    constexpr double value2 = -0.5;
    constexpr double value3 = -0.0;
    constexpr double value4 = 0.0;
    constexpr double value5 = 0.5;
    constexpr double value6 = 1.5;

    constexpr double result1 = Trunc( value1 );
    BOOST_CHECK( result1 == -1. );
    constexpr double result2 = Trunc( value2 );
    BOOST_CHECK( result2 == -0. );
    constexpr double result3 = Trunc( value3 );
    BOOST_CHECK( result3 == -0. );
    constexpr double result4 = Trunc( value4 );
    BOOST_CHECK( result4 == 0. );
    constexpr double result5 = Trunc( value5 );
    BOOST_CHECK( result5 == 0. );
    constexpr double result6 = Trunc( value6 );
    BOOST_CHECK( result6 == 1. );
}

// --run_test=ConstexprMathTests/FloatRoundTest1
BOOST_AUTO_TEST_CASE( FloatRoundTest1 )
{
    constexpr float value1 = -1.5f;
    constexpr float value2 = -0.5f;
    constexpr float value3 = -0.0f;
    constexpr float value4 = 0.0f;
    constexpr float value5 = 0.5f;
    constexpr float value6 = 1.5f;

    constexpr double result1 = Round( value1 );
    BOOST_CHECK( result1 == -2.f );
    constexpr double result2 = Round( value2 );
    BOOST_CHECK( result2 == -1.f );
    constexpr double result3 = Round( value3 );
    BOOST_CHECK( result3 == -0.f );
    constexpr double result4 = Round( value4 );
    BOOST_CHECK( result4 == 0.f );
    constexpr double result5 = Round( value5 );
    BOOST_CHECK( result5 == 1.f );
    constexpr double result6 = Round( value6 );
    BOOST_CHECK( result6 == 2.f );
}

// --run_test=ConstexprMathTests/DoubleRoundTest1
BOOST_AUTO_TEST_CASE( DoubleRoundTest1 )
{
    constexpr double value1 = -1.5;
    constexpr double value2 = -0.5;
    constexpr double value3 = -0.0;
    constexpr double value4 = 0.0;
    constexpr double value5 = 0.5;
    constexpr double value6 = 1.5;

    constexpr double result1 = Round( value1 );
    BOOST_CHECK( result1 == -2. );
    constexpr double result2 = Round( value2 );
    BOOST_CHECK( result2 == -1. );
    constexpr double result3 = Round( value3 );
    BOOST_CHECK( result3 == -0. );
    constexpr double result4 = Round( value4 );
    BOOST_CHECK( result4 == 0. );
    constexpr double result5 = Round( value5 );
    BOOST_CHECK( result5 == 1. );
    constexpr double result6 = Round( value6 );
    BOOST_CHECK( result6 == 2. );
}

// --run_test=ConstexprMathTests/FloatClampTest1
BOOST_AUTO_TEST_CASE( FloatClampTest1 )
{
    constexpr float result1 = Clamp( -1.f, 0.f, 10.f );
    BOOST_CHECK( result1 == 0.f );
    constexpr float result2 = Clamp( 11.f, 0.f, 10.f );
    BOOST_CHECK( result2 == 10.f );
    constexpr float result3 = Clamp( 5.f, 0.f, 10.f );
    BOOST_CHECK( result3 == 5.f );
}

// --run_test=ConstexprMathTests/DoubleClampTest1
BOOST_AUTO_TEST_CASE( DoublelampTest1 )
{
    constexpr double result1 = Clamp( -1., 0., 10. );
    BOOST_CHECK( result1 == 0. );
    constexpr double result2 = Clamp( 11., 0., 10. );
    BOOST_CHECK( result2 == 10. );
    constexpr double result3 = Clamp( 5., 0., 10. );
    BOOST_CHECK( result3 == 5. );
}

// --run_test=ConstexprMathTests/FloatLerpTest1
BOOST_AUTO_TEST_CASE( FloatLerpTest1 )
{
    constexpr auto result1 = Lerp( 3.f, 5.f, 0.5f );
    BOOST_CHECK( result1 == 4.f );
    constexpr auto result2 = Lerp( 3.f, 5.f, -0.5f );
    BOOST_CHECK( result2 == 2.f );
    constexpr auto result3 = Lerp( 3.f, 5.f, 1.5f );
    BOOST_CHECK( result3 == 6.f );
    constexpr auto result4 = Lerp( 3.f, 5.f, 0.f );
    BOOST_CHECK( result4 == 3.f );
    constexpr auto result5 = Lerp( 3.f, 5.f, 1.f );
    BOOST_CHECK( result5 == 5.f );
}

// --run_test=ConstexprMathTests/DoubleLerpTest1
BOOST_AUTO_TEST_CASE( DoubleLerpTest1 )
{
    constexpr auto result1 = Lerp( 3., 5., 0.5 );
    BOOST_CHECK( result1 == 4.f );
    constexpr auto result2 = Lerp( 3., 5., -0.5 );
    BOOST_CHECK( result2 == 2.f );
    constexpr auto result3 = Lerp( 3., 5., 1.5 );
    BOOST_CHECK( result3 == 6.f );
    constexpr auto result4 = Lerp( 3., 5., 0. );
    BOOST_CHECK( result4 == 3.f );
    constexpr auto result5 = Lerp( 3., 5., 1. );
    BOOST_CHECK( result5 == 5.f );
}

// --run_test=ConstexprMathTests/FloatCopySignTest1
BOOST_AUTO_TEST_CASE( FloatCopySignTest1 )
{
    using C = Constants<float>;

    constexpr auto result1 = CopySign( C::One, C::sNegativeNaN );
    BOOST_CHECK( result1 == -C::One );

    constexpr auto result2 = CopySign( C::One, C::NegativeNaN );
    BOOST_CHECK( result2 == -C::One );

    constexpr auto result3 = CopySign( C::One, C::NegativeInfinity );
    BOOST_CHECK( result3 == -C::One );

    constexpr auto result4 = CopySign( C::sNegativeNaN, C::One );
    BOOST_CHECK( IsNaN( result4 ) );

    constexpr auto result5 = CopySign( C::NegativeNaN, C::One );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = CopySign( C::NegativeInfinity, C::One );
    BOOST_CHECK( result6 == C::Infinity );

    constexpr auto result7 = CopySign( C::Infinity, -C::One );
    BOOST_CHECK( result7 == C::NegativeInfinity );

    constexpr auto result8 = CopySign( C::Max, -C::One );
    BOOST_CHECK( result8 == C::Lowest );

    constexpr auto result9 = CopySign( C::Lowest, C::One );
    BOOST_CHECK( result9 == C::Max );

    constexpr auto result10 = CopySign( C::DenormalMin, -C::One );
    BOOST_CHECK( result10 == -C::DenormalMin );

    constexpr auto result11 = CopySign( -C::DenormalMin, C::One );
    BOOST_CHECK( result11 == C::DenormalMin );

    
}


// --run_test=ConstexprMathTests/DoubleCopySignTest1
BOOST_AUTO_TEST_CASE( DoubleCopySignTest1 )
{
    using C = Constants<double>;

    constexpr auto result1 = CopySign( C::One, C::sNegativeNaN );
    BOOST_CHECK( result1 == -C::One );

    constexpr auto result2 = CopySign( C::One, C::NegativeNaN );
    BOOST_CHECK( result2 == -C::One );

    constexpr auto result3 = CopySign( C::One, C::NegativeInfinity );
    BOOST_CHECK( result3 == -C::One );

    constexpr auto result4 = CopySign( C::sNegativeNaN, C::One );
    BOOST_CHECK( IsNaN( result4 ) );

    constexpr auto result5 = CopySign( C::NegativeNaN, C::One );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = CopySign( C::NegativeInfinity, C::One );
    BOOST_CHECK( result6 == C::Infinity );

    constexpr auto result7 = CopySign( C::Infinity, -C::One );
    BOOST_CHECK( result7 == C::NegativeInfinity );

    constexpr auto result8 = CopySign( C::Max, -C::One );
    BOOST_CHECK( result8 == C::Lowest );

    constexpr auto result9 = CopySign( C::Lowest, C::One );
    BOOST_CHECK( result9 == C::Max );

    constexpr auto result10 = CopySign( C::DenormalMin, -C::One );
    BOOST_CHECK( result10 == -C::DenormalMin );

    constexpr auto result11 = CopySign( -C::DenormalMin, C::One );
    BOOST_CHECK( result11 == C::DenormalMin );
}

// --run_test=ConstexprMathTests/FloatScaleByNTest1
BOOST_AUTO_TEST_CASE( FloatScaleByNTest1 )
{
    using C = Constants<float>;
    
    constexpr auto result1 = ScaleBN( C::NaN, C::Two );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = ScaleBN( C::Infinity, C::Two );
    BOOST_CHECK( IsInf( result2 ) );

    constexpr auto result3 = ScaleBN( C::Max, C::Two );
    BOOST_CHECK( IsInf( result3 ) );

    constexpr auto result4 = ScaleBN( -C::Max, C::Two );
    BOOST_CHECK( IsInf( result4 ) );

    auto result5 = std::scalbn( -C::Max, C::Two );
    BOOST_CHECK( IsInf( result5 ) );
    BOOST_CHECK( result4 == result5 );

    constexpr auto result6 = ScaleBN( -C::Max, C::Three );
    BOOST_CHECK( IsInf( result6 ) );

    auto result7 = std::scalbn( -C::Max, C::Three );
    BOOST_CHECK( IsInf( result7 ) );
    BOOST_CHECK( result6 == result7 );

    constexpr auto result8 = ScaleBN( C::Two, C::Two );
    BOOST_CHECK( result8 == 8.f );

    constexpr auto result9 = ScaleBN( -C::Two, C::Two );
    BOOST_CHECK( result9 == -8.f );
}

// --run_test=ConstexprMathTests/DoubleScaleByNTest1
BOOST_AUTO_TEST_CASE( DoubleScaleByNTest1 )
{
    using C = Constants<double>;

    constexpr auto result1 = ScaleBN( C::NaN, C::Two );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = ScaleBN( C::Infinity, C::Two );
    BOOST_CHECK( IsInf( result2 ) );

    constexpr auto result3 = ScaleBN( C::Max, C::Two );
    BOOST_CHECK( IsInf( result3 ) );

    constexpr auto result4 = ScaleBN( -C::Max, C::Two );
    BOOST_CHECK( IsInf( result4 ) );

    auto result5 = std::scalbn( -C::Max, C::Two );
    BOOST_CHECK( IsInf( result5 ) );
    BOOST_CHECK( result4 == result5 );

    constexpr auto result6 = ScaleBN( -C::Max, C::Three );
    BOOST_CHECK( IsInf( result6 ) );

    auto result7 = std::scalbn( -C::Max, C::Three );
    BOOST_CHECK( IsInf( result7 ) );
    BOOST_CHECK( result6 == result7 );

    constexpr auto result8 = ScaleBN( C::Two, C::Two );
    BOOST_CHECK( result8 == 8. );

    constexpr auto result9 = ScaleBN( -C::Two, C::Two );
    BOOST_CHECK( result9 == -8. );
}


// --run_test=ConstexprMathTests/FloatFModTest1
BOOST_AUTO_TEST_CASE( FloatFModTest1 )
{
    using C = Constants<float>;
    
    constexpr auto result1 = FMod( C::NaN, C::Two );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = FMod( C::sNaN, C::Two );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = FMod( C::NegativeNaN, C::Two );
    BOOST_CHECK( IsNaN( result3 ) );

    constexpr auto result4 = FMod( C::sNegativeNaN, C::Two );
    BOOST_CHECK( IsNaN( result4 ) );

    constexpr auto result5 = FMod( C::Two, C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = FMod( C::Two, C::Infinity );
    BOOST_CHECK( result6 == C::Two );

    constexpr auto result7 = FMod( C::Two, C::Max );
    BOOST_CHECK( result7 == C::Two );

    constexpr auto result8 = FMod( C::Two, C::Three );
    BOOST_CHECK( result8 == C::Two );

    constexpr auto result9 = FMod( C::Three, C::Two );
    BOOST_CHECK( result9 == C::One );

    constexpr auto result10 = FMod( C::Three + .5f, C::Two );
    BOOST_CHECK( result10 == 1.5f );

    constexpr auto result11 = FMod( (C::Pi * 3)+C::PiOver4, C::Pi );
    constexpr auto equal11 = AreNearlyEqual( result11, C::PiOver4 );
    BOOST_CHECK( equal11 );
}

// --run_test=ConstexprMathTests/DoubleFModTest1
BOOST_AUTO_TEST_CASE( DoubleFModTest1 )
{
    using C = Constants<double>;

    constexpr auto result1 = FMod( C::NaN, C::Two );
    BOOST_CHECK( IsNaN( result1 ) );

    constexpr auto result2 = FMod( C::sNaN, C::Two );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = FMod( C::NegativeNaN, C::Two );
    BOOST_CHECK( IsNaN( result3 ) );

    constexpr auto result4 = FMod( C::sNegativeNaN, C::Two );
    BOOST_CHECK( IsNaN( result4 ) );

    constexpr auto result5 = FMod( C::Two, C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = FMod( C::Two, C::Infinity );
    BOOST_CHECK( result6 == C::Two );

    constexpr auto result7 = FMod( C::Two, C::Max );
    BOOST_CHECK( result7 == C::Two );

    constexpr auto result8 = FMod( C::Two, C::Three );
    BOOST_CHECK( result8 == C::Two );

    constexpr auto result9 = FMod( C::Three, C::Two );
    BOOST_CHECK( result9 == C::One );

    constexpr auto result10 = FMod( C::Three + .5, C::Two );
    BOOST_CHECK( result10 == 1.5 );

    constexpr auto result11 = FMod( ( C::Pi * 3 ) + C::PiOver4, C::Pi );
    constexpr auto equal11 = AreNearlyEqual( result11, C::PiOver4 );
    BOOST_CHECK( equal11 );
}

// --run_test=ConstexprMathTests/FloatExpTest1
BOOST_AUTO_TEST_CASE( FloatExpTest1 )
{
    using C = Constants<float>;

    constexpr auto result1 = Exp( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Exp( C::NegativeInfinity );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Exp( C::Zero );
    BOOST_CHECK( result3 == 1 );

    constexpr auto result4 = Exp( -C::Zero );
    BOOST_CHECK( result4 == 1 );

    constexpr auto result5 = Exp( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Exp( C::One );
    BOOST_CHECK( result6 == C::E );

    constexpr auto result7 = Exp( C::Two );
    BOOST_CHECK( result7 == C::E2 );

    constexpr auto result8 = Exp( C::Three );
    BOOST_CHECK( result8 == C::E3 );

    constexpr auto result9 = Exp( .7f );
    BOOST_CHECK( result9 == 2.01375270f );

    constexpr auto result10 = Exp( 50.f );
    BOOST_CHECK( result10 == 5.18470546e+21f );
}

// --run_test=ConstexprMathTests/DoubleExpTest1
BOOST_AUTO_TEST_CASE( DoubleExpTest1 )
{
    using C = Constants<double>;

    constexpr auto result1 = Exp( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Exp( C::NegativeInfinity );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Exp( C::Zero );
    BOOST_CHECK( result3 == 1 );

    constexpr auto result4 = Exp( -C::Zero );
    BOOST_CHECK( result4 == 1 );

    constexpr auto result5 = Exp( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Exp( C::One );
    BOOST_CHECK( result6 == C::E );

    constexpr auto result7 = Exp( C::Two );
    constexpr auto equal7 = AreNearlyEqual( result7, C::E2 );
    BOOST_CHECK( equal7 );

    constexpr auto result8 = Exp( C::Three );
    constexpr auto equal8 = AreNearlyEqual( result8, C::E3 );
    BOOST_CHECK( equal8 );

    constexpr auto result9 = Exp( .7 );
    constexpr auto equal9 = AreNearlyEqual( result9, 2.0137527074704765216 );
    BOOST_CHECK( equal9 );

    constexpr auto result10 = Exp( 50. );
    constexpr auto equal10 = AreNearlyEqual( result10, 5184705528587072464087.45332293348538 );
    BOOST_CHECK( equal10 );
}

// --run_test=ConstexprMathTests/FloatExp2Test1
BOOST_AUTO_TEST_CASE( FloatExp2Test1 )
{
    using C = Constants<float>;

    constexpr auto result1 = Exp2( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Exp2( C::NegativeInfinity );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Exp2( C::Zero );
    BOOST_CHECK( result3 == 1 );

    constexpr auto result4 = Exp2( -C::Zero );
    BOOST_CHECK( result4 == 1 );

    constexpr auto result5 = Exp2( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Exp2( C::One );
    BOOST_CHECK( result6 == 2.f );

    constexpr auto result7 = Exp2( C::Two );
    BOOST_CHECK( result7 == 4.f );

    constexpr auto result8 = Exp2( C::Three );
    BOOST_CHECK( result8 == 8.f );

    constexpr auto result9 = Exp2( .7f );
    BOOST_CHECK( result9 == 1.62450480f );
}

// --run_test=ConstexprMathTests/DoubleExp2Test1
BOOST_AUTO_TEST_CASE( DoubleExp2Test1 )
{
    using C = Constants<double>;

    constexpr auto result1 = Exp2( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Exp2( C::NegativeInfinity );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Exp2( C::Zero );
    BOOST_CHECK( result3 == 1 );

    constexpr auto result4 = Exp2( -C::Zero );
    BOOST_CHECK( result4 == 1 );

    constexpr auto result5 = Exp2( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Exp2( C::One );
    
    constexpr auto equal6 = AreNearlyEqual( result6, 2. );
    BOOST_CHECK( equal6 );

    constexpr auto result7 = Exp2( C::Two );
    constexpr auto equal7 = AreNearlyEqual( result7, 4. );
    BOOST_CHECK( equal7 );

    constexpr auto result8 = Exp2( C::Three );
    constexpr auto equal8 = AreNearlyEqual( result8, 8. );
    BOOST_CHECK( equal8 );

    constexpr auto result9 = Exp2( .7 );
    constexpr auto equal9 = AreNearlyEqual( result9, 1.6245047927124710452 );
    BOOST_CHECK( equal9 );
}




// --run_test=ConstexprMathTests/FloatExp10Test1
BOOST_AUTO_TEST_CASE( FloatExp10Test1 )
{
    using C = Constants<float>;

    constexpr auto result1 = Exp10( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Exp10( C::NegativeInfinity );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Exp10( C::Zero );
    BOOST_CHECK( result3 == 1 );

    constexpr auto result4 = Exp10( -C::Zero );
    BOOST_CHECK( result4 == 1 );

    constexpr auto result5 = Exp10( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Exp10( C::One );
    constexpr auto equal6 = AreNearlyEqual( result6, 10.f );
    BOOST_CHECK( equal6 );

    constexpr auto result7 = Exp10( C::Two );
    constexpr auto equal7 = AreNearlyEqual( result7, 100.f );
    BOOST_CHECK( equal7 );

    constexpr auto result8 = Exp10( C::Three );
    constexpr auto equal8 = AreNearlyEqual( result8, 1000.f, 1.e-3f );
    BOOST_CHECK( equal8 );

    
    
    constexpr auto result9 = Exp10( .7f );
    constexpr auto equal9 = AreNearlyEqual( result9, 5.0118723362727228500155418688494574f );
    BOOST_CHECK( equal9 );
}

// --run_test=ConstexprMathTests/DoubleExp10Test1
BOOST_AUTO_TEST_CASE( DoubleExp10Test1 )
{
    using C = Constants<double>;

    constexpr auto result1 = Exp10( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Exp10( C::NegativeInfinity );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Exp10( C::Zero );
    BOOST_CHECK( result3 == 1 );

    constexpr auto result4 = Exp10( -C::Zero );
    BOOST_CHECK( result4 == 1 );

    constexpr auto result5 = Exp10( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Exp10( C::One );
    constexpr auto equal6 = AreNearlyEqual( result6, 10. );
    BOOST_CHECK( equal6 );

    constexpr auto result7 = Exp10( C::Two );
    constexpr auto equal7 = AreNearlyEqual( result7, 100. );
    BOOST_CHECK( equal7 );

    constexpr auto result8 = Exp10( C::Three );
    constexpr auto equal8 = AreNearlyEqual( result8, 1000. );
    BOOST_CHECK( equal8 );

    constexpr auto result9 = Exp10( 0.7 );
    constexpr auto equal9 = AreNearlyEqual( result9, 5.0118723362727228500155418688494574 );
    BOOST_CHECK( equal9 );
}





// --run_test=ConstexprMathTests/FloatExpM1Test1
BOOST_AUTO_TEST_CASE( FloatExpM1Test1 )
{
    using C = Constants<float>;

    constexpr auto result1 = ExpM1( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = ExpM1( C::NegativeInfinity );
    BOOST_CHECK( result2 == -1 );

    constexpr auto result3 = ExpM1( C::Zero );
    BOOST_CHECK( result3 == 0 );

    constexpr auto result4 = ExpM1( -C::Zero );
    BOOST_CHECK( result4 == 0 );

    constexpr auto result5 = ExpM1( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = ExpM1( C::One );
    BOOST_CHECK( result6 == (C::E - 1) );

    constexpr auto result7 = ExpM1( C::Two );
    BOOST_CHECK( result7 == (C::E2 - 1 ) );

    constexpr auto result8 = ExpM1( C::Three );
    BOOST_CHECK( result8 == ( C::E3 - 1 ) );

    constexpr auto result9 = ExpM1( .7f );
    BOOST_CHECK( result9 == 1.01375270f );

    constexpr auto result10 = ExpM1( 50.f );
    BOOST_CHECK( result10 == 5.18470546e+21f );
}

// --run_test=ConstexprMathTests/DoubleExpM1Test1
BOOST_AUTO_TEST_CASE( DoubleExpM1Test1 )
{
    using C = Constants<double>;

    constexpr auto result1 = ExpM1( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = ExpM1( C::NegativeInfinity );
    BOOST_CHECK( result2 == -1 );

    constexpr auto result3 = ExpM1( C::Zero );
    BOOST_CHECK( result3 == 0 );

    constexpr auto result4 = ExpM1( -C::Zero );
    BOOST_CHECK( result4 == 0 );

    constexpr auto result5 = ExpM1( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = ExpM1( C::One );
    BOOST_CHECK( result6 == ( C::E - 1 ) );

    constexpr auto result7 = ExpM1( C::Two );
    constexpr auto equal7 = AreNearlyEqual( result7, ( C::E2 - 1 ) );
    BOOST_CHECK( equal7 );

    constexpr auto result8 = ExpM1( C::Three );
    constexpr auto equal8 = AreNearlyEqual( result8, ( C::E3 - 1 ) );
    BOOST_CHECK( equal8 );

    constexpr auto result9 = ExpM1( .7 );
    constexpr auto equal9 = AreNearlyEqual( result9, 1.0137527074704765216 );
    BOOST_CHECK( equal9 );

    constexpr auto result10 = ExpM1( 50. );
    constexpr auto equal10 = AreNearlyEqual( result10, 5184705528587072464086.45332293348538 );
    BOOST_CHECK( equal10 );
}

// --run_test=ConstexprMathTests/FloatHypotTest1
BOOST_AUTO_TEST_CASE( FloatHypotTest1 )
{
    using C = Constants<float>;

    constexpr auto result = Hypot( C::Two, C::Two );
    constexpr auto expected = Sqrt( C::Two * C::Two + C::Two * C::Two );
    constexpr auto equal = result == expected;
    BOOST_CHECK( result );
}

// --run_test=ConstexprMathTests/DoubleHypotTest1
BOOST_AUTO_TEST_CASE( DoubleHypotTest1 )
{
    using C = Constants<double>;

    constexpr auto result = Hypot( C::Two, C::Two );
    constexpr auto expected = Sqrt( C::Two * C::Two + C::Two * C::Two );
    constexpr auto equal = result == expected;
    BOOST_CHECK( result );
}


// --run_test=ConstexprMathTests/FloatHypot3Test1
BOOST_AUTO_TEST_CASE( FloatHypot3Test1 )
{
    using C = Constants<float>;

    constexpr auto result = Hypot( C::Two, C::Two, C::Two );
    constexpr auto expected = Sqrt( C::Two * C::Two + C::Two * C::Two + C::Two * C::Two );
    constexpr auto equal = result == expected;
    BOOST_CHECK( result );
}

// --run_test=ConstexprMathTests/DoubleHypot3Test1
BOOST_AUTO_TEST_CASE( DoubleHypot3Test1 )
{
    using C = Constants<double>;

    constexpr auto result = Hypot( C::Two, C::Two, C::Two );
    constexpr auto expected = Sqrt( C::Two * C::Two + C::Two * C::Two + C::Two * C::Two );
    constexpr auto equal = result == expected;
    BOOST_CHECK( result );
}


// --run_test=ConstexprMathTests/FloatLogTest1
BOOST_AUTO_TEST_CASE( FloatLogTest1 )
{
    using C = Constants<float>;

    constexpr auto result1 = Log( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Log( C::NegativeInfinity );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = Log( C::Zero );
    BOOST_CHECK( IsInf( result3 ) );

    constexpr auto result4 = Log( -C::Zero );
    BOOST_CHECK( IsInf( result4 ) );

    constexpr auto result5 = Log( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Log( C::One );
    BOOST_CHECK( result6 == C::Zero );

    constexpr auto result7 = Log( -C::One );
    BOOST_CHECK( IsNaN( result7 ) );

    constexpr auto result8 = Log( C::E );
    BOOST_CHECK( result8 == C::One );

    constexpr auto result9 = Log( C::E2 );
    BOOST_CHECK( result9 == C::Two );

    constexpr auto result10 = Log( C::E3 );
    BOOST_CHECK( result10 == C::Three );

    constexpr auto result11 = Log( .7f );
    BOOST_CHECK( result11 == -0.356674969f );
}

// --run_test=ConstexprMathTests/DoubleLogTest1
BOOST_AUTO_TEST_CASE( DoubleLogTest1 )
{
    using C = Constants<double>;

    constexpr auto result1 = Log( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Log( C::NegativeInfinity );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = Log( C::Zero );
    BOOST_CHECK( IsInf( result3 ) );

    constexpr auto result4 = Log( -C::Zero );
    BOOST_CHECK( IsInf( result4 ) );

    constexpr auto result5 = Log( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Log( C::One );
    BOOST_CHECK( result6 == C::Zero );

    constexpr auto result7 = Log( -C::One );
    BOOST_CHECK( IsNaN( result7 ) );

    constexpr auto result8 = Log( C::E );
    BOOST_CHECK( result8 == C::One );

    constexpr auto result9 = Log( C::E2 );
    BOOST_CHECK( result9 == C::Two );

    constexpr auto result10 = Log( C::E3 );
    BOOST_CHECK( result10 == C::Three );


    constexpr auto result11 = Log( .7 );
    constexpr auto equal11 = AreNearlyEqual( result11, -0.35667494393873237891263871124118447 );
    BOOST_CHECK( equal11 );
}


// --run_test=ConstexprMathTests/FloatLog2Test1
BOOST_AUTO_TEST_CASE( FloatLog2Test1 )
{
    using C = Constants<float>;

    constexpr auto result1 = Log2( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Log2( C::NegativeInfinity );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = Log2( C::Zero );
    BOOST_CHECK( IsInf( result3 ) );

    constexpr auto result4 = Log2( -C::Zero );
    BOOST_CHECK( IsInf( result4 ) );

    constexpr auto result5 = Log2( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Log2( C::One );
    BOOST_CHECK( result6 == C::Zero );

    constexpr auto result7 = Log2( -C::One );
    BOOST_CHECK( IsNaN( result7 ) );

    constexpr auto result8 = Log2( C::Two );
    BOOST_CHECK( result8 == C::One );

    constexpr auto result9 = Log2( C::Two* C::Two );
    BOOST_CHECK( result9 == C::Two );

    constexpr auto result10 = Log2( C::Two * C::Two * C::Two );
    BOOST_CHECK( result10 == C::Three );

    constexpr auto result11 = Log2( .7f );
    BOOST_CHECK( result11 == -0.514573216f );
}

// --run_test=ConstexprMathTests/DoubleLog2Test1
BOOST_AUTO_TEST_CASE( DoubleLog2Test1 )
{
    using C = Constants<double>;

    constexpr auto result1 = Log2( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Log2( C::NegativeInfinity );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = Log2( C::Zero );
    BOOST_CHECK( IsInf( result3 ) );

    constexpr auto result4 = Log2( -C::Zero );
    BOOST_CHECK( IsInf( result4 ) );

    constexpr auto result5 = Log2( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Log2( C::One );
    BOOST_CHECK( result6 == C::Zero );

    constexpr auto result7 = Log2( -C::One );
    BOOST_CHECK( IsNaN( result7 ) );

    constexpr auto result8 = Log2( C::Two );
    BOOST_CHECK( result8 == C::One );

    constexpr auto result9 = Log2( C::Two * C::Two );
    BOOST_CHECK( result9 == C::Two );

    constexpr auto result10 = Log2( C::Two * C::Two * C::Two );
    BOOST_CHECK( result10 == C::Three );


    constexpr auto result11 = Log2( .7 );
    constexpr auto equal11 = AreNearlyEqual( result11, -0.51457317282975824043 );
    BOOST_CHECK( equal11 );
}


// --run_test=ConstexprMathTests/FloatLog10Test1
BOOST_AUTO_TEST_CASE( FloatLog10Test1 )
{
    using C = Constants<float>;

    constexpr auto result1 = Log10( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Log10( C::NegativeInfinity );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = Log10( C::Zero );
    BOOST_CHECK( IsInf( result3 ) );

    constexpr auto result4 = Log10( -C::Zero );
    BOOST_CHECK( IsInf( result4 ) );

    constexpr auto result5 = Log10( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Log10( C::One );
    BOOST_CHECK( result6 == C::Zero );

    constexpr auto result7 = Log10( -C::One );
    BOOST_CHECK( IsNaN( result7 ) );

    constexpr auto result8 = Log10( 10.f );
    BOOST_CHECK( result8 == C::One );

    constexpr auto result9 = Log10( 100.f );
    BOOST_CHECK( result9 == C::Two );

    constexpr auto result10 = Log10( 1000.f );
    BOOST_CHECK( result10 == C::Three );

    constexpr auto result11 = Log10( .7f );
    BOOST_CHECK( result11 == -0.154901966f );
}

// --run_test=ConstexprMathTests/DoubleLog10Test1
BOOST_AUTO_TEST_CASE( DoubleLog10Test1 )
{
    using C = Constants<double>;

    constexpr auto result1 = Log10( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Log10( C::NegativeInfinity );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = Log10( C::Zero );
    BOOST_CHECK( IsInf( result3 ) );

    constexpr auto result4 = Log10( -C::Zero );
    BOOST_CHECK( IsInf( result4 ) );

    constexpr auto result5 = Log10( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Log10( C::One );
    BOOST_CHECK( result6 == C::Zero );

    constexpr auto result7 = Log10( -C::One );
    BOOST_CHECK( IsNaN( result7 ) );

    constexpr auto result8 = Log10( 10. );
    BOOST_CHECK( result8 == C::One );

    constexpr auto result9 = Log10( 100. );
    BOOST_CHECK( result9 == C::Two );

    constexpr auto result10 = Log10( 1000. );
    BOOST_CHECK( result10 == C::Three );


    constexpr auto result11 = Log10( .7 );
    constexpr auto equal11 = AreNearlyEqual( result11, -0.15490195998574316929 );
    BOOST_CHECK( equal11 );
}


// --run_test=ConstexprMathTests/FloatLog1PTest1
BOOST_AUTO_TEST_CASE( FloatLog1PTest1 )
{
    using C = Constants<float>;

    constexpr auto result1 = Log1P( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Log1P( C::NegativeInfinity );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = Log1P( C::Zero );
    BOOST_CHECK( result3 == C::Zero );

    constexpr auto result4 = Log1P( -C::Zero );
    BOOST_CHECK( result4 == C::Zero );

    constexpr auto result5 = Log1P( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Log1P( C::One );
    BOOST_CHECK( result6 == 0.693147182f );

    constexpr auto result7 = Log1P( -C::One );
    BOOST_CHECK( IsInf( result7 ) );

    constexpr auto result8 = Log1P( C::E - 1 );
    BOOST_CHECK( result8 == C::One );

    constexpr auto result9 = Log1P( C::E2 - 1 );
    BOOST_CHECK( result9 == C::Two );

    constexpr auto result10 = Log1P( C::E3 - 1 );
    BOOST_CHECK( result10 == C::Three );


    constexpr auto result11 = Log1P( -0.3f );
    BOOST_CHECK( result11 == -0.356674969f );
}

// --run_test=ConstexprMathTests/DoubleLog1PTest1
BOOST_AUTO_TEST_CASE( DoubleLog1PTest1 )
{
    using C = Constants<double>;

    constexpr auto result1 = Log1P( C::Infinity );
    BOOST_CHECK( IsInf( result1 ) );

    constexpr auto result2 = Log1P( C::NegativeInfinity );
    BOOST_CHECK( IsNaN( result2 ) );

    constexpr auto result3 = Log1P( C::Zero );
    BOOST_CHECK( result3 == C::Zero );

    constexpr auto result4 = Log1P( -C::Zero );
    BOOST_CHECK( result4 == C::Zero );

    constexpr auto result5 = Log1P( C::NaN );
    BOOST_CHECK( IsNaN( result5 ) );

    constexpr auto result6 = Log1P( C::One );
    BOOST_CHECK( result6 == 0.69314718055994529 );

    constexpr auto result7 = Log1P( -C::One );
    BOOST_CHECK( IsInf( result7 ) );

    constexpr auto result8 = Log1P( C::E - 1 );
    BOOST_CHECK( result8 == C::One );

    constexpr auto result9 = Log1P( C::E2 - 1 );
    BOOST_CHECK( result9 == C::Two );

    constexpr auto result10 = Log1P( C::E3 - 1 );
    BOOST_CHECK( result10 == C::Three );


    constexpr auto result11 = Log1P( -0.3 );
    constexpr auto equal11 = AreNearlyEqual( result11, -0.35667494393873237891263871124118447 );
    BOOST_CHECK( equal11 );
}


// --run_test=ConstexprMathTests/FloatPowTest1
BOOST_AUTO_TEST_CASE( FloatPowTest1 )
{
    using C = Constants<float>;
    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected ) -> bool
        {
            auto r = Pow( x, y );
            return IsSameValue( r, expected );
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsNaN( r );
        };

    constexpr auto CheckIsInf = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsInf( r );
        };

    constexpr auto CheckIsPosInf = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsSameValue( r, C::Infinity );
        };

    constexpr auto CheckIsNegInf = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsSameValue( r, C::NegativeInfinity );
        };


    constexpr auto check1 = Check( 0., 0., 1 ) && Check( -0., 0., 1 ) && Check( 0., -0., 1 ) && Check( -0., -0., 1 );
    BOOST_CHECK( check1 );
    constexpr auto check2 = Check( 10., 0., 1 ) && Check( -10., 0., 1 ) && Check( 10., -0., 1 ) && Check( -10., -0., 1 );
    BOOST_CHECK( check2 );
    constexpr auto check3 = Check( C::NaN, 0., 1 ) && Check( C::NaN, -0., 1 );
    BOOST_CHECK( check3 );

    constexpr auto check4 = CheckIsInf( 1.1f, C::Infinity ) && 
        CheckIsInf( C::Infinity, C::Infinity ) && 
        CheckIsInf( -1.1f, C::Infinity ) &&
        CheckIsInf( -C::Infinity, C::Infinity );
    BOOST_CHECK( check4 );

    constexpr auto check5 = Check( 0.9f, C::Infinity, 0.f ) && 
        Check( 1e-7, C::Infinity, 0 ) && 
        Check( -0.9, C::Infinity, 0 ) && 
        Check( -1e-7, C::Infinity, 0 );
    BOOST_CHECK( check5 );

    constexpr auto check6 = Check( 1.1, -C::Infinity, 0 ) && Check( C::Infinity, -C::Infinity, 0 ) && Check( -1.1, -C::Infinity, 0 ) && Check( -C::Infinity, -C::Infinity, 0 );
    BOOST_CHECK( check6 );

    constexpr auto check7 = CheckIsInf( 0.9, -C::Infinity ) && CheckIsInf( 1e-7, -C::Infinity ) && CheckIsInf( -0.9, -C::Infinity ) && CheckIsInf( -1e-7, -C::Infinity );
    BOOST_CHECK( check7 );

    constexpr auto check8 = CheckIsInf( C::Infinity, 1e-7 ) && CheckIsInf( C::Infinity, 1 ) && CheckIsInf( C::Infinity, 1e7 );
    BOOST_CHECK( check8 );

    constexpr auto check9 = Check( C::Infinity, -1e-7, 0 ) && Check( C::Infinity, -1, 0 ) && Check( C::Infinity, -1e7, 0 );
    BOOST_CHECK( check9 );

    constexpr auto check10 = CheckIsNegInf( -C::Infinity, 1 ) && CheckIsNegInf( -C::Infinity, 11 ) && CheckIsNegInf( -C::Infinity, 1001 );
    BOOST_CHECK( check10 );

    constexpr auto check11 = CheckIsPosInf( -C::Infinity, 2 ) &&
        CheckIsPosInf( -C::Infinity, 12 ) &&
        CheckIsPosInf( -C::Infinity, 1002 ) &&
        CheckIsPosInf( -C::Infinity, 0.1 ) &&
        CheckIsPosInf( -C::Infinity, 1.1 ) &&
        CheckIsPosInf( -C::Infinity, 11.1 ) &&
        CheckIsPosInf( -C::Infinity, 1001.1 );
    BOOST_CHECK( check11 );

    constexpr auto check12 = Check( -C::Infinity, -1, -0.f ) && Check( -C::Infinity, -11, -0.f ) && Check( -C::Infinity, -1001, -0.f );
    BOOST_CHECK( check12 );

    constexpr auto check13 = Check( -C::Infinity, -2, 0. ) &&
        Check( -C::Infinity, -12, 0. ) &&
        Check( -C::Infinity, -1002, 0. ) &&
        Check( -C::Infinity, -0.1, 0. ) &&
        Check( -C::Infinity, -1.1, 0. ) &&
        Check( -C::Infinity, -11.1, 0. ) &&
        Check( -C::Infinity, -1001.1, 0. );
    BOOST_CHECK( check13 );

    constexpr auto check14 = CheckIsNaN( C::NaN, C::NaN ) &&
        CheckIsNaN( 0.f, C::NaN ) &&
        Check( 1.f, C::NaN, 1.f ) &&
        CheckIsNaN( -1.f, C::NaN ) &&
        CheckIsNaN( C::NaN, 1.f ) &&
        CheckIsNaN( C::NaN, -1.f ) &&
        CheckIsNaN( 3.f, C::NaN );
    BOOST_CHECK( check14 );

    constexpr auto check15 = Check( 1.f, C::Infinity, 1.f ) &&
        Check( -1.f, C::Infinity, 1.f ) &&
        Check( 1.f, -C::Infinity, 1.f ) &&
        Check( -1.f, -C::Infinity, 1.f );
    BOOST_CHECK( check15 );

    constexpr auto check16 = CheckIsNaN( -0.1f, 1.1f ) &&
        CheckIsNaN( -0.1f, -1.1f ) &&
        CheckIsNaN( -10.1f, 1.1f ) &&
        CheckIsNaN( -10.1f, -1.1f );
    BOOST_CHECK( check16 );


    constexpr auto check17 = CheckIsPosInf( 0.f, -1.f ) &&
        CheckIsPosInf( 0.f, -11.f ) &&
        CheckIsNegInf( -0.f, -1.f )&&
        CheckIsNegInf( -0.f, -11.f );
    BOOST_CHECK( check17 );

    constexpr auto check18 = CheckIsPosInf( 0., -2. ) &&
        CheckIsPosInf( 0, -11.1 ) &&
        CheckIsPosInf( -0.f, -2 ) &&
        CheckIsPosInf( -0.f, -11.1 );
    BOOST_CHECK( check18 );

    constexpr auto check19 = Check( 0.f, 1.f, 0.f ) &&
        Check( 0.f, 11.f, 0.f ) &&
        Check( -0.f, 1.f, -0.f ) &&
        Check( -0.f, 11.f, -0.f ) &&
        Check( 0.f, 2.f, 0.f )&&
        Check( 0.f, 11.1f, 0.f ) &&
        Check( -0.f, 2.f, 0.f ) &&
        Check( -0.f, 11.1f, 0.f );
    BOOST_CHECK( check19 );

    constexpr auto check20 = CheckIsPosInf( 1.5, C::Infinity ) &&
        Check( 0.5, C::Infinity, 0. ) &&
        Check( 1.5, -C::Infinity, 0. ) &&
        CheckIsPosInf( 0.5, -C::Infinity );
    BOOST_CHECK( check20 );

    // pow (inf, 2) == inf
    constexpr auto check21 = CheckIsPosInf( C::Infinity, 2.f );
    BOOST_CHECK( check21 );

    // pow (inf, -1) == 0.0
    constexpr auto check22 = Check( C::Infinity, -1.f, 0.f );
    BOOST_CHECK( check22 );

    // pow (-inf, 27) == -inf
    constexpr auto check23 = CheckIsNegInf( -C::Infinity, 27.f );
    BOOST_CHECK( check23 );

    // pow (-inf, 28) == inf
    constexpr auto check24 = CheckIsPosInf( -C::Infinity, 28.f );
    BOOST_CHECK( check24 );

    // pow (-inf, -3) == -0
    constexpr auto check25 = Check( -C::Infinity, -3.f, -0.f );
    BOOST_CHECK( check25 );

    // pow (-inf, -2.0) == 0.0
    constexpr auto check26 = Check( -C::Infinity, -2.f, 0.f );
    BOOST_CHECK( check26 );

    // pow (0.0, 27) == 0.0
    constexpr auto check27 = Check( 0., 27.f, 0.f );
    BOOST_CHECK( check27 );

    // pow (-0, 27) == -0
    constexpr auto check28 = Check( -0., 27.f, -0.f );
    BOOST_CHECK( check28 );

    // pow (0.0, 4) == 0.0
    constexpr auto check29 = Check( 0., 4.f, 0.f );
    BOOST_CHECK( check29 );

    // pow (-0, 4) == 0.0
    constexpr auto check30 = Check( -0., 4.f, 0.f );
    BOOST_CHECK( check30 );

    // pow (0.7, 1.2) == 0.65180494056638638188
    constexpr auto check31 = Check( 0.7f, 1.2f, 0.65180494056638638188f );
    BOOST_CHECK( check31 );

}

// --run_test=ConstexprMathTests/DoublePowTest1
BOOST_AUTO_TEST_CASE( DoublePowTest1 )
{
    using C = Constants<double>;
    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected ) -> bool
        {
            auto r = Pow( x, y );
            return IsSameValue( r, expected );
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsNaN( r );
        };

    constexpr auto CheckIsInf = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsInf( r );
        };

    constexpr auto CheckIsPosInf = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsSameValue( r, C::Infinity );
        };

    constexpr auto CheckIsNegInf = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsSameValue( r, C::NegativeInfinity );
        };


    constexpr auto check1 = Check( 0., 0., 1 ) && Check( -0., 0., 1 ) && Check( 0., -0., 1 ) && Check( -0., -0., 1 );
    BOOST_CHECK( check1 );
    constexpr auto check2 = Check( 10., 0., 1 ) && Check( -10., 0., 1 ) && Check( 10., -0., 1 ) && Check( -10., -0., 1 );
    BOOST_CHECK( check2 );
    constexpr auto check3 = Check( C::NaN, 0., 1 ) && Check( C::NaN, -0., 1 );
    BOOST_CHECK( check3 );

    constexpr auto check4 = CheckIsInf( 1.1, C::Infinity ) &&
        CheckIsInf( C::Infinity, C::Infinity ) &&
        CheckIsInf( -1.1f, C::Infinity ) &&
        CheckIsInf( -C::Infinity, C::Infinity );
    BOOST_CHECK( check4 );

    constexpr auto check5 = Check( 0.9, C::Infinity, 0.f ) &&
        Check( 1e-7, C::Infinity, 0 ) &&
        Check( -0.9, C::Infinity, 0 ) &&
        Check( -1e-7, C::Infinity, 0 );
    BOOST_CHECK( check5 );

    constexpr auto check6 = Check( 1.1, -C::Infinity, 0 ) && Check( C::Infinity, -C::Infinity, 0 ) && Check( -1.1, -C::Infinity, 0 ) && Check( -C::Infinity, -C::Infinity, 0 );
    BOOST_CHECK( check6 );

    constexpr auto check7 = CheckIsInf( 0.9, -C::Infinity ) && CheckIsInf( 1e-7, -C::Infinity ) && CheckIsInf( -0.9, -C::Infinity ) && CheckIsInf( -1e-7, -C::Infinity );
    BOOST_CHECK( check7 );

    constexpr auto check8 = CheckIsInf( C::Infinity, 1e-7 ) && CheckIsInf( C::Infinity, 1 ) && CheckIsInf( C::Infinity, 1e7 );
    BOOST_CHECK( check8 );

    constexpr auto check9 = Check( C::Infinity, -1e-7, 0 ) && Check( C::Infinity, -1, 0 ) && Check( C::Infinity, -1e7, 0 );
    BOOST_CHECK( check9 );

    constexpr auto check10 = CheckIsNegInf( -C::Infinity, 1 ) && CheckIsNegInf( -C::Infinity, 11 ) && CheckIsNegInf( -C::Infinity, 1001 );
    BOOST_CHECK( check10 );

    constexpr auto check11 = CheckIsPosInf( -C::Infinity, 2 ) &&
        CheckIsPosInf( -C::Infinity, 12 ) &&
        CheckIsPosInf( -C::Infinity, 1002 ) &&
        CheckIsPosInf( -C::Infinity, 0.1 ) &&
        CheckIsPosInf( -C::Infinity, 1.1 ) &&
        CheckIsPosInf( -C::Infinity, 11.1 ) &&
        CheckIsPosInf( -C::Infinity, 1001.1 );
    BOOST_CHECK( check11 );

    constexpr auto check12 = Check( -C::Infinity, -1., -0. ) && Check( -C::Infinity, -11, -0. ) && Check( -C::Infinity, -1001, -0. );
    BOOST_CHECK( check12 );

    constexpr auto check13 = Check( -C::Infinity, -2, 0. ) &&
        Check( -C::Infinity, -12, 0. ) &&
        Check( -C::Infinity, -1002, 0. ) &&
        Check( -C::Infinity, -0.1, 0. ) &&
        Check( -C::Infinity, -1.1, 0. ) &&
        Check( -C::Infinity, -11.1, 0. ) &&
        Check( -C::Infinity, -1001.1, 0. );
    BOOST_CHECK( check13 );

    constexpr auto check14 = CheckIsNaN( C::NaN, C::NaN ) &&
        CheckIsNaN( 0., C::NaN ) &&
        Check( 1., C::NaN, 1. ) &&
        CheckIsNaN( -1., C::NaN ) &&
        CheckIsNaN( C::NaN, 1. ) &&
        CheckIsNaN( C::NaN, -1. ) &&
        CheckIsNaN( 3., C::NaN );
    BOOST_CHECK( check14 );

    constexpr auto check15 = Check( 1., C::Infinity, 1. ) &&
        Check( -1., C::Infinity, 1. ) &&
        Check( 1., -C::Infinity, 1. ) &&
        Check( -1., -C::Infinity, 1. );
    BOOST_CHECK( check15 );

    constexpr auto check16 = CheckIsNaN( -0.1, 1.1 ) &&
        CheckIsNaN( -0.1, -1.1 ) &&
        CheckIsNaN( -10.1, 1.1 ) &&
        CheckIsNaN( -10.1, -1.1 );
    BOOST_CHECK( check16 );


    constexpr auto check17 = CheckIsPosInf( 0., -1. ) &&
        CheckIsPosInf( 0., -11. ) &&
        CheckIsNegInf( -0., -1. ) &&
        CheckIsNegInf( -0., -11. );
    BOOST_CHECK( check17 );

    constexpr auto check18 = CheckIsPosInf( 0., -2. ) &&
        CheckIsPosInf( 0, -11.1 ) &&
        CheckIsPosInf( -0., -2 ) &&
        CheckIsPosInf( -0., -11.1 );
    BOOST_CHECK( check18 );

    constexpr auto check19 = Check( 0., 1., 0. ) &&
        Check( 0., 11., 0. ) &&
        Check( -0., 1., -0. ) &&
        Check( -0., 11., -0. ) &&
        Check( 0., 2., 0. ) &&
        Check( 0., 11.1, 0. ) &&
        Check( -0., 2., 0.f ) &&
        Check( -0., 11.1, 0.f );
    BOOST_CHECK( check19 );

    constexpr auto check20 = CheckIsPosInf( 1.5, C::Infinity ) &&
        Check( 0.5, C::Infinity, 0. ) &&
        Check( 1.5, -C::Infinity, 0. ) &&
        CheckIsPosInf( 0.5, -C::Infinity );
    BOOST_CHECK( check20 );

    // pow (inf, 2) == inf
    constexpr auto check21 = CheckIsPosInf( C::Infinity, 2. );
    BOOST_CHECK( check21 );

    // pow (inf, -1) == 0.0
    constexpr auto check22 = Check( C::Infinity, -1., 0. );
    BOOST_CHECK( check22 );

    // pow (-inf, 27) == -inf
    constexpr auto check23 = CheckIsNegInf( -C::Infinity, 27. );
    BOOST_CHECK( check23 );

    // pow (-inf, 28) == inf
    constexpr auto check24 = CheckIsPosInf( -C::Infinity, 28. );
    BOOST_CHECK( check24 );

    // pow (-inf, -3) == -0
    constexpr auto check25 = Check( -C::Infinity, -3., -0. );
    BOOST_CHECK( check25 );

    // pow (-inf, -2.0) == 0.0
    constexpr auto check26 = Check( -C::Infinity, -2., 0. );
    BOOST_CHECK( check26 );

    // pow (0.0, 27) == 0.0
    constexpr auto check27 = Check( 0., 27., 0. );
    BOOST_CHECK( check27 );

    // pow (-0, 27) == -0
    constexpr auto check28 = Check( -0., 27., -0. );
    BOOST_CHECK( check28 );

    // pow (0.0, 4) == 0.0
    constexpr auto check29 = Check( 0., 4., 0. );
    BOOST_CHECK( check29 );

    // pow (-0, 4) == 0.0
    constexpr auto check30 = Check( -0., 4., 0. );
    BOOST_CHECK( check30 );

    // pow (0.7, 1.2) == 0.65180494056638638188
    constexpr auto check31 = Check( 0.7, 1.2, 0.65180494056638638188 );
    BOOST_CHECK( check31 );

}

// --run_test=ConstexprMathTests/FloatRemainderTest1
BOOST_AUTO_TEST_CASE( FloatRemainderTest1 )
{
    using C = Constants<float>;
    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected ) -> bool
        {
            auto r = Remainder( x, y );
            return IsSameValue( r, expected );
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Remainder( x, y );
            return IsNaN( r );
        };

    // remainder (1, 0) == NaN
    constexpr auto check1 = CheckIsNaN( 1., 0. );
    BOOST_CHECK( check1 );

    // remainder (1, -0) == NaN
    constexpr auto check2 = CheckIsNaN( 1., -0. );
    BOOST_CHECK( check2 );

    // remainder (inf, 1) == NaN
    constexpr auto check3 = CheckIsNaN( C::Infinity, 1. );
    BOOST_CHECK( check3 );

    // remainder (-inf, 1) == NaN
    constexpr auto check4 = CheckIsNaN( C::NegativeInfinity, 1. );
    BOOST_CHECK( check4 );

    // remainder (NaN, NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN, C::NaN );
    BOOST_CHECK( check5 );

    // remainder (1.625, 1.0) == -0.375
    constexpr auto check6 = Check( 1.625, 1.0, -0.375 );
    BOOST_CHECK( check6 );

    // remainder (-1.625, 1.0) == 0.375
    constexpr auto check7 = Check( -1.625, 1.0, 0.375 );
    BOOST_CHECK( check7 );

    // remainder (1.625, -1.0) == -0.375
    constexpr auto check8 = Check( 1.625, -1.0, -0.375 );
    BOOST_CHECK( check8 );

    // remainder (-1.625, -1.0) == 0.375
    constexpr auto check9 = Check( -1.625, -1.0, 0.375 );
    BOOST_CHECK( check9 );

    // remainder (5.0, 2.0) == 1.0
    constexpr auto check10 = Check( 5.0, 2.0, 1.0 );
    BOOST_CHECK( check10 );

    // remainder (3.0, 2.0) == -1.0
    constexpr auto check11 = Check( 3.0, 2.0, -1.0 );
    BOOST_CHECK( check11 );
}

// --run_test=ConstexprMathTests/DoubleRemainderTest1
BOOST_AUTO_TEST_CASE( DoubleRemainderTest1 )
{
    using C = Constants<double>;
    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected ) -> bool
        {
            auto r = Remainder( x, y );
            return IsSameValue( r, expected );
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Remainder( x, y );
            return IsNaN( r );
        };

    // remainder (1, 0) == NaN
    constexpr auto check1 = CheckIsNaN( 1., 0. );
    BOOST_CHECK( check1 );

    // remainder (1, -0) == NaN
    constexpr auto check2 = CheckIsNaN( 1., -0. );
    BOOST_CHECK( check2 );

    // remainder (inf, 1) == NaN
    constexpr auto check3 = CheckIsNaN( C::Infinity, 1. );
    BOOST_CHECK( check3 );

    // remainder (-inf, 1) == NaN
    constexpr auto check4 = CheckIsNaN( C::NegativeInfinity, 1. );
    BOOST_CHECK( check4 );

    // remainder (NaN, NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN, C::NaN );
    BOOST_CHECK( check5 );

    // remainder (1.625, 1.0) == -0.375
    constexpr auto check6 = Check( 1.625, 1.0, -0.375 );
    BOOST_CHECK( check6 );

    // remainder (-1.625, 1.0) == 0.375
    constexpr auto check7 = Check( -1.625, 1.0, 0.375 );
    BOOST_CHECK( check7 );

    // remainder (1.625, -1.0) == -0.375
    constexpr auto check8 = Check( 1.625, -1.0, -0.375 );
    BOOST_CHECK( check8 );

    // remainder (-1.625, -1.0) == 0.375
    constexpr auto check9 = Check( -1.625, -1.0, 0.375 );
    BOOST_CHECK( check9 );

    // remainder (5.0, 2.0) == 1.0
    constexpr auto check10 = Check( 5.0, 2.0, 1.0 );
    BOOST_CHECK( check10 );

    // remainder (3.0, 2.0) == -1.0
    constexpr auto check11 = Check( 3.0, 2.0, -1.0 );
    BOOST_CHECK( check11 );
}

// --run_test=ConstexprMathTests/FloatRemQuoTest1
BOOST_AUTO_TEST_CASE( FloatRemQuoTest1 )
{
    using C = Constants<float>;
    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected, int expectedQuo ) -> bool
        {
            int quo{};
            auto r = RemQuo( x, y, &quo );
            return IsSameValue( r, expected ) && expectedQuo == quo;
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            int quo{};
            auto r = RemQuo( x, y, &quo );
            return IsNaN( r );
        };

    // remquo (1, 0, &x) == NaN
    constexpr auto check1 = CheckIsNaN( 1., 0. );
    BOOST_CHECK( check1 );

    // remquo (1, -0, &x) == NaN
    constexpr auto check2 = CheckIsNaN( 1., -0. );
    BOOST_CHECK( check2 );

    // remquo (inf, 1, &x) == NaN
    constexpr auto check3 = CheckIsNaN( C::Infinity, 1. );
    BOOST_CHECK( check3 );

    // remquo (-inf, 1, &x) == NaN
    constexpr auto check4 = CheckIsNaN( -C::Infinity, 1. );
    BOOST_CHECK( check4 );

    // remquo (NaN, NaN, &x) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN, C::NaN );
    BOOST_CHECK( check5 );

    // remquo (1.625, 1.0, &x) == -0.375, x == 2
    constexpr auto check6 = Check( 1.625, 1.0, -0.375, 2 );
    BOOST_CHECK( check6 );

    // remquo (-1.625, 1.0, &x) == 0.375, x == -2
    constexpr auto check7 = Check( -1.625, 1.0, 0.375, -2 );
    BOOST_CHECK( check7 );

    // remquo (1.625, -1.0, &x) == -0.375, x == -2
    constexpr auto check8 = Check( 1.625, -1.0, -0.375, -2 );
    BOOST_CHECK( check8 );

    // remquo (-1.625, -1.0, &x) == 0.375, x == 2
    constexpr auto check9 = Check( -1.625, -1.0, 0.375, 2 );
    BOOST_CHECK( check9 );

    // remquo (5, 2, &x) == 1, x == 2
    constexpr auto check10 = Check( 5, 2, 1., 2 );
    BOOST_CHECK( check10 );

    // remquo (3, 2, &x) == -1, x == 2
    constexpr auto check11 = Check( 3, 2, -1., 2 );
    BOOST_CHECK( check11 );
}

// --run_test=ConstexprMathTests/DoubleRemQuoTest1
BOOST_AUTO_TEST_CASE( DoubleRemQuoTest1 )
{
    using C = Constants<double>;
    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected, int expectedQuo ) -> bool
        {
            int quo{};
            auto r = RemQuo( x, y, &quo );
            return IsSameValue( r, expected ) && expectedQuo == quo;
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            int quo{};
            auto r = RemQuo( x, y, &quo );
            return IsNaN( r );
        };

    // remquo (1, 0, &x) == NaN
    constexpr auto check1 = CheckIsNaN( 1., 0. );
    BOOST_CHECK( check1 );

    // remquo (1, -0, &x) == NaN
    constexpr auto check2 = CheckIsNaN( 1., -0. );
    BOOST_CHECK( check2 );

    // remquo (inf, 1, &x) == NaN
    constexpr auto check3 = CheckIsNaN( C::Infinity, 1. );
    BOOST_CHECK( check3 );

    // remquo (-inf, 1, &x) == NaN
    constexpr auto check4 = CheckIsNaN( -C::Infinity, 1. );
    BOOST_CHECK( check4 );

    // remquo (NaN, NaN, &x) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN, C::NaN );
    BOOST_CHECK( check5 );

    // remquo (1.625, 1.0, &x) == -0.375, x == 2
    constexpr auto check6 = Check( 1.625, 1.0, -0.375, 2 );
    BOOST_CHECK( check6 );

    // remquo (-1.625, 1.0, &x) == 0.375, x == -2
    constexpr auto check7 = Check( -1.625, 1.0, 0.375, -2 );
    BOOST_CHECK( check7 );

    // remquo (1.625, -1.0, &x) == -0.375, x == -2
    constexpr auto check8 = Check( 1.625, -1.0, -0.375, -2 );
    BOOST_CHECK( check8 );

    // remquo (-1.625, -1.0, &x) == 0.375, x == 2
    constexpr auto check9 = Check( -1.625, -1.0, 0.375, 2 );
    BOOST_CHECK( check9 );

    // remquo (5, 2, &x) == 1, x == 2
    constexpr auto check10 = Check( 5, 2, 1., 2 );
    BOOST_CHECK( check10 );

    // remquo (3, 2, &x) == -1, x == 2
    constexpr auto check11 = Check( 3, 2, -1., 2 );
    BOOST_CHECK( check11 );
}


// --run_test=ConstexprMathTests/FloatDeg2RadTest1
BOOST_AUTO_TEST_CASE( FloatDeg2RadTest1 )
{
    using C = Constants<float>;

    constexpr auto result1 = Deg2Rad( 0.f );
    BOOST_CHECK( result1 == C::Zero );

    constexpr auto result2 = Deg2Rad( 45.f );
    static_assert( result2 == C::PiOver4 );
    BOOST_CHECK( result2 == C::PiOver4 );

    constexpr auto result3 = Deg2Rad( 90.f );
    static_assert( result3 == C::PiOver2 );
    BOOST_CHECK( result3 == C::PiOver2 );

}


// --run_test=ConstexprMathTests/DoubleDeg2RadTest1
BOOST_AUTO_TEST_CASE( DoubleDeg2RadTest1 )
{
    constexpr auto arg = 0.001;
    const auto& arg2 = arg;
    constexpr auto result1 = Deg2Rad( arg );
    BOOST_CHECK( result1 == 1.7453292519943296e-5 );

    auto result2 = Deg2Rad<double>( arg2 );

}

// --run_test=ConstexprMathTests/FloatRad2DegTest1
BOOST_AUTO_TEST_CASE( FloatRad2DegTest1 )
{
    using C = Constants<float>;

    constexpr auto result1 = Rad2Deg( 0.f );
    BOOST_CHECK( result1 == C::Zero );

    constexpr auto result2 = Rad2Deg( C::PiOver4 );
    static_assert( result2 == 45.f );
    BOOST_CHECK( result2 == 45.f );

    constexpr auto result3 = Rad2Deg( C::PiOver2 );
    static_assert( result3 == 90.f );
    BOOST_CHECK( result3 == 90.f );

}


// --run_test=ConstexprMathTests/FloatSinTest1
BOOST_AUTO_TEST_CASE( FloatSinTest1 )
{
    constexpr auto rM20000 = Deg2Rad( -20000.f );
    constexpr auto rM720 = Deg2Rad( -720.f );
    constexpr auto rM360 = Deg2Rad( -360.f );
    constexpr auto rM180 = Deg2Rad( -180.f );
    constexpr auto rM135 = Deg2Rad( 135.f );
    constexpr auto rM90 = Deg2Rad( -90.f );
    constexpr auto rM45 = Deg2Rad( -45.f );
    constexpr auto r0 = Deg2Rad( 0.f );
    constexpr auto r45 = Deg2Rad( 45.f );
    constexpr auto r90 = Deg2Rad( 90.f );
    constexpr auto r135 = Deg2Rad( 135.f );
    constexpr auto r180 = Deg2Rad( 180.f );
    constexpr auto r360 = Deg2Rad( 360.f );
    constexpr auto r720 = Deg2Rad( 720.f );
    constexpr auto r20000 = Deg2Rad( 20000.f );

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
    constexpr auto sineMax = Sin( std::numeric_limits<float>::max() );

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
    auto expectedSineMax = std::sin( std::numeric_limits<float>::max( ) );

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
    BOOST_CHECK( expectedSineMax == sineMax );


    constexpr auto radians = Deg2Rad( 0.001f );
    constexpr auto result1a = Sin( radians );
    auto result1b = std::sin( radians );
    auto result1Diff = result1a - result1b;
    BOOST_CHECK( result1a == result1b );
    BOOST_CHECK( result1a == 1.7453292519057202e-5f );
    BOOST_CHECK( result1b == 1.7453292519057202e-5f );
}

// --run_test=ConstexprMathTests/DoubleSinTest1
BOOST_AUTO_TEST_CASE( DoubleSinTest1 )
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
    constexpr auto sineMax = Sin( std::numeric_limits<double>::max( ) );

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
    auto expectedSineMax = std::sin( std::numeric_limits<double>::max( ) );

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
    BOOST_CHECK( expectedSineMax == sineMax );

    constexpr auto radians = Deg2Rad( 0.001 );
    constexpr auto result1a = Sin( radians );
    auto result1b = std::sin( radians );
    auto result1Diff = result1a - result1b;
    BOOST_CHECK( result1a == result1b );
    BOOST_CHECK( result1a == 1.7453292519057202e-5 );
    BOOST_CHECK( result1b == 1.7453292519057202e-5 );
}

// --run_test=ConstexprMathTests/FloatCosTest1
BOOST_AUTO_TEST_CASE( FloatCosTest1 )
{
    constexpr auto rM20000 = Deg2Rad( -20000.f );
    constexpr auto rM720 = Deg2Rad( -720.f );
    constexpr auto rM360 = Deg2Rad( -360.f );
    constexpr auto rM180 = Deg2Rad( -180.f );
    constexpr auto rM135 = Deg2Rad( 135.f );
    constexpr auto rM90 = Deg2Rad( -90.f );
    constexpr auto rM45 = Deg2Rad( -45.f );
    constexpr auto r0 = Deg2Rad( 0.f );
    constexpr auto r45 = Deg2Rad( 45.f );
    constexpr auto r90 = Deg2Rad( 90.f );
    constexpr auto r135 = Deg2Rad( 135.f );
    constexpr auto r180 = Deg2Rad( 180.f );
    constexpr auto r360 = Deg2Rad( 360.f );
    constexpr auto r720 = Deg2Rad( 720.f );
    constexpr auto r20000 = Deg2Rad( 20000.f );

    constexpr auto cosineRM20000 = Cos( rM20000 );
    constexpr auto cosineRM720 = Cos( rM720 );
    constexpr auto cosineRM360 = Cos( rM360 );
    constexpr auto cosineRM180 = Cos( rM180 );
    constexpr auto cosineRM135 = Cos( rM135 );
    constexpr auto cosineRM90 = Cos( rM90 );
    constexpr auto cosineRM45 = Cos( rM45 );
    constexpr auto cosineR0 = Cos( r0 );
    constexpr auto cosineR45 = Cos( r45 );
    constexpr auto cosineR90 = Cos( r90 );
    constexpr auto cosineR135 = Cos( r135 );
    constexpr auto cosineR180 = Cos( r180 );
    constexpr auto cosineR360 = Cos( r360 );
    constexpr auto cosineR720 = Cos( r720 );
    constexpr auto cosineR20000 = Cos( r20000 );

    auto expectedCosineRM20000 = std::cos( rM20000 );
    auto expectedCosineRM720 = std::cos( rM720 );
    auto expectedCosineRM360 = std::cos( rM360 );
    auto expectedCosineRM180 = std::cos( rM180 );
    auto expectedCosineRM135 = std::cos( rM135 );
    auto expectedCosineRM90 = std::cos( rM90 );
    auto expectedCosineRM45 = std::cos( rM45 );
    auto expectedCosineR0 = std::cos( r0 );
    auto expectedCosineR45 = std::cos( r45 );
    auto expectedCosineR90 = std::cos( r90 );
    auto expectedCosineR135 = std::cos( r135 );
    auto expectedCosineR180 = std::cos( r180 );
    auto expectedCosineR360 = std::cos( r360 );
    auto expectedCosineR720 = std::cos( r720 );
    auto expectedCosineR20000 = std::cos( r20000 );

    BOOST_CHECK( expectedCosineRM20000 == cosineRM20000 );
    BOOST_CHECK( expectedCosineRM720 == cosineRM720 );
    BOOST_CHECK( expectedCosineRM360 == cosineRM360 );
    BOOST_CHECK( expectedCosineRM180 == cosineRM180 );
    BOOST_CHECK( expectedCosineRM135 == cosineRM135 );
    BOOST_CHECK( expectedCosineRM90 == cosineRM90 );
    BOOST_CHECK_CLOSE( expectedCosineRM45, cosineRM45, 0.0000000000001 );
    BOOST_CHECK( expectedCosineR0 == cosineR0 );
    BOOST_CHECK_CLOSE( expectedCosineR45, cosineR45, 0.0000000000001 );
    BOOST_CHECK( expectedCosineR90 == cosineR90 );
    BOOST_CHECK( expectedCosineR135 == cosineR135 );
    BOOST_CHECK( expectedCosineR180 == cosineR180 );
    BOOST_CHECK( expectedCosineR360 == cosineR360 );
    BOOST_CHECK( expectedCosineR720 == cosineR720 );
    BOOST_CHECK( expectedCosineR20000 == cosineR20000 );


    constexpr auto radians = Deg2Rad( 0.001f );
    constexpr auto result1a = Cos( radians );
    auto result1b = std::cos( radians );
    auto result1Diff = result1a - result1b;
    BOOST_CHECK( result1a == result1b );
    BOOST_CHECK( result1a == 1.f );
    BOOST_CHECK( result1b == 1.f );
}

// --run_test=ConstexprMathTests/DoubleCosTest1
BOOST_AUTO_TEST_CASE( DoubleCosTest1 )
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

    constexpr auto cosineRM20000 = Cos( rM20000 );
    constexpr auto cosineRM720 = Cos( rM720 );
    constexpr auto cosineRM360 = Cos( rM360 );
    constexpr auto cosineRM180 = Cos( rM180 );
    constexpr auto cosineRM135 = Cos( rM135 );
    constexpr auto cosineRM90 = Cos( rM90 );
    constexpr auto cosineRM45 = Cos( rM45 );
    constexpr auto cosineR0 = Cos( r0 );
    constexpr auto cosineR45 = Cos( r45 );
    constexpr auto cosineR90 = Cos( r90 );
    constexpr auto cosineR135 = Cos( r135 );
    constexpr auto cosineR180 = Cos( r180 );
    constexpr auto cosineR360 = Cos( r360 );
    constexpr auto cosineR720 = Cos( r720 );
    constexpr auto cosineR20000 = Cos( r20000 );

    auto expectedCosineRM20000 = std::cos( rM20000 );
    auto expectedCosineRM720 = std::cos( rM720 );
    auto expectedCosineRM360 = std::cos( rM360 );
    auto expectedCosineRM180 = std::cos( rM180 );
    auto expectedCosineRM135 = std::cos( rM135 );
    auto expectedCosineRM90 = std::cos( rM90 );
    auto expectedCosineRM45 = std::cos( rM45 );
    auto expectedCosineR0 = std::cos( r0 );
    auto expectedCosineR45 = std::cos( r45 );
    auto expectedCosineR90 = std::cos( r90 );
    auto expectedCosineR135 = std::cos( r135 );
    auto expectedCosineR180 = std::cos( r180 );
    auto expectedCosineR360 = std::cos( r360 );
    auto expectedCosineR720 = std::cos( r720 );
    auto expectedCosineR20000 = std::cos( r20000 );

    BOOST_CHECK( expectedCosineRM20000 == cosineRM20000 );
    BOOST_CHECK( expectedCosineRM720 == cosineRM720 );
    BOOST_CHECK( expectedCosineRM360 == cosineRM360 );
    BOOST_CHECK( expectedCosineRM180 == cosineRM180 );
    BOOST_CHECK( expectedCosineRM135 == cosineRM135 );
    BOOST_CHECK( expectedCosineRM90 == cosineRM90 );
    BOOST_CHECK_CLOSE( expectedCosineRM45, cosineRM45, 0.0000000000001 );
    BOOST_CHECK( expectedCosineR0 == cosineR0 );
    BOOST_CHECK_CLOSE( expectedCosineR45, cosineR45, 0.0000000000001 );
    BOOST_CHECK( expectedCosineR90 == cosineR90 );
    BOOST_CHECK( expectedCosineR135 == cosineR135 );
    BOOST_CHECK( expectedCosineR180 == cosineR180 );
    BOOST_CHECK( expectedCosineR360 == cosineR360 );
    BOOST_CHECK( expectedCosineR720 == cosineR720 );
    BOOST_CHECK( expectedCosineR20000 == cosineR20000 );


    constexpr auto radians = Deg2Rad( 0.001 );
    constexpr auto result1a = Cos( radians );
    auto result1b = std::cos( radians );
    auto result1Diff = result1a - result1b;
    BOOST_CHECK( result1a == result1b );
    BOOST_CHECK( result1a == 0.99999999984769128 );
    BOOST_CHECK( result1b == 0.99999999984769128 );
}

// --run_test=ConstexprMathTests/FloatTanTest1
BOOST_AUTO_TEST_CASE( FloatTanTest1 )
{
    constexpr auto rM20000 = Deg2Rad( -20000.f );
    constexpr auto rM720 = Deg2Rad( -720.f );
    constexpr auto rM360 = Deg2Rad( -360.f );
    constexpr auto rM180 = Deg2Rad( -180.f );
    constexpr auto rM135 = Deg2Rad( 135.f );
    constexpr auto rM90 = Deg2Rad( -90.f );
    constexpr auto rM45 = Deg2Rad( -45.f );
    constexpr auto r0 = Deg2Rad( 0.f );
    constexpr auto r45 = Deg2Rad( 45.f );
    constexpr auto r90 = Deg2Rad( 90.f );
    constexpr auto r135 = Deg2Rad( 135.f );
    constexpr auto r180 = Deg2Rad( 180.f );
    constexpr auto r360 = Deg2Rad( 360.f );
    constexpr auto r720 = Deg2Rad( 720.f );
    constexpr auto r20000 = Deg2Rad( 20000.f );

    constexpr auto tanRM20000 = Tan( rM20000 );
    constexpr auto tanRM720 = Tan( rM720 );
    constexpr auto tanRM360 = Tan( rM360 );
    constexpr auto tanRM180 = Tan( rM180 );
    constexpr auto tanRM135 = Tan( rM135 );
    constexpr auto tanRM90 = Tan( rM90 );
    constexpr auto tanRM45 = Tan( rM45 );
    constexpr auto tanR0 = Tan( r0 );
    constexpr auto tanR45 = Tan( r45 );
    constexpr auto tanR90 = Tan( r90 );
    constexpr auto tanR135 = Tan( r135 );
    constexpr auto tanR180 = Tan( r180 );
    constexpr auto tanR360 = Tan( r360 );
    constexpr auto tanR720 = Tan( r720 );
    constexpr auto tanR20000 = Tan( r20000 );

    auto expectedTanRM20000 = std::tan( rM20000 );
    auto expectedTanRM720 = std::tan( rM720 );
    auto expectedTanRM360 = std::tan( rM360 );
    auto expectedTanRM180 = std::tan( rM180 );
    auto expectedTanRM135 = std::tan( rM135 );
    auto expectedTanRM90 = std::tan( rM90 );
    auto expectedTanRM45 = std::tan( rM45 );
    auto expectedTanR0 = std::tan( r0 );
    auto expectedTanR45 = std::tan( r45 );
    auto expectedTanR90 = std::tan( r90 );
    auto expectedTanR135 = std::tan( r135 );
    auto expectedTanR180 = std::tan( r180 );
    auto expectedTanR360 = std::tan( r360 );
    auto expectedTanR720 = std::tan( r720 );
    auto expectedTanR20000 = std::tan( r20000 );

    BOOST_CHECK( expectedTanRM20000 == tanRM20000 );
    BOOST_CHECK( expectedTanRM720 == tanRM720 );
    BOOST_CHECK_CLOSE( expectedTanRM360, tanRM360, 0.00001f );
    BOOST_CHECK_CLOSE( expectedTanRM180, tanRM180, 0.00001f );
    BOOST_CHECK( expectedTanRM135 == tanRM135 );
    BOOST_CHECK( expectedTanRM90 == tanRM90 );
    BOOST_CHECK( expectedTanRM45 == tanRM45 );
    BOOST_CHECK( expectedTanR0 == tanR0 );
    BOOST_CHECK( expectedTanR45 == tanR45 );
    BOOST_CHECK( expectedTanR90 == tanR90 );
    BOOST_CHECK( expectedTanR135 == tanR135 );
    BOOST_CHECK_CLOSE( expectedTanR180, tanR180, 0.00001f );
    BOOST_CHECK_CLOSE( expectedTanR360, tanR360, 0.00001f );
    BOOST_CHECK( expectedTanR720 == tanR720 );
    BOOST_CHECK( expectedTanR20000 == tanR20000 );


    constexpr auto radians = Deg2Rad( 0.001f );
    constexpr auto result1a = Tan( radians );
    auto result1b = std::tan( radians );
    auto result1Diff = result1a - result1b;
    BOOST_CHECK( result1a == result1b );
    BOOST_CHECK( result1a == 1.74532925e-05f );
    BOOST_CHECK( result1b == 1.74532925e-05f );
}

// --run_test=ConstexprMathTests/DoubleTanTest1
BOOST_AUTO_TEST_CASE( DoubleTanTest1 )
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

    constexpr auto tanRM20000 = Tan( rM20000 );
    constexpr auto tanRM720 = Tan( rM720 );
    constexpr auto tanRM360 = Tan( rM360 );
    constexpr auto tanRM180 = Tan( rM180 );
    constexpr auto tanRM135 = Tan( rM135 );
    constexpr auto tanRM90 = Tan( rM90 );
    constexpr auto tanRM45 = Tan( rM45 );
    constexpr auto tanR0 = Tan( r0 );
    constexpr auto tanR45 = Tan( r45 );
    constexpr auto tanR90 = Tan( r90 );
    constexpr auto tanR135 = Tan( r135 );
    constexpr auto tanR180 = Tan( r180 );
    constexpr auto tanR360 = Tan( r360 );
    constexpr auto tanR720 = Tan( r720 );
    constexpr auto tanR20000 = Tan( r20000 );

    auto expectedTanRM20000 = std::tan( rM20000 );
    auto expectedTanRM720 = std::tan( rM720 );
    auto expectedTanRM360 = std::tan( rM360 );
    auto expectedTanRM180 = std::tan( rM180 );
    auto expectedTanRM135 = std::tan( rM135 );
    auto expectedTanRM90 = std::tan( rM90 );
    auto expectedTanRM45 = std::tan( rM45 );
    auto expectedTanR0 = std::tan( r0 );
    auto expectedTanR45 = std::tan( r45 );
    auto expectedTanR90 = std::tan( r90 );
    auto expectedTanR135 = std::tan( r135 );
    auto expectedTanR180 = std::tan( r180 );
    auto expectedTanR360 = std::tan( r360 );
    auto expectedTanR720 = std::tan( r720 );
    auto expectedTanR20000 = std::tan( r20000 );

    BOOST_CHECK( expectedTanRM20000 == tanRM20000 );
    BOOST_CHECK( expectedTanRM720 == tanRM720 );
    BOOST_CHECK_CLOSE( expectedTanRM360, tanRM360, 0.00001f );
    BOOST_CHECK_CLOSE( expectedTanRM180, tanRM180, 0.00001f );
    BOOST_CHECK( expectedTanRM135 == tanRM135 );
    BOOST_CHECK( expectedTanRM90 == tanRM90 );
    BOOST_CHECK( expectedTanRM45 == tanRM45 );
    BOOST_CHECK( expectedTanR0 == tanR0 );
    BOOST_CHECK( expectedTanR45 == tanR45 );
    BOOST_CHECK( expectedTanR90 == tanR90 );
    BOOST_CHECK( expectedTanR135 == tanR135 );
    BOOST_CHECK_CLOSE( expectedTanR180, tanR180, 0.00001f );
    BOOST_CHECK_CLOSE( expectedTanR360, tanR360, 0.00001f );
    BOOST_CHECK( expectedTanR720 == tanR720 );
    BOOST_CHECK( expectedTanR20000 == tanR20000 );


    constexpr auto radians = Deg2Rad( 0.001 );
    constexpr auto result1a = Tan( radians );
    auto result1b = std::tan( radians );
    auto result1Diff = result1a - result1b;
    BOOST_CHECK( result1a == result1b );
    BOOST_CHECK( result1a == 1.7453292521715489e-05 );
    BOOST_CHECK( result1b == 1.7453292521715489e-05 );
}

// --run_test=ConstexprMathTests/FloatASinTest1
BOOST_AUTO_TEST_CASE( FloatASinTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ASin( x );
            return IsSameValue( r, expected );
        };
    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ASin( x );
            return IsNaN( r );
        };

    // asin( inf ) == NaN
    constexpr auto check1 = CheckIsNaN( C::Infinity );
    BOOST_CHECK( check1 );

    // asin (-inf) == NaN
    constexpr auto check2 = CheckIsNaN( -C::Infinity );
    BOOST_CHECK( check2 );

    // asin (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check3 );

    // asin (1.1) == NaN
    constexpr auto check4 = CheckIsNaN( 1.1 );
    BOOST_CHECK( check4 );

    // asin (-1.1) == NaN
    constexpr auto check5 = CheckIsNaN( -1.1 );
    BOOST_CHECK( check5 );

    // asin (0) == 0
    constexpr auto check6 = Check( 0., 0. );
    BOOST_CHECK( check6 );

    // asin (-0) == -0
    constexpr auto check7 = Check( -0., -0. );
    BOOST_CHECK( check7 );

    // asin (0.5) == pi/6
    constexpr auto check8 = Check( 0.5, C::Pi/6.f );
    BOOST_CHECK( check8 );

    // asin (-0.5) == -pi/6
    constexpr auto check9 = Check( -0.5, -C::Pi / 6.f );
    BOOST_CHECK( check9 );

    // asin (1.0) == pi/2
    constexpr auto check10 = Check( 1.0, C::Pi / 2.f );
    BOOST_CHECK( check10 );

    // asin (-1.0) == -pi/2
    constexpr auto check11 = Check( -1.0, -C::Pi / 2.f );
    BOOST_CHECK( check11 );

    // asin (0.7) == 0.77539749661075306374035335271498708
    
    constexpr auto check12 = Check( 0.7, 0.775397539f );
    BOOST_CHECK( check12 );
}

// --run_test=ConstexprMathTests/DoubleASinTest1
BOOST_AUTO_TEST_CASE( DoubleASinTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ASin( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon() * 10 ) -> bool
        {
            auto r = ASin( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ASin( x );
            return IsNaN( r );
        };

    // asin( inf ) == NaN
    constexpr auto check1 = CheckIsNaN( C::Infinity );
    BOOST_CHECK( check1 );

    // asin (-inf) == NaN
    constexpr auto check2 = CheckIsNaN( -C::Infinity );
    BOOST_CHECK( check2 );

    // asin (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check3 );

    // asin (1.1) == NaN
    constexpr auto check4 = CheckIsNaN( 1.1 );
    BOOST_CHECK( check4 );

    // asin (-1.1) == NaN
    constexpr auto check5 = CheckIsNaN( -1.1 );
    BOOST_CHECK( check5 );

    // asin (0) == 0
    constexpr auto check6 = Check( 0., 0. );
    BOOST_CHECK( check6 );

    // asin (-0) == -0
    constexpr auto check7 = Check( -0., -0. );
    BOOST_CHECK( check7 );

    // asin (0.5) == pi/6

    auto res = ASin( 0.5 );
    constexpr auto check8 = CheckClose( 0.5, C::PiOver6 );
    BOOST_CHECK( check8 );

    // asin (-0.5) == -pi/6
    constexpr auto check9 = CheckClose( -0.5, -C::PiOver6 );
    BOOST_CHECK( check9 );

    // asin (1.0) == pi/2
    constexpr auto check10 = CheckClose( 1.0, C::PiOver2 );
    BOOST_CHECK( check10 );

    // asin (-1.0) == -pi/2
    constexpr auto check11 = CheckClose( -1.0, -C::PiOver2 );
    BOOST_CHECK( check11 );

    // asin (0.7) == 0.77539749661075306374035335271498708
    constexpr auto check12 = Check( 0.7, 0.77539749661075306374035335271498708 );
    BOOST_CHECK( check12 );


}

// --run_test=ConstexprMathTests/FloatACosTest1
BOOST_AUTO_TEST_CASE( FloatACosTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ACos( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ACos( x );
            return IsNaN( r );
        };

    // acos (inf) == NaN
    constexpr auto check1 = CheckIsNaN( C::Infinity );
    BOOST_CHECK( check1 );

    // acos (-inf) == NaN
    constexpr auto check2 = CheckIsNaN( C::NegativeInfinity );
    BOOST_CHECK( check2 );

    // acos (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check3 );

    // acos (1.1) == NaN
    constexpr auto check4 = CheckIsNaN( 1.1f );
    BOOST_CHECK( check4 );

    // acos (-1.1) == NaN
    constexpr auto check5 = CheckIsNaN( -1.1f );
    BOOST_CHECK( check5 );

    // acos (0) == pi/2
    constexpr auto check6 = Check( 0.f, C::PiOver2 );
    BOOST_CHECK( check6 );

    // acos (-0) == pi/2
    constexpr auto check7 = Check( -0.f, C::PiOver2 );
    BOOST_CHECK( check7 );

    // acos (1) == 0
    constexpr auto check8 = Check( 1.f, C::Zero );
    BOOST_CHECK( check8 );

    // acos (-1) == pi
    constexpr auto check9 = Check( -1.f, C::Pi );
    BOOST_CHECK( check9 );

    // acos (0.5) == M_PI_6l*2.0
    constexpr auto check10 = Check( 0.5f, 1.04719758f );
    BOOST_CHECK( check10 );

    // acos (-0.5) == M_PI_6l*4.0
    constexpr auto check11 = Check( -0.5f, 2.09439516f );
    BOOST_CHECK( check11 );

    // acos (0.7) == 0.795398831f
    constexpr auto check12 = Check( 0.7f, 0.795398831f );
    BOOST_CHECK( check12 );
}

// --run_test=ConstexprMathTests/DoubleACosTest1
BOOST_AUTO_TEST_CASE( DoubleACosTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ACos( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = ACos( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ACos( x );
            return IsNaN( r );
        };

    // acos (inf) == NaN
    constexpr auto check1 = CheckIsNaN( C::Infinity );
    BOOST_CHECK( check1 );

    // acos (-inf) == NaN
    constexpr auto check2 = CheckIsNaN( C::NegativeInfinity );
    BOOST_CHECK( check2 );

    // acos (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check3 );

    // acos (1.1) == NaN
    constexpr auto check4 = CheckIsNaN( 1.1 );
    BOOST_CHECK( check4 );

    // acos (-1.1) == NaN
    constexpr auto check5 = CheckIsNaN( -1.1 );
    BOOST_CHECK( check5 );

    // acos (0) == pi/2
    constexpr auto check6 = Check( 0., C::PiOver2 );
    BOOST_CHECK( check6 );

    // acos (-0) == pi/2
    constexpr auto check7 = Check( -0., C::PiOver2 );
    BOOST_CHECK( check7 );

    // acos (1) == 0
    constexpr auto check8 = Check( 1., C::Zero );
    BOOST_CHECK( check8 );

    // acos (-1) == pi
    constexpr auto check9 = Check( -1., C::Pi );
    BOOST_CHECK( check9 );

    // acos (0.5) == M_PI_6l*2.0
    constexpr auto check10 = CheckClose( 0.5, C::PiOver6 * 2. );
    BOOST_CHECK( check10 );

    // acos (-0.5) == M_PI_6l*4.0
    constexpr auto check11 = CheckClose( -0.5, C::PiOver6 * 4. );
    BOOST_CHECK( check11 );

    // acos (0.7) == 0.79539883018414355549096833892476432
    constexpr auto check12 = Check( 0.7, 0.79539883018414355549096833892476432 );
    BOOST_CHECK( check12 );


}

// --run_test=ConstexprMathTests/FloatATanTest1
BOOST_AUTO_TEST_CASE( FloatATanTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ATan( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ATan( x );
            return IsNaN( r );
        };

    // atan (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    BOOST_CHECK( check1 );

    // atan (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    BOOST_CHECK( check2 );

    // atan (inf) == pi/2
    constexpr auto check3 = Check( C::Infinity, C::PiOver2 );
    BOOST_CHECK( check3 );

    // atan (-inf) == -pi/2
    constexpr auto check4 = Check( -C::Infinity, -C::PiOver2 );
    BOOST_CHECK( check4 );

    // atan (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    // atan (1) == pi/4
    constexpr auto check6 = Check( C::One, C::PiOver4 );
    BOOST_CHECK( check6 );

    // atan (-1) == -pi/4
    constexpr auto check7 = Check( -C::One, -C::PiOver4 );
    BOOST_CHECK( check7 );

    // atan (0.7) == 0.610725939f
    constexpr auto check8 = Check( 0.7, 0.610725939f );
    BOOST_CHECK( check8 );
}

// --run_test=ConstexprMathTests/DoubleATanTest1
BOOST_AUTO_TEST_CASE( DoubleATanTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ATan( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ATan( x );
            return IsNaN( r );
        };

    // atan (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    BOOST_CHECK( check1 );

    // atan (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    BOOST_CHECK( check2 );

    // atan (inf) == pi/2
    constexpr auto check3 = Check( C::Infinity, C::PiOver2 );
    BOOST_CHECK( check3 );

    // atan (-inf) == -pi/2
    constexpr auto check4 = Check( -C::Infinity, -C::PiOver2 );
    BOOST_CHECK( check4 );

    // atan (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    // atan (1) == pi/4
    constexpr auto check6 = Check( C::One, C::PiOver4 );
    BOOST_CHECK( check6 );

    // atan (-1) == -pi/4
    constexpr auto check7 = Check( -C::One, -C::PiOver4 );
    BOOST_CHECK( check7 );

    // atan (0.7) == 0.61072596438920861654375887649023613
    constexpr auto check8 = Check( 0.7, 0.61072596438920861654375887649023613 );
    BOOST_CHECK( check8 );
}

// --run_test=ConstexprMathTests/FloatATan2Test1
BOOST_AUTO_TEST_CASE( FloatATan2Test1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected ) -> bool
        {
            auto r = ATan2( x, y );
            return IsSameValue( r, expected );
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = ATan2( x, y );
            return IsNaN( r );
        };

    // atan2 (0,x) == 0 for x > 0
    // atan2 (0, 1) == 0
    constexpr auto check1 = Check( 0, 1., 0 );
    BOOST_CHECK( check1 );

    // atan2 (-0,x) == -0 for x > 0
    // atan2 (-0, 1) == -0
    constexpr auto check2 = Check( -0, 1., -0 );
    BOOST_CHECK( check2 );

    // atan2 (0, 0) == 0
    constexpr auto check3 = Check( 0, 0., 0 );
    BOOST_CHECK( check3 );

    // atan2 (-0, 0) == -0
    constexpr auto check4 = Check( -0., 0., -0. );
    BOOST_CHECK( check4 );

    // atan2 (+0,x) == +pi for x < 0
    // atan2 (0, -1) == pi
    constexpr auto check5 = Check( 0., -1., C::Pi );
    BOOST_CHECK( check5 );


    // atan2 (-0,x) == -pi for x < 0
    // atan2 (-0, -1) == -pi
    constexpr auto check6 = Check( -0., -1., -C::Pi );
    BOOST_CHECK( check6 );


    // atan2 (0, -0) == pi
    constexpr auto check7 = Check( 0., -0., C::Pi );
    BOOST_CHECK( check7 );

    // atan2 (-0, -0) == -pi
    constexpr auto check8 = Check( -0., -0., -C::Pi );
    BOOST_CHECK( check8 );

    // atan2 (y,+0) == pi/2 for y > 0
    // atan2 (1, 0) == pi/2
    constexpr auto check9 = Check( 1., 0., C::PiOver2 );
    BOOST_CHECK( check9 );

    // atan2 (y,-0) == pi/2 for y > 0
    // atan2 (1, -0) == pi/2
    constexpr auto check10 = Check( 1., -0., C::PiOver2 );
    BOOST_CHECK( check10 );

    // atan2 (y,+0) == -pi/2 for y < 0
    // atan2 (-1, 0) == -pi/2
    constexpr auto check11 = Check( -1., 0., -C::PiOver2 );
    BOOST_CHECK( check11 );

    // atan2 (y,-0) == -pi/2 for y < 0
    // atan2 (-1, -0) == -pi/2
    constexpr auto check12 = Check( -1., -0., -C::PiOver2 );
    BOOST_CHECK( check12 );

    // atan2 (y,inf) == +0 for finite y > 0
    // atan2 (1, inf) == 0
    constexpr auto check13 = Check( 1., C::Infinity, C::Zero );
    BOOST_CHECK( check13 );

    // atan2 (y,inf) == -0 for finite y < 0
    // atan2 (-1, inf) == -0
    constexpr auto check14 = Check( -1., C::Infinity, -C::Zero );
    BOOST_CHECK( check14 );

    // atan2(+inf, x) == pi/2 for finite x
    // atan2 (inf, -1) == pi/2
    constexpr auto check15 = Check( C::Infinity, -1., C::PiOver2 );
    BOOST_CHECK( check15 );

    // atan2(-inf, x) == -pi/2 for finite x
    // atan2 (-inf, 1) == -pi/2
    constexpr auto check16 = Check( -C::Infinity, 1., -C::PiOver2 );
    BOOST_CHECK( check16 );

    // atan2 (y,-inf) == +pi for finite y > 0
    // atan2 (1, -inf) == pi
    constexpr auto check17 = Check( 1., -C::Infinity, C::Pi );
    BOOST_CHECK( check17 );

    // atan2 (y,-inf) == -pi for finite y < 0
    // atan2 (-1, -inf) == -pi
    constexpr auto check18 = Check( -1., -C::Infinity, -C::Pi );
    BOOST_CHECK( check18 );

    // atan2 (inf, inf) == pi/4
    constexpr auto check19 = Check( C::Infinity, C::Infinity, C::PiOver4 );
    BOOST_CHECK( check19 );

    // atan2 (-inf, inf) == -pi/4
    constexpr auto check20 = Check( -C::Infinity, C::Infinity, -C::PiOver4 );
    BOOST_CHECK( check20 );

    // atan2 (inf, -inf) == 3/4 pi
    constexpr auto check21 = Check( C::Infinity, -C::Infinity, 3.*C::PiOver4 );
    BOOST_CHECK( check21 );


    // atan2 (-inf, -inf) == -3/4 pi
    constexpr auto check22 = Check( -C::Infinity, -C::Infinity, -3. * C::PiOver4 );
    BOOST_CHECK( check22 );

    // atan2 (NaN, NaN) == NaN
    constexpr auto check23 = CheckIsNaN( C::NaN, C::NaN );
    BOOST_CHECK( check23 );

    // atan2 (0.7, 1) == 0.610725939f
    constexpr auto check24 = Check( 0.7f, 1.f, 0.610725939f );
    BOOST_CHECK( check24 );

    // atan2 (-0.7, 1.0) == -0.610725939f
    constexpr auto check25 = Check( -0.7f, 1.f, -0.610725939f );
    BOOST_CHECK( check25 );

    // atan2 (0.7, -1.0) == 2.53086662f
    constexpr auto check26 = Check( 0.7f, -1.f, 2.53086662f );
    BOOST_CHECK( check26 );

    // atan2 (-0.7, -1.0) == -2.53086662f
    constexpr auto check27 = Check( -0.7f, -1.f, -2.53086662f );
    BOOST_CHECK( check27 );

    // atan2 (0.4, 0.0003) == 1.57004631
    constexpr auto check28 = Check( 0.4f, 0.0003f, 1.57004631f );
    BOOST_CHECK( check28 );

    // atan2 (1.4, -0.93) == 2.15714884f
    constexpr auto check29 = Check( 1.4f, -0.93f, 2.15714884f );
    BOOST_CHECK( check29 );
}

// --run_test=ConstexprMathTests/DoubleATan2Test1
BOOST_AUTO_TEST_CASE( DoubleATan2Test1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected ) -> bool
        {
            auto r = ATan2( x, y );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType y, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = ATan2( x, y );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = ATan2( x, y );
            return IsNaN( r );
        };

    // atan2 (0,x) == 0 for x > 0
    // atan2 (0, 1) == 0
    constexpr auto check1 = Check( 0, 1., 0 );
    BOOST_CHECK( check1 );

    // atan2 (-0,x) == -0 for x > 0
    // atan2 (-0, 1) == -0
    constexpr auto check2 = Check( -0, 1., -0 );
    BOOST_CHECK( check2 );

    // atan2 (0, 0) == 0
    constexpr auto check3 = Check( 0, 0., 0 );
    BOOST_CHECK( check3 );

    // atan2 (-0, 0) == -0
    constexpr auto check4 = Check( -0., 0., -0. );
    BOOST_CHECK( check4 );

    // atan2 (+0,x) == +pi for x < 0
    // atan2 (0, -1) == pi
    constexpr auto check5 = Check( 0., -1., C::Pi );
    BOOST_CHECK( check5 );


    // atan2 (-0,x) == -pi for x < 0
    // atan2 (-0, -1) == -pi
    constexpr auto check6 = Check( -0., -1., -C::Pi );
    BOOST_CHECK( check6 );


    // atan2 (0, -0) == pi
    constexpr auto check7 = Check( 0., -0., C::Pi );
    BOOST_CHECK( check7 );

    // atan2 (-0, -0) == -pi
    constexpr auto check8 = Check( -0., -0., -C::Pi );
    BOOST_CHECK( check8 );

    // atan2 (y,+0) == pi/2 for y > 0
    // atan2 (1, 0) == pi/2
    constexpr auto check9 = Check( 1., 0., C::PiOver2 );
    BOOST_CHECK( check9 );

    // atan2 (y,-0) == pi/2 for y > 0
    // atan2 (1, -0) == pi/2
    constexpr auto check10 = Check( 1., -0., C::PiOver2 );
    BOOST_CHECK( check10 );

    // atan2 (y,+0) == -pi/2 for y < 0
    // atan2 (-1, 0) == -pi/2
    constexpr auto check11 = Check( -1., 0., -C::PiOver2 );
    BOOST_CHECK( check11 );

    // atan2 (y,-0) == -pi/2 for y < 0
    // atan2 (-1, -0) == -pi/2
    constexpr auto check12 = Check( -1., -0., -C::PiOver2 );
    BOOST_CHECK( check12 );

    // atan2 (y,inf) == +0 for finite y > 0
    // atan2 (1, inf) == 0
    constexpr auto check13 = Check( 1., C::Infinity, C::Zero );
    BOOST_CHECK( check13 );

    // atan2 (y,inf) == -0 for finite y < 0
    // atan2 (-1, inf) == -0
    constexpr auto check14 = Check( -1., C::Infinity, -C::Zero );
    BOOST_CHECK( check14 );

    // atan2(+inf, x) == pi/2 for finite x
    // atan2 (inf, -1) == pi/2
    constexpr auto check15 = Check( C::Infinity, -1., C::PiOver2 );
    BOOST_CHECK( check15 );

    // atan2(-inf, x) == -pi/2 for finite x
    // atan2 (-inf, 1) == -pi/2
    constexpr auto check16 = Check( -C::Infinity, 1., -C::PiOver2 );
    BOOST_CHECK( check16 );

    // atan2 (y,-inf) == +pi for finite y > 0
    // atan2 (1, -inf) == pi
    constexpr auto check17 = Check( 1., -C::Infinity, C::Pi );
    BOOST_CHECK( check17 );

    // atan2 (y,-inf) == -pi for finite y < 0
    // atan2 (-1, -inf) == -pi
    constexpr auto check18 = Check( -1., -C::Infinity, -C::Pi );
    BOOST_CHECK( check18 );

    // atan2 (inf, inf) == pi/4
    constexpr auto check19 = Check( C::Infinity, C::Infinity, C::PiOver4 );
    BOOST_CHECK( check19 );

    // atan2 (-inf, inf) == -pi/4
    constexpr auto check20 = Check( -C::Infinity, C::Infinity, -C::PiOver4 );
    BOOST_CHECK( check20 );

    // atan2 (inf, -inf) == 3/4 pi
    constexpr auto check21 = Check( C::Infinity, -C::Infinity, 3. * C::PiOver4 );
    BOOST_CHECK( check21 );


    // atan2 (-inf, -inf) == -3/4 pi
    constexpr auto check22 = Check( -C::Infinity, -C::Infinity, -3. * C::PiOver4 );
    BOOST_CHECK( check22 );

    // atan2 (NaN, NaN) == NaN
    constexpr auto check23 = CheckIsNaN( C::NaN, C::NaN );
    BOOST_CHECK( check23 );

    // atan2 (0.7, 1) == 0.61072596438920861654375887649023613
    constexpr auto check24 = Check( 0.7, 1, 0.61072596438920861654375887649023613 );
    BOOST_CHECK( check24 );

    // atan2 (-0.7, 1.0) == -0.61072596438920861654375887649023613
    constexpr auto check25 = Check( -0.7, 1, -0.61072596438920861654375887649023613 );
    BOOST_CHECK( check25 );

    // atan2 (0.7, -1.0) == 2.530866689200584621918884506789267
    constexpr auto check26 = Check( 0.7, -1, 2.530866689200584621918884506789267 );
    BOOST_CHECK( check26 );

    // atan2 (-0.7, -1.0) == -2.530866689200584621918884506789267
    constexpr auto check27 = Check( -0.7, -1, -2.530866689200584621918884506789267 );
    BOOST_CHECK( check27 );

    // atan2 (0.4, 0.0003) == 1.5700463269355215717704032607580829
    constexpr auto check28 = Check( 0.4, 0.0003, 1.5700463269355215717704032607580829 );
    BOOST_CHECK( check28 );

    // atan2 (1.4, -0.93) == 2.1571487668237843754887415992772736
    constexpr auto check29 = Check( 1.4, -0.93, 2.1571487668237843754887415992772736 );
    BOOST_CHECK( check29 );
}

// --run_test=ConstexprMathTests/FloatSinCosTest1
BOOST_AUTO_TEST_CASE( FloatSinCosTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expectedSine, C::ValueType expectedCosine ) -> bool
        {
            C::ValueType sine, cosine;
            SinCos( x, &sine, &cosine );
            return IsSameValue( sine, expectedSine ) && IsSameValue( cosine, expectedCosine );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expectedSine, C::ValueType expectedCosine, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            C::ValueType sine, cosine;
            SinCos( x, &sine, &cosine );
            return AreNearlyEqual( sine, expectedSine, epsilon ) && AreNearlyEqual( cosine, expectedCosine, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            C::ValueType sine, cosine;
            SinCos( x, &sine, &cosine );
            return IsNaN( sine ) && IsNaN( cosine );
        };

    constexpr auto check1 = Check( 0, 0, 1 );
    BOOST_CHECK( check1 );

    constexpr auto check2 = Check( -0., -0., 1 );
    BOOST_CHECK( check2 );


    constexpr auto check3 = CheckIsNaN( C::Infinity );
    BOOST_CHECK( check3 );

    constexpr auto check4 = CheckIsNaN( C::NegativeInfinity );
    BOOST_CHECK( check4 );

    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    constexpr auto check6 = CheckClose( C::PiOver2, 1., 0. );
    BOOST_CHECK( check6 );

    constexpr auto check7 = Check( C::PiOver6, 0.5, 0.86602540378443864676372317075293616f );
    BOOST_CHECK( check7 );

    constexpr auto check8 = CheckClose( 2* C::PiOver6, 0.86602540378443864676372317075293616f, 0.5f );
    BOOST_CHECK( check8 );

    constexpr auto check9 = Check( 0.7, 0.64421768723769105367261435139872014f, 0.76484218728448842625585999019186495f );
    BOOST_CHECK( check9 );

}

// --run_test=ConstexprMathTests/DoubleSinCosTest1
BOOST_AUTO_TEST_CASE( DoubleSinCosTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expectedSine, C::ValueType expectedCosine ) -> bool
        {
            C::ValueType sine, cosine;
            SinCos( x, &sine, &cosine );
            return IsSameValue( sine, expectedSine ) && IsSameValue( cosine, expectedCosine );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expectedSine, C::ValueType expectedCosine, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            C::ValueType sine, cosine;
            SinCos( x, &sine, &cosine );
            return AreNearlyEqual( sine, expectedSine, epsilon ) && AreNearlyEqual( cosine, expectedCosine, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            C::ValueType sine, cosine;
            SinCos( x, &sine, &cosine );
            return IsNaN( sine ) && IsNaN( cosine );
        };

    constexpr auto check1 = Check( 0, 0, 1 );
    BOOST_CHECK( check1 );

    constexpr auto check2 = Check( -0., -0., 1 );
    BOOST_CHECK( check2 );


    constexpr auto check3 = CheckIsNaN( C::Infinity );
    BOOST_CHECK( check3 );

    constexpr auto check4 = CheckIsNaN( C::NegativeInfinity );
    BOOST_CHECK( check4 );

    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    constexpr auto check6 = CheckClose( C::PiOver2, 1., 0. );
    BOOST_CHECK( check6 );

    constexpr auto check7 = CheckClose( C::PiOver6, 0.5, 0.86602540378443864676372317075293616 );
    BOOST_CHECK( check7 );

    constexpr auto check8 = CheckClose( 2 * C::PiOver6, 0.86602540378443864676372317075293616, 0.5 );
    BOOST_CHECK( check8 );

    constexpr auto check9 = CheckClose( 0.7, 0.64421768723769105367261435139872014, 0.76484218728448842625585999019186495 );
    BOOST_CHECK( check9 );

}

// --run_test=ConstexprMathTests/FloatSinHTest1
BOOST_AUTO_TEST_CASE( FloatSinHTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = SinH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = SinH( x );
            return IsNaN( r );
        };

    // sinh (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    BOOST_CHECK( check1 );

    // sinh (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    BOOST_CHECK( check2 );

    // sinh (inf) == inf
    constexpr auto check3 = Check( C::Infinity, C::Infinity );
    BOOST_CHECK( check3 );

    // sinh (-inf) == -inf
    constexpr auto check4 = Check( -C::Infinity, -C::Infinity );
    BOOST_CHECK( check4 );

    // sinh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    // sinh (0.7) == 0.758583665f
    constexpr auto check6 = Check( 0.7f, 0.758583665f );
    BOOST_CHECK( check6 );

}

// --run_test=ConstexprMathTests/DoubleSinHTest1
BOOST_AUTO_TEST_CASE( DoubleSinHTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = SinH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = SinH( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = SinH( x );
            return IsNaN( r );
        };

    // sinh (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    BOOST_CHECK( check1 );

    // sinh (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    BOOST_CHECK( check2 );

    // sinh (inf) == inf
    constexpr auto check3 = Check( C::Infinity, C::Infinity );
    BOOST_CHECK( check3 );

    // sinh (-inf) == -inf
    constexpr auto check4 = Check( -C::Infinity, -C::Infinity );
    BOOST_CHECK( check4 );

    // sinh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    // sinh (0.7) == 0.75858370183953350346
    constexpr auto check6 = CheckClose( 0.7, 0.75858370183953350346 );
    BOOST_CHECK( check6 );

}


// --run_test=ConstexprMathTests/FloatASinHTest1
BOOST_AUTO_TEST_CASE( FloatASinHTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ASinH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ASinH( x );
            return IsNaN( r );
        };

    // asinh (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    BOOST_CHECK( check1 );

    // asinh (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    BOOST_CHECK( check2 );

    // asinh (inf) == inf
    constexpr auto check3 = Check( C::Infinity, C::Infinity );
    BOOST_CHECK( check3 );

    // asinh (-inf) == -inf
    constexpr auto check4 = Check( -C::Infinity, -C::Infinity );
    BOOST_CHECK( check4 );

    // asinh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    // asinh (0.7) == 0.652666569f
    constexpr auto check6 = Check( 0.7f, 0.652666569f );
    BOOST_CHECK( check6 );
}

// --run_test=ConstexprMathTests/DoubleASinHTest1
BOOST_AUTO_TEST_CASE( DoubleASinHTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ASinH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = ASinH( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ASinH( x );
            return IsNaN( r );
        };

    // asinh (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    BOOST_CHECK( check1 );

    // asinh (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    BOOST_CHECK( check2 );

    // asinh (inf) == inf
    constexpr auto check3 = Check( C::Infinity, C::Infinity );
    BOOST_CHECK( check3 );

    // asinh (-inf) == -inf
    constexpr auto check4 = Check( -C::Infinity, -C::Infinity );
    BOOST_CHECK( check4 );

    // asinh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    // asinh (0.7) == 0.652666566082355786
    constexpr auto check6 = Check( 0.7, 0.652666566082355786 );
    BOOST_CHECK( check6 );
}

// --run_test=ConstexprMathTests/FloatCosHTest1
BOOST_AUTO_TEST_CASE( FloatCosHTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = CosH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = CosH( x );
            return IsNaN( r );
        };

    // cosh (0) == 1
    constexpr auto check1 = Check( 0.f, 1.f );
    BOOST_CHECK( check1 );

    // cosh (-0) == 1
    constexpr auto check2 = Check( -0.f, 1.f );
    BOOST_CHECK( check2 );

    // cosh (inf) == inf
    constexpr auto check3 = Check( C::Infinity, C::Infinity );
    BOOST_CHECK( check3 );

    // cosh (-inf) == inf
    constexpr auto check4 = Check( -C::Infinity, C::Infinity );
    BOOST_CHECK( check4 );

    // cosh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    // cosh (0.7) == 1.25516903f
    constexpr auto check6 = Check( 0.7f, 1.25516903f );
    BOOST_CHECK( check6 );

}

// --run_test=ConstexprMathTests/DoubleCosHTest1
BOOST_AUTO_TEST_CASE( DoubleCosHTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = CosH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = CosH( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = CosH( x );
            return IsNaN( r );
        };

    // cosh (0) == 1
    constexpr auto check1 = Check( 0., 1. );
    BOOST_CHECK( check1 );

    // cosh (-0) == 1
    constexpr auto check2 = Check( -0., 1. );
    BOOST_CHECK( check2 );

    // cosh (inf) == inf
    constexpr auto check3 = Check( C::Infinity, C::Infinity );
    BOOST_CHECK( check3 );

    // cosh (-inf) == inf
    constexpr auto check4 = Check( -C::Infinity, C::Infinity );
    BOOST_CHECK( check4 );

    // cosh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    // cosh (0.7) == 1.255169005630943018
    constexpr auto check6 = Check( 0.7, 1.255169005630943018 );
    BOOST_CHECK( check6 );

}

// --run_test=ConstexprMathTests/FloatACosHTest1
BOOST_AUTO_TEST_CASE( FloatACosHTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ACosH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ACosH( x );
            return IsNaN( r );
        };

    // acosh (inf) == inf
    constexpr auto check1 = Check( C::Infinity, C::Infinity );
    BOOST_CHECK( check1 );

    // acosh (-inf) == NaN
    constexpr auto check2 = CheckIsNaN( -C::Infinity );
    BOOST_CHECK( check2 );

    // acosh (-1.1) == NaN
    constexpr auto check3 = CheckIsNaN( -1.1 );
    BOOST_CHECK( check3 );

    // acosh (1) == 0
    constexpr auto check4 = Check( C::One, C::Zero );
    BOOST_CHECK( check4 );

    // acosh (7) == 2.63391590f
    constexpr auto check5 = Check( 7.f, 2.63391590f );
    BOOST_CHECK( check5 );

}

// --run_test=ConstexprMathTests/DoubleACosHTest1
BOOST_AUTO_TEST_CASE( DoubleACosHTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ACosH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = ACosH( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ACosH( x );
            return IsNaN( r );
        };

    // acosh (inf) == inf
    constexpr auto check1 = Check( C::Infinity, C::Infinity );
    BOOST_CHECK( check1 );

    // acosh (-inf) == NaN
    constexpr auto check2 = CheckIsNaN( -C::Infinity );
    BOOST_CHECK( check2 );

    // acosh (-1.1) == NaN
    constexpr auto check3 = CheckIsNaN( -1.1 );
    BOOST_CHECK( check3 );

    // acosh (1) == 0
    constexpr auto check4 = Check( C::One, C::Zero );
    BOOST_CHECK( check4 );

    // acosh (7) == 2.633915793849633417250092694615937
    constexpr auto check5 = Check( 7., 2.633915793849633417250092694615937 );
    BOOST_CHECK( check5 );

}


// --run_test=ConstexprMathTests/FloatTanHTest1
BOOST_AUTO_TEST_CASE( FloatTanHTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = TanH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = TanH( x );
            return IsNaN( r );
        };

    // tanh (0) == 0
    constexpr auto check1 = Check( C::Zero, C::Zero );
    BOOST_CHECK( check1 );

    // tanh (-0) == -0
    constexpr auto check2 = Check( -C::Zero, -C::Zero );
    BOOST_CHECK( check2 );

    // tanh (inf) == 1
    constexpr auto check3 = Check( C::Infinity, C::One );
    BOOST_CHECK( check3 );

    // tanh (NaN) == NaN
    constexpr auto check4 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check4 );

    // tanh (0.7) == 0.604367733f
    constexpr auto check5 = Check( 0.7f, 0.604367733f );
    BOOST_CHECK( check5 );

    // tanh (-0.7) == -0.604367733f
    constexpr auto check6 = Check( -0.7f, -0.604367733f );
    BOOST_CHECK( check6 );

    // tanh (1.0) == 0.761594176f
    constexpr auto check7 = Check( 1.f, 0.761594176f );
    BOOST_CHECK( check7 );

    // tanh (-1.0) == -0.761594176f
    constexpr auto check8 = Check( -1., -0.761594176f );
    BOOST_CHECK( check8 );

    // tanh (6.93889390e-18) == 6.93889390e-18
    constexpr auto check9 = Check( 6.93889390e-18f, 6.93889390e-18f );
    BOOST_CHECK( check9 );
}

// --run_test=ConstexprMathTests/DoubleTanHTest1
BOOST_AUTO_TEST_CASE( DoubleTanHTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = TanH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = TanH( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = TanH( x );
            return IsNaN( r );
        };

    // tanh (0) == 0
    constexpr auto check1 = Check( C::Zero, C::Zero );
    BOOST_CHECK( check1 );

    // tanh (-0) == -0
    constexpr auto check2 = Check( -C::Zero, -C::Zero );
    BOOST_CHECK( check2 );

    // tanh (inf) == 1
    constexpr auto check3 = Check( C::Infinity, C::One );
    BOOST_CHECK( check3 );

    // tanh (NaN) == NaN
    constexpr auto check4 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check4 );

    // tanh (0.7) == 0.60436777711716349631
    constexpr auto check5 = CheckClose( 0.7, 0.60436777711716349631 );
    BOOST_CHECK( check5 );

    // tanh (-0.7) == -0.60436777711716349631
    constexpr auto check6 = CheckClose( -0.7, -0.60436777711716349631 );
    BOOST_CHECK( check6 );

    // tanh (1.0) == 0.7615941559557648881194582826047935904
    constexpr auto check7 = Check( 1., 0.7615941559557648881194582826047935904 );
    BOOST_CHECK( check7 );

    // tanh (-1.0) == -0.7615941559557648881194582826047935904
    constexpr auto check8 = Check( -1., -0.7615941559557648881194582826047935904 );
    BOOST_CHECK( check8 );

    // tanh (6.938893903907228377647697925567626953125e-18) == 6.938893903907228377647697925567626953125e-18
    constexpr auto check9 = Check( 6.938893903907228377647697925567626953125e-18, 6.938893903907228377647697925567626953125e-18 );
    BOOST_CHECK( check9 );
}

// --run_test=ConstexprMathTests/FloatATanHTest1
BOOST_AUTO_TEST_CASE( FloatATanHTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ATanH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ATanH( x );
            return IsNaN( r );
        };

    // atanh (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    BOOST_CHECK( check1 );

    // atanh (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    BOOST_CHECK( check2 );

    // atanh (1) == inf
    constexpr auto check3 = Check( 1., C::Infinity );
    BOOST_CHECK( check3 );

    // atanh (-1) == -inf
    constexpr auto check4 = Check( -1., -C::Infinity );
    BOOST_CHECK( check4 );

    // atanh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );
    // atanh (1.1) == NaN
    constexpr auto check6 = CheckIsNaN( 1.1 );
    BOOST_CHECK( check6 );

    // atanh (-1.1) == NaN
    constexpr auto check7 = CheckIsNaN( -1.1 );
    BOOST_CHECK( check7 );

    // atanh (0.7) == 0.867300510f
    constexpr auto check8 = Check( 0.7, 0.867300510f );
    BOOST_CHECK( check8 );
}

// --run_test=ConstexprMathTests/DoubleATanHTest1
BOOST_AUTO_TEST_CASE( DoubleATanHTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ATanH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = ATanH( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ATanH( x );
            return IsNaN( r );
        };

    // atanh (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    BOOST_CHECK( check1 );

    // atanh (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    BOOST_CHECK( check2 );

    // atanh (1) == inf
    constexpr auto check3 = Check( 1., C::Infinity );
    BOOST_CHECK( check3 );

    // atanh (-1) == -inf
    constexpr auto check4 = Check( -1., -C::Infinity );
    BOOST_CHECK( check4 );

    // atanh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );
    // atanh (1.1) == NaN
    constexpr auto check6 = CheckIsNaN( 1.1 );
    BOOST_CHECK( check6 );

    // atanh (-1.1) == NaN
    constexpr auto check7 = CheckIsNaN( -1.1 );
    BOOST_CHECK( check7 );

    // atanh (0.7) == 0.8673005276940531944
    constexpr auto check8 = CheckClose( 0.7, 0.8673005276940531944 );
    BOOST_CHECK( check8 );
}

// --run_test=ConstexprMathTests/FloatJ0Test1
BOOST_AUTO_TEST_CASE( FloatJ0Test1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = J0( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = J0( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = J0( x );
            return IsNaN( r );
        };

    // j0 (NaN) == NaN
    constexpr auto check1 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check1 );

    // j0 (inf) == 0
    constexpr auto check2 = Check( C::Infinity, 0. );
    BOOST_CHECK( check2 );

    // j0 (-1.0) == 0.76519768655796655145
    constexpr auto check3 = Check( -C::One, 0.76519768655796655145 );
    BOOST_CHECK( check3 );

    // j0 (0.0) == 1.0
    constexpr auto check4 = Check( C::Zero, 1.0 );
    BOOST_CHECK( check4 );

    // j0( 0.1 ) == 0.99750156206604003228
    constexpr auto check5 = Check( 0.1, 0.99750156206604003228 );
    BOOST_CHECK( check5 );
    
    // j0( 0.7 ) == 0.88120088860740528084
    constexpr auto check6 = Check( 0.7, 0.88120088860740528084 );
    BOOST_CHECK( check6 );

    // j0( 1.0 ) == 0.76519768655796655145
    constexpr auto check7 = Check( C::One, 0.76519768655796655145 );
    BOOST_CHECK( check7 );

    // j0( 1.5 ) == 0.51182767173591812875
    constexpr auto check8 = Check( 1.5, 0.51182767173591812875 );
    BOOST_CHECK( check8 );

    // j0( 2.0 ) == 0.22389077914123566805
    constexpr auto check9 = CheckClose( 2.0, 0.22389077914123566805 );
    BOOST_CHECK( check9 );

    // j0( 8.0 ) == 0.17165080713755390609
    constexpr auto check10 = CheckClose( 8.0, 0.17165080713755390609 );
    BOOST_CHECK( check10 );

    // j0 (10.0) == -0.24593576445134833520
    constexpr auto check11 = CheckClose( 10.0, -0.24593576445134833520 );
    BOOST_CHECK( check11 );
}

// --run_test=ConstexprMathTests/DoubleJ0Test1
BOOST_AUTO_TEST_CASE( DoubleJ0Test1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = J0( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = J0( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = J0( x );
            return IsNaN( r );
        };

    // j0 (NaN) == NaN
    constexpr auto check1 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check1 );

    // j0 (inf) == 0
    constexpr auto check2 = Check( C::Infinity, 0. );
    BOOST_CHECK( check2 );

    // j0 (-1.0) == 0.76519768655796655145
    constexpr auto check3 = Check( -C::One, 0.76519768655796655145 );
    BOOST_CHECK( check3 );

    // j0 (0.0) == 1.0
    constexpr auto check4 = Check( C::Zero, 1.0 );
    BOOST_CHECK( check4 );

    // j0( 0.1 ) == 0.99750156206604003228
    constexpr auto check5 = Check( 0.1, 0.99750156206604003228 );
    BOOST_CHECK( check5 );

    // j0( 0.7 ) == 0.88120088860740528084
    constexpr auto check6 = Check( 0.7, 0.88120088860740528084 );
    BOOST_CHECK( check6 );

    // j0( 1.0 ) == 0.76519768655796655145
    constexpr auto check7 = Check( C::One, 0.76519768655796655145 );
    BOOST_CHECK( check7 );

    // j0( 1.5 ) == 0.51182767173591812875
    constexpr auto check8 = Check( 1.5, 0.51182767173591812875 );
    BOOST_CHECK( check8 );

    // j0( 2.0 ) == 0.22389077914123566805
    constexpr auto check9 = Check( 2.0, 0.22389077914123566805 );
    BOOST_CHECK( check9 );

    // j0( 8.0 ) == 0.17165080713755390609
    constexpr auto check10 = Check( 8.0, 0.17165080713755390609 );
    BOOST_CHECK( check10 );

    // j0 (10.0) == -0.24593576445134833520
    constexpr auto check11 = CheckClose( 10.0, -0.24593576445134833520 );
    BOOST_CHECK( check11 );
}

// --run_test=ConstexprMathTests/FloatJ1Test1
BOOST_AUTO_TEST_CASE( FloatJ1Test1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = J1( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = J1( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = J1( x );
            return IsNaN( r );
        };

    // j1 (NaN) == NaN
    constexpr auto check1 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check1 );

    // j1 (inf) == 0
    constexpr auto check2 = Check( C::Infinity, 0. );
    BOOST_CHECK( check2 );

    // j1 (-1.0) == -0.44005058574493351596
    constexpr auto check3 = Check( -1.0, -0.44005058574493351596 );
    BOOST_CHECK( check3 );
    
    // j1 (0.0) == 0.0
    constexpr auto check4 = Check( 0.0, 0.0 );
    BOOST_CHECK( check4 );

    // j1 (0.1) == 0.049937526036241997556
    constexpr auto check5 = Check( 0.1, 0.049937526036241997556 );
    BOOST_CHECK( check5 );

    // j1 (0.7) == 0.32899574154005894785
    constexpr auto check6 = Check( 0.7, 0.32899574154005894785 );
    BOOST_CHECK( check6 );

    // j1 (1.0) == 0.44005058574493351596
    constexpr auto check7 = Check( 1.0, 0.44005058574493351596 );
    BOOST_CHECK( check7 );

    // j1 (1.5) == 0.55793650791009964199
    constexpr auto check8 = Check( 1.5, 0.55793650791009964199 );
    BOOST_CHECK( check8 );

    // j1 (2.0) == 0.57672480775687338720
    constexpr auto check9 = Check( 2.0, 0.57672480775687338720 );
    BOOST_CHECK( check9 );

    // j1 (8.0) == 0.23463634685391462438
    constexpr auto check10 = Check( 8.0, 0.23463634685391462438 );
    BOOST_CHECK( check10 );

    // j1 (10.0) == 0.043472746168861436670
    constexpr auto check11 = CheckClose( 10.0, 0.043472746168861436670 );
    BOOST_CHECK( check11 );

}

// --run_test=ConstexprMathTests/DoubleJ1Test1
BOOST_AUTO_TEST_CASE( DoubleJ1Test1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = J1( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = J1( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = J1( x );
            return IsNaN( r );
        };

    // j1 (NaN) == NaN
    constexpr auto check1 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check1 );

    // j1 (inf) == 0
    constexpr auto check2 = Check( C::Infinity, 0. );
    BOOST_CHECK( check2 );

    // j1 (-1.0) == -0.44005058574493351596
    constexpr auto check3 = Check( -1.0, -0.44005058574493351596 );
    BOOST_CHECK( check3 );

    // j1 (0.0) == 0.0
    constexpr auto check4 = Check( 0.0, 0.0 );
    BOOST_CHECK( check4 );

    // j1 (0.1) == 0.049937526036241997556
    constexpr auto check5 = Check( 0.1, 0.049937526036241997556 );
    BOOST_CHECK( check5 );

    // j1 (0.7) == 0.32899574154005894785
    constexpr auto check6 = Check( 0.7, 0.32899574154005894785 );
    BOOST_CHECK( check6 );

    // j1 (1.0) == 0.44005058574493351596
    constexpr auto check7 = Check( 1.0, 0.44005058574493351596 );
    BOOST_CHECK( check7 );

    // j1 (1.5) == 0.55793650791009964199
    constexpr auto check8 = Check( 1.5, 0.55793650791009964199 );
    BOOST_CHECK( check8 );

    // j1 (2.0) == 0.57672480775687338720
    constexpr auto check9 = CheckClose( 2.0, 0.57672480775687338720 );
    BOOST_CHECK( check9 );

    // j1 (8.0) == 0.23463634685391462438
    constexpr auto check10 = CheckClose( 8.0, 0.23463634685391462438 );
    BOOST_CHECK( check10 );

    // j1 (10.0) == 0.043472746168861436670
    constexpr auto check11 = Check( 10.0, 0.043472746168861436670 );
    BOOST_CHECK( check11 );

}


// --run_test=ConstexprMathTests/FloatJNTest1
BOOST_AUTO_TEST_CASE( FloatJNTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( int n, C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = JN( n, x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( int n, C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = JN( n, x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( int n, C::ValueType x ) -> bool
        {
            auto r = JN( n, x );
            return IsNaN( r );
        };

    // jn (0, x) == j0 (x)  
    // jn (0, NaN) == NaN
    constexpr auto check1 = CheckIsNaN( 0, C::NaN );
    BOOST_CHECK( check1 );

    // jn (0, inf) == 0
    constexpr auto check2 = Check( 0, C::Infinity, 0. );
    BOOST_CHECK( check2 );

    // jn (0, -1.0) == 0.76519768655796655145
    constexpr auto check3 = Check( 0, -1.0, 0.76519768655796655145 );
    BOOST_CHECK( check3 );

    // jn (0, 0.0) == 1.0
    constexpr auto check4 = Check( 0, 0.0, 1.0 );
    BOOST_CHECK( check4 );

    // jn (0, 0.1) == 0.99750156206604003228
    constexpr auto check5 = Check( 0, 0.1, 0.99750156206604003228 );
    BOOST_CHECK( check5 );

    // jn (0, 0.7) == 0.88120088860740528084
    constexpr auto check6 = Check( 0, 0.7, 0.88120088860740528084 );
    BOOST_CHECK( check6 );

    // jn (0, 1.0) == 0.76519768655796655145
    constexpr auto check7 = Check( 0, 1.0, 0.76519768655796655145 );
    BOOST_CHECK( check7 );

    // jn (0, 1.5) == 0.51182767173591812875
    constexpr auto check8 = Check( 0, 1.5, 0.51182767173591812875 );
    BOOST_CHECK( check8 );

    // jn (0, 2.0) == 0.22389077914123566805
    constexpr auto check9 = CheckClose( 0, 2.0, 0.22389077914123566805 );
    BOOST_CHECK( check9 );

    // jn (0, 8.0) == 0.17165080713755390609
    constexpr auto check10 = CheckClose( 0, 8.0, 0.17165080713755390609 );
    BOOST_CHECK( check10 );

    // jn (0, 10.0) == -0.24593576445134833520
    constexpr auto check11 = CheckClose( 0, 10.0, -0.24593576445134833520 );
    BOOST_CHECK( check11 );

    // jn (1, x) == j1 (x)  
    // jn (1, NaN) == NaN
    constexpr auto check12 = CheckIsNaN( 1, C::NaN );
    BOOST_CHECK( check12 );

    // jn (1, inf) == 0
    constexpr auto check13 = Check( 1, C::Infinity, 0. );
    BOOST_CHECK( check13 );

    // jn (1, -1.0) == -0.44005058574493351596
    constexpr auto check14 = Check( 1, -1.0, -0.44005058574493351596 );
    BOOST_CHECK( check14 );

    // jn (1, 0.0) == 0.0
    constexpr auto check15 = Check( 1, 0.0, 0.0 );
    BOOST_CHECK( check15 );

    // jn (1, 0.1) == 0.049937526036241997556
    constexpr auto check16 = Check( 1, 0.1, 0.049937526036241997556 );
    BOOST_CHECK( check16 );

    // jn (1, 0.7) == 0.32899574154005894785
    constexpr auto check17 = Check( 1, 0.7, 0.32899574154005894785 );
    BOOST_CHECK( check17 );

    // jn (1, 1.0) == 0.44005058574493351596
    constexpr auto check18 = Check( 1, 1.0, 0.44005058574493351596 );
    BOOST_CHECK( check18 );
    
    // jn (1, 1.5) == 0.55793650791009964199
    constexpr auto check19 = Check( 1, 1.5, 0.55793650791009964199 );
    BOOST_CHECK( check19 );

    // jn (1, 2.0) == 0.57672480775687338720
    constexpr auto check20 = Check( 1, 2.0, 0.57672480775687338720 );
    BOOST_CHECK( check20 );

    // jn (1, 8.0) == 0.23463634685391462438
    constexpr auto check21 = Check( 1, 8.0, 0.23463634685391462438 );
    BOOST_CHECK( check21 );

    // jn (1, 10.0) == 0.043472746168861436670
    constexpr auto check22 = CheckClose( 1, 10.0, 0.043472746168861436670 );
    BOOST_CHECK( check22 );

    // jn (3, x)  
    // jn (3, NaN) == NaN
    constexpr auto check23 = CheckIsNaN( 3, C::NaN );
    BOOST_CHECK( check23 );

    // jn (3, inf) == 0
    constexpr auto check24 = Check( 3, C::Infinity, 0.0 );
    BOOST_CHECK( check24 );

    // jn (3, -1.0) == -0.019563353982668405919
    constexpr auto check25 = Check( 3, -1.0, -0.019563353982668405919 );
    BOOST_CHECK( check25 );

    // jn (3, 0.0) == 0.0
    constexpr auto check26 = Check( 3, 0.0, 0.0 );
    BOOST_CHECK( check26 );

    // jn (3, 0.1) == 0.000020820315754756261429
    constexpr auto check27 = Check( 3, 0.1, 0.000020820315754756261429 );
    BOOST_CHECK( check27 );

    // jn (3, 0.7) == 0.0069296548267508408077
    constexpr auto check28 = CheckClose( 3, 0.7, 0.0069296548267508408077 );
    BOOST_CHECK( check28 );

    // jn (3, 1.0) == 0.019563353982668405919
    constexpr auto check29 = Check( 3, 1.0, 0.019563353982668405919 );
    BOOST_CHECK( check29 );

    // jn (3, 2.0) == 0.12894324947440205110
    constexpr auto check30 = CheckClose( 3, 2.0, 0.12894324947440205110 );
    BOOST_CHECK( check30 );

    // jn (3, 10.0) == 0.058379379305186812343
    constexpr auto check31 = CheckClose( 3, 10.0, 0.058379379305186812343 );
    BOOST_CHECK( check31 );

    //  jn (10, x)  
    // jn (10, NaN) == NaN
    constexpr auto check32 = CheckIsNaN( 10, C::NaN );
    BOOST_CHECK( check32 );

    // jn (10, inf) == 0
    constexpr auto check33 = Check( 10, C::Infinity, 0.0 );
    BOOST_CHECK( check33 );

    // jn (10, -1.0) == 0.26306151236874532070e-9
    constexpr auto check34 = Check( 10, -1.0, 0.26306151236874532070e-9 );
    BOOST_CHECK( check34 );

    // jn (10, 0.0) == 0.0
    constexpr auto check35 = Check( 10, 0.0, 0.0 );
    BOOST_CHECK( check35 );

    // jn (10, 0.1) == 0.26905328954342155795e-19
    constexpr auto check36 = CheckClose( 10, 0.1, 0.26905328954342155795e-19 );
    BOOST_CHECK( check36 );

    // jn (10, 0.7) == 0.75175911502153953928e-11
    constexpr auto check37 = CheckClose( 10, 0.7, 0.75175911502153953928e-11 );
    BOOST_CHECK( check37 );

    // jn (10, 1.0) == 0.26306151236874532070e-9
    constexpr auto check38 = Check( 10, 1.0, 0.26306151236874532070e-9 );
    BOOST_CHECK( check38 );

    // jn (10, 2.0) == 0.25153862827167367096e-6
    constexpr auto check39 = CheckClose( 10, 2.0, 0.25153862827167367096e-6 );
    BOOST_CHECK( check39 );

    // jn (10, 10.0) == 0.20748610663335885770
    constexpr auto check40 = CheckClose( 10, 10.0, 0.20748610663335885770 );
    BOOST_CHECK( check40 );

}

// --run_test=ConstexprMathTests/DoubleJNTest1
BOOST_AUTO_TEST_CASE( DoubleJNTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( int n, C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = JN( n, x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( int n, C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = JN( n, x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( int n, C::ValueType x ) -> bool
        {
            auto r = JN( n, x );
            return IsNaN( r );
        };

    // jn (0, x) == j0 (x)  
    // jn (0, NaN) == NaN
    constexpr auto check1 = CheckIsNaN( 0, C::NaN );
    BOOST_CHECK( check1 );

    // jn (0, inf) == 0
    constexpr auto check2 = Check( 0, C::Infinity, 0. );
    BOOST_CHECK( check2 );

    // jn (0, -1.0) == 0.76519768655796655145
    constexpr auto check3 = Check( 0, -1.0, 0.76519768655796655145 );
    BOOST_CHECK( check3 );

    // jn (0, 0.0) == 1.0
    constexpr auto check4 = Check( 0, 0.0, 1.0 );
    BOOST_CHECK( check4 );

    // jn (0, 0.1) == 0.99750156206604003228
    constexpr auto check5 = Check( 0, 0.1, 0.99750156206604003228 );
    BOOST_CHECK( check5 );

    // jn (0, 0.7) == 0.88120088860740528084
    constexpr auto check6 = Check( 0, 0.7, 0.88120088860740528084 );
    BOOST_CHECK( check6 );

    // jn (0, 1.0) == 0.76519768655796655145
    constexpr auto check7 = Check( 0, 1.0, 0.76519768655796655145 );
    BOOST_CHECK( check7 );

    // jn (0, 1.5) == 0.51182767173591812875
    constexpr auto check8 = Check( 0, 1.5, 0.51182767173591812875 );
    BOOST_CHECK( check8 );

    // jn (0, 2.0) == 0.22389077914123566805
    constexpr auto check9 = Check( 0, 2.0, 0.22389077914123566805 );
    BOOST_CHECK( check9 );

    // jn (0, 8.0) == 0.17165080713755390609
    constexpr auto check10 = Check( 0, 8.0, 0.17165080713755390609 );
    BOOST_CHECK( check10 );

    // jn (0, 10.0) == -0.24593576445134833520
    constexpr auto check11 = CheckClose( 0, 10.0, -0.24593576445134833520 );
    BOOST_CHECK( check11 );

    // jn (1, x) == j1 (x)  
    // jn (1, NaN) == NaN
    constexpr auto check12 = CheckIsNaN( 1, C::NaN );
    BOOST_CHECK( check12 );

    // jn (1, inf) == 0
    constexpr auto check13 = Check( 1, C::Infinity, 0. );
    BOOST_CHECK( check13 );

    // jn (1, -1.0) == -0.44005058574493351596
    constexpr auto check14 = Check( 1, -1.0, -0.44005058574493351596 );
    BOOST_CHECK( check14 );

    // jn (1, 0.0) == 0.0
    constexpr auto check15 = Check( 1, 0.0, 0.0 );
    BOOST_CHECK( check15 );

    // jn (1, 0.1) == 0.049937526036241997556
    constexpr auto check16 = Check( 1, 0.1, 0.049937526036241997556 );
    BOOST_CHECK( check16 );

    // jn (1, 0.7) == 0.32899574154005894785
    constexpr auto check17 = Check( 1, 0.7, 0.32899574154005894785 );
    BOOST_CHECK( check17 );

    // jn (1, 1.0) == 0.44005058574493351596
    constexpr auto check18 = Check( 1, 1.0, 0.44005058574493351596 );
    BOOST_CHECK( check18 );

    // jn (1, 1.5) == 0.55793650791009964199
    constexpr auto check19 = Check( 1, 1.5, 0.55793650791009964199 );
    BOOST_CHECK( check19 );

    // jn (1, 2.0) == 0.57672480775687338720
    constexpr auto check20 = CheckClose( 1, 2.0, 0.57672480775687338720 );
    BOOST_CHECK( check20 );

    // jn (1, 8.0) == 0.23463634685391462438
    constexpr auto check21 = CheckClose( 1, 8.0, 0.23463634685391462438 );
    BOOST_CHECK( check21 );

    // jn (1, 10.0) == 0.043472746168861436670
    constexpr auto check22 = Check( 1, 10.0, 0.043472746168861436670 );
    BOOST_CHECK( check22 );

    // jn (3, x)  
    // jn (3, NaN) == NaN
    constexpr auto check23 = CheckIsNaN( 3, C::NaN );
    BOOST_CHECK( check23 );

    // jn (3, inf) == 0
    constexpr auto check24 = Check( 3, C::Infinity, 0.0 );
    BOOST_CHECK( check24 );

    // jn (3, -1.0) == -0.019563353982668405919
    constexpr auto check25 = Check( 3, -1.0, -0.019563353982668405919 );
    BOOST_CHECK( check25 );

    // jn (3, 0.0) == 0.0
    constexpr auto check26 = Check( 3, 0.0, 0.0 );
    BOOST_CHECK( check26 );

    // jn (3, 0.1) == 0.000020820315754756261429
    constexpr auto check27 = CheckClose( 3, 0.1, 0.000020820315754756261429 );
    BOOST_CHECK( check27 );

    // jn (3, 0.7) == 0.0069296548267508408077
    constexpr auto check28 = Check( 3, 0.7, 0.0069296548267508408077 );
    BOOST_CHECK( check28 );

    // jn (3, 1.0) == 0.019563353982668405919
    constexpr auto check29 = Check( 3, 1.0, 0.019563353982668405919 );
    BOOST_CHECK( check29 );

    // jn (3, 2.0) == 0.12894324947440205110
    constexpr auto check30 = Check( 3, 2.0, 0.12894324947440205110 );
    BOOST_CHECK( check30 );

    // jn (3, 10.0) == 0.058379379305186812343
    constexpr auto check31 = CheckClose( 3, 10.0, 0.058379379305186812343 );
    BOOST_CHECK( check31 );

    //  jn (10, x)  
    // jn (10, NaN) == NaN
    constexpr auto check32 = CheckIsNaN( 10, C::NaN );
    BOOST_CHECK( check32 );

    // jn (10, inf) == 0
    constexpr auto check33 = Check( 10, C::Infinity, 0.0 );
    BOOST_CHECK( check33 );

    // jn (10, -1.0) == 0.26306151236874532070e-9
    constexpr auto check34 = Check( 10, -1.0, 0.26306151236874532070e-9 );
    BOOST_CHECK( check34 );

    // jn (10, 0.0) == 0.0
    constexpr auto check35 = Check( 10, 0.0, 0.0 );
    BOOST_CHECK( check35 );

    // jn (10, 0.1) == 0.26905328954342155795e-19
    constexpr auto check36 = CheckClose( 10, 0.1, 0.26905328954342155795e-19 );
    BOOST_CHECK( check36 );

    // jn (10, 0.7) == 0.75175911502153953928e-11
    constexpr auto check37 = CheckClose( 10, 0.7, 0.75175911502153953928e-11 );
    BOOST_CHECK( check37 );

    // jn (10, 1.0) == 0.26306151236874532070e-9
    constexpr auto check38 = Check( 10, 1.0, 0.26306151236874532070e-9 );
    BOOST_CHECK( check38 );

    // jn (10, 2.0) == 0.25153862827167367096e-6
    constexpr auto check39 = CheckClose( 10, 2.0, 0.25153862827167367096e-6 );
    BOOST_CHECK( check39 );

    // jn (10, 10.0) == 0.20748610663335885770
    constexpr auto check40 = CheckClose( 10, 10.0, 0.20748610663335885770 );
    BOOST_CHECK( check40 );

}

// --run_test=ConstexprMathTests/FloatY0Test1
BOOST_AUTO_TEST_CASE( FloatY0Test1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = Y0( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = Y0( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = Y0( x );
            return IsNaN( r );
        };

    // y0 (-1.0) == NaN
    constexpr auto check1 = CheckIsNaN( -1.0 );
    BOOST_CHECK( check1 );

    // y0 (0.0) == -inf
    constexpr auto check2 = Check( 0.0, -C::Infinity );
    BOOST_CHECK( check2 );

    // y0 (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check3 );

    // y0 (inf) == 0
    constexpr auto check4 = Check( C::Infinity, 0.0 );
    BOOST_CHECK( check4 );

    // y0 (0.1) == -1.5342386513503668441
    constexpr auto check5 = Check( 0.1, -1.5342386513503668441 );
    BOOST_CHECK( check5 );
    
    // y0 (0.7) == -0.19066492933739506743
    constexpr auto check6 = CheckClose( 0.7, -0.19066492933739506743 );
    BOOST_CHECK( check6 );

    // y0 (1.0) == 0.088256964215676957983
    constexpr auto check7 = CheckClose( 1.0, 0.088256964215676957983f );
    BOOST_CHECK( check7 );
    
    // y0 (1.5) == 0.38244892379775884396
    constexpr auto check8 = CheckClose( 1.5, 0.38244892379775884396 );
    BOOST_CHECK( check8 );

    // y0 (2.0) == 0.51037567264974511960
    constexpr auto check9 = Check( 2.0, 0.51037567264974511960 );
    BOOST_CHECK( check9 );

    // y0 (8.0) == 0.22352148938756622053
    constexpr auto check10 = CheckClose( 8.0, 0.22352148938756622053 );
    BOOST_CHECK( check10 );

    // y0 (10.0) == 0.055671167283599391424
    constexpr auto check11 = CheckClose( 10.0, 0.055671167283599391424 );
    BOOST_CHECK( check11 );
}

// --run_test=ConstexprMathTests/DoubleY0Test1
BOOST_AUTO_TEST_CASE( DoubleY0Test1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = Y0( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = Y0( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = Y0( x );
            return IsNaN( r );
        };

    // y0 (-1.0) == NaN
    constexpr auto check1 = CheckIsNaN( -1.0 );
    BOOST_CHECK( check1 );

    // y0 (0.0) == -inf
    constexpr auto check2 = Check( 0.0, -C::Infinity );
    BOOST_CHECK( check2 );

    // y0 (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check3 );

    // y0 (inf) == 0
    constexpr auto check4 = Check( C::Infinity, 0.0 );
    BOOST_CHECK( check4 );

    // y0 (0.1) == -1.5342386513503668441
    constexpr auto check5 = Check( 0.1, -1.5342386513503668441 );
    BOOST_CHECK( check5 );

    // y0 (0.7) == -0.19066492933739506743
    constexpr auto check6 = CheckClose( 0.7, -0.19066492933739506743 );
    BOOST_CHECK( check6 );

    // y0 (1.0) == 0.088256964215676957983
    constexpr auto check7 = CheckClose( 1.0, 0.088256964215676957983 );
    BOOST_CHECK( check7 );

    // y0 (1.5) == 0.38244892379775884396
    constexpr auto check8 = CheckClose( 1.5, 0.38244892379775884396 );
    BOOST_CHECK( check8 );

    // y0 (2.0) == 0.51037567264974511960
    constexpr auto check9 = Check( 2.0, 0.51037567264974511960 );
    BOOST_CHECK( check9 );

    // y0 (8.0) == 0.22352148938756622053
    constexpr auto check10 = CheckClose( 8.0, 0.22352148938756622053 );
    BOOST_CHECK( check10 );

    // y0 (10.0) == 0.055671167283599391424
    constexpr auto check11 = Check( 10.0, 0.055671167283599391424 );
    BOOST_CHECK( check11 );


}


// --run_test=ConstexprMathTests/FloatY1Test1
BOOST_AUTO_TEST_CASE( FloatY1Test1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = Y1( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = Y1( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = Y1( x );
            return IsNaN( r );
        };

    // y1 (-1.0) == NaN
    constexpr auto check1 = CheckIsNaN( -1.0 );
    BOOST_CHECK( check1 );

    // y1 (0.0) == -inf
    constexpr auto check2 = Check( 0.0, -C::Infinity );
    BOOST_CHECK( check2 );

    // y1 (inf) == 0
    constexpr auto check3 = Check( C::Infinity,0.0 );
    BOOST_CHECK( check3 );

    // y1 (NaN) == NaN
    constexpr auto check4 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check4 );

    // y1 (0.1) == -6.4589510947020269877
    constexpr auto check5 = Check( 0.1, -6.4589510947020269877 );
    BOOST_CHECK( check5 );

    // y1 (0.7) == -1.1032498719076333697
    constexpr auto check6 = CheckClose( 0.7, -1.1032498719076333697 );
    BOOST_CHECK( check6 );

    // y1 (1.0) == -0.78121282130028871655
    constexpr auto check7 = Check( 1.0, -0.78121282130028871655 );
    BOOST_CHECK( check7 );

    // y1 (1.5) == -0.41230862697391129595
    constexpr auto check8 = CheckClose( 1.5, -0.41230862697391129595 );
    BOOST_CHECK( check8 );

    // y1 (2.0) == -0.10703243154093754689
    constexpr auto check9 = CheckClose( 2.0, -0.10703243154093754689 );
    BOOST_CHECK( check9 );

    // y1 (8.0) == -0.15806046173124749426
    constexpr auto check10 = CheckClose( 8.0, -0.15806046173124749426 );
    BOOST_CHECK( check10 );

    // y1 (10.0) == 0.24901542420695388392
    constexpr auto check11 = CheckClose( 10.0, 0.24901542420695388392 );
    BOOST_CHECK( check11 );


}

// --run_test=ConstexprMathTests/DoubleY1Test1
BOOST_AUTO_TEST_CASE( DoubleY1Test1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = Y1( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = Y1( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = Y1( x );
            return IsNaN( r );
        };

    // y1 (-1.0) == NaN
    constexpr auto check1 = CheckIsNaN( -1.0 );
    BOOST_CHECK( check1 );

    // y1 (0.0) == -inf
    constexpr auto check2 = Check( 0.0, -C::Infinity );
    BOOST_CHECK( check2 );

    // y1 (inf) == 0
    constexpr auto check3 = Check( C::Infinity, 0.0 );
    BOOST_CHECK( check3 );

    // y1 (NaN) == NaN
    constexpr auto check4 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check4 );

    // y1 (0.1) == -6.4589510947020269877
    constexpr auto check5 = CheckClose( 0.1, -6.4589510947020269877 );
    BOOST_CHECK( check5 );

    // y1 (0.7) == -1.1032498719076333697
    constexpr auto check6 = CheckClose( 0.7, -1.1032498719076333697 );
    BOOST_CHECK( check6 );

    // y1 (1.0) == -0.78121282130028871655
    constexpr auto check7 = Check( 1.0, -0.78121282130028871655 );
    BOOST_CHECK( check7 );

    // y1 (1.5) == -0.41230862697391129595
    constexpr auto check8 = Check( 1.5, -0.41230862697391129595 );
    BOOST_CHECK( check8 );

    // y1 (2.0) == -0.10703243154093754689
    constexpr auto check9 = CheckClose( 2.0, -0.10703243154093754689 );
    BOOST_CHECK( check9 );

    // y1 (8.0) == -0.15806046173124749426
    constexpr auto check10 = CheckClose( 8.0, -0.15806046173124749426 );
    BOOST_CHECK( check10 );

    // y1 (10.0) == 0.24901542420695388392
    constexpr auto check11 = CheckClose( 10.0, 0.24901542420695388392 );
    BOOST_CHECK( check11 );


}

// --run_test=ConstexprMathTests/FloatYNTest1
BOOST_AUTO_TEST_CASE( FloatYNTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( int n, C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = YN( n, x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( int n, C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = YN( n, x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( int n, C::ValueType x ) -> bool
        {
            auto r = YN( n, x );
            return IsNaN( r );
        };

    // y0 (-1.0) == NaN
    constexpr auto check1 = CheckIsNaN( 0, -1.0 );
    BOOST_CHECK( check1 );

    // y0 (0.0) == -inf
    constexpr auto check2 = Check( 0, 0.0, -C::Infinity );
    BOOST_CHECK( check2 );

    // y0 (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( 0, C::NaN );
    BOOST_CHECK( check3 );

    // y0 (inf) == 0
    constexpr auto check4 = Check( 0, C::Infinity, 0.0 );
    BOOST_CHECK( check4 );

    // y0 (0.1) == -1.5342386513503668441
    constexpr auto check5 = Check( 0, 0.1, -1.5342386513503668441 );
    BOOST_CHECK( check5 );

    // y0 (0.7) == -0.19066492933739506743
    constexpr auto check6 = CheckClose( 0, 0.7, -0.19066492933739506743 );
    BOOST_CHECK( check6 );

    // y0 (1.0) == 0.088256964215676957983
    constexpr auto check7 = CheckClose( 0, 1.0, 0.088256964215676957983f );
    BOOST_CHECK( check7 );

    // y0 (1.5) == 0.38244892379775884396
    constexpr auto check8 = CheckClose( 0, 1.5, 0.38244892379775884396 );
    BOOST_CHECK( check8 );

    // y0 (2.0) == 0.51037567264974511960
    constexpr auto check9 = Check( 0, 2.0, 0.51037567264974511960 );
    BOOST_CHECK( check9 );

    // y0 (8.0) == 0.22352148938756622053
    constexpr auto check10 = CheckClose( 0, 8.0, 0.22352148938756622053 );
    BOOST_CHECK( check10 );

    // y0 (10.0) == 0.055671167283599391424
    constexpr auto check11 = CheckClose( 0, 10.0, 0.055671167283599391424 );
    BOOST_CHECK( check11 );

    // y1 (-1.0) == NaN
    constexpr auto check12 = CheckIsNaN( 1, -1.0 );
    BOOST_CHECK( check12 );

    // y1 (0.0) == -inf
    constexpr auto check13 = Check( 1, 0.0, -C::Infinity );
    BOOST_CHECK( check13 );

    // y1 (inf) == 0
    constexpr auto check14 = Check( 1, C::Infinity, 0.0 );
    BOOST_CHECK( check14 );

    // y1 (NaN) == NaN
    constexpr auto check15 = CheckIsNaN( 1, C::NaN );
    BOOST_CHECK( check15 );

    // y1 (0.1) == -6.4589510947020269877
    constexpr auto check16 = Check( 1, 0.1, -6.4589510947020269877 );
    BOOST_CHECK( check16 );

    // y1 (0.7) == -1.1032498719076333697
    constexpr auto check17 = CheckClose( 1, 0.7, -1.1032498719076333697 );
    BOOST_CHECK( check17 );

    // y1 (1.0) == -0.78121282130028871655
    constexpr auto check18 = Check( 1, 1.0, -0.78121282130028871655 );
    BOOST_CHECK( check18 );

    // y1 (1.5) == -0.41230862697391129595
    constexpr auto check19 = CheckClose( 1, 1.5, -0.41230862697391129595 );
    BOOST_CHECK( check19 );

    // y1 (2.0) == -0.10703243154093754689
    constexpr auto check20 = CheckClose( 1, 2.0, -0.10703243154093754689 );
    BOOST_CHECK( check20 );

    // y1 (8.0) == -0.15806046173124749426
    constexpr auto check21 = CheckClose( 1, 8.0, -0.15806046173124749426 );
    BOOST_CHECK( check21 );

    // y1 (10.0) == 0.24901542420695388392
    constexpr auto check22 = CheckClose( 1, 10.0, 0.24901542420695388392 );
    BOOST_CHECK( check22 );

    /* yn (3, x)  */
    // yn (3, inf) == 0
    constexpr auto check23 = Check( 3, C::Infinity, 0.0 );
    BOOST_CHECK( check23 );

    // yn (3, NaN) == NaN
    constexpr auto check24 = CheckIsNaN( 3, C::NaN );
    BOOST_CHECK( check24 );

    // yn (3, 0.1) == -5099.33203
    constexpr auto check25 = Check( 3, 0.1, -5099.33203 );
    BOOST_CHECK( check25 );

    // yn (3, 0.7) == -15.8194780
    constexpr auto check26 = Check( 3, 0.7, -15.8194780 );
    BOOST_CHECK( check26 );

    // yn (3, 1.0) == -5.82151747
    constexpr auto check27 = Check( 3, 1.0, -5.82151747 );
    BOOST_CHECK( check27 );

    // yn (3, 2.0) == -1.12778378
    constexpr auto check28 = Check( 3, 2.0, -1.12778378 );
    BOOST_CHECK( check28 );

    // yn (3, 10.0) == -0.251362681
    constexpr auto check29 = Check( 3, 10.0, -0.251362681 );
    BOOST_CHECK( check29 );

    /* yn (10, x)  */
    // yn (10, inf) == 0
    constexpr auto check30 = Check( 10, C::Infinity, 0.0 );
    BOOST_CHECK( check30 );

    // yn (10, NaN) == NaN
    constexpr auto check31 = CheckIsNaN( 10, C::NaN );
    BOOST_CHECK( check31 );

    // yn (10, 0.1) == -1.18313320e+18
    constexpr auto check32 = Check( 10, 0.1, -1.18313320e+18 );
    BOOST_CHECK( check32 );

    // yn (10, 0.7) == -4.24471936e+09
    constexpr auto check33 = Check( 10, 0.7, -4.24471936e+09 );
    BOOST_CHECK( check33 );

    // yn (10, 1.0) == -121618016.
    constexpr auto check34 = Check( 10, 1.0, -121618016. );
    BOOST_CHECK( check34 );

    // yn (10, 2.0) == -129184.539
    constexpr auto check35 = Check( 10, 2.0, -129184.539 );
    BOOST_CHECK( check35 );

    // yn (10, 10.0) == -0.359814137
    constexpr auto check36 = Check( 10, 10.0, -0.359814137 );
    BOOST_CHECK( check36 );
}

// --run_test=ConstexprMathTests/DoubleYNTest1
BOOST_AUTO_TEST_CASE( DoubleYNTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( int n, C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = YN( n, x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( int n, C::ValueType x, C::ValueType expected, C::ValueType epsilon = std::numeric_limits<C::ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = YN( n, x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( int n, C::ValueType x ) -> bool
        {
            auto r = YN( n, x );
            return IsNaN( r );
        };

    // y0 (-1.0) == NaN
    constexpr auto check1 = CheckIsNaN( 0, -1.0 );
    BOOST_CHECK( check1 );

    // y0 (0.0) == -inf
    constexpr auto check2 = Check( 0, 0.0, -C::Infinity );
    BOOST_CHECK( check2 );

    // y0 (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( 0, C::NaN );
    BOOST_CHECK( check3 );

    // y0 (inf) == 0
    constexpr auto check4 = Check( 0, C::Infinity, 0.0 );
    BOOST_CHECK( check4 );

    // y0 (0.1) == -1.5342386513503668441
    constexpr auto check5 = Check( 0, 0.1, -1.5342386513503668441 );
    BOOST_CHECK( check5 );

    // y0 (0.7) == -0.19066492933739506743
    constexpr auto check6 = CheckClose( 0, 0.7, -0.19066492933739506743 );
    BOOST_CHECK( check6 );

    // y0 (1.0) == 0.088256964215676957983
    constexpr auto check7 = CheckClose( 0, 1.0, 0.088256964215676957983 );
    BOOST_CHECK( check7 );

    // y0 (1.5) == 0.38244892379775884396
    constexpr auto check8 = CheckClose( 0, 1.5, 0.38244892379775884396 );
    BOOST_CHECK( check8 );

    // y0 (2.0) == 0.51037567264974511960
    constexpr auto check9 = Check( 0, 2.0, 0.51037567264974511960 );
    BOOST_CHECK( check9 );

    // y0 (8.0) == 0.22352148938756622053
    constexpr auto check10 = CheckClose( 0, 8.0, 0.22352148938756622053 );
    BOOST_CHECK( check10 );

    // y0 (10.0) == 0.055671167283599391424
    constexpr auto check11 = CheckClose( 0, 10.0, 0.055671167283599391424 );
    BOOST_CHECK( check11 );

    // y1 (-1.0) == NaN
    constexpr auto check12 = CheckIsNaN( 1, -1.0 );
    BOOST_CHECK( check12 );

    // y1 (0.0) == -inf
    constexpr auto check13 = Check( 1, 0.0, -C::Infinity );
    BOOST_CHECK( check13 );

    // y1 (inf) == 0
    constexpr auto check14 = Check( 1, C::Infinity, 0.0 );
    BOOST_CHECK( check14 );

    // y1 (NaN) == NaN
    constexpr auto check15 = CheckIsNaN( 1, C::NaN );
    BOOST_CHECK( check15 );

    // y1 (0.1) == -6.4589510947020269877
    constexpr auto check16 = CheckClose( 1, 0.1, -6.4589510947020269877 );
    BOOST_CHECK( check16 );

    // y1 (0.7) == -1.1032498719076333697
    constexpr auto check17 = CheckClose( 1, 0.7, -1.1032498719076333697 );
    BOOST_CHECK( check17 );

    // y1 (1.0) == -0.78121282130028871655
    constexpr auto check18 = Check( 1, 1.0, -0.78121282130028871655 );
    BOOST_CHECK( check18 );

    // y1 (1.5) == -0.41230862697391129595
    constexpr auto check19 = CheckClose( 1, 1.5, -0.41230862697391129595 );
    BOOST_CHECK( check19 );

    // y1 (2.0) == -0.10703243154093754689
    constexpr auto check20 = CheckClose( 1, 2.0, -0.10703243154093754689 );
    BOOST_CHECK( check20 );

    // y1 (8.0) == -0.15806046173124749426
    constexpr auto check21 = CheckClose( 1, 8.0, -0.15806046173124749426 );
    BOOST_CHECK( check21 );

    // y1 (10.0) == 0.24901542420695388392
    constexpr auto check22 = CheckClose( 1, 10.0, 0.24901542420695388392 );
    BOOST_CHECK( check22 );

    /* yn (3, x)  */
    // yn (3, inf) == 0
    constexpr auto check23 = Check( 3, C::Infinity, 0.0 );
    BOOST_CHECK( check23 );

    // yn (3, NaN) == NaN
    constexpr auto check24 = CheckIsNaN( 3, C::NaN );
    BOOST_CHECK( check24 );

    // yn (3, 0.1) == -5099.3323786129058

    constexpr auto check25 = Check( 3, 0.1, -5099.3323786129058 );
    BOOST_CHECK( check25 );

    // yn (3, 0.7) == -15.819479052819633505
    constexpr auto check26 = Check( 3, 0.7, -15.819479052819640 );
    BOOST_CHECK( check26 );

    // yn (3, 1.0) == -5.8215176059647291
    constexpr auto check27 = Check( 3, 1.0, -5.8215176059647291 );
    BOOST_CHECK( check27 );

    // yn (3, 2.0) == -1.1277837768404280
    constexpr auto check28 = Check( 3, 2.0, -1.1277837768404280 );
    BOOST_CHECK( check28 );

    // yn (3, 10.0) == -0.25136265718383727
    constexpr auto check29 = Check( 3, 10.0, -0.25136265718383727 );
    BOOST_CHECK( check29 );

    /* yn (10, x)  */
    // yn (10, inf) == 0
    constexpr auto check30 = Check( 10, C::Infinity, 0.0 );
    BOOST_CHECK( check30 );

    // yn (10, NaN) == NaN
    constexpr auto check31 = CheckIsNaN( 10, C::NaN );
    BOOST_CHECK( check31 );

    // yn (10, 0.1) == -1.1831335132045202e+18
    constexpr auto check32 = Check( 10, 0.1, -1.1831335132045202e+18 );
    BOOST_CHECK( check32 );

    // yn (10, 0.7) == -4244719426.0703883
    constexpr auto check33 = Check( 10, 0.7, -4244719426.0703883 );
    BOOST_CHECK( check33 );

    // yn (10, 1.0) == -121618014.27868918
    constexpr auto check34 = Check( 10, 1.0, -121618014.27868918 );
    BOOST_CHECK( check34 );

    // yn (10, 2.0) == -129184.54220803932
    constexpr auto check35 = Check( 10, 2.0, -129184.54220803932 );
    BOOST_CHECK( check35 );

    // yn (10, 10.0) == -0.35981415218340268
    constexpr auto check36 = Check( 10, 10.0, -0.35981415218340268 );
    BOOST_CHECK( check36 );
}

// --run_test=ConstexprMathTests/FloatErfTest1
BOOST_AUTO_TEST_CASE( FloatErfTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = Erf( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = Erf( x );
            return IsNaN( r );
        };

    // erf (0) == 0
    constexpr auto check1 = Check( C::Zero, C::Zero );
    BOOST_CHECK( check1 );

    // erf (-0) == -0
    constexpr auto check2 = Check( -C::Zero, -C::Zero );
    BOOST_CHECK( check2 );

    // erf (inf) == 1
    constexpr auto check3 = Check( C::Infinity, C::One );
    BOOST_CHECK( check3 );

    // erf (-inf) == -1
    constexpr auto check4 = Check( C::NegativeInfinity, -C::One );
    BOOST_CHECK( check4 );

    // erf (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    // erf (0.7) == 0.67780119383741847297
    constexpr auto check6 = Check( 0.7, 0.67780119383741847297 );
    BOOST_CHECK( check6 );

    // erf (1.2) == 0.91031397822963538024
    constexpr auto check7 = Check( 1.2, 0.91031397822963538024 );
    BOOST_CHECK( check7 );

    // erf (2.0) == 0.99532226501895273416
    constexpr auto check8 = Check( 2.0, 0.99532226501895273416 );
    BOOST_CHECK( check8 );

    // erf (4.1) == 0.99999999329997234592
    constexpr auto check9 = Check( 4.1, 0.99999999329997234592 );
    BOOST_CHECK( check9 );

    // erf (27) == 1.0
    constexpr auto check10 = Check( 27, 1.0 );
    BOOST_CHECK( check10 );

}

// --run_test=ConstexprMathTests/DoubleErfTest1
BOOST_AUTO_TEST_CASE( DoubleErfTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = Erf( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = Erf( x );
            return IsNaN( r );
        };

    // erf (0) == 0
    constexpr auto check1 = Check( C::Zero, C::Zero );
    BOOST_CHECK( check1 );

    // erf (-0) == -0
    constexpr auto check2 = Check( -C::Zero, -C::Zero );
    BOOST_CHECK( check2 );

    // erf (inf) == 1
    constexpr auto check3 = Check( C::Infinity, C::One );
    BOOST_CHECK( check3 );

    // erf (-inf) == -1
    constexpr auto check4 = Check( C::NegativeInfinity, -C::One );
    BOOST_CHECK( check4 );

    // erf (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    // erf (0.7) == 0.67780119383741847297
    constexpr auto check6 = Check( 0.7, 0.67780119383741847297 );
    BOOST_CHECK( check6 );

    // erf (1.2) == 0.91031397822963538024
    constexpr auto check7 = Check( 1.2, 0.91031397822963538024 );
    BOOST_CHECK( check7 );

    // erf (2.0) == 0.99532226501895273416
    constexpr auto check8 = Check( 2.0, 0.99532226501895273416 );
    BOOST_CHECK( check8 );

    // erf (4.1) == 0.99999999329997234592
    constexpr auto check9 = Check( 4.1, 0.99999999329997234592 );
    BOOST_CHECK( check9 );

    // erf (27) == 1.0
    constexpr auto check10 = Check( 27, 1.0 );
    BOOST_CHECK( check10 );

}

// --run_test=ConstexprMathTests/FloatErfCTest1
BOOST_AUTO_TEST_CASE( FloatErfCTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ErfC( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ErfC( x );
            return IsNaN( r );
        };

    // erfc (inf) == 0.0
    constexpr auto check1 = Check( C::Infinity, C::Zero );
    static_assert( ErfC( C::Infinity ) == C::Zero );
    BOOST_CHECK( check1 );

    // erfc (-inf) == 2.0
    constexpr auto check2 = Check( C::NegativeInfinity, C::Two );
    BOOST_CHECK( check2 );
    
    // erfc (0.0) == 1.0
    constexpr auto check3 = Check( C::Zero, C::One );
    BOOST_CHECK( check3 );

    // erfc (-0) == 1.0
    constexpr auto check4 = Check( -C::Zero, C::One );
    BOOST_CHECK( check4 );

    // erfc (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    // erfc (0.7) == 0.322198808
    constexpr auto check6 = Check( 0.7f, 0.322198808f );
    BOOST_CHECK( check6 );

    // erfc (1.2) == 0.0896860063
    constexpr auto check7 = Check( 1.2f, 0.0896860063f );
    BOOST_CHECK( check7 );

    // erfc (2.0) == 0.00467773527
    constexpr auto check8 = Check( 2.0f, 0.00467773527f );
    static_assert( ErfC( 2.0f ) == 0.00467773527f );
    BOOST_CHECK( check8 );

    // erfc (4.1) == 6.70003297e-09
    constexpr auto check9 = Check( 4.1f, 6.70003297e-09f );
    BOOST_CHECK( check9 );

    // erfc (9) == 4.13703171e-37
    constexpr auto check10 = Check( 9.f, 4.13703171e-37 );
    BOOST_CHECK( check10 );

}

// --run_test=ConstexprMathTests/DoubleErfCTest1
BOOST_AUTO_TEST_CASE( DoubleErfCTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ErfC( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ErfC( x );
            return IsNaN( r );
        };

    // erfc (inf) == 0.0
    constexpr auto check1 = Check( C::Infinity, C::Zero );
    BOOST_CHECK( check1 );

    // erfc (-inf) == 2.0
    constexpr auto check2 = Check( C::NegativeInfinity, C::Two );
    BOOST_CHECK( check2 );

    // erfc (0.0) == 1.0
    constexpr auto check3 = Check( C::Zero, C::One );
    BOOST_CHECK( check3 );

    // erfc (-0) == 1.0
    constexpr auto check4 = Check( -C::Zero, C::One );
    BOOST_CHECK( check4 );

    // erfc (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    // erfc (0.7) == 0.32219880616258156
    constexpr auto check6 = Check( 0.7, 0.32219880616258156 );
    BOOST_CHECK( check6 );

    // erfc (1.2) == 0.089686021770364638
    constexpr auto check7 = Check( 1.2, 0.089686021770364638 );
    BOOST_CHECK( check7 );

    // erfc (2.0) == 0.0046777349810472662
    constexpr auto check8 = Check( 2.0, 0.0046777349810472662 );
    BOOST_CHECK( check8 );

    // erfc (4.1) == 6.7000276540849183e-09
    constexpr auto check9 = Check( 4.1, 6.7000276540849183e-09 );
    BOOST_CHECK( check9 );

    // erfc (9) == 4.1370317465138101e-37
    constexpr auto check10 = Check( 9., 4.1370317465138101e-37 );
    BOOST_CHECK( check10 );

}

// --run_test=ConstexprMathTests/DoubleTGammaTest1
BOOST_AUTO_TEST_CASE( DoubleTGammaTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = TGamma( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = TGamma( x );
            return IsNaN( r );
        };

    // tgamma (inf) == inf
    constexpr auto check1 = Check( C::Infinity, C::Infinity );
    BOOST_CHECK( check1 );

    // tgamma (0) == inf
    constexpr auto check2 = Check( C::Zero, C::Infinity );
    BOOST_CHECK( check2 );
    
    // tgamma (-0) == inf
    constexpr auto check3 = Check( -C::Zero, C::Infinity );
    BOOST_CHECK( check3 );

    // tgamma (-2) == NaN
    constexpr auto check4 = CheckIsNaN( -C::Two );
    BOOST_CHECK( check4 );
    // tgamma (-inf) == NaN
    constexpr auto check5 = CheckIsNaN( -C::Infinity );
    BOOST_CHECK( check5 );
    // tgamma (NaN) == NaN
    constexpr auto check6 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check6 );

    // tgamma (0.5) == sqrt (pi)
    constexpr auto check7 = Check( .5, Sqrt( C::Pi ) );
    BOOST_CHECK( check7 );
    // tgamma (-0.5) == -2 sqrt (pi)
    constexpr auto check8 = Check( -.5, -2. * Sqrt( C::Pi ) );
    BOOST_CHECK( check8 );

    // tgamma (1) == 1
    constexpr auto check9 = Check( 1., 1. );
    BOOST_CHECK( check9 );
    // tgamma (4) == 6
    constexpr auto check10 = Check( 4., 6. );
    BOOST_CHECK( check10 );

    // tgamma (0.7) == 1.29805533264755778568
    constexpr auto check11 = Check( 0.7, 1.29805533264755778568 );
    BOOST_CHECK( check11 );
                       
    // tgamma (1.2) == 0.91816874239976054
    constexpr auto check12 = Check( 1.2, 0.91816874239976054 );
    auto res = TGamma( 1.2 );
    BOOST_CHECK( check12 );

}

// --run_test=ConstexprMathTests/FloatLGammaTest1
BOOST_AUTO_TEST_CASE( FloatLGammaTest1 )
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = LGamma( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = LGamma( x );
            return IsNaN( r );
        };

    constexpr auto check1 = Check( C::Infinity, C::Infinity );
    BOOST_CHECK( check1 );

    constexpr auto check2 = Check( C::Zero, C::Infinity );
    BOOST_CHECK( check2 );

    constexpr auto check3 = Check( -3.0, C::Infinity );
    BOOST_CHECK( check3 );

    constexpr auto check4 = Check( -C::Infinity, C::Infinity );
    BOOST_CHECK( check4 );

    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    constexpr auto check6 = Check( C::One, C::Zero );
    BOOST_CHECK( check6 );

    constexpr auto check7 = Check( C::Three, 0.6931471805599453094172321214581766 );
    BOOST_CHECK( check7 );

    constexpr auto check8 = Check( 0.5, 0.57236494292470008707171367567652933 );
    BOOST_CHECK( check8 );

    constexpr auto check9 = Check( -0.5, 1.265512123484645396488945797134706 );
    BOOST_CHECK( check9 );
}


// --run_test=ConstexprMathTests/DoubleLGammaTest1
BOOST_AUTO_TEST_CASE( DoubleLGammaTest1 )
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = LGamma( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = LGamma( x );
            return IsNaN( r );
        };

    constexpr auto check1 = Check( C::Infinity, C::Infinity );
    BOOST_CHECK( check1 );

    constexpr auto check2 = Check( C::Zero, C::Infinity );
    BOOST_CHECK( check2 );

    constexpr auto check3 = Check( -3.0, C::Infinity );
    BOOST_CHECK( check3 );

    constexpr auto check4 = Check( -C::Infinity, C::Infinity );
    BOOST_CHECK( check4 );

    constexpr auto check5 = CheckIsNaN( C::NaN );
    BOOST_CHECK( check5 );

    constexpr auto check6 = Check( C::One, C::Zero );
    BOOST_CHECK( check6 );

    constexpr auto check7 = Check( C::Three, 0.6931471805599453094172321214581766 );
    BOOST_CHECK( check7 );

    constexpr auto check8 = Check( 0.5, 0.57236494292470008707171367567652933 );
    BOOST_CHECK( check8 );

    constexpr auto check9 = Check( -0.5, 1.265512123484645396488945797134706 );
    BOOST_CHECK( check9 );
}


BOOST_AUTO_TEST_SUITE_END( )
