#pragma once
#ifndef HARLINN_MEDIA_GLIB_HWMGSTRING_H_
#define HARLINN_MEDIA_GLIB_HWMGSTRING_H_
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

#include "HWMgtraits.h"

namespace Harlinn::Media::GLib
{
    class StringPtr
    {
        char* data_ = nullptr;
    public:
        using value_type = char;
        StringPtr( ) = default;
        StringPtr( const StringPtr& other ) = delete;
        StringPtr( StringPtr&& other ) noexcept
            : data_( other.data_ )
        {
            other.data_ = nullptr;
        }
        /// <summary>
        /// StringPtr takes ownership of the argument and ensures that
        /// it will be freed using g_free
        /// </summary>
        /// <param name="data"></param>
        explicit StringPtr( char* data )
            : data_( data )
        { }

        ~StringPtr( )
        {
            g_free( data_ );
        }
        
        StringPtr& operator = ( const StringPtr& other ) = delete;
        StringPtr& operator = ( StringPtr&& other ) noexcept
        {
            std::swap(data_, other.data_);
            return *this;
        }

        StringPtr& operator = ( char* str )
        {
            if ( data_ != str )
            {
                if ( data_ )
                {
                    g_free( data_ );
                }
                data_ = str;
            }
            return *this;
        }

        char* data( )
        {
            return data_;
        }
        const char* data( ) const
        {
            return data_;
        }

        const char* c_str( ) const
        {
            if ( data_ )
            {
                return data_;
            }
            else
            {
                static const char* empty = "";
                return empty;
            }
        }

        size_t size( ) const
        {
            if ( data_ )
            {
                return strlen( data_ );
            }
            return 0;
        }
        size_t length( ) const
        {
            return size( );
        }

        char* Detach( )
        {
            auto tmp = data_;
            data_ = nullptr;
            return tmp;
        }
    };

    class String
    {
        GString* data_ = nullptr;
    public:
        String( ) = default;
        ~String( )
        {
            if ( data_ )
            {
                g_string_free( data_, true );
            }
        }

        explicit String( GString* data )
            : data_( data )
        { }

        explicit String( const char* init )
            : data_( g_string_new( init ) )
        { }

        explicit String( const char* init, gssize length )
            : data_( g_string_new_len( init, length ) )
        {
        }

        explicit String( const AnsiString& string )
            : data_( g_string_new_len( string.data(), static_cast< ssize_t >( string.length( ) ) ) )
        {
        }

        explicit String( const std::string& string )
            : data_( g_string_new_len( string.data( ), static_cast< ssize_t >( string.length( ) ) ) )
        {
        }

        explicit String( const std::string_view& string )
            : data_( g_string_new_len( string.data( ), static_cast< ssize_t >( string.length( ) ) ) )
        {
        }

        String( const String& other ) = delete;
        String( String&& other ) noexcept
            : data_( other.data_ )
        {
            other.data_ = nullptr;
        }

        String& operator = ( const String& other ) = delete;
        String& operator = ( String&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            return *this;
        }

        void Assign( const char* string )
        {
            if ( data_ )
            {
                if ( string )
                {
                    if ( data_->str != string )
                    {
                        g_string_assign( data_, string );
                    }
                }
                else
                {
                    auto tmp = data_;
                    data_ = nullptr;
                    g_string_free( tmp, true );
                }
            }
            else if ( string )
            {
                data_ = g_string_new( string );
            }
        }

        void Assign( GString* string )
        {
            if ( data_ != string )
            {
                if ( data_ )
                {
                    g_string_free( data_, true );
                }
                data_ = string;
            }
        }

        void Assign( const AnsiString& string )
        {
            if ( data_ )
            {
                g_string_free( data_, true );
            }
            data_ = g_string_new_len( string.c_str(), static_cast<ssize_t>( string.length() ) );
        }
        void Assign( const std::string& string )
        {
            if ( data_ )
            {
                g_string_free( data_, true );
            }
            data_ = g_string_new_len( string.c_str( ), static_cast< ssize_t >( string.length( ) ) );
        }
        void Assign( const std::string_view& string )
        {
            if ( data_ )
            {
                g_string_free( data_, true );
            }
            data_ = g_string_new_len( string.data( ), static_cast< ssize_t >( string.length( ) ) );
        }


        String& operator = ( const char* string )
        {
            Assign( string );
            return *this;
        }
        String& operator = ( GString* string )
        {
            Assign( string );
            return *this;
        }

        String& operator = ( const AnsiString& string )
        {
            Assign( string );
            return *this;
        }
        String& operator = ( const std::string& string )
        {
            Assign( string );
            return *this;
        }
        String& operator = ( const std::string_view& string )
        {
            Assign( string );
            return *this;
        }

        String& operator = ( nullptr_t )
        {
            if ( data_ )
            {
                g_string_free( data_, true );
                data_ = nullptr;
            }
            return *this;
        }


        bool empty( )
        {
            return data_ ? data_->len == 0 : true;
        }

        explicit operator bool( ) const
        {
            return data_ != nullptr;
        }

        bool operator == ( nullptr_t ) const
        {
            return data_ == nullptr;
        }

    private:
        static bool AreEqual( const GString* first, const GString* second )
        {
            if ( first != second )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return g_string_equal( first, second ) != 0;
                    }
                    return false;
                }
                else if ( second )
                {
                    return false;
                }
            }
            return true;
        }
    public:

        bool operator == ( const GString* other ) const
        {
            return AreEqual( data_, other );
        }
        bool operator == ( const String& other ) const
        {
            return AreEqual( data_, other.data_ );
        }
        bool operator != ( const GString* other ) const
        {
            return AreEqual( data_, other ) == false;
        }
        bool operator != ( const String& other ) const
        {
            return AreEqual( data_, other.data_ ) == false;
        }

        static String Take( char* init )
        {
            GString* string;

            if ( init == nullptr )
            {
                return String( g_string_new( nullptr ) );
            }

            string = g_slice_new( GString );

            string->str = init;
            string->len = strlen( string->str );
            string->allocated_len = string->len + 1;

            return String( string );
        }

        static String Take( StringPtr&& init )
        {
            return Take( init.Detach( ) );
        }

        GString* Detach( )
        {
            auto tmp = data_;
            data_ = nullptr;
            return tmp;
        }
        StringPtr DetachToStringPtr( )
        {
            auto tmp = data_;
            data_ = nullptr;
            if ( tmp )
            {
                StringPtr result( tmp->str );
                g_slice_free( GString, tmp );
                return result;
            }
            return {};
        }

        size_t size( ) const
        {
            return data_ ? data_->len : 0;
        }
        size_t length( ) const
        {
            return data_ ? data_->len : 0;
        }

        const char* c_str( ) const
        {
            if ( data_ )
            {
                return data_->str;
            }
            else
            {
                static const char* empty = "";
                return empty;
            }
        }

        char* data( )
        {
            if ( data_ )
            {
                return data_->str;
            }
            return nullptr;
        }
        const char* data( ) const
        {
            if ( data_ )
            {
                return data_->str;
            }
            return nullptr;
        }

        size_t capacity( ) const
        {
            return data_ ? (data_->allocated_len - 1) : 0;
        }

        size_t resize( size_t newSize )
        {
            if ( data_ )
            {
                g_string_set_size( data_, newSize );
            }
            else
            {
                data_ = g_string_sized_new( newSize );
                data_->len = newSize;
                data_->str[ newSize ] = '\x0';
            }
        }


        UInt32 Hash( ) const
        {
            return data_ ? g_string_hash( data_ ) : 0;
        }

        void Truncate( size_t newSize )
        {
            if ( data_ )
            {
                g_string_truncate( data_, newSize );
            }
            else
            {
                data_ = g_string_new( nullptr );
            }
        }

    };


}

inline std::string to_string( const Harlinn::Media::GLib::StringPtr& stringPtr )
{
    return std::string( stringPtr.c_str( ) );
}

namespace Harlinn::Common::Core
{
    inline AnsiString ToAnsiString( const Harlinn::Media::GLib::StringPtr& stringPtr )
    {
        return AnsiString( stringPtr.c_str( ) );
    }
    inline WideString ToWideString( const Harlinn::Media::GLib::StringPtr& stringPtr )
    {
        return ToWideString( stringPtr.c_str( ) );
    }
}



#endif
