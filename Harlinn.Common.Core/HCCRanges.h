#pragma once
#ifndef HCCCONTAINERS_H_
#define HCCCONTAINERS_H_

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

#include <HCCString.h>

namespace Harlinn::Common::Core::Ranges
{
    template<std::ranges::viewable_range RangeT>
    class All;

    template <std::ranges::range RangeT>
        requires std::is_object_v<RangeT>
    class RefView;

    template <std::ranges::range RangeT>
        requires ( std::movable<RangeT> && !IsInitializerList<RangeT> )
    class OwningView;

    template <std::ranges::input_range RangeT>
        requires std::ranges::view<RangeT>
    class AsRValueView;

    template <std::ranges::input_range RangeT, std::indirect_unary_predicate<std::ranges::iterator_t<RangeT>> PredicateT>
        requires std::ranges::view<RangeT>&& std::is_object_v<PredicateT>
    class FilterView;


    namespace Internal
    {
        


        template<typename DerivedT, typename RangeT>
        class RangeBase : public RangeT
        {
        public:
            using Base = RangeT;
            using DerivedType = DerivedT;

            using value_type = std::ranges::range_value_t<Base>;
            using iterator = std::ranges::iterator_t<Base>;
            using const_iterator = std::ranges::const_iterator_t<Base>;
            using reference = std::ranges::range_reference_t<Base>;
            using const_reference = std::ranges::range_const_reference_t<Base>;

            RangeBase()
                requires std::is_default_constructible_v<Base>
                : Base()
            { }

            template<typename ...Args>
                requires std::is_constructible_v<Base,Args...>
            RangeBase(Args&& ... args )
                : Base(std::forward<Args>(args)...)
            { }

            RangeBase( std::initializer_list<value_type> items )
                requires std::is_constructible_v<Base, std::initializer_list<value_type> >
                : Base( std::move( items ) )
            { }
        

            template<typename FuncT>
            bool Any( FuncT func )
            {
                auto& self = static_cast<DerivedType&>( *this );
                auto it = std::find_if( self.begin( ), self.end( ), func );
                return it != self.end( );
            }

            template<typename FuncT>
            bool Any( FuncT func ) const
                requires std::ranges::range<const DerivedType>
            {
                const auto& self = static_cast<const DerivedType&>( *this );
                auto it = std::find_if( self.cbegin( ), self.cend( ), func );
                return it != self.end( );
            }

            template<typename Self, std::ranges::forward_range RangeT>
            bool ContainsAnyOf( this Self& self, const RangeT& range )
            {
                return self.Any( [ &range ]( const auto& element )
                { 
                    auto it = std::ranges::find( range, element );
                    return it != range.end( );
                } );
            }

            template<typename ... Args>
                requires std::conjunction_v<std::is_same<Args, value_type>...>
            bool ContainsAnyOf( const Args& ... args )
            {
                if ( sizeof...( args ) > 0 )
                {
                    auto& self = static_cast<DerivedType&>( *this );
                    auto beginIt = self.begin( );
                    auto endIt = self.end( );
                    if ( beginIt != endIt )
                    {
                        return ( ( std::find( beginIt, endIt, args ) != endIt ) || ... );
                    }
                    else
                    {
                        return false;
                    }

                }
                return true;
            }

            template<typename ... Args>
                requires std::conjunction_v<std::is_same<Args, value_type>...> && std::ranges::range<const DerivedType>
            bool ContainsAnyOf( const Args& ... args ) const
            {
                if ( sizeof...( args ) > 0 )
                {
                    const auto& self = static_cast<const DerivedType&>( *this );
                    auto beginIt = self.cbegin( );
                    auto endIt = self.cend( );
                    if ( beginIt != endIt )
                    {
                        return ( ( std::find( beginIt, endIt, args ) != endIt ) || ... );
                    }
                    else
                    {
                        return false;
                    }

                }
                return true;
            }



            template<typename FuncT>
            bool All( FuncT func )
            {
                auto& self = static_cast<DerivedType&>( *this );
                auto it = self.begin( );
                auto endIt = self.end( );
                for ( ; it != endIt; ++it )
                {
                    if ( func( *it ) == false )
                    {
                        return false;
                    }
                }
                return true;
            }

            template<typename FuncT>
            bool All( FuncT func ) const
                requires std::ranges::range<const DerivedType>
            {
                const auto& self = static_cast<const DerivedType&>( *this );
                auto it = self.cbegin( );
                auto endIt = self.cend( );
                for ( ; it != endIt; ++it )
                {
                    if ( func( *it ) == false )
                    {
                        return false;
                    }
                }
                return true;
            }

            template<typename Self, std::ranges::forward_range RangeT>
            bool ContainsAllOf(this Self& self, const RangeT& range )
            {
                return self.All( [ &range ]( const auto& element )
                {
                    auto it = std::ranges::find( range, element );
                    return it != range.end( );
                } );
            }


            template<typename ... Args>
                requires std::conjunction_v<std::is_same<Args, value_type>...>
            bool ContainsAllOf( const Args& ... args )
            {
                if ( sizeof...( args ) > 0)  
                {
                    auto& self = static_cast<DerivedType&>( *this );
                    auto beginIt = self.begin( );
                    auto endIt = self.end( );
                    if ( beginIt != endIt )
                    {
                        return ( ( std::find( beginIt, endIt, args ) != endIt ) && ... );
                    }
                    else
                    {
                        return false;
                    }
                }
                return true;
            }

            template<typename ... Args>
                requires std::conjunction_v<std::is_same<Args, value_type>...> && std::ranges::range<const DerivedType>
            bool ContainsAllOf( const Args& ... args ) const
            {
                if ( sizeof...( args ) > 0 )
                {
                    const auto& self = static_cast<const DerivedType&>( *this );
                    auto beginIt = self.cbegin( );
                    auto endIt = self.cend( );
                    if ( beginIt != endIt )
                    {
                        return ( ( std::find( beginIt, endIt, args ) != endIt ) && ... );
                    }
                    else
                    {
                        return false;
                    }
                }
                return true;
            }


            template<typename FuncT>
            bool None( FuncT func ) 
            {
                auto& self = static_cast<DerivedType&>( *this );
                auto it = self.begin( );
                auto endIt = self.end( );
                for ( ; it != endIt; ++it )
                {
                    if ( func( *it ) )
                    {
                        return false;
                    }
                }
                return true;
            }

            template<typename FuncT>
                requires std::ranges::range<const DerivedType>
            bool None( FuncT func ) const
            {
                const auto& self = static_cast<const DerivedType&>( *this );
                auto it = self.cbegin( );
                auto endIt = self.cend( );
                for ( ; it != endIt; ++it )
                {
                    if ( func( *it ) )
                    {
                        return false;
                    }
                }
                return true;
            }

            template<typename Self, std::ranges::forward_range RangeT>
            bool ContainsNoneOf(this Self& self, const RangeT& range )
            {
                return self.None( [ &range ]( const auto& element )
                {
                    auto it = std::ranges::find( range, element );
                    return it != range.end( );
                } );
            }


            template<typename ... Args>
                requires std::conjunction_v<std::is_same<Args, value_type>...>
            bool ContainsNoneOf( const Args& ... args )
            {
                if ( sizeof...( args ) > 0 )
                {
                    auto& self = static_cast<DerivedType&>( *this );
                    auto beginIt = self.begin( );
                    auto endIt = self.end( );
                    if ( beginIt != endIt )
                    {
                        return ( ( std::find( beginIt, endIt, args ) == endIt ) && ... );
                    }
                    else
                    {
                        return true;
                    }
                }
                return true;
            }

            template<typename ... Args>
                requires std::conjunction_v<std::is_same<Args, value_type>...> && std::ranges::range<const DerivedType>
            bool ContainsNoneOf( const Args& ... args ) const
            {
                if ( sizeof...( args ) > 0 )
                {
                    const auto& self = static_cast<const DerivedType&>( *this );
                    auto beginIt = self.cbegin( );
                    auto endIt = self.cend( );
                    if ( beginIt != endIt )
                    {
                        return ( ( std::find( beginIt, endIt, args ) == endIt ) && ... );
                    }
                    else
                    {
                        return true;
                    }
                }
                return true;
            }


            template<typename FuncT>
            reference First(FuncT func )
            {
                auto& self = static_cast<DerivedType&>( *this );
                auto beginIt = self.begin( );
                auto endIt = self.end( );
                auto it = std::find_if( beginIt, endIt, func );
                if ( it != endIt )
                {
                    return *it;
                }
                throw InvalidOperationException( );
            }

            template<typename FuncT>
            const_reference First( FuncT func ) const
                requires std::ranges::range<const DerivedType>
            {
                auto& self = static_cast<const DerivedType&>( *this );
                auto beginIt = self.cbegin( );
                auto endIt = self.cend( );
                auto it = std::find_if( beginIt, endIt, func );
                if ( it != endIt )
                {
                    return *it;
                }
                throw InvalidOperationException( );
            }

            reference First( )
            {
                auto& self = static_cast<DerivedType&>( *this );

                auto beginIt = self.begin( );
                auto endIt = self.end( );
                if ( beginIt != endIt )
                {
                    return *beginIt;
                }
                throw InvalidOperationException( );
            }

            const_reference First( ) const
                requires std::ranges::range<const DerivedType>
            {
                const auto& self = static_cast<const DerivedType&>( *this );

                auto beginIt = self.cbegin( );
                auto endIt = self.cend( );
                if ( beginIt != endIt )
                {
                    return *beginIt;
                }
                throw InvalidOperationException( );
            }

            reference Single()
            {
                auto& self = static_cast<DerivedType&>( *this );

                auto beginIt = self.begin( );
                auto endIt = self.end( );
                if ( beginIt != endIt )
                {
                    auto it = beginIt;
                    ++it;
                    if ( it == endIt )
                    {
                        return *beginIt;
                    }
                }
                throw InvalidOperationException( );
            }

            const_reference Single( ) const
                requires std::ranges::range<const DerivedType>
            {
                auto& self = static_cast<const DerivedType&>( *this );

                auto beginIt = self.cbegin( );
                auto endIt = self.cend( );
                if ( beginIt != endIt )
                {
                    auto it = beginIt;
                    ++it;
                    if ( it == endIt )
                    {
                        return *beginIt;
                    }
                }
                throw InvalidOperationException( );
            }


        

            template<typename FuncT>
                requires (std::is_same_v<FuncT,value_type> == false && std::is_same_v<FuncT, iterator> == false && std::is_same_v<FuncT, const_iterator> == false && std::ranges::range<const DerivedType> )
            const_iterator Find( FuncT func ) const
            {
                const auto& self = static_cast<const DerivedType&>( *this );
                return std::find_if( self.cbegin( ), self.cend( ), func );
            }
            template<typename FuncT>
                requires ( std::is_same_v<FuncT, value_type> == false && std::is_same_v<FuncT, iterator> == false && std::is_same_v<FuncT, const_iterator> == false )
            iterator Find( FuncT func )
            {
                const auto& self = static_cast<const DerivedType&>( *this );
                return std::find_if( self.begin( ), self.end( ), func );
            }

            template<typename FuncT>
                requires std::ranges::range<const DerivedType>
            const_iterator Find( const_iterator it, FuncT func ) const
            {
                const auto& self = static_cast<const DerivedType&>( *this );
                return std::find_if( it, self.cend( ), func );
            }
            template<typename FuncT>
            iterator Find( iterator it, FuncT func )
            {
                auto& self = static_cast<DerivedType&>( *this );
                return std::find_if( it, self.end( ), func );
            }

            const_iterator Find( const value_type& value ) const
                requires std::ranges::range<const DerivedType>
            {
                const auto& self = static_cast<const DerivedType&>( *this );
                return std::find( self.cbegin( ), self.cend( ), value );
            }
            iterator Find( const value_type& value )
            {
                auto& self = static_cast<DerivedType&>( *this );
                return std::find( self.begin( ), self.end( ), value );
            }

            const_iterator Find( const_iterator it, const value_type& value ) const
                requires std::ranges::range<const DerivedType>
            {
                const auto& self = static_cast<const DerivedType&>( *this );
                return std::find( it, self.cend( ), value );
            }
            iterator Find( iterator it, const value_type& value )
            {
                auto& self = static_cast<DerivedType&>( *this );
                return std::find( it, self.end( ), value );
            }

            template<typename FuncT>
            auto Select( FuncT func ) const
                requires ( std::is_same_v<FuncT, value_type> == false && std::is_same_v<FuncT, iterator> == false && std::is_same_v<FuncT, const_iterator> == false && std::ranges::range<const DerivedType> );

            template<typename FuncT>
            auto Select( FuncT func )
                requires ( std::is_same_v<FuncT, value_type> == false && std::is_same_v<FuncT, iterator> == false && std::is_same_v<FuncT, const_iterator> == false );

        private:
            template <typename T, typename... Args>
            static std::array<T, sizeof...( Args )> MakeArray( Args&&... args )
            {
                return { static_cast<T>( std::forward<Args>( args ) )... };
            }
        public:

            template<typename ... Args>
                requires std::conjunction_v<std::is_same<Args, value_type>...>
            bool Equals( const Args& ... args ) 
            {
                auto& self = static_cast<DerivedType&>( *this );
                auto arrayOfArgs = MakeArray<value_type>( args... );
                return std::ranges::equal( self, arrayOfArgs );
            }

            template<typename ... Args>
                requires std::conjunction_v<std::is_same<Args, value_type>...> && std::ranges::range<const DerivedType>
            bool Equals( const Args& ... args ) const
            {
                const auto& self = static_cast<const DerivedType&>( *this );
                auto arrayOfArgs = MakeArray<value_type>( args... );
                return std::ranges::equal( self.cbegin( ), self.cend( ), arrayOfArgs.cbegin( ), arrayOfArgs.cend( ) );
            }

            template<std::ranges::range RengeT>
            bool Equals( RengeT&& range )
            {
                auto& self = static_cast<DerivedType&>( *this );
                return std::ranges::equal( self, std::move(range) );
            }

            template<std::ranges::range RengeT>
                requires std::ranges::range<const DerivedType>
            bool Equals( RengeT&& range ) const
            {
                const auto& self = static_cast<const DerivedType&>( *this );
                return std::ranges::equal( self, std::move( range ) );
            }


        
        };


        template<typename DerivedT, typename RangeT>
        class ContiguousRangeBase : public RangeBase<DerivedT,RangeT>
        {
        public:
            using Base = RangeBase<DerivedT, RangeT>;
            using value_type = typename Base::value_type;
            using size_type = typename Base::size_type;
            using iterator = typename Base::iterator;
            using const_iterator = typename Base::const_iterator;
            using reference = typename Base::reference;
            using const_reference = typename Base::const_reference;


            using Base::begin;
            using Base::end;
            using Base::rbegin;
            using Base::rend;
            using Base::erase;
            using Base::size;
            using Base::emplace_back;

            static constexpr size_type npos = MaxUInt64;

            ContiguousRangeBase( )
                : Base( )
            { }

            template<typename ...Args>
                requires std::is_constructible_v<Base, Args...>
            ContiguousRangeBase( Args&& ... args )
                : Base( std::forward<Args>( args )... )
            { }

            ContiguousRangeBase( std::initializer_list<value_type> items )
                : Base( std::move( items ) )
            { }

            size_type IndexOf( const value_type& value ) const
            {
                auto beginIt = begin( );
                auto it = beginIt;
                auto endIt = end( );
                for ( ; it != endIt; ++it )
                {
                    if ( *it == value )
                    {
                        return std::distance( beginIt, it );
                    }
                }
                return npos;
            }

            bool Contains( const value_type& value ) const
            {
                return IndexOf( value ) != npos;
            }

            template<typename FuncT>
            const_reference Last( FuncT func ) const
            {
                auto it = std::find_if( rbegin( ), rend( ), func );
                if ( it != rend( ) )
                {
                    return *it;
                }
                throw InvalidOperationException( );
            }

            const_reference Last( ) const
            {
                if ( size( ) )
                {
                    return *rbegin( );
                }
                throw InvalidOperationException( );
            }

            template<typename FuncT>
            const_iterator FindLast( FuncT func ) const
            {
                return std::find_if( rbegin( ), rend( ), func );
            }
            template<typename FuncT>
            iterator FindLast( FuncT func )
            {
                return std::find_if( rbegin( ), rend( ), func );
            }


            template<typename ... Args>
                requires std::conjunction_v<std::is_same<Args, typename VertexList::value_type>...>
            void Add( Args&& ... args )
            {
                (emplace_back( std::forward<Args>(args) ),...);
            }
        

            void RemoveAt( size_type index )
            {
                auto sz = size( );
                if ( index >= sz )
                {
                    throw ArgumentOutOfRangeException( L"index", Format( L"index({}) >= size({})", index, sz ) );
                }
                erase( begin() + sz );
            }

            bool Remove( const value_type& value )
            {
                auto index = IndexOf( value );
                if ( index != npos )
                {
                    erase( begin( ) + index );
                    return true;
                }
                return false;
            }

            template<typename ... Args>
                requires std::conjunction_v<std::is_same<Args, value_type>...>
            bool Equals( const Args& ... args ) const
            {
                if ( sizeof...( args ) == Base::size( ) )
                {
                    auto compare_elements = [ & ]( auto... Is )
                        {
                            bool result = true;
                            size_t index = 0;
                            ( ( result = result && ( ( *this )[ index++ ] == args ) ), ... );
                            return result;
                        };

                    return compare_elements( std::make_index_sequence<sizeof...( args )>{} );

                }
                return false;
            }

            template<SpanLike SpanT>
                requires std::equality_comparable_with<value_type, typename SpanT::value_type>
            bool Equals( const SpanT& other ) const
            {
                auto otherSize = other.size( );
                auto thisSize = size( );
                if ( thisSize == otherSize )
                {
                    return std::equal( begin( ), end( ), other.begin( ) );
                }
                return false;
            }

            template<typename ... Args>
                requires std::conjunction_v<std::is_same<Args, typename VertexList::value_type>...>
            bool SequenceEqual( const Args& ... args ) const
            {
                return Equals( std::forward<Args&>( args )... );
            }

            template<SpanLike SpanT>
                requires std::equality_comparable_with<value_type, typename SpanT::value_type>
            bool SequenceEqual( const SpanT& other ) const
            {
                return Equals( other );
            }

        };


        template<typename DerivedT, typename RangeT>
        class MapBase : public RangeBase<DerivedT, RangeT>
        {
        public:
            using Base = RangeBase<DerivedT, RangeT>;
            using value_type = typename Base::value_type;
            using size_type = typename Base::size_type;

            using Base::begin;
            using Base::end;
            using Base::erase;
            using Base::size;

            MapBase( )
                : Base( )
            { }

            template<typename ...Args>
                requires std::is_constructible_v<Base, Args...>
            MapBase( Args&& ... args )
                : Base( std::forward<Args>( args )... )
            { }

            MapBase( std::initializer_list<value_type> items )
                : Base( std::move( items ) )
            { }
        };

        template<typename DerivedT, typename RangeT>
        class ReversibleMapBase : public MapBase<DerivedT, RangeT>
        {
        public:
            using Base = MapBase<DerivedT, RangeT>;
            using value_type = typename Base::value_type;
            using size_type = typename Base::size_type;

            using Base::begin;
            using Base::end;
            using Base::rbegin;
            using Base::rend;
            using Base::erase;
            using Base::size;

            ReversibleMapBase( )
                : Base( )
            { }

            template<typename ...Args>
                requires std::is_constructible_v<Base, Args...>
            ReversibleMapBase( Args&& ... args )
                : Base( std::forward<Args>( args )... )
            { }

            ReversibleMapBase( std::initializer_list<value_type> items )
                : Base( std::move( items ) )
            { }
        };


        template<typename DerivedT, typename RangeT>
        class SetBase : public RangeBase<DerivedT, RangeT>
        {
        public:
            using Base = RangeBase<DerivedT, RangeT>;
            using value_type = typename Base::value_type;
            using size_type = typename Base::size_type;

            using Base::begin;
            using Base::end;
            using Base::erase;
            using Base::size;

            SetBase( )
                : Base( )
            { }

            template<typename ...Args>
                requires std::is_constructible_v<Base, Args...>
            SetBase( Args&& ... args )
                : Base( std::forward<Args>( args )... )
            { }

            SetBase( std::initializer_list<value_type> items )
                : Base( std::move( items ) )
            { }

        };

        template<typename DerivedT, typename RangeT>
        class ReversibleSetBase : public SetBase<DerivedT, RangeT>
        {
        public:
            using Base = SetBase<DerivedT, RangeT>;
            using value_type = typename Base::value_type;
            using size_type = typename Base::size_type;

            using Base::begin;
            using Base::end;
            using Base::rbegin;
            using Base::rend;
            using Base::erase;
            using Base::size;

            ReversibleSetBase( )
                : Base( )
            { }

            template<typename ...Args>
                requires std::is_constructible_v<Base, Args...>
            ReversibleSetBase( Args&& ... args )
                : Base( std::forward<Args>( args )... )
            { }

            ReversibleSetBase( std::initializer_list<value_type> items )
                : Base( std::move( items ) )
            { }

        };


    }



    


    template<typename ValueT, typename AllocatorT = std::allocator<ValueT>>
    class Vector : public Internal::ContiguousRangeBase<Vector<ValueT, AllocatorT>, std::vector<ValueT, AllocatorT>>
    {
    public:
        using Base = Internal::ContiguousRangeBase<Vector<ValueT, AllocatorT>, std::vector<ValueT, AllocatorT>>;
        using value_type = Base::value_type;


        Vector( )
            : Base( )
        { }

        template<typename ...Args>
            requires std::is_constructible_v<Base, Args...>
        Vector( Args&& ... args )
            : Base( std::forward<Args>( args )... )
        { }

        Vector( std::initializer_list<value_type> items )
            : Base( std::move( items ) )
        { }

    };

    template<typename KeyT, typename ValueT, typename Hash = std::hash<KeyT>, typename KeyEqual = std::equal_to<KeyT>,typename AllocatorT = std::allocator<std::pair<const KeyT, ValueT>>>
    class UnorderedMap : public Internal::MapBase<UnorderedMap<KeyT, ValueT, Hash, KeyEqual, AllocatorT>, std::unordered_map<KeyT, ValueT, Hash, KeyEqual, AllocatorT>>
    {
    public:
        using Base = Internal::MapBase<UnorderedMap<KeyT, ValueT, Hash, KeyEqual, AllocatorT>, std::unordered_map<KeyT, ValueT, Hash, KeyEqual, AllocatorT>>;
    };

    template<typename KeyT, typename Hash = std::hash<KeyT>, typename KeyEqual = std::equal_to<KeyT>, typename AllocatorT = std::allocator<KeyT>>
    class UnorderedSet : public Internal::SetBase<UnorderedSet<KeyT, Hash, KeyEqual, AllocatorT>, std::unordered_set<KeyT, Hash, KeyEqual, AllocatorT>>
    {
    public:
        using Base = Internal::SetBase<UnorderedSet<KeyT, Hash, KeyEqual, AllocatorT>, std::unordered_set<KeyT, Hash, KeyEqual, AllocatorT>>;
    };

    template<typename KeyT, typename ValueT, typename CompareT = std::less<KeyT>, typename AllocatorT = std::allocator<std::pair<const KeyT, ValueT>>>
    class Map : public Internal::ReversibleMapBase<Map<KeyT, ValueT, CompareT, AllocatorT>, std::map<KeyT, ValueT, CompareT, AllocatorT>>
    {
    public:
        using Base = Internal::ReversibleMapBase<Map<KeyT, ValueT, CompareT, AllocatorT>, std::map<KeyT, ValueT, CompareT, AllocatorT>>;
    };

    template<typename KeyT, typename CompareT = std::less<KeyT>, typename AllocatorT = std::allocator<KeyT>>
    class Set : public Internal::ReversibleSetBase<Set<KeyT, CompareT, AllocatorT>, std::set<KeyT, CompareT, AllocatorT>>
    {
    public:
        using Base = Internal::ReversibleSetBase<Set<KeyT, CompareT, AllocatorT>, std::set<KeyT, CompareT, AllocatorT>>;
    };



    template<std::ranges::viewable_range RangeT>
    class All : public Internal::RangeBase< All<RangeT>, std::ranges::views::all_t<RangeT> >
    {
    public:
        using Base = Internal::RangeBase< All<RangeT>, std::ranges::views::all_t<RangeT> >;
    };

    template <std::ranges::range RangeT>
        requires std::is_object_v<RangeT>
    class RefView : public Internal::RangeBase<RefView<RangeT>, std::ranges::ref_view<RangeT> >
    {
    public:
        using Base = Internal::RangeBase<RefView<RangeT>, std::ranges::ref_view<RangeT> >;
    };


    template <std::ranges::range RangeT>
        requires ( std::movable<RangeT> && !IsInitializerList<RangeT> )
    class OwningView : public Internal::RangeBase<OwningView<RangeT>, std::ranges::owning_view<RangeT> >
    {
    public:
        using Base = Internal::RangeBase<OwningView<RangeT>, std::ranges::owning_view<RangeT> >;
    };

    template <std::ranges::input_range RangeT, std::indirect_unary_predicate<std::ranges::iterator_t<RangeT>> PredicateT>
        requires std::ranges::view<RangeT>&& std::is_object_v<PredicateT>
    class FilterView : public Internal::RangeBase<FilterView<RangeT, PredicateT>, std::ranges::filter_view<RangeT, PredicateT> >
    {
    public:
        using Base = Internal::RangeBase<FilterView<RangeT, PredicateT>, std::ranges::filter_view<RangeT, PredicateT> >;

        template<typename ...Args>
            requires std::is_constructible_v<Base, Args...>
        FilterView( Args&& ... args )
            : Base( std::forward<Args>( args )... )
        { }

        constexpr explicit FilterView( RangeT range, PredicateT predicate )
            noexcept( std::is_nothrow_move_constructible_v<RangeT> && std::is_nothrow_move_constructible_v<PredicateT> )
            : Base( std::move( range ), std::move( predicate ) )
        { }

    };

    template <class RangeT, class PredicateT>
    FilterView( RangeT&&, PredicateT ) -> FilterView<std::ranges::views::all_t<RangeT>, PredicateT>;

    
    namespace Internal
    {
        template<typename DerivedT, typename RangeT>
        template<typename FuncT>
        inline auto RangeBase<DerivedT, RangeT>::Select( FuncT func ) const
                requires ( std::is_same_v<FuncT, value_type> == false && std::is_same_v<FuncT, iterator> == false && std::is_same_v<FuncT, const_iterator> == false && std::ranges::range<const DerivedType> )
        {
            return FilterView( static_cast<const DerivedT&>( *this ), std::forward<FuncT>( func ) );
        }

        template<typename DerivedT, typename RangeT>
        template<typename FuncT>
        inline auto RangeBase<DerivedT, RangeT>::Select( FuncT func )
            requires ( std::is_same_v<FuncT, value_type> == false && std::is_same_v<FuncT, iterator> == false && std::is_same_v<FuncT, const_iterator> == false )
        {
            return FilterView( static_cast<const DerivedT&>( *this ), std::forward<FuncT>( func ) );
        }
    }
    

}

#endif
