#pragma once
#ifndef __HCCRdtscConverter_h__
#define __HCCRdtscConverter_h__
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

#include <HCCThread.h>


namespace Harlinn::Common::Core
{
    class RdtscConverter
    {
        TimeSpan callibrationTime_;
        DateTime start_;
        DateTime end_;
        UInt64 rdtscStart_;
        UInt64 rdtscEnd_;
        UInt64 rdtscCyclesPerTick_;
    public:
        RdtscConverter( const TimeSpan& callibrationTime = TimeSpan::FromMilliseconds(200) ) noexcept
            : callibrationTime_( callibrationTime ), rdtscStart_( 0 ), rdtscEnd_( 0 ), rdtscCyclesPerTick_( 0 )
        {
            Calibrate( );
        }
    private:
        void Calibrate( )
        {
            Int64 ftStart, ftEnd;
            unsigned int ui = 0;
            auto initialPriority = CurrentThread::Priority( );
            CurrentThread::SetPriority( ThreadPriority::TimeCritical );

            WaitableTimer waitableTimer( false, true );
            waitableTimer.SetTimer( TimeSpan::FromMilliseconds( 10 ), callibrationTime_ );
            waitableTimer.Wait( );
            GetSystemTimePreciseAsFileTime( (LPFILETIME)&ftStart );
            rdtscStart_ = __rdtscp( &ui );

            waitableTimer.Wait( );
            GetSystemTimePreciseAsFileTime( (LPFILETIME)&ftEnd );
            rdtscEnd_ = __rdtscp( &ui );

            CurrentThread::SetPriority( initialPriority );

            start_ = DateTime::FromFileTime( ftStart );
            end_ = DateTime::FromFileTime( ftEnd );

            UInt64 interval = ftEnd - ftStart;

            UInt64 rdtscInterval = rdtscEnd_ - rdtscStart_;
            rdtscCyclesPerTick_ = rdtscInterval / interval;
        }
    public:
        void Recalibrate( )
        {
            Int64 ftNow;
            unsigned int ui = 0;

            auto initialPriority = CurrentThread::Priority( );
            CurrentThread::SetPriority( ThreadPriority::TimeCritical );
            GetSystemTimePreciseAsFileTime( (LPFILETIME)&ftNow );
            UInt64 rdtscNow = __rdtscp( &ui );
            CurrentThread::SetPriority( initialPriority );

            start_ = end_;
            end_ = DateTime::FromFileTime( ftNow );
            rdtscStart_ = rdtscEnd_;
            rdtscEnd_ = rdtscNow;
        }

        static constexpr DateTime ToDateTime( UInt64 rdtsc, const DateTime& epoch, UInt64 rdtscEpoch, UInt64 rdtscCyclesPerTick ) noexcept
        {
            if ( rdtsc < rdtscEpoch )
            {
                Int64 rdtscOffset = static_cast<Int64>( rdtscEpoch - rdtsc );
                Int64 offset = static_cast<Int64>( rdtscOffset / rdtscCyclesPerTick );
                DateTime result( epoch.Ticks( ) - offset );
                return result;
            }
            else
            {
                Int64 rdtscOffset = static_cast<Int64>( rdtsc - rdtscEpoch );
                Int64 offset = static_cast<Int64>( rdtscOffset / rdtscCyclesPerTick );
                DateTime result( epoch.Ticks( ) + offset );
                return result;
            }
        }


        constexpr DateTime ToDateTime( UInt64 rdtsc ) const noexcept
        {
            return ToDateTime( rdtsc, start_, rdtscStart_, rdtscCyclesPerTick_ );
        }

        constexpr const DateTime& Start( ) const noexcept
        {
            return start_;
        }
        constexpr const DateTime& End( ) const noexcept
        {
            return end_;
        }

        constexpr UInt64 RdtscStart( ) const noexcept
        {
            return rdtscStart_;
        }
        constexpr UInt64 RdtscEnd( ) const noexcept
        {
            return rdtscEnd_;
        }

        constexpr UInt64 RdtscCyclesPerTick( ) const noexcept
        {
            return rdtscCyclesPerTick_;
        }


    };

}

#endif
