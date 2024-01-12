#pragma once
#ifndef HARLINN_MEDIA_GST_HWMGSTBUFFER_H_
#define HARLINN_MEDIA_GST_HWMGSTBUFFER_H_

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

#include "HWMGstMemory.h"

namespace Harlinn::Media::GStreamer
{
    namespace Internal
    {
        template<typename BaseT>
        class Buffer;
    }
    using BasicBuffer = Internal::Buffer<BasicMiniObject>;
    using Buffer = Internal::Buffer<MiniObject>;

    namespace Internal
    {
        template<typename BaseT>
        class Buffer : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GSTMINIOBJECT_IMPLEMENT_STANDARD_MEMBERS( Buffer, GstBuffer )

            /// <summary>
            /// Creates a newly allocated buffer without any data.
            /// </summary>
            /// <returns>
            /// The new Buffer.
            /// </returns>
            static GStreamer::Buffer Create( )
            {
                return GStreamer::Buffer( gst_buffer_new( ) );
            }

            /// <summary>
            /// <para>
            /// Tries to create a newly allocated buffer with data of the given size and extra 
            /// parameters from allocator. If the requested amount of memory can't be allocated, 
            /// NULL will be returned. The allocated buffer memory is not cleared.
            /// </para>
            /// <para>
            /// When allocator is nullptr, the default memory allocator will be used.
            /// </para>
            /// <para>
            /// Note that when size == 0, the buffer will not have memory associated with it.
            /// </para>
            /// </summary>
            /// <param name="allocator">
            ///  the GstAllocator to use, or nullptr to use the default allocator
            /// </param>
            /// <param name="size">
            ///  the size in bytes of the new buffer's data.
            /// </param>
            /// <param name="params">
            /// optional parameters
            /// </param>
            /// <returns>
            /// The new Buffer.
            /// </returns>
            static GStreamer::Buffer Create( GstAllocator* allocator, size_t size, GstAllocationParams* params = nullptr )
            {
                return GStreamer::Buffer( gst_buffer_new_allocate( allocator, size, params ) );
            }

            /// <summary>
            /// <para>
            /// Allocates a new buffer that wraps the given memory. data must point to maxsize of memory, 
            /// the wrapped buffer will have the region from offset and size visible.
            /// </para>
            /// <para>
            /// When the buffer is destroyed, notify will be called with user_data.
            /// </para>
            /// <para>
            /// The prefix/padding must be filled with 0 if flags contains 
            /// GST_MEMORY_FLAG_ZERO_PREFIXED and GST_MEMORY_FLAG_ZERO_PADDED respectively.
            /// </para>
            /// </summary>
            /// <param name="flags">
            /// GstMemoryFlags
            /// </param>
            /// <param name="data">
            /// Data to wrap.
            /// </param>
            /// <param name="maxsize">
            /// Allocated size of data.
            /// </param>
            /// <param name="offset">
            /// Offset in data.
            /// </param>
            /// <param name="size">
            /// Size of valid data.
            /// </param>
            /// <param name="userData">
            /// User data passed to notify.
            /// </param>
            /// <param name="notify">
            /// Called with userData when the memory is freed.
            /// </param>
            /// <returns>
            /// The new Buffer.
            /// </returns>
            static GStreamer::Buffer Create( GstMemoryFlags flags, gpointer data, size_t maxsize, size_t offset, size_t size, gpointer userData, GDestroyNotify notify )
            {
                return GStreamer::Buffer( gst_buffer_new_wrapped_full( flags, data, maxsize, offset, size, userData, notify ) );
            }

            /// <summary>
            /// Creates a new buffer that wraps the given data. The memory will be 
            /// freed with g_free and will be marked writable.
            /// </summary>
            /// <param name="data">
            /// The data to wrap.
            /// </param>
            /// <param name="size">
            /// The allocated size of the data.
            /// </param>
            /// <returns>
            /// The new Buffer.
            /// </returns>
            static GStreamer::Buffer Create( gpointer data, size_t size )
            {
                return GStreamer::Buffer( gst_buffer_new_wrapped( data, size ) );
            }


            /// <summary>
            /// Creates a new Buffer that wraps the given bytes. The data inside bytes cannot be 
            /// nullptr and the resulting buffer will be marked as read only..
            /// </summary>
            /// <param name="bytes">
            /// The GBytes to wrap.
            /// </param>
            /// <returns>
            /// The new Buffer.
            /// </returns>
            static GStreamer::Buffer Create( GBytes* bytes )
            {
                return GStreamer::Buffer( gst_buffer_new_wrapped_bytes( bytes ) );
            }

            /// <summary>
            /// Creates a new buffer of size size and fills it with a copy of data.
            /// </summary>
            /// <param name="data">
            /// The data to copy into the new buffer.
            /// </param>
            /// <param name="size">
            /// The size of the data in bytes
            /// </param>
            /// <returns>
            /// The new Buffer.
            /// </returns>
            static GStreamer::Buffer MemDup( gconstpointer data, size_t size )
            {
                return GStreamer::Buffer( gst_buffer_new_memdup( data, size ) );
            }

            /// <summary>
            /// Retrieves the number of memory blocks that this buffer has. 
            /// This number is never larger than what MaxMemory() returns.
            /// </summary>
            UInt32 MemoryCount( ) const
            {
                return gst_buffer_n_memory( get() );
            }

            /// <summary>
            /// <para>
            /// Inserts the memory block mem into buffer at idx. This function 
            /// takes ownership of mem and thus doesn't increase its refcount.
            /// </para>
            /// <para>
            /// Only MaxMemory() can be added to a buffer.If more memory is added, 
            /// existing memory blocks will automatically be merged to make room 
            /// for the new memory.
            /// </para>
            /// </summary>
            /// <param name="index">
            ///  the index to add the memory at, or -1 to append it to the end.
            /// </param>
            /// <param name="mem">
            /// A pointer to the GstMemory instance.
            /// </param>
            void Insert( Int32 index, GstMemory* mem ) const
            {
                gst_buffer_insert_memory( get(), index, mem );
            }
            template<typename T>
                requires std::is_base_of_v<GStreamer::BasicMemory,T> || std::is_base_of_v<GStreamer::Memory, T>
            void Insert( Int32 index, T& mem ) const
            {
                gst_buffer_insert_memory( get( ), index, mem.Detach() );
            }

            /// <summary>
            /// <para>
            /// Replaces length memory blocks in buffer starting at index with mem.
            /// </para>
            /// <para>
            /// If length is -1, all memory starting from idx will be removed and replaced with mem.
            /// </para>
            /// <para>
            /// This function takes ownership of mem and thus doesn't increase its refcount.
            /// </para>
            /// </summary>
            /// <param name="index">
            /// The index of the first memory block that will be replaced.
            /// </param>
            /// <param name="length">
            /// The number of memory blocks to replace, or -1 to replace all the remaining memory blocks
            /// starting with the memory block at index. 
            /// </param>
            /// <param name="mem">
            /// 
            /// </param>
            void Replace( UInt32 index, Int32 length, GstMemory* mem ) const
            {
                gst_buffer_replace_memory_range( get(), index, length, mem );
            }
            template<typename T>
                requires std::is_base_of_v<GStreamer::BasicMemory, T> || std::is_base_of_v<GStreamer::Memory, T>
            void Replace( UInt32 index, Int32 length, T& mem ) const
            {
                gst_buffer_replace_memory_range( get( ), index, length, mem.Detach() );
            }

            /// <summary>
            /// <para>
            /// Replaces the memory block at index idx in buffer with mem.
            /// </para>
            /// <para>
            /// This function takes ownership of mem and thus doesn't increase its refcount.
            /// </para>
            /// </summary>
            /// <param name="index">
            /// The index of the buffer to replace.
            /// </param>
            /// <param name="mem">
            /// The replacement memory block.
            /// </param>
            void Replace( UInt32 index, GstMemory* mem ) const
            {
                gst_buffer_replace_memory( get( ), index, mem );
            }
            template<typename T>
                requires std::is_base_of_v<GStreamer::BasicMemory, T> || std::is_base_of_v<GStreamer::Memory, T>
            void Replace( UInt32 index, T& mem ) const
            {
                gst_buffer_replace_memory( get( ), index, mem.Detach() );
            }

            /// <summary>
            /// <para>
            /// Replaces all memory in buffer with mem.
            /// </para>
            /// <para>
            /// This function takes ownership of mem and thus doesn't increase its refcount.
            /// </para>
            /// </summary>
            /// <param name="mem">
            /// The replacement memory block.
            /// </param>
            void Replace( GstMemory* mem ) const
            {
                gst_buffer_replace_all_memory( get( ), mem );
            }
            template<typename T>
                requires std::is_base_of_v<GStreamer::BasicMemory, T> || std::is_base_of_v<GStreamer::Memory, T>
            void Replace( T& mem ) const
            {
                gst_buffer_replace_all_memory( get( ), mem.Detach() );
            }


            /// <summary>
            /// Gets the memory block at index in buffer. The memory block stays valid until 
            /// the memory block in buffer is removed, replaced or merged, typically with 
            /// any call that modifies the memory in buffer.
            /// </summary>
            /// <param name="index">
            /// The index of the requested memory block.
            /// </param>
            /// <returns>
            /// The memory block at index.
            /// </returns>
            GStreamer::BasicMemory Peek( UInt32 index ) const
            {
                auto memory = gst_buffer_peek_memory( get( ), index );
                if ( memory )
                {
                    return GStreamer::BasicMemory( memory );
                }
                return {};
            }
            GStreamer::BasicMemory operator[]( size_t index ) const
            {
                return Peek( static_cast< UInt32 >( index ) );
            }

            /// <summary>
            /// <para>
            /// Gets length memory blocks in buffer starting at index. The memory blocks will be merged into one large memory block.
            /// </para>
            /// <para>
            /// If length is -1, all memory starting from index is merged.
            /// </para>
            /// </summary>
            /// <param name="index">
            /// The index of the first memory block to copy.
            /// </param>
            /// <param name="length">
            /// The number of memory blocks to copy, or -1 to copy the remaining memory blocks.
            /// </param>
            /// <returns>
            /// A memory block that contains the merged data of length blocks starting at index.
            /// </returns>
            GStreamer::Memory Range( UInt32 index, Int32 length ) const
            {
                auto memory = gst_buffer_get_memory_range( get(), index, length );
                if ( memory )
                {
                    return GStreamer::Memory( memory );
                }
                return {};
            }

            /// <summary>
            /// <para>
            /// Removes length memory blocks in buffer starting from index.
            /// </para>
            /// <para>
            /// length can be -1, in which case all memory starting from index is removed.
            /// </para>
            /// </summary>
            /// <param name="index">
            /// The index of the first memory block to remove.
            /// </param>
            /// <param name="length">
            /// The number of memory blocks to remove, or -1 to remove the remaining memory blocks.
            /// </param>
            void Remove( UInt32 index, Int32 length ) const
            {
                gst_buffer_remove_memory_range( get(), index, length );
            }

            /// <summary>
            /// Removes all the memory blocks in the buffer.
            /// </summary>
            void RemoveAll( ) const
            {
                gst_buffer_remove_all_memory( get() );
            }
            /// <summary>
            /// Removes all the memory blocks in the buffer.
            /// </summary>
            void clear( ) const
            {
                gst_buffer_remove_all_memory( get( ) );
            }

            /// <summary>
            /// <para>
            /// Prepends the memory block mem to buffer. This function takes ownership of 
            /// mem and thus doesn't increase its refcount.
            /// </para>
            /// <para>
            /// This function is identical to Insert with an index of 0. 
            /// </para>
            /// </summary>
            /// <param name="mem">
            /// The memory block to prepend to the buffer.
            /// </param>
            void Prepend( GstMemory* mem ) const
            {
                gst_buffer_prepend_memory( get( ), mem );
            }
            template<typename T>
                requires std::is_base_of_v<GStreamer::BasicMemory, T> || std::is_base_of_v<GStreamer::Memory, T>
            void Prepend( T& mem ) const
            {
                gst_buffer_prepend_memory( get( ), mem.Detach() );
            }

            /// <summary>
            /// <para>
            /// Appends the memory block mem to buffer. This function takes ownership 
            /// of mem and thus doesn't increase its refcount.
            /// </para>
            /// <para>
            /// This function is identical to Insert with an index of -1.
            /// </para>
            /// </summary>
            /// <param name="mem">
            /// The memory block to append to the buffer.
            /// </param>
            void Append( GstMemory* mem ) const
            {
                gst_buffer_append_memory( get( ), mem );
            }
            template<typename T>
                requires std::is_base_of_v<GStreamer::BasicMemory, T> || std::is_base_of_v<GStreamer::Memory, T>
            void Append( T& mem ) const
            {
                gst_buffer_append_memory( get( ), mem.Detach() );
            }


            /// <summary>
            /// Retrieves the memory block at index in buffer.
            /// </summary>
            /// <param name="index"></param>
            /// <returns>
            /// The index of the memory block to retrieve.
            /// </returns>
            GStreamer::Memory At( UInt32 index ) const
            {
                auto memory = gst_buffer_get_memory( get(), index );
                if ( memory )
                {
                    return GStreamer::Memory( memory );
                }
                return {};
            }

            /// <summary>
            /// Gets all the memory blocks in buffer. The memory blocks will be merged into one large memory block.
            /// </summary>
            /// <returns>
            /// The merged memory block.
            /// </returns>
            GStreamer::Memory Merged( ) const
            {
                auto memory = gst_buffer_get_all_memory( get( ) );
                if ( memory )
                {
                    return GStreamer::Memory( memory );
                }
                return {};
            }
            GStreamer::Memory All( ) const
            {
                return Merged( );
            }

            /// <summary>
            /// <para>
            /// Finds the memory blocks that span size bytes starting from offset in buffer.
            /// </para>
            /// <para>
            /// When this function returns TRUE, idx will contain the index of the first memory 
            /// block where the byte for offset can be found and length contains the number of 
            /// memory blocks containing the size remaining bytes.skip contains the number of 
            /// bytes to skip in the memory block at idx to get to the byte for offset.
            /// </para>
            /// <para>
            /// size can be -1 to get all the memory blocks after index.
            /// </para>
            /// </summary>
            /// <param name="offset">
            /// The offset to look for.
            /// </param>
            /// <param name="size">
            /// The number of bytes to look for.
            /// </param>
            /// <param name="index">
            /// On success index will contain the index of the first memory block where 
            /// the byte for offset can be found.
            /// </param>
            /// <param name="length">
            /// On success length contains the number of memory blocks containing the size remaining bytes.
            /// </param>
            /// <param name="skip">
            /// On success skip contains the number of bytes to skip in the 
            /// memory block at index to get to the byte for offset.
            /// </param>
            /// <returns></returns>
            bool Find( size_t offset, size_t size, UInt32* index, UInt32* length, size_t* skip ) const
            {
                return gst_buffer_find_memory( get(), offset, size, index, length, skip ) != 0;
            }

            /// <summary>
            /// <para>
            /// Checks if length memory blocks in buffer starting from index are writable.
            /// </para>
            /// <para>
            /// length can be -1 to check all the memory blocks after index.
            /// </para>
            /// <para>
            /// Note that this function does not check if buffer is writable, use IsWritable to check that if needed.
            /// </para>
            /// </summary>
            /// <param name="index">
            /// Index of first memory block.
            /// </param>
            /// <param name="length">
            /// Number of memory blocks to check, or -1 to check all the memory blocks after index.
            /// </param>
            /// <returns>
            /// true if the all the requested memory blocks are writable.
            /// </returns>
            bool IsRangeWritable( UInt32 index, Int32 length ) const
            {
                return gst_buffer_is_memory_range_writable( get( ), index, length ) != 0;
            }

            /// <summary>
            /// <para>
            /// Checks if all memory blocks in buffer are writable.
            /// </para>
            /// <para>
            /// Note that this function does not check if buffer is writable, use IsWritable to check that if needed.
            /// </para>
            /// </summary>
            /// <returns>
            /// true if all the memory blocks in the buffer are writable.
            /// </returns>
            bool IsAllWritable( ) const
            {
                return gst_buffer_is_all_memory_writable( get( ) ) != 0;
            }

            /// <summary>
            /// Copies size bytes from src to buffer at offset.
            /// </summary>
            /// <param name="offset">
            /// destination offset in buffer.
            /// </param>
            /// <param name="src">
            /// The source address.
            /// </param>
            /// <param name="size">
            /// The number of bytes to copy.
            /// </param>
            /// <returns>
            /// The number of of bytes copied. This value can be less than size if 
            /// the buffer is not large enough to hold the data.
            /// </returns>
            size_t Fill( size_t offset, gconstpointer src, size_t size ) const
            {
                return gst_buffer_fill( get(), offset, src, size );
            }


            /// <summary>
            /// Copies size bytes starting from offset in buffer to dest.
            /// </summary>
            /// <param name="offset">
            /// The offset to extract.
            /// </param>
            /// <param name="dest">
            /// The destination address.
            /// </param>
            /// <param name="size">
            /// The number of bytes to extract.
            /// </param>
            /// <returns>
            /// The amount of bytes extracted. This value can be lower than size when buffer did not contain enough data.
            /// </returns>
            size_t Extract( size_t offset, gpointer dest, size_t size ) const
            {
                return gst_buffer_extract( get(), offset, dest, size );
            }


            /// <summary>
            /// Compares size bytes starting from offset in buffer with the memory in mem.
            /// </summary>
            /// <param name="offset">
            /// The offset into the buffer.
            /// </param>
            /// <param name="mem">
            /// The memory to compare.
            /// </param>
            /// <param name="size">
            /// The size to compare
            /// </param>
            /// <returns>
            /// 0 if the memory is equal.
            /// </returns>
            Int32 MemCmp( size_t offset, gconstpointer mem, size_t size ) const
            {
                return gst_buffer_memcmp( get(), offset, mem, size );
            }


            size_t MemSet( size_t offset, Byte val, size_t size ) const
            {
                return gst_buffer_memset( get(), offset, val, size );
            }

            size_t SizeInfoOfRange( UInt32 index, Int32 length, size_t* offset, size_t* maxsize ) const
            {
                return gst_buffer_get_sizes_range( get(), index, length, offset, maxsize );
            }

            bool ResizeRange( UInt32 index, Int32 length, ssize_t offset, ssize_t size )
            {
                return gst_buffer_resize_range( get(), index, length, offset, size ) != 0;
            }

            size_t SizeInfo( size_t* offset, size_t* maxsize ) const
            {
                return gst_buffer_get_sizes( get( ), offset, maxsize );
            }

            size_t size( ) const
            {
                return gst_buffer_get_size( get( ) );
            }
            size_t Size( ) const
            {
                return gst_buffer_get_size( get( ) );
            }

            void Resize( ssize_t offset, ssize_t size ) const
            {
                gst_buffer_resize( get(), offset, size );
            }


            void SetSize( ssize_t size ) const
            {
                gst_buffer_set_size( get(), size );
            }

            bool MapRange( UInt32 index, Int32 length, GstMapInfo* info, GstMapFlags flags ) const
            {
                return gst_buffer_map_range( get(), index, length, info, flags ) != 0;
            }

            bool Map( GstMapInfo* info, GstMapFlags flags ) const
            {
                return gst_buffer_map( get( ), info, flags ) != 0;
            }

            void Unmap( GstMapInfo* info ) const
            {
                gst_buffer_unmap( get(), info );
            }


            void ExtractDup( size_t offset, size_t size, gpointer* dest, size_t* destSize ) const
            {
                gst_buffer_extract_dup( get(), offset, size, dest, destSize );
            }

            void ExtractDup( size_t offset, size_t size, GLib::FreeMemoryPtr<Byte[]>& dest, size_t* destSize ) const
            {
                gpointer dst = nullptr;
                gst_buffer_extract_dup( get( ), offset, size, &dst, destSize );
                dest.reset( dst );
            }

            GstBufferFlags Flags( ) const
            {
                return gst_buffer_get_flags( get( ) );
            }
            bool HasFlags( GstBufferFlags flags ) const
            {
                return gst_buffer_has_flags( get( ), flags ) != 0;
            }
            bool SetFlags( GstBufferFlags flags )
            {
                return gst_buffer_set_flags( get( ), flags ) != 0;
            }
            bool UnsetFlags( GstBufferFlags flags )
            {
                return gst_buffer_unset_flags( get( ), flags ) != 0;
            }

            GStreamer::Buffer Copy( ) const
            {
                auto buffer = gst_buffer_copy( get( ) );
                if ( buffer )
                {
                    return GStreamer::Buffer( buffer );
                }
                return {};
            }

            GStreamer::Buffer CopyDeep( ) const
            {
                auto buffer = gst_buffer_copy_deep( get( ) );
                if ( buffer )
                {
                    return GStreamer::Buffer( buffer );
                }
                return {};
            }

            bool CopyTo( GstBuffer* dest, GstBufferCopyFlags flags, size_t offset, size_t size ) const
            {
                return gst_buffer_copy_into( dest, get(), flags, offset, size );
            }

            template<typename T>
                requires std::is_base_of_v<GStreamer::BasicMemory, T> || std::is_base_of_v<GStreamer::Memory, T>
            bool CopyTo( const T& dest, GstBufferCopyFlags flags, size_t offset, size_t size ) const
            {
                return gst_buffer_copy_into( dest.get(), get( ), flags, offset, size );
            }

            bool CopyFrom( GstBuffer* source, GstBufferCopyFlags flags, size_t offset, size_t size ) const
            {
                return gst_buffer_copy_into( get( ), source, flags, offset, size );
            }
            template<typename T>
                requires std::is_base_of_v<GStreamer::BasicMemory, T> || std::is_base_of_v<GStreamer::Memory, T>
            bool CopyFrom( const T& source, GstBufferCopyFlags flags, size_t offset, size_t size ) const
            {
                return gst_buffer_copy_into( get( ), source.get(), flags, offset, size );
            }

            bool IsWritable( ) const
            {
                return gst_buffer_is_writable( get( ) ) != 0;
            }

            GStreamer::Buffer MakeWritable( ) const
            {
                //return Base::MakeWritable<GStreamer::Buffer>( );
                auto buffer = gst_buffer_make_writable( get( ) );
                if ( buffer )
                {
                    return GStreamer::Buffer( buffer );
                }
                return {};
            }

            GStreamer::Buffer CopyRegion( GstBufferCopyFlags flags, size_t offset, size_t size ) const
            {
                auto buffer = gst_buffer_copy_region( get( ), flags, offset, size );
                if ( buffer )
                {
                    return GStreamer::Buffer( buffer );
                }
                return {};
            }

            static GStreamer::Buffer Append( GstBuffer* buf1, GstBuffer* buf2, ssize_t offset, ssize_t size )
            {
                auto buffer = gst_buffer_append_region( buf1, buf2, offset, size );
                if ( buffer )
                {
                    return GStreamer::Buffer( buffer );
                }
                return {};
            }

            template<typename T1, typename T2>
                requires ((std::is_base_of_v<GStreamer::BasicMemory, T1> || std::is_base_of_v<GStreamer::Memory, T1>) &&
                            ( std::is_base_of_v<GStreamer::BasicMemory, T2> || std::is_base_of_v<GStreamer::Memory, T2> ))
            static GStreamer::Buffer Append( T1& buf1, T2& buf2, ssize_t offset, ssize_t size )
            {
                auto buffer = gst_buffer_append_region( buf1.Detach(), buf2.Detach( ), offset, size );
                if ( buffer )
                {
                    return GStreamer::Buffer( buffer );
                }
                return {};
            }

            static GStreamer::Buffer Append( GstBuffer* buf1, GstBuffer* buf2 )
            {
                auto buffer = gst_buffer_append( buf1, buf2 );
                if ( buffer )
                {
                    return GStreamer::Buffer( buffer );
                }
                return {};
            }

            template<typename T1, typename T2>
                requires ( ( std::is_base_of_v<GStreamer::BasicMemory, T1> || std::is_base_of_v<GStreamer::Memory, T1> ) &&
                    ( std::is_base_of_v<GStreamer::BasicMemory, T2> || std::is_base_of_v<GStreamer::Memory, T2> ) )
            static GStreamer::Buffer Append( T1& buf1, T2& buf2 )
            {
                auto buffer = gst_buffer_append( buf1.Detach( ), buf2.Detach( ) );
                if ( buffer )
                {
                    return GStreamer::Buffer( buffer );
                }
                return {};
            }

        };
    }

    

    static_assert( sizeof( BasicBuffer ) == sizeof( GstBuffer* ) );
    static_assert( sizeof( Buffer ) == sizeof( GstBuffer* ) );



}
#endif
