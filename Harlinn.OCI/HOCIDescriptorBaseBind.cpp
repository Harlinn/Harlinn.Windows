#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    void* DescriptorBaseBind::DescriptorAlloc( OCI::HandleType handleType )
    {
        void* result = nullptr;
        auto& environment = Environment( );
        auto environmentHandle = (OCIEnv*)environment.Handle();
        auto rc = OCIDescriptorAlloc( environmentHandle, &result, static_cast<UInt32>( handleType ), 0, nullptr );
        if ( rc != OCI_SUCCESS )
        {
            HCC_THROW( Data::OracleClient::OracleException, L"OCIDescriptorAlloc failed" );
        }
        return result;
    }

    void DescriptorBaseBind::DescriptorFree( void* handle, OCI::HandleType handleType )
    {
        if ( handle && handleType != OCI::HandleType::PARAM )
        {
            OCIDescriptorFree( handle, static_cast<UInt32>( handleType ) );
        }
    }
}