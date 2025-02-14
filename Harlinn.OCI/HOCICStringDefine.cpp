/*
   Copyright 2024-2025 Espen Harlinn

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
        result.resize( s.length( ) * sizeof( WideString::value_type ) );
        memcpy( result.data( ), s.c_str( ), s.length( ) * sizeof( WideString::value_type ) );
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
    WideString CStringDefine::AsString( ) const
    {
        WideString result( data_.data( ), static_cast<size_t>( actualSize_ ) / sizeof( wchar_t ) );
        return result;
    }

    Guid CStringDefine::AsGuid( ) const
    {
        auto s = this->AsString( );
        auto result = ConvertTo<Guid>( s );
        return result;
    }

}