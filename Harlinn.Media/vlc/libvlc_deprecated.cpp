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
    LIBVLC_API float libvlc_media_player_get_fps( libvlc_media_player_t* p_mi )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_media_player_get_fps( p_mi );
    }
    LIBVLC_API void libvlc_media_player_set_agl( libvlc_media_player_t* p_mi, uint32_t drawable )
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_media_player_set_agl( p_mi, drawable );
    }
    LIBVLC_API uint32_t libvlc_media_player_get_agl( libvlc_media_player_t* p_mi )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_media_player_get_agl( p_mi );
    }
    LIBVLC_API void libvlc_track_description_release( libvlc_track_description_t* p_track_description )
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_track_description_release( p_track_description );
    }
    LIBVLC_API int libvlc_video_get_height( libvlc_media_player_t* p_mi )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_video_get_height( p_mi );
    }
    LIBVLC_API int libvlc_video_get_width( libvlc_media_player_t* p_mi )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_video_get_width( p_mi );
    }
    LIBVLC_API libvlc_track_description_t* libvlc_video_get_title_description( libvlc_media_player_t* p_mi )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_video_get_title_description( p_mi );
    }
    LIBVLC_API libvlc_track_description_t* libvlc_video_get_chapter_description( libvlc_media_player_t* p_mi, int i_title )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_video_get_chapter_description( p_mi, i_title );
    }
    LIBVLC_API int libvlc_video_set_subtitle_file( libvlc_media_player_t* p_mi, const char* psz_subtitle )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_video_set_subtitle_file( p_mi, psz_subtitle );
    }
    LIBVLC_API void libvlc_toggle_teletext( libvlc_media_player_t* p_mi )
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_toggle_teletext( p_mi );
    }
    LIBVLC_API int libvlc_audio_output_device_count( libvlc_instance_t* p_instance, const char* psz_audio_output )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_audio_output_device_count( p_instance, psz_audio_output );
    }
    LIBVLC_API char* libvlc_audio_output_device_longname( libvlc_instance_t* p_instance, const char* psz_output, int i_device )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_audio_output_device_longname( p_instance, psz_output, i_device );
    }
    LIBVLC_API char* libvlc_audio_output_device_id( libvlc_instance_t* p_instance, const char* psz_audio_output, int i_device )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_audio_output_device_id( p_instance, psz_audio_output, i_device );
    }
    LIBVLC_API int libvlc_audio_output_get_device_type( libvlc_media_player_t* p_mi )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_audio_output_get_device_type( p_mi );
    }
    LIBVLC_API void libvlc_audio_output_set_device_type( libvlc_media_player_t* p_mp, int device_type )
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_audio_output_set_device_type( p_mp, device_type );
    }
    LIBVLC_API void libvlc_media_parse( libvlc_media_t* p_md )
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_media_parse( p_md );
    }
    LIBVLC_API void libvlc_media_parse_async( libvlc_media_t* p_md )
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_media_parse_async( p_md );
    }
    LIBVLC_API int libvlc_media_is_parsed( libvlc_media_t* p_md )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_media_is_parsed( p_md );
    }
    LIBVLC_API int libvlc_media_get_tracks_info( libvlc_media_t* p_md, libvlc_media_track_info_t** tracks )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_media_get_tracks_info( p_md, tracks );
    }
    LIBVLC_API libvlc_media_discoverer_t* libvlc_media_discoverer_new_from_name( libvlc_instance_t* p_inst, const char* psz_name )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_media_discoverer_new_from_name( p_inst, psz_name );
    }
    LIBVLC_API char* libvlc_media_discoverer_localized_name( libvlc_media_discoverer_t* p_mdis )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_media_discoverer_localized_name( p_mdis );
    }
    LIBVLC_API libvlc_event_manager_t* libvlc_media_discoverer_event_manager( libvlc_media_discoverer_t* p_mdis )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_media_discoverer_event_manager( p_mdis );
    }
    LIBVLC_API void libvlc_wait( libvlc_instance_t* p_instance )
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_wait( p_instance );
    }
    LIBVLC_API unsigned libvlc_get_log_verbosity( const libvlc_instance_t* p_instance )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_get_log_verbosity( p_instance );
    }
    LIBVLC_API void libvlc_set_log_verbosity( libvlc_instance_t* p_instance, unsigned level )
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_set_log_verbosity( p_instance, level );
    }
    LIBVLC_API libvlc_log_t* libvlc_log_open( libvlc_instance_t* p_instance )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_log_open( p_instance );
    }
    LIBVLC_API void libvlc_log_close( libvlc_log_t* p_log )
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_log_close( p_log );
    }
    LIBVLC_API unsigned libvlc_log_count( const libvlc_log_t* p_log )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_log_count( p_log );
    }
    LIBVLC_API void libvlc_log_clear( libvlc_log_t* p_log )
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_log_clear( p_log );
    }
    LIBVLC_API libvlc_log_iterator_t* libvlc_log_get_iterator( const libvlc_log_t* p_log )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_log_get_iterator( p_log );
    }
    LIBVLC_API void libvlc_log_iterator_free( libvlc_log_iterator_t* p_iter )
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_log_iterator_free( p_iter );
    }
    LIBVLC_API int libvlc_log_iterator_has_next( const libvlc_log_iterator_t* p_iter )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_log_iterator_has_next( p_iter );
    }
    LIBVLC_API libvlc_log_message_t* libvlc_log_iterator_next( libvlc_log_iterator_t* p_iter, libvlc_log_message_t* p_buf )
    {
        auto libVlc = LibVLC::Instance( );
        return libVlc->libvlc_log_iterator_next( p_iter, p_buf );
    }
    LIBVLC_API void libvlc_playlist_play( libvlc_instance_t* p_instance, int i_id, int i_options, char** ppsz_options )
    {
        auto libVlc = LibVLC::Instance( );
        libVlc->libvlc_playlist_play( p_instance, i_id, i_options, ppsz_options );
    }

}