/*
   Copyright 2024 Espen Harlinn

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