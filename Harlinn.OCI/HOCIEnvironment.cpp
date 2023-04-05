#include "pch.h"
#include <HOCIInternal.h>

#pragma comment(lib,"oci.lib")
#pragma comment(lib,"ociw32.lib")

namespace Harlinn::OCI
{
    std::atomic<EnvironmentMode> Environment::defaultEnvironmentMode_ =
        EnvironmentMode::Threaded |
        EnvironmentMode::Object |
        EnvironmentMode::Events; //|
        //EnvironmentMode::NewLengthSemantics | 
        //EnvironmentMode::UTF16;

    void* Environment::CreateEnvironment( )
    {
        void* handle = nullptr;

        //auto rc = OCIEnvCreate( (OCIEnv**)&handle,  (UInt32)DefaultEnvironmentMode( ),  nullptr, nullptr, nullptr, nullptr, (size_t)0, (dvoid**)0 );
        auto rc = OCIEnvNlsCreate( (OCIEnv**)&handle, (UInt32)DefaultEnvironmentMode( ), nullptr,nullptr,nullptr,nullptr,0,nullptr, OCI_UTF16ID, OCI_UTF16ID );
        if ( rc < OCI::Result::Success )
        {
            ThrowOracleExceptionOnError( handle, rc );
        }
#ifdef HOCI_DEBUG_TRACK_HANDLES_WITH_PRINTF
        printf( "Created environment handle %p\n", handle );
#endif
        return handle;
    }



    EnvironmentMode Environment::DefaultEnvironmentMode( )
    {
        return defaultEnvironmentMode_.load( );
    }
    void Environment::SetDefaultEnvironmentMode( EnvironmentMode defaultEnvironmentMode )
    {
        defaultEnvironmentMode_ = defaultEnvironmentMode;
    }

    OCI::ErrorHandle Environment::CreateError( ) const
    {
        void* errorHandle = nullptr;
        auto rc = OCIHandleAlloc( (dvoid*)Handle( ), 
            (dvoid**)&errorHandle, 
            OCI_HTYPE_ERROR, 0, (dvoid**)0 );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( Handle( ), rc );
        }
#ifdef HOCI_DEBUG_TRACK_HANDLES_WITH_PRINTF
        printf( "Allocated error handle %p\n", errorHandle );
#endif
        return OCI::ErrorHandle( *this, errorHandle, true );
    }

    OCI::Server Environment::CreateServer( ) const
    {
        OCIServer* server = nullptr;
        auto rc = OCIHandleAlloc( (dvoid*)Handle( ), (dvoid**)&server, OCI_HTYPE_SERVER, 0, (dvoid**)0 );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( Handle( ), rc );
        }
#ifdef HOCI_DEBUG_TRACK_HANDLES_WITH_PRINTF
        printf( "Allocated server handle %p\n", server );
#endif
        return OCI::Server( *this, server, true );
    }

    OCI::Session Environment::CreateSession( ) const
    {
        OCISession* session = nullptr;
        auto rc = OCIHandleAlloc( (dvoid*)Handle( ), (dvoid**)&session, OCI_HTYPE_SESSION, 0, (dvoid**)0 );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( Handle( ), rc );
        }
#ifdef HOCI_DEBUG_TRACK_HANDLES_WITH_PRINTF
        printf( "Allocated user session handle %p\n", session );
#endif
        return OCI::Session( *this, session, true );
    }


    ServiceContext Environment::CreateServiceContext( ) const
    {
        OCISvcCtx* svcctx = nullptr;
        auto rc = OCIHandleAlloc( (dvoid*)Handle( ), (dvoid**)&svcctx, OCI_HTYPE_SVCCTX, 0, (dvoid**)0 );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( Handle( ), rc );
        }
#ifdef HOCI_DEBUG_TRACK_HANDLES_WITH_PRINTF
        printf( "Allocated service context handle %p\n", svcctx );
#endif
        return ServiceContext( *this, svcctx, true );
    }

    OCI::TransactionHandle Environment::CreateTransaction( const OCI::ServiceContext& serviceContext ) const
    {
        OCITrans* transactionHandle = nullptr;
        auto rc = OCIHandleAlloc( (dvoid*)Handle( ), (dvoid**)&transactionHandle, OCI_HTYPE_TRANS, 0, (dvoid**)0 );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( Handle( ), rc );
        }
#ifdef HOCI_DEBUG_TRACK_HANDLES_WITH_PRINTF
        printf( "Allocated transaction handle %p\n", transactionHandle );
#endif
        return TransactionHandle( serviceContext, transactionHandle, true );
    }

    Subscription Environment::CreateSubscription( ) const
    {
        OCISubscription* subscription = nullptr;
        auto rc = OCIHandleAlloc( (dvoid*)Handle( ), (dvoid**)&subscription, OCI_HTYPE_SUBSCRIPTION, 0, (dvoid**)0 );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( Handle( ), rc );
        }
#ifdef HOCI_DEBUG_TRACK_HANDLES_WITH_PRINTF
        printf( "Allocated subscription handle %p\n", subscription );
#endif
        return Subscription( *this, subscription, true );
    }
}