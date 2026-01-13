#pragma once
#ifndef __HCCSERVICE_H__
#define __HCCSERVICE_H__
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
#include <HCCSecurity.h>
#include <HCCString.h>
#include <HCCConcepts.h>
#include <HCCSync.h>
#include <HCCArray.h>
#include <HCCApplication.h>
#include <HCCIterator.h>

namespace Harlinn::Common::Core::Services
{
#ifdef USE_REPORTSERVICEMESSAGE
    inline void ReportServiceMessage( const char* message )
    {
        if ( message && message[ 0 ] )
        {
            size_t length = strlen( message );
            IO::FileStream fileStream( L"C:\\Logs\\simple.log", IO::FileAccess::ReadWrite | IO::FileAccess::Append, IO::FileShare::Read, IO::FileMode::Append, IO::FileAttributes::Normal, IO::FileOptions::Default );
            fileStream.Write( message, length );
            fileStream.Write( "\r\n", 2 );
        }
    }
#endif

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

    enum class ServiceErrorControl : DWORD
    {
        Ignore = SERVICE_ERROR_IGNORE,
        Normal = SERVICE_ERROR_NORMAL,
        Severe = SERVICE_ERROR_SEVERE,
        Critical = SERVICE_ERROR_CRITICAL
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

    enum class ServiceFlags : DWORD
    {

        None = 0,
        /// <summary>
        /// The service runs in a system process that must always be running.
        /// </summary>
        RunsInSystemProcess = SERVICE_RUNS_IN_SYSTEM_PROCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ServiceFlags, DWORD );

    enum class ServiceEnumFlags : DWORD
    {
        Active = SERVICE_ACTIVE,
        Inactive = SERVICE_INACTIVE,
        All = SERVICE_STATE_ALL
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ServiceEnumFlags, DWORD );


    struct ServiceStatus
    {
        Services::ServiceType ServiceType = Services::ServiceType::None;
        Services::ServiceState CurrentState = Services::ServiceState::Unknown;
        Services::ServiceControlAccepted ControlsAccepted = Services::ServiceControlAccepted::None;
        DWORD ExitCode = 0;
        DWORD ServiceSpecificExitCode = 0;
        DWORD CheckPoint = 0;
        DWORD WaitHint = 0;

        DWORD WaitTime( )
        {
            DWORD waitTime = WaitHint / 10;

            if ( waitTime < 1000 )
            {
                waitTime = 1000;
            }
            else if ( waitTime > 10000 )
            {
                waitTime = 10000;
            }
            return waitTime;
        }

    };
    static_assert( sizeof( ServiceStatus ) == sizeof( SERVICE_STATUS ) );

    struct ServiceStatusProcess : public ServiceStatus
    {
        DWORD ProcessId = 0;
        Services::ServiceFlags ServiceFlags = Services::ServiceFlags::None;
    };
    static_assert( sizeof( ServiceStatusProcess ) == sizeof( SERVICE_STATUS_PROCESS ));

    



    struct ServiceStatusEntry
    {
        LPWSTR ServiceName;
        LPWSTR DisplayName;
        Services::ServiceStatus ServiceStatus;
    };
    static_assert( sizeof( ServiceStatusEntry ) == sizeof( ENUM_SERVICE_STATUSW ) );

    class ServiceHandle;
    class ServiceStatusEntries
    {
        size_t memorySize_ = 0;
        size_t size_ = 0;
        ServiceStatusEntry* data_ = nullptr;
    public:
        using value_type = ServiceStatusEntry;
        using size_type = size_t;
        using difference_type = SSizeT;
        using pointer = value_type*;
        using reference = value_type&;
        using const_pointer = const value_type*;
        using const_reference = const value_type&;
        using iterator = Core::Internal::PointerIterator<ServiceStatusEntries>;
        using const_iterator = Core::Internal::ConstPointerIterator<ServiceStatusEntries>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        ServiceStatusEntries( ) = default;
        ServiceStatusEntries( const ServiceStatusEntries& other ) = delete;
        ServiceStatusEntries& operator = ( const ServiceStatusEntries& other ) = delete;

        ServiceStatusEntries( ServiceStatusEntries&& other ) noexcept
            : memorySize_( other.memorySize_ ), size_( other.size_ ), data_( other.data_ )
        {
            other.memorySize_ = 0;
            other.size_ = 0;
            other.data_ = nullptr;
        }
        ServiceStatusEntries& operator = ( ServiceStatusEntries&& other ) noexcept
        {
            std::swap( memorySize_, other.memorySize_ );
            std::swap( size_, other.size_ );
            std::swap( data_, other.data_ );
            return *this;
        }
        ~ServiceStatusEntries( )
        {
            if ( data_ )
            {
                free( data_ );
            }
        }

        void Clear( )
        {
            if ( data_ )
            {
                free( data_ );
                data_ = nullptr;
                memorySize_ = 0;
                size_ = 0;
            }
        }
        void clear( )
        {
            Clear( );
        }

        void Resize( size_t memorySize, size_t size )
        {
            if ( memorySize_ != memorySize )
            {
                Clear( );
                data_ = reinterpret_cast< ServiceStatusEntry* >( malloc( memorySize ) );
                memorySize_ = memorySize;
            }
            size_ = size;
        }
        void resize( size_t memorySize, size_t size )
        {
            Resize( memorySize, size );
        }

        [[nodiscard]] constexpr bool empty( ) const noexcept
        {
            return size_ == 0;
        }
        [[nodiscard]] constexpr size_type size( ) const noexcept
        {
            return size_;
        }
        [[nodiscard]] constexpr size_type size_in_bytes( ) const noexcept
        {
            return memorySize_;
        }
        [[nodiscard]] constexpr size_type max_size( ) const noexcept
        {
            return std::numeric_limits<size_type>::max( ) / static_cast< size_type >( sizeof( value_type ) );
        }
        [[nodiscard]] constexpr size_type capacity( ) const noexcept
        {
            return size_;
        }
        [[nodiscard]] constexpr reference operator[]( size_type i ) noexcept
        {
            return data_[ i ];
        }
        [[nodiscard]] constexpr const_reference operator[]( size_type i ) const noexcept
        {
            return data_[ i ];
        }

        [[nodiscard]] constexpr iterator begin( ) noexcept
        {
            return iterator( data_ );
        }
        [[nodiscard]] constexpr const_iterator begin( ) const noexcept
        {
            return const_iterator( const_cast< value_type* >( data_ ) );
        }

        [[nodiscard]] constexpr const_iterator cbegin( ) const noexcept
        {
            return const_iterator( const_cast< value_type* >( data_ ) );
        }

        [[nodiscard]] constexpr iterator end( ) noexcept
        {
            return iterator( data_ + size_ );
        }
        [[nodiscard]] constexpr const_iterator end( ) const noexcept
        {
            return const_iterator( const_cast< value_type* >( data_ + size_ ) );
        }
        [[nodiscard]] constexpr const_iterator cend( ) const noexcept
        {
            return const_iterator( const_cast< value_type* >( data_ + size_ ) );
        }


        [[nodiscard]] constexpr reverse_iterator rbegin( ) noexcept
        {
            return reverse_iterator( end( ) );
        }

        [[nodiscard]] constexpr const_reverse_iterator rbegin( ) const noexcept
        {
            return const_reverse_iterator( end( ) );
        }

        [[nodiscard]] constexpr reverse_iterator rend( ) noexcept
        {
            return reverse_iterator( begin( ) );
        }

        [[nodiscard]] constexpr const_reverse_iterator rend( ) const noexcept
        {
            return const_reverse_iterator( begin( ) );
        }

        [[nodiscard]] constexpr const_reverse_iterator crbegin( ) const noexcept
        {
            return rbegin( );
        }

        [[nodiscard]] constexpr const_reverse_iterator crend( ) const noexcept
        {
            return rend( );
        }


        [[nodiscard]] constexpr pointer data( ) noexcept
        {
            return data_;
        }
        [[nodiscard]] constexpr const_pointer data( ) const noexcept
        {
            return data_;
        }

        [[nodiscard]] constexpr reference front( ) noexcept
        {
            return *data_;
        }
        [[nodiscard]] constexpr const_reference front( ) const noexcept
        {
            return *data_;
        }
        [[nodiscard]] constexpr reference back( ) noexcept
        {
            return *( data_ + (size_ - 1) );
        }
        [[nodiscard]] constexpr const_reference back( ) const noexcept
        {
            return *( data_ + ( size_ - 1 ) );
        }


    };

    class ServiceControlManager;
    class ServiceHandle
    {
        friend class ServiceControlManager;
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

        /// <summary>
        /// Marks the service for deletion from the service control manager database.
        /// </summary>
        void DeleteService( ) const
        {
            auto rc = ::DeleteService( handle_ );
            if ( rc == FALSE )
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_SERVICE_DOES_NOT_EXIST && errorCode != ERROR_SERVICE_MARKED_FOR_DELETE )
                {
                    ThrowOSError( errorCode );
                }
            }
        }

        /// <summary>
        /// Starts the service.
        /// </summary>
        /// <param name="serviceArgumentCount">
        /// The number of strings in the serviceArguments array. If serviceArguments is NULL, this parameter can be zero.
        /// </param>
        /// <param name="serviceArguments">
        /// The null-terminated strings to be passed to the ServiceMain function for the service as arguments. 
        /// If there are no arguments, this parameter can be NULL. Otherwise, the first argument 
        /// (serviceArguments[0]) is the name of the service, followed by any additional arguments 
        /// (serviceArguments[1] through serviceArguments[serviceArgumentCount-1]).
        /// </param>
        void StartService( DWORD serviceArgumentCount = 0, LPCWSTR* serviceArguments = nullptr ) const
        {
            auto rc = ::StartServiceW( handle_, serviceArgumentCount, serviceArguments );
            if ( rc == FALSE )
            {
                ThrowLastOSError( );
            }
        }
    private:
        bool WaitForServiceState( ServiceStatusProcess& serviceStatusProcess, ServiceState currentState, ServiceState stateToWaitFor ) const
        {
            auto startTickCount = GetTickCount64( );
            auto previousCheckPoint = serviceStatusProcess.CheckPoint;

            while ( serviceStatusProcess.CurrentState == currentState )
            {
                auto waitTime = serviceStatusProcess.WaitTime( );
                CurrentThread::Sleep( waitTime );
                if ( QueryServiceStatus( serviceStatusProcess ) == false )
                {
                    return false;
                }
                if ( serviceStatusProcess.CurrentState == currentState )
                {
                    if ( serviceStatusProcess.CheckPoint > previousCheckPoint )
                    {
                        startTickCount = GetTickCount64( );
                        previousCheckPoint = serviceStatusProcess.CheckPoint;
                    }
                    else
                    {
                        if ( ( GetTickCount64( ) - startTickCount ) > static_cast< ULONGLONG >( serviceStatusProcess.WaitHint ) )
                        {
                            // Wait timeout
                            return false;
                        }
                    }
                }
            }
            return serviceStatusProcess.CurrentState == stateToWaitFor;
        }
    public:

        bool Start( DWORD serviceArgumentCount = 0, LPCWSTR* serviceArguments = nullptr ) const
        {
            ServiceStatusProcess serviceStatusProcess{};
            if ( QueryServiceStatus( serviceStatusProcess ) )
            {
                if ( serviceStatusProcess.CurrentState == ServiceState::Stopped || serviceStatusProcess.CurrentState == ServiceState::StopPending )
                {
                    WaitForServiceState( serviceStatusProcess, ServiceState::StopPending, ServiceState::Stopped );
                    
                    if ( serviceStatusProcess.CurrentState == ServiceState::Stopped )
                    {
                        StartService( serviceArgumentCount, serviceArguments );
                        return WaitForServiceState( serviceStatusProcess, ServiceState::StartPending, ServiceState::Running );
                    }
                }
            }
            return false;
        }

        template<typename ServiceStatusT>
            requires std::is_same_v< ServiceStatusT, ServiceStatus > || std::is_same_v< ServiceStatusT, ServiceStatusProcess >
        void ControlService( Services::ServiceControl serviceControl, ServiceStatusT& serviceStatus ) const
        {
            auto rc = ::ControlService( handle_, static_cast< DWORD >( serviceControl ), reinterpret_cast< LPSERVICE_STATUS >( &serviceStatus ) );
            if ( rc == false )
            {
                ThrowLastOSError( );
            }
        }



        ServiceStatusProcess QueryServiceStatus( ) const
        {
            ServiceStatusProcess serviceStatusProcess{};
            DWORD bytesRequired = 0;
            auto rc = QueryServiceStatusEx( handle_, SC_STATUS_PROCESS_INFO, reinterpret_cast<LPBYTE>(&serviceStatusProcess), sizeof( ServiceStatusProcess ), &bytesRequired );
            if ( rc == FALSE )
            {
                ThrowLastOSError( );
            }
            return serviceStatusProcess;
        }

        bool QueryServiceStatus( ServiceStatusProcess& serviceStatusProcess ) const
        {
            DWORD bytesRequired = 0;
            auto rc = QueryServiceStatusEx( handle_, SC_STATUS_PROCESS_INFO, reinterpret_cast< LPBYTE >( &serviceStatusProcess ), sizeof( ServiceStatusProcess ), &bytesRequired );
            if ( rc == FALSE )
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_SERVICE_DOES_NOT_EXIST )
                {
                    ThrowOSError( errorCode );
                }
                return false;
            }
            return true;
        }

        ServiceState CurrentState( ) const
        {
            ServiceStatusProcess serviceStatusProcess{};
            if ( QueryServiceStatus( serviceStatusProcess ) )
            {
                return serviceStatusProcess.CurrentState;
            }
            return ServiceState::Unknown;
        }

        bool IsStopped( ) const
        {
            return CurrentState( ) == ServiceState::Stopped;
        }

        bool IsRunning( ) const
        {
            return CurrentState( ) == ServiceState::Running;
        }

        bool HasActiveDependentServices( ) const
        {
            DWORD bytesNeeded = 0;
            DWORD count = 0;
            auto rc = EnumDependentServicesW( handle_, SERVICE_ACTIVE, nullptr, 0, &bytesNeeded, &count );
            if ( rc == FALSE )
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_MORE_DATA )
                {
                    ThrowOSError( errorCode );
                }
                return true;
            }
            return false;
        }
        ServiceStatusEntries DependentServices( ServiceEnumFlags serviceEnumFlags ) const
        {
            DWORD bytesNeeded = 0;
            DWORD count = 0;
            auto rc = EnumDependentServicesW( handle_, static_cast<DWORD>( serviceEnumFlags ), nullptr, 0, &bytesNeeded, &count );
            if ( rc == FALSE )
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_MORE_DATA )
                {
                    ThrowOSError( errorCode );
                }
                ServiceStatusEntries result;
                result.Resize( bytesNeeded, count );

                auto bufferSize = bytesNeeded;
                rc = EnumDependentServicesW( handle_, static_cast< DWORD >( serviceEnumFlags ), reinterpret_cast< LPENUM_SERVICE_STATUSW >( result.data() ), bufferSize, &bytesNeeded, &count );
                if ( rc == FALSE )
                {
                    ThrowLastOSError( );
                }
                return result;
            }
            return {};
        }
        ServiceStatusEntries ActiveDependentServices( ) const
        {
            return DependentServices( ServiceEnumFlags::Active );
        }


    };
    


    class ServiceControlManager
    {
        SC_HANDLE handle_ = nullptr;
    public:
        static constexpr wchar_t LocalService[ ] = L"NT AUTHORITY\\LocalService";
        static constexpr wchar_t LocalSystem[ ] = L".\\LocalSystem";
        static constexpr wchar_t NetworkService[ ] = L"NT AUTHORITY\\NetworkService";
        static constexpr wchar_t DefaultServiceDependencies[ ] = L"RpcSs\x0";

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

        ServiceHandle OpenService( const wchar_t* serviceName, ServiceAccessRights desiredAccessRights ) const
        {
            auto serviceHandle = ::OpenServiceW( handle_, serviceName, static_cast< DWORD >( desiredAccessRights ) );
            if ( serviceHandle == nullptr )
            {
                ThrowLastOSError( );
            }
            return ServiceHandle{ serviceHandle };
        }

        bool IsServiceRegistered( const wchar_t* serviceName ) const
        {
            auto serviceHandle = ::OpenServiceW( handle_, serviceName, static_cast< DWORD >( ServiceAccessRights::QueryConfig ) );
            if ( serviceHandle )
            {
                CloseServiceHandle( serviceHandle );
                return true;
            }
            else
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_SERVICE_DOES_NOT_EXIST )
                {
                    ThrowOSError( errorCode );
                }
                return false;
            }
        }

        bool QueryServiceStatus( const wchar_t* serviceName, ServiceStatusProcess& serviceStatusProcess ) const
        {
            serviceStatusProcess = {};
            auto serviceHandle = ::OpenServiceW( handle_, serviceName, static_cast< DWORD >( ServiceAccessRights::QueryConfig | ServiceAccessRights::QueryStatus ) );
            if ( serviceHandle )
            {
                ServiceHandle sh( serviceHandle );
                return sh.QueryServiceStatus( serviceStatusProcess );
            }
            else
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_SERVICE_DOES_NOT_EXIST )
                {
                    ThrowOSError( errorCode );
                }
                return false;
            }
        }



        bool IsServiceRunning( const wchar_t* serviceName ) const
        {
            ServiceStatusProcess serviceStatusProcess{};
            if ( QueryServiceStatus( serviceName, serviceStatusProcess ) )
            {
                return serviceStatusProcess.CurrentState == ServiceState::Running;
            }
            return false;
        }

        bool IsServiceStopped( const wchar_t* serviceName ) const
        {
            ServiceStatusProcess serviceStatusProcess{};
            if ( QueryServiceStatus( serviceName, serviceStatusProcess ) )
            {
                return serviceStatusProcess.CurrentState == ServiceState::Stopped;
            }
            return false;
        }


        ServiceHandle CreateService( _In_ LPCWSTR serviceName,
            _In_opt_ LPCWSTR displayName,
            _In_opt_ LPCWSTR binaryPathName,
            _In_opt_ LPCWSTR serviceStartName = NetworkService,
            _In_opt_ LPCWSTR password = nullptr,
            _In_opt_ LPCWSTR dependencies = DefaultServiceDependencies,
            _In_ ServiceAccessRights desiredAccess = ServiceAccessRights::FullControl,
            _In_ ServiceType serviceType = ServiceType::WindowsOwnProcess,
            _In_ ServiceStartType startType = ServiceStartType::AutoStart,
            _In_ ServiceErrorControl errorControl = ServiceErrorControl::Normal,
            _In_opt_ LPCWSTR loadOrderGroup = nullptr,
            _Out_opt_ LPDWORD tagId = nullptr )
        {
            auto serviceHandle = ::CreateServiceW( handle_, serviceName, displayName, static_cast< DWORD >( desiredAccess ), static_cast< DWORD >( serviceType ), static_cast< DWORD >( startType ), static_cast< DWORD >( errorControl ), binaryPathName, loadOrderGroup, tagId, dependencies, serviceStartName, password );
            if ( serviceHandle == nullptr )
            {
                ThrowLastOSError( );
            }
            return ServiceHandle{ serviceHandle };
        }


        bool StopDependentServices( const ServiceHandle& serviceHandle ) const
        {
            auto activeDependentServices = serviceHandle.ActiveDependentServices( );
            if ( activeDependentServices.size( ) )
            {
                for ( auto& entry : activeDependentServices )
                {
                    auto dependentService = OpenService( entry.ServiceName, ServiceAccessRights::Stop | ServiceAccessRights::QueryStatus );
                    ServiceStatusProcess serviceStatusProcess;
                    dependentService.ControlService( ServiceControl::Stop, serviceStatusProcess );
                    if ( dependentService.WaitForServiceState( serviceStatusProcess, ServiceState::StopPending, ServiceState::Stopped ) == false )
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        bool StopService( const ServiceHandle& serviceHandle ) const
        {
            ServiceStatusProcess serviceStatusProcess;
            if ( serviceHandle.QueryServiceStatus( serviceStatusProcess ) )
            {
                if ( serviceStatusProcess.CurrentState == ServiceState::Stopped )
                {
                    return true;
                }
                else if ( serviceStatusProcess.CurrentState == ServiceState::StopPending )
                {
                    return serviceHandle.WaitForServiceState( serviceStatusProcess, ServiceState::StopPending, ServiceState::Stopped );
                }
                else
                {
                    if ( StopDependentServices( serviceHandle ) )
                    {
                        ServiceStatusProcess serviceStatusProcess;
                        serviceHandle.ControlService( ServiceControl::Stop, serviceStatusProcess );
                        return serviceHandle.WaitForServiceState( serviceStatusProcess, ServiceState::StopPending, ServiceState::Stopped );
                    }
                }
            }
            return false;
        }

        bool StopService( const wchar_t* serviceName ) const
        {
            auto serviceHandle = OpenService( serviceName, ServiceAccessRights::Stop | ServiceAccessRights::QueryStatus | ServiceAccessRights::EnumerateDependents );
            return StopService( serviceHandle );
        }

        bool DeleteService( const wchar_t* serviceName ) const
        {
            auto serviceHandle = OpenService( serviceName, ServiceAccessRights::Stop | ServiceAccessRights::QueryStatus | ServiceAccessRights::EnumerateDependents | ServiceAccessRights::Delete );
            if ( serviceHandle.IsStopped( ) == false )
            {
                if ( StopService( serviceHandle ) == false )
                {
                    return false;
                }
            }
            serviceHandle.DeleteService( );
            return true;
        }

        bool StartService( const wchar_t* serviceName, DWORD serviceArgumentCount = 0, LPCWSTR* serviceArguments = nullptr ) const
        {
            auto serviceHandle = OpenService( serviceName, ServiceAccessRights::Start | ServiceAccessRights::QueryStatus );
            return serviceHandle.Start( serviceArgumentCount, serviceArguments );
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
#ifdef USE_REPORTSERVICEMESSAGE
            ReportServiceMessage( "In WindowsServiceHost::StartDispatcher" );
#endif
            return StartServiceCtrlDispatcherW( serviceStartTable ) != FALSE;
        }

        virtual SERVICE_STATUS_HANDLE RegisterHandler( _In_ LPCWSTR serviceName, _In_ __callback LPHANDLER_FUNCTION_EX handlerProc, _In_opt_ LPVOID context ) override
        {
#ifdef USE_REPORTSERVICEMESSAGE
            ReportServiceMessage( "In WindowsServiceHost::RegisterHandler" );
#endif
            auto result = RegisterServiceCtrlHandlerExW( serviceName, handlerProc, context );
#ifdef USE_REPORTSERVICEMESSAGE
            auto message = Format( "SERVICE_STATUS_HANDLE:{:X}", reinterpret_cast<size_t>(result) );
            ReportServiceMessage( message.c_str() );
#endif
            return result;
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
#ifdef USE_REPORTSERVICEMESSAGE
            ServiceState currentState = static_cast< ServiceState >( serviceStatus->dwCurrentState );
            ServiceControlAccepted serviceControlAccepted = static_cast< ServiceControlAccepted >( serviceStatus->dwControlsAccepted );
            auto messageStr = Format( "In ServiceBase::SetStatus - serviceStatusHandle:{:X}, CurrentState:{}, ControlsAccepted:{}, CheckPoint:{}, WaitHint:{}", reinterpret_cast< size_t >( serviceStatusHandle ), currentState, serviceControlAccepted, serviceStatus->dwCheckPoint, serviceStatus->dwWaitHint );
            ReportServiceMessage( messageStr.c_str( ) );
#endif
            auto rc = ::SetServiceStatus( serviceStatusHandle, serviceStatus );
            if ( rc == FALSE )
            {
#ifdef USE_REPORTSERVICEMESSAGE
                auto errorCode = GetLastError( );
                messageStr = FormatErrorA( errorCode );
                ReportServiceMessage( messageStr.c_str( ) );
#endif
                return false;
            }
            return true;
        }
    };





    class Application;
    class ServiceBase : public std::enable_shared_from_this<ServiceBase>
    {
        friend class Services::Application;
        WideString name_;
        WideString displayName_;
        Services::ServiceControlAccepted serviceControlAccepted_;
        Services::ServiceType serviceType_;

        SERVICE_STATUS_HANDLE serviceStatusHandle_ = nullptr;
        SERVICE_STATUS serviceStatus_{};
        EventWaitHandle serviceStoppedEventWaitHandle_{true};
        EventWaitHandle serviceStopCompletedEventWaitHandle_{ true };
        HANDLE waitForSingleObjectHandle_ = nullptr;
        IServiceHost* serviceHost_ = nullptr;
        DWORD argc_ = 0;
        LPWSTR* argv_ = nullptr;
    public:
        ServiceBase( const WideString& name, const WideString& displayName, Services::ServiceControlAccepted serviceControlAccepted = Services::ServiceControlAccepted::Stop, Services::ServiceType serviceType = Services::ServiceType::WindowsOwnProcess );
        
        virtual ~ServiceBase( )
        {
        }

        const WideString& Name( ) const noexcept
        {
            return name_;
        }

        bool RegisterServiceControlHandler( )
        {
            serviceStatusHandle_ = serviceHost_->RegisterHandler( name_.c_str( ), &ServiceHandlerFunctionEx, this );
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

            if ( ( currentState == Services::ServiceState::Running ) ||
                ( currentState == Services::ServiceState::Stopped ) ||
                ( currentState == Services::ServiceState::Paused ) )
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
#ifdef USE_REPORTSERVICEMESSAGE
            ReportServiceMessage( "In ServiceBase::Execute" );
#endif
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
#ifdef USE_REPORTSERVICEMESSAGE
            ReportServiceMessage( "In ServiceBase::Initialize" );
#endif
            SetServiceStatus( Services::ServiceState::StartPending );
            return true;
        }

    private: 
        
        static void __stdcall ServiceDoneCallback( PVOID self, BOOLEAN timerOrWaitFired )
        {
            auto serviceBase = reinterpret_cast< ServiceBase* >( self );
            serviceBase->Done( );
        }
        
    protected:
        
        virtual void Done( )
        {
            try
            {
                ( void )UnregisterWait( waitForSingleObjectHandle_ );
            }
            catch(...)
            { }
            serviceStopCompletedEventWaitHandle_.Signal( );
        }
        
        virtual void Run( )
        {
#ifdef USE_REPORTSERVICEMESSAGE
            ReportServiceMessage( "In ServiceBase::Run" );
#endif

            
            auto rc = RegisterWaitForSingleObject( &waitForSingleObjectHandle_, serviceStoppedEventWaitHandle_.GetHandle( ), ( WAITORTIMERCALLBACK )&ServiceDoneCallback, this, INFINITE, WT_EXECUTEDEFAULT );
            if ( rc == FALSE )
            {
                ThrowLastOSError( );
            }
            
            SetServiceStatus( Services::ServiceState::Running );
        }
        
    protected:
        virtual WinError HandleStop( ) noexcept
        {
            SetServiceStatus( Services::ServiceState::StopPending,0,15000 );
            this->Stop( );
            serviceStopCompletedEventWaitHandle_.Wait( );
            SetServiceStatus( Services::ServiceState::Stopped );
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
#ifdef USE_REPORTSERVICEMESSAGE
            auto messageStr = Format( "In ServiceBase::HandleControl:{}", serviceControl );
            ReportServiceMessage( messageStr.c_str( ) );
#endif
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
#ifdef USE_REPORTSERVICEMESSAGE
            auto serviceControl = static_cast< ServiceControl >( control );
            auto messageStr = Format( "In ServiceBase::ServiceHandlerFunctionEx:{}", serviceControl );
            ReportServiceMessage( messageStr.c_str() );
#endif
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
    /// Derived classes must: 
    ///   1. implement a parameterless constructor.
    ///   2. implement two static functions with the following signatures:
    /// 
    ///         static const wchar_t* ServiceName( );
    ///         static const wchar_t* ServiceDisplayName( );
    /// 
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
            : Base( WideString(DerivedType::ServiceName( )), WideString( DerivedType::ServiceDisplayName()), serviceControlAccepted, serviceType )
        {
        }

        static void __stdcall Main( DWORD argc, LPWSTR* argv );

        static bool IsRegistered( )
        {
            const wchar_t* serviceName = DerivedType::ServiceName( );
            auto scm = ServiceControlManager::Open( ServiceControlManagerAccessRights::Connect | ServiceControlManagerAccessRights::Enumerate );
            return scm.IsServiceRegistered( serviceName );
        }

        static bool IsRunning( )
        {
            const wchar_t* serviceName = DerivedType::ServiceName( );
            auto scm = ServiceControlManager::Open( ServiceControlManagerAccessRights::Connect | ServiceControlManagerAccessRights::Enumerate );
            return scm.IsServiceRunning( serviceName );
        }

        static bool IsStopped( )
        {
            const wchar_t* serviceName = DerivedType::ServiceName( );
            auto scm = ServiceControlManager::Open( ServiceControlManagerAccessRights::Connect | ServiceControlManagerAccessRights::Enumerate );
            return scm.IsServiceRunning( serviceName );
        }

        static bool RegisterService( const wchar_t* account, const wchar_t* password )
        {
            const wchar_t* serviceName = DerivedType::ServiceName( );
            auto scm = ServiceControlManager::Open( ServiceControlManagerAccessRights::FullControl );
            if ( scm.IsServiceRegistered( serviceName ) == false )
            {
                const wchar_t* serviceDisplayName = DerivedType::ServiceDisplayName( );
                auto executable = IO::File::GetExecutableFilename<WideString>( );
                auto executablePtr = executable.c_str( );
                auto serviceHandle = scm.CreateService( serviceName, serviceDisplayName, executablePtr, account, password );
            }
            return true;
        }

        static bool UnregisterService( )
        {
            const wchar_t* serviceName = DerivedType::ServiceName( );
            auto scm = ServiceControlManager::Open( ServiceControlManagerAccessRights::FullControl );
            if ( scm.IsServiceRegistered( serviceName ) )
            {
                scm.DeleteService( serviceName );
            }
            return true;
        }

        static bool StartService( )
        {
            const wchar_t* serviceName = DerivedType::ServiceName( );
            auto scm = ServiceControlManager::Open( ServiceControlManagerAccessRights::FullControl );
            if ( scm.IsServiceRegistered( serviceName ) )
            {
                return scm.StartService( serviceName );
            }
            return false;
        }

        static bool StopService( )
        {
            const wchar_t* serviceName = DerivedType::ServiceName( );
            auto scm = ServiceControlManager::Open( ServiceControlManagerAccessRights::FullControl );
            if ( scm.IsServiceRegistered( serviceName ) )
            {
                return scm.StopService( serviceName );
            }
            return false;
        }

    };

    class Application : public Core::Application
    {
        IServiceHost* serviceHost_ = nullptr;
        size_t registeredServiceCount_ = 0;
        std::vector<SERVICE_TABLE_ENTRYW> serviceEntries_;
        std::vector<std::shared_ptr<ServiceBase>> services_;
    public:
        using Base = Core::Application;

        HCC_EXPORT Application( const std::shared_ptr<ApplicationOptions>& options, IServiceHost* serviceHost );
        HCC_EXPORT ~Application( );

        static Services::Application& Instance( ) noexcept
        {
            return static_cast< Services::Application& >( Base::Instance( ) );
        }

        IServiceHost* ServiceHost( ) const
        {
            return serviceHost_;
        }

        void RegisterService( const std::shared_ptr<ServiceBase>& serviceBase )
        {
            services_.emplace_back( serviceBase );
        }

        void Stop( )
        {
            for ( auto& service : services_ )
            {
                service->serviceStopCompletedEventWaitHandle_.Wait( );
            }
            services_.clear( );
            Base::Stop( );
        }


        template<typename ServiceT>
        void RegisterServiceType( )
        {
            registeredServiceCount_++;
            SERVICE_TABLE_ENTRYW& entry = serviceEntries_.emplace_back();
            entry.lpServiceName = const_cast<wchar_t*>(ServiceT::ServiceName( ));
            entry.lpServiceProc = &ServiceT::Main;
        }

        void Run( )
        {
#ifdef USE_REPORTSERVICEMESSAGE
            ReportServiceMessage( "In Application::Run" );
#endif
            // Add final empty entry, which marks the end of the SERVICE_TABLE_ENTRYW array.
            SERVICE_TABLE_ENTRYW& entry = serviceEntries_.emplace_back( );
            entry.lpServiceName = nullptr;
            entry.lpServiceProc = nullptr;
            serviceHost_->StartDispatcher( serviceEntries_.data() );
#ifdef USE_REPORTSERVICEMESSAGE
            ReportServiceMessage( "Leaving Application::Run" );
#endif
        }
    };

    inline ServiceBase::ServiceBase( const WideString& name, const WideString& displayName, Services::ServiceControlAccepted serviceControlAccepted, Services::ServiceType serviceType )
        : name_( name ), displayName_( displayName ), serviceControlAccepted_( serviceControlAccepted ), serviceType_( serviceType ), serviceStoppedEventWaitHandle_( true ), serviceHost_( Application::Instance( ).ServiceHost( ) )
    {
        serviceStatus_.dwServiceType = static_cast< DWORD >( serviceType );
    }

    template<typename DerivedT>
    inline void __stdcall Service<DerivedT>::Main( DWORD argc, LPWSTR* argv )
    {
#ifdef USE_REPORTSERVICEMESSAGE
        ReportServiceMessage( "In Service::Main" );
#endif
        Com::Initialize( );
        auto service = std::make_shared<DerivedType>( );
        Services::Application::Instance( ).RegisterService( service );
        if ( service->RegisterServiceControlHandler( ) )
        {
            service->Execute( argc, argv );
        }
        Com::Uninitialize( );
#ifdef USE_REPORTSERVICEMESSAGE
        ReportServiceMessage( "Leaving Service::Main" );
#endif
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

    // =========================================================================
    // HardwareProfileChangeEventType
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Services::HardwareProfileChangeEventType value );
    HCC_EXPORT WideString ToWideString( Services::HardwareProfileChangeEventType value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Services::HardwareProfileChangeEventType value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Services::HardwareProfileChangeEventType value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Services
    {
        HCC_EXPORT Services::HardwareProfileChangeEventType ParseHardwareProfileChangeEventType( const WideString& str );
        HCC_EXPORT Services::HardwareProfileChangeEventType ParseHardwareProfileChangeEventType( const WideString& str, Services::HardwareProfileChangeEventType defaultResult );
        HCC_EXPORT bool TryParseHardwareProfileChangeEventType( const WideString& str, Services::HardwareProfileChangeEventType& value );

        inline Services::HardwareProfileChangeEventType ParseHardwareProfileChangeEventType( const AnsiString& str )
        {
            return ParseHardwareProfileChangeEventType( ToWideString( str ) );
        }
        inline Services::HardwareProfileChangeEventType ParseHardwareProfileChangeEventType( const AnsiString& str, Services::HardwareProfileChangeEventType defaultResult )
        {
            return ParseHardwareProfileChangeEventType( ToWideString( str ), defaultResult );
        }
        inline bool TryParseHardwareProfileChangeEventType( const AnsiString& str, Services::HardwareProfileChangeEventType& value )
        {
            return TryParseHardwareProfileChangeEventType( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Services::HardwareProfileChangeEventType& value )
    {
        return Services::TryParseHardwareProfileChangeEventType( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Services::HardwareProfileChangeEventType, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Services::ParseHardwareProfileChangeEventType( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Services::HardwareProfileChangeEventType, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Services::ParseHardwareProfileChangeEventType( str );
    }

    // =========================================================================
    // PowerEventType
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Services::PowerEventType value );
    HCC_EXPORT WideString ToWideString( Services::PowerEventType value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Services::PowerEventType value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Services::PowerEventType value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Services
    {
        HCC_EXPORT Services::PowerEventType ParsePowerEventType( const WideString& str );
        HCC_EXPORT Services::PowerEventType ParsePowerEventType( const WideString& str, Services::PowerEventType defaultResult );
        HCC_EXPORT bool TryParsePowerEventType( const WideString& str, Services::PowerEventType& value );

        inline Services::PowerEventType ParsePowerEventType( const AnsiString& str )
        {
            return ParsePowerEventType( ToWideString( str ) );
        }
        inline Services::PowerEventType ParsePowerEventType( const AnsiString& str, Services::PowerEventType defaultResult )
        {
            return ParsePowerEventType( ToWideString( str ), defaultResult );
        }
        inline bool TryParsePowerEventType( const AnsiString& str, Services::PowerEventType& value )
        {
            return TryParsePowerEventType( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Services::PowerEventType& value )
    {
        return Services::TryParsePowerEventType( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Services::PowerEventType, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Services::ParsePowerEventType( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Services::PowerEventType, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Services::ParsePowerEventType( str );
    }

    namespace Internal
    {
        // =========================================================================
        // ServicesFormatterImpl
        // =========================================================================
        template<typename EnumT, typename CharT>
        struct ServicesFormatterImpl
        {
            std::formatter<std::basic_string_view<CharT>, CharT> viewFormatter;
            constexpr auto parse( std::basic_format_parse_context<CharT>& ctx )
            {
                return viewFormatter.parse( ctx );
            }

            template <typename FormatContext>
            auto format( EnumT value, FormatContext& ctx ) const
            {
                if constexpr ( sizeof( CharT ) == 2 )
                {
                    auto str = ToWideString( value );
                    std::basic_string_view<CharT> view( str.data( ), str.size( ) );
                    return viewFormatter.format( view, ctx );
                }
                else
                {
                    auto str = ToAnsiString( value );
                    std::basic_string_view<CharT> view( str.data( ), str.size( ) );
                    return viewFormatter.format( view, ctx );
                }
            }
        };
    }
}

namespace std
{
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Services::ServiceAccessRights, CharT> : public Harlinn::Common::Core::Internal::ServicesFormatterImpl<Harlinn::Common::Core::Services::ServiceAccessRights, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Services::ServiceControlManagerAccessRights, CharT> : public Harlinn::Common::Core::Internal::ServicesFormatterImpl<Harlinn::Common::Core::Services::ServiceControlManagerAccessRights, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Services::ServiceType, CharT> : public Harlinn::Common::Core::Internal::ServicesFormatterImpl<Harlinn::Common::Core::Services::ServiceType, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Services::ServiceStartType, CharT> : public Harlinn::Common::Core::Internal::ServicesFormatterImpl<Harlinn::Common::Core::Services::ServiceStartType, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Services::ServiceEnumerationState, CharT> : public Harlinn::Common::Core::Internal::ServicesFormatterImpl<Harlinn::Common::Core::Services::ServiceEnumerationState, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Services::ServiceState, CharT> : public Harlinn::Common::Core::Internal::ServicesFormatterImpl<Harlinn::Common::Core::Services::ServiceState, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Services::ServiceControl, CharT> : public Harlinn::Common::Core::Internal::ServicesFormatterImpl<Harlinn::Common::Core::Services::ServiceControl, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Services::ServiceControlAccepted, CharT> : public Harlinn::Common::Core::Internal::ServicesFormatterImpl<Harlinn::Common::Core::Services::ServiceControlAccepted, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Services::DeviceEventType, CharT> : public Harlinn::Common::Core::Internal::ServicesFormatterImpl<Harlinn::Common::Core::Services::DeviceEventType, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Services::HardwareProfileChangeEventType, CharT> : public Harlinn::Common::Core::Internal::ServicesFormatterImpl<Harlinn::Common::Core::Services::HardwareProfileChangeEventType, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Services::PowerEventType, CharT> : public Harlinn::Common::Core::Internal::ServicesFormatterImpl<Harlinn::Common::Core::Services::PowerEventType, CharT>
    {
    };

}


#endif
