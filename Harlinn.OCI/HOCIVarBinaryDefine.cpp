#include "pch.h"
#include <HOCIInternal.h>
#include <HCCBinaryReader.h>

namespace Harlinn::OCI
{
    VarBinaryDefine::VarBinaryDefine( const OCI::Statement& statement, UInt32 columnDataSize )
        : Base( statement ), data_( nullptr ), columnDataSize_( columnDataSize )
    {
        data_ = (DataType*)malloc( DataTypeSize + columnDataSize_ );
        if ( data_ )
        {
            memset( data_, 0, DataTypeSize + columnDataSize_ );
        }
    }

    VarBinaryDefine::VarBinaryDefine( const OCI::Statement& statement, const OCI::ColumnDescriptor& columnDescriptor )
        : VarBinaryDefine( statement, columnDescriptor.Length( ) )
    {
    }

    VarBinaryDefine::~VarBinaryDefine( )
    {
        if ( data_ )
        {
            free( data_ );
        }
    }

    void VarBinaryDefine::Initialize( UInt32 positon )
    {
        DefineByPos( positon, OCI::OraType::VBI, data_, DataTypeSize + columnDataSize_ );
    }

    bool VarBinaryDefine::AsBoolean( ) const
    {
        auto columnData = ColumnData( );
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
        inline T ConvertBinaryTo( VarBinaryDefine::DataType* rowData )
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
    Byte VarBinaryDefine::AsByte( ) const
    {
        return ConvertBinaryTo<Byte>( ColumnData( ) );
    }
    std::vector<Byte> VarBinaryDefine::AsBytes( ) const
    {
        auto columnData = ColumnData( );
        if ( columnData && columnData->size )
        {
            return std::vector<Byte>( columnData->data, columnData->data + columnData->size );
        }
        return std::vector<Byte>();
    }
    SByte VarBinaryDefine::AsSByte( ) const
    {
        return ConvertBinaryTo<SByte>( ColumnData( ) );
    }
    Int16 VarBinaryDefine::AsInt16( ) const
    {
        return ConvertBinaryTo<Int16>( ColumnData( ) );
    }
    UInt16 VarBinaryDefine::AsUInt16( ) const
    {
        return ConvertBinaryTo<UInt16>( ColumnData( ) );
    }
    Int32 VarBinaryDefine::AsInt32( ) const
    {
        return ConvertBinaryTo<Int32>( ColumnData( ) );
    }
    UInt32 VarBinaryDefine::AsUInt32( ) const
    {
        return ConvertBinaryTo<UInt32>( ColumnData( ) );
    }
    Int64 VarBinaryDefine::AsInt64( ) const
    {
        return ConvertBinaryTo<Int64>( ColumnData( ) );
    }
    UInt64 VarBinaryDefine::AsUInt64( ) const
    {
        return ConvertBinaryTo<UInt64>( ColumnData( ) );
    }
    float VarBinaryDefine::AsSingle( ) const
    {
        return ConvertBinaryTo<Single>( ColumnData( ) );
    }
    double VarBinaryDefine::AsDouble( ) const
    {
        return ConvertBinaryTo<Double>( ColumnData( ) );
    }
    DateTime VarBinaryDefine::AsDateTime( ) const
    {
        return ConvertBinaryTo<DateTime>( ColumnData( ) );
    }
    TimeSpan VarBinaryDefine::AsTimeSpan( ) const
    {
        return ConvertBinaryTo<TimeSpan>( ColumnData( ) );
    }
    std::wstring VarBinaryDefine::AsString( ) const
    {
        auto columnData = ColumnData( );
        if ( columnData && columnData->size )
        {
            IO::BufferStream bufferStream( columnData->data, columnData->size );
            IO::BinaryReader reader( bufferStream );
            return reader.Read<std::wstring>( );
        }
        return std::wstring();
    }
    Guid VarBinaryDefine::AsGuid( ) const
    {
        return ConvertBinaryTo<Guid>( ColumnData( ) );
    }

}