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

namespace Harlinn::OCI::Metadata
{
    Database::Database( const OCI::ServiceContext* serviceContext )
        : Base( serviceContext, serviceContext->DbName() )
    { 

    }
    Database::Database( const OCI::ServiceContext& serviceContext )
        : Database( &serviceContext )
    {
    }

    Database::~Database( ) = default;

    Database::SchemaContainer Database::Schemas( ) const
    {
        SchemaContainer result;
        auto* serviceContext = ServiceContext( );
        auto describe = serviceContext->Describe( Name( ), OCI::ParameterType::Database );
        auto databaseDescriptor = describe.Descriptor<DatabaseDescriptor>( );
        auto schemaDescriptors = databaseDescriptor->Schemas( );
        for ( auto& schemaDescriptor : schemaDescriptors )
        {
            auto schema = std::make_unique<Schema>( serviceContext, this, schemaDescriptor.get() );
            result.emplace( schema->Name(), std::move( schema ) );
        }
        return result;
    }

}