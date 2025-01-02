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
        using FloatingPoint = Math::FloatingPoint<double>;
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

            fraction_ = fp_.FractionValue( );
            exponent_ = fp_.ExponentValue( );
            signed_ = fp_.Signed( );

            ceil_ = fp_.Ceil( );
            fpceil_ = __ceil( v );
            trunc_ = fp_.Trunc( );
            fptrunc_ = __trunc( v );
            floor_ = fp_.Floor( );
            fpfloor_ = __floor( v );
        }
    };


    template<typename StdFunc, typename MathFunc, typename StepFunc, typename FloatT>
    void RangeTest( const char* testName, StdFunc stdFunc, MathFunc mathFunc, StepFunc stepFunc, FloatT start, FloatT stop, double maxAllowedDeviation = 1e-5 )
    {
        auto value = start;
        Int64 unexpectedDeviationCount = 0;
        Int64 testCount = 0;
        bool isFirst = true;
        double maxDeviation = 0.0;
        double maxDeviationFor = 0.0;
        double maxDeviationStdResult = 0.0;
        double maxDeviationMathResult = 0.0;
        double firstDeviation = 0.0;
        double lastDeviation = 0.0;
        while ( value < stop )
        {
            auto stdResult = stdFunc( value );
            auto mathResult = mathFunc( value );
            auto deviation = Deviation( stdResult, mathResult );

            if ( deviation > maxDeviation )
            {
                maxDeviationFor = value;
                maxDeviation = deviation;
                maxDeviationStdResult = stdResult;
                maxDeviationMathResult = mathResult;
            }

            if ( deviation > maxAllowedDeviation )
            {
                if ( isFirst )
                {
                    firstDeviation = value;
                    isFirst = false;
                }
                lastDeviation = value;
                unexpectedDeviationCount++;
                
            }
            value = stepFunc( value );
            testCount++;
        }
        if ( unexpectedDeviationCount )
        {
            BOOST_CHECK( unexpectedDeviationCount == 0 );
            PrintLn( "{} -> Iterations: {}, unexpected deviations: {}, max deviation: {:g}, for: {:g}, std: {:g}, Math: {:g}, first unexpected: {:g}, last unexpected: {:g}.",
                testName, testCount, unexpectedDeviationCount, maxDeviation, maxDeviationFor, maxDeviationStdResult, maxDeviationMathResult, firstDeviation, lastDeviation );
        }
        else
        {
            if ( maxDeviation )
            {
                PrintLn( "{} -> Iterations: {}, no unexpected deviations, max deviation: {:g}, for: {:g}, std: {:g}, Math: {:g}.",
                    testName, testCount, maxDeviation, maxDeviationFor, maxDeviationStdResult, maxDeviationMathResult );
            }
            else
            {
                PrintLn( "{} -> Iterations: {}, no unexpected deviations.", testName, testCount, maxDeviation );
            }
        }
    }

    template<typename FloatT, typename StdFunc, typename MathFunc>
    void TrigonometricRangeTest( const char* testName, StdFunc stdFunc, MathFunc mathFunc, double maxDeviation = 1e-5 )
    {
        constexpr FloatT start = ( static_cast< FloatT >( -2 ) * Constants<FloatT>::Pi ) - std::numeric_limits<FloatT>::epsilon( );
        constexpr FloatT stop = ( static_cast< FloatT >( 2 ) * Constants<FloatT>::Pi ) + std::numeric_limits<FloatT>::epsilon( );

        if constexpr ( std::is_same_v<float, FloatT> )
        {
            RangeTest( testName, stdFunc, mathFunc, []( float value ) { return NextUp( value ); }, start, stop, maxDeviation );
        }
        else
        {
            RangeTest( testName, stdFunc, mathFunc, []( double value ) { return static_cast< double >( NextUp( static_cast< float >( value ) ) ); }, start, stop, maxDeviation );
        }
    }

    template<typename FloatT, typename StdFunc, typename MathFunc>
    void ReverseTrigonometricRangeTest( const char* testName, StdFunc stdFunc, MathFunc mathFunc, double maxDeviation = 1e-5 )
    {
        constexpr FloatT start = static_cast< FloatT >( -1. );
        constexpr FloatT stop = static_cast< FloatT >( 1. );

        if constexpr ( std::is_same_v<float, FloatT> )
        {
            RangeTest( testName, stdFunc, mathFunc, []( float value ) { return NextUp( value ); }, start, stop, maxDeviation );
        }
        else
        {
            RangeTest( testName, stdFunc, mathFunc, []( double value ) { return static_cast< double >( NextUp( static_cast< float >( value ) ) ); }, start, stop, maxDeviation );
        }
    }


    template<typename FloatT, size_t iterations, typename StdFunc, typename MathFunc>
    void RandomValueTest( const char* testName, StdFunc stdFunc, MathFunc mathFunc, FloatT minValue = static_cast< FloatT >( -10000 ), FloatT maxValue = static_cast< FloatT >( -10000 ), double maxAllowedDeviation = 1e-5 )
    {
        constexpr size_t Iterations = iterations;
        RandomGenerator<FloatT, Iterations> generator( minValue, maxValue );

        Int64 unexpectedDeviationCount = 0;
        Int64 testCount = 0;
        bool isFirst = true;
        double maxDeviation = 0.0;
        double maxDeviationFor = 0.0;
        double maxDeviationStdResult = 0.0;
        double maxDeviationMathResult = 0.0;
        double firstDeviation = 0.0;
        double lastDeviation = 0.0;
        for ( size_t i = 0; i < Iterations; i++ )
        {
            auto value = generator( );
            auto stdResult = stdFunc( value );
            auto mathResult = mathFunc( value );
            auto deviation = Deviation( stdResult, mathResult );

            if ( deviation > maxDeviation )
            {
                maxDeviationFor = value;
                maxDeviation = deviation;
                maxDeviationStdResult = stdResult;
                maxDeviationMathResult = mathResult;
            }

            if ( deviation > maxAllowedDeviation )
            {
                if ( isFirst )
                {
                    firstDeviation = value;
                    isFirst = false;
                }
                lastDeviation = value;
                unexpectedDeviationCount++;

            }
            testCount++;
        }
        if ( unexpectedDeviationCount )
        {
            BOOST_CHECK( unexpectedDeviationCount == 0 );
            PrintLn( "{} -> Iterations: {}, unexpected deviations: {}, max deviation: {:g}, for: {:g}, std: {:g}, Math: {:g}, first unexpected: {:g}, last unexpected: {:g}",
                testName, testCount, unexpectedDeviationCount, maxDeviation, maxDeviationFor, maxDeviationStdResult, maxDeviationMathResult, firstDeviation, lastDeviation );
        }
        else
        {
            if ( maxDeviation )
            {
                PrintLn( "{} -> Iterations: {}, no unexpected deviations, max deviation: {:g}, for: {:g}, std: {:g}, Math: {:g}",
                    testName, testCount, maxDeviation, maxDeviationFor, maxDeviationStdResult, maxDeviationMathResult );
            }
            else
            {
                PrintLn( "{} -> Iterations: {}, no unexpected deviations.", testName, testCount );
            }
        }
    }

    template<typename FloatT, size_t iterations, typename StdFunc, typename MathFunc>
    void RandomValueTest2( const char* testName, StdFunc stdFunc, MathFunc mathFunc, FloatT minValue = static_cast< FloatT >( -10000 ), FloatT maxValue = static_cast< FloatT >( -10000 ), double maxAllowedDeviation = 1e-5 )
    {
        constexpr size_t Iterations = iterations;
        RandomGenerator<FloatT, Iterations> generator( minValue, maxValue );

        Int64 unexpectedDeviationCount = 0;
        Int64 testCount = 0;
        bool isFirst = true;
        double maxDeviation = 0.0;
        double maxDeviationForX = 0.0;
        double maxDeviationForY = 0.0;
        double maxDeviationStdResult = 0.0;
        double maxDeviationMathResult = 0.0;
        double firstDeviationX = 0.0;
        double firstDeviationY = 0.0;
        double lastDeviationX = 0.0;
        double lastDeviationY = 0.0;
        for ( size_t i = 0; i < Iterations; i++ )
        {
            auto x = generator( );
            auto y = generator( );
            if ( y )
            {
                auto stdResult = stdFunc( x, y );
                auto mathResult = mathFunc( x, y );
                auto deviation = Deviation( stdResult, mathResult );

                if ( deviation > maxDeviation )
                {
                    maxDeviationForX = x;
                    maxDeviationForY = y;
                    maxDeviation = deviation;
                    maxDeviationStdResult = stdResult;
                    maxDeviationMathResult = mathResult;
                }

                if ( deviation > maxAllowedDeviation )
                {
                    if ( isFirst )
                    {
                        firstDeviationX = x;
                        firstDeviationY = y;
                        isFirst = false;
                    }
                    lastDeviationX = x;
                    lastDeviationY = y;
                    unexpectedDeviationCount++;
                }
            }
            testCount++;
        }
        if ( unexpectedDeviationCount )
        {
            BOOST_CHECK( unexpectedDeviationCount == 0 );
            PrintLn( "{} -> Iterations: {}, unexpected deviations: {}, max deviation: {:g}, for X: {:g}, for Y: {:g}, std: {:g}, Math: {:g}, first unexpected x: {:g}, first unexpected y: {:g}, last unexpected x: {:g}, last unexpected y: {:g}.",
                testName, testCount, unexpectedDeviationCount, maxDeviation, maxDeviationForX, maxDeviationForY, maxDeviationStdResult, maxDeviationMathResult, firstDeviationX, firstDeviationY, lastDeviationX, lastDeviationY );
        }
        else
        {
            if ( maxDeviation )
            {
                PrintLn( "{} -> Iterations: {}, no unexpected deviations, max deviation: {:g}, for X: {:g}, for Y: {:g}, std: {:g}, Math: {:g}",
                    testName, testCount, maxDeviation, maxDeviationForX, maxDeviationForY, maxDeviationStdResult, maxDeviationMathResult );
            }
            else
            {
                PrintLn( "{} -> Iterations: {}, no unexpected deviations.", testName, testCount );
            }
        }
    }


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

inline double DeviationTest( double first, double second )
{
    using std::abs;
    if ( first <= second )
    {
        return abs( second - first ) / abs( first );
    }
    else
    {
        return abs( first - second  ) / abs( first );
    }
}

// --run_test=MathTests/DeviationTest1
BOOST_AUTO_TEST_CASE( DeviationTest1 )
{
    using namespace Test;
    auto deviation = DeviationTest( 3.f, 3.f );
    BOOST_CHECK( deviation == 0.f );

    deviation = DeviationTest( -3.f, 3.f );
    BOOST_CHECK( deviation == 2.f );

    deviation = DeviationTest( 3.f, -3.f );
    BOOST_CHECK( deviation == 2.f );

    auto expected = ( 4.5f / 3.f );
    deviation = DeviationTest( -3.f, 1.5f );
    BOOST_CHECK( deviation == expected );

    expected = ( 4.5f / 3.f );
    deviation = DeviationTest( 3.f, -1.5f );
    BOOST_CHECK( deviation == expected );

    expected = ( 4.5f / 1.5f );
    deviation = DeviationTest( -1.5f, 3.f );
    BOOST_CHECK( deviation == expected );

    expected = ( 4.5f / 1.5f );
    deviation = DeviationTest( 1.5f, -3.f );
    BOOST_CHECK( deviation == expected );

    expected = ( 1.5f / 1.5f );
    deviation = DeviationTest( -1.5f, -3.f );
    BOOST_CHECK( deviation == expected );

    expected = ( 1.5f / 3.f );
    deviation = DeviationTest( -3.f, -1.5f );
    BOOST_CHECK( deviation == expected );


}

// --run_test=MathTests/IsNaNDoubleTest1
BOOST_AUTO_TEST_CASE( IsNaNDoubleTest1 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = double;
    Generators::RandomGenerator<FloatT, 20000> generator;
    NumericTest test( "IsNaNDoubleTest1" );
    auto success = test.Run( generator, std::isnan<FloatT>, IsNaN<FloatT>,
        {
            std::numeric_limits<FloatT>::quiet_NaN( ),
            -std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::lowest( ),
            std::numeric_limits<FloatT>::min( ),
            -std::numeric_limits<FloatT>::min( ),
            std::numeric_limits<FloatT>::max( ),
            std::numeric_limits<FloatT>::epsilon( ),
            -std::numeric_limits<FloatT>::epsilon( ),
            std::numeric_limits<FloatT>::denorm_min( ),
            -std::numeric_limits<FloatT>::denorm_min( ),
            -0.0,0.0
        } );
    BOOST_CHECK( success );
}


// --run_test=MathTests/IsInfDoubleTest1
BOOST_AUTO_TEST_CASE( IsInfDoubleTest1 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = double;
    Generators::RandomGenerator<FloatT, 20000> generator;
    NumericTest test( "IsInfDoubleTest1" );
    auto success = test.Run( generator, std::isinf<FloatT>, IsInf<FloatT>,
        {
            std::numeric_limits<FloatT>::quiet_NaN( ),
            -std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::lowest( ),
            std::numeric_limits<FloatT>::min( ),
            -std::numeric_limits<FloatT>::min( ),
            std::numeric_limits<FloatT>::max( ),
            std::numeric_limits<FloatT>::epsilon( ),
            -std::numeric_limits<FloatT>::epsilon( ),
            std::numeric_limits<FloatT>::denorm_min( ),
            -std::numeric_limits<FloatT>::denorm_min( ),
            -0.0,0.0
        } );
    BOOST_CHECK( success );

}

// --run_test=MathTests/AbsDoubleTest1
BOOST_AUTO_TEST_CASE( AbsDoubleTest1 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = double;
    Generators::RandomGenerator<FloatT, 20000> generator;
    NumericTest test( "AbsDoubleTest1" );
    auto success = test.Run( generator, []( auto x ) { return std::abs( x ); }, []( auto x ) { return Abs( x ); },
        {
            std::numeric_limits<FloatT>::quiet_NaN( ),
            -std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::lowest( ),
            std::numeric_limits<FloatT>::min( ),
            -std::numeric_limits<FloatT>::min( ),
            std::numeric_limits<FloatT>::max( ),
            std::numeric_limits<FloatT>::epsilon( ),
            -std::numeric_limits<FloatT>::epsilon( ),
            std::numeric_limits<FloatT>::denorm_min( ),
            -std::numeric_limits<FloatT>::denorm_min( ),
            -0.0,0.0
        } );
    BOOST_CHECK( success );
}

// --run_test=MathTests/AbsImplDoubleTest1
BOOST_AUTO_TEST_CASE( AbsImplDoubleTest1 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = double;
    Generators::RandomGenerator<FloatT, 20000> generator;
    NumericTest test( "Math::Internal::AbsImplDoubleTest1" );
    auto success = test.Run( generator, []( auto x ) { return std::abs( x ); }, []( auto x ) { return Math::Internal::AbsImpl( x ); },
        {
            std::numeric_limits<FloatT>::quiet_NaN( ),
            -std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::lowest( ),
            std::numeric_limits<FloatT>::min( ),
            -std::numeric_limits<FloatT>::min( ),
            std::numeric_limits<FloatT>::max( ),
            std::numeric_limits<FloatT>::epsilon( ),
            -std::numeric_limits<FloatT>::epsilon( ),
            std::numeric_limits<FloatT>::denorm_min( ),
            -std::numeric_limits<FloatT>::denorm_min( ),
            -0.0,0.0
        } );
    BOOST_CHECK( success );
}


// --run_test=MathTests/SignBitDoubleTest1
BOOST_AUTO_TEST_CASE( SignBitDoubleTest1 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = double;
    Generators::RandomGenerator<FloatT, 20000> generator;
    NumericTest test( "SignBitDoubleTest1" );
    auto success = test.Run( generator, []( auto x ) { return std::signbit( x ); }, []( auto x ) { return SignBit( x ) != 0; },
        {
            std::numeric_limits<FloatT>::quiet_NaN( ),
            -std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::lowest( ),
            std::numeric_limits<FloatT>::min( ),
            -std::numeric_limits<FloatT>::min( ),
            std::numeric_limits<FloatT>::max( ),
            std::numeric_limits<FloatT>::epsilon( ),
            -std::numeric_limits<FloatT>::epsilon( ),
            std::numeric_limits<FloatT>::denorm_min( ),
            -std::numeric_limits<FloatT>::denorm_min( ),
            -0.0,0.0
        } );
    BOOST_CHECK( success );

}

// --run_test=MathTests/FRExpDoubleTest1
BOOST_AUTO_TEST_CASE( FRExpDoubleTest1 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = double;
    Generators::RandomGenerator<FloatT, 20000> generator;
    NumericTest test( "FRExpDoubleTest1" );
    auto success = test.Run( generator, 
        []( auto x ) 
        { 
            int exp = 0; 
            auto fraction = std::frexp( x, &exp ); 
            return std::make_pair( fraction, static_cast<double>( exp ) );
        }, 
        []( auto x ) 
        { 
            int exp = 0; 
            auto fraction = FRExp( x, exp );
            return std::make_pair( fraction, static_cast< double >( exp ) );
        },
        {
            std::numeric_limits<FloatT>::quiet_NaN( ),
            -std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::lowest( ),
            std::numeric_limits<FloatT>::min( ),
            -std::numeric_limits<FloatT>::min( ),
            std::numeric_limits<FloatT>::max( ),
            std::numeric_limits<FloatT>::epsilon( ),
            -std::numeric_limits<FloatT>::epsilon( ),
            std::numeric_limits<FloatT>::denorm_min( ),
            -std::numeric_limits<FloatT>::denorm_min( ),
            -0.0,0.0
        } );
    BOOST_CHECK( success );

}

// --run_test=MathTests/ModFDoubleTest1
BOOST_AUTO_TEST_CASE( ModFDoubleTest1 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = double;
    Generators::RandomGenerator<FloatT, 20000> generator;
    NumericTest test( "ModFDoubleTest1" );
    auto success = test.Run( generator,
        []( auto x )
        {
            using FloatT = std::remove_cvref_t<decltype( x )>;
            FloatT exp = 0;
            auto fraction = std::modf( x, &exp );
            return std::make_pair( fraction, exp );
        },
        []( auto x )
        {
            using FloatT = std::remove_cvref_t<decltype( x )>;
            FloatT exp = 0;
            auto fraction = ModF( x, exp );
            return std::make_pair( fraction, exp );
        },
        {
            std::numeric_limits<FloatT>::quiet_NaN( ),
            -std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::lowest( ),
            std::numeric_limits<FloatT>::min( ),
            -std::numeric_limits<FloatT>::min( ),
            std::numeric_limits<FloatT>::max( ),
            std::numeric_limits<FloatT>::epsilon( ),
            -std::numeric_limits<FloatT>::epsilon( ),
            std::numeric_limits<FloatT>::denorm_min( ),
            -std::numeric_limits<FloatT>::denorm_min( ),
            -0.0,0.0
        } );
    BOOST_CHECK( success );
}

// --run_test=MathTests/InternalMinImplFloatTest1
BOOST_AUTO_TEST_CASE( InternalMinImplFloatTest1 )
{
    auto minValue = Math::Min( 5.f, 4.f, 3.f, 4.f, 4.f );
    bool equal = minValue == 3.f;
    BOOST_CHECK( equal );
}

// --run_test=MathTests/InternalMaxImplFloatTest1
BOOST_AUTO_TEST_CASE( InternalMaxImplFloatTest1 )
{
    auto minValue = Math::Max( 5.f, 4.f, 3.f, 4.f, 4.f );
    bool equal = minValue == 5.f;
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


// --run_test=MathTests/SinImplFloatTest1
BOOST_AUTO_TEST_CASE( SinImplFloatTest1 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = float;
    Generators::RangeGenerator<FloatT> generator( static_cast<float>( -2.0 * M_PI ), static_cast < float >(2.0 * M_PI) );
    
    //Generators::RangeGenerator<FloatT> generator( -42781604.0, 42781604.0 );
    NumericTest test( "Math::Internal::SinImplFloatTest1" );
    auto success = test.Run( generator, 
        []( auto x ) 
        { 
            return std::sin( x ); 
        }, 
        []( auto x ) 
        { 
            return Math::Internal::SinImpl( x ); 
        },
        {
            std::numeric_limits<FloatT>::quiet_NaN( ),
            -std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::infinity( ),
            -1e5,
            -1e10,
            std::numeric_limits<FloatT>::min( ),
            -std::numeric_limits<FloatT>::min( ),
            1e5,
            1e10,
            std::numeric_limits<FloatT>::epsilon( ),
            -std::numeric_limits<FloatT>::epsilon( ),
            std::numeric_limits<FloatT>::denorm_min( ),
            -std::numeric_limits<FloatT>::denorm_min( ),
            -0.0,0.0,
            std::bit_cast<float>(0x3f06'0a92U), // x = pi/6
            std::bit_cast<float>(0x3f3a'dc51U), // x = 0x1.75b8a2p-1f
            std::bit_cast<float>(0x3f49'0fdbU), // x = pi/4
            std::bit_cast<float>(0x3f86'0a92U), // x = pi/3
            std::bit_cast<float>(0x3fa7'832aU), // x = 0x1.4f0654p+0f
            std::bit_cast<float>(0x3fc9'0fdbU), // x = pi/2
            std::bit_cast<float>(0x4017'1973U), // x = 0x1.2e32e6p+1f
            std::bit_cast<float>(0x4049'0fdbU), // x = pi
            std::bit_cast<float>(0x4096'cbe4U), // x = 0x1.2d97c8p+2f
            std::bit_cast<float>(0x40c9'0fdbU), // x = 2*pi
            std::bit_cast<float>(0x433b'7490U), // x = 0x1.76e92p+7f
            std::bit_cast<float>(0x437c'e5f1U), // x = 0x1.f9cbe2p+7f
            std::bit_cast<float>(0x4619'9998U), // x = 0x1.33333p+13f
            std::bit_cast<float>(0x474d'246fU), // x = 0x1.9a48dep+15f
            std::bit_cast<float>(0x4afd'ece4U), // x = 0x1.fbd9c8p+22f
            std::bit_cast<float>(0x4c23'32e9U), // x = 0x1.4665d2p+25f
            //std::bit_cast<float>(0x50a3'e87fU), // x = 0x1.47d0fep+34f
            //std::bit_cast<float>(0x5239'47f6U), // x = 0x1.728fecp+37f
            //std::bit_cast<float>(0x53b1'46a6U), // x = 0x1.628d4cp+40f
            //std::bit_cast<float>(0x55ca'fb2aU), // x = 0x1.95f654p+44f
            //std::bit_cast<float>(0x588e'f060U), // x = 0x1.1de0cp+50f
            //std::bit_cast<float>(0x5c07'bcd0U), // x = 0x1.0f79ap+57f
            //std::bit_cast<float>(0x5ebc'fddeU), // x = 0x1.79fbbcp+62f
            //std::bit_cast<float>(0x5fa6'eba7U), // x = 0x1.4dd74ep+64f
            //std::bit_cast<float>(0x61a4'0b40U), // x = 0x1.48168p+68f
            //std::bit_cast<float>(0x6386'134eU), // x = 0x1.0c269cp+72f
            //std::bit_cast<float>(0x6589'8498U), // x = 0x1.13093p+76f
            //std::bit_cast<float>(0x6600'0001U), // x = 0x1.000002p+77f
            //std::bit_cast<float>(0x664e'46e4U), // x = 0x1.9c8dc8p+77f
            //std::bit_cast<float>(0x66b0'14aaU), // x = 0x1.602954p+78f
            //std::bit_cast<float>(0x67a9'242bU), // x = 0x1.524856p+80f
            //std::bit_cast<float>(0x6a19'76f1U), // x = 0x1.32ede2p+85f
            //std::bit_cast<float>(0x6c55'da58U), // x = 0x1.abb4bp+89f
            //std::bit_cast<float>(0x6f79'be45U), // x = 0x1.f37c8ap+95f
            //std::bit_cast<float>(0x7276'69d4U), // x = 0x1.ecd3a8p+101f
            //std::bit_cast<float>(0x7758'4625U), // x = 0x1.b08c4ap+111f
        } );
    BOOST_CHECK( success );
}


// --run_test=MathTests/SIMDTraitsSinDoubleTest1
BOOST_AUTO_TEST_CASE( SIMDTraitsSinDoubleTest1 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = double;
    Generators::RangeGenerator<FloatT> generator( -M_PI * 2, M_PI * 2 );
    NumericTest test( "Math::Internal::SinImplDoubleTest1" );
    auto success = test.Run( generator,
        []( auto x )
        {
            return std::sin( x );
        },
        []( auto x )
        {
            using Traits = SIMD::Traits<double, 2>;
            auto rmmx = Traits::Fill( x );
            return Traits::First( Traits::Sin( rmmx ) );
        },
        {
            std::numeric_limits<FloatT>::quiet_NaN( ),
            -std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::infinity( ),
            -1e5,
            -1e10,
            -1e50,
            -1e100,
            std::numeric_limits<FloatT>::min( ),
            -std::numeric_limits<FloatT>::min( ),
            1e5,
            1e10,
            1e50,
            1e100,
            std::numeric_limits<FloatT>::epsilon( ),
            -std::numeric_limits<FloatT>::epsilon( ),
            std::numeric_limits<FloatT>::denorm_min( ),
            -std::numeric_limits<FloatT>::denorm_min( ),
            -0.0,0.0,
            0x1.940c877fb7dacp-7,    0x1.fffffffffdb6p24,    0x1.fd4da4ef37075p29,
              0x1.b951f1572eba5p+31,   0x1.55202aefde314p+31,  /*0x1.85fc0f04c0128p101,
              0x1.7776c2343ba4ep101,   0x1.678309fa50d58p110,  0x1.fffffffffef4ep199,*/
              -0x1.ab514bfc61c76p+7,   -0x1.f7898d5a756ddp+2,  -0x1.f42fb19b5b9b2p-6,
              0x1.5f09cad750ab1p+3,    -0x1.14823229799c2p+7,  -0x1.0285070f9f1bcp-5,
              0x1.23f40dccdef72p+0,    0x1.43cf16358c9d7p+0,   0x1.addf3b9722265p+0,
              0x1.48ff1782ca91dp+8,    0x1.a211877de55dbp+4,   0x1.dcbfda0c7559ep+8,
              0x1.1ffb509f3db15p+5,    0x1.2345d1e090529p+5,   0x1.ae945054939c2p+10,
              0x1.2e566149bf5fdp+9,    0x1.be886d9c2324dp+6,   -0x1.119471e9216cdp+10,
              -0x1.aaf85537ea4c7p+3,   0x1.cb996c60f437ep+9,   0x1.c96e28eb679f8p+5,
              -0x1.a5eece87e8606p+4,   0x1.e31b55306f22cp+2,   0x1.ae78d360afa15p+0,
              0x1.1685973506319p+3,    0x1.4f2b874135d27p+4,   0x1.ae945054939c2p+10,
              /*0x1.3eec5912ea7cdp+331,*/  0x1.dcbfda0c7559ep+8,   0x1.a65d441ea6dcep+4,
              0x1.e639103a05997p+2,    0x1.13114266f9764p+4,   /*-0x1.3eec5912ea7cdp+331,
              0x1.08087e9aad90bp+887,  0x1.2b5fe88a9d8d5p+903, -0x1.a880417b7b119p+1023,
              -0x1.6deb37da81129p+205, 0x1.08087e9aad90bp+887, 0x1.f6d7518808571p+1023,
              -0x1.8bb5847d49973p+845, 0x1.f08b14e1c4d0fp+890, 0x1.6ac5b262ca1ffp+849,*/
              0x1.e0000000001c2p-20
        } );
    BOOST_CHECK( success );

        
}

// --run_test=MathTests/SinFloatTest1
BOOST_AUTO_TEST_CASE( SinFloatTest1 )
{
    TrigonometricRangeTest<float>( "SinFloatTest2", []( float value ) { return std::sin( value ); }, []( float value ) { return Math::Internal::SinImpl( value ); } );
}

// --run_test=MathTests/SinDoubleTest2
BOOST_AUTO_TEST_CASE( SinDoubleTest2 )
{
    TrigonometricRangeTest<double>( "SinDoubleTest2", []( double value ) { return std::sin( value ); }, []( double value ) { return Math::Internal::SinImpl( value ); } );
}

// --run_test=MathTests/CosFloatTest2
BOOST_AUTO_TEST_CASE( CosFloatTest2 )
{
    TrigonometricRangeTest<float>( "CosFloatTest2", []( float value ) { return std::cos( value ); }, []( float value ) { return Math::Internal::CosImpl( value ); } );
}

// --run_test=MathTests/CosDoubleTest2
BOOST_AUTO_TEST_CASE( CosDoubleTest2 )
{
    TrigonometricRangeTest<double>( "CosDoubleTest2", []( double value ) { return std::cos( value ); }, []( double value ) { return Math::Internal::CosImpl( value ); } );
}

// --run_test=MathTests/TanFloatTest2
BOOST_AUTO_TEST_CASE( TanFloatTest2 )
{
    TrigonometricRangeTest<float>( "TanFloatTest2", []( float value ) { return std::tan( value ); }, []( float value ) { return Math::Internal::TanImpl( value ); } );
}


// --run_test=MathTests/TanDoubleTest2
BOOST_AUTO_TEST_CASE( TanDoubleTest2 )
{
    TrigonometricRangeTest<double>( "TanFloatTest2", []( double value ) { return std::tan( value ); }, []( double value ) { return Math::Internal::TanImpl( value ); } );
}



// --run_test=MathTests/ASinFloatTest2
BOOST_AUTO_TEST_CASE( ASinFloatTest2 )
{
    ReverseTrigonometricRangeTest<float>( "ASinFloatTest2", []( float value ) { return std::asin( value ); }, []( float value ) { return Math::Internal::ASinImpl( value ); } );
}

// --run_test=MathTests/ASinDoubleTest2
BOOST_AUTO_TEST_CASE( ASinDoubleTest2 )
{
    ReverseTrigonometricRangeTest<double>( "ASinDoubleTest2", []( double value ) { return std::asin( value ); }, []( double value ) { return Math::Internal::ASinImpl( value ); } );
}


// --run_test=MathTests/ACosFloatTest2
BOOST_AUTO_TEST_CASE( ACosFloatTest2 )
{
    ReverseTrigonometricRangeTest<float>( "ACosFloatTest2", []( float value ) { return std::acos( value ); }, []( float value ) { return Math::Internal::ACosImpl( value ); } );
}



// --run_test=MathTests/ACosDoubleTest2
BOOST_AUTO_TEST_CASE( ACosDoubleTest2 )
{
    ReverseTrigonometricRangeTest<double>( "ACosDoubleTest2", []( double value ) { return std::acos( value ); }, []( double value ) { return Math::Internal::ACosImpl( value ); } );
}


// --run_test=MathTests/ATanFloatTest2
BOOST_AUTO_TEST_CASE( ATanFloatTest2 )
{
    RandomValueTest<float, 10000>( "ATanFloatTest2", []( float value ) { return std::atan( value ); }, []( float value ) { return Math::Internal::ATanImpl( value ); } );
}

// --run_test=MathTests/ATanDoubleTest2
BOOST_AUTO_TEST_CASE( ATanDoubleTest2 )
{
    RandomValueTest<double, 10000>( "ATanDoubleTest2", []( double value ) { return std::atan( value ); }, []( double value ) { return Math::Internal::ATanImpl( value ); } );
}


// --run_test=MathTests/ATan2FloatTest2
BOOST_AUTO_TEST_CASE( ATan2FloatTest2 )
{
    RandomValueTest2<float, 10000>( "ATan2FloatTest2", []( float x, float y ) { return std::atan2( x, y ); }, []( float x, float y ) { return Math::Internal::ATan2Impl( x, y ); } );
}

// --run_test=MathTests/ATan2DoubleTest2
BOOST_AUTO_TEST_CASE( ATan2DoubleTest2 )
{
    RandomValueTest2<double, 10000>( "ATan2DoubleTest2", []( double x, double y ) { return std::atan2( x, y ); }, []( double x, double y ) { return Math::Internal::ATan2Impl( x, y ); } );
}

// --run_test=MathTests/FModFloatTest2
BOOST_AUTO_TEST_CASE( FModFloatTest2 )
{
    RandomValueTest2<float, 10000>( "FModFloatTest2", []( float x, float y ) { return std::fmod( x, y ); }, []( float x, float y ) { return Math::FMod( x, y ); } );
}


// --run_test=MathTests/FModDoubleTest2
BOOST_AUTO_TEST_CASE( FModDoubleTest2 )
{
    RandomValueTest2<double, 10000>( "FModDoubleTest2", []( double x, double y ) { return std::fmod( x, y ); }, []( double x, double y ) { return Math::FMod( x, y ); } );
}

// --run_test=MathTests/ExpFloatTest2
BOOST_AUTO_TEST_CASE( ExpFloatTest2 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = float;
    //Generators::RandomGenerator<FloatT, 200000> generator( -9, 10 );
    Generators::RangeGenerator<FloatT> generator( -89, 89 );
    NumericTest test( "ExpFloatTest2" );
    auto success = test.Run( generator,
        []( auto x )
        {
            return std::exp( x );
        },
        []( auto x )
        {
            return Exp( x );
        },
        {
            std::numeric_limits<FloatT>::quiet_NaN( ),
            -std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::lowest( ),
            std::numeric_limits<FloatT>::min( ),
            -std::numeric_limits<FloatT>::min( ),
            std::numeric_limits<FloatT>::max( ),
            std::numeric_limits<FloatT>::epsilon( ),
            -std::numeric_limits<FloatT>::epsilon( ),
            std::numeric_limits<FloatT>::denorm_min( ),
            -std::numeric_limits<FloatT>::denorm_min( ),
            -0.0,0.0
        } );
    BOOST_CHECK( success );
    //RandomValueTest<float, 10000>( "ExpFloatTest2", []( float value ) { return std::exp( value ); }, []( float value ) { return Math::Exp( value ); }, -9, 10 );
}


/*
// --run_test=MathTests/PbrtFastExpFloatTest1
BOOST_AUTO_TEST_CASE( PbrtFastExpFloatTest1 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = float;
    //Generators::RandomGenerator<FloatT, 200000> generator( -9, 10 );
    Generators::RangeGenerator<FloatT> generator( 0, 1 );
    NumericTest test( "PbrtFastExpFloatTest1" );
    auto success = test.Run( generator,
        []( auto x )
        {
            return std::exp( x );
        },
        []( auto x )
        {
            return pbrt::FastExp( x );
        },
        {
            std::numeric_limits<FloatT>::quiet_NaN( ),
            -std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::lowest( ),
            std::numeric_limits<FloatT>::min( ),
            -std::numeric_limits<FloatT>::min( ),
            std::numeric_limits<FloatT>::max( ),
            std::numeric_limits<FloatT>::epsilon( ),
            -std::numeric_limits<FloatT>::epsilon( ),
            std::numeric_limits<FloatT>::denorm_min( ),
            -std::numeric_limits<FloatT>::denorm_min( ),
            -0.0,0.0
        } );
    BOOST_CHECK( success );
}
*/

// --run_test=MathTests/ExpDoubleTest2
BOOST_AUTO_TEST_CASE( ExpDoubleTest2 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = double;
    //auto generator = std::make_unique<Generators::RandomGenerator<FloatT, 200000>>( -9, 10 );
    Generators::RangeGenerator<FloatT> generator( -744, 710 );
    NumericTest test( "ExpDoubleTest2" );
    auto success = test.Run( generator,
        []( auto x )
        {
            return std::exp( x );
        },
        []( auto x )
        {
            return Exp( x );
        },
        {
            std::numeric_limits<FloatT>::quiet_NaN( ),
            -std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::infinity( ),
            std::numeric_limits<FloatT>::lowest( ),
            std::numeric_limits<FloatT>::min( ),
            -std::numeric_limits<FloatT>::min( ),
            std::numeric_limits<FloatT>::max( ),
            std::numeric_limits<FloatT>::epsilon( ),
            -std::numeric_limits<FloatT>::epsilon( ),
            std::numeric_limits<FloatT>::denorm_min( ),
            -std::numeric_limits<FloatT>::denorm_min( ),
            -0.0,0.0
        } );
    BOOST_CHECK( success );
    //RandomValueTest<double, 10000>( "ExpDoubleTest2", []( double value ) { return std::exp( value ); }, []( double value ) { return Math::Exp( value ); }, -9, 10 );
}

// --run_test=MathTests/LogFloatTest2
BOOST_AUTO_TEST_CASE( LogFloatTest2 )
{
    RandomValueTest<float, 10000>( "LogFloatTest2", []( float value ) { return std::log( value ); }, []( float value ) { return Math::Log( value ); }, 0, 100000 );
}

// --run_test=MathTests/LogDoubleTest2
BOOST_AUTO_TEST_CASE( LogDoubleTest2 )
{
    RandomValueTest<double, 10000>( "LogDoubleTest2", []( double value ) { return std::log( value ); }, []( double value ) { return Math::Log( value ); }, 0, 100000 );
}

// --run_test=MathTests/Log2FloatTest2
BOOST_AUTO_TEST_CASE( Log2FloatTest2 )
{
    RandomValueTest<float, 10000>( "Log2FloatTest2", []( float value ) { return std::log2( value ); }, []( float value ) { return Math::Log2( value ); }, 0, 100000 );
}

// --run_test=MathTests/Log2DoubleTest2
BOOST_AUTO_TEST_CASE( Log2DoubleTest2 )
{
    RandomValueTest<double, 10000>( "Log2DoubleTest2", []( double value ) { return std::log2( value ); }, []( double value ) { return Math::Log2( value ); }, 0, 100000 );
}

// --run_test=MathTests/Log10FloatTest2
BOOST_AUTO_TEST_CASE( Log10FloatTest2 )
{
    RandomValueTest<float, 10000>( "Log10FloatTest2", []( float value ) { return std::log10( value ); }, []( float value ) { return Math::Log10( value ); }, 0, 100000 );
}

// --run_test=MathTests/Log10DoubleTest2
BOOST_AUTO_TEST_CASE( Log10DoubleTest2 )
{
    RandomValueTest<double, 10000>( "Log10DoubleTest2", []( double value ) { return std::log10( value ); }, []( double value ) { return Math::Log10( value ); }, 0, 100000 );
}


// --run_test=MathTests/Log2DoubleTest3
BOOST_AUTO_TEST_CASE( Log2DoubleTest3 )
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

// --run_test=MathTests/NextUpFloatTest1
BOOST_AUTO_TEST_CASE( NextUpFloatTest1 )
{
    constexpr float val1 = 2.0f;
    constexpr float val2 = 1.0f;

    constexpr float result1 = NextUp( val2 );
    static_assert( result1 > val2 );

    float result2 = std::nextafter( val2, val1 );

    float result3 = pbrt::NextFloatUp( val2 );

    bool equal = IsSameValue( result2, result1 );
    BOOST_CHECK( equal );

    equal = IsSameValue( result3, result1 );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/NextUpFloatTest2
BOOST_AUTO_TEST_CASE( NextUpFloatTest2 )
{
    constexpr float val1 = -2.0f;
    constexpr float val2 = -1.0f;

    constexpr float result1 = NextUp( val2 );
    static_assert( result1 > val2 );

    float result2 = std::nextafter( val2, 0.f );

    float result3 = pbrt::NextFloatUp( val2 );

    bool equal = IsSameValue( result2, result1 );
    BOOST_CHECK( equal );

    equal = IsSameValue( result3, result1 );
    BOOST_CHECK( equal );

}

// --run_test=MathTests/NextDownFloatTest1
BOOST_AUTO_TEST_CASE( NextDownFloatTest1 )
{
    constexpr float val1 = 2.0f;
    constexpr float val2 = 1.0f;

    constexpr float result1 = NextDown( val1 );
    static_assert( result1 < val1 );

    float result2 = std::nextafter( val1, val2 );

    float result3 = pbrt::NextFloatDown( val1 );

    bool equal = IsSameValue( result2, result1 );
    BOOST_CHECK( equal );

    equal = IsSameValue( result3, result1 );
    BOOST_CHECK( equal );
}

// --run_test=MathTests/NextDownFloatTest2
BOOST_AUTO_TEST_CASE( NextDownFloatTest2 )
{
    constexpr float val1 = -2.0f;
    constexpr float val2 = -1.0f;

    constexpr float result1 = NextDown( val2 );
    static_assert( result1 < val2 );

    float result2 = std::nextafter( val2, val1 );

    float result3 = pbrt::NextFloatDown( val2 );

    bool equal = IsSameValue( result2, result1 );
    BOOST_CHECK( equal );

    equal = IsSameValue( result3, result1 );
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
