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

    void HandleBase::HandleFree( void* handle, OCI::HandleType handleType ) noexcept
    {
#ifdef HOCI_DEBUG_TRACK_HANDLES_WITH_PRINTF
        printf( "Calling OCIHandleFree for %p, type %d\n", handle, static_cast<Int32>( handleType ) );
#endif
        OCIHandleFree( handle, static_cast<UInt32>( handleType ) );
    }

    Int32 HandleBase::GetAttribute( void* buffer, UInt32* size, Attribute attribute ) const
    {
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIAttrGet( Handle( ), static_cast<UInt32>( handleType_ ), (dvoid*)buffer, size, static_cast<UInt32>( attribute ), errorHandle );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        return rc;
    }
    Int32 HandleBase::SetAttribute( void* buffer, UInt32 size, Attribute attribute ) const
    {
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIAttrSet( Handle( ), static_cast<UInt32>( handleType_ ), (dvoid*)buffer, size, static_cast<UInt32>( attribute ), errorHandle );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        return rc;
    }

}