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

#include "pch.h"
#include <HCCApplication.h>
#include <HCCLoggerImpl.h>
#include <HCCSync.h>

namespace Harlinn::Common::Core
{

    static UInt64 applicationThreadId = 0xFFFFFFFFFFFFFFFF;
    static UInt64 mainThreadId = 0xFFFFFFFFFFFFFFFF;
    HCC_EXPORT Application* Application::instance_ = nullptr;

    Application::Application( const std::shared_ptr<ApplicationOptions>& options )
        : Base(WideString(L"Core::Application") ), options_( options )
    {
        Logging::LogManager::SetOptions( options->LoggerOptions( ) );

        instance_ = this;
        mainThreadId = CurrentThread::Id( );
    }

    HCC_EXPORT Application::Application( )
        : Application( ApplicationOptions::LoadFromFile( ) )
    {
    }

    Application::~Application( )
    {
        instance_ = nullptr;
    }

    UInt64 Application::MainThreadId( ) noexcept
    {
        return mainThreadId;
    }

    void Application::HandleDllMainEvent( HMODULE moduleHandle, DWORD reason, LPVOID freeLibrary ) noexcept
    {
        try
        {
            switch ( reason )
            {
                case DLL_PROCESS_ATTACH:
                    break;
                case DLL_THREAD_ATTACH:
                {
                    if ( instance_ )
                    {
                        instance_->PostThreadAttachedMessage( );
                    }
                }
                break;
                case DLL_THREAD_DETACH:
                {
                    if ( instance_ )
                    {
                        instance_->PostThreadDetachedMessage( );
                    }
                    auto logManager = Logging::LogManager::Instance( );
                    if ( logManager )
                    {
                        logManager->PostThreadDetachedMessage( );
                    }
                }
                break;
                case DLL_PROCESS_DETACH:
                    break;
            }
        }
        catch ( ... )
        {
        }
    }

    void Application::ProcessMessage( const MessageType& message )
    {
        Base::ProcessMessage( message );
        auto messageType = message->MessageType( );
        switch ( messageType )
        {
            case ApplicationMessageType::ThreadAttached:
            {
                ProcessThreadAttachedMessage( std::static_pointer_cast< ApplicationThreadAttachedMessage >( message ) );
            }
            break;
            case ApplicationMessageType::ThreadDetached:
            {
                ProcessThreadDetachedMessage( std::static_pointer_cast< ApplicationThreadDetachedMessage >( message ) );
            }
            break;
        }
    }

    void Application::BeforeProcessMessages( )
    {
        Base::BeforeProcessMessages( );
        applicationThreadId = CurrentThread::Id( );
    }

    void Application::PostThreadAttachedMessage( )
    {
        auto threadId = CurrentThread::Id( );
        if ( applicationThreadId != threadId && mainThreadId != threadId )
        {
            auto message = std::make_shared< ApplicationThreadAttachedMessage >( static_cast< UInt32 >( threadId ) );
            PostMessage( message );
        }
    }

    void Application::ProcessThreadAttachedMessage( const std::shared_ptr<ApplicationThreadAttachedMessage>& message )
    {
        auto attachedThreadId = message->Value( );
        OnThreadAttached( attachedThreadId );
    }

    void Application::PostThreadDetachedMessage( )
    {
        auto threadId = CurrentThread::Id( );
        if ( applicationThreadId != threadId && mainThreadId != threadId )
        {
            auto message = std::make_shared< ApplicationThreadDetachedMessage >( static_cast< UInt32 >( threadId ) );
            PostMessage( message );
        }
    }

    void Application::ProcessThreadDetachedMessage( const std::shared_ptr<ApplicationThreadDetachedMessage>& message )
    {
        auto detachedThreadId = message->Value( );
        OnThreadDetached( detachedThreadId );
    }



}
