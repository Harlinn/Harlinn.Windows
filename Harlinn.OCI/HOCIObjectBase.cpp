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
    ObjectBase::~ObjectBase( )
    {
        auto& serviceContext = ServiceContext( );
        if ( serviceContext.IsValid( ) && object_ && objectReleaseMethod_ != ObjectReleaseMethod::None )
        {
            auto& error = Error( );
            auto& environment = serviceContext.Environment( );
            auto environmentHandle = (OCIEnv*)environment.Handle( );
            auto errorHandle = (OCIError*)error.Handle( );

            if ( ( objectReleaseMethod_ & ObjectReleaseMethod::ObjectFree ) != ObjectReleaseMethod::ObjectFree )
            {
                OCIObjectUnpin( environmentHandle, errorHandle, object_ );
            }
            else
            {
                OCIObjectFree( environmentHandle, errorHandle, object_, static_cast<UInt16>( objectReleaseMethod_ & ObjectReleaseMethod::ObjectFreeMask ) );
            }
        }
    }
}