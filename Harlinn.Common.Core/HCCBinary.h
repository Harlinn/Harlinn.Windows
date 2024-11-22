#pragma once
#ifndef HARLINN_COMMON_CORE_HCCBINARY_H_
#define HARLINN_COMMON_CORE_HCCBINARY_H_

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

#include <HCCIterator.h>
#include <HCCLib.h>

namespace Harlinn::Common::Core
{
    /// <summary>
    /// A reference counted buffer, primarily intended for binary data.
    /// </summary>
    class Binary
    {
        struct Data
        {
            size_t referenceCount_ = 1;
            size_t size_;
#pragma warning(push)
#pragma warning(disable:4200)
            Byte buffer_[ 0 ];
#pragma warning(pop)

            size_t AddRef( ) noexcept
            {
                return InterlockedIncrementSizeT( &referenceCount_ );
            }

            size_t DecRef( ) noexcept
            {
                return InterlockedDecrementSizeT( &referenceCount_ );
            }

            constexpr bool Contains( const Byte* ptr ) noexcept
            {
                return ptr >= buffer_ && ptr <= ( buffer_ + size_ );
            }
            constexpr bool Contains( const Byte* ptr, size_t startPosition ) noexcept
            {
                return ptr >= ( buffer_ + startPosition ) && ptr <= ( buffer_ + size_ );
            }
        };
    public:
    public:
        using value_type = Byte;

        using pointer = Byte*;
        using const_pointer = const Byte*;
        using reference = Byte&;
        using const_reference = const Byte&;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

        using iterator = Internal::PointerIterator<Binary>;
        using const_iterator = Internal::ConstPointerIterator<Binary>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;


        static constexpr size_type npos = MAXUINT64;
        static constexpr size_type AllocationGranularity = 64;
        
        static constexpr size_t BufferHeaderSize = offsetof( Data, buffer_ );
    private:
    private:
        Data* data_ = nullptr;

        static constexpr size_type AllocationByteCountForLengthNotZero( size_type length ) noexcept
        {
            return ( ( BufferHeaderSize + length ) + ( AllocationGranularity - 1 ) ) & ~( AllocationGranularity - 1 );
        }

        static constexpr size_type AllocationByteCount( size_type length ) noexcept
        {
            return length ? ( ( BufferHeaderSize + length ) + ( AllocationGranularity - 1 ) ) & ~( AllocationGranularity - 1 ) : 0;
        }

        static Data* Allocate( size_t size )
        {
            size_t allocationByteCount = AllocationByteCount( size );
            Data* data = ( Data* )malloc( allocationByteCount );
            if ( !data )
            {
                throw std::bad_alloc( );
            }
            data->referenceCount_ = 1;
            data->size_ = size;
            return data;
        }

        static Data* Allocate( size_type allocationByteCount, size_t size )
        {
            Data* data = ( Data* )malloc( allocationByteCount );
            if ( !data )
            {
                throw std::bad_alloc( );
            }
            data->referenceCount_ = 1;
            data->size_ = size;
            return data;
        }

        static void ReleaseData( Data* data )
        {
            if ( data && data->DecRef( ) == 0 )
            {
                
                free( data );
            }
        }

        Byte* ExpandIntoNewBuffer( size_t offset, size_t expandSize )
        {
            auto currentSize = data_->size_;
            auto newSize = currentSize + expandSize;
            auto newData = Allocate( newSize );
            memcpy( newData->buffer_, data_->buffer_, offset );
            auto remaining = currentSize - offset;
            memcpy( &newData->buffer_[ offset + expandSize ], &data_->buffer_[ offset ], remaining );
            auto* tmp = data_;
            data_ = newData;
            ReleaseData( tmp );
            return &newData->buffer_[ offset ];
        }

        Byte* ExpandCurrentBuffer( size_t offset, size_t expandSize )
        {
            auto currentSize = data_->size_;
            auto remaining = currentSize - offset;
            memmove( &data_->buffer_[ offset + expandSize ], &data_->buffer_[ offset ], remaining );
            data_->size_ += expandSize;
            return &data_->buffer_[ offset ];
        }


        Byte* Expand( size_t offset, size_t expandSize )
        {
            if ( data_ )
            {
                if ( data_->referenceCount_ > 1 )
                {
                    return ExpandIntoNewBuffer( offset, expandSize );
                }
                else
                {
                    auto currentSize = data_->size_;
                    auto newSize = currentSize + expandSize;
                    auto currentBufferSize = AllocationByteCountForLengthNotZero( currentSize );
                    auto newBufferSize = AllocationByteCountForLengthNotZero( newSize );
                    if ( currentBufferSize == newBufferSize )
                    {
                        return ExpandCurrentBuffer( offset, expandSize );
                    }
                    else
                    {
                        return ExpandIntoNewBuffer( offset, expandSize );
                    }

                }
            }
            else
            {
                data_ = Allocate( expandSize );
                return data_->buffer_;
            }
        }

        Byte* ExtendIntoNewBuffer( size_t extendSize )
        {
            auto currentSize = data_->size_;
            auto newSize = currentSize + extendSize;
            auto newData = Allocate( newSize );
            memcpy( newData->buffer_, data_->buffer_, currentSize );
            auto* tmp = data_;
            data_ = newData;
            ReleaseData( tmp );
            return &newData->buffer_[ currentSize ];
        }

        Byte* ExtendCurrentBuffer( size_t extendSize )
        {
            auto currentSize = data_->size_;
            data_->size_ += extendSize;
            return &data_->buffer_[ currentSize ];
        }

        Byte* Extend( size_t extendSize )
        {
            if ( data_ )
            {
                if ( data_->referenceCount_ > 1 )
                {
                    return ExtendIntoNewBuffer( extendSize );
                }
                else
                {
                    auto currentSize = data_->size_;
                    auto newSize = currentSize + extendSize;
                    auto currentBufferSize = AllocationByteCountForLengthNotZero( currentSize );
                    auto newBufferSize = AllocationByteCountForLengthNotZero( newSize );
                    if ( currentBufferSize == newBufferSize )
                    {
                        return ExtendCurrentBuffer( extendSize );
                    }
                    else
                    {
                        return ExtendIntoNewBuffer( extendSize );
                    }

                }
            }
            else
            {
                data_ = Allocate( extendSize );
                return data_->buffer_;
            }
        }

        void RangeCheck( const_iterator position )
        {
            if ( data_ )
            {
                if ( position < data_->buffer_ )
                {
                    throw std::out_of_range( "position < begin()" );
                }
                auto currentSize = data_->size_;
                if ( position >= &data_->buffer_[ currentSize ] )
                {
                    throw std::out_of_range( "position >= end()" );
                }
            }
            else
            {
                throw std::out_of_range( "buffer is empty" );
            }
        }



        Byte* Erase( size_t offset, size_t numberOfCharactersToErase )
        {
            if ( data_ )
            {
                auto currentSize = data_->size_;

                if ( offset < currentSize )
                {
                    if ( ( offset + numberOfCharactersToErase ) > currentSize )
                    {
                        numberOfCharactersToErase = currentSize - offset;
                    }
                    size_t newSize = currentSize - numberOfCharactersToErase;
                    if ( newSize )
                    {
                        auto currentBufferSize = AllocationByteCountForLengthNotZero( currentSize );
                        auto newBufferSize = AllocationByteCountForLengthNotZero( newSize );

                        if ( ( data_->referenceCount_ == 1 ) && ( currentBufferSize == newBufferSize ) )
                        {
                            size_t remainingSize = currentSize - ( offset + numberOfCharactersToErase );
                            if ( remainingSize )
                            {
                                auto* dest = &data_->buffer_[ offset ];
                                memcpy( dest, dest + numberOfCharactersToErase, remainingSize );
                            }
                            data_->size_ = newSize;
                        }
                        else
                        {
                            auto* newData = Allocate( newSize );
                            if ( offset )
                            {
                                memcpy( newData->buffer_, data_->buffer_, offset );
                            }
                            size_t remainingSize = currentSize - ( offset + numberOfCharactersToErase );
                            if ( remainingSize )
                            {
                                memcpy( &newData->buffer_[ offset ], &data_->buffer_[ offset + numberOfCharactersToErase ], remainingSize );
                            }
                            ReleaseData( data_ );
                            data_ = newData;
                        }
                        return &data_->buffer_[ offset ];

                    }
                    else
                    {
                        ReleaseData( data_ );
                        data_ = nullptr;
                    }
                }
                else
                {
                    return &data_->buffer_[ currentSize ];
                }
            }
            return nullptr;
        }


        static Data* Initialize( const Byte* string, size_type size )
        {
            if ( size )
            {
                Data* data = Allocate( size );
                memcpy( data->buffer_, string, size );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        static Data* Initialize( const Byte* string1, size_type size1, const Byte* string2, size_type size2 )
        {
            auto size = size1 + size2;
            if ( size )
            {
                Data* data = Allocate( size );
                memcpy( data->buffer_, string1, size1 );
                memcpy( data->buffer_ + size1, string2, size2 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        static Data* Initialize( Byte value, size_type count, const Byte* string2, size_type size2 )
        {
            auto size = count + size2;
            if ( size )
            {
                Data* data = Allocate( size );
                memset( data->buffer_, value, count );
                memcpy( data->buffer_ + count, string2, size2 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        static Data* Initialize( const Byte* string1, size_type size1, Byte value, size_type count )
        {
            auto size = size1 + count;
            if ( size )
            {
                Data* data = Allocate( size );
                memcpy( data->buffer_, string1, size1 );
                memset( data->buffer_ + size1, value, count );
                return data;
            }
            else
            {
                return nullptr;
            }
        }



        static Data* Initialize( const Byte* string1, size_type size1, const Byte* string2, size_type size2, const Byte* string3, size_type size3 )
        {
            auto size = size1 + size2 + size3;
            if ( size )
            {
                Data* data = Allocate( size );
                memcpy( data->buffer_, string1, size1 );
                memcpy( data->buffer_ + size1, string2, size2 );
                memcpy( data->buffer_ + size1 + size2, string3, size3 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        static Data* Initialize( Byte value, size_type count, const Byte* string2, size_type size2, const Byte* string3, size_type size3 )
        {
            auto size = count + size2 + size3;
            if ( size )
            {
                Data* data = Allocate( size );
                memset( data->buffer_, value, count );
                memcpy( data->buffer_ + count, string2, size2 );
                memcpy( data->buffer_ + count + size2, string3, size3 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }


        static Data* Initialize( const Byte* string1, size_type size1, Byte value, size_type count, const Byte* string3, size_type size3 )
        {
            auto size = size1 + count + size3;
            if ( size )
            {
                Data* data = Allocate( size );
                memcpy( data->buffer_, string1, size1 );
                memset( data->buffer_ + size1, value, count );
                memcpy( data->buffer_ + size1 + count, string3, size3 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        static Data* Initialize( const Byte* string1, size_type size1, const Byte* string2, size_type size2, Byte value, size_type count )
        {
            auto size = size1 + size2 + count;
            if ( size )
            {
                Data* data = Allocate( size );
                memcpy( data->buffer_, string1, size1 );
                memcpy( data->buffer_ + size1, string2, size2 );
                memset( data->buffer_ + size1 + size2, value, count );
                return data;
            }
            else
            {
                return nullptr;
            }
        }



        template<typename InputIt>
        static Data* Initialize( InputIt first, InputIt last )
        {
            auto size = std::distance( first, last );
            if ( size )
            {
                Data* data = Allocate( size );
                std::copy( first, last, data->buffer_ );
                return data;
            }
            else
            {
                return nullptr;
            }
        }



        static Data* Initialize( size_type count, Byte value )
        {
            if ( count )
            {
                Data* data = Allocate( count );
                memset( data->buffer_, value, count );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        Binary( Data* data, bool addRef = true ) noexcept
            : data_( data )
        {
            if ( addRef && data )
            {
                data->AddRef( );
            }
        }
    public:
        constexpr Binary( ) noexcept = default;

        Binary( const Byte* buffer, size_type size )
            : data_( Initialize( buffer, size ) )
        {
        }
        template<typename T, size_t N>
            requires (sizeof(T) == 1)
        Binary( const T( &array )[ N ] )
            : data_( Initialize( reinterpret_cast<const Byte*>(array), N ) )
        {
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, Byte>
        explicit Binary( const SpanT& span )
            : data_( Initialize( span.data( ), span.size( ) ) )
        {
        }

        Binary( const Byte* buffer1, size_type size1, const Byte* buffer2, size_type size2 )
            : data_( Initialize( buffer1, size1, buffer2, size2 ) )
        {
        }

        Binary( Byte value, size_type count, const Byte* buffer2, size_type size2 )
            : data_( Initialize( value, count, buffer2, size2 ) )
        {
        }

        Binary( const Byte* buffer1, size_type size1, Byte value, size_type count )
            : data_( Initialize( buffer1, size1, value, count ) )
        {
        }

        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, Byte>&& std::is_same_v<typename SpanT2::value_type, Byte> )
        Binary( const SpanT1& span1, const SpanT2& span2 )
            : data_( Initialize( span1.data( ), span1.size( ), span2.data( ), span2.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, Byte>
        Binary( Byte value, size_type count, const SpanT& span )
            : data_( Initialize( value, count, span.data( ), span.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, Byte>
        Binary( Byte value, const SpanT& span )
            : data_( Initialize( value, 1, span.data( ), span.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, Byte>
        Binary( const SpanT& span, Byte value, size_type count )
            : data_( Initialize( span.data( ), span.size( ), value, count ) )
        {
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, Byte>
        Binary( const SpanT& span, Byte value )
            : data_( Initialize( span.data( ), span.size( ), value, 1 ) )
        {
        }



        Binary( const Byte* buffer1, size_type size1, const Byte* buffer2, size_type size2, const Byte* buffer3, size_type size3 )
            : data_( Initialize( buffer1, size1, buffer2, size2, buffer3, size3 ) )
        {
        }

        Binary( Byte value, size_type count, const Byte* buffer2, size_type size2, const Byte* buffer3, size_type size3 )
            : data_( Initialize( value, count, buffer2, size2, buffer3, size3 ) )
        {
        }

        Binary( const Byte* buffer1, size_type size1, Byte value, size_type count, const Byte* buffer3, size_type size3 )
            : data_( Initialize( buffer1, size1, value, count, buffer3, size3 ) )
        {
        }

        Binary( const Byte* buffer1, size_type size1, const Byte* buffer2, size_type size2, Byte value, size_type count )
            : data_( Initialize( buffer1, size1, buffer2, size2, value, count ) )
        {
        }

        Binary( Byte value, const Byte* buffer2, size_type size2, const Byte* buffer3, size_type size3 )
            : data_( Initialize( value, 1, buffer2, size2, buffer3, size3 ) )
        {
        }

        Binary( const Byte* buffer1, size_type size1, Byte value, const Byte* buffer3, size_type size3 )
            : data_( Initialize( buffer1, size1, value, 1, buffer3, size3 ) )
        {
        }

        Binary( const Byte* buffer1, size_type size1, const Byte* buffer2, size_type size2, Byte value )
            : data_( Initialize( buffer1, size1, buffer2, size2, value, 1 ) )
        {
        }


        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, Byte>&& std::is_same_v<typename SpanT2::value_type, Byte> )
        Binary( Byte value, size_type count, const SpanT1& span1, const SpanT2& span2 )
            : data_( Initialize( value, count, span1.data( ), span1.size( ), span2.data( ), span2.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, Byte>&& std::is_same_v<typename SpanT2::value_type, Byte> )
        Binary( const SpanT1& span1, Byte value, size_type count, const SpanT2& span2 )
            : data_( Initialize( span1.data( ), span1.size( ), value, count, span2.data( ), span2.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, Byte>&& std::is_same_v<typename SpanT2::value_type, Byte> )
        Binary( const SpanT1& span1, const SpanT2& span2, Byte value, size_type count )
            : data_( Initialize( span1.data( ), span1.size( ), span2.data( ), span2.size( ), value, count ) )
        {
        }


        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, Byte>&& std::is_same_v<typename SpanT2::value_type, Byte> )
        Binary( Byte value, const SpanT1& span1, const SpanT2& span2 )
            : data_( Initialize( value, 1, span1.data( ), span1.size( ), span2.data( ), span2.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, Byte>&& std::is_same_v<typename SpanT2::value_type, Byte> )
        Binary( const SpanT1& span1, Byte value, const SpanT2& span2 )
            : data_( Initialize( span1.data( ), span1.size( ), value, 1, span2.data( ), span2.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, Byte>&& std::is_same_v<typename SpanT2::value_type, Byte> )
        Binary( const SpanT1& span1, const SpanT2& span2, Byte value )
            : data_( Initialize( span1.data( ), span1.size( ), span2.data( ), span2.size( ), value, 1 ) )
        {
        }




        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2, SimpleSpanLike SpanT3>
            requires ( std::is_same_v<typename SpanT1::value_type, Byte>&& std::is_same_v<typename SpanT2::value_type, Byte>&& std::is_same_v<typename SpanT3::value_type, Byte> )
        Binary( const SpanT1& span1, const SpanT2& span2, const SpanT3& span3 )
            : data_( Initialize( span1.data( ), span1.size( ), span2.data( ), span2.size( ), span3.data( ), span3.size( ) ) )
        {
        }


        Binary( const_iterator first, const_iterator last )
            : data_( Initialize( first.ptr_, first <= last ? static_cast< size_type >( last - first ) : 0 ) )
        {
        }

        Binary( const_pointer first, const_pointer last )
            : data_( Initialize( first, first <= last ? static_cast< size_type >( last - first ) : 0 ) )
        {
        }

        template<typename InputIt>
        Binary( InputIt first, InputIt last )
            : data_( Initialize( first, last ) )
        {
        }


        Binary( size_type count, Byte value )
            : data_( Initialize( count, value ) )
        {
        }

        Binary( const Binary& other ) noexcept
            : data_( other.data_ )
        {
            if ( data_ )
            {
                data_->AddRef( );
            }
        }

        Binary( Binary&& other ) noexcept
            : data_( other.data_ )
        {
            other.data_ = nullptr;
        }

        Binary& operator = ( nullptr_t )
        {
            if ( data_ )
            {
                ReleaseData( data_ );
                data_ = nullptr;
            }
            return *this;
        }

        Binary& operator = ( const Binary& other )
        {
            if ( other.data_ != data_ )
            {
                if ( data_ )
                {
                    ReleaseData( data_ );
                }
                data_ = other.data_;
                if ( data_ )
                {
                    data_->AddRef( );
                }
            }
            return *this;
        }

        Binary& operator = ( Binary&& other ) noexcept
        {
            std::swap( other.data_, data_ );
            return *this;
        }

        [[nodiscard]] bool IsUnique( ) const noexcept
        {
            return data_ ? data_->referenceCount_ == 1 : false;
        }

        [[nodiscard]] Binary Clone( ) const
        {
            if ( data_ )
            {
                return Binary( data_->buffer_, data_->size_ );
            }
            return {};
        }

        void EnsureUnique( )
        {
            if ( data_ && data_->referenceCount_ > 1 )
            {
                auto tmp = Initialize( data_->buffer_, data_->size_ );
                ReleaseData( data_ );
                data_ = tmp;
            }
        }

        void Assign( const Byte* buffer, size_type size )
        {
            if ( data_ )
            {
                auto tmp = Initialize( buffer, size );
                ReleaseData( data_ );
                data_ = tmp;
            }
            else
            {
                data_ = Initialize( buffer, size );
            }
        }
        void assign( const Byte* buffer, size_type size )
        {
            Assign( buffer, size );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, Byte>
        void Assign( const SpanT& buffer )
        {
            Assign( buffer.data( ), buffer.size( ) );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, Byte>
        void assign( const SpanT& buffer )
        {
            Assign( buffer.data( ), buffer.size( ) );
        }


        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, Byte>
        Binary& operator = ( const SpanT& buffer )
        {
            Assign( buffer.data( ), buffer.size( ) );
            return *this;
        }

        [[nodiscard]] constexpr const Byte* data( ) const noexcept
        {
            return data_ ? data_->buffer_ : nullptr;
        }

        [[nodiscard]] constexpr Byte* data( ) noexcept
        {
            return data_ ? data_->buffer_ : nullptr;
        }

        [[nodiscard]] size_t Hash( ) const noexcept
        {
            if ( data_ )
            {
                return XXH3_64bits( data_->buffer_, data_->size_ );
            }
            else
            {
                return 0;
            }
        }


        [[nodiscard]] constexpr iterator begin( ) noexcept
        {
            return data_ ? data_->buffer_ : nullptr;
        }

        [[nodiscard]] constexpr iterator end( ) noexcept
        {
            return data_ ? &data_->buffer_[ data_->size_ ] : nullptr;
        }

        [[nodiscard]] constexpr const_iterator begin( ) const noexcept
        {
            return data_ ? data_->buffer_ : nullptr;
        }

        [[nodiscard]] constexpr const_iterator end( ) const noexcept
        {
            return data_ ? &data_->buffer_[ data_->size_ ] : nullptr;
        }

        [[nodiscard]] constexpr const_iterator cbegin( ) const noexcept
        {
            return begin( );
        }

        [[nodiscard]] constexpr const_iterator cend( ) const noexcept
        {
            return end( );
        }

        [[nodiscard]] constexpr reverse_iterator rbegin( ) noexcept
        {
            return reverse_iterator( end( ) );
        }

        [[nodiscard]] constexpr reverse_iterator rend( ) noexcept
        {
            return reverse_iterator( begin( ) );
        }

        [[nodiscard]] constexpr const_reverse_iterator rbegin( ) const noexcept
        {
            return const_reverse_iterator( end( ) );
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



        [[nodiscard]] constexpr const Byte front( ) const
        {
            return *begin( );
        }
        [[nodiscard]] constexpr Byte front( )
        {
            return *begin( );
        }
        [[nodiscard]] constexpr Byte back( ) const
        {
            return *( end( ) - 1 );
        }
        [[nodiscard]] constexpr Byte back( )
        {
            return *( end( ) - 1 );
        }


        [[nodiscard]] constexpr size_type max_size( ) const noexcept
        {
            return ( MaxInt64 / sizeof( Byte ) ) - BufferHeaderSize;
        }


        [[nodiscard]] constexpr size_type size( ) const noexcept
        {
            return data_ ? data_->size_ : 0;
        }

        [[nodiscard]] constexpr size_type capacity( ) const noexcept
        {
            return data_ ? AllocationByteCount( data_->size_ ) : 0;
        }

        constexpr void reserve( size_type ) const noexcept
        {
        }


        [[nodiscard]] constexpr size_type length( ) const noexcept
        {
            return size( );
        }
        [[nodiscard]] constexpr size_type Length( ) const noexcept
        {
            return size( );
        }

        void SetLength( size_type newLength )
        {
            if ( data_ )
            {
                if ( newLength )
                {
                    if ( data_->referenceCount_ > 1 )
                    {
                        auto tmp = data_;
                        data_ = Allocate( newLength );
                        auto copyLength = std::min( newLength, tmp->size_ );
                        memcpy( data_->buffer_, tmp->buffer_, copyLength );
                        ReleaseData( tmp );
                    }
                    else
                    {
                        auto currentSize = data_->size_;
                        auto currentByteCount = AllocationByteCountForLengthNotZero( currentSize );
                        auto newByteCount = AllocationByteCountForLengthNotZero( newLength );
                        if ( currentByteCount == newByteCount )
                        {
                            data_->size_ = newLength;
                            data_->buffer_[ newLength ] = 0;
                        }
                        else
                        {
                            auto tmp = data_;
                            data_ = Allocate( newLength );
                            auto copyLength = std::min( newLength, tmp->size_ );
                            memcpy( data_->buffer_, tmp->buffer_, copyLength );
                            ReleaseData( tmp );
                        }
                    }
                }
                else
                {
                    ReleaseData( data_ );
                    data_ = nullptr;
                }
            }
            else if ( newLength )
            {
                data_ = Allocate( newLength );
            }
        }

        void resize( size_type newLength )
        {
            SetLength( newLength );
        }


        [[nodiscard]] constexpr bool empty( ) const noexcept
        {
            return data_ ? data_->size_ == 0 : true;
        }

        [[nodiscard]] constexpr bool IsEmpty( ) const noexcept
        {
            return empty( );
        }


        [[nodiscard]] constexpr explicit operator bool( ) const noexcept
        {
            return empty( ) == false;
        }


        [[nodiscard]] reference operator[]( size_type offset ) noexcept
        {
            return data_->buffer_[ offset ];
        }
        [[nodiscard]] const_reference operator[]( size_type offset ) const noexcept
        {
            return data_->buffer_[ offset ];
        }

        [[nodiscard]] friend Binary operator +( const Binary& first, const Binary& second )
        {
            auto firstSize = first.size( );
            auto* firstData = first.data( );

            auto secondSize = second.size( );
            auto* secondData = second.data( );

            return Binary( firstData, firstSize, secondData, secondSize );
        }

        [[nodiscard]] friend Binary operator +( Byte first, const Binary& second )
        {
            auto secondSize = second.size( );
            auto* secondData = second.data( );

            return Binary( &first, 1, secondData, secondSize );
        }

        [[nodiscard]] friend Binary operator +( const Binary& first, const Byte second )
        {
            auto firstSize = first.size( );
            auto* firstData = first.data( );

            return Binary( firstData, firstSize, &second, 1 );
        }

        void Append( const Byte* other, size_t otherLength )
        {
            auto* dest = Extend( otherLength );
            memcpy( dest, other, otherLength );
        }

        void append( const Byte* other, size_t otherLength )
        {
            Append( other, otherLength );
        }

        void Append( const Byte* first, const Byte* last )
        {
            if ( first < last )
            {
                Append( first, static_cast< size_type >( last - first ) );
            }
        }
        void append( const Byte* first, const Byte* last )
        {
            Append( first, last );
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        void Append( const T& other )
        {
            auto otherLength = other.size( );
            auto* dest = Extend( otherLength );
            memcpy( dest, other.data( ), otherLength );
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        void append( const T& other )
        {
            Append( other );
        }


        void Append( Byte b )
        {
            auto* dest = Extend( 1 );
            *dest = b;
        }

        void append( Byte b )
        {
            Append( b );
        }

        void push_back( Byte b )
        {
            Append( b );
        }
        void emplace_back( Byte b )
        {
            Append( b );
        }

        void pop_back( )
        {
            auto sz = size( );
            if ( sz )
            {
                SetLength( sz - 1 );
            }
        }

        Binary& operator += ( Byte b ) { Append( b ); return *this; }
        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        Binary& operator += ( const T& other ) { Append( other.data( ), other.size( ) ); return *this; }

        iterator Insert( const_iterator pos, Byte b )
        {
            auto position = pos.ptr_;
            iterator end_ = Extend( 1 );
            if ( position < end_ )
            {
                memmove( position + 1, position, static_cast< size_t >( end_ - position ) );
            }
            *position = b;
            return position;
        }

        iterator insert( const_iterator pos, Byte b )
        {
            return Insert( pos, b );
        }

        iterator Insert( const_iterator pos, size_type count, Byte b )
        {
            auto position = pos.ptr_;
            iterator end_ = Extend( count );
            if ( position < end_ )
            {
                memmove( position + count, position, static_cast< size_t >( end_ - position ) );
            }
            memset( position, b, count );
            return position;
        }

        iterator insert( const_iterator pos, size_type count, Byte b )
        {
            return Insert( pos, count, b );
        }


        iterator Insert( size_type index, size_type count, Byte b )
        {
            const_iterator pos = cbegin( ) + index;
            return insert( pos, count, b );
        }

        iterator insert( size_type index, size_type count, Byte b )
        {
            return Insert( index, count, b );
        }

        iterator Insert( const_iterator pos, const Byte* buffer, size_type bufferLength )
        {
            auto position = pos.ptr_;
            iterator end_ = Extend( bufferLength );
            if ( position < end_ )
            {
                memmove( position + bufferLength, position, static_cast< size_t >( end_ - position ) );
            }
            memcpy( position, buffer, bufferLength );
            return position;
        }

        iterator insert( const_iterator pos, const Byte* buffer, size_type bufferLength )
        {
            return Insert( pos, buffer, bufferLength );
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        iterator Insert( const_iterator pos, const T& buffer )
        {
            return Insert( pos, buffer.data( ), buffer.size( ) );
        }
        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        iterator insert( const_iterator pos, const T& buffer )
        {
            return Insert( pos, buffer.data( ), buffer.size( ) );
        }

    private:
        [[nodiscard]] static bool AreEqual( const Data* first, const Byte* second, size_type secondSize ) noexcept
        {
            if ( first )
            {
                if ( second )
                {
                    if ( first->size_ == secondSize )
                    {
                        return memcmp( first->buffer_, second, secondSize ) == 0;
                    }
                }
                return false;
            }
            return second && secondSize ? false : true;
        }

        [[nodiscard]] static bool AreEqual( const Byte* first, size_type firstSize, const Data* second ) noexcept
        {
            if ( second )
            {
                if ( first && firstSize )
                {
                    if ( second->size_ == firstSize )
                    {
                        return memcmp( first, second->buffer_, second->size_ ) == 0;
                    }
                }
                return false;
            }
            return first && firstSize ? false : true;
        }
    public:
        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] bool operator == ( const T& other ) const noexcept
        {
            return AreEqual( data_, other.data( ), other.size( ) );
        }
        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] bool operator != ( const T& other ) const noexcept
        {
            return AreEqual( data_, other.data( ), other.size( ) ) == false;
        }


        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte> && (std::is_same_v<T,Binary> == false)
        [[nodiscard]] friend bool operator==( const T& first, const Binary& second ) noexcept
        {
            return AreEqual( first.data( ), first.size( ), second.data_ );
        }
        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte> && ( std::is_same_v<T, Binary> == false )
        [[nodiscard]] friend bool operator!=( const T& first, const Binary& second ) noexcept
        {
            return AreEqual( first.data( ), first.size( ), second.data_ ) == false;
        }

    private:
        [[nodiscard]] static int Compare( const Data* first, const Byte* second, size_type secondSize ) noexcept
        {
            if ( first )
            {
                if ( second && secondSize )
                {
                    auto compareSize = std::min( first->size_, secondSize );
                    auto cmpResult = memcmp( first->buffer_, second, compareSize );
                    if ( cmpResult == 0 && first->size_ != secondSize )
                    {
                        if ( first->size_ > secondSize )
                        {
                            return 1;
                        }
                        return -1;
                    }
                    return cmpResult;
                }
                return 1;
            }
            return second && secondSize ? -1 : 0;
        }

        [[nodiscard]] static int Compare( const Byte* first, size_type firstSize, const Data* second ) noexcept
        {
            if ( first && firstSize )
            {
                if ( second )
                {
                    auto compareSize = std::min( firstSize, second->size_ );
                    auto cmpResult = memcmp( first, second->buffer_, compareSize );
                    if ( cmpResult == 0 && firstSize != second->size_ )
                    {
                        if ( firstSize > second->size_ )
                        {
                            return 1;
                        }
                        return -1;
                    }
                    return cmpResult;
                }
                return 1;
            }
            return second ? -1 : 0;
        }
    public:
        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] bool operator < ( const T& other ) const noexcept
        {
            return Compare( data_, other.data( ), other.size( ) ) < 0;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte> && ( std::is_same_v<T, Binary> == false )
        [[nodiscard]] friend bool operator < ( const T& first, const Binary& second ) noexcept
        {
            return Compare( first.data( ), first.size( ), second.data_ ) < 0;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] bool operator <= ( const T& other ) const noexcept
        {
            return Compare( data_, other.data( ), other.size( ) ) <= 0;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte> && ( std::is_same_v<T, Binary> == false )
        [[nodiscard]] friend bool operator <= ( const T& first, const Binary& second ) noexcept
        {
            return Compare( first.data( ), first.size( ), second.data_ ) <= 0;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] bool operator > ( const T& other ) const noexcept
        {
            return Compare( data_, other.data( ), other.size( ) ) > 0;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte> && ( std::is_same_v<T, Binary> == false )
        [[nodiscard]] friend bool operator > ( const T& first, const Binary& second ) noexcept
        {
            return Compare( first.data( ), first.size( ), second.data_ ) > 0;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] bool operator >= ( const T& other ) const noexcept
        {
            return Compare( data_, other.data( ), other.size( ) ) >= 0;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte> && ( std::is_same_v<T, Binary> == false )
        [[nodiscard]] friend bool operator >= ( const T& first, const Binary& second ) noexcept
        {
            return Compare( first.data( ), first.size( ), second.data_ ) >= 0;
        }

        [[nodiscard]] size_type IndexOf( Byte b ) const
        {
            if ( data_ )
            {
                auto* foundAt = reinterpret_cast<const Byte*>(memchr( data_->buffer_, b, data_->size_ ));
                return foundAt ? foundAt - data_->buffer_ : npos;
            }
            else
            {
                return npos;
            }
        }

        [[nodiscard]] size_type find_first_of( Byte b ) const
        {
            return IndexOf( b );
        }

        [[nodiscard]] size_type find( Byte b ) const
        {
            return IndexOf( b );
        }

        [[nodiscard]] size_type IndexOfAnyOf( const Byte* searchValues, size_type numberOfSearchValues, size_type start ) const
        {
            if ( data_ && searchValues && numberOfSearchValues )
            {
                auto ptr = data_->buffer_ + start;
                auto endPtr = data_->buffer_ + data_->size_;
                if ( numberOfSearchValues == 1 && ptr < endPtr )
                {
                    auto p = reinterpret_cast< const Byte* >( memchr( ptr, *searchValues, data_->size_ - start ) );
                    if ( p )
                    {
                        return static_cast< size_type >( p - data_->buffer_ );
                    }
                }
                else
                {
                    auto searchEndPtr = searchValues + numberOfSearchValues;

                    while ( ptr < endPtr )
                    {
                        auto searchPtr = searchValues;
                        while ( searchPtr < searchEndPtr )
                        {
                            if ( *ptr == *searchPtr )
                            {
                                return static_cast< size_type >( ptr - data_->buffer_ );
                            }
                            searchPtr++;
                        }
                        ptr++;
                    }
                }
            }
            return npos;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte> 
        [[nodiscard]] size_type IndexOfAnyOf( const T& searchValues, size_type start = 0 ) const
        {
            return IndexOfAnyOf( searchValues.data( ), searchValues.size( ), start );
        }

    private:
        static bool Contains( const Byte* buffer, size_type bufferLength, Byte value )
        {
            return memchr( buffer, value, bufferLength ) != nullptr;
        }
    public:
        [[nodiscard]] size_type IndexOfAnyBut( const Byte* searchValues, size_type numberOfSearchValues, size_type start ) const
        {
            if ( data_ && start < data_->size_ )
            {
                if ( searchValues && numberOfSearchValues )
                {
                    auto ptr = data_->buffer_ + start;
                    auto endPtr = data_->buffer_ + data_->size_;
                    while ( ptr < endPtr )
                    {
                        if ( Contains( searchValues, numberOfSearchValues, *ptr ) == false )
                        {
                            return static_cast< size_type >( ptr - data_->buffer_ );
                        }
                        ptr++;
                    }
                }
                else
                {
                    return start;
                }
            }
            return npos;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] size_type IndexOfAnyBut( const T& searchValues, size_type start = 0 ) const
        {
            return IndexOfAnyBut( searchValues.data( ), searchValues.size( ), start );
        }

        [[nodiscard]] size_type find_first_not_of( const Byte* searchValues, size_type numberOfSearchValues, size_type start ) const
        {
            return IndexOfAnyBut( searchValues, numberOfSearchValues, start );
        }

        [[nodiscard]] size_type IndexOfAnyBut( Byte searchValue, size_type start = 0 ) const
        {
            return IndexOfAnyBut( &searchValue, 1, start );
        }

        [[nodiscard]] size_type find_first_not_of( Byte searchValue, size_type start = 0 ) const
        {
            return IndexOfAnyBut( searchValue, start );
        }

        [[nodiscard]] size_type LastIndexOfAnyOf( const Byte* searchValues, size_type numberOfSearchValues, size_type start ) const
        {
            if ( data_ && searchValues && numberOfSearchValues )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }
                do
                {
                    const auto* p = reinterpret_cast<const Byte*>( memchr( searchValues, data_->buffer_[ start ], static_cast< size_t >( numberOfSearchValues ) ) );
                    if ( p )
                    {
                        return start;
                    }
                } while ( start-- );
            }
            return npos;
        }
        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] size_type LastIndexOfAnyOf( const T& searchValues, size_type start = npos ) const
        {
            return LastIndexOfAnyOf( searchValues.data( ), searchValues.size( ), start );
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] size_type find_last_of( const T& searchValues, size_type start = npos ) const
        {
            return LastIndexOfAnyOf( searchValues, start );
        }

        [[nodiscard]] size_type LastIndexOfAnyOf( Byte searchValue, size_type start = npos ) const
        {
            return LastIndexOfAnyOf( &searchValue, 1, start );
        }

        [[nodiscard]] size_type find_last_of( Byte searchValue, size_type start = npos ) const
        {
            return LastIndexOfAnyOf( &searchValue, 1, start );
        }


        [[nodiscard]] size_type LastIndexOfAnyBut( const Byte* searchValues, size_type numberOfSearchValues, size_type start ) const
        {
            if ( data_ )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }
                do
                {
                    const auto* p = reinterpret_cast< const Byte* >( memchr( searchValues, data_->buffer_[ start ], static_cast< size_t >( numberOfSearchValues ) ) );
                    if ( !p )
                    {
                        return start;
                    }
                } while ( start-- );
            }
            return npos;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] size_type LastIndexOfAnyBut( const T& searchValues, size_type start = npos ) const
        {
            return LastIndexOfAnyBut( searchValues.data( ), searchValues.size( ), start );
        }

        [[nodiscard]] size_type IndexOf( const Byte* searchSequence, size_type searchSequenceLength, size_type start ) const
        {
            if ( data_ )
            {
                auto dataSize = data_->size_;
                if ( ( start + searchSequenceLength ) <= dataSize )
                {
                    const auto* ptr = data_->buffer_ + start;
                    auto endPtr = data_->buffer_ + dataSize - searchSequenceLength;

                    while ( ptr <= endPtr )
                    {
                        auto* p = reinterpret_cast< const Byte* >( memchr( ptr, *searchSequence, static_cast< size_type >( endPtr - ptr ) + searchSequenceLength ) );
                        if ( p && p <= endPtr )
                        {
                            auto compareLength = searchSequenceLength - 1;
                            if ( memcmp( p + 1, searchSequence + 1, compareLength ) == 0 )
                            {
                                return static_cast< size_type >( p - data_->buffer_ );
                            }
                            ptr = p + 1;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            return npos;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] size_type IndexOf( const T& searchSequence, size_type start = 0 ) const
        {
            return IndexOf( searchSequence.data( ), searchSequence.size( ), start );
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] size_type find( const T& searchSequence, size_type start = 0 ) const
        {
            return IndexOf( searchSequence.data( ), searchSequence.size( ), start );
        }

        [[nodiscard]] size_type IndexOf( Byte searchValue, size_type start ) const
        {
            return IndexOf( &searchValue, 1, start );
        }
        [[nodiscard]] size_type find( Byte searchValue, size_type start ) const
        {
            return IndexOf( &searchValue, 1, start );
        }

        [[nodiscard]] size_type LastIndexOf( const Byte* searchSequence, size_type searchSequenceLength, size_type start ) const
        {
            if ( data_ && ( searchSequenceLength <= data_->size_ ) )
            {
                if ( start > ( data_->size_ - searchSequenceLength ) )
                {
                    start = data_->size_ - searchSequenceLength;
                }

                if ( searchSequenceLength == 1 )
                {
                    do
                    {
                        if ( data_->buffer_[ start ] == *searchSequence )
                        {
                            return start;
                        }
                    } while ( start-- );
                }
                else if ( searchSequenceLength )
                {
                    do
                    {
                        if ( memcmp( &data_->buffer_[ start ], searchSequence, searchSequenceLength ) == 0 )
                        {
                            return start;
                        }
                    } while ( start-- );
                }
            }
            return npos;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] size_type LastIndexOf( const T& searchSequence, size_type start = npos ) const
        {
            return LastIndexOf( searchSequence.data( ), searchSequence.size( ), start );
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] size_type find_last( const T& searchSequence, size_type start = npos ) const
        {
            return LastIndexOf( searchSequence.data( ), searchSequence.size( ), start );
        }

        [[nodiscard]] size_type LastIndexOf( Byte searchValue, size_type start = npos ) const
        {
            return LastIndexOf( &searchValue, 1, start );
        }

        [[nodiscard]] size_type find_last( Byte searchValue, size_type start = npos ) const
        {
            return LastIndexOf( &searchValue, 1, start );
        }

        [[nodiscard]] bool StartsWith( const Byte b ) const
        {
            if ( data_ )
            {
                auto size = data_->size_;
                if ( size )
                {
                    return data_->buffer_[ 0 ] == b;
                }
            }
            return false;
        }
        [[nodiscard]] bool starts_with( Byte b ) const
        {
            return StartsWith( b );
        }

        [[nodiscard]] bool StartsWith( const Byte* buffer, size_t bufferSize ) const
        {
            if ( buffer && bufferSize && data_ && data_->size_ >= bufferSize )
            {
                const auto* p = data_->buffer_;
                const auto* endOfBuffer = buffer + bufferSize;
                while ( buffer < endOfBuffer )
                {
                    if ( *p != *buffer )
                    {
                        break;
                    }
                    p++;
                    buffer++;
                }
                return buffer == endOfBuffer;
            }
            return false;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] bool StartsWith( const T& buffer ) const
        {
            return StartsWith( buffer.data( ), StartsWith.size( ) );
        }

        [[nodiscard]] bool EndsWith( const Byte b ) const
        {
            if ( data_ )
            {
                auto size = data_->size_;
                if ( size )
                {
                    return data_->buffer_[ size - 1 ] == b;
                }
            }
            return false;
        }

        [[nodiscard]] bool ends_with( const Byte b ) const
        {
            return EndsWith( b );
        }

        [[nodiscard]] bool EndsWith( const Byte* buffer, size_t bufferSize ) const
        {
            if ( buffer && bufferSize && data_ && data_->size_ && data_->size_ >= bufferSize )
            {
                return memcmp( &data_->buffer_[ data_->size_ - bufferSize ], buffer, bufferSize ) == 0;
            }
            return false;
        }
        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] bool EndsWith( const T& buffer ) const
        {
            return EndsWith( buffer.data( ), StartsWith.size( ) );
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<std::remove_cvref_t<typename T::value_type>, Byte>
        [[nodiscard]] bool ends_with( const T& buffer ) const
        {
            return EndsWith( buffer.data( ), StartsWith.size( ) );
        }

        [[nodiscard]] Binary SubString( size_type start, size_type length = npos ) const
        {
            if ( data_ && ( start < data_->size_ ) )
            {
                if ( length > ( data_->size_ - start ) )
                {
                    length = data_->size_ - start;
                }
                if ( ( start == 0 ) && ( length == data_->size_ ) )
                {
                    return Binary( data_ );
                }
                else
                {
                    return Binary( data_->buffer_ + start, length );
                }
            }
            else
            {
                return Binary( );
            }
        }

        void erase( )
        {
            ReleaseData( data_ );
            data_ = nullptr;
        }

        void erase( size_type index, size_type count = npos )
        {
            Erase( index, count );
        }

        iterator erase( const_iterator position )
        {
            // RangeCheck throws if data_ is nullptr
            RangeCheck( position );
            return Erase( static_cast< size_type >( position - begin( ) ), 1 );
        }


        void Clear( )
        {
            ReleaseData( data_ );
            data_ = nullptr;
        }

        void clear( )
        {
            Clear( );
        }

        void Remove( size_type start, size_type length = npos )
        {
            if ( data_ && start < data_->size_ )
            {
                Erase( start, length );
            }
        }

        void RemoveRange( size_type start, size_type end )
        {
            if ( data_ && start < data_->size_ && start < end )
            {
                Erase( start, end - start );
            }
        }

        void Replace( size_type replaceAtPosition, size_type replaceLength, const Byte* with, size_type withLength, Byte padValue = '\x0' )
        {
            if ( data_ )
            {
                auto currentLength = data_->size_;
                auto currentAllocationSize = AllocationByteCount( currentLength );
                if ( ( data_->referenceCount_ == 1 ) &&
                    ( data_->Contains( with, replaceAtPosition ) == false ) )
                {
                    if ( replaceAtPosition < currentLength )
                    {
                        auto maxReplaceLength = currentLength - replaceAtPosition;
                        if ( maxReplaceLength < replaceLength )
                        {
                            replaceLength = maxReplaceLength;
                        }
                        if ( withLength != replaceLength )
                        {
                            auto newLength = currentLength + withLength - replaceLength;
                            auto curentRemainingPosition = replaceAtPosition + replaceLength;
                            auto remainingLength = currentLength - curentRemainingPosition;
                            auto newRemainingPosition = replaceAtPosition + withLength;
                            size_type newAllocationSize = AllocationByteCount( newLength );
                            if ( newAllocationSize == currentAllocationSize )
                            {
                                memmove( data_->buffer_ + newRemainingPosition, data_->buffer_ + curentRemainingPosition, remainingLength );
                                memmove( data_->buffer_ + replaceAtPosition, with, withLength );
                                data_->size_ = newLength;
                            }
                            else
                            {
                                std::unique_ptr<Data> tmp( Allocate( newAllocationSize, newLength ) );
                                memcpy( tmp->buffer_, data_->buffer_, replaceAtPosition );
                                memcpy( tmp->buffer_ + newRemainingPosition, data_->buffer_ + curentRemainingPosition, remainingLength );
                                memcpy( tmp->buffer_ + replaceAtPosition, with, withLength );
                                ReleaseData( data_ );
                                data_ = tmp.release( );
                            }
                        }
                        else
                        {
                            // No change in size, just overwrite
                            memmove( data_->buffer_ + replaceAtPosition, with, withLength );
                        }
                    }
                    else
                    {
                        if ( withLength )
                        {
                            auto newLength = replaceAtPosition + withLength;
                            size_type newAllocationSize = AllocationByteCount( newLength );
                            if ( newAllocationSize == currentAllocationSize )
                            {
                                memset( data_->buffer_ + data_->size_, padValue, replaceAtPosition - data_->size_ );
                                memcpy( data_->buffer_ + replaceAtPosition, with, withLength );
                                data_->size_ = newLength;
                            }
                            else
                            {
                                std::unique_ptr<Data> tmp( Initialize( data_->buffer_, data_->size_, padValue, replaceAtPosition, with, withLength ) );
                                ReleaseData( data_ );
                                data_ = tmp.release( );
                            }
                        }
                    }
                }
                else
                {
                    if ( replaceAtPosition < currentLength )
                    {
                        auto maxReplaceLength = currentLength - replaceAtPosition;
                        if ( maxReplaceLength < replaceLength )
                        {
                            replaceLength = maxReplaceLength;
                        }

                        auto newLength = currentLength + withLength - replaceLength;
                        auto curentRemainingPosition = replaceAtPosition + replaceLength;
                        auto remainingLength = currentLength - curentRemainingPosition;
                        auto newRemainingPosition = replaceAtPosition + withLength;
                        size_type newAllocationSize = AllocationByteCount( newLength );

                        std::unique_ptr<Data> tmp( Allocate( newAllocationSize, newLength ) );
                        memcpy( tmp->buffer_, data_->buffer_, replaceAtPosition );
                        memcpy( tmp->buffer_ + newRemainingPosition, data_->buffer_ + curentRemainingPosition, remainingLength );
                        memcpy( tmp->buffer_ + replaceAtPosition, with, withLength );
                        ReleaseData( data_ );
                        data_ = tmp.release( );
                    }
                    else
                    {
                        if ( withLength )
                        {
                            std::unique_ptr<Data> tmp( Initialize( data_->buffer_, data_->size_, padValue, replaceAtPosition - data_->size_, with, withLength ) );
                            ReleaseData( data_ );
                            data_ = tmp.release( );
                        }
                    }
                }
            }
            else
            {
                data_ = Initialize( padValue, replaceAtPosition, with, withLength );
            }
        }

        void replace( size_type replaceAtPosition, size_type replaceLength, const Byte* with, size_type withLength, Byte padValue = '\x0' )
        {
            Replace( replaceAtPosition, replaceLength, with, withLength, padValue );
        }

        void Replace( const_iterator replaceFirst, const_iterator replaceLast, const Byte* with, size_type withLength, Byte padValue = '\x0' )
        {
            size_type replaceAtPosition = std::distance( cbegin( ), replaceFirst );
            size_type replaceLength = replaceLast.ptr_ - replaceFirst.ptr_;
            Replace( replaceAtPosition, replaceLength, with, withLength, padValue );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, Byte>
        void Replace( size_type replaceAtPosition, size_type replaceLength, const SpanT& with, Byte padValue = '\x0' )
        {
            Replace( replaceAtPosition, replaceLength, with.data( ), with.size( ), padValue );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, Byte>
        void replace( size_type replaceAtPosition, size_type replaceLength, const SpanT& with, Byte padValue = '\x0' )
        {
            Replace( replaceAtPosition, replaceLength, with.data( ), with.size( ), padValue );
        }

    };

    namespace Internal
    {
        HCC_EXPORT void ThrowFixedBinaryArgumentToLong( size_t size, size_t maxSize );
        template<size_t maxSize>
        inline size_t CheckFixedBinarySize( size_t size )
        {
            if ( size > maxSize )
            {
                ThrowFixedBinaryArgumentToLong( size, maxSize );
            }
            return size;
        }
    }


    template<size_t maxSize>
    class FixedBinary
    {
    public:
        using value_type = Byte;

        static constexpr size_t MaxSize = maxSize;
        using ArrayType = std::array<Byte, MaxSize>;

        using size_type = typename ArrayType::size_type;
        using difference_type = typename ArrayType::difference_type;
        using pointer = typename ArrayType::pointer;
        using const_pointer = typename ArrayType::const_pointer;
        using reference = typename ArrayType::reference;
        using const_reference = typename ArrayType::const_reference;
        using iterator = typename ArrayType::iterator;
        using const_iterator = typename ArrayType::const_iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    protected:
        size_t size_ = 0;
    private:
        ArrayType data_ = {};
    protected:
        static size_t CheckSize( size_t size )
        {
            return Internal::CheckFixedBinarySize<MaxSize>( size );
        }
    public:
        FixedBinary( ) noexcept = default;

        explicit FixedBinary( const Byte* buffer, size_t size )
            : size_( CheckSize( size ) )
        {
            memcpy( data_.data( ), buffer, size );
        }

        template<typename T>
            requires std::is_same_v<typename T::value_type, Byte>&&
            requires( const T& v )
        {
            { v.data( ) }->std::convertible_to<const Byte*>;
            { v.size( ) }->std::convertible_to<size_t>;
        }
        explicit FixedBinary( const T& buffer )
            : size_( CheckSize( buffer.size( ) ) )
        {
            memcpy( data_.data( ), buffer.data( ), size_ );
        }

        template<typename T>
            requires std::is_same_v<typename T::value_type, Byte>&&
            requires( const T& v )
        {
            { v.data( ) }->std::convertible_to<const Byte*>;
            { v.size( ) }->std::convertible_to<size_t>;
        }
        FixedBinary& operator = ( const T& buffer )
        {
            size_ = CheckSize( buffer.size( ) );
            memcpy( data_.data( ), buffer.data( ), size_ );
            return *this;
        }


        [[nodiscard]] constexpr size_type size( ) const noexcept
        {
            return size_ <= MaxSize ? size_ : 0;
        }
        [[nodiscard]] constexpr size_type length( ) const noexcept
        {
            return size_ <= MaxSize ? size_ : 0;
        }
        [[nodiscard]] constexpr size_type Length( ) const noexcept
        {
            return size_ <= MaxSize ? size_ : 0;
        }

        [[nodiscard]] constexpr bool empty( ) const noexcept
        {
            return size( ) == 0;
        }

        [[nodiscard]] iterator begin( ) noexcept
        {
            return data_.begin( );
        }
        [[nodiscard]] const_iterator begin( ) const noexcept
        {
            return data_.begin( );
        }

        [[nodiscard]] iterator end( ) noexcept
        {
            return data_.begin( ) + size( );
        }
        [[nodiscard]] const_iterator end( ) const noexcept
        {
            return data_.begin( ) + size( );
        }

        [[nodiscard]] reverse_iterator rbegin( ) noexcept
        {
            return reverse_iterator( end( ) );
        }

        [[nodiscard]] const_reverse_iterator rbegin( ) const noexcept
        {
            return const_reverse_iterator( end( ) );
        }

        [[nodiscard]] reverse_iterator rend( ) noexcept
        {
            return reverse_iterator( begin( ) );
        }

        [[nodiscard]] const_reverse_iterator rend( ) const noexcept
        {
            return const_reverse_iterator( begin( ) );
        }

        [[nodiscard]] const_iterator cbegin( ) const noexcept
        {
            return begin( );
        }

        [[nodiscard]] const_iterator cend( ) const noexcept
        {
            return end( );
        }

        [[nodiscard]] const_reverse_iterator crbegin( ) const noexcept
        {
            return rbegin( );
        }

        [[nodiscard]] const_reverse_iterator crend( ) const noexcept
        {
            return rend( );
        }

        [[nodiscard]] constexpr const Byte* data( ) const noexcept
        {
            return data_.data( );
        }
        [[nodiscard]] constexpr Byte* data( ) noexcept
        {
            return data_.data( );
        }

        [[nodiscard]] constexpr reference at( size_type index ) noexcept
        {
            return data_.at( index );
        }
        [[nodiscard]] constexpr const_reference at( size_type index ) const noexcept
        {
            return data_.at( index );
        }

        [[nodiscard]] constexpr reference operator[]( size_type index ) noexcept
        {
            return data_[ index ];
        }
        [[nodiscard]] constexpr const_reference operator[]( size_type index ) const noexcept
        {
            return data_[ index ];
        }

        [[nodiscard]] constexpr reference front( ) noexcept
        {
            return data_[ 0 ];
        }

        [[nodiscard]] constexpr const_reference front( ) const noexcept
        {
            return data_[ 0 ];
        }

        [[nodiscard]] constexpr reference back( ) noexcept
        {
            return data_[ size( ) - 1 ];
        }

        [[nodiscard]] constexpr const_reference back( ) const noexcept
        {
            return data_[ size( ) - 1 ];
        }

    private:
        [[nodiscard]] static bool AreEqual( const Byte* first, size_type firstSize, const Byte* second, size_type secondSize )
        {
            if ( first && firstSize )
            {
                if ( second )
                {
                    if ( firstSize == secondSize )
                    {
                        return memcmp( first, second, secondSize ) == 0;
                    }
                }
                return false;
            }
            return second && secondSize ? false : true;
        }

    public:
        template<size_t M>
        bool operator == ( const FixedBinary<M>& other ) const
        {
            return AreEqual( data( ), size( ), other.data( ), other.size( ) );
        }
        template<size_t M>
        bool operator != ( const FixedBinary<M>& other ) const
        {
            return AreEqual( data( ), size( ), other.data( ), other.size( ) ) == false;
        }

    };


}


#endif
