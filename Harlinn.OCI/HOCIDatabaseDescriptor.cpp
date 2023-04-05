#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    std::unique_ptr<ListDescriptor> DatabaseDescriptor::SchemaList( ) const
    {
        auto* param = (OCIParam*)GetPointerAttribute( Attribute::LIST_SCHEMAS );
        auto& serviceContext = ServiceContext( );
        auto paramDescriptor = CreateParameter( serviceContext, param, false );
        
        return std::unique_ptr<ListDescriptor>( static_cast<ListDescriptor*>(paramDescriptor.release()) );
    }
}