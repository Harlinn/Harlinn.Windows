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
#include "HWMVlc.h"
#include "vlc/LibVLCWrapper.h"

namespace Harlinn::Media::Vlc
{
    // ModuleDescription
    HWM_EXPORT ModuleDescription::ModuleDescription( const AnsiString& name, const AnsiString& shortName, const AnsiString& longName, const AnsiString& help )
        : name_( ToWideString(name) ), shortName_( ToWideString( shortName ) ), longName_( ToWideString( longName ) ), help_( ToWideString( help ) )
    {
    }

    HWM_EXPORT ModuleDescription::ModuleDescription( const char* name, const char* shortName, const char* longName, char* help )
        : name_( ToWideString( name ) ), shortName_( ToWideString( shortName ) ), longName_( ToWideString( longName ) ), help_( ToWideString( help ) )
    {

    }

    HWM_EXPORT ModuleDescription::~ModuleDescription( )
    {

    }

    // Instance
    HWM_EXPORT Instance::Instance( int argc, const char* const* argv )
    {
        auto libVlc = LibVLC::Instance( );
        instance_ = libVlc->libvlc_new( argc, argv );
    }

    HWM_EXPORT Instance::Instance( const std::vector<WideString>& args )
    {
        std::vector<AnsiString> argsa;
        for ( const auto& arg : args )
        {
            argsa.push_back( ToAnsiString( arg ) );
        }
        std::vector<const char*> argsp;
        for ( const auto& arg : argsa )
        {
            argsp.push_back( arg.c_str() );
        }
        argsp.push_back( nullptr );
        int argc = static_cast< int >( argsp.size() ) - 1;
        const char** argv = argsp.data( );

        auto libVlc = LibVLC::Instance( );
        instance_ = libVlc->libvlc_new( argc, argv );
    }


    HWM_EXPORT Instance::~Instance( )
    {
        if ( instance_ )
        {
            auto libVlc = LibVLC::Instance( );
            auto tmp = instance_;
            instance_ = nullptr;
            libVlc->libvlc_release( tmp );
        }
    }

    HWM_EXPORT Instance Instance::Create( )
    {
        return Instance(0,nullptr);
    }

    HWM_EXPORT int Instance::AddInterface( const char* name ) const
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_add_intf( instance_, name );
    }

    HWM_EXPORT void Instance::SetExitHandler( ExitHandler exitHandler, void* userData ) const
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_set_exit_handler( instance_, exitHandler, userData );
    }

    HWM_EXPORT void Instance::SetUserAgent( const char* name, const char* http ) const
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_set_user_agent( instance_, name, http );
    }

    HWM_EXPORT void Instance::SetApplicationId( const char* id, const char* version, const char* icon ) const
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_set_app_id( instance_, id, version, icon );
    }

    HWM_EXPORT const char* Instance::Version( )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_get_version( );
    }

    HWM_EXPORT const char* Instance::Compiler( )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_get_compiler( );
    }

    HWM_EXPORT const char* Instance::ChangeSet( )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_get_changeset( );
    }

    HWM_EXPORT void Instance::Free( void* ptr )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_free( ptr );
    }

    HWM_EXPORT void Instance::Wait( ) const
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_wait( instance_ );
    }
    HWM_EXPORT void Instance::PlayListPlay( int i_id, int i_options, char** ppsz_options ) const
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_playlist_play( instance_, i_id, i_options, ppsz_options );
    }

    HWM_EXPORT std::vector<ModuleDescription> Instance::AudioFilters( ) const
    {
        std::vector<ModuleDescription> result;
        auto libVlc = LibVLC::Instance( );
        auto filters = libVlc->libvlc_audio_filter_list_get( instance_ );
        if ( filters )
        {
            auto filter = filters;
            do
            {
                result.emplace_back( filter->psz_name, filter->psz_shortname, filter->psz_longname, filter->psz_help );
                filter = filter->p_next;
            } while ( filter );
            libVlc->libvlc_module_description_list_release( filters );
        }
        return result;
    }
    HWM_EXPORT std::vector<ModuleDescription> Instance::VideoFilters( ) const
    {
        std::vector<ModuleDescription> result;
        auto libVlc = LibVLC::Instance( );
        auto filters = libVlc->libvlc_video_filter_list_get( instance_ );
        if ( filters )
        {
            auto filter = filters;
            do
            {
                result.emplace_back( filter->psz_name, filter->psz_shortname, filter->psz_longname, filter->psz_help );
                filter = filter->p_next;
            } while ( filter );
            libVlc->libvlc_module_description_list_release( filters );
        }
        return result;
    }

    
}