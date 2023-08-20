// HCCVectorPerf02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <HCCVector.h>
#include <HCCDateTime.h>
#include <HCCString.h>
#include <ranges>

using namespace Harlinn::Common::Core;
namespace ranges = std::ranges;

struct SimpleType
{
    DateTime timeStamp_;
    Int64 flags_ = 0;
    double value_ = 0.0;
};


struct OldVectorTypes
{
    using ByteVector = OldVector<Byte>;
    using SimpleTypeVector = OldVector<SimpleType>;
};

struct NewVectorTypes
{
    using ByteVector = Vector<Byte>;
    using SimpleTypeVector = Vector<SimpleType>;
};

struct StdVectorTypes
{
    using ByteVector = std::vector<Byte>;
    using SimpleTypeVector = std::vector<SimpleType>;
};


template<typename VectorTypesT >
class PerformanceTest
{
public:
    using VectorTypes = VectorTypesT;
    using ByteVector = typename VectorTypes::ByteVector;
    using SimpleTypeVector = typename VectorTypes::SimpleTypeVector;
    constexpr static size_t Iterations = 100000;
    constexpr static size_t ByteVectorSize = 1000;
    constexpr static size_t SimpleTypeVectorSize = 1000;
private:
    WideString testName_;
    ByteVector byteVector1_;
    ByteVector byteVector2_;
    ByteVector byteVector3_;
    SimpleTypeVector simpleTypeVector1_;
    SimpleTypeVector simpleTypeVector2_;
    SimpleTypeVector simpleTypeVector3_;
public:
    

    PerformanceTest(const WideString& testName )
        : testName_( testName )
    { 
        byteVector1_.resize( ByteVectorSize );

        for ( size_t i = 0; i < ByteVectorSize; i++ )
        {
            byteVector1_[ i ] = static_cast< Byte >( i % 64 );
        }

        simpleTypeVector1_.resize( SimpleTypeVectorSize );
        auto now = DateTime::UtcNow();

        for ( size_t i = 0; i < SimpleTypeVectorSize; i++ )
        {
            auto& simpleValue = simpleTypeVector1_[ i ];

            simpleValue.timeStamp_ = now + TimeSpan::FromSeconds(static_cast<double>(i));
            simpleValue.flags_ = 1;
            simpleValue.value_ = static_cast<double>(i+1);

        }
    }



    bool AllOfByteVector( size_t iteration )
    {
        return std::all_of( byteVector1_.begin( ), byteVector1_.end( ), [ iteration ]( const auto& value ) { return value < static_cast< Byte >( iteration % 256 );  } );
    }

    bool AllOfSimpleTypeVector( size_t iteration )
    {
        return std::all_of( simpleTypeVector1_.begin( ), simpleTypeVector1_.end( ), [ iteration ]( const auto& value ) { return value.value_ < static_cast< double >( iteration % 256 );  } );
    }


    bool AnyOfByteVector( size_t iteration )
    {
        return std::any_of( byteVector1_.begin( ), byteVector1_.end( ), [ iteration ]( const auto& value ) { return value > static_cast< Byte >( iteration % 256 );  } );
    }

    bool AnyOfSimpleTypeVector( size_t iteration )
    {
        return std::any_of( simpleTypeVector1_.begin( ), simpleTypeVector1_.end( ), [ iteration ]( const auto& value ) { return value.value_ > static_cast< double >( SimpleTypeVectorSize );  } );
    }


    bool NoneOfByteVector( size_t iteration )
    {
        return std::none_of( byteVector1_.begin( ), byteVector1_.end( ), [ iteration ]( const auto& value ) { return value > static_cast< Byte >( iteration % 256 );  } );
    }
    bool NoneOfSimpleTypeVector( size_t iteration )
    {
        return std::none_of( simpleTypeVector1_.begin( ), simpleTypeVector1_.end( ), [ iteration ]( const auto& value ) { return value.value_ > static_cast< double >( SimpleTypeVectorSize );  } );
    }


    size_t ForEachByteVector( size_t iteration )
    {
        size_t result = 0;
        std::for_each( byteVector1_.begin( ), byteVector1_.end( ), [ &result, iteration ]( const auto& value )
            {
                if ( value > static_cast< Byte >( iteration % 256 ) )
                {
                    result++;
                }
            } );
        return result;
    }
    size_t ForEachSimpleTypeVector( size_t iteration )
    {
        size_t result = 0;
        std::for_each( simpleTypeVector1_.begin( ), simpleTypeVector1_.end( ), [ &result, iteration ]( const auto& value )
            {
                if ( value.value_ > static_cast< double >( SimpleTypeVectorSize ) )
                {
                    result++;
                }
            } );
        return result;
    }

    void EmplaceBackByteVector( size_t iteration )
    {
        byteVector2_.clear( );
        for ( const auto value : byteVector1_ )
        {
            byteVector2_.emplace_back( value );
        }
    }

    void EmplaceBackSimpleTypeVector( size_t iteration )
    {
        simpleTypeVector2_.clear( );
        for ( const auto& value : simpleTypeVector1_ )
        {
            simpleTypeVector2_.emplace_back( value );
        }
    }

    void InsertFrontByteVector( size_t iteration )
    {
        byteVector2_.clear( );
        for ( const auto value : byteVector1_ )
        {
            byteVector2_.insert( byteVector2_.begin(), value );
        }
    }

    void InsertFrontSimpleTypeVector( size_t iteration )
    {
        simpleTypeVector2_.clear( );
        for ( const auto& value : simpleTypeVector1_ )
        {
            simpleTypeVector2_.insert( simpleTypeVector2_.begin( ), value );
        }
    }

    void InsertBackByteVector( size_t iteration )
    {
        byteVector2_.clear( );
        for ( const auto value : byteVector1_ )
        {
            byteVector2_.insert( byteVector2_.end(), value );
        }
    }

    void InsertBackSimpleTypeVector( size_t iteration )
    {
        simpleTypeVector2_.clear( );
        for ( const auto& value : simpleTypeVector1_ )
        {
            simpleTypeVector2_.insert( simpleTypeVector2_.end( ), value );
        }
    }



    void Run( )
    {
        size_t counter = 0;
        Stopwatch stopwatch;
        stopwatch.Start( );

        for ( size_t i = 0; i < Iterations; i++ )
        {
            counter += AllOfByteVector( i + 1 ) ? 1 : 0;
            counter += AllOfSimpleTypeVector( i + 1 ) ? 1 : 0;

            counter += AnyOfByteVector( i + 1 ) ? 1 : 0;
            counter += AnyOfSimpleTypeVector( i + 1 ) ? 1 : 0;

            counter += NoneOfByteVector( i + 1 ) ? 1 : 0;
            counter += NoneOfSimpleTypeVector( i + 1 ) ? 1 : 0;


            counter += ForEachByteVector( i + 1 );
            counter += ForEachSimpleTypeVector( i + 1 );

            EmplaceBackByteVector( i + 1 );
            EmplaceBackSimpleTypeVector( i + 1 );

            InsertFrontByteVector( i + 1 );
            InsertFrontSimpleTypeVector( i + 1 );

            InsertBackByteVector( i + 1 );
            InsertBackSimpleTypeVector( i + 1 );
        }

        stopwatch.Stop( );

        auto duration = stopwatch.Elapsed( ).TotalSeconds( );

        auto message = Format( L"{} executed in {} seconds, counter = {}\n", testName_, duration, counter );
        fputws( message.c_str( ), stdout );

    }

};



int main()
{
    auto oldVectorTest = std::make_unique<PerformanceTest<OldVectorTypes>>( L"Old Vector" );
    oldVectorTest->Run( );

    auto newVectorTest = std::make_unique<PerformanceTest<NewVectorTypes>>( L"New Vector" );
    newVectorTest->Run( );

    auto stdVectorTest = std::make_unique<PerformanceTest<StdVectorTypes>>( L"std::vector" );
    stdVectorTest->Run( );

    return 0;
}

