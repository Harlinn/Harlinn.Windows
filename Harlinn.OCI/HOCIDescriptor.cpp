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
    Descriptor::~Descriptor( )
    {
        if ( OwnsHandle( ) && IsValid( ) )
        {
            auto handleType = HandleType( );
            auto handle = DetachHandle( );
            DescriptorFree( handle, handleType );
        }
    }

    void* Descriptor::DescriptorAlloc( const OCI::ServiceContext& serviceContext, OCI::HandleType handleType )
    {
        if ( serviceContext.IsValid( ) == false )
        {
            HCC_THROW( ArgumentNullException, L"serviceContext" );
        }

        void* result = nullptr;
        auto& environment = serviceContext.Environment( );
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto rc = OCIDescriptorAlloc( environmentHandle, &result, static_cast<UInt32>( handleType ), 0, nullptr );
        if ( rc < OCI_SUCCESS )
        {
            HCC_THROW( Data::OracleClient::OracleException, L"OCIDescriptorAlloc failed" );
        }
        return result;
    }

    void Descriptor::DescriptorFree( void* handle, OCI::HandleType handleType )
    {
        if ( handle && handleType != OCI::HandleType::PARAM )
        {
            OCIDescriptorFree( handle, static_cast<UInt32>( handleType ) );
        }
    }

}