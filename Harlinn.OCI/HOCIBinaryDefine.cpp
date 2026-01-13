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
    BinaryDefine::BinaryDefine( const OCI::Statement& statement, UInt32 columnDataSize )
        : Base( statement ), data_( nullptr ), columnDataSize_( columnDataSize )
    {
        data_ = (Byte*)malloc( columnDataSize_ );
        if ( data_ )
        {
            memset( data_, 0, columnDataSize_ );
        }
    }

    BinaryDefine::BinaryDefine( const OCI::Statement& statement, const OCI::ColumnDescriptor& columnDescriptor )
        : BinaryDefine( statement, columnDescriptor.Length( ) )
    {
    }

    BinaryDefine::~BinaryDefine( )
    {
        if ( data_ )
        {
            free( data_ );
        }
    }

    void BinaryDefine::Initialize( UInt32 positon )
    {
        DefineByPos( positon, OCI::OraType::BIN, data_, columnDataSize_ );
    }

    bool BinaryDefine::AsBoolean( ) const
    {
        auto columnData = ColumnData( );
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
    Byte BinaryDefine::AsByte( ) const
    {
        return ConvertBinaryTo<Byte>( ColumnData( ), columnDataSize_ );
    }
    std::vector<Byte> BinaryDefine::AsBytes( ) const
    {
        auto columnData = ColumnData( );
        if ( columnData && columnDataSize_ )
        {
            return std::vector<Byte>( columnData, columnData + columnDataSize_ );
        }
        return std::vector<Byte>( );
    }
    SByte BinaryDefine::AsSByte( ) const
    {
        return ConvertBinaryTo<SByte>( ColumnData( ), columnDataSize_ );
    }
    Int16 BinaryDefine::AsInt16( ) const
    {
        return ConvertBinaryTo<Int16>( ColumnData( ), columnDataSize_ );
    }
    UInt16 BinaryDefine::AsUInt16( ) const
    {
        return ConvertBinaryTo<UInt16>( ColumnData( ), columnDataSize_ );
    }
    Int32 BinaryDefine::AsInt32( ) const
    {
        return ConvertBinaryTo<Int32>( ColumnData( ), columnDataSize_ );
    }
    UInt32 BinaryDefine::AsUInt32( ) const
    {
        return ConvertBinaryTo<UInt32>( ColumnData( ), columnDataSize_ );
    }
    Int64 BinaryDefine::AsInt64( ) const
    {
        return ConvertBinaryTo<Int64>( ColumnData( ), columnDataSize_ );
    }
    UInt64 BinaryDefine::AsUInt64( ) const
    {
        return ConvertBinaryTo<UInt64>( ColumnData( ), columnDataSize_ );
    }
    float BinaryDefine::AsSingle( ) const
    {
        return ConvertBinaryTo<Single>( ColumnData( ), columnDataSize_ );
    }
    double BinaryDefine::AsDouble( ) const
    {
        return ConvertBinaryTo<Double>( ColumnData( ), columnDataSize_ );
    }
    DateTime BinaryDefine::AsDateTime( ) const
    {
        return ConvertBinaryTo<DateTime>( ColumnData( ), columnDataSize_ );
    }
    TimeSpan BinaryDefine::AsTimeSpan( ) const
    {
        return ConvertBinaryTo<TimeSpan>( ColumnData( ), columnDataSize_ );
    }
    WideString BinaryDefine::AsString( ) const
    {
        auto columnData = ColumnData( );
        if ( columnData && columnDataSize_ )
        {
            IO::BufferStream bufferStream( columnData, columnDataSize_ );
            IO::BinaryReader reader( bufferStream );
            return reader.Read<WideString>( );
        }
        return {};
    }
    Guid BinaryDefine::AsGuid( ) const
    {
        return ConvertBinaryTo<Guid>( ColumnData( ), columnDataSize_ );
    }

}