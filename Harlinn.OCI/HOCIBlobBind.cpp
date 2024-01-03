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
    BlobBind::BlobBind( const OCI::Statement& statement, const WideString& name )
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
    void BlobBind::Bind( const WideString& name, UInt32 iters )
    {
        SimpleBindByName( name, ExternalType, &data_, static_cast<Int32>( sizeof( BoundType ) ) );
    }
}