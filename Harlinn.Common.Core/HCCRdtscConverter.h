#pragma once
#ifndef __HCCRdtscConverter_h__
#define __HCCRdtscConverter_h__

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
        double rdtscFrequency_;
    public:
        RdtscConverter( const TimeSpan& callibrationTime = TimeSpan::FromMilliseconds(100) ) noexcept
            : callibrationTime_( callibrationTime ), rdtscStart_( 0 ), rdtscEnd_( 0 ), rdtscFrequency_( 0.0 )
        {
            Callibrate( );
        }
    private:
        void Callibrate( )
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
            rdtscFrequency_ = static_cast<double>( rdtscInterval ) / static_cast<double>( interval );
        }
    public:
        void Recallibrate( )
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

        static constexpr DateTime ToDateTime( UInt64 rdtsc, const DateTime& epoch, UInt64 rdtscEpoch, double rdtscFrequency ) noexcept
        {
            if ( rdtsc < rdtscEpoch )
            {
                Int64 rdtscOffset = static_cast<Int64>( rdtscEpoch - rdtsc );
                Int64 offset = static_cast<Int64>( rdtscOffset / rdtscFrequency );
                DateTime result( epoch.Ticks( ) - offset );
                return result;
            }
            else
            {
                Int64 rdtscOffset = static_cast<Int64>( rdtsc - rdtscEpoch );
                Int64 offset = static_cast<Int64>( rdtscOffset / rdtscFrequency );
                DateTime result( epoch.Ticks( ) + offset );
                return result;
            }
        }


        constexpr DateTime ToDateTime( UInt64 rdtsc ) const noexcept
        {
            return ToDateTime( rdtsc, start_, rdtscStart_, rdtscFrequency_ );
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
        constexpr UInt64 rdtscEnd( ) const noexcept
        {
            return rdtscEnd_;
        }

        constexpr double RdtscFrequency( ) const noexcept
        {
            return rdtscFrequency_;
        }


    };

}

#endif
