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


#include "HCCMathPerfTest01.h"

#include <HCCMatrix.h>
#include <HCCDateTime.h>
#include <HCCString.h>

using namespace Harlinn::Common::Core;

namespace
{
    template<typename VectorT, typename Func1 >
    inline void RunTest( Int64 outerIterationCount,
        const char* testName, Func1&& func1,
        const VectorT& baseValue, const VectorT& baseIncrement )
    {
        Int64 innerIterationCount = 1'000'000'000;

        for ( int j = 0; j < outerIterationCount; j++ )
        {
            VectorT argumentValue = baseValue;
            VectorT accumulated;
            Stopwatch stopwatch;
            stopwatch.Start( );


            for ( Int64 i = 0; i < innerIterationCount; i++ )
            {
                accumulated += func1( argumentValue );
                argumentValue += baseIncrement;
            }

            stopwatch.Stop( );
            auto duration = stopwatch.TotalSeconds( );
            PrintLn( "{}: Duration={}, Accumulated={}",
                testName, duration, accumulated.ToString() );
        }
    }


    template<typename VectorT, typename Func1, typename FloatT >
    inline void RunTest( Int64 outerIterationCount,
        const char* testName, Func1&& func1,
        const VectorT& vectorBaseValue, FloatT baseValue, FloatT baseIncrement )
    {
        Int64 innerIterationCount = 1'000'000'000;

        for ( int j = 0; j < outerIterationCount; j++ )
        {
            VectorT argumentValue1 = vectorBaseValue;
            FloatT argumentValue2 = baseValue;
            VectorT accumulated;
            Stopwatch stopwatch;
            stopwatch.Start( );

            for ( Int64 i = 0; i < innerIterationCount; i++ )
            {
                accumulated += func1( argumentValue1, argumentValue2 );
                argumentValue1 += baseIncrement;
                argumentValue2 += baseIncrement;
            }

            stopwatch.Stop( );
            auto duration = stopwatch.TotalSeconds( );
            PrintLn( "{}: Duration={}, Accumulated={}",
                testName, duration, accumulated.ToString( ) );
        }
    }



    template<typename VectorT, typename Func1 >
    inline void RunTest( Int64 outerIterationCount,
        const char* testName, Func1&& func1,
        const VectorT& baseValue1, const VectorT& baseValue2, const VectorT& baseIncrement )
    {
        Int64 innerIterationCount = 1'000'000'000;

        for ( int j = 0; j < outerIterationCount; j++ )
        {
            VectorT argumentValue1 = baseValue1;
            VectorT argumentValue2 = baseValue2;
            VectorT accumulated;
            Stopwatch stopwatch;
            stopwatch.Start( );


            for ( Int64 i = 0; i < innerIterationCount; i++ )
            {
                accumulated += func1( argumentValue1, argumentValue2 );
                argumentValue1 += baseIncrement;
                argumentValue2 += baseIncrement;
            }

            stopwatch.Stop( );
            auto duration = stopwatch.TotalSeconds( );
            PrintLn( "{}: Duration={}, Accumulated={}",
                testName, duration, accumulated.ToString( ) );
        }
    }


}


void RunAddDouble1ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 1>;
    VectorType baseValue( 1.0 );
    VectorType increment( 0.000001 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}

void RunAddDouble1BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 1>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddDouble1CTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 1>;
    using FloatType = VectorType::ValueType;
    VectorType baseValue1( 1.0 );
    FloatType baseValue2 = static_cast<FloatType>( 10.0 );
    FloatType increment = static_cast<FloatType>( 0.000001 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, auto arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}


void RunSubDouble1ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 1>;
    VectorType baseValue( 1.0 );
    VectorType increment( 0.000001 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return -arg; }, baseValue, increment );
}

void RunSubDouble1BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 1>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return -arg1 - arg2; }, baseValue1, baseValue2, increment );
}




void RunAddDouble2ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 2>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}

void RunAddDouble2BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 2>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddDouble2CTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 2>;
    using FloatType = VectorType::ValueType;
    VectorType baseValue1( 1.0 );
    FloatType baseValue2 = static_cast<FloatType>( 10.0 );
    FloatType increment = static_cast<FloatType>( 0.000001 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, auto arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}



void RunSubDouble2ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 2>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return -arg; }, baseValue, increment );

}

void RunSubDouble2BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 2>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return -arg1 - arg2; }, baseValue1, baseValue2, increment );
}



void RunAddDouble3ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 3>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}

void RunAddDouble3BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 3>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}


void RunAddDouble4ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 4>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}


void RunAddDouble4BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 4>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddDouble5ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 5>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}
void RunAddDouble5BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 5>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddDouble6ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 6>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}
void RunAddDouble6BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 6>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}


void RunAddDouble7ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 7>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}
void RunAddDouble7BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 7>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}


void RunAddDouble8ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 8>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}
void RunAddDouble8BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 8>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}


void RunAddDouble9ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 9>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}
void RunAddDouble9BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 9>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}


void RunAddDouble10ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 10>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}
void RunAddDouble10BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 10>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddDouble11ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 11>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}
void RunAddDouble11BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 11>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}


void RunAddDouble12ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 12>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}
void RunAddDouble12BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 12>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddDouble16ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 16>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012, 0.000013, 0.000014, 0.000015, 0.000016 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}
void RunAddDouble16BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 16>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012, 0.000013, 0.000014, 0.000015, 0.000016 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}


void RunAddDouble24ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 24>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012, 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}
void RunAddDouble24BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 24>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012, 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddDouble48ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 48>;
    VectorType baseValue( 1 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012, 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012, 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012, 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}
void RunAddDouble48BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<double, 48>;
    VectorType baseValue1( 1.0 );
    VectorType baseValue2( 10.0 );
    VectorType increment( 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012, 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012, 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012, 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009, 0.000010, 0.000011, 0.000012 );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}


void RunAddFloat1ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 1>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}

void RunAddFloat1BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 1>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

/*
void RunAddFloat2ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 2>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}

void RunAddFloat2BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 2>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}


void RunAddFloat3ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 3>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );
}

void RunAddFloat3BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 3>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}


void RunAddFloat4ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 4>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat4BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 4>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}
*/
void RunAddFloat5ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 5>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat5BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 5>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat6ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 6>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat6BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 6>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat7ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 7>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat7BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 7>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat8ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 8>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat8BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 8>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat9ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 9>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat9BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 9>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat10ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 10>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat10BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 10>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat11ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 11>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat11BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 11>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat12ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 12>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat12BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 12>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat13ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 13>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000013f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat13BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 13>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000013f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat14ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 14>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000013f, 0.000014f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat14BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 14>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000013f, 0.000014f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat15ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 15>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000013f, 0.000014f, 0.000015f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat15BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 15>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000013f, 0.000014f, 0.000015f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat16ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 16>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000013f, 0.000014f, 0.000015f, 0.000016f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat16BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 16>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000013f, 0.000014f, 0.000015f, 0.000016f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat24ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 24>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat24BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 24>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}

void RunAddFloat48ATest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 48>;
    VectorType baseValue( 1.f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg ) { return arg; }, baseValue, increment );

}
void RunAddFloat48BTest( Int64 outerIterationCount )
{
    using VectorType = Math::Vector<float, 48>;
    VectorType baseValue1( 1.0f );
    VectorType baseValue2( 10.0f );
    VectorType increment( 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f, 0.000001f, 0.000002f, 0.000003f, 0.000004f, 0.000005f, 0.000006f, 0.000007f, 0.000008f, 0.000009f, 0.000010f, 0.000011f, 0.000012f );
    RunTest<VectorType>( outerIterationCount, __FUNCTION__, []( const auto& arg1, const auto& arg2 ) { return arg1 + arg2; }, baseValue1, baseValue2, increment );
}


void RunVectorOperations( )
{
    Int64 outerIterationCount = 1;
    
    //RunAddDouble16ATest( outerIterationCount );
    //RunAddDouble16BTest( outerIterationCount );
    
    RunAddDouble1ATest( outerIterationCount );
    RunAddDouble1BTest( outerIterationCount );
    RunAddDouble1CTest( outerIterationCount );

    RunSubDouble1ATest( outerIterationCount );
    RunSubDouble1BTest( outerIterationCount );


    RunAddDouble2ATest( outerIterationCount );
    RunAddDouble2BTest( outerIterationCount );
    RunAddDouble2CTest( outerIterationCount );

    RunSubDouble2ATest( outerIterationCount );
    RunSubDouble2BTest( outerIterationCount );


    RunAddDouble3ATest( outerIterationCount );
    RunAddDouble3BTest( outerIterationCount );

    RunAddDouble4ATest( outerIterationCount );
    
    RunAddDouble4BTest( outerIterationCount );
    
    
    RunAddDouble5ATest( outerIterationCount );
    RunAddDouble5BTest( outerIterationCount );

    RunAddDouble6ATest( outerIterationCount );
    RunAddDouble6BTest( outerIterationCount );

    RunAddDouble7ATest( outerIterationCount );
    RunAddDouble7BTest( outerIterationCount );

    RunAddDouble8ATest( outerIterationCount );
    RunAddDouble8BTest( outerIterationCount );

    RunAddDouble9ATest( outerIterationCount );
    RunAddDouble9BTest( outerIterationCount );

    RunAddDouble10ATest( outerIterationCount );
    RunAddDouble10BTest( outerIterationCount );

    RunAddDouble11ATest( outerIterationCount );
    RunAddDouble11BTest( outerIterationCount );

    RunAddDouble12ATest( outerIterationCount );
    RunAddDouble12BTest( outerIterationCount );
    
    RunAddDouble16ATest( outerIterationCount );
    RunAddDouble16BTest( outerIterationCount );

    RunAddDouble24ATest( outerIterationCount );
    RunAddDouble24BTest( outerIterationCount );

    RunAddDouble48ATest( outerIterationCount );
    RunAddDouble48BTest( outerIterationCount );

    RunAddFloat1ATest( outerIterationCount );
    RunAddFloat1BTest( outerIterationCount );
    /*
    RunAddFloat2ATest( outerIterationCount );
    RunAddFloat2BTest( outerIterationCount );
    
    RunAddFloat3ATest( outerIterationCount );
    RunAddFloat3BTest( outerIterationCount );

    RunAddFloat4ATest( outerIterationCount );
    RunAddFloat4BTest( outerIterationCount );
    */
    RunAddFloat5ATest( outerIterationCount );
    RunAddFloat5BTest( outerIterationCount );

    RunAddFloat6ATest( outerIterationCount );
    RunAddFloat6BTest( outerIterationCount );

    RunAddFloat7ATest( outerIterationCount );
    RunAddFloat7BTest( outerIterationCount );

    RunAddFloat8ATest( outerIterationCount );
    RunAddFloat8BTest( outerIterationCount );

    RunAddFloat9ATest( outerIterationCount );
    RunAddFloat9BTest( outerIterationCount );

    RunAddFloat10ATest( outerIterationCount );
    RunAddFloat10BTest( outerIterationCount );

    RunAddFloat11ATest( outerIterationCount );
    RunAddFloat11BTest( outerIterationCount );

    RunAddFloat12ATest( outerIterationCount );
    RunAddFloat12BTest( outerIterationCount );

    RunAddFloat13ATest( outerIterationCount );
    RunAddFloat13BTest( outerIterationCount );

    RunAddFloat14ATest( outerIterationCount );
    RunAddFloat14BTest( outerIterationCount );

    RunAddFloat15ATest( outerIterationCount );
    RunAddFloat15BTest( outerIterationCount );

    RunAddFloat16ATest( outerIterationCount );
    RunAddFloat16BTest( outerIterationCount );

    RunAddFloat24ATest( outerIterationCount );
    RunAddFloat24BTest( outerIterationCount );

    RunAddFloat48ATest( outerIterationCount );
    RunAddFloat48BTest( outerIterationCount );

    

    
}