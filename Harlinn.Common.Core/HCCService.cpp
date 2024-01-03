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
#include "HCCService.h"
#include "HCCDebugServiceHost.h"
#include "HCCFlags.h"

namespace Harlinn::Common::Core::Services
{
    Application::Application( const std::shared_ptr<ApplicationOptions>& options, IServiceHost* serviceHost )
        : Base( options ), serviceHost_( serviceHost )
    {

    }
    Application::~Application( ) = default;
}
namespace Harlinn::Common::Core
{
    // =========================================================================
    // ServiceAccessRights
    // =========================================================================
    namespace
    {
        using ServiceAccessRights = Services::ServiceAccessRights;
        class ServiceAccessRightsConverter : public Flags<ServiceAccessRights>
        {
        public:
            ServiceAccessRightsConverter( )
            {
                Add( L"None", ServiceAccessRights::None );
                Add( L"Delete", ServiceAccessRights::Delete );
                Add( L"ReadPermissions", ServiceAccessRights::ReadPermissions );
                Add( L"Synchronize", ServiceAccessRights::Synchronize );
                Add( L"ChangePermissions", ServiceAccessRights::ChangePermissions );
                Add( L"TakeOwnership", ServiceAccessRights::TakeOwnership );
                Add( L"SystemSecurity", ServiceAccessRights::SystemSecurity );
                Add( L"StandardRightsRead", ServiceAccessRights::StandardRightsRead );
                Add( L"StandardRightsWrite", ServiceAccessRights::StandardRightsWrite );
                Add( L"StandardRightsExecute", ServiceAccessRights::StandardRightsExecute );
                Add( L"QueryConfig", ServiceAccessRights::QueryConfig );
                Add( L"ChangeConfig", ServiceAccessRights::ChangeConfig );
                Add( L"QueryStatus", ServiceAccessRights::QueryStatus );
                Add( L"EnumerateDependents", ServiceAccessRights::EnumerateDependents );
                Add( L"Start", ServiceAccessRights::Start );
                Add( L"Stop", ServiceAccessRights::Stop );
                Add( L"PauseAndContinue", ServiceAccessRights::PauseAndContinue );
                Add( L"Interrogate", ServiceAccessRights::Interrogate );
                Add( L"UserDefinedControl", ServiceAccessRights::UserDefinedControl );
                Add( L"Read", ServiceAccessRights::Read );
                Add( L"Write", ServiceAccessRights::Write );
                Add( L"Execute", ServiceAccessRights::Execute );
                Add( L"StandardRightsRequiredMask", ServiceAccessRights::StandardRightsRequiredMask );
                Add( L"StandardRightsAllMask", ServiceAccessRights::StandardRightsAllMask );
                Add( L"MaximumAllowed", ServiceAccessRights::MaximumAllowed );
                Add( L"FullControl", ServiceAccessRights::FullControl );

                
            }
        };
        ServiceAccessRightsConverter serviceAccessRightsConverter;
    }

    WideString ToWideString( Services::ServiceAccessRights value )
    {
        return serviceAccessRightsConverter.ToString( value );
    }
    WideString ToWideString( Services::ServiceAccessRights value, const WideString& defaultResult )
    {
        return serviceAccessRightsConverter.ToString( value, defaultResult );
    }

    namespace Services
    {
        Services::ServiceAccessRights ParseServiceAccessRights( const WideString& str )
        {
            return serviceAccessRightsConverter.Parse( str );
        }

        Services::ServiceAccessRights ParseServiceAccessRights( const WideString& str, Services::ServiceAccessRights defaultResult )
        {
            return serviceAccessRightsConverter.Parse( str, defaultResult );
        }

        bool TryParseServiceAccessRights( const WideString& str, Services::ServiceAccessRights& value )
        {
            return serviceAccessRightsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // ServiceControlManagerAccessRights
    // =========================================================================
    namespace
    {
        using ServiceControlManagerAccessRights = Services::ServiceControlManagerAccessRights;
        class ServiceControlManagerAccessRightsConverter : public Flags<ServiceControlManagerAccessRights>
        {
        public:
            ServiceControlManagerAccessRightsConverter( )
            {
                Add( L"None", ServiceControlManagerAccessRights::None );
                Add( L"Delete", ServiceControlManagerAccessRights::Delete );
                Add( L"ReadPermissions", ServiceControlManagerAccessRights::ReadPermissions );
                Add( L"Synchronize", ServiceControlManagerAccessRights::Synchronize );
                Add( L"ChangePermissions", ServiceControlManagerAccessRights::ChangePermissions );
                Add( L"TakeOwnership", ServiceControlManagerAccessRights::TakeOwnership );
                Add( L"SystemSecurity", ServiceControlManagerAccessRights::SystemSecurity );
                Add( L"MaximumAllowed", ServiceControlManagerAccessRights::MaximumAllowed );
                Add( L"StandardRightsRequiredMask", ServiceControlManagerAccessRights::StandardRightsRequiredMask );
                Add( L"StandardRightsAllMask", ServiceControlManagerAccessRights::StandardRightsAllMask );
                Add( L"StandardRightsRead", ServiceControlManagerAccessRights::StandardRightsRead );
                Add( L"StandardRightsWrite", ServiceControlManagerAccessRights::StandardRightsWrite );
                Add( L"StandardRightsExecute", ServiceControlManagerAccessRights::StandardRightsExecute );
                Add( L"Connect", ServiceControlManagerAccessRights::Connect );
                Add( L"Create", ServiceControlManagerAccessRights::Create );
                Add( L"Enumerate", ServiceControlManagerAccessRights::Enumerate );
                Add( L"Lock", ServiceControlManagerAccessRights::Lock );
                Add( L"QueryLockStatus", ServiceControlManagerAccessRights::QueryLockStatus );
                Add( L"ModifyBootConfig", ServiceControlManagerAccessRights::ModifyBootConfig );
                Add( L"Read", ServiceControlManagerAccessRights::Read );
                Add( L"Write", ServiceControlManagerAccessRights::Write );
                Add( L"Execute", ServiceControlManagerAccessRights::Execute );
                Add( L"FullControl", ServiceControlManagerAccessRights::FullControl );
            }
        };
        ServiceControlManagerAccessRightsConverter serviceControlManagerAccessRightsConverter;
    }

    WideString ToWideString( Services::ServiceControlManagerAccessRights value )
    {
        return serviceControlManagerAccessRightsConverter.ToString( value );
    }
    WideString ToWideString( Services::ServiceControlManagerAccessRights value, const WideString& defaultResult )
    {
        return serviceControlManagerAccessRightsConverter.ToString( value, defaultResult );
    }

    namespace Services
    {
        Services::ServiceControlManagerAccessRights ParseServiceControlManagerAccessRights( const WideString& str )
        {
            return serviceControlManagerAccessRightsConverter.Parse( str );
        }

        Services::ServiceControlManagerAccessRights ParseServiceControlManagerAccessRights( const WideString& str, Services::ServiceControlManagerAccessRights defaultResult )
        {
            return serviceControlManagerAccessRightsConverter.Parse( str, defaultResult );
        }

        bool TryParseServiceControlManagerAccessRights( const WideString& str, Services::ServiceControlManagerAccessRights& value )
        {
            return serviceControlManagerAccessRightsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // ServiceType
    // =========================================================================
    namespace
    {
        using ServiceType = Services::ServiceType;
        class ServiceTypeConverter : public Flags<ServiceType>
        {
        public:
            ServiceTypeConverter( )
            {
                Add( L"None", ServiceType::None );
                Add( L"KernelDriver", ServiceType::KernelDriver );
                Add( L"FileSystemDriver", ServiceType::FileSystemDriver );
                Add( L"Adapter", ServiceType::Adapter );
                Add( L"RecognizerDriver", ServiceType::RecognizerDriver );
                Add( L"Driver", ServiceType::Driver );
                Add( L"WindowsOwnProcess", ServiceType::WindowsOwnProcess );
                Add( L"WindowsShareProcess", ServiceType::WindowsShareProcess );
                Add( L"Windows", ServiceType::Windows );
                Add( L"UserService", ServiceType::UserService );
                Add( L"UserServiceInstance", ServiceType::UserServiceInstance );
                Add( L"UserShareProcess", ServiceType::UserShareProcess );
                Add( L"UserOwnProcess", ServiceType::UserOwnProcess );
                Add( L"InteractiveProcess", ServiceType::InteractiveProcess );
                Add( L"PkgService", ServiceType::PkgService );
            }
        };
        ServiceTypeConverter serviceTypeConverter;
    }

    WideString ToWideString( Services::ServiceType value )
    {
        return serviceTypeConverter.ToString( value );
    }
    WideString ToWideString( Services::ServiceType value, const WideString& defaultResult )
    {
        return serviceTypeConverter.ToString( value, defaultResult );
    }

    namespace Services
    {
        Services::ServiceType ParseServiceType( const WideString& str )
        {
            return serviceTypeConverter.Parse( str );
        }

        Services::ServiceType ParseServiceType( const WideString& str, Services::ServiceType defaultResult )
        {
            return serviceTypeConverter.Parse( str, defaultResult );
        }

        bool TryParseServiceType( const WideString& str, Services::ServiceType& value )
        {
            return serviceTypeConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // ServiceStartType
    // =========================================================================
    namespace
    {
        using ServiceStartType = Services::ServiceStartType;
        class ServiceStartTypeConverter : public Enum<ServiceStartType>
        {
        public:
            ServiceStartTypeConverter( )
            {
                Add( L"BootStart", ServiceStartType::BootStart );
                Add( L"SystemStart", ServiceStartType::SystemStart );
                Add( L"AutoStart", ServiceStartType::AutoStart );
                Add( L"DemandStart", ServiceStartType::DemandStart );
                Add( L"Disabled", ServiceStartType::Disabled );
            }
        };
        ServiceStartTypeConverter serviceStartTypeConverter;
    }

    WideString ToWideString( Services::ServiceStartType value )
    {
        return serviceStartTypeConverter.ToString( value );
    }
    WideString ToWideString( Services::ServiceStartType value, const WideString& defaultResult )
    {
        return serviceStartTypeConverter.ToString( value, defaultResult );
    }

    namespace Services
    {
        Services::ServiceStartType ParseServiceStartType( const WideString& str )
        {
            return serviceStartTypeConverter.Parse( str );
        }

        Services::ServiceStartType ParseServiceStartType( const WideString& str, Services::ServiceStartType defaultResult )
        {
            return serviceStartTypeConverter.Parse( str, defaultResult );
        }

        bool TryParseServiceStartType( const WideString& str, Services::ServiceStartType& value )
        {
            return serviceStartTypeConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // ServiceEnumerationState
    // =========================================================================
    namespace
    {
        using ServiceEnumerationState = Services::ServiceEnumerationState;
        class ServiceEnumerationStateConverter : public Flags<ServiceEnumerationState>
        {
        public:
            ServiceEnumerationStateConverter( )
            {
                Add( L"None", ServiceEnumerationState::None );
                Add( L"Active", ServiceEnumerationState::Active );
                Add( L"Inactive", ServiceEnumerationState::Inactive );
                Add( L"All", ServiceEnumerationState::All );
            }
        };
        ServiceEnumerationStateConverter serviceEnumerationStateConverter;
    }

    WideString ToWideString( Services::ServiceEnumerationState value )
    {
        return serviceEnumerationStateConverter.ToString( value );
    }
    WideString ToWideString( Services::ServiceEnumerationState value, const WideString& defaultResult )
    {
        return serviceEnumerationStateConverter.ToString( value, defaultResult );
    }

    namespace Services
    {
        Services::ServiceEnumerationState ParseServiceEnumerationState( const WideString& str )
        {
            return serviceEnumerationStateConverter.Parse( str );
        }

        Services::ServiceEnumerationState ParseServiceEnumerationState( const WideString& str, Services::ServiceEnumerationState defaultResult )
        {
            return serviceEnumerationStateConverter.Parse( str, defaultResult );
        }

        bool TryParseServiceEnumerationState( const WideString& str, Services::ServiceEnumerationState& value )
        {
            return serviceEnumerationStateConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // ServiceState
    // =========================================================================
    namespace
    {
        using ServiceState = Services::ServiceState;
        class ServiceStateConverter : public Enum<ServiceState>
        {
        public:
            ServiceStateConverter( )
            {
                Add( L"Unknown", ServiceState::Unknown );
                Add( L"Stopped", ServiceState::Stopped );
                Add( L"StartPending", ServiceState::StartPending );
                Add( L"StopPending", ServiceState::StopPending );
                Add( L"Running", ServiceState::Running );
                Add( L"ContinuePending", ServiceState::ContinuePending );
                Add( L"PausePending", ServiceState::PausePending );
                Add( L"Paused", ServiceState::Paused );
            }
        };
        ServiceStateConverter serviceStateConverter;
    }

    WideString ToWideString( Services::ServiceState value )
    {
        return serviceStateConverter.ToString( value );
    }
    WideString ToWideString( Services::ServiceState value, const WideString& defaultResult )
    {
        return serviceStateConverter.ToString( value, defaultResult );
    }

    namespace Services
    {
        Services::ServiceState ParseServiceState( const WideString& str )
        {
            return serviceStateConverter.Parse( str );
        }

        Services::ServiceState ParseServiceState( const WideString& str, Services::ServiceState defaultResult )
        {
            return serviceStateConverter.Parse( str, defaultResult );
        }

        bool TryParseServiceState( const WideString& str, Services::ServiceState& value )
        {
            return serviceStateConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // ServiceControl
    // =========================================================================
    namespace
    {
        using ServiceControl = Services::ServiceControl;
        class ServiceControlConverter : public Enum<ServiceControl>
        {
        public:
            ServiceControlConverter( )
            {
                Add( L"Unknown", ServiceControl::Unknown );
                Add( L"Stop", ServiceControl::Stop );
                Add( L"Pause", ServiceControl::Pause );
                Add( L"Continue", ServiceControl::Continue );
                Add( L"Interrogate", ServiceControl::Interrogate );
                Add( L"Shutdown", ServiceControl::Shutdown );
                Add( L"ParamChange", ServiceControl::ParamChange );
                Add( L"NetBindAdd", ServiceControl::NetBindAdd );
                Add( L"NetBindRemove", ServiceControl::NetBindRemove );
                Add( L"NetBindEnable", ServiceControl::NetBindEnable );
                Add( L"NetBindDisable", ServiceControl::NetBindDisable );
                Add( L"DeviceEvent", ServiceControl::DeviceEvent );
                Add( L"HardwareProfileChange", ServiceControl::HardwareProfileChange );
                Add( L"PowerEvent", ServiceControl::PowerEvent );
                Add( L"SessionChange", ServiceControl::SessionChange );
                Add( L"PreShutdown", ServiceControl::PreShutdown );
                Add( L"TimeChange", ServiceControl::TimeChange );
                Add( L"UserLogoff", ServiceControl::UserLogoff );
                Add( L"TriggerEvent", ServiceControl::TriggerEvent );
                Add( L"LowResources", ServiceControl::LowResources );
                Add( L"SystemLowResources", ServiceControl::SystemLowResources );
            }
        };
        ServiceControlConverter serviceControlConverter;
    }

    WideString ToWideString( Services::ServiceControl value )
    {
        return serviceControlConverter.ToString( value );
    }
    WideString ToWideString( Services::ServiceControl value, const WideString& defaultResult )
    {
        return serviceControlConverter.ToString( value, defaultResult );
    }

    namespace Services
    {
        Services::ServiceControl ParseServiceControl( const WideString& str )
        {
            return serviceControlConverter.Parse( str );
        }

        Services::ServiceControl ParseServiceControl( const WideString& str, Services::ServiceControl defaultResult )
        {
            return serviceControlConverter.Parse( str, defaultResult );
        }

        bool TryParseServiceControl( const WideString& str, Services::ServiceControl& value )
        {
            return serviceControlConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // ServiceControlAccepted
    // =========================================================================
    namespace
    {
        using ServiceControlAccepted = Services::ServiceControlAccepted;
        class ServiceControlAcceptedConverter : public Flags<ServiceControlAccepted>
        {
        public:
            ServiceControlAcceptedConverter( )
            {
                Add( L"None", ServiceControlAccepted::None );
                Add( L"Stop", ServiceControlAccepted::Stop );
                Add( L"PauseAndContinue", ServiceControlAccepted::PauseAndContinue );
                Add( L"Shutdown", ServiceControlAccepted::Shutdown );
                Add( L"ParamChange", ServiceControlAccepted::ParamChange );
                Add( L"NetBindChange", ServiceControlAccepted::NetBindChange );
                Add( L"HardwareProfileChange", ServiceControlAccepted::HardwareProfileChange );
                Add( L"PowerEvent", ServiceControlAccepted::PowerEvent );
                Add( L"SessionChange", ServiceControlAccepted::SessionChange );
                Add( L"PreShutdown", ServiceControlAccepted::PreShutdown );
                Add( L"TimeChange", ServiceControlAccepted::TimeChange );
                Add( L"TriggerEvent", ServiceControlAccepted::TriggerEvent );
                Add( L"UserLogoff", ServiceControlAccepted::UserLogoff );
                Add( L"LowResources", ServiceControlAccepted::LowResources );
                Add( L"SystemLowResources", ServiceControlAccepted::SystemLowResources );
            }
        };
        ServiceControlAcceptedConverter serviceControlAcceptedConverter;
    }

    WideString ToWideString( Services::ServiceControlAccepted value )
    {
        return serviceControlAcceptedConverter.ToString( value );
    }
    WideString ToWideString( Services::ServiceControlAccepted value, const WideString& defaultResult )
    {
        return serviceControlAcceptedConverter.ToString( value, defaultResult );
    }

    namespace Services
    {
        Services::ServiceControlAccepted ParseServiceControlAccepted( const WideString& str )
        {
            return serviceControlAcceptedConverter.Parse( str );
        }

        Services::ServiceControlAccepted ParseServiceControlAccepted( const WideString& str, Services::ServiceControlAccepted defaultResult )
        {
            return serviceControlAcceptedConverter.Parse( str, defaultResult );
        }

        bool TryParseServiceControlAccepted( const WideString& str, Services::ServiceControlAccepted& value )
        {
            return serviceControlAcceptedConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // DeviceEventType
    // =========================================================================
    namespace
    {
        using DeviceEventType = Services::DeviceEventType;
        class DeviceEventTypeConverter : public Enum<DeviceEventType>
        {
        public:
            DeviceEventTypeConverter( )
            {
                Add( L"None", DeviceEventType::None );
                Add( L"Arrival", DeviceEventType::Arrival );
                Add( L"QueryRemove", DeviceEventType::QueryRemove );
                Add( L"QueryRemoveFailed", DeviceEventType::QueryRemoveFailed );
                Add( L"RemovePending", DeviceEventType::RemovePending );
                Add( L"RemoveComplete", DeviceEventType::RemoveComplete );
                Add( L"TypeSpecific", DeviceEventType::TypeSpecific );
                Add( L"CustomEvent", DeviceEventType::CustomEvent );
            }
        };
        DeviceEventTypeConverter deviceEventTypeConverter;
    }

    WideString ToWideString( Services::DeviceEventType value )
    {
        return deviceEventTypeConverter.ToString( value );
    }
    WideString ToWideString( Services::DeviceEventType value, const WideString& defaultResult )
    {
        return deviceEventTypeConverter.ToString( value, defaultResult );
    }

    namespace Services
    {
        Services::DeviceEventType ParseDeviceEventType( const WideString& str )
        {
            return deviceEventTypeConverter.Parse( str );
        }

        Services::DeviceEventType ParseDeviceEventType( const WideString& str, Services::DeviceEventType defaultResult )
        {
            return deviceEventTypeConverter.Parse( str, defaultResult );
        }

        bool TryParseDeviceEventType( const WideString& str, Services::DeviceEventType& value )
        {
            return deviceEventTypeConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // HardwareProfileChangeEventType
    // =========================================================================
    namespace
    {
        using HardwareProfileChangeEventType = Services::HardwareProfileChangeEventType;
        class HardwareProfileChangeEventTypeConverter : public Enum<HardwareProfileChangeEventType>
        {
        public:
            HardwareProfileChangeEventTypeConverter( )
            {
                Add( L"None", HardwareProfileChangeEventType::None );
                Add( L"ConfigChanged", HardwareProfileChangeEventType::ConfigChanged );
                Add( L"QueryChangeConfig", HardwareProfileChangeEventType::QueryChangeConfig );
                Add( L"ConfigChangeCanceled", HardwareProfileChangeEventType::ConfigChangeCanceled );
            }
        };
        HardwareProfileChangeEventTypeConverter hardwareProfileChangeEventTypeConverter;
    }

    WideString ToWideString( Services::HardwareProfileChangeEventType value )
    {
        return hardwareProfileChangeEventTypeConverter.ToString( value );
    }
    WideString ToWideString( Services::HardwareProfileChangeEventType value, const WideString& defaultResult )
    {
        return hardwareProfileChangeEventTypeConverter.ToString( value, defaultResult );
    }

    namespace Services
    {
        Services::HardwareProfileChangeEventType ParseHardwareProfileChangeEventType( const WideString& str )
        {
            return hardwareProfileChangeEventTypeConverter.Parse( str );
        }

        Services::HardwareProfileChangeEventType ParseHardwareProfileChangeEventType( const WideString& str, Services::HardwareProfileChangeEventType defaultResult )
        {
            return hardwareProfileChangeEventTypeConverter.Parse( str, defaultResult );
        }

        bool TryParseHardwareProfileChangeEventType( const WideString& str, Services::HardwareProfileChangeEventType& value )
        {
            return hardwareProfileChangeEventTypeConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // PowerEventType
    // =========================================================================
    namespace
    {
        using PowerEventType = Services::PowerEventType;
        class PowerEventTypeConverter : public Enum<PowerEventType>
        {
        public:
            PowerEventTypeConverter( )
            {
                Add( L"None", PowerEventType::None );
                Add( L"PowerStatusChange", PowerEventType::PowerStatusChange );
                Add( L"ResumeAutomatic", PowerEventType::ResumeAutomatic );
                Add( L"ResumeSuspend", PowerEventType::ResumeSuspend );
                Add( L"Suspend", PowerEventType::Suspend );
            }
        };
        PowerEventTypeConverter powerEventTypeConverter;
    }

    WideString ToWideString( Services::PowerEventType value )
    {
        return powerEventTypeConverter.ToString( value );
    }
    WideString ToWideString( Services::PowerEventType value, const WideString& defaultResult )
    {
        return powerEventTypeConverter.ToString( value, defaultResult );
    }

    namespace Services
    {
        Services::PowerEventType ParsePowerEventType( const WideString& str )
        {
            return powerEventTypeConverter.Parse( str );
        }

        Services::PowerEventType ParsePowerEventType( const WideString& str, Services::PowerEventType defaultResult )
        {
            return powerEventTypeConverter.Parse( str, defaultResult );
        }

        bool TryParsePowerEventType( const WideString& str, Services::PowerEventType& value )
        {
            return powerEventTypeConverter.TryParse( str, value );
        }
    }

}
