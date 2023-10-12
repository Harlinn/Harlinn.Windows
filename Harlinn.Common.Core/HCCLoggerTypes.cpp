#include "pch.h"
#include <HCCLoggerTypes.h>
#include <HCCEnvironment.h>

namespace Harlinn::Common::Core::Logging::Types
{

    HCC_EXPORT ComputerInfo GetComputerInfo( )
    {
        Guid machineGuid = Environment::MachineGuid( );
        WideString domainName = Environment::DomainName( );
        WideString computerName = Environment::ComputerName( Environment::ComputerNameFormat::NetBIOS );
        ComputerInfo result( machineGuid, domainName, computerName );
        return result;
    }
    HCC_EXPORT UserInfo GetUserInfo( )
    {
        Guid userId;
        if ( Environment::IsComputerDomainJoined( ) )
        {
            auto uniqueId = Environment::UserName( Environment::UserNameFormat::UniqueId );
            userId = Guid( uniqueId );
        }
        WideString domainName = Environment::DomainName( );
        WideString userName = Environment::UserName( Environment::UserNameFormat::SamCompatible );
        UserInfo result( userId, domainName, userName );
        return result;
    }

    HCC_EXPORT ExecutableInfo GetExecutableInfo( )
    {
        wchar_t buffer[512];

        auto rc = GetModuleFileNameW( nullptr, buffer, sizeof( buffer ) / sizeof( wchar_t ) );
        if ( !rc )
        {
            ThrowLastOSError( );
        }

        ExecutableInfo result( Guid( ), WideString( buffer, static_cast<size_t>(rc) ) );
        return result;
    }


    // ------------------------------------------------------------------------
    //  ProcessInfo
    // ------------------------------------------------------------------------
    ProcessInfo ProcessInfo::Create( )
    {
        /*
        Guid id = Guid::NewGuid( );
        DateTime startTime = DateTime::UtcNow( );
        UInt32 processId = GetCurrentProcessId( );
        WideString computerName = Environment::ComputerName( Environment::ComputerNameFormat::NetBIOS );
        WideString userName = Environment::UserName( Environment::UserNameFormat::SamCompatible );
        */
        return ProcessInfo( );
    }

}