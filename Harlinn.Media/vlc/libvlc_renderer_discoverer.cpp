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
#include "LibVLCWrapper.h"

extern "C"
{
    LIBVLC_API libvlc_renderer_item_t* libvlc_renderer_item_hold( libvlc_renderer_item_t* p_item )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_renderer_item_hold( p_item );
    }
    LIBVLC_API void libvlc_renderer_item_release( libvlc_renderer_item_t* p_item )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_renderer_item_release( p_item );
    }
    LIBVLC_API const char* libvlc_renderer_item_name( const libvlc_renderer_item_t* p_item )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_renderer_item_name( p_item );
    }
    LIBVLC_API const char* libvlc_renderer_item_type( const libvlc_renderer_item_t* p_item )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_renderer_item_type( p_item );
    }
    LIBVLC_API const char* libvlc_renderer_item_icon_uri( const libvlc_renderer_item_t* p_item )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_renderer_item_icon_uri( p_item );
    }
    LIBVLC_API int libvlc_renderer_item_flags( const libvlc_renderer_item_t* p_item )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_renderer_item_flags( p_item );
    }
    LIBVLC_API libvlc_renderer_discoverer_t* libvlc_renderer_discoverer_new( libvlc_instance_t* p_inst, const char* psz_name )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_renderer_discoverer_new( p_inst, psz_name );
    }
    LIBVLC_API void libvlc_renderer_discoverer_release( libvlc_renderer_discoverer_t* p_rd )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_renderer_discoverer_release( p_rd );
    }
    LIBVLC_API int libvlc_renderer_discoverer_start( libvlc_renderer_discoverer_t* p_rd )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_renderer_discoverer_start( p_rd );
    }
    LIBVLC_API void libvlc_renderer_discoverer_stop( libvlc_renderer_discoverer_t* p_rd )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_renderer_discoverer_stop( p_rd );
    }
    LIBVLC_API libvlc_event_manager_t* libvlc_renderer_discoverer_event_manager( libvlc_renderer_discoverer_t* p_rd )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_renderer_discoverer_event_manager( p_rd );
    }
    LIBVLC_API size_t libvlc_renderer_discoverer_list_get( libvlc_instance_t* p_inst, libvlc_rd_description_t*** ppp_services )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_renderer_discoverer_list_get( p_inst, ppp_services );
    }
    LIBVLC_API void libvlc_renderer_discoverer_list_release( libvlc_rd_description_t** pp_services, size_t i_count )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_renderer_discoverer_list_release( pp_services, i_count );
    }
}