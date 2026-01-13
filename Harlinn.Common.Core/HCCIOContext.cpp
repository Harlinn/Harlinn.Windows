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

#include "pch.h"
#include <HCCIOContext.h>

namespace Harlinn::Common::Core::IO
{
    Context::~Context( )
    {
    }

    namespace
    {
        int SEHFilter( unsigned int exceptionCode, struct _EXCEPTION_POINTERS* exceptionInformation )
        {
            if ( exceptionCode == EXCEPTION_ACCESS_VIOLATION )
            {
                return EXCEPTION_EXECUTE_HANDLER;
            }
            else
            {
                return EXCEPTION_CONTINUE_SEARCH;
            };
        }
    }

    void Context::Start( )
    {
        std::lock_guard guard( criticalSection_ );
        for ( DWORD i = 0; i < numberOfThreads_; i++ )
        {
            threads_.Add( []( Context* context )
            {
                CurrentThread::SetDescription( L"IO::Context worker thread" );
                __try
                {
                    context->ProcessRequests( );
                }
                __except ( SEHFilter( GetExceptionCode( ), GetExceptionInformation( ) ) )
                {
                    printf( "In __except\n" );
                }
            }, this );
        }
        for ( auto& handler : handlers_ )
        {
            handler->Start( );
        }
    }

    void Context::Stop( )
    {
        std::lock_guard guard( criticalSection_ );
        for ( auto& handler : handlers_ )
        {
            handler->Stop( );
        }
        for ( DWORD i = 0; i < numberOfThreads_; i++ )
        {
            Post( 0, reinterpret_cast<void*>( StopId ), nullptr );
        }
        threads_.Wait( );
        event_.Signal( );
    }

    void Context::HandleUnprocessedMessage( Message& message )
    {
        
    }

    void Context::ProcessRequests( )
    {
        while ( true )
        {
            try
            {
                Message message{};
                if ( Dequeue( message, INFINITE ) == false )
                {
                    break;
                }
                if ( message.Id( ) == StopId )
                {
                    break;
                }
                else if ( message.Id( ) == AsynchId && message.Overlapped() != nullptr )
                {
                    // overlapped gets deleted by the overlapped->invokeFunction_
                    AsyncOverlappedBase* overlapped = static_cast<AsyncOverlappedBase*>( message.Overlapped() );
                    overlapped->invokeFunction_( overlapped );
                }
                else
                {
                    ContextHandler* contextHandlerPtr = (ContextHandler*)message.Data( );
                    if ( contextHandlerPtr )
                    {
                        auto contextHandler = contextHandlerPtr->shared_from_this( );
                        try
                        {
                            auto rc = contextHandler->Process( message );
                            if ( !rc )
                            {
                                this->HandleUnprocessedMessage( message );
                            }
                        }
                        HCC_CATCH_ALL_AND_REPORT_EXCEPTION
                        contextHandler->ProcessDone( message );
                    }
                    else
                    {
                        auto overlapped = message.Overlapped( );
                        auto winError = static_cast<WinError>( overlapped->Internal );
                        if ( winError != WinError::None )
                        {
                            printf( "%d\r\n", static_cast<int>( winError ) );
                        }
                    }
                }
            }
            HCC_CATCH_ALL_AND_REPORT_EXCEPTION
        }
    }

}