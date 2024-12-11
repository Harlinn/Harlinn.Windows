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

#include <HCCMath.h>


using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Math;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    struct FloatingPointDecoder
    {
        using FloatingPoint = Math::Internal::FloatingPoint<double>;
        static constexpr UInt64 FractionMask = FloatingPoint::FractionMask;
        static constexpr Int32 FractionWidth = FloatingPoint::FractionWidth;

        static constexpr UInt64 ExponentBias = FloatingPoint::ExponentBias;
        static constexpr UInt64 ExponentMask = FloatingPoint::ExponentMask;
        static constexpr Int32 ExponentWidth = FloatingPoint::ExponentWidth;
        static constexpr Int32 MaxExponentValue = FloatingPoint::MaxExponentValue;

        static constexpr UInt64 SignMask = FloatingPoint::SignMask;

        double value_;
        FloatingPoint fp_;
        UInt64 uiValue_;
        UInt64 uiFractionMasked_;
        UInt64 fraction_;
        UInt64 uiExponentMasked_;
        UInt64 uiSignMasked_;
        bool signed_;
        UInt64 uiExponentShifted_;
        Int32 iExponent_;
        Int32 exponent_;

        double ceil_;
        double fpceil_;
        double trunc_;
        double fptrunc_;
        //double round_;
        double floor_;
        double fpfloor_;



        FloatingPointDecoder( double v )
            : value_( v ), fp_( v )
        {
            uiValue_ = fp_.AsUnsigned( );
            uiFractionMasked_ = uiValue_ & FractionMask;
            uiExponentMasked_ = uiValue_ & ExponentMask;
            uiSignMasked_ = uiValue_ & SignMask;

            uiExponentShifted_ = uiExponentMasked_ >> FractionWidth;
            iExponent_ = static_cast<Int32>( static_cast<Int64>( uiExponentShifted_ ) - ExponentBias );

            fraction_ = fp_.Fraction( );
            exponent_ = fp_.Exponent( );
            signed_ = fp_.Sign( );

            ceil_ = fp_.Ceil( );
            fpceil_ = __ceil( v );
            trunc_ = fp_.Trunc( );
            fptrunc_ = __trunc( v );
            floor_ = fp_.Floor( );
            fpfloor_ = __floor( v );
        }


    };

}

BOOST_FIXTURE_TEST_SUITE( MathTests, LocalFixture )

#if 0
// --run_test=MathTests/ConstexprStdTest1
BOOST_AUTO_TEST_CASE( ConstexprStdTest1 )
{
    constexpr double absResult = std::abs( -1.0 );
}
#endif
// --run_test=MathTests/ConstexprMathTest1
BOOST_AUTO_TEST_CASE( ConstexprMathTest1 )
{
    constexpr double absResult = Abs( -1.0 );
    BOOST_CHECK( absResult == 1.0 );
}


// --run_test=MathTests/boolSignumTest1
BOOST_AUTO_TEST_CASE( boolSignumTest1 )
{
    constexpr auto falseBoolVal = signum( static_cast<bool>( false ) );
    BOOST_CHECK( falseBoolVal == false );
    constexpr auto trueBoolVal = signum( static_cast<bool>( true ) );
    BOOST_CHECK( trueBoolVal == true );
}

// --run_test=MathTests/SByteSignumTest1
BOOST_AUTO_TEST_CASE( SByteSignumTest1 )
{
    constexpr auto negativeValue = signum( static_cast<SByte>( -2 ) );
    BOOST_CHECK( negativeValue == -1 );
    constexpr auto zeroValue = signum( static_cast<SByte>( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast<SByte>( 2 ) );
    BOOST_CHECK( positiveValue == 1 );
}

// --run_test=MathTests/ByteSignumTest1
BOOST_AUTO_TEST_CASE( ByteSignumTest1 )
{
    constexpr auto positiveValue1 = signum( static_cast<Byte>( -2 ) );
    BOOST_CHECK( positiveValue1 == 1 );
    constexpr auto zeroValue = signum( static_cast<Byte>( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue2 = signum( static_cast<Byte>( 2 ) );
    BOOST_CHECK( positiveValue2 == 1 );
}

// --run_test=MathTests/Int16SignumTest1
BOOST_AUTO_TEST_CASE( Int16SignumTest1 )
{
    constexpr auto negativeValue = signum( static_cast<Int16>( -2 ) );
    BOOST_CHECK( negativeValue == -1 );
    constexpr auto zeroValue = signum( static_cast<Int16>( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast<Int16>( 2 ) );
    BOOST_CHECK( positiveValue == 1 );
}
// --run_test=MathTests/UInt16SignumTest1
BOOST_AUTO_TEST_CASE( UInt16SignumTest1 )
{
    constexpr auto positiveValue1 = signum( static_cast<UInt16>( -2 ) );
    BOOST_CHECK( positiveValue1 == 1 );
    constexpr auto zeroValue = signum( static_cast<UInt16>( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue2 = signum( static_cast<UInt16>( 2 ) );
    BOOST_CHECK( positiveValue2 == 1 );
}

// --run_test=MathTests/Int32SignumTest1
BOOST_AUTO_TEST_CASE( Int32SignumTest1 )
{
    constexpr auto negativeValue = signum( static_cast<Int32>( -2 ) );
    BOOST_CHECK( negativeValue == -1 );
    constexpr auto zeroValue = signum( static_cast<Int32>( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast<Int32>( 2 ) );
    BOOST_CHECK( positiveValue == 1 );
}
// --run_test=MathTests/UInt32SignumTest1
BOOST_AUTO_TEST_CASE( UInt32SignumTest1 )
{
    constexpr auto positiveValue1 = signum( static_cast<UInt32>( -2 ) );
    BOOST_CHECK( positiveValue1 == 1 );
    constexpr auto zeroValue = signum( static_cast<UInt32>( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue2 = signum( static_cast<UInt32>( 2 ) );
    BOOST_CHECK( positiveValue2 == 1 );
}

// --run_test=MathTests/Int64SignumTest1
BOOST_AUTO_TEST_CASE( Int64SignumTest1 )
{
    constexpr auto negativeValue = signum( static_cast<Int64>( -2 ) );
    BOOST_CHECK( negativeValue == -1 );
    constexpr auto zeroValue = signum( static_cast<Int64>( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast<Int64>( 2 ) );
    BOOST_CHECK( positiveValue == 1 );
}
// --run_test=MathTests/UInt64SignumTest1
BOOST_AUTO_TEST_CASE( UInt64SignumTest1 )
{
    constexpr auto positiveValue1 = signum( static_cast<UInt64>( -2 ) );
    BOOST_CHECK( positiveValue1 == 1 );
    constexpr auto zeroValue = signum( static_cast<UInt64>( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue2 = signum( static_cast<UInt64>( 2 ) );
    BOOST_CHECK( positiveValue2 == 1 );
}

// --run_test=MathTests/wchar_tSignumTest1
BOOST_AUTO_TEST_CASE( wchar_tSignumTest1 )
{
    constexpr auto positiveValue1 = signum( static_cast<wchar_t>( -2 ) );
    BOOST_CHECK( positiveValue1 == 1 );
    constexpr auto zeroValue = signum( static_cast<wchar_t>( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue2 = signum( static_cast<wchar_t>( 2 ) );
    BOOST_CHECK( positiveValue2 == 1 );
}

// --run_test=MathTests/SingleSignumTest1
BOOST_AUTO_TEST_CASE( SingleSignumTest1 )
{
    constexpr auto negativeValue = signum( static_cast<float>( -2 ) );
    BOOST_CHECK( negativeValue == -1 );
    constexpr auto zeroValue = signum( static_cast<float>( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast<float>( 2 ) );
    BOOST_CHECK( positiveValue == 1 );
}

// --run_test=MathTests/DoubleSignumTest1
BOOST_AUTO_TEST_CASE( DoubleSignumTest1 )
{
    constexpr auto negativeValue = signum( static_cast<Double>( -2 ) );
    BOOST_CHECK( negativeValue == -1 );
    constexpr auto zeroValue = signum( static_cast<Double>( 0 ) );
    BOOST_CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast<Double>( 2 ) );
    BOOST_CHECK( positiveValue == 1 );
}

// --run_test=MathTests/FloatingPointDoubleExponentTest1
BOOST_AUTO_TEST_CASE( FloatingPointDoubleExponentTest1 )
{
    using FloatingPoint = FloatingPointDecoder::FloatingPoint;
    using FPD = FloatingPointDecoder;

    constexpr double dblOne = std::bit_cast<double>( 0x3FF0000000000000ULL );
    constexpr double dblGtThanOne = std::bit_cast<double>( 0x3FF0000000000001ULL );
    constexpr double dblGtThanGtThanOne = std::bit_cast<double>( 0x3FF0000000000002ULL );
    constexpr double dblTwo = std::bit_cast<double>( 0x4000000000000000ULL );
    constexpr double dblMinusTwo = std::bit_cast<double>( 0xC000000000000000ULL );
    constexpr double dblThree = std::bit_cast<double>( 0x4008000000000000ULL );
    constexpr double dblFour = std::bit_cast<double>( 0x4010000000000000ULL );
    constexpr double dblFive = std::bit_cast<double>( 0x4014000000000000ULL );
    constexpr double dblSix = std::bit_cast<double>( 0x4018000000000000ULL );

    FPD fpdLtMinusThree( std::nextafter( -3.0, -4.0 ) );
    FPD fpdGtMinusThree( std::nextafter( -3.0, 0.0 ) );
    FPD fpdMinusTwoPointFive( -2.5 );
    FPD fpdMinusOnePointFive( -1.5 );
    FPD fpdMinusOne( -1.0 );
    FPD fpdMinusZeroPointFive( -0.5 );
    FPD fpdLtMinusZero( std::nextafter( -0.0, -1.0 ) );
    FPD fpdMinusZero( -0.0 );
    FPD fpdZero( 0.0 );
    FPD fpdGtZero( std::nextafter( 0.0, 1.0 ) );
    FPD fpdZeroPointFive( 0.5 );
    FPD fpdOne( dblOne );
    FPD fpdGtThanOne( dblGtThanOne );
    FPD fpdGtThanGtThanOne( dblGtThanGtThanOne );
    FPD fpdOnePointFive( 1.5 );
    FPD fpdTwo( dblTwo );
    FPD fpdMinusTwo( dblMinusTwo );
    FPD fpdThree( dblThree );
    FPD fpdFour( dblFour );
    FPD fpdFive( dblFive );
    FPD fpdSix( dblSix );

    printf( "Stop\n" );


}

// --run_test=MathTests/IsNaNDoubleTest1
BOOST_AUTO_TEST_CASE( IsNaNDoubleTest1 )
{
    double value = std::numeric_limits<double>::quiet_NaN( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = -std::numeric_limits<double>::infinity( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );
    value = std::numeric_limits<double>::infinity( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = std::numeric_limits<double>::lowest( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = std::numeric_limits<double>::min( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = -std::numeric_limits<double>::min( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = std::numeric_limits<double>::max( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = std::numeric_limits<double>::epsilon( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = std::numeric_limits<double>::denorm_min( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = -std::numeric_limits<double>::denorm_min( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = -0.0;
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = 0.0;
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );
}


// --run_test=MathTests/IsInfDoubleTest1
BOOST_AUTO_TEST_CASE( IsInfDoubleTest1 )
{
    double value = std::numeric_limits<double>::quiet_NaN( );
    BOOST_CHECK( IsInf( value ) == std::isinf( value ) );

    value = -std::numeric_limits<double>::infinity( );
    BOOST_CHECK( IsInf( value ) == std::isinf( value ) );
    value = std::numeric_limits<double>::infinity( );
    BOOST_CHECK( IsInf( value ) == std::isinf( value ) );

    value = std::numeric_limits<double>::lowest( );
    BOOST_CHECK( IsInf( value ) == std::isinf( value ) );

    value = std::numeric_limits<double>::min( );
    BOOST_CHECK( IsInf( value ) == std::isinf( value ) );

    value = -std::numeric_limits<double>::min( );
    BOOST_CHECK( IsInf( value ) == std::isinf( value ) );

    value = std::numeric_limits<double>::max( );
    BOOST_CHECK( IsInf( value ) == std::isinf( value ) );

    value = std::numeric_limits<double>::epsilon( );
    BOOST_CHECK( IsInf( value ) == std::isinf( value ) );

    value = std::numeric_limits<double>::denorm_min( );
    BOOST_CHECK( IsInf( value ) == std::isinf( value ) );

    value = -std::numeric_limits<double>::denorm_min( );
    BOOST_CHECK( IsInf( value ) == std::isinf( value ) );

    value = -0.0;
    BOOST_CHECK( IsInf( value ) == std::isinf( value ) );

    value = 0.0;
    BOOST_CHECK( IsInf( value ) == std::isinf( value ) );
}

// --run_test=MathTests/AbsDoubleTest1
BOOST_AUTO_TEST_CASE( AbsDoubleTest1 )
{
    double value = std::numeric_limits<double>::quiet_NaN( );
    double result = Abs( value );
    double stdResult = std::abs( value );
    UInt64 uiResult = std::bit_cast<UInt64>( result );
    UInt64 stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::isinf( result ) == std::isinf( stdResult ) );

    value = -std::numeric_limits<double>::infinity( );
    result = Abs( value );
    result = Math::Internal::AbsImpl<double>( value );
    stdResult = std::abs( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::infinity( );
    result = Abs( value );
    stdResult = std::abs( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::lowest( );
    result = Abs( value );
    stdResult = std::abs( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::min( );
    result = Abs( value );
    stdResult = std::abs( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -std::numeric_limits<double>::min( );
    result = Abs( value );
    stdResult = std::abs( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::max( );
    result = Abs( value );
    stdResult = std::abs( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::epsilon( );
    result = Abs( value );
    stdResult = std::abs( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::denorm_min( );
    result = Abs( value );
    stdResult = std::abs( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -std::numeric_limits<double>::denorm_min( );
    result = Abs( value );
    stdResult = std::abs( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -0.0;
    result = Abs( value );
    stdResult = std::abs( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = 0.0;
    result = Abs( value );
    stdResult = std::abs( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );
}

// --run_test=MathTests/SignBitDoubleTest1
BOOST_AUTO_TEST_CASE( SignBitDoubleTest1 )
{
    double value = -std::numeric_limits<double>::quiet_NaN( );

    auto signBit1 = SignBit( value ) != 0;
    auto signBit2 = std::signbit( value );

    BOOST_CHECK( signBit1 == signBit2 );

    value = std::numeric_limits<double>::quiet_NaN( );

    signBit1 = SignBit( value ) == 0;
    signBit2 = std::signbit( value ) == false;

    BOOST_CHECK( signBit1 == signBit2 );

    value = -std::numeric_limits<double>::infinity( );

    signBit1 = SignBit( value ) != 0;
    signBit2 = std::signbit( value );

    BOOST_CHECK( signBit1 == signBit2 );

    value = std::numeric_limits<double>::infinity( );

    signBit1 = SignBit( value ) == 0;
    signBit2 = std::signbit( value ) == false;

    BOOST_CHECK( signBit1 == signBit2 );


    value = std::numeric_limits<double>::lowest( );

    signBit1 = SignBit( value ) != 0;
    signBit2 = std::signbit( value );

    BOOST_CHECK( signBit1 == signBit2 );


    value = std::numeric_limits<double>::min( );

    signBit1 = SignBit( value ) == 0;
    signBit2 = std::signbit( value ) == false;

    BOOST_CHECK( signBit1 == signBit2 );


    value = -std::numeric_limits<double>::min( );

    signBit1 = SignBit( value ) != 0;
    signBit2 = std::signbit( value );

    BOOST_CHECK( signBit1 == signBit2 );


    value = std::numeric_limits<double>::max( );

    signBit1 = SignBit( value ) == 0;
    signBit2 = std::signbit( value ) == false;

    BOOST_CHECK( signBit1 == signBit2 );


    value = std::numeric_limits<double>::epsilon( );

    signBit1 = SignBit( value ) == 0;
    signBit2 = std::signbit( value ) == false;

    BOOST_CHECK( signBit1 == signBit2 );


    value = std::numeric_limits<double>::denorm_min( );

    signBit1 = SignBit( value ) == 0;
    signBit2 = std::signbit( value ) == false;

    BOOST_CHECK( signBit1 == signBit2 );


    value = -std::numeric_limits<double>::denorm_min( );

    signBit1 = SignBit( value ) != 0;
    signBit2 = std::signbit( value );

    BOOST_CHECK( signBit1 == signBit2 );


    value = -0.0;

    signBit1 = SignBit( value ) != 0; 
    signBit2 = std::signbit( value );

    BOOST_CHECK( signBit1 == signBit2 );


    value = 0.0;

    signBit1 = SignBit( value ) == 0;
    signBit2 = std::signbit( value ) == false;

    BOOST_CHECK( signBit1 == signBit2 );

}

// --run_test=MathTests/FRExpDoubleTest1
BOOST_AUTO_TEST_CASE( FRExpDoubleTest1 )
{
    double value = -std::numeric_limits<double>::quiet_NaN( );

    int exp = 0;
    double result = FRExp( value, exp );
    int stdExp = 0;
    double stdResult = std::frexp( value, &stdExp );
    UInt64 uiResult = std::bit_cast<UInt64>( result );
    UInt64 uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );

    value = std::numeric_limits<double>::quiet_NaN( );

    exp = 0;
    result = FRExp( value, exp );
    stdExp = 0;
    stdResult = std::frexp( value, &stdExp );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );

    value = -std::numeric_limits<double>::infinity( );
    exp = 0;
    result = FRExp( value, exp );
    stdExp = 0;
    stdResult = std::frexp( value, &stdExp );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );

    value = std::numeric_limits<double>::infinity( );
    exp = 0;
    result = FRExp( value, exp );
    stdExp = 0;
    stdResult = std::frexp( value, &stdExp );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );

    value = std::numeric_limits<double>::lowest( );
    exp = 0;
    result = FRExp( value, exp );
    stdExp = 0;
    stdResult = std::frexp( value, &stdExp );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );

    value = std::numeric_limits<double>::min( );
    exp = 0;
    result = FRExp( value, exp );
    stdExp = 0;
    stdResult = std::frexp( value, &stdExp );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );

    value = -std::numeric_limits<double>::min( );
    exp = 0;
    result = FRExp( value, exp );
    stdExp = 0;
    stdResult = std::frexp( value, &stdExp );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );

    value = std::numeric_limits<double>::max( );
    exp = 0;
    result = FRExp( value, exp );
    stdExp = 0;
    stdResult = std::frexp( value, &stdExp );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );

    value = std::numeric_limits<double>::epsilon( );
    exp = 0;
    result = FRExp( value, exp );
    stdExp = 0;
    stdResult = std::frexp( value, &stdExp );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );

    value = std::numeric_limits<double>::denorm_min( );
    exp = 0;
    result = FRExp( value, exp );
    stdExp = 0;
    stdResult = std::frexp( value, &stdExp );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );

    value = -std::numeric_limits<double>::denorm_min( );
    exp = 0;
    result = FRExp( value, exp );
    stdExp = 0;
    stdResult = std::frexp( value, &stdExp );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );

    value = -0.0;
    exp = 0;
    result = FRExp( value, exp );
    stdExp = 0;
    stdResult = std::frexp( value, &stdExp );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );

    value = 0.0;
    exp = 0;
    result = FRExp( value, exp );
    stdExp = 0;
    stdResult = std::frexp( value, &stdExp );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( exp == stdExp );
}

// --run_test=MathTests/ModFDoubleTest1
BOOST_AUTO_TEST_CASE( ModFDoubleTest1 )
{
    double value = -std::numeric_limits<double>::quiet_NaN( );

    double integerPart = 0;
    double result = ModF( value, integerPart );
    double stdIntegerPart = 0;
    double stdResult = std::modf( value, &stdIntegerPart );
    UInt64 uiResult = std::bit_cast<UInt64>( result );
    UInt64 uiStdResult = std::bit_cast<UInt64>( stdResult );
    UInt64 uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    UInt64 uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = std::numeric_limits<double>::quiet_NaN( );
     
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = -std::numeric_limits<double>::infinity( );
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = std::numeric_limits<double>::infinity( );
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = std::numeric_limits<double>::lowest( );
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = std::numeric_limits<double>::min( );
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = -std::numeric_limits<double>::min( );
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = std::numeric_limits<double>::max( );
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = std::numeric_limits<double>::epsilon( );
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = std::numeric_limits<double>::denorm_min( );
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = -std::numeric_limits<double>::denorm_min( );
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = -0.0;
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = 0.0;
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );

    value = M_PI;
    integerPart = 0;
    result = ModF( value, integerPart );
    stdIntegerPart = 0;
    stdResult = std::modf( value, &stdIntegerPart );
    uiResult = std::bit_cast<UInt64>( result );
    uiStdResult = std::bit_cast<UInt64>( stdResult );
    uiIntegerPart = std::bit_cast<UInt64>( integerPart );
    uiStdIntegerPart = std::bit_cast<UInt64>( stdIntegerPart );
    BOOST_CHECK( uiResult == uiStdResult );
    BOOST_CHECK( uiIntegerPart == uiStdIntegerPart );


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

// --run_test=MathTests/MinDoubleTest2
BOOST_AUTO_TEST_CASE( MinDoubleTest2 )
{
    double val1 = 1.0;
    double val2 = 2.0;

    double result = Min( val1, val2 );

    bool equal = AreNearlyEqual( val1, result );
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

// --run_test=MathTests/MaxDoubleTest2
BOOST_AUTO_TEST_CASE( MaxDoubleTest2 )
{
    double val1 = 2.0;
    double val2 = 1.0;

    double result = Max( val1, val2 );

    bool equal = AreNearlyEqual( val1, result );
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
    constexpr double result2 = Floor( value2 );
    constexpr double result3 = Floor( value3 );
    constexpr double result4 = Floor( value4 );
    constexpr double result5 = Floor( value5 );
    constexpr double result6 = Floor( value6 );

}

// --run_test=MathTests/FloorDoubleTest2
BOOST_AUTO_TEST_CASE( FloorDoubleTest2 )
{
    double value = std::numeric_limits<double>::quiet_NaN( );
    double result = Floor( value );
    double stdResult = std::floor( value );
    UInt64 uiResult = std::bit_cast<UInt64>( result );
    UInt64 stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::isinf( result ) == std::isinf( stdResult ) );

    value = -std::numeric_limits<double>::infinity( );
    result = Floor( value );
    stdResult = std::floor( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::infinity( );
    result = Floor( value );
    stdResult = std::floor( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::lowest( );
    result = Floor( value );
    stdResult = std::floor( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::min( );
    result = Floor( value );
    stdResult = std::floor( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -std::numeric_limits<double>::min( );
    result = Floor( value );
    stdResult = std::floor( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::max( );
    result = Floor( value );
    stdResult = std::floor( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::epsilon( );
    result = Floor( value );
    stdResult = std::floor( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::denorm_min( );
    result = Floor( value );
    stdResult = std::floor( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -std::numeric_limits<double>::denorm_min( );
    result = Floor( value );
    stdResult = std::floor( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -0.0;
    result = Floor( value );
    stdResult = std::floor( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = 0.0;
    result = Floor( value );
    stdResult = std::floor( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );
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
    constexpr double result2 = Ceil( value2 );
    constexpr double result3 = Ceil( value3 );
    constexpr double result4 = Ceil( value4 );
    constexpr double result5 = Ceil( value5 );
    constexpr double result6 = Ceil( value6 );

}

// --run_test=MathTests/CeilDoubleTest2
BOOST_AUTO_TEST_CASE( CeilDoubleTest2 )
{
    double value = std::numeric_limits<double>::quiet_NaN( );
    double result = Ceil( value );
    double stdResult = std::ceil( value );
    UInt64 uiResult = std::bit_cast<UInt64>( result );
    UInt64 stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::isinf( result ) == std::isinf( stdResult ) );

    value = -std::numeric_limits<double>::infinity( );
    result = Ceil( value );
    stdResult = std::ceil( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::infinity( );
    result = Ceil( value );
    stdResult = std::ceil( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::lowest( );
    result = Ceil( value );
    stdResult = std::ceil( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::min( );
    result = Ceil( value );
    stdResult = std::ceil( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -std::numeric_limits<double>::min( );
    result = Ceil( value );
    stdResult = std::ceil( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::max( );
    result = Ceil( value );
    stdResult = std::ceil( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::epsilon( );
    result = Ceil( value );
    stdResult = std::ceil( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::denorm_min( );
    result = Ceil( value );
    stdResult = std::ceil( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -std::numeric_limits<double>::denorm_min( );
    result = Ceil( value );
    stdResult = std::ceil( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -0.0;
    result = Ceil( value );
    stdResult = std::ceil( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = 0.0;
    result = Ceil( value );
    stdResult = std::ceil( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

}




// --run_test=MathTests/TruncDoubleTest2
BOOST_AUTO_TEST_CASE( TruncDoubleTest2 )
{
    double value = std::numeric_limits<double>::quiet_NaN( );
    double result = Trunc( value );
    double stdResult = std::trunc( value );
    UInt64 uiResult = std::bit_cast<UInt64>( result );
    UInt64 stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::isinf( result ) == std::isinf( stdResult ) );

    value = -std::numeric_limits<double>::infinity( );
    result = Trunc( value );
    stdResult = std::trunc( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::infinity( );
    result = Trunc( value );
    stdResult = std::trunc( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::lowest( );
    result = Trunc( value );
    stdResult = std::trunc( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::min( );
    result = Trunc( value );
    stdResult = std::trunc( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -std::numeric_limits<double>::min( );
    result = Trunc( value );
    stdResult = std::trunc( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::max( );
    result = Trunc( value );
    stdResult = std::trunc( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::epsilon( );
    result = Trunc( value );
    stdResult = std::trunc( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::denorm_min( );
    result = Trunc( value );
    stdResult = std::trunc( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -std::numeric_limits<double>::denorm_min( );
    result = Trunc( value );
    stdResult = std::trunc( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -0.0;
    result = Trunc( value );
    stdResult = std::trunc( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = 0.0;
    result = Trunc( value );
    stdResult = std::trunc( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );
}

// --run_test=MathTests/RoundDoubleTest2
BOOST_AUTO_TEST_CASE( RoundDoubleTest2 )
{
    double value = std::numeric_limits<double>::quiet_NaN( );
    double result = Round( value );
    double stdResult = std::round( value );
    UInt64 uiResult = std::bit_cast<UInt64>( result );
    UInt64 stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::isinf( result ) == std::isinf( stdResult ) );

    value = -std::numeric_limits<double>::infinity( );
    result = Round( value );
    stdResult = std::round( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::infinity( );
    result = Round( value );
    stdResult = std::round( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::lowest( );
    result = Round( value );
    stdResult = std::round( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::min( );
    result = Round( value );
    stdResult = std::round( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -std::numeric_limits<double>::min( );
    result = Round( value );
    stdResult = std::round( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::max( );
    result = Round( value );
    stdResult = std::round( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::epsilon( );
    result = Round( value );
    stdResult = std::round( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = std::numeric_limits<double>::denorm_min( );
    result = Round( value );
    stdResult = std::round( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -std::numeric_limits<double>::denorm_min( );
    result = Round( value );
    stdResult = std::round( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = -0.0;
    result = Round( value );
    stdResult = std::round( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );

    value = 0.0;
    result = Round( value );
    stdResult = std::round( value );
    uiResult = std::bit_cast<UInt64>( result );
    stdUInt64Result = std::bit_cast<UInt64>( stdResult );
    BOOST_CHECK( std::bit_cast<UInt64>( result ) == std::bit_cast<UInt64>( stdResult ) );
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
    constexpr auto radians = Deg2Rad( 0.001 );
    constexpr auto result1a = Sin( radians );
    auto result1b = std::sin( radians );
    auto result1Diff = result1a - result1b;
    BOOST_CHECK( result1a == result1b );
    BOOST_CHECK( result1a == 1.7453292519057202e-5 );
    BOOST_CHECK( result1b == 1.7453292519057202e-5 );
}


// --run_test=MathTests/Log2DoubleTest2
BOOST_AUTO_TEST_CASE( Log2DoubleTest2 )
{
    constexpr double increment = 1.0000000000000001e-09;
    constexpr double argValue2 = 1.4142112734437984;
    constexpr double argValue1 = argValue2 - increment;

    double result1a = Log2( argValue1 );
    double result1b = std::log2( argValue1 );
    BOOST_CHECK( result1a == result1b );

    double result2a = Log2( argValue2 );
    double result2b = std::log2( argValue2 );
    BOOST_CHECK( result2a == result2b );

}



// --run_test=MathTests/IsNaNFloatTest1
BOOST_AUTO_TEST_CASE( IsNaNFloatTest1 )
{
    float value = std::numeric_limits<float>::quiet_NaN( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = -std::numeric_limits<float>::infinity( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );
    value = std::numeric_limits<float>::infinity( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = std::numeric_limits<float>::lowest( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );

    value = std::numeric_limits<float>::max( );
    BOOST_CHECK( IsNaN( value ) == std::isnan( value ) );
}


// --run_test=MathTests/MinFloatTest1
BOOST_AUTO_TEST_CASE( MinFloatTest1 )
{
    constexpr float val1 = 1.0f;
    constexpr float val2 = 2.0f;

    constexpr float result = Min( val1, val2 );

    constexpr bool equal = AreNearlyEqual( val1, result );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/MinFloatTest2
BOOST_AUTO_TEST_CASE( MinFloatTest2 )
{
    float val1 = 1.0f;
    float val2 = 2.0f;

    float result = Min( val1, val2 );

    bool equal = AreNearlyEqual( val1, result );
    BOOST_CHECK( equal );

}


// --run_test=MathTests/MaxFloatTest1
BOOST_AUTO_TEST_CASE( MaxFloatTest1 )
{
    constexpr float val1 = 2.0;
    constexpr float val2 = 1.0;

    constexpr float result = Max( val1, val2 );

    constexpr bool equal = AreNearlyEqual( val1, result );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/MaxFloatTest2
BOOST_AUTO_TEST_CASE( MaxFloatTest2 )
{
    float val1 = 2.0;
    float val2 = 1.0;

    float result = Max( val1, val2 );

    bool equal = AreNearlyEqual( val1, result );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/NextAfterDoubleTest1
BOOST_AUTO_TEST_CASE( NextAfterDoubleTest1 )
{
    constexpr double val1 = 2.0;
    constexpr double val2 = 1.0;

    constexpr double result1 = NextAfter( val1, val2 );
    static_assert( result1 < val1 );

    double result2 = std::nextafter( val1, val2 );

    bool equal = IsSameValue( result2, result1 );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/NextUpDoubleTest1
BOOST_AUTO_TEST_CASE( NextUpDoubleTest1 )
{
    constexpr double val1 = 2.0;
    constexpr double val2 = 1.0;

    constexpr double result1 = NextUp( val2 );
    static_assert( result1 > val2 );

    double result2 = std::nextafter( val2, val1 );

    bool equal = IsSameValue( result2, result1 );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/NextDownDoubleTest1
BOOST_AUTO_TEST_CASE( NextDownDoubleTest1 )
{
    constexpr double val1 = 2.0;
    constexpr double val2 = 1.0;

    constexpr double result1 = NextDown( val1 );
    static_assert( result1 > val2 );

    double result2 = std::nextafter( val1, val2 );

    bool equal = IsSameValue( result2, result1 );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/HypotDoubleTest1
BOOST_AUTO_TEST_CASE( HypotDoubleTest1 )
{
    constexpr double val1 = 2.0;
    constexpr double val2 = 3.0;

    constexpr double result1 = Hypot( val1, val2 );
    static_assert( result1 > val2 );

    double result2 = Hypot( val1, val2 );
    double result3 = std::hypot( val1, val2 );

    bool equal = IsSameValue( result3, result1 );
    BOOST_CHECK( equal );
    equal = IsSameValue( result3, result2 );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/HypotFloatTest1 )
BOOST_AUTO_TEST_CASE( HypotFloatTest1 )
{
    constexpr float val1 = 2.0;
    constexpr float val2 = 3.0;

    constexpr float result1 = Hypot( val1, val2 );
    static_assert( result1 > val2 );

    float result2 = Hypot( val1, val2 );
    float result3 = std::hypot( val1, val2 );

    bool equal = IsSameValue( result3, result1 );
    BOOST_CHECK( equal );
    equal = IsSameValue( result3, result2 );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/Hypot3DoubleTest1
BOOST_AUTO_TEST_CASE( Hypot3DoubleTest1 )
{
    constexpr double val1 = 2.0;
    constexpr double val2 = 3.0;
    constexpr double val3 = 4.0;

    constexpr double result1 = Hypot( val1, val2, val3 );
    static_assert( result1 > val2 );

    double result2 = Hypot( val1, val2, val3 );
    double result3 = std::hypot( val1, val2, val3 );

    bool equal = IsSameValue( result3, result1 );
    BOOST_CHECK( equal );
    equal = IsSameValue( result3, result2 );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/Hypot3FloatTest1 )
BOOST_AUTO_TEST_CASE( Hypot3FloatTest1 )
{
    constexpr float val1 = 2.0;
    constexpr float val2 = 3.0;
    constexpr float val3 = 4.0;

    constexpr float result1 = Hypot( val1, val2, val3 );
    static_assert( result1 > val2 );

    float result2 = Hypot( val1, val2, val3 );
    float result3 = std::hypot( val1, val2, val3 );

    bool equal = IsSameValue( result3, result1 );
    BOOST_CHECK( equal );
    equal = IsSameValue( result3, result2 );
    BOOST_CHECK( equal );

}



BOOST_AUTO_TEST_SUITE_END( )
