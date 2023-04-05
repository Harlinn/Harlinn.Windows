#pragma once
#ifndef HARLINN_WINDOWS_HWFONTS_H_
#define HARLINN_WINDOWS_HWFONTS_H_

#include "HWHandles.h"

namespace Harlinn::Windows::Fonts
{
    class Font 
    {
        struct Data : public ENUMLOGFONTEXW
        { 
            using Base = ENUMLOGFONTEXW;
            Data()
                : Base{ }
            { }

            Data( const ENUMLOGFONTEXW& data )
                : Base( data )
            {
            }

            Data( const LOGFONTW& data )
                : Base( { data, } )
            {
            }
        };
        std::unique_ptr<Data> data_;
    public:
        constexpr Font( ) = default;

        Font( const ENUMLOGFONTEXW& data )
            : data_( new Data( data ) )
        { }

        Font( const LOGFONTW& data )
            : data_( new Data( data ) )
        { }

        Font( const Font& other ) = delete;
        Font& operator = ( const Font& other ) = delete;

        Font( Font&& other ) noexcept
            : data_( std::move( other.data_ ) )
        { }
        Font& operator = ( Font&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            return *this;
        }

        void swap( Font& other ) noexcept
        {
            std::swap( data_, other.data_ );
        }



    };

    class TypesFace
    {
        struct Data : public ENUMLOGFONTEXW
        {
            using Base = ENUMLOGFONTEXW;
            Data( )
                : Base{ }
            {
            }

            Data( const ENUMLOGFONTEXW& data )
                : Base( data )
            {
            }

            Data( const LOGFONTW& data )
                : Base( { data, } )
            {
            }
        };
        std::unique_ptr<Data> data_;
    public:
    public:
        constexpr TypesFace( ) = default;

        TypesFace( const ENUMLOGFONTEXW & data )
            : data_( new Data( data ) )
        {
        }

        TypesFace( const LOGFONTW & data )
            : data_( new Data( data ) )
        {
        }

        TypesFace( const TypesFace & other ) = delete;
        TypesFace& operator = ( const TypesFace & other ) = delete;

        TypesFace( TypesFace && other ) noexcept
            : data_( std::move( other.data_ ) )
        {
        }
        TypesFace& operator = ( TypesFace && other ) noexcept
        {
            std::swap( data_, other.data_ );
            return *this;
        }

        void swap( TypesFace & other ) noexcept
        {
            std::swap( data_, other.data_ );
        }
    };


    class TypeFaceList : public std::vector<TypesFace>
    {
    public:
        TypeFaceList( )
        {
            
        }
    };


}



#endif
