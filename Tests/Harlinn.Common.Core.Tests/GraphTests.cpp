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
#include <HCCGraph.h>

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


BOOST_FIXTURE_TEST_SUITE( GraphTests, LocalFixture )

// --run_test=GraphTests/AddOne
BOOST_AUTO_TEST_CASE( AddOne )
{
    using GraphType = Graph<Vertex, Edge>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{. Id = 2 };

    GraphType graph;

    graph.AddVertex( vertexOne );
    graph.AddVertex( vertexTwo );

    const auto& vertices = graph.Vertices( );
    BOOST_CHECK_EQUAL( vertices.size(), 2 );
    BOOST_CHECK( vertices.contains( vertexOne ) );
    BOOST_CHECK( vertices.contains( vertexTwo ) );

}

// --run_test=GraphTests/AddVertices
BOOST_AUTO_TEST_CASE( AddVertices )
{
    using GraphType = Graph<Vertex, Edge>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };
    Vertex vertexThree{ .Id = 3 };
    Vertex vertexFour{ .Id = 4 };

    GraphType graph;

    graph.AddVertices( std::vector<Vertex>{ vertexOne, vertexTwo } );
    graph.AddVertices( std::vector<Vertex>{ vertexThree, vertexFour } );

    const auto& vertices = graph.Vertices( );
    BOOST_CHECK_EQUAL( vertices.size( ), 4 );
    BOOST_CHECK( vertices.contains( vertexOne ) );
    BOOST_CHECK( vertices.contains( vertexTwo ) );
    BOOST_CHECK( vertices.contains( vertexThree ) );
    BOOST_CHECK( vertices.contains( vertexFour ) );

}

// --run_test=GraphTests/AddEdge
BOOST_AUTO_TEST_CASE( AddEdge )
{
    using GraphType = Graph<Vertex, Edge>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };

    Edge edgeOne{ .Id = 1 };
    Edge edgeTwo{ .Id = 2 };

    GraphType graph;

    graph.AddVertices( { vertexOne, vertexTwo } );

    graph.AddEdge( vertexOne, vertexTwo, edgeOne );
    graph.AddEdge( vertexOne, vertexTwo, edgeTwo );


    const auto& vertices = graph.Vertices( );
    
    const auto& twoToOneEdges = graph.GetEdges( vertexTwo, vertexOne );
    BOOST_CHECK_EQUAL( twoToOneEdges.size( ), 0 );

    const auto& oneToTwoEdges = graph.GetEdges( vertexOne, vertexTwo );
    BOOST_CHECK_EQUAL( oneToTwoEdges.size( ), 2 );
    BOOST_CHECK_EQUAL( oneToTwoEdges[ 0 ], edgeOne );
    BOOST_CHECK_EQUAL( oneToTwoEdges[ 1 ], edgeTwo );
}

// --run_test=GraphTests/TopologicalSortOnGraphWithNoEdges
BOOST_AUTO_TEST_CASE( TopologicalSortOnGraphWithNoEdges )
{
    using GraphType = Graph<Vertex, Edge>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };
    Vertex vertexThree{ .Id = 3 };

    GraphType graph;

    graph.AddVertices( { vertexOne, vertexTwo, vertexThree } );

    auto batches = graph.TopologicalSort( );
    BOOST_CHECK_EQUAL( 1, batches.size( ) );
    const auto& result = *batches.front( );
    BOOST_CHECK_EQUAL( 3, result.size( ) );
    
    auto success = result.ContainsAllOf( vertexOne, vertexTwo, vertexThree );
    BOOST_CHECK( success );
}


// --run_test=GraphTests/TopologicalSortOnGraphWithTwoEdges
BOOST_AUTO_TEST_CASE( TopologicalSortOnGraphWithTwoEdges )
{
    using GraphType = Graph<Vertex, Edge>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };
    Vertex vertexThree{ .Id = 3 };

    Edge edgeOne{ .Id = 1 };
    Edge edgeTwo{ .Id = 2 };

    GraphType graph;

    graph.AddVertices( { vertexOne, vertexTwo, vertexThree } );

    graph.AddEdge( vertexTwo, vertexOne, edgeOne );
    
    graph.AddEdge( vertexOne, vertexThree, edgeTwo );

    auto batches = graph.TopologicalSort( );
    BOOST_CHECK_EQUAL( 1, batches.size( ) );
    const auto& result = *batches.front( );
    BOOST_CHECK_EQUAL( 3, result.size( ) );

    auto success = result.Equals( vertexTwo, vertexOne, vertexThree );
    BOOST_CHECK( success );
}


// --run_test=GraphTests/TopologicalSortOnGraphWithTwoEdges
BOOST_AUTO_TEST_CASE( TopologicalSortOnGraphCanBreakTwoCycles )
{
    using GraphType = Graph<Vertex, Edge>;
    Vertex vertexOne{ .Id = 1 };
    Vertex vertexTwo{ .Id = 2 };
    Vertex vertexThree{ .Id = 3 };
    Vertex vertexFour{ .Id = 4 };
    Vertex vertexFive{ .Id = 5 };


    Edge edgeOne{ .Id = 1 };
    Edge edgeTwo{ .Id = 2 };
    Edge edgeThree{ .Id = 3 };
    Edge edgeFour{ .Id = 4 };
    Edge edgeFive{ .Id = 5 };
    Edge edgeSix{ .Id = 6 };


    GraphType graph;

    graph.AddVertices( { vertexOne, vertexTwo, vertexThree, vertexFour, vertexFive } );

    // 1 -> {2, 4}
    graph.AddEdge( vertexOne, vertexTwo, edgeOne );
    graph.AddEdge( vertexOne, vertexFour, edgeTwo );
    // 2 -> {3}
    graph.AddEdge( vertexTwo, vertexThree, edgeThree );
    // 3 -> {1}
    graph.AddEdge( vertexThree, vertexOne, edgeFour );
    // 4 -> {5}
    graph.AddEdge( vertexFour, vertexFive, edgeFive );
    // 5 -> {1}
    graph.AddEdge( vertexFive, vertexOne, edgeSix );

    auto batches = graph.TopologicalSort( [& ]( const auto& from, const auto& to, const auto& edges ) -> bool
                                          {
                                              const auto& edge = *edges[0];
                                              return ( edge == edgeOne ) || ( edge == edgeSix );

                                          } );
    BOOST_CHECK_EQUAL( 1, batches.size( ) );
    const auto& result = *batches.front( );
    BOOST_CHECK_EQUAL( 5, result.size( ) );

    auto success = result.Equals( vertexTwo, vertexThree, vertexOne, vertexFour, vertexFive );
    BOOST_CHECK( success );
}






BOOST_AUTO_TEST_SUITE_END( )