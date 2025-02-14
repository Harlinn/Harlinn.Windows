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
    CStringArrayDefine::CStringArrayDefine( const OCI::Statement& statement, size_t size, size_t maxColumnSize )
        : Base( statement, size ), maxColumnDataSize_( maxColumnSize + 1ull )
    {
        size_t totalDataSize = size * maxColumnDataSize_ * sizeof( wchar_t );
        data_ = (wchar_t*)malloc( totalDataSize );
        dataSizes_.resize( size, static_cast<UInt32>( maxColumnDataSize_ ) );
    }

    CStringArrayDefine::CStringArrayDefine( const OCI::Statement& statement, size_t size, const OCI::ColumnDescriptor& columnDescriptor )
        : Base( statement, size ), maxColumnDataSize_( columnDescriptor.Length( ) + 1ull )
    {
        size_t totalDataSize = size * maxColumnDataSize_ * sizeof( wchar_t );
        data_ = (wchar_t*)malloc( totalDataSize );
        dataSizes_.resize( size, static_cast<UInt32>( maxColumnDataSize_ ) );
    }



    CStringArrayDefine::~CStringArrayDefine( )
    {
        free( data_ );
    }


    void CStringArrayDefine::Initialize( UInt32 positon )
    {
        DefineByPos( positon, OCI::OraType::STR, data_, static_cast<Int64>( maxColumnDataSize_ * sizeof( wchar_t ) ), dataSizes_.data( ) );
    }

    bool CStringArrayDefine::AsBoolean( size_t index ) const
    {
        auto result = ConvertTo<bool>( this->AsString( index ) );
        return result;
    }
    Byte CStringArrayDefine::AsByte( size_t index ) const
    {
        auto result = ConvertTo<Byte>( this->AsString( index ) );
        return result;
    }
    SByte CStringArrayDefine::AsSByte( size_t index ) const
    {
        auto result = ConvertTo<SByte>( this->AsString( index ) );
        return result;
    }
    std::vector<Byte> CStringArrayDefine::AsBytes( size_t index ) const
    {
        auto s = this->AsString( index );
        std::vector<Byte> result;
        result.resize( s.length( ) * sizeof( WideString::value_type ) );
        memcpy( result.data( ), s.c_str( ), s.length( ) * sizeof( WideString::value_type ) );
        return result;
    }
    short CStringArrayDefine::AsInt16( size_t index ) const
    {
        auto result = ConvertTo<Int16>( this->AsString( index ) );
        return result;
    }
    UInt16 CStringArrayDefine::AsUInt16( size_t index ) const
    {
        auto result = ConvertTo<UInt16>( this->AsString( index ) );
        return result;
    }
    Int32 CStringArrayDefine::AsInt32( size_t index ) const
    {
        auto result = ConvertTo<Int32>( this->AsString( index ) );
        return result;
    }
    UInt32 CStringArrayDefine::AsUInt32( size_t index ) const
    {
        auto result = ConvertTo<UInt32>( this->AsString( index ) );
        return result;
    }
    long long CStringArrayDefine::AsInt64( size_t index ) const
    {
        auto result = ConvertTo<Int64>( this->AsString( index ) );
        return result;
    }
    UInt64 CStringArrayDefine::AsUInt64( size_t index ) const
    {
        auto result = ConvertTo<UInt64>( this->AsString( index ) );
        return result;
    }
    float CStringArrayDefine::AsSingle( size_t index ) const
    {
        auto result = ConvertTo<Single>( this->AsString( index ) );
        return result;
    }
    double CStringArrayDefine::AsDouble( size_t index ) const
    {
        auto result = ConvertTo<Double>( this->AsString( index ) );
        return result;
    }
    DateTime CStringArrayDefine::AsDateTime( size_t index ) const
    {
        auto result = ConvertTo<DateTime>( this->AsString( index ) );
        return result;
    }


    TimeSpan CStringArrayDefine::AsTimeSpan( size_t index ) const
    {
        auto result = ConvertTo<TimeSpan>( this->AsString( index ) );
        return result;
    }
    WideString CStringArrayDefine::AsString( size_t index ) const
    {
        const wchar_t* ptr = (const wchar_t*)&data_[index * maxColumnDataSize_];
        size_t length = dataSizes_[index] / sizeof( wchar_t );
        WideString result( ( WideString::value_type* )ptr, length );
        return result;
    }

    Guid CStringArrayDefine::AsGuid( size_t index ) const
    {
        auto s = this->AsString( index );
        auto result = ConvertTo<Guid>( s );
        return result;
    }
}