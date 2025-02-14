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
    bool ServiceContext::SetSession( OCI::Session&& session )
    {
        auto& currentSession = Session( );
        if ( currentSession.Handle( ) != session.Handle( ) )
        {
            auto& environment = Environment( );
            if ( environment )
            {
                auto& error = Error( );
                auto errorHandle = (OCIError*)error.Handle( );
                auto rc = OCIAttrSet( (dvoid*)Handle( ), static_cast<UInt32>( OCIHandleType ),
                    (dvoid*)session.Handle( ), (UInt32)0,
                    static_cast<UInt32>( Attribute::SESSION ), errorHandle );
                error.CheckResult( rc );
                session_ = std::move( session );
            }
            else
            {
                ThrowInvalidEnvironment( );
            }
            return true;
        }
        return false;
    }

    void ServiceContext::ObjectNew( TypeCode typecode, Duration duration, bool value, void** instance ) const
    {
        auto& environment = Environment( );
        if ( environment.IsValid( ) )
        {
            auto& error = Error( );
            auto errorHandle = (OCIError*)error.Handle( );
            auto rc = OCIObjectNew( (OCIEnv*)environment.Handle( ), errorHandle, (OCISvcCtx*)Handle( ), static_cast<OCITypeCode>( typecode ), nullptr, nullptr, static_cast<OCIDuration>( duration ), value ? TRUE : FALSE, instance );
            error.CheckResult( rc );
        }
        else
        {
            ThrowInvalidEnvironment( );
        }
    }


    void ServiceContext::TypeByName( const WideString& schemaName, const WideString& typeName, const WideString& versionName, OCI::Duration pinDuration, OCI::TypeGetOpt typeGetOption, OCIType** ociType ) const
    {
        auto& environment = Environment( );
        if ( environment.IsValid( ) )
        {
            auto ociSchemaName = (OraText*)schemaName.data( );
            auto schemaNameLength = static_cast<UInt32>( schemaName.size( ) * sizeof( wchar_t ) );

            auto ociTypeName = (OraText*)typeName.data( );
            auto typeNameLength = static_cast<UInt32>( typeName.size( ) * sizeof( wchar_t ) );

            auto ociVersionName = (OraText*)versionName.data( );
            auto versionNameLength = static_cast<UInt32>( versionName.size( ) * sizeof( wchar_t ) );

            auto& error = Error( );
            auto errorHandle = (OCIError*)error.Handle( );
            auto rc = OCITypeByName( (OCIEnv*)environment.Handle( ), errorHandle, (OCISvcCtx*)this->Handle( ),
                ociSchemaName, schemaNameLength, ociTypeName, typeNameLength, ociVersionName, versionNameLength,
                static_cast<OCIDuration>( pinDuration ), static_cast<OCITypeGetOpt>( typeGetOption ), ociType );
            error.CheckResult( rc );
        }
        else
        {
            ThrowInvalidEnvironment( );
        }
    }


    void ServiceContext::TypeByFullName( const WideString& fullName, const WideString& versionName, OCI::Duration pinDuration, OCI::TypeGetOpt typeGetOption, OCIType** ociType ) const
    {
        auto& environment = Environment( );
        if ( environment.IsValid( ) )
        {
            auto ociFullName = (OraText*)fullName.data( );
            auto fullNameLength = static_cast<UInt32>( fullName.size( ) * sizeof( wchar_t ) );

            auto ociVersionName = (OraText*)versionName.data( );
            auto versionNameLength = static_cast<UInt32>( versionName.size( ) * sizeof( wchar_t ) );

            auto& error = Error( );
            auto errorHandle = (OCIError*)error.Handle( );
            auto rc = OCITypeByFullName( (OCIEnv*)environment.Handle( ), errorHandle, (OCISvcCtx*)Handle( ),
                ociFullName, fullNameLength, ociVersionName, versionNameLength,
                static_cast<OCIDuration>( pinDuration ), static_cast<OCITypeGetOpt>( typeGetOption ), ociType );
            error.CheckResult( rc );
        }
        else
        {
            ThrowInvalidEnvironment( );
        }
    }

    bool ServiceContext::Exists( const WideString& objectName, OCI::ParameterType parameterType ) const
    {
        OCIDescribe* ociDescribe = nullptr;

        auto& environment = Environment( );
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto rc = OCIHandleAlloc( environmentHandle, (void**)&ociDescribe, (UInt32)OCI_HTYPE_DESCRIBE, (size_t)0, (void**)0 );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( environmentHandle, rc );
        }
        OCI::Describe result( *this, ociDescribe, true );

        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );

        rc = OCIDescribeAny( (OCISvcCtx*)Handle( ), errorHandle, (OraText*)objectName.data( ), static_cast<UInt32>( objectName.length( ) * sizeof( wchar_t ) ),
            OCI_OTYPE_NAME, OCI_DEFAULT, static_cast<Byte>( parameterType ), ociDescribe );

        if ( rc < OCI_SUCCESS )
        {
            Int32 errorCode = 0;
            wchar_t messageBuffer[OCI_ERROR_MAXMSG_SIZE2];
            auto rc2 = OCIErrorGet( errorHandle, 1,
                nullptr, &errorCode, (OraText*)messageBuffer, OCI_ERROR_MAXMSG_SIZE2 * sizeof( wchar_t ), static_cast<UInt32>( HandleType::Error ) );
            switch ( errorCode )
            {
                case 942:
                case 4043:
                    return false;
                default:
                    if ( rc2 == OCI_SUCCESS )
                    {
                        HCC_THROW( Data::OracleClient::OracleException, errorCode, messageBuffer );
                    }
                    else
                    {
                        HCC_THROW( Data::OracleClient::OracleException, errorCode, HCC_TEXT( "Unknown Oracle RDBMS error" ) );
                    }
            }
        }
        return true;
    }

    OCI::Describe ServiceContext::Describe( const WideString& objectName, OCI::ParameterType parameterType, bool showInvisibleColumns ) const
    {
        OCIDescribe* ociDescribe = nullptr;

        auto& environment = Environment( );
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto rc = OCIHandleAlloc( environmentHandle, (void**)&ociDescribe, (UInt32)OCI_HTYPE_DESCRIBE, (size_t)0, (void**)0 );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( environmentHandle, rc );
        }
        OCI::Describe result( *this, ociDescribe, true );

        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );

        if ( showInvisibleColumns )
        {
            Byte invscols = 1;
            rc = OCIAttrSet( ociDescribe, OCI_HTYPE_DESCRIBE, &invscols, 0, OCI_ATTR_SHOW_INVISIBLE_COLUMNS, errorHandle );
            error.CheckResult( rc );
        }
        rc = OCIDescribeAny( (OCISvcCtx*)Handle( ), errorHandle, (OraText*)objectName.data( ), static_cast<UInt32>( objectName.length( ) * sizeof( wchar_t ) ), 
            OCI_OTYPE_NAME, OCI_DEFAULT, static_cast<Byte>( parameterType ), ociDescribe );
        error.CheckResult( rc );

        return result;

    }

    OCI::Describe ServiceContext::Describe( const wchar_t* objectName, OCI::ParameterType parameterType, bool showInvisibleColumns ) const
    {
        return Describe( WideString( objectName ), parameterType, showInvisibleColumns );
    }

    OCI::Describe ServiceContext::Describe( const OCI::Type& type ) const
    {
        return Describe( (OCIType*)type.Handle( ) );
    }

    OCI::Describe ServiceContext::Describe( OCIType* type ) const
    {
        OCIDescribe* describe = nullptr;

        auto& environment = Environment( );
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto rc = OCIHandleAlloc( environmentHandle, (void**)&describe, (UInt32)OCI_HTYPE_DESCRIBE, (size_t)0, (void**)0 );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( environmentHandle, rc );
        }
        OCI::Describe result( *this, describe );

        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        rc = OCIDescribeAny( (OCISvcCtx*)Handle( ), errorHandle, type, 0, OCI_OTYPE_PTR, OCI_DEFAULT, OCI_PTYPE_TYPE, describe );
        error.CheckResult( rc );

        return result;
    }

    OCI::Describe ServiceContext::Describe( const OCI::Ref& typeRef ) const
    {
        auto result = Describe( (OCIRef*)typeRef.Handle( ) );
        return result;
    }

    OCI::Describe ServiceContext::Describe( OCIRef* typeRef ) const
    {
        OCIDescribe* describe = nullptr;

        auto& environment = Environment( );
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto rc = OCIHandleAlloc( environmentHandle, (void**)&describe, (UInt32)OCI_HTYPE_DESCRIBE, (size_t)0, (void**)0 );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( environmentHandle, rc );
        }
        OCI::Describe result( *this, describe );

        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        rc = OCIDescribeAny( (OCISvcCtx*)Handle( ), errorHandle, typeRef, 0, OCI_OTYPE_REF, OCI_DEFAULT, OCI_PTYPE_TYPE, describe );
        error.CheckResult( rc );

        return result;
    }


    const OCI::Session& ServiceContext::CreateSession( )
    {
        auto& environment = Environment( );
        if ( environment.IsValid( ) )
        {
            auto result = environment.CreateSession( );
            SetSession( std::move( result ) );
            return session_;
        }
        else
        {
            ThrowInvalidEnvironment( );
        }
    }

    const OCI::Session& ServiceContext::CreateSession( const wchar_t* username, size_t usernameLength, const wchar_t* password, size_t passwordLength )
    {
        auto& result = CreateSession( );
        result.SetUserName( username, usernameLength );
        result.SetPassword( password, passwordLength );
        return result;
    }


    bool ServiceContext::SetServer( const OCI::Server* server )
    {
        auto currentServer = Server( );
        if ( currentServer != server )
        {
            auto& environment = Environment( );
            if ( environment.IsValid( ) )
            {
                auto& error = Error( );
                auto errorHandle = (OCIError*)error.Handle( );
                auto rc = OCIAttrSet( (dvoid*)Handle( ), static_cast<UInt32>( OCIHandleType ), (dvoid*)server->Handle( ), (UInt32)0, static_cast<UInt32>( Attribute::SERVER ), errorHandle );
                error.CheckResult( rc );
                server_ = server;
            }
            else
            {
                ThrowInvalidEnvironment( );
            }
            return true;
        }
        return false;
    }



    void ServiceContext::SessionBegin( CredidentialType credidentialType, AuthenticationMode authenticationMode ) const
    {
        auto& environment = Environment( );
        if ( environment.IsValid( ) )
        {
            auto& session = Session( );
            if ( !session && credidentialType == CredidentialType::DatabaseServer )
            {
                HCC_THROW( Data::OracleClient::OracleException, L"Authentication not set" );
            }
            auto& error = Error( );
            auto errorHandle = (OCIError*)error.Handle( );
            auto rc = OCISessionBegin( (OCISvcCtx*)Handle( ), errorHandle, (OCISession*)session.Handle( ), static_cast<UInt32>( credidentialType ), static_cast<UInt32>( authenticationMode ) );
            error.CheckResult( rc );

        }
        else
        {
            ThrowInvalidEnvironment( );
        }
    }

    void ServiceContext::SessionEnd( ) const
    {
        auto& environment = Environment( );
        if ( environment.IsValid( ) )
        {
            OCISession* sessionHandle = nullptr;
            auto& session = Session( );
            if ( session.IsValid( ) )
            {
                sessionHandle = (OCISession*)session.Handle( );
            }
            auto& error = Error( );
            auto errorHandle = (OCIError*)error.Handle( );
            auto rc = OCISessionEnd( (OCISvcCtx*)Handle( ), errorHandle, sessionHandle, OCI_DEFAULT );
            error.CheckResult( rc );
        }
        else
        {
            ThrowInvalidEnvironment( );
        }
    }

    OCI::Statement ServiceContext::CreateStatement( const wchar_t* sql, size_t sqlLength ) const
    {
        auto& environment = Environment( );
        if ( environment.IsValid( ) )
        {
            OCIStmt* ociStatement = nullptr;
            auto& error = Error( );
            auto errorHandle = (OCIError*)error.Handle( );
            auto rc = OCIStmtPrepare2( (OCISvcCtx*)Handle( ), &ociStatement, errorHandle, 
                (OraText*)sql, static_cast<UInt32>( sqlLength * sizeof( wchar_t ) ),
                nullptr, 0, OCI_NTV_SYNTAX, OCI_DEFAULT );
            error.CheckResult( rc );
            return Statement( *this, ociStatement, true );
        }
        else
        {
            ThrowInvalidEnvironment( );
        }
    }


    OCI::Describe ServiceContext::CreateDescribe( ) const
    {
        OCIDescribe* ociDescribe = nullptr;

        auto& environment = Environment( );
        auto environmentHandle = (OCIEnv*)environment.Handle( );

        auto rc = OCIHandleAlloc( environmentHandle, (dvoid**)&ociDescribe, OCI_HTYPE_DESCRIBE, 0, (dvoid**)0 );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( environmentHandle, rc );
        }

        OCI::Describe result( *this, ociDescribe );
        return result;
    }


    std::vector<WideString> ServiceContext::GetDbmsOutput( ) const
    {
        std::vector<WideString> result;
        auto statement = CreateStatement( L"BEGIN DBMS_OUTPUT.GET_LINE(line=>:p1, status=>:p2); END;" );

        auto bufferBind = statement.Bind<OCI::CStringBind>( 1, 32767 );
        auto statusBind = statement.Bind<OCI::Int16Bind>( 2 );

        statement.Execute( );
        auto status = statusBind->AsInt16( );
        while ( status != 1 )
        {
            result.emplace_back( bufferBind->AsString( ) );
            statement.Execute( );
            status = statusBind->AsInt16( );
        }
        return result;
    }


    

}