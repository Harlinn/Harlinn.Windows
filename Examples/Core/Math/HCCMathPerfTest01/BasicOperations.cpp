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


#include "HCCMathPerfTest01.h"

#include <Harlinn/Math/Math.h>
#include <HCCDateTime.h>
#include <HCCString.h>

using namespace Harlinn;
using namespace Harlinn::Common;
using namespace Harlinn::Common::Core;
using namespace Harlinn::Math;

namespace
{
    template<typename FloatT, typename Func1 >
    void RunTest1( Int64 outerIterationCount,
        const char* testName, Func1&& func1,
        FloatT baseValue = static_cast<FloatT>( M_PI ), FloatT increment = static_cast<FloatT>( 0.000001 ) )
    {
        Int64 innerIterationCount = 1'000'000'000;

        for ( int j = 0; j < outerIterationCount; j++ )
        {
            double argumentValue = baseValue;
            double accumulated{};
            Stopwatch stopwatch;
            stopwatch.Start( );


            for ( Int64 i = 0; i < innerIterationCount; i++ )
            {
                accumulated += func1( argumentValue );
                argumentValue += increment;
            }

            stopwatch.Stop( );
            auto duration = stopwatch.TotalSeconds( );
            PrintLn( "{}: Duration={}, Accumulated={}",
                testName, duration, accumulated );
        }
    }


    template<typename FloatT>
    void PrintAccumulated( FloatT accumulated1, FloatT accumulated2 )
    {
        using FloatingPointType = Math::Internal::FloatingPoint<FloatT>;
        using UIntType = typename FloatingPointType::UIntType;
        if ( std::bit_cast<UIntType>( accumulated1 ) != std::bit_cast<UIntType>( accumulated2 ) )
        {
            if ( AreNearlyEqual( accumulated1, accumulated2 ) )
            {
                PrintLn( "\tAccumulated 1(={}) is nearly equal to Accumulated 2(={})\n", accumulated1, accumulated2 );
            }
            else
            {
                PrintLn( "\tAccumulated 1(={}) differs significantly from Accumulated 2(={})\n", accumulated1, accumulated2 );
            }
        }
        else
        {
            PrintLn( "\tAccumulated 1 is identical to Accumulated 2\n" );
        }
    }

    template<typename FloatT>
    void PrintAccumulated( FloatT accumulated1a, FloatT accumulated1b, FloatT accumulated2a, FloatT accumulated2b )
    {
        using FloatingPointType = Math::Internal::FloatingPoint<FloatT>;
        using UIntType = typename FloatingPointType::UIntType;
        if ( std::bit_cast<UIntType>( accumulated1a ) != std::bit_cast<UIntType>( accumulated2a ) || std::bit_cast<UIntType>( accumulated1b ) != std::bit_cast<UIntType>( accumulated2b ) )
        {
            if ( AreNearlyEqual( accumulated1a, accumulated2a ) )
            {
                PrintLn( "\tAccumulated 1a(={}) is nearly equal to Accumulated 2a(={})", accumulated1a, accumulated2a );
            }
            else
            {
                PrintLn( "\tAccumulated 1a(={}) differs significantly from Accumulated 2a(={})", accumulated1a, accumulated2a );
            }
            if ( AreNearlyEqual( accumulated1b, accumulated2b ) )
            {
                PrintLn( "\tAccumulated 1b(={}) is nearly equal to Accumulated 2b(={})\n", accumulated1b, accumulated2b );
            }
            else
            {
                PrintLn( "\tAccumulated 1b(={}) differs significantly from Accumulated 2b(={})\n", accumulated1b, accumulated2b );
            }
        }
        else
        {
            PrintLn( "\tAccumulated 1(a and b) is identical to Accumulated 2(a and b)\n" );
        }
    }


    void PrintPerformance( double mathDuration, double stdDuration )
    {
        auto performanceImprovement = (( stdDuration - mathDuration ) / mathDuration ) * 100.0;
        if ( performanceImprovement > 1.0 )
        {
            PrintLn( "\tMath improved performance by {:.2f} %\n", performanceImprovement );
        }
        else if ( performanceImprovement < -1.0 )
        {
            PrintLn( "\tMath degraded performance by {:.2f} %\n", performanceImprovement );
        }
        else
        {
            PrintLn( "\tMath performs like the standard implementation.\n" );
        }
    }

    template<typename FloatT, typename Func1, typename Func2 >
    void RunTest1( Int64 outerIterationCount, const char* testName, Func1&& func1, Func2&& func2, FloatT base = static_cast<FloatT>( M_PI ), FloatT increment = static_cast<FloatT>( 0.000001 ) )
    {
        constexpr Int64 innerIterationCount = 1'000'000'000;
        PrintLn( "{}: Outer {}, Inner {}", testName, outerIterationCount, innerIterationCount );

        for ( int j = 0; j < outerIterationCount; j++ )
        {
            FloatT argumentValue = base;
            FloatT accumulated1 = 0.0;
            Stopwatch stopwatch;
            stopwatch.Start( );


            for ( Int64 i = 0; i < innerIterationCount; i++ )
            {
                accumulated1 += func1( argumentValue );
                argumentValue += increment;
            }

            stopwatch.Stop( );
            auto duration1 = stopwatch.TotalSeconds( );
            PrintLn( "\tMath: Duration={}, Accumulated 1={}", duration1, accumulated1 );

            argumentValue = base;
            FloatT accumulated2 = 0.0;
            stopwatch.Restart( );

            for ( Int64 i = 0; i < innerIterationCount; i++ )
            {
                accumulated2 += func2( argumentValue );
                argumentValue += increment;
            }

            stopwatch.Stop( );
            auto duration2 = stopwatch.TotalSeconds( );
            PrintLn( "\tstd:  Duration={}, Accumulated 2={}", duration2, accumulated2 );
            PrintPerformance( duration1, duration2 );
            PrintAccumulated( accumulated1, accumulated2 );
        }
    }





    template<typename FloatT, typename Func1, typename Func2 >
    void RunCompareTest( Int64 outerIterationCount, const char* testName, Func1&& func1, Func2&& func2, FloatT base = static_cast<FloatT>( M_PI ), FloatT increment = static_cast<FloatT>( 0.000001 ) )
    {
        using FloatingPointType = Math::Internal::FloatingPoint<FloatT>;
        using UIntType = typename FloatingPointType::UIntType;
        Int64 innerIterationCount = 1'000'000'000;
        PrintLn( "{}: Outer {}, Inner {}", testName, outerIterationCount, innerIterationCount );

        for ( int j = 0; j < outerIterationCount; j++ )
        {
            FloatT argumentValue = base;
            FloatT accumulated1 = 0.0;
            FloatT accumulated2 = 0.0;

            for ( Int64 i = 0; i < innerIterationCount; i++ )
            {
                auto result1 = func1( argumentValue );
                auto result2 = func2( argumentValue );
                //if ( std::bit_cast<UIntType>( result1 ) != std::bit_cast<UIntType>( result2 ) )
                if ( AreNearlyEqual( result1, result2, 0.0000001 ) == false )
                {
                    PrintLn( "\ti:{} Argument={} Result 1={}(0x{:X}), Result 2={}(0x{:X})\n", i, argumentValue, result1, std::bit_cast<UIntType>( result1 ), result2, std::bit_cast<UIntType>( result2 ) );
                }
                accumulated1 += result1;
                accumulated2 += result2;

                argumentValue += increment;
            }

            PrintLn( "\tAccumulated 1={}, Accumulated 2={}\n", accumulated1, accumulated2 );
        }
    }




    template<typename FloatT, typename Func1, typename Func2 >
    void RunTrigTest( Int64 outerIterationCount, const char* testName, Func1&& func1, Func2&& func2 )
    {
        RunTest1<FloatT, Func1, Func2>( outerIterationCount, testName, std::move( func1 ), std::move( func2 ), static_cast<FloatT>( M_PI / 100.0 ) );
    }

    template<typename FloatT, typename Func1, typename Func2 >
    void RunATrigTest( Int64 outerIterationCount, const char* testName, Func1&& func1, Func2&& func2 )
    {
        RunTest1<FloatT, Func1, Func2 >( outerIterationCount, testName, std::move( func1 ), std::move( func2 ), static_cast<FloatT>( 0.9 / 1000000000.0 ), static_cast<FloatT>( 1.0 / 1000000000.0 ) );
    }




    template<typename FloatT, typename Result2T, typename Func1, typename Func2 >
    void RunTest2( Int64 outerIterationCount, const char* testName, Func1&& func1, Func2&& func2, FloatT base = static_cast<FloatT>( M_PI ), FloatT increment = static_cast<FloatT>( 0.000001 ) )
    {
        Int64 innerIterationCount = 1'000'000'000;
        PrintLn( "{}: Outer {}, Inner {}", testName, outerIterationCount, innerIterationCount );

        for ( int j = 0; j < outerIterationCount; j++ )
        {
            FloatT argumentValue = base;
            Result2T result2{};
            FloatT accumulated1a = 0.0;
            FloatT accumulated1b = 0.0;
            Stopwatch stopwatch;
            stopwatch.Start( );

            for ( Int64 i = 0; i < innerIterationCount; i++ )
            {
                accumulated1a += func1( argumentValue, result2 );
                accumulated1b += result2;
                argumentValue += increment;
            }

            stopwatch.Stop( );
            auto duration1 = stopwatch.TotalSeconds( );
            PrintLn( "\tMath: Duration={}, Accumulated 1={}, Accumulated 2={}", duration1, accumulated1a, accumulated1b );

            argumentValue = base;
            FloatT accumulated2a = 0.0;
            FloatT accumulated2b = 0.0;
            stopwatch.Restart( );

            for ( Int64 i = 0; i < innerIterationCount; i++ )
            {
                accumulated2a += func2( argumentValue, result2 );
                accumulated2b += result2;
                argumentValue += increment;
            }

            stopwatch.Stop( );
            auto duration2 = stopwatch.TotalSeconds( );
            PrintLn( "\tstd:  Duration={}, Accumulated 1={}, Accumulated 2={}", duration2, accumulated2a, accumulated2b );
            PrintPerformance( duration1, duration2 );
            PrintAccumulated( accumulated1a, accumulated1b, accumulated2a, accumulated2b );
        }
    }
}


void IsNaNDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return IsNaN( arg ); }, []( auto arg ) { return std::isnan( arg ); } );
}

void IsNaNFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return IsNaN( arg ); }, []( auto arg ) { return std::isnan( arg ); } );
}


void OverheadDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return arg; }, []( auto arg ) { return arg; } );
}
void OverheadFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return arg; }, []( auto arg ) { return arg; } );
}

void IsInfDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return IsInf( arg ); }, []( auto arg ) { return std::isinf( arg ); } );
}
void IsInfFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return IsInf( arg ); }, []( auto arg ) { return std::isinf( arg ); } );
}


void AbsDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Abs( arg ); }, []( auto arg ) { return std::abs( arg ); } );
}
void AbsFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Abs( arg ); }, []( auto arg ) { return std::abs( arg ); } );
}

void SignBitDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return SignBit( arg ); }, []( auto arg ) { return std::signbit( arg ); } );
}
void SignBitFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return SignBit( arg ); }, []( auto arg ) { return std::signbit( arg ); } );
}

void FRExpDoubleTest( Int64 outerIterationCount )
{
    RunTest2<double, int>( outerIterationCount, __FUNCTION__, []( auto arg, auto& result ) { return FRExp( arg, result ); }, []( auto arg, auto& result ) { return std::frexp( arg, &result ); } );
}
void FRExpFloatTest( Int64 outerIterationCount )
{
    RunTest2<float, int>( outerIterationCount, __FUNCTION__, []( auto arg, auto& result ) { return FRExp( arg, result ); }, []( auto arg, auto& result ) { return std::frexp( arg, &result ); } );
}


void ModFDoubleTest( Int64 outerIterationCount )
{
    RunTest2<double, double>( outerIterationCount, __FUNCTION__, []( auto arg, auto& result ) { return ModF( arg, result ); }, []( auto arg, auto& result ) { return std::modf( arg, &result ); } );
}
void ModFFloatTest( Int64 outerIterationCount )
{
    RunTest2<float, float>( outerIterationCount, __FUNCTION__, []( auto arg, auto& result ) { return ModF( arg, result ); }, []( auto arg, auto& result ) { return std::modf( arg, &result ); } );
}


void MinDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Min( arg, arg ); }, []( auto arg ) { return std::min( arg, arg ); } );
}

void MinFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Min( arg, arg ); }, []( auto arg ) { return std::min( arg, arg ); } );
}

void MaxDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Max( arg, arg ); }, []( auto arg ) { return std::max( arg, arg ); } );
}
void MaxFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Max( arg, arg ); }, []( auto arg ) { return std::max( arg, arg ); } );
}


void FloorDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Floor( arg ); }, []( auto arg ) { return std::floor( arg ); } );
}
void FloorFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Floor( arg ); }, []( auto arg ) { return std::floor( arg ); } );
}

void CeilDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Ceil( arg ); }, []( auto arg ) { return std::ceil( arg ); } );
}
void CeilFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Ceil( arg ); }, []( auto arg ) { return std::ceil( arg ); } );
}


void TruncDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Trunc( arg ); }, []( auto arg ) { return std::trunc( arg ); } );
}
void TruncFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Trunc( arg ); }, []( auto arg ) { return std::trunc( arg ); } );
}


void RoundDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Round( arg ); }, []( auto arg ) { return std::round( arg ); } );
}
void RoundFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Round( arg ); }, []( auto arg ) { return std::round( arg ); } );
}


template<typename FloatT>
void ClampTest( Int64 outerIterationCount, const char* testName )
{
    constexpr Int64 InnerIterationCount = 1'000'000'000;
    PrintLn( "{}: Outer {}, Inner {}\n", testName, outerIterationCount, InnerIterationCount );

    constexpr FloatT increment = static_cast<FloatT>( 0.000001 );
    constexpr FloatT baseMin = static_cast<FloatT>( M_PI_2 );
    constexpr FloatT base = static_cast<FloatT>( M_PI );
    constexpr FloatT baseMax = static_cast<FloatT>( 2 * M_PI );

    for ( int j = 0; j < outerIterationCount; j++ )
    {
        FloatT accumulated1 = 0.0;
        Stopwatch stopwatch;
        stopwatch.Start( );

        FloatT valueMin = baseMin;
        FloatT value = base;
        FloatT valueMax = baseMax;

        for ( Int64 i = 0; i < InnerIterationCount; i++ )
        {
            accumulated1 += Clamp( value, valueMin, valueMax );
            valueMin += increment;
            value += increment;
            valueMax += increment;
        }

        stopwatch.Stop( );
        auto duration1 = stopwatch.TotalSeconds( );
        PrintLn( "\tMath: Duration={}, Accumulated={}", duration1, accumulated1 );

        FloatT accumulated2 = 0.0;
        valueMin = baseMin;
        value = base;
        valueMax = baseMax;

        stopwatch.Restart( );

        for ( Int64 i = 0; i < InnerIterationCount; i++ )
        {
            accumulated2 += std::clamp( value, valueMin, valueMax );
            valueMin += increment;
            value += increment;
            valueMax += increment;
        }

        stopwatch.Stop( );
        auto duration2 = stopwatch.TotalSeconds( );
        PrintLn( "\tstd:  Duration={}, Accumulated={}", duration2, accumulated2 );
        PrintPerformance( duration1, duration2 );
        PrintAccumulated( accumulated1, accumulated2 );
    }
}
void ClampDoubleTest( Int64 outerIterationCount )
{
    ClampTest<double>( outerIterationCount, __FUNCTION__ );
}
void ClampFloatTest( Int64 outerIterationCount )
{
    ClampTest<float>( outerIterationCount, __FUNCTION__ );
}


template<typename FloatT>
void LerpTest( Int64 outerIterationCount, const char* testName )
{
    constexpr Int64 InnerIterationCount = 1'000'000'000;
    PrintLn( "{}: Outer {}, Inner {}", testName, outerIterationCount, InnerIterationCount );
    constexpr FloatT increment = static_cast<FloatT>( 0.000001 );
    constexpr FloatT baseMin = static_cast<FloatT>( M_PI_2 );
    constexpr FloatT baseMax = static_cast<FloatT>( 3 * M_PI );


    for ( int j = 0; j < outerIterationCount; j++ )
    {
        FloatT accumulated1 = 0.0;
        Stopwatch stopwatch;
        stopwatch.Start( );

        FloatT valueMin = baseMin;
        FloatT valueMax = baseMax;

        for ( Int64 i = 0; i < InnerIterationCount; i++ )
        {
            accumulated1 += Lerp( valueMin, valueMax, static_cast<FloatT>( 0.5 ) );
            valueMin += increment;
            valueMax += increment;
        }

        stopwatch.Stop( );
        auto duration1 = stopwatch.TotalSeconds( );
        PrintLn( "\tMath: Duration={}, Accumulated={}", duration1, accumulated1 );

        FloatT accumulated2 = 0.0;
        valueMin = baseMin;
        valueMax = baseMax;
        stopwatch.Restart( );

        for ( Int64 i = 0; i < InnerIterationCount; i++ )
        {
            accumulated2 += std::lerp( valueMin, valueMax, static_cast<FloatT>( 0.5 ) );
            valueMin += increment;
            valueMax += increment;
        }

        stopwatch.Stop( );
        auto duration2 = stopwatch.TotalSeconds( );
        PrintLn( "\tstd:  Duration={}, Accumulated={}", duration2, accumulated2 );
        PrintPerformance( duration1, duration2 );
        PrintAccumulated( accumulated1, accumulated2 );
    }
}
void LerpDoubleTest( Int64 outerIterationCount )
{
    LerpTest<double>( outerIterationCount, __FUNCTION__ );
}
void LerpFloatTest( Int64 outerIterationCount )
{
    LerpTest<float>( outerIterationCount, __FUNCTION__ );
}


void CopySignDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return CopySign( arg, -1.0 ); }, []( auto arg ) { return std::copysign( arg, -1.0 ); } );
}
void CopySignFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return CopySign( arg, -1.0f ); }, []( auto arg ) { return std::copysign( arg, -1.0f ); } );
}

template<typename FloatT>
void ScaleBNTest( Int64 outerIterationCount, const char* testName )
{
    constexpr Int64 ValueIterationCount = 10'000'000;
    constexpr Int64 ExpIterationCount = 100;
    constexpr Int64 InnerIterationCount = ValueIterationCount * ExpIterationCount;
    PrintLn( "{}: Outer {}, Inner {}", testName, outerIterationCount, InnerIterationCount );

    constexpr FloatT base = static_cast<FloatT>( M_PI_2 );
    constexpr FloatT increment = static_cast<FloatT>( 0.000001 );

    for ( int j = 0; j < outerIterationCount; j++ )
    {
        FloatT accumulated1 = static_cast<FloatT>( 0.0 );
        Stopwatch stopwatch;
        stopwatch.Start( );

        FloatT value = base;
        for ( Int64 i = 0; i < ValueIterationCount; i++ )
        {
            for ( Int32 j = 0; j < ExpIterationCount; ++j )
            {
                accumulated1 += ScaleBN( value, j + 1 );
            }
            value += increment;
        }

        stopwatch.Stop( );
        auto duration1 = stopwatch.TotalSeconds( );
        PrintLn( "\tMath: Duration={}, Accumulated={}", duration1, accumulated1 );

        FloatT accumulated2 = static_cast<FloatT>( 0.0 );
        value = base;
        stopwatch.Restart( );

        for ( Int64 i = 0; i < ValueIterationCount; i++ )
        {
            for ( Int32 j = 0; j < ExpIterationCount; ++j )
            {
                accumulated2 += std::scalbn( value, j + 1 );
            }
            value += increment;
        }

        stopwatch.Stop( );
        auto duration2 = stopwatch.TotalSeconds( );
        PrintLn( "\tstd:  Duration={}, Accumulated={}", duration2, accumulated2 );
        PrintPerformance( duration1, duration2 );
        PrintAccumulated( accumulated1, accumulated2 );
    }
}

void ScaleBNDoubleTest( Int64 outerIterationCount )
{
    ScaleBNTest<double>( outerIterationCount, __FUNCTION__ );
}
void ScaleBNFloatTest( Int64 outerIterationCount )
{
    ScaleBNTest<float>( outerIterationCount, __FUNCTION__ );
}




void SinDoubleTest( Int64 outerIterationCount )
{
    RunTrigTest<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Sin( arg ); }, []( auto arg ) { return std::sin( arg ); } );
}

void SinFloatTest( Int64 outerIterationCount )
{
    RunTrigTest<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Sin( arg ); }, []( auto arg ) { return std::sin( arg ); } );
}

void ASinDoubleTest( Int64 outerIterationCount )
{
    RunATrigTest<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return ASin( arg ); }, []( auto arg ) { return std::asin( arg ); } );
}

void ASinFloatTest( Int64 outerIterationCount )
{
    RunATrigTest<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return ASin( arg ); }, []( auto arg ) { return std::asin( arg ); } );
}


void CosDoubleTest( Int64 outerIterationCount )
{
    RunTrigTest<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Cos( arg ); }, []( auto arg ) { return std::cos( arg ); } );
}

void CosFloatTest( Int64 outerIterationCount )
{
    RunTrigTest<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Cos( arg ); }, []( auto arg ) { return std::cos( arg ); } );
}

void ACosDoubleTest( Int64 outerIterationCount )
{
    RunATrigTest<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return ACos( arg ); }, []( auto arg ) { return std::acos( arg ); } );
}

void ACosFloatTest( Int64 outerIterationCount )
{
    RunATrigTest<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return ACos( arg ); }, []( auto arg ) { return std::acos( arg ); } );
}


void TanDoubleTest( Int64 outerIterationCount )
{
    RunTrigTest<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Tan( arg ); }, []( auto arg ) { return std::tan( arg ); } );
}

void TanFloatTest( Int64 outerIterationCount )
{
    RunTrigTest<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Tan( arg ); }, []( auto arg ) { return std::tan( arg ); } );
}

void ATanDoubleTest( Int64 outerIterationCount )
{
    RunATrigTest<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return ATan( arg ); }, []( auto arg ) { return std::atan( arg ); } );
}

void ATanFloatTest( Int64 outerIterationCount )
{
    RunATrigTest<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return ATan( arg ); }, []( auto arg ) { return std::atan( arg ); } );
}

void ATan2DoubleTest( Int64 outerIterationCount )
{
    RunTrigTest<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return ATan2( arg, arg ); }, []( auto arg ) { return std::atan2( arg, arg ); } );
}

void ATan2FloatTest( Int64 outerIterationCount )
{
    RunTrigTest<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return ATan2( arg, arg ); }, []( auto arg ) { return std::atan2( arg, arg ); } );
}




void SqrtDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Sqrt( arg ); }, []( auto arg ) { return std::sqrt( arg ); } );
}
void SqrtFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Sqrt( arg ); }, []( auto arg ) { return std::sqrt( arg ); } );
}

template<typename FloatT >
void NextAfterTest( Int64 outerIterationCount, const char* testName )
{
    Int64 innerIterationCount = 1'000'000'000;
    PrintLn( "{}: Outer {}, Inner {}", testName, outerIterationCount, innerIterationCount );

    for ( int j = 0; j < outerIterationCount; j++ )
    {
        FloatT argumentValue = static_cast<FloatT>( 0.0 );
        FloatT accumulated1 = static_cast<FloatT>( 0.0 );
        Stopwatch stopwatch;
        stopwatch.Start( );

        for ( Int64 i = 0; i < innerIterationCount; i++ )
        {
            argumentValue = NextAfter( argumentValue, static_cast<FloatT>( 1'000'000'000.0 ) );
            accumulated1 += argumentValue;
        }

        stopwatch.Stop( );
        auto duration1 = stopwatch.TotalSeconds( );
        PrintLn( "\tMath: Duration={}, Accumulated={}", duration1, accumulated1 );

        argumentValue = static_cast<FloatT>( 0.0 );
        FloatT accumulated2 = static_cast<FloatT>( 0.0 );
        stopwatch.Restart( );

        for ( Int64 i = 0; i < innerIterationCount; i++ )
        {
            argumentValue = std::nextafter( argumentValue, static_cast<FloatT>( 1'000'000'000.0 ) );
            accumulated2 += argumentValue;
        }

        stopwatch.Stop( );
        auto duration2 = stopwatch.TotalSeconds( );
        PrintLn( "\tstd:  Duration={}, Accumulated={}", duration2, accumulated2 );
        PrintPerformance( duration1, duration2 );
        PrintAccumulated( accumulated1, accumulated2 );
    }
}

void NextAfterDoubleTest( Int64 outerIterationCount )
{
    NextAfterTest<double>( outerIterationCount, __FUNCTION__ );
}
void NextAfterFloatTest( Int64 outerIterationCount )
{
    NextAfterTest<float>( outerIterationCount, __FUNCTION__ );
}

template<typename FloatT >
void NextUpTest( Int64 outerIterationCount, const char* testName )
{
    Int64 innerIterationCount = 1'000'000'000;
    PrintLn( "{}: Outer {}, Inner {}", testName, outerIterationCount, innerIterationCount );
    constexpr FloatT baseValue = static_cast<FloatT>( -0.0 );

    for ( int j = 0; j < outerIterationCount; j++ )
    {
        FloatT argumentValue = static_cast<FloatT>( 0.0 );
        FloatT accumulated1 = static_cast<FloatT>( 0.0 );
        Stopwatch stopwatch;
        stopwatch.Start( );

        for ( Int64 i = 0; i < innerIterationCount; i++ )
        {
            argumentValue = NextUp( argumentValue );
            accumulated1 += argumentValue;
        }

        stopwatch.Stop( );
        auto duration1 = stopwatch.TotalSeconds( );
        PrintLn( "\tMath: Duration={}, Accumulated={}", duration1, accumulated1 );

        argumentValue = static_cast<FloatT>( 0.0 );
        FloatT accumulated2 = static_cast<FloatT>( 0.0 );
        stopwatch.Restart( );

        for ( Int64 i = 0; i < innerIterationCount; i++ )
        {
            argumentValue = std::nextafter( argumentValue, std::numeric_limits<FloatT>::infinity( ) );
            accumulated2 += argumentValue;
        }

        stopwatch.Stop( );
        auto duration2 = stopwatch.TotalSeconds( );
        PrintLn( "\tstd: Duration={}, Accumulated={}", duration2, accumulated2 );
        PrintPerformance( duration1, duration2 );
        PrintAccumulated( accumulated1, accumulated2 );
    }

}

void NextUpDoubleTest( Int64 outerIterationCount )
{
    NextUpTest<double>( outerIterationCount, __FUNCTION__ );
}
void NextUpFloatTest( Int64 outerIterationCount )
{
    NextUpTest<float>( outerIterationCount, __FUNCTION__ );
}


template<typename FloatT >
void NextDownTest( Int64 outerIterationCount, const char* testName )
{
    Int64 innerIterationCount = 1'000'000'000;
    PrintLn( "{}: Outer {}, Inner {}", testName, outerIterationCount, innerIterationCount );

    for ( int j = 0; j < outerIterationCount; j++ )
    {
        FloatT argumentValue = static_cast<FloatT>( 0.0 );
        FloatT accumulated1 = static_cast<FloatT>( 0.0 );
        Stopwatch stopwatch;
        stopwatch.Start( );

        for ( Int64 i = 0; i < innerIterationCount; i++ )
        {
            argumentValue = NextDown( argumentValue );
            accumulated1 += argumentValue;
        }

        stopwatch.Stop( );
        auto duration1 = stopwatch.TotalSeconds( );
        PrintLn( "\tMath: Duration={}, Accumulated={}", duration1, accumulated1 );


        argumentValue = static_cast<FloatT>( 0.0 );
        FloatT accumulated2 = static_cast<FloatT>( 0.0 );

        stopwatch.Restart( );

        for ( Int64 i = 0; i < innerIterationCount; i++ )
        {
            argumentValue = std::nextafter( argumentValue, -std::numeric_limits<FloatT>::infinity( ) );
            accumulated2 += argumentValue;
        }

        stopwatch.Stop( );
        auto duration2 = stopwatch.TotalSeconds( );
        PrintLn( "\tstd: Duration={}, Accumulated={}", duration2, accumulated2 );
        PrintPerformance( duration1, duration2 );
        PrintAccumulated( accumulated1, accumulated2 );
    }
}

void NextDownDoubleTest( Int64 outerIterationCount )
{
    NextDownTest<double>( outerIterationCount, __FUNCTION__ );
}
void NextDownFloatTest( Int64 outerIterationCount )
{
    NextDownTest<float>( outerIterationCount, __FUNCTION__ );
}


template<typename FloatT >
void FModTest( Int64 outerIterationCount, const char* testName )
{
    constexpr FloatT increment = static_cast<FloatT>( 0.000001 );
    Int64 innerIterationCount = 1'000'000'000;
    PrintLn( "{}: Outer {}, Inner {}", testName, outerIterationCount, innerIterationCount );

    for ( int j = 0; j < outerIterationCount; j++ )
    {
        FloatT argument1Value = static_cast<FloatT>( M_PI );
        FloatT argument2Value = static_cast<FloatT>( M_PI_4 );
        FloatT accumulated1 = static_cast<FloatT>( 0.0 );
        Stopwatch stopwatch;
        stopwatch.Start( );

        for ( Int64 i = 0; i < innerIterationCount; i++ )
        {
            accumulated1 += FMod( argument1Value, argument2Value );
            argument1Value += increment;
            argument2Value += increment;
        }

        stopwatch.Stop( );
        auto duration1 = stopwatch.TotalSeconds( );
        PrintLn( "\tMath: Duration={}, Accumulated={}", duration1, accumulated1 );


        argument1Value = static_cast<FloatT>( M_PI );
        argument2Value = static_cast<FloatT>( M_PI_4 );
        FloatT accumulated2 = static_cast<FloatT>( 0.0 );

        stopwatch.Restart( );

        for ( Int64 i = 0; i < innerIterationCount; i++ )
        {
            accumulated2 += std::fmod( argument1Value, argument2Value );
            argument1Value += increment;
            argument2Value += increment;
        }

        stopwatch.Stop( );
        auto duration2 = stopwatch.TotalSeconds( );
        PrintLn( "\tstd: Duration={}, Accumulated={}", duration2, accumulated2 );
        PrintPerformance( duration1, duration2 );
        PrintAccumulated( accumulated1, accumulated2 );
    }
}

void FModDoubleTest( Int64 outerIterationCount )
{
    FModTest<double>( outerIterationCount, __FUNCTION__ );
}

void FModFloatTest( Int64 outerIterationCount )
{
    FModTest<float>( outerIterationCount, __FUNCTION__ );
}

void ExpDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Exp( arg ); }, []( auto arg ) { return std::exp( arg ); }, 0.9, 0.000000001 );
}
void ExpFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Exp( arg ); }, []( auto arg ) { return std::exp( arg ); }, 0.9f, 0.000000001f );
}

void HypotDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Hypot( arg, arg ); }, []( auto arg ) { return std::hypot( arg, arg ); }, 0.999, 0.000000001 );
}
void HypotFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Hypot( arg, arg ); }, []( auto arg ) { return std::hypot( arg, arg ); }, 0.999f, 0.000000001f );
}

void LogDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Log( arg ); }, []( auto arg ) { return std::log( arg ); }, 0.9, 0.000000001 );
}
void LogFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Log( arg ); }, []( auto arg ) { return std::log( arg ); }, 0.9f, 0.000000001f );
}

void Log2DoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Log2( arg ); }, []( auto arg ) { return std::log2( arg ); }, 0.9, 0.000000001 );
}
void Log2FloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Log2( arg ); }, []( auto arg ) { return std::log2( arg ); }, 0.9f, 0.000000001f );
}

void Log10DoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Log10( arg ); }, []( auto arg ) { return std::log10( arg ); }, 0.9, 0.000000001 );
}
void Log10FloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto arg ) { return Log10( arg ); }, []( auto arg ) { return std::log10( arg ); }, 0.9f, 0.000000001f );
}




/*
template<typename FloatT >
void RemQuoTest( Int64 outerIterationCount, const char* testName )
{
    constexpr FloatT increment = static_cast<FloatT>( 0.000001 );
    Int64 innerIterationCount = 1'000'000'000;
    PrintLn( "{}: Outer {}, Inner {}", testName, outerIterationCount, innerIterationCount );

    for ( int j = 0; j < outerIterationCount; j++ )
    {
        FloatT argument1Value = static_cast<FloatT>( M_PI );
        FloatT argument2Value = static_cast<FloatT>( M_PI_4 );
        FloatT accumulated = static_cast<FloatT>( 0.0 );
        int accumulatedQuotient = 0;
        Stopwatch stopwatch;
        stopwatch.Start( );

        for ( Int64 i = 0; i < innerIterationCount; i++ )
        {
            int quotient;
            accumulated += RemQuo( argument1Value, argument2Value, quotient );
            accumulatedQuotient += quotient;
            argument1Value += increment;
            argument2Value += increment;
        }

        stopwatch.Stop( );
        auto duration = stopwatch.TotalSeconds( );
        PrintLn( "\tMath: Duration={}, Accumulated={} Accumulated Quotient={}", duration, accumulated, accumulatedQuotient );
    }
    for ( int j = 0; j < outerIterationCount; j++ )
    {
        FloatT argument1Value = static_cast<FloatT>( M_PI );
        FloatT argument2Value = static_cast<FloatT>( M_PI_4 );
        FloatT accumulated = static_cast<FloatT>( 0.0 );
        int accumulatedQuotient = 0;
        Stopwatch stopwatch;
        stopwatch.Start( );

        for ( Int64 i = 0; i < innerIterationCount; i++ )
        {
            int quotient;
            accumulated += std::remquo( argument1Value, argument2Value, &quotient );
            accumulatedQuotient += quotient;
            argument1Value += increment;
            argument2Value += increment;
        }

        stopwatch.Stop( );
        auto duration = stopwatch.TotalSeconds( );
        PrintLn( "\tstd: Duration={}, Accumulated={} Accumulated Quotient={}", duration, accumulated, accumulatedQuotient );
    }
}

void RemQuoDoubleTest( Int64 outerIterationCount )
{
    RemQuoTest<double>( outerIterationCount, __FUNCTION__ );
}
void RemQuoFloatTest( Int64 outerIterationCount )
{
    RemQuoTest<float>( outerIterationCount, __FUNCTION__ );
}
*/

void OverheadTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto x ) { return x; } );
}

void SimpleOverheadDoubleTest( Int64 outerIterationCount )
{
    RunTest1<double>( outerIterationCount, __FUNCTION__, []( auto x ) { return x; } );
}
void SimpleOverheadFloatTest( Int64 outerIterationCount )
{
    RunTest1<float>( outerIterationCount, __FUNCTION__, []( auto x ) { return x; } );
}


void RunBasicOperations( )
{
    constexpr Int64 OuterIterationCount = 1;

    SimpleOverheadDoubleTest( OuterIterationCount );
    SimpleOverheadFloatTest( OuterIterationCount );

    OverheadDoubleTest( OuterIterationCount );
    OverheadFloatTest( OuterIterationCount );


    IsNaNDoubleTest( OuterIterationCount );
    IsNaNFloatTest( OuterIterationCount );

    IsInfDoubleTest( OuterIterationCount );
    IsInfFloatTest( OuterIterationCount );

    AbsDoubleTest( OuterIterationCount );
    AbsFloatTest( OuterIterationCount );

    SignBitDoubleTest( OuterIterationCount );
    SignBitFloatTest( OuterIterationCount );

    FRExpDoubleTest( OuterIterationCount );
    FRExpFloatTest( OuterIterationCount );


    ModFDoubleTest( OuterIterationCount );
    ModFFloatTest( OuterIterationCount );

    MinDoubleTest( OuterIterationCount );
    MinFloatTest( OuterIterationCount );

    MaxDoubleTest( OuterIterationCount );
    MaxFloatTest( OuterIterationCount );

    FloorDoubleTest( OuterIterationCount );
    FloorFloatTest( OuterIterationCount );

    CeilDoubleTest( OuterIterationCount );
    CeilFloatTest( OuterIterationCount );

    TruncDoubleTest( OuterIterationCount );
    TruncFloatTest( OuterIterationCount );

    RoundDoubleTest( OuterIterationCount );
    RoundFloatTest( OuterIterationCount );

    ClampDoubleTest( OuterIterationCount );
    ClampFloatTest( OuterIterationCount );

    LerpDoubleTest( OuterIterationCount );
    LerpFloatTest( OuterIterationCount );

    CopySignDoubleTest( OuterIterationCount );
    CopySignFloatTest( OuterIterationCount );

    ScaleBNDoubleTest( OuterIterationCount );
    ScaleBNFloatTest( OuterIterationCount );


    SinDoubleTest( OuterIterationCount );
    SinFloatTest( OuterIterationCount );

    CosDoubleTest( OuterIterationCount );
    CosFloatTest( OuterIterationCount );

    TanDoubleTest( OuterIterationCount );
    TanFloatTest( OuterIterationCount );


    SqrtDoubleTest( OuterIterationCount );
    SqrtFloatTest( OuterIterationCount );


    ASinDoubleTest( OuterIterationCount );
    ASinFloatTest( OuterIterationCount );

    ACosDoubleTest( OuterIterationCount );
    ACosFloatTest( OuterIterationCount );

    ATanDoubleTest( OuterIterationCount );
    ATanFloatTest( OuterIterationCount );

    ATan2DoubleTest( OuterIterationCount );
    ATan2FloatTest( OuterIterationCount );

    NextAfterDoubleTest( OuterIterationCount );
    NextAfterFloatTest( OuterIterationCount );

    NextUpDoubleTest( OuterIterationCount );
    NextUpFloatTest( OuterIterationCount );

    NextDownDoubleTest( OuterIterationCount );
    NextDownFloatTest( OuterIterationCount );
    
    FModDoubleTest( OuterIterationCount );
    FModFloatTest( OuterIterationCount );

    ExpDoubleTest( OuterIterationCount );
    ExpFloatTest( OuterIterationCount );

    HypotDoubleTest( OuterIterationCount );
    HypotFloatTest( OuterIterationCount );

    LogDoubleTest( OuterIterationCount );
    LogFloatTest( OuterIterationCount );

    Log2DoubleTest( OuterIterationCount );
    Log2FloatTest( OuterIterationCount );


    Log10DoubleTest( OuterIterationCount );
    Log10FloatTest( OuterIterationCount );


    //RemQuoDoubleTest( OuterIterationCount );
    //RemQuoFloatTest( OuterIterationCount );


}
