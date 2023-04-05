#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    CStringDefine::CStringDefine( const OCI::Statement& statement, size_t size )
        : Base( statement ), actualSize_( static_cast<UInt16>( size ) )
    {
        data_.resize( size + 1 );
    }

    CStringDefine::CStringDefine( const OCI::Statement& statement, const OCI::ColumnDescriptor& columnDescriptor )
        : Base( statement )
    {
        actualSize_ = static_cast<UInt16>( columnDescriptor.CharacterLength( ) );
        data_.resize( static_cast<size_t>(actualSize_) + 1 );

    }

    CStringDefine::~CStringDefine( ) = default;

    void CStringDefine::Initialize( UInt32 positon )
    {
        DefineByPos( positon, OCI::OraType::STR, data_.data( ), static_cast<Int64>( data_.size( ) * sizeof( wchar_t ) ), &actualSize_ );
    }

    bool CStringDefine::AsBoolean( ) const
    {
        auto result = ConvertTo<bool>( this->AsString( ) );
        return result;
    }
    Byte CStringDefine::AsByte( ) const
    {
        auto result = ConvertTo<Byte>( this->AsString( ) );
        return result;
    }
    SByte CStringDefine::AsSByte( ) const
    {
        auto result = ConvertTo<SByte>( this->AsString( ) );
        return result;
    }
    std::vector<Byte> CStringDefine::AsBytes( ) const
    {
        auto s = this->AsString( );
        std::vector<Byte> result;
        result.resize( s.length( ) * sizeof( std::wstring::value_type ) );
        memcpy( result.data( ), s.c_str( ), s.length( ) * sizeof( std::wstring::value_type ) );
        return result;
    }
    short CStringDefine::AsInt16( ) const
    {
        auto result = ConvertTo<Int16>( this->AsString( ) );
        return result;
    }
    UInt16 CStringDefine::AsUInt16( ) const
    {
        auto result = ConvertTo<UInt16>( this->AsString( ) );
        return result;
    }
    Int32 CStringDefine::AsInt32( ) const
    {
        auto result = ConvertTo<Int32>( this->AsString( ) );
        return result;
    }
    UInt32 CStringDefine::AsUInt32( ) const
    {
        auto result = ConvertTo<UInt32>( this->AsString( ) );
        return result;
    }
    Int64 CStringDefine::AsInt64( ) const
    {
        auto result = ConvertTo<Int64>( this->AsString( ) );
        return result;
    }
    UInt64 CStringDefine::AsUInt64( ) const
    {
        auto result = ConvertTo<UInt64>( this->AsString( ) );
        return result;
    }
    float CStringDefine::AsSingle( ) const
    {
        auto result = ConvertTo<Single>( this->AsString( ) );
        return result;
    }
    double CStringDefine::AsDouble( ) const
    {
        auto result = ConvertTo<Double>( this->AsString( ) );
        return result;
    }
    DateTime CStringDefine::AsDateTime( ) const
    {
        auto result = ConvertTo<DateTime>( this->AsString( ) );
        return result;
    }

    TimeSpan CStringDefine::AsTimeSpan( ) const
    {
        auto result = ConvertTo<TimeSpan>( this->AsString( ) );
        return result;
    }
    std::wstring CStringDefine::AsString( ) const
    {
        std::wstring result( data_.data( ), static_cast<size_t>( actualSize_ ) / sizeof( wchar_t ) );
        return result;
    }

    Guid CStringDefine::AsGuid( ) const
    {
        auto s = this->AsString( );
        auto result = ConvertTo<Guid>( s );
        return result;
    }

}