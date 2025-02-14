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