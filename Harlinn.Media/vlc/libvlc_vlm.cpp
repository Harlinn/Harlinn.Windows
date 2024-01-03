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
    LIBVLC_API void libvlc_vlm_release( libvlc_instance_t* p_instance )
    {
        LibVLC::Instance( )->libvlc_vlm_release( p_instance );
    }
    LIBVLC_API int libvlc_vlm_add_broadcast( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input, const char* psz_output, int i_options, const char* const* ppsz_options, int b_enabled, int b_loop )
    {
        return LibVLC::Instance( )->libvlc_vlm_add_broadcast( p_instance, psz_name, psz_input, psz_output, i_options, ppsz_options, b_enabled, b_loop );
    }
    LIBVLC_API int libvlc_vlm_add_vod( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input, int i_options, const char* const* ppsz_options, int b_enabled, const char* psz_mux )
    {
        return LibVLC::Instance( )->libvlc_vlm_add_vod( p_instance, psz_name, psz_input, i_options, ppsz_options, b_enabled, psz_mux );
    }
    LIBVLC_API int libvlc_vlm_del_media( libvlc_instance_t* p_instance, const char* psz_name )
    {
        return LibVLC::Instance( )->libvlc_vlm_del_media( p_instance, psz_name );
    }
    LIBVLC_API int libvlc_vlm_set_enabled( libvlc_instance_t* p_instance, const char* psz_name, int b_enabled )
    {
        return LibVLC::Instance( )->libvlc_vlm_set_enabled( p_instance, psz_name, b_enabled );
    }
    LIBVLC_API int libvlc_vlm_set_output( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_output )
    {
        return LibVLC::Instance( )->libvlc_vlm_set_output( p_instance, psz_name, psz_output );
    }
    LIBVLC_API int libvlc_vlm_set_input( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input )
    {
        return LibVLC::Instance( )->libvlc_vlm_set_input( p_instance, psz_name, psz_input );
    }
    LIBVLC_API int libvlc_vlm_add_input( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input )
    {
        return LibVLC::Instance( )->libvlc_vlm_add_input( p_instance, psz_name, psz_input );
    }
    LIBVLC_API int libvlc_vlm_set_loop( libvlc_instance_t* p_instance, const char* psz_name, int b_loop )
    {
        return LibVLC::Instance( )->libvlc_vlm_set_loop( p_instance, psz_name, b_loop );
    }
    LIBVLC_API int libvlc_vlm_set_mux( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_mux )
    {
        return LibVLC::Instance( )->libvlc_vlm_set_mux( p_instance, psz_name, psz_mux );
    }
    LIBVLC_API int libvlc_vlm_change_media( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input, const char* psz_output, int i_options, const char* const* ppsz_options, int b_enabled, int b_loop )
    {
        return LibVLC::Instance( )->libvlc_vlm_change_media( p_instance, psz_name, psz_input, psz_output, i_options, ppsz_options, b_enabled, b_loop );
    }
    LIBVLC_API int libvlc_vlm_play_media( libvlc_instance_t* p_instance, const char* psz_name )
    {
        return LibVLC::Instance( )->libvlc_vlm_play_media( p_instance, psz_name );
    }
    LIBVLC_API int libvlc_vlm_stop_media( libvlc_instance_t* p_instance, const char* psz_name )
    {
        return LibVLC::Instance( )->libvlc_vlm_stop_media( p_instance, psz_name );
    }
    LIBVLC_API int libvlc_vlm_pause_media( libvlc_instance_t* p_instance, const char* psz_name )
    {
        return LibVLC::Instance( )->libvlc_vlm_pause_media( p_instance, psz_name );
    }
    LIBVLC_API int libvlc_vlm_seek_media( libvlc_instance_t* p_instance, const char* psz_name, float f_percentage )
    {
        return LibVLC::Instance( )->libvlc_vlm_seek_media( p_instance, psz_name, f_percentage );
    }
    LIBVLC_API const char* libvlc_vlm_show_media( libvlc_instance_t* p_instance, const char* psz_name )
    {
        return LibVLC::Instance( )->libvlc_vlm_show_media( p_instance, psz_name );
    }
    LIBVLC_API float libvlc_vlm_get_media_instance_position( libvlc_instance_t* p_instance, const char* psz_name, int i_instance )
    {
        return LibVLC::Instance( )->libvlc_vlm_get_media_instance_position( p_instance, psz_name, i_instance );
    }
    LIBVLC_API int libvlc_vlm_get_media_instance_time( libvlc_instance_t* p_instance, const char* psz_name, int i_instance )
    {
        return LibVLC::Instance( )->libvlc_vlm_get_media_instance_time( p_instance, psz_name, i_instance );
    }
    LIBVLC_API int libvlc_vlm_get_media_instance_length( libvlc_instance_t* p_instance, const char* psz_name, int i_instance )
    {
        return LibVLC::Instance( )->libvlc_vlm_get_media_instance_length( p_instance, psz_name, i_instance );
    }
    LIBVLC_API int libvlc_vlm_get_media_instance_rate( libvlc_instance_t* p_instance, const char* psz_name, int i_instance )
    {
        return LibVLC::Instance( )->libvlc_vlm_get_media_instance_rate( p_instance, psz_name, i_instance );
    }
    LIBVLC_API libvlc_event_manager_t* libvlc_vlm_get_event_manager( libvlc_instance_t* p_instance )
    {
        return LibVLC::Instance( )->libvlc_vlm_get_event_manager( p_instance );
    }
}