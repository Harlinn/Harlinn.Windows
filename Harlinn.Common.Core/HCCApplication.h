#pragma once
#ifndef __HCCAPPLICATION_H__
#define __HCCAPPLICATION_H__

#include <HCCDef.h>
#include <HCCApplicationOptions.h>
#include <HCCLoggerBackend.h>

namespace Harlinn::Common::Core
{

    enum class ApplicationMessageType
    {
        Unknown,
        Stop,
        ThreadDetached
    };


    using ApplicationMessage = Concurrency::Messages::Message<ApplicationMessageType>;

    template<ApplicationMessageType messageId>
    using SimpleApplicationMessage = Concurrency::Messages::SimpleMessage<ApplicationMessageType, messageId>;

    template<typename ValueT, ApplicationMessageType messageId>
    using SimpleApplicationValueMessage = Concurrency::Messages::SimpleValueMessage<ValueT, ApplicationMessageType, messageId>;

    class Application : public Concurrency::ActiveObject<std::shared_ptr<ApplicationMessage>>
    {
    public:
        using Base = Concurrency::ActiveObject<std::shared_ptr<ApplicationMessage>>;
        
    private:
        HCC_EXPORT static Application* instance_;
        const std::shared_ptr<ApplicationOptions> options_;
        std::shared_ptr<Logging::Backend> loggingBackend_;
    public:
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

        static Application& Instance( ) noexcept
        {
            return *instance_;
        }

        HCC_EXPORT static void HandleDllMainEvent( HMODULE moduleHandle, DWORD reason, LPVOID freeLibrary ) noexcept;
        HCC_EXPORT virtual void ProcessMessage( const MessageType& message ) override;

        void Start( )
        {
            Base::Start( );
            loggingBackend_->Start( );

        }

        void Stop( )
        {
            loggingBackend_->Stop( );
            Base::Stop( );
        }


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
    protected:


    };



}

#endif
