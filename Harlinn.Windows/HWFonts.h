#pragma once
#ifndef HARLINN_WINDOWS_HWFONTS_H_
#define HARLINN_WINDOWS_HWFONTS_H_
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
