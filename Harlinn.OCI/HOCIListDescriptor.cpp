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