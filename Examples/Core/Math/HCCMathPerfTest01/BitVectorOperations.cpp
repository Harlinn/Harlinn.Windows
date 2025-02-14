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


#include "HCCMathPerfTest01.h"

#include <HCCMath.h>
#include <HCCDateTime.h>
#include <HCCBits.h>
#include <bitset>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Math;

namespace
{
    using BitVectorType = BitVector<std::vector<UInt16>>;

    template<size_t N>
    void PushBackTest( const char* testName, UInt64 outerIterationCount )
    {
        constexpr size_t BitCount = N;
        Stopwatch stopwatch;
        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            std::vector<bool> bits;
            bits.reserve( BitCount );
            for ( size_t i = 0; i < BitCount; i++ )
            {
                bits.push_back( true );
            }
        }
        stopwatch.Stop( );
        double stdDuration = stopwatch.Elapsed( ).TotalSeconds( );
        stopwatch.Reset( );

        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            BitVectorType bits;
            bits.reserve( BitCount );
            for ( size_t i = 0; i < BitCount; i++ )
            {
                bits.push_back( true );
            }
        }
        stopwatch.Stop( );
        double duration = stopwatch.Elapsed( ).TotalSeconds( );

        double factor = stdDuration / duration;
        printf( "%s\r\n\tstd::vector<bool>:%f seconds\r\n\tBitVector  :%f seconds, factor: %f\r\n\r\n", testName, stdDuration, duration, factor );
    }

    template<size_t N>
    void SetTest( const char* testName, UInt64 outerIterationCount )
    {
        constexpr size_t BitCount = N;
        Stopwatch stopwatch;
        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            std::vector<bool> bits;
            bits.resize( BitCount );
            for ( size_t i = 0; i < BitCount; i++ )
            {
                bits[i] = true;
            }
        }
        stopwatch.Stop( );
        double stdDuration = stopwatch.Elapsed( ).TotalSeconds( );
        stopwatch.Reset( );

        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            BitVectorType bits;
            bits.resize( BitCount );
            for ( size_t i = 0; i < BitCount; i++ )
            {
                bits[i] = true;
            }
        }
        stopwatch.Stop( );
        double duration = stopwatch.Elapsed( ).TotalSeconds( );

        double factor = stdDuration / duration;
        printf( "%s\r\n\tstd::vector<bool>:%f seconds\r\n\tBitVector  :%f seconds, factor: %f\r\n\r\n", testName, stdDuration, duration, factor );
    }
}

void RunBitVectorOperations( )
{
    UInt64 OuterIterationCount1 = 10000000;
    UInt64 OuterIterationCount2 = 100000;
    UInt64 OuterIterationCount3 = 10000;
    PushBackTest<16>( "Small PushBackTest", OuterIterationCount1 );
    PushBackTest<1024>( "Medium PushBackTest", OuterIterationCount2 );
    PushBackTest<200* 1024>( "Large PushBackTest", OuterIterationCount3 );

    SetTest<16>( "Small SetTest", OuterIterationCount1 );
    SetTest<1024>( "Medium SetTest", OuterIterationCount2 );
    SetTest<200 * 1024>( "Large SetTest", OuterIterationCount3 );

}