#pragma once
#ifndef __HCCSERVICE_H__
#define __HCCSERVICE_H__

#include <HCCDef.h> 
#include <HCCSecurity.h>
#include <HCCString.h>
#include <HCCConcepts.h>
#include <HCCSync.h>
#include <HCCArray.h>
#include <HCCApplication.h>

namespace Harlinn::Common::Core::Services
{
    enum class ServiceAccessRights : DWORD
    {
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,
        // Required to call the QueryServiceConfig and QueryServiceConfig2 functions to query the service configuration.
        QueryConfig = SERVICE_QUERY_CONFIG,
        // Required to call the ChangeServiceConfig or ChangeServiceConfig2 function to change the service configuration. 
        // Because this grants the caller the right to change the executable file that the system runs, it should be granted 
        // only to administrators.
        ChangeConfig = SERVICE_CHANGE_CONFIG,
        // Required to call the QueryServiceStatus or QueryServiceStatusEx function to ask the service control manager 
        // about the status of the service.
        // Required to call the NotifyServiceStatusChange function to receive notification when a service changes status.
        QueryStatus = SERVICE_QUERY_STATUS,
        // Required to call the EnumDependentServices function to enumerate all the services dependent on the service.
        EnumerateDependents = SERVICE_ENUMERATE_DEPENDENTS,
        // Required to call the StartService function to start the service.
        Start = SERVICE_START,
        // Required to call the ControlService function to stop the service.
        Stop = SERVICE_STOP,
        // Required to call the ControlService function to pause or continue the service.
        PauseAndContinue = SERVICE_PAUSE_CONTINUE,
        // Required to call the ControlService function to ask the service to report its status immediately.
        Interrogate = SERVICE_INTERROGATE,
        // Required to call the ControlService function to specify a user-defined control code.
        UserDefinedControl = SERVICE_USER_DEFINED_CONTROL,

        Read = StandardRightsRead | QueryConfig | QueryStatus | Interrogate | EnumerateDependents,
        Write = StandardRightsWrite | ChangeConfig,
        Execute = StandardRightsExecute | Start | Stop | PauseAndContinue | UserDefinedControl,


        FullControl = SERVICE_ALL_ACCESS

    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ServiceAccessRights, DWORD );

    /// <summary>
    /// The access mask for a service
    /// </summary>
    class ServiceAccessMask : public Security::AccessMaskT<ServiceAccessMask, ServiceAccessRights>
    {
    public:
        using Base = Security::AccessMaskT<ServiceAccessMask, ServiceAccessRights>;
        static constexpr const Security::GenericMapping Mapping
        {
            static_cast< ACCESS_MASK >( static_cast< ACCESS_MASK >( ServiceAccessRights::Read ) ),
            static_cast< ACCESS_MASK >( static_cast< ACCESS_MASK >( ServiceAccessRights::Write ) ),
            static_cast< ACCESS_MASK >( static_cast< ACCESS_MASK >( ServiceAccessRights::Execute ) ),
            static_cast< ACCESS_MASK >( static_cast< ACCESS_MASK >( ServiceAccessRights::FullControl ) )
        };

        constexpr ServiceAccessMask( ) noexcept
        {
        }
        constexpr explicit ServiceAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        constexpr explicit ServiceAccessMask( ServiceAccessRights rights ) noexcept
            : Base( rights )
        {
        }

        explicit ServiceAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit ServiceAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        explicit ServiceAccessMask( const ServiceAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }
        explicit ServiceAccessMask( const ServiceAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        explicit ServiceAccessMask( ServiceAccessRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
        explicit ServiceAccessMask( ServiceAccessRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }

    };


    enum class ServiceControlManagerAccessRights : DWORD
    {
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,
        // Required to connect to the service control manager.
        Connect = SC_MANAGER_CONNECT,
        // Required to call the CreateService function to create a service object and add it to the database.
        Create = SC_MANAGER_CREATE_SERVICE,
        // Required to call the EnumServicesStatus or EnumServicesStatusEx function to list the services that are in the database.
        // Required to call the NotifyServiceStatusChange function to receive notification when any service is created or deleted.
        Enumerate = SC_MANAGER_ENUMERATE_SERVICE,
        // Required to call the LockServiceDatabase function to acquire a lock on the database.
        Lock = SC_MANAGER_LOCK,
        // Required to call the QueryServiceLockStatus function to retrieve the lock status information for the database.
        QueryLockStatus = SC_MANAGER_QUERY_LOCK_STATUS,
        ModifyBootConfig = SC_MANAGER_MODIFY_BOOT_CONFIG,

        Read = StandardRightsRead | Enumerate | QueryLockStatus,
        Write = StandardRightsWrite | Create | ModifyBootConfig,
        Execute = StandardRightsExecute | Connect | Lock,

        FullControl = SC_MANAGER_ALL_ACCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ServiceControlManagerAccessRights, DWORD );

    /// <summary>
    /// The access mask for the service control manager
    /// </summary>
    class ServiceControlManagerAccessMask : public Security::AccessMaskT<ServiceControlManagerAccessMask, ServiceControlManagerAccessRights>
    {
    public:
        using Base = Security::AccessMaskT<ServiceControlManagerAccessMask, ServiceControlManagerAccessRights>;
        static constexpr const Security::GenericMapping Mapping
        {
            static_cast< ACCESS_MASK >( static_cast< ACCESS_MASK >( ServiceControlManagerAccessRights::Read ) ),
            static_cast< ACCESS_MASK >( static_cast< ACCESS_MASK >( ServiceControlManagerAccessRights::Write ) ),
            static_cast< ACCESS_MASK >( static_cast< ACCESS_MASK >( ServiceControlManagerAccessRights::Execute ) ),
            static_cast< ACCESS_MASK >( static_cast< ACCESS_MASK >( ServiceControlManagerAccessRights::FullControl ) )
        };

        constexpr ServiceControlManagerAccessMask( ) noexcept
        {
        }
        constexpr explicit ServiceControlManagerAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        constexpr explicit ServiceControlManagerAccessMask( ServiceControlManagerAccessRights rights ) noexcept
            : Base( rights )
        {
        }

        explicit ServiceControlManagerAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit ServiceControlManagerAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        explicit ServiceControlManagerAccessMask( const ServiceControlManagerAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }
        explicit ServiceControlManagerAccessMask( const ServiceControlManagerAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        explicit ServiceControlManagerAccessMask( ServiceControlManagerAccessRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
        explicit ServiceControlManagerAccessMask( ServiceControlManagerAccessRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
    };

    enum class ServiceType : DWORD
    {
        None = 0,
        KernelDriver = SERVICE_KERNEL_DRIVER,
        FileSystemDriver = SERVICE_FILE_SYSTEM_DRIVER,
        Adapter = SERVICE_ADAPTER,
        RecognizerDriver = SERVICE_RECOGNIZER_DRIVER,
        Driver = SERVICE_DRIVER,
        WindowsOwnProcess = SERVICE_WIN32_OWN_PROCESS,
        WindowsShareProcess = SERVICE_WIN32_SHARE_PROCESS,
        Windows = SERVICE_WIN32,
        UserService = SERVICE_USER_SERVICE,
        UserServiceInstance = SERVICE_USERSERVICE_INSTANCE,
        UserShareProcess = SERVICE_USER_SHARE_PROCESS,
        UserOwnProcess = SERVICE_USER_OWN_PROCESS,
        InteractiveProcess = SERVICE_INTERACTIVE_PROCESS,
        PkgService = SERVICE_PKG_SERVICE
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ServiceType, DWORD );

    enum class ServiceStartType : DWORD
    {
        BootStart = SERVICE_BOOT_START,
        SystemStart = SERVICE_SYSTEM_START,
        AutoStart = SERVICE_AUTO_START,
        DemandStart = SERVICE_DEMAND_START,
        Disabled = SERVICE_DISABLED
    };

    enum class ServiceEnumerationState : DWORD
    {
        None = 0,

        Active = SERVICE_ACTIVE,
        Inactive = SERVICE_INACTIVE,
        All = SERVICE_STATE_ALL
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ServiceEnumerationState, DWORD );


    enum class ServiceState : DWORD
    {
        Unknown = 0,
        Stopped = SERVICE_STOPPED,
        StartPending = SERVICE_START_PENDING,
        StopPending = SERVICE_STOP_PENDING,
        Running = SERVICE_RUNNING,
        ContinuePending = SERVICE_CONTINUE_PENDING,
        PausePending = SERVICE_PAUSE_PENDING,
        Paused = SERVICE_PAUSED,
    };


    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    enum class ServiceControl
    {
        Unknown = 0,
        /// <summary>
        /// <p>
        /// Notifies a service that it should stop.
        /// </p>
        /// <p>
        /// If a service accepts this control code, it must stop upon receipt and return NO_ERROR. 
        /// After the SCM sends this control code, it will not send other control codes to the 
        /// service. Windows XP:  If the service returns NO_ERROR and continues to run, it continues to 
        /// receive control codes. This behavior changed starting with Windows Server 2003 and Windows 
        /// XP with SP2.
        /// </p>
        /// </summary>
        Stop = SERVICE_CONTROL_STOP,
        /// <summary>
        /// <p>
        /// Notifies a service that it should pause.
        /// </p>
        /// </summary>
        Pause = SERVICE_CONTROL_PAUSE,
        /// <summary>
        /// <p>
        /// Notifies a paused service that it should resume.
        /// </p>
        /// </summary>
        Continue = SERVICE_CONTROL_CONTINUE,
        /// <summary>
        /// <p>
        /// Notifies a service to report its current status information to the service control manager.
        /// </p>
        /// <p>
        /// The handler should simply return NO_ERROR; the SCM is aware of the current state of the service.
        /// </p>
        /// </summary>
        Interrogate = SERVICE_CONTROL_INTERROGATE,
        /// <summary>
        /// <p>
        /// Notifies a service that the system is shutting down so the service can perform cleanup tasks. 
        /// Note that services that register for SERVICE_CONTROL_PRESHUTDOWN notifications cannot receive 
        /// this notification because they have already stopped.
        /// </p>
        /// <p>
        /// If a service accepts this control code, it must stop after it performs its cleanup tasks and 
        /// return NO_ERROR. After the SCM sends this control code, it will not send other control codes 
        /// to the service.
        /// </p>
        /// </summary>
        Shutdown = SERVICE_CONTROL_SHUTDOWN,
        /// <summary>
        /// <p>
        /// Notifies a service that service-specific startup parameters have changed. The service should 
        /// reread its startup parameters.
        /// </p>
        /// </summary>
        ParamChange = SERVICE_CONTROL_PARAMCHANGE,
        /// <summary>
        /// <p>
        /// Notifies a network service that there is a new component for binding. The service should bind 
        /// to the new component.
        /// </p>
        /// <p>
        /// Applications should use Plug and Play functionality instead.
        /// </p>
        /// </summary>
        NetBindAdd = SERVICE_CONTROL_NETBINDADD,
        /// <summary>
        /// <p>
        /// Notifies a network service that a component for binding has been removed. The service should 
        /// reread its binding information and unbind from the removed component.
        /// </p>
        /// <p>
        /// Applications should use Plug and Play functionality instead.
        /// </p>
        /// </summary>
        NetBindRemove = SERVICE_CONTROL_NETBINDREMOVE,
        /// <summary>
        /// <p>
        /// Notifies a network service that a disabled binding has been enabled. The service should reread 
        /// its binding information and add the new binding.
        /// </p>
        /// <p>
        /// Applications should use Plug and Play functionality instead.
        /// </p>
        /// </summary>
        NetBindEnable = SERVICE_CONTROL_NETBINDENABLE,
        /// <summary>
        /// <p>
        /// Notifies a network service that one of its bindings has been disabled. The service should reread 
        /// its binding information and remove the binding.
        /// </p>
        /// <p>
        /// Applications should use Plug and Play functionality instead.
        /// </p>
        /// </summary>
        NetBindDisable = SERVICE_CONTROL_NETBINDDISABLE,
        /// <summary>
        /// <p>
        /// Notifies a service of device events. (The service must have registered to receive these 
        /// notifications using the RegisterDeviceNotification function.) The eventType and eventData 
        /// parameters contain additional information.
        /// </p>
        /// </summary>
        DeviceEvent = SERVICE_CONTROL_DEVICEEVENT,
        /// <summary>
        /// <p>
        /// Notifies a service that the computer's hardware profile has changed. The eventType parameter 
        /// contains additional information.
        /// </p>
        /// </summary>
        HardwareProfileChange = SERVICE_CONTROL_HARDWAREPROFILECHANGE,
        /// <summary>
        /// <p>
        /// Notifies a service of system power events. The dwEventType parameter contains additional 
        /// information. If eventType is PBT_POWERSETTINGCHANGE, the eventData parameter also contains 
        /// additional information.
        /// </p>
        /// </summary>
        PowerEvent = SERVICE_CONTROL_POWEREVENT,
        /// <summary>
        /// <p>
        /// Notifies a service of session change events. Note that a service will only be notified of 
        /// a user logon if it is fully loaded before the logon attempt is made. The eventType and 
        /// eventData parameters contain additional information.
        /// </p>
        /// </summary>
        SessionChange = SERVICE_CONTROL_SESSIONCHANGE,
        /// <summary>
        /// <p>
        /// Notifies a service that the system will be shutting down. Services that need additional 
        /// time to perform cleanup tasks beyond the tight time restriction at system shutdown can 
        /// use this notification. The service control manager sends this notification to applications 
        /// that have registered for it before sending a SERVICE_CONTROL_SHUTDOWN notification to 
        /// applications that have registered for that notification.
        /// </p>
        /// <p>
        /// A service that handles this notification blocks system shutdown until the service stops 
        /// or the preshutdown time-out interval specified through SERVICE_PRESHUTDOWN_INFO expires. 
        /// Because this affects the user experience, services should use this feature only if it is 
        /// absolutely necessary to avoid data loss or significant recovery time at the next system 
        /// start.
        /// </p>
        /// </summary>
        PreShutdown = SERVICE_CONTROL_PRESHUTDOWN,
        /// <summary>
        /// <p>
        /// Notifies a service that the system time has changed. The eventData parameter contains 
        /// additional information. The eventType parameter is not used.
        /// </p>
        /// </summary>
        TimeChange = SERVICE_CONTROL_TIMECHANGE,

        UserLogoff = 0x00000011,
        /// <summary>
        /// <p>
        /// Notifies a service registered for a service trigger event that the event has occurred.
        /// </p>
        /// </summary>
        TriggerEvent = SERVICE_CONTROL_TRIGGEREVENT,
        /// <summary>
        /// <p>
        /// 
        /// </p>
        /// </summary>
        LowResources = SERVICE_CONTROL_LOWRESOURCES,
        /// <summary>
        /// <p>
        /// </p>
        /// </summary>
        SystemLowResources = SERVICE_CONTROL_SYSTEMLOWRESOURCES
    };


    enum class ServiceControlAccepted : DWORD
    {
        None = 0,
        Stop = SERVICE_ACCEPT_STOP,
        PauseAndContinue = SERVICE_ACCEPT_PAUSE_CONTINUE,
        Shutdown = SERVICE_ACCEPT_SHUTDOWN,
        ParamChange = SERVICE_ACCEPT_PARAMCHANGE,
        NetBindChange = SERVICE_ACCEPT_NETBINDCHANGE,
        HardwareProfileChange = SERVICE_ACCEPT_HARDWAREPROFILECHANGE,
        PowerEvent = SERVICE_ACCEPT_POWEREVENT,
        SessionChange = SERVICE_ACCEPT_SESSIONCHANGE,
        PreShutdown = SERVICE_ACCEPT_PRESHUTDOWN,
        TimeChange = SERVICE_ACCEPT_TIMECHANGE,
        TriggerEvent = SERVICE_ACCEPT_TRIGGEREVENT,
        UserLogoff = SERVICE_ACCEPT_USER_LOGOFF,
        LowResources = SERVICE_ACCEPT_LOWRESOURCES,
        SystemLowResources = SERVICE_ACCEPT_SYSTEMLOWRESOURCES
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ServiceControlAccepted, DWORD );

    enum class DeviceEventType : DWORD
    {
        None = 0,
        // system detected a new device
        Arrival = DBT_DEVICEARRIVAL,
        QueryRemove = DBT_DEVICEQUERYREMOVE,
        QueryRemoveFailed = DBT_DEVICEQUERYREMOVEFAILED,
        RemovePending = DBT_DEVICEREMOVEPENDING,
        RemoveComplete = DBT_DEVICEREMOVECOMPLETE,
        TypeSpecific = DBT_DEVICETYPESPECIFIC,
        CustomEvent = DBT_CUSTOMEVENT
    };

    enum class HardwareProfileChangeEventType : DWORD
    {
        None = 0,
        ConfigChanged = DBT_CONFIGCHANGED,
        QueryChangeConfig = DBT_QUERYCHANGECONFIG,
        ConfigChangeCanceled = DBT_CONFIGCHANGECANCELED
    };

    enum class PowerEventType
    {
        None = 0,
        PowerStatusChange = PBT_APMPOWERSTATUSCHANGE,
        ResumeAutomatic = PBT_APMRESUMEAUTOMATIC,
        ResumeSuspend = PBT_APMRESUMESUSPEND,
        Suspend = PBT_APMSUSPEND
    };





    class ServiceHandle
    {
        SC_HANDLE handle_ = nullptr;
    public:
        constexpr ServiceHandle( ) = default;

        constexpr explicit ServiceHandle( SC_HANDLE handle )
            : handle_( handle )
        {
        }

        ServiceHandle( const ServiceHandle& other ) = delete;
        constexpr ServiceHandle( ServiceHandle&& other ) noexcept
            : handle_( other.handle_ )
        {
            other.handle_ = nullptr;
        }

        ~ServiceHandle( )
        {
            if ( handle_ )
            {
                CloseServiceHandle( handle_ );
            }
        }

        ServiceHandle& operator = ( const ServiceHandle& other ) = delete;
        constexpr ServiceHandle& operator = ( ServiceHandle&& other ) noexcept
        {
            std::swap( handle_, other.handle_ );
            return *this;
        }
    };
    


    class ServiceControlManager
    {
        SC_HANDLE handle_ = nullptr;
    public:
        constexpr ServiceControlManager( ) = default;

        constexpr explicit ServiceControlManager( SC_HANDLE handle )
            : handle_( handle )
        { }

        ServiceControlManager( const ServiceControlManager& other ) = delete;
        constexpr ServiceControlManager( ServiceControlManager&& other ) noexcept
            : handle_( other.handle_ )
        {
            other.handle_ = nullptr;
        }

        ~ServiceControlManager()
        {
            if ( handle_ )
            {
                CloseServiceHandle( handle_ );
            }
        }

        ServiceControlManager& operator = ( const ServiceControlManager& other ) = delete;
        constexpr ServiceControlManager& operator = ( ServiceControlManager&& other ) noexcept
        {
            std::swap( handle_, other.handle_);
            return *this;
        }

        /// <summary>
        /// Establishes a connection to the service control manager on the specified 
        /// computer and opens the specified service control manager database.
        /// </summary>
        /// <param name="machineName">
        /// The name of the target computer. If the pointer is nullptr or points to 
        /// an empty string, the function connects to the service control manager on 
        /// the local computer.
        /// </param>
        /// <param name="databaseName">
        /// The name of the service control manager database. This parameter should be 
        /// set to SERVICES_ACTIVE_DATABASE. If it is NULL, the SERVICES_ACTIVE_DATABASE 
        /// database is opened by default.
        /// </param>
        /// <param name="desiredAccessRights">
        /// <p>
        /// The access to the service control manager. For a list of access rights, 
        /// see <see cref="ServiceControlManagerAccessRights">ServiceControlManagerAccessRights</see>.
        /// </p>
        /// <p>
        /// Before granting the requested access rights, the system checks the access token of the 
        /// calling process against the discretionary access-control list of the security descriptor 
        /// associated with the service control manager.
        /// </p>
        /// <p>
        /// The ServiceControlManagerAccessRights::Connect access right is implicitly specified by calling this function.
        /// </p>
        /// </param>
        /// <returns>
        /// A ServiceControlManager object connected to the specified service control manager database.
        /// </returns>
        static ServiceControlManager Open( const wchar_t* machineName, const wchar_t* databaseName, ServiceControlManagerAccessRights desiredAccessRights )
        {
            auto handle = OpenSCManagerW( machineName, databaseName, static_cast<DWORD>(desiredAccessRights) );
            if ( handle == nullptr )
            {
                ThrowLastOSError( );
            }
            return ServiceControlManager( handle );
        }

        static ServiceControlManager Open( const wchar_t* machineName, ServiceControlManagerAccessRights desiredAccessRights )
        {
            return Open( machineName, nullptr, desiredAccessRights );
        }
        static ServiceControlManager Open( ServiceControlManagerAccessRights desiredAccessRights )
        {
            return Open( nullptr, nullptr, desiredAccessRights );
        }
        template<SimpleWideStringLike StringT>
        static ServiceControlManager Open( const StringT& machineName, const StringT& databaseName, ServiceControlManagerAccessRights desiredAccessRights )
        {
            return Open( machineName.c_str(), databaseName.c_str( ), desiredAccessRights );
        }
        template<SimpleWideStringLike StringT>
        static ServiceControlManager Open( const StringT& machineName, ServiceControlManagerAccessRights desiredAccessRights )
        {
            return Open( machineName.c_str( ), nullptr, desiredAccessRights );
        }
    };


    class IServiceHost
    {
    public:
        virtual ~IServiceHost( ) = default;

        virtual bool StartDispatcher( const SERVICE_TABLE_ENTRYW* serviceStartTable ) = 0;
        virtual SERVICE_STATUS_HANDLE RegisterHandler(_In_ LPCWSTR serviceName, _In_ __callback LPHANDLER_FUNCTION_EX handlerProc, _In_opt_ LPVOID context ) = 0;
        virtual bool SupportsRequestDeviceNotifications( )
        {
            return false;
        }
        virtual HDEVNOTIFY RequestDeviceNotifications( SERVICE_STATUS_HANDLE serviceStatusHandle, bool allInterfaceClasses, LPVOID notificationFilter ) = 0;
        virtual bool SetStatus( _In_ SERVICE_STATUS_HANDLE serviceStatusHandle, _In_ LPSERVICE_STATUS serviceStatus) = 0;
    };

    class WindowsServiceHost : public IServiceHost
    {
    public:
        virtual bool StartDispatcher( const SERVICE_TABLE_ENTRYW* serviceStartTable ) override
        {
            return StartServiceCtrlDispatcherW( serviceStartTable ) != FALSE;
        }

        virtual SERVICE_STATUS_HANDLE RegisterHandler( _In_ LPCWSTR serviceName, _In_ __callback LPHANDLER_FUNCTION_EX handlerProc, _In_opt_ LPVOID context ) override
        {
            return RegisterServiceCtrlHandlerExW( serviceName, handlerProc, context );
        }

        virtual bool SupportsRequestDeviceNotifications( )
        {
            return true;
        }
        virtual HDEVNOTIFY RequestDeviceNotifications( SERVICE_STATUS_HANDLE serviceStatusHandle, bool allInterfaceClasses, LPVOID notificationFilter )
        {
            DWORD flags = DEVICE_NOTIFY_SERVICE_HANDLE;
            if ( allInterfaceClasses )
            {
                flags |= DEVICE_NOTIFY_ALL_INTERFACE_CLASSES;
            }
            return RegisterDeviceNotificationW( serviceStatusHandle, notificationFilter, flags );
        }

        virtual bool SetStatus( _In_ SERVICE_STATUS_HANDLE serviceStatusHandle, _In_ LPSERVICE_STATUS serviceStatus ) override
        {
            return SetServiceStatus( serviceStatusHandle, serviceStatus ) != FALSE;
        }
    };





    class ServiceApplication;
    class ServiceBase
    {
        friend class ServiceApplication;
        WideString name_;
        Services::ServiceControlAccepted serviceControlAccepted_;
        Services::ServiceType serviceType_;

        SERVICE_STATUS_HANDLE serviceStatusHandle_ = nullptr;
        SERVICE_STATUS serviceStatus_{};
        EventWaitHandle serviceStoppedEventWaitHandle_;
        IServiceHost* serviceHost_ = nullptr;
        DWORD argc_ = 0;
        LPWSTR* argv_ = nullptr;
    public:
        ServiceBase( const WideString& name, Services::ServiceControlAccepted serviceControlAccepted = Services::ServiceControlAccepted::Stop, Services::ServiceType serviceType = Services::ServiceType::WindowsOwnProcess );
        
        virtual ~ServiceBase( )
        {
        }

        const WideString& Name( ) const noexcept
        {
            return name_;
        }

        bool RegisterServiceControlHandler( )
        {
            serviceStatusHandle_ = serviceHost_->RegisterHandler( name_.c_str( ), ServiceHandlerFunctionEx, this );
            return serviceStatusHandle_ != nullptr;
        }
    protected:
        void SetServiceStatus( Services::ServiceState currentState, DWORD exitCode = NO_ERROR, DWORD waitHint = 0 )
        {
            serviceStatus_.dwCurrentState = static_cast<DWORD>( currentState );
            serviceStatus_.dwWin32ExitCode = exitCode;
            serviceStatus_.dwWaitHint = waitHint;

            if ( currentState == Services::ServiceState::StartPending )
            {
                serviceStatus_.dwControlsAccepted = 0;
            }
            else
            {
                serviceStatus_.dwControlsAccepted = static_cast< DWORD >( serviceControlAccepted_ );
            }

            if ( ( currentState == Services::ServiceState::Running ) || ( currentState == Services::ServiceState::Stopped ) )
            {
                serviceStatus_.dwCheckPoint = 0;
            }
            else
            {
                serviceStatus_.dwCheckPoint++;
            }
            serviceHost_->SetStatus( serviceStatusHandle_, &serviceStatus_ );
        }

    public:
        virtual void Execute( DWORD argc, LPWSTR* argv )
        {
            argc_ = argc;
            argv_ = argv;

            if ( this->Initialize( ) )
            {
                this->Run( );
            }
            else
            {
                SetServiceStatus( Services::ServiceState::Stopped );
            }
        }

        virtual void Stop()
        {
            serviceStoppedEventWaitHandle_.Signal( );
        }

    protected:
        virtual bool Initialize( )
        {
            SetServiceStatus( Services::ServiceState::StartPending );
            return true;
        }


        virtual void Run( )
        {
            SetServiceStatus( Services::ServiceState::Running );
            serviceStoppedEventWaitHandle_.Wait( );
            SetServiceStatus( Services::ServiceState::Stopped );
        }
        
    protected:
        virtual WinError HandleStop( ) noexcept
        {
            this->Stop( );
            return WinError::NoError;
        }
        virtual WinError HandlePause( )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandleContinue( )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandleInterrogate( )
        {
            return WinError::NoError;
        }
        virtual WinError HandleShutdown( )
        {
            return WinError::NoError;
        }
        virtual WinError HandleParamChange( )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandleNetBindAdd( )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandleNetBindRemove( )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandleNetBindEnable( )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandleNetBindDisable( )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandleDeviceEvent( DeviceEventType deviceEventType, const void* deviceEventData )
        {
            return WinError::NoError;
        }
        virtual WinError HandleHardwareProfileChange( HardwareProfileChangeEventType hardwareProfileChangeEventType )
        {
            return WinError::NoError;
        }
        virtual WinError HandlePowerEvent( PowerEventType powerEventType, const POWERBROADCAST_SETTING* powerEventData )
        {
            return WinError::NoError;
        }
        virtual WinError HandleSessionChange( const WTSSESSION_NOTIFICATION* eventData )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandlePreShutdown( )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandleTimeChange( const SERVICE_TIMECHANGE_INFO* serviceTimeChangeInfo )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandleUserLogoff( )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandleTriggerEvent( )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandleLowResources( )
        {
            return WinError::CallNotImplemented;
        }
        virtual WinError HandleSystemLowResources( )
        {
            return WinError::CallNotImplemented;
        }



    protected:
        virtual WinError HandleControl( ServiceControl serviceControl, DWORD eventType, LPVOID eventData )
        {
            WinError result = WinError::CallNotImplemented;

            switch ( serviceControl )
            {
                case ServiceControl::Stop:
                    result = this->HandleStop( );
                    break;
                case ServiceControl::Pause:
                    result = this->HandlePause( );
                    break;
                case ServiceControl::Continue:
                    result = this->HandleContinue( );
                    break;
                case ServiceControl::Interrogate:
                    result = this->HandleInterrogate( );
                    break;
                case ServiceControl::Shutdown:
                    result = this->HandleShutdown( );
                    break;
                case ServiceControl::ParamChange:
                    result = this->HandleParamChange( );
                    break;
                case ServiceControl::NetBindAdd:
                    result = this->HandleNetBindAdd( );
                    break;
                case ServiceControl::NetBindRemove:
                    result = this->HandleNetBindRemove( );
                    break;
                case ServiceControl::NetBindEnable:
                    result = this->HandleNetBindEnable( );
                    break;
                case ServiceControl::NetBindDisable:
                    result = this->HandleNetBindDisable( );
                    break;
                case ServiceControl::DeviceEvent:
                    result = this->HandleDeviceEvent( static_cast< DeviceEventType >( eventType ), eventData );
                    break;
                case ServiceControl::HardwareProfileChange:
                    result = this->HandleHardwareProfileChange( static_cast< HardwareProfileChangeEventType >( eventType ) );
                    break;
                case ServiceControl::PowerEvent:
                    result = this->HandlePowerEvent( static_cast< PowerEventType >( eventType ), reinterpret_cast< const POWERBROADCAST_SETTING* >( eventData ) );
                    break;
                case ServiceControl::SessionChange:
                    result = this->HandleSessionChange( reinterpret_cast< const WTSSESSION_NOTIFICATION* >( eventData ) );
                    break;
                case ServiceControl::PreShutdown:
                    result = this->HandlePreShutdown( );
                    break;
                case ServiceControl::TimeChange:
                    result = this->HandleTimeChange( reinterpret_cast< const SERVICE_TIMECHANGE_INFO* >( eventData ) );
                    break;
                case ServiceControl::UserLogoff:
                    result = this->HandleUserLogoff( );
                    break;
                case ServiceControl::TriggerEvent:
                    result = this->HandleTriggerEvent( );
                    break;
                case ServiceControl::LowResources:
                    result = this->HandleLowResources( );
                    break;
                case ServiceControl::SystemLowResources:
                    result = this->HandleSystemLowResources( );
                    break;
            }

            return result;
        }
    protected:
        static DWORD WINAPI ServiceHandlerFunctionEx( DWORD control, DWORD eventType, LPVOID eventData, LPVOID context )
        {
            DWORD result = ERROR_CALL_NOT_IMPLEMENTED;
            if ( context )
            {
                auto* serviceBase = reinterpret_cast<ServiceBase*>( context );
                try
                {
                    result = static_cast< DWORD >( serviceBase->HandleControl( static_cast< ServiceControl >( control ), eventType, eventData ) );
                }
                catch ( const ThreadAbortException& /*exception*/ )
                { 
                    // This thread cannot be aborted
                    //throw; 
                } 
                catch ( const Exception& exception ) 
                { 
                    ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); 
                } 
                catch ( const std::exception& exception ) 
                { 
                    ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); 
                } 
                catch ( ... ) 
                { 
                    ReportUnknownException( CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); 
                }
            }
            return result;
        }
    };


    /// <summary>
    /// Derived classes must implement a parameterless constructor.
    /// </summary>
    template<typename DerivedT>
    class Service : public ServiceBase
    {
    public:
        using Base = ServiceBase;
        using DerivedType = DerivedT;
    private:
        
    public:
        Service( Services::ServiceControlAccepted serviceControlAccepted = Services::ServiceControlAccepted::Stop, Services::ServiceType serviceType = Services::ServiceType::WindowsOwnProcess )
            : Base( DerivedType::ServiceName( ), serviceControlAccepted, serviceType )
        {
        }

        static void __stdcall Main( DWORD argc, LPWSTR* argv )
        {
            auto service = std::make_unique<DerivedType>( );
            if ( service->RegisterServiceControlHandler( ) )
            {
                service->Execute( argc, argv );
            }
        }

        // static constexpr const wchar_t* ServiceName( ) { return L""; }

    };





    class Application : public Core::Application
    {
        IServiceHost* serviceHost_ = nullptr;
        std::vector<SERVICE_TABLE_ENTRYW> serviceEntries_;
    public:
        using Base = Core::Application;

        HCC_EXPORT Application( const std::shared_ptr<ApplicationOptions>& options, IServiceHost* serviceHost );
        HCC_EXPORT ~Application( );

        static Application& Instance( ) noexcept
        {
            return static_cast< Application& >( Base::Instance( ) );
        }

        IServiceHost* ServiceHost( ) const
        {
            return serviceHost_;
        }

        template<typename ServiceT>
        void RegisterService( )
        {
            SERVICE_TABLE_ENTRYW& entry = serviceEntries_.emplace_back();
            entry.lpServiceName = ServiceT::ServiceName( );
            entry.lpServiceProc = &ServiceT::Main;
        }

        void Run( )
        {
            SERVICE_TABLE_ENTRYW& entry = serviceEntries_.emplace_back( );
            entry.lpServiceName = nullptr;
            entry.lpServiceProc = nullptr;
            serviceHost_->StartDispatcher( serviceEntries_.data( ) );
        }

    };

    inline ServiceBase::ServiceBase( const WideString& name, Services::ServiceControlAccepted serviceControlAccepted, Services::ServiceType serviceType )
        : name_( name ), serviceControlAccepted_( serviceControlAccepted ), serviceType_( serviceType ), serviceStoppedEventWaitHandle_( true ), serviceHost_( Application::Instance().ServiceHost() )
    {
    }
}

namespace Harlinn::Common::Core
{
    // =========================================================================
    // ServiceAccessRights
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Services::ServiceAccessRights value );
    HCC_EXPORT WideString ToWideString( Services::ServiceAccessRights value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Services::ServiceAccessRights value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Services::ServiceAccessRights value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Services
    {
        HCC_EXPORT Services::ServiceAccessRights ParseServiceAccessRights( const WideString& str );
        HCC_EXPORT Services::ServiceAccessRights ParseServiceAccessRights( const WideString& str, Services::ServiceAccessRights defaultResult );
        HCC_EXPORT bool TryParseServiceAccessRights( const WideString& str, Services::ServiceAccessRights& value );

        inline Services::ServiceAccessRights ParseServiceAccessRights( const AnsiString& str )
        {
            return ParseServiceAccessRights( ToWideString( str ) );
        }
        inline Services::ServiceAccessRights ParseServiceAccessRights( const AnsiString& str, Services::ServiceAccessRights defaultResult )
        {
            return ParseServiceAccessRights( ToWideString( str ), defaultResult );
        }
        inline bool TryParseServiceAccessRights( const AnsiString& str, Services::ServiceAccessRights& value )
        {
            return TryParseServiceAccessRights( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Services::ServiceAccessRights& value )
    {
        return Services::TryParseServiceAccessRights( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Services::ServiceAccessRights, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Services::ParseServiceAccessRights( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Services::ServiceAccessRights, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Services::ParseServiceAccessRights( str );
    }

    // =========================================================================
    // ServiceControlManagerAccessRights
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Services::ServiceControlManagerAccessRights value );
    HCC_EXPORT WideString ToWideString( Services::ServiceControlManagerAccessRights value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Services::ServiceControlManagerAccessRights value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Services::ServiceControlManagerAccessRights value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Services
    {
        HCC_EXPORT Services::ServiceControlManagerAccessRights ParseServiceControlManagerAccessRights( const WideString& str );
        HCC_EXPORT Services::ServiceControlManagerAccessRights ParseServiceControlManagerAccessRights( const WideString& str, Services::ServiceControlManagerAccessRights defaultResult );
        HCC_EXPORT bool TryParseServiceControlManagerAccessRights( const WideString& str, Services::ServiceControlManagerAccessRights& value );

        inline Services::ServiceControlManagerAccessRights ParseServiceControlManagerAccessRights( const AnsiString& str )
        {
            return ParseServiceControlManagerAccessRights( ToWideString( str ) );
        }
        inline Services::ServiceControlManagerAccessRights ParseServiceControlManagerAccessRights( const AnsiString& str, Services::ServiceControlManagerAccessRights defaultResult )
        {
            return ParseServiceControlManagerAccessRights( ToWideString( str ), defaultResult );
        }
        inline bool TryParseServiceControlManagerAccessRights( const AnsiString& str, Services::ServiceControlManagerAccessRights& value )
        {
            return TryParseServiceControlManagerAccessRights( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Services::ServiceControlManagerAccessRights& value )
    {
        return Services::TryParseServiceControlManagerAccessRights( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Services::ServiceControlManagerAccessRights, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Services::ParseServiceControlManagerAccessRights( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Services::ServiceControlManagerAccessRights, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Services::ParseServiceControlManagerAccessRights( str );
    }

    // =========================================================================
    // ServiceType
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Services::ServiceType value );
    HCC_EXPORT WideString ToWideString( Services::ServiceType value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Services::ServiceType value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Services::ServiceType value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Services
    {
        HCC_EXPORT Services::ServiceType ParseServiceType( const WideString& str );
        HCC_EXPORT Services::ServiceType ParseServiceType( const WideString& str, Services::ServiceType defaultResult );
        HCC_EXPORT bool TryParseServiceType( const WideString& str, Services::ServiceType& value );

        inline Services::ServiceType ParseServiceType( const AnsiString& str )
        {
            return ParseServiceType( ToWideString( str ) );
        }
        inline Services::ServiceType ParseServiceType( const AnsiString& str, Services::ServiceType defaultResult )
        {
            return ParseServiceType( ToWideString( str ), defaultResult );
        }
        inline bool TryParseServiceType( const AnsiString& str, Services::ServiceType& value )
        {
            return TryParseServiceType( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Services::ServiceType& value )
    {
        return Services::TryParseServiceType( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Services::ServiceType, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Services::ParseServiceType( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Services::ServiceType, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Services::ParseServiceType( str );
    }

    // =========================================================================
    // ServiceStartType
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Services::ServiceStartType value );
    HCC_EXPORT WideString ToWideString( Services::ServiceStartType value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Services::ServiceStartType value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Services::ServiceStartType value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Services
    {
        HCC_EXPORT Services::ServiceStartType ParseServiceStartType( const WideString& str );
        HCC_EXPORT Services::ServiceStartType ParseServiceStartType( const WideString& str, Services::ServiceStartType defaultResult );
        HCC_EXPORT bool TryParseServiceStartType( const WideString& str, Services::ServiceStartType& value );

        inline Services::ServiceStartType ParseServiceStartType( const AnsiString& str )
        {
            return ParseServiceStartType( ToWideString( str ) );
        }
        inline Services::ServiceStartType ParseServiceStartType( const AnsiString& str, Services::ServiceStartType defaultResult )
        {
            return ParseServiceStartType( ToWideString( str ), defaultResult );
        }
        inline bool TryParseServiceStartType( const AnsiString& str, Services::ServiceStartType& value )
        {
            return TryParseServiceStartType( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Services::ServiceStartType& value )
    {
        return Services::TryParseServiceStartType( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Services::ServiceStartType, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Services::ParseServiceStartType( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Services::ServiceStartType, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Services::ParseServiceStartType( str );
    }

    // =========================================================================
    // ServiceEnumerationState
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Services::ServiceEnumerationState value );
    HCC_EXPORT WideString ToWideString( Services::ServiceEnumerationState value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Services::ServiceEnumerationState value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Services::ServiceEnumerationState value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Services
    {
        HCC_EXPORT Services::ServiceEnumerationState ParseServiceEnumerationState( const WideString& str );
        HCC_EXPORT Services::ServiceEnumerationState ParseServiceEnumerationState( const WideString& str, Services::ServiceEnumerationState defaultResult );
        HCC_EXPORT bool TryParseServiceEnumerationState( const WideString& str, Services::ServiceEnumerationState& value );

        inline Services::ServiceEnumerationState ParseServiceEnumerationState( const AnsiString& str )
        {
            return ParseServiceEnumerationState( ToWideString( str ) );
        }
        inline Services::ServiceEnumerationState ParseServiceEnumerationState( const AnsiString& str, Services::ServiceEnumerationState defaultResult )
        {
            return ParseServiceEnumerationState( ToWideString( str ), defaultResult );
        }
        inline bool TryParseServiceEnumerationState( const AnsiString& str, Services::ServiceEnumerationState& value )
        {
            return TryParseServiceEnumerationState( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Services::ServiceEnumerationState& value )
    {
        return Services::TryParseServiceEnumerationState( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Services::ServiceEnumerationState, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Services::ParseServiceEnumerationState( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Services::ServiceEnumerationState, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Services::ParseServiceEnumerationState( str );
    }

    // =========================================================================
    // ServiceState
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Services::ServiceState value );
    HCC_EXPORT WideString ToWideString( Services::ServiceState value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Services::ServiceState value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Services::ServiceState value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Services
    {
        HCC_EXPORT Services::ServiceState ParseServiceState( const WideString& str );
        HCC_EXPORT Services::ServiceState ParseServiceState( const WideString& str, Services::ServiceState defaultResult );
        HCC_EXPORT bool TryParseServiceState( const WideString& str, Services::ServiceState& value );

        inline Services::ServiceState ParseServiceState( const AnsiString& str )
        {
            return ParseServiceState( ToWideString( str ) );
        }
        inline Services::ServiceState ParseServiceState( const AnsiString& str, Services::ServiceState defaultResult )
        {
            return ParseServiceState( ToWideString( str ), defaultResult );
        }
        inline bool TryParseServiceState( const AnsiString& str, Services::ServiceState& value )
        {
            return TryParseServiceState( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Services::ServiceState& value )
    {
        return Services::TryParseServiceState( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Services::ServiceState, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Services::ParseServiceState( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Services::ServiceState, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Services::ParseServiceState( str );
    }

    // =========================================================================
    // ServiceControl
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Services::ServiceControl value );
    HCC_EXPORT WideString ToWideString( Services::ServiceControl value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Services::ServiceControl value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Services::ServiceControl value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Services
    {
        HCC_EXPORT Services::ServiceControl ParseServiceControl( const WideString& str );
        HCC_EXPORT Services::ServiceControl ParseServiceControl( const WideString& str, Services::ServiceControl defaultResult );
        HCC_EXPORT bool TryParseServiceControl( const WideString& str, Services::ServiceControl& value );

        inline Services::ServiceControl ParseServiceControl( const AnsiString& str )
        {
            return ParseServiceControl( ToWideString( str ) );
        }
        inline Services::ServiceControl ParseServiceControl( const AnsiString& str, Services::ServiceControl defaultResult )
        {
            return ParseServiceControl( ToWideString( str ), defaultResult );
        }
        inline bool TryParseServiceControl( const AnsiString& str, Services::ServiceControl& value )
        {
            return TryParseServiceControl( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Services::ServiceControl& value )
    {
        return Services::TryParseServiceControl( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Services::ServiceControl, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Services::ParseServiceControl( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Services::ServiceControl, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Services::ParseServiceControl( str );
    }

    // =========================================================================
    // ServiceControlAccepted
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Services::ServiceControlAccepted value );
    HCC_EXPORT WideString ToWideString( Services::ServiceControlAccepted value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Services::ServiceControlAccepted value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Services::ServiceControlAccepted value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Services
    {
        HCC_EXPORT Services::ServiceControlAccepted ParseServiceControlAccepted( const WideString& str );
        HCC_EXPORT Services::ServiceControlAccepted ParseServiceControlAccepted( const WideString& str, Services::ServiceControlAccepted defaultResult );
        HCC_EXPORT bool TryParseServiceControlAccepted( const WideString& str, Services::ServiceControlAccepted& value );

        inline Services::ServiceControlAccepted ParseServiceControlAccepted( const AnsiString& str )
        {
            return ParseServiceControlAccepted( ToWideString( str ) );
        }
        inline Services::ServiceControlAccepted ParseServiceControlAccepted( const AnsiString& str, Services::ServiceControlAccepted defaultResult )
        {
            return ParseServiceControlAccepted( ToWideString( str ), defaultResult );
        }
        inline bool TryParseServiceControlAccepted( const AnsiString& str, Services::ServiceControlAccepted& value )
        {
            return TryParseServiceControlAccepted( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Services::ServiceControlAccepted& value )
    {
        return Services::TryParseServiceControlAccepted( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Services::ServiceControlAccepted, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Services::ParseServiceControlAccepted( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Services::ServiceControlAccepted, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Services::ParseServiceControlAccepted( str );
    }

    // =========================================================================
    // DeviceEventType
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Services::DeviceEventType value );
    HCC_EXPORT WideString ToWideString( Services::DeviceEventType value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Services::DeviceEventType value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Services::DeviceEventType value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Services
    {
        HCC_EXPORT Services::DeviceEventType ParseDeviceEventType( const WideString& str );
        HCC_EXPORT Services::DeviceEventType ParseDeviceEventType( const WideString& str, Services::DeviceEventType defaultResult );
        HCC_EXPORT bool TryParseDeviceEventType( const WideString& str, Services::DeviceEventType& value );

        inline Services::DeviceEventType ParseDeviceEventType( const AnsiString& str )
        {
            return ParseDeviceEventType( ToWideString( str ) );
        }
        inline Services::DeviceEventType ParseDeviceEventType( const AnsiString& str, Services::DeviceEventType defaultResult )
        {
            return ParseDeviceEventType( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDeviceEventType( const AnsiString& str, Services::DeviceEventType& value )
        {
            return TryParseDeviceEventType( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Services::DeviceEventType& value )
    {
        return Services::TryParseDeviceEventType( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Services::DeviceEventType, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Services::ParseDeviceEventType( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Services::DeviceEventType, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Services::ParseDeviceEventType( str );
    }


}


#endif
