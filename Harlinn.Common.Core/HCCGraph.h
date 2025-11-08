#pragma once
#ifndef HCCGRAPH_H_
#define HCCGRAPH_H_
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


#include "HCCRanges.h"

namespace Harlinn::Common::Core
{
    template<typename VertexT, typename EdgeT>
    class Graph
    {
    public:
        using VertexType = VertexT;
        using EdgeType = EdgeT;
        using VertexComparer = std::function<int(const VertexType&, const VertexType& )>;
        
        using VertexSet = Ranges::UnorderedSet<VertexType>;

        class Edge
        {
        public:
            using element_type = std::remove_extent_t<EdgeType>;
        private:
            element_type* payload_ = nullptr;
            bool requiresBatchingBoundary_ = false;
        public:

            Edge( )
            { }

            Edge( bool requiresBatchingBoundary )
                : requiresBatchingBoundary_( requiresBatchingBoundary )
            { }

            Edge( const EdgeType& payload )
                : payload_( const_cast<EdgeType*>( std::addressof( payload ) ) )
            { }
            Edge( const EdgeType& payload, bool requiresBatchingBoundary )
                : payload_( const_cast<EdgeType*>(std::addressof(payload)) ), requiresBatchingBoundary_( requiresBatchingBoundary )
            { }

            Edge( const Edge& other )
                : payload_( other.payload_ ), requiresBatchingBoundary_( other.requiresBatchingBoundary_ )
            { }
            Edge& operator = ( const Edge& other )
            {
                payload_ = other.payload_; 
                requiresBatchingBoundary_ = other.requiresBatchingBoundary_;
                return *this;
            }

            bool operator == ( const EdgeType& edgeType ) const
            {
                return *payload_ == edgeType;
            }

            bool operator != ( const EdgeType& edgeType ) const
            {
                return *payload_ != edgeType;
            }


            element_type* Payload( ) const
            {
                return payload_;
            }
            bool RequiresBatchingBoundary( ) const
            {
                return requiresBatchingBoundary_;
            }

            element_type& operator*( ) const noexcept
            {
                return *payload_;
            }

            element_type* operator->( ) const noexcept
            {
                return payload_;
            }

            template <typename CharT, typename Traits>
            friend std::basic_ostream<CharT, Traits>& operator<<( std::basic_ostream<CharT, Traits>& os, const Edge& edge )
            {
                if constexpr ( sizeof( CharT ) > 1 )
                {
                    if ( edge.Payload( ) )
                    {
                        const EdgeType& payload = *edge.Payload( );
                        os << L"Edge:{.Payload{" << payload << L"}, .RequiresBatchingBoundary{"<< edge.RequiresBatchingBoundary() << L"}";
                    }
                    else
                    {
                        os << L"Edge:{.Payload{nullptr}, .RequiresBatchingBoundary{" << edge.RequiresBatchingBoundary( ) << L"}";
                    }
                }
                else
                {
                    if ( edge.Payload( ) )
                    {
                        const EdgeType& payload = *edge.Payload( );
                        os << "Edge:{.Payload{" << payload << "}, .RequiresBatchingBoundary{" << edge.RequiresBatchingBoundary( ) << "}";
                    }
                    else
                    {
                        os << "Edge:{.Payload{nullptr}, .RequiresBatchingBoundary{" << edge.RequiresBatchingBoundary( ) << "}";
                    }
                }
                return os;
            }
        };

        //using EdgeList = boost::container::small_vector<Edge, 4>;
        using EdgeList = Ranges::Vector< Edge >;

        using EdgeMap = Ranges::UnorderedMap<VertexType, EdgeList>;
        using AdjacencyMap = Ranges::UnorderedMap<VertexType, EdgeMap>;
        
        using VertexList = Ranges::Vector< VertexType >;

        class Batch : public std::enable_shared_from_this<Batch>, public VertexList
        {
        public:
            using Base = VertexList;
            Batch( ) = default;
        };
        using BatchPointer = std::shared_ptr<Batch>;



        using ResultType = std::vector<BatchPointer>;
    private:
        using PredecessorCounts = std::unordered_map<VertexType, ssize_t>;

        std::optional<VertexComparer> secondarySortComparer_;
        VertexSet vertices_;

        AdjacencyMap successorMap_;
        AdjacencyMap predecessorMap_;
        const EdgeMap emptyEdgeMap;
        const EdgeList emptyEdgeList;
    public:
        Graph() 
        { }

        Graph( const VertexComparer& secondarySortComparer )
            : secondarySortComparer_( secondarySortComparer )
        { }

        void AddVertex( const VertexType& vertex )
        {
            vertices_.emplace( vertex );
        }
            
        template<SpanLike SpanT>
            requires std::is_convertible_v<typename SpanT::value_type,VertexType>
        void AddVertices( const SpanT& items )
        {
            for ( const auto& item : items )
            {
                VertexType vertex( item );
                if ( !vertices_.contains( vertex ) )
                {
                    vertices_.emplace( vertex );
                }
            }
        }

        void AddVertices( const std::initializer_list<VertexType>& items )
        {
            for ( const auto& item : items )
            {
                if ( !vertices_.contains( item ) )
                {
                    vertices_.emplace( item );
                }
            }
        }

        void AddEdge( const VertexType& from, const VertexType& to, const EdgeType& payload, bool requiresBatchingBoundary = false )
        {
#ifdef _DEBUG
            if ( !vertices_.contains( from ) )
            {
                
                throw InvalidOperationException( L"The graph does not contain the 'from' vertex." );
            }

            if ( !vertices_.contains( to ) )
            {
                throw InvalidOperationException( L"The graph does not contain the 'to' vertex." );
            }
#endif

            Edge edge( payload, requiresBatchingBoundary );
            auto fromIt = successorMap_.find( from );

            if ( fromIt == successorMap_.end( ) )
            {
                fromIt = successorMap_.emplace( from, EdgeMap( ) ).first;
            }
            EdgeMap& successorEdges = fromIt->second;
            auto successorEdgeIt = successorEdges.find( to );
            if ( successorEdgeIt == successorEdges.end( ) )
            {
                EdgeList edges( { edge } );
                successorEdges.emplace( to, std::move( edges ) );
            }
            else
            {
                successorEdgeIt->second.emplace_back( edge );
            }


            auto toIt = predecessorMap_.find( to );

            if ( toIt == predecessorMap_.end( ) )
            {
                toIt = predecessorMap_.emplace( to, EdgeMap( ) ).first;
            }
            EdgeMap& predecessorEdges = toIt->second;
            auto predecessorEdgeIt = predecessorEdges.find( from );
            if ( predecessorEdgeIt == predecessorEdges.end( ) )
            {
                EdgeList edges( { edge } );
                predecessorEdges.emplace( from, std::move( edges ) );
            }
            else
            {
                predecessorEdgeIt->second.emplace_back( edge );
            }
        }
        
        void RemoveEdge( const VertexType& from, const VertexType& to )
        {
            auto fromIt = successorMap_.find( from );
            if ( fromIt != successorMap_.end( ) )
            {
                EdgeMap& successorEdges = fromIt->second;
                successorEdges.erase( to );
            }

            auto toIt = predecessorMap_.find( to );
            if ( toIt != predecessorMap_.end( ) )
            {
                EdgeMap& predecessorEdges = toIt->second;
                predecessorEdges.erase( from );
            }
        }


        void Clear( )
        {
            vertices_.clear( );
            successorMap_.clear( );
            predecessorMap_.clear( );
        }

        const VertexSet& Vertices( ) const
        {
            return vertices_;
        }

        const EdgeList& GetEdges( const VertexType& from, const VertexType& to )
        {
            auto fromIt = successorMap_.find( from );

            if ( fromIt != successorMap_.end( ) )
            {
                auto toIt = fromIt->second.find( to );
                if ( toIt != fromIt->second.end( ) )
                {
                    return toIt->second;
                }
            }
            return emptyEdgeList;
        }

    private:
        bool AreEqual( const VertexType& first, const VertexType& second ) const
        {
            return first == second;
        }

        

        const EdgeMap& GetOutgoingNeighbors( const VertexType& from ) const
        {
            auto fromIt = successorMap_.find( from );

            if ( fromIt != successorMap_.end( ) )
            {
                return fromIt->second;
            }
            return emptyEdgeMap;
        }

        const EdgeMap& GetIncomingNeighbors( const VertexType& to ) const
        {
            auto toIt = predecessorMap_.find( to );

            if ( toIt != predecessorMap_.end( ) )
            {
                return toIt->second;
            }
            return emptyEdgeMap;
        }

        


        // Find a vertex in the unsorted portion of the graph that has edges to the candidate
        VertexType* GetIncomingNeighbor( const VertexType& candidateVertex, const PredecessorCounts& predecessorCounts ) const
        {
            const auto& incomingNeighbors = GetIncomingNeighbors( candidateVertex );

            for ( const auto& entry : incomingNeighbors )
            {
                auto it = predecessorCounts.find( entry.first );
                if ( it != predecessorCounts.end( ) )
                {
                    if ( it->second > 0 )
                    {
                        return const_cast<VertexType*>( &it->first );
                    }
                }
            }
            return nullptr;
        }

        const VertexType& GetCurrentCycleVertex( const PredecessorCounts& predecessorCounts ) const
        {
            for ( const auto& vertex : vertices_ )
            {
                auto it = predecessorCounts.find( vertex );
                if ( it != predecessorCounts.end( ) )
                {
                    if ( it->second != 0 )
                    {
                        return vertex;
                    }
                }
            }
            throw InvalidOperationException( );
        }


        bool CheckBatchingBoundary( bool withBatching, const VertexSet& currentBatchSet, const VertexType& vertex ) const
        {
            if ( withBatching )
            {
                auto predecessorIt = predecessorMap_.find( vertex );
                if ( predecessorIt != predecessorMap_.end( ) )
                {
                    const EdgeMap& predecessorEdges = predecessorIt->second;
                    for ( const auto& entry : predecessorEdges )
                    {
                        if ( entry.second.Any( [ ]( const auto& e )
                                               {
                                                   return e.RequiresBatchingBoundary( );
                                               } ) && currentBatchSet.contains( entry.first ) )
                        {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        
        /*
        void ThrowCycle( const VertexList& cycle, std::optional<std::function<std::string( const VertexType&, const VertexType&, const EdgeMap& )>> formatCycle, std::optional<std::function<std::string( const std::string& )>> formatException = {} )
        {
            WideString cycleString;
            if ( !formatCycle.has_value() )
            {
                cycleString = cycle.Select( [ ]( auto e )
                {
                    return ToString( e ) ).Join( L" ->" + Environment::NewLine;
                } );
            }
            else
            {
                auto currentCycleVertex = cycle.First( );
                auto cycleData = new List<Tuple<TVertex, TVertex, IEnumerable<TEdge>>>( );

                for( const auto& vertex : cycle.Skip( 1 ) )
                {
                    cycleData.Add( Tuple.Create( currentCycleVertex, vertex, GetEdges( currentCycleVertex, vertex ) ) );
                    currentCycleVertex = vertex;
                }

                cycleString = formatCycle( cycleData );
            }

            //var message = formatException == null ? CoreStrings.CircularDependency(cycleString) : formatException(cycleString);
            var message = $"Circular Dependency: {cycleString}";
            throw new InvalidOperationException( message );
        }
        */




        ResultType TopologicalSortCore(
            bool withBatching,
            std::optional<std::function<bool(const VertexType&, const VertexType&, const EdgeList& )>> canBreakEdges,
            std::optional<std::function<std::string( const VertexType&, const VertexType&, const EdgeMap& )>> formatCycle,
            std::optional<std::function<std::string( const std::string& )>> formatException = {} )
        {
            // Performs a breadth-first topological sort (Kahn's algorithm)
            ResultType result;
            VertexList currentRootsQueue;
            VertexList nextRootsQueue;
            size_t vertexesProcessed = 0;
            bool batchBoundaryRequired = false;
            auto currentBatch = std::make_shared<Batch>();
            VertexSet currentBatchSet;

            PredecessorCounts predecessorCounts;
            for( const auto& entry : predecessorMap_ )
            {
                if ( entry.second.size( ) )
                {
                    predecessorCounts[ entry.first ] = entry.second.size( );
                }
            }

            // Bootstrap the topological sort by finding all vertexes which have no predecessors
            for( const auto& vertex : vertices_ )
            {
                if ( !predecessorCounts.contains( vertex ) )
                {
                    currentRootsQueue.push_back( vertex );
                }
            }

            result.push_back( currentBatch );

            while ( vertexesProcessed < vertices_.size() )
            {
                while ( currentRootsQueue.size( ) > 0 )
                {
                    // Secondary sorting: after the first topological sorting (according to dependencies between the commands as expressed in
                    // the graph), we apply an optional secondary sort.
                    // When sorting modification commands, this ensures a deterministic ordering and prevents deadlocks between concurrent
                    // transactions locking the same rows in different orders.
                    if ( secondarySortComparer_.has_value() )
                    {
                        const auto& comp = secondarySortComparer_.value( );
                        std::sort( currentRootsQueue.begin( ), currentRootsQueue.end( ), [ &comp ](const auto& first, const auto& second )
                                   { 
                                       return comp( first, second ) < 0;
                                   } );
                    }

                    // If we detected in the last roots pass that a batch boundary is required, close the current batch and start a new one.
                    if ( batchBoundaryRequired )
                    {
                        currentBatch = std::make_shared<Batch>( );
                        result.push_back( currentBatch );
                        currentBatchSet.clear( );

                        batchBoundaryRequired = false;
                    }

                    for( const auto& currentRoot : currentRootsQueue )
                    {
                        currentBatch->push_back( currentRoot );
                        currentBatchSet.emplace( currentRoot );
                        vertexesProcessed++;

                        const auto& outgoingNeighbors = GetOutgoingNeighbors( currentRoot );
                        for( const auto& entry : outgoingNeighbors )
                        {
                            const auto& successor = entry.first;
                            predecessorCounts[ successor ]--;

                            // If the successor has no other predecessors, add it for processing in the next roots pass.
                            if ( predecessorCounts[ successor ] == 0 )
                            {
                                nextRootsQueue.emplace_back( successor );
                                if ( CheckBatchingBoundary( withBatching, currentBatchSet, successor ) )
                                {
                                    batchBoundaryRequired = true;
                                }
                            }
                        }
                    }

                    // Finished passing over the current roots, move on to the next set.
                    std::swap( currentRootsQueue, nextRootsQueue );
                    nextRootsQueue.clear( );
                }

                // We have no more roots to process. That either means we're done, or that there's a cycle which we need to break
                if ( vertexesProcessed < vertices_.size() )
                {
                    bool broken = false;

                    VertexList candidateVertices( predecessorCounts.size( ) );
                    for ( const auto& entry : predecessorCounts )
                    {
                        candidateVertices.emplace_back( entry.first );
                    }
                    
                    size_t candidateIndex = 0;

                    while ( ( candidateIndex < candidateVertices.size() )
                            && !broken
                            && canBreakEdges )
                    {
                        const auto& candidateVertex = candidateVertices[ candidateIndex ];
                        if ( predecessorCounts[ candidateVertex ] == 0 )
                        {
                            candidateIndex++;
                            continue;
                        }

                        auto* incomingNeighborPtr = GetIncomingNeighbor( candidateVertex, predecessorCounts );

                        if ( incomingNeighborPtr )
                        {
                            const auto& incomingNeighbor = *incomingNeighborPtr;
                            if ( canBreakEdges.value( )( incomingNeighbor, candidateVertex, GetEdges( incomingNeighbor, candidateVertex ) ) )
                            {
                                RemoveEdge( incomingNeighbor, candidateVertex );

                                predecessorCounts[ candidateVertex ]--;
                                if ( predecessorCounts[ candidateVertex ] == 0 )
                                {
                                    currentRootsQueue.push_back( candidateVertex );
                                    if ( CheckBatchingBoundary( withBatching, currentBatchSet, candidateVertex ) )
                                    {
                                        batchBoundaryRequired = true;
                                    }
                                    broken = true;
                                }

                                continue;
                            }
                        }

                        candidateIndex++;
                    }

                    if ( broken )
                    {
                        continue;
                    }

                    auto currentCycleVertex = GetCurrentCycleVertex( predecessorCounts );


                    VertexList cycle{ currentCycleVertex };
                    auto finished = false;
                    while ( !finished )
                    {
                        const auto& incomingNeighbors = GetIncomingNeighbors( currentCycleVertex );
                        for( const auto& entry : incomingNeighbors )
                        {
                            const auto& predecessor = entry.first;
                            auto it = predecessorCounts.find( predecessor );
                            if ( it == predecessorCounts.end( ) || it->second == 0 )
                            {
                                continue;
                            }

                            predecessorCounts[ currentCycleVertex ] = -1;
                            currentCycleVertex = predecessor;
                            cycle.emplace_back( currentCycleVertex );
                            finished = predecessorCounts[ predecessor ] == -1;
                            break;
                        }
                    }

                    std::ranges::reverse( cycle );

                    // Remove any tail that's not part of the cycle
                    auto startingVertex = cycle[ 0 ];
                    for ( ssize_t i = static_cast<ssize_t>(cycle.size()) - 1; i >= 0; i-- )
                    {
                        if ( AreEqual( cycle[ i ], startingVertex ) )
                        {
                            break;
                        }

                        cycle.erase( cycle.begin() + static_cast<size_t>( i ) );
                    }

                    //ThrowCycle( cycle, formatCycle, formatException );
                }
            }

            return result;

            
            
        }

    public:
        auto TopologicalSort( )
        {
            return TopologicalSortCore( false, {}, {}, {} );
        }

        auto TopologicalSort( std::optional<std::function<bool( const VertexType&, const VertexType&, const EdgeList& )>> canBreakEdges )
        {
            return TopologicalSortCore( false, canBreakEdges, {}, {} );
        }



    };
}

#endif
