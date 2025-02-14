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
    template<size_t N>
    void RunBitsAnyTest( const char* testName, UInt64 outerIterationCount )
    {
        constexpr size_t MaxValue = Bits<N>::Mask;
        size_t StdBitsetAccumulated = 0;
        size_t BitsAccumulated = 0;
        Stopwatch stopwatch;
        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                const std::bitset<N> bits( i );
                if ( bits.any( ) )
                {
                    StdBitsetAccumulated++;
                }
            }
        }
        stopwatch.Stop( );
        double StdBitsetDuration = stopwatch.Elapsed( ).TotalSeconds();
        stopwatch.Reset( );

        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                const Bits<N> bits( static_cast<Bits<N>::word_type>( i ) );
                if ( bits.any( ) )
                {
                    BitsAccumulated++;
                }
            }
        }
        stopwatch.Stop( );
        double BitsDuration = stopwatch.Elapsed( ).TotalSeconds( );

        if ( StdBitsetAccumulated == BitsAccumulated )
        {
            double factor = StdBitsetDuration / BitsDuration;
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>  :%f seconds - factor: %f\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration, factor );
        }
        else
        {
            printf( "Error in %s\r\n\tstd::bitset<%zu> accumulated:%zu\r\n\tBits<%zu> accumulated:  %zu\r\n\r\n", testName, N, StdBitsetAccumulated, N, BitsAccumulated );
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>:  %f seconds\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration );
        }
    }

    template<size_t N>
    void RunBitsNoneTest( const char* testName, UInt64 outerIterationCount )
    {
        constexpr size_t MaxValue = Bits<N>::Mask;
        size_t StdBitsetAccumulated = 0;
        size_t BitsAccumulated = 0;
        Stopwatch stopwatch;
        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                const std::bitset<N> bits( i );
                if ( bits.none( ) )
                {
                    StdBitsetAccumulated++;
                }
            }
        }
        stopwatch.Stop( );
        double StdBitsetDuration = stopwatch.Elapsed( ).TotalSeconds( );
        stopwatch.Reset( );

        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                const Bits<N> bits( static_cast<Bits<N>::word_type>( i ) );
                if ( bits.none( ) )
                {
                    BitsAccumulated++;
                }
            }
        }
        stopwatch.Stop( );
        double BitsDuration = stopwatch.Elapsed( ).TotalSeconds( );

        if ( StdBitsetAccumulated == BitsAccumulated )
        {
            double factor = StdBitsetDuration / BitsDuration;
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>  :%f seconds - factor:%f\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration, factor );
        }
        else
        {
            printf( "Error in %s\r\n\tstd::bitset<%zu> accumulated:%zu\r\n\tBits<%zu> accumulated:  %zu\r\n\r\n", testName, N, StdBitsetAccumulated, N, BitsAccumulated );
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>:  %f seconds\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration );
        }
    }

    template<size_t N>
    void RunBitsAllTest( const char* testName, UInt64 outerIterationCount )
    {
        constexpr size_t MaxValue = Bits<N>::Mask;
        size_t StdBitsetAccumulated = 0;
        size_t BitsAccumulated = 0;
        Stopwatch stopwatch;
        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                const std::bitset<N> bits( i );
                if ( bits.all( ) )
                {
                    StdBitsetAccumulated++;
                }
            }
        }
        stopwatch.Stop( );
        double StdBitsetDuration = stopwatch.Elapsed( ).TotalSeconds( );
        stopwatch.Reset( );

        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                const Bits<N> bits( static_cast<Bits<N>::word_type>( i ) );
                if ( bits.all( ) )
                {
                    BitsAccumulated++;
                }
            }
        }
        stopwatch.Stop( );
        double BitsDuration = stopwatch.Elapsed( ).TotalSeconds( );

        if ( StdBitsetAccumulated == BitsAccumulated )
        {
            double factor = StdBitsetDuration / BitsDuration;
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>  :%f seconds - factor %f\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration, factor );
        }
        else
        {
            printf( "Error in %s\r\n\tstd::bitset<%zu> accumulated:%zu\r\n\tBits<%zu> accumulated:  %zu\r\n\r\n", testName, N, StdBitsetAccumulated, N, BitsAccumulated );
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>:  %f seconds\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration );
        }
    }


    template<size_t N>
    void RunBitsCountTest( const char* testName, UInt64 outerIterationCount )
    {
        constexpr size_t MaxValue = Bits<N>::Mask;
        size_t StdBitsetAccumulated = 0;
        size_t BitsAccumulated = 0;
        Stopwatch stopwatch;
        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                const std::bitset<N> bits( i );
                StdBitsetAccumulated += bits.count( );
            }
        }
        stopwatch.Stop( );
        double StdBitsetDuration = stopwatch.Elapsed( ).TotalSeconds( );
        stopwatch.Reset( );

        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                const Bits<N> bits( static_cast<Bits<N>::word_type>( i ) );
                BitsAccumulated += bits.count( );
            }
        }
        stopwatch.Stop( );
        double BitsDuration = stopwatch.Elapsed( ).TotalSeconds( );

        if ( StdBitsetAccumulated == BitsAccumulated )
        {
            double factor = StdBitsetDuration / BitsDuration;
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>  :%f seconds - factor: %f\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration, factor );
        }
        else
        {
            printf( "Error in %s\r\n\tstd::bitset<%zu> accumulated:%zu\r\n\tBits<%zu> accumulated:  %zu\r\n\r\n", testName, N, StdBitsetAccumulated, N, BitsAccumulated );
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>:  %f seconds\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration );
        }
    }

    template<size_t N>
    void RunBitsTestTest( const char* testName, UInt64 outerIterationCount )
    {
        constexpr size_t MaxValue = Bits<N>::Mask;
        size_t StdBitsetAccumulated = 0;
        size_t BitsAccumulated = 0;
        Stopwatch stopwatch;
        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                const std::bitset<N> bits( i );
                for ( size_t k = 0; k < N; k++ )
                {
                    if ( bits.test( k ) )
                    {
                        StdBitsetAccumulated++;
                    }
                }
            }
        }
        stopwatch.Stop( );
        double StdBitsetDuration = stopwatch.Elapsed( ).TotalSeconds( );
        stopwatch.Reset( );

        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                const Bits<N> bits( static_cast<Bits<N>::word_type>( i ) );
                for ( size_t k = 0; k < N; k++ )
                {
                    if ( bits.test( k ) )
                    {
                        BitsAccumulated++;
                    }
                }
            }
        }
        stopwatch.Stop( );
        double BitsDuration = stopwatch.Elapsed( ).TotalSeconds( );

        if ( StdBitsetAccumulated == BitsAccumulated )
        {
            double factor = StdBitsetDuration / BitsDuration;
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>  :%f seconds - factor: %f\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration, factor );
        }
        else
        {
            printf( "Error in %s\r\n\tstd::bitset<%zu> accumulated:%zu\r\n\tBits<%zu> accumulated:  %zu\r\n\r\n", testName, N, StdBitsetAccumulated, N, BitsAccumulated );
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>:  %f seconds\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration );
        }
    }

    template<size_t N>
    void RunBitsIndexTest( const char* testName, UInt64 outerIterationCount )
    {
        constexpr size_t MaxValue = Bits<N>::Mask;
        size_t StdBitsetAccumulated = 0;
        size_t BitsAccumulated = 0;
        Stopwatch stopwatch;
        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                const std::bitset<N> bits( i );
                for ( size_t k = 0; k < N; k++ )
                {
                    if ( bits[ k ] )
                    {
                        StdBitsetAccumulated++;
                    }
                }
            }
        }
        stopwatch.Stop( );
        double StdBitsetDuration = stopwatch.Elapsed( ).TotalSeconds( );
        stopwatch.Reset( );

        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                const Bits<N> bits( static_cast<Bits<N>::word_type>( i ) );
                for ( size_t k = 0; k < N; k++ )
                {
                    if ( bits[k] )
                    {
                        BitsAccumulated++;
                    }
                }
            }
        }
        stopwatch.Stop( );
        double BitsDuration = stopwatch.Elapsed( ).TotalSeconds( );

        if ( StdBitsetAccumulated == BitsAccumulated )
        {
            double factor = StdBitsetDuration / BitsDuration;
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>  :%f seconds - factor: %f\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration, factor );
        }
        else
        {
            printf( "Error in %s\r\n\tstd::bitset<%zu> accumulated:%zu\r\n\tBits<%zu> accumulated:  %zu\r\n\r\n", testName, N, StdBitsetAccumulated, N, BitsAccumulated );
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>:  %f seconds\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration );
        }
    }

    template<size_t N>
    void RunBitsFlipByIndexTest( const char* testName, UInt64 outerIterationCount )
    {
        constexpr size_t MaxValue = Bits<N>::Mask;
        size_t StdBitsetAccumulated = 0;
        size_t BitsAccumulated = 0;
        Stopwatch stopwatch;
        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                std::bitset<N> bits( i );
                for ( size_t k = 0; k < N; k++ )
                {
                    auto ref = bits[k];
                    ref = ref ? false : true;
                    if ( ref )
                    {
                        StdBitsetAccumulated++;
                    }
                }
            }
        }
        stopwatch.Stop( );
        double StdBitsetDuration = stopwatch.Elapsed( ).TotalSeconds( );
        stopwatch.Reset( );

        stopwatch.Start( );
        for ( size_t j = 0; j < outerIterationCount; j++ )
        {
            for ( size_t i = 0; i < MaxValue; i++ )
            {
                __declspec( align( 64 ) ) Bits<N> bits( static_cast<Bits<N>::word_type>( i ) );
                for ( size_t k = 0; k < N; k++ )
                {
                    __declspec( align( 64 ) ) auto ref = bits[k];
                    ref = ref ? false : true;
                    if ( ref )
                    {
                        BitsAccumulated++;
                    }
                }
            }
        }
        stopwatch.Stop( );
        double BitsDuration = stopwatch.Elapsed( ).TotalSeconds( );

        if ( StdBitsetAccumulated == BitsAccumulated )
        {
            double factor = StdBitsetDuration / BitsDuration;
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>  :%f seconds - factor: %f\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration, factor );
        }
        else
        {
            printf( "Error in %s\r\n\tstd::bitset<%zu> accumulated:%zu\r\n\tBits<%zu> accumulated:  %zu\r\n\r\n", testName, N, StdBitsetAccumulated, N, BitsAccumulated );
            printf( "%s\r\n\tstd::bitset<%zu>:%f seconds\r\n\tBits<%zu>:  %f seconds\r\n\r\n", testName, N, StdBitsetDuration, N, BitsDuration );
        }
    }

}
void RunBitsOperations( )
{
    //constexpr UInt64 OuterIterationCount = 1'000'000'000;
    constexpr UInt64 OuterIterationCount1 = 10'000'000;
    constexpr UInt64 OuterIterationCount2 = 10'000;
    constexpr UInt64 OuterIterationCount3 = 1;
    
    RunBitsAnyTest<7>( "RunBitsAnyTest<7>", OuterIterationCount1 );
    RunBitsAnyTest<8>( "RunBitsAnyTest<8>", OuterIterationCount1 );
    RunBitsAnyTest<9>( "RunBitsAnyTest<9>", OuterIterationCount1 );
    RunBitsAnyTest<15>( "RunBitsAnyTest<15>", OuterIterationCount2 );
    RunBitsAnyTest<16>( "RunBitsAnyTest<16>", OuterIterationCount2 );
    RunBitsAnyTest<17>( "RunBitsAnyTest<17>", OuterIterationCount2 );
    RunBitsAnyTest<32>( "RunBitsAnyTest<32>", OuterIterationCount3 );

    RunBitsNoneTest<7>( "RunBitsNoneTest<7>", OuterIterationCount1 );
    RunBitsNoneTest<8>( "RunBitsNoneTest<8>", OuterIterationCount1 );
    RunBitsNoneTest<9>( "RunBitsNoneTest<9>", OuterIterationCount1 );
    RunBitsNoneTest<15>( "RunBitsNoneTest<15>", OuterIterationCount2 );
    RunBitsNoneTest<16>( "RunBitsNoneTest<16>", OuterIterationCount2 );
    RunBitsNoneTest<17>( "RunBitsNoneTest<17>", OuterIterationCount2 );
    RunBitsNoneTest<32>( "RunBitsNoneTest<32>", OuterIterationCount3 );

    
    RunBitsAllTest<7>( "RunBitsAllTest<7>", OuterIterationCount1 );
    RunBitsAllTest<8>( "RunBitsAllTest<8>", OuterIterationCount1 );
    RunBitsAllTest<9>( "RunBitsAllTest<9>", OuterIterationCount1 );
    RunBitsAllTest<15>( "RunBitsAllTest<15>", OuterIterationCount2 );
    RunBitsAllTest<16>( "RunBitsAllTest<16>", OuterIterationCount2 );
    RunBitsAllTest<17>( "RunBitsAllTest<17>", OuterIterationCount2 );
    RunBitsAllTest<32>( "RunBitsAllTest<32>", OuterIterationCount3 );
    
    RunBitsCountTest<7>( "RunBitsCountTest<7>", OuterIterationCount1 );
    RunBitsCountTest<8>( "RunBitsCountTest<8>", OuterIterationCount1 );
    RunBitsCountTest<9>( "RunBitsCountTest<9>", OuterIterationCount1 );
    RunBitsCountTest<15>( "RunBitsCountTest<15>", OuterIterationCount2 );
    RunBitsCountTest<16>( "RunBitsCountTest<16>", OuterIterationCount2 );
    RunBitsCountTest<17>( "RunBitsCountTest<17>", OuterIterationCount2 );
    RunBitsCountTest<32>( "RunBitsCountTest<32>", OuterIterationCount3 );

    RunBitsTestTest<7>( "RunBitsTestTest<7>", OuterIterationCount1 );
    RunBitsTestTest<8>( "RunBitsTestTest<8>", OuterIterationCount1 );
    RunBitsTestTest<9>( "RunBitsTestTest<9>", OuterIterationCount1 );
    RunBitsTestTest<16>( "RunBitsTestTest<15>", OuterIterationCount2 );
    RunBitsTestTest<16>( "RunBitsTestTest<16>", OuterIterationCount2 );
    RunBitsTestTest<17>( "RunBitsTestTest<17>", OuterIterationCount2 );
    RunBitsTestTest<32>( "RunBitsTestTest<32>", OuterIterationCount3 );
   
    RunBitsIndexTest<7>( "RunBitsIndexTest<7>", OuterIterationCount1 );
    RunBitsIndexTest<8>( "RunBitsIndexTest<8>", OuterIterationCount1 );
    RunBitsIndexTest<9>( "RunBitsIndexTest<9>", OuterIterationCount1 );
    RunBitsIndexTest<15>( "RunBitsIndexTest<15>", OuterIterationCount2 );
    RunBitsIndexTest<16>( "RunBitsIndexTest<16>", OuterIterationCount2 );
    RunBitsIndexTest<17>( "RunBitsIndexTest<17>", OuterIterationCount2 );
    RunBitsIndexTest<32>( "RunBitsIndexTest<32>", OuterIterationCount3 );
    

    RunBitsFlipByIndexTest<7>( "RunBitsFlipByIndexTest<7>", OuterIterationCount1 );
    RunBitsFlipByIndexTest<8>( "RunBitsFlipByIndexTest<8>", OuterIterationCount1 );
    RunBitsFlipByIndexTest<9>( "RunBitsFlipByIndexTest<9>", OuterIterationCount1 );
    RunBitsFlipByIndexTest<15>( "RunBitsFlipByIndexTest<15>", OuterIterationCount2 );
    RunBitsFlipByIndexTest<16>( "RunBitsFlipByIndexTest<16>", OuterIterationCount2 );
    RunBitsFlipByIndexTest<17>( "RunBitsFlipByIndexTest<17>", OuterIterationCount2 );
    RunBitsFlipByIndexTest<32>( "RunBitsFlipByIndexTest<32>", OuterIterationCount3 );

}