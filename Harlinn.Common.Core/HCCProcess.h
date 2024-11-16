#pragma once
#ifndef __HCCPROCESS_H__
#define __HCCPROCESS_H__
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

#include <HCCDef.h>
#include <HCCException.h>
#include <HCCThread.h>


namespace Harlinn::Common::Core
{
    enum class ProcessAccessRights : DWORD
    {
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,
        
        Terminate = PROCESS_TERMINATE,
        CreateThread = PROCESS_CREATE_THREAD,
        WriteSessionId = PROCESS_SET_SESSIONID,
        AccessMemory = PROCESS_VM_OPERATION,
        ReadMemory = PROCESS_VM_READ,
        WriteMemory = PROCESS_VM_WRITE,
        DuplicateHandle = PROCESS_DUP_HANDLE,
        ExecuteProcess = PROCESS_CREATE_PROCESS,
        WriteQuota = PROCESS_SET_QUOTA,
        WriteInformation = PROCESS_SET_INFORMATION,
        ReadInformation = PROCESS_QUERY_INFORMATION,
        SuspenAndResume = PROCESS_SUSPEND_RESUME,
        ReadLimitedInformation = PROCESS_QUERY_LIMITED_INFORMATION,
        WriteLimitedInformation = PROCESS_SET_LIMITED_INFORMATION,
        FullControl = PROCESS_ALL_ACCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ProcessAccessRights, DWORD );

    class ProcessAccessMask : public Security::AccessMaskT<ProcessAccessMask, ProcessAccessRights>
    {
    public:
        using Base = Security::AccessMaskT<ProcessAccessMask, ProcessAccessRights>;
        static constexpr const Security::GenericMapping Mapping{
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( ProcessAccessRights::FullControl ) ) };

        constexpr ProcessAccessMask( ) noexcept
        {
        }
        constexpr explicit ProcessAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        constexpr explicit ProcessAccessMask( ProcessAccessRights rights ) noexcept
            : Base( rights )
        {
        }

        explicit ProcessAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit ProcessAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        explicit ProcessAccessMask( const ProcessAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }
        explicit ProcessAccessMask( const ProcessAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        explicit ProcessAccessMask( ProcessAccessRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
        explicit ProcessAccessMask( ProcessAccessRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }


        constexpr bool CanTerminate( ) const noexcept
        {
            return Check<ProcessAccessRights::Terminate>( );
        }
        constexpr void SetTerminate( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::Terminate>( value );
        }

        constexpr bool CanCreateThread( ) const noexcept
        {
            return Check<ProcessAccessRights::CreateThread>( );
        }
        constexpr void SetCreateThread( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::CreateThread>( value );
        }

        constexpr bool CanWriteSessionId( ) const noexcept
        {
            return Check<ProcessAccessRights::WriteSessionId>( );
        }
        constexpr void SetWriteSessionId( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::WriteSessionId>( value );
        }

        constexpr bool CanAccessMemory( ) const noexcept
        {
            return Check<ProcessAccessRights::AccessMemory>( );
        }
        constexpr void SetAccessMemory( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::AccessMemory>( value );
        }

        constexpr bool CanReadMemory( ) const noexcept
        {
            return Check<ProcessAccessRights::ReadMemory>( );
        }
        constexpr void SetReadMemory( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::ReadMemory>( value );
        }

        constexpr bool CanWriteMemory( ) const noexcept
        {
            return Check<ProcessAccessRights::WriteMemory>( );
        }
        constexpr void SetWriteMemory( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::WriteMemory>( value );
        }

        constexpr bool CanDuplicateHandle( ) const noexcept
        {
            return Check<ProcessAccessRights::DuplicateHandle>( );
        }
        constexpr void SetDuplicateHandle( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::DuplicateHandle>( value );
        }

        constexpr bool CanExecuteProcess( ) const noexcept
        {
            return Check<ProcessAccessRights::ExecuteProcess>( );
        }
        constexpr void SetExecuteProcess( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::ExecuteProcess>( value );
        }

        constexpr bool CanWriteQuota( ) const noexcept
        {
            return Check<ProcessAccessRights::WriteQuota>( );
        }
        constexpr void SetWriteQuota( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::WriteQuota>( value );
        }

        constexpr bool CanWriteInformation( ) const noexcept
        {
            return Check<ProcessAccessRights::WriteInformation>( );
        }
        constexpr void SetWriteInformation( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::WriteInformation>( value );
        }

        constexpr bool CanReadInformation( ) const noexcept
        {
            return Check<ProcessAccessRights::ReadInformation>( );
        }
        constexpr void SetReadInformation( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::ReadInformation>( value );
        }

        constexpr bool CanSuspenAndResume( ) const noexcept
        {
            return Check<ProcessAccessRights::SuspenAndResume>( );
        }
        constexpr void SetSuspenAndResume( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::SuspenAndResume>( value );
        }

        constexpr bool CanReadLimitedInformation( ) const noexcept
        {
            return Check<ProcessAccessRights::ReadLimitedInformation>( );
        }
        constexpr void SetReadLimitedInformation( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::ReadLimitedInformation>( value );
        }

        constexpr bool CanWriteLimitedInformation( ) const noexcept
        {
            return Check<ProcessAccessRights::WriteLimitedInformation>( );
        }
        constexpr void SetWriteLimitedInformation( bool value = true ) noexcept
        {
            SetBitFlag<ProcessAccessRights::WriteLimitedInformation>( value );
        }
    };




    enum class ProcessCreationFlags : DWORD
    {
        None = 0,
        Debug = DEBUG_PROCESS,
        DebugOnlyThis = DEBUG_ONLY_THIS_PROCESS,
        Suspended = CREATE_SUSPENDED,
        Detached = DETACHED_PROCESS,
        CreateNewConsole = CREATE_NEW_CONSOLE,
        NormalPriority = NORMAL_PRIORITY_CLASS,
        IdlePriority = IDLE_PRIORITY_CLASS,
        HighPriority = HIGH_PRIORITY_CLASS,
        RealTimePriority = REALTIME_PRIORITY_CLASS,
        CreateNewProcessGroup = CREATE_NEW_PROCESS_GROUP,
        CreateUnicodeEnvironment = CREATE_UNICODE_ENVIRONMENT,
        CreateSeparateWowVdm = CREATE_SEPARATE_WOW_VDM,
        CreateSharedWowVdm = CREATE_SHARED_WOW_VDM,
        CreateForceDos =  CREATE_FORCEDOS,
        BelowNormalPriority = BELOW_NORMAL_PRIORITY_CLASS,
        AboveNormalPriority = ABOVE_NORMAL_PRIORITY_CLASS,
        InheritParentAffinity = INHERIT_PARENT_AFFINITY,
        InheritCallerPriority = INHERIT_CALLER_PRIORITY,
        CreateProtectedProcess = CREATE_PROTECTED_PROCESS,
        ExtendedStartupInfoPresent = EXTENDED_STARTUPINFO_PRESENT,
        ProcessModeBackgroundBegin = PROCESS_MODE_BACKGROUND_BEGIN,
        ProcessModeBackgroundEnd = PROCESS_MODE_BACKGROUND_END,
        CreateSecureProcess = CREATE_SECURE_PROCESS,
        CreateBreakawayFromJob = CREATE_BREAKAWAY_FROM_JOB,
        CreatePreserveCodeAuthzLevel = CREATE_PRESERVE_CODE_AUTHZ_LEVEL,
        CreateDefaultErrorMode = CREATE_DEFAULT_ERROR_MODE,
        CreateNoWindow = CREATE_NO_WINDOW,
        ProfileUser = PROFILE_USER,
        ProfileKernel = PROFILE_KERNEL,
        ProfileServer = PROFILE_SERVER,
        CreateIgnoreSystemDefault = CREATE_IGNORE_SYSTEM_DEFAULT
    };


    class StartupInfo : public STARTUPINFOW
    {
    public:
        using Base = STARTUPINFOW;
        StartupInfo()
            : Base{sizeof(Base),0,}
        {
            
        }

    };

    class ProcessOptions
    {
        WideString applicationName_;
        WideString commandLine_;
        SECURITY_ATTRIBUTES* processAttributes_;
        SECURITY_ATTRIBUTES* threadAttributes_;
        bool inheritHandles_;
        ProcessCreationFlags creationFlags_;
        WideString environment_;
        WideString currentDirectory_;
        Core::StartupInfo startupInfo_;
    public:
        ProcessOptions()
            : processAttributes_(nullptr), threadAttributes_(nullptr), inheritHandles_(false), creationFlags_( ProcessCreationFlags::None )
        { }

        ProcessOptions( const WideString& applicationName, const WideString& commandLine, ProcessCreationFlags creationFlags = ProcessCreationFlags::ProfileUser )
            :applicationName_( applicationName ), commandLine_( commandLine ), processAttributes_( nullptr ), threadAttributes_( nullptr ), inheritHandles_( false ), creationFlags_( creationFlags )
        {
        }

        ProcessOptions( const wchar_t* applicationName, const wchar_t* commandLine, ProcessCreationFlags creationFlags = ProcessCreationFlags::ProfileUser )
            :applicationName_( applicationName ), commandLine_( commandLine ), processAttributes_( nullptr ), threadAttributes_( nullptr ), inheritHandles_( false ), creationFlags_( creationFlags )
        { }

        const WideString& ApplicationName( ) const noexcept
        {
            return applicationName_;
        }
        void SetApplicationName( const WideString& applicationName )
        {
            applicationName_ = applicationName;
        }

        const WideString& CommandLine( ) const noexcept
        {
            return commandLine_;
        }
        void SetCommandLine( const WideString& commandLine )
        {
            commandLine_ = commandLine;
        }

        SECURITY_ATTRIBUTES* ProcessAttributes( ) const noexcept
        {
            return processAttributes_;
        }
        void SetProcessAttributes( SECURITY_ATTRIBUTES* processAttributes )
        {
            processAttributes_ = processAttributes;
        }

        SECURITY_ATTRIBUTES* ThreadAttributes( ) const noexcept
        {
            return threadAttributes_;
        }
        void SetThreadAttributes( SECURITY_ATTRIBUTES* threadAttributes )
        {
            threadAttributes_ = threadAttributes;
        }


        bool InheritHandles( ) const noexcept
        {
            return inheritHandles_;
        }
        void SetInheritHandles( bool inheritHandles )
        {
            inheritHandles_ = inheritHandles;
        }

        ProcessCreationFlags CreationFlags( ) const noexcept
        {
            return creationFlags_;
        }
        void SetCreationFlags( ProcessCreationFlags creationFlags )
        {
            creationFlags_ = creationFlags;
        }

        const WideString& Environment( ) const noexcept
        {
            return environment_;
        }
        void SetEnvironment( const WideString& environment )
        {
            environment_ = environment;
        }

        const WideString& CurrentDirectory( )  const noexcept
        {
            return currentDirectory_;
        }
        void SetCurrentDirectory( const WideString& currentDirectory )
        {
            currentDirectory_ = currentDirectory;
        }

        const Core::StartupInfo& StartupInfo( ) const noexcept
        {
            return startupInfo_;
        }
        void SetStartupInfo( const Core::StartupInfo& startupInfo )
        {
            startupInfo_ = startupInfo;
        }
    };


    enum class ProcessPriorityClass
    {
        Normal = NORMAL_PRIORITY_CLASS,
        Idle = IDLE_PRIORITY_CLASS,
        High = HIGH_PRIORITY_CLASS,
        Realtime = REALTIME_PRIORITY_CLASS,
        BelowNormal = BELOW_NORMAL_PRIORITY_CLASS,
        AboveNormal = ABOVE_NORMAL_PRIORITY_CLASS
    };


    namespace CurrentProcess
    {
        inline UInt32 Id( )
        {
            return GetCurrentProcessId( );
        }
        inline HANDLE Handle( )
        {
            return GetCurrentProcess( );
        }

        inline Security::Token OpenToken( Security::TokenAccessMask desiredAccess )
        {
            HANDLE processTokenHandle = 0;
            HANDLE currentProcessHandle = Handle( );
            auto rc = OpenProcessToken( currentProcessHandle, desiredAccess.Value( ), &processTokenHandle );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return Security::Token( processTokenHandle );
        }

        inline Security::Token OpenToken( Security::TokenAccessRights desiredAccess )
        {
            Security::TokenAccessMask mask( desiredAccess );
            return OpenToken( mask );
        }

        inline ProcessPriorityClass PriorityClass( )
        {
            auto rc = GetPriorityClass( Handle( ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return static_cast<ProcessPriorityClass>( rc );
        }

        inline WideString ExecutableFilename( )
        {
            wchar_t buffer[4096];
            auto rc = GetModuleFileNameW( 0, buffer, sizeof( buffer ) / sizeof( wchar_t ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return WideString( buffer, static_cast<size_t>(rc) );
        }

        inline DateTime CreationTime( )
        {
            Int64 creationTime = 0;
            Int64 exitTime = 0;
            Int64 kernelTime = 0;
            Int64 userTime = 0;
            auto rc = GetProcessTimes( GetCurrentProcess( ), reinterpret_cast< FILETIME* >( &creationTime ), reinterpret_cast< FILETIME* >( &exitTime ), reinterpret_cast< FILETIME* >( &kernelTime ), reinterpret_cast< FILETIME* >( &userTime ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return DateTime( creationTime + DateTime::FileTimeOffset );
        }


    }


    class Process : public WaitableHandle
    {
        DWORD processId_;
        Core::Thread primaryThread_;
    public:
        using Base = WaitableHandle;
        constexpr Process( )
            : processId_( 0 )
        { }

        explicit HCC_EXPORT Process( const ProcessOptions& options );

        Process( Process&& other )
            : Base(std::move( other )), processId_( other.processId_ )
        {
            primaryThread_ = std::move( other.primaryThread_ );
            other.processId_ = 0;
        }


        Process& operator = ( Process&& other )
        {
            if ( this != &other )
            {
                Base::operator = ( std::move( other ) );
                std::swap( primaryThread_, other.primaryThread_ );
                std::swap( processId_, other.processId_ );
            }
            return *this;
        }

        const Core::Thread& PrimaryThread( ) const
        {
            return primaryThread_;
        }

        DWORD ProcessId( ) const
        {
            return processId_;
        }



        DWORD ExitCode( ) const
        {
            DWORD result = 0;
            auto rc = GetExitCodeProcess( GetHandle( ), &result );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        ProcessPriorityClass PriorityClass( ) const
        {
            auto rc = GetPriorityClass( GetHandle( ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return static_cast<ProcessPriorityClass>( rc );
        }


    };
}

#endif
