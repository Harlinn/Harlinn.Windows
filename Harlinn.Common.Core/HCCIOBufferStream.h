#pragma once
#ifndef __HCCIOBUFFERSTREAM_H__
#define __HCCIOBUFFERSTREAM_H__
/*
   Copyright 2024-2026 Espen Harlinn

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

#include <HCCIOBase.h>

namespace Harlinn::Common::Core::IO
{
    /// <summary>
    /// Implements a stream for a buffer 
    /// </summary>
    class BufferStream
    {
        Byte* start_;
        Byte* end_;
        Byte* current_;
    public:
        constexpr BufferStream( ) noexcept
            : start_( nullptr ), end_( nullptr ), current_( nullptr )
        {
        }
        constexpr BufferStream( Byte* buffer, size_t bufferSize ) noexcept
            : start_( buffer ), end_( buffer + bufferSize ), current_( buffer )
        {
        }

        constexpr void Assign( Byte* buffer, size_t bufferSize ) noexcept
        {
            start_ = buffer;
            end_ = buffer + bufferSize;
            current_ = buffer;
        }

        constexpr bool CanRead( ) const noexcept
        {
            return true;
        }
        constexpr bool CanSeek( ) const noexcept
        {
            return true;
        }
        constexpr bool CanTimeout( ) const noexcept
        {
            return false;
        }
        constexpr bool CanWrite( ) const noexcept
        {
            return true;
        }

        constexpr void Flush( ) const noexcept
        {
        }

        constexpr long long Position( ) const noexcept
        {
            return static_cast<long long>( current_ - start_ );
        }
        constexpr void SetPosition( long long position ) noexcept
        {
            if ( position < Size( ) )
            {
                current_ = start_ + position;
            }
            else
            {
                current_ = end_;
            }
        }

        constexpr long long Size( ) const noexcept
        {
            return static_cast<long long>( end_ - start_ );
        }
        void SetSize( long long size )
        {
            if ( size != Size( ) )
            {
                //HCC_THROW( InvalidOperationException, L"Cannot change the size of a buffer stream." );
            }
        }

        long long Read( void* buffer, size_t numberOfBytesToRead ) noexcept
        {
            if ( current_ + numberOfBytesToRead > end_ )
            {
                numberOfBytesToRead = end_ - current_;
            }
            memcpy( buffer, current_, numberOfBytesToRead );
            current_ += numberOfBytesToRead;
            return static_cast<long long>( numberOfBytesToRead );
        }
        long long Write( const void* buffer, size_t numberOfBytesToWrite ) noexcept
        {
            if ( current_ + numberOfBytesToWrite > end_ )
            {
                numberOfBytesToWrite = end_ - current_;
            }
            memcpy( current_, buffer, numberOfBytesToWrite );
            current_ += numberOfBytesToWrite;
            return static_cast<long long>( numberOfBytesToWrite );
        }
        long long Seek( long long offset, SeekOrigin seekOrigin ) noexcept
        {
            long long size = static_cast<long long>( end_ - start_ );
            long long newPosition = 0;
            size_t currentPosition = current_ - start_;
            switch ( seekOrigin )
            {
                case SeekOrigin::StartOfFile:
                    if ( offset > 0 )
                    {
                        newPosition = offset;
                    }
                    break;
                case SeekOrigin::CurrentPosition:
                    newPosition = static_cast<long long>( currentPosition ) + offset;
                    break;
                case SeekOrigin::EndOfFile:
                    newPosition = size + offset;
                    break;
            }
            if ( newPosition < 0 )
            {
                newPosition = 0;
                current_ = start_;
            }
            else if ( newPosition > size )
            {
                newPosition = size;
                current_ = end_;
            }
            else
            {
                current_ = start_ + static_cast<size_t>( newPosition );
            }
            return newPosition;
        }
    };

    static_assert( StreamReader<BufferStream> );
    static_assert( StreamWriter<BufferStream> );
    static_assert( StreamSeek<BufferStream> );
    static_assert( StreamPosition<BufferStream> );
    static_assert( StreamSize<BufferStream> );
    static_assert( StreamFlush<BufferStream> );
    static_assert( StreamFeatureTests<BufferStream> );
    static_assert( Stream<BufferStream> );
}


#endif
