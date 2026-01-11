#include <benchmark/benchmark.h>
#include <HCCString.h>

using namespace Harlinn::Common::Core;

static void BenchmarkStdWStringDefaultConstructor( benchmark::State& state )
{
    for ( auto _ : state )
    {
        std::wstring str;
        benchmark::DoNotOptimize( str );
    }
}
BENCHMARK( BenchmarkStdWStringDefaultConstructor );

static void BenchmarkWideStringDefaultConstructor( benchmark::State& state )
{
    for ( auto _ : state )
    {
        WideString str;
        benchmark::DoNotOptimize( str );
    }
}
BENCHMARK( BenchmarkWideStringDefaultConstructor );

const wchar_t* sampleText = L"The quick brown fox jumps over the lazy dog.";

static void BenchmarkStdWStringCStringConstructor( benchmark::State& state )
{
    for ( auto _ : state )
    {
        std::wstring str( sampleText );
        benchmark::DoNotOptimize( str );
    }
}
BENCHMARK( BenchmarkStdWStringCStringConstructor );

static void BenchmarkWideStringCStringConstructor( benchmark::State& state )
{
    for ( auto _ : state )
    {
        WideString str( sampleText );
        benchmark::DoNotOptimize( str );
    }
}
BENCHMARK( BenchmarkWideStringCStringConstructor );

static void BenchmarkStdWStringAppendChar( benchmark::State& state )
{
    for ( auto _ : state )
    {
        std::wstring str( sampleText );
        for ( size_t i = 0; i < 100; ++i )
        {
            str += L'A';
		}
        benchmark::DoNotOptimize( str );
    }
}
BENCHMARK( BenchmarkStdWStringAppendChar );

static void BenchmarkWideStringAppendChar( benchmark::State& state )
{
    for ( auto _ : state )
    {
        WideString str( sampleText );
        for ( size_t i = 0; i < 100; ++i )
        {
            str += L'A';
        }
        benchmark::DoNotOptimize( str );
    }
}
BENCHMARK( BenchmarkWideStringAppendChar );


static void BenchmarkStdWStringCopy( benchmark::State& state )
{
    std::wstring str( sampleText );
    for ( auto _ : state )
    {
        std::array<std::wstring, 100> copies;
        for ( size_t i = 0; i < 100; ++i )
        {
            copies[ i ] = str;
        }
        benchmark::DoNotOptimize( copies );
    }
}
BENCHMARK( BenchmarkStdWStringCopy );

static void BenchmarkWideStringCopy( benchmark::State& state )
{
    WideString str( sampleText );
    for ( auto _ : state )
    {
		std::array<WideString, 100> copies;
        for ( size_t i = 0; i < 100; ++i )
        {
			copies[ i ] = str;
        }
        benchmark::DoNotOptimize( copies );
    }
}
BENCHMARK( BenchmarkWideStringCopy );


template<typename StringType>
StringType ArgCopyReturn( const StringType& str )
{
	StringType result;
	result = str;
    return result;
}

static void BenchmarkStdWStringArgCopyReturn( benchmark::State& state )
{
    std::wstring str( sampleText );
    for ( auto _ : state )
    {
        auto str2 = ArgCopyReturn( str );
        benchmark::DoNotOptimize( str2 );
    }
}
BENCHMARK( BenchmarkStdWStringArgCopyReturn );

static void BenchmarkWideStringArgCopyReturn( benchmark::State& state )
{
    WideString str( sampleText );
    for ( auto _ : state )
    {
        auto str2 = ArgCopyReturn( str );
        benchmark::DoNotOptimize( str2 );
    }
}
BENCHMARK( BenchmarkWideStringArgCopyReturn );

template<typename StringType>
StringType ArgCopyReturn2( const StringType& str1, const StringType& str2 )
{
    StringType result;
    result = str1 + str2;
    return result;
}

static void BenchmarkStdWStringArgCopyReturn2( benchmark::State& state )
{
    std::wstring str( sampleText );
    for ( auto _ : state )
    {
        auto str2 = ArgCopyReturn2( str, str );
        benchmark::DoNotOptimize( str2 );
    }
}
BENCHMARK( BenchmarkStdWStringArgCopyReturn2 );

static void BenchmarkWideStringArgCopyReturn2( benchmark::State& state )
{
    WideString str( sampleText );
    for ( auto _ : state )
    {
        auto str2 = ArgCopyReturn2( str, str );
        benchmark::DoNotOptimize( str2 );
    }
}
BENCHMARK( BenchmarkWideStringArgCopyReturn2 );

template<typename StringType>
std::vector<StringType> ArgCopyReturn3( const StringType& str1, const StringType& str2 )
{
    std::vector<StringType> result;
	result.reserve( 100 );
    for ( size_t i = 0; i < 100; ++i )
    {
        result.push_back( str1 + str2 );
    }
    return result;
}

static void BenchmarkStdWStringArgCopyReturn3( benchmark::State& state )
{
    std::wstring str( sampleText );
    for ( auto _ : state )
    {
        auto vector = ArgCopyReturn3( str, str );
        benchmark::DoNotOptimize( vector );
    }
}
BENCHMARK( BenchmarkStdWStringArgCopyReturn3 );

static void BenchmarkWideStringArgCopyReturn3( benchmark::State& state )
{
    WideString str( sampleText );
    for ( auto _ : state )
    {
        auto vector = ArgCopyReturn3( str, str );
        benchmark::DoNotOptimize( vector );
    }
}
BENCHMARK( BenchmarkWideStringArgCopyReturn3 );






BENCHMARK_MAIN( );
