#pragma once 
#ifndef HARLINN_MEDIA_GLIB_GOBJECT_HWMGVALUE_H_
#define HARLINN_MEDIA_GLIB_GOBJECT_HWMGVALUE_H_

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

#include "HWMgforwards.h"
#include <glib/HWMgvariant.h>


namespace Harlinn::Media::GLib
{
    enum class ValueType
    {
        Invalid = G_TYPE_INVALID,
        None = G_TYPE_NONE,
        Interface = G_TYPE_INTERFACE,
        SByte = G_TYPE_CHAR,
        Byte = G_TYPE_UCHAR,
        Boolean = G_TYPE_BOOLEAN,
        Int32 = G_TYPE_INT,
        UInt32 = G_TYPE_UINT,
        Long = G_TYPE_LONG,
        ULong = G_TYPE_ULONG,
        Int64 = G_TYPE_INT64,
        UInt64 = G_TYPE_UINT64,
        Enum = G_TYPE_ENUM,
        Flags = G_TYPE_FLAGS,
        Single = G_TYPE_FLOAT,
        Double = G_TYPE_DOUBLE,
        String = G_TYPE_STRING,
        TypePointer = G_TYPE_POINTER,
        Boxed = G_TYPE_BOXED,
        Param = G_TYPE_PARAM,
        Object = G_TYPE_OBJECT,
        Variant = G_TYPE_VARIANT,

        Type
    };
    enum class StringType
    {
        Regular,
        Static,
        Interned
    };

    



    class Value : public GValue
    {
    public:
        using Base = GValue;

        Value( )
            : Base{}
        { }



        template<ValueType type>
        explicit Value( GType value )
            : Base{}
        {
            if constexpr ( type == ValueType::Type )
            {
                g_value_init( this, value );
            }
            else
            {
                g_value_init( this, G_TYPE_UINT64 );
                g_value_set_uint64( this, value );
            }
        }

        explicit Value( gpointer instance )
            : Base{}
        {
            g_value_init_from_instance( this, instance );
        }

        explicit Value( GType type, gpointer instance )
            : Base{}
        {
            g_value_init( this, type );
            g_value_set_instance( this, instance );
        }

        explicit Value( bool value )
            : Base{}
        {
            g_value_init( this, G_TYPE_BOOLEAN );
            g_value_set_boolean( this, static_cast< gboolean >( value ) );
        }

        explicit Value( char value )
            : Base{}
        {
            g_value_init( this, G_TYPE_CHAR );
            g_value_set_schar( this, value );
        }
        explicit Value( SByte value )
            : Base{}
        {
            g_value_init( this, G_TYPE_CHAR );
            g_value_set_schar( this, value );
        }
        explicit Value( Byte value )
            : Base{}
        {
            g_value_init( this, G_TYPE_UCHAR );
            g_value_set_uchar( this, value );
        }

        explicit Value( Int32 value )
            : Base{}
        {
            g_value_init( this, G_TYPE_INT );
            g_value_set_int( this, value );
        }
        explicit Value( UInt32 value )
            : Base{}
        {
            g_value_init( this, G_TYPE_UINT );
            g_value_set_uint( this, value );
        }

        explicit Value( glong value )
            : Base{}
        {
            g_value_init( this, G_TYPE_LONG );
            g_value_set_long( this, value );
        }

        explicit Value( gulong value )
            : Base{}
        {
            g_value_init( this, G_TYPE_ULONG );
            g_value_set_ulong( this, value );
        }

        explicit Value( Int64 value )
            : Base{}
        {
            g_value_init( this, G_TYPE_INT64 );
            g_value_set_int64( this, value );
        }
        explicit Value( UInt64 value )
            : Base{}
        {
            g_value_init( this, G_TYPE_UINT64 );
            g_value_set_uint64( this, value );
        }

        explicit Value( float value )
            : Base{}
        {
            g_value_init( this, G_TYPE_FLOAT );
            g_value_set_float( this, value );
        }

        explicit Value( double value )
            : Base{}
        {
            g_value_init( this, G_TYPE_DOUBLE );
            g_value_set_double( this, value );
        }

        explicit Value( const char* value, StringType stringType = StringType::Regular )
            : Base{}
        {
            g_value_init( this, G_TYPE_STRING );
            switch ( stringType )
            {
                case StringType::Regular:
                    g_value_set_string( this, value );
                    break;
                case StringType::Static:
                    g_value_set_static_string( this, value );
                    break;
                case StringType::Interned:
                    g_value_set_interned_string( this, value );
                    break;
            }
        }

        explicit Value( GObject* value, bool take = false )
            : Base{}
        {
            g_value_init( this, G_TYPE_OBJECT );
            if ( take == false )
            {
                g_value_set_object( this, value );
            }
            else
            {
                g_value_take_object( this, value );
            }
        }

        template<typename T>
            requires std::is_enum_v<T>  
        explicit Value( T value )
            : Base{}
        {
            g_value_init( this, G_TYPE_ENUM );
            g_value_set_enum( this, static_cast<gint>( value ) );
        }

        explicit Value( UInt32 value, bool flags )
            : Base{}
        {
            if ( flags )
            {
                g_value_init( this, G_TYPE_FLAGS );
                g_value_set_flags( this, value );
            }
            else
            {
                g_value_init( this, G_TYPE_UINT );
                g_value_set_uint( this, value );
            }
        }

        template<typename T>
            requires std::is_enum_v<T>
        explicit Value( T value, bool flags )
            : Base{}
        {
            if ( flags )
            {
                g_value_init( this, G_TYPE_FLAGS );
                g_value_set_flags( this, static_cast< guint >( value ) );
            }
            else
            {
                g_value_init( this, G_TYPE_ENUM );
                g_value_set_enum( this, static_cast< gint >( value ) );
            }
        }

        Value( const Value& other )
            : Base{}
        {
            g_value_init( this, other.g_type );
            g_value_copy( &other, this );
        }

        Value( Value&& other )
            : Base( other )
        {
            memset( &other, 0, sizeof( GValue ) );
        }


        ~Value( )
        {
            if ( IsInitialized( ) )
            {
                g_value_unset( this );
            }
        }

        bool IsInitialized( ) const noexcept
        {
            static const GValue empty{};
            return memcmp(static_cast<const GValue*>(this), &empty,sizeof( GValue )) != 0;
        }

        Value& operator = ( const Value& other )
        {
            g_value_copy( &other, this );
            return *this;
        }


        Value& operator = ( Value&& other ) noexcept
        {
            if ( &other != this )
            {
                memcpy( this, &other, sizeof( GValue ) );
                memset( &other, 0, sizeof( GValue ) );
            }
            return *this;
        }


        Value Clone( ) const
        {
            Value result;
            g_value_copy( this, &result );
            return result;
        }



        template<typename T>
        T As( ) const
        {
            static_assert( AlwaysFalse<T>::value, "Unsupported conversion" );
        }

        bool AsBoolean( ) const
        {
            return g_value_get_boolean( this );
        }
        template<>
        bool As<bool>( ) const
        {
            return AsBoolean( );
        }
        void SetBoolean( bool value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_BOOLEAN );
            }
            g_value_set_boolean( this, value );
        }
        Value& operator = ( bool value )
        {
            SetBoolean( value );
            return *this;
        }


        SByte AsSByte( ) const
        {
            return g_value_get_schar( this );
        }
        template<>
        SByte As<SByte>( ) const
        {
            return AsSByte( );
        }
        void SetSByte( SByte value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_CHAR );
            }
            g_value_set_schar( this, value );
        }
        Value& operator = ( SByte value )
        {
            SetSByte( value );
            return *this;
        }

        char AsChar( ) const
        {
            return g_value_get_schar( this );
        }
        template<>
        char As<char>( ) const
        {
            return AsChar( );
        }
        void SetChar( char value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_CHAR );
            }
            g_value_set_schar( this, value );
        }
        Value& operator = ( char value )
        {
            SetChar( value );
            return *this;
        }

        char AsByte( ) const
        {
            return g_value_get_uchar( this );
        }
        template<>
        Byte As<Byte>( ) const
        {
            return AsByte( );
        }
        void SetByte( Byte value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_UCHAR );
            }
            g_value_set_uchar( this, value );
        }
        Value& operator = ( Byte value )
        {
            SetByte( value );
            return *this;
        }


        Int16 AsInt16( ) const
        {
            return static_cast<Int16>( g_value_get_int( this ) );
        }
        template<>
        Int16 As<Int16>( ) const
        {
            return AsInt16( );
        }
        void SetInt16( Int16 value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_INT );
            }
            g_value_set_int( this, value );
        }
        Value& operator = ( Int16 value )
        {
            SetInt16( value );
            return *this;
        }

        UInt16 AsUInt16( ) const
        {
            return static_cast< UInt16 >( g_value_get_uint( this ) );
        }
        template<>
        UInt16 As<UInt16>( ) const
        {
            return AsUInt16( );
        }
        void SetUInt16( UInt16 value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_UINT );
            }
            g_value_set_int( this, value );
        }
        Value& operator = ( UInt16 value )
        {
            SetUInt16( value );
            return *this;
        }

        Int32 AsInt32( ) const
        {
            return g_value_get_int( this );
        }
        template<>
        Int32 As<Int32>( ) const
        {
            return AsInt32( );
        }
        void SetInt32( Int32 value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_INT );
            }
            g_value_set_int( this, value );
        }
        Value& operator = ( Int32 value )
        {
            SetInt32( value );
            return *this;
        }

        UInt32 AsUInt32( ) const
        {
            return g_value_get_uint( this );
        }
        template<>
        UInt32 As<UInt32>( ) const
        {
            return AsUInt32( );
        }
        void SetUInt32( UInt32 value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_UINT );
            }
            g_value_set_int( this, value );
        }
        Value& operator = ( UInt32 value )
        {
            SetUInt32( value );
            return *this;
        }


        Long32 AsLong( ) const
        {
            return g_value_get_long( this );
        }
        template<>
        Long32 As<Long32>( ) const
        {
            return AsLong( );
        }
        void SetLong( Long32 value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_LONG );
            }
            g_value_set_long( this, value );
        }
        Value& operator = ( Long32 value )
        {
            SetLong( value );
            return *this;
        }

        ULong32 AsULong( ) const
        {
            return g_value_get_ulong( this );
        }
        template<>
        ULong32 As<ULong32>( ) const
        {
            return AsULong( );
        }
        void SetULong( ULong32 value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_ULONG );
            }
            g_value_set_ulong( this, value );
        }
        Value& operator = ( ULong32 value )
        {
            SetLong( value );
            return *this;
        }
        
        Int64 AsInt64( ) const
        {
            return g_value_get_int64( this );
        }
        template<>
        Int64 As<Int64>( ) const
        {
            return AsInt64( );
        }
        void SetInt64( Int64 value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_INT64 );
            }
            g_value_set_int64( this, value );
        }
        Value& operator = ( Int64 value )
        {
            SetInt64( value );
            return *this;
        }

        UInt64 AsUInt64( ) const
        {
            return g_value_get_uint64( this );
        }
        template<>
        UInt64 As<UInt64>( ) const
        {
            return AsUInt64( );
        }
        void SetUInt64( UInt64 value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_UINT64 );
            }
            g_value_set_int64( this, value );
        }
        Value& operator = ( UInt64 value )
        {
            SetUInt64( value );
            return *this;
        }

        float AsSingle( ) const
        {
            return g_value_get_float( this );
        }
        template<>
        float As<float>( ) const
        {
            return AsSingle( );
        }
        void SetSingle( float value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_FLOAT );
            }
            g_value_set_float( this, value );
        }
        Value& operator = ( float value )
        {
            SetSingle( value );
            return *this;
        }

        double AsDouble( ) const
        {
            return g_value_get_double( this );
        }
        template<>
        double As<double>( ) const
        {
            return AsDouble( );
        }
        void SetDouble( double value )
        {
            if ( IsInitialized( ) == false )
            {
                g_value_init( this, G_TYPE_DOUBLE );
            }
            g_value_set_double( this, value );
        }
        Value& operator = ( double value )
        {
            SetDouble( value );
            return *this;
        }



    };

    static_assert( sizeof( Value ) == sizeof( GValue ) );


}

#endif
