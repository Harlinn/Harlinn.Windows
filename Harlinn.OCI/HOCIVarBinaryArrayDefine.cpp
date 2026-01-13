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
#include <HCCBinaryReader.h>

namespace Harlinn::OCI
{
    VarBinaryArrayDefine::VarBinaryArrayDefine( const OCI::Statement& statement, size_t arraySize, UInt32 columnDataSize )
        : Base( statement, arraySize ), columnDataSize_( columnDataSize )
    {
        size_t allocationSize = (static_cast<size_t>( DataTypeSize ) + static_cast<size_t>( columnDataSize_ )) * arraySize;
        data_ = (DataType*)malloc( allocationSize );
        if ( data_ )
        {
            memset( data_, 0, allocationSize );
        }
    }

    VarBinaryArrayDefine::VarBinaryArrayDefine( const OCI::Statement& statement, size_t arraySize, const OCI::ColumnDescriptor& columnDescriptor )
        : VarBinaryArrayDefine( statement, arraySize, columnDescriptor.Length( ) )
    {
        
    }

    VarBinaryArrayDefine::~VarBinaryArrayDefine( )
    {
        if ( data_ )
        {
            free( data_ );
        }
    }

    void VarBinaryArrayDefine::Initialize( UInt32 positon )
    {
        auto allocationSize = static_cast<UInt32>(( DataTypeSize + columnDataSize_ ) * Count());
        DefineByPos( positon, OCI::OraType::VBI, data_, allocationSize );
    }

    bool VarBinaryArrayDefine::AsBoolean( size_t index ) const
    {
        auto columnData = ColumnData( index );
        if ( columnData && columnData->size )
        {
            for ( UInt16 i = 0; i < columnData->size; ++i )
            {
                if ( columnData->data[i] )
                {
                    return true;
                }
            }
        }
        return false;
    }
    namespace
    {
        template<typename T>
        inline T ConvertBinaryTo( VarBinaryArrayDefine::DataType* rowData )
        {
            if ( rowData && rowData->size == sizeof( T ) )
            {
                return *( (T*)rowData->data );
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"Unable to perform the requested conversion" );
            }
        }
    }
    Byte VarBinaryArrayDefine::AsByte( size_t index ) const
    {
        return ConvertBinaryTo<Byte>( ColumnData( index ) );
    }
    std::vector<Byte> VarBinaryArrayDefine::AsBytes( size_t index ) const
    {
        auto columnData = ColumnData( index );
        if ( columnData && columnData->size )
        {
            return std::vector<Byte>( columnData->data, columnData->data + columnData->size );
        }
        return std::vector<Byte>( );
    }
    SByte VarBinaryArrayDefine::AsSByte( size_t index ) const
    {
        return ConvertBinaryTo<SByte>( ColumnData( index ) );
    }
    Int16 VarBinaryArrayDefine::AsInt16( size_t index ) const
    {
        return ConvertBinaryTo<Int16>( ColumnData( index ) );
    }
    UInt16 VarBinaryArrayDefine::AsUInt16( size_t index ) const
    {
        return ConvertBinaryTo<UInt16>( ColumnData( index ) );
    }
    Int32 VarBinaryArrayDefine::AsInt32( size_t index ) const
    {
        return ConvertBinaryTo<Int32>( ColumnData( index ) );
    }
    UInt32 VarBinaryArrayDefine::AsUInt32( size_t index ) const
    {
        return ConvertBinaryTo<UInt32>( ColumnData( index ) );
    }
    Int64 VarBinaryArrayDefine::AsInt64( size_t index ) const
    {
        return ConvertBinaryTo<Int64>( ColumnData( index ) );
    }
    UInt64 VarBinaryArrayDefine::AsUInt64( size_t index ) const
    {
        return ConvertBinaryTo<UInt64>( ColumnData( index ) );
    }
    float VarBinaryArrayDefine::AsSingle( size_t index ) const
    {
        return ConvertBinaryTo<Single>( ColumnData( index ) );
    }
    double VarBinaryArrayDefine::AsDouble( size_t index ) const
    {
        return ConvertBinaryTo<Double>( ColumnData( index ) );
    }
    DateTime VarBinaryArrayDefine::AsDateTime( size_t index ) const
    {
        return ConvertBinaryTo<DateTime>( ColumnData( index ) );
    }
    TimeSpan VarBinaryArrayDefine::AsTimeSpan( size_t index ) const
    {
        return ConvertBinaryTo<TimeSpan>( ColumnData( index ) );
    }
    WideString VarBinaryArrayDefine::AsString( size_t index ) const
    {
        auto columnData = ColumnData( index );
        if ( columnData && columnData->size )
        {
            IO::BufferStream bufferStream( columnData->data, columnData->size );
            IO::BinaryReader reader( bufferStream );
            return reader.Read<WideString>( );
        }
        return {};
    }
    Guid VarBinaryArrayDefine::AsGuid( size_t index ) const
    {
        return ConvertBinaryTo<Guid>( ColumnData( index ) );
    }

}