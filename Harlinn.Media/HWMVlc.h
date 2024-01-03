#pragma once
#ifndef HARLINN_MEDIA_HWMVLC_H_
#define HARLINN_MEDIA_HWMVLC_H_
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

#include "HWMVlcCommon.h"

namespace Harlinn::Media::Vlc
{
    using ExitHandler = void ( * ) ( void* userData );

    class ModuleDescription
    {
        WideString name_;
        WideString shortName_;
        WideString longName_;
        WideString help_;
    public:
        ModuleDescription( const WideString& name, const WideString& shortName, const WideString& longName, const WideString& help)
            : name_( name ), shortName_( shortName ), longName_( longName ), help_( help )
        { }

        HWM_EXPORT ModuleDescription( const AnsiString& name, const AnsiString& shortName, const AnsiString& longName, const AnsiString& help );
        HWM_EXPORT ModuleDescription( const char* name, const char* shortName, const char* longName, char* help );
        HWM_EXPORT ~ModuleDescription( );
    };


    class Arguments : public std::vector<WideString>
    {
    public:
        HWM_EXPORT Arguments( );
        HWM_EXPORT ~Arguments( );

        Arguments( const Arguments& ) = delete;
        Arguments& operator = ( const Arguments& ) = delete;

        HWM_EXPORT void ImportCommandLine( );
        HWM_EXPORT bool Contains( const WideString& str );
    };


    class Instance
    {
        libvlc_instance_t* instance_ = nullptr;
    public:
        Instance( ) = default;
        HWM_EXPORT Instance( int argc, const char* const* argv );
        HWM_EXPORT Instance( const std::vector<WideString>& args );
        HWM_EXPORT ~Instance( );

        HWM_EXPORT static Instance Create( );


        Instance( const Instance& other ) = delete;
        Instance& operator = ( const Instance& other ) = delete;

        Instance( Instance&& other ) noexcept
            : instance_( other.instance_ )
        {
            other.instance_ = nullptr;
        }
        Instance& operator = ( Instance&& other ) noexcept
        {
            std::swap( instance_, other.instance_ );
            return *this;
        }

        explicit operator bool( ) const noexcept
        {
            return instance_ != nullptr;
        }

        bool operator == ( nullptr_t ) const noexcept
        {
            return instance_ == nullptr;
        }
        bool operator != ( nullptr_t ) const noexcept
        {
            return instance_ != nullptr;
        }

        bool operator == ( libvlc_instance_t* instance ) const noexcept
        {
            return instance_ == instance;
        }
        bool operator != ( libvlc_instance_t* instance ) const noexcept
        {
            return instance_ != instance;
        }

        bool operator == ( const Instance& other ) const noexcept
        {
            return instance_ == other.instance_;
        }
        bool operator != ( const Instance& other ) const noexcept
        {
            return instance_ != other.instance_;
        }


        HWM_EXPORT int AddInterface( const char* name ) const;
        HWM_EXPORT void SetExitHandler( ExitHandler exitHandler, void* userData ) const;
        HWM_EXPORT void SetUserAgent( const char* name, const char* http ) const;
        HWM_EXPORT void SetApplicationId( const char* id, const char* version, const char* icon ) const;

        HWM_EXPORT static const char* Version( );
        HWM_EXPORT static const char* Compiler( );
        HWM_EXPORT static const char* ChangeSet( );
        HWM_EXPORT static void Free( void* ptr );

        HWM_EXPORT void Wait( ) const;
        HWM_EXPORT void PlayListPlay( int i_id, int i_options, char** ppsz_options ) const;


        HWM_EXPORT std::vector<ModuleDescription> AudioFilters( ) const;
        HWM_EXPORT std::vector<ModuleDescription> VideoFilters( ) const;


    };
}


#endif
