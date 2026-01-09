#pragma once
#ifndef __HCCSTRING_H__
#define __HCCSTRING_H__
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

#include <HCCDef.h>
#include <HCCTraits.h>
#include <Harlinn/Common/Concepts.h>
#include <HCCException.h>
#include <HCCIterator.h>



namespace Harlinn::Common::Core
{


    namespace Internal
    {
        inline char* AllocateBytes( size_t count )
        {
            auto result = ( char* )malloc( count );
            if ( !result )
            {
                ThrowOSError( E_OUTOFMEMORY );
            }
            return result;
        }
        inline void FreeBytes( char* bytes, size_t size )
        {
            if ( bytes )
            {
                free( bytes );
            }
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
    /// <para>
    /// Multiple BasicString instances may share the same internal buffer until a modifying operation requires
    /// uniqueness. Call <see cref="EnsureUnique"/> before obtaining raw pointers/iterators if you intend
    /// to mutate the contents while shared references may exist.
    /// </para>
    /// <para>
    /// There are potential pitfalls when this class is used in 
    /// a multi-threaded program, but they can easily be avoided:
    /// </para>
	/// <list type="number">
	///   <item>
    ///     <description>
    ///     There should be no problems as long as the strings 
    ///     are just passed around between threads. This is
    ///     the normal/most common use case.
    ///     </description>
    ///   </item>
    ///   <item>
    ///     <description>
    ///     Call EnsureUnique before changes are made using
    ///     character references, iterators and pointers to
    ///     the contents of a string. This will invalidate
    ///     existing references, iterators and pointers to
    ///     the contents of that string object, but not references,
    ///     iterators and pointers to other string objects that
    ///     originally shared the internal reference counted string
    ///     representation. Ideally the editing functions should
    ///     be used to change the contents of a string.
    ///     </description>
    ///   </item>
    ///   <item>
    ///     <description>
    ///     Never call an editing function using a reference
    ///     to a string object that is shared between threads.
    ///     Two string objects, each local to a separate thread,
    ///     may share the same internal data object, and this is
    ///     fine, but sharing a reference/pointer to a string object 
    ///     between threads is not OK when editing functions will 
    ///     be called. 
    ///     </description>
    ///   </item>
	/// </list>
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

        /// <summary>
        /// Computes the required allocation size in bytes for a buffer that can hold
        /// the specified number of characters plus the non-text buffer header.
        /// The returned byte count is rounded up to the nearest multiple of
        /// <see cref="AllocationGranularity"/>.
        /// </summary>
        /// <param name="length">The number of characters to allocate space for.</param>
        /// <returns>
        /// The number of bytes required for the allocation (including header and
        /// character storage), rounded up to the nearest allocation granularity.
        /// Returns 0 when <paramref name="length"/> is 0.
        /// </returns>
        /// <remarks>
        /// The calculation performed is:
        /// (NonTextBufferByteCount + length * sizeof(CharType)) rounded up to
        /// the next multiple of AllocationGranularity. Rounding is implemented by
        /// adding (AllocationGranularity - 1) and masking the low bits.
        /// Callers should ensure that the requested length does not exceed the
        /// limits exposed by <see cref="max_size"/> to avoid integer overflow.
        /// </remarks>
        static constexpr size_type AllocationByteCount( size_type length ) noexcept
        {
            return length ? ( ( NonTextBufferByteCount + length * sizeof( CharType ) ) + ( AllocationGranularity - 1 ) ) & ~( AllocationGranularity - 1 ) : 0;
        }


        /// <summary>
        /// Computes the number of bytes required to allocate an internal buffer that can hold
        /// a non-zero number of characters plus the non-text buffer header.
        /// </summary>
        /// <param name="length">The number of characters (must be non-zero) to allocate space for.</param>
        /// <returns>
        /// The total number of bytes required for the allocation (including the header and
        /// character storage), rounded up to the nearest multiple of <see cref="AllocationGranularity"/>.
        /// </returns>
        /// <remarks>
        /// The calculation performed is:
        /// (NonTextBufferByteCount + length * sizeof(CharType)) rounded up to the next multiple
        /// of AllocationGranularity. Rounding is implemented by adding (AllocationGranularity - 1)
        /// and clearing the lower bits via bitwise AND with the complement of (AllocationGranularity - 1).
        /// This function assumes <paramref name="length"/> is non-zero; for zero-length buffers callers
        /// should use AllocationByteCount which returns 0 for length == 0.
        /// </remarks>
        static constexpr size_type AllocationByteCountForLengthNotZero( size_type length ) noexcept
        {
            return ( ( NonTextBufferByteCount + length * sizeof( CharType ) ) + ( AllocationGranularity - 1 ) ) & ~( AllocationGranularity - 1 );
        }

        /// <summary>
        /// Allocates an internal <c>Data</c> object capable of holding <paramref name="size"/> characters
        /// plus the non-text buffer header. The allocation size in bytes is computed by
        /// <see cref="AllocationByteCount(size_t)"/> which rounds up to the internal
        /// allocation granularity.
        /// </summary>
        /// <param name="size">
        /// Number of characters to allocate for the string content. Must be greater than zero.
        /// </param>
        /// <returns>
        /// Pointer to a newly allocated <c>Data</c> instance. The returned object's <c>referenceCount_</c>
        /// is initialized to 1, <c>size_</c> is set to <paramref name="size"/>, and a terminating null
        /// character is written at <c>buffer_[size]</c>.
        /// </returns>
        /// <remarks>
        /// The allocation is performed via <see cref="Internal::AllocateBytes"/>, which wraps a raw memory
        /// allocation (malloc). Callers must release the returned <c>Data*</c> using the corresponding
        /// release routine (for example <see cref="ReleaseData"/>). In debug builds a zero size is considered
        /// a programming error and will trigger an <c>ArgumentOutOfRangeException</c> to surface the problem early.
        /// </remarks>
        /// <exception cref="ArgumentOutOfRangeException">Thrown in debug builds when <paramref name="size"/> is zero.</exception>
        /// <exception cref="...">
        /// If the underlying allocation fails, <c>Internal::AllocateBytes</c> will call <c>ThrowOSError</c> which 
        /// throws a platform-specific error exception.
        /// </exception>
        static Data* Allocate( size_t size )
        {
#ifdef _DEBUG
            if ( size == 0 )
            {
                throw ArgumentOutOfRangeException( L"size must be greater than zero" );
			}
#endif
            size_t allocationByteCount = AllocationByteCount( size );
            Data* data = (Data*)Internal::AllocateBytes( allocationByteCount );
            data->referenceCount_ = 1;
            data->size_ = size;
            data->buffer_[size] = 0;
            return data;
        }

        /// <summary>
        /// Allocates and initializes a new internal <c>Data</c> object using a precomputed
        /// allocation byte count.
        /// </summary>
        /// <param name="allocationByteCount">
        /// The exact number of bytes to allocate for the new <c>Data</c> instance. This value
        /// must include the non-text header size and the rounded character storage size
        /// (see <see cref="AllocationByteCountForLengthNotZero"/> and <see cref="AllocationByteCount"/>).
        /// The caller is responsible for computing this value.
        /// </param>
        /// <param name="size">
        /// The number of characters to store in the returned <c>Data</c>::buffer_. This value
        /// represents the logical character count (not bytes). In debug builds a zero value
        /// triggers an <c>ArgumentOutOfRangeException</c>.
        /// </param>
        /// <returns>
        /// Pointer to an initialized <c>Data</c> instance. The returned object's
        /// <c>referenceCount_</c> is set to 1, <c>size_</c> is set to <paramref name="size"/>,
        /// and a terminating null character is written at <c>buffer_[size]</c>.
        /// </returns>
        /// <remarks>
        /// - The function performs a raw memory allocation via <c>Internal::AllocateBytes</c>.
        /// - The caller must free the returned <c>Data*</c> by calling <see cref="ReleaseData"/>.
        /// - The <paramref name="allocationByteCount"/> must be consistent with
        ///   <paramref name="size"/>; mismatches may lead to buffer corruption.
        /// - This overload is used when the precise allocation size (in bytes) has already been
        ///   computed by the caller to avoid recalculation and to allow allocation granularity control.
        /// </remarks>
        /// <exception cref="ArgumentOutOfRangeException">
        /// Thrown in debug builds when <paramref name="size"/> is zero.
        /// </exception>
        /// <exception cref="...">
        /// If underlying allocation fails, <c>Internal::AllocateBytes</c> will call
        /// <c>ThrowOSError</c>, which throws a platform-specific error exception.
        /// </exception>
        static Data* Allocate( size_type allocationByteCount, size_t size )
        {
#ifdef _DEBUG
            if ( size == 0 )
            {
                throw ArgumentOutOfRangeException( L"size must be greater than zero" );
            }
#endif
            Data* data = ( Data* )Internal::AllocateBytes( allocationByteCount );
            data->referenceCount_ = 1;
            data->size_ = size;
            data->buffer_[ size ] = 0;
            return data;
        }

        /// <summary>
        /// Releases a reference-counted internal <c>Data</c> object and frees its memory when the
        /// last reference is released.
        /// </summary>
        /// <param name="data">
        /// Pointer to the <c>Data</c> instance to release. May be <c>nullptr</c>. If <c>nullptr</c>,
        /// the function returns immediately and no action is taken.
        /// </param>
        /// <remarks>
        /// <para>
        /// This routine decrements the reference count on the provided <c>Data</c> instance by calling
        /// <c>Data::DecRef()</c>. If the resulting reference count is zero the function computes the
        /// exact number of bytes that were originally allocated for this instance using
        /// <c>AllocationByteCountForLengthNotZero(data->size_)</c> and forwards the raw pointer and
        /// allocation size to <c>Internal::FreeBytes</c> to release the memory.
        /// </para>
        /// <para>
        /// The function is intended to be the single point that releases internally allocated
        /// string buffers and performs the corresponding raw memory free. It is safe to call from
        /// any thread, because <c>DecRef</c> uses interlocked operations. However, callers must
        /// ensure they do not access the memory pointed to by <paramref name="data"/> after the
        /// last reference has been released (i.e. when this function frees the memory).
        /// </para>
        /// </remarks>
        /// <exception cref="...">
        /// The routine itself does not throw. If underlying platform-specific routines used by
        /// <c>Internal::FreeBytes</c> were to signal errors, those are handled by the implementation
        /// of <c>Internal::FreeBytes</c>. Memory allocation failures are handled at allocation time
        /// (see <c>Internal::AllocateBytes</c>), not here.
        /// </exception>
        /// <seealso cref="AllocationByteCountForLengthNotZero(size_t)"/>
        /// <seealso cref="Internal::FreeBytes(char*, size_t)"/>
        static void ReleaseData( Data* data )
        {
            if ( data && data->DecRef( ) == 0 )
            {
                size_t allocationByteCount = AllocationByteCountForLengthNotZero( data->size_ );
                Internal::FreeBytes( (char*)data, allocationByteCount );
            }
        }


        /// <summary>
        /// Allocate a fresh internal buffer and create an insertion gap at the specified position.
        /// </summary>
        /// <param name="offset">
        /// Zero-based character index into the current buffer where the expansion (gap)
        /// should be created. All characters at and after <paramref name="offset"/> are
        /// moved so that the returned pointer points to the start of the new gap.
        /// </param>
        /// <param name="expandSize">
        /// Number of characters to insert (the size of the expansion gap). May be zero.
        /// </param>
        /// <returns>
        /// Pointer to the character position within the newly allocated buffer that
        /// corresponds to the insertion point (i.e. the start of the expansion gap).
        /// The returned pointer refers to memory owned by this BasicString instance and
        /// must not be freed by the caller.
        /// </returns>
        /// <remarks>
        /// <para>
        /// This routine always allocates a new <c>Data</c> instance that is large enough
        /// to hold the existing characters plus <paramref name="expandSize"/> additional
        /// characters. The contents before <paramref name="offset"/> are copied unchanged,
        /// and the trailing content starting at <paramref name="offset"/> is copied to
        /// begin at <c>offset + expandSize</c> in the new buffer, leaving a gap at
        /// <c>offset</c> for insertion.
        /// </para>
        /// <para>
        /// After successful allocation and copy the string takes ownership of the new
        /// buffer and releases the previous <c>Data</c> object (decrementing its
        /// reference count). The operation therefore produces a unique buffer for this
        /// BasicString instance.
        /// </para>
        /// <para>
        /// Thread-safety: the method is not synchronized; callers must ensure appropriate
        /// synchronization when multiple threads may access or modify the same
        /// BasicString instance concurrently. Producing a new buffer from a shared
        /// buffer is safe because it does not mutate other BasicString instances that
        /// reference the old data object.
        /// </para>
        /// </remarks>
        /// <exception cref="InvalidOperationException">
        /// In debug builds the method validates preconditions and may throw:
        /// <list type="bullet">
        ///   <item><description>When <c>data_ == nullptr</c>.</description></item>
        ///   <item><description>When the buffer is unique and the allocation already fits the expanded size
        ///   (caller should call <c>ExpandCurrentBuffer</c> instead).</description></item>
        /// </list>
        /// </exception>
        /// <exception cref="...">
        /// Allocation or low-level copy/move helpers may fail. Underlying helpers such as
        /// <c>Internal::AllocateBytes</c> will raise platform-specific exceptions (for
        /// example via <c>ThrowOSError</c>) when allocation fails.
        /// </exception>
        CharType* ExpandIntoNewBuffer( size_t offset, size_t expandSize )
        {
#ifdef _DEBUG
            if ( data_ == nullptr )
            {
                throw InvalidOperationException( L"data cannot be null" );
            }
            if ( data_->referenceCount_ == 1 )
            {
                auto allocatedByteCount = AllocationByteCountForLengthNotZero( data_->size_ );
                auto requiredByteCount = AllocationByteCountForLengthNotZero( data_->size_ + expandSize );
                if ( allocatedByteCount == requiredByteCount )
                {
                    throw InvalidOperationException( L"Call ExpandCurrentBuffer, not ExpandIntoNewBuffer" );
                }
            }
            
#endif
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


        
        /// <summary>
        /// Expands the current internal buffer in-place to create an insertion gap at a given position.
        /// </summary>
        /// <param name="offset">
        /// Zero-based character index into the current buffer where the expansion (gap) should be created.
        /// Characters at and after <paramref name="offset"/> are moved so that the returned pointer points
        /// to the start of the new gap. If <paramref name="offset"/> equals the current length the gap
        /// will be created at the end of the string.
        /// </param>
        /// <param name="expandSize">
        /// Number of characters to insert (the size of the expansion gap). May be zero.
        /// </param>
        /// <returns>
        /// Pointer to the character position within the internal buffer that corresponds to the insertion point.
        /// The returned pointer refers to memory owned by this BasicString instance and must not be freed by the caller.
        /// </returns>
        /// <remarks>
        /// <para>
        /// This routine modifies the existing buffer in-place and therefore requires that:
        /// </para>
        /// <list type="bullet">
        ///   <item><description>
        ///    The string currently owns a buffer (<c>data_ != nullptr</c>).
        ///   </description></item>
        ///   <item><description>
        ///     The buffer is unique (<c>data_->referenceCount_ == 1</c>) so no other BasicString 
        ///     instances share the same backing storage.
        ///   </description></item>
        ///   <item><description>
        ///     The existing allocation is large enough to accommodate the enlarged size; this 
        ///     function will not allocate memory. In debug builds this requirement is asserted 
        ///     and will throw if violated.
        ///   </description></item>
        /// </list>
        /// <para>
        /// The implementation shifts the trailing content starting at <paramref name="offset"/>
        /// right by <paramref name="expandSize"/> characters using <c>MemMove</c>, updates
        /// <c>data_->size_</c>, writes a terminating null character and returns a pointer
        /// to the insertion point.
        /// </para>
        /// <para>
        /// Thread-safety: the method is not synchronized. Callers must ensure appropriate
        /// synchronization when multiple threads may access or modify the same BasicString
        /// instance concurrently.
        /// </para>
        /// </remarks>
        /// <exception cref="InvalidOperationException">
        /// Thrown in debug builds when <c>data_ == nullptr</c>, when the buffer is not unique
        /// (<c>data_->referenceCount_ != 1</c>), or when the current allocation is insufficient
        /// to hold the expanded size (the function does not perform allocation).
        /// </exception>
        CharType* ExpandCurrentBuffer( size_t offset, size_t expandSize )
        {
#ifdef _DEBUG
            if ( data_ == nullptr )
            {
				throw InvalidOperationException( L"data_ cannot be null" );
            }
            if ( data_->referenceCount_ != 1 )
            {
                throw InvalidOperationException( L"Cannot expand current buffer when reference count is greater than 1" );
            }
			auto allocatedByteCount = AllocationByteCountForLengthNotZero( data_->size_ );
            auto requiredByteCount = AllocationByteCountForLengthNotZero( data_->size_ + expandSize );
            if ( allocatedByteCount < requiredByteCount )
            {
                throw InvalidOperationException( L"Cannot expand current buffer when allocation is insufficient" );
			}
#endif
            auto currentSize = data_->size_;
            auto remaining = currentSize - offset;
            MemMove( &data_->buffer_[offset + expandSize], &data_->buffer_[offset], remaining );
            data_->size_ += expandSize;
            data_->buffer_[data_->size_] = 0;
            return &data_->buffer_[offset];
        }

        
        /// <summary>
        /// Ensures space for an insertion of <paramref name="expandSize"/> characters at the specified <paramref name="offset"/>.
        /// </summary>
        /// <param name="offset">Zero-based index in the current string where the expansion (gap) should be created. If greater than the current length the behaviour is to allocate space and pad as required by callers.</param>
        /// <param name="expandSize">Number of characters to insert (the size of the expansion gap).</param>
        /// <returns>
        /// Pointer to the character position within the owned buffer that corresponds to the insertion point.
        /// The returned pointer points into memory owned by this BasicString instance and must not be freed by the caller.
        /// </returns>
        /// <remarks>
        /// <para>
        /// The method guarantees that after it returns the string owns a buffer large enough to accommodate the
        /// requested expansion. The implementation chooses one of three strategies:
        /// </para>
        /// <list type="bullet">
        ///   <item><description>If the string has no internal data (<c>data_ == nullptr</c>) a new buffer is allocated sized to <paramref name="expandSize"/> and the pointer to the start of the buffer is returned.</description></item>
        ///   <item><description>If the buffer is shared (<c>data_->referenceCount_ &gt; 1</c>) a fresh buffer large enough for the new size is allocated and the existing content is copied; the string then owns the new unique buffer.</description></item>
        ///   <item><description>When the buffer is unique and the internal allocation already covers the enlarged size the function expands the buffer in-place; otherwise it allocates a new buffer and copies the data.</description></item>
        /// </list>
        /// <para>
        /// Callers that hold raw pointers/iterators into the string must call <c>EnsureUnique()</c> or avoid reusing those references
        /// since this operation may replace the internal buffer and invalidate pointers into the old buffer.
        /// </para>
        /// <para>
        /// Thread-safety: the function is not synchronized; callers must ensure appropriate synchronization when multiple threads
        /// may modify the same BasicString instance concurrently. Producing a unique buffer from a shared buffer is safe because
        /// it does not mutate other BasicString instances that reference the old data object.
        /// </para>
        /// </remarks>
        /// <exception cref="...">
        /// Underlying allocation may fail; allocation helpers (for example <c>Internal::AllocateBytes</c>) will call platform-specific
        /// error routines such as <c>ThrowOSError</c> which will throw. Copy operations use <c>MemCopy</c>/<c>MemMove</c> and will
        /// propagate platform-specific errors if they occur.
        /// </exception>
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

        /// <summary>
        /// Allocate a new internal buffer and extend the current content by <paramref name="extendSize"/> characters.
        /// </summary>
        /// <param name="extendSize">Number of characters to append space for. May be zero.</param>
        /// <returns>
        /// Pointer to the first newly available character position (i.e. the old end of the string)
        /// inside the newly allocated buffer. The returned pointer refers to memory owned by this
        /// BasicString instance and must not be freed by the caller.
        /// </returns>
        /// <remarks>
        /// <para>
        /// This routine always allocates a new <c>Data</c> instance capable of holding the existing
        /// characters plus <paramref name="extendSize"/> additional characters. The existing content
        /// is copied to the start of the new buffer. After the copy the string takes ownership of the
        /// new buffer and releases the previous <c>Data</c> object (decrementing its reference count).
        /// </para>
        /// <para>
        /// Thread-safety: the method is not synchronized. Callers must ensure appropriate synchronization
        /// when multiple threads may access or modify the same BasicString instance concurrently.
        /// Producing a new buffer from a shared buffer is safe because it does not mutate other
        /// BasicString instances that reference the old data object.
        /// </para>
        /// </remarks>
        /// <exception cref="InvalidOperationException">
        /// In debug builds the method validates preconditions and may throw when <c>data_ == nullptr</c>.
        /// </exception>
        CharType* ExtendIntoNewBuffer( size_t extendSize )
        {
#ifdef _DEBUG
            if ( data_ == nullptr )
            {
                throw InvalidOperationException( L"data cannot be null" );
            }
            if ( data_->referenceCount_ == 1 )
            {
                auto allocatedByteCount = AllocationByteCountForLengthNotZero( data_->size_ );
                auto requiredByteCount = AllocationByteCountForLengthNotZero( data_->size_ + extendSize );
                if ( allocatedByteCount == requiredByteCount )
                {
                    throw InvalidOperationException( L"Call ExtendCurrentBuffer, not ExtendIntoNewBuffer" );
                }
            }

#endif

            auto currentSize = data_->size_;
            auto newSize = currentSize + extendSize;
            auto newData = Allocate( newSize );
            MemCopy( newData->buffer_, data_->buffer_, currentSize );
            auto* tmp = data_;
            data_ = newData;
            ReleaseData( tmp );
            return &newData->buffer_[currentSize];
        }

        /// <summary>
        /// Extends the current internal buffer in-place by the specified number of characters and
        /// returns a pointer to the first newly available character position.
        /// </summary>
        /// <param name="extendSize">
        /// The number of characters to append to the existing buffer. May be zero.
        /// </param>
        /// <returns>
        /// A pointer to the first character of the appended region (i.e. the previous end of the string).
        /// The returned pointer refers to memory owned by this BasicString instance and must not be freed.
        /// </returns>
        /// <remarks>
        /// <para>
        /// This operation does not allocate a new buffer. It updates the existing buffer in-place and thus
        /// requires unique ownership and sufficient capacity. If the current allocation cannot accommodate
        /// the extended size, callers should use editing operations that trigger reallocation
        /// (e.g. <see cref="ExtendIntoNewBuffer(size_t)"/> or <see cref="Extend(size_t)"/>).
        /// </para>
        /// <list type="bullet">
        ///   <item>
        ///     <description>
        ///       Ensures the buffer is uniquely owned (<c>data_->referenceCount_ == 1</c>).
        ///     </description>
        ///   </item>
        ///   <item>
        ///     <description>
        ///       Validates that the rounded allocation size computed via
        ///       <see cref="AllocationByteCountForLengthNotZero(size_t)"/> for <c>size_ + extendSize</c>
        ///       does not exceed the current allocation.
        ///     </description>
        ///   </item>
        /// </list>
        /// <para>
        /// After extending, the method updates <c>size_</c> and writes a trailing null terminator at
        /// <c>buffer_[size_]</c>. As this may invalidate previously obtained end-iterators, callers
        /// should reacquire iterators or raw pointers after the call.
        /// </para>
        /// <para>
        /// Thread-safety: not synchronized. If multiple threads can modify the same instance,
        /// external synchronization is required.
        /// </para>
        /// </remarks>
        /// <exception cref="InvalidOperationException">
        /// Thrown in debug builds when:
        /// <list type="bullet">
        ///   <item><description><c>data_ == nullptr</c></description></item>
        ///   <item><description><c>data_->referenceCount_ != 1</c> (buffer is shared)</description></item>
        ///   <item><description>Current allocation is insufficient for the requested extension</description></item>
        /// </list>
        /// </exception>
        CharType* ExtendCurrentBuffer( size_t extendSize )
        {
#ifdef _DEBUG
            if ( data_ == nullptr )
            {
                throw InvalidOperationException( L"data_ cannot be null" );
            }
            if ( data_->referenceCount_ != 1 )
            {
                throw InvalidOperationException( L"Cannot extend current buffer when reference count is greater than 1" );
            }
            auto allocatedByteCount = AllocationByteCountForLengthNotZero( data_->size_ );
            auto requiredByteCount = AllocationByteCountForLengthNotZero( data_->size_ + extendSize );
            if ( allocatedByteCount < requiredByteCount )
            {
                throw InvalidOperationException( L"Cannot extend current buffer when allocation is insufficient" );
            }
#endif

            auto currentSize = data_->size_;
            data_->size_ += extendSize;
            data_->buffer_[data_->size_] = 0;
            return &data_->buffer_[currentSize];
        }

        /// <summary>
        /// Extend the current internal buffer in-place by <paramref name="extendSize"/> characters
        /// and return a pointer to the first newly available character position.
        /// </summary>
        /// <param name="extendSize">Number of characters to append (may be zero).</param>
        /// <returns>
        /// Pointer to the first character of the appended region (i.e. the previous end of string).
        /// The returned pointer refers to memory owned by this BasicString instance and must not be freed by the caller.
        /// </returns>
        /// <remarks>
        /// <para>
        /// This routine updates the existing buffer in-place and therefore does not allocate memory.
        /// Callers must ensure the following preconditions are met before calling this method:
        /// </para>
        /// <list type="bullet">
        ///   <item><description>
        ///     <c>data_ != nullptr</c> (there is an existing buffer)
        ///   </description></item>
        ///   <item><description>
        ///     The buffer is uniquely owned (<c>data_->referenceCount_ == 1</c>).
        ///   </description></item>
        ///   <item><description>
        ///     The existing allocation already covers the enlarged size (no allocation required).
        ///   </description></item>
        /// </list>
        /// <para>
        /// The implementation increments <c>data_->size_</c>, writes a terminating null character and
        /// returns a pointer to the first appended character.
        /// </para>
        /// <para>
        /// Thread-safety: this method is not synchronized. Callers must ensure appropriate synchronization
        /// if multiple threads may access or modify the same BasicString instance concurrently.
        /// </para>
        /// </remarks>
        /// <exception cref="InvalidOperationException">
        /// In debug builds thrown when any of the preconditions are violated:
        /// <list type="bullet">
        ///   <item><description><c>data_ == nullptr</c></description></item>
        ///   <item><description><c>data_->referenceCount_ != 1</c> (buffer is shared)</description></item>
        ///   <item><description>Current allocation is insufficient for the requested extension</description></item>
        /// </list>
        /// </exception>
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


        /// <summary>
        /// Validates that the provided iterator refers to a position inside this string's valid range.
        /// </summary>
        /// <param name="position">
        /// A <c>const_iterator</c> pointing into this string. The function verifies that
        /// <c>position</c> is not before <c>begin()</c> and is strictly less than <c>end()</c>.
        /// For an empty string the iterator is expected to be <c>nullptr</c>.
        /// </param>
        /// <remarks>
        /// <para>
        /// The function performs pointer comparisons against the internal buffer and does not
        /// dereference <c>position.ptr_</c>. It is intended as a debug-time range validator
        /// for public APIs that accept iterators; callers should ensure the iterator originates
        /// from this string instance.
        /// </para>
        /// <para>
        /// Thread-safety: this routine is not synchronized. Callers must provide external
        /// synchronization if multiple threads may access or modify the same BasicString instance.
        /// </para>
        /// </remarks>
        /// <exception cref="std::out_of_range">
        /// Thrown when the string is empty and <c>position.ptr_ != nullptr</c>, when
        /// <c>position.ptr_ &lt; begin()</c>, or when <c>position.ptr_ &gt;= end()</c>.
        /// </exception>
        void RangeCheck( const_iterator position )
        {
            if ( data_ )
            {
                if ( position.ptr_ < data_->buffer_ )
                {
                    throw std::out_of_range( "position < begin()" );
                }
                auto currentSize = data_->size_;
                if ( position.ptr_ >= &data_->buffer_[ currentSize ] )
                {
                    throw std::out_of_range( "position >= end()" );
                }
            }
            else
            {
				// In this case position is considered to point to beginning of an empty string.
                if ( position.ptr_ != nullptr )
                {
                    throw std::out_of_range( "string is empty" );
                }
            }
        }


        /// <summary>
        /// Erases a region of characters from the string starting at <paramref name="offset"/>.
        /// </summary>
        /// <param name="offset">
        /// Zero-based index of the first character to erase. If <paramref name="offset"/> is
        /// greater than or equal to the current string length the call is a no-op and returns
        /// a pointer to the end of the string.
        /// </param>
        /// <param name="numberOfCharactersToErase">
        /// Number of characters to remove beginning at <paramref name="offset"/>. If the sum
        /// of <paramref name="offset"/> and this value exceeds the current length the erase
        /// length is clamped to the available characters.
        /// </param>
        /// <returns>
        /// If characters remain after the erase, returns a pointer to the character in the
        /// (possibly updated) internal buffer that now occupies the original <paramref name="offset"/>.
        /// If the erase removes the entire contents the function releases internal storage and
        /// returns <c>nullptr</c>. If <paramref name="offset"/> is past the end a pointer to the
        /// current end of string is returned. If there is no data to operate on the function
        /// returns <c>nullptr</c>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// The function chooses between two strategies:
        /// </para>
        /// <list type="bullet">
        ///   <item>
        ///     <description>
        ///       In-place removal: when the buffer is uniquely owned (<c>data_->referenceCount_ == 1</c>)
        ///       and the allocation size computed by <see cref="AllocationByteCountForLengthNotZero"/>
        ///       does not change for the new logical length, the trailing content is shifted left
        ///       using <c>MemMove</c> and <c>data_->size_</c> is updated.
        ///     </description>
        ///   </item>
        ///   <item>
        ///     <description>
        ///       Reallocation: when the buffer is shared or the rounded allocation changes, a new
        ///       <c>Data</c> buffer is allocated, the preserved prefix and suffix copied into it,
        ///       the previous data object is released and the new buffer becomes owned by this string.
        ///     </description>
        ///   </item>
        /// </list>
        /// <para>
        /// When the erase results in an empty string the internal buffer is released and the
        /// stored pointer is set to <c>nullptr</c>.
        /// </para>
        /// <para>
        /// Thread-safety: this method is not synchronized. Callers must ensure exclusive access
        /// when modifying the same BasicString instance from multiple threads.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// If the underlying memory allocation fails, <c>Internal::AllocateBytes</c> (used by <see cref="Allocate(size_t)"/>) calls <c>ThrowOSError</c>,
        /// which throws a SystemException exception.
        /// </exception>
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
                                MemMove( dest, dest + numberOfCharactersToErase, remainingSize );
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


        
        /// <summary>
        /// Allocates and initializes a new internal <c>Data</c> buffer by copying exactly
        /// <paramref name="size"/> characters from <paramref name="string"/>.
        /// </summary>
        /// <param name="string">
        /// Pointer to the source character sequence to copy. The source is not required to be null-terminated;
        /// exactly <paramref name="size"/> characters are copied.
        /// </param>
        /// <param name="size">
        /// The number of characters to copy from <paramref name="string"/>. When zero, the function returns <c>nullptr</c>.
        /// </param>
        /// <returns>
        /// A pointer to a newly allocated <c>Data</c> instance with <c>referenceCount_ == 1</c>, <c>size_ == size</c>,
        /// and a trailing null character written at <c>buffer_[size]</c>. Returns <c>nullptr</c> when <paramref name="size"/> is zero.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Allocation is performed via <see cref="Allocate(size_t)"/> which rounds the allocation size to the internal
        ///   granularity and ensures a terminating null at <c>buffer_[size]</c>.
        /// </para>
        /// <para>
        /// - Use this initializer when the exact character count is known and the input may not be null-terminated.
        ///   For null-terminated input, consider the overload that infers the length automatically.
        /// </para>
        /// <para>
        /// - This function is frequently used by constructors and assignment helpers in <c>BasicString</c> to
        ///   produce uniquely owned buffers that adhere to the class invariants. Prefer these higher-level APIs
        ///   over raw buffer manipulation.
        /// </para>
        /// <para>
        /// Thread-safety: not synchronized. Callers must ensure appropriate synchronization when multiple threads may
        /// access or modify the same <c>BasicString</c> instance concurrently.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// If the underlying memory allocation fails, <c>Internal::AllocateBytes</c> (used by <see cref="Allocate(size_t)"/>) calls <c>ThrowOSError</c>,
        /// which throws a SystemException exception.
        /// </exception>
        static Data* Initialize( const CharType* string, size_type size )
        {
            if ( size )
            {
                Data* data = Allocate( size );
                MemCopyOrZero( data->buffer_, string, size );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        /// <summary>
        /// Allocates and initializes a new internal <c>Data</c> buffer by concatenating two character sequences.
        /// </summary>
        /// <param name="string1">Pointer to the first source character sequence.</param>
        /// <param name="size1">Number of characters to copy from <paramref name="string1"/>.</param>
        /// <param name="string2">Pointer to the second source character sequence.</param>
        /// <param name="size2">Number of characters to copy from <paramref name="string2"/>.</param>
        /// <returns>
        /// Pointer to a newly allocated <c>Data</c> instance containing the concatenation of the two sequences.
        /// Returns <c>nullptr</c> if the total size is zero.
        /// </returns>
        /// <remarks>
        /// Allocation is performed via <see cref="Allocate(size_t)"/> and writes a trailing null at <c>buffer_[size]</c>.
        /// </remarks>
        /// <exception cref="SystemException">
        /// If the underlying memory allocation fails, <c>Internal::AllocateBytes</c> (used by <see cref="Allocate(size_t)"/>) calls <c>ThrowOSError</c>,
        /// which throws a SystemException exception.
        /// </exception>
        static Data* Initialize( const CharType* string1, size_type size1, const CharType* string2, size_type size2 )
        {
            auto size = size1 + size2;
            if ( size )
            {
                Data* data = Allocate( size );
                MemCopyOrZero( data->buffer_, string1, size1 );
                MemCopyOrZero( data->buffer_ + size1, string2, size2 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        /// <summary>
        /// Allocates and initializes a new internal <c>Data</c> buffer by filling a leading region with a repeated character value
        /// followed by copying exactly <paramref name="size2"/> characters from <paramref name="string2"/>.
        /// </summary>
        /// <param name="value">
        /// The character value to repeat for the leading region.
        /// </param>
        /// <param name="count">
        /// The number of times <paramref name="value"/> is written at the start of the buffer. May be zero.
        /// </param>
        /// <param name="string2">
        /// Pointer to the trailing source character sequence to copy. The source is not required to be null-terminated;
        /// exactly <paramref name="size2"/> characters are copied.
        /// </param>
        /// <param name="size2">
        /// The number of characters to copy from <paramref name="string2"/>. May be zero.
        /// </param>
        /// <returns>
        /// A pointer to a newly allocated <c>Data</c> instance with <c>referenceCount_ == 1</c>, <c>size_ == count + size2</c>,
        /// and a trailing null character written at <c>buffer_[count + size2]</c>. Returns <c>nullptr</c> when the total size is zero.
        /// </returns>
        /// <remarks>
        /// <para>
        /// Allocation is performed via <see cref="Allocate(size_t)"/> which rounds the allocation size to the internal granularity and ensures a terminating null.
        /// </para>
        /// <para>
        /// The contents are written in order: first <paramref name="count"/> repetitions of <paramref name="value"/>,
        /// then <paramref name="size2"/> characters copied from <paramref name="string2"/>.
        /// </para>
        /// <para>
        /// This initializer is commonly used by constructors and editing helpers in <c>BasicString</c> when building a string
        /// from a repeated character followed by a provided sequence.
        /// </para>
        /// <para>
        /// Thread-safety: not synchronized. Callers must ensure appropriate synchronization if multiple threads may access or modify the same instance.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// If the underlying memory allocation fails, <c>Internal::AllocateBytes</c> (used by <see cref="Allocate(size_t)"/>) calls <c>ThrowOSError</c>,
        /// which throws a SystemException exception.
        /// </exception>
        static Data* Initialize( CharType value, size_type count, const CharType* string2, size_type size2 )
        {
            auto size = count + size2;
            if ( size )
            {
                Data* data = Allocate( size );
                MemSet( data->buffer_, value, count );
                MemCopyOrZero( data->buffer_ + count, string2, size2 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        /// <summary>
        /// Create and initialize a new internal <c>Data</c> buffer by copying a prefix and filling a suffix with a repeated character.
        /// </summary>
        /// <param name="string1">
        /// Pointer to the prefix characters to copy. May be <c>nullptr</c> only when <paramref name="size1"/> is zero.
        /// </param>
        /// <param name="size1">Number of characters to copy from <paramref name="string1"/>.</param>
        /// <param name="value">Character value that will be repeated to fill the suffix.</param>
        /// <param name="count">Number of times <paramref name="value"/> is written after the copied prefix.</param>
        /// <returns>
        /// Pointer to a newly allocated <c>Data</c> instance whose <c>referenceCount_</c> is initialized to 1
        /// and whose <c>buffer_</c> contains the concatenation of the copied prefix followed by <paramref name="count"/> repetitions
        /// of <paramref name="value"/>. Returns <c>nullptr</c> when the total length (<paramref name="size1"/> + <paramref name="count"/>) is zero.
        /// </returns>
        /// <remarks>
        /// - Allocation is performed via <see cref="Allocate(size_t)"/> which rounds the allocation size to the internal granularity
        ///   and writes a terminating null at <c>buffer_[size]</c>.
        /// - The caller is responsible for releasing the returned <c>Data*</c> using <see cref="ReleaseData"/>.
        /// - The function copies exactly <paramref name="size1"/> characters from <paramref name="string1"/> and writes exactly
        ///   <paramref name="count"/> repetitions of <paramref name="value"/>; neither source is required to be null-terminated.
        /// </remarks>
        /// <exception cref="...">Underlying allocation helpers (for example <c>Internal::AllocateBytes</c>) may throw on failure.</exception>
        static Data* Initialize( const CharType* string1, size_type size1, CharType value, size_type count )
        {
            auto size = size1 + count;
            if ( size )
            {
                Data* data = Allocate( size );
                MemCopyOrZero( data->buffer_, string1, size1 );
                MemSet( data->buffer_ + size1, value, count );
                return data;
            }
            else
            {
                return nullptr;
            }
        }



        /// <summary>
        /// Create and initialize a new internal <c>Data</c> buffer by concatenating three character sequences.
        /// </summary>
        /// <param name="string1">Pointer to the first source character sequence. May be <c>nullptr</c> only when <paramref name="size1"/> is zero.</param>
        /// <param name="size1">Number of characters to copy from <paramref name="string1"/>.</param>
        /// <param name="string2">Pointer to the second source character sequence. May be <c>nullptr</c> only when <paramref name="size2"/> is zero.</param>
        /// <param name="size2">Number of characters to copy from <paramref name="string2"/>.</param>
        /// <param name="string3">Pointer to the third source character sequence. May be <c>nullptr</c> only when <paramref name="size3"/> is zero.</param>
        /// <param name="size3">Number of characters to copy from <paramref name="string3"/>.</param>
        /// <returns>
        /// Pointer to a newly allocated <c>Data</c> instance whose <c>referenceCount_</c> is initialized to 1
        /// and whose <c>buffer_</c> contains the concatenation of the provided sequences.
        /// Returns <c>nullptr</c> when the total length (<paramref name="size1"/> + <paramref name="size2"/> + <paramref name="size3"/>) is zero.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Allocation is performed via <see cref="Allocate(size_t)"/> which rounds the allocation size
        ///   to the internal granularity and writes a terminating null at <c>buffer_[size]</c>.
        /// - The contents are copied in order: first <paramref name="string1"/> (length <paramref name="size1"/>),
        ///   then <paramref name="string2"/> (length <paramref name="size2"/>), then <paramref name="string3"/> (length <paramref name="size3"/>).
        /// - The function copies exactly the specified lengths; none of the sources are required to be null-terminated.
        /// - The caller is responsible for releasing the returned <c>Data*</c> using <see cref="ReleaseData"/>.
        /// </para>
        /// <para>
        /// Thread-safety: the routine itself is not synchronized; callers must ensure appropriate synchronization
        /// if multiple threads may access or modify the same BasicString instance.
        /// </para>
        /// </remarks>
        /// <exception cref="...">Underlying allocation helpers (for example <c>Internal::AllocateBytes</c>) may throw on failure.</exception>
        static Data* Initialize( const CharType* string1, size_type size1, const CharType* string2, size_type size2, const CharType* string3, size_type size3 )
        {
            auto size = size1 + size2 + size3;
            if ( size )
            {
                Data* data = Allocate( size );
                MemCopyOrZero( data->buffer_, string1, size1 );
                MemCopyOrZero( data->buffer_ + size1, string2, size2 );
                MemCopyOrZero( data->buffer_ + size1 + size2, string3, size3 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        /// <summary>
        /// Create and initialize a new internal <c>Data</c> buffer by filling a leading region
        /// with a repeated character and then appending two provided character sequences.
        /// </summary>
        /// <param name="value">Character to repeat for the leading region.</param>
        /// <param name="count">Number of times <paramref name="value"/> is written at the start of the buffer.</param>
        /// <param name="string2">Pointer to the second source character sequence. May be <c>nullptr</c> only when <paramref name="size2"/> is zero.</param>
        /// <param name="size2">Number of characters to copy from <paramref name="string2"/>.</param>
        /// <param name="string3">Pointer to the third source character sequence. May be <c>nullptr</c> only when <paramref name="size3"/> is zero.</param>
        /// <param name="size3">Number of characters to copy from <paramref name="string3"/>.</param>
        /// <returns>
        /// Pointer to a newly allocated <c>Data</c> instance whose <c>referenceCount_</c> is initialized to 1
        /// and whose <c>buffer_</c> contains <paramref name="count"/> repetitions of <paramref name="value"/>
        /// followed by the characters copied from <paramref name="string2"/> and <paramref name="string3"/>.
        /// Returns <c>nullptr</c> when the total length (<paramref name="count"/> + <paramref name="size2"/> + <paramref name="size3"/>) is zero.
        /// </returns>
        /// <remarks>
        /// <list type="bullet">
        ///   <item>
        ///     <description>
        ///       Allocation is performed via <see cref="Allocate(size_t)"/>, which rounds the allocation size
        ///       to the internal granularity and writes a terminating null at <c>buffer_[size]</c>.
        ///     </description>
        ///   </item>
        ///   <item>
        ///     <description>
        ///       The contents are written in order:
        ///       first the repeated <paramref name="value"/> (count times),
        ///       then <paramref name="string2"/> (<paramref name="size2"/> characters),
        ///       then <paramref name="string3"/> (<paramref name="size3"/> characters).
        ///     </description>
        ///   </item>
        ///   <item>
        ///     <description>
        ///       The function copies exactly the specified lengths; none of the sources are required to be null-terminated.
        ///     </description>
        ///   </item>
        ///   <item>
        ///     <description>
        ///       The caller is responsible for releasing the returned <c>Data*</c> using <see cref="ReleaseData"/>.
        ///     </description>
        ///   </item>
        /// </list>
        /// <para>
        /// Thread-safety: the routine itself is not synchronized; callers must ensure appropriate synchronization
        /// if multiple threads may access or modify the same BasicString instance.
        /// </para>
        /// </remarks>
        /// <exception cref="...">Underlying allocation helpers (for example <c>Internal::AllocateBytes</c>) may throw on failure.</exception>
        static Data* Initialize( CharType value, size_type count, const CharType* string2, size_type size2, const CharType* string3, size_type size3 )
        {
            auto size = count + size2 + size3;
            if ( size )
            {
                Data* data = Allocate( size );
                MemSet( data->buffer_, value, count );
                MemCopyOrZero( data->buffer_ + count, string2, size2 );
                MemCopyOrZero( data->buffer_ + count + size2, string3, size3 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }


        /// <summary>
        /// Create and initialize a new internal <c>Data</c> buffer by copying a prefix,
        /// filling a middle region with a repeated character value, and then copying a suffix.
        /// </summary>
        /// <param name="string1">
        /// Pointer to the prefix characters to copy. May be <c>nullptr</c> only when <paramref name="size1"/> is zero.
        /// The function copies exactly <paramref name="size1"/> characters from this pointer; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size1">
        /// Number of characters to copy from <paramref name="string1"/>.
        /// </param>
        /// <param name="value">
        /// Character value that will be repeated in the middle region.
        /// </param>
        /// <param name="count">
        /// Number of times <paramref name="value"/> is written after the prefix.
        /// </param>
        /// <param name="string3">
        /// Pointer to the suffix characters to copy. May be <c>nullptr</c> only when <paramref name="size3"/> is zero.
        /// The function copies exactly <paramref name="size3"/> characters from this pointer; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size3">
        /// Number of characters to copy from <paramref name="string3"/>.
        /// </param>
        /// <returns>
        /// Pointer to a newly allocated <c>Data</c> instance whose <c>referenceCount_</c> is initialized to 1
        /// and whose <c>buffer_</c> contains the concatenation: prefix (size1) + repeated value (count) + suffix (size3).
        /// Returns <c>nullptr</c> when the total length (<paramref name="size1"/> + <paramref name="count"/> + <paramref name="size3"/>) is zero.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Allocation is performed via <see cref="Allocate(size_t)"/> which rounds the allocation size
        ///   to the internal granularity and writes a terminating null at <c>buffer_[size]</c>.
        /// - The contents are written in order: first the copied prefix, then exactly <paramref name="count"/>
        ///   repetitions of <paramref name="value"/>, then the copied suffix. Exact lengths are used; no null-termination
        ///   is assumed for the input pointers.
        /// - The caller is responsible for releasing the returned <c>Data*</c> using <see cref="ReleaseData"/>.
        /// </para>
        /// <para>
        /// Thread-safety: the routine itself is not synchronized; callers must ensure appropriate synchronization
        /// if multiple threads may access or modify the same BasicString instance.
        /// </para>
        /// </remarks>
        /// <exception cref="...">
        /// Underlying allocation helpers (for example <c>Internal::AllocateBytes</c>) may throw platform-specific
        /// exceptions (for example via <c>ThrowOSError</c>) on allocation failure.
        /// </exception>
        static Data* Initialize( const CharType* string1, size_type size1, CharType value, size_type count, const CharType* string3, size_type size3 )
        {
            auto size = size1 + count + size3;
            if ( size )
            {
                Data* data = Allocate( size );
                MemCopyOrZero( data->buffer_, string1, size1 );
                MemSet( data->buffer_ + size1, value, count );
                MemCopyOrZero( data->buffer_ + size1 + count, string3, size3 );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        /// <summary>
        /// Create and initialize a new internal <c>Data</c> buffer by copying a prefix,
        /// copying a middle sequence and then filling a trailing region with a repeated character.
        /// </summary>
        /// <param name="string1">
        /// Pointer to the prefix characters to copy. May be <c>nullptr</c> only when <paramref name="size1"/> is zero.
        /// The function copies exactly <paramref name="size1"/> characters; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size1">Number of characters to copy from <paramref name="string1"/>.</param>
        /// <param name="string2">
        /// Pointer to the middle characters to copy. May be <c>nullptr</c> only when <paramref name="size2"/> is zero.
        /// The function copies exactly <paramref name="size2"/> characters; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size2">Number of characters to copy from <paramref name="string2"/>.</param>
        /// <param name="value">Character value that will be repeated to fill the suffix (trailing region).</param>
        /// <param name="count">Number of times <paramref name="value"/> is written after the copied prefix and middle sequence.</param>
        /// <returns>
        /// Pointer to a newly allocated <c>Data</c> instance with <c>referenceCount_</c> == 1 and
        /// <c>buffer_</c> containing: prefix (size1) + middle (size2) + repeated value (count).
        /// Returns <c>nullptr</c> when total length (<paramref name="size1"/> + <paramref name="size2"/> + <paramref name="count"/>) is zero.
        /// </returns>
        /// <remarks>
        /// <para>Allocation is performed via <see cref="Allocate(size_t)"/>, which rounds the allocation size to the internal granularity
        /// and writes a terminating null at <c>buffer_[size]</c>.</para>
        /// <para>The contents are written in order and exact lengths are used; no null-termination is assumed for the input pointers.</para>
        /// <para>The caller is responsible for releasing the returned <c>Data*</c> using <see cref="ReleaseData"/>.</para>
        /// </remarks>
        /// <exception cref="...">Underlying allocation helpers (for example <c>Internal::AllocateBytes</c>) may throw on allocation failure.</exception>
        static Data* Initialize( const CharType* string1, size_type size1, const CharType* string2, size_type size2, CharType value, size_type count )
        {
            auto size = size1 + size2 + count;
            if ( size )
            {
                Data* data = Allocate( size );
                MemCopyOrZero( data->buffer_, string1, size1 );
                MemCopyOrZero( data->buffer_ + size1, string2, size2 );
                MemSet( data->buffer_ + size1 + size2, value, count );
                return data;
            }
            else
            {
                return nullptr;
            }
        }


        /// <summary>
        /// Allocates and initializes a new internal <c>Data</c> buffer by copying characters from the input range [<paramref name="first"/>, <paramref name="last"/>).
        /// </summary>
        /// <typeparam name="InputIt">
        /// An input iterator type denoting the source range. The iterator's value_type must be convertible to <c>CharType</c>.
        /// </typeparam>
        /// <param name="first">Iterator to the first element in the source range to copy.</param>
        /// <param name="last">Iterator one past the last element in the source range to copy.</param>
        /// <returns>
        /// A pointer to a newly allocated <c>Data</c> instance with <c>referenceCount_ == 1</c>, <c>size_ == std::distance(first, last)</c>,
        /// and a trailing null character written at <c>buffer_[size]</c>. Returns <c>nullptr</c> when the range is empty.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The function computes the number of elements using <c>std::distance</c>, allocates storage via <see cref="Allocate(size_t)"/>,
        ///   and copies the range into the destination using <c>std::copy</c>.
        /// </para>
        /// <para>
        /// - Use this initializer when constructing a <c>BasicString</c> from iterator ranges, e.g. containers, pointer ranges, or custom iterators.
        /// </para>
        /// <para>
        /// - Allocation size is rounded internally based on the string's allocation granularity.
        /// </para>
        /// <para>
        /// - Prefer Harlinn.Common.Core string facilities over raw C-style APIs to maintain consistent memory management and safety guarantees.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// If the underlying memory allocation fails, <c>Internal::AllocateBytes</c> (used by <see cref="Allocate(size_t)"/>) calls <c>ThrowOSError</c>,
        /// which throws a platform-specific error.
        /// </exception>
        template<typename InputIt>
			requires std::is_convertible_v<typename std::iterator_traits<InputIt>::value_type, CharType> && 
                std::forward_iterator<InputIt>
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

        /// <summary>
        /// Initializes a new internal <c>Data</c> buffer by copying characters from a single-pass input iterator range.
        /// </summary>
        /// <typeparam name="InputIt">An input iterator type whose <c>value_type</c> is convertible to <c>CharType</c>.</typeparam>
        /// <param name="first">Iterator to the first element in the source range.</param>
        /// <param name="last">Iterator one past the last element in the source range.</param>
        /// <returns>
        /// Pointer to a newly allocated <c>Data</c> instance containing the copied characters.
        /// Returns <c>nullptr</c> when the range is empty.
        /// </returns>
        /// <remarks>
        /// This overload handles single-pass input iterators (non-forward). It accumulates elements into a temporary
        /// contiguous buffer and then allocates the final internal <c>Data</c> object sized to the exact element count.
        /// </remarks>
        template<typename InputIt>
            requires std::is_convertible_v<typename std::iterator_traits<InputIt>::value_type, CharType>&&
                (std::forward_iterator<InputIt> == false) && std::input_iterator<InputIt>
        static Data* Initialize( InputIt first, InputIt last )
        {
			boost::container::small_vector<CharType, 256> temp;
            for ( ; first != last; ++first )
            {
                temp.push_back( static_cast<CharType>( *first ) );
            }

            if ( temp.empty( ) )
            {
                return nullptr;
            }

            size_type size = static_cast<size_type>( temp.size( ) );
            Data* data = Allocate( size );
            MemCopy( data->buffer_, temp.data( ), size );
            return data;
        }

        /// <summary>
        /// Initializes a new internal Data buffer from a null-terminated character sequence.
        /// </summary>
        /// <param name="string">
        /// Pointer to a null-terminated character sequence of type <see cref="CharType"/>.
        /// The pointer may be <c>nullptr</c>; in that case the computed length is zero and the
        /// function returns <c>nullptr</c>.
        /// </param>
        /// <returns>
        /// A pointer to a newly allocated <c>Data</c> instance whose <c>buffer_</c> contains
        /// a copy of the input characters (excluding the terminating null), <c>size_</c> equals
        /// the number of characters copied, and a trailing null is written at <c>buffer_[size_]</c>.
        /// Returns <c>nullptr</c> if the input string length is zero.
        /// </returns>
        /// <remarks>
        /// <para>
        /// The length of the input is computed using <c>Common::Internal::LengthOf</c>, which
        /// measures characters (not bytes) for the current <see cref="CharType"/>.
        /// The allocation is performed via <see cref="Allocate(size_type)"/> ensuring the buffer
        /// adheres to the internal allocation granularity and terminator invariants.
        /// </para>
        /// <para>
        /// Prefer higher-level constructors of <see cref="BasicString{T}"/> when building string
        /// instances from null-terminated inputs, which internally call this helper to maintain
        /// consistent memory management using the Harlinn.Common.Core facilities rather than
        /// raw C-style APIs.
        /// </para>
        /// <exception cref="SystemException">
        /// If memory allocation fails, underlying helpers will call <c>ThrowOSError</c> which
        /// throws a platform-specific error exception.
        /// </exception>
        /// <seealso cref="Initialize(const CharType*, size_type)"/>
        /// <seealso cref="BasicString{T}::BasicString(const CharType*)"/>
        static Data* Initialize( const CharType* string )
        {

            auto size = Common::Internal::LengthOf( string );
            return Initialize( string, size );
        }


        /// <summary>
        /// Allocates and initializes a new internal <c>Data</c> buffer filled with a repeated character value.
        /// </summary>
        /// <param name="count">
        /// The number of characters to write into the buffer. When zero, the function returns <c>nullptr</c>.
        /// </param>
        /// <param name="value">
        /// The character value to repeat across the newly allocated buffer.
        /// </param>
        /// <returns>
        /// A pointer to a newly allocated <c>Data</c> instance with <c>referenceCount_ == 1</c>,
        /// <c>size_ == count</c>, and a trailing null terminator written at <c>buffer_[count]</c>.
        /// Returns <c>nullptr</c> when <paramref name="count"/> is zero.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Allocation is performed via <see cref="Allocate(size_t)"/> which rounds the allocation size to the internal
        ///   granularity and ensures a trailing terminator at <c>buffer_[count]</c>.
        /// </para>
        /// <para>
        /// - The buffer content is written using <c>MemSet</c> and is not dependent on any locale. For wide strings,
        ///   this repeats the specified <paramref name="value"/> as <c>wchar_t</c> elements.
        /// </para>
        /// <para>
        /// - Prefer higher-level `BasicString` constructors and editing methods when building strings from repeated
        ///   characters to maintain consistent ownership and safety guarantees provided by Harlinn.Common.Core.
        /// </para>
        /// <example>
        /// <code>
        /// // Create an internal Data buffer for 10 asterisks
        /// auto* data = Initialize(10, static_cast<CharType>('*'));
        /// </code>
        /// </example>
        /// <exception cref="SystemException">
        /// If the underlying memory allocation fails, <c>Internal::AllocateBytes</c> (used by <see cref="Allocate(size_t)"/>) calls <c>ThrowOSError</c>,
        /// which throws a platform-specific error.
        /// </exception>
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

        /// <summary>
        /// Constructs a <see cref="BasicString{T}"/> that references an existing internal <c>Data</c> buffer.
        /// </summary>
        /// <param name="data">
        /// Pointer to an existing <c>Data</c> instance that holds the string content. May be <c>nullptr</c>.
        /// When non-null, the pointer is stored and may be shared among multiple <c>BasicString</c> instances.
        /// </param>
        /// <param name="addRef">
        /// When <c>true</c> and <paramref name="data"/> is non-null, increments the internal reference count
        /// via <c>Data::AddRef()</c>. When <c>false</c>, the constructor assumes ownership was already accounted for
        /// by the caller and does not modify the reference count.
        /// </param>
        /// <remarks>
        /// <para>
        /// This constructor enables efficient creation of string objects that share the same backing storage.
        /// Reference counting is used to manage the lifetime of the internal buffer. Use <see cref="EnsureUnique"/>
        /// before mutating through raw pointers, references, or iterators if other shared references may exist.
        /// </para>
        /// <para>
        /// Prefer using higher-level APIs in Harlinn.Common.Core (e.g., constructors from character ranges,
        /// <see cref="Initialize(const CharType*, size_type)"/>, and editing functions) over raw C-style manipulation
        /// to maintain consistent ownership and safety guarantees. For Windows-related text processing, use facilities
        /// from Harlinn.Windows; for numeric/string conversions or formatting consider Harlinn.Common.Core helpers
        /// and Harlinn.Math where applicable.
        /// </para>
        /// </remarks>
        BasicString( Data* data, bool addRef = true ) noexcept
            : data_( data )
        {
            if ( addRef && data )
            {
                data->AddRef( );
            }
        }
    public:
        
        /// <summary>
        /// Initializes a new empty instance of <see cref="BasicString{T}"/>.
        /// </summary>
        /// <remarks>
        /// <para>
        /// The constructed string has no internal data; <c>data_</c> is set to <c>nullptr</c>, and
        /// methods that depend on existing content will behave as operating on an empty string.
        /// </para>
        /// <para>
        /// To populate the string, use constructors that accept character pointers, spans, or other
        /// string objects, or call editing methods like <see cref="Append"/> and <see cref="Insert"/>.
        /// </para>
        /// <para>
        /// When building applications, prefer the high-level facilities provided by the Harlinn.Common.Core
        /// library (e.g., string conversions and formatting) rather than raw C-style APIs to ensure consistent
        /// memory management, performance, and safety in Windows environments.
        /// </para>
        /// </remarks>
        constexpr BasicString( ) noexcept
            : data_( nullptr )
        {
        }

        /// <summary>
        /// Initializes a new instance of <see cref="BasicString{T}"/> from a null-terminated character sequence.
        /// </summary>
        /// <param name="string">
        /// Pointer to a null-terminated character buffer of type <see cref="CharType"/>.
        /// May be <c>nullptr</c>. When the computed length is zero the constructed string is empty.
        /// </param>
        /// <remarks>
        /// <para>
        /// The constructor delegates to <see cref="Initialize(const CharType*)"/> which computes the input length,
        /// allocates the internal buffer using the class allocation granularity, copies the characters excluding
        /// the terminating null, and ensures a trailing null terminator in the internal storage.
        /// </para>
        /// <para>
        /// Multiple <see cref="BasicString{T}"/> instances may share the same internal buffer via reference counting
        /// when constructed through other APIs. This constructor produces a uniquely owned buffer.
        /// Use <see cref="EnsureUnique"/> before mutating through raw pointers/iterators if other shared references may exist.
        /// </para>
        /// <para>
        /// Prefer Harlinn.Common.Core string facilities over raw C-style APIs for Windows applications.
        /// For conversions between ANSI and Wide strings use <see cref="Internal::From(const wchar_t*, size_t, unsigned, unsigned)"/>
        /// and <see cref="Internal::From(const char*, size_t, unsigned, unsigned)"/> or the respective <c>From</c> helpers on this type.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// If memory allocation fails, underlying helpers may call <c>ThrowOSError</c> which throws a SystemException.
        /// </exception>
        BasicString( const CharType* string )
            : data_( Initialize( string ) )
        {
        }

        /// <summary>
        /// Initializes a new instance of <see cref="BasicString{T}"/> from a character buffer and an explicit length.
        /// </summary>
        /// <param name="string">
        /// Pointer to the source character buffer. The buffer is not required to be null-terminated; exactly
        /// <paramref name="size"/> characters are copied.
        /// </param>
        /// <param name="size">
        /// The number of characters to copy from <paramref name="string"/> into the newly allocated internal buffer.
        /// When zero, the constructed string will be empty.
        /// </param>
        /// <returns>
        /// A <see cref="BasicString{T}"/> that uniquely owns its internal buffer. The internal buffer is terminated
        /// with a null character at index <c>size</c>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// This constructor delegates to <see cref="Initialize(const CharType*, size_type)"/> which allocates a buffer
        /// sized according to the string's internal allocation granularity, copies exactly <paramref name="size"/> characters,
        /// and writes a trailing null terminator. The resulting instance has a reference count of one on the internal data.
        /// </para>
        /// <para>
        /// Prefer using high-level facilities in Harlinn.Common.Core for subsequent editing and manipulation instead of
        /// raw C-style APIs. For Windows-specific text handling and conversions consider Harlinn.Windows utilities; for
        /// formatting and numeric conversions see helpers in Harlinn.Common.Core and Harlinn.Math.
        /// </para>
        /// <exception cref="SystemException">
        /// Allocation failures propagate via <c>ThrowOSError</c> invoked by the underlying allocator.
        /// </exception>
        BasicString( const CharType* string, size_type size )
            : data_( Initialize( string, size ) )
        {
        }

        /// <summary>
        /// Initializes a new instance of <c>BasicString&lt;T&gt;</c> by concatenating two character sequences.
        /// </summary>
        /// <param name="string1">
        /// Pointer to the first character sequence. May be <c>nullptr</c> only when <paramref name="size1"/> is zero.
        /// The source is not required to be null-terminated; exactly <paramref name="size1"/> characters are copied.
        /// </param>
        /// <param name="size1">
        /// Number of characters to copy from <paramref name="string1"/>. May be zero.
        /// </param>
        /// <param name="string2">
        /// Pointer to the second character sequence. May be <c>nullptr</c> only when <paramref name="size2"/> is zero.
        /// The source is not required to be null-terminated; exactly <paramref name="size2"/> characters are copied.
        /// </param>
        /// <param name="size2">
        /// Number of characters to copy from <paramref name="string2"/>. May be zero.
        /// </param>
        /// <remarks>
        /// <para>
        /// This constructor allocates a uniquely owned internal buffer large enough to hold
        /// <paramref name="size1"/> + <paramref name="size2"/> characters, copies the contents of the two
        /// sequences in order, and writes a trailing null terminator at the end of the internal buffer.
        /// </para>
        /// <para>
        /// The allocation and initialization are delegated to <see cref="Initialize(const CharType*, size_type, const CharType*, size_type)"/>,
        /// which adheres to the allocation granularity policy of <c>BasicString&lt;T&gt;</c>.
        /// </para>
        /// <para>
        /// Prefer higher-level editing APIs (e.g., <c>Append</c>, <c>Insert</c>, <c>Replace</c>) from Harlinn.Common.Core
        /// when composing strings incrementally, and consider conversion helpers in this header to interoperate with
        /// Windows text encodings instead of raw Win32 APIs.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails. Allocation helpers invoke platform-specific error routines.
        /// </exception>
        /// <example>
        /// <code>
        /// using namespace Harlinn::Common::Core;
        /// AnsiString a("foo", 3, "bar", 3);          // Produces "foobar"
        /// WideString w(L"hello", 5, L" world", 6);   // Produces "hello world"
        /// </code>
        /// </example>
        BasicString( const CharType* string1, size_type size1, const CharType* string2, size_type size2 )
            : data_( Initialize( string1, size1, string2, size2 ) )
        {
        }

        /// <summary>
        /// Initializes a new instance of <see cref="BasicString{T}"/> by creating an internal buffer that
        /// contains <paramref name="count"/> repetitions of <paramref name="value"/> followed by the characters
        /// copied from <paramref name="string2"/> (exactly <paramref name="size2"/> characters).
        /// </summary>
        /// <param name="value">The character to repeat at the start of the new string.</param>
        /// <param name="count">The number of times <paramref name="value"/> is written at the beginning of the buffer. May be zero.</param>
        /// <param name="string2">
        /// Pointer to the trailing character sequence to append. May be <c>nullptr</c> only when <paramref name="size2"/> is zero.
        /// The function copies exactly <paramref name="size2"/> characters from this pointer; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size2">Number of characters to copy from <paramref name="string2"/>. May be zero.</param>
        /// <remarks>
        /// <para>
        /// This constructor delegates to the internal <see cref="Initialize(CharType, size_type, const CharType*, size_type)"/> helper
        /// which performs allocation according to the string class allocation granularity and writes a trailing null terminator.
        /// </para>
        /// <para>
        /// When the total length (<paramref name="count"/> + <paramref name="size2"/>) is zero the constructed string is empty.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails. Allocation helpers will propagate platform-specific errors.
        /// </exception>
        /// <example>
        /// <code>
        /// // Create a string that begins with five asterisks followed by "hello"
        /// BasicString<char> s( '*', 5, "hello", 5 ); // produces "*****hello"
        /// </code>
        /// </example>
        BasicString( CharType value, size_type count, const CharType* string2, size_type size2 )
            : data_( Initialize( value, count, string2, size2 ) )
        {
        }

        /// <summary>
        /// Initializes a new instance of <see cref="BasicString{T}"/> by copying a prefix and then appending a repeated character value.
        /// </summary>
        /// <param name="string1">Pointer to the prefix characters to copy. May be <c>nullptr</c> only when <paramref name="size1"/> is zero.</param>
        /// <param name="size1">Number of characters to copy from <paramref name="string1"/>. May be zero.</param>
        /// <param name="value">The character value to repeat after the copied prefix.</param>
        /// <param name="count">Number of times <paramref name="value"/> is written after the copied prefix. May be zero.</param>
        /// <remarks>
        /// <para>
        /// The constructor delegates to the internal <see cref="Initialize(const CharType*, size_type, CharType, size_type)"/> helper which
        /// allocates a uniquely owned internal buffer sized according to the string's allocation granularity, copies the prefix and fills the suffix
        /// with <paramref name="count"/> repetitions of <paramref name="value"/>, and ensures a trailing null terminator.
        /// </para>
        /// <para>
        /// If the total length (<paramref name="size1"/> + <paramref name="count"/>) is zero the constructed string is empty and no internal buffer is allocated.
        /// </para>
        /// <para>
        /// Callers should prefer the higher-level Harlinn.Common.Core facilities for conversions and editing where applicable.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if underlying memory allocation fails; allocation helpers will propagate platform-specific errors (for example via <c>ThrowOSError</c>).
        /// </exception>
        BasicString( const CharType* string1, size_type size1, CharType value, size_type count )
            : data_( Initialize( string1, size1, value, count ) )
        {
        }

        /// <summary>
        /// Constructs a <see cref="BasicString{T}"/> by copying the contents of two contiguous containers.
        /// </summary>
        /// <param name="span1">
        /// The first contiguous container whose <c>value_type</c> must be identical to the string's <c>CharType</c>.
        /// The elements from <paramref name="span1"/> are copied into the newly allocated internal buffer as the leading segment.
        /// </param>
        /// <param name="span2">
        /// The second contiguous container whose <c>value_type</c> must be identical to the string's <c>CharType</c>.
        /// The elements from <paramref name="span2"/> are copied and appended after the contents of <paramref name="span1"/>.
        /// </param>
        /// <remarks>
        /// <para>
        /// This constructor is constrained at compile time to accept only contiguous container-like types whose element
        /// type matches <c>CharType</c> (enforced by the template <c>requires</c> clause).
        /// The contents are copied using the internal <see cref="Initialize(const CharType*, size_type, const CharType*, size_type)"/>
        /// helper which allocates a uniquely owned internal <c>Data</c> buffer. After construction the resulting
        /// <see cref="BasicString{T}"/> owns its buffer and has a reference count of one.
        /// </para>
        /// <para>
        /// Allocation follows the string class allocation granularity. Callers that hold raw pointers or iterators into
        /// other string instances should call <see cref="EnsureUnique"/> before performing mutations to avoid invalidating
        /// references that may originate from shared buffers.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when the underlying memory allocation fails during initialization (propagated from the internal allocator).
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view a = "Hello";
        /// std::string_view b = " World";
        /// BasicString<char> s( a, b ); // produces "Hello World"
        /// </code>
        /// </example>
        /// <seealso cref="Initialize(const CharType*, size_type, const CharType*, size_type)"/>
        template<ContiguousContainerLike SpanT1, ContiguousContainerLike SpanT2>
            requires (std::is_same_v<typename SpanT1::value_type, CharType> && std::is_same_v<typename SpanT2::value_type, CharType> )
        BasicString( const SpanT1& span1, const SpanT2& span2 )
            : data_( Initialize( span1.data( ), span1.size( ), span2.data( ), span2.size( ) ) )
        {
        }

        /// <summary>
        /// Initializes a new instance of <see cref="BasicString{CharType}"/> by copying the contents of a contiguous container
        /// followed by a specified number of characters from a raw character pointer.
        /// </summary>
        /// <param name="span1">
        /// A contiguous container whose <c>value_type</c> is identical to this string's <c>CharType</c>.
        /// The elements in <paramref name="span1"/> are copied into the newly allocated internal buffer as the leading segment.
        /// </param>
        /// <param name="string2">
        /// Pointer to the second character sequence to append after <paramref name="span1"/>. May be <c>nullptr</c> only when
        /// <paramref name="size2"/> is zero. The source is not required to be null-terminated; exactly <paramref name="size2"/>
        /// characters are copied.
        /// </param>
        /// <param name="size2">
        /// The number of characters to copy from <paramref name="string2"/>. May be zero.
        /// </param>
        /// <remarks>
        /// <para>
        /// The constructor delegates to the internal <c>Initialize(const CharType*, size_type, const CharType*, size_type)</c>
        /// helper which performs allocation according to the string's allocation granularity, copies the two sequences in order,
        /// and ensures a trailing null terminator. When the total length (<c>span1.size() + size2</c>) is zero the constructed
        /// string is empty and no internal buffer is allocated.
        /// </para>
        /// <para>
        /// The template is constrained to contiguous container-like types (see <c>ContiguousContainerLike</c>) and requires
        /// <c>std::is_same_v<typename SpanT::value_type, CharType></c>.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails. Allocation helpers propagate platform-specific errors.
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view a = "Hello";
        /// BasicString<char> s( a, " world", 6 ); // produces "Hello world"
        /// </code>
        /// </example>
        template<ContiguousContainerLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        BasicString( const SpanT& span1, const CharType* string2, size_type size2 )
            : data_( Initialize( span1.data( ), span1.size( ), string2, size2 ) )
        {
        }

        /// <summary>
        /// Constructs a new <see cref="BasicString{T}"/> by copying exactly <paramref name="size1"/> characters from
        /// the raw character pointer <paramref name="string1"/> and then appending the contents of
        /// <paramref name="span2"/>. The resulting instance owns a uniquely allocated internal buffer sized to
        /// hold the concatenation (rounded according to the class allocation granularity).
        /// </summary>
        /// <param name="string1">
        /// Pointer to the first input character sequence. May be <c>nullptr</c> only when <paramref name="size1"/> is zero.
        /// The pointer is not required to be null-terminated; exactly <paramref name="size1"/> characters are copied.
        /// </param>
        /// <param name="size1">
        /// The number of characters to copy from <paramref name="string1"/>. When zero, no characters are copied from the pointer.
        /// </param>
        /// <param name="span2">
        /// A contiguous container-like object whose <c>value_type</c> is identical to this string's character type.
        /// The elements in <paramref name="span2"/> are appended after the characters copied from <paramref name="string1"/>.
        /// </param>
        /// <remarks>
        /// The constructor delegates initialization to the internal <see cref="Initialize(const CharType*, size_type, const CharType*, size_type)"/>
        /// helper which performs allocation using the string's allocation granularity and writes a terminating null character.
        /// If the total length ( <paramref name="size1"/> + <c>span2.size()</c> ) is zero the constructed string will be empty
        /// and no internal buffer is allocated. Callers should prefer higher-level editing APIs when composing strings incrementally.
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails. Allocation helpers will propagate platform-specific errors (for example via ThrowOSError).
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view suffix = " world";
        /// BasicString<char> s( "Hello", 5, suffix ); // produces "Hello world"
        /// </code>
        /// </example>
        /// <seealso cref="Initialize(const CharType*, size_type, const CharType*, size_type)"/>
        template<ContiguousContainerLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        BasicString( const CharType* string1, size_type size1, const SpanT& span2 )
            : data_( Initialize( string1, size1, span2.data( ), span2.size( ) ) )
        {
        }

        /// <summary>
        /// Constructs a new <see cref="BasicString{CharType}"/> by creating an internal buffer that
        /// contains <paramref name="count"/> repetitions of <paramref name="value"/> followed by the
        /// elements from <paramref name="span"/>.
        /// </summary>
        /// <param name="value">The character to repeat at the start of the new string.</param>
        /// <param name="count">
        /// The number of times <paramref name="value"/> is written at the beginning of the buffer.
        /// May be zero; when the total resulting length is zero the constructed string will be empty.
        /// </param>
        /// <param name="span">
        /// A contiguous container-like object whose <c>value_type</c> is identical to this string's
        /// character type. The elements in <paramref name="span"/> are appended after the repeated values.
        /// </param>
        /// <remarks>
        /// <para>
        /// The constructor delegates to the internal <c>Initialize(CharType, size_type, const CharType*, size_type)</c>
        /// helper which performs allocation according to the string's internal allocation granularity,
        /// writes the repeated characters, copies the contents of <paramref name="span"/>, and ensures a
        /// trailing null terminator in the internal buffer.
        /// </para>
        /// <para>
        /// Thread-safety: this constructor is not synchronized. If multiple threads access the same source
        /// container concurrently, external synchronization is required. After construction the resulting
        /// BasicString owns its buffer and has a reference count of one.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails. Allocation helpers will propagate platform-specific errors
        /// (for example via <c>ThrowOSError</c>).
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view suffix = "hello";
        /// BasicString<char> s( '*', 5, suffix ); // produces "*****hello"
        /// </code>
        /// </example>
        /// <seealso cref="Initialize(CharType,size_type,const CharType*,size_type)"/>
        template<ContiguousContainerLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        BasicString( CharType value, size_type count, const SpanT& span )
            : data_( Initialize( value, count, span.data( ), span.size( ) ) )
        {
        }

        /// <summary>
        /// Initializes a new <see cref="BasicString{CharType}"/> by prepending a single character value
        /// and then copying the contents of a contiguous container-like span.
        /// </summary>
        /// <param name="value">The character to write as the first character of the new string.</param>
        /// <param name="span">A contiguous container-like object whose element type must match <c>CharType</c>.
        /// The elements of <paramref name="span"/> are copied and appended after <paramref name="value"/>.</param>
        /// <remarks>
        /// <para>
        /// The constructor delegates to the internal <c>Initialize(CharType, size_type, const CharType*, size_type)</c>
        /// helper which allocates a uniquely owned internal buffer sized according to the class allocation granularity,
        /// writes the leading character, copies the span content and ensures a trailing null terminator.
        /// </para>
        /// <para>
        /// Allocation follows the string class allocation granularity. If memory allocation fails the underlying
        /// allocation helper will signal a platform-specific error (for example by calling <c>ThrowOSError</c>).
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when underlying memory allocation fails during initialization.
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view suffix = "world";
        /// BasicString<char> s( '*', suffix ); // produces "*world"
        /// </code>
        /// </example>
        /// <seealso cref="Initialize(CharType,size_type,const CharType*,size_type)"/>
        template<ContiguousContainerLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        BasicString( CharType value, const SpanT& span )
            : data_( Initialize( value, 1, span.data( ), span.size( ) ) )
        {
        }

        /// <summary>
        /// Constructs a new instance of <see cref="BasicString"/> by copying the contents of a contiguous container
        /// and then appending a repeated character value.
        /// </summary>
        /// <param name="span">
        /// A contiguous container-like object whose <c>value_type</c> is identical to this string's character type.
        /// The elements in <paramref name="span"/> are copied into the newly allocated internal buffer as the leading segment.
        /// </param>
        /// <param name="value">
        /// The character value to append after the contents of <paramref name="span"/>.
        /// </param>
        /// <param name="count">
        /// Number of times <paramref name="value"/> is written after the copied <paramref name="span"/>.
        /// May be zero; when the total resulting length is zero the constructed string will be empty.
        /// </param>
        /// <remarks>
        /// <para>
        /// The constructor delegates to the internal <see cref="Initialize(CharType,size_type,CharType,size_type)"/> helper
        /// which performs allocation according to the string's allocation granularity, copies the span content and fills the suffix
        /// with <paramref name="count"/> repetitions of <paramref name="value"/>, and ensures a trailing null terminator.
        /// </para>
        /// <para>
        /// The template constraint enforces at compile time that the element type of <paramref name="span"/> matches the
        /// string's character type (<c>CharType</c>).
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when underlying memory allocation fails during initialization. Allocation helpers will propagate platform-specific errors.
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view suffix = "hello";
        /// BasicString<char> s( suffix, '*', 5 ); // produces "hello*****"
        /// </code>
        /// </example>
        template<ContiguousContainerLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        BasicString( const SpanT& span, CharType value, size_type count )
            : data_( Initialize( span.data( ), span.size( ), value, count ) )
        {
        }

        /// <summary>
        /// Constructs a new instance of <see cref="BasicString{CharType}"/> by prepending a single character
        /// and then copying the contents of a contiguous container-like span.
        /// </summary>
        /// <param name="span">
        /// A contiguous container-like object whose element type must match <c>CharType</c>.
        /// The elements of <paramref name="span"/> are copied and appended after <paramref name="value"/>.
        /// </param>
        /// <param name="value">
        /// The character to write as the first character of the new string.
        /// </param>
        /// <remarks>
        /// <para>
        /// The constructor delegates to the internal <c>Initialize(CharType, size_type, const CharType*, size_type)</c>
        /// helper which allocates a uniquely owned internal buffer sized according to the class allocation granularity,
        /// writes the leading character, copies the span content and ensures a trailing null terminator.
        /// </para>
        /// <para>
        /// If the total resulting length is zero the constructed string will be empty and no internal buffer is allocated.
        /// Use Harlinn.Common.Core conversion and editing helpers where possible to preserve ownership semantics.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code>
        /// std::string_view suffix = "world";
        /// BasicString<char> s( '*', suffix ); // produces "*world"
        /// </code>
        /// </example>
        /// <seealso cref="Initialize(CharType, size_type, const CharType*, size_type)"/>
        template<ContiguousContainerLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, CharType>
        BasicString( const SpanT& span, CharType value )
            : data_( Initialize( span.data( ), span.size( ), value, 1 ) )
        {
        }


        /// <summary>
        /// Constructs a new <see cref="BasicString{T}"/> by concatenating three character sequences.
        /// </summary>
        /// <param name="string1">
        /// Pointer to the first character sequence to copy. May be <c>nullptr</c> only when <paramref name="size1"/> is zero.
        /// The function copies exactly <paramref name="size1"/> characters from this pointer; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size1">
        /// The number of characters to copy from <paramref name="string1"/>. May be zero.
        /// </param>
        /// <param name="string2">
        /// Pointer to the second character sequence to copy. May be <c>nullptr</c> only when <paramref name="size2"/> is zero.
        /// The function copies exactly <paramref name="size2"/> characters from this pointer; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size2">
        /// The number of characters to copy from <paramref name="string2"/>. May be zero.
        /// </param>
        /// <param name="string3">
        /// Pointer to the third character sequence to copy. May be <c>nullptr</c> only when <paramref name="size3"/> is zero.
        /// The function copies exactly <paramref name="size3"/> characters from this pointer; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size3">
        /// The number of characters to copy from <paramref name="string3"/>. May be zero.
        /// </param>
        /// <remarks>
        /// This constructor delegates to the internal <see cref="Initialize(const CharType*, size_type, const CharType*, size_type, const CharType*, size_type)"/>
        /// helper which performs allocation according to the string class allocation granularity, copies the provided sequences in order,
        /// and ensures a trailing null terminator. When the total resulting length ( <paramref name="size1"/> + <paramref name="size2"/> + <paramref name="size3"/> )
        /// is zero the constructed string will be empty and no internal buffer is allocated.
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when underlying memory allocation fails. Allocation helpers will propagate platform-specific errors (for example via <c>ThrowOSError</c>).
        /// </exception>
        /// <example>
        /// <code>
        /// // Construct a BasicString<char> containing "hello:world!"
        /// BasicString<char> s( "hello", 5, ":", 1, "world!", 6 );
        /// </code>
        /// </example>
        /// <seealso cref="Initialize(const CharType*, size_type, const CharType*, size_type, const CharType*, size_type)"/>
        BasicString( const CharType* string1, size_type size1, const CharType* string2, size_type size2, const CharType* string3, size_type size3 )
            : data_( Initialize( string1, size1, string2, size2, string3, size3 ) )
        {
        }

        /// <summary>
        /// Constructs a new <see cref="BasicString{T}"/> by creating an internal buffer that
        /// contains <paramref name="count"/> repetitions of <paramref name="value"/> followed by the
        /// characters copied from <paramref name="string2"/> (exactly <paramref name="size2"/> characters)
        /// and then the characters copied from <paramref name="string3"/> (exactly <paramref name="size3"/> characters).
        /// </summary>
        /// <param name="value">The character to repeat for the leading region of the new string.</param>
        /// <param name="count">Number of times <paramref name="value"/> is written at the beginning of the buffer. May be zero.</param>
        /// <param name="string2">
        /// Pointer to the second source character sequence to append after the repeated values.
        /// May be <c>nullptr</c> only when <paramref name="size2"/> is zero.
        /// </param>
        /// <param name="size2">Number of characters to copy from <paramref name="string2"/>. May be zero.</param>
        /// <param name="string3">
        /// Pointer to the third source character sequence to append after <paramref name="string2"/>.
        /// May be <c>nullptr</c> only when <paramref name="size3"/> is zero.
        /// </param>
        /// <param name="size3">Number of characters to copy from <paramref name="string3"/>. May be zero.</param>
        /// <remarks>
        /// <para>
        /// The constructor delegates to the internal <see cref="Initialize(CharType,size_type,const CharType*,size_type,const CharType*,size_type)"/>
        /// helper which performs allocation according to the string class allocation granularity
        /// and writes a trailing null terminator. The resulting instance uniquely owns its internal
        /// buffer and has a reference count of one when allocation succeeds.
        /// </para>
        /// <para>
        /// Thread-safety: this constructor is not synchronized. Callers should provide external
        /// synchronization if multiple threads access the same source buffers concurrently.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when underlying memory allocation fails. Underlying allocation helpers will
        /// call platform-specific error routines (for example via <c>ThrowOSError</c>).
        /// </exception>
        /// <exception cref="ArgumentOutOfRangeException">
        /// In debug builds thrown if an internal size check fails (for example when a zero-size
        /// allocation is considered invalid by the allocator helpers).
        /// </exception>
        /// <example>
        /// <code>
        /// // Create a string that begins with five asterisks followed by "hello" and then " world"
        /// BasicString<char> s( '*', 5, "hello", 5, " world", 6 ); // produces "*****hello world"
        /// </code>
        /// </example>
        BasicString( CharType value, size_type count, const CharType* string2, size_type size2, const CharType* string3, size_type size3 )
            : data_( Initialize( value, count, string2, size2, string3, size3 ) )
        {
        }

        /// <summary>
        /// Constructs a new instance of <c>BasicString&lt;CharType&gt;</c> by copying a leading prefix,
        /// inserting a repeated character sequence, and appending a trailing suffix.
        /// </summary>
        /// <param name="string1">
        /// Pointer to the prefix characters to copy. May be <c>nullptr</c> only when <paramref name="size1"/> is zero.
        /// The function copies exactly <paramref name="size1"/> characters from this pointer; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size1">
        /// The number of characters to copy from <paramref name="string1"/>. May be zero.
        /// </param>
        /// <param name="value">
        /// The character value that will be repeated in the middle region.
        /// </param>
        /// <param name="count">
        /// Number of times <paramref name="value"/> is written after the copied prefix. May be zero.
        /// </param>
        /// <param name="string3">
        /// Pointer to the suffix characters to copy. May be <c>nullptr</c> only when <paramref name="size3"/> is zero.
        /// The function copies exactly <paramref name="size3"/> characters from this pointer; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size3">
        /// Number of characters to copy from <paramref name="string3"/>. May be zero.
        /// </param>
        /// <remarks>
        /// This constructor delegates allocation and initialization to the internal
        /// <see cref="Initialize(const CharType*, size_type, CharType, size_type, const CharType*, size_type)"/> helper.
        /// The helper performs allocation according to the string class allocation granularity,
        /// writes the prefix, fills the repeated character region and copies the suffix, and ensures
        /// a trailing null terminator. The resulting instance uniquely owns its internal buffer
        /// and has reference count one when allocation succeeds.
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when underlying memory allocation fails. Allocation helpers will propagate platform-specific errors.
        /// </exception>
        /// <example>
        /// <para>Example usage:</para>
        /// <code>
        /// // Produces "pre*****post"
        /// BasicString<char> s( "pre", 3, '*', 5, "post", 4 );
        /// </code>
        /// </example>
        /// <seealso cref="Initialize(const CharType*, size_type, CharType, size_type, const CharType*, size_type)"/>
        BasicString( const CharType* string1, size_type size1, CharType value, size_type count, const CharType* string3, size_type size3 )
            : data_( Initialize( string1, size1, value, count, string3, size3 ) )
        {
        }

        /// <summary>
        /// Constructs a new <see cref="BasicString{CharType}"/> by copying a leading character sequence,
        /// appending a repeated character value, and then copying a trailing character sequence.
        /// </summary>
        /// <param name="string1">
        /// Pointer to the first (prefix) character sequence to copy. May be <c>nullptr</c> only when
        /// <paramref name="size1"/> is zero. Exactly <paramref name="size1"/> characters are copied; the
        /// source is not required to be null-terminated.
        /// </param>
        /// <param name="size1">
        /// Number of characters to copy from <paramref name="string1"/>. May be zero.
        /// </param>
        /// <param name="string2">
        /// Pointer to the trailing character sequence to copy. May be <c>nullptr</c> only when
        /// <paramref name="size2"/> is zero. Exactly <paramref name="size2"/> characters are copied; the
        /// source is not required to be null-terminated.
        /// </param>
        /// <param name="size2">
        /// Number of characters to copy from <paramref name="string2"/>. May be zero.
        /// </param>
        /// <param name="value">
        /// The character value that will be repeated between the two copied sequences.
        /// </param>
        /// <param name="count">
        /// Number of times <paramref name="value"/> is written after the prefix and before the suffix.
        /// May be zero. The resulting string length is <c>size1 + count + size2</c>.
        /// </param>
        /// <remarks>
        /// <para>
        /// The constructor delegates to the internal <see cref="Initialize(const CharType*, size_type, const CharType*, size_type, CharType, size_type)"/>
        /// helper which performs allocation according to the class allocation granularity and writes a terminating null
        /// character at the end of the internal buffer. The resulting BasicString owns its buffer and has a reference
        /// count of one when allocation succeeds.
        /// </para>
        /// <para>
        /// If the total length (<c>size1 + count + size2</c>) is zero the constructed string will be empty
        /// and no internal buffer is allocated.
        /// </para>
        /// <para>
        /// This operation may throw platform-specific exceptions if underlying allocation fails; allocation helpers
        /// propagate errors via <c>ThrowOSError</c> (for example resulting in a <c>SystemException</c>).
        /// </para>
        /// </remarks>
        /// <example>
        /// <code>
        /// // Produces "1st2nd*****"
        /// BasicString<char> s( "pre", 3, "2nd", 3, '*', 5 );
        /// </code>
        /// </example>
        /// <seealso cref="Initialize(const CharType*, size_type, const CharType*, size_type, CharType, size_type)"/>
        BasicString( const CharType* string1, size_type size1, const CharType* string2, size_type size2, CharType value, size_type count )
            : data_( Initialize( string1, size1, string2, size2, value, count ) )
        {
        }

        /// <summary>
        /// Constructs a new <see cref="BasicString{CharType}"/> by prepending a single character value
        /// and then concatenating two character sequences into a newly allocated internal buffer.
        /// </summary>
        /// <param name="value">
        /// The character value that will be written as the very first character of the new string.
        /// </param>
        /// <param name="string2">
        /// Pointer to the first character sequence to append after <paramref name="value"/>.
        /// May be <c>nullptr</c> only when <paramref name="size2"/> is zero. The pointer is not required to be null-terminated;
        /// exactly <paramref name="size2"/> characters are copied.
        /// </param>
        /// <param name="size2">
        /// Number of characters to copy from <paramref name="string2"/>. May be zero.
        /// </param>
        /// <param name="string3">
        /// Pointer to the second character sequence to append after <paramref name="string2"/>.
        /// May be <c>nullptr</c> only when <paramref name="size3"/> is zero. The pointer is not required to be null-terminated;
        /// exactly <paramref name="size3"/> characters are copied.
        /// </param>
        /// <param name="size3">
        /// Number of characters to copy from <paramref name="string3"/>. May be zero.
        /// </param>
        /// <remarks>
        /// <para>
        /// The constructor allocates a uniquely owned internal <c>Data</c> buffer using the internal
        /// <c>Initialize</c> helper. The resulting string contains <c>1 + size2 + size3</c> characters:
        /// the single <paramref name="value"/> followed by the characters copied from <paramref name="string2"/> and <paramref name="string3"/>.
        /// </para>
        /// <para>
        /// Allocation follows the class allocation granularity. If memory allocation fails the underlying allocator
        /// will call platform-specific error reporting (for example <c>ThrowOSError</c>) which will propagate an exception.
        /// </para>
        /// <para>
        /// Use <see cref="EnsureUnique"/> before mutating the returned string via raw pointers/iterators if other shared references
        /// to the same underlying buffer may exist.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code>
        /// // Construct a BasicString<char> containing "*hello world"
        /// BasicString<char> s( '*', "hello", 5, " world", 6 );
        /// </code>
        /// </example>
        /// <seealso cref="Initialize(CharType, size_type, const CharType*, size_type, const CharType*, size_type)"/>
        BasicString( CharType value, const CharType* string2, size_type size2, const CharType* string3, size_type size3 )
            : data_( Initialize( value, 1, string2, size2, string3, size3 ) )
        {
        }

        /// <summary>
        /// Initializes a new instance of <see cref="BasicString{T}"/> by copying a leading prefix,
        /// inserting a single character in the middle, and then copying a trailing suffix.
        /// </summary>
        /// <param name="string1">
        /// Pointer to the prefix characters to copy. May be <c>nullptr</c> only when <paramref name="size1"/> is zero.
        /// The function copies exactly <paramref name="size1"/> characters; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size1">
        /// Number of characters to copy from <paramref name="string1"/>. May be zero.
        /// </param>
        /// <param name="value">
        /// The single character that will be inserted between the copied prefix and suffix.
        /// </param>
        /// <param name="string3">
        /// Pointer to the suffix characters to copy. May be <c>nullptr</c> only when <paramref name="size3"/> is zero.
        /// The function copies exactly <paramref name="size3"/> characters; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size3">
        /// Number of characters to copy from <paramref name="string3"/>. May be zero.
        /// </param>
        /// <remarks>
        /// <para>
        /// This is a convenience overload that is semantically equivalent to the constructor taking a
        /// repeated character count, with the count fixed to 1. It delegates to
        /// <see cref="Initialize(const CharType*, size_type, CharType, size_type, const CharType*, size_type)"/>.
        /// </para>
        /// <para>
        /// Allocation follows the string class allocation granularity and a trailing null terminator is written.
        /// Prefer using Harlinn.Common.Core editing facilities (for example <c>Insert</c>, <c>Append</c>, and <c>Replace</c>)
        /// when composing strings incrementally; these APIs preserve ownership and performance characteristics better than
        /// raw C-style routines.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails. Allocation helpers may call platform-specific error routines
        /// (for example <c>ThrowOSError</c>), which propagate an exception.
        /// </exception>
        /// <example>
        /// <code>
        /// using namespace Harlinn::Common::Core;
        /// BasicString<char> s("pre", 3, '-', "post", 4); // Produces "pre-post"
        /// </code>
        /// </example>
        /// <seealso cref="Initialize(const CharType*, size_type, CharType, size_type, const CharType*, size_type)"/>
        BasicString( const CharType* string1, size_type size1, CharType value, const CharType* string3, size_type size3 )
            : data_( Initialize( string1, size1, value, 1, string3, size3 ) )
        {
        }

        /// <summary>
        /// Initializes a new instance of <see cref="BasicString{T}"/> by copying two character sequences
        /// and then appending a single trailing character.
        /// </summary>
        /// <param name="string1">
        /// Pointer to the first (prefix) character sequence to copy. May be <c>nullptr</c> only when
        /// <paramref name="size1"/> is zero. Exactly <paramref name="size1"/> characters are copied; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size1">Number of characters to copy from <paramref name="string1"/>. May be zero.</param>
        /// <param name="string2">
        /// Pointer to the second character sequence to copy after <paramref name="string1"/>. May be <c>nullptr</c> only when
        /// <paramref name="size2"/> is zero. Exactly <paramref name="size2"/> characters are copied; the source is not required to be null-terminated.
        /// </param>
        /// <param name="size2">Number of characters to copy from <paramref name="string2"/>. May be zero.</param>
        /// <param name="value">The single character to append after the copied sequences.</param>
        /// <remarks>
        /// <para>
        /// This is a convenience overload equivalent to
        /// <see cref="BasicString(const CharType*, size_type, const CharType*, size_type, CharType, size_type)"/>
        /// with the repeat <c>count</c> fixed to 1.
        /// </para>
        /// <para>
        /// Allocation and initialization are delegated to the internal <c>Initialize</c> helper which adheres to the class
        /// allocation granularity and writes a trailing null terminator. The resulting instance uniquely owns its internal buffer.
        /// </para>
        /// <para>
        /// Prefer Harlinn.Common.Core editing APIs (<c>Append</c>, <c>Insert</c>, <c>Replace</c>) when composing strings incrementally,
        /// and use the provided conversion helpers in this header instead of raw C/Win32 routines.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails; allocation helpers propagate platform-specific errors (for example via <c>ThrowOSError</c>).
        /// </exception>
        /// <example>
        /// <code>
        /// using namespace Harlinn::Common::Core;
        /// BasicString&lt;char&gt; s("left", 4, "right", 5, '!');
        /// // Result: "leftright!"
        /// </code>
        /// </example>
        /// <seealso cref="BasicString(const CharType*, size_type, const CharType*, size_type, CharType, size_type)"/>
        BasicString( const CharType* string1, size_type size1, const CharType* string2, size_type size2, CharType value )
            : data_( Initialize( string1, size1, string2, size2, value, 1 ) )
        {
        }


        /// <summary>
        /// Constructs a new instance of <see cref="BasicString{T}"/> by prepending a repeated character value,
        /// then copying the contents of two contiguous container-like spans.
        /// </summary>
        /// <typeparam name="SpanT1">
        /// The type of the first contiguous container whose <c>value_type</c> must match <c>CharType</c>.
        /// </typeparam>
        /// <typeparam name="SpanT2">
        /// The type of the second contiguous container whose <c>value_type</c> must match <c>CharType</c>.
        /// </typeparam>
        /// <param name="value">
        /// The character value to repeat at the start of the new string.
        /// </param>
        /// <param name="count">
        /// The number of times <paramref name="value"/> is written at the beginning of the buffer.
        /// </param>
        /// <param name="span1">
        /// The first contiguous container whose elements are copied after the repeated value.
        /// </param>
        /// <param name="span2">
        /// The second contiguous container whose elements are copied after <paramref name="span1"/>.
        /// </param>
        /// <remarks>
        /// <para>
        /// This constructor allocates a uniquely owned internal buffer large enough to hold
        /// <paramref name="count"/> repetitions of <paramref name="value"/>, followed by the contents of
        /// <paramref name="span1"/> and <paramref name="span2"/>. The buffer is null-terminated.
        /// </para>
        /// <para>
        /// Use this overload to efficiently construct a string from a repeated prefix and two containers,
        /// such as when building formatted or composite strings in high-performance scenarios.
        /// </para>
        /// <para>
        /// Prefer Harlinn.Common.Core string facilities for memory safety and performance over raw C APIs.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails. Allocation helpers propagate platform-specific errors.
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view a = "foo";
        /// std::string_view b = "bar";
        /// BasicString<char> s('*', 3, a, b); // produces "***foobar"
        /// </code>
        /// </example>
        template<ContiguousContainerLike SpanT1, ContiguousContainerLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType>&& std::is_same_v<typename SpanT2::value_type, CharType> )
        BasicString( CharType value, size_type count, const SpanT1& span1, const SpanT2& span2 )
            : data_( Initialize( value, count, span1.data( ), span1.size( ), span2.data( ), span2.size( ) ) )
        {
        }

        /// <summary>
        /// Constructs a new instance of <see cref="BasicString{T}"/> by concatenating the contents of a contiguous container,
        /// a repeated character value, and another contiguous container.
        /// </summary>
        /// <typeparam name="SpanT1">
        /// The type of the first contiguous container whose <c>value_type</c> must match <c>CharType</c>.
        /// </typeparam>
        /// <typeparam name="SpanT2">
        /// The type of the second contiguous container whose <c>value_type</c> must match <c>CharType</c>.
        /// </typeparam>
        /// <param name="span1">
        /// The first contiguous container whose elements are copied as the leading segment of the new string.
        /// </param>
        /// <param name="value">
        /// The character value to repeat after the contents of <paramref name="span1"/>.
        /// </param>
        /// <param name="count">
        /// The number of times <paramref name="value"/> is written after <paramref name="span1"/>.
        /// </param>
        /// <param name="span2">
        /// The second contiguous container whose elements are copied after the repeated value segment.
        /// </param>
        /// <remarks>
        /// <para>
        /// This constructor allocates a uniquely owned internal buffer large enough to hold the concatenation of
        /// <paramref name="span1"/>, <paramref name="count"/> repetitions of <paramref name="value"/>, and <paramref name="span2"/>.
        /// The buffer is null-terminated.
        /// </para>
        /// <para>
        /// Use this overload to efficiently construct a string from a container, a repeated character, and another container,
        /// such as when building formatted or composite strings in high-performance scenarios.
        /// </para>
        /// <para>
        /// Prefer Harlinn.Common.Core string facilities for memory safety and performance over raw C APIs.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails. Allocation helpers propagate platform-specific errors.
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view a = "foo";
        /// std::string_view b = "bar";
        /// BasicString&lt;char&gt; s(a, '*', 3, b); // produces "foo***bar"
        /// </code>
        /// </example>
        template<ContiguousContainerLike SpanT1, ContiguousContainerLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType>&& std::is_same_v<typename SpanT2::value_type, CharType> )
        BasicString( const SpanT1& span1, CharType value, size_type count, const SpanT2& span2 )
            : data_( Initialize( span1.data( ), span1.size( ), value, count, span2.data( ), span2.size( ) ) )
        {
        }

        /// <summary>
        /// Constructs a new <see cref="BasicString{T}"/> by concatenating the contents of two contiguous containers
        /// and then appending a repeated character value.
        /// </summary>
        /// <typeparam name="SpanT1">
        /// The type of the first contiguous container whose <c>value_type</c> must match <c>CharType</c>.
        /// </typeparam>
        /// <typeparam name="SpanT2">
        /// The type of the second contiguous container whose <c>value_type</c> must match <c>CharType</c>.
        /// </typeparam>
        /// <param name="span1">
        /// The first contiguous container whose elements are copied as the leading segment of the new string.
        /// </param>
        /// <param name="span2">
        /// The second contiguous container whose elements are copied after <paramref name="span1"/>.
        /// </param>
        /// <param name="value">
        /// The character value to repeat after the contents of <paramref name="span2"/>.
        /// </param>
        /// <param name="count">
        /// The number of times <paramref name="value"/> is written after the copied segments.
        /// </param>
        /// <remarks>
        /// <para>
        /// This constructor allocates a uniquely owned internal buffer large enough to hold the concatenation of
        /// <paramref name="span1"/>, <paramref name="span2"/>, and <paramref name="count"/> repetitions of <paramref name="value"/>.
        /// The buffer is null-terminated.
        /// </para>
        /// <para>
        /// Use this overload to efficiently construct a string from two containers and a repeated character,
        /// such as when building formatted or composite strings in high-performance scenarios.
        /// </para>
        /// <para>
        /// Prefer Harlinn.Common.Core string facilities for memory safety and performance over raw C APIs.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails. Allocation helpers propagate platform-specific errors.
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view a = "foo";
        /// std::string_view b = "bar";
        /// BasicString&lt;char&gt; s(a, b, '*', 3); // produces "foobar***"
        /// </code>
        /// </example>
        template<ContiguousContainerLike SpanT1, ContiguousContainerLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType>&& std::is_same_v<typename SpanT2::value_type, CharType> )
        BasicString( const SpanT1& span1, const SpanT2& span2, CharType value, size_type count )
            : data_( Initialize( span1.data( ), span1.size( ), span2.data( ), span2.size( ), value, count ) )
        {
        }


        /// <summary>
        /// Constructs a new instance of <see cref="BasicString{T}"/> by prepending a single character value
        /// and then copying the contents of two contiguous container-like spans.
        /// </summary>
        /// <typeparam name="SpanT1">
        /// The type of the first contiguous container whose <c>value_type</c> must match <c>CharType</c>.
        /// </typeparam>
        /// <typeparam name="SpanT2">
        /// The type of the second contiguous container whose <c>value_type</c> must match <c>CharType</c>.
        /// </typeparam>
        /// <param name="value">
        /// The character value to write as the very first character of the new string.
        /// </param>
        /// <param name="span1">
        /// The first contiguous container whose elements are copied after the leading character.
        /// </param>
        /// <param name="span2">
        /// The second contiguous container whose elements are copied after <paramref name="span1"/>.
        /// </param>
        /// <remarks>
        /// <para>
        /// This constructor allocates a uniquely owned internal buffer large enough to hold
        /// the single <paramref name="value"/>, followed by the contents of <paramref name="span1"/>
        /// and <paramref name="span2"/>. The buffer is null-terminated.
        /// </para>
        /// <para>
        /// Use this overload to efficiently construct a string from a prepended character and two containers,
        /// such as when building formatted or composite strings in high-performance scenarios.
        /// </para>
        /// <para>
        /// Prefer Harlinn.Common.Core string facilities for memory safety and performance over raw C APIs.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails. Allocation helpers propagate platform-specific errors.
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view a = "foo";
        /// std::string_view b = "bar";
        /// BasicString&lt;char&gt; s('*', a, b); // produces "*foobar"
        /// </code>
        /// </example>
        template<ContiguousContainerLike SpanT1, ContiguousContainerLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType>&& std::is_same_v<typename SpanT2::value_type, CharType> )
        BasicString( CharType value, const SpanT1& span1, const SpanT2& span2 )
            : data_( Initialize( value, 1, span1.data( ), span1.size( ), span2.data( ), span2.size( ) ) )
        {
        }

        /// <summary>
        /// Constructs a new <see cref="BasicString{T}"/> by concatenating the contents of a contiguous container,
        /// a single character value, and another contiguous container.
        /// </summary>
        /// <typeparam name="SpanT1">
        /// The type of the first contiguous container whose <c>value_type</c> must match <c>CharType</c>.
        /// </typeparam>
        /// <typeparam name="SpanT2">
        /// The type of the second contiguous container whose <c>value_type</c> must match <c>CharType</c>.
        /// </typeparam>
        /// <param name="span1">
        /// The first contiguous container whose elements are copied as the leading segment of the new string.
        /// </param>
        /// <param name="value">
        /// The character value to insert between the two containers. Only a single instance of <paramref name="value"/> is inserted.
        /// </param>
        /// <param name="span2">
        /// The second contiguous container whose elements are copied after the inserted character.
        /// </param>
        /// <remarks>
        /// <para>
        /// This constructor allocates a uniquely owned internal buffer large enough to hold the concatenation of
        /// <paramref name="span1"/>, the single <paramref name="value"/>, and <paramref name="span2"/>.
        /// The buffer is null-terminated.
        /// </para>
        /// <para>
        /// Use this overload to efficiently construct a string from a container, a character, and another container,
        /// such as when building formatted or composite strings in high-performance scenarios.
        /// </para>
        /// <para>
        /// Prefer Harlinn.Common.Core string facilities for memory safety and performance over raw C APIs.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails. Allocation helpers propagate platform-specific errors.
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view a = "foo";
        /// std::string_view b = "bar";
        /// BasicString&lt;char&gt; s(a, '*', b); // produces "foo*bar"
        /// </code>
        /// </example>
        template<ContiguousContainerLike SpanT1, ContiguousContainerLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType>&& std::is_same_v<typename SpanT2::value_type, CharType> )
        BasicString( const SpanT1& span1, CharType value, const SpanT2& span2 )
            : data_( Initialize( span1.data( ), span1.size( ), value, 1, span2.data( ), span2.size( ) ) )
        {
        }

        /// <summary>
        /// Initializes a new instance of <see cref="BasicString{T}"/> by concatenating the contents of two contiguous containers
        /// and then appending a single character value.
        /// </summary>
        /// <typeparam name="SpanT1">
        /// The type of the first contiguous container whose <c>value_type</c> must match <c>CharType</c>.
        /// </typeparam>
        /// <typeparam name="SpanT2">
        /// The type of the second contiguous container whose <c>value_type</c> must match <c>CharType</c>.
        /// </typeparam>
        /// <param name="span1">
        /// The first contiguous container whose elements are copied as the leading segment of the new string.
        /// </param>
        /// <param name="span2">
        /// The second contiguous container whose elements are copied after <paramref name="span1"/>.
        /// </param>
        /// <param name="value">
        /// The character value to append after the contents of <paramref name="span2"/>.
        /// </param>
        /// <remarks>
        /// <para>
        /// This constructor allocates a uniquely owned internal buffer large enough to hold the concatenation of
        /// <paramref name="span1"/>, <paramref name="span2"/>, and a single instance of <paramref name="value"/>.
        /// The buffer is null-terminated.
        /// </para>
        /// <para>
        /// Use this overload to efficiently construct a string from two containers and a trailing character,
        /// such as when building formatted or composite strings in high-performance scenarios.
        /// </para>
        /// <para>
        /// Prefer Harlinn.Common.Core string facilities for memory safety and performance over raw C APIs.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if the underlying memory allocation fails. Allocation helpers propagate platform-specific errors.
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view a = "foo";
        /// std::string_view b = "bar";
        /// BasicString&lt;char&gt; s(a, b, '*'); // produces "foobar*"
        /// </code>
        /// </example>
        template<ContiguousContainerLike SpanT1, ContiguousContainerLike SpanT2>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType>&& std::is_same_v<typename SpanT2::value_type, CharType> )
        BasicString( const SpanT1& span1, const SpanT2& span2, CharType value )
            : data_( Initialize( span1.data( ), span1.size( ), span2.data( ), span2.size( ), value, 1 ) )
        {
        }




        /// <summary>
        /// Constructs a new <see cref="BasicString"/> by concatenating three contiguous containers.
        /// </summary>
        /// <typeparam name="SpanT1">Type of the first contiguous container. Its <c>value_type</c> must match <c>CharType</c>.</typeparam>
        /// <typeparam name="SpanT2">Type of the second contiguous container. Its <c>value_type</c> must match <c>CharType</c>.</typeparam>
        /// <typeparam name="SpanT3">Type of the third contiguous container. Its <c>value_type</c> must match <c>CharType</c>.</typeparam>
        /// <param name="span1">The first span whose contents will be copied as the leading segment.</param>
        /// <param name="span2">The second span whose contents will be copied after <paramref name="span1"/>.</param>
        /// <param name="span3">The third span whose contents will be copied after <paramref name="span2"/>.</param>
        /// <remarks>
        /// <para>
        /// The constructor allocates a uniquely owned internal <c>Data</c> buffer sized to hold the
        /// concatenation of the three spans (rounded according to the class allocation granularity).
        /// The contents are copied in order: <paramref name="span1"/>, then <paramref name="span2"/>, then <paramref name="span3"/>.
        /// </para>
        /// <para>
        /// After construction the resulting <see cref="BasicString"/> owns its internal buffer and has
        /// a reference count of one. Call <see cref="EnsureUnique"/> before performing in-place mutations
        /// if the buffer may be shared.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when underlying memory allocation fails. Allocation helpers will propagate platform-specific errors
        /// (for example via <c>ThrowOSError</c>).
        /// </exception>
        /// <example>
        /// <code>
        /// std::string_view a = "foo";
        /// std::string_view b = "bar";
        /// std::string_view c = "baz";
        /// BasicString<char> s( a, b, c ); // produces "foobarbaz"
        /// </code>
        /// </example>
        /// <seealso cref="Initialize(const CharType*, size_type, const CharType*, size_type, const CharType*, size_type)"/>
        template<ContiguousContainerLike SpanT1, ContiguousContainerLike SpanT2, ContiguousContainerLike SpanT3>
            requires ( std::is_same_v<typename SpanT1::value_type, CharType> && std::is_same_v<typename SpanT2::value_type, CharType> && std::is_same_v<typename SpanT3::value_type, CharType> )
        BasicString( const SpanT1& span1, const SpanT2& span2, const SpanT3& span3 )
            : data_( Initialize( span1.data( ), span1.size( ), span2.data( ), span2.size( ), span3.data( ), span3.size( ) ) )
        {
        }


        /// <summary>
        /// Constructs a <c>BasicString</c> by copying the character range identified by the iterator pair <paramref name="first"/> and <paramref name="last"/>.
        /// </summary>
        /// <param name="first">A const iterator pointing to the first character in the input range (inclusive).</param>
        /// <param name="last">A const iterator pointing one past the last character in the input range (exclusive).</param>
        /// <returns>
        /// Constructs and stores an internal <c>Data</c> buffer containing the characters in the range [<paramref name="first"/>, <paramref name="last"/>).
        /// When the range is empty the resulting string is empty (no internal buffer is allocated).
        /// </returns>
        /// <remarks>
        /// <para>
        /// The constructor delegates to the static helper <see cref="Initialize(const CharType*, size_type)"/> which computes the character count
        /// using the iterator difference and allocates a uniquely owned internal buffer sized according to the class allocation granularity.
        /// </para>
        /// <para>
        /// If <paramref name="first"/> is greater than <paramref name="last"/>, zero characters are copied and an empty string is constructed.
        /// </para>
        /// <para>
        /// Exceptions:
        /// <list type="bullet">
        ///   <item><description><c>SystemException</c> (or platform allocation error) may be thrown by the underlying allocator if memory allocation fails.</description></item>
        /// </list>
        /// </para>
        /// </remarks>
        BasicString( const_iterator first, const_iterator last)
            : data_( Initialize( first.ptr_, first <= last ? static_cast<size_type>( last - first ) : 0 ) )
        {
        }

        /// <summary>
        /// Constructs a new <see cref="BasicString{T}"/> by copying the character range [<paramref name="first"/>, <paramref name="last"/>).
        /// </summary>
        /// <param name="first">Pointer to the first character in the input range (inclusive). May be <c>nullptr</c> when the range is empty.</param>
        /// <param name="last">Pointer one past the last character in the input range (exclusive). If <c>last &lt; first</c> the range is considered empty.</param>
        /// <remarks>
        /// <para>
        /// The constructor computes the number of characters to copy as <c>first <= last ? static_cast<size_type>(last - first) : 0</c>
        /// and delegates to <see cref="Initialize(const CharType*, size_type)"/> which allocates a uniquely owned internal buffer
        /// sized according to the class allocation granularity and copies the characters (excluding any terminating null).
        /// </para>
        /// <para>
        /// When the range is empty no internal buffer is allocated and the constructed string is empty.
        /// </para>
        /// <para>
        /// Allocation failures propagate via the underlying allocator and result in platform-specific exceptions (for example the allocator
        /// calls <c>ThrowOSError</c> which will throw an exception).
        /// </para>
        /// </remarks>
        BasicString( const_pointer first, const_pointer last )
            : data_( Initialize( first, first <= last ? static_cast< size_type >( last - first ) : 0 ) )
        {
        }

        /// <summary>
        /// Constructs a <see cref="BasicString{T}"/> by copying characters from the iterator range [first, last).
        /// </summary>
        /// <typeparam name="InputIt">
        /// The input iterator type. The iterator's <c>value_type</c> must be convertible to <c>CharType</c>
        /// and the iterator must satisfy the requirements of <c>std::input_iterator</c>.
        /// </typeparam>
        /// <param name="first">Iterator to the first element in the source range (inclusive).</param>
        /// <param name="last">Iterator one past the last element in the source range (exclusive).</param>
        /// <remarks>
        /// <para>
        /// The constructor delegates to the static helper <c>Initialize(first, last)</c>, which:
        /// </para>
        /// <list type="bullet">
        ///   <item>
        ///     <description>Computes the number of characters when possible (for forward iterators).</description>
        ///   </item>
        ///   <item>
        ///     <description>For single-pass input iterators accumulates elements into a temporary buffer before allocation.</description>
        ///   </item>
        ///   <item>
        ///     <description>Allocates an internal reference-counted Data buffer and copies the characters into it.</description>
        ///   </item>
        /// </list>
        /// <para>
        /// The resulting BasicString owns a uniquely allocated internal buffer with a reference count of one.
        /// Prefer passing contiguous container-like types (spans, string_views, etc.) when available for better performance.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown if underlying memory allocation fails (propagated from the internal allocator called by <c>Initialize</c>).
        /// </exception>
        /// <example>
        /// <code>
        /// std::vector<CharType> v = ...;
        /// BasicString<CharType> s( v.begin(), v.end() );
        /// </code>
        /// </example>
        template<std::input_iterator InputIt>
            requires std::is_convertible_v<typename std::iterator_traits<InputIt>::value_type, CharType>
        BasicString( InputIt first, InputIt last )
            : data_( Initialize( first, last ) )
        {
        }

        /// <summary>
        /// Constructs a <see cref="BasicString"/> by copying characters from the specified input range.
        /// </summary>
        /// <typeparam name="R">
        /// A type satisfying <c>std::ranges::input_range</c>. The range's <c>value_type</c> must be convertible to
        /// the string character type (<c>CharType</c>).
        /// </typeparam>
        /// <param name="range">Input range whose elements will be copied into the newly allocated internal buffer.</param>
        /// <remarks>
        /// <para>
        /// The constructor delegates to the static helper <c>Initialize(first, last)</c> which copies the elements
        /// from <c>std::ranges::begin(range)</c> to <c>std::ranges::end(range)</c> into a newly allocated internal
        /// <c>Data</c> buffer. For forward ranges the element count can be determined and a single allocation is performed.
        /// For single-pass input iterators the helper accumulates elements into a temporary buffer before allocating the
        /// final internal storage sized to the exact element count.
        /// </para>
        /// <para>
        /// Allocation follows the class allocation granularity and the resulting buffer is null-terminated. Callers
        /// should be aware that existing raw pointers or iterators into other strings remain valid only if those buffers
        /// are not modified; use <c>EnsureUnique()</c> before performing in-place mutations when sharing may occur.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when underlying memory allocation fails. Underlying allocation helpers (for example <c>Internal::AllocateBytes</c>)
        /// will report platform-specific errors which are forwarded as exceptions.
        /// </exception>
        template <std::ranges::input_range R>
			requires std::is_convertible_v<std::ranges::range_value_t<R>, CharType>
        BasicString( const R& range )
            : data_( Initialize( std::ranges::begin( range ), std::ranges::end( range ) ) )
        {
		}


        //BasicString( const BasicStringView<T>& v );

        /// <summary>
        /// Constructs a <see cref="BasicString{T}"/> containing <paramref name="count"/> repetitions 
        /// of the specified <paramref name="value"/>.
        /// </summary>
        /// <param name="count">
        /// The number of characters to write into the new string. When zero the constructed string is 
        /// empty and no internal buffer is allocated.
        /// </param>
        /// <param name="value">
        /// The character value that will be repeated <paramref name="count"/> times to initialize the string content.
        /// </param>
        /// <remarks>
        /// <para>
        /// This constructor delegates to the internal helper <c>Initialize(size_type, CharType)</c> which allocates an internal
        /// reference-counted <c>Data</c> buffer sized according to the class allocation granularity and writes a terminating null
        /// character at the end of the buffer. The resulting object owns the allocated buffer and its internal reference count is
        /// initialized to one.
        /// </para>
        /// <para>
        /// Call <see cref="EnsureUnique"/> before performing in-place mutations if other <see cref="BasicString{T}"/> instances might
        /// share the same internal data. Prefer high-level editing APIs (for example <c>Append</c>, <c>Insert</c>, <c>Replace</c>)
        /// for incremental composition to preserve ownership semantics and performance characteristics.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when the underlying memory allocation fails. Allocation helpers (for example <c>Internal::AllocateBytes</c>)
        /// will call <c>ThrowOSError</c> which results in a platform-specific <c>SystemException</c>.
        /// </exception>
        BasicString( size_type count, CharType value )
            : data_( Initialize( count, value ) )
        {
        }


        /// <summary>
        /// Constructs a new <see cref="BasicString{T}"/> as a shallow copy of <paramref name="other"/>.
        /// </summary>
        /// <param name="other">
        /// The source <see cref="BasicString{T}"/> to copy. When <paramref name="other"/> contains internal
        /// data the new instance will share the same internal <c>Data</c> buffer.
        /// </param>
        /// <remarks>
        /// This constructor performs a shallow copy: it stores the same internal <c>Data*</c> pointer as
        /// <paramref name="other"/> and increments the internal reference count via <c>Data::AddRef()</c>.
        /// No memory allocation is performed by this operation and it is safe to call in noexcept contexts.
        /// If you intend to mutate the contents after copying, call <see cref="EnsureUnique"/> first to
        /// obtain a unique buffer and avoid modifying shared storage.
        /// <para>
        /// Thread-safety: the reference count increment is performed using interlocked operations. However,
        /// callers must ensure external synchronization if multiple threads may modify the same
        /// BasicString instance concurrently.
        /// </para>
        /// </remarks>
        /// <exception cref="std::bad_alloc">
        /// This constructor does not allocate and therefore does not throw due to allocation. The operation is
        /// declared <c>noexcept</c>.
        /// </exception>
        /// <seealso cref="EnsureUnique"/>
        BasicString( const BasicString& other ) noexcept
            : data_( other.data_ )
        {
            if ( data_ )
            {
                data_->AddRef( );
            }
        }

        /// <summary>
        /// Move constructor.
        /// </summary>
        /// <param name="other">
        /// The source <see cref="BasicString{T}"/> to move from. Ownership of the internal buffer is transferred
        /// to the newly constructed object.
        /// </param>
        /// <remarks>
        /// This constructor performs a shallow transfer of the internal <c>Data*</c> pointer 
        /// from <paramref name="other"/> to the newly created instance. The source object's 
        /// <c>data_</c> pointer is set to <c>nullptr</c>, leaving it in a valid but empty state. 
        /// The operation is marked <c>noexcept</c> to allow efficient relocation of <see cref="BasicString{T}"/> 
        /// instances in standard containers and algorithms that depend on noexcept move
        /// constructors for strong exception-safety guarantees.
        /// <para>
        /// Note: If caller code requires the source object to retain its buffer contents after the move, call
        /// <see cref="EnsureUnique"/> prior to moving or use copy semantics instead.
        /// </para>
        /// </remarks>
        /// <seealso cref="EnsureUnique"/>
        BasicString( BasicString&& other ) noexcept
            : data_( other.data_ )
        {
            other.data_ = nullptr;
        }

        /// <summary>
        /// Finalizes this <see cref="BasicString{T}"/> instance and releases its internal storage.
        /// </summary>
        /// <remarks>
        /// <para>
        /// Decrements the reference count of the internal <c>Data</c> object and, when the last
        /// reference is released, frees the underlying memory. This destructor is safe to call
        /// in noexcept contexts and does not allocate memory. Any allocation failures would have
        /// occurred earlier during construction or editing operations; this routine only releases
        /// previously allocated resources.
        /// </para>
        /// <para>
        /// Thread-safety: the reference count decrement is performed using interlocked operations.
        /// Callers must ensure they do not access the object's memory after destruction. Creating
        /// a unique buffer for mutation is performed by higher-level helpers (for example
        /// <see cref="EnsureUnique"/>) and is unrelated to this destructor's behavior.
        /// </para>
        /// </remarks>
        /// <seealso cref="ReleaseData"/>
        ~BasicString( )
        {
            if ( data_ )
            {
                ReleaseData( data_ );
            }
        }

        /// <summary>
        /// Determines whether this string instance uniquely owns its internal data buffer.
        /// </summary>
        /// <returns>
        /// <c>true</c> when the instance has an internal <c>Data</c> object and its reference count equals 1;
        /// otherwise <c>false</c>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// This check is performed in constant time and does not perform any synchronization. It is intended
        /// as a lightweight query to decide whether in-place mutation is safe for this instance.
        /// </para>
        /// <para>
        /// In multi-threaded scenarios other threads may change the reference count concurrently, so callers
        /// that will mutate the contents should call <see cref="EnsureUnique()"/> to obtain exclusive ownership
        /// of the internal buffer prior to performing modifications.
        /// </para>
        /// </remarks>
        [[nodiscard]] bool IsUnique( ) const noexcept
        {
            return data_ ? data_->referenceCount_ == 1 : false;
        }

        /// <summary>
        /// Creates a deep copy of this string and returns a newly allocated <see cref="BasicString"/> instance
        /// that owns an independent buffer containing the same characters.
        /// </summary>
        /// <returns>
        /// A <see cref="BasicString"/> that contains the same character sequence as this instance.
        /// If this instance is empty the returned <see cref="BasicString"/> will be empty.
        /// </returns>
        /// <remarks>
        /// <para>
        /// The returned string is a unique (non-shared) copy: it is allocated via the internal
        /// allocation helpers and initialized with the exact character count of this instance.
        /// </para>
        /// <list type="bullet">
        ///   <item>
        ///     <description>
        ///       If this instance holds internal data the method allocates a new internal buffer and copies
        ///       the characters; the returned object owns that buffer and has reference count == 1.
        ///     </description>
        ///   </item>
        ///   <item>
        ///     <description>
        ///       If this instance is empty the method returns an empty <see cref="BasicString"/>.
        ///     </description>
        ///   </item>
        /// </list>
        /// <para>
        /// Thread-safety: this routine does not synchronize access to this object. Callers should ensure
        /// appropriate external synchronization if other threads may mutate or release this instance
        /// concurrently.
        /// </para>
        /// <seealso cref="EnsureUnique"/>
        /// <example>
        /// <code>
        /// // Create a deep copy that can be modified without affecting the original
        /// auto copy = original.Clone();
        /// copy.Append( '!' );
        /// </code>
        /// </example>
        /// </remarks>
        [[nodiscard]] BasicString Clone( ) const
        {
            if ( data_ )
            {
                return BasicString( data_->buffer_, data_->size_ );
            }
            return {};
        }


        /// <summary>
        /// Ensures this string instance uniquely owns its internal <c>Data</c> buffer.
        /// </summary>
        /// <remarks>
        /// <para>
        /// When multiple <c>BasicString</c> instances share the same internal buffer (the internal
        /// reference count is greater than one) this method allocates a new internal buffer, copies
        /// the current contents into it and replaces the shared buffer so that this instance becomes
        /// the sole owner. If the buffer is already unique or the string is empty, the method returns
        /// without performing any allocation or copy.
        /// </para>
        /// <para>
        /// Callers that hold raw pointers, iterators or references into this string's buffer must be
        /// prepared for those references to be invalidated after this call because the internal buffer
        /// may be replaced.
        /// </para>
        /// <para>
        /// Thread-safety: this method is not synchronized. External synchronization is required if
        /// multiple threads may modify the same <c>BasicString</c> instance concurrently. Converting
        /// a shared buffer into a unique one is safe because other string instances that referenced the
        /// old buffer are not mutated.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when allocation of the new internal buffer fails. Underlying allocation helpers
        /// (for example <c>Internal::AllocateBytes</c> used by <c>Initialize</c>) will raise a
        /// platform-specific error which is propagated as an exception.
        /// </exception>
        /// <seealso cref="Initialize(const CharType*, size_type)"/>
        /// <seealso cref="ReleaseData(Data*)"/>
        void EnsureUnique( )
        {
            if ( data_ && data_->referenceCount_ > 1 )
            {
                auto tmp = Initialize( data_->buffer_, data_->size_ );
                ReleaseData( data_ );
                data_ = tmp;
            }
        }

        /// <summary>
        /// Creates a new <see cref="BasicString"/> by copying the contents of a contiguous container.
        /// </summary>
        /// <typeparam name="ContainerT">
        /// A contiguous container type whose <c>value_type</c> is identical to this string's character type.
        /// Examples include <c>std::basic_string</c>, <c>std::basic_string_view</c>, <c>std::vector</c> (contiguous elements),
        /// and other contiguous container-like types that expose <c>data()</c> and <c>size()</c>.
        /// </typeparam>
        /// <param name="s">
        /// The source container whose elements will be copied into the new string. The container must provide
        /// contiguous storage via <c>data()</c> and the number of elements via <c>size()</c>.
        /// </param>
        /// <returns>
        /// A <see cref="BasicString"/> instance that owns a newly allocated internal buffer containing a copy
        /// of the characters from <paramref name="s"/>. If <paramref name="s"/> is empty an empty
        /// <see cref="BasicString"/> is returned.
        /// </returns>
        /// <remarks>
        /// <para>
        /// The function performs a single allocation sized to hold the exact number of elements returned by
        /// <c>s.size()</c> and copies the elements from <c>s.data()</c>. Use this overload when the container's
        /// element type already matches the string character type for optimal performance.
        /// </para>
        /// <para>
        /// For containers with a different element type (for example converting between ANSI and wide strings),
        /// prefer the conversion helpers in <c>Internal::From</c> or the conversion free functions in this header
        /// (for example <c>ToWideString</c> / <c>ToAnsiString</c>), which handle encoding and code page details.
        /// </para>
        /// </remarks>
        template<ContiguousContainerLike ContainerT>
            requires std::is_same_v<typename ContainerT::value_type, CharType>
        [[nodiscard]] static BasicString From( const ContainerT& s )
        {
            return BasicString( s.data( ), s.size( ) );
        }

        /// <summary>
        /// Creates a new <c>BasicString</c> by converting the characters stored in a contiguous container
        /// whose element type is different from the string's character type (<c>CharType</c>).
        /// This overload delegates the conversion work to <see cref="Internal::From(const CharT*, size_t, unsigned, unsigned)"/>,
        /// which performs any necessary encoding or character-type conversion and allocates a new internal buffer.
        /// </summary>
        /// <typeparam name="ContainerT">
        /// The contiguous container type holding the source characters. The container's <c>value_type</c>
        /// must not be the same as this string's <c>CharType</c> and the container must provide
        /// contiguous access via <c>data()</c> and <c>size()</c>.
        /// </typeparam>
        /// <param name="s">
        /// The source container instance to convert. When empty an empty <c>BasicString</c> is returned.
        /// </param>
        /// <returns>
        /// A <c>BasicString</c> instance that owns a newly allocated internal buffer containing the converted characters.
        /// </returns>
        /// <remarks>
        /// - The conversion may allocate memory; allocation failures are reported via platform-specific exceptions
        ///   (for example the underlying allocator calls <c>ThrowOSError</c> which will propagate a <c>SystemException</c>).
        /// - The caller must ensure <c>ContainerT</c> exposes contiguous storage and that its elements are convertible
        ///   to the expected source character type for <c>Internal::From</c>.
        /// </remarks>
        /// <exception cref="SystemException">Thrown when memory allocation or underlying conversion fails.</exception>
        /// <seealso cref="Internal::From(const char*, size_t, unsigned, unsigned)"/>
        template<ContiguousContainerLike ContainerT>
            requires (std::is_same_v<typename ContainerT::value_type, CharType> == false)
        [[nodiscard]] static BasicString From( const ContainerT& s )
        {
            return Internal::From( s.data( ), s.size( ) );
		}

        /// <summary>
        /// Creates a new <c>BasicString</c> by copying the characters from a null-terminated character sequence.
        /// </summary>
        /// <param name="s">
        /// Pointer to a null-terminated character sequence of the same character type as this string
        /// (<c>CharType</c>). The pointer may be <c>nullptr</c>; in that case the computed length is zero
        /// and an empty <c>BasicString</c> is returned. The character count is determined using <c>LengthOf</c>.
        /// </param>
        /// <returns>
        /// A <c>BasicString</c> instance that owns a newly allocated internal buffer containing a copy of the
        /// characters from <paramref name="s"/> (excluding the terminating null). If <paramref name="s"/> is
        /// <c>nullptr</c> or empty an empty <c>BasicString</c> is returned.
        /// </returns>
        /// <remarks>
        /// - This is a convenience factory that delegates to the <c>BasicString(const CharType*, size_type)</c>
        ///   constructor which in turn calls the internal initializers and allocation helpers.
        /// - Memory allocation may fail; underlying allocation helpers will report platform-specific errors
        ///   (for example by calling <c>ThrowOSError</c>), which will propagate an exception to the caller.
        /// </remarks>
        /// <seealso cref="LengthOf">LengthOf (computes the length of a null-terminated string)</seealso>
        /// <seealso cref="BasicString::Initialize">BasicString::Initialize (internal allocation helpers)</seealso>
        template<typename CharT>
            requires std::is_same_v<CharType, CharT>
        [[nodiscard]] static BasicString From( const CharT* s )
        {
            return BasicString( s, LengthOf( s ) );
        }

        /// <summary>
        /// Creates a new <see cref="BasicString"/> by converting a null-terminated character sequence
        /// whose element type differs from this string's <c>CharType</c>.
        /// </summary>
        /// <typeparam name="CharT">Source character type. Must not be identical to this string's <c>CharType</c>.</typeparam>
        /// <param name="s">
        /// Pointer to a null-terminated character sequence of type <c>CharT</c>.
        /// May be <c>nullptr</c>; when <c>nullptr</c> or the sequence is empty an empty <see cref="BasicString"/> is returned.
        /// </param>
        /// <returns>
        /// A <see cref="BasicString"/> containing the converted characters. The returned string owns a newly allocated
        /// internal buffer (reference count == 1) when the input is non-empty.
        /// </returns>
        /// <remarks>
        /// <para>
        /// The conversion and allocation are delegated to <see cref="Internal::From(const CharT*, size_t)"/>.
        /// For ANSI/Wide conversions the internal implementation uses the platform facilities (for example
        /// MultiByteToWideChar / WideCharToMultiByte) and respects code page and flag parameters when applicable.
        /// </para>
        /// <para>
        /// Callers that require explicit control over encoding (code page or flags) should call the corresponding
        /// Internal::From overload directly.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code>
        /// // Convert narrow C-string to a WideString
        /// WideString w = BasicString<wchar_t>::From( "hello" );
        /// </code>
        /// </example>
        /// <seealso cref="Internal::From(const char*, size_t, unsigned, unsigned)"/>
        template<typename CharT>
            requires (std::is_same_v<CharType, CharT> == false)
        [[nodiscard]] static BasicString From( const CharT* s )
        {
            return Internal::From( s, LengthOf( s ) );
        }

        /// <summary>
        /// Releases any internal storage held by this string and resets the instance to an empty state.
        /// </summary>
        /// <remarks>
        /// If the string currently owns an internal <c>Data</c> object, this operation decrements its
        /// reference count via <c>ReleaseData</c>. When the last reference is released the backing memory
        /// is freed. After this call the string contains no data (<c>data_ == nullptr</c>).
        /// <para>
        /// This operation is safe to call when the string is already empty. The underlying reference-count
        /// decrement is performed using interlocked operations; callers must ensure external synchronization
        /// if multiple threads may concurrently mutate the same <c>BasicString</c> instance.
        /// </para>
        /// </remarks>
        /// <returns>A reference to this <c>BasicString</c> instance, now empty.</returns>
        BasicString& operator = ( nullptr_t )
        {
            if ( data_ )
            {
                ReleaseData( data_ );
                data_ = nullptr;
            }
            return *this;
        }

        /// <summary>
        /// Copy assignment operator.
        /// </summary>
        /// <param name="other">
        /// The source <see cref="BasicString"/> to copy from. When <paramref name="other"/> contains internal data
        /// the assignment performs a shallow copy: this instance will reference the same internal <c>Data</c> buffer
        /// and the buffer's reference count is incremented.
        /// </param>
        /// <returns>
        /// A reference to this <see cref="BasicString"/> instance after assignment.
        /// </returns>
        /// <remarks>
        /// <para>
        /// The operator first checks for self-assignment and only performs work when the source and destination
        /// differ. If this object currently owns an internal buffer it releases that buffer (decrementing the
        /// reference count and freeing memory when the last reference is released). Then the internal pointer
        /// is updated to point to the source buffer and the reference count is incremented when non-null.
        /// </para>
        /// <para>
        /// This operation implements copy semantics with shared, reference-counted storage. Call <see cref="EnsureUnique"/>
        /// before performing in-place mutations if other <see cref="BasicString"/> instances may share the same buffer.
        /// </para>
        /// <para>
        /// Thread-safety: the reference count operations use interlocked primitives, but external synchronization
        /// is required if multiple threads may concurrently modify the same <see cref="BasicString"/> object.
        /// </para>
        /// </remarks>
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

        /// <summary>
        /// Move assignment operator that exchanges the internal buffer pointer with <paramref name="other"/>.
        /// </summary>
        /// <param name="other">Source <see cref="BasicString"/> to move from. After the call the source remains valid.
        /// The internal <c>Data*</c> pointers are exchanged; the source is left in a valid but unspecified state
        /// unless the destination was empty prior to the call.</param>
        /// <returns>Reference to this instance after move-assignment.</returns>
        /// <remarks>
        /// This operation is <c>noexcept</c>, non-allocating, and does not modify reference counts on existing
        /// <c>Data</c> objects; it swaps the <c>data_</c> pointers. Call <see cref="EnsureUnique"/> if you require
        /// a unique buffer for subsequent in-place mutation.
        /// </remarks>
        /// <seealso cref="EnsureUnique"/>
        BasicString& operator = ( BasicString&& other ) noexcept
        {
            std::swap( other.data_, data_ );
            return *this;
        }

        /// <summary>
        /// Assigns the contents of a null-terminated character sequence to this string.
        /// </summary>
        /// <param name="string">
        /// Pointer to a null-terminated character sequence of type <c>CharType</c>.
        /// May be <c>nullptr</c>. When <c>nullptr</c> or the sequence is empty the resulting
        /// string becomes empty.
        /// </param>
        /// <remarks>
        /// <para>
        /// This method delegates the actual allocation and initialization to
        /// <c>Initialize(const CharType*)</c>. If this instance already owns internal
        /// data, the method creates a new internal buffer initialized from <paramref name="string"/>,
        /// releases the currently held buffer via <c>ReleaseData</c> and replaces it with the new buffer.
        /// When the instance does not own a buffer (<c>data_ == nullptr</c>), the method simply
        /// initializes and takes ownership of the newly allocated buffer.
        /// </para>
        /// <para>
        /// The operation preserves the copy-on-write/reference-counting semantics of
        /// <c>BasicString</c>. Callers that need to mutate existing raw pointers/iterators should
        /// call <c>EnsureUnique()</c> before performing in-place modifications.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when underlying memory allocation fails. Allocation helpers (for example
        /// <c>Internal::AllocateBytes</c>) will propagate platform-specific errors (via
        /// <c>ThrowOSError</c> or similar) which surface as exceptions.
        /// </exception>
        /// <example>
        /// <code>
        /// BasicString<char> s;
        /// s.Assign("hello"); // s now contains "hello"
        /// s.Assign(nullptr); // s becomes empty
        /// </code>
        /// </example>
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

        /// <summary>
        /// Assigns the characters from a null-terminated character sequence to this string.
        /// </summary>
        /// <param name="string">
        /// Pointer to a null-terminated character sequence of type <c>CharType</c>.
        /// May be <c>nullptr</c>; when <c>nullptr</c> or the sequence is empty the resulting string
        /// becomes empty.
        /// </param>
        /// <remarks>
        /// <para>
        /// This lowercase overload is a convenience wrapper that forwards to <see cref="Assign(const CharType*)"/>.
        /// It preserves the reference-counted copy-on-write semantics of <c>BasicString</c>. If the
        /// underlying call requires allocation (for example when creating a new unique buffer) the
        /// allocation is performed by the internal helpers invoked by <c>Assign</c>.
        /// </para>
        /// <para>
        /// Call <see cref="EnsureUnique()"/> before performing in-place mutations through raw pointers,
        /// iterators or references if other <c>BasicString</c> instances may share the internal buffer.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when underlying memory allocation fails. Allocation helpers (for example
        /// <c>Internal::AllocateBytes</c>) will propagate platform-specific errors (for example via
        /// <c>ThrowOSError</c>) which surface as exceptions.
        /// </exception>
        /// <seealso cref="Assign(const CharType*)"/>
        void assign( const CharType* string )
        {
            Assign( string );
        }

        /// <summary>
        /// Assigns the characters from a null-terminated character sequence to this string.
        /// </summary>
        /// <param name="string">
        /// Pointer to a null-terminated character sequence of type <c>CharType</c>.
        /// May be <c>nullptr</c>. When <c>nullptr</c> or the sequence is empty the resulting string becomes empty.
        /// </param>
        /// <returns>
        /// A reference to this <see cref="BasicString"/> instance after assignment.
        /// </returns>
        /// <remarks>
        /// <para>
        /// This operator forwards to <see cref="Assign(const CharType*)"/> which performs the actual allocation
        /// and initialization. The operation preserves the reference-counted copy-on-write semantics of
        /// <see cref="BasicString"/>: when necessary a new internal buffer will be allocated and the previous
        /// buffer released. Call <see cref="EnsureUnique"/> before performing in-place mutations through raw
        /// pointers, iterators or references if other <see cref="BasicString"/> instances may share the internal buffer.
        /// </para>
        /// <para>
        /// For Windows-specific or encoding conversions prefer the Harlinn.Common.Core conversion helpers
        /// provided elsewhere in this header (for example <c>Internal::From</c>) when applicable.
        /// </para>
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when underlying memory allocation fails during the assignment performed by the helper.
        /// Underlying allocation helpers (for example <c>Internal::AllocateBytes</c>) will raise a platform-specific error
        /// which is propagated as an exception.
        /// </exception>
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
            return iterator(data_ ? data_->buffer_ : nullptr);
        }

        [[nodiscard]] constexpr iterator end( ) noexcept
        {
            return iterator(data_ ? &data_->buffer_[data_->size_] : nullptr);
        }

        [[nodiscard]] constexpr const_iterator begin( ) const noexcept
        {
            return const_iterator(data_ ? data_->buffer_ : nullptr);
        }

        [[nodiscard]] constexpr const_iterator end( ) const noexcept
        {
            return const_iterator(data_ ? &data_->buffer_[data_->size_] : nullptr);
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
            auto firstSize = LengthOf( first );

            auto secondSize = second.size( );
            auto* secondData = second.data( );

            return BasicString( first, firstSize, secondData, secondSize );
        }

        [[nodiscard]] friend BasicString<CharType> operator +( const BasicString<CharType>& first, const CharType* second )
        {
            auto firstSize = first.size( );
            auto* firstData = first.data( );

            auto secondSize = LengthOf( second );

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
            auto otherLength = LengthOf( other );
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

        iterator Insert( size_type index, const CharType* str, size_type strLength,CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto size = Length( );
            if ( size )
            {
                if ( index < size )
                {
                    if ( strLength )
                    {
                        auto endPtr = Extend( strLength );
                        auto startPtr = data_->buffer_;
                        auto positionPtr = startPtr + index;
                        MemMove( positionPtr + strLength, positionPtr, static_cast< size_t >( endPtr - positionPtr ) );
                        MemCopy( positionPtr, str, strLength );
                        return iterator(positionPtr);
                    }
                    else
                    {
                        return iterator(data_->buffer_ + index);
                    }
                }
                else if ( index == size )
                {
                    if ( strLength )
                    {
                        auto endPtr = Extend( strLength );
                        MemCopy( endPtr, str, strLength );
                        return iterator(endPtr);
                    }
                    else
                    {
                        return iterator(data_->buffer_ + index);
                    }
                }
                else
                {
                    auto padding = index - size;
                    auto endPtr = Extend( padding + strLength );
                    MemSet( endPtr, padCharacter, padding );
                    auto positionPtr = endPtr + padding;
                    MemCopy( positionPtr, str, strLength );
                    return iterator(positionPtr);
                }
            }
            else
            {
                auto endPtr = Extend( index + strLength );
                if ( index )
                {
                    MemSet( endPtr, padCharacter, index );
                    auto positionPtr = endPtr + index;
                    MemCopy( positionPtr, str, strLength );
                    return iterator(positionPtr);
                }
                else
                {
                    MemCopy( endPtr, str, strLength );
                    return iterator(endPtr);
                }
            }
        }

        iterator insert( size_type index, const CharType* str, size_type strLength, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            return Insert( index, str, strLength, padCharacter );
        }

        template<SimpleSpanLike StringT>
            requires std::is_same_v<CharType, typename StringT::value_type>
        iterator Insert( size_type index, const StringT& str, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            return Insert( index, str.data( ), str.size( ), padCharacter );
        }

        template<SimpleSpanLike StringT>
            requires std::is_same_v<CharType, typename StringT::value_type>
        iterator insert( size_type index, const StringT& str, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            return Insert( index, str.data( ), str.size( ), padCharacter );
        }

        iterator Insert( size_type index, const CharType* str, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto strLength = LengthOf( str );
            return Insert( index, str, strLength, padCharacter );
        }
        iterator insert( size_type index, const CharType* str, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto strLength = LengthOf( str );
            return Insert( index, str, strLength, padCharacter );
        }

        iterator Insert( size_type index, size_type count, CharType ch, CharType padCharacter = static_cast< CharType >(' ') )
        {
            auto size = Length( );
            if ( size )
            {
                if ( index < size )
                {
                    if ( count )
                    {
                        auto endPtr = Extend( count );
                        auto startPtr = data_->buffer_;
                        auto positionPtr = startPtr + index;
                        MemMove( positionPtr + count, positionPtr, static_cast< size_t >( endPtr - positionPtr ) );
                        MemSet( positionPtr, ch, count );
                        return iterator(positionPtr);
                    }
                    else
                    {
                        return iterator(data_->buffer_+ index);
                    }
                }
                else if( index == size )
                {
                    if ( count )
                    {
                        auto endPtr = Extend( count );
                        MemSet( endPtr, ch, count );
                        return iterator(endPtr);
                    }
                    else
                    {
                        return iterator(data_->buffer_ + index);
                    }
                }
                else
                {
                    auto padding = index - size;
                    auto endPtr = Extend( padding + count );
                    MemSet( endPtr, padCharacter, padding );
                    auto positionPtr = endPtr + padding;
                    MemSet( positionPtr, ch, count );
                    return iterator(positionPtr);
                }
            }
            else
            {
                auto endPtr = Extend( index + count );
                if ( index )
                {
                    MemSet( endPtr, padCharacter, index );
                    auto positionPtr = endPtr + index;
                    MemSet( positionPtr, ch, count );
                    return iterator(positionPtr);
                }
                else
                {
                    MemSet( endPtr, ch, count );
                    return iterator(endPtr);
                }
            }
        }

        iterator insert( size_type index, size_type count, CharType ch, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            return Insert( index, count, ch, padCharacter );
        }

        iterator Insert( size_type index, CharType ch, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            return Insert( index, 1, ch, padCharacter );
        }

        iterator insert( size_type index, CharType ch, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            return Insert( index, 1, ch, padCharacter );
        }

        
    private:
        size_type ToIndex( const_iterator position ) const
        {
            return static_cast< size_type >( position.ptr_ - data( ) );
        }
    public:
        iterator Insert( const_iterator position, const CharType* str, size_type strLength, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto index = ToIndex( position );
            return Insert( index, str, strLength, padCharacter );
        }
        iterator insert( const_iterator position, const CharType* str, size_type strLength, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto index = ToIndex( position );
            return Insert( index, str, strLength, padCharacter );
        }
        template<SimpleSpanLike StringT>
            requires std::is_same_v<CharType, typename StringT::value_type>
        iterator Insert( const_iterator position, const StringT& str, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto index = ToIndex( position );
            return Insert( index, str.data( ), str.size( ), padCharacter );
        }

        template<SimpleSpanLike StringT>
            requires std::is_same_v<CharType, typename StringT::value_type>
        iterator insert( const_iterator position, const StringT& str, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto index = ToIndex( position );
            return Insert( index, str.data( ), str.size( ), padCharacter );
        }

        iterator Insert( const_iterator position, const CharType* str, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto strLength = LengthOf( str );
            auto index = ToIndex( position );
            return Insert( index, str, strLength, padCharacter );
        }
        iterator insert( const_iterator position, const CharType* str, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto strLength = LengthOf( str );
            auto index = ToIndex( position );
            return Insert( index, str, strLength, padCharacter );
        }

        iterator Insert( const_iterator position, size_type count, CharType ch, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto index = ToIndex( position );
            return Insert( index, count, ch, padCharacter );
        }
        iterator insert( const_iterator position, size_type count, CharType ch, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto index = ToIndex( position );
            return Insert( index, count, ch, padCharacter );
        }

        iterator Insert( const_iterator position, CharType ch, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto index = ToIndex( position );
            return Insert( index, 1, ch, padCharacter );
        }

        iterator insert( const_iterator position, CharType ch, CharType padCharacter = static_cast< CharType >( ' ' ) )
        {
            auto index = ToIndex( position );
            return Insert( index, 1, ch, padCharacter );
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
                        size_type secondSize = LengthOf( second );
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
                    size_type firstSize = LengthOf( first );
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
            size_type length = LengthOf( searchChars );
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
            size_type length = LengthOf( searchChars );
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
            size_type length = LengthOf( searchChars );
            return IndexOfAnyBut( searchChars, length, start );
        }

        [[nodiscard]] size_type find_first_not_of( const CharType* searchChars, size_type start = 0 ) const
        {
            return IndexOfAnyBut( searchChars, start );
        }

        [[nodiscard]] size_type IIndexOfAnyBut( const CharType* searchChars, size_type start = 0 ) const
        {
            size_type length = LengthOf( searchChars );
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
            size_type length = LengthOf( searchChars );
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
            size_type length = LengthOf( searchChars );
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
            size_type length = LengthOf( searchChars );
            if ( length )
            {
                return LastIndexOfAnyBut( searchChars, length, start );
            }
            return data_ ? data_->size_ - 1 : npos;
        }

        [[nodiscard]] size_type ILastIndexOfAnyBut( const CharType* searchChars, size_type start = npos ) const
        {
            size_type length = LengthOf( searchChars );
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
            size_type length = LengthOf( searchString );
            if ( length )
            {

                return LastIndexOf( searchString, length, start );
            }
            return npos;
        }

        [[nodiscard]] size_type ILastIndexOf( const CharType* searchString, size_type start = npos ) const
        {
            size_type length = LengthOf( searchString );
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
                auto otherLength = LengthOf( str );
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
                auto otherLength = LengthOf( str );
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
            return iterator(Erase( static_cast<size_type>(position - begin()) , 1 ));
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
                    Replace( index, whatLength, with, withLength );
                    return true;
                }
            }
            return false;
        }



    };

    template< class CharT, class Traits >
    inline std::basic_ostream<CharT, Traits>& operator<<( std::basic_ostream<CharT, Traits>& os, const BasicString<CharT>& str )
    {
        if ( str.size( ) )
        {
            os.write( str.data( ), static_cast<std::streamsize>( str.size( ) ) );
        }
        return os;
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

    /*
    template<typename T>
    inline BasicString<T>::BasicString( const BasicStringView<T>& v )
        : data_( Initialize( v.data( ), v.size( ) ) )
    {
    }
    */

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
    inline std::wstring to_wstring( const std::string& source )
    {
        std::wstring result;
        ToWideString( source, result );
        return result;
    }

    inline WideString ToWideString( const AnsiString& source )
    {
        WideString result;
        ToWideString( source, result );
        return result;
    }

    inline std::wstring to_wstring( const AnsiString& source )
    {
        std::wstring result;
        ToWideString( source, result );
        return result;
    }



    inline WideString ToWideString( const std::string_view& source )
    {
        WideString result;
        ToWideString( source.data( ), source.size( ), result );
        return result;
    }

    inline std::wstring to_wstring( const std::string_view& source )
    {
        std::wstring result;
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

    inline std::wstring to_wstring( const char* source )
    {
        if ( source && source[ 0 ] )
        {
            auto length = strlen( source );
            std::wstring result;
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

    inline std::wstring to_wstring( const wchar_t* source )
    {
        if ( source && source[ 0 ] )
        {
            auto length = wcslen( source );
            std::wstring result( source, length );
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

    template<AnsiStringLike AnsiStringT = std::string, WideStringLike WideStringT>
    inline AnsiStringT to_string( const WideStringT& source )
    {
        AnsiStringT result;
        ToAnsiString( source, result );
        return result;
    }

    inline void ToAnsiString( const std::wstring_view& source, AnsiString& dest )
    {
        ToAnsiString( source.data( ), source.length( ), CP_ACP, 0, dest );
    }

    inline void to_string( const std::wstring_view& source, std::string& dest )
    {
        ToAnsiString( source.data( ), source.length( ), CP_ACP, 0, dest );
    }

    inline AnsiString ToAnsiString( const std::wstring_view& source )
    {
        AnsiString result;
        ToAnsiString( source, result );
        return result;
    }

    inline std::string to_string( const std::wstring_view& source )
    {
        std::string result;
        to_string( source, result );
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

    inline std::string to_string( const wchar_t* source )
    {
        if ( source && source[ 0 ] )
        {
            auto length = wcslen( source );
            std::string result;
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

    template<AnsiStringLike StringT = std::string>
    inline StringT to_string( const wchar_t* source )
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

    template<AnsiStringLike StringT = std::string>
    inline StringT to_string( const char* source )
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

    inline std::string to_string( const AnsiString& source )
    {
        std::string result( source.c_str( ), source.size( ) );
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
        return std::isalnum( static_cast< int >( std::bit_cast< Byte >( c ) ) );
    }
    inline bool IsAlpha( wchar_t c )
    {
        return std::iswalpha( c );
    }
    inline bool IsAlpha( char c )
    {
        return std::isalpha( static_cast< int >( std::bit_cast< Byte >( c ) ) );
    }
    inline bool IsBlank( wchar_t c )
    {
        return std::iswblank( c );
    }
    inline bool IsBlank( char c )
    {
        return std::isblank( static_cast< int >( std::bit_cast< Byte >( c ) ) );
    }
    inline bool IsCntrl( wchar_t c )
    {
        return std::iswcntrl( c );
    }
    inline bool IsCntrl( char c )
    {
        return std::iscntrl( static_cast< int >( std::bit_cast< Byte >( c ) ) );
    }
    inline bool IsDigit( wchar_t c )
    {
        return std::iswdigit( c );
    }
    inline bool IsDigit( char c )
    {
        return std::isdigit( static_cast< int >( std::bit_cast< Byte >( c ) ) );
    }
    inline bool IsGraph( wchar_t c )
    {
        return std::iswgraph( c );
    }
    inline bool IsGraph( char c )
    {
        return std::isgraph( static_cast< int >( std::bit_cast< Byte >( c ) ) );
    }
    inline bool IsLower( wchar_t c )
    {
        return std::iswlower( c );
    }
    inline bool IsLower( char c )
    {
        return std::islower( static_cast< int >( std::bit_cast< Byte >( c ) ) );
    }
    inline bool IsPrint( wchar_t c )
    {
        return std::iswprint( c );
    }
    inline bool IsPrint( char c )
    {
        return std::isprint( static_cast< int >( std::bit_cast< Byte >( c ) ) );
    }
    inline bool IsPunct( wchar_t c )
    {
        return std::iswpunct( c );
    }
    inline bool IsPunct( char c )
    {
        return std::ispunct( static_cast< int >( std::bit_cast< Byte >( c ) ) );
    }
    inline bool IsSpace( wchar_t c )
    {
        return std::iswspace( c );
    }
    inline bool IsSpace( char c )
    {
        return std::isspace( static_cast<int>( std::bit_cast<Byte>( c ) ) );
    }
    inline bool IsUpper( wchar_t c )
    {
        return std::iswupper( c );
    }
    inline bool IsUpper( char c )
    {
        return std::isupper( static_cast< int >( std::bit_cast< Byte >( c ) ) );
    }
    inline bool IsXDigit( wchar_t c )
    {
        return std::iswxdigit( c );
    }
    inline bool IsXDigit( char c )
    {
        return std::isxdigit( static_cast< int >( std::bit_cast< Byte >( c ) ) );
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

        result.reserve( str.size( ) );

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


    template<typename CharT>
    std::basic_string<CharT> FindAndReplace( const std::basic_string<CharT>& str, const std::basic_string<CharT>& what, const std::basic_string<CharT>& with )
    {
        if ( what.length( ) )
        {

        }
        else
        {
            return str;
        }
    }





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
        template<WideStringLike T>
        HCC_EXPORT T Encode( const wchar_t* text, size_t textLength );

        

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
        template<WideStringLike T>
        HCC_EXPORT T Decode( const wchar_t* text, size_t textLength );

        
        

        template<WideStringLike StringT, typename ArgStringT>
            requires std::is_same_v<ArgStringT, WideString> || std::is_same_v<ArgStringT, std::wstring> || std::is_same_v<ArgStringT, std::wstring_view>
        inline StringT Encode( const ArgStringT& str )
        {
            if ( str.empty( ) == false )
            {
                return Encode<StringT>( str.data( ), str.size( ) );
            }
            return {};
        }

        template<WideStringLike StringT, typename ArgStringT>
            requires std::is_same_v<ArgStringT, WideString> || std::is_same_v<ArgStringT, std::wstring> || std::is_same_v<ArgStringT, std::wstring_view>
        inline StringT Decode( const ArgStringT& str )
        {
            if ( str.empty( ) == false )
            {
                return Decode<StringT>( str.data( ), str.size( ) );
            }
            return {};
        }

        template<AnsiStringLike T>
        inline T Encode( const char* text, size_t textLength )
        {
            WideString ws;
            ToWideString( text, textLength, ws );
            auto encoded = Encode<WideString>( ws );
            T result;
            ToAnsiString( encoded.c_str( ), encoded.size( ), result );
            return result;
        }
        template<AnsiStringLike T>
        inline T Decode( const char* text, size_t textLength )
        {
            WideString ws;
            ToWideString( text, textLength, ws );
            auto decoded = Decode<WideString>( ws );
            T result;
            ToAnsiString( decoded.c_str( ), decoded.size( ), result );
            return result;
        }


        template<AnsiStringLike StringT, typename ArgStringT>
            requires std::is_same_v<ArgStringT, AnsiString> || std::is_same_v<ArgStringT, std::string> || std::is_same_v<ArgStringT, std::string_view>
        inline StringT Encode( const ArgStringT& str )
        {
            if ( str.empty( ) == false )
            {
                return Encode<StringT>( str.data( ), str.size( ) );
            }
            return {};
        }

        template<AnsiStringLike StringT, typename ArgStringT>
            requires std::is_same_v<ArgStringT, AnsiString> || std::is_same_v<ArgStringT, std::string> || std::is_same_v<ArgStringT, std::string_view>
        inline StringT Decode( const ArgStringT& str )
        {
            if ( str.empty( ) == false )
            {
                return Decode<StringT>( str.data( ), str.size( ) );
            }
            return {};
        }
    }

}


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
