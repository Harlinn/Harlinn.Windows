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

#include "pch.h"
#include <HCCRanges.h>

using namespace Harlinn::Common;
using namespace Harlinn::Common::Core;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( )
        { }
        ~LocalFixture( )
        { }
    };


    struct Vertex
    {
        int Id = 0;

        auto operator<=>( const Vertex& ) const = default;

        template <typename CharT, typename Traits>
        friend std::basic_ostream<CharT, Traits>& operator<<( std::basic_ostream<CharT, Traits>& os, const Vertex& vertex )
        {
            if constexpr ( sizeof( CharT ) > 1 )
            {
                os << L"Vertex:{.Id=" << vertex.Id << L"} ";
            }
            else
            {
                os << "Vertex:{.Id=" << vertex.Id << "} ";
            }
            return os;
        }
    };



    struct Edge
    {
        int Id = 0;

        auto operator<=>( const Edge& ) const = default;

        template <typename CharT, typename Traits>
        friend std::basic_ostream<CharT, Traits>& operator<<( std::basic_ostream<CharT, Traits>& os, const Edge& edge )
        {
            if constexpr ( sizeof( CharT ) > 1 )
            {
                os << L"Edge:{.Id=" << edge.Id << L"} ";
            }
            else
            {
                os << "Edge:{.Id=" << edge.Id << "} ";
            }
            return os;
        }

    };


}

namespace std
{
    template<> struct hash<Vertex>
    {
        constexpr std::size_t operator()( const Vertex& vertex ) const noexcept
        {
            return static_cast<std::size_t>( vertex.Id ) << 32 | static_cast<std::size_t>( ReverseBits( vertex.Id ) );
        }
    };

    template<> struct hash<Edge>
    {
        constexpr std::size_t operator()( const Edge& edge ) const noexcept
        {
            return static_cast<std::size_t>( edge.Id ) << 32 | static_cast<std::size_t>( ReverseBits( edge.Id ) );
        }
    };
}

BOOST_FIXTURE_TEST_SUITE( ContainersTests, LocalFixture )

// --run_test=ContainersTests/ConstructorTest
BOOST_AUTO_TEST_CASE( ConstructorTest )
{
    using Vector = Ranges::Vector<Vertex>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };
    Vertex vertexThree{ .Id = 3 };

    Vector vector{ vertexOne, vertexTwo, vertexThree };
    auto equals = vector.Equals( vertexOne, vertexTwo, vertexThree );
    BOOST_CHECK( equals );
}

// --run_test=ContainersTests/AnyTest
BOOST_AUTO_TEST_CASE( AnyTest )
{
    using Vector = Ranges::Vector<Vertex>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };
    Vertex vertexThree{ .Id = 3 };

    Vector vector{ vertexOne, vertexTwo, vertexThree };
    auto expectTrue = vector.Any( [ ]( const auto& element )
                                  { 
                                      return element.Id == 3;
                                  } );
    BOOST_CHECK( expectTrue );

    auto expectFalse = vector.Any( [ ]( const auto& element )
                                  {
                                      return element.Id == 4;
                                  } );
    BOOST_CHECK( expectFalse == false );

}

// --run_test=ContainersTests/AllTest
BOOST_AUTO_TEST_CASE( AllTest )
{
    using Vector = Ranges::Vector<Vertex>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };
    Vertex vertexThree{ .Id = 3 };

    Vector vector{ vertexOne, vertexTwo, vertexThree };
    auto expectTrue = vector.All( [ ]( const auto& element )
                                  {
                                      return element.Id >= 1 && element.Id <= 3;
                                  } );
    BOOST_CHECK( expectTrue );

    auto expectFalse = vector.All( [ ]( const auto& element )
                                   {
                                       return element.Id >= 1 && element.Id <= 2;
                                   } );
    BOOST_CHECK( expectFalse == false );

}

// --run_test=ContainersTests/NoneTest
BOOST_AUTO_TEST_CASE( NoneTest )
{
    using Vector = Ranges::Vector<Vertex>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };
    Vertex vertexThree{ .Id = 3 };

    Vector vector{ vertexOne, vertexTwo, vertexThree };
    auto expectTrue = vector.None( [ ]( const auto& element )
                                  {
                                      return element.Id < 1 && element.Id > 3;
                                  } );
    BOOST_CHECK( expectTrue );

    auto expectFalse = vector.None( [ ]( const auto& element )
                                   {
                                       return element.Id >= 1 && element.Id <= 2;
                                   } );
    BOOST_CHECK( expectFalse == false );

}

// --run_test=ContainersTests/FirstTest
BOOST_AUTO_TEST_CASE( FirstTest )
{
    using Vector = Ranges::Vector<Vertex>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };
    Vertex vertexThree{ .Id = 3 };

    Vector vector{ vertexOne, vertexTwo, vertexThree };
    const auto& vertexTwoExpected = vector.First( [ ]( const auto& element )
                                   {
                                       return element.Id == 2;
                                   } );
    BOOST_CHECK_EQUAL( vertexTwoExpected.Id, 2 );

    const auto& vertexOneExpected = vector.First( [ ]( const auto& element )
    {
        return element.Id < 2;
    } );
    BOOST_CHECK_EQUAL( vertexOneExpected.Id, 1 );

    const auto& vertexThreeExpected = vector.First( [ ]( const auto& element )
    {
        return element.Id > 2;
    } );
    BOOST_CHECK_EQUAL( vertexThreeExpected.Id, 3 );


}


// --run_test=ContainersTests/LastTest
BOOST_AUTO_TEST_CASE( LastTest )
{
    using Vector = Ranges::Vector<Vertex>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };
    Vertex vertexThree{ .Id = 3 };

    Vector vector{ vertexOne, vertexTwo, vertexThree };
    const auto& vertexTwoExpected = vector.Last( [ ]( const auto& element )
    {
        return element.Id == 2;
    } );
    BOOST_CHECK_EQUAL( vertexTwoExpected.Id, 2 );

    const auto& vertexOneExpected = vector.Last( [ ]( const auto& element )
    {
        return element.Id < 2;
    } );
    BOOST_CHECK_EQUAL( vertexOneExpected.Id, 1 );

    const auto& vertexThreeExpected = vector.Last( [ ]( const auto& element )
    {
        return element.Id > 2;
    } );
    BOOST_CHECK_EQUAL( vertexThreeExpected.Id, 3 );


}

// --run_test=ContainersTests/SelectTest
BOOST_AUTO_TEST_CASE( SelectTest )
{
    using Vector = Ranges::Vector<Vertex>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };
    Vertex vertexThree{ .Id = 3 };

    Vector vector{ vertexOne, vertexTwo, vertexThree };
    auto expectTrue = vector.Select( [ ]( const auto& element )
    {
        return element.Id >= 2;
    } ).Equals( vertexTwo, vertexThree );

    BOOST_CHECK( expectTrue );
}

// --run_test=ContainersTests/SingleTest
BOOST_AUTO_TEST_CASE( SingleTest )
{
    using Vector = Ranges::Vector<Vertex>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };
    Vertex vertexThree{ .Id = 3 };

    Vector vector{ vertexOne, vertexTwo, vertexThree };

    auto& vertexTwoExpected = vector.Select( [ ]( const auto& e )
    {
        return e.Id >= 2;
    } )
        .Select( [ ]( const auto& e )
    {
        return e.Id < 3;
    } )
        .Single( );
    auto trueExpected2 = vertexTwoExpected == vertexTwo;
    BOOST_CHECK( trueExpected2 );

}





BOOST_AUTO_TEST_SUITE_END( )