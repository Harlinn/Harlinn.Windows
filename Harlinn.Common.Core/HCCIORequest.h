#pragma once
#ifndef __HCCIOREQUEST_H__
#define __HCCIOREQUEST_H__

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

namespace Harlinn::Common::Core::IO
{
    class Context;

    struct Overlapped : public OVERLAPPED
    {
        using Base = OVERLAPPED;

        constexpr Overlapped( ) noexcept
            : Base{}
        {
        }

        constexpr void ClearOverlapped( )
        {
            Internal = 0;
            InternalHigh = 0;
            Pointer = nullptr;
            hEvent = 0;
        }

    };


    /// <summary>
    /// The result for Request::Wait
    /// </summary>
    enum class RequestWaitResult : Int32
    {
        /// <summary>
        /// timeoutInMilliseconds was set to zero and the operation is still in progress.
        /// </summary>
        Incomplete = -3,
        /// <summary>
        /// The wait was interrupted by an I/O completion routine or APC.
        /// </summary>
        IoCompletion = -2,
        /// <summary>
        /// Indicates that the timeout interval elapsed.
        /// </summary>
        Timeout = -1,
        /// <summary>
        /// Not used.
        /// </summary>
        Unknown = 0,
        /// <summary>
        /// Indicates that the wait succeeded.
        /// </summary>
        Success = 1,

    };

    /// <summary>
    /// Base class for all asynchronous requests
    /// </summary>
    class Request : public OVERLAPPED
    {
        bool ownsEvent_;
        HANDLE handle_;
        std::weak_ptr<Context> context_;
    public:
        using Base = OVERLAPPED;
    private:
        static HANDLE CreateManualResetEvent( )
        {
            auto result = CreateEventW( nullptr, TRUE, FALSE, nullptr );
            if ( result == nullptr )
            {
                ThrowLastOSError( );
            }
            return result;
        }
    public:
        Request( )
            : Base{}, ownsEvent_( true ), handle_( nullptr )
        {
            hEvent = CreateManualResetEvent( );
        }

        explicit Request( HANDLE handle )
            : Base{}, ownsEvent_( true ), handle_( handle )
        {
            hEvent = CreateManualResetEvent( );
        }

        constexpr explicit Request( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent )
            : Base{}, ownsEvent_( ownsEvent ), handle_( handle )
        {
            hEvent = manualResetEvent;
        }


        Request( const Request& other ) = delete;
        Request( Request&& other ) = delete;

        virtual ~Request( ) noexcept
        {
            if ( ownsEvent_ && hEvent )
            {
                CloseHandle( hEvent );
            }
        }

        Request& operator = ( const Request& other ) = delete;
        Request& operator = ( Request&& other ) = delete;

        /// <summary>
        /// Retrieves the status code for the I/O request. 
        /// Will return STATUS_PENDING to indicate that the operation has not yet 
        /// completed, and for operations that has completed it will return the 
        /// status code for the completed request.
        /// </summary>
        /// <returns>The status code for the request.</returns>
        constexpr ULONG_PTR Status( ) const noexcept
        {
            return Internal;
        }

        /// <summary>
        /// Sets the status code and number of bytes transferred for this request.
        /// </summary>
        /// <param name="ioResult">
        /// The status code.
        /// </param>
        /// <param name="numberOfBytesTransferred">
        /// The number of bytes transferred,
        /// </param>
        /// <remarks>
        /// Sometimes an asynchronous request will complete synchronously.
        /// The library then uses this function to update the status code 
        /// and number of bytes transferred for the request before calling
        /// the handler implementation.
        /// </remarks>
        constexpr void SetResult( WinError ioResult, UInt64 numberOfBytesTransferred ) noexcept
        {
            Internal = static_cast<ULONG_PTR>( ioResult );
            InternalHigh = numberOfBytesTransferred;
        }
        /// <summary>
        /// Sets the status code for this request.
        /// </summary>
        /// <param name="ioResult">
        /// The status code.
        /// </param>
        /// <remarks>
        /// Sometimes an asynchronous request will complete synchronously.
        /// The library then uses this function to update the status code 
        /// for the request before calling the handler implementation.
        /// </remarks>
        constexpr void SetResult( WinError ioResult ) noexcept
        {
            Internal = static_cast<ULONG_PTR>( ioResult );
        }

        /// <summary>
        /// Retrieves the status code for the I/O request as an unsigned 32-bit integer. 
        /// Will return STATUS_PENDING to indicate that the operation has not yet 
        /// completed, and for operations that has completed it will return the 
        /// status code for the completed request.
        /// </summary>
        /// <returns>The status code for the request as an unsigned 32-bit integer.</returns>
        constexpr WinError IoResult( ) const noexcept
        {
            return static_cast<WinError>( Internal );
        }

        /// <summary>
        /// Retrieves the number of bytes transferred for the I/O request. 
        /// The result is only valid if the request is completed without errors.
        /// </summary>
        /// <returns>The number of bytes transferred.</returns>
        constexpr ULONG_PTR NumberOfBytesTransferred( ) const noexcept
        {
            return InternalHigh;
        }

        /// <summary>
        /// Retrieves the file position at which to start the I/O request.
        /// </summary>
        /// <remarks>
        /// Only use this when performing I/O requests on a seeking device 
        /// that supports the concept of an offset, such as a file.
        /// </remarks>
        /// <returns>The file position at which to start the I/O request.</returns>
        constexpr size_t Position( ) const noexcept
        {
            return ( static_cast<size_t>( OffsetHigh ) << 32 ) + Offset;
        }


        /// <summary>
        /// Sets the file position at which to start the I/O request.
        /// </summary>
        /// <param name="position">
        /// The file position at which to start the I/O request.
        /// </param>
        /// <remarks>
        /// Only use this when performing I/O requests on a seeking device 
        /// that supports the concept of an offset, such as a file.
        /// </remarks>
        constexpr void SetPosition( size_t position ) noexcept
        {
            OffsetHigh = static_cast<UInt32>( position >> 32 );
            Offset = static_cast<UInt32>( position & 0xFFFFFFFFUL );
        }


        /// <summary>
        /// Prepares the OVERLAPPED for reuse  
        /// </summary>
        void Clear( ) noexcept
        {
            Internal = 0;
            InternalHigh = 0;
            Pointer = nullptr;
        }

        /// <summary>
        /// Prepares the request for reuse  
        /// </summary>
        void Reset( )
        {
            Clear( );
            handle_ = 0;
            context_.reset();
        }
        /// <summary>
        /// Prepares the request for reuse  
        /// </summary>
        void Reset( HANDLE handle )
        {
            Clear( );
            handle_ = handle;
            context_.reset( );
        }
        /// <summary>
        /// Prepares the request for reuse  
        /// </summary>
        void Reset( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent )
        {
            Clear( );
            handle_ = handle;
            context_.reset( );
            if ( hEvent != manualResetEvent )
            {
                if ( ownsEvent_ && hEvent )
                {
                    CloseHandle( hEvent );
                }
                hEvent = manualResetEvent;
                ownsEvent_ = ownsEvent;
            }
        }


        /// <summary>
        /// Retrieves the handle that this asynchronous operates on.
        /// </summary>
        /// <returns>The handle that this asynchronous operates on.</returns>
        constexpr HANDLE Handle( ) const noexcept
        {
            return handle_;
        }

        /// <summary>
        /// Sets the handle that this asynchronous operates on.
        /// </summary>
        /// <param name="handle">
        /// The handle that this asynchronous operates on.
        /// </param>
        constexpr void SetHandle( HANDLE handle )
        {
            handle_ = handle;
        }

        /// <summary>
        /// Retrieves a pointer to the IO::Context that the handle this
        /// Request operates on is bound to.
        /// </summary>
        /// <returns>
        /// A pointer to the IO::Context that the handle this Request 
        /// operates on is bound to.
        /// </returns>
        std::shared_ptr<IO::Context> Context( ) const noexcept
        {
            return context_.lock();
        }

        /// <summary>
        /// Sets the pointer to the IO::Context that the handle this Request 
        /// operates on is bound to.
        /// </summary>
        /// <param name="context">
        /// Pointer to an IO::Context.
        /// </param>
        void SetContext( std::shared_ptr<IO::Context>& context )
        {
            context_ = context;
        }
        void SetContext( std::weak_ptr<IO::Context>& context )
        {
            context_ = context;
        }

        /// <summary>
        /// A high performance test operation that can be used to poll for 
        /// the completion of an outstanding I/O request.
        /// </summary>
        /// <remarks>
        /// Do not call this member function unless this request has been successfully
        /// queued to the IO::Context.
        /// </remarks>
        /// <returns>
        /// true if the request has completed, otherwise false.
        /// </returns>
        bool IoCompleted( ) const
        {
            const OVERLAPPED* self = this;
            return HasOverlappedIoCompleted( self );
        }

        /// <summary>
        /// Wait for the completion of this asynchronous request.
        /// </summary>
        /// <param name="numberOfBytesTransferred">
        /// <p>
        /// A pointer to a variable that receives the number of bytes that were 
        /// actually transferred by a read or write operation.
        /// </p>
        /// <p>
        /// For a TransactNamedPipe operation, this is the number of bytes that 
        /// were read from the pipe. For a DeviceIoControl operation, this is the 
        /// number of bytes of output data returned by the device driver. For a 
        /// ConnectNamedPipe or WaitCommEvent operation, this value is undefined.
        /// </p>
        /// </param>
        /// <param name="timeoutInMilliseconds">
        /// <p>
        /// The time-out interval, in milliseconds.
        /// </p>
        /// <p>
        /// The function returns RequestWaitResult::Success if it successfully
        /// waits for the request to complete.
        /// </p>
        /// <p>
        /// If timeoutInMilliseconds is zero and the operation is still in progress, 
        /// the function returns immediately with the return value set to RequestWaitResult::Incomplete.
        /// </p>
        /// <p>
        /// The function returns RequestWaitResult::Timeout if the timeoutInMilliseconds interval elapses 
        /// before returning.
        /// </p>
        /// The function returns RequestWaitResult::IoCompletion if the wait was interrupted 
        /// by an I/O completion routine or APC.
        /// </param>
        /// <param name="alertableWait">
        /// If this parameter is true and the calling thread is in the waiting state, the 
        /// function returns when the system queues an I/O completion routine or APC. The 
        /// calling thread then runs the routine or function. Otherwise, the function does 
        /// not return, and the completion routine or APC function is not executed.
        /// </param>
        /// <returns>
        /// The result of the wait operation.
        /// </returns>
        RequestWaitResult Wait( UInt32* numberOfBytesTransferred, UInt32 timeoutInMilliseconds, bool alertableWait ) const
        {
            const OVERLAPPED* self = this;
            auto rc = GetOverlappedResultEx( handle_, const_cast<OVERLAPPED*>( self ), reinterpret_cast<LPDWORD>( numberOfBytesTransferred ), timeoutInMilliseconds, alertableWait );
            if ( !rc )
            {
                auto err = GetLastError( );
                if ( timeoutInMilliseconds )
                {
                    if ( err == WAIT_IO_COMPLETION )
                    {
                        return RequestWaitResult::IoCompletion;
                    }
                    else if ( err == WAIT_TIMEOUT )
                    {
                        return RequestWaitResult::Timeout;
                    }
                }
                else
                {
                    if ( err == ERROR_IO_INCOMPLETE )
                    {
                        return RequestWaitResult::Incomplete;
                    }
                }
                ThrowOSError( err );
            }
            return RequestWaitResult::Success;
        }

        /// <summary>
        /// Wait for the completion of this asynchronous request.
        /// </summary>
        /// <param name="numberOfBytesTransferred">
        /// <p>
        /// A pointer to a variable that receives the number of bytes that were 
        /// actually transferred by a read or write operation.
        /// </p>
        /// <p>
        /// For a TransactNamedPipe operation, this is the number of bytes that 
        /// were read from the pipe. For a DeviceIoControl operation, this is the 
        /// number of bytes of output data returned by the device driver. For a 
        /// ConnectNamedPipe or WaitCommEvent operation, this value is undefined.
        /// </p>
        /// </param>
        /// <param name="timeoutInMilliseconds">
        /// <p>
        /// The time-out interval, in milliseconds.
        /// </p>
        /// </param>
        /// <returns>
        /// true if the wait succeeded, otherwise false.
        /// </returns>
        bool Wait( UInt32* numberOfBytesTransferred, UInt32 timeoutInMilliseconds = INFINITE ) const
        {
            const OVERLAPPED* self = this;
            auto rc = GetOverlappedResultEx( handle_, const_cast<OVERLAPPED*>( self ), reinterpret_cast<LPDWORD>( numberOfBytesTransferred ), timeoutInMilliseconds, FALSE );
            if ( !rc )
            {
                auto err = GetLastError( );
                if ( timeoutInMilliseconds )
                {
                    if ( err == WAIT_TIMEOUT )
                    {
                        return false;
                    }
                }
                else
                {
                    if ( err == ERROR_IO_INCOMPLETE )
                    {
                        return false;
                    }
                }
                ThrowOSError( err );
            }
            return true;
        }

        /// <summary>
        /// Wait for the completion of this asynchronous request.
        /// </summary>
        /// <param name="timeoutInMilliseconds">
        /// <p>
        /// The time-out interval, in milliseconds.
        /// </p>
        /// </param>
        /// <returns>
        /// true if the wait succeeded, otherwise false.
        /// </returns>
        bool Wait( UInt32 timeoutInMilliseconds = INFINITE ) const
        {
            UInt32 numberOfBytesTransferred = 0;
            return Wait( &numberOfBytesTransferred, timeoutInMilliseconds );
        }

        /// <summary>
        /// Cancels the outstanding I/O operation
        /// </summary>
        /// <returns>
        /// <ul>
        /// <li><em>true</em> if the outstanding operation was cancelled.</li>
        /// <li><em>false</em> if the system was unable to locate the request.</li>
        /// </ul>
        /// </returns>
        bool Cancel( ) const
        {
            const OVERLAPPED* self = this;
            auto rc = CancelIoEx( handle_, const_cast<OVERLAPPED*>( self ) );
            if ( !rc )
            {
                auto err = GetLastError( );
                if ( err == ERROR_NOT_FOUND )
                {
                    return false;
                }
                ThrowOSError( err );
            }
            return true;
        }

        /// <summary>
        /// Sets the event object to the signaled state
        /// </summary>
        void SetEvent( ) const
        {
            auto rc = ::SetEvent( hEvent );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
        /// <summary>
        /// Sets the event object to the signaled state
        /// </summary>
        void Signal( ) const
        {
            SetEvent( );
        }
        /// <summary>
        /// Sets the event object to the non-signaled state
        /// </summary>
        void ResetEvent( ) const
        {
            auto rc = ::ResetEvent( hEvent );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
    };


}

#endif
