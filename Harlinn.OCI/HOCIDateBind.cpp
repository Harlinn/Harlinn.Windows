#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    void DateBind::Bind( UInt32 positon, UInt32 iters )
    {
        SimpleBindByPos( positon, OCI::OraType::ORA_OCIDate, &ocidate_, sizeof( ocidate_ ) );
    }

    void DateBind::Bind( const WideString& name, UInt32 iters )
    {
        SimpleBindByName( name, OCI::OraType::ORA_OCIDate, &ocidate_, sizeof( ocidate_ ) );
    }

    void* DateBind::Data( ) const
    {
        return (void*)&ocidate_;
    }

    void DateBind::GetTime( Byte& hour, Byte& minute, Byte& second ) const
    {
        ocidate_.GetTime( hour, minute, second );
    }
    void DateBind::SetTime( Byte hour, Byte minute, Byte second )
    {
        ocidate_.SetTime( hour, minute, second );
        SetDBNotNull( );
    }
    void DateBind::GetDate( short& year, Byte& month, Byte& day ) const
    {
        ocidate_.GetDate( year, month, day );
    }
    void DateBind::SetDate( short year, Byte month, Byte day )
    {
        ocidate_.SetDate( year, month, day );
        SetDBNotNull( );
    }

    void DateBind::GetDateTime( short& year, Byte& month, Byte& day, Byte& hour, Byte& minute, Byte& second ) const
    {
        ocidate_.GetDateTime( year, month, day, hour, minute, second );
    }
    void DateBind::SetDateTime( short year, Byte month, Byte day, Byte hour, Byte minute, Byte second )
    {
        ocidate_.SetDateTime( year, month, day, hour, minute, second );
        SetDBNotNull( );
    }

    long long DateBind::AsInt64( ) const
    {
        return ocidate_.Ticks( );
    }
    void DateBind::Assign( long long newValue )
    {
        ocidate_.SetTicks( newValue );
        SetDBNotNull( );
    }

    DateTime DateBind::AsDateTime( ) const
    {
        return ocidate_.ToDateTime( );
    }
    void DateBind::Assign( const DateTime& dt )
    {
        ocidate_.Assign( dt );
        SetDBNotNull( );
    }
    TimeSpan DateBind::AsTimeSpan( ) const
    {
        return TimeSpan( AsInt64( ) );
    }
    void DateBind::Assign( const TimeSpan& newValue )
    {
        Assign( newValue.Ticks( ) );
    }

    WideString DateBind::AsString( const WideString& format ) const
    {
        wchar_t buffer[64];
        UInt32 bufferSize = sizeof( buffer );
        auto& error = Error( );
        OCI::DateToText( error, &ocidate_, format.c_str( ), static_cast<Byte>( format.length( ) ), nullptr, 0, &bufferSize, buffer );
        WideString result( ( WideString::value_type* )buffer, static_cast<WideString::size_type>( bufferSize / sizeof( wchar_t ) ) );
        return result;
    }

    WideString DateBind::AsString( ) const
    {
        wchar_t buffer[32];
        UInt32 bufferSize = sizeof( buffer );
        static WideString fmt( L"YYYY/MM/DD HH24:MI:SS" );
        auto& error = Error( );
        OCI::DateToText( error, &ocidate_, fmt.c_str( ), static_cast<Byte>( fmt.length( ) ), nullptr, 0, &bufferSize, buffer );
        WideString result( ( WideString::value_type* )buffer, static_cast<WideString::size_type>( bufferSize / sizeof( wchar_t ) ) );
        return result;
    }

    void DateBind::Assign( const WideString& newValue )
    {
        static WideString fmt( HCC_TEXT( "YYYY/MM/DD HH24:MI:SS" ) );
        Assign( fmt, newValue );
    }
    void DateBind::Assign( const WideString& format, const WideString& newValue )
    {
        auto& error = Error( );
        OCI::DateFromText( error, newValue.c_str( ), static_cast<UInt32>( newValue.length( ) ),
            format.c_str( ), static_cast<Byte>( format.length( ) ), nullptr, 0, &ocidate_ );
        SetDBNotNull( );
    }


    Int32 DateBind::AsInt32( ) const
    {
        auto result = ( AsInt64( ) - DateTime::UnixEpoch ) / TimeSpan::TicksPerSecond;
        return static_cast<Int32>( result );
    }
    void DateBind::Assign( Int32 newValue )
    {
        auto value = ( static_cast<long long>( newValue ) + newValue ) * TimeSpan::TicksPerSecond;
        Assign( value );
    }
    UInt32 DateBind::AsUInt32( ) const
    {
        return static_cast<UInt32>( AsInt32( ) );
    }
    void DateBind::Assign( UInt32 newValue )
    {
        Assign( static_cast<Int32>( newValue ) );
    }
    UInt64 DateBind::AsUInt64( ) const
    {
        return static_cast<UInt64>( AsInt64( ) );
    }
    void DateBind::Assign( UInt64 newValue )
    {
        Assign( static_cast<long long>( newValue ) );
    }

    float DateBind::AsSingle( ) const
    {
        DateTime dt( AsInt64( ) );
        return static_cast<float>( dt.ToOADate( ) );
    }

    void DateBind::Assign( float newValue )
    {
        auto dt = DateTime::FromOADate( newValue );
        Assign( dt.Ticks( ) );
    }

    double DateBind::AsDouble( ) const
    {
        DateTime dt( AsInt64( ) );
        return dt.ToOADate( );
    }

    void DateBind::Assign( double newValue )
    {
        auto dt = DateTime::FromOADate( newValue );
        Assign( dt.Ticks( ) );
    }
}