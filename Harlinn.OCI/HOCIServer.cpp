#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{

    void Server::Attach( const std::wstring& databaseLink, ServerAttachMode attachMode ) const
    {
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        if ( databaseLink.empty( ) )
        {
            auto rc = OCIServerAttach( (OCIServer*)Handle( ), errorHandle, ( OraText* )nullptr, 0, (UInt32)attachMode );
            error.CheckResult( rc );
        }
        else
        {
            auto rc = OCIServerAttach( (OCIServer*)Handle( ), errorHandle, (OraText*)databaseLink.c_str( ), static_cast<sb4>( databaseLink.length( ) * sizeof( wchar_t ) ), (UInt32)attachMode );
            error.CheckResult( rc );
        }
    }

    void Server::Detach( ) const
    {
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIServerDetach( (OCIServer*)Handle( ), errorHandle, OCI_DEFAULT );
        error.CheckResult( rc );
    }

    ServiceContext Server::CreateServiceContext( ) const
    {
        auto& environment = Environment( );
        if ( environment.IsValid( ) )
        {
            auto result = environment.CreateServiceContext( );
            result.SetServer( this );
            return result;
        }
        else
        {
            ThrowInvalidEnvironment( );
        }
    }
    ServiceContext Server::CreateServiceContext( const std::wstring& username, const std::wstring& password, const std::wstring& databaseLink, ServerAttachMode attachMode ) const
    {
        Attach( databaseLink, attachMode );
        auto result = CreateServiceContext( );
        result.CreateSession( username, password );
        return result;
    }

}