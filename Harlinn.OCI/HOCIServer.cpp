/*
   Copyright 2024-2025 Espen Harlinn

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
#include <HOCIInternal.h>

namespace Harlinn::OCI
{

    void Server::Attach( const wchar_t* databaseLink, size_t databaseLinkLength, ServerAttachMode attachMode ) const
    {
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        if ( databaseLinkLength == 0 )
        {
            auto rc = OCIServerAttach( (OCIServer*)Handle( ), errorHandle, ( OraText* )nullptr, 0, (UInt32)attachMode );
            error.CheckResult( rc );
        }
        else
        {
            auto rc = OCIServerAttach( (OCIServer*)Handle( ), errorHandle, (OraText*)databaseLink, static_cast<sb4>( databaseLinkLength * sizeof( wchar_t ) ), (UInt32)attachMode );
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
    ServiceContext Server::CreateServiceContext( const wchar_t* username, size_t usernameLength, const wchar_t* password, size_t passwordLength, const wchar_t* databaseLink, size_t databaseLinkLength, ServerAttachMode attachMode ) const
    {
        Attach( databaseLink, databaseLinkLength, attachMode );
        auto result = CreateServiceContext( );
        result.CreateSession( username, usernameLength, password, passwordLength );
        return result;
    }

}