/*
   Copyright 2024-2026 Espen Harlinn

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

#include "pch.h"
#include "HCCList.h"
#include "HCCVector.h"

using namespace Harlinn::Common;
using namespace Harlinn::Common::Core;

template<typename T>
using small_vector = boost::container::small_vector<T, 4096>;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( )
        {
        }
        ~LocalFixture( )
        {
        }
    };

    enum class FooBarType
    {
        Number,
        Pointer
    };

    struct Foo
    { 
        FooBarType type = FooBarType::Number;
        union
        {
            double dbl;
            void* ptr;
        };
    };
    struct Bar
    {
        FooBarType type = FooBarType::Number;
        union
        {
            double dbl;
            void* ptr;
        };
        Bar( )
        {
        }
        ~Bar()
        { 
            if ( type == FooBarType::Pointer )
            {
                Byte* p = reinterpret_cast<Byte*>( ptr );
                delete[] p;
            }
        }
    };


    struct Baz : public std::enable_shared_from_this<Baz>
    {
        FooBarType type = FooBarType::Number;
        union
        {
            double dbl;
            void* ptr;
        };
    };


    struct Counted
    {
        static Int64 ctor;
        static Int64 dtor;
        FooBarType type;
        union
        {
            double dbl;
            void* ptr;
        };
        Counted( )
            : dbl(0.0)
        {
            ctor++;
        }
        Counted( const Counted& other )
            : dbl( other.dbl )
        {
            ctor++;
        }


        ~Counted( )
        {
            if ( type == FooBarType::Pointer )
            {
                Byte* p = reinterpret_cast<Byte*>( ptr );
                delete[] p;
            }
            dtor++;
        }
    };

    Int64 Counted::ctor = 0; 
    Int64 Counted::dtor = 0;

}




BOOST_FIXTURE_TEST_SUITE( ListTests, LocalFixture )


template<typename ContainerT>
double EmplaceBackContainerTestImpl( )
{
    constexpr int Iterations = 10000;
    constexpr int ItemCount = 100000;
    Stopwatch stopwatch;
    stopwatch.Start( );
    for ( int i = 0; i < Iterations; i++ )
    {
        ContainerT container;
        for ( int j = 0; j < ItemCount; j++ )
        {
            container.emplace_back( );
        }
        BOOST_CHECK( container.size() == ItemCount );
    }
    stopwatch.Stop( );
    return stopwatch.Elapsed( ).TotalSeconds( );
}


// --run_test=ListTests/EmplaceBackContainerTest1
BOOST_AUTO_TEST_CASE( EmplaceBackContainerTest1 )
{
    double duration = EmplaceBackContainerTestImpl<List<Foo>>( );
    printf( "List<Foo>:       %f seconds\n", duration );

    duration = EmplaceBackContainerTestImpl<List<Bar>>( );
    printf( "List<Bar>:       %f seconds\n", duration );

    duration = EmplaceBackContainerTestImpl<Vector<Foo>>( );
    printf( "Vector<Foo>:     %f seconds\n", duration );

    duration = EmplaceBackContainerTestImpl<Vector<Bar>>( );
    printf( "Vector<Bar>:     %f seconds\n", duration );

    
    duration = EmplaceBackContainerTestImpl<std::vector<Foo>>( );
    printf( "std::vector<Foo>:%f seconds\n", duration );

    duration = EmplaceBackContainerTestImpl<std::vector<Bar>>( );
    printf( "std::vector<Bar>:%f seconds\n", duration );

    duration = EmplaceBackContainerTestImpl<small_vector<Foo>>( );
    printf( "small_vector<Foo>:%f seconds\n", duration );

    duration = EmplaceBackContainerTestImpl<small_vector<Bar>>( );
    printf( "small_vector<Bar>:%f seconds\n", duration );


    /*
    duration = EmplaceBackContainerTestImpl<std::list<Foo>>( );
    printf( "std::list<Foo>:%f seconds\n", duration );

    duration = EmplaceBackContainerTestImpl<std::list<Bar>>( );
    printf( "std::list<Bar>:%f seconds\n", duration );
    */
}

// --run_test=ListTests/EmplaceBackContainerTest2
BOOST_AUTO_TEST_CASE( EmplaceBackContainerTest2 )
{
    Counted::ctor = 0;
    Counted::dtor = 0;
    double duration = EmplaceBackContainerTestImpl<List<Counted>>( );
    printf( "List<Counted>:  %f seconds\n", duration );
    if ( Counted::ctor != Counted::dtor )
    {
        printf( "Counted::ctor(%lld) != Counted::dtor(%lld)  \n", Counted::ctor, Counted::dtor );
    }

    Counted::ctor = 0;
    Counted::dtor = 0;
    duration = EmplaceBackContainerTestImpl<Vector<Counted>>( );
    printf( "Vector<Counted>:%f seconds\n", duration );
    if ( Counted::ctor != Counted::dtor )
    {
        printf( "Counted::ctor(%lld) != Counted::dtor(%lld)  \n", Counted::ctor, Counted::dtor );
    }

    
    Counted::ctor = 0;
    Counted::dtor = 0;
    duration = EmplaceBackContainerTestImpl<std::vector<Counted>>( );
    printf( "std::vector<Counted>:%f seconds\n", duration );
    if ( Counted::ctor != Counted::dtor )
    {
        printf( "Counted::ctor(%lld) != Counted::dtor(%lld)  \n", Counted::ctor, Counted::dtor );
    }

    Counted::ctor = 0;
    Counted::dtor = 0;
    duration = EmplaceBackContainerTestImpl<small_vector<Counted>>( );
    printf( "small_vector<Counted>:%f seconds\n", duration );
    if ( Counted::ctor != Counted::dtor )
    {
        printf( "Counted::ctor(%lld) != Counted::dtor(%lld)  \n", Counted::ctor, Counted::dtor );
    }

    /*
    Counted::ctor = 0;
    Counted::dtor = 0;
    duration = EmplaceBackContainerTestImpl<std::list<Counted>>( );
    printf( "std::list<Counted>:%f seconds\n", duration );
    if ( Counted::ctor != Counted::dtor )
    {
        printf( "Counted::ctor(%lld) != Counted::dtor(%lld)  \n", Counted::ctor, Counted::dtor );
    }
    */
}

template<typename ContainerT>
double EmplaceBackContainerTest3Impl( )
{
    constexpr int Iterations = 1000;
    constexpr int ItemCount = 100000;
    Stopwatch stopwatch;
    stopwatch.Start( );
    for ( int i = 0; i < Iterations; i++ )
    {
        ContainerT container;
        for ( int j = 0; j < ItemCount; j++ )
        {
            container.emplace_back( std::make_shared<Baz>( ) );
        }
        BOOST_CHECK( container.size( ) == ItemCount );
    }
    stopwatch.Stop( );
    return stopwatch.Elapsed( ).TotalSeconds( );
}


// --run_test=ListTests/EmplaceBackContainerTest3
BOOST_AUTO_TEST_CASE( EmplaceBackContainerTest3 )
{
    double duration = EmplaceBackContainerTest3Impl<List<std::shared_ptr<Baz>>>( );
    printf( "List<std::shared_ptr<Baz>>:        %f seconds\n", duration );

    duration = EmplaceBackContainerTest3Impl<Vector<std::shared_ptr<Baz>>>( );
    printf( "Vector<std::shared_ptr<Baz>>:      %f seconds\n", duration );

    duration = EmplaceBackContainerTest3Impl<std::vector<std::shared_ptr<Baz>>>( );
    printf( "std::vector<std::shared_ptr<Baz>>: %f seconds\n", duration );

    duration = EmplaceBackContainerTest3Impl<small_vector<std::shared_ptr<Baz>>>( );
    printf( "small_vector<std::shared_ptr<Baz>>:%f seconds\n", duration );
}



template<typename ContainerT>
std::pair<double,UInt64> IteratorContainerTestImpl1( )
{
    constexpr int OuterIterations = 500;
    constexpr int Iterations = 20;
    constexpr int ItemCount = 100000;
    UInt64 counted = 0;
    Stopwatch stopwatch;
    stopwatch.Start( );
    for ( int i = 0; i < OuterIterations; i++ )
    {
        ContainerT container;
        for ( int j = 0; j < ItemCount; j++ )
        {
            container.emplace_back( );
        }
        BOOST_CHECK( container.size( ) == ItemCount );
        auto itEnd = container.end( );
        for ( int j = 0; j < Iterations; j++ )
        {
            for( auto it = container.begin(); it != itEnd; ++it )
            {
                counted++;
            }
        }
    }
    stopwatch.Stop( );
    return { stopwatch.Elapsed( ).TotalSeconds( ), counted };
}

// --run_test=ListTests/IteratorContainerTest1
BOOST_AUTO_TEST_CASE( IteratorContainerTest1 )
{
    auto result = IteratorContainerTestImpl1<List<Foo>>( );
    printf( "List<Foo>:%f seconds,         count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl1<List<Bar>>( );
    printf( "List<Bar>:%f seconds,         count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl1<Vector<Foo>>( );
    printf( "Vector<Foo>:%f seconds,       count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl1<Vector<Bar>>( );
    printf( "Vector<Bar>:%f seconds,       count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl1<std::vector<Foo>>( );
    printf( "std::vector<Foo>:%f seconds,  count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl1<std::vector<Bar>>( );
    printf( "std::vector<Bar>:%f seconds,  count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl1<small_vector<Foo>>( );
    printf( "small_vector<Foo>:%f seconds, count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl1<small_vector<Bar>>( );
    printf( "small_vector<Bar>:%f seconds, count %llu\n", result.first, result.second );

}

template<typename ContainerT>
std::pair<double, UInt64> IteratorContainerTestImpl2( )
{
    constexpr int OuterIterations = 500;
    constexpr int Iterations = 20;
    constexpr int ItemCount = 100000;
    UInt64 counted = 0;
    Stopwatch stopwatch;
    stopwatch.Start( );
    for ( int i = 0; i < OuterIterations; i++ )
    {
        ContainerT container;
        for ( int j = 0; j < ItemCount; j++ )
        {
            container.emplace_back( );
        }
        BOOST_CHECK( container.size( ) == ItemCount );
        auto itEnd = container.end( );
        for ( int j = 0; j < Iterations; j++ )
        {
            for ( auto& entry : container )
            {
                counted++;
            }
        }
    }
    stopwatch.Stop( );
    return { stopwatch.Elapsed( ).TotalSeconds( ), counted };
}

// --run_test=ListTests/IteratorContainerTest2
BOOST_AUTO_TEST_CASE( IteratorContainerTest2 )
{
    auto result = IteratorContainerTestImpl2<List<Foo>>( );
    printf( "List<Foo>:%f seconds,         count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl2<List<Bar>>( );
    printf( "List<Bar>:%f seconds,         count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl2<Vector<Foo>>( );
    printf( "Vector<Foo>:%f seconds,       count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl2<Vector<Bar>>( );
    printf( "Vector<Bar>:%f seconds,       count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl2<std::vector<Foo>>( );
    printf( "std::vector<Foo>:%f seconds,  count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl2<std::vector<Bar>>( );
    printf( "std::vector<Bar>:%f seconds,  count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl2<small_vector<Foo>>( );
    printf( "small_vector<Foo>:%f seconds, count %llu\n", result.first, result.second );

    result = IteratorContainerTestImpl2<small_vector<Bar>>( );
    printf( "small_vector<Bar>:%f seconds, count %llu\n", result.first, result.second );


}


BOOST_AUTO_TEST_SUITE_END( )

