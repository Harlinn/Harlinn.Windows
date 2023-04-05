#include <HTSegment.h>
#include <HTEngine.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn;
using namespace Harlinn::Common::Core;


namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

using Point = Timeseries::TimeseriesPoint;
using Overflow = std::optional<Point>;
using SegmentData = Timeseries::Segment<Point, 3>;


BOOST_FIXTURE_TEST_SUITE( SegmentTests, LocalFixture )

// --run_test=SegmentTests/SegmentDataInsertTest1
BOOST_AUTO_TEST_CASE( SegmentDataInsertTest1 )
{
    SegmentData segmentData;
    Point point1( DateTime( 1LL ) );
    Point point2( DateTime( 2LL ) );
    Point point3( DateTime( 3LL ) );
    Point point4( DateTime( 4LL ) );
    Overflow overflow;
    BOOST_CHECK( segmentData.empty( ) );
    segmentData.insert( point1, overflow );
    BOOST_CHECK( segmentData.empty( ) == false );
    BOOST_CHECK( segmentData.size( ) == 1 );
    BOOST_CHECK( overflow.has_value( ) == false );

    segmentData.insert( point2, overflow );
    BOOST_CHECK( segmentData.size( ) == 2 );
    BOOST_CHECK( overflow.has_value( ) == false );

    segmentData.insert( point4, overflow );
    BOOST_CHECK( segmentData.size( ) == 3 );
    BOOST_CHECK( overflow.has_value( ) == false );

    segmentData.insert( point3, overflow );
    BOOST_CHECK( overflow.has_value( ) );
    BOOST_CHECK( overflow.value( ) == point4 );
}

// --run_test=SegmentTests/SegmentDataInsertTest2
BOOST_AUTO_TEST_CASE( SegmentDataInsertTest2 )
{
    SegmentData segmentData;
    Point point1( DateTime( 1LL ) );
    Point point2( DateTime( 2LL ) );
    Point point3( DateTime( 3LL ) );
    Point point4( DateTime( 4LL ) );
    Overflow overflow;
    BOOST_CHECK( segmentData.empty( ) );
    segmentData.insert( point4, overflow );
    BOOST_CHECK( segmentData.empty( ) == false );
    BOOST_CHECK( segmentData.size( ) == 1 );
    BOOST_CHECK( overflow.has_value( ) == false );
    BOOST_CHECK( segmentData[0] == point4 );

    segmentData.insert( point2, overflow );
    BOOST_CHECK( segmentData.size( ) == 2 );
    BOOST_CHECK( overflow.has_value( ) == false );
    BOOST_CHECK( segmentData[0] == point2 );
    BOOST_CHECK( segmentData[1] == point4 );

    segmentData.insert( point3, overflow );
    BOOST_CHECK( segmentData.size( ) == 3 );
    BOOST_CHECK( overflow.has_value( ) == false );
    BOOST_CHECK( segmentData[0] == point2 );
    BOOST_CHECK( segmentData[1] == point3 );
    BOOST_CHECK( segmentData[2] == point4 );

    segmentData.insert( point1, overflow );
    BOOST_CHECK( segmentData.size( ) == 3 );
    BOOST_CHECK( overflow.has_value( ) );
    BOOST_CHECK( segmentData[0] == point1 );
    BOOST_CHECK( segmentData[1] == point2 );
    BOOST_CHECK( segmentData[2] == point3 );

    BOOST_CHECK( overflow.has_value( ) );
    BOOST_CHECK( overflow.value( ) == point4 );
}


// --run_test=SegmentTests/SegmentDataSearchTest1
BOOST_AUTO_TEST_CASE( SegmentDataSearchTest1 )
{
    SegmentData segmentData;
    auto result = segmentData.Search( DateTime( 1LL ) );

    BOOST_CHECK( result.IsEmpty( ) );

    Point point1( DateTime( 2LL ) );
    Point point2( DateTime( 4LL ) );
    Point point3( DateTime( 6LL ) );
    segmentData.insert( point1 );
    segmentData.insert( point2 );
    segmentData.insert( point3 );

    result = segmentData.Search( DateTime( 1LL ) );
    BOOST_CHECK( result.IsGreater( ) );
    BOOST_CHECK( segmentData[result.Index( )].Timestamp( ) == DateTime( 2LL ) );
    result = segmentData.Search( DateTime( 2LL ) );
    BOOST_CHECK( result.IsEqual( ) );
    BOOST_CHECK( segmentData[result.Index( )].Timestamp( ) == DateTime( 2LL ) );
    result = segmentData.Search( DateTime( 3LL ) );
    BOOST_CHECK( result.IsLess( ) );
    BOOST_CHECK( segmentData[result.Index( )].Timestamp( ) == DateTime( 2LL ) );
    result = segmentData.Search( DateTime( 4LL ) );
    BOOST_CHECK( result.IsEqual( ) );
    BOOST_CHECK( segmentData[result.Index( )].Timestamp( ) == DateTime( 4LL ) );
    result = segmentData.Search( DateTime( 5LL ) );
    BOOST_CHECK( result.IsLess( ) );
    BOOST_CHECK( segmentData[result.Index( )].Timestamp( ) == DateTime( 4LL ) );
    result = segmentData.Search( DateTime( 6LL ) );
    BOOST_CHECK( result.IsEqual( ) );
    BOOST_CHECK( segmentData[result.Index( )].Timestamp( ) == DateTime( 6LL ) );
    result = segmentData.Search( DateTime( 7LL ) );
    BOOST_CHECK( result.IsLess( ) );
    BOOST_CHECK( segmentData[result.Index( )].Timestamp( ) == DateTime( 6LL ) );

}



BOOST_AUTO_TEST_SUITE_END( )
