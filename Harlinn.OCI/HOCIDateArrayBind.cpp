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
    void DateArrayBind::Bind( UInt32 positon, UInt32 iters )
    {
        auto dataSize = data_.size( );
        actualSize_ = static_cast<UInt32>( dataSize );
        if ( indicator_.size( ) < dataSize )
        {
            indicator_.resize( dataSize );
        }
        if ( IsPlSQL( ) == false )
        {
            Base::BindByPos( positon, ExternalType, data_.data( ), sizeof( OCI::Date ), indicator_.data( ), nullptr, nullptr, 0, nullptr );
        }
        else
        {
            SimpleBindByPos( positon, ExternalType, data_.data( ), sizeof( OCI::Date ), actualSize_, &actualSize_ );
        }
    }

    void DateArrayBind::Bind( const WideString& name, UInt32 iters )
    {
        auto dataSize = data_.size( );
        actualSize_ = static_cast<UInt32>( dataSize );
        if ( indicator_.size( ) < dataSize )
        {
            indicator_.resize( dataSize );
        }
        if ( IsPlSQL( ) == false )
        {
            Base::BindByName( name, ExternalType, data_.data( ), sizeof( OCI::Date ), indicator_.data( ), nullptr, nullptr, 0, nullptr );
        }
        else
        {
            SimpleBindByName( name, ExternalType, data_.data( ), sizeof( OCI::Date ), actualSize_, &actualSize_ );
        }
    }

    void* DateArrayBind::Data( size_t index ) const
    {
        return (void*)std::addressof( data_[index] );
    }

    void DateArrayBind::GetTime( size_t index, Byte& hour, Byte& minute, Byte& second ) const
    {
        data_[index].GetTime( hour, minute, second );
    }
    void DateArrayBind::SetTime( size_t index, Byte hour, Byte minute, Byte second )
    {
        data_[index].SetTime( hour, minute, second );
    }
    void DateArrayBind::GetDate( size_t index, short& year, Byte& month, Byte& day ) const
    {
        data_[index].GetDate( year, month, day );
    }
    void DateArrayBind::SetDate( size_t index, short year, Byte month, Byte day )
    {
        data_[index].SetDate( year, month, day );
    }

    void DateArrayBind::GetDateTime( size_t index, short& year, Byte& month, Byte& day, Byte& hour, Byte& minute, Byte& second ) const
    {
        data_[index].GetDateTime( year, month, day, hour, minute, second );
    }
    void DateArrayBind::SetDateTime( size_t index, short year, Byte month, Byte day, Byte hour, Byte minute, Byte second )
    {
        data_[index].SetDateTime( year, month, day, hour, minute, second );
    }

    long long DateArrayBind::AsInt64( size_t index ) const
    {
        return data_[index].Ticks( );
    }
    void DateArrayBind::Assign( size_t index, long long newValue )
    {
        DateTime dt( newValue );
        data_[index].Assign( dt );
    }

    DateTime DateArrayBind::AsDateTime( size_t index ) const
    {
        return data_[index].ToDateTime( );
    }
    void DateArrayBind::Assign( size_t index, const DateTime& dt )
    {
        data_[index].Assign( dt );
    }

    TimeSpan DateArrayBind::AsTimeSpan( size_t index ) const
    {
        return TimeSpan( AsInt64( index ) );
    }
    void DateArrayBind::Assign( size_t index, const TimeSpan& newValue )
    {
        Assign( index, newValue.Ticks( ) );
    }

    WideString DateArrayBind::AsString( size_t index, const WideString& format ) const
    {
        wchar_t buffer[64];
        UInt32 bufferSize = sizeof(64);
        const OCIDate* ociDate = (OCIDate*)std::addressof( data_[index] );
        auto& error = Error( );
        OCI::DateToText( error, &data_[index], format.c_str( ), static_cast<Byte>( format.length( ) ), nullptr, 0, &bufferSize, buffer );
        WideString result( ( WideString::value_type* )buffer, static_cast<WideString::size_type>( bufferSize ) );
        return result;
    }

    WideString DateArrayBind::AsString( size_t index ) const
    {
        wchar_t buffer[32];
        UInt32 bufferSize = sizeof( buffer );
        static WideString fmt( HCC_TEXT( "YYYY/MM/DD HH24:MI:SS" ) );
        auto& error = Error( );
        OCI::DateToText( error, &data_[index], fmt.c_str( ), static_cast<Byte>( fmt.length( ) ), nullptr, 0, &bufferSize, buffer );
        WideString result( ( WideString::value_type* )buffer, static_cast<WideString::size_type>( bufferSize ) );
        return result;
    }

    void DateArrayBind::Assign( size_t index, const WideString& newValue )
    {
        static WideString fmt( HCC_TEXT( "YYYY/MM/DD HH24:MI:SS" ) );
        Assign( index, fmt, newValue );
    }
    void DateArrayBind::Assign( size_t index, const WideString& format, const WideString& newValue )
    {
        OCI::Date* ociDate = &data_[index];
        auto& error = Error( );
        OCI::DateFromText( error, newValue.c_str( ), static_cast<UInt32>( newValue.length( ) ),
            format.c_str( ), static_cast<Byte>( format.length( ) ), nullptr, 0, ociDate );
    }


    Int32 DateArrayBind::AsInt32( size_t index ) const
    {
        static auto ticks19700101 = DateTime::UnixEpoch;

        auto result = ( AsInt64( index ) - DateTime::UnixEpoch ) / TimeSpan::TicksPerSecond;
        return static_cast<Int32>( result );
    }
    void DateArrayBind::Assign( size_t index, Int32 newValue )
    {
        auto value = ( static_cast<long long>( newValue ) + newValue ) * TimeSpan::TicksPerSecond;
        Assign( index, value );
    }
    UInt32 DateArrayBind::AsUInt32( size_t index ) const
    {
        return static_cast<UInt32>( AsInt32( index ) );
    }
    void DateArrayBind::Assign( size_t index, UInt32 newValue )
    {
        Assign( index, static_cast<Int32>( newValue ) );
    }
    UInt64 DateArrayBind::AsUInt64( size_t index ) const
    {
        return static_cast<UInt64>( AsInt64( index ) );
    }
    void DateArrayBind::Assign( size_t index, UInt64 newValue )
    {
        Assign( index, static_cast<long long>( newValue ) );
    }

    float DateArrayBind::AsSingle( size_t index ) const
    {
        DateTime dt( AsInt64( index ) );
        return static_cast<float>( dt.ToOADate( ) );
    }

    void DateArrayBind::Assign( size_t index, float newValue )
    {
        auto dt = DateTime::FromOADate( newValue );
        Assign( index, dt.Ticks( ) );
    }

    double DateArrayBind::AsDouble( size_t index ) const
    {
        DateTime dt( AsInt64( index ) );
        return dt.ToOADate( );
    }

    void DateArrayBind::Assign( size_t index, double newValue )
    {
        auto dt = DateTime::FromOADate( newValue );
        Assign( index, dt.Ticks( ) );
    }
}