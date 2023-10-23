#pragma once
#ifndef HCCITERATOR_H_
#define HCCITERATOR_H_

#include <HCCLib.h>

namespace Harlinn::Common::Core::Internal
{
    template<typename ContainerT>
    class ConstPointerIterator
    {
    public:
        using ContainerType = ContainerT;
        using iterator_concept = std::contiguous_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type = typename ContainerType::value_type;
        using difference_type = typename ContainerType::difference_type;
        using pointer = typename ContainerType::const_pointer;
        using Pointer = typename ContainerType::pointer;
        using reference = const value_type&;
    public:
        Pointer ptr_;
    public:
        constexpr ConstPointerIterator( ) noexcept
            : ptr_( nullptr )
        {
        }
        constexpr ConstPointerIterator( pointer ptr ) noexcept
            : ptr_( const_cast<Pointer>(ptr) )
        {
        }

        constexpr ConstPointerIterator( const ConstPointerIterator& other, const difference_type offset ) noexcept
            : ptr_( other.ptr_ + offset )
        {
        }


        [[nodiscard]] constexpr reference operator*( ) const noexcept
        {
            return *ptr_;
        }

        [[nodiscard]] constexpr pointer operator->( ) const noexcept
        {
            return ptr_;
        }

        constexpr ConstPointerIterator& operator++( ) noexcept
        {
            ++ptr_;
            return *this;
        }

        constexpr ConstPointerIterator operator++( int ) noexcept
        {
            ConstPointerIterator tmp = *this;
            ++ptr_;
            return tmp;
        }

        constexpr ConstPointerIterator& operator--( ) noexcept
        {
            --ptr_;
            return *this;
        }

        constexpr ConstPointerIterator operator--( int ) noexcept
        {
            ConstPointerIterator tmp = *this;
            --ptr_;
            return tmp;
        }

        constexpr ConstPointerIterator& operator+=( const difference_type offset ) noexcept
        {
            ptr_ += offset;
            return *this;
        }

        [[nodiscard]] constexpr ConstPointerIterator operator+( const difference_type offset ) const noexcept
        {
            ConstPointerIterator tmp( *this, offset );
            return tmp;
        }

        friend [[nodiscard]] constexpr ConstPointerIterator operator+( const difference_type lhs, const ConstPointerIterator& rhs ) noexcept
        {
            ConstPointerIterator tmp( rhs, lhs );
            return tmp;
        }

        constexpr ConstPointerIterator& operator-=( const difference_type offset ) noexcept
        {
            ptr_ -= offset;
            return *this;
        }

        [[nodiscard]] constexpr ConstPointerIterator operator-( const difference_type offset ) const noexcept
        {
            ConstPointerIterator tmp( *this );
            tmp -= offset;
            return tmp;
        }

        [[nodiscard]] constexpr difference_type operator-( const ConstPointerIterator& other ) const noexcept
        {
            return ptr_ - other.ptr_;
        }

        [[nodiscard]] constexpr reference operator[]( const difference_type offset ) const noexcept
        {
            return *( ptr_ + offset );
        }

        [[nodiscard]] constexpr bool operator==( const ConstPointerIterator& other ) const noexcept
        {
            return ptr_ == other.ptr_;
        }

        [[nodiscard]] constexpr std::strong_ordering operator<=>( const ConstPointerIterator& other ) const noexcept
        {
            return UnwrapPointer( ptr_ ) <=> UnwrapPointer( other.ptr_ );
        }
    };
}

namespace std
{
    template <typename ContainerT>
    struct pointer_traits<Harlinn::Common::Core::Internal::ConstPointerIterator<ContainerT>>
    {
        using pointer = Harlinn::Common::Core::Internal::ConstPointerIterator<ContainerT>;
        using element_type = const typename pointer::value_type;
        using difference_type = typename pointer::difference_type;

        [[nodiscard]] static constexpr pointer pointer_to( element_type& element ) noexcept
        {
            return pointer( &element );
        }


        [[nodiscard]] static constexpr element_type* to_address( const pointer it ) noexcept
        {
            return std::to_address( it.ptr_ );
        }
    };
}

namespace Harlinn::Common::Core::Internal
{
    template<typename ContainerT>
    class PointerIterator : public ConstPointerIterator<ContainerT>
    {
    public:
        using Base = ConstPointerIterator<ContainerT>;
        using ContainerType = ContainerT;
        using iterator_concept = std::contiguous_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type = typename ContainerType::value_type;
        using difference_type = typename ContainerType::difference_type;
        using pointer = typename ContainerType::pointer;
        using reference = value_type&;

        constexpr PointerIterator( ) noexcept
        {
        }

        constexpr PointerIterator( pointer ptr ) noexcept
            : Base( ptr )
        {
        }

        constexpr PointerIterator( const PointerIterator& other, const difference_type offset ) noexcept
            : Base( other.ptr_, offset )
        {
        }


        [[nodiscard]] constexpr reference operator*( ) const noexcept
        {
            return const_cast< reference >( Base::operator*( ) );
        }

        [[nodiscard]] constexpr pointer operator->( ) const noexcept
        {
            return Base::ptr_;
        }

        constexpr PointerIterator& operator++( ) noexcept
        {
            Base::operator++( );
            return *this;
        }

        constexpr PointerIterator operator++( int ) noexcept
        {
            PointerIterator tmp = *this;
            Base::operator++( );
            return tmp;
        }

        constexpr PointerIterator& operator--( ) noexcept
        {
            Base::operator--( );
            return *this;
        }

        constexpr PointerIterator operator--( int ) noexcept
        {
            PointerIterator tmp = *this;
            Base::operator--( );
            return tmp;
        }

        constexpr PointerIterator& operator+=( const difference_type offset ) noexcept
        {
            Base::operator+=( offset );
            return *this;
        }

        [[nodiscard]] constexpr PointerIterator operator+( const difference_type offset ) const noexcept
        {
            PointerIterator tmp = *this;
            tmp += offset;
            return tmp;
        }

        friend [[nodiscard]] constexpr PointerIterator operator+( const difference_type lhs, PointerIterator rhs ) noexcept
        {
            rhs += lhs;
            return rhs;
        }

        constexpr PointerIterator& operator-=( const difference_type offset ) noexcept
        {
            Base::operator-=( offset );
            return *this;
        }

        using Base::operator-;

        [[nodiscard]] constexpr PointerIterator operator-( const difference_type offset ) const noexcept
        {
            PointerIterator tmp = *this;
            tmp -= offset;
            return tmp;
        }

        [[nodiscard]] constexpr reference operator[]( const difference_type offset ) const noexcept
        {
            return const_cast< reference >( Base::operator[]( offset ) );
        }
    };
}


namespace std
{
    template <typename ContainerT>
    struct pointer_traits<Harlinn::Common::Core::Internal::PointerIterator<ContainerT>>
    {
        using pointer = Harlinn::Common::Core::Internal::PointerIterator<ContainerT>;
        using element_type = typename pointer::value_type;
        using difference_type = typename pointer::difference_type;

        [[nodiscard]] static constexpr pointer pointer_to( element_type& element ) noexcept
        {
            return pointer( &element );
        }


        [[nodiscard]] static constexpr element_type* to_address( const pointer it ) noexcept
        {
            return std::to_address( it.ptr_ );
        }
    };
}

namespace Harlinn::Common::Core::Internal
{

    template<typename CollectionT, typename ValueT = typename CollectionT::value_type, typename ReferenceT = std::reference_wrapper<ValueT>>
    ReferenceT GetCollectionElement( const CollectionT* collection, size_t index )
    {
        return (*collection )[ index ];
    }

    template<typename CollectionT, typename ValueT = typename CollectionT::value_type, typename ReferenceT = std::reference_wrapper<ValueT> >
    class IndexIterator
    {
    public:
        using CollectionType = CollectionT;
        using ValueType = ValueT;
        using iterator_category = std::random_access_iterator_tag;
        using value_type = ValueT;
        using difference_type = SSIZE_T;
        using pointer = const value_type*;
        using reference = const value_type&;
    private:
        CollectionType* collection_;
        size_t index_;
        size_t size_;
        using ReferenceType = ReferenceT;
        ReferenceType valueReference_;
    public:
        explicit IndexIterator( )
            : collection_( nullptr ), index_( 0 ), size_( 0 )
        {
        }

        explicit IndexIterator( CollectionType* collection )
            : collection_( collection ), index_( 0 ), size_( 0 )
        {
            if ( collection_ )
            {
                size_ = collection_->size( );
                if ( size_ )
                {
                    valueReference_ = (*collection_)[0];
                }
            }
        }

        explicit IndexIterator( CollectionType* collection, bool end )
            : collection_( collection ), index_( 0 ), size_( 0 )
        {
            if ( collection_ )
            {
                size_ = collection_->size( );
                index_ = size_;
            }
        }
    private:
        size_t size( ) const
        {
            return std::size( *collection_ );
        }
    public:

        reference operator*( ) const
        {
            return valueReference_;
        }
        pointer operator->( ) const
        {
            return &valueReference_;
        }

        IndexIterator& operator++( )
        {
            ++index_;
            valueReference_ = ( *collection_ )[ index_ ];
            return *this;
        }

        IndexIterator operator++( int )
        {
            auto tmp = *this;
            ++*this;
            return tmp;
        }
        IndexIterator& operator--( )
        {
            --index_;
            valueReference_ = ( *collection_ )[ index_ ];
            return *this;
        }

        IndexIterator operator--( int )
        {
            auto tmp = *this;
            --*this;
            return tmp;
        }

        IndexIterator& operator += ( const difference_type offset )
        {
            index_ += static_cast< size_t >( offset );
            valueReference_ = ( *collection_ )[ index_ ];
            return *this;
        }

        [[nodiscard]] IndexIterator operator+( const difference_type offset ) const
        {
            IndexIterator tmp = *this;
            tmp += offset;
            return tmp;
        }

        IndexIterator& operator-=( const difference_type offset )
        {
            index_ -= static_cast< size_t >( offset );
            valueReference_ = ( *collection_ )[ index_ ];
            return *this;
        }

        [[nodiscard]] IndexIterator operator-( const difference_type offset ) const
        {
            IndexIterator tmp = *this;
            tmp -= offset;
            return tmp;
        }

        constexpr bool operator == ( const IndexIterator& other ) const noexcept
        {
            return index_ == other.index_;
        }
        constexpr bool operator != ( const IndexIterator& other ) const noexcept
        {
            return index_ != other.index_;
        }
        constexpr bool operator < ( const IndexIterator& other ) const noexcept
        {
            return index_ < other.index_;
        }
        constexpr bool operator <= ( const IndexIterator& other ) const noexcept
        {
            return index_ <= other.index_;
        }
        constexpr bool operator > ( const IndexIterator& other ) const noexcept
        {
            return index_ > other.index_;
        }
        constexpr bool operator >= ( const IndexIterator& other ) const noexcept
        {
            return index_ >= other.index_;
        }
    };
}


#endif
