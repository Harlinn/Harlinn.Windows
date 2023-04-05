#include <HCCDateTime.h>
#include <HCCBtree.h>
#include <HCCBtree2.h>
#include <HCCMemory.h>
#include <HCCTsEngine.h>

using namespace Harlinn::Common::Core;
using TimeseriesPoint = Harlinn::Common::Core::Timeseries::TimeseriesPoint;


using MapType = std::unordered_map<DateTime, TimeseriesPoint >;

struct DateTimeComparer : public Harlinn::Common::Core::BTree::btree_key_compare_to_tag 
{
    int operator()(const DateTime& a, const DateTime& b) const 
    {
        return a.CompareTo(b);
    }
};

using BTree1MapType = BTree::map<DateTime, TimeseriesPoint, DateTimeComparer >;

struct DateTimeCompare
{
    constexpr int operator ()( const DateTime& first, const DateTime& second )
    {
        return first.CompareTo( second );
    }
};

using BTreeT = Harlinn::Common::Core::BTree2::BTreeImpl<DateTime, TimeseriesPoint, DateTimeCompare, 254,126>;


void Fill( DateTime fromTimestamp, DateTime toTimestamp, TimeSpan interval, MapType& result )
{
    while ( fromTimestamp < toTimestamp )
    {
        result.emplace( fromTimestamp, TimeseriesPoint( fromTimestamp, 0, 1.0 ) );
        fromTimestamp += interval;
    }
}

void Fill( DateTime fromTimestamp, DateTime toTimestamp, TimeSpan interval, BTree1MapType& result )
{
    while ( fromTimestamp < toTimestamp )
    {
        result.emplace( fromTimestamp, TimeseriesPoint( fromTimestamp, 0, 1.0 ) );
        fromTimestamp += interval;
    }
}


void Fill( DateTime fromTimestamp, DateTime toTimestamp, TimeSpan interval, BTreeT& result )
{
    while ( fromTimestamp < toTimestamp )
    {
        result.emplace( fromTimestamp, TimeseriesPoint( fromTimestamp, 0, 1.0 ) );
        fromTimestamp += interval;
    }
}


size_t PointPerIteration( )
{
    DateTime startDateTime( 2010, 1, 1 );
    DateTime endDateTime( 2015, 1, 1 );
    TimeSpan resolution = TimeSpan::FromMinutes( 1 );

    return ( endDateTime.Ticks( ) - startDateTime.Ticks( ) ) / resolution.Ticks( );
}

void RunUnorderedMap( int iterations )
{
    DateTime startDateTime( 2010, 1, 1 );
    DateTime endDateTime( 2015, 1, 1 );
    TimeSpan resolution = TimeSpan::FromMinutes( 1 );
    for ( int i = 0; i < iterations; i++ )
    {
        MapType dict;
        Fill( startDateTime, endDateTime, resolution, dict );
    }
}

void RunBTree1Map( int iterations )
{
    DateTime startDateTime( 2010, 1, 1 );
    DateTime endDateTime( 2015, 1, 1 );
    TimeSpan resolution = TimeSpan::FromMinutes( 1 );
    for ( int i = 0; i < iterations; i++ )
    {
        BTree1MapType btree;
        Fill( startDateTime, endDateTime, resolution, btree );
    }
}



int main()
{

    Stopwatch stopwatch;
    stopwatch.Start( );
    RunBTree1Map( 5 );
    stopwatch.Stop( );
    auto duration = stopwatch.TotalSeconds( );
    auto pointPerIteration = PointPerIteration( );
    printf( "Size %zu, Duration %f seconds\n", pointPerIteration, duration );
}
