#include "pch.h"
#include <HCCLoggerBackendDataTypes.h>
#include <HCCEnvironment.h>

namespace Harlinn::Common::Core::Logging
{

    HCC_EXPORT BackendComputerInfo GetBackendComputerInfo( )
    {
        Guid machineGuid = Environment::MachineGuid( );
        WideString domainName = Environment::DomainName( );
        WideString computerName = Environment::ComputerName( Environment::ComputerNameFormat::NetBIOS );
        BackendComputerInfo result( machineGuid, domainName, computerName );
        return result;
    }
    HCC_EXPORT BackendUserInfo GetBackendUserInfo( )
    {
        Guid userId;
        if ( Environment::IsComputerDomainJoined( ) )
        {
            auto uniqueId = Environment::UserName( Environment::UserNameFormat::UniqueId );
            userId = Guid( uniqueId );
        }
        WideString domainName = Environment::DomainName( );
        WideString userName = Environment::UserName( Environment::UserNameFormat::SamCompatible );
        BackendUserInfo result( userId, domainName, userName );
        return result;
    }

    HCC_EXPORT BackendExecutableInfo GetBackendExecutableInfo( )
    {
        wchar_t buffer[512];

        auto rc = GetModuleFileNameW( nullptr, buffer, sizeof( buffer ) / sizeof( wchar_t ) );
        if ( !rc )
        {
            ThrowLastOSError( );
        }

        BackendExecutableInfo result( Guid( ), WideString( buffer, static_cast<size_t>(rc) ) );
        return result;
    }


    // ------------------------------------------------------------------------
    //  BackendProcessInfo
    // ------------------------------------------------------------------------
    BackendProcessInfo BackendProcessInfo::Create( )
    {
        /*
        Guid id = Guid::NewGuid( );
        DateTime startTime = DateTime::UtcNow( );
        UInt32 processId = GetCurrentProcessId( );
        WideString computerName = Environment::ComputerName( Environment::ComputerNameFormat::NetBIOS );
        WideString userName = Environment::UserName( Environment::UserNameFormat::SamCompatible );
        */
        return BackendProcessInfo( );
    }

}