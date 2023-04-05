//#include <HCCLoggerStorageX.h>
#include <HCCLogging.h>
#include <HCCLoggerBackend.h>
#include <HCCApplication.h>

#include <HCCIO.h>
#include <HCCEnvironment.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Logging;

std::string GetLogDatabaseDir( )
{
    std::string TestDataRoot = Environment::EnvironmentVariable( "HCC_TEST_DATA_ROOT" );
    auto directoryPath = IO::Path::Append( TestDataRoot, "\\LogStorageTest" );

    if ( IO::Directory::Exist( directoryPath ) == false )
    {
        IO::Directory::Create( directoryPath );
    }
    return directoryPath;
}

#define USE_LOGGER 

int main( )
{
    ApplicationOptions options;
    Application application( options );
    application.Start( );

    try
    {
        constexpr size_t Iterations = 1'000'000'000;
        //constexpr size_t Iterations = 100;

        Logger<Writers::ConsoleWriter> consoleLogger(Level::Default);
        BackendLogger backendLogger( Level::Default, Backend::Instance( ) );


        HCC_DEBUG( consoleLogger, "Debug {}", 1 );
        HCC_INFO( consoleLogger, "Info {}", 1 );

        constexpr Int32 intValue1 = 1;
        constexpr Int32 intValue2 = 2;
        constexpr double dblValue1 = 3.0;
        constexpr double dblValue2 = 4.0;
        constexpr double dblValue3 = 5.0;
        constexpr double dblValue4 = 6.0;
        std::string strValue = "something";

        Stopwatch stopwatch;
        stopwatch.Start( );

        for ( size_t i = 0; i < Iterations; i++ )
        {
            // HCC_ERROR( backendLogger, "Level:{level}, Timestamp:{timestamp:%Y-%m-%d %H:%M:%S}, RDTSC:{rdtsc}, Thread:{thread}, first:{}, second:{}, third:{}\n", intValue1, intValue2, dblValue1 );
            // HCC_ERROR( backendLogger, "Level:{level}, Timestamp:{timestamp:%Y-%m-%d %H:%M:%S}, RDTSC:{rdtsc}, Thread:{thread}, first:{}, second:{}, third:{}\n", intValue1 );
            HCC_ERROR( *BackendLogger::Instance(), "first:{}\n", intValue1 );
            //HCC_ERROR( backendLogger, "Level:{level}, Timestamp:{timestamp:%Y-%m-%d %H:%M:%S}, RDTSC:{rdtsc}, Thread:{thread}, first:{}, second:{}, third:{}\n", strValue );
            //HCC_ERROR( backendLogger, "first:{}\n", strValue );
        }

        BackendLogger::Instance( )->Flush( );
        stopwatch.Stop( );

        auto duration = stopwatch.TotalSeconds( );
        auto perSecond = Iterations / duration;
        auto average = duration / Iterations;

        printf( "Logged %zu records in %f seconds. %f per second, Average %.9f seconds per record\n", Iterations, duration, perSecond, average );

    }
    catch ( Exception& exception )
    {
        auto typeName = exception.TypeName( );
        auto message = exception.Message( );
        wprintf( L"Caught %s Exception\nMessage:%s\n", typeName.c_str( ), message.c_str( ) );
    }
    application.Stop( );

}


/*
int main()
{
    try
    {
        constexpr size_t Iterations = 100'000'000;
        //constexpr size_t Iterations = 1'000;
        //constexpr size_t Iterations = 10;

        LoggerOptions loggerOptions;
        auto logger = std::make_unique< Logger<> >( loggerOptions );

        auto logDatabaseDir = GetLogDatabaseDir( );
        Log::Storage::LogDatabaseOptions logDatabaseOptions( logDatabaseDir, 500_gb );
        Log::Storage::LogDatabaseStore logDatabaseStore( logDatabaseOptions );

        auto& logDatabase = logDatabaseStore.Database( );
        auto session = logDatabase.CreateSession( );
        auto* logDataTable = session->GetLogDataTable( );

        size_t buffersInDatabase = 0;
        size_t recordsInDatabase = 0;
        if ( logDataTable->MoveFirst( ) )
        {

            do
            {
                buffersInDatabase++;
                auto* logBuffer = logDataTable->Value( );
                auto count = logBuffer->Count( );
                auto logRecord = logBuffer->First( );
                for ( UInt32 i = 0; i < count; ++i )
                {
                    Decoder decoder( logBuffer, logRecord );
                    recordsInDatabase++;
                    logRecord = decoder.Next( );
                }
            } while ( logDataTable->MoveNext( ) );
        }
        session.Reset( );
        logDataTable = nullptr;
        printf( "Log database initially contains %llu log records in %llu log buffers\n", recordsInDatabase, buffersInDatabase );

        //Log::ConsoleSink consoleSink;
        LogManager::Start( 1 );

        Stopwatch stopwatch;
        stopwatch.Start( );

        constexpr Int32 intValue1 = 1;
        constexpr Int32 intValue2 = 2;
        constexpr double dblValue1 = 3.0;
        constexpr double dblValue2 = 4.0;
        constexpr double dblValue3 = 5.0;
        constexpr double dblValue4 = 6.0;

        constexpr size_t ticksPerSecond = TimeSpan::TicksPerSecond * 100;
        constexpr size_t maxSeconds = UINT64_MAX / ticksPerSecond;
        constexpr size_t secondsPerYear = static_cast<size_t>( 24 * 60 * 6 * 3654 );
        constexpr size_t maxYears = maxSeconds / secondsPerYear;
        constexpr size_t endTime = 1970 + maxYears;

        if ( logger->IsErrorEnabled( ) )
        {
            printf( "Error enabled\n" );
        }

        auto sysClockNow = std::chrono::system_clock::now( );
        auto dateTimeNow = DateTime::UtcNow( );
        auto sysClockNowTicks = sysClockNow.time_since_epoch( ).count( );
        auto dateTimeNowTicks = dateTimeNow.Ticks( ) - DateTime::UnixEpoch;
        auto diffTicks = dateTimeNowTicks - sysClockNowTicks;


        for ( size_t i = 0; i < Iterations; i++ )
        {
            //logger->Error( "Level:{level}, Timestamp:{timestamp:%Y-%m-%d %H:%M:%S}, RDTSC:{rdtsc}, Thread:{thread}, first:{}, second:{}, third:{}\n", intValue1, intValue2, dblValue1 );
            HCC_ERROR( logger, "Level:{level}, Timestamp:{timestamp:%Y-%m-%d %H:%M:%S}, RDTSC:{rdtsc}, Thread:{thread}, first:{}, second:{}, third:{}\n", intValue1, intValue2, dblValue1 );
            //HCC_ERROR( logger, 1, intValue1, intValue2, dblValue1 );
            //HCC_ERROR( logger, "Level:{level}\n\tTimestamp:{timestamp:%Y-%m-%d %H:%M:%S}\n\tRDTSC:{rdtsc}\n\tThread:{thread}\n\tfirst:{}, second:{}, third:{}\n\tFile:{file}, Line:{line}\n\tFunction:{function}\n", intValue1, intValue2, dblValue1 );
            //HCC_DEBUG( logger, "Level:{level}\n\tTimestamp:{timestamp:%Y-%m-%d %H:%M:%S}\n\tRDTSC:{rdtsc}\n\tThread:{thread}\n\tfirst:{}, second:{}, third:{}\n\tFile:{file}, Line:{line}\n\tFunction:{function}\n", intValue1, intValue2, dblValue1 );
            //logger->Debug( "Level:{level}, Timestamp:{timestamp:%Y-%m-%d %H:%M:%S}, RDTSC:{rdtsc}, Thread:{thread}, first:{}, second:{}, third:{}\n", intValue1, intValue2, dblValue1 );
            //logger->Error( "{} {} {}", intValue1, intValue2, dblValue1, dblValue2, dblValue3, dblValue4 );
            //logger->Debug( 1, intValue1, intValue2, dblValue1, dblValue2, dblValue3, dblValue4 );
            //logger->Error( 1, intValue1, intValue2, dblValue1 );
        }
        logger->Flush( );

        stopwatch.Stop( );
        
        auto duration = stopwatch.TotalSeconds( );
        auto perSecond = Iterations / duration;
        auto average = duration / Iterations;

        printf( "Logged %zu records in %f seconds. %f per second, Average %.9f seconds per record\n", Iterations, duration, perSecond, average );

        puts( "Stopping and flushing logger" );
        stopwatch.Reset( );
        stopwatch.Start( );
        LogManager::Stop( );
        stopwatch.Stop( );
        duration = stopwatch.TotalSeconds( );
        printf( "Logger stopped and logs flushed in %f seconds.\n", duration );

        LogManagerStatistics logManagerStatistics;
        Log::LogManager::GetStatistics( logManagerStatistics );
        printf( "Log manager processed %llu log records from %llu log buffers\n", logManagerStatistics.RecordsProcessed, logManagerStatistics.BuffersProcessed );

        printf( "Log database sink processed %llu log records from %llu log buffers\n", logDatabaseStore.LogRecordCount(), logDatabaseStore.LogBufferCount() );

        session = logDatabase.CreateSession( );
        logDataTable = session->GetLogDataTable( );

        buffersInDatabase = 0;
        recordsInDatabase = 0;
        if ( logDataTable->MoveFirst( ) )
        {

            do
            {
                buffersInDatabase++;
                auto* logBuffer = logDataTable->Value( );
                auto count = logBuffer->Count( );
                auto logRecord = logBuffer->First( );
                for ( UInt32 i = 0; i < count; ++i )
                {
                    Decoder decoder( logBuffer, logRecord );
                    recordsInDatabase++;
                    logRecord = decoder.Next( );
                }
            } while ( logDataTable->MoveNext( ) );
        }
        printf( "Log database contains %llu log records in %llu log buffers\n", recordsInDatabase, buffersInDatabase );


        //Internal::LogArguments arguments( boolValue, byteValue );
    }
    catch ( Exception& exception )
    {
        auto typeName = exception.TypeName( );
        auto message = exception.Message( );
        wprintf( L"Caught %s Exception\nMessage:%s\n", typeName.c_str( ), message.c_str( ) );
    }


}
*/
