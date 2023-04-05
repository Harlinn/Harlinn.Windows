#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    void* DescriptorArrayBaseBind::DescriptorAlloc( OCI::HandleType handleType )
    {
        auto& environment = Environment( );
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        void* result = nullptr;
        auto rc = OCIDescriptorAlloc( environmentHandle, &result, static_cast<UInt32>( handleType ), 0, nullptr );
        if ( rc != OCI_SUCCESS )
        {
            HCC_THROW( Data::OracleClient::OracleException, L"OCIDescriptorAlloc failed" );
        }
        return result;
    }
    void DescriptorArrayBaseBind::DescriptorFree( void* handle, OCI::HandleType handleType )
    {
        if ( handle )
        {
            OCIDescriptorFree( handle, static_cast<UInt32>( handleType ) );
        }
    }
}