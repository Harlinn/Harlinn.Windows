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
    void DescriptorBaseArrayDefine::ArrayDescriptorAlloc( const OCI::Statement& statement, OCI::HandleType descriptorType, size_t size, void** descriptors )
    {
        auto& environment = statement.Environment( );
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto rc = OCIArrayDescriptorAlloc( environmentHandle, descriptors, static_cast<UInt32>( descriptorType ), static_cast<UInt32>( size ) ,0, nullptr );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( environmentHandle, rc );
        }
    }
    void DescriptorBaseArrayDefine::ArrayDescriptorFree( void** descriptors, OCI::HandleType descriptorType )
    {
        OCIArrayDescriptorFree( descriptors, static_cast<UInt32>( descriptorType ) );
    }
}