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