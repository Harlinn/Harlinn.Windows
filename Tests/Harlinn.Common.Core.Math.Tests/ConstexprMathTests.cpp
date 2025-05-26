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




// --run_test=MathTests/FloatMinTest1
BOOST_AUTO_TEST_CASE( FloatMinTest1 )
{
    constexpr auto minValue = Math::Min( 5.f, 4.f, 3.f, 4.f, 4.f );
    constexpr bool equal = minValue == 3.f;
    BOOST_CHECK( equal );
}

// --run_test=MathTests/DoubleMinTest1
BOOST_AUTO_TEST_CASE( DoubleMinTest1 )
{
    constexpr auto minValue = Math::Min( 5., 4., 3., 4., 4. );
    constexpr bool equal = minValue == 3.;
    BOOST_CHECK( equal );
}



// --run_test=MathTests/FloatMaxTest1
BOOST_AUTO_TEST_CASE( FloatMaxTest1 )
{
    constexpr auto minValue = Math::Max( 5.f, 4.f, 3.f, 4.f, 4.f );
    constexpr bool equal = minValue == 5.f;
    BOOST_CHECK( equal );
}

// --run_test=MathTests/DoubleMaxTest1
BOOST_AUTO_TEST_CASE( DoubleMaxTest1 )
{
    constexpr auto minValue = Math::Max( 5., 4., 3., 4., 4. );
    constexpr bool equal = minValue == 5.;
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
