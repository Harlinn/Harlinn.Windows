#pragma once
#ifndef __HCCAPPLICATION_H__
#define __HCCAPPLICATION_H__

#include <HCCDef.h>
#include <HCCApplicationOptions.h>
#include <HCCLoggerBackend.h>

namespace Harlinn::Common::Core
{

    namespace ApplicationMessageIds
    {
        constexpr UInt64 ThreadDetached = ActiveObjectMessageIds::Last + 1;
        constexpr UInt64 Last = ThreadDetached;
    }

    class Application : public ActiveObject<Application>
    {
    public:
        using Base = ActiveObject<Application>;
        
    private:
        HCC_EXPORT static Application* instance_;
        const std::shared_ptr<ApplicationOptions> options_;
        Logging::Backend loggingBackend_;
    public:
        HCC_EXPORT Application( const std::shared_ptr<ApplicationOptions>& options );
        Application( )
            : Application( ApplicationOptions::LoadFromFile() )
        { }
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
        HCC_EXPORT void Process( const Message& message ) noexcept;

        void Start( )
        {
            Base::Start( );
            loggingBackend_.Start( );

        }

        void Stop( )
        {
            loggingBackend_.Stop( );
            Base::Stop( );
        }

        void Post( UInt64 Id, OVERLAPPED* requestData )
        {
            Base::Post( CurrentThread::Id( ), reinterpret_cast<void*>( Id ), requestData );
        }


    };



}

#endif
