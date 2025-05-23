#pragma once
#ifndef PBRTO_UTIL_NEWMEMORY_H_
#define PBRTO_UTIL_NEWMEMORY_H_

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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/NewPbrt.h>

#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewPStd.h>

#include <atomic>
#include <cstddef>
#include <list>
#include <memory>
#include <mutex>
#include <type_traits>
#include <utility>

namespace pbrto
{

    PBRTO_EXPORT
        size_t GetCurrentRSS( );

    class TrackedMemoryResource : public pstdo::pmr::memory_resource
    {
    public:
        TrackedMemoryResource(
            pstdo::pmr::memory_resource* source = pstdo::pmr::get_default_resource( ) )
            : source( source )
        {
        }

        void* do_allocate( size_t size, size_t alignment )
        {
            void* ptr = source->allocate( size, alignment );
            uint64_t currentBytes = allocatedBytes.fetch_add( size ) + size;
            uint64_t prevMax = maxAllocatedBytes.load( std::memory_order_relaxed );
            while ( prevMax < currentBytes &&
                !maxAllocatedBytes.compare_exchange_weak( prevMax, currentBytes ) )
                ;
            return ptr;
        }
        void do_deallocate( void* p, size_t bytes, size_t alignment )
        {
            source->deallocate( p, bytes, alignment );
            allocatedBytes -= bytes;
        }

        bool do_is_equal( const memory_resource& other ) const noexcept
        {
            return this == &other;
        }

        size_t CurrentAllocatedBytes( ) const { return allocatedBytes.load( ); }
        size_t MaxAllocatedBytes( ) const { return maxAllocatedBytes.load( ); }

    private:
        pstdo::pmr::memory_resource* source;
        std::atomic<uint64_t> allocatedBytes{ 0 }, maxAllocatedBytes{ 0 };
    };

    template <typename T>
    struct AllocationTraits
    {
        using SingleObject = T*;
    };
    template <typename T>
    struct AllocationTraits<T[ ]>
    {
        using Array = T*;
    };
    template <typename T, size_t n>
    struct AllocationTraits<T[ n ]>
    {
        struct Invalid {};
    };

    // ScratchBuffer Definition
    class alignas( PBRT_L1_CACHE_LINE_SIZE ) ScratchBuffer
    {
    public:
        // ScratchBuffer Public Methods
        ScratchBuffer( int size = 256 ) : allocSize( size )
        {
            ptr = ( char* )Allocator( ).allocate_bytes( size, align );
        }

        ScratchBuffer( const ScratchBuffer& ) = delete;

        ScratchBuffer( ScratchBuffer&& b )
        {
            ptr = b.ptr;
            allocSize = b.allocSize;
            offset = b.offset;
            smallBuffers = std::move( b.smallBuffers );

            b.ptr = nullptr;
            b.allocSize = b.offset = 0;
        }

        ~ScratchBuffer( )
        {
            Reset( );
            Allocator( ).deallocate_bytes( ptr, allocSize, align );
        }

        ScratchBuffer& operator=( const ScratchBuffer& ) = delete;

        ScratchBuffer& operator=( ScratchBuffer&& b )
        {
            std::swap( b.ptr, ptr );
            std::swap( b.allocSize, allocSize );
            std::swap( b.offset, offset );
            std::swap( b.smallBuffers, smallBuffers );
            return *this;
        }

        void* Alloc( size_t size, size_t align )
        {
            if ( ( offset % align ) != 0 )
                offset += align - ( offset % align );
            if ( offset + size > allocSize )
                Realloc( size );
            void* p = ptr + offset;
            offset += size;
            return p;
        }

        template <typename T, typename... Args>
        typename AllocationTraits<T>::SingleObject Alloc( Args &&...args )
        {
            T* p = ( T* )Alloc( sizeof( T ), alignof( T ) );
            return new ( p ) T( std::forward<Args>( args )... );
        }

        template <typename T>
        typename AllocationTraits<T>::Array Alloc( size_t n = 1 )
        {
            using ElementType = typename std::remove_extent_t<T>;
            ElementType* ret =
                ( ElementType* )Alloc( n * sizeof( ElementType ), alignof( ElementType ) );
            for ( size_t i = 0; i < n; ++i )
                new ( &ret[ i ] ) ElementType( );
            return ret;
        }

        void Reset( )
        {
            for ( const auto& buf : smallBuffers )
                Allocator( ).deallocate_bytes( buf.first, buf.second, align );
            smallBuffers.clear( );
            offset = 0;
        }

    private:
        // ScratchBuffer Private Methods
        void Realloc( size_t minSize )
        {
            smallBuffers.push_back( std::make_pair( ptr, allocSize ) );
            allocSize = std::max( 2 * minSize, allocSize + minSize );
            ptr = ( char* )Allocator( ).allocate_bytes( allocSize, align );
            offset = 0;
        }

        // ScratchBuffer Private Members
        static constexpr int align = PBRT_L1_CACHE_LINE_SIZE;
        char* ptr = nullptr;
        int allocSize = 0, offset = 0;
        std::list<std::pair<char*, size_t>> smallBuffers;
    };

}

#endif
