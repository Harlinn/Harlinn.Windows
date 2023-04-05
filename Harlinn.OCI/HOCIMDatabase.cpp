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