#pragma once
#ifndef __HCCSTRING_H__
#define __HCCSTRING_H__
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

#include <HCCDef.h>
#include <HCCTraits.h>
#include <HCCConcepts.h>
#include <HCCException.h>
#include <HCCIterator.h>



namespace Harlinn::Common::Core
{

#ifdef HCC_WITH_BASIC_STRING
    namespace Internal
    {
        inline char* AllocateBytes( size_t count )
        {
            return ( char* )malloc( count );
        }
        inline void FreeBytes( char* bytes, size_t size )
        {
            free( bytes );
        }
        
        template<typename CharT>
            requires std::is_same_v<CharT, char> || std::is_same_v<CharT, wchar_t>
        inline bool AreEqual( const CharT* first, int firstLength, const CharT* second, int secondLength )
        {
            if ( firstLength == secondLength )
            {
                if ( first != second )
                {
                    return MemCmp( first, second, firstLength ) == 0;
                }
                else
                {
                    return true;
                }
            }
            return false;
        }

        inline int Compare( DWORD compareFlags, const char* first, int firstLength, const char* second, int secondLength )
        {
            if ( first && second )
            {
                auto result = CompareStringA( LOCALE_USER_DEFAULT, compareFlags, first, firstLength, second, secondLength );
                if ( !result )
                {
                    ThrowLastOSError( );
                }
                return result - 2;
            }
            else if ( first )
            {
                return 1;
            }
            else if ( second )
            {
                return -1;
            }
            return 0;
        }

        inline int Compare( DWORD compareFlags, const wchar_t* first, int firstLength, const wchar_t* second, int secondLength )
        {
            if ( first && second )
            {
                auto result = CompareStringW( LOCALE_USER_DEFAULT, compareFlags, first, static_cast<int>( firstLength ), second, static_cast<int>( secondLength ) );
                if ( !result )
                {
                    ThrowLastOSError( );
                }
                return result - 2;
            }
            else if ( first )
            {
                return 1;
            }
            else if ( second )
            {
                return -1;
            }
            return 0;
        }


        inline int Compare( const char* first, size_t firstLength, const char* second, size_t secondLength )
        {
            return Compare( 0, first, static_cast<int>( firstLength ), second, static_cast<int>( secondLength ) );
        }

        inline int Compare( const wchar_t* first, size_t firstLength, const wchar_t* second, size_t secondLength )
        {
            return Compare( 0, first, static_cast<int>( firstLength ), second, static_cast<int>( secondLength ) );
        }

        inline int Compare( const char* first, size_t firstLength, const char* second )
        {
            return Compare( 0, first, static_cast<int>( firstLength ), second, -1 );
        }

        inline int Compare( const wchar_t* first, size_t firstLength, const wchar_t* second )
        {
            return Compare( 0, first, static_cast<int>( firstLength ), second, -1 );
        }

        inline int Compare( const char* first, const char* second, size_t secondLength )
        {
            return Compare( 0, first, -1, second, static_cast<int>( secondLength ) );
        }

        inline int Compare( const wchar_t* first, const wchar_t* second, size_t secondLength )
        {
            return Compare( 0, first, -1, second, static_cast<int>( secondLength ) );
        }


        inline int Compare( const char* first, const char* second )
        {
            return Compare( 0, first, -1, second, -1 );
        }
        inline int Compare( const wchar_t* first, const wchar_t* second )
        {
            return Compare( 0, first, -1, second, -1 );
        }

        inline int ICompare( const char* first, size_t firstLength, const char* second, size_t secondLength )
        {
            return Compare( NORM_IGNORECASE, first, static_cast<int>( firstLength ), second, static_cast<int>( secondLength ) );
        }

        inline int ICompare( const wchar_t* first, size_t firstLength, const wchar_t* second, size_t secondLength )
        {
            return Compare( NORM_IGNORECASE, first, static_cast<int>( firstLength ), second, static_cast<int>( secondLength ) );
        }

        inline int ICompare( const char* first, size_t firstLength, const char* second )
        {
            return Compare( NORM_IGNORECASE, first, static_cast<int>( firstLength ), second, -1 );
        }

        inline int ICompare( const wchar_t* first, size_t firstLength, const wchar_t* second )
        {
            return Compare( NORM_IGNORECASE, first, static_cast<int>( firstLength ), second, -1 );
        }

        inline int ICompare( const char* first, const char* second, size_t secondLength )
        {
            return Compare( NORM_IGNORECASE, first, -1, second, static_cast<int>( secondLength ) );
        }

        inline int ICompare( const wchar_t* first, const wchar_t* second, size_t secondLength )
        {
            return Compare( NORM_IGNORECASE, first, -1, second, static_cast<int>( secondLength ) );
        }


        inline int ICompare( const char* first, const char* second )
        {
            return Compare( NORM_IGNORECASE, first, -1, second, -1 );
        }
        inline int ICompare( const wchar_t* first, const wchar_t* second )
        {
            return Compare( NORM_IGNORECASE, first, -1, second, -1 );
        }


        

        





        inline bool IsSpace( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isspace( c );
#pragma warning(pop)
        }
        inline bool IsSpace( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswspace( c );
#pragma warning(pop)
        }


        inline bool IsControl( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iscntrl( c );
#pragma warning(pop)
        }
        inline bool IsControl( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswcntrl( c );
#pragma warning(pop)
        }

        inline bool IsDigit( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isdigit( c );
#pragma warning(pop)
        }
        inline bool IsDigit( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswdigit( c );
#pragma warning(pop)
        }

        inline bool IsLetter( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isalpha( c );
#pragma warning(pop)
        }
        inline bool IsLetter( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswalpha( c );
#pragma warning(pop)
        }

        inline bool IsLetterOrDigit( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isalnum( c );
#pragma warning(pop)
        }
        inline bool IsLetterOrDigit( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswalnum( c );
#pragma warning(pop)
        }


        inline bool IsLower( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return islower( c );
#pragma warning(pop)
        }
        inline bool IsLower( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswlower( c );
#pragma warning(pop)
        }


        inline bool IsUpper( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isupper( c );
#pragma warning(pop)
        }
        inline bool IsUpper( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswupper( c );
#pragma warning(pop)
        }

        inline bool IsPunctuation( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return ispunct( c );
#pragma warning(pop)
        }
        inline bool IsPunctuation( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswpunct( c );
#pragma warning(pop)
        }

        inline bool IsWhiteSpace( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isspace( c );
#pragma warning(pop)
        }
        inline bool IsWhiteSpace( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswspace( c );
#pragma warning(pop)
        }



        template< typename T >
        struct Data
        {
            using CharType = T;
            size_t referenceCount_ = 1;
            size_t size_ = 0;
            CharType buffer_[1024];

            size_t AddRef( ) noexcept
            {
                return InterlockedIncrementSizeT( &referenceCount_ );
            }

            size_t DecRef( ) noexcept
            {
                return InterlockedDecrementSizeT( &referenceCount_ );
            }

            constexpr bool Contains( const CharType* ptr ) noexcept
            {
                return ptr >= buffer_ && ptr <= (buffer_ + size_);
            }
            constexpr bool Contains( const CharType* ptr, size_t startPosition ) noexcept
            {
                return ptr >= (buffer_ + startPosition ) && ptr <= ( buffer_ + size_ );
            }

        };


        HCC_EXPORT WideString From( const char* text, size_t textLength, unsigned codePage = CP_ACP, unsigned flags = 0 );
        HCC_EXPORT AnsiString From( const wchar_t* text, size_t textLength, unsigned codePage = CP_ACP, unsigned flags = 0 );

        template<typename CharType> 
        const CharType* SkipWhiteSpace( const CharType* start, const CharType* end )
        {
            while ( start < end )
            {
                CharType c = *start;
                if ( IsWhiteSpace( c ) == false )
                {
                    break;
                }
                ++start;
            }
            return start;
        }

        template<typename CharType, bool ignoreWhiteSpace, typename VectorT>
        const CharType* SplitProcessToken( const CharType* start, const CharType* end, CharType separator, VectorT& result )
        {
            using DestinationT = typename VectorT::value_type;
            auto pos = start;
            if constexpr ( ignoreWhiteSpace )
            {
                
                while ( pos < end )
                {
                    CharType c = *pos;
                    if ( c == separator || IsWhiteSpace( c ) )
                    {
                        break;
                    }
                    ++pos;
                }
                result.emplace_back( start, static_cast<typename DestinationT::size_type >( pos - start ) );
                return pos;
            }
            else
            {
                while ( pos < end )
                {
                    CharType c = *pos;
                    if ( c == separator )
                    {
                        break;
                    }
                    ++pos;
                }
                result.emplace_back( start, static_cast< typename DestinationT::size_type >( pos - start ) );
                return pos;
            }
        }

        template<typename CharType, bool ignoreWhiteSpace>
        const CharType* SplitProcessSeparator( const CharType* start, const CharType* end, CharType separator, bool& foundSeparator )
        {
            foundSeparator = false;
            auto pos = start;
            if constexpr ( ignoreWhiteSpace )
            {
                pos = SkipWhiteSpace( pos, end );
                if ( pos < end )
                {
                    CharType c = *pos;
                    if ( c == separator )
                    {
                        foundSeparator = true;
                        pos++;
                    }
                    pos = SkipWhiteSpace( pos, end );
                }
                return pos;
            }
            else
            {
                if ( pos < end )
                {
                    CharType c = *pos;
                    if ( c == separator )
                    {
                        foundSeparator = true;
                        pos++;
                    }
                }
                return pos;
            }
        }



        template<typename CharType, bool ignoreWhiteSpace = true, typename VectorT>
        void Split( const CharType* string, size_t stringLength, CharType separator, VectorT& result )
        {
            using DestinationT = typename VectorT::value_type;
            auto startIt = string;
            auto endIt = string + stringLength;
            result.clear( );
            bool moreTokensExpected = true;
            while ( startIt < endIt && moreTokensExpected )
            {
                startIt = SplitProcessToken<CharType, ignoreWhiteSpace, VectorT>( startIt, endIt, separator, result );
                startIt = SplitProcessSeparator<CharType, ignoreWhiteSpace>( startIt, endIt, separator, moreTokensExpected );
            }
            if ( moreTokensExpected )
            {
                result.emplace_back( );
            }
        }


    }

    /// <summary>
    /// This is a reference counted string class.
    /// </summary>
    /// <remarks>
    /// There are potential pitfalls when this class is used in 
    /// a multi-threaded program, but they can easily be avoided:
    /// 
    ///     1. There should be no problems as long as the strings 
    ///        are just passed around between threads. This is
    ///        the normal/most common use case.
    /// 
    ///     2. Call EnsureUnique before changes are made using 
    ///        character references, iterators and pointers to
    ///        the contents of a string. This will invalidate
    ///        existing references, iterators and pointers to
    ///        the contents of that string object, but not references, 
    ///        iterators and pointers to other string objects that
    ///        originally shared the internal reference counted string
    ///        representation. Ideally the editing functions should
    ///        be used to change the contents of a string.
    ///     
    ///     3. Never call an editing function using a reference 
    ///        to a string object that is shared between threads.
    ///        Two string objects, each local to a separate thread,
    ///        may share the same internal data object, and this is
    ///        fine, but sharing a reference/pointer to a string object 
    ///        between threads is not OK when editing functions will 
    ///        be called. 
    /// </remarks>
    /// <typeparam name="T">The character type of the string</typeparam>
    template<typename T>
    class BasicString
    {
    public:
        using CharType = T;
        using value_type = T;

        using pointer = CharType*;
        using const_pointer = const CharType*;
        using reference = CharType&;
        using const_reference = const CharType&;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

        using iterator = Internal::PointerIterator<BasicString<T>>;
        using const_iterator = Internal::ConstPointerIterator<BasicString<T>>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;


        static constexpr size_type npos = MAXUINT64;
        static constexpr size_type AllocationGranularity = 64;
        static constexpr CharType DefaultPadCharacter = static_cast< CharType >( ' ' );
        using Data = Internal::Data<CharType>;
        static constexpr size_t BufferHeaderSize = offsetof( Data, buffer_ );
        static constexpr size_type NonTextBufferByteCount = BufferHeaderSize + sizeof( CharType );
    private:
        Data* data_;


        static constexpr size_type AllocationByteCount( size_type length ) noexcept
        {
            return length ? ( ( NonTextBufferByteCount + length * sizeof( CharType ) ) + ( AllocationGranularity - 1 ) ) & ~( AllocationGranularity - 1 ) : 0;
        }
        static constexpr size_type AllocationByteCountForLengthNotZero( size_type length ) noexcept
        {
            return ( ( NonTextBufferByteCount + length * sizeof( CharType ) ) + ( AllocationGranularity - 1 ) ) & ~( AllocationGranularity - 1 );
        }


        static Data* Allocate( size_t size )
        {
            size_t allocationByteCount = AllocationByteCount( size );
            Data* data = (Data*)Internal::AllocateBytes( allocationByteCount );
            data->referenceCount_ = 1;
            data->size_ = size;
            data->buffer_[size] = 0;
            return data;
        }

        static Data* Allocate( size_type allocationByteCount, size_t size )
        {
            Data* data = ( Data* )Internal::AllocateBytes( allocationByteCount );
            data->referenceCount_ = 1;
            data->size_ = size;
            data->buffer_[ size ] = 0;
            return data;
        }

        static void ReleaseData( Data* data )
        {
            if ( data && data->DecRef( ) == 0 )
            {
                size_t allocationByteCount = AllocationByteCountForLengthNotZero( data->size_ );
                Internal::FreeBytes( (char*)data, allocationByteCount );
            }
        }


        CharType* ExpandIntoNewBuffer( size_t offset, size_t expandSize )
        {
            auto currentSize = data_->size_;
            auto newSize = currentSize + expandSize;
            auto newData = Allocate( newSize );
            MemCopy( newData->buffer_, data_->buffer_, offset );
            auto remaining = currentSize - offset;
            MemCopy( &newData->buffer_[offset + expandSize], &data_->buffer_[offset], remaining );
            auto* tmp = data_;
            data_ = newData;
            ReleaseData( tmp );
            return &newData->buffer_[offset];
        }

        CharType* ExpandCurrentBuffer( size_t offset, size_t expandSize )
        {
            auto currentSize = data_->size_;
            auto remaining = currentSize - offset;
            MemMove( &data_->buffer_[offset + expandSize], &data_->buffer_[offset], remaining );
            data_->size_ += expandSize;
            data_->buffer_[data_->size_] = 0;
            return &data_->buffer_[offset];
        }


        CharType* Expand( size_t offset, size_t expandSize )
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

        CharType* ExtendIntoNewBuffer( size_t extendSize )
        {
            auto currentSize = data_->size_;
            auto newSize = currentSize + extendSize;
            auto newData = Allocate( newSize );
            MemCopy( newData->buffer_, data_->buffer_, currentSize );
            auto* tmp = data_;
            data_ = newData;
            ReleaseData( tmp );
            return &newData->buffer_[currentSize];
        }

        CharType* ExtendCurrentBuffer( size_t extendSize )
        {
            auto currentSize = data_->size_;
            data_->size_ += extendSize;
            data_->buffer_[data_->size_] = 0;
            return &data_->buffer_[currentSize];
        }

        CharType* Extend( size_t extendSize )
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
                throw std::out_of_range( "string is empty" );
            }
        }



        CharType* Erase( size_t offset, size_t numberOfCharactersToErase )
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
                                auto* dest = &data_->buffer_[offset];
                                MemCopy( dest, dest + numberOfCharactersToErase, remainingSize );
                            }
                            data_->buffer_[newSize] = 0;
                            data_->size_ = newSize;
                        }
                        else
                        {
                            auto* newData = Allocate( newSize );
                            if ( offset )
                            {
                                MemCopy( newData->buffer_, data_->buffer_, offset );
                            }
                            size_t remainingSize = currentSize - ( offset + numberOfCharactersToErase );
                            if ( remainingSize )
                            {
                                MemCopy( &newData->buffer_[offset], &data_->buffer_[offset + numberOfCharactersToErase], remainingSize );
                            }
                            ReleaseData( data_ );
                            data_ = newData;
                        }
                        return &data_->buffer_[offset];

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


        static Data* Initialize( const CharType* string, size_type size )
        {
            if ( size )
            {
                Data* data = Allocate( size );
                MemCopy( data->buffer_, string, size );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        static Data* Initialize( const CharType* string1, size_type size1, const CharType* string2, size_type size2 )
        {
            auto size = size1 + size2;
            if ( size )
            {
                Data* data = Allocate( size );
                MemCopy( data->buffer_, string1, size1 );
                MemCopy( data->buffer_ + size1, string2, size2 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        static Data* Initialize( CharType value, size_type count, const CharType* string2, size_type size2 )
        {
            auto size = count + size2;
            if ( size )
            {
                Data* data = Allocate( size );
                MemSet( data->buffer_, value, count );
                MemCopy( data->buffer_ + count, string2, size2 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        static Data* Initialize( const CharType* string1, size_type size1, CharType value, size_type count )
        {
            auto size = size1 + count;
            if ( size )
            {
                Data* data = Allocate( size );
                MemCopy( data->buffer_, string1, size1 );
                MemSet( data->buffer_ + size1, value, count );
                return data;
            }
            else
            {
                return nullptr;
            }
        }



        static Data* Initialize( const CharType* string1, size_type size1, const CharType* string2, size_type size2, const CharType* string3, size_type size3 )
        {
            auto size = size1 + size2 + size3;
            if ( size )
            {
                Data* data = Allocate( size );
                MemCopy( data->buffer_, string1, size1 );
                MemCopy( data->buffer_ + size1, string2, size2 );
                MemCopy( data->buffer_ + size1 + size2, string3, size3 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        static Data* Initialize( CharType value, size_type count, const CharType* string2, size_type size2, const CharType* string3, size_type size3 )
        {
            auto size = count + size2 + size3;
            if ( size )
            {
                Data* data = Allocate( size );
                MemSet( data->buffer_, value, count );
                MemCopy( data->buffer_ + count, string2, size2 );
                MemCopy( data->buffer_ + count + size2, string3, size3 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }


        static Data* Initialize( const CharType* string1, size_type size1, CharType value, size_type count, const CharType* string3, size_type size3 )
        {
            auto size = size1 + count + size3;
            if ( size )
            {
                Data* data = Allocate( size );
                MemCopy( data->buffer_, string1, size1 );
                MemSet( data->buffer_ + size1, value, count );
                MemCopy( data->buffer_ + size1 + count, string3, size3 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        static Data* Initialize( const CharType* string1, size_type size1, const CharType* string2, size_type size2, CharType value, size_type count )
        {
            auto size = size1 + size2 + count;
            if ( size )
            {
                Data* data = Allocate( size );
                MemCopy( data->buffer_, string1, size1 );
                MemCopy( data->buffer_ + size1, string2, size2 );
                MemSet( data->buffer_ + size1 + size2, value, count );
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


        static Data* Initialize( const CharType* string )
        {
            auto size = Internal::LengthOf( string );
            return Initialize( string, size );
        }

        static Data* Initialize( size_type count, CharType value )
        {
            if ( count )
            {
                Data* data = Allocate( count );
                MemSet( data->buffer_, value, count );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        BasicString( Data* data, bool addRef = true ) noexcept
            : data_( data )
        {
            if ( addRef && data )
            {
                data->AddRef( );
            }
        }
    public:
        constexpr BasicString( ) noexcept
            : data_( nullptr )
        {
        }

        explicit BasicString( const CharType* string )
            : data_( Initialize( string ) )
        {
        }

        explicit BasicString( const CharType* string, size_type size )
            : data_( Initialize( string, size ) )
        {
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        explicit BasicString( const SpanT& span )
            : data_( Initialize( span.data(), span.size() ) )
        {
        }

        explicit BasicString( const CharType* string1, size_type size1, const CharType* string2, size_type size2 )
            : data_( Initialize( string1, size1, string2, size2 ) )
        {
        }

        explicit BasicString( CharType value, size_type count, const CharType* string2, size_type size2 )
            : data_( Initialize( value, count, string2, size2 ) )
        {
        }

        explicit BasicString( const CharType* string1, size_type size1, CharType value, size_type count )
            : data_( Initialize( string1, size1, value, count ) )
        {
        }


        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires (std::is_same_v<typename SpanT1::value_type, CharType> && std::is_same_v<typename SpanT2::value_type, CharType> )
        explicit BasicString( const SpanT1& span1, const SpanT2& span2 )
            : data_( Initialize( span1.data( ), span1.size( ), span2.data( ), span2.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        explicit BasicString( const SpanT& span1, const CharType* string2, size_type size2 )
            : data_( Initialize( span1.data( ), span1.size( ), string2, size2 ) )
        {
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        explicit BasicString( const CharType* string1, size_type size1, const SpanT& span2 )
            : data_( Initialize( string1, size1, span2.data( ), span2.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        explicit BasicString( CharType value, size_type count, const SpanT& span )
            : data_( Initialize( value, count, span.data( ), span.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        explicit BasicString( CharType value, const SpanT& span )
            : data_( Initialize( value, 1, span.data( ), span.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        explicit BasicString( const SpanT& span, CharType value, size_type count )
            : data_( Initialize( span.data( ), span.size( ), value, count ) )
        {
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        explicit BasicString( const SpanT& span, CharType value )
            : data_( Initialize( span.data( ), span.size( ), value, 1 ) )
        {
        }



        explicit BasicString( const CharType* string1, size_type size1, const CharType* string2, size_type size2, const CharType* string3, size_type size3 )
            : data_( Initialize( string1, size1, string2, size2, string3, size3 ) )
        {
        }

        explicit BasicString( CharType value, size_type count, const CharType* string2, size_type size2, const CharType* string3, size_type size3 )
            : data_( Initialize( value, count, string2, size2, string3, size3 ) )
        {
        }

        explicit BasicString( const CharType* string1, size_type size1, CharType value, size_type count, const CharType* string3, size_type size3 )
            : data_( Initialize( string1, size1, value, count, string3, size3 ) )
        {
        }

        explicit BasicString( const CharType* string1, size_type size1, const CharType* string2, size_type size2, CharType value, size_type count )
            : data_( Initialize( string1, size1, string2, size2, value, count ) )
        {
        }

        explicit BasicString( CharType value, const CharType* string2, size_type size2, const CharType* string3, size_type size3 )
            : data_( Initialize( value, 1, string2, size2, string3, size3 ) )
        {
        }

        explicit BasicString( const CharType* string1, size_type size1, CharType value, const CharType* string3, size_type size3 )
            : data_( Initialize( string1, size1, value, 1, string3, size3 ) )
        {
        }

        explicit BasicString( const CharType* string1, size_type size1, const CharType* string2, size_type size2, CharType value )
            : data_( Initialize( string1, size1, string2, size2, value, 1 ) )
        {
        }


        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType>&& std::is_same_v<typename SpanT2::value_type, CharType> )
        explicit BasicString( CharType value, size_type count, const SpanT1& span1, const SpanT2& span2 )
            : data_( Initialize( value, count, span1.data( ), span1.size( ), span2.data( ), span2.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType>&& std::is_same_v<typename SpanT2::value_type, CharType> )
        explicit BasicString( const SpanT1& span1, CharType value, size_type count, const SpanT2& span2 )
            : data_( Initialize( span1.data( ), span1.size( ), value, count, span2.data( ), span2.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType>&& std::is_same_v<typename SpanT2::value_type, CharType> )
        explicit BasicString( const SpanT1& span1, const SpanT2& span2, CharType value, size_type count )
            : data_( Initialize( span1.data( ), span1.size( ), span2.data( ), span2.size( ), value, count ) )
        {
        }


        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType>&& std::is_same_v<typename SpanT2::value_type, CharType> )
        explicit BasicString( CharType value, const SpanT1& span1, const SpanT2& span2 )
            : data_( Initialize( value, 1, span1.data( ), span1.size( ), span2.data( ), span2.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType>&& std::is_same_v<typename SpanT2::value_type, CharType> )
        explicit BasicString( const SpanT1& span1, CharType value, const SpanT2& span2 )
            : data_( Initialize( span1.data( ), span1.size( ), value, 1, span2.data( ), span2.size( ) ) )
        {
        }

        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType>&& std::is_same_v<typename SpanT2::value_type, CharType> )
        explicit BasicString( const SpanT1& span1, const SpanT2& span2, CharType value )
            : data_( Initialize( span1.data( ), span1.size( ), span2.data( ), span2.size( ), value, 1 ) )
        {
        }




        template<SimpleSpanLike SpanT1, SimpleSpanLike SpanT2, SimpleSpanLike SpanT3>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType> && std::is_same_v<typename SpanT2::value_type, CharType> && std::is_same_v<typename SpanT3::value_type, CharType> )
        explicit BasicString( const SpanT1& span1, const SpanT2& span2, const SpanT3& span3 )
            : data_( Initialize( span1.data( ), span1.size( ), span2.data( ), span2.size( ), span3.data( ), span3.size( ) ) )
        {
        }


        explicit BasicString( const_iterator first, const_iterator last)
            : data_( Initialize( first.ptr_, first <= last ? static_cast<size_type>( last - first ) : 0 ) )
        {
        }

        explicit BasicString( const_pointer first, const_pointer last )
            : data_( Initialize( first, first <= last ? static_cast< size_type >( last - first ) : 0 ) )
        {
        }

        template<std::input_iterator InputIt>
        explicit BasicString( InputIt first, InputIt last )
            : data_( Initialize( first, last ) )
        {
        }

        explicit BasicString( const BasicStringView<T>& v );


        explicit BasicString( size_type count, CharType value )
            : data_( Initialize( count, value ) )
        {
        }


        BasicString( const BasicString& other ) noexcept
            : data_( other.data_ )
        {
            if ( data_ )
            {
                data_->AddRef( );
            }
        }

        BasicString( BasicString&& other ) noexcept
            : data_( other.data_ )
        {
            other.data_ = nullptr;
        }


        ~BasicString( )
        {
            if ( data_ )
            {
                ReleaseData( data_ );
            }
        }

        [[nodiscard]] bool IsUnique( ) const noexcept
        {
            return data_ ? data_->referenceCount_ == 1 : false;
        }

        [[nodiscard]] BasicString Clone( ) const
        {
            if ( data_ )
            {
                return BasicString( data_->buffer_, data_->size_ );
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


        [[nodiscard]] static BasicString From( const WideString& s )
            requires std::is_same_v<CharType, char>
        {
            return Internal::From( s.data( ), s.Length( ) );
        }
        [[nodiscard]] static BasicString From( const std::wstring& s )
            requires std::is_same_v<CharType, char>
        {
            return Internal::From( s.data( ), s.size( ) );
        }
        [[nodiscard]] static BasicString From( const wchar_t* s )
            requires std::is_same_v<CharType, char>
        {
            return Internal::From( s, Internal::LengthOf( s ) );
        }
        [[nodiscard]] static BasicString From( const char* s )
            requires std::is_same_v<CharType, char>
        {
            return BasicString( s, Internal::LengthOf( s ) );
        }


        [[nodiscard]] static BasicString From( const AnsiString& s )
            requires std::is_same_v<CharType, char>
        {
            return s;
        }
        [[nodiscard]] static BasicString From( const std::string& s )
            requires std::is_same_v<CharType, char>
        {
            return BasicString( s.data( ), s.size( ) );
        }

        [[nodiscard]] static BasicString From( const std::string_view& s )
            requires std::is_same_v<CharType, char>
        {
            return BasicString( s.data( ), s.size( ) );
        }


        [[nodiscard]] static BasicString From( const AnsiString& s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return Internal::From( s.data( ), s.Length( ) );
        }
        [[nodiscard]] static BasicString From( const std::string& s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return Internal::From( s.data( ), s.size( ) );
        }

        [[nodiscard]] static BasicString From( const std::string_view& s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return Internal::From( s.data( ), s.size( ) );
        }


        [[nodiscard]] static BasicString From( const WideString& s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return s;
        }
        [[nodiscard]] static BasicString From( const std::wstring& s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return BasicString( s.data( ), s.size( ) );
        }

        [[nodiscard]] static BasicString From( const std::wstring_view& s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return BasicString( s.data( ), s.size( ) );
        }
        [[nodiscard]] static BasicString From( const std::wstring_view& s )
            requires std::is_same_v<CharType, char>
        {
            return Internal::From( s.data( ), s.size( ) );
        }



        [[nodiscard]] static BasicString From( const wchar_t* s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return BasicString( s, Internal::LengthOf( s ) );
        }
        [[nodiscard]] static BasicString From( const char* s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return Internal::From( s, Internal::LengthOf( s ) );
        }



        BasicString& operator = ( nullptr_t )
        {
            if ( data_ )
            {
                ReleaseData( data_ );
                data_ = nullptr;
            }
            return *this;
        }


        BasicString& operator = ( const BasicString& other )
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

        BasicString& operator = ( BasicString&& other ) noexcept
        {
            std::swap( other.data_, data_ );
            return *this;
        }

        void Assign( const CharType* string )
        {
            if ( data_ )
            {
                auto tmp = Initialize( string );
                ReleaseData( data_ );
                data_ = tmp;
            }
            else
            {
                data_ = Initialize( string );
            }
        }
        void assign( const CharType* string )
        {
            Assign( string );
        }


        BasicString& operator = ( const CharType* string )
        {
            Assign( string );
            return *this;
        }


        void Assign( const CharType* string, size_type size )
        {
            if ( data_ )
            {
                auto tmp = Initialize( string, size );
                ReleaseData( data_ );
                data_ = tmp;
            }
            else
            {
                data_ = Initialize( string, size );
            }
        }
        void assign( const CharType* string, size_type size )
        {
            Assign( string, size );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, CharType>
        void Assign( const SpanT& string )
        {
            Assign( string.data( ), string.size( ) );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, CharType>
        void assign( const SpanT& string )
        {
            Assign( string.data( ), string.size( ) );
        }


        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        BasicString& operator = ( const SpanT& string )
        {
            Assign( string.data(), string.size() );
            return *this;
        }


        [[nodiscard]] constexpr const CharType* c_str( ) const noexcept
        {
            if constexpr ( std::is_same_v<CharType, char> )
            {
                return data_ ? data_->buffer_ : "";
            }
            else
            {
                return data_ ? data_->buffer_ : L"";
            }
        }

        [[nodiscard]] constexpr const CharType* data( ) const noexcept
        {
            return data_ ? data_->buffer_ : nullptr;
        }

        [[nodiscard]] constexpr CharType* data( ) noexcept
        {
            return data_ ? data_->buffer_ : nullptr;
        }

        template<typename T>
            requires std::is_same_v<typename T::value_type, value_type> && std::is_constructible_v<T,const value_type*,size_t> && std::is_constructible_v<T>
        T To( ) const
        {
            if ( data_ && data_->size_ )
            {
                return T( data_->buffer, data_->size_ );
            }
            else
            {
                return T();
            }
        }


        [[nodiscard]] size_t Hash( ) const noexcept
        {
            if ( data_ )
            {
                return XXH3_64bits( data_->buffer_, data_->size_ * sizeof( CharType ) );
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
            return data_ ? &data_->buffer_[data_->size_] : nullptr;
        }

        [[nodiscard]] constexpr const_iterator begin( ) const noexcept
        {
            return data_ ? data_->buffer_ : nullptr;
        }

        [[nodiscard]] constexpr const_iterator end( ) const noexcept
        {
            return data_ ? &data_->buffer_[data_->size_] : nullptr;
        }

        [[nodiscard]] constexpr const_iterator cbegin( ) const noexcept
        {
            return begin();
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



        [[nodiscard]] constexpr const CharType front( ) const
        {
            return *begin( );
        }
        [[nodiscard]] constexpr CharType front( )
        {
            return *begin( );
        }
        [[nodiscard]] constexpr CharType back( ) const
        {
            return *( end( ) - 1 );
        }
        [[nodiscard]] constexpr CharType back( )
        {
            return *( end( ) - 1 );
        }


        [[nodiscard]] constexpr size_type max_size( ) const noexcept
        {
            return ( MaxInt64 / sizeof( CharType ) ) - NonTextBufferByteCount;
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
        { }


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
                        MemCopy( data_->buffer_, tmp->buffer_, copyLength );
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
                            data_->buffer_[newLength] = 0;
                        }
                        else
                        {
                            auto tmp = data_;
                            data_ = Allocate( newLength );
                            auto copyLength = std::min( newLength, tmp->size_ );
                            MemCopy( data_->buffer_, tmp->buffer_, copyLength );
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
            return data_->buffer_[offset];
        }
        [[nodiscard]] const_reference operator[]( size_type offset ) const noexcept
        {
            return data_->buffer_[offset];
        }


        [[nodiscard]] friend BasicString<CharType> operator +( const BasicString<CharType>& first, const BasicString<CharType>& second )
        {
            auto firstSize = first.size( );
            auto* firstData = first.data( );

            auto secondSize = second.size( );
            auto* secondData = second.data( );

            return BasicString( firstData, firstSize, secondData, secondSize );

        }

        [[nodiscard]] friend BasicString<CharType> operator +( const CharType* first, const BasicString<CharType>& second )
        {
            auto firstSize = Internal::LengthOf( first );

            auto secondSize = second.size( );
            auto* secondData = second.data( );

            return BasicString( first, firstSize, secondData, secondSize );
        }

        [[nodiscard]] friend BasicString<CharType> operator +( const BasicString<CharType>& first, const CharType* second )
        {
            auto firstSize = first.size( );
            auto* firstData = first.data( );

            auto secondSize = Internal::LengthOf( second );

            return BasicString( firstData, firstSize, second, secondSize );
        }

        [[nodiscard]] friend BasicString<CharType> operator +( const CharType first, const BasicString<CharType>& second )
        {
            auto secondSize = second.size( );
            auto* secondData = second.data( );

            return BasicString( &first, 1, secondData, secondSize );
        }

        [[nodiscard]] friend BasicString<CharType> operator +( const BasicString<CharType>& first, const CharType second )
        {
            auto firstSize = first.size( );
            auto* firstData = first.data( );

            return BasicString( firstData, firstSize, &second, 1 );
        }






        void Append( const CharType* other )
        {
            auto otherLength = Internal::LengthOf( other );
            auto* dest = Extend( otherLength );
            MemCopy( dest, other, otherLength );
        }
        void append( const CharType* other )
        {
            Append( other );
        }


        void Append( const CharType* other, size_t otherLength )
        {
            auto* dest = Extend( otherLength );
            MemCopy( dest, other, otherLength );
        }

        void append( const CharType* other, size_t otherLength )
        {
            Append( other, otherLength );
        }

        void Append( const CharType* first, const CharType* last )
        {
            if ( first < last )
            {
                Append( first, static_cast< size_type >( last - first ) );
            }
        }
        void append( const CharType* first, const CharType* last )
        {
            Append( first, last );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<CharType, typename SpanT::value_type>
        void Append( const SpanT& other )
        {
            auto otherLength = other.size( );
            auto* dest = Extend( otherLength );
            MemCopy( dest, other.data( ), otherLength );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<CharType, typename SpanT::value_type>
        void append( const SpanT& other )
        {
            Append( other );
        }


        void Append( size_type count, CharType c )
        {
            auto* dest = Extend( count );
            MemSet( dest, c, count );
        }

        void append( size_type count, CharType c )
        {
            Append( count, c );
        }

        void Append( CharType c )
        {
            auto* dest = Extend( 1 );
            *dest = c;
        }

        void append( CharType c )
        {
            Append( c );
        }

        void push_back( CharType c )
        {
            Append( c );
        }

        void pop_back( )
        {
            erase( end( ) - 1 );
        }

        BasicString<CharType>& operator += ( const CharType* other ) { Append( other ); return *this; }
        template<SimpleSpanLike SpanT>
            requires std::is_same_v<CharType, typename SpanT::value_type>
        BasicString<CharType>& operator += ( const SpanT& other ) { Append( other ); return *this; }
        BasicString<CharType>& operator += ( CharType c ) { Append( c ); return *this; }

        iterator Insert( const_iterator pos, CharType ch )
        {
            auto position = pos.ptr_;
            iterator end_ = Extend( 1 );
            if ( position < end_ )
            {
                MemMove( position + 1, position, static_cast< size_t >( end_ - position ) );
            }
            *position = ch;
            return position;
        }

        iterator insert( const_iterator pos, CharType ch )
        {
            return Insert( pos, ch );
        }


        iterator Insert( const_iterator pos, size_type count, CharType ch )
        {
            auto position = pos.ptr_;
            iterator end_ = Extend( count );
            if ( position < end_ )
            {
                MemMove( position + count, position, static_cast< size_t >( end_ - position ) );
            }
            MemSet( position, ch, count );
            return position;
        }

        iterator insert( const_iterator pos, size_type count, CharType ch )
        {
            return Insert( pos, count, ch );
        }


        iterator Insert( size_type index, size_type count, CharType ch )
        {
            const_iterator pos = cbegin( ) + index;
            return insert( pos, count, ch );
        }

        iterator insert( size_type index, size_type count, CharType ch )
        {
            return Insert( index, count, ch );
        }

        iterator Insert( const_iterator pos, const CharType* buffer, size_type bufferLength )
        {
            auto position = pos.ptr_;
            iterator end_ = Extend( bufferLength );
            if ( position < end_ )
            {
                MemMove( position + bufferLength, position, static_cast< size_t >( end_ - position ) );
            }
            MemCopy( position, buffer, bufferLength );
            return position;
        }




    private:
        [[nodiscard]] static bool AreEqual( const Data* first, const Data* second )
        {
            if ( first != second )
            {
                if ( first )
                {
                    if ( second )
                    {
                        if ( first->size_ == second->size_ )
                        {
                            return Internal::Compare( first->buffer_, first->size_, second->buffer_, second->size_ ) == 0;
                        }
                    }
                }
                return false;
            }
            else
            {
                return true;
            }
        }
        [[nodiscard]] static bool AreEqual( const Data* first, const CharType* second )
        {
                if ( first )
                {
                    if ( second )
                    {
                        size_type secondSize = Internal::LengthOf( second );
                        if ( first->size_ == secondSize )
                        {
                            return MemCmp( first->buffer_, second, secondSize ) == 0;
                        }
                    }
                    return false;
                }
                return second && second[0] ? false : true;
        }

        [[nodiscard]] static bool AreEqual( const CharType* first, const Data* second )
        {
            if ( second )
            {
                if ( first )
                {
                    size_type firstSize = Internal::LengthOf( first );
                    if ( second->size_ == firstSize )
                    {
                        return MemCmp( second->buffer_, first, firstSize ) == 0;
                    }
                }
                return false;
            }
            return first && first[0] ? false : true;
        }


        [[nodiscard]] static bool AreEqual( const Data* first, const CharType* second, size_type secondSize )
        {
            if ( first )
            {
                if ( second )
                {
                    if ( first->size_ == secondSize )
                    {
                        return Internal::Compare( first->buffer_, first->size_, second, secondSize ) == 0;
                    }
                }
                return false;
            }
            return second && secondSize ? false : true;
        }

        [[nodiscard]] static bool AreEqual( const CharType* first, size_type firstSize, const Data* second )
        {
            if ( second )
            {
                if ( first )
                {
                    if ( second->size_ == firstSize )
                    {
                        return Internal::Compare( first, firstSize, second->buffer_, second->size_ ) == 0;
                    }
                }
                return false;
            }
            return first && firstSize ? false : true;
        }



        [[nodiscard]] static int Compare( const Data* first, const Data* second )
        {
            if ( first != second )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::Compare( first->buffer_, first->size_, second->buffer_, second->size_ );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
        }

        


        [[nodiscard]] static int ICompare( const Data* first, const Data* second )
        {
            if ( first != second )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::ICompare( first->buffer_, first->size_, second->buffer_, second->size_ );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
        }

        [[nodiscard]] static bool IsNotSame( const CharType* first, const Data* second )
        {
            if ( second )
            {
                return first != second->buffer_;
            }
            else
            {
                return first && first[0] ? true : false;
            }
        }
        [[nodiscard]] static bool IsNotSame( const Data* first, const CharType* second )
        {
            if ( first )
            {
                return first->buffer_ != second;
            }
            else
            {
                return second && second[0] ? true : false;
            }
        }

        [[nodiscard]] static bool IsNotSame( const CharType* first, size_type firstLength, const Data* second )
        {
            if ( second )
            {
                return first != second->buffer_ || firstLength != second->size_;
            }
            else
            {
                return first && firstLength ? true : false;
            }
        }
        [[nodiscard]] static bool IsNotSame( const Data* first, const CharType* second, size_type secondLength )
        {
            if ( first )
            {
                return first->buffer_ != second || first->size_ != secondLength;
            }
            else
            {
                return second && secondLength ? true : false;
            }
        }



        [[nodiscard]] static int Compare( const CharType* first, const Data* second )
        {
            if ( IsNotSame( first, second ) )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::Compare( first, second->buffer_, second->size_ );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
        }

        [[nodiscard]] static int Compare( const CharType* first, size_t firstLength, const Data* second )
        {
            if ( IsNotSame( first, firstLength, second ) )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::Compare( first, firstLength, second->buffer_, second->size_ );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }

            
        }


        [[nodiscard]] static int ICompare( const CharType* first, const Data* second )
        {
            if ( IsNotSame( first, second ) )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::ICompare( first, second->buffer_, second->size_ );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
        }

        [[nodiscard]] static int ICompare( const CharType* first, size_t firstLength, const Data* second )
        {
            if ( IsNotSame( first, firstLength, second ) )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::ICompare( first, firstLength, second->buffer_, second->size_ );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }

            
        }

        [[nodiscard]] static int Compare( const Data* first, const CharType* second )
        {
            if ( IsNotSame( first, second ) )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::Compare( first->buffer_, first->size_, second );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
        }

        [[nodiscard]] static int Compare( const Data* first, const CharType* second, size_t secondLength )
        {
            if ( IsNotSame( first, second, secondLength ) )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::Compare( first->buffer_, first->size_, second, secondLength );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }

            
        }


        [[nodiscard]] static int ICompare( const Data* first, const CharType* second )
        {
            if ( IsNotSame( first, second ) )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::ICompare( first->buffer_, first->size_, second );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
        }

        [[nodiscard]] static int ICompare( const Data* first, const CharType* second, size_t secondLength )
        {
            if ( IsNotSame( first, second, secondLength ) )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::ICompare( first->buffer_, first->size_, second, secondLength );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
            
        }

    public:
        [[nodiscard]] static int Compare( const BasicString& first, const BasicString& second )
        {
            return Compare( first.data_, second.data_ );
        }
        [[nodiscard]] static int Compare( const CharType* first, const BasicString& second )
        {
            return Compare( first, second.data_ );
        }
        [[nodiscard]] static int Compare( const BasicString& first, const CharType* second )
        {
            return Compare( first.data_, second );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] static int Compare( const SpanT& first, const BasicString& second )
        {
            return Compare( first.data(), first.size(), second.data_ );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] static int Compare( const BasicString& first, const SpanT& second )
        {
            return Compare( first.data_, second.data(), second.size() );
        }


        [[nodiscard]] int Compare( const BasicString& second ) const
        {
            return Compare( data_, second.data_ );
        }
        [[nodiscard]] int Compare( const CharType* second ) const
        {
            return Compare( data_, second );
        }


        [[nodiscard]] static int compare( const BasicString& first, const BasicString& second )
        {
            return Compare( first, second );
        }
        [[nodiscard]] static int compare( const CharType* first, const BasicString& second )
        {
            return Compare( first, second );
        }
        [[nodiscard]] static int compare( const BasicString& first, const CharType* second )
        {
            return Compare( first, second );
        }

        [[nodiscard]] int compare( const BasicString& second ) const
        {
            return Compare( second );
        }
        [[nodiscard]] int compare( const CharType* second ) const
        {
            return Compare( second );
        }


        [[nodiscard]] static int ICompare( const BasicString& first, const BasicString& second )
        {
            return ICompare( first.data_, second.data_ );
        }
        [[nodiscard]] static int ICompare( const CharType* first, const BasicString& second )
        {
            return ICompare( first, second.data_ );
        }
        [[nodiscard]] static int ICompare( const BasicString& first, const CharType* second )
        {
            return ICompare( first.data_, second );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] static int ICompare( const SpanT& first, const BasicString& second )
        {
            return ICompare( first.data( ), first.size( ), second.data_ );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] static int ICompare( const BasicString& first, const SpanT& second )
        {
            return ICompare( first.data_, second.data( ), second.size( ) );
        }


        [[nodiscard]] friend bool operator == ( const BasicString& first, const BasicString& second )
        {
            return AreEqual( first.data_, second.data_ );
        }
        [[nodiscard]] friend bool operator == ( const CharType* first, const BasicString& second )
        {
            return AreEqual( first, second.data_ );
        }
        [[nodiscard]] friend bool operator == ( const BasicString& first, const CharType* second )
        {
            return AreEqual( first.data_, second );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] friend bool operator == ( const SpanT& first, const BasicString& second )
        {
            return AreEqual( first.data(), first.size(), second.data_ );
        }
        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] friend bool operator == ( const BasicString& first, const SpanT& second )
        {
            return AreEqual( first.data_, second.data( ), second.size() );
        }

        
        [[nodiscard]] friend bool operator == ( const std::basic_string_view<CharType>& first, const BasicString& second )
        {
            return AreEqual( first.data( ), first.size( ), second.data_ );
        }
        [[nodiscard]] friend bool operator == ( const BasicString& first, const std::basic_string_view<CharType>& second )
        {
            return AreEqual( first.data_, second.data( ), second.size( ) );
        }



        [[nodiscard]] friend bool operator <= ( const BasicString& first, const BasicString& second )
        {
            return Compare( first, second ) <= 0;
        }
        [[nodiscard]] friend bool operator <= ( const CharType* first, const BasicString& second )
        {
            return Compare( first, second ) <= 0;
        }
        [[nodiscard]] friend bool operator <= ( const BasicString& first, const CharType* second )
        {
            return Compare( first, second ) <= 0;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] friend bool operator <= ( const SpanT& first, const BasicString& second )
        {
            return Compare( first.data( ), first.size( ), second.data_ ) <= 0;
        }
        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] friend bool operator <= ( const BasicString& first, const SpanT& second )
        {
            return Compare( first.data_, second.data( ), second.size( ) ) <= 0;
        }

        [[nodiscard]] friend bool operator <= ( const std::basic_string_view<CharType>& first, const BasicString& second )
        {
            return Compare( first.data( ), first.size( ), second.data_ ) <= 0;
        }
        [[nodiscard]] friend bool operator <= ( const BasicString& first, const std::basic_string_view<CharType>& second )
        {
            return Compare( first.data_, second.data( ), second.size( ) ) <= 0;
        }


        [[nodiscard]] friend bool operator >= ( const BasicString& first, const BasicString& second )
        {
            return Compare( first, second ) >= 0;
        }
        [[nodiscard]] friend bool operator >= ( const CharType* first, const BasicString& second )
        {
            return Compare( first, second ) >= 0;
        }
        [[nodiscard]] friend bool operator >= ( const BasicString& first, const CharType* second )
        {
            return Compare( first, second ) >= 0;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] friend bool operator >= ( const SpanT& first, const BasicString& second )
        {
            return Compare( first.data( ), first.size( ), second.data_ ) >= 0;
        }
        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] friend bool operator >= ( const BasicString& first, const SpanT& second )
        {
            return Compare( first.data_, second.data( ), second.size( ) ) >= 0;
        }

        [[nodiscard]] friend bool operator >= ( const std::basic_string_view<CharType>& first, const BasicString& second )
        {
            return Compare( first.data( ), first.size( ), second.data_ ) >= 0;
        }
        [[nodiscard]] friend bool operator >= ( const BasicString& first, const std::basic_string_view<CharType>& second )
        {
            return Compare( first.data_, second.data( ), second.size( ) ) >= 0;
        }


        [[nodiscard]] friend bool operator < ( const BasicString& first, const BasicString& second )
        {
            return Compare( first, second ) < 0;
        }
        [[nodiscard]] friend bool operator < ( const CharType* first, const BasicString& second )
        {
            return Compare( first, second ) < 0;
        }
        [[nodiscard]] friend bool operator < ( const BasicString& first, const CharType* second )
        {
            return Compare( first, second ) < 0;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] friend bool operator < ( const SpanT & first, const BasicString & second )
        {
            return Compare( first.data( ), first.size( ), second.data_ ) < 0;
        }
        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] friend bool operator < ( const BasicString & first, const SpanT & second )
        {
            return Compare( first.data_, second.data( ), second.size( ) ) < 0;
        }

        [[nodiscard]] friend bool operator < ( const std::basic_string_view<CharType>& first, const BasicString& second )
        {
            return Compare( first.data( ), first.size( ), second.data_ ) < 0;
        }
        [[nodiscard]] friend bool operator < ( const BasicString& first, const std::basic_string_view<CharType>& second )
        {
            return Compare( first.data_, second.data( ), second.size( ) ) < 0;
        }



        [[nodiscard]] friend bool operator > ( const BasicString& first, const BasicString& second )
        {
            return Compare( first, second ) > 0;
        }
        [[nodiscard]] friend bool operator > ( const CharType* first, const BasicString& second )
        {
            return Compare( first, second ) > 0;
        }
        [[nodiscard]] friend bool operator > ( const BasicString& first, const CharType* second )
        {
            return Compare( first, second ) > 0;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] friend bool operator > ( const SpanT& first, const BasicString& second )
        {
            return Compare( first.data( ), first.size( ), second.data_ ) > 0;
        }
        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] friend bool operator > ( const BasicString& first, const SpanT& second )
        {
            return Compare( first.data_, second.data( ), second.size( ) ) > 0;
        }

        [[nodiscard]] friend bool operator > ( const std::basic_string_view<CharType>& first, const BasicString& second )
        {
            return Compare( first.data( ), first.size( ), second.data_ ) > 0;
        }
        [[nodiscard]] friend bool operator > ( const BasicString& first, const std::basic_string_view<CharType>& second )
        {
            return Compare( first.data_, second.data( ), second.size( ) ) > 0;
        }


        [[nodiscard]] friend bool operator != ( const BasicString& first, const BasicString& second )
        {
            return AreEqual( first.data_, second.data_ ) == false;
        }
        [[nodiscard]] friend bool operator != ( const CharType* first, const BasicString& second )
        {
            return AreEqual( first, second.data_ ) == false;
        }
        [[nodiscard]] friend bool operator != ( const BasicString& first, const CharType* second )
        {
            return AreEqual( first.data_, second ) == false;
        }


        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] friend bool operator != ( const SpanT& first, const BasicString& second )
        {
            return AreEqual( first.data( ), first.size( ), second.data_ ) == false;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type >, CharType >
        [[nodiscard]] friend bool operator != ( const BasicString& first, const SpanT& second )
        {
            return AreEqual( first.data_, second.data( ), second.size( ) ) == false;
        }

        [[nodiscard]] friend bool operator != ( const std::basic_string_view<CharType>& first, const BasicString& second )
        {
            return AreEqual( first.data( ), first.size( ), second.data_ ) == false;
        }

        [[nodiscard]] friend bool operator != ( const BasicString& first, const std::basic_string_view<CharType>& second )
        {
            return AreEqual( first.data_, second.data( ), second.size( ) ) == false;
        }





        [[nodiscard]] size_type IndexOf( CharType c ) const
        {
            if ( data_ )
            {
                auto* foundAt = MemChr( data_->buffer_, c, data_->size_ );
                return foundAt ? foundAt - data_->buffer_ : npos;
            }
            else
            {
                return npos;
            }
        }

        [[nodiscard]] size_type IIndexOf( CharType c ) const
        {
            if ( data_ )
            {
                auto* foundAt = MemIChr( data_->buffer_, c, data_->size_ );
                return foundAt ? foundAt - data_->buffer_ : npos;
            }
            else
            {
                return npos;
            }
        }



        [[nodiscard]] size_type find_first_of( CharType c ) const
        {
            return IndexOf( c );
        }

        [[nodiscard]] size_type find( CharType c ) const
        {
            return IndexOf( c );
        }

        


        [[nodiscard]] size_type IndexOfAnyOf( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ && searchChars && numberOfSearchChars )
            {
                auto ptr = data_->buffer_ + start;
                auto endPtr = data_->buffer_ + data_->size_;
                if ( numberOfSearchChars == 1 && ptr < endPtr )
                {
                    auto p = MemChr( ptr, *searchChars, data_->size_ - start );
                    if ( p )
                    {
                        return static_cast< size_type >( p - data_->buffer_ );
                    }
                }
                else
                {
                    auto searchEndPtr = searchChars + numberOfSearchChars;

                    while ( ptr < endPtr )
                    {
                        auto searchPtr = searchChars;
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

        [[nodiscard]] size_type find_first_of( const CharType* searchChars, size_type start, size_type numberOfSearchChars ) const
        {
            return IndexOfAnyOf( searchChars, numberOfSearchChars, start );
        }


        [[nodiscard]] size_type IIndexOfAnyOf( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ && searchChars && numberOfSearchChars )
            {
                auto ptr = data_->buffer_ + start;
                auto endPtr = data_->buffer_ + data_->size_;
                if ( numberOfSearchChars == 1 && ptr < endPtr )
                {
                    auto p = MemIChr( ptr, *searchChars, data_->size_ - start );
                    if ( p )
                    {
                        return static_cast< size_type >( p - data_->buffer_ );
                    }
                }
                else
                {
                    auto searchEndPtr = searchChars + numberOfSearchChars;

                    while ( ptr < endPtr )
                    {
                        auto searchPtr = searchChars;
                        auto c = Core::ToUpper( *ptr );
                        while ( searchPtr < searchEndPtr )
                        {
                            auto sc = Core::ToUpper( *searchPtr );
                            if ( c == sc )
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


        [[nodiscard]] size_type IndexOfAnyOf( const BasicString<CharType>& searchChars, size_type start = 0 ) const
        {
            const auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return IndexOfAnyOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>,CharType>
        [[nodiscard]] size_type IndexOfAnyOf( const SpanT& searchChars, size_type start = 0 ) const
        {
            return IndexOfAnyOf( searchChars.data(), searchChars.size(), start );
        }

        [[nodiscard]] size_type IndexOfAnyOf( const std::basic_string_view<CharType>& searchChars, size_type start = 0 ) const
        {
            return IndexOfAnyOf( searchChars.data( ), searchChars.size( ), start );
        }

        [[nodiscard]] size_type IIndexOfAnyOf( const BasicString<CharType>& searchChars, size_type start = 0 ) const
        {
            const auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return IIndexOfAnyOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, CharType>
        [[nodiscard]] size_type IIndexOfAnyOf( const SpanT& searchChars, size_type start = 0 ) const
        {
            return IIndexOfAnyOf( searchChars.data( ), searchChars.size( ), start );
        }

        [[nodiscard]] size_type IIndexOfAnyOf( const std::basic_string_view<CharType>& searchChars, size_type start = 0 ) const
        {
            return IIndexOfAnyOf( searchChars.data( ), searchChars.size( ), start );
        }


        [[nodiscard]] size_type IndexOfAnyOf( const CharType* searchChars, size_type start = 0 ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            if ( length )
            {
                return IndexOfAnyOf( searchChars, length, start );
            }
            return npos;
        }

        [[nodiscard]] size_type find_first_of( const CharType* searchChars, size_type start = 0 ) const
        {
            return IndexOfAnyOf( searchChars, start );
        }

        [[nodiscard]] size_type IIndexOfAnyOf( const CharType* searchChars, size_type start = 0 ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            if ( length )
            {
                return IIndexOfAnyOf( searchChars, length, start );
            }
            return npos;
        }
    private:
        static bool Contains( const CharType* buffer, size_type bufferLength, CharType value )
        {
            return MemChr( buffer, value, bufferLength ) != nullptr;
        }
        static bool IContains( const CharType* buffer, size_type bufferLength, CharType value )
        {
            return MemIChr( buffer, value, bufferLength ) != nullptr;
        }
    public:

        [[nodiscard]] size_type IndexOfAnyBut( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ && start < data_->size_ )
            {
                if ( searchChars && numberOfSearchChars )
                {
                    auto ptr = data_->buffer_ + start;
                    auto endPtr = data_->buffer_ + data_->size_;
                    while ( ptr < endPtr )
                    {
                        if ( Contains( searchChars, numberOfSearchChars, *ptr ) == false )
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

        [[nodiscard]] size_type IIndexOfAnyBut( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ && start < data_->size_ )
            {
                if ( searchChars && numberOfSearchChars )
                {
                    auto ptr = data_->buffer_ + start;
                    auto endPtr = data_->buffer_ + data_->size_;
                    while ( ptr < endPtr )
                    {
                        if ( IContains( searchChars, numberOfSearchChars, *ptr ) == false )
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


        [[nodiscard]] size_type find_first_not_of( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            return IndexOfAnyBut( searchChars, numberOfSearchChars, start );
        }

        [[nodiscard]] size_type IndexOfAnyBut( const CharType searchChar, size_type start = 0 ) const
        {
            return IndexOfAnyBut( &searchChar, 1, start );
        }

        [[nodiscard]] size_type find_first_not_of( const CharType searchChar, size_type start = 0 ) const
        {
            return IndexOfAnyBut( searchChar, start );
        }



        [[nodiscard]] size_type IndexOfAnyBut( const BasicString& searchChars, size_type start = 0 ) const
        {
            auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return IndexOfAnyBut( searchData->buffer_, searchData->size_, start );
            }
            return start;
        }

        [[nodiscard]] size_type find_first_not_of( const BasicString& searchChars, size_type start = 0 ) const
        {
            return IndexOfAnyBut( searchChars, start );
        }

        [[nodiscard]] size_type IIndexOfAnyBut( const BasicString& searchChars, size_type start = 0 ) const
        {
            auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return IIndexOfAnyBut( searchData->buffer_, searchData->size_, start );
            }
            return start;
        }

        [[nodiscard]] size_type IndexOfAnyBut( const CharType* searchChars, size_type start = 0 ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            return IndexOfAnyBut( searchChars, length, start );
        }

        [[nodiscard]] size_type find_first_not_of( const CharType* searchChars, size_type start = 0 ) const
        {
            return IndexOfAnyBut( searchChars, start );
        }

        [[nodiscard]] size_type IIndexOfAnyBut( const CharType* searchChars, size_type start = 0 ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            return IIndexOfAnyBut( searchChars, length, start );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>,CharType>
        [[nodiscard]] size_type IndexOfAnyBut( const SpanT& searchChars, size_type start = 0 ) const
        {
            return IndexOfAnyBut( searchChars.data(), searchChars.size(), start );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, CharType>
        [[nodiscard]] size_type IIndexOfAnyBut( const SpanT& searchChars, size_type start = 0 ) const
        {
            return IIndexOfAnyBut( searchChars.data( ), searchChars.size( ), start );
        }

        [[nodiscard]] size_type IndexOfAnyBut( const std::basic_string_view<CharType>& searchChars, size_type start = 0 ) const
        {
            return IndexOfAnyBut( searchChars.data( ), searchChars.size( ), start );
        }
        [[nodiscard]] size_type IIndexOfAnyBut( const std::basic_string_view<CharType>& searchChars, size_type start = 0 ) const
        {
            return IIndexOfAnyBut( searchChars.data( ), searchChars.size( ), start );
        }


        [[nodiscard]] size_type LastIndexOfAnyOf( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ && searchChars && numberOfSearchChars )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }
                do
                {
                    const auto* p = MemChr( searchChars, data_->buffer_[start], static_cast<size_t>( numberOfSearchChars ) );
                    if ( p )
                    {
                        return start;
                    }
                } while ( start-- );
            }
            return npos;
        }

        [[nodiscard]] size_type find_last_of( const CharType* searchChars, size_type start, size_type numberOfSearchChars ) const
        {
            return LastIndexOfAnyOf( searchChars, numberOfSearchChars, start);
        }


        [[nodiscard]] size_type ILastIndexOfAnyOf( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ && searchChars && numberOfSearchChars )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }
                do
                {
                    auto c = Core::ToUpper( data_->buffer_[start] );
                    for ( size_t i = 0; i < numberOfSearchChars; i++ )
                    {
                        auto sc = Core::ToUpper( searchChars[i] );
                        if ( c == sc )
                        {
                            return start;
                        }
                    }
                } while ( start-- );
            }
            return npos;
        }


        [[nodiscard]] size_type LastIndexOfAnyOf( const BasicString& searchChars, size_type start = npos ) const
        {
            auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return LastIndexOfAnyOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        [[nodiscard]] size_type find_last_of( const BasicString& searchChars, size_type start = npos ) const
        {
            return LastIndexOfAnyOf( searchChars, start );
        }


        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, CharType>
        [[nodiscard]] size_type LastIndexOfAnyOf( const SpanT& searchChars, size_type start = npos ) const
        {
            return LastIndexOfAnyOf( searchChars.data(), searchChars.size(), start );
        }

        [[nodiscard]] size_type LastIndexOfAnyOf( const std::basic_string_view<CharType>& searchChars, size_type start = npos ) const
        {
            return LastIndexOfAnyOf( searchChars.data( ), searchChars.size( ), start );
        }


        [[nodiscard]] size_type ILastIndexOfAnyOf( const BasicString& searchChars, size_type start = npos ) const
        {
            auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return ILastIndexOfAnyOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, CharType>
        [[nodiscard]] size_type ILastIndexOfAnyOf( const SpanT& searchChars, size_type start = npos ) const
        {
            return ILastIndexOfAnyOf( searchChars.data( ), searchChars.size( ), start );
        }

        [[nodiscard]] size_type ILastIndexOfAnyOf( const std::basic_string_view<CharType>& searchChars, size_type start = npos ) const
        {
            return ILastIndexOfAnyOf( searchChars.data( ), searchChars.size( ), start );
        }


        [[nodiscard]] size_type LastIndexOfAnyOf( const CharType* searchChars, size_type start = npos ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            if ( length )
            {
                return LastIndexOfAnyOf( searchChars, length, start );
            }
            return npos;
        }

        [[nodiscard]] size_type find_last_of( const CharType* searchChars, size_type start = npos ) const
        {
            return LastIndexOfAnyOf( searchChars, start );
        }


        [[nodiscard]] size_type ILastIndexOfAnyOf( const CharType* searchChars, size_type start = npos ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            if ( length )
            {
                return ILastIndexOfAnyOf( searchChars, length, start );
            }
            return npos;
        }


        [[nodiscard]] size_type LastIndexOfAnyBut( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }
                do
                {
                    const auto* p = MemChr( searchChars, data_->buffer_[start], static_cast<size_t>( numberOfSearchChars ) );
                    if ( !p )
                    {
                        return start;
                    }
                } while ( start-- );
            }
            return npos;
        }

        [[nodiscard]] size_type ILastIndexOfAnyBut( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }
                do
                {
                    auto c = Core::ToUpper( data_->buffer_[start] );
                    size_t i = 0;
                    for ( ; i < numberOfSearchChars; i++ )
                    {
                        auto sc = Core::ToUpper( searchChars[i] );
                        if ( c == sc )
                        {
                            break;
                        }
                    }
                    if ( i == numberOfSearchChars )
                    {
                        return start;
                    }
                } while ( start-- );
            }
            return npos;
        }




        [[nodiscard]] size_type LastIndexOfAnyBut( const BasicString& searchChars, size_type start = npos ) const
        {
            auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return LastIndexOfAnyBut( searchData->buffer_, searchData->size_, start );
            }
            return data_ ? data_->size_ - 1 : npos;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, CharType>
        [[nodiscard]] size_type LastIndexOfAnyBut( const SpanT& searchChars, size_type start = npos ) const
        {
            return LastIndexOfAnyBut( searchChars.data( ), searchChars.size( ), start );
        }

        [[nodiscard]] size_type LastIndexOfAnyBut( const std::basic_string_view<CharType>& searchChars, size_type start = npos ) const
        {
            return LastIndexOfAnyBut( searchChars.data( ), searchChars.size( ), start );
        }



        [[nodiscard]] size_type ILastIndexOfAnyBut( const BasicString& searchChars, size_type start = npos ) const
        {
            auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return ILastIndexOfAnyBut( searchData->buffer_, searchData->size_, start );
            }
            return data_ ? data_->size_ - 1 : npos;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, CharType>
        [[nodiscard]] size_type ILastIndexOfAnyBut( const SpanT& searchChars, size_type start = npos ) const
        {
            return ILastIndexOfAnyBut( searchChars.data( ), searchChars.size( ), start );
        }

        [[nodiscard]] size_type ILastIndexOfAnyBut( const std::basic_string_view<CharType>& searchChars, size_type start = npos ) const
        {
            return ILastIndexOfAnyBut( searchChars.data( ), searchChars.size( ), start );
        }



        [[nodiscard]] size_type LastIndexOfAnyBut( const CharType* searchChars, size_type start = npos ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            if ( length )
            {
                return LastIndexOfAnyBut( searchChars, length, start );
            }
            return data_ ? data_->size_ - 1 : npos;
        }

        [[nodiscard]] size_type ILastIndexOfAnyBut( const CharType* searchChars, size_type start = npos ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            if ( length )
            {
                return ILastIndexOfAnyBut( searchChars, length, start );
            }
            return data_ ? data_->size_ - 1 : npos;
        }


        [[nodiscard]] size_type IndexOf( const CharType* searchString, size_type searchStringLength, size_type start ) const
        {
            if ( data_ )
            {
                auto dataSize = data_->size_;
                if ( ( start + searchStringLength ) <= dataSize )
                {
                    auto ptr = data_->buffer_ + start;
                    auto endPtr = data_->buffer_ + dataSize - searchStringLength;

                    while ( ptr <= endPtr )
                    {
                        auto* p = MemChr( ptr, *searchString, static_cast< size_type >( endPtr - ptr ) + searchStringLength );
                        if ( p && p <= endPtr )
                        {
                            auto compareLength = searchStringLength - 1;
                            if ( Internal::Compare( p + 1, compareLength, searchString + 1, compareLength ) == 0 )
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

        [[nodiscard]] size_type find( const CharType* searchString, size_type start, size_type searchStringLength ) const
        {
            return IndexOf( searchString, searchStringLength, start );
        }


        [[nodiscard]] size_type IIndexOf( const CharType* searchString, size_type searchStringLength, size_type start ) const
        {
            if ( data_ )
            {
                auto dataSize = data_->size_;
                if ( ( start + searchStringLength ) <= dataSize )
                {
                    auto ptr = data_->buffer_ + start;
                    auto endPtr = data_->buffer_ + dataSize - searchStringLength;

                    while ( ptr <= endPtr )
                    {
                        auto* p = MemIChr( ptr, *searchString, static_cast< size_type >( endPtr - ptr ) + searchStringLength );
                        if ( p && p <= endPtr )
                        {
                            auto compareLength = searchStringLength - 1;
                            if ( Internal::ICompare( p + 1, compareLength, searchString + 1, compareLength ) == 0 )
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


        [[nodiscard]] size_type IndexOf( const BasicString& searchString, size_type start = 0 ) const
        {
            auto* searchData = searchString.data_;
            if ( searchData )
            {
                return IndexOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        [[nodiscard]] size_type find( const BasicString& searchString, size_type start = 0 ) const
        {
            return IndexOf( searchString, start );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type>,CharType>
        [[nodiscard]] size_type IndexOf( const SpanT& searchString, size_type start = 0 ) const
        {
            if ( searchString.size() )
            {
                return IndexOf( searchString.data(), searchString.size( ), start );
            }
            return npos;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type>, CharType>
        [[nodiscard]] size_type find( const SpanT& searchString, size_type start = 0 ) const
        {
            return IndexOf( searchString, start );
        }

        [[nodiscard]] size_type IndexOf( const std::basic_string_view<CharType>& searchString, size_type start = 0 ) const
        {
            if ( searchString.size( ) )
            {
                return IndexOf( searchString.data( ), searchString.size( ), start );
            }
            return npos;
        }
        [[nodiscard]] size_type find( const std::basic_string_view<CharType>& searchString, size_type start = 0 ) const
        {
            return IndexOf( searchString, start );
        }


        [[nodiscard]] size_type IIndexOf( const BasicString& searchString, size_type start = 0 ) const
        {
            auto* searchData = searchString.data_;
            if ( searchData )
            {
                return IIndexOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type>, CharType>
        [[nodiscard]] size_type IIndexOf( const SpanT& searchString, size_type start = 0 ) const
        {
            if ( searchString.size( ) )
            {
                return IIndexOf( searchString.data( ), searchString.size( ), start );
            }
            return npos;
        }

        [[nodiscard]] size_type IIndexOf( const std::basic_string_view<CharType>& searchString, size_type start = 0 ) const
        {
            if ( searchString.size( ) )
            {
                return IIndexOf( searchString.data( ), searchString.size( ), start );
            }
            return npos;
        }


        [[nodiscard]] size_type IndexOf( const CharType* searchString, size_type start = 0 ) const
        {
            if ( searchString && searchString[0] && data_ && start < data_->size_ )
            {
                const CharType* pStart = &data_->buffer_[start];
                const CharType* pEnd = &data_->buffer_[data_->size_];
                while ( pStart < pEnd )
                {
                    auto* p = MemChr( pStart, *searchString, pEnd - pStart );
                    if ( p )
                    {
                        const CharType* pSearchChar = searchString + 1;
                        const CharType* pContent = p + 1;
                        while ( *pSearchChar )
                        {
                            if ( *pContent != *pSearchChar )
                            {
                                break;
                            }
                            pContent++;
                            pSearchChar++;
                        }
                        if ( !( *pSearchChar ) )
                        {
                            return p - data_->buffer_;
                        }
                        pStart = p + 1;
                    }
                    else
                    {
                        return npos;
                    }
                }
            }
            return npos;
        }

        [[nodiscard]] size_type find( const CharType* searchString, size_type start = 0 ) const
        {
            return IndexOf( searchString, start );
        }


        [[nodiscard]] size_type IIndexOf( const CharType* searchString, size_type start = 0 ) const
        {
            if ( searchString && searchString[0] && data_ && start < data_->size_ )
            {
                const CharType* pStart = &data_->buffer_[start];
                const CharType* pEnd = &data_->buffer_[data_->size_];
                while ( pStart < pEnd )
                {
                    auto* p = MemIChr( pStart, *searchString, pEnd - pStart );
                    if ( p )
                    {
                        const CharType* pSearchChar = searchString + 1;
                        const CharType* pContent = p + 1;
                        while ( *pSearchChar )
                        {
                            if ( toupper( *pContent ) != toupper( *pSearchChar ) )
                            {
                                break;
                            }
                            pContent++;
                            pSearchChar++;
                        }
                        if ( !( *pSearchChar ) )
                        {
                            return p - data_->buffer_;
                        }
                        pStart = p + 1;
                    }
                    else
                    {
                        return npos;
                    }
                }
            }
            return npos;
        }


        [[nodiscard]] size_type IndexOf( CharType c, size_type start ) const
        {
            if ( data_ && start < data_->size_ )
            {
                auto* foundAt = MemChr( data_->buffer_ + start, c, data_->size_ - start );
                return foundAt ? foundAt - data_->buffer_ : npos;
            }
            else
            {
                return npos;
            }
        }

        [[nodiscard]] size_type find( CharType c, size_type start ) const
        {
            return IndexOf( c, start );
        }


        [[nodiscard]] size_type IIndexOf( CharType c, size_type start ) const
        {
            if ( data_ && start < data_->size_ )
            {
                auto* foundAt = MemIChr( data_->buffer_ + start, c, data_->size_ - start );
                return foundAt ? foundAt - data_->buffer_ : npos;
            }
            else
            {
                return npos;
            }
        }


        [[nodiscard]] size_type find_first_of( CharType c, size_type start ) const
        {
            return IndexOf( c, start );
        }


        [[nodiscard]] size_type IndexOf( bool( *test )( CharType ), size_type start = 0 ) const
        {
            if ( data_ )
            {
                while ( start < data_->size_ )
                {
                    auto c = data_->buffer_[start];
                    if ( test( c ) )
                    {
                        return start;
                    }
                    start++;
                }
            }
            return npos;
        }

        [[nodiscard]] size_type IndexOf( bool( *test )( const CharType*, size_type length ), size_type start = 0 ) const
        {
            if ( data_ && start < data_->size_ )
            {
                CharType* pStart = &data_->buffer_[start];
                size_type remainingLength = data_->size_ - start;
                while ( remainingLength )
                {
                    if ( test( pStart, remainingLength ) )
                    {
                        return start;
                    }
                    remainingLength--;
                    pStart++;
                }
            }
            return npos;
        }

        [[nodiscard]] size_type IndexOf( bool( *test )( const CharType*, const CharType* ), size_type start = 0 ) const
        {
            if ( data_ && start < data_->size_ )
            {
                const CharType* pStart = &data_->buffer_[start];
                const CharType* pEnd = end( );
                while ( pStart < pEnd )
                {
                    if ( test( pStart, pEnd ) )
                    {
                        return start;
                    }
                    pStart++;
                }
            }
            return npos;
        }




        [[nodiscard]] size_type LastIndexOf( const CharType* searchString, size_type searchStringLength, size_type start ) const
        {
            if ( data_ && ( searchStringLength <= data_->size_ ) )
            {
                if ( start > ( data_->size_ - searchStringLength ) )
                {
                    start = data_->size_ - searchStringLength;
                }

                if ( searchStringLength == 1 )
                {
                    do
                    {
                        if ( data_->buffer_[start] == *searchString )
                        {
                            return start;
                        }
                    } while ( start-- );
                }
                else if ( searchStringLength )
                {
                    do
                    {
                        if ( Internal::Compare( &data_->buffer_[start], searchStringLength, searchString, searchStringLength ) == 0 )
                        {
                            return start;
                        }
                    } while ( start-- );
                }
            }
            return npos;
        }


        [[nodiscard]] size_type ILastIndexOf( const CharType* searchString, size_type searchStringLength, size_type start ) const
        {
            if ( data_ && ( searchStringLength <= data_->size_ ) )
            {
                if ( start > ( data_->size_ - searchStringLength ) )
                {
                    start = data_->size_ - searchStringLength;
                }

                if ( searchStringLength == 1 )
                {
                    auto c = Core::ToUpper( *searchString );
                    do
                    {
                        if ( Core::ToUpper( data_->buffer_[start] ) == c )
                        {
                            return start;
                        }
                    } while ( start-- );
                }
                else if ( searchStringLength )
                {
                    do
                    {
                        if ( Internal::ICompare( &data_->buffer_[start], searchStringLength, searchString, static_cast<size_t>( searchStringLength ) ) == 0 )
                        {
                            return start;
                        }
                    } while ( start-- );
                }
            }
            return npos;
        }

        [[nodiscard]] size_type LastIndexOf( const BasicString& searchString, size_type start = npos ) const
        {
            auto* searchData = searchString.data_;
            if ( searchData )
            {
                return LastIndexOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type> ,CharType>
        [[nodiscard]] size_type LastIndexOf( const SpanT& searchString, size_type start = npos ) const
        {
            return LastIndexOf( searchString.data(), searchString.size(), start );
        }

        [[nodiscard]] size_type LastIndexOf( const std::basic_string_view<CharType>& searchString, size_type start = npos ) const
        {
            return LastIndexOf( searchString.data( ), searchString.size( ), start );
        }


        [[nodiscard]] size_type ILastIndexOf( const BasicString& searchString, size_type start = npos ) const
        {
            auto* searchData = searchString.data_;
            if ( searchData )
            {
                return ILastIndexOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v< std::remove_cvref_t<typename SpanT::value_type>, CharType>
        [[nodiscard]] size_type ILastIndexOf( const SpanT& searchString, size_type start = npos ) const
        {
            return ILastIndexOf( searchString.data( ), searchString.size( ), start );
        }

        [[nodiscard]] size_type ILastIndexOf( const std::basic_string_view<CharType>& searchString, size_type start = npos ) const
        {
            return ILastIndexOf( searchString.data( ), searchString.size( ), start );
        }


        [[nodiscard]] size_type LastIndexOf( const CharType* searchString, size_type start = npos ) const
        {
            size_type length = Internal::LengthOf( searchString );
            if ( length )
            {

                return LastIndexOf( searchString, length, start );
            }
            return npos;
        }

        [[nodiscard]] size_type ILastIndexOf( const CharType* searchString, size_type start = npos ) const
        {
            size_type length = Internal::LengthOf( searchString );
            if ( length )
            {

                return ILastIndexOf( searchString, length, start );
            }
            return npos;
        }

        [[nodiscard]] size_type LastIndexOf( CharType c, size_type start = npos ) const
        {
            if ( data_ )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }

                do
                {
                    if ( data_->buffer_[start] == c )
                    {
                        return start;
                    }
                } while ( start-- );
            }
            return npos;
        }

        [[nodiscard]] size_type ILastIndexOf( CharType c, size_type start = npos ) const
        {
            c = Core::ToUpper( c );
            if ( data_ )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }

                do
                {
                    if ( Core::ToUpper( data_->buffer_[start] ) == c )
                    {
                        return start;
                    }
                } while ( start-- );
            }
            return npos;
        }


        [[nodiscard]] size_type LastIndexOf( bool( *test )( CharType ), size_type start = npos ) const
        {
            if ( data_ )
            {
                if ( start >= ( data_->size_ ) )
                {
                    start = data_->size_ - 1;
                }

                do
                {
                    CharType c = data_->buffer_[start];
                    if ( test( c ) )
                    {
                        return start;
                    }
                } while ( start-- );

            }
            return npos;
        }


        [[nodiscard]] size_type LastIndexOf( bool( *test )( const CharType*, size_type length ), size_type start = npos ) const
        {
            if ( ( data_ ) && ( start < data_->size_ ) )
            {
                if ( start >= ( data_->size_ ) )
                {
                    start = data_->size_ - 1;
                }

                const CharType* pStart = &data_->buffer_[start];
                size_type remainingLength = data_->size_ - start;

                do
                {
                    if ( test( pStart, remainingLength ) )
                    {
                        return start;
                    }
                    remainingLength++;
                } while ( data_ != pStart-- );
            }
            return npos;
        }


        [[nodiscard]] size_type LastIndexOf( bool( *test )( const CharType*, const CharType* ), size_type start = npos ) const
        {
            if ( ( data_ ) && ( start < data_->size_ ) )
            {
                if ( start >= ( data_->size_ ) )
                {
                    start = data_->size_ - 1;
                }

                const CharType* pStart = &data_->buffer_[start];
                const CharType* pEnd = end( );
                do
                {
                    if ( test( pStart, pEnd ) )
                    {
                        return start;
                    }
                } while ( data_ != pStart-- );
            }
            return npos;
        }

        [[nodiscard]] bool IsSpace( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsSpace( data_->buffer_[position] ) != 0;
            }
            return false;
        }

        [[nodiscard]] bool IsControl( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsControl( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        [[nodiscard]] bool IsDigit( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsDigit( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        [[nodiscard]] bool IsLetter( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsLetter( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        [[nodiscard]] bool IsLetterOrDigit( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsLetterOrDigit( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        [[nodiscard]] bool IsLower( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsLower( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        [[nodiscard]] bool IsUpper( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsUpper( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        [[nodiscard]] bool IsPunctuation( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsPunctuation( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        [[nodiscard]] bool IsWhiteSpace( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsWhiteSpace( data_->buffer_[position] ) != 0;
            }
            return false;
        }

        [[nodiscard]] bool IsEmptyOrWhiteSpace( ) const
        {
            if ( data_ )
            {
                for ( size_t i = 0; i < data_->size_; ++i )
                {
                    if ( Internal::IsWhiteSpace( data_->buffer_[ i ] ) == 0 )
                    {
                        return false;
                    }
                }
            }
            return true;
        }



        [[nodiscard]] bool StartsWith( const CharType ch ) const
        {
            if ( data_ )
            {
                auto size = data_->size_;
                if ( size )
                {
                    return data_->buffer_[ 0 ] == ch;
                }
            }
            return false;
        }
        [[nodiscard]] bool starts_with( const CharType ch ) const
        {
            return StartsWith( ch );
        }


        [[nodiscard]] bool StartsWith( const CharType* str ) const
        {
            if ( data_ && data_->buffer_[0] && str && str[0] )
            {
                const CharType* p = data_->buffer_;
                while ( *p && *str )
                {
                    if ( *p != *str )
                    {
                        break;
                    }
                    p++;
                    str++;
                }
                return *str == L'\x00';
            }
            return false;
        }
        [[nodiscard]] bool starts_with( const CharType* str ) const
        {
            return StartsWith( str );
        }


        [[nodiscard]] bool StartsWith( const BasicString& str ) const
        {
            if ( str.data_ )
            {
                return StartsWith( str.data_->buffer_ );
            }
            else
            {
                return false;
            }
        }

        [[nodiscard]] bool starts_with( const BasicString& str ) const
        {
            return StartsWith( str );
        }


        [[nodiscard]] bool IStartsWith( const CharType* str ) const
        {
            if ( data_ && data_->buffer_[0] && str && str[0] )
            {
                const CharType* p = data_->buffer_;
                while ( *p && *str )
                {
                    if ( Core::ToUpper( *p ) != Core::ToUpper( *str ) )
                    {
                        break;
                    }
                    p++;
                    str++;
                }
                return *str == L'\x00';
            }
            return false;
        }

        [[nodiscard]] bool IStartsWith( const BasicString& str ) const
        {
            if ( str.data_ )
            {
                return IStartsWith( str.data_->buffer_ );
            }
            else
            {
                return false;
            }
        }

        [[nodiscard]] bool EndsWith( const CharType ch ) const
        {
            if ( data_  )
            {
                auto size = data_->size_;
                if ( size )
                {
                    return data_->buffer_[ size - 1 ] == ch;
                }
            }
            return false;
        }

        [[nodiscard]] bool ends_with( const CharType ch ) const
        {
            return EndsWith( ch );
        }

        [[nodiscard]] bool EndsWith( const CharType* str ) const
        {
            if ( data_ && data_->size_ && str && str[0] )
            {
                auto otherLength = Internal::LengthOf( str );
                if ( otherLength <= data_->size_ )
                {
                    return Internal::Compare( &data_->buffer_[data_->size_ - otherLength], otherLength, str, otherLength ) == 0;
                }
            }
            return false;
        }

        [[nodiscard]] bool ends_with( const CharType* str ) const
        {
            return EndsWith( str );
        }

        [[nodiscard]] bool EndsWith( const BasicString& str ) const
        {
            auto* other = str.data_;
            if ( data_ && data_->size_ && other && other->size_ )
            {
                if ( other->size_ <= data_->size_ )
                {
                    return Internal::Compare( &data_->buffer_[data_->size_ - other->size_], other->size_, other->buffer_, other->size_ ) == 0;
                }
            }
            return false;
        }

        [[nodiscard]] bool ends_with( const BasicString& str ) const
        {
            return EndsWith( str );
        }

        [[nodiscard]] bool IEndsWith( const CharType* str ) const
        {
            if ( data_ && data_->size_ && str && str[0] )
            {
                auto otherLength = Internal::LengthOf( str );
                if ( otherLength <= data_->size_ )
                {
                    return Internal::ICompare( &data_->buffer_[data_->size_ - otherLength], otherLength, str, otherLength ) == 0;
                }
            }
            return false;
        }
        [[nodiscard]] bool IEndsWith( const BasicString& str ) const
        {
            auto* other = str.data_;
            if ( data_ && data_->size_ && other && other->size_ )
            {
                if ( other->size_ <= data_->size_ )
                {
                    return Internal::ICompare( &data_->buffer_[data_->size_ - other->size_], other->size_, other->buffer_, other->size_ ) == 0;
                }
            }
            return false;
        }

        [[nodiscard]] size_type Count( CharType what, size_type start = 0 ) const
        {
            size_type result = 0;
            if ( data_ )
            {
                while ( start < data_->size_ )
                {
                    auto index = IndexOf( what, start );
                    if ( index != npos )
                    {
                        result++;
                        start = index + 1;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            return result;
        }

        [[nodiscard]] size_type Count( const CharType* what, size_type whatLength, size_type start = 0 ) const
        {
            size_type result = 0;
            if ( data_ && what && whatLength )
            {
                while ( start < data_->size_ )
                {
                    auto index = IndexOf( what, whatLength, start );
                    if ( index != npos )
                    {
                        result++;
                        start = index + whatLength;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            return result;
        }

        [[nodiscard]] size_type Count( const BasicString& what, size_type start = 0 ) const
        {
            if ( what.data_ )
            {
                return Count( what.data_->buffer_, what.data_->size_, start );
            }
            return 0;
        }

        [[nodiscard]] size_type Count( const std::basic_string_view<CharType>& what, size_type start = 0 ) const
        {
            if ( what.size() )
            {
                return Count( what.data(), what.size( ), start );
            }
            return 0;
        }

        template<typename T >
            requires std::is_convertible_v<size_type, typename T::value_type>
        [[nodiscard]] bool Locate( CharType what, size_type start, T& container)
        {
            container.clear( );
            if ( data_ )
            {
                while ( start < data_->size_ )
                {
                    auto index = IndexOf( what, start );
                    if ( index != npos )
                    {
                        container.push_back( index );
                        start = index + 1;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            return container.size( ) > 0;
        }

        template<typename T >
            requires std::is_convertible_v<size_type, typename T::value_type>
        [[nodiscard]] bool Locate( const CharType* what, size_type whatLength, size_type start, T& container )
        {
            container.clear( );
            if ( data_ )
            {
                while ( start < data_->size_ )
                {
                    auto index = IndexOf( what, whatLength, start );
                    if ( index != npos )
                    {
                        container.push_back( index );
                        start = index + whatLength;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            return container.size( ) > 0;
        }



        [[nodiscard]] BasicString SubString( size_type start, size_type length = npos ) const
        {
            if ( data_ && ( start < data_->size_ ) )
            {
                if ( length > ( data_->size_ - start ) )
                {
                    length = data_->size_ - start;
                }
                if ( ( start == 0 ) && ( length == data_->size_ ) )
                {
                    return BasicString( data_ );
                }
                else
                {
                    return BasicString( data_->buffer_ + start, length );
                }
            }
            else
            {
                return BasicString( );
            }
        }

        [[nodiscard]] BasicString substr( size_type start, size_type length = npos ) const
        {
            return SubString( start, length );
        }


        template<typename VectorT = std::vector<std::basic_string_view<CharType>>>
        [[nodiscard]] VectorT Split( const CharType* delimiters, size_type delimitersLength, size_type start ) const
        {
            using DestT = typename VectorT::value_type;
            VectorT result;
            if ( data_ && ( start < data_->size_ ) )
            {
                auto startPtr = data_->buffer_ + start;
                auto endPtr = startPtr + data_->size_;
                auto ptr = startPtr;
                while ( ptr < endPtr )
                {
                    if ( Contains( delimiters, delimitersLength, *ptr ) )
                    {
                        size_type length = ptr - startPtr;
                        result.emplace_back( DestT( startPtr, length ) );
                        startPtr = ptr + 1;
                    }
                    ptr++;
                }
                if ( startPtr < endPtr )
                {
                    size_type length = endPtr - startPtr;
                    result.emplace_back( DestT( startPtr, length ) );
                }
            }
            return result;
        }

        template<typename VectorT = std::vector<std::basic_string_view<CharType>>, SimpleSpanLike SpanT>
            requires std::is_same_v<CharType,std::remove_cvref_t<typename SpanT::value_type>>
        [[nodiscard]] VectorT Split( const SpanT& delimiterSpan, size_type start = 0 ) const
        {
            return Split<VectorT>( delimiterSpan.data(), delimiterSpan.size(), start );
        }

        template<typename VectorT = std::vector<std::basic_string_view<CharType>>>
        [[nodiscard]] VectorT Split( const CharType* delimiters, size_type start = 0 ) const
        {
            size_type delimitersLength = LengthOf( delimiters );
            return Split<VectorT>( delimiters, delimitersLength, start );
        }

        template<bool ignoreWhiteSpace = true, typename VectorT>
        void Split( CharType separator, VectorT& result ) const
        {
            if ( data_ )
            {
                Internal::Split<CharType, ignoreWhiteSpace, VectorT>( data_->buffer_, data_->size_, separator, result );
            }
            else
            {
                using DestinationT = typename VectorT::value_type;
                result.clear( );
                result.push_back( DestinationT() );
            }
        }

        template<SimpleSpanLike VectorT, bool ignoreWhiteSpace = true>
        VectorT Split( CharType separator ) const
        {
            VectorT result;
            Split( separator, result );
            return result;
        }

        BasicString& UpperCase( )
        {
            if ( data_ )
            {
                if ( data_->referenceCount_ > 1 )
                {
                    auto newData = Allocate( data_->size_ );
                    MemCopy( newData->buffer_, data_->buffer_, data_->size_ );
                    ReleaseData( data_ );
                    data_ = newData;
                }
                Core::ToUpper( data_->buffer_, data_->size_ );
            }
            return *this;
        }

        BasicString& LowerCase( )
        {
            if ( data_ )
            {
                if ( data_->referenceCount_ > 1 )
                {
                    auto newData = Allocate( data_->size_ );
                    MemCopy( newData->buffer_, data_->buffer_, data_->size_ );
                    ReleaseData( data_ );
                    data_ = newData;
                }
                Core::ToLower( data_->buffer_, data_->size_ );
            }
            return *this;
        }

        [[nodiscard]] BasicString ToLower( ) const
        {
            if ( data_ )
            {
                auto newData = Allocate( data_->size_ );
                MemCopy( newData->buffer_, data_->buffer_, data_->size_ );
                Core::ToLower( newData->buffer_, newData->size_ );
                return BasicString( newData );
            }
            else
            {
                return BasicString( );
            }
        }

        [[nodiscard]] BasicString ToUpper( ) const
        {
            if ( data_ )
            {
                auto newData = Allocate( data_->size_ );
                MemCopy( newData->buffer_, data_->buffer_, data_->size_ );
                Core::ToUpper( newData->buffer_, newData->size_ );
                return BasicString( newData );
            }
            else
            {
                return BasicString( );
            }
        }


        [[nodiscard]] BasicString FirstToUpper( ) const
        {
            if ( data_ )
            {
                if ( IsLower( 0 ) )
                {
                    auto newData = Allocate( data_->size_ );
                    MemCopy( newData->buffer_, data_->buffer_, data_->size_ );
                    *newData->buffer_ = Core::ToUpper( *newData->buffer_ );
                    return BasicString( newData );
                }
                return *this;
            }
            else
            {
                return BasicString( );
            }
        }

        [[nodiscard]] BasicString FirstToLower( ) const
        {
            if ( data_ )
            {
                if ( IsUpper( 0 ) )
                {
                    auto newData = Allocate( data_->size_ );
                    MemCopy( newData->buffer_, data_->buffer_, data_->size_ );
                    *newData->buffer_ = Core::ToLower( *newData->buffer_ );
                    return BasicString( newData );
                }
                return *this;
            }
            else
            {
                return BasicString( );
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
            return Erase( static_cast<size_type>(position - begin()) , 1 );
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

        bool FindAndReplace( CharType what, CharType with, size_type start = 0 )
        {
            if ( data_ )
            {
                auto index = IndexOf( what, start );
                if ( index != npos )
                {
                    if ( data_->referenceCount_ > 1 )
                    {
                        auto currentSize = data_->size_;
                        auto* newData = Allocate( currentSize );
                        MemCopy( newData->buffer_, data_->buffer_, index );
                        auto endIt = data_->buffer_ + currentSize;
                        auto it = data_->buffer_ + index;
                        auto destIt = newData->buffer_ + index;
                        while ( it < endIt )
                        {
                            auto c = *it;
                            if ( c != what )
                            {
                                *destIt = c;
                            }
                            else
                            {
                                *destIt = with;
                            }
                            destIt++;
                            it++;
                        }
                        ReleaseData( data_ );
                        data_ = newData;
                    }
                    else
                    {
                        std::replace( begin( ) + index, end( ), what, with );
                    }
                    return true;
                }
            }
            return false;
        }

        bool FindAndReplace( const CharType* what, size_type whatLength, const CharType* with, size_type withLength, size_type start = 0 )
        {
            if ( data_ )
            {
                auto index = IndexOf( what, whatLength, start );
                if ( index != npos )
                {
                    if ( data_->referenceCount_ > 1 )
                    {
                        auto currentSize = data_->size_;
                        auto* newData = Allocate( currentSize );
                        MemCopy( newData->buffer_, data_->buffer_, index );
                        auto endIt = data_->buffer_ + currentSize;
                        auto it = data_->buffer_ + index;
                        auto destIt = newData->buffer_ + index;
                        while ( it < endIt )
                        {
                            auto c = *it;
                            if ( c != what )
                            {
                                *destIt = c;
                            }
                            else
                            {
                                *destIt = with;
                            }
                            destIt++;
                            it++;
                        }
                        ReleaseData( data_ );
                        data_ = newData;
                    }
                    else
                    {
                        std::replace( begin( ) + index, end( ), what, with );
                    }
                }
            }
            return false;
        }





        void TrimRight( const CharType* charactersToRemove, size_type numberOfCharactersToRemove )
        {
            if ( data_ )
            {
                auto index = LastIndexOfAnyBut( charactersToRemove, numberOfCharactersToRemove );
                erase( index );
            }
        }

        void TrimRight( BasicString& charactersToRemove )
        {
            if ( data_ )
            {
                auto index = LastIndexOfAnyBut( charactersToRemove.c_str( ), charactersToRemove.size( ) );
                erase( index );
            }
        }

        void Replace( size_type replaceAtPosition, size_type replaceLength, const CharType* with, size_type withLength, CharType padCharacter = DefaultPadCharacter )
        {
            if ( data_ )
            {
                auto currentLength = data_->size_;
                auto currentAllocationSize = AllocationByteCount( currentLength );
                if ( (data_->referenceCount_ == 1) && 
                    (data_->Contains( with, replaceAtPosition ) == false) )
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
                                MemMove( data_->buffer_ + newRemainingPosition, data_->buffer_ + curentRemainingPosition, remainingLength );
                                MemMove( data_->buffer_ + replaceAtPosition, with, withLength );
                                data_->size_ = newLength;
                                data_->buffer_[ newLength ] = static_cast< CharType >( 0 );
                            }
                            else
                            {
                                std::unique_ptr<Data> tmp( Allocate( newAllocationSize, newLength ) );
                                MemCopy( tmp->buffer_, data_->buffer_, replaceAtPosition );
                                MemCopy( tmp->buffer_ + newRemainingPosition, data_->buffer_ + curentRemainingPosition, remainingLength );
                                MemCopy( tmp->buffer_ + replaceAtPosition, with, withLength );
                                ReleaseData( data_ );
                                data_ = tmp.release( );
                            }
                        }
                        else
                        {
                            // No change in size, just overwrite
                            MemMove( data_->buffer_ + replaceAtPosition, with, withLength );
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
                                MemSet( data_->buffer_ + data_->size_, padCharacter, replaceAtPosition - data_->size_ );
                                MemCopy( data_->buffer_ + replaceAtPosition, with, withLength );
                                data_->size_ = newLength;
                                data_->buffer_[ newLength ] = static_cast< CharType >( 0 );
                            }
                            else
                            {
                                std::unique_ptr<Data> tmp( Initialize( data_->buffer_, data_->size_, padCharacter, replaceAtPosition, with, withLength ) );
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
                        MemCopy( tmp->buffer_, data_->buffer_, replaceAtPosition );
                        MemCopy( tmp->buffer_ + newRemainingPosition, data_->buffer_ + curentRemainingPosition, remainingLength );
                        MemCopy( tmp->buffer_ + replaceAtPosition, with, withLength );
                        ReleaseData( data_ );
                        data_ = tmp.release( );
                    }
                    else
                    {
                        if ( withLength )
                        {
                            std::unique_ptr<Data> tmp( Initialize( data_->buffer_, data_->size_, padCharacter, replaceAtPosition - data_->size_, with, withLength ) );
                            ReleaseData( data_ );
                            data_ = tmp.release( );
                        }
                    }
                }
            }
            else
            {
                data_ = Initialize( padCharacter, replaceAtPosition, with, withLength);
            }
        }

        void replace( size_type replaceAtPosition, size_type replaceLength, const CharType* with, size_type withLength, CharType padCharacter = DefaultPadCharacter )
        {
            Replace( replaceAtPosition, replaceLength, with, withLength, padCharacter );
        }

        void Replace( const_iterator replaceFirst, const_iterator replaceLast, const CharType* with, size_type withLength, CharType padCharacter = DefaultPadCharacter )
        {
            size_type replaceAtPosition = std::distance(begin(), replaceFirst );
            size_type replaceLength = replaceLast.ptr_ - replaceFirst.ptr_;
            Replace( replaceAtPosition, replaceLength, with, withLength, padCharacter );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, CharType>
        void Replace( size_type replaceAtPosition, size_type replaceLength, const SpanT& with, CharType padCharacter = DefaultPadCharacter )
        {
            Replace( replaceAtPosition, replaceLength, with.data( ), with.size( ), padCharacter );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<std::remove_cvref_t<typename SpanT::value_type>, CharType>
        void replace( size_type replaceAtPosition, size_type replaceLength, const SpanT& with, CharType padCharacter = DefaultPadCharacter )
        {
            Replace( replaceAtPosition, replaceLength, with.data( ), with.size( ), padCharacter );
        }



    };

    template< class CharT, class Traits >
    inline std::basic_ostream<CharT, Traits>& operator<<( std::basic_ostream<CharT, Traits>& os, const BasicString<CharT>& str )
    {
        return std::_Insert_string( os, str.data( ), str.size( ) );
    }

    template <class CharT, class CharTraitsT>
    std::basic_istream<CharT, CharTraitsT>& operator >> ( std::basic_istream<CharT, CharTraitsT>& inputStream, BasicString<CharT>& str )
    {
        using IStreamT = std::basic_istream<CharT, CharTraitsT>;
        using CTypeT = std::ctype<CharT>;
        using SizeType = typename BasicString<CharT>::size_type;

        typename IStreamT::iostate inputStreamState = IStreamT::goodbit;
        bool changed = false;
        const typename IStreamT::sentry sentryOk( inputStream );

        if ( sentryOk )
        { 
            const CTypeT& ctypeFacet = std::use_facet<CTypeT>( inputStream.getloc( ) );
            str.erase( );

            try
            {
                SizeType inputStreamWidth = static_cast< SizeType >( inputStream.width( ) );
                SizeType inputSize;
                if ( inputStreamWidth == 0 )
                {
                    inputSize = str.max_size( );
                }
                else
                {
                    inputSize = std::min( inputStreamWidth, str.max_size( ) );
                }

                typename CharTraitsT::int_type inputCharacter = inputStream.rdbuf( )->sgetc( );

                while( inputSize )
                {
                    if ( CharTraitsT::eq_int_type( CharTraitsT::eof( ), inputCharacter ) )
                    {
                        inputStreamState |= IStreamT::eofbit;
                        break;
                    }
                    else if ( ctypeFacet.is( CTypeT::space, CharTraitsT::to_char_type( inputCharacter ) ) )
                    {
                        break;
                    }
                    else
                    {
                        str.push_back( CharTraitsT::to_char_type( inputCharacter ) );
                        changed = true;
                    }
                    inputSize--; 
                    inputCharacter = inputStream.rdbuf( )->snextc( );
                }
            }
            catch ( ... )
            {
                inputStream.setstate( IStreamT::badbit, true );
            }
        }

        inputStream.width( 0 );
        if ( !changed )
        {
            inputStreamState |= IStreamT::failbit;
        }

        inputStream.setstate( inputStreamState );
        return inputStream;
    }






    static_assert( AnsiStringLike< BasicString<char> > );
    static_assert( WideStringLike< BasicString<wchar_t> > );
    static_assert( SimpleSpanLike< BasicString<char> > );
    static_assert( SimpleSpanLike< BasicString<wchar_t> > );





    template<typename T>
    class BasicStringView : public std::basic_string_view<T>
    {
    public:
        using Base = std::basic_string_view<T>;
        using CharType = typename Base::value_type;
        using const_iterator = typename Base::const_iterator;
        using const_reference = typename Base::const_reference;
        using size_type = typename Base::size_type;
        using value_type = typename Base::value_type;
        using Base::begin;
        using Base::end;
    public:
        constexpr BasicStringView( ) noexcept
        {
        }


        constexpr BasicStringView( const CharType* s, size_type count ) noexcept
            : Base( s, count )
        {
        }

        constexpr BasicStringView( const CharType* s ) noexcept
            : Base(s)
        {
        }

        constexpr BasicStringView( const BasicString<T>& s ) noexcept
            : Base( s.data( ), s.size( ) )
        {
        }

        constexpr BasicStringView( const std::basic_string<T>& s ) noexcept
            : Base( s.data( ), s.size( ) )
        {
        }

        constexpr BasicStringView( const std::basic_string_view<T>& s ) noexcept
            : Base( s.data( ), s.size( ) )
        {
        }


        constexpr BasicStringView& operator = ( const CharType* other )
        {
            Base::operator = ( other );
            return *this;
        }

        constexpr BasicStringView& operator = ( const BasicStringView& other )
        {
            Base::operator = ( other );
            return *this;
        }

        constexpr BasicStringView& operator = ( const std::basic_string_view<T>& other )
        {
            Base::operator = ( other );
            return *this;
        }


        constexpr BasicStringView& operator = ( const BasicString<T>& other )
        {
            *this = BasicStringView( other );
            return *this;
        }

        constexpr BasicStringView& operator = ( const std::basic_string<T>& other )
        {
            *this = BasicStringView( other );
            return *this;
        }


        constexpr explicit operator bool( ) const noexcept
        {
            return Base::size( ) != 0;
        }

        constexpr bool empty( ) const noexcept
        {
            return Base::size( ) == 0;
        }



        [[nodiscard]] size_t Hash( ) const noexcept
        {
            if ( Base::data() )
            {
                return XXH3_64bits( Base::data( ), Base::size( ) * sizeof( CharType ) );
            }
            else
            {
                return 0;
            }
        }

        template<bool ignoreWhiteSpace = true, typename VectorT>
        void Split( CharType separator, VectorT& result ) const
        {
            if ( Base::data( ) )
            {
                Internal::Split<CharType, ignoreWhiteSpace, VectorT>( Base::data( ), Base::size( ), separator, result );
            }
            else
            {
                using DestinationT = typename VectorT::value_type;
                result.clear( );
                result.push_back( DestinationT( ) );
            }
        }

        template<SimpleSpanLike VectorT, bool ignoreWhiteSpace = true>
        VectorT Split( CharType separator ) const
        {
            VectorT result;
            Split( separator, result );
            return result;
        }

    };

    template<typename T>
    inline BasicString<T>::BasicString( const BasicStringView<T>& v )
        : data_( Initialize( v.data( ), v.size( ) ) )
    {
    }
#endif
    template<WideStringLike StringT>
    inline void ToWideString( const char* source, size_t length, unsigned codePage, unsigned flags, StringT& dest )
    {
        auto byteCount = static_cast< int >( length );
        if ( byteCount )
        {
            auto wideCharCount = MultiByteToWideChar( codePage, flags, source, byteCount, nullptr, 0 );
            if ( !wideCharCount )
            {
                ThrowLastOSError( );
            }
            dest.resize( wideCharCount );
            auto rc = MultiByteToWideChar( codePage, flags, source, byteCount, dest.data( ), wideCharCount );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
    }

    namespace Internal
    {
        HCC_EXPORT void ThrowFixedStringArgumentToLong( size_t size, size_t maxSize );
        template<size_t maxSize>
        inline size_t CheckFixedStringSize( size_t size )
        {
            if( size > maxSize )
            {
                ThrowFixedStringArgumentToLong( size, maxSize );
            }
            return size;
        }
    }



    template<typename CharT, size_t maxSize, bool internalSizeInBytes = false>
        requires std::is_same_v<CharT,char> || std::is_same_v<CharT, wchar_t>
    class FixedString
    {
    public:
        using value_type = CharT;
        
        static constexpr bool InternalSizeInBytes = internalSizeInBytes;

        using CharType = CharT;
        static constexpr size_t MaxSize = maxSize;
        using ArrayType = std::array<CharType, MaxSize + 1>;

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

        using StringType = std::conditional_t<std::is_same_v<wchar_t, CharType>, WideString, AnsiString>;
        using StringViewType = std::conditional_t<std::is_same_v<wchar_t, CharType>, std::wstring_view, std::string_view>;
    protected:
        size_t size_ = 0;
    private:
        ArrayType data_ = {};
    protected:
        static size_t CheckSize( size_t size )
        {
            return Internal::CheckFixedStringSize<MaxSize>( size );
        }
        static constexpr size_t ConvertSizeToInternalSize( size_t size )
        {
            if constexpr ( std::is_same_v<CharType, wchar_t> && InternalSizeInBytes )
            {
                return size * sizeof( CharType );
            }
            else
            {
                return size;
            }
        }
        static constexpr size_t ConvertSizeFromInternalSize( size_t size )
        {
            if constexpr ( std::is_same_v<CharType, wchar_t> && InternalSizeInBytes )
            {
                return size / sizeof( CharType );
            }
            else
            {
                return size;
            }
        }

    public:
        constexpr FixedString( ) noexcept = default;

        explicit FixedString( const CharType* str, size_t size )
            : size_( ConvertSizeToInternalSize(CheckSize( size ) ) )
        {
            MemCopy( data_.data( ), str, size );
            data_[ size ] = static_cast< CharType >( 0 );
        }

        explicit FixedString( const CharType* str )
            : size_( ConvertSizeToInternalSize( CheckSize( LengthOf( str ) ) ) )
        {
            if constexpr ( std::is_same_v<CharType, wchar_t> && InternalSizeInBytes )
            {
                auto sz = size_ / sizeof( CharType );
                MemCopy( data_.data( ), str, sz );
                data_[ sz ] = static_cast< CharType >( 0 );
            }
            else
            {
                MemCopy( data_.data( ), str, size_ );
                data_[ size_ ] = static_cast< CharType >( 0 );
            }
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<typename T::value_type, CharType>
        explicit FixedString( const T& str )
            : size_( ConvertSizeToInternalSize( CheckSize( str.size( ) ) ) )
        {
            if constexpr ( std::is_same_v<CharType, wchar_t> && InternalSizeInBytes )
            {
                auto sz = size_ / sizeof( CharType );
                MemCopy( data_.data( ), str.data( ), sz );
                data_[ sz ] = static_cast< CharType >( 0 );
            }
            else
            {
                MemCopy( data_.data( ), str.data( ), str.size( ) );
                data_[ size_ ] = static_cast< CharType >( 0 );
            }
        }

        void Assign( const CharType* str, size_type length )
        {
            size_ = ConvertSizeToInternalSize( CheckSize( length ) );
            MemCopy( data_.data( ), str, length );
            data_[ length ] = static_cast< CharType >( 0 );
        }


        template<SimpleSpanLike T>
            requires std::is_same_v<typename T::value_type, CharType>
        FixedString& operator = ( const T& str )
        {
            Assign( str.data( ), str.size( ) );
            return *this;
        }

        FixedString& operator = ( const CharType* str )
        {
            auto sz = CheckSize( LengthOf(str) );
            size_ = ConvertSizeToInternalSize( sz );
            MemCopy( data_.data( ), str.data( ), sz );
            data_[ sz ] = static_cast< CharType >( 0 );
            return *this;
        }

        [[nodiscard]] constexpr size_type size( ) const noexcept
        {
            if constexpr ( std::is_same_v<CharType, wchar_t> && InternalSizeInBytes )
            {
                auto sz = ConvertSizeFromInternalSize( size_ );
                return sz <= MaxSize ? sz : 0;
            }
            else
            {
                return size_ <= MaxSize ? size_ : 0;
            }
        }
        [[nodiscard]] constexpr size_type length( ) const noexcept
        {
            return size( );
        }
        [[nodiscard]] constexpr size_type Length( ) const noexcept
        {
            return size( );
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


        [[nodiscard]] constexpr const CharType* c_str( ) const noexcept
        {
            if constexpr ( std::is_same_v<CharType, char> )
            {
                return size( ) ? data_.data( ) : "";
            }
            else
            {
                return size( ) ? data_.data( ) : L"";
            }
        }

        [[nodiscard]] constexpr const CharType* data( ) const noexcept
        {
            return data_.data( );
        }
        [[nodiscard]] constexpr CharType* data( ) noexcept
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

        


        [[nodiscard]] StringType ToString( ) const
        {
            if ( size_ )
            {
                return StringType( data_.data( ), size( ) );
            }
            return {};
        }

        [[nodiscard]] StringViewType ToStringView( ) const
        {
            if ( size_ )
            {
                return StringViewType( data_.data( ), size( ) );
            }
            return {};
        }

    private:
        [[nodiscard]] static bool AreEqual( const CharType* first, size_type firstSize, const CharType* second, size_type secondSize )
        {
            if ( first && firstSize )
            {
                if ( second )
                {
                    if ( firstSize == secondSize )
                    {
                        return Internal::Compare( first, firstSize, second, secondSize ) == 0;
                    }
                }
                return false;
            }
            return second && secondSize ? false : true;
        }

    public:
        template<size_t M, bool ist>
        bool operator == ( const FixedString<CharType,M, ist>& other ) const
        {
            return AreEqual( data( ), size( ), other.data( ), other.size( ) );
        }
        template<size_t M, bool ist>
        bool operator != ( const FixedString<CharType, M,ist>& other ) const
        {
            return AreEqual( data( ), size( ), other.data( ), other.size( ) ) == false;
        }

    };

    template<size_t maxSize>
    using FixedWideString = FixedString<wchar_t, maxSize>;
    template<size_t maxSize>
    using FixedAnsiString = FixedString<char, maxSize>;



    template<WideStringLike StringT>
    inline void ToWideString( const char* source, size_t length, StringT& dest )
    {
        ToWideString( source, length, CP_ACP, 0, dest );
    }

    template<AnsiStringLike AnsiStringT,WideStringLike WideStringT>
    inline void ToWideString( const AnsiStringT& source, WideStringT& dest )
    {
        ToWideString( source.c_str( ), source.length( ), dest );
    }
    inline WideString ToWideString( const std::string& source )
    {
        WideString result;
        ToWideString( source, result );
        return result;
    }

    inline WideString ToWideString( const AnsiString& source )
    {
        WideString result;
        ToWideString( source, result );
        return result;
    }


    inline WideString ToWideString( const std::string_view& source )
    {
        WideString result;
        ToWideString( source.data( ), source.size( ), result );
        return result;
    }

    inline WideString ToWideString( const char* source )
    {
        if ( source && source[ 0 ] )
        {
            auto length = strlen( source );
            WideString result;
            ToWideString( source, length, CP_ACP, 0, result );
            return result;
        }
        else
        {
            return {};
        }
    }
    inline WideString ToWideString( const wchar_t* source )
    {
        if ( source && source[ 0 ] )
        {
            auto length = wcslen( source );
            WideString result( source, length );
            return result;
        }
        else
        {
            return {};
        }
    }

    HCC_EXPORT WideString ToWideString( bool value );
    HCC_EXPORT WideString ToWideString( SByte value, int base = 10 );
    HCC_EXPORT WideString ToWideString( Byte value, int base = 10 );
    HCC_EXPORT WideString ToWideString( Int16 value, int base = 10 );
    HCC_EXPORT WideString ToWideString( UInt16 value, int base = 10 );
    HCC_EXPORT WideString ToWideString( Int32 value, int base = 10 );
    HCC_EXPORT WideString ToWideString( UInt32 value, int base = 10 );
    HCC_EXPORT WideString ToWideString( Int64 value, int base = 10 );
    HCC_EXPORT WideString ToWideString( UInt64 value, int base = 10 );
    HCC_EXPORT WideString ToWideStringInvariant( Single value, int width, int precision );
    HCC_EXPORT WideString ToWideStringInvariant( Single value );
    HCC_EXPORT WideString ToWideString( Single value );
    HCC_EXPORT WideString ToWideString( Single value, int width, int precission );
    HCC_EXPORT WideString ToWideString( Single value, const std::locale& locale );
    HCC_EXPORT WideString ToWideString( Single value, int width, int precission, const std::locale& locale );
    HCC_EXPORT WideString ToWideString( Double value );
    HCC_EXPORT WideString ToWideString( const DateTime& value );
    HCC_EXPORT WideString ToWideString( const TimeSpan& value );
    HCC_EXPORT WideString ToWideString( const Guid& value );
    HCC_EXPORT WideString ToWideString( const Currency& value );
    HCC_EXPORT WideString ToWideString( const Variant& value );

    struct FixedSizeMemoryManagerStatistics;

    HCC_EXPORT [[nodiscard]] WideString ToWideString( const FixedSizeMemoryManagerStatistics& statistics );
    

    template<AnsiStringLike StringT>
    inline void ToAnsiString( const wchar_t* source, size_t length, unsigned codePage, unsigned flags, StringT& dest )
    {
        auto wideCharCount = static_cast< int >( length );
        if ( wideCharCount )
        {
            auto byteCount = WideCharToMultiByte( codePage, flags, source, wideCharCount, nullptr, 0, nullptr, nullptr );
            if ( !byteCount )
            {
                ThrowLastOSError( );
            }
            dest.resize( byteCount );
            auto rc = WideCharToMultiByte( codePage, flags, source, wideCharCount, dest.data( ), byteCount, nullptr, nullptr );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
    }

    template<AnsiStringLike StringT>
    inline void ToAnsiString( const wchar_t* source, size_t length, StringT& dest )
    {
        ToAnsiString( source, length, CP_ACP, 0, dest );
    }

    template<WideStringLike WideStringT,AnsiStringLike AnsiStringT>
    inline void ToAnsiString( const WideStringT& source, AnsiStringT& dest )
    {
        ToAnsiString( source.c_str( ), source.length( ), CP_ACP, 0, dest );
    }
    template<AnsiStringLike AnsiStringT = AnsiString, WideStringLike WideStringT>
    inline AnsiStringT ToAnsiString( const WideStringT& source )
    {
        AnsiStringT result;
        ToAnsiString( source, result );
        return result;
    }

    inline void ToAnsiString( const std::wstring_view& source, AnsiString& dest )
    {
        ToAnsiString( source.data( ), source.length( ), CP_ACP, 0, dest );
    }
    inline AnsiString ToAnsiString( const std::wstring_view& source )
    {
        AnsiString result;
        ToAnsiString( source, result );
        return result;
    }

    inline AnsiString ToAnsiString( const wchar_t* source )
    {
        if ( source && source[ 0 ] )
        {
            auto length = wcslen( source );
            AnsiString result;
            ToAnsiString( source, length, CP_ACP, 0, result );
            return result;
        }
        else
        {
            return {};
        }
    }

    template<AnsiStringLike StringT = AnsiString>
    inline StringT ToAnsiString( const wchar_t* source )
    {
        if ( source && source[ 0 ] )
        {
            auto length = wcslen( source );
            StringT result;
            ToAnsiString( source, length, CP_ACP, 0, result );
            return result;
        }
        else
        {
            return {};
        }
    }

    template<AnsiStringLike StringT = AnsiString>
    inline StringT ToAnsiString( const char* source )
    {
        if ( source && source[ 0 ] )
        {
            auto length = strlen( source );
            StringT result( source, length );
            return result;
        }
        else
        {
            return {};
        }
    }

    inline AnsiString ToAnsiString( const std::string& source )
    {
        AnsiString result( source.c_str(), source.size() );
        return result;
    }


    HCC_EXPORT AnsiString ToAnsiString( bool value );
    HCC_EXPORT AnsiString ToAnsiString( SByte value, int base = 10 );
    HCC_EXPORT AnsiString ToAnsiString( Byte value, int base = 10 );
    HCC_EXPORT AnsiString ToAnsiString( Int16 value, int base = 10 );
    HCC_EXPORT AnsiString ToAnsiString( UInt16 value, int base = 10 );
    HCC_EXPORT AnsiString ToAnsiString( Int32 value, int base = 10 );
    HCC_EXPORT AnsiString ToAnsiString( UInt32 value, int base = 10 );
    HCC_EXPORT AnsiString ToAnsiString( Int64 value, int base = 10 );
    HCC_EXPORT AnsiString ToAnsiString( UInt64 value, int base = 10 );
    HCC_EXPORT AnsiString ToAnsiStringInvariant( Single value, int width, int precision );
    HCC_EXPORT AnsiString ToAnsiStringInvariant( Single value );
    HCC_EXPORT AnsiString ToAnsiString( Single value );
    HCC_EXPORT AnsiString ToAnsiString( Single value, const std::locale& locale );
    HCC_EXPORT AnsiString ToAnsiString( Single value, int width, int precision );
    HCC_EXPORT AnsiString ToAnsiString( Single value, int width, int precision, const std::locale& locale );
    HCC_EXPORT AnsiString ToAnsiStringInvariant( Double value, int width, int precision );
    HCC_EXPORT AnsiString ToAnsiStringInvariant( Double value );
    HCC_EXPORT AnsiString ToAnsiString( Double value );
    HCC_EXPORT AnsiString ToAnsiString( Double value, const std::locale& locale );
    HCC_EXPORT AnsiString ToAnsiString( Double value, int width, int precision );
    HCC_EXPORT AnsiString ToAnsiString( Double value, int width, int precision, const std::locale& locale );
    HCC_EXPORT AnsiString ToAnsiString( const DateTime& value );
    HCC_EXPORT AnsiString ToAnsiString( const TimeSpan& value );
    HCC_EXPORT AnsiString ToAnsiString( const Guid& value );
    HCC_EXPORT AnsiString ToAnsiString( const Currency& value );
    HCC_EXPORT AnsiString ToAnsiString( const Variant& value );

    HCC_EXPORT [[nodiscard]] AnsiString ToAnsiString( const FixedSizeMemoryManagerStatistics& statistics );

    

    HCC_EXPORT bool ParseBoolean( const wchar_t* str ) noexcept;
    HCC_EXPORT bool ParseBoolean( const char* str ) noexcept;

    template<SimpleStringLike StringT>
    inline bool ParseBoolean( const StringT& str ) noexcept
    {
        return ParseBoolean( str.c_str( ) );
    }

    HCC_EXPORT bool TryParseBoolean( const wchar_t* str, bool& value ) noexcept;
    HCC_EXPORT bool TryParseBoolean( const char* str, bool& value ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseBoolean( const StringT& str, bool& value ) noexcept
    {
        return TryParseBoolean( str.c_str( ), value );
    }

    template<typename T>
        requires std::is_same_v<char,T> || std::is_same_v<wchar_t, T>
    inline bool TryParse( const T* str, bool& value )
    {
        return TryParseBoolean( str, value );
    }
    template<SimpleStringLike StringT>
    inline bool TryParse( const StringT& str, bool& value ) noexcept
    {
        return TryParseBoolean( str.c_str( ), value );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<bool,T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T Parse( const CharT* str )
    { 
        return ParseBoolean( str );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<bool, T>
    inline T Parse( const StringT& str )
    {
        return ParseBoolean( str.c_str() );
    }



    HCC_EXPORT Byte ParseByte( const wchar_t* str, int radix = 10 );
    HCC_EXPORT Byte ParseByte( const char* str, int radix = 10 );

    template<SimpleStringLike StringT>
    inline Byte ParseByte( const StringT& str, int radix = 10 )
    {
        return ParseByte( str.c_str( ), radix );
    }
    
    HCC_EXPORT bool TryParseByte( const wchar_t* str, Byte& value, int radix = 10 ) noexcept;
    HCC_EXPORT bool TryParseByte( const char* str, Byte& value, int radix = 10 ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseByte( const StringT& str, Byte& value, int radix = 10 ) noexcept
    {
        return TryParseByte( str.c_str( ), value, radix );
    }

    template<typename CharT>
        requires std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT>
    inline bool TryParse( const CharT* str, Byte& value, int radix = 10 )
    {
        return TryParseByte( str, value, radix );
    }
    template<SimpleStringLike StringT>
    inline bool TryParse( const StringT& str, Byte& value, int radix = 10 ) noexcept
    {
        return TryParseByte( str.c_str( ), value, radix );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Byte, T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T Parse( const CharT* str, int radix = 10 )
    {
        return ParseByte( str, radix );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<Byte, T>
    inline T Parse( const StringT& str, int radix = 10 )
    {
        return ParseByte( str.c_str( ), radix );
    }



    HCC_EXPORT SByte ParseSByte( const wchar_t* str, int radix = 10 );
    HCC_EXPORT SByte ParseSByte( const char* str, int radix = 10 );

    template<SimpleStringLike StringT>
    inline SByte ParseSByte( const StringT& str, int radix = 10 )
    {
        return ParseSByte( str.c_str( ), radix );
    }

    HCC_EXPORT bool TryParseSByte( const wchar_t* str, SByte& value, int radix = 10 ) noexcept;
    HCC_EXPORT bool TryParseSByte( const char* str, SByte& value, int radix = 10 ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseSByte( const StringT& str, SByte& value, int radix = 10 ) noexcept
    {
        return TryParseSByte( str.c_str( ), value, radix );
    }

    template<typename CharT>
        requires std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT>
    inline bool TryParse( const CharT* str, SByte& value, int radix = 10 )
    {
        return TryParseSByte( str, value, radix );
    }
    template<SimpleStringLike StringT>
    inline bool TryParse( const StringT& str, SByte& value, int radix = 10 ) noexcept
    {
        return TryParseSByte( str.c_str( ), value, radix );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<SByte, T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T Parse( const CharT* str, int radix = 10 )
    {
        return ParseSByte( str, radix );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<SByte, T>
    inline T Parse( const StringT& str, int radix = 10 )
    {
        return ParseSByte( str.c_str( ), radix );
    }


    HCC_EXPORT Int16 ParseInt16( const wchar_t* str, int radix = 10 );
    HCC_EXPORT Int16 ParseInt16( const char* str, int radix = 10 );

    template<SimpleStringLike StringT>
    inline Int16 ParseInt16( const StringT& str, int radix = 10 )
    {
        return ParseInt16( str.c_str( ), radix );
    }

    HCC_EXPORT bool TryParseInt16( const wchar_t* str, Int16& value, int radix = 10 ) noexcept;
    HCC_EXPORT bool TryParseInt16( const char* str, Int16& value, int radix = 10 ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseInt16( const StringT& str, Int16& value, int radix = 10 ) noexcept
    {
        return TryParseInt16( str.c_str( ), value, radix );
    }

    template<typename CharT>
        requires std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT>
    inline bool TryParse( const CharT* str, Int16& value, int radix = 10 )
    {
        return TryParseInt16( str, value, radix );
    }
    template<SimpleStringLike StringT>
    inline bool TryParse( const StringT& str, Int16& value, int radix = 10 ) noexcept
    {
        return TryParseInt16( str.c_str( ), value, radix );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Int16, T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T Parse( const CharT* str, int radix = 10 )
    {
        return ParseInt16( str, radix );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<Int16, T>
    inline T Parse( const StringT& str, int radix = 10 )
    {
        return ParseInt16( str.c_str( ), radix );
    }


    HCC_EXPORT UInt16 ParseUInt16( const wchar_t* str, int radix = 10 );
    HCC_EXPORT UInt16 ParseUInt16( const char* str, int radix = 10 );

    template<SimpleStringLike StringT>
    inline UInt16 ParseUInt16( const StringT& str, int radix = 10 )
    {
        return ParseUInt16( str.c_str( ), radix );
    }

    HCC_EXPORT bool TryParseUInt16( const wchar_t* str, UInt16& value, int radix = 10 ) noexcept;
    HCC_EXPORT bool TryParseUInt16( const char* str, UInt16& value, int radix = 10 ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseUInt16( const StringT& str, UInt16& value, int radix = 10 ) noexcept
    {
        return TryParseUInt16( str.c_str( ), value, radix );
    }

    template<typename CharT>
        requires std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT>
    inline bool TryParse( const CharT* str, UInt16& value, int radix = 10 )
    {
        return TryParseUInt16( str, value, radix );
    }
    template<SimpleStringLike StringT>
    inline bool TryParse( const StringT& str, UInt16& value, int radix = 10 ) noexcept
    {
        return TryParseUInt16( str.c_str( ), value, radix );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<UInt16, T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T Parse( const CharT* str, int radix = 10 )
    {
        return ParseUInt16( str, radix );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<UInt16, T>
    inline T Parse( const StringT& str, int radix = 10 )
    {
        return ParseUInt16( str.c_str( ), radix );
    }


    HCC_EXPORT Int32 ParseInt32( const wchar_t* str, int radix = 10 );
    HCC_EXPORT Int32 ParseInt32( const char* str, int radix = 10 );

    template<SimpleStringLike StringT>
    inline Int32 ParseInt32( const StringT& str, int radix = 10 )
    {
        return ParseInt32( str.c_str( ), radix );
    }

    HCC_EXPORT bool TryParseInt32( const wchar_t* str, Int32& value, int radix = 10 ) noexcept;
    HCC_EXPORT bool TryParseInt32( const char* str, Int32& value, int radix = 10 ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseInt32( const StringT& str, Int32& value, int radix = 10 ) noexcept
    {
        return TryParseInt32( str.c_str( ), value, radix );
    }

    template<typename CharT>
        requires std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT>
    inline bool TryParse( const CharT* str, Int32& value, int radix = 10 )
    {
        return TryParseInt32( str, value, radix );
    }
    template<SimpleStringLike StringT>
    inline bool TryParse( const StringT& str, Int32& value, int radix = 10 ) noexcept
    {
        return TryParseInt32( str.c_str( ), value, radix );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Int32, T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T Parse( const CharT* str, int radix = 10 )
    {
        return ParseInt32( str, radix );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<Int32, T>
    inline T Parse( const StringT& str, int radix = 10 )
    {
        return ParseInt32( str.c_str( ), radix );
    }


    HCC_EXPORT UInt32 ParseUInt32( const wchar_t* str, int radix = 10 );
    HCC_EXPORT UInt32 ParseUInt32( const char* str, int radix = 10 );

    template<SimpleStringLike StringT>
    inline UInt32 ParseUInt32( const StringT& str, int radix = 10 )
    {
        return ParseUInt32( str.c_str( ), radix );
    }

    HCC_EXPORT bool TryParseUInt32( const wchar_t* str, UInt32& value, int radix = 10 ) noexcept;
    HCC_EXPORT bool TryParseUInt32( const char* str, UInt32& value, int radix = 10 ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseUInt32( const StringT& str, UInt32& value, int radix = 10 ) noexcept
    {
        return TryParseUInt32( str.c_str( ), value, radix );
    }

    template<typename CharT>
        requires std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT>
    inline bool TryParse( const CharT* str, UInt32& value, int radix = 10 )
    {
        return TryParseUInt32( str, value, radix );
    }
    template<SimpleStringLike StringT>
    inline bool TryParse( const StringT& str, UInt32& value, int radix = 10 ) noexcept
    {
        return TryParseUInt32( str.c_str( ), value, radix );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<UInt32, T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T Parse( const CharT* str, int radix = 10 )
    {
        return ParseUInt32( str, radix );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<UInt32, T>
    inline T Parse( const StringT& str, int radix = 10 )
    {
        return ParseUInt32( str.c_str( ), radix );
    }


    HCC_EXPORT Int64 ParseInt64( const wchar_t* str, int radix = 10 );
    HCC_EXPORT Int64 ParseInt64( const char* str, int radix = 10 );

    template<SimpleStringLike StringT>
    inline Int64 ParseInt64( const StringT& str, int radix = 10 )
    {
        return ParseInt64( str.c_str( ), radix );
    }

    HCC_EXPORT bool TryParseInt64( const wchar_t* str, Int64& value, int radix = 10 ) noexcept;
    HCC_EXPORT bool TryParseInt64( const char* str, Int64& value, int radix = 10 ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseInt64( const StringT& str, Int64& value, int radix = 10 ) noexcept
    {
        return TryParseInt64( str.c_str( ), value, radix );
    }

    template<typename CharT>
        requires std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT>
    inline bool TryParse( const CharT* str, Int64& value, int radix = 10 )
    {
        return TryParseInt64( str, value, radix );
    }
    template<SimpleStringLike StringT>
    inline bool TryParse( const StringT& str, Int64& value, int radix = 10 ) noexcept
    {
        return TryParseInt64( str.c_str( ), value, radix );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Int64, T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T Parse( const CharT* str, int radix = 10 )
    {
        return ParseInt64( str, radix );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<Int64, T>
    inline T Parse( const StringT& str, int radix = 10 )
    {
        return ParseInt64( str.c_str( ), radix );
    }


    HCC_EXPORT UInt64 ParseUInt64( const wchar_t* str, int radix = 10 );
    HCC_EXPORT UInt64 ParseUInt64( const char* str, int radix = 10 );

    template<SimpleStringLike StringT>
    inline UInt64 ParseUInt64( const StringT& str, int radix = 10 )
    {
        return ParseUInt64( str.c_str( ), radix );
    }

    HCC_EXPORT bool TryParseUInt64( const wchar_t* str, UInt64& value, int radix = 10 ) noexcept;
    HCC_EXPORT bool TryParseUInt64( const char* str, UInt64& value, int radix = 10 ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseUInt64( const StringT& str, UInt64& value, int radix = 10 ) noexcept
    {
        return TryParseUInt64( str.c_str( ), value, radix );
    }

    template<typename CharT>
        requires std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT>
    inline bool TryParse( const CharT* str, UInt64& value, int radix = 10 )
    {
        return TryParseUInt64( str, value, radix );
    }
    template<SimpleStringLike StringT>
    inline bool TryParse( const StringT& str, UInt64& value, int radix = 10 ) noexcept
    {
        return TryParseUInt64( str.c_str( ), value, radix );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<UInt64, T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T Parse( const CharT* str, int radix = 10 )
    {
        return ParseUInt64( str, radix );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<UInt64, T>
    inline T Parse( const StringT& str, int radix = 10 )
    {
        return ParseUInt64( str.c_str( ), radix );
    }

    HCC_EXPORT Single ParseSingle( const wchar_t* str );
    HCC_EXPORT Single ParseSingle( const char* str );

    template<SimpleStringLike StringT>
    inline Single ParseSingle( const StringT& str )
    {
        return ParseSingle( str.c_str( ) );
    }

    HCC_EXPORT bool TryParseSingle( const wchar_t* str, float& value ) noexcept;
    HCC_EXPORT bool TryParseSingle( const char* str, float& value ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseSingle( const StringT& str, float& value ) noexcept
    {
        return TryParseSingle( str.c_str( ), value );
    }

    template<typename CharT>
        requires std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT>
    inline bool TryParse( const CharT* str, float& value )
    {
        return TryParseSingle( str, value );
    }
    template<SimpleStringLike StringT>
    inline bool TryParse( const StringT& str, float& value ) noexcept
    {
        return TryParseSingle( str.c_str( ), value );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<float, T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T Parse( const CharT* str )
    {
        return ParseSingle( str );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<float, T>
    inline T Parse( const StringT& str )
    {
        return ParseSingle( str.c_str( ) );
    }

    HCC_EXPORT Single ParseSingleInvariant( const wchar_t* str );
    HCC_EXPORT Single ParseSingleInvariant( const char* str );

    template<SimpleStringLike StringT>
    inline Single ParseSingleInvariant( std::locale locale, const StringT& str )
    {
        return ParseSingleInvariant( str.c_str( ) );
    }

    HCC_EXPORT bool TryParseSingleInvariant( const wchar_t* str, float& value ) noexcept;
    HCC_EXPORT bool TryParseSingleInvariant( const char* str, float& value ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseSingleInvariant( const StringT& str, float& value ) noexcept
    {
        return TryParseSingleInvariant( str.c_str( ), value );
    }


    template<typename CharT>
        requires std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT>
    inline bool TryParseInvariant( const CharT* str, float& value )
    {
        return TryParseSingleInvariant( str, value );
    }
    template<SimpleStringLike StringT>
    inline bool TryParseInvariant( const StringT& str, float& value) noexcept
    {
        return TryParseSingleInvariant( str.c_str( ), value );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<float, T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T ParseInvariant( const CharT* str )
    {
        return ParseSingleInvariant( str );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<float, T>
    inline T ParseInvariant( const StringT& str )
    {
        return ParseSingleInvariant( str.c_str( ) );
    }


    HCC_EXPORT Double ParseDouble( const wchar_t* str );
    HCC_EXPORT Double ParseDouble( const char* str );

    template<SimpleStringLike StringT>
    inline Double ParseDouble( const StringT& str )
    {
        return ParseDouble( str.c_str( ) );
    }

    HCC_EXPORT bool TryParseDouble( const wchar_t* str, double& value ) noexcept;
    HCC_EXPORT bool TryParseDouble( const char* str, double& value ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseDouble( const StringT& str, double& value ) noexcept
    {
        return TryParseDouble( str.c_str( ), value );
    }

    template<typename CharT>
        requires std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT>
    inline bool TryParse( const CharT* str, double& value )
    {
        return TryParseDouble( str, value );
    }
    template<SimpleStringLike StringT>
    inline bool TryParse( const StringT& str, double& value ) noexcept
    {
        return TryParseDouble( str.c_str( ), value );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<double, T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T Parse( const CharT* str )
    {
        return ParseDouble( str );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<double, T>
    inline T Parse( const StringT& str )
    {
        return ParseDouble( str.c_str( ) );
    }


    HCC_EXPORT Double ParseDoubleInvariant( const wchar_t* str );
    HCC_EXPORT Double ParseDoubleInvariant( const char* str );

    template<SimpleStringLike StringT>
    inline Double ParseDoubleInvariant( const StringT& str )
    {
        return ParseDoubleInvariant( str.c_str( ) );
    }

    HCC_EXPORT bool TryParseDoubleInvariant( const wchar_t* str, double& value ) noexcept;
    HCC_EXPORT bool TryParseDoubleInvariant( const char* str, double& value ) noexcept;

    template<SimpleStringLike StringT>
    inline bool TryParseDoubleInvariant( const StringT& str, double& value ) noexcept
    {
        return TryParseDoubleInvariant( str.c_str( ), value );
    }

    template<typename CharT>
        requires std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT>
    inline bool TryParseInvariant( const CharT* str, double& value )
    {
        return TryParseDoubleInvariant( str, value );
    }
    template<SimpleStringLike StringT>
    inline bool TryParseInvariant( const StringT& str, double& value ) noexcept
    {
        return TryParseDoubleInvariant( str.c_str( ), value );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<double, T> && ( std::is_same_v<char, CharT> || std::is_same_v<wchar_t, CharT> )
    inline T ParseInvariant( const CharT* str )
    {
        return ParseDoubleInvariant( str );
    }
    template<typename T, SimpleStringLike StringT>
        requires std::is_same_v<double, T>
    inline T ParseInvariant( const StringT& str )
    {
        return ParseDoubleInvariant( str.c_str( ) );
    }



    inline bool IsAlnum( wchar_t c )
    {
        return std::iswalnum( c );
    }
    inline bool IsAlnum( char c )
    {
        return std::isalnum( c );
    }
    inline bool IsAlpha( wchar_t c )
    {
        return std::iswalpha( c );
    }
    inline bool IsAlpha( char c )
    {
        return std::isalpha( c );
    }
    inline bool IsBlank( wchar_t c )
    {
        return std::iswblank( c );
    }
    inline bool IsBlank( char c )
    {
        return std::isblank( c );
    }
    inline bool IsCntrl( wchar_t c )
    {
        return std::iswcntrl( c );
    }
    inline bool IsCntrl( char c )
    {
        return std::iscntrl( c );
    }
    inline bool IsDigit( wchar_t c )
    {
        return std::iswdigit( c );
    }
    inline bool IsDigit( char c )
    {
        return std::isdigit( c );
    }
    inline bool IsGraph( wchar_t c )
    {
        return std::iswgraph( c );
    }
    inline bool IsGraph( char c )
    {
        return std::isgraph( c );
    }
    inline bool IsLower( wchar_t c )
    {
        return std::iswlower( c );
    }
    inline bool IsLower( char c )
    {
        return std::islower( c );
    }
    inline bool IsPrint( wchar_t c )
    {
        return std::iswprint( c );
    }
    inline bool IsPrint( char c )
    {
        return std::isprint( c );
    }
    inline bool IsPunct( wchar_t c )
    {
        return std::iswpunct( c );
    }
    inline bool IsPunct( char c )
    {
        return std::ispunct( c );
    }
    inline bool IsSpace( wchar_t c )
    {
        return std::iswspace( c );
    }
    inline bool IsSpace( char c )
    {
        return std::isspace( c );
    }
    inline bool IsUpper( wchar_t c )
    {
        return std::iswupper( c );
    }
    inline bool IsUpper( char c )
    {
        return std::isupper( c );
    }
    inline bool IsXDigit( wchar_t c )
    {
        return std::iswxdigit( c );
    }
    inline bool IsXDigit( char c )
    {
        return std::isxdigit( c );
    }

    template<typename T>
        requires ( IsStdBasicString<T> || IsStdBasicStringView<T> || IsBasicString<T> || IsBasicStringView<T> )
    inline T TrimTrailing( const T& str, bool( testFunction )( typename T::value_type c ) )
    {
        using StringType = T;
        using CharType = StringType::value_type;
        auto begin = str.begin( );
        auto end = str.end( );
        while ( end > begin )
        {
            --end;
            CharType c = *end;
            if ( testFunction( c ) == false )
            {
                ++end;
                break;
            }
        }
        return StringType( begin, end );
    }

    template<typename T >
        requires ( IsStdBasicString<T> || IsStdBasicStringView<T> || IsBasicString<T> || IsBasicStringView<T> )
    inline T TrimTrailing( const T& str )
    {
        return TrimTrailing<T>( str, IsSpace );
    }

    template<typename T>
        requires ( IsStdBasicString<T> || IsStdBasicStringView<T> || IsBasicString<T> || IsBasicStringView<T> )
    inline T Trim( const T& str, bool( testFunction )( typename T::value_type c ) )
    {
        using StringType = T;
        using CharType = StringType::value_type;
        auto begin = str.begin( );
        auto end = str.end( );

        while ( begin < end )
        {
            CharType c = *begin;
            if ( testFunction( c ) == false )
            {
                break;
            }
            ++begin;
        }
        if ( begin < end )
        {
            while ( end > begin )
            {
                --end;
                CharType c = *end;
                if ( testFunction( c ) == false )
                {
                    ++end;
                    break;
                }
            }
        }
        return StringType( begin, end );
    }

    template<typename T >
        requires ( IsStdBasicString<T> || IsStdBasicStringView<T> || IsBasicString<T> || IsBasicStringView<T> )
    inline T Trim( const T& str )
    {
        return Trim<T>( str, IsSpace );
    }


    template<typename T>
        requires ( IsStdBasicString<T> || IsStdBasicStringView<T> || IsBasicString<T> || IsBasicStringView<T> )
    inline T TrimLeading( const T& str, bool( testFunction )( typename T::value_type c ) )
    {
        using StringType = T;
        using CharType = StringType::value_type;
        auto begin = str.begin( );
        auto end = str.end( );

        while ( begin < end )
        {
            CharType c = *begin;
            if ( testFunction( c ) == false )
            {
                break;
            }
            ++begin;
        }
        return StringType( begin, end );
    }

    template<typename T >
        requires ( IsStdBasicString<T> || IsStdBasicStringView<T> || IsBasicString<T> || IsBasicStringView<T> )
    inline T TrimLeading( const T& str )
    {
        return TrimLeading<T>( str, IsSpace );
    }

    template<typename T >
        requires ( IsStdBasicString<T> || IsBasicString<T> )
    inline T Strip( const T& str, bool( testFunction )( typename T::value_type c ) )
    {
        using StringType = T;
        using CharType = StringType::value_type;
        auto begin = str.begin( );
        auto end = str.end( );
        StringType result;
        result.reserve( str.size( ) );
        while ( begin < end )
        {
            CharType c = *begin;
            if ( testFunction( c ) == false )
            {
                result += c;
            }
            ++begin;
        }
        return result;
    }

    


    template<typename T >
        requires ( IsStdBasicString<T> )
    inline T ToLower( const T& str )
    {
        using StringType = T;
        using CharType = StringType::value_type;
        auto begin = str.begin( );
        auto end = str.end( );
        StringType result;
#ifndef HCC_WITH_BASIC_STRING
        result.reserve( str.size( ) );
#endif
        while ( begin < end )
        {
            CharType c = *begin;
            if ( IsUpper( c ) == false )
            {
                result += c;
            }
            else
            {
                result += ToLower( c );
            }
            ++begin;
        }
        return result;
    }
    template<typename T >
        requires ( IsBasicString<T> )
    inline T ToLower( const T& str )
    {
        return str.ToLower( );
    }



    template<typename T >
        requires ( IsStdBasicString<T> )
    inline T ToUpper( const T& str )
    {
        using StringType = T;
        using CharType = StringType::value_type;
        auto begin = str.begin( );
        auto end = str.end( );
        StringType result;
        result.reserve( str.size( ) );
        while ( begin < end )
        {
            CharType c = *begin;
            if ( IsLower( c ) == false )
            {
                result += c;
            }
            else
            {
                result += ToUpper( c );
            }
            ++begin;
        }
        return result;
    }

    template<typename T >
        requires ( IsBasicString<T> )
    inline T ToUpper( const T& str )
    {
        return str.ToUpper( );
    }


    template<SimpleCharSpanLike SpanT>
    inline bool StartsWith( const SpanT& span, typename SpanT::value_type value )
    {
        if ( span.size( ) )
        {
            return span[ 0 ] == value;
        }
        return false;
    }

    template<SimpleCharSpanLike SpanT>
    inline bool EndsWith( const SpanT& span, typename SpanT::value_type value )
    {
        auto size = span.size( );
        if ( size )
        {
            return span[ size - 1 ] == value;
        }
        return false;
    }



#ifdef HCC_WITH_BASIC_STRING
    inline [[nodiscard]] AnsiString FormatV( const std::string_view fmt, const std::format_args args )
    {
        AnsiString result;
        std::vformat_to( std::back_insert_iterator{ result }, fmt, args );
        return result;
    }

    inline [[nodiscard]] WideString FormatV( const std::wstring_view fmt, const std::wformat_args args )
    {
        WideString result;
        std::vformat_to( std::back_insert_iterator{ result }, fmt, args );
        return result;
    }

    inline [[nodiscard]] AnsiString FormatV( const std::locale& locale, const std::string_view fmt, const std::format_args args )
    {
        AnsiString result;
        std::vformat_to( std::back_insert_iterator{ result }, locale, fmt, args );
        return result;
    }

    inline [[nodiscard]] WideString FormatV( const std::locale& locale, const std::wstring_view fmt, const std::wformat_args args )
    {
        WideString result;
        std::vformat_to( std::back_insert_iterator{ result }, locale, fmt, args );
        return result;
    }


    template <class... Types>
    inline [[nodiscard]] AnsiString Format( const std::format_string<Types...> fmt, Types&&... args )
    {
        return FormatV( fmt.get( ), std::make_format_args( args... ) );
    }

    template <class... Types>
    inline [[nodiscard]] WideString Format( const std::wformat_string<Types...> fmt, Types&&... args )
    {
        return FormatV( fmt.get( ), std::make_wformat_args( args... ) );
    }


    template <class... Types>
    inline [[nodiscard]] AnsiString Format( const std::locale& locale, const std::format_string<Types...> fmt, Types&&... args )
    {
        return FormatV( locale, fmt.get( ), std::make_format_args( args... ) );
    }

    template <class... Types>
    inline [[nodiscard]] WideString Format( const std::locale& locale, const std::wformat_string<Types...> fmt, Types&&... args )
    {
        return FormatV( locale, fmt.get( ), std::make_wformat_args( args... ) );
    }

    //
    template <class... Types>
    inline void PrintLn( const std::format_string<Types...> fmt, Types&&... args )
    {
        auto str = FormatV( fmt.get( ), std::make_format_args( args... ) );
        puts( str.c_str( ) );
    }

    template <class... Types>
    inline void PrintLn( const std::wformat_string<Types...> fmt, Types&&... args )
    {
        auto str = FormatV( fmt.get( ), std::make_wformat_args( args... ) );
        _putws( str.c_str( ) );
    }


    template <class... Types>
    inline void PrintLn( const std::locale& locale, const std::format_string<Types...> fmt, Types&&... args )
    {
        auto str = FormatV( locale, fmt.get( ), std::make_format_args( args... ) );
        puts( str.c_str( ) );
    }

    template <class... Types>
    inline void PrintLn( const std::locale& locale, const std::wformat_string<Types...> fmt, Types&&... args )
    {
        auto str = FormatV( locale, fmt.get( ), std::make_wformat_args( args... ) );
        _putws( str.c_str( ) );
    }


#endif
    namespace Html
    {
        /// <summary>
        /// Converts a string to an HTML-encoded string.
        /// </summary>
        /// <param name="text"></param>
        /// A pointer to the text to encode.
        /// <param name="textLength">
        /// The length of the text to encode.
        /// </param>
        /// <returns>
        /// The HTML-encoded string.
        /// </returns>
        HCC_EXPORT WideString Encode( const wchar_t* text, size_t textLength );
        /// <summary>
        /// Converts a string that has been HTML-encoded for HTTP transmission into a decoded string.
        /// </summary>
        /// <param name="text"></param>
        /// A pointer to the text to decode.
        /// <param name="textLength">
        /// The length of the text to decode.
        /// </param>
        /// <returns>
        /// The HTML-decoded string.
        /// </returns>
        HCC_EXPORT WideString Decode( const wchar_t* text, size_t textLength );

        template<typename StringT>
            requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, std::wstring> || std::is_same_v<StringT, std::wstring_view>
        inline WideString Encode( const StringT& str )
        {
            if ( str.empty( ) == false )
            {
                return Encode( str.data( ), str.size( ) );
            }
            return {};
        }

        template<typename StringT>
            requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, std::wstring> || std::is_same_v<StringT, std::wstring_view>
        inline WideString Decode( const StringT& str )
        {
            if ( str.empty( ) == false )
            {
                return Decode( str.data( ), str.size( ) );
            }
            return {};
        }


        inline AnsiString Encode( const char* text, size_t textLength )
        {
            WideString ws;
            ToWideString( text, textLength, ws );
            auto encoded = Encode( ws );
            AnsiString result;
            ToAnsiString( encoded.c_str( ), encoded.size( ), result );
            return result;
        }
        inline AnsiString Decode( const char* text, size_t textLength )
        {
            WideString ws;
            ToWideString( text, textLength, ws );
            auto decoded = Decode( ws );
            AnsiString result;
            ToAnsiString( decoded.c_str( ), decoded.size( ), result );
            return result;
        }


        template<typename StringT>
            requires std::is_same_v<StringT, AnsiString> || std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::string_view>
        inline AnsiString Encode( const StringT& str )
        {
            if ( str.empty( ) == false )
            {
                return Encode( str.data( ), str.size( ) );
            }
            return {};
        }

        template<typename StringT>
            requires std::is_same_v<StringT, AnsiString> || std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::string_view>
        inline AnsiString Decode( const StringT& str )
        {
            if ( str.empty( ) == false )
            {
                return Decode( str.data( ), str.size( ) );
            }
            return {};
        }
    }

}

#ifdef HCC_WITH_BASIC_STRING
namespace std
{
    template<> struct hash<Harlinn::Common::Core::WideString>
    {
        std::size_t operator()( const Harlinn::Common::Core::WideString& s ) const noexcept
        {
            return s.Hash( );
        }
    };

    template<> struct hash<Harlinn::Common::Core::WideStringView>
    {
        std::size_t operator()( const Harlinn::Common::Core::WideStringView& s ) const noexcept
        {
            return s.Hash( );
        }
    };


    template<> struct hash<Harlinn::Common::Core::AnsiString>
    {
        std::size_t operator()( const Harlinn::Common::Core::AnsiString& s ) const noexcept
        {
            return s.Hash( );
        }
    };

    template<> struct hash<Harlinn::Common::Core::AnsiStringView>
    {
        std::size_t operator()( const Harlinn::Common::Core::AnsiStringView& s ) const noexcept
        {
            return s.Hash( );
        }
    };

    
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::BasicString<CharT>, CharT>
    {
        formatter<std::basic_string_view<CharT>, CharT> viewFormatter;
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return viewFormatter.parse( ctx );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::BasicString<CharT>& v, FormatContext& ctx ) const
        {
            basic_string_view<CharT> view( v.data( ), v.size( ) );
            return viewFormatter.format( view, ctx );
        }
    };
    
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::BasicStringView<CharT>, CharT>
    {
        formatter<std::basic_string_view<CharT>, CharT> viewFormatter;
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return viewFormatter.parse( ctx );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::BasicStringView<CharT>& view, FormatContext& ctx ) const
        {
            return viewFormatter.format( view, ctx );
        }
    };

}
#endif


#endif
