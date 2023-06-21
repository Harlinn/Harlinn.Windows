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