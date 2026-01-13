#pragma once
#ifndef __HOCIINTERNAL_H__
#define __HOCIINTERNAL_H__
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

#include <HOCI.h>
#include <oci.h>

namespace Harlinn::OCI
{
    namespace
    {
        inline Int32 ThrowOracleExceptionOnError( void* errorHandle, Int32 rc, OCI::HandleType handleType = OCI::HandleType::Environment )
        {
            if ( rc < OCI_SUCCESS )
            {
                Int32 error = 0;
                wchar_t messageBuffer[OCI_ERROR_MAXMSG_SIZE2];
                auto rc2 = OCIErrorGet( errorHandle, 1, 
                    nullptr, &error, (OraText*)messageBuffer, OCI_ERROR_MAXMSG_SIZE2 * sizeof( wchar_t ), static_cast<UInt32>( handleType ) );
                if ( rc2 == OCI_SUCCESS )
                {
                    HCC_THROW( Data::OracleClient::OracleException, error, messageBuffer );
                }
                else
                {
                    HCC_THROW( Data::OracleClient::OracleException, error, HCC_TEXT( "Unknown Oracle RDBMS error" ) );
                }

            }
            return rc;
        }

        inline __declspec( noreturn ) void ThrowInvalidEnvironment( )
        {
            HCC_THROW( Data::OracleClient::OracleException, L"Invalid Environment" );
        }

        inline __declspec( noreturn ) void ThrowInvalidServer( )
        {
            HCC_THROW( Data::OracleClient::OracleException, L"Invalid Server" );
        }

        inline __declspec( noreturn ) void ThrowInvalidSession( )
        {
            HCC_THROW( Data::OracleClient::OracleException, L"Invalid Session" );
        }

        template<typename T>
        inline T ByteSize( const WideString& str ) noexcept
        {
            return static_cast<T>( str.length( ) * sizeof( wchar_t ) );
        }
        inline OraText* TextOf( WideString& str )
        {
            return (OraText*)str.data( );
        }
        inline const OraText* TextOf( const WideString& str )
        {
            return (OraText*)str.data( );
        }
    }
}

#endif
