#pragma once
#ifndef __HCCVECTOR_H__
#define __HCCVECTOR_H__

#include <HCCLib.h>

namespace Harlinn::Common::Core
{
    template<typename T>
    class Vector;
    template<typename T>
    class OwnerVector;

    template< typename VectorT >
    class VectorConstIterator
    {
        template<typename T>
        friend class Vector;
        template<typename T>
        friend class OwnerVector;
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

        constexpr VectorConstIterator operator++( int ) noexcept
        {
            VectorConstIterator result = *this;
            ptr_++;
            return result;
        }

        constexpr VectorConstIterator& operator--( ) noexcept
        {
            ptr_--;
            return *this;
        }

        constexpr VectorConstIterator operator--( int ) noexcept
        {
            VectorConstIterator result = *this;
            ptr_--;
            return result;
        }

        constexpr VectorConstIterator& operator += ( const difference_type offset ) noexcept
        {
            ptr_ += offset;
            return *this;
        }

        [[nodiscard]] constexpr VectorConstIterator operator + ( const difference_type offset ) const noexcept
        {
            VectorConstIterator result( ptr_ + offset );
            return result;
        }

        constexpr VectorConstIterator& operator-=( const difference_type offset ) noexcept
        {
            ptr_ -= offset;
            return *this;
        }


        [[nodiscard]] constexpr VectorConstIterator operator - ( const difference_type offset ) const noexcept
        {
            VectorConstIterator result( ptr_ - offset );
            return result;
        }

        [[nodiscard]] constexpr difference_type operator - ( const VectorConstIterator& other ) const noexcept
        {
            return static_cast<difference_type>( ptr_ - other.ptr_ );
        }


        [[nodiscard]] constexpr reference operator[]( const difference_type offset ) const noexcept
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
        template<typename T>
        friend class OwnerVector;
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

        constexpr VectorIterator operator++( int ) noexcept
        {
            VectorIterator result = *this;
            Base::ptr_++;
            return result;
        }

        constexpr VectorIterator& operator--( ) noexcept
        {
            Base::ptr_--;
            return *this;
        }

        constexpr VectorIterator operator--( int ) noexcept
        {
            VectorIterator result = *this;
            Base::ptr_--;
            return result;
        }

        constexpr VectorIterator& operator += ( const difference_type offset ) noexcept
        {
            Base::ptr_ += offset;
            return *this;
        }

        template <typename DiffT>
        requires IsInteger<DiffT>
        [[nodiscard]] constexpr VectorIterator operator + ( const DiffT offset ) const noexcept
        {
            VectorIterator result( Base::ptr_ + static_cast<size_t>(offset) );
            return result;
        }

        [[nodiscard]] constexpr difference_type operator - ( const VectorIterator& other ) const noexcept
        {
            return static_cast<difference_type>( Base::ptr_ - other.ptr_ );
        }


        constexpr VectorIterator& operator-=( const difference_type offset ) noexcept
        {
            Base::ptr_ -= offset;
            return *this;
        }


        template <typename DiffT>
        requires IsInteger<DiffT>
        [[nodiscard]] constexpr VectorIterator operator - ( const DiffT offset ) const noexcept
        {
            VectorIterator result( Base::ptr_ - static_cast<size_t>( offset ) );
            return result;
        }

        [[nodiscard]] constexpr reference operator[]( const difference_type offset ) const noexcept
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
            size_type currentCapacity = allocatedEnd_ - data_.get( );
            size_type newCapacity = currentCapacity ? ( currentCapacity + currentCapacity / 2 ) : 16;
            return newCapacity > sz ? newCapacity : sz;
        }

        
        DataPtr data_;
        T* end_ = nullptr;
        T* allocatedEnd_ = nullptr;
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
                auto newDataPtr = newData.get( );
                std::uninitialized_fill_n( newDataPtr, count, val );
                data_ = std::move( newData );
                end_ = newDataPtr + count;
                allocatedEnd_ = newDataPtr + requiredCapacity;
            }
        }

        Vector( size_type count ) noexcept
        {
            if ( count )
            {
                auto requiredCapacity = CapacityForSize( count );
                DataPtr newData( Allocate( requiredCapacity ) );
                auto newDataPtr = newData.get( );
                auto endPtr = newDataPtr + count;
                if constexpr ( CanZeroInitialize )
                {
                    memset( newDataPtr, 0, count * sizeof( T ) );
                }
                else
                {
                    std::uninitialized_default_construct( newDataPtr, endPtr );
                }
                data_ = std::move( newData );
                end_ = endPtr;
                allocatedEnd_ = newDataPtr + requiredCapacity;
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
                auto newDataPtr = newData.get( );
                std::uninitialized_copy( first, last, newDataPtr );
                data_ = std::move( newData );
                end_ = newDataPtr + count;
                allocatedEnd_ = newDataPtr + requiredCapacity;
            }
        }


        Vector( std::initializer_list<T> values )
            : Vector( values.begin(), values.end() )
        {

        }


        Vector( const Vector& other )
        {
            auto otherDataPtr = const_cast<T*>( other.data_.get( ) );
            auto otherEndPtr = const_cast<T*>( other.end_ );
            if ( otherDataPtr != otherEndPtr )
            {
                auto size = otherEndPtr - otherDataPtr;
                auto requiredCapacity = CapacityForSize( size );
                DataPtr newData( Allocate( requiredCapacity ) );
                auto newDataPtr = newData.get( );
                std::uninitialized_copy( otherDataPtr, otherEndPtr, newDataPtr );

                data_ = std::move( newData );
                end_ = newDataPtr + size;
                allocatedEnd_ = newDataPtr + requiredCapacity;
            }
        }

        constexpr Vector( Vector&& other ) noexcept
            : data_( other.data_.release( ) ), end_( other.end_ ), allocatedEnd_( other.allocatedEnd_ )
        {
            other.end_ = nullptr;
            other.allocatedEnd_ = nullptr;
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
            auto dataPtr = data( );
            auto otherDataPtr = other.data( );
            if ( dataPtr != otherDataPtr )
            {
                auto selfCapacity = allocatedEnd_ - dataPtr;
                auto otherSize = other.end_ - otherDataPtr;
                if ( selfCapacity < otherSize )
                {
                    auto requiredCapacity = CapacityForSize( otherSize );
                    DataPtr newData( Allocate( requiredCapacity ) );
                    auto newDataPtr = newData.get( );
                    
                    if constexpr ( std::is_trivially_copyable_v<T> )
                    {
                        memcpy( newDataPtr, otherDataPtr, static_cast<size_t>( otherSize ) * sizeof(T) );
                    }
                    else
                    {
                        std::uninitialized_copy( otherDataPtr, const_cast<T*>( other.end_ ), newDataPtr );
                    }
                    if constexpr ( std::is_trivially_destructible_v<T> == false )
                    {
                        std::destroy( otherDataPtr, other.end_ );
                    }

                    data_ = std::move( newData );
                    end_ = newDataPtr + otherSize;
                    allocatedEnd_ = newDataPtr + requiredCapacity;
                }
                else
                {
                    auto selfSize = size( );
                    
                    if ( selfSize <= otherSize )
                    {
                        if constexpr ( std::is_trivially_copyable_v<T> )
                        {
                            memcpy( dataPtr, otherDataPtr, static_cast<size_t>( otherSize ) * sizeof( T ) );
                        }
                        else
                        {
                            std::copy( otherDataPtr, &otherDataPtr[selfSize], dataPtr );
                            std::uninitialized_copy( &otherDataPtr[selfSize], other.end_, &dataPtr[selfSize] );
                        }
                        end_ = dataPtr + otherSize;
                    }
                    else
                    {
                        if constexpr ( std::is_trivially_copyable_v<T> )
                        {
                            memcpy( dataPtr, otherDataPtr, static_cast<size_t>( otherSize ) * sizeof( T ) );
                        }
                        else
                        {
                            std::copy( otherDataPtr, const_cast<T*>( other.end_ ), dataPtr );
                        }
                        if constexpr ( std::is_trivially_destructible_v<T> == false )
                        {
                            std::destroy( &dataPtr[otherSize], end_ );
                        }
                        end_ = dataPtr + otherSize;
                    }
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
            std::swap( data_, other.data_ );
            std::swap( end_, other.end_ );
            std::swap( allocatedEnd_, other.allocatedEnd_ );
            return *this;
        }


        [[nodiscard]] bool Equals( Vector& other ) const
        {
            auto dataPtr = data_.get( );
            auto otherDataPtr = other.data_.get( );
            if ( dataPtr != otherDataPtr ) [[likely]]
            {
                auto otherEndPtr = other.end_;
                auto selfSize = end_ - dataPtr;
                auto otherSize = otherEndPtr - otherDataPtr;

                if ( selfSize != otherSize )
                {
                    auto endPtr = end_;
                    while ( dataPtr < endPtr )
                    {
                        if ( *dataPtr != *otherDataPtr )
                        {
                            return false;
                        }
                        dataPtr++;
                        otherDataPtr++;
                    }
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return true;
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
            return data_.get() == end_;
        }
        [[nodiscard]] constexpr size_type size( ) const noexcept
        {
            return end_ - data_.get( );
        }
        [[nodiscard]] constexpr size_type size_in_bytes( ) const noexcept
        {
            return size( ) * static_cast<size_type>(sizeof( T ));
        }
        [[nodiscard]] constexpr size_type max_size( ) const noexcept
        {
            return std::numeric_limits<size_type>::max() / static_cast<size_type>( sizeof( T ) );
        }
        [[nodiscard]] constexpr size_type capacity( ) const noexcept
        {
            return allocatedEnd_ - data_.get( );
        }
        [[nodiscard]] constexpr reference operator[]( size_type i ) noexcept
        {
            return data_.get( )[i];
        }
        [[nodiscard]] constexpr const_reference operator[]( size_type i ) const noexcept
        {
            return data_.get( )[i];
        }

        void clear( )
        {
            auto dataPtr = data_.get( );

            if constexpr ( std::is_trivially_destructible_v<T> == false )
            {
                if ( dataPtr != end_ )
                {
                    std::destroy( dataPtr, end_ );
                }
            }
            end_ = dataPtr;
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
            return iterator( end_ );
        }
        [[nodiscard]] constexpr const_iterator end( ) const noexcept
        {
            return const_iterator( const_cast<T*>( end_ ) );
        }
        [[nodiscard]] constexpr const_iterator cend( ) const noexcept
        {
            return const_iterator( const_cast<T*>( end_ ) );
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
            return *( end_ - 1 );
        }
        [[nodiscard]] constexpr const_reference back( ) const noexcept
        {
            return *( end_ - 1 );
        }
        constexpr void swap( Vector<T>& other )
        {
            std::swap( data_, other.data_ );
            std::swap( end_, other.end_ );
            std::swap( allocatedEnd_, other.allocatedEnd_ );
        }

        void resize( size_type newSize )
        {
            auto dataPtr = data_.get( );
            auto currentSize = end_ - dataPtr;
            if ( newSize > currentSize )
            {
                auto currentCapacity = allocatedEnd_ - dataPtr;
                if ( newSize > currentCapacity )
                {
                    auto newCapacity = CapacityForSize( newSize );
                    reserve( newCapacity );
                    dataPtr = data_.get( );
                }
                auto newEndPtr = dataPtr + newSize;
                if constexpr ( CanZeroInitialize )
                {
                    memset( end_, 0, static_cast<size_t>( newEndPtr - end_ ) * sizeof( T ) );
                }
                else
                {
                    std::uninitialized_default_construct( end_, newEndPtr );
                }
                end_ = newEndPtr;
            }
            else if ( newSize < currentSize )
            {
                if ( newSize < 0 )
                {
                    newSize = 0;
                }
                auto newEndPtr = dataPtr + newSize;
                if constexpr ( std::is_trivially_destructible_v<T> == false )
                {
                    std::destroy( newEndPtr, end_ );
                }
                end_ = newEndPtr;
            }
        }

        void resize( size_type newSize, const T& v )
        {
            auto dataPtr = data_.get( );
            auto currentSize = end_ - dataPtr;
            if ( newSize > currentSize )
            {
                auto currentCapacity = allocatedEnd_ - dataPtr;
                if ( newSize > currentCapacity )
                {
                    auto newCapacity = CapacityForSize( newSize );
                    reserve( newCapacity );
                    dataPtr = data_.get( );
                }
                auto newEndPtr = dataPtr + newSize;
                std::uninitialized_fill( end_, newEndPtr, v );
                end_ = newEndPtr;
            }
            else if ( newSize < currentSize )
            {
                if ( newSize < 0 )
                {
                    newSize = 0;
                }
                auto newEndPtr = dataPtr + newSize;
                if constexpr ( std::is_trivially_destructible_v<T> == false )
                {
                    std::destroy( newEndPtr, end_ );
                }
                end_ = newEndPtr;
            }
        }

        // Resize a vector to a smaller size, guaranteed not to cause a reallocation
        void shrink( size_type newSize )
        {
            if ( newSize < 0 )
            {
                newSize = 0;
            }
            auto dataPtr = data_.get( );
            auto newEndPtr = dataPtr + newSize;
            if constexpr ( std::is_trivially_destructible_v<T> == false )
            {
                std::destroy( newEndPtr, end_ );
            }
            end_ = newEndPtr;
        }

        void reserve( size_type requiredCapacity )
        {
            auto dataPtr = data_.get( );
            if ( dataPtr + requiredCapacity > allocatedEnd_ )
            {
                requiredCapacity = CapacityForSize( requiredCapacity );
                auto newData = Allocate( requiredCapacity );
                auto newDataPtr = newData.get( );
                auto currentSize = end_ - dataPtr;
                if ( dataPtr )
                {
                    if constexpr ( std::is_trivially_copyable_v<T> )
                    {
                        memcpy( newDataPtr, dataPtr, static_cast<size_t>( currentSize ) * sizeof( T ) );
                    }
                    else 
                    {
                        auto destPtr = newDataPtr;
                        while ( dataPtr < end_ )
                        {
                            if constexpr ( std::is_move_constructible_v<T> )
                            {
                                new ( destPtr ) T( std::move( *dataPtr ) );
                            }
                            else
                            {
                                new ( destPtr ) T( *dataPtr );
                            }
                            dataPtr->~T( );

                            dataPtr++;
                            destPtr++;
                        }
                    }
                }
                data_ = std::move(newData);
                end_ = newDataPtr + currentSize;
                allocatedEnd_ = newDataPtr + requiredCapacity;
            }
        }

    private:
        void expand( size_type uninitializedStart, size_type uninitializedEnd, size_type requiredCapacity )
        {
            auto newData = Allocate( requiredCapacity );
            auto newDataPtr = newData.get( );

            auto dataPtr = data( );
            auto currentSize = end_ - dataPtr;

            if ( dataPtr )
            {
                if constexpr ( std::is_trivially_copyable_v<T> )
                {
                    memcpy( newDataPtr, dataPtr, static_cast<size_t>( uninitializedStart ) * sizeof( T ) );
                    auto remaining = currentSize - uninitializedStart;
                    memcpy( newDataPtr + uninitializedEnd, dataPtr + uninitializedStart, static_cast<size_t>( remaining ) * sizeof( T ) );
                }
                else 
                {
                    auto destPtr = newDataPtr;
                    auto copy1End = dataPtr + uninitializedStart;
                    while ( dataPtr < copy1End )
                    {
                        if constexpr ( std::is_move_constructible_v<T> )
                        {
                            new ( destPtr ) T( std::move( *dataPtr ) );
                        }
                        else
                        {
                            new ( destPtr ) T( *dataPtr );
                        }
                        dataPtr->~T( );

                        dataPtr++;
                        destPtr++;
                    }

                    auto distance = uninitializedEnd - uninitializedStart;
                    destPtr += distance;

                    while ( dataPtr < end_ )
                    {
                        if constexpr ( std::is_move_constructible_v<T> )
                        {
                            new ( destPtr ) T( std::move( *dataPtr ) );
                        }
                        else
                        {
                            new ( destPtr ) T( *dataPtr );
                        }
                        dataPtr->~T( );

                        dataPtr++;
                        destPtr++;
                    }
                }
            }
            data_ = std::move( newData );
            end_ = newDataPtr + currentSize;
            allocatedEnd_ = newDataPtr + requiredCapacity;
        }

        void expand( size_type offset, size_type requiredCapacity )
        {
            auto newData = Allocate( requiredCapacity );
            auto newDataPtr = newData.get( );

            auto dataPtr = data( );
            auto currentSize = end_ - dataPtr;

            if ( dataPtr )
            {
                if constexpr ( std::is_trivially_copyable_v<T> )
                {
                    memcpy( newDataPtr, dataPtr, static_cast<size_t>( offset ) * sizeof( T ) );
                    auto remaining = currentSize - offset;
                    memcpy( newDataPtr + offset + 1, dataPtr + offset, static_cast<size_t>( remaining ) * sizeof( T ) );
                }
                else
                {
                    auto destPtr = newDataPtr;
                    auto copy1End = dataPtr + offset;
                    while ( dataPtr < copy1End )
                    {
                        if constexpr ( std::is_move_constructible_v<T> )
                        {
                            new ( destPtr ) T( std::move( *dataPtr ) );
                        }
                        else
                        {
                            new ( destPtr ) T( *dataPtr );
                        }
                        dataPtr->~T( );

                        dataPtr++;
                        destPtr++;
                    }

                    destPtr++;

                    while ( dataPtr < end_ )
                    {
                        if constexpr ( std::is_move_constructible_v<T> )
                        {
                            new ( destPtr ) T( std::move( *dataPtr ) );
                        }
                        else
                        {
                            new ( destPtr ) T( *dataPtr );
                        }
                        dataPtr->~T( );

                        dataPtr++;
                        destPtr++;
                    }
                }
            }
            data_ = std::move( newData );
            end_ = newDataPtr + currentSize;
            allocatedEnd_ = newDataPtr + requiredCapacity;
        }

    public:


        template<typename ... Args>
        reference emplace_back( Args&&... args )
        {
            if ( end_ == allocatedEnd_ ) [[unlikely]]
            {
                auto dataPtr = data_.get( );
                auto requiredCapacity = CapacityForSize( end_ - dataPtr + 1 );
                reserve( requiredCapacity );
            }
            
            auto* ptr = new ( end_ ) T( std::forward<Args>( args )... );
            //auto* ptr = std::construct_at( end_, std::forward<Args>( args )... );

            end_++;
            return *ptr;
        }


        template<typename ... Args>
        reference emplace_front( Args&&... args )
        {
            auto dataPtr = data_.get( );
            if ( end_ != allocatedEnd_ ) [[likely]]
            {
                
                auto currentSize = end_ - dataPtr;
                if ( currentSize )
                {
                    if constexpr ( std::is_trivially_copyable_v<T> )
                    {
                        memmove( dataPtr + 1, dataPtr, currentSize * sizeof( T ) );
                        new ( dataPtr ) T( std::forward<Args>( args )... );
                    }
                    else 
                    {

                        new ( end_ ) T( std::move( *(end_ - 1) ) );
                        auto remaining = currentSize - 1;
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
                end_++;
                return *dataPtr;
            }
            else
            {
                auto requiredCapacity = CapacityForSize( ( end_ - dataPtr ) + 1 );
                expand( 0, requiredCapacity );
                auto dataPtr = data_.get( );
                new ( dataPtr ) T( std::forward<Args>( args )... );
                end_++;
                return *dataPtr;
            }
        }


        template< class... Args >
        iterator emplace( const_iterator it, Args&&... args )
        {
            auto* itPtr = it.ptr_;
            auto dataPtr = data_.get( );
            auto endPtr = end_;
            if ( endPtr < allocatedEnd_ ) [[likely]]
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
                end_++;
                return iterator( itPtr );
            }
            else
            {
                auto offset = itPtr - dataPtr;
                auto currentSize = endPtr - dataPtr;
                if ( itPtr < endPtr )
                {
                    auto requiredCapacity = CapacityForSize( currentSize + 1 );
                    expand( offset, requiredCapacity );
                }
                else
                {
                    reserve( currentSize + 1 );
                }
                dataPtr = data_.get( );
                itPtr = dataPtr + offset;
                new ( itPtr ) T( std::forward<Args>( args )... );
                end_++;
                return iterator( itPtr );
            }
        }


        
        void push_back( const T& v )
        {
            if ( end_ == allocatedEnd_ ) [[unlikely]]
            {
                auto currentSize = end_ - data_.get( );
                auto requiredCapacity = CapacityForSize( currentSize + 1 );
                reserve( requiredCapacity );
            }
            std::construct_at( end_, v );
            end_++;
        }

        void push_back( T&& v )
        {
            if ( end_ == allocatedEnd_ ) [[unlikely]]
            {
                auto currentSize = end_ - data_.get( );
                auto requiredCapacity = CapacityForSize( currentSize + 1 );
                reserve( requiredCapacity );
            }
            std::construct_at( end_, std::move( v ) );
            end_++;
        }


        void pop_back( )
        {
            auto dataPtr = data_.get( );
            if ( end_ > dataPtr )
            {
                if constexpr ( std::is_trivially_destructible_v<T> == false )
                {
                    end_->~T( );
                }
                end_--;
            }
        }
        void push_front( const T& v )
        {
            auto dataPtr = data_.get( );
            if ( dataPtr == end_ )
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
            auto dataPtr = data_.get( );
            if ( dataPtr == end_ )
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
            auto endPtr = end_;
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
                end_--;
            }
            return iterator( it.ptr_ );
        }

        iterator erase( const_iterator it, const_iterator itLast )
        {
            auto itPtr = it.ptr_;
            auto itLastPtr = itLast.ptr_;
            auto dataPtr = data_.get( );
            auto endPtr = end_;
            
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
                end_ -= numberOfItemsToErase;
            }
            return iterator( it.ptr_ );
        }


        iterator insert( const_iterator it, const T& v )
        {
            auto itPtr = it.ptr_;
            auto dataPtr = data_.get( );
            auto endPtr = end_;
            
            if ( endPtr != allocatedEnd_ )
            {
                if ( itPtr != endPtr ) [[likely]]
                {
                    auto remaining = endPtr - itPtr;
                    if constexpr ( std::is_trivially_copyable_v<T> )
                    {
                        auto offset = itPtr - dataPtr;
                        memmove( itPtr + 1, itPtr, static_cast<size_t>( remaining ) * sizeof( T ) );
                    }
                    else
                    {
                        if constexpr ( std::is_move_assignable_v<T> )
                        {
                            new ( endPtr ) T( std::move( *( endPtr - 1 ) ) );
                            while ( remaining )
                            {
                                --remaining;
                                itPtr[remaining + 1] = std::move( itPtr[remaining] );
                            }
                        }
                        else
                        {
                            new ( endPtr ) T( *( endPtr - 1 ) );
                            while ( remaining )
                            {
                                --remaining;
                                itPtr[remaining + 1] = itPtr[remaining];
                            }
                        }
                    }
                }
            }
            else
            {
                auto offset = itPtr - dataPtr;
                auto currentSize = endPtr - dataPtr;
                auto requiredCapacity = CapacityForSize( currentSize + 1 );
                expand( offset, requiredCapacity );
                dataPtr = data_.get( );
                itPtr = dataPtr + offset;
            }
            *itPtr = v;
            end_++;
            return iterator( itPtr );
        }

        iterator insert( const_iterator it, T&& v )
        {
            auto itPtr = it.ptr_;
            auto dataPtr = data_.get( );
            auto endPtr = end_;

            if ( endPtr != allocatedEnd_ )
            {
                if ( itPtr != endPtr ) [[likely]]
                {
                    auto remaining = endPtr - itPtr;
                    if constexpr ( std::is_trivially_copyable_v<T> )
                    {
                        auto offset = itPtr - dataPtr;
                        memmove( itPtr + 1, itPtr, static_cast<size_t>( remaining ) * sizeof( T ) );
                    }
                    else
                    {
                        if constexpr ( std::is_move_assignable_v<T> )
                        {
                            new ( endPtr ) T( std::move( *( endPtr - 1 ) ) );
                            while ( remaining )
                            {
                                --remaining;
                                itPtr[remaining + 1] = std::move( itPtr[remaining] );
                            }
                        }
                        else
                        {
                            new ( endPtr ) T( *( endPtr - 1 ) );
                            while ( remaining )
                            {
                                --remaining;
                                itPtr[remaining + 1] = itPtr[remaining];
                            }
                        }
                    }
                }
            }
            else
            {
                auto offset = itPtr - dataPtr;
                auto currentSize = endPtr - dataPtr;
                auto requiredCapacity = CapacityForSize( currentSize + 1 );
                expand( offset, requiredCapacity );
                dataPtr = data_.get( );
                itPtr = dataPtr + offset;
            }
            *itPtr = std::move( v );
            end_++;
            return iterator( itPtr );
        }

        void MoveToFront( const_iterator it )
        {
            auto itPtr = it.ptr_;
            auto dataPtr = data_.get( );
            if ( itPtr > dataPtr && itPtr < end_ )
            {
                auto tmp = *itPtr;

                if constexpr ( std::is_trivially_copyable_v<T> )
                {
                    memmove( dataPtr + 1, dataPtr, static_cast<size_t>( itPtr - dataPtr ) * sizeof(T) );
                }
                else
                {
                    auto ptr = itPtr;
                    while ( ptr > dataPtr )
                    {
                        ptr--;
                        *( ptr + 1 ) = *ptr;
                    }
                }
                *dataPtr = tmp;
            }
        }

        
        void MoveToBack( const_iterator it )
        {
            auto itPtr = it.ptr_;
            auto dataPtr = data_.get( );
            auto destPtr = end_ - 1;
            if ( dataPtr && 
                ( dataPtr <= itPtr ) && 
                (itPtr < destPtr ) )
            {
                auto tmp = *itPtr;
                
                if constexpr ( std::is_trivially_copyable_v<T> )
                {
                    memcpy( itPtr, itPtr + 1, static_cast<size_t>( end_ - itPtr ) * sizeof( T ) );
                }
                else
                {
                    auto ptr = itPtr;
                    while ( ptr < destPtr )
                    {
                        *ptr = *( ptr + 1 );
                        ptr++;
                    }
                }
                *destPtr = tmp;
            }
        }
        



        [[nodiscard]] bool contains( const T& v ) const
        {
            auto* dataPtr = data_.get( );
            auto* endPtr = end_;
            while ( dataPtr < endPtr )
            {
                if ( *dataPtr++ == v )
                {
                    return true;
                }
            }
            return false;
        }
        [[nodiscard]] iterator find( const T& v )
        {
            auto* dataPtr = data_.get( );
            const auto* endPtr = end_;
            const auto* locationPtr = endPtr;
            while ( dataPtr < endPtr )
            {
                if ( *dataPtr == v ) [[unlikely]]
                {
                    locationPtr = dataPtr;
                    break;
                }
                ++dataPtr;
            }
            return iterator( const_cast<T*>(locationPtr) );
        }

        [[nodiscard]] const_iterator find( const T& v ) const
        {
            auto* dataPtr = data_.get( );
            const auto* endPtr = end_;
            const auto* locationPtr = endPtr;
            while ( dataPtr < endPtr )
            {
                if ( *dataPtr == v ) [[unlikely]]
                {
                    locationPtr = dataPtr;
                    break;
                }
                ++dataPtr;
            }
            return const_iterator( const_cast<T*>( locationPtr ) );
        }

        [[nodiscard]] iterator reverse_find( const T& v )
        {
            auto* dataPtr = data_.get( );
            const auto* endPtr = end_;
            const auto* locationPtr = endPtr;
            while ( endPtr > dataPtr )
            {
                endPtr--;
                if ( *endPtr == v ) [[unlikely]]
                {
                    locationPtr = endPtr;
                    break;
                }
            }
            return iterator( const_cast<T*>( locationPtr ) );
        }
        [[nodiscard]] const_iterator reverse_find( const T& v ) const
        {
            auto* dataPtr = data_.get( );
            const auto* endPtr = end_;
            const auto* locationPtr = endPtr;
            while ( endPtr > dataPtr )
            {
                endPtr--;
                if ( *endPtr == v ) [[unlikely]]
                {
                    locationPtr = endPtr;
                    break;
                }
            }
            return const_iterator( const_cast<T*>( locationPtr ) );
        }

        [[nodiscard]] iterator reverse_find( const T& v, const_iterator itLast )
        {
            auto* dataPtr = data_.get( );
            const auto* endPtr = itLast.ptr_;
            const auto* locationPtr = end_;
            while ( endPtr > dataPtr )
            {
                endPtr--;
                if ( *endPtr == v ) [[unlikely]]
                {
                    locationPtr = endPtr;
                    break;
                }
            }
            return iterator( const_cast<T*>( locationPtr ) );
        }
        [[nodiscard]] const_iterator reverse_find( const T& v, const_iterator itLast ) const
        {
            auto* dataPtr = data_.get( );
            const auto* endPtr = itLast.ptr_;
            const auto* locationPtr = end_;
            while ( endPtr > dataPtr )
            {
                endPtr--;
                if ( *endPtr == v ) [[unlikely]]
                {
                    locationPtr = endPtr;
                    break;
                }
            }
            return const_iterator( const_cast<T*>( locationPtr ) );
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

        [[nodiscard]] size_type IndexOf( const T* ptr ) const
        {
            const size_type index = ptr - data_.get( );
            return index;
        }
        [[nodiscard]] size_type IndexOf( const_iterator it ) const
        {
            const size_type index = it.ptr_ - data_.get( );
            return index;
        }


    };


    template <typename It>
        requires IsIterator_v<It>
    Vector( It, It ) -> Vector<IteratorValue_t<It>>;


    template<typename T>
    class OwnerVector
    {
    public:
        using VectorType = Vector<T*>;

        using size_type = typename VectorType::size_type;
        using difference_type = typename VectorType::difference_type;
        using value_type = T*;
        using pointer = value_type*;
        using reference = value_type&;
        using const_pointer = const value_type*;
        using const_reference = const value_type&;
        using iterator = typename VectorType::iterator;
        using const_iterator = typename VectorType::const_iterator;
        using reverse_iterator = typename VectorType::reverse_iterator;
        using const_reverse_iterator = typename VectorType::const_reverse_iterator;

    private:
        VectorType data_;
    public:
        constexpr OwnerVector( ) noexcept
        {

        }

        OwnerVector( size_type count ) noexcept
            : data_( count, nullptr )
        { }


        template<typename It>
            requires IsIterator_v<It>
        OwnerVector( It first, It last )
            : data_( first, last )
        { 
        }

        OwnerVector( std::initializer_list<T*> values )
            : data_( values.begin( ), values.end( ) )
        {
        }


        OwnerVector( const OwnerVector& other )
            : data_( other.data_ )
        { }

        constexpr OwnerVector( OwnerVector&& other ) noexcept
            : data_( std::move( other.data_ ) )
        {
        }

        ~OwnerVector( )
        {
            auto dataPtr = data_.data( );
            auto endPtr = data_.data( );
            while ( dataPtr < endPtr )
            {
                if ( *dataPtr )
                {
                    delete ( *dataPtr );
                    *dataPtr = nullptr;
                }
                dataPtr++;
            }
        }
    private:
        void Delete( T** itPtr, T** itLastPtr )
        {
            while ( itPtr < itLastPtr )
            {
                if ( *itPtr )
                {
                    delete ( *itPtr );
                    *itPtr = nullptr;
                }
                itPtr++;
            }
        }
    public:
        void Delete( const_iterator it, const_iterator itLast )
        {
            auto itPtr = it.ptr_;
            auto itLastPtr = itLast.ptr_;
            Delete( itPtr, itLastPtr );
        }

        void clear( )
        {
            auto dataPtr = data_.data( );
            auto endPtr = data_.end( ).ptr_;
            while ( dataPtr < endPtr )
            {
                if ( *dataPtr )
                {
                    delete ( *dataPtr );
                    *dataPtr = nullptr;
                }
                dataPtr++;
            }
            data_.clear( );
        }


        void Assign( const OwnerVector& other )
        {
            if ( &data_ != &other.data_ )
            {
                clear( );
                data_.Assign( other.data_ );
            }
        }

        OwnerVector& operator = ( const OwnerVector& other )
        {
            Assign( other );
            return *this;
        }

        OwnerVector& operator = ( OwnerVector&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            return *this;
        }

        [[nodiscard]] bool Equals( OwnerVector& other ) const
        {
            return data_.Equals( other.data_ );
        }

        [[nodiscard]] bool operator == ( OwnerVector& other ) const
        {
            return data_.Equals( other.data_ );
        }
        [[nodiscard]] bool operator != ( OwnerVector& other ) const
        {
            return data_.Equals( other.data_ );
        }

        [[nodiscard]] bool operator == ( Vector<T*>& other ) const
        {
            return data_.Equals( other );
        }
        [[nodiscard]] bool operator != ( Vector<T*>& other ) const
        {
            return data_.Equals( other );
        }

        [[nodiscard]] constexpr bool empty( ) const noexcept
        {
            return data_.empty( );
        }
        [[nodiscard]] constexpr size_type size( ) const noexcept
        {
            return data_.size( );
        }
        [[nodiscard]] constexpr size_type size_in_bytes( ) const noexcept
        {
            return data_.size_in_bytes( );
        }
        [[nodiscard]] constexpr size_type max_size( ) const noexcept
        {
            return data_.max_size( );
        }
        [[nodiscard]] constexpr size_type capacity( ) const noexcept
        {
            return data_.capacity( );
        }
        [[nodiscard]] constexpr T* operator[]( size_type i ) noexcept
        {
            return data_[i];
        }
        [[nodiscard]] constexpr const T* operator[]( size_type i ) const noexcept
        {
            return data_[i];
        }
        [[nodiscard]] constexpr iterator begin( ) noexcept
        {
            return data_.begin( );
        }
        [[nodiscard]] constexpr const_iterator begin( ) const noexcept
        {
            return data_.begin( );
        }

        [[nodiscard]] constexpr const_iterator cbegin( ) const noexcept
        {
            return data_.cbegin( );
        }

        [[nodiscard]] constexpr iterator end( ) noexcept
        {
            return data_.end( );
        }
        [[nodiscard]] constexpr const_iterator end( ) const noexcept
        {
            return data_.end( );
        }
        [[nodiscard]] constexpr const_iterator cend( ) const noexcept
        {
            return data_.cend( );
        }


        [[nodiscard]] constexpr reverse_iterator rbegin( ) noexcept
        {
            return data_.rbegin( );
        }

        [[nodiscard]] constexpr const_reverse_iterator rbegin( ) const noexcept
        {
            return data_.rbegin( );
        }

        [[nodiscard]] constexpr reverse_iterator rend( ) noexcept
        {
            return data_.rend( );
        }

        [[nodiscard]] constexpr const_reverse_iterator rend( ) const noexcept
        {
            return data_.rend( );
        }

        [[nodiscard]] constexpr const_reverse_iterator crbegin( ) const noexcept
        {
            return data_.crbegin( );
        }

        [[nodiscard]] constexpr const_reverse_iterator crend( ) const noexcept
        {
            return data_.crend( );
        }


        [[nodiscard]] constexpr pointer data( ) noexcept
        {
            return data_.data( );
        }
        [[nodiscard]] constexpr const_pointer data( ) const noexcept
        {
            return data_.data( );
        }

        [[nodiscard]] Vector<T*>& Raw( )
        {
            return data_;
        }
        [[nodiscard]] const Vector<T*>& Raw( ) const
        {
            return data_;
        }

        [[nodiscard]] constexpr reference front( ) noexcept
        {
            return data_.front( );
        }
        [[nodiscard]] constexpr const_reference front( ) const noexcept
        {
            return data_.front( );
        }
        [[nodiscard]] constexpr reference back( ) noexcept
        {
            return data_.back( );
        }
        [[nodiscard]] constexpr const_reference back( ) const noexcept
        {
            return data_.back( );
        }

        constexpr void swap( Vector<T*>& other )
        {
            data_.swap( other );
        }
        constexpr void swap( OwnerVector& other )
        {
            data_.swap( other.data_ );
        }

        void resize( size_type newSize )
        {
            auto dataPtr = data_.data( );
            auto endPtr = data_.end( ).ptr_;
            auto currentSize = endPtr - dataPtr;

            if ( newSize < currentSize )
            {
                auto itPtr = dataPtr + newSize;
                Delete( itPtr, endPtr );
            }
            data_.resize( newSize );
        }

        void reserve( size_type requiredCapacity )
        {
            data_.reserve( requiredCapacity );
        }

        reference emplace_back( T* ptr )
        {
            return data_.emplace_back( ptr );
        }
        reference emplace_front( T* ptr )
        {
            return data_.emplace_front( ptr );
        }

        iterator emplace( const_iterator it, T* ptr )
        {
            return data_.emplace( it, ptr );
        }

        void push_back( T* ptr )
        {
            data_.push_back( ptr );
        }
        void push_front( T* ptr )
        {
            data_.push_front( ptr );
        }

        iterator erase( const_iterator it )
        {
            auto itPtr = it.ptr_;
            if ( *itPtr )
            {
                delete ( *itPtr );
                *itPtr = nullptr;
            }
            return data_.erase( it );
        }

        [[nodiscard]] std::unique_ptr<T> release( const_iterator it )
        {
            std::unique_ptr<T> result;
            auto itPtr = it.ptr_;
            if ( *itPtr )
            {
                result.reset( *itPtr );
                *itPtr = nullptr;
            }
            data_.erase( it );
            return result;
        }


        iterator insert( const_iterator it, T* ptr )
        {
            return data_.insert( it, ptr );
        }

        void MoveToFront( const_iterator it )
        {
            data_.MoveToFront( it );
        }
        void MoveToBack( const_iterator it )
        {
            data_.MoveToBack( it );
        }

        [[nodiscard]] bool contains( const T* ptr ) const
        {
            return data_.contains( const_cast<T*>( ptr ) );
        }

        [[nodiscard]] iterator find( const T* ptr )
        {
            return data_.find( const_cast<T*>( ptr ) );
        }
        [[nodiscard]] const_iterator find( const T* ptr ) const
        {
            return data_.find( const_cast<T*>( ptr ) );
        }

        [[nodiscard]] iterator reverse_find( const T* ptr )
        {
            return data_.reverse_find( const_cast<T*>( ptr ) );
        }

        [[nodiscard]] const_iterator reverse_find( const T* ptr ) const
        {
            return data_.reverse_find( const_cast<T*>( ptr ) );
        }

        [[nodiscard]] iterator reverse_find( const T* ptr, const_iterator itLast )
        {
            return data_.reverse_find( const_cast<T*>( ptr ), itLast );
        }

        [[nodiscard]] const_iterator reverse_find( const T* ptr, const_iterator itLast ) const
        {
            return data_.reverse_find( const_cast<T*>( ptr ), itLast );
        }




    };


}

#endif
