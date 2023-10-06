#include <HCCGuid.h>
#include <HCCApplication.h>
#include <boost/uuid/uuid.hpp>
#include <boost/functional/hash.hpp>

using namespace Harlinn::Common::Core;

template<typename F, typename ...Args>
void PerformanceOf( const char* preamble, F testFunction, Args&&... args )
{
    using Seconds = std::chrono::duration<double, std::chrono::seconds::period>;

    auto start = std::chrono::high_resolution_clock::now( );

    auto testResult = testFunction( std::forward<Args>( args )... );
    auto end = std::chrono::high_resolution_clock::now( );
    auto testDuration = Seconds( end - start );
    printf( "%s %lld in %f seconds\n", preamble, testResult, testDuration.count( ) );
}



void CompareTest1()
{
#ifdef _DEBUG
    constexpr size_t IterationCount = 1000;
    constexpr size_t TestSize = 1'000;
#else
    constexpr size_t IterationCount = 100'000;
    constexpr size_t TestSize = 1'000'000;
#endif
    std::vector<Guid> guids;
    std::unordered_map<Guid, size_t> guidMap;
    guids.reserve( TestSize );
    std::vector<boost::uuids::uuid> uuids;
    std::unordered_map<boost::uuids::uuid, size_t, boost::hash<boost::uuids::uuid>> uuidMap;
    uuids.reserve( TestSize );
    for ( size_t i = 0; i < TestSize; ++i )
    {
        Guid newGuid = Guid::New( );
        guids.emplace_back( newGuid );
        guidMap.emplace( newGuid, i );
        uuids.emplace_back( *( ( boost::uuids::uuid* ) & newGuid ) );
        uuidMap.emplace( *( ( boost::uuids::uuid* ) & newGuid ), i );
    }

    std::sort( guids.begin( ), guids.end( ) );
    std::sort( uuids.begin( ), uuids.end( ) );

    const auto& lastGuid = guids.back( );
    const auto& lastUuid = uuids.back( );


    PerformanceOf( "Search Guid:", [&guids, &lastGuid]( )
    {
        size_t result = 0;
        for ( size_t i = 0; i < IterationCount; ++i )
        {

            auto it = std::find( guids.begin( ), guids.end( ), lastGuid );
            if ( it != guids.end( ) )
            {
                ++result;
            }
        }
        return result;
    } );
    PerformanceOf( "Search uuid:", [&uuids, &lastUuid]( )
    {
        size_t result = 0;
        for ( size_t i = 0; i < IterationCount; ++i )
        {

            auto it = std::find( uuids.begin( ), uuids.end( ), lastUuid );
            if ( it != uuids.end( ) )
            {
                ++result;
            }
        }
        return result;
    } );

    PerformanceOf( "Search Guid map:", [&guids, &guidMap]( )
    {
        size_t result = 0;
        for ( const auto& id : guids )
        {
            auto it = guidMap.find( id );
            if ( it != guidMap.end( ) )
            {
                result++;
            }
        }
        return result;
    } );

    PerformanceOf( "Search uuid map:", [&uuids, &uuidMap]( )
    {
        size_t result = 0;
        for ( const auto& id : uuids )
        {
            auto it = uuidMap.find( id );
            if ( it != uuidMap.end( ) )
            {
                result++;
            }
        }
        return result;
    } );



}


void CompareTest2( )
{
#ifdef _DEBUG
    constexpr size_t TestSize = 10'000;
#else
    constexpr size_t TestSize = 1'000'000;
#endif
    //constexpr size_t TestSize = 10;
    std::vector<Guid> guids;
    guids.reserve( TestSize );
    std::vector<boost::uuids::uuid> uuids;
    uuids.reserve( TestSize );

    for ( size_t i = 0; i < TestSize; ++i )
    {
        Guid newGuid = Guid::New( );
        guids.emplace_back( newGuid );
        uuids.emplace_back( *( ( boost::uuids::uuid* ) & newGuid ) );
    }

    std::sort( guids.begin( ), guids.end( ) );
    std::sort( uuids.begin( ), uuids.end( ) );

    std::array<GUID, TestSize>* p1 = ( std::array<GUID, TestSize>* )guids.data( );
    std::array<GUID, TestSize>* p2 = ( std::array<GUID, TestSize>* )uuids.data( );


    for ( size_t i = 0; i < TestSize; ++i )
    {
        if ( guids[i] != uuids[i] )
        {
            printf("Warning:Different sort order for Guid and uuid\n");
        }
    }


}



int main()
{
    auto options = std::make_shared<Harlinn::Common::Core::ApplicationOptions>( );
    options->Load( );
    Application application( options );
    application.Start( );
    CompareTest1( );
    CompareTest2( );
    application.Stop( );
}
