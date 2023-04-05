#pragma once
#ifndef __HOCIINTERNAL_H__
#define __HOCIINTERNAL_H__

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
        inline T ByteSize( const std::wstring& str ) noexcept
        {
            return static_cast<T>( str.length( ) * sizeof( wchar_t ) );
        }
        inline OraText* TextOf( std::wstring& str )
        {
            return (OraText*)str.data( );
        }
        inline const OraText* TextOf( const std::wstring& str )
        {
            return (OraText*)str.data( );
        }
    }
}

#endif
