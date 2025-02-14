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

namespace Harlinn::OCI::Metadata
{

    MetadataObject::MetadataObject( const OCI::ServiceContext* serviceContext, const MetadataObject* owner, const OCI::ParameterDescriptor* parameterDescriptor )
        : serviceContext_( serviceContext ), owner_( owner ), name_( parameterDescriptor->Name() )
    { 
    }

    MetadataObject::MetadataObject( const OCI::ServiceContext* serviceContext, const MetadataObject* owner, const WideString& name )
        : serviceContext_( serviceContext ), owner_( owner ), name_( name )
    {
    }

    MetadataObject::MetadataObject( const OCI::ServiceContext* serviceContext, const WideString& name )
        : serviceContext_( serviceContext ), owner_( nullptr ), name_( name )
    {
    }

    MetadataObject::~MetadataObject( )
    { 
    }
}