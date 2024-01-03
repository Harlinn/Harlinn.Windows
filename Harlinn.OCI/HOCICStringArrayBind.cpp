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
    CStringArrayBind::~CStringArrayBind( )
    {
        free( data_ );
    }

    void CStringArrayBind::Resize( size_t arraySize, size_t arrayMaxSize, size_t elementSize )
    {

        size_t allocationSize = arrayMaxSize * elementSize * sizeof( wchar_t );
        wchar_t* newData = (wchar_t*)malloc( allocationSize );
        if ( !newData )
        {
            HCC_THROW( OutOfMemoryException, L"Cannot reserve the requested amount of memory" );
        }

        memset( newData, 0, allocationSize );
        if ( data_ )
        {
            free( data_ );
        }

        indicator_.resize( arrayMaxSize, -1 );
        dataSizes_.resize( arrayMaxSize );
        data_ = newData;
        arraySize_ = static_cast<UInt32>( arraySize );
        arrayMaxSize_ = static_cast<UInt32>( arrayMaxSize );
        maxColumnDataSize_ = static_cast<UInt32>( elementSize );
    }


    void CStringArrayBind::Bind( UInt32 positon, UInt32 iters )
    {
        if ( IsPlSQL( ) == false )
        {
            Base::BindByPos( positon, ExternalType, data_, static_cast<Int32>( maxColumnDataSize_ ) * sizeof( wchar_t ), indicator_.data( ), dataSizes_.data( ), nullptr, 0, nullptr );
        }
        else
        {
            Base::BindByPos( positon, ExternalType, data_, static_cast<Int32>( maxColumnDataSize_ ) * sizeof( wchar_t ), indicator_.data( ), dataSizes_.data( ), nullptr, arrayMaxSize_, &arraySize_ );
        }
    }
    void CStringArrayBind::Bind( const WideString& name, UInt32 iters )
    {
        if ( IsPlSQL( ) == false )
        {
            Base::BindByName( name, ExternalType, data_, static_cast<Int32>( maxColumnDataSize_ ) * sizeof( wchar_t ), indicator_.data( ), dataSizes_.data( ), nullptr, 0, nullptr );
        }
        else
        {
            Base::BindByName( name, ExternalType, data_, static_cast<Int32>( maxColumnDataSize_ ) * sizeof( wchar_t ), indicator_.data( ), dataSizes_.data( ), nullptr, arrayMaxSize_, &arraySize_ );
        }
    }
    void* CStringArrayBind::Data( size_t index ) const
    {
        return &data_[index * maxColumnDataSize_];
    }
    bool CStringArrayBind::AsBoolean( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<bool>( s );
    }
    void CStringArrayBind::Assign( size_t index, bool newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( index, s );
    }
    Byte CStringArrayBind::AsByte( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<Byte>( s );
    }
    void CStringArrayBind::Assign( size_t index, Byte newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( index, s );
    }
    SByte CStringArrayBind::AsSByte( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<SByte>( s );
    }
    void CStringArrayBind::Assign( size_t index, SByte newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( index, s );
    }
    short CStringArrayBind::AsInt16( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<Int16>( s );
    }
    void CStringArrayBind::Assign( size_t index, Int16 newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( index, s );
    }
    UInt16 CStringArrayBind::AsUInt16( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<UInt16>( s );
    }
    void CStringArrayBind::Assign( size_t index, UInt16 newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( index, s );
    }
    Int32 CStringArrayBind::AsInt32( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<Int32>( s );
    }
    void CStringArrayBind::Assign( size_t index, Int32 newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( index, s );
    }
    UInt32 CStringArrayBind::AsUInt32( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<UInt32>( s );
    }
    void CStringArrayBind::Assign( size_t index, UInt32 newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( index, s );
    }
    Int64 CStringArrayBind::AsInt64( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<Int64>( s );
    }
    void CStringArrayBind::Assign( size_t index, Int64 newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( index, s );
    }
    UInt64 CStringArrayBind::AsUInt64( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<UInt64>( s );
    }
    void CStringArrayBind::Assign( size_t index, UInt64 newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( index, s );
    }
    float CStringArrayBind::AsSingle( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<Single>( s );
    }
    void CStringArrayBind::Assign( size_t index, float newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( index, s );
    }
    double CStringArrayBind::AsDouble( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<Double>( s );
    }
    void CStringArrayBind::Assign( size_t index, double newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( index, s );
    }

    DateTime CStringArrayBind::AsDateTime( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<DateTime>( s );
    }

    void CStringArrayBind::Assign( size_t index, const DateTime& newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( index, s );
    }

    TimeSpan CStringArrayBind::AsTimeSpan( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<TimeSpan>( s );
    }

    void CStringArrayBind::Assign( size_t index, const TimeSpan& newValue )
    {
        auto s = ConvertTo<WideString>( newValue.Ticks( ) );
        Assign( index, s );
    }


    WideString CStringArrayBind::AsString( size_t index ) const
    {
        auto dataSize = dataSizes_[index];
        auto length = dataSize ? ( dataSize - 2 ) / sizeof( wchar_t ) : 0;
        auto ptr = &data_[index * maxColumnDataSize_];

        WideString result( ( WideString::value_type* )ptr, length );
        return result;
    }

    void CStringArrayBind::Assign( size_t index, const WideString& newValue )
    {
        auto copyLength = std::min( static_cast<size_t>( newValue.length( ) ), ( maxColumnDataSize_ - 1 ) );
        auto ptr = &data_[index * maxColumnDataSize_];
        if ( copyLength )
        {
            wmemcpy( ptr, newValue.data( ), copyLength );
        }
        dataSizes_[index] = static_cast<UInt16>( ( copyLength + 1 ) * sizeof( wchar_t ) );
        indicator_[index] = 0;
        ptr[copyLength] = 0;
    }

    void CStringArrayBind::Assign( size_t index, const wchar_t* newValue )
    {
        auto length = wcslen( newValue );
        auto copyLength = std::min( static_cast<size_t>( length ), ( maxColumnDataSize_ - 1 ) );
        auto ptr = &data_[index * maxColumnDataSize_];
        if ( copyLength )
        {
            wmemcpy( ptr, newValue, copyLength );
        }
        dataSizes_[index] = static_cast<UInt16>( ( copyLength + 1 ) * sizeof( wchar_t ) );
        indicator_[index] = 0;
        ptr[copyLength] = 0;
    }

    Guid CStringArrayBind::AsGuid( size_t index ) const
    {
        auto s = AsString( index );
        return ConvertTo<Guid>( s );
    }
    void CStringArrayBind::Assign( size_t index, const Guid& newValue )
    {
        auto s = ConvertTo<WideString>( newValue.ToString( ) );
        Assign( index, s );
    }
}