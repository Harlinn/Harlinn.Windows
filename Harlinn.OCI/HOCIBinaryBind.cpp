#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    BinaryBind::~BinaryBind( )
    {
        if ( data_ )
        {
            free( data_ );
        }
    }

    void BinaryBind::Bind( UInt32 positon, UInt32 iters )
    {
        SimpleBindByPos( positon, ExternalType, data_, size_ );
    }

    void BinaryBind::Bind( const WideString& name, UInt32 iters )
    {
        SimpleBindByName( name, ExternalType, data_, size_ );
    }

    size_t BinaryBind::Size( ) const
    {
        return size_;
    }
    void* BinaryBind::Data( ) const
    {
        return data_;
    }
    void BinaryBind::Resize( size_t newSize )
    {
        if ( newSize != size_ )
        {
            data_ = (Byte*)realloc( data_, newSize );
            size_ = static_cast<UInt32>( newSize );
        }
    }
    void BinaryBind::Write( const IO::MemoryStream& stream )
    {
        UInt32 size = static_cast<UInt32>( stream.Size( ) );
        auto buffer = static_cast<const Byte*>( stream.Buffer( ) );
        Resize( size );
        if ( size )
        {
            memcpy( data_, buffer, size );
            indicator_ = 0;
        }
        else
        {
            indicator_ = -1;
        }
    }
    void BinaryBind::Write( void* data, size_t dataSize )
    {
        UInt32 size = static_cast<UInt32>( dataSize );
        auto buffer = static_cast<const Byte*>( data );
        Resize( size );
        if ( size )
        {
            memcpy( data_, buffer, size );
            indicator_ = 0;
        }
        else
        {
            indicator_ = -1;
        }
    }
}