#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    Int32 DynamicDefine::DynamicDefineCallback( void* octxp, OCIDefine* defnp, UInt32 iter, void** bufpp, UInt32** alenp, Byte* piecep, void** indp, UInt16** rcodep )
    {
        DynamicDefine* self = (DynamicDefine*)octxp;
        if ( self )
        {
            return self->HandleData( iter, bufpp, alenp, piecep, indp, rcodep );
        }
        return OCI_CONTINUE;
    }

    Int32 DynamicDefine::HandleData( UInt32 iter, void** bufpp, UInt32** alenp, Byte* piecep, void** indp, UInt16** rcodep )
    {
        return OCI_CONTINUE;
    }
    void DynamicDefine::RegisterCallback( )
    {
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto defineHandle = (OCIDefine*)Handle( );
        auto rc = OCIDefineDynamic( (OCIDefine*)Handle( ), errorHandle, this, DynamicDefineCallback );
        if ( rc != OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }

}