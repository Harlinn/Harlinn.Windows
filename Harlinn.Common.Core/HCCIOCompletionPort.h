#pragma once
#ifndef __HCCIOCOMPLETIONPORT_H__
#define __HCCIOCOMPLETIONPORT_H__
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

#include <HCCIORequest.h>

namespace Harlinn::Common::Core::IO
{
    namespace Sockets
    {
        class Socket;
    }

    /// <summary>
    ///  
    /// </summary>
    /// <remarks>
    /// I/O completion ports provide an efficient threading model for processing multiple asynchronous 
    /// I/O requests on a multiprocessor system. When a process creates an I/O completion port, the 
    /// system creates an associated queue object for requests whose sole purpose is to service these requests. 
    /// Processes that handle many concurrent asynchronous I/O requests can do so more quickly and efficiently 
    /// by using I/O completion ports in conjunction with a pre-allocated thread pool than by creating threads 
    /// at the time they receive an I/O request.
    /// </remarks>
    class IOCompletionPort
    {
        HANDLE handle_;
    public:
        HCC_EXPORT IOCompletionPort( DWORD numberOfConcurrentThreads );

        IOCompletionPort( const IOCompletionPort& other ) = delete;

        IOCompletionPort( IOCompletionPort&& other ) noexcept
            : handle_( other.handle_ )
        {
            other.handle_ = INVALID_HANDLE_VALUE;
        }


        ~IOCompletionPort( )
        {
            Close( );
        }

        IOCompletionPort& operator = ( const IOCompletionPort& other ) = delete;

        IOCompletionPort& operator = ( IOCompletionPort&& other ) noexcept
        {
            if ( &other != this )
            {
                Close( );
                handle_ = other.handle_;
                other.handle_ = INVALID_HANDLE_VALUE;
            }
        }

        void Close( ) noexcept
        {
            if ( handle_ != INVALID_HANDLE_VALUE )
            {
                CloseHandle( handle_ );
                handle_ = INVALID_HANDLE_VALUE;
            }
        }

        HCC_EXPORT void Bind( HANDLE iohandle, void* data = nullptr ) const;
        HCC_EXPORT void Bind( const Sockets::Socket& socket, void* data = nullptr ) const;


        struct Message
        {
            DWORD numberOfBytesTransferred_;
            void* data_;
            OVERLAPPED* overlapped_;

            Message()
                : numberOfBytesTransferred_(0), data_(nullptr), overlapped_( nullptr )
            { }

            explicit Message( DWORD numberOfBytesTransferred, void* data = nullptr, OVERLAPPED* overlapped = nullptr )
                : numberOfBytesTransferred_( numberOfBytesTransferred ), data_( data ), overlapped_( overlapped )
            {
            }

            constexpr IO::Request* Request( ) const noexcept
            {
                return static_cast<IO::Request*>( overlapped_ );
            }

            UInt64 Id( ) const noexcept
            {
                return reinterpret_cast<UInt64>( data_ );
            }

            DWORD NumberOfBytesTransferred( ) const noexcept
            {
                return numberOfBytesTransferred_;
            }
            void* Data( ) const noexcept
            {
                return data_;
            }

            OVERLAPPED* Overlapped( ) const noexcept
            {
                return overlapped_;
            }


        };

        HCC_EXPORT void Post( DWORD numberOfBytesTransferred, void* data, OVERLAPPED* overlapped ) const;

        void Post( const Message& message ) const
        {
            Post( message.numberOfBytesTransferred_, message.data_, message.overlapped_ );
        }

        HCC_EXPORT Message Dequeue( DWORD timeoutInMillis ) const;
        HCC_EXPORT bool Dequeue( Message& message, DWORD timeoutInMillis ) const;

    };

}

#endif
