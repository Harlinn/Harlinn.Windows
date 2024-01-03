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
    LIBVLC_API libvlc_media_discoverer_t* libvlc_media_discoverer_new( libvlc_instance_t* p_inst, const char* psz_name )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_discoverer_new( p_inst, psz_name );
    }
    LIBVLC_API int libvlc_media_discoverer_start( libvlc_media_discoverer_t* p_mdis )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_discoverer_start( p_mdis );
    }
    LIBVLC_API void libvlc_media_discoverer_stop( libvlc_media_discoverer_t* p_mdis )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_discoverer_stop( p_mdis );
    }
    LIBVLC_API void libvlc_media_discoverer_release( libvlc_media_discoverer_t* p_mdis )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_discoverer_release( p_mdis );
    }
    LIBVLC_API libvlc_media_list_t* libvlc_media_discoverer_media_list( libvlc_media_discoverer_t* p_mdis )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_discoverer_media_list( p_mdis );
    }
    LIBVLC_API int libvlc_media_discoverer_is_running( libvlc_media_discoverer_t* p_mdis )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_discoverer_is_running( p_mdis );
    }
    LIBVLC_API size_t libvlc_media_discoverer_list_get( libvlc_instance_t* p_inst, libvlc_media_discoverer_category_t i_cat, libvlc_media_discoverer_description_t*** ppp_services )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_discoverer_list_get( p_inst, i_cat, ppp_services );
    }
    LIBVLC_API void libvlc_media_discoverer_list_release( libvlc_media_discoverer_description_t** pp_services, size_t i_count )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_discoverer_list_release( pp_services, i_count );
    }
}