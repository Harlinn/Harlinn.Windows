#include <HCCDateTime.h>
#include <HCCString.h>
#include <span>

using namespace Harlinn::Common::Core;

struct A
{
    Byte data[1024];
    A( ) : data{ 0, } { }
    explicit A(Byte value ) : data{ value, } { }
};

struct B
{
    std::array<std::string, 1024> data;
    B( ) { }
    explicit B( const std::string& value ) { std::fill( data.begin( ), data.end( ), value ); }
};

struct C
{
    std::array<std::string_view, 1024> data;
    C( ) { }
    explicit C( const std::string_view& value ) { std::fill( data.begin( ), data.end( ), value ); }
};

struct D
{
    std::array<std::span<char>, 1024> data;
    D( ) {}
    explicit D( const std::span<char>& value ) { std::fill( data.begin( ), data.end( ), value ); }
};

#ifdef HCC_WITH_BASIC_STRING
struct E
{
    std::array<AnsiString, 1024> data;
    E( ) {}
    explicit E( const AnsiString& value ) { std::fill( data.begin( ), data.end( ), value ); }
};
#endif

template<typename T>
void TestMemcpy( size_t iterations, const T* source, T* target, size_t count )
{
    Stopwatch stopwatch;
    stopwatch.Start( );
    for ( size_t i = 0; i < iterations; i++ )
    {
        memcpy( target, source, count * sizeof( T ) );
    }
    stopwatch.Stop( );
    auto duration = stopwatch.TotalSeconds( );
    auto totalSize = iterations * sizeof( T ) * count;
    auto gigaPerSecond = ( totalSize / static_cast<double>(1024*1024*1024) ) / duration;
    printf("Memcpy duration: %f seconds, GB/s: %f\n", duration, gigaPerSecond );
}

template<typename T>
void TestStdCopy( size_t iterations, const T* source, T* target, size_t count )
{
    Stopwatch stopwatch;
    stopwatch.Start( );
    for ( size_t i = 0; i < iterations; i++ )
    {
        std::copy( source, source + count, target );
    }
    stopwatch.Stop( );
    auto duration = stopwatch.TotalSeconds( );
    auto totalSize = iterations * sizeof( T ) * count;
    auto gigaPerSecond = ( totalSize / static_cast<double>( 1024 * 1024 * 1024 ) ) / duration;
    printf( "std::copy duration: %f seconds, GB/s: %f\n", duration, gigaPerSecond );
}



std::string target1[1024];
byte        target2[1024 * sizeof( std::string )];
void Fidler()
{
    constexpr size_t sizeofStdString = sizeof( std::string );
    std::string source[1024];
    for ( int i = 0; i < 1024; i++ )
    {
        source[i] = std::to_string( std::rand()% 5000 );
    }
    const int N = 1000000;
    {
        Stopwatch stopwatch;
        stopwatch.Start( );
        for ( int i = 0; i < N; i++ )
        {
            std::copy( source, source + 1024, target1 );
        }
        stopwatch.Stop( );
        auto duration = stopwatch.TotalSeconds( );
        auto totalSize = N * 1024 * sizeofStdString;
        auto gigaPerSecond = ( totalSize / static_cast<double>( 1024 * 1024 * 1024 ) ) / duration;
        printf( "Fidler std::copy duration: %f seconds, GB/s: %f\n", duration, gigaPerSecond );
    }
    {
        Stopwatch stopwatch;
        stopwatch.Start( );
        for ( int i = 0; i < N; i++ )
        {
            memcpy( target2, source, sizeof( source ) );
        }
        stopwatch.Stop( );
        auto duration = stopwatch.TotalSeconds( );
        auto totalSize = N*1024* sizeofStdString;
        auto gigaPerSecond = ( totalSize / static_cast<double>( 1024 * 1024 * 1024 ) ) / duration;
        printf( "Fidler memcpy duration: %f seconds, GB/s: %f\n", duration, gigaPerSecond );
    }
}



int main()
{
    constexpr size_t Iterations1 = 100'000;
    constexpr size_t Iterations2 = 1'000;
    std::vector<A> sourceA;
    std::vector<A> targetA;
    sourceA.resize( 1024 );
    targetA.resize( 1024 );

    std::string s1( "text" );
    B b( s1 );
    std::vector<B> sourceB1;
    std::vector<B> targetB1;
    std::vector<B> sourceB2;
    std::vector<B> targetB2;
    sourceB1.resize( 1024, b );
    targetB1.resize( 1024 );
    sourceB2.resize( 1024, b );
    targetB2.resize( 1024 );

    std::string_view sv( s1 );
    C c( sv );
    std::vector<C> sourceC1;
    std::vector<C> targetC1;
    std::vector<C> sourceC2;
    std::vector<C> targetC2;
    sourceC1.resize( 1024, c );
    targetC1.resize( 1024 );
    sourceC2.resize( 1024, c );
    targetC2.resize( 1024 );

    constexpr bool string_view_is_safe = std::is_standard_layout_v<std::string_view>;

    std::span sp( s1.begin(), s1.end( ) );
    D d( sp );
    std::vector<D> sourceD1;
    std::vector<D> targetD1;
    std::vector<D> sourceD2;
    std::vector<D> targetD2;
    sourceD1.resize( 1024, d );
    targetD1.resize( 1024 );
    sourceD2.resize( 1024, d );
    targetD2.resize( 1024 );

#ifdef HCC_WITH_BASIC_STRING    
    AnsiString as1( "text" );
    E e( as1 );
    std::vector<E> sourceE2;
    std::vector<E> targetE2;
    sourceE2.resize( 1024, e );
    targetE2.resize( 1024 );
#endif


    TestMemcpy( Iterations1, sourceA.data(), targetA.data( ), 1024 );
    TestStdCopy( Iterations1, sourceA.data( ), targetA.data( ), 1024 );

    // not really safe, unless the string is small and the implementation
    // use small string optimization
    TestMemcpy( Iterations2, sourceB1.data( ), targetB1.data( ), 1024 );
    TestStdCopy( Iterations2, sourceB2.data( ), targetB2.data( ), 1024 );

    for ( auto& entry : targetB1 )
    {
        for ( auto& s2 : entry.data )
        {
            if ( s1 != s2 )
            {
                printf( "Something went wrong\n" );
            }
        }
    }
    TestMemcpy( Iterations2, sourceC1.data( ), targetC1.data( ), 1024 );
    TestStdCopy( Iterations2, sourceC2.data( ), targetC2.data( ), 1024 );

    TestMemcpy( Iterations2, sourceD1.data( ), targetD1.data( ), 1024 );
    TestStdCopy( Iterations2, sourceD2.data( ), targetD2.data( ), 1024 );
#ifdef HCC_WITH_BASIC_STRING
    TestStdCopy( Iterations2, sourceE2.data( ), targetE2.data( ), 1024 );
#endif

    Fidler( );

    return 0;

}

