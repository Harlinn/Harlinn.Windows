#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    void* DescriptorBaseDefine::DescriptorAlloc( const OCI::Statement& statement, OCI::HandleType descriptorType )
    {
        auto& environment = statement.Environment( );
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        void* result = nullptr;
        auto rc = OCIDescriptorAlloc( environmentHandle, &result, static_cast<UInt32>( descriptorType ), 0, nullptr );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( environmentHandle, rc );
        }
        return result;
    }
    void DescriptorBaseDefine::DescriptorFree( void* descriptor, OCI::HandleType descriptorType )
    {
        OCIDescriptorFree( descriptor, static_cast<UInt32>(descriptorType) );
    }

}