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
    LIBVLC_API libvlc_media_t* libvlc_media_new_location( libvlc_instance_t* p_instance, const char* psz_mrl )
    {
        return LibVLC::Instance( )->libvlc_media_new_location( p_instance, psz_mrl );
    }
    LIBVLC_API libvlc_media_t* libvlc_media_new_path( libvlc_instance_t* p_instance, const char* path )
    {
        return LibVLC::Instance( )->libvlc_media_new_path( p_instance, path );
    }
    LIBVLC_API libvlc_media_t* libvlc_media_new_fd( libvlc_instance_t* p_instance, int fd )
    {
        return LibVLC::Instance( )->libvlc_media_new_fd( p_instance, fd );
    }
    LIBVLC_API libvlc_media_t* libvlc_media_new_callbacks( libvlc_instance_t* instance, libvlc_media_open_cb open_cb, libvlc_media_read_cb read_cb, libvlc_media_seek_cb seek_cb, libvlc_media_close_cb close_cb, void* opaque )
    {
        return LibVLC::Instance( )->libvlc_media_new_callbacks( instance, open_cb, read_cb, seek_cb, close_cb, opaque );
    }
    LIBVLC_API libvlc_media_t* libvlc_media_new_as_node(libvlc_instance_t* p_instance,const char* psz_name )
    {
        return LibVLC::Instance( )->libvlc_media_new_as_node( p_instance, psz_name );
    }
    LIBVLC_API void libvlc_media_add_option( libvlc_media_t* p_md, const char* psz_options )
    {
        LibVLC::Instance( )->libvlc_media_add_option( p_md, psz_options );
    }
    LIBVLC_API void libvlc_media_add_option_flag( libvlc_media_t* p_md, const char* psz_options, unsigned i_flags )
    {
        LibVLC::Instance( )->libvlc_media_add_option_flag( p_md, psz_options, i_flags );
    }
    LIBVLC_API void libvlc_media_retain( libvlc_media_t* p_md )
    {
        LibVLC::Instance( )->libvlc_media_retain( p_md );
    }
    LIBVLC_API void libvlc_media_release( libvlc_media_t* p_md )
    {
        LibVLC::Instance( )->libvlc_media_release( p_md );
    }
    LIBVLC_API char* libvlc_media_get_mrl( libvlc_media_t* p_md )
    {
        return LibVLC::Instance( )->libvlc_media_get_mrl( p_md );
    }
    LIBVLC_API libvlc_media_t* libvlc_media_duplicate( libvlc_media_t* p_md )
    {
        return LibVLC::Instance( )->libvlc_media_duplicate( p_md );
    }
    LIBVLC_API char* libvlc_media_get_meta( libvlc_media_t* p_md, libvlc_meta_t e_meta )
    {
        return LibVLC::Instance( )->libvlc_media_get_meta( p_md, e_meta );
    }
    LIBVLC_API void libvlc_media_set_meta( libvlc_media_t* p_md, libvlc_meta_t e_meta, const char* psz_value )
    {
        LibVLC::Instance( )->libvlc_media_set_meta( p_md, e_meta, psz_value );
    }
    LIBVLC_API int libvlc_media_save_meta( libvlc_media_t* p_md )
    {
        return LibVLC::Instance( )->libvlc_media_save_meta( p_md );
    }
    LIBVLC_API libvlc_state_t libvlc_media_get_state( libvlc_media_t* p_md )
    {
        return LibVLC::Instance( )->libvlc_media_get_state( p_md );
    }
    LIBVLC_API int libvlc_media_get_stats( libvlc_media_t* p_md, libvlc_media_stats_t* p_stats )
    {
        return LibVLC::Instance( )->libvlc_media_get_stats( p_md, p_stats );
    }
    LIBVLC_API struct libvlc_media_list_t* libvlc_media_subitems( libvlc_media_t* p_md )
    {
        return LibVLC::Instance( )->libvlc_media_subitems( p_md );
    }
    LIBVLC_API libvlc_event_manager_t* libvlc_media_event_manager( libvlc_media_t* p_md )
    {
        return LibVLC::Instance( )->libvlc_media_event_manager( p_md );
    }
    LIBVLC_API libvlc_time_t libvlc_media_get_duration( libvlc_media_t* p_md )
    {
        return LibVLC::Instance( )->libvlc_media_get_duration( p_md );
    }
    LIBVLC_API int libvlc_media_parse_with_options( libvlc_media_t* p_md, libvlc_media_parse_flag_t parse_flag, int timeout )
    {
        return LibVLC::Instance( )->libvlc_media_parse_with_options( p_md, parse_flag, timeout );
    }
    LIBVLC_API void libvlc_media_parse_stop( libvlc_media_t* p_md )
    {
        LibVLC::Instance( )->libvlc_media_parse_stop( p_md );
    }
    LIBVLC_API libvlc_media_parsed_status_t libvlc_media_get_parsed_status( libvlc_media_t* p_md )
    {
        return LibVLC::Instance( )->libvlc_media_get_parsed_status( p_md );
    }
    LIBVLC_API void libvlc_media_set_user_data( libvlc_media_t* p_md, void* p_new_user_data )
    {
        LibVLC::Instance( )->libvlc_media_set_user_data( p_md, p_new_user_data );
    }
    LIBVLC_API void* libvlc_media_get_user_data( libvlc_media_t* p_md )
    {
        return LibVLC::Instance( )->libvlc_media_get_user_data( p_md );
    }
    LIBVLC_API unsigned libvlc_media_tracks_get( libvlc_media_t* p_md, libvlc_media_track_t*** tracks )
    {
        return LibVLC::Instance( )->libvlc_media_tracks_get( p_md, tracks );
    }
    LIBVLC_API const char* libvlc_media_get_codec_description( libvlc_track_type_t i_type, uint32_t i_codec )
    {
        return LibVLC::Instance( )->libvlc_media_get_codec_description( i_type, i_codec );
    }
    LIBVLC_API void libvlc_media_tracks_release( libvlc_media_track_t** p_tracks, unsigned i_count )
    {
        LibVLC::Instance( )->libvlc_media_tracks_release( p_tracks, i_count );
    }
    LIBVLC_API libvlc_media_type_t libvlc_media_get_type( libvlc_media_t* p_md )
    {
        return LibVLC::Instance( )->libvlc_media_get_type( p_md );
    }
    LIBVLC_API int libvlc_media_slaves_add( libvlc_media_t* p_md, libvlc_media_slave_type_t i_type, unsigned int i_priority, const char* psz_uri )
    {
        return LibVLC::Instance( )->libvlc_media_slaves_add( p_md, i_type, i_priority, psz_uri );
    }
    LIBVLC_API void libvlc_media_slaves_clear( libvlc_media_t* p_md )
    {
        LibVLC::Instance( )->libvlc_media_slaves_clear( p_md );
    }
    LIBVLC_API unsigned int libvlc_media_slaves_get( libvlc_media_t* p_md, libvlc_media_slave_t*** ppp_slaves )
    {
        return LibVLC::Instance( )->libvlc_media_slaves_get( p_md, ppp_slaves );
    }
    LIBVLC_API void libvlc_media_slaves_release( libvlc_media_slave_t** pp_slaves, unsigned int i_count )
    {
        LibVLC::Instance( )->libvlc_media_slaves_release( pp_slaves, i_count );
    }
}