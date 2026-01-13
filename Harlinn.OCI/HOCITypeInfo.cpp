/*
   Copyright 2024-2026 Espen Harlinn

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
    TypeInfo::TypeInfo( const TypeDescriptor* type )
        : dataSize_( 0 )
    {
        if ( !type )
        {
            HCC_THROW( ArgumentNullException, L"type" );
        }
        auto attributes = type->Attributes( );
        reserve( attributes.size( ) );

        size_t typeSize = 0;
        for ( auto& attribute : attributes )
        {
            OCIRef* ref = nullptr;
            auto typeCode = attribute->TypeCode( );
            auto dataSize = DataSizeOf( typeCode, attribute->DataSize( ) );
            auto offset = Offset( typeCode, typeSize );
            typeSize = offset + dataSize;
            auto precision = attribute->Precision( );
            auto scale = attribute->Scale( );
            if ( typeCode == OCI::TypeCode::Object ||
                typeCode == OCI::TypeCode::Ref ||
                typeCode == OCI::TypeCode::Table ||
                typeCode == OCI::TypeCode::VArray )
            {
                ref = attribute->TDO( );
            }
            emplace_back( typeCode, precision, scale, dataSize, offset, ref );
        }
        dataSize_ = typeSize;

    }
}