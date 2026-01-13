/*
   Copyright 2024-2025 Espen Harlinn

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

#include <benchmark/benchmark.h>
#include <HCCString.h>

using namespace Harlinn::Common::Core;

const wchar_t* sampleText = L"The quick brown fox jumps over the lazy dog.";

const wchar_t* longSampleText = LR"(
The quick brown fox jumps over the lazy dog. This expanded test string is designed to exercise
wide-character handling, buffer growth, and common text-processing code paths used in performance
benchmarks. It contains punctuation, numbers 0123456789, multiple spaces, a tab\tcharacter, and
mixed sentence lengths to better simulate real-world text. The content also includes examples of
file paths such as C:\Temp\sample.txt and URLs like https://example.com/path?query=1 to cover
typical tokenization cases. A few special symbols (© ™ ∑) are present to ensure non-ASCII
wchar_t values are handled correctly. Longer clauses are included to trigger reallocation and
copy behaviour: sequences of words, hyphenated-words-to-test-tokenization, repeated phrases,
and varied whitespace. Finally, a deterministic repeated tail is appended to reach the needed
length for buffering tests: Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod
tempor incididunt ut labore et dolore magna aliqua. Lorem ipsum dolor sit amet, consectetur.
)";

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

static void BenchmarkStdWStringAppendChar1( benchmark::State& state )
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
BENCHMARK( BenchmarkStdWStringAppendChar1 );

static void BenchmarkWideStringAppendChar1( benchmark::State& state )
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
BENCHMARK( BenchmarkWideStringAppendChar1 );


static void BenchmarkStdWStringAppendChar2( benchmark::State& state )
{
    std::wstring str1( sampleText );
    for ( auto _ : state )
    {
		auto str2 = str1;
		str2 += L'A';
        benchmark::DoNotOptimize( str2 );
    }
}
BENCHMARK( BenchmarkStdWStringAppendChar2 );

static void BenchmarkWideStringAppendChar2( benchmark::State& state )
{
    WideString str1( sampleText );
    for ( auto _ : state )
    {
        auto str2 = str1;
        str2 += L'A';
        benchmark::DoNotOptimize( str2 );
    }
}
BENCHMARK( BenchmarkWideStringAppendChar2 );


static void BenchmarkStdWStringAppendString1( benchmark::State& state )
{
    std::wstring str1( sampleText );
	std::wstring str2 = str1.substr( 0, str1.size() - 2 );
    for ( auto _ : state )
    {
		auto str = str1;
		str += str2;
        benchmark::DoNotOptimize( str );
    }
}
BENCHMARK( BenchmarkStdWStringAppendString1 );

static void BenchmarkWideStringAppendString1( benchmark::State& state )
{
    WideString str1( sampleText );
    WideString str2 = str1.substr( 0, str1.size() - 2 );
    for ( auto _ : state )
    {
        auto str = str1;
        str += str2;
        benchmark::DoNotOptimize( str );
    }
}
BENCHMARK( BenchmarkWideStringAppendString1 );


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


template<typename StringType>
StringType ArgCopyReturn4( const wchar_t c, const StringType& str2 )
{
    StringType result;
    result = c + str2;
    return result;
}

static void BenchmarkStdWStringArgCopyReturn4( benchmark::State& state )
{
	wchar_t c = L'A';
    std::wstring str( sampleText );
    for ( auto _ : state )
    {
        auto str2 = ArgCopyReturn4( c, str );
        benchmark::DoNotOptimize( str2 );
    }
}
BENCHMARK( BenchmarkStdWStringArgCopyReturn4 );

static void BenchmarkWideStringArgCopyReturn4( benchmark::State& state )
{
    wchar_t c = L'A';
    WideString str( sampleText );
    for ( auto _ : state )
    {
        auto str2 = ArgCopyReturn4( c, str );
        benchmark::DoNotOptimize( str2 );
    }
}
BENCHMARK( BenchmarkWideStringArgCopyReturn4 );


static void BenchmarkStdWStringFind1( benchmark::State& state )
{
    wchar_t c = L'A';
    std::wstring str( sampleText );
    for ( auto _ : state )
    {
        auto index = str.find( c );
        benchmark::DoNotOptimize( index );
    }
}
BENCHMARK( BenchmarkStdWStringFind1 );

static void BenchmarkWideStringFind1( benchmark::State& state )
{
    wchar_t c = L'A';
    WideString str( sampleText );
    for ( auto _ : state )
    {
        auto index = str.find( c );
        benchmark::DoNotOptimize( index );
    }
}
BENCHMARK( BenchmarkWideStringFind1 );

static void BenchmarkStdWStringFind2( benchmark::State& state )
{
    std::wstring str1( sampleText );
    std::wstring str2 = str1.substr( 0, str1.size( ) - 2 );
    for ( auto _ : state )
    {
        auto index = str1.find( str2 );
        benchmark::DoNotOptimize( index );
    }
}
BENCHMARK( BenchmarkStdWStringFind2 );

static void BenchmarkWideStringFind2( benchmark::State& state )
{
    WideString str1( sampleText );
    WideString str2 = str1.substr( 0, str1.size( ) - 2 );
    for ( auto _ : state )
    {
        auto index = str1.find( str2 );
        benchmark::DoNotOptimize( index );
    }
}
BENCHMARK( BenchmarkWideStringFind2 );


static void BenchmarkStdWStringFind3( benchmark::State& state )
{
    std::wstring str1( longSampleText );
    std::wstring str2 = L"https";
    for ( auto _ : state )
    {
        auto index = str1.find( str2 );
        benchmark::DoNotOptimize( index );
    }
}
BENCHMARK( BenchmarkStdWStringFind3 );

static void BenchmarkWideStringFind3( benchmark::State& state )
{
    WideString str1( longSampleText );
    WideString str2 = L"https";
    for ( auto _ : state )
    {
        auto index = str1.find( str2 );
        benchmark::DoNotOptimize( index );
    }
}
BENCHMARK( BenchmarkWideStringFind3 );




static void BenchmarkStdWStringSubstr1( benchmark::State& state )
{
	size_t index = 2;
    std::wstring str( sampleText );
    for ( auto _ : state )
    {
        auto substr = str.substr( index );
        benchmark::DoNotOptimize( substr );
    }
}
BENCHMARK( BenchmarkStdWStringSubstr1 );

static void BenchmarkWideStringSubstr1( benchmark::State& state )
{
    size_t index = 2;
    WideString str( sampleText );
    for ( auto _ : state )
    {
        auto substr = str.substr( index );
        benchmark::DoNotOptimize( substr );
    }
}
BENCHMARK( BenchmarkWideStringSubstr1 );

template<typename StringType>
bool AreEqual1( const StringType& str1, const StringType& str2 )
{
    return str1 == str2;
}

static void BenchmarkStdWStringAreEqual1( benchmark::State& state )
{
    std::wstring str( sampleText );
    for ( auto _ : state )
    {
        auto equal = AreEqual1( str, str );
        benchmark::DoNotOptimize( equal );
    }
}
BENCHMARK( BenchmarkStdWStringAreEqual1 );

static void BenchmarkWideStringAreEqual1( benchmark::State& state )
{
    WideString str( sampleText );
    for ( auto _ : state )
    {
        auto equal = AreEqual1( str, str );
        benchmark::DoNotOptimize( equal );
    }
}
BENCHMARK( BenchmarkWideStringAreEqual1 );

static void BenchmarkStdWStringAreEqual2( benchmark::State& state )
{
    std::wstring str1( sampleText );
    std::wstring str2 = str1.substr( 0, str1.size( ) - 2 );
    for ( auto _ : state )
    {
        auto equal = AreEqual1( str1, str2 );
        benchmark::DoNotOptimize( equal );
    }
}
BENCHMARK( BenchmarkStdWStringAreEqual2 );

static void BenchmarkWideStringAreEqual2( benchmark::State& state )
{
    WideString str1( sampleText );
    WideString str2 = str1.substr( 0, str1.size( ) - 2 );
    for ( auto _ : state )
    {
        auto equal = AreEqual1( str1, str2 );
        benchmark::DoNotOptimize( equal );
    }
}
BENCHMARK( BenchmarkWideStringAreEqual2 );


template<typename StringType>
StringType MyToUpper( const StringType& str )
{
    StringType upper_case = str;
    for ( auto& c : upper_case )
    {
        c = std::toupper( c );
    }
    return upper_case;
}

static void BenchmarkStdWStringToUpper1( benchmark::State& state )
{
    std::wstring str( sampleText );
    for ( auto _ : state )
    {
        auto upperCaseStr = MyToUpper( str );
        benchmark::DoNotOptimize( upperCaseStr );
    }
}
BENCHMARK( BenchmarkStdWStringToUpper1 );

static void BenchmarkWideStringToUpper1A( benchmark::State& state )
{
    WideString str( sampleText );
    for ( auto _ : state )
    {
        auto upperCaseStr = str.ToUpper( );
        benchmark::DoNotOptimize( upperCaseStr );
    }
}
BENCHMARK( BenchmarkWideStringToUpper1A );

static void BenchmarkWideStringToUpper1B( benchmark::State& state )
{
    WideString str( sampleText );
    for ( auto _ : state )
    {
        auto upperCaseStr = MyToUpper( str );
        benchmark::DoNotOptimize( upperCaseStr );
    }
}
BENCHMARK( BenchmarkWideStringToUpper1B );

static void BenchmarkStdWStringFormat1( benchmark::State& state )
{
    std::wstring str1( sampleText );
	double value = 3.14159;
    const wchar_t* arg1 = L"The art of debugging is figuring out what you really told your program to do rather than what you thought you told it to do.";
    for ( auto _ : state )
    {
        auto str2 = std::format(L"{} {} {}", value, str1, arg1);
        benchmark::DoNotOptimize( str2 );
    }
}
BENCHMARK( BenchmarkStdWStringFormat1 );

static void BenchmarkWideStringFormat1( benchmark::State& state )
{
    WideString str1( sampleText );
    double value = 3.14159;
    const wchar_t* arg1 = L"The art of debugging is figuring out what you really told your program to do rather than what you thought you told it to do.";

    for ( auto _ : state )
    {
        auto str2 = Format( L"{} {} {}", value, str1, arg1 );
        benchmark::DoNotOptimize( str2 );
    }
}
BENCHMARK( BenchmarkWideStringFormat1 );


static void BenchmarkStdWStringFormat2( benchmark::State& state )
{
    double value = 3.14159;
    for ( auto _ : state )
    {
        auto str = std::format( L"{}", value );
        benchmark::DoNotOptimize( str );
    }
}
BENCHMARK( BenchmarkStdWStringFormat2 );

static void BenchmarkWideStringFormat2( benchmark::State& state )
{
    double value = 3.14159;

    for ( auto _ : state )
    {
        auto str = Format( L"{}", value );
        benchmark::DoNotOptimize( str );
    }
}
BENCHMARK( BenchmarkWideStringFormat2 );

static void BenchmarkStdWStringFormat3( benchmark::State& state )
{
    std::wstring value( sampleText );
    for ( auto _ : state )
    {
        auto str = std::format( L"{}", value );
        benchmark::DoNotOptimize( str );
    }
}
BENCHMARK( BenchmarkStdWStringFormat3 );

static void BenchmarkWideStringFormat3( benchmark::State& state )
{
    WideString value( sampleText );

    for ( auto _ : state )
    {
        auto str = Format( L"{}", value );
        benchmark::DoNotOptimize( str );
    }
}
BENCHMARK( BenchmarkWideStringFormat3 );




BENCHMARK_MAIN( );
