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