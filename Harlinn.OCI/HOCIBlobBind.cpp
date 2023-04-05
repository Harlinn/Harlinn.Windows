#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    BlobBind::BlobBind( const OCI::Statement& statement )
        : Base( statement ), data_( 0 )
    {
        auto rc = OCIDescriptorAlloc( statement.Handle( ), (void**)&data_, OCI_DTYPE_LOB, 0, nullptr );
        if ( rc < OCI_SUCCESS )
        {
            auto& error = statement.Error( );
            error.CheckResult( rc );
        }
    }


    BlobBind::BlobBind( const OCI::Statement& statement, UInt32 position )
        : Base( statement, position ), data_( 0 )
    {
        auto rc = OCIDescriptorAlloc( statement.Handle( ), (void**)&data_, OCI_DTYPE_LOB, 0, nullptr );
        if ( rc < OCI_SUCCESS )
        {
            auto& error = statement.Error( );
            error.CheckResult( rc );
        }
    }
    BlobBind::BlobBind( const OCI::Statement& statement, const std::wstring& name )
        : Base( statement, name ), data_( 0 )
    {
        auto rc = OCIDescriptorAlloc( statement.Handle( ), (void**)&data_, OCI_DTYPE_LOB, 0, nullptr );
        if ( rc < OCI_SUCCESS )
        {
            auto& error = statement.Error( );
            error.CheckResult( rc );
        }
    }


    BlobBind::~BlobBind( )
    {
        OCIDescriptorFree( data_, OCI_DTYPE_LOB );
    }

    void BlobBind::Bind( UInt32 positon, UInt32 iters )
    {
        SimpleBindByPos( positon, ExternalType, &data_, static_cast<Int32>( sizeof( BoundType ) ) );
    }
    void BlobBind::Bind( const std::wstring& name, UInt32 iters )
    {
        SimpleBindByName( name, ExternalType, &data_, static_cast<Int32>( sizeof( BoundType ) ) );
    }
}