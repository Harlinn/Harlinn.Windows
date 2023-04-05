#include "pch.h"
#include <HCCLoggerBackendDataTypes.h>
#include <HCCEnvironment.h>

namespace Harlinn::Common::Core::Logging
{

    HCC_EXPORT BackendComputerInfo GetBackendComputerInfo( )
    {
        Guid machineGuid = Environment::MachineGuid( );
        std::wstring domainName = Environment::DomainName( );
        std::wstring computerName = Environment::ComputerName( Environment::ComputerNameFormat::NetBIOS );
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
        std::wstring domainName = Environment::DomainName( );
        std::wstring userName = Environment::UserName( Environment::UserNameFormat::SamCompatible );
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

        BackendExecutableInfo result( Guid( ), std::wstring( buffer, static_cast<size_t>(rc) ) );
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
        std::wstring computerName = Environment::ComputerName( Environment::ComputerNameFormat::NetBIOS );
        std::wstring userName = Environment::UserName( Environment::UserNameFormat::SamCompatible );
        */
        return BackendProcessInfo( );
    }

}