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


#include <HCCEnvironment.h>
#include <HCCIO.h>
#include <HCCGuid.h>
#include <HCCCurrency.h>
#include <HTEngine.h>
#include <HCCApplication.h>

using namespace Harlinn;
using namespace Harlinn::Common::Core;

AnsiString GetDatabaseDir( )
{
    auto TestDataRoot = Environment::EnvironmentVariable( "HCC_TEST_DATA_ROOT" );
    auto directoryPath = IO::Path::Combine( TestDataRoot, "\\LMDB" );

    if ( IO::Directory::Exist( directoryPath ) == false )
    {
        IO::Directory::Create( directoryPath );
    }
    return directoryPath;
}

class Trade
{
    DateTime timestamp_;
    Int64 bidId_;
    Int64 offerId_;
    double volume_;
    Currency price_;
public:
    Trade( )
        : bidId_( 0 ), offerId_( 0 ), volume_( 0.0 )
    {
    }
    Trade( DateTime& timestamp, Int64 bidId, Int64 offerId, double volume, const Currency& price )
        : timestamp_( timestamp ), bidId_( bidId ), offerId_( offerId ), volume_( volume ), price_( price )
    {

    }

    Trade( DateTime& timestamp, const Currency& price )
        : timestamp_( timestamp ), bidId_( 123 ), offerId_( 456 ), volume_( 100 ), price_( price )
    {

    }

    void Assign( DateTime& timestamp, Int64 bidId, Int64 offerId, double volume, const Currency& price )
    {
        timestamp_ = timestamp; 
        bidId_ = bidId; 
        offerId_ = offerId; 
        volume_ = volume; 
        price_ = price;
    }

    constexpr const DateTime& Timestamp( ) const noexcept
    {
        return timestamp_;
    }
    void SetTimestamp( const DateTime& timestamp ) noexcept
    {
        timestamp_ = timestamp;
    }
    constexpr Int64 BidId( ) const noexcept
    {
        return bidId_;
    }
    void SetBidId( Int64 bidId ) noexcept
    {
        bidId_ = bidId;
    }
    constexpr Int64 OfferId( ) const noexcept
    {
        return offerId_;
    }
    void SetOfferId( Int64 offerId ) noexcept
    {
        offerId_ = offerId;
    }
    constexpr double Volume( ) const noexcept
    {
        return volume_;
    }
    void SetVolume( double volume ) noexcept
    {
        volume_ = volume;
    }
    constexpr const Currency& Price( ) const noexcept
    {
        return price_;
    }
    void SetPrice( const Currency& price ) noexcept
    {
        price_ = price;
    }
};

int main( )
{
    auto applicationOptions = std::make_shared<ApplicationOptions>( );
    applicationOptions->Load( );
    auto application = std::make_shared<Application>( applicationOptions );
    application->Start( );
#ifdef _DEBUG
    constexpr size_t NumberOfPoints = 30;
    using Engine = Timeseries::Engine<Trade, 6>;
    constexpr size_t TimeseriesCount = 4;
#else
    constexpr size_t NumberOfPoints = 100'000;
    using Engine = Timeseries::Engine<Trade>;
    constexpr size_t TimeseriesCount = 10'000;
#endif
    constexpr Currency price( 10 );

    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;

    auto DatabaseDir = GetDatabaseDir( );
    printf( "Database directory:%s\n", DatabaseDir.c_str( ) );

    Guid timeseriesId1 = Test::Ids[0];
    std::vector<Guid> timeseriesIds;
    for ( size_t i = 0; i < TimeseriesCount; ++i )
    {
        timeseriesIds.push_back( Test::Ids[i] );
    }

    Timeseries::TimeseriesEngineOptions options;
    options.DatabaseDirectory = DatabaseDir;
    options.Create = true;

    Engine engine( options );
    auto transaction = engine.BeginTransaction( );
    auto timeseriesCursor1 = transaction.OpenTimeseries( timeseriesId1 );


    Currency sumWritten;
    Stopwatch stopwatch;
    stopwatch.Start( );
    Trade trade;

    for ( size_t i = 0; i < NumberOfPoints; ++i )
    {
        for ( auto& timeseriesId : timeseriesIds )
        {
            timeseriesCursor1.ChangeTimeseries( timeseriesId );
            Int64 value = static_cast<Int64>( i + 1 );
            sumWritten += price;
            trade.SetTimestamp( DateTime( value ) );
            trade.SetPrice( price );
            timeseriesCursor1.Insert( trade );
        }
    }

    timeseriesCursor1.Close( );
    transaction.Commit( );
    stopwatch.Stop( );

    auto totalSeconds = stopwatch.Elapsed( ).TotalSeconds( );
    auto totalPoints = timeseriesIds.size( ) * NumberOfPoints;
    auto pointsPrSeconds = static_cast<double>( totalPoints ) / totalSeconds;
    printf( "Inserted %llu timeseries points into %zu timeseries in %f seconds\n\t - points pr. second: %f\n", totalPoints, TimeseriesCount, totalSeconds, pointsPrSeconds );

    Currency sumRead;
    stopwatch.Restart( );

    transaction = engine.BeginTransaction( LMDB::TransactionFlags::ReadOnly );
    auto timeseriesCursor2 = transaction.OpenTimeseries( timeseriesId1 );


    size_t totalRows = 0;
    for ( auto& timeseriesId : timeseriesIds )
    {
        timeseriesCursor2.ChangeTimeseries( timeseriesId );
        totalRows += timeseriesCursor2.ForEach( []( const Point& point, Currency& sumRead )
        {
            sumRead += point.Price( );
        }, sumRead );

    }



    timeseriesCursor2.Close( );
    transaction.Close( );

    totalSeconds = stopwatch.Elapsed( ).TotalSeconds( );
    pointsPrSeconds = static_cast<double>( totalRows ) / totalSeconds;
    printf( "Read  %llu timeseries points from %zu timeseries in %f seconds\n\t - points pr. second: %f\n", totalRows, TimeseriesCount, totalSeconds, pointsPrSeconds );
    printf( "Sum inserted:%lld,\n"
        "Sum read:    %lld\n", sumWritten.Value(), sumRead.Value( ) );

    application->Stop( );

}

