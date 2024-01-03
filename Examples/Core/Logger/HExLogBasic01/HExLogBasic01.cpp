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


#include <HCCLogging.h>
#include <HCCLoggerImpl.h>
#include <HCCApplication.h>

#include <HCCIO.h>
#include <HCCEnvironment.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Logging;


// The purpose of this application is to check the overhead of the logging operations.
// When the program is compiled as a release build, the impact of HCC_DEBUG loop should be completely eliminated,
// while the overhead of each HCC_ERROR should be 23-24 nano seconds.
//
// The multithreaded part should be monitored using Task Manager, or something similar. 
// 
// CPU utilization should be at 100% Until "Entering barrier" starts popping up on the display,
// This demonstrates that the synchronization overhead is *very* light, and should have 
// minimal impact on how the rest of the application operates.
// 
// At the end the program prints some statistics. 
//
int main( )
{
    auto options = std::make_shared<Harlinn::Common::Core::ApplicationOptions>( );
    options->Load( );
    auto application = std::make_shared<Application>( options );
    application->Start( );

    try
    {
#ifdef _DEBUG
        constexpr size_t Iterations = 20'000'000;
#else
        constexpr size_t Iterations = 2'000'000'000;
#endif

        constexpr Int32 intValue1 = 1;

        auto logManager = Logging::LogManager::Instance( );

        Stopwatch stopwatch;
        stopwatch.Start( );

        for ( size_t i = 0; i < Iterations; i++ )
        {
            HCC_DEBUG( "first:{}\n", intValue1 );
        }

        CurrentThread::FlushLogger( );
        stopwatch.Stop( );

        auto duration = stopwatch.TotalSeconds( );
        auto perSecond = Iterations / duration;
        auto average = duration / Iterations;
        auto messagesPosted = logManager->MessagesPosted( );

        printf( "Logged %zu DEBUG records in %f seconds. %f per second, Average %.9f seconds per record, Messages posted: %zu\n", Iterations, duration, perSecond, average, messagesPosted );

        
        auto statistics = logManager->Statistics( );


        stopwatch.Reset( );
        stopwatch.Start( );

        for ( size_t i = 0; i < Iterations; i++ )
        {
            HCC_ERROR( "first:{}\n", intValue1 );
        }

        CurrentThread::FlushLogger( );
        stopwatch.Stop( );

        duration = stopwatch.TotalSeconds( );
        perSecond = Iterations / duration;
        average = duration / Iterations;
        messagesPosted = logManager->MessagesPosted( );

        printf( "Logged %zu ERROR records in %f seconds. %f per second, Average %.9f seconds per record, Messages posted: %zu\n", Iterations, duration, perSecond, average, messagesPosted );

        statistics = logManager->Statistics( );

        
        size_t ThreadCount = Thread::HardwareConcurrency( );
        printf( "Logging on %zu threads\n", ThreadCount );
        SynchronizationBarrier barrier( ThreadCount + 1 );
        stopwatch.Reset( );
        stopwatch.Start( );

        for ( size_t i = 0; i < ThreadCount; ++i )
        {
            Thread thread( [&barrier ]()
                {
                    for ( size_t i = 0; i < Iterations; i++ )
                    {
                        HCC_ERROR( "first:{}\n", intValue1 );
                    }
                    CurrentThread::FlushLogger( );
                    puts( "Entering barrier" );
                    barrier.Enter( );
                } );
        }

        barrier.Enter( );
        stopwatch.Stop( );

        size_t ThreadedIterations = Iterations * ThreadCount;
        duration = stopwatch.TotalSeconds( );
        perSecond = ThreadedIterations / duration;
        average = duration / ThreadedIterations;
        messagesPosted = logManager->MessagesPosted( );

        printf( "Logged %zu ERROR records on %zu threads in %f seconds. %f per second, Average %.9f seconds per record\n", ThreadedIterations, ThreadCount, duration, perSecond, average );

        auto logManagerStatistics = logManager->Statistics( );
        auto logManagerStatisticsStr = ToAnsiString( logManagerStatistics );
        printf( "Statistics: %s\n", logManagerStatisticsStr.c_str( ) );

    }
    catch ( Exception& exception )
    {
        auto typeName = exception.TypeName( );
        auto message = exception.Message( );
        wprintf( L"Caught %s Exception\nMessage:%s\n", typeName.c_str( ), message.c_str( ) );
    }
    application->Stop( );

}


