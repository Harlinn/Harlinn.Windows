#pragma once
#ifndef HCCDEBUGSERVICEHOST_H_
#define HCCDEBUGSERVICEHOST_H_

#include "HCCService.h"

namespace Harlinn::Common::Core::Services
{
    namespace Internal
    {
        class ServiceEntry
        {
            WideString name_;
            size_t handle_ = 0;
            LPSERVICE_MAIN_FUNCTIONW mainFunction_ = nullptr;
            LPHANDLER_FUNCTION_EX serviceHandler_ = nullptr;
            void* serviceContext_ = nullptr;
            SERVICE_STATUS serviceStatus_{};
            Thread serviceThread_;
            std::vector<WideString> arguments_;
        public:
            ServiceEntry(const WideString& serviceName, size_t handleValue, LPSERVICE_MAIN_FUNCTIONW mainFunction )
                : name_( serviceName ), handle_( handleValue ), mainFunction_( mainFunction )
            { 
            }

            SERVICE_STATUS_HANDLE RegisterHandler( _In_ __callback LPHANDLER_FUNCTION_EX handlerProc, _In_opt_ LPVOID context )
            {
                serviceHandler_ = handlerProc;
                serviceContext_ = context;
                return reinterpret_cast< SERVICE_STATUS_HANDLE >( handle_ );
            }

            void SetStatus( _In_ LPSERVICE_STATUS serviceStatus )
            {
                if ( serviceStatus )
                {
                    serviceStatus_ = *serviceStatus;
                    ServiceState currentState = static_cast< ServiceState >( serviceStatus_.dwCurrentState );
                    auto currentStateStr = Format( "{}", currentState );
                    auto name = ToAnsiString( name_ );
                    HCC_DEBUG( "{} {}", name, currentStateStr );
                }
            }

            void Start( )
            {
                ServiceEntry* serviceEntry = this;
                serviceThread_ = Thread( [ serviceEntry ]()
                    {
                        std::vector<wchar_t*> args;
                        args.push_back( const_cast< wchar_t* >( serviceEntry->Name().c_str() ) );
                        const auto& otherArgs = serviceEntry->Arguments( );
                        for ( const auto& arg : otherArgs )
                        {
                            args.push_back( const_cast< wchar_t* >( arg.c_str( ) ) );
                        }
                        DWORD argc = static_cast< DWORD >( args.size( ) );
                        wchar_t** argv = args.data( );
                        auto mainFunction = serviceEntry->MainFunction( );
                        mainFunction( argc, argv );
                    });
            }


            void Stop( )
            {
                if ( serviceHandler_ )
                {
                    serviceHandler_( SERVICE_CONTROL_STOP, 0, nullptr, serviceContext_ );
                    serviceThread_.Wait( );
                }
            }


            const WideString& Name( ) const
            {
                return name_;
            }
            size_t Handle( ) const
            {
                return handle_;
            }
            LPSERVICE_MAIN_FUNCTIONW MainFunction( ) const
            {
                return mainFunction_;
            }
            LPHANDLER_FUNCTION_EX ServiceHandler( ) const
            {
                return serviceHandler_;
            }
            void* ServiceContext( ) const
            {
                return serviceContext_;
            }
            const SERVICE_STATUS& ServiceStatus( ) const
            {
                return serviceStatus_;
            }

            const Thread& ServiceThread( ) const
            {
                return serviceThread_;
            }

            const std::vector<WideString>& Arguments( ) const
            {
                return arguments_;
            }
        };
    }



    class DebugServiceHost : public IServiceHost
    {
        std::map<WideString, std::unique_ptr<Internal::ServiceEntry>> serviceNameMap_;
        std::map<size_t, Internal::ServiceEntry*> serviceHandleMap_;
    public:
        virtual bool StartDispatcher( const SERVICE_TABLE_ENTRYW* serviceStartTable ) override
        {
            size_t counter = 0;
            while ( serviceStartTable->lpServiceName && serviceStartTable->lpServiceProc )
            {
                counter++;
                WideString serviceName = serviceStartTable->lpServiceName;
                serviceNameMap_.emplace( serviceName, std::make_unique<Internal::ServiceEntry>( serviceName, counter, serviceStartTable->lpServiceProc ) );
                serviceStartTable++;
            }

            for ( auto& entry : serviceNameMap_ )
            {
                auto handle = entry.second->Handle( );
                serviceHandleMap_.emplace( handle, entry.second.get() );
            }

            for ( auto& entry : serviceNameMap_ )
            {
                entry.second->Start( );
            }
            this->Run( );
            return true;
        }

        virtual void Run( )
        {
            puts( "Press ENTER to exit" );
            getc( stdin );
            Stop( );
        }

        void Stop( )
        {
            for ( auto& entry : serviceNameMap_ )
            {
                entry.second->Stop( );
            }
        }


        Internal::ServiceEntry* Find( const WideString& serviceName )
        {
            auto it = serviceNameMap_.find( serviceName );
            if ( it != serviceNameMap_.end( ) )
            {
                return it->second.get( );
            }
            return nullptr;
        }

        Internal::ServiceEntry* Find( const SERVICE_STATUS_HANDLE serviceStatusHandle )
        {
            auto it = serviceHandleMap_.find( reinterpret_cast<size_t>( serviceStatusHandle ) );
            if ( it != serviceHandleMap_.end( ) )
            {
                return it->second;
            }
            return nullptr;
        }


        virtual SERVICE_STATUS_HANDLE RegisterHandler( _In_ LPCWSTR serviceName, _In_ __callback LPHANDLER_FUNCTION_EX handlerProc, _In_opt_ LPVOID context ) override
        {
            auto serviceEntry = Find( serviceName );
            if ( serviceEntry )
            {
                serviceEntry->RegisterHandler( handlerProc, context );
                return reinterpret_cast< SERVICE_STATUS_HANDLE >( serviceEntry->Handle( ) );
            }
            return nullptr;
        }

        virtual bool SupportsRequestDeviceNotifications( )
        {
            return false;
        }
        virtual HDEVNOTIFY RequestDeviceNotifications( SERVICE_STATUS_HANDLE serviceStatusHandle, bool allInterfaceClasses, LPVOID notificationFilter )
        {
            return nullptr;
        }

        virtual bool SetStatus( _In_ SERVICE_STATUS_HANDLE serviceStatusHandle, _In_ LPSERVICE_STATUS serviceStatus ) override
        {
            auto serviceEntry = Find( serviceStatusHandle );
            if ( serviceEntry )
            {
                serviceEntry->SetStatus( serviceStatus );
                return true;
            }
            return false;
        }
    };

}

#endif
