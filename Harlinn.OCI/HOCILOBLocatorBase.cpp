#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    void LOBLocatorBase::Append( const LOBLocatorBase& source ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error();
        auto handle = (OCILobLocator*)Handle( );
        auto sourceHandle = (OCILobLocator*)source.Handle( );

        OCI::LobAppend( serviceContext, error, handle, sourceHandle );
    }


    void LOBLocatorBase::Close( ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto handle = (OCILobLocator*)Handle( );

        OCI::LobClose( serviceContext, error, handle );
    }


    void LOBLocatorBase::Copy( UInt64 destinationOffset, const LOBLocatorBase& source, UInt64 sourceOffset, UInt64 count ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto handle = (OCILobLocator*)Handle( );
        auto sourceHandle = (OCILobLocator*)source.Handle( );

        OCI::LobCopy2( serviceContext, error, handle, sourceHandle, count, destinationOffset, sourceOffset );
    }

    void LOBLocatorBase::DisableBuffering( ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto handle = (OCILobLocator*)Handle( );
        OCI::LobDisableBuffering( serviceContext, error, handle );
    }

    void LOBLocatorBase::EnableBuffering( ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto handle = (OCILobLocator*)Handle( );

        OCI::LobEnableBuffering( serviceContext, error, handle );
    }

    UInt64 LOBLocatorBase::Erase( UInt64 offset, UInt64 count ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto handle = (OCILobLocator*)Handle( );

        UInt64 result = count;
        OCI::LobErase2( serviceContext, error, handle, &count, offset );
        return result;
    }

    void LOBLocatorBase::FlushBuffer( bool releaseResources ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto handle = (OCILobLocator*)Handle( );

        OCI::LobFlushBuffer( serviceContext, error, handle, releaseResources ? OCI_LOB_BUFFER_FREE : 0 );
    }

}