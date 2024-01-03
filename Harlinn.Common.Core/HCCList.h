#pragma once
#ifndef HARLINN_COMMON_CORE_HCCLIST_H_
#define HARLINN_COMMON_CORE_HCCLIST_H_
/*
   Copyright 2024 Espen Harlinn

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

#include <HCCLib.h>

namespace Harlinn::Common::Core
{

    template<typename ListT>
    class ListConstIterator
    {
    public:
        using ListType = ListT;
        using size_type = typename ListType::size_type;
        using value_type = typename ListType::value_type;
        using pointer = const value_type*;
        using reference = const value_type&;
        using Node = typename ListType::Node;
        using iterator_concept = std::forward_iterator_tag;
        using iterator_category = std::forward_iterator_tag;
            
        static constexpr size_type NodeSize = ListType::NodeSize;
        static constexpr size_type NodeSizeM1 = NodeSize - 1;
        static_assert( NodeSize >= 2 );
    protected:
        Node* current_ = nullptr;
        size_type index_ = 0;
    public:
        ListConstIterator( ) = default;
        ListConstIterator( Node* current, size_type index )
            : current_( current ), index_( index )
        { }

        constexpr operator bool( ) const noexcept
        {
            return current_ != nullptr;
        }

        constexpr __forceinline bool operator == ( const ListConstIterator& other ) const noexcept
        {
            return current_ == other.current_ && index_ == other.index_;
        }
        constexpr __forceinline bool operator != ( const ListConstIterator& other ) const noexcept
        {
            return current_ != other.current_ || index_ != other.index_;
        }

        constexpr bool operator == ( nullptr_t ) const noexcept
        {
            return current_ == nullptr;
        }
        constexpr bool operator != ( nullptr_t ) const noexcept
        {
            return current_ != nullptr;
        }

        [[nodiscard]] constexpr reference operator*( ) const noexcept
        {
            return *(reinterpret_cast<pointer>( current_->data_ ) + index_ );
        }

        [[nodiscard]] constexpr pointer operator->( ) const noexcept
        {
            return ( reinterpret_cast<pointer>( current_->data_ ) + index_ );
        }

    protected:
        constexpr __forceinline void Advance( ) noexcept
        {
            if ( index_ < NodeSizeM1 ) [[likely]]
            {
                index_++;
            }
            else
            {
                current_ = current_->next_;
                index_ = 0;
            }
        }
    public:
        constexpr __forceinline ListConstIterator& operator++( ) noexcept
        {
            Advance( );
            return *this;
        }

        constexpr ListConstIterator operator++( int ) noexcept
        {
            ListConstIterator result = *this;
            Advance( );
            return result;
        }

        constexpr void swap( ListConstIterator& other ) noexcept
        {
            std::swap( current_, other.current_ );
            std::swap( index_, other.index_ );
        }
    };


    template<typename ListT>
    class ListIterator : public ListConstIterator<ListT>
    {
    public:
        using Base = ListConstIterator<ListT>;
        using Node = typename ListT::Node;
        using value_type = typename ListT::value_type;
        using size_type = typename ListT::size_type;
        using pointer = typename ListT::pointer;
        using reference = typename ListT::reference;

        ListIterator( ) = default;
        ListIterator( Node * current, size_type index )
            : Base( current, index )
        {
        }


        constexpr __forceinline ListIterator& operator++( ) noexcept
        {
            Base::Advance( );
            return *this;
        }

        constexpr ListIterator operator++( int ) noexcept
        {
            ListIterator result = *this;
            Base::Advance( );
            return result;
        }

        [[nodiscard]] constexpr reference operator*( ) const noexcept
        {
            return *( reinterpret_cast<pointer>( Base::current_->data_ ) + Base::index_ );
        }

        [[nodiscard]] constexpr pointer operator->( ) const noexcept
        {
            return ( reinterpret_cast<pointer>( Base::current_->data_ ) + Base::index_ );
        }

    };


    template<typename T, size_t nodeSize = 4096 >
    class List
    {
    public:
        using size_type = size_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_pointer = const T*;
        using const_reference = const T&;
        using iterator = ListIterator< List<T, nodeSize> >;
        using const_iterator = ListConstIterator< List<T, nodeSize> >;

        static constexpr size_type NodeSize = nodeSize;
    private:
        template<typename ListT>
        friend class ListConstIterator;
        template<typename ListT>
        friend class ListIterator;
        struct Node
        {
            static constexpr size_type ByteSize = sizeof( T[NodeSize] );
            Byte data_[ByteSize];
            Node* next_ = nullptr;
        };
        Node* first_ = nullptr;
        Node* last_ = nullptr;
        size_type size_ = 0;
    public:
        constexpr List( )
        {
        }

        constexpr List( List&& other )
            : first_( other.first_ ), last_( other.last_ ), size_( other.size_ )
        {
            other.first_ = nullptr;
            other.last_ = nullptr;
            other.size_ = 0;
        }

        ~List( )
        {
            clear( );
        }

        void clear( )
        {
            if ( last_ )
            {
                auto node = first_;
                while ( node != last_ )
                {
                    auto tmp = node;
                    node = node->next_;
                    for ( size_type i = 0; i < NodeSize; i++ )
                    {
                        auto ptr = reinterpret_cast<T*>( tmp->data_ ) + i;
                        ptr->~T( );
                    }
                    ReleaseNode( tmp );
                }
                auto lastNodeSize = size_ % NodeSize;
                if ( !lastNodeSize )
                {
                    lastNodeSize = NodeSize;
                }
                for ( size_type i = 0; i < lastNodeSize; i++ )
                {
                    auto ptr = reinterpret_cast<T*>( last_->data_ ) + i;
                    ptr->~T( );
                }
                ReleaseNode( last_ );
                first_ = nullptr;
                last_ = nullptr;
                size_ = 0;
            }
        }

        List( const List& other ) = delete;
        List& operator = ( const List& other ) = delete;

        constexpr List& operator = ( List&& other ) noexcept
        {
            std::swap( first_, other.first_ );
            std::swap( last_, other.last_ );
            std::swap( size_, other.size_ );
            return *this;
        }
    private:
        static Node* AcquireNode( )
        {
            return new Node( );
        }
        static void ReleaseNode( Node* node )
        {
            delete node;
        }
    public:
        constexpr size_type size( ) const noexcept
        {
            return size_;
        }
        constexpr bool empty( ) const noexcept
        {
            return size_ == 0;
        }

        template<typename ...Args>
        reference emplace_back( Args&& ... args )
        {
            auto lastNodeSize = size_ % NodeSize;
            if ( lastNodeSize != 0 )
            {
                auto* ptr = new ( reinterpret_cast<T*>( last_->data_ ) + lastNodeSize ) T( std::forward<Args>( args )... );
                size_++;
                return *ptr;
            }
            else
            {
                auto newNode = AcquireNode( );
                auto* ptr = new ( reinterpret_cast<T*>( newNode->data_ ) ) T( std::forward<Args>( args )... );
                std::construct_at<T>( ptr, std::forward<Args>( args )... );
                size_++;

                if ( last_ )
                {
                    last_->next_ = newNode;
                    last_ = newNode;
                }
                else
                {
                    first_ = newNode;
                    last_ = first_;
                }
                return *ptr;
            }
        }

        iterator begin( )
        {
            return iterator( first_, 0 );
        }
        const_iterator begin( ) const
        {
            return const_iterator( first_, 0 );
        }
        iterator end( )
        {
            if ( last_ )
            {
                size_type remainder = size_ % NodeSize;
                return iterator( last_, remainder ? remainder : NodeSize );
            }
            else
            {
                return iterator( nullptr, 0 );
            }
        }
        const_iterator end( ) const
        {
            if ( last_ )
            {
                size_type remainder = size_ % NodeSize;
                return const_iterator( last_, remainder ? remainder : NodeSize );
            }
            else
            {
                return const_iterator( nullptr, 0 );
            }
        }
        const_iterator cbegin( ) const
        {
            return begin( );
        }
        const_iterator cend( ) const
        {
            return end( );
        }

    };

}

#endif
