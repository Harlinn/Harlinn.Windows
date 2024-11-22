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
    StringBind::~StringBind( )
    {
        if ( string_ )
        {
            auto& environment = Environment( );
            auto environmentHandle = (OCIEnv*)environment.Handle( );
            OCIStringResize( environmentHandle, nullptr, 0, &string_ );
        }
    }



    void StringBind::Bind( UInt32 positon, UInt32 iters )
    {
        if ( !string_ )
        {
            auto& error = Error( );
            auto errorHandle = (OCIError*)error.Handle( );
            auto& environment = Environment( );
            auto environmentHandle = (OCIEnv*)environment.Handle( );
            auto rc = OCIStringResize( environmentHandle, errorHandle, 256, &string_ );
            error.CheckResult( rc );
        }
        SimpleBindByPos( positon, ExternalType, &string_, sizeof( string_ ) );
    }
    void StringBind::Bind( const WideString& name, UInt32 iters )
    {
        SimpleBindByName( name, ExternalType, &string_, sizeof( string_ ) );
    }
    void* StringBind::Data( ) const
    {
        return (void*)string_;
    }
    bool StringBind::AsBoolean( ) const
    {
        auto s = AsString( );
        return ConvertTo<bool>( s );
    }
    void StringBind::Assign( bool newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( s );
    }
    Byte StringBind::AsByte( ) const
    {
        auto s = AsString( );
        return ConvertTo<Byte>( s );
    }
    void StringBind::Assign( Byte newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( s );
    }
    SByte StringBind::AsSByte( ) const
    {
        auto s = AsString( );
        return ConvertTo<SByte>( s );
    }
    void StringBind::Assign( SByte newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( s );
    }
    short StringBind::AsInt16( ) const
    {
        auto s = AsString( );
        return ConvertTo<Int16>( s );
    }
    void StringBind::Assign( short newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( s );
    }
    UInt16 StringBind::AsUInt16( ) const
    {
        auto s = AsString( );
        return ConvertTo<UInt16>( s );
    }
    void StringBind::Assign( UInt16 newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( s );
    }
    Int32 StringBind::AsInt32( ) const
    {
        auto s = AsString( );
        return ConvertTo<Int32>( s );
    }
    void StringBind::Assign( Int32 newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( s );
    }
    UInt32 StringBind::AsUInt32( ) const
    {
        auto s = AsString( );
        return ConvertTo<UInt32>( s );
    }
    void StringBind::Assign( UInt32 newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( s );
    }
    long long StringBind::AsInt64( ) const
    {
        auto s = AsString( );
        return ConvertTo<Int64>( s );
    }
    void StringBind::Assign( long long newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( s );
    }
    UInt64 StringBind::AsUInt64( ) const
    {
        auto s = AsString( );
        return ConvertTo<UInt64>( s );
    }
    void StringBind::Assign( UInt64 newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( s );
    }
    float StringBind::AsSingle( ) const
    {
        auto s = AsString( );
        return ConvertTo<Single>( s );
    }
    void StringBind::Assign( float newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( s );
    }
    double StringBind::AsDouble( ) const
    {
        auto s = AsString( );
        return ConvertTo<Double>( s );
    }
    void StringBind::Assign( double newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( s );
    }

    DateTime StringBind::AsDateTime( ) const
    {
        auto s = AsString( );
        return ConvertTo<DateTime>( s );
    }

    void StringBind::Assign( const DateTime& newValue )
    {
        auto s = ConvertTo<WideString>( newValue );
        Assign( s );
    }

    TimeSpan StringBind::AsTimeSpan( ) const
    {
        auto s = AsString( );
        return ConvertTo<TimeSpan>( s );
    }

    void StringBind::Assign( const TimeSpan& newValue )
    {
        auto s = ConvertTo<WideString>( newValue.Ticks( ) );
        Assign( s );
    }


    WideString StringBind::AsString( ) const
    {
        if ( indicator_ != -1 )
        {
            if ( string_ )
            {
                auto& environment = Environment( );
                auto environmentHandle = (OCIEnv*)environment.Handle( );
                auto byteCount = OCIStringSize( environmentHandle, string_ );
                wchar_t* ptr = (wchar_t*)OCIStringPtr( environmentHandle, string_ );
                return WideString( ptr, static_cast<size_t>( byteCount / sizeof( wchar_t ) ) );
            }
        }

        return WideString( );
    }

    void StringBind::Assign( const WideString& newValue )
    {
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto& environment = Environment( );
        auto environmentHandle = (OCIEnv*)environment.Handle( );

        auto newLength = newValue.length( );
        if ( newLength == 0 )
        {
            if ( string_ )
            {
                auto rc = OCIStringResize( environmentHandle, errorHandle, 0, &string_ );
                error.CheckResult( rc );
                string_ = nullptr;
            }
            indicator_ = -1;
        }
        else
        {
            auto newByteLength = static_cast<UInt32>( newLength * sizeof( wchar_t ) );
            auto rc = OCIStringResize( environmentHandle, errorHandle, newByteLength, &string_ );
            error.CheckResult( rc );
            wchar_t* ptr = (wchar_t*)OCIStringPtr( environmentHandle, string_ );
            memcpy( ptr, newValue.c_str( ), newByteLength );
        }
    }
    Guid StringBind::AsGuid( ) const
    {
        auto s = AsString( );
        return ConvertTo<Guid>( s );
    }
    void StringBind::Assign( const Guid& newValue )
    {
        auto s = ConvertTo<WideString>( newValue.ToWideString( ) );
        Assign( s );
    }
}