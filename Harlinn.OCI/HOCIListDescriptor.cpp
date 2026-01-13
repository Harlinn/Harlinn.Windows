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

#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    std::unique_ptr<ParameterDescriptor> ListDescriptor::_Parameter( UInt32 index ) const
    {
        OCIParam* parameter = nullptr;
        auto* handle = Handle( );
        auto& error = Error( );
        OCIError* errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIParamGet( handle, OCI_DTYPE_PARAM, errorHandle, (void**)&parameter, index );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        auto& serviceContext = ServiceContext( );
        return ParameterDescriptor::CreateParameter( serviceContext, parameter );
    }

}