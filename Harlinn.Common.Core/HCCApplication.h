#pragma once
#ifndef __HCCAPPLICATION_H__
#define __HCCAPPLICATION_H__
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

#include <HCCDef.h>
#include <HCCApplicationOptions.h>
#include <HCCActiveObject.h>

namespace Harlinn::Common::Core
{

    enum class ApplicationMessageType
    {
        Unknown,
        Stop,
        ThreadAttached,
        ThreadDetached
    };


    using ApplicationMessage = Concurrency::Messages::Message<ApplicationMessageType>;

    template<ApplicationMessageType messageId>
    using SimpleApplicationMessage = Concurrency::Messages::SimpleMessage<ApplicationMessageType, messageId>;

    template<typename ValueT, ApplicationMessageType messageId>
    using SimpleApplicationValueMessage = Concurrency::Messages::SimpleValueMessage<ValueT, ApplicationMessageType, messageId>;

    using ApplicationStopMessage = SimpleApplicationMessage<ApplicationMessageType::Stop>;
    using ApplicationThreadAttachedMessage = SimpleApplicationValueMessage<UInt32, ApplicationMessageType::ThreadAttached>;
    using ApplicationThreadDetachedMessage = SimpleApplicationValueMessage<UInt32, ApplicationMessageType::ThreadDetached>;

    /// <summary>
    /// <para>
    /// A base class for application objects.
    /// </para>
    /// <para>
    /// There must only be a single instance of this class in an application.
    /// </para>
    /// </summary>
    /// <remarks>
    /// <para>
    /// If your executable is named MyApp.exe, the application object will attempt to 
    /// load configuration data from a file named MyApp.options.
    /// </para>
    /// <para>
    /// Your main function could look like this:
    /// </para>
    /// <code>
    /// int main( int argc, char* argv[], char* envp[] )
    /// {
    ///     int result = 0;
    ///     auto application = std::make_shared&lt;Harlinn::Common::Core::Application&gt;( );
    ///     application->Start( );
    ///     try
    ///     {
    ///         // Application logic goes here
    ///     }
    ///     catch(...)
    ///     {
    ///     }
    ///     application->Stop( );
    ///     return result;
    /// }
    /// </code>
    /// <para>
    /// </para>
    /// </remarks>
    class Application : public Concurrency::ActiveObject<std::shared_ptr<ApplicationMessage>>
    {
    public:
        using Base = Concurrency::ActiveObject<std::shared_ptr<ApplicationMessage>>;
        using Base::Start;
        using Base::Stop;
    private:
        HCC_EXPORT static Application* instance_;
        const std::shared_ptr<ApplicationOptions> options_;
        
    public:
        boost::signals2::signal<void( UInt32 attachedThreadId )> OnThreadAttached;
        boost::signals2::signal<void( UInt32 detachedThreadId )> OnThreadDetached;
        HCC_EXPORT Application( const std::shared_ptr<ApplicationOptions>& options );
        HCC_EXPORT Application( );
        HCC_EXPORT ~Application( );

        Application( const Application& other ) = delete;
        Application( Application&& other ) = delete;
        Application& operator = ( const Application& other ) = delete;
        Application& operator = ( Application&& other ) = delete;

        const std::shared_ptr<ApplicationOptions>& Options( ) const
        {
            return options_;
        }

        HCC_EXPORT static Application& Instance( );
        
        HCC_EXPORT WideString ExecutableFilename( );
        HCC_EXPORT WideString ExecutableDirectory( );

        HCC_EXPORT static UInt64 MainThreadId( ) noexcept;

        HCC_EXPORT static void HandleDllMainEvent( HMODULE moduleHandle, DWORD reason, LPVOID freeLibrary ) noexcept;
    protected:
        HCC_EXPORT virtual void ProcessMessage( const MessageType& message ) override;
    public:

    protected:
        virtual bool IsStopMessage( const MessageType& message ) const noexcept override
        {
            return message->MessageType( ) == ApplicationMessageType::Stop;
        }
        virtual void PostStopMessage( ) override
        {
            auto message = std::make_shared< SimpleApplicationMessage<ApplicationMessageType::Stop > >( );
            PostMessage( message );
        }
        HCC_EXPORT virtual void BeforeProcessMessages( ) override;
    public:
        HCC_EXPORT void PostThreadAttachedMessage( );
    protected:
        HCC_EXPORT virtual void ProcessThreadAttachedMessage( const std::shared_ptr<ApplicationThreadAttachedMessage>& message );
    public:
        HCC_EXPORT void PostThreadDetachedMessage( );
    protected:
        HCC_EXPORT virtual void ProcessThreadDetachedMessage( const std::shared_ptr<ApplicationThreadDetachedMessage>& message );

    };



}

#endif
