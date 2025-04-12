#pragma once
#ifndef PBRTO_UTIL_NEWBUFFERCACHE_H_
#define PBRTO_UTIL_NEWBUFFERCACHE_H_

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
#include <pbrto/util/NewHash.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewStats.h>
#include <pbrto/util/NewVecMath.h>

#include <atomic>
#include <cstring>
#include <shared_mutex>
#include <string>
#include <unordered_set>

namespace pbrto
{

    NSTAT_MEMORY_COUNTER( "Memory/Redundant vertex and index buffers", redundantBufferBytes );
    NSTAT_PERCENT( "Geometry/Buffer cache hits", nBufferCacheHits, nBufferCacheLookups );

    // BufferCache Definition
    template <typename T>
    class BufferCache
    {
    public:
        // BufferCache Public Methods
        const T* LookupOrAdd( pstdo::span<const T> buf, Allocator alloc )
        {
            ++nBufferCacheLookups;
            // Return pointer to data if _buf_ contents are already in the cache
            Buffer lookupBuffer( buf.data( ), buf.size( ) );
            int shardIndex = uint32_t( lookupBuffer.hash ) >> ( 32 - logShards );
            NDCHECK( shardIndex >= 0 && shardIndex < nShards );
            mutex[ shardIndex ].lock_shared( );
            if ( auto iter = cache[ shardIndex ].find( lookupBuffer );
                iter != cache[ shardIndex ].end( ) )
            {
                const T* ptr = iter->ptr;
                mutex[ shardIndex ].unlock_shared( );
                NDCHECK( std::memcmp( buf.data( ), iter->ptr, buf.size( ) * sizeof( T ) ) == 0 );
                ++nBufferCacheHits;
                redundantBufferBytes += buf.size( ) * sizeof( T );
                return ptr;
            }

            // Add _buf_ contents to cache and return pointer to cached copy
            mutex[ shardIndex ].unlock_shared( );
            T* ptr = alloc.allocate_object<T>( buf.size( ) );
            std::copy( buf.begin( ), buf.end( ), ptr );
            bytesUsed += buf.size( ) * sizeof( T );
            mutex[ shardIndex ].lock( );
            // Handle the case of another thread adding the buffer first
            if ( auto iter = cache[ shardIndex ].find( lookupBuffer );
                iter != cache[ shardIndex ].end( ) )
            {
                const T* cachePtr = iter->ptr;
                mutex[ shardIndex ].unlock( );
                alloc.deallocate_object( ptr, buf.size( ) );
                ++nBufferCacheHits;
                redundantBufferBytes += buf.size( ) * sizeof( T );
                return cachePtr;
            }

            cache[ shardIndex ].insert( Buffer( ptr, buf.size( ) ) );
            mutex[ shardIndex ].unlock( );
            return ptr;
        }

        size_t BytesUsed( ) const { return bytesUsed; }

    private:
        // BufferCache::Buffer Definition
        struct Buffer
        {
            // BufferCache::Buffer Public Methods
            Buffer( ) = default;
            Buffer( const T* ptr, size_t size ) : ptr( ptr ), size( size )
            {
                hash = HashBuffer( ptr, size );
            }

            bool operator==( const Buffer& b ) const
            {
                return size == b.size && hash == b.hash &&
                    std::memcmp( ptr, b.ptr, size * sizeof( T ) ) == 0;
            }

            const T* ptr = nullptr;
            size_t size = 0, hash;
        };

        // BufferCache::BufferHasher Definition
        struct BufferHasher
        {
            size_t operator()( const Buffer& b ) const { return b.hash; }
        };

        // BufferCache Private Members
        static constexpr int logShards = 6;
        static constexpr int nShards = 1 << logShards;
        std::shared_mutex mutex[ nShards ];
        std::unordered_set<Buffer, BufferHasher> cache[ nShards ];
        std::atomic<size_t> bytesUsed{};
    };

    // BufferCache Global Declarations
    extern BufferCache<int>* intBufferCache;
    extern BufferCache<Point2f>* point2BufferCache;
    extern BufferCache<Point3f>* point3BufferCache;
    extern BufferCache<Vector3f>* vector3BufferCache;
    extern BufferCache<Normal3f>* normal3BufferCache;

    void InitBufferCaches( );

}

#endif
