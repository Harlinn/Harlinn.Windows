#pragma once
#ifndef __HCCVECTOR_H__
#define __HCCVECTOR_H__

#include <HCCLib.h>

namespace Harlinn::Common::Core
{
    template<typename T>
    class Vector;

    template< typename VectorT >
    class VectorConstIterator
    {
        template<typename T>
        friend class Vector;
    public:
        using iterator_concept = std::contiguous_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type = typename VectorT::value_type;
        using difference_type = typename VectorT::difference_type;
        using pointer = typename VectorT::const_pointer;
        using reference = const value_type&;
    protected:
        value_type* ptr_ = nullptr;
    
        constexpr explicit VectorConstIterator( value_type* ptr ) noexcept
            : ptr_( ptr )
        {

        }
    public:
        constexpr VectorConstIterator() noexcept
        { }


        constexpr operator bool( ) const noexcept
        {
            return ptr_ != nullptr;
        }

        constexpr bool operator == ( const VectorConstIterator& other ) const noexcept
        {
            return ptr_ == other.ptr_;
        }
        constexpr bool operator != ( const VectorConstIterator& other ) const noexcept
        {
            return ptr_ != other.ptr_;
        }

        constexpr bool operator == ( nullptr_t ) const noexcept
        {
            return ptr_ == nullptr;
        }
        constexpr bool operator != ( nullptr_t ) const noexcept
        {
            return ptr_ != nullptr;
        }


        constexpr bool operator <= ( const VectorConstIterator& other ) const noexcept
        {
            return ptr_ <= other.ptr_;
        }
        constexpr bool operator < ( const VectorConstIterator& other ) const noexcept
        {
            return ptr_ < other.ptr_;
        }
        constexpr bool operator >= ( const VectorConstIterator& other ) const noexcept
        {
            return ptr_ >= other.ptr_;
        }
        constexpr bool operator > ( const VectorConstIterator& other ) const noexcept
        {
            return ptr_ > other.ptr_;
        }


        [[nodiscard]] constexpr reference operator*( ) const noexcept
        {
            return const_cast<reference>( *ptr_ );
        }

        [[nodiscard]] constexpr pointer operator->( ) const noexcept
        {
            return const_cast<pointer>( ptr_ );
        }

        constexpr VectorConstIterator& operator++( ) noexcept
        {
            ptr_++;
            return *this;
        }

        VectorConstIterator operator++( int ) noexcept
        {
            VectorConstIterator result = *this;
            ptr_++;
            return result;
        }

        VectorConstIterator& operator--( ) noexcept
        {
            ptr_--;
            return *this;
        }

        VectorConstIterator operator--( int ) noexcept
        {
            VectorConstIterator result = *this;
            ptr_--;
            return result;
        }

        VectorConstIterator& operator += ( const difference_type offset ) noexcept
        {
            ptr_ += offset;
            return *this;
        }

        [[nodiscard]] VectorConstIterator operator + ( const difference_type offset ) const noexcept
        {
            VectorConstIterator result( ptr_ + offset );
            return result;
        }

        VectorConstIterator& operator-=( const difference_type offset ) noexcept
        {
            ptr_ += offset;
            return *this;
        }


        [[nodiscard]] VectorConstIterator operator - ( const difference_type offset ) const noexcept
        {
            VectorConstIterator result( ptr_ - offset );
            return result;
        }

        [[nodiscard]] difference_type operator - ( const VectorConstIterator& other ) const noexcept
        {
            return static_cast<difference_type>( ptr_ - other.ptr_ );
        }


        [[nodiscard]] reference operator[]( const difference_type offset ) const noexcept
        {
            return const_cast<reference>( ptr_[offset] );
        }

        constexpr void swap( VectorConstIterator& other ) noexcept
        {
            std::swap( ptr_, other.ptr_ );
        }

    };

    template<typename VectorT>
    class VectorIterator : public VectorConstIterator<VectorT>
    {
        template<typename T>
        friend class Vector;
    public:
        using Base = VectorConstIterator<VectorT>;

        using iterator_concept = std::contiguous_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type = typename VectorT::value_type;
        using difference_type = typename VectorT::difference_type;
        using pointer = typename VectorT::pointer;
        using reference = value_type&;
    private:
        constexpr explicit VectorIterator( value_type* ptr ) noexcept
            : Base( ptr )
        {

        }
    public:
        constexpr VectorIterator( ) noexcept
        {
        }


        [[nodiscard]] constexpr reference operator*( ) const noexcept
        {
            return const_cast<reference>( *Base::ptr_ );
        }

        [[nodiscard]] constexpr pointer operator->( ) const noexcept
        {
            return const_cast<pointer>( Base::ptr_ );
        }

        constexpr VectorIterator& operator++( ) noexcept
        {
            Base::ptr_++;
            return *this;
        }

        VectorIterator operator++( int ) noexcept
        {
            VectorIterator result = *this;
            Base::ptr_++;
            return result;
        }

        VectorIterator& operator--( ) noexcept
        {
            Base::ptr_--;
            return *this;
        }

        VectorIterator operator--( int ) noexcept
        {
            VectorIterator result = *this;
            Base::ptr_--;
            return result;
        }

        VectorIterator& operator += ( const difference_type offset ) noexcept
        {
            Base::ptr_ += offset;
            return *this;
        }

        template <typename DiffT>
        requires IsInteger<DiffT>
        [[nodiscard]] VectorIterator operator + ( const DiffT offset ) const noexcept
        {
            VectorIterator result( Base::ptr_ + static_cast<size_t>(offset) );
            return result;
        }

        [[nodiscard]] difference_type operator - ( const VectorIterator& other ) const noexcept
        {
            return static_cast<difference_type>( Base::ptr_ - other.ptr_ );
        }


        VectorIterator& operator-=( const difference_type offset ) noexcept
        {
            Base::ptr_ += offset;
            return *this;
        }


        template <typename DiffT>
        requires IsInteger<DiffT>
        [[nodiscard]] VectorIterator operator - ( const DiffT offset ) const noexcept
        {
            VectorIterator result( Base::ptr_ - static_cast<size_t>( offset ) );
            return result;
        }

        [[nodiscard]] reference operator[]( const difference_type offset ) const noexcept
        {
            return const_cast<reference>( Base::ptr_[offset] );
        }

        constexpr void swap( VectorIterator& other ) noexcept
        {
            std::swap( Base::ptr_, other.ptr_ );
        }

    };



    template<typename T>
    class Vector
    {
        static constexpr bool CanZeroInitialize = std::is_trivially_default_constructible_v<T>;
        static constexpr size_t ElementSize = sizeof( T );
    public:
        using size_type = SSizeT;
        using difference_type = SSizeT;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_pointer = const T*;
        using const_reference = const T&;
        using iterator = VectorIterator<Vector>;
        using const_iterator = VectorConstIterator<Vector>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    private:

        static void Free( T* ptr )
        {
            if ( ptr )
            {
                delete[] reinterpret_cast<Byte*>( ptr );
            }
        }

        class DataPtr
        {
            T* storage_;
        public:
            constexpr DataPtr() noexcept
                : storage_(nullptr)
            { }

            constexpr explicit DataPtr( T* storage ) noexcept
                : storage_( storage )
            {
            }

            DataPtr( const DataPtr& other ) = delete;
            constexpr DataPtr( DataPtr&& other ) noexcept
                : storage_( other.storage_ )
            {
                other.storage_ = nullptr;
            }

            ~DataPtr( )
            {
                if ( storage_ )
                {
                    Free( storage_ );
                }
            }

            void reset( )
            {
                if ( storage_ )
                {
                    Free( storage_ );
                    storage_ = nullptr;
                }
            }
            void reset( T* newStorage )
            {
                if ( storage_ != newStorage )
                {
                    if ( storage_ )
                    {
                        Free( storage_ );
                    }
                    storage_ = newStorage;
                }
            }

            constexpr T* release( ) noexcept
            {
                auto result = storage_;
                storage_ = nullptr;
                return result;
            }


            DataPtr& operator = ( const DataPtr& other ) = delete;
            DataPtr& operator = ( DataPtr&& other ) noexcept
            {
                std::swap( storage_, other.storage_ );
                return *this;
            }


            constexpr T* get( ) noexcept
            {
                return storage_;
            }
            constexpr const T* get( ) const noexcept
            {
                return storage_;
            }

            constexpr void swap( DataPtr& other ) noexcept
            {
                std::swap( storage_, other.storage_ );
            }
        };

        static DataPtr Allocate( size_type requiredCapacity )
        {
            DataPtr result( reinterpret_cast<T*>( new Byte[requiredCapacity * sizeof( T )] ) );
            return result;
        }


        constexpr size_type CapacityForSize( size_type sz ) const noexcept
        {
            size_type newCapacity = capacity_ ? ( capacity_ + capacity_ / 2 ) : 16;
            return newCapacity > sz ? newCapacity : sz;
        }

        
        DataPtr data_;
        size_type size_ = 0;
        size_type capacity_ = 0;
    public:

        constexpr Vector( ) noexcept
        {

        }

        Vector(size_type count, const value_type& val ) noexcept
        {
            if ( count )
            {
                auto requiredCapacity = CapacityForSize( count );
                DataPtr newData( Allocate( requiredCapacity ) );
                std::uninitialized_fill_n( newData.get( ), count, val );
                data_ = std::move( newData );
                size_ = count;
                capacity_ = requiredCapacity;
            }
        }

        Vector( size_type count ) noexcept
        {
            if ( count )
            {
                auto requiredCapacity = CapacityForSize( count );
                DataPtr newData( Allocate( requiredCapacity ) );
                if constexpr ( CanZeroInitialize )
                {
                    memset( newData.get( ), 0, count * sizeof( T ) );
                }
                else
                {
                    std::uninitialized_default_construct( newData.get( ), newData.get( ) + count );
                }
                data_ = std::move( newData );
                size_ = count;
                capacity_ = requiredCapacity;
            }
        }
        

        template<typename It>
            requires IsIterator_v<It>
        Vector( It first, It last )
        { 
            auto count = std::distance( first, last );
            if ( count )
            {
                auto requiredCapacity = CapacityForSize( count );
                DataPtr newData( Allocate( requiredCapacity ) );
                std::uninitialized_copy( first, last, newData.get( ) );
                data_ = std::move( newData );
                size_ = count;
                capacity_ = requiredCapacity;
            }
        }


        Vector( std::initializer_list<T> values )
            : Vector( values.begin(), values.end() )
        {

        }


        Vector( const Vector& other )
        {
            if ( other.size_ > 0 )
            {
                auto requiredCapacity = CapacityForSize( other.size_ );
                DataPtr newData( Allocate( requiredCapacity ) );
                std::uninitialized_copy( other.data( ), &other.data( )[other.size_], newData.get( ) );

                data_ = std::move( newData );
                size_ = other.size_;
                capacity_ = requiredCapacity;
            }
        }

        constexpr Vector( Vector&& other ) noexcept
            : size_( other.size_ ), capacity_( other.capacity_ ), data_( other.data_.release( ) )
        {
            other.capacity_ = 0;
            other.size_ = 0;
        }

        ~Vector( )
        {
            if constexpr ( std::is_trivially_destructible_v<T> == false )
            {
                if ( data( ) )
                {
                    std::destroy( begin( ), end() );
                }
            }
        }

        void Assign( const Vector& other )
        {
            if ( data( ) != other.data( ) )
            {
                if ( capacity_ < other.size_ )
                {
                    auto requiredCapacity = CapacityForSize( other.size_ );
                    DataPtr newData( Allocate( requiredCapacity ) );
                    std::uninitialized_copy( other.data( ), &other.data( )[other.size_], newData.get( ) );

                    if constexpr ( std::is_trivially_destructible_v<T> == false )
                    {
                        std::destroy( data( ), &data( )[size_] );
                    }

                    capacity_ = requiredCapacity;
                    size_ = other.size_;
                    data_ = std::move( newData );
                }
                else if ( size_ <= other.size_ )
                {
                    std::copy( other.data( ), &other.data( )[size_], data( ) );
                    std::uninitialized_copy( &other.data( )[size_], &other.data( )[other.size_], &data( )[size_] );
                    size_ = other.size_;
                }
                else
                {
                    std::copy( other.data( ), &other.data( )[other.size_], data( ) );
                    if constexpr ( std::is_trivially_destructible_v<T> == false )
                    {
                        std::destroy( &data( )[other.size_], &data( )[size_] );
                    }
                    size_ = other.size_;
                }
            }
        }

        Vector& operator = ( const Vector& other )
        {
            Assign( other );
            return *this;
        }

        Vector& operator = ( Vector&& other ) noexcept
        {
            std::swap( size_, other.size_ );
            std::swap( capacity_, other.capacity_ );
            std::swap( data_, other.data_ );
            return *this;
        }


        [[nodiscard]] bool Equals( Vector& other ) const
        {
            if ( size_ == other.size_ )
            {
                auto selfPtr = data_.get( );
                auto otherPtr = other.data_.get( );
                if ( selfPtr != otherPtr )
                {
                    auto endPtr = selfPtr + size_;
                    while ( selfPtr < endPtr )
                    {
                        if ( *selfPtr != *otherPtr )
                        {
                            return false;
                        }
                        selfPtr++;
                        otherPtr++;
                    }
                }
                return true;
            }
            else
            {
                return false;
            }
        }

        [[nodiscard]] bool operator == ( Vector& other ) const
        {
            return Equals( other );
        }
        [[nodiscard]] bool operator != ( Vector& other ) const
        {
            return Equals( other ) == false;
        }


        [[nodiscard]] constexpr bool empty( ) const noexcept
        {
            return size_ == 0;
        }
        [[nodiscard]] constexpr size_type size( ) const noexcept
        {
            return size_;
        }
        [[nodiscard]] constexpr size_type size_in_bytes( ) const noexcept
        {
            return size_ * static_cast<size_type>(sizeof( T ));
        }
        [[nodiscard]] constexpr size_type max_size( ) const noexcept
        {
            return std::numeric_limits<size_type>::max() / static_cast<size_type>( sizeof( T ) );
        }
        [[nodiscard]] constexpr size_type capacity( ) const noexcept
        {
            return capacity_;
        }
        [[nodiscard]] constexpr T& operator[]( size_type i ) noexcept
        {
            return data( )[i];
        }
        [[nodiscard]] constexpr const T& operator[]( size_type i ) const noexcept
        {
            return data( )[i];
        }

        void clear( )
        {
            if constexpr ( std::is_trivially_destructible_v<T> == false )
            {
                auto dataPtr = data( );
                if ( data( ) )
                {
                    std::destroy( dataPtr, &dataPtr[size_] );
                }
            }
            size_ = 0;
        }
        [[nodiscard]] constexpr iterator begin( ) noexcept
        {
            return iterator( data_.get( ) );
        }
        [[nodiscard]] constexpr const_iterator begin( ) const noexcept
        {
            return const_iterator( const_cast<T*>( data_.get( ) ) );
        }

        [[nodiscard]] constexpr const_iterator cbegin( ) const noexcept
        {
            return const_iterator( const_cast<T*>( data_.get( ) ) );
        }

        [[nodiscard]] constexpr iterator end( ) noexcept
        {
            return iterator( data_.get( ) + size_ );
        }
        [[nodiscard]] constexpr const_iterator end( ) const noexcept
        {
            return const_iterator( const_cast<T*>( data_.get( ) + size_ ) );
        }
        [[nodiscard]] constexpr const_iterator cend( ) const noexcept
        {
            return const_iterator( const_cast<T*>( data_.get( ) + size_ ) );
        }


        [[nodiscard]] constexpr reverse_iterator rbegin( ) noexcept
        {
            return reverse_iterator( end( ) );
        }

        [[nodiscard]] constexpr const_reverse_iterator rbegin( ) const noexcept
        {
            return const_reverse_iterator( end( ) );
        }

        [[nodiscard]] constexpr reverse_iterator rend( ) noexcept
        {
            return reverse_iterator( begin( ) );
        }

        [[nodiscard]] constexpr const_reverse_iterator rend( ) const noexcept
        {
            return const_reverse_iterator( begin( ) );
        }

        [[nodiscard]] constexpr const_reverse_iterator crbegin( ) const noexcept
        {
            return rbegin( );
        }

        [[nodiscard]] constexpr const_reverse_iterator crend( ) const noexcept
        {
            return rend( );
        }


        [[nodiscard]] constexpr pointer data( ) noexcept
        {
            return data_.get( );
        }
        [[nodiscard]] constexpr const_pointer data( ) const noexcept
        {
            return data_.get( );
        }

        [[nodiscard]] constexpr reference front( ) noexcept
        {
            return *data_.get( );
        }
        [[nodiscard]] constexpr const_reference front( ) const noexcept
        {
            return *data_.get( );
        }
        [[nodiscard]] constexpr reference back( ) noexcept
        {
            return *( data_.get( ) + ( size_ - 1 ) );
        }
        [[nodiscard]] constexpr const_reference back( ) const noexcept
        {
            return *( data_.get( ) + ( size_ - 1 ) );
        }
        constexpr void swap( Vector<T>& other )
        {
            std::swap( size_, other.size_ );
            std::swap( capacity_, other.capacity_ );
            std::swap( data_, other.data_ );
        }

        void resize( size_type newSize )
        {
            if ( newSize > size_ )
            {
                if ( newSize > capacity_ )
                {
                    auto newCapacity = CapacityForSize( newSize );
                    reserve( newCapacity );
                }
                if constexpr ( CanZeroInitialize )
                {
                    memset( &data( )[size_], 0, ( newSize - size_ ) * sizeof( T ) );
                }
                else
                {
                    std::uninitialized_default_construct( &data( )[size_], &data( )[newSize] );
                }
                size_ = newSize;
            }
            else if ( newSize < size_ )
            {
                if ( newSize < 0 )
                {
                    newSize = 0;
                }
                if constexpr ( std::is_trivially_destructible_v<T> == false )
                {
                    std::destroy( &data( )[newSize], &data( )[size_] );
                }
                size_ = newSize;
            }
        }

        void resize( size_type newSize, const T& v )
        {
            if ( newSize > size_ )
            {
                if ( newSize > capacity_ )
                {
                    auto newCapacity = CapacityForSize( newSize );
                    reserve( newCapacity );
                }
                std::uninitialized_fill( &data( )[size_], &data( )[newSize], v );
                size_ = newSize;
            }
            else if ( newSize < size_ )
            {
                if ( newSize < 0 )
                {
                    newSize = 0;
                }
                if constexpr ( std::is_trivially_destructible_v<T> == false )
                {
                    std::destroy( &data( )[newSize], &data( )[size_] );
                }
                size_ = newSize;
            }
        }

        // Resize a vector to a smaller size, guaranteed not to cause a reallocation
        void shrink( size_type newSize )
        {
            if ( newSize < 0 )
            {
                newSize = 0;
            }
            if ( newSize < size_ )
            {
                if constexpr ( std::is_trivially_destructible_v<T> == false )
                {
                    std::destroy( &data( )[newSize], &data( )[size_] );
                }
                size_ = newSize;
            }
        }

        void reserve( size_type requiredCapacity )
        {
            if ( requiredCapacity > capacity_ )
            {
                requiredCapacity = CapacityForSize( requiredCapacity );
                auto newData = Allocate( requiredCapacity );
                auto dataPtr = data( );
                if ( dataPtr )
                {
                    auto newDataPtr = newData.get( );
                    if constexpr ( std::is_trivially_copyable_v<T> )
                    {
                        memcpy( newDataPtr, dataPtr, static_cast<size_t>( size_ ) * sizeof( T ) );
                    }
                    else 
                    {
                        for ( size_type i = 0; i < size_; i++ )
                        {
                            if constexpr ( std::is_move_constructible_v<T> )
                            {
                                new ( &newDataPtr[i] ) T( std::move( dataPtr[i] ) );
                            }
                            else
                            {
                                new ( &newDataPtr[i] ) T( dataPtr[i] );
                            }

                            dataPtr[i].~T( );
                        }
                    }
                }
                data_ = std::move(newData);
                capacity_ = requiredCapacity;
            }
        }

    private:
        void expand( size_type uninitializedStart, size_type uninitializedEnd, size_type requiredCapacity )
        {
            auto newData = Allocate( requiredCapacity );
            auto dataPtr = data( );
            if ( dataPtr )
            {
                auto newDataPtr = newData.get( );
                if constexpr ( std::is_trivially_copyable_v<T> )
                {
                    memcpy( newDataPtr, dataPtr, static_cast<size_t>( uninitializedStart ) * sizeof( T ) );
                    auto remaining = size_ - uninitializedStart;
                    memcpy( newDataPtr + uninitializedEnd, dataPtr + uninitializedStart, static_cast<size_t>( remaining ) * sizeof( T ) );
                }
                else 
                {
                    size_type i = 0;
                    for ( ; i < uninitializedStart; i++ )
                    {
                        if constexpr ( std::is_move_constructible_v<T> )
                        {
                            new ( &newDataPtr[i] ) T( std::move( dataPtr[i] ) );
                        }
                        else
                        {
                            new ( &newDataPtr[i] ) T( dataPtr[i] );
                        }
                        dataPtr[i].~T( );
                    }

                    auto distance = uninitializedEnd - uninitializedStart;

                    for ( ; i < size_; i++ )
                    {
                        if constexpr ( std::is_move_constructible_v<T> )
                        {
                            new ( &newDataPtr[distance + i] ) T( std::move( dataPtr[i] ) );
                        }
                        else
                        {
                            new ( &newDataPtr[distance + i] ) T( dataPtr[i] );
                        }
                        dataPtr[i].~T( );
                    }
                }
            }
            data_ = std::move( newData );
            capacity_ = requiredCapacity;
        }

        void expand( size_type offset, size_type requiredCapacity )
        {
            auto newData = Allocate( requiredCapacity );
            auto dataPtr = data( );
            if ( dataPtr )
            {
                auto newDataPtr = newData.get( );
                if constexpr ( std::is_trivially_copyable_v<T> )
                {
                    memcpy( newDataPtr, dataPtr, static_cast<size_t>( offset ) * sizeof( T ) );
                    auto remaining = size_ - offset;
                    memcpy( newDataPtr + offset + 1, dataPtr + offset, static_cast<size_t>( remaining ) * sizeof( T ) );
                }
                else
                {
                    size_type i = 0;
                    for ( ; i < offset; i++ )
                    {
                        if constexpr ( std::is_move_constructible_v<T> )
                        {
                            new ( &newDataPtr[i] ) T( std::move( dataPtr[i] ) );
                        }
                        else
                        {
                            new ( &newDataPtr[i] ) T( dataPtr[i] );
                        }
                        /*
                        if constexpr ( std::is_trivially_destructible_v<T> == false )
                        {
                            dataPtr[i].~T( );
                        }
                        */
                    }

                    for ( ; i < size_; i++ )
                    {
                        if constexpr ( std::is_move_constructible_v<T> )
                        {
                            new ( &newDataPtr[i+1] ) T( std::move( dataPtr[i] ) );
                        }
                        else
                        {
                            new ( &newDataPtr[i+1] ) T( dataPtr[i] );
                        }
                        /*
                        if constexpr ( std::is_trivially_destructible_v<T> == false )
                        {
                            dataPtr[i].~T( );
                        }
                        */
                    }
                    
                    if constexpr ( std::is_trivially_destructible_v<T> == false )
                    {
                        for ( i = 0; i < size_; i++ )
                        {
                            dataPtr[i].~T( );
                        }
                    }
                    
                }
            }
            data_ = std::move( newData );
            capacity_ = requiredCapacity;
        }

    public:


        template<typename ... Args>
        reference emplace_back( Args&&... args )
        {
            if ( size_ == capacity_ )
            {
                auto requiredCapacity = CapacityForSize( size_ + 1 );
                reserve( requiredCapacity );
            }
            auto* ptr = std::construct_at( &data_.get()[size_], std::forward<Args>( args )... );
            size_++;
            return *ptr;
        }


        template<typename ... Args>
        reference emplace_front( Args&&... args )
        {
            if ( size_ < capacity_ ) [[likely]]
            {
                auto dataPtr = data( );
                if ( size_ )
                {
                    if constexpr ( std::is_trivially_copyable_v<T> )
                    {
                        memmove( dataPtr + 1, dataPtr, size_ * sizeof( T ) );
                        new ( dataPtr ) T( std::forward<Args>( args )... );
                    }
                    else 
                    {

                        new ( &dataPtr[size_] ) T( std::move( dataPtr[size_ - 1] ) );
                        auto remaining = size_ - 1;
                        while ( remaining )
                        {
                            --remaining;
                            if constexpr ( std::is_move_assignable_v<T> )
                            {
                                dataPtr[remaining + 1] = std::move( dataPtr[remaining] );
                            }
                            else
                            {
                                dataPtr[remaining + 1] = dataPtr[remaining];
                            }
                        }
                        *dataPtr = T( std::forward<Args>( args )... );
                    }
                }
                else
                {
                    new ( dataPtr ) T( std::forward<Args>( args )... );
                }
                size_++;
                return *dataPtr;
            }
            else
            {
                auto requiredCapacity = CapacityForSize( size_ + 1 );
                expand( 0, requiredCapacity );
                auto dataPtr = data( );
                new ( dataPtr ) T( std::forward<Args>( args )... );
                size_++;
                return *dataPtr;
            }
        }


        template< class... Args >
        iterator emplace( const_iterator it, Args&&... args )
        {
            auto* itPtr = it.ptr_;
            auto dataPtr = data_.get( );
            auto endPtr = dataPtr + size_;
            if ( size_ < capacity_ ) [[likely]]
            {
                if ( itPtr < endPtr ) [[likely]]
                {
                    auto remaining = endPtr - itPtr;
                    if constexpr ( std::is_trivially_copyable_v<T> )
                    {
                        memmove( itPtr + 1, itPtr, remaining * sizeof( T ) );
                        new ( itPtr ) T( std::forward<Args>( args )... );
                    }
                    else
                    {
                        /*
                        if constexpr ( std::is_move_assignable_v<T> )
                        {
                            auto tmp = std::move( *itPtr );
                            *itPtr = T( std::forward<Args>( args )... );
                            auto ptr = itPtr + 1;
                            while ( ptr < endPtr )
                            {
                                *ptr = std::move( tmp );
                                ptr++;
                                tmp = std::move( *ptr );
                            }
                            new ( endPtr ) T( std::move( tmp ) );
                        }
                        else
                        {
                            auto tmp = *itPtr;
                            *itPtr = T( std::forward<Args>( args )... );
                            auto ptr = itPtr + 1;
                            while ( ptr < endPtr )
                            {
                                *ptr = tmp;
                                ptr++;
                                tmp = *ptr;
                            }
                            new ( endPtr ) T( tmp );
                        }
                        */

                        /*
                        auto destPtr = endPtr;
                        auto ptr = endPtr - 1;
                        new ( destPtr ) T( std::move( *( ptr ) ) );
                        
                        while ( ptr > itPtr )
                        {
                            if constexpr ( std::is_move_assignable_v<T> )
                            {
                                *( --destPtr ) = std::move( *--ptr );
                            }
                            else
                            {
                                *( --destPtr ) = *--ptr;
                            }
                        }
                        *itPtr = T( std::forward<Args>( args )... );
                        */
                        
                        new ( endPtr ) T( std::move( *(endPtr - 1) ) );
                        
                        while ( remaining )
                        {
                            --remaining;
                            if constexpr ( std::is_move_assignable_v<T> )
                            {
                                itPtr[remaining + 1] = std::move( itPtr[remaining] );
                            }
                            else
                            {
                                itPtr[remaining + 1] = itPtr[remaining];
                            }
                        }
                        *itPtr = T( std::forward<Args>( args )... );
                        
                    }
                }
                else
                {
                    new ( endPtr ) T( std::forward<Args>( args )... );
                }
                size_++;
                return iterator( itPtr );
            }
            else
            {
                auto offset = itPtr - dataPtr;
                if ( itPtr < endPtr )
                {
                    auto requiredCapacity = CapacityForSize( size_ + 1 );
                    expand( offset, requiredCapacity );
                }
                else
                {
                    reserve( size_ + 1 );
                }
                dataPtr = data_.get( );
                itPtr = dataPtr + offset;
                new ( itPtr ) T( std::forward<Args>( args )... );
                size_++;
                return iterator( itPtr );
            }
        }


        
        void push_back( const T& v )
        {
            if ( size_ == capacity_ )
            {
                auto requiredCapacity = CapacityForSize( size_ + 1 );
                reserve( requiredCapacity );
            }
            std::construct_at( &data_.get( )[size_], v );
            size_++;
        }

        void push_back( T&& v )
        {
            if ( size_ == capacity_ )
            {
                auto requiredCapacity = CapacityForSize( size_ + 1 );
                reserve( requiredCapacity );
            }
            std::construct_at( &data_.get( )[size_], std::move( v ) );
            size_++;
        }


        void pop_back( )
        {
            if ( size_ )
            {
                if constexpr ( std::is_trivially_destructible_v<T> == false )
                {
                    auto dataPtr = data_.get( );
                    dataPtr->~T( );
                }
                size_--;
            }
        }
        void push_front( const T& v )
        {
            if ( size_ == 0 )
            {
                push_back( v );
            }
            else
            {
                insert( begin( ), v );
            }
        }

        void push_front( T&& v )
        {
            if ( size_ == 0 )
            {
                push_back( std::move( v ) );
            }
            else
            {
                insert( begin( ), std::move( v ) );
            }
        }



        iterator erase( const_iterator it )
        {
            auto itPtr = it.ptr_;
            auto dataPtr = data_.get( );
            auto endPtr = dataPtr + size_;
            if ( itPtr < endPtr )
            {
                auto newEndPtr = endPtr - 1;

                if ( itPtr < newEndPtr )
                {
                    if constexpr ( std::is_trivially_copyable_v<T> )
                    {
                        if constexpr ( std::is_trivially_destructible_v<T> == false )
                        {
                            itPtr->~T( );
                        }
                        memcpy( itPtr, itPtr + 1, static_cast<size_t>( ( endPtr - itPtr ) ) * sizeof( T ) );
                    }
                    else
                    {
                        while ( itPtr < newEndPtr )
                        {
                            if constexpr ( std::is_move_assignable_v<T> )
                            {
                                *itPtr = std::move( *( itPtr + 1 ) );
                            }
                            else
                            {
                                *itPtr = *( itPtr + 1 );
                            }
                            itPtr++;
                        }
                        if constexpr ( std::is_trivially_destructible_v<T> == false )
                        {
                            newEndPtr->~T( );
                        }
                    }
                }
                else
                {
                    if constexpr ( std::is_trivially_destructible_v<T> == false )
                    {
                        itPtr->~T( );
                    }
                }
                size_--;
            }
            return iterator( it.ptr_ );
        }

        iterator erase( const_iterator it, const_iterator itLast )
        {
            auto itPtr = it.ptr_;
            auto itLastPtr = itLast.ptr_;
            auto dataPtr = data_.get( );
            auto endPtr = dataPtr + size_;
            
            if ( itPtr < endPtr )
            {
                auto numberOfItemsToErase = itLastPtr - itPtr;

                if ( itPtr + numberOfItemsToErase < endPtr )
                {
                    auto remaining = endPtr - itLastPtr;
                    if constexpr ( std::is_trivially_copyable_v<T> )
                    {
                        if constexpr ( std::is_trivially_destructible_v<T> == false )
                        {
                            for ( auto ptr = itPtr; ptr < itLastPtr; ++ptr )
                            {
                                ptr->~T( );
                            }
                        }
                        memcpy( itPtr, itLastPtr, static_cast<size_t>( remaining ) * sizeof( T ) );
                    }
                    else
                    {
                        while ( itLastPtr < endPtr )
                        {
                            if constexpr ( std::is_move_assignable_v<T> )
                            {
                                *itPtr = std::move( *itLastPtr );
                            }
                            else
                            {
                                *itPtr = *itLastPtr;
                            }
                            itPtr++;
                            itLastPtr++;
                        }
                        if constexpr ( std::is_trivially_destructible_v<T> == false )
                        {
                            while ( itPtr < endPtr )
                            {
                                itPtr->~T( );
                                itPtr++;
                            }
                        }
                    }
                }
                else
                {
                    if constexpr ( std::is_trivially_destructible_v<T> == false )
                    {
                        while ( itPtr < endPtr )
                        {
                            itPtr->~T( );
                            itPtr++;
                        }
                    }
                }
                size_ -= numberOfItemsToErase;
            }
            return iterator( it.ptr_ );
        }





        iterator erase_unsorted( const_iterator it )
        {
            auto itPtr = it.ptr_;
            auto dataPtr = data_.get( );
            const ptrdiff_t off = itPtr - dataPtr;
            if ( itPtr < dataPtr + size_ - 1 )
                memcpy( dataPtr + off, dataPtr + size_ - 1, sizeof( T ) );
            size_--;
            return begin() + off;
        }
        iterator insert( iterator it, const T& v )
        {
            auto itPtr = it.ptr_;
            auto dataPtr = data_.get( );
            auto endPtr = end( ).ptr_;
            const ptrdiff_t offset = itPtr - dataPtr;

            if ( size_ == capacity_ )
            {
                auto requiredCapacity = CapacityForSize( size_ + 1 );
                reserve( requiredCapacity );
                dataPtr = data_.get( );
            }


            if ( offset < size_ )
            {
                memmove( dataPtr + offset + 1, dataPtr + offset, ( (size_t)size_ - (size_t)offset ) * sizeof( T ) );
            }
            memcpy( dataPtr + offset, &v, sizeof( v ) );
            size_++;
            return begin() + offset;
        }

        iterator insert( iterator it, T&& v )
        {
            auto itPtr = it.ptr_;
            auto dataPtr = data_.get( );
            auto endPtr = end( ).ptr_;
            const ptrdiff_t offset = itPtr - dataPtr;

            if ( size_ == capacity_ )
            {
                auto requiredCapacity = CapacityForSize( size_ + 1 );
                reserve( requiredCapacity );
                dataPtr = data_.get( );
            }


            if ( offset < size_ )
            {
                memmove( dataPtr + offset + 1, dataPtr + offset, ( (size_t)size_ - (size_t)offset ) * sizeof( T ) );
            }
            memcpy( dataPtr + offset, &v, sizeof( v ) );
            size_++;
            return begin( ) + offset;
        }

        [[nodiscard]] bool contains( const T& v ) const
        {
            const T* data = data_.get( );
            const T* data_end = data + size_;
            while ( data < data_end )
            {
                if ( *data++ == v )
                {
                    return true;
                }
            }
            return false;
        }
        [[nodiscard]] iterator find( const T& v )
        {
            T* data = data_.get( );
            const T* data_end = data + size_;
            while ( data < data_end )
            {
                if ( *data != v ) [[likely]]
                {
                    ++data;
                }
                else
                {
                    break;
                }
            }
            return iterator( data );
        }
        [[nodiscard]] const_iterator find( const T& v ) const
        {
            const T* data = data_.get( );
            const T* data_end = data + size_;
            while ( data < data_end )
            {
                if ( *data != v ) [[likely]]
                {
                    ++data;
                }
                else
                {
                    break;
                }
            }
            return const_iterator( data );
        }
        bool find_erase( const T& v )
        {
            auto it = find( v );
            if ( it != end( ) )
            {
                erase( it );
                return true;
            }
            return false;
        }
        bool find_erase_unsorted( const T& v )
        {
            auto it = find( v );
            if ( it != end( ) )
            {
                erase_unsorted( it );
                return true;
            }
            return false;
        }
        size_type index_from_ptr( const T* it ) const
        {
            const ptrdiff_t off = it - data_.get( );
            return (size_type)off;
        }
    };


    template <typename It>
        requires IsIterator_v<It>
    Vector( It, It ) -> Vector<IteratorValue_t<It>>;

}

#endif
