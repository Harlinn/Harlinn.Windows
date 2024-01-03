/*
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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