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
    BinaryArrayDefine::BinaryArrayDefine( const OCI::Statement& statement, size_t arraySize, UInt32 columnDataSize )
        : Base( statement, arraySize ), columnDataSize_( columnDataSize )
    {
        size_t allocationSize = static_cast<size_t>( columnDataSize_ ) * arraySize;
        data_ = (DataType*)malloc( allocationSize );
        if ( data_ )
        {
            memset( data_, 0, allocationSize );
        }
    }

    BinaryArrayDefine::BinaryArrayDefine( const OCI::Statement& statement, size_t arraySize, const OCI::ColumnDescriptor& columnDescriptor )
        : BinaryArrayDefine( statement, arraySize, columnDescriptor.Length( ) )
    {

    }

    BinaryArrayDefine::~BinaryArrayDefine( )
    {
        if ( data_ )
        {
            free( data_ );
        }
    }

    void BinaryArrayDefine::Initialize( UInt32 positon )
    {
        auto allocationSize = static_cast<UInt32>( columnDataSize_ * Count( ) );
        DefineByPos( positon, OCI::OraType::BIN, data_, allocationSize );
    }

    bool BinaryArrayDefine::AsBoolean( size_t index ) const
    {
        auto columnData = ColumnData( index );
        if ( columnData && columnDataSize_ )
        {
            for ( UInt16 i = 0; i < columnDataSize_; ++i )
            {
                if ( columnData[i] )
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
        inline T ConvertBinaryTo( Byte* columnData, UInt32 columnDataSize )
        {
            if ( columnData && columnDataSize == sizeof( T ) )
            {
                return *( (T*)columnData );
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"Unable to perform the requested conversion" );
            }
        }
    }
    Byte BinaryArrayDefine::AsByte( size_t index ) const
    {
        return ConvertBinaryTo<Byte>( ColumnData( index ), columnDataSize_ );
    }
    std::vector<Byte> BinaryArrayDefine::AsBytes( size_t index ) const
    {
        auto columnData = ColumnData( index );
        if ( columnData && columnDataSize_ )
        {
            return std::vector<Byte>( columnData, columnData+ columnDataSize_ );
        }
        return std::vector<Byte>( );
    }
    SByte BinaryArrayDefine::AsSByte( size_t index ) const
    {
        return ConvertBinaryTo<SByte>( ColumnData( index ), columnDataSize_ );
    }
    Int16 BinaryArrayDefine::AsInt16( size_t index ) const
    {
        return ConvertBinaryTo<Int16>( ColumnData( index ), columnDataSize_ );
    }
    UInt16 BinaryArrayDefine::AsUInt16( size_t index ) const
    {
        return ConvertBinaryTo<UInt16>( ColumnData( index ), columnDataSize_ );
    }
    Int32 BinaryArrayDefine::AsInt32( size_t index ) const
    {
        return ConvertBinaryTo<Int32>( ColumnData( index ), columnDataSize_ );
    }
    UInt32 BinaryArrayDefine::AsUInt32( size_t index ) const
    {
        return ConvertBinaryTo<UInt32>( ColumnData( index ), columnDataSize_ );
    }
    Int64 BinaryArrayDefine::AsInt64( size_t index ) const
    {
        return ConvertBinaryTo<Int64>( ColumnData( index ), columnDataSize_ );
    }
    UInt64 BinaryArrayDefine::AsUInt64( size_t index ) const
    {
        return ConvertBinaryTo<UInt64>( ColumnData( index ), columnDataSize_ );
    }
    float BinaryArrayDefine::AsSingle( size_t index ) const
    {
        return ConvertBinaryTo<Single>( ColumnData( index ), columnDataSize_ );
    }
    double BinaryArrayDefine::AsDouble( size_t index ) const
    {
        return ConvertBinaryTo<Double>( ColumnData( index ), columnDataSize_ );
    }
    DateTime BinaryArrayDefine::AsDateTime( size_t index ) const
    {
        return ConvertBinaryTo<DateTime>( ColumnData( index ), columnDataSize_ );
    }
    TimeSpan BinaryArrayDefine::AsTimeSpan( size_t index ) const
    {
        return ConvertBinaryTo<TimeSpan>( ColumnData( index ), columnDataSize_ );
    }
    WideString BinaryArrayDefine::AsString( size_t index ) const
    {
        auto columnData = ColumnData( index );
        if ( columnData && columnDataSize_ )
        {
            IO::BufferStream bufferStream( columnData, columnDataSize_ );
            IO::BinaryReader reader( bufferStream );
            return reader.Read<WideString>( );
        }
        return WideString( );
    }
    Guid BinaryArrayDefine::AsGuid( size_t index ) const
    {
        return ConvertBinaryTo<Guid>( ColumnData( index ), columnDataSize_ );
    }

}