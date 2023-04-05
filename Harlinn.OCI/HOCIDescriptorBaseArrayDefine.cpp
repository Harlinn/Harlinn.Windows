#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    void DescriptorBaseArrayDefine::ArrayDescriptorAlloc( const OCI::Statement& statement, OCI::HandleType descriptorType, size_t size, void** descriptors )
    {
        auto& environment = statement.Environment( );
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto rc = OCIArrayDescriptorAlloc( environmentHandle, descriptors, static_cast<UInt32>( descriptorType ), static_cast<UInt32>( size ) ,0, nullptr );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( environmentHandle, rc );
        }
    }
    void DescriptorBaseArrayDefine::ArrayDescriptorFree( void** descriptors, OCI::HandleType descriptorType )
    {
        OCIArrayDescriptorFree( descriptors, static_cast<UInt32>( descriptorType ) );
    }
}