#pragma once 
#ifndef HARLINN_MEDIA_GST_HWMGSTMEMORY_H_
#define HARLINN_MEDIA_GST_HWMGSTMEMORY_H_

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

#include "HWMGstMiniObject.h"

namespace Harlinn::Media::GStreamer
{
    class BasicObject;
    class Object;
    namespace Internal
    {
        template<typename BaseT>
        class AllocatorImpl;
        template<typename BaseT>
        class MemoryImpl;
    }

    using BasicAllocator = Internal::AllocatorImpl<BasicObject>;
    using Allocator = Internal::AllocatorImpl<Object>;

    using BasicMemory = Internal::MemoryImpl<BasicMiniObject>;
    using Memory = Internal::MemoryImpl<MiniObject>;


    namespace Internal
    {
        template<typename BaseT>
        class MemoryImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GSTMINIOBJECT_IMPLEMENT_STANDARD_MEMBERS( MemoryImpl, GstMemory )

            BasicAllocator Allocator( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const;

            BasicMemory Parent( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const
            {
                return BasicMemory( get( )->parent, referenceType );
            }

            size_t MaxSize( ) const
            {
                return get( )->maxsize;
            }
            size_t Align( ) const
            {
                return get( )->align;
            }

            size_t Offset( ) const
            {
                return get( )->offset;
            }
            size_t Size( ) const
            {
                return get( )->size;
            }

            size_t SizeInfo( size_t* offset, size_t* maxsize ) const
            {
                return gst_memory_get_sizes( get(), offset, maxsize );
            }

            void Resize( ssize_t offset, size_t size ) const
            {
                gst_memory_resize( get( ), offset, size );
            }

            GStreamer::Memory MakeWritable( ) const
            {
                //return Base::MakeWritable<GStreamer::Buffer>( );
                auto memory = gst_memory_make_writable( get( ) );
                if ( memory )
                {
                    return GStreamer::Memory( memory );
                }
                return {};
            }

            GStreamer::Memory MakeMapped( GstMapInfo* info, GstMapFlags flags ) const
            {
                auto memory = gst_memory_make_mapped( get( ), info, flags );
                if ( memory )
                {
                    return GStreamer::Memory( memory );
                }
                return {};
            }

            bool Map( GstMapInfo* info, GstMapFlags flags ) const
            {
                return gst_memory_map( get( ), info, flags ) != 0;
            }

            void Map( GstMapInfo* info ) const
            {
                gst_memory_unmap( get( ), info ) != 0;
            }

            GStreamer::Memory Share( ssize_t offset, ssize_t size ) const
            {
                auto memory = gst_memory_share( get( ), offset, size );
                if ( memory )
                {
                    return GStreamer::Memory( memory );
                }
                return {};
            }

            GStreamer::Memory Copy( ssize_t offset, ssize_t size ) const
            {
                auto memory = gst_memory_copy( get( ), offset, size );
                if ( memory )
                {
                    return GStreamer::Memory( memory );
                }
                return {};
            }

            bool IsSpan( GstMemory* mem, size_t* offset ) const
            {
                return gst_memory_is_span( get( ), mem, offset ) != 0;
            }
            template<typename T>
                requires std::is_base_of_v<GStreamer::BasicMemory, T> || std::is_base_of_v<GStreamer::Memory, T>
            bool IsSpan( const T& mem, size_t* offset ) const
            {
                return gst_memory_is_span( get( ), mem.get(), offset ) != 0;
            }

        };
    }
    static_assert( sizeof( BasicMemory ) == sizeof( GstMemory* ) );
    static_assert( sizeof( Memory ) == sizeof( GstMemory* ) );
    static_assert( std::is_base_of_v<BasicMiniObject, BasicMemory> );
    static_assert( std::is_base_of_v<MiniObject, Memory> );
}

#endif

