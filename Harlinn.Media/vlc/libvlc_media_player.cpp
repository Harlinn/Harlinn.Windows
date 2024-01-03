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
    

    LIBVLC_API libvlc_media_player_t* libvlc_media_player_new( libvlc_instance_t* p_libvlc_instance )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_new( p_libvlc_instance );
    }
    LIBVLC_API libvlc_media_player_t* libvlc_media_player_new_from_media( libvlc_media_t* p_md )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_new_from_media( p_md );
    }
    LIBVLC_API void libvlc_media_player_release( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_release( p_mi );
    }
    LIBVLC_API void libvlc_media_player_retain( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_retain( p_mi );
    }
    LIBVLC_API void libvlc_media_player_set_media( libvlc_media_player_t* p_mi, libvlc_media_t* p_md )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_set_media( p_mi, p_md );
    }
    LIBVLC_API libvlc_media_t* libvlc_media_player_get_media( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_media( p_mi );
    }
    LIBVLC_API libvlc_event_manager_t* libvlc_media_player_event_manager( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_event_manager( p_mi );
    }
    LIBVLC_API int libvlc_media_player_is_playing( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_is_playing( p_mi );
    }
    LIBVLC_API int libvlc_media_player_play( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_play( p_mi );
    }
    LIBVLC_API void libvlc_media_player_set_pause( libvlc_media_player_t* mp, int do_pause )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_set_pause( mp, do_pause );
    }
    LIBVLC_API void libvlc_media_player_pause( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_pause( p_mi );
    }
    LIBVLC_API void libvlc_media_player_stop( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_stop( p_mi );
    }
    LIBVLC_API int libvlc_media_player_set_renderer( libvlc_media_player_t* p_mi, libvlc_renderer_item_t* p_item )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_set_renderer( p_mi, p_item );
    }
    LIBVLC_API void libvlc_video_set_callbacks( libvlc_media_player_t* mp, libvlc_video_lock_cb lock, libvlc_video_unlock_cb unlock, libvlc_video_display_cb display, void* opaque )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_callbacks( mp, lock, unlock, display, opaque );
    }
    LIBVLC_API void libvlc_video_set_format( libvlc_media_player_t* mp, const char* chroma, unsigned width, unsigned height, unsigned pitch )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_format( mp, chroma, width, height, pitch );
    }
    LIBVLC_API void libvlc_video_set_format_callbacks( libvlc_media_player_t* mp, libvlc_video_format_cb setup, libvlc_video_cleanup_cb cleanup )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_format_callbacks( mp, setup, cleanup );
    }
    LIBVLC_API void libvlc_media_player_set_nsobject( libvlc_media_player_t* p_mi, void* drawable )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_set_nsobject( p_mi, drawable );
    }
    LIBVLC_API void* libvlc_media_player_get_nsobject( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_nsobject( p_mi );
    }
    LIBVLC_API void libvlc_media_player_set_xwindow( libvlc_media_player_t* p_mi, uint32_t drawable )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_set_xwindow( p_mi, drawable );
    }
    LIBVLC_API uint32_t libvlc_media_player_get_xwindow( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_xwindow( p_mi );
    }
    LIBVLC_API void libvlc_media_player_set_hwnd( libvlc_media_player_t* p_mi, void* drawable )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_set_hwnd( p_mi, drawable );
    }
    LIBVLC_API void* libvlc_media_player_get_hwnd( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_hwnd( p_mi );
    }
    LIBVLC_API void libvlc_media_player_set_android_context( libvlc_media_player_t* p_mi, void* p_awindow_handler )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_set_android_context( p_mi, p_awindow_handler );
    }
    LIBVLC_API int libvlc_media_player_set_evas_object( libvlc_media_player_t* p_mi, void* p_evas_object )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_set_evas_object( p_mi, p_evas_object );
    }
    LIBVLC_API void libvlc_audio_set_callbacks( libvlc_media_player_t* mp, libvlc_audio_play_cb play, libvlc_audio_pause_cb pause, libvlc_audio_resume_cb resume, libvlc_audio_flush_cb flush, libvlc_audio_drain_cb drain, void* opaque )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_audio_set_callbacks( mp, play, pause, resume, flush, drain, opaque );
    }
    LIBVLC_API void libvlc_audio_set_volume_callback( libvlc_media_player_t* mp, libvlc_audio_set_volume_cb set_volume )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_audio_set_volume_callback( mp, set_volume );
    }
    LIBVLC_API void libvlc_audio_set_format_callbacks( libvlc_media_player_t* mp, libvlc_audio_setup_cb setup, libvlc_audio_cleanup_cb cleanup )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_audio_set_format_callbacks( mp, setup, cleanup );
    }
    LIBVLC_API void libvlc_audio_set_format( libvlc_media_player_t* mp, const char* format, unsigned rate, unsigned channels )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_audio_set_format( mp, format, rate, channels );
    }
    LIBVLC_API libvlc_time_t libvlc_media_player_get_length( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_length( p_mi );
    }
    LIBVLC_API libvlc_time_t libvlc_media_player_get_time( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_time( p_mi );
    }
    LIBVLC_API void libvlc_media_player_set_time( libvlc_media_player_t* p_mi, libvlc_time_t i_time )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_set_time( p_mi, i_time );
    }
    LIBVLC_API float libvlc_media_player_get_position( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_position( p_mi );
    }
    LIBVLC_API void libvlc_media_player_set_position( libvlc_media_player_t* p_mi, float f_pos )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_set_position( p_mi, f_pos );
    }
    LIBVLC_API void libvlc_media_player_set_chapter( libvlc_media_player_t* p_mi, int i_chapter )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_set_chapter( p_mi, i_chapter );
    }
    LIBVLC_API int libvlc_media_player_get_chapter( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_chapter( p_mi );
    }
    LIBVLC_API int libvlc_media_player_get_chapter_count( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_chapter_count( p_mi );
    }
    LIBVLC_API int libvlc_media_player_will_play( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_will_play( p_mi );
    }
    LIBVLC_API int libvlc_media_player_get_chapter_count_for_title( libvlc_media_player_t* p_mi, int i_title )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_chapter_count_for_title( p_mi, i_title );
    }
    LIBVLC_API void libvlc_media_player_set_title( libvlc_media_player_t* p_mi, int i_title )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_set_title( p_mi, i_title );
    }
    LIBVLC_API int libvlc_media_player_get_title( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_title( p_mi );
    }
    LIBVLC_API int libvlc_media_player_get_title_count( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_title_count( p_mi );
    }
    LIBVLC_API void libvlc_media_player_previous_chapter( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_previous_chapter( p_mi );
    }
    LIBVLC_API void libvlc_media_player_next_chapter( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_next_chapter( p_mi );
    }
    LIBVLC_API float libvlc_media_player_get_rate( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_rate( p_mi );
    }
    LIBVLC_API int libvlc_media_player_set_rate( libvlc_media_player_t* p_mi, float rate )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_set_rate( p_mi, rate );
    }
    LIBVLC_API libvlc_state_t libvlc_media_player_get_state( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_state( p_mi );
    }
    LIBVLC_API unsigned libvlc_media_player_has_vout( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_has_vout( p_mi );
    }
    LIBVLC_API int libvlc_media_player_is_seekable( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_is_seekable( p_mi );
    }
    LIBVLC_API int libvlc_media_player_can_pause( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_can_pause( p_mi );
    }
    LIBVLC_API int libvlc_media_player_program_scrambled( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_program_scrambled( p_mi );
    }
    LIBVLC_API void libvlc_media_player_next_frame( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_next_frame( p_mi );
    }
    LIBVLC_API void libvlc_media_player_navigate( libvlc_media_player_t* p_mi, unsigned navigate )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_navigate( p_mi, navigate );
    }
    LIBVLC_API void libvlc_media_player_set_video_title_display( libvlc_media_player_t* p_mi, libvlc_position_t position, unsigned int timeout )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_player_set_video_title_display( p_mi, position, timeout );
    }
    LIBVLC_API int libvlc_media_player_add_slave( libvlc_media_player_t* p_mi, libvlc_media_slave_type_t i_type, const char* psz_uri, bool b_select )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_add_slave( p_mi, i_type, psz_uri, b_select );
    }
    LIBVLC_API void libvlc_track_description_list_release( libvlc_track_description_t* p_track_description )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_track_description_list_release( p_track_description );
    }
    LIBVLC_API void libvlc_toggle_fullscreen( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_toggle_fullscreen( p_mi );
    }
    LIBVLC_API void libvlc_set_fullscreen( libvlc_media_player_t* p_mi, int b_fullscreen )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_set_fullscreen( p_mi, b_fullscreen );
    }
    LIBVLC_API int libvlc_get_fullscreen( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_get_fullscreen( p_mi );
    }
    LIBVLC_API void libvlc_video_set_key_input( libvlc_media_player_t* p_mi, unsigned on )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_key_input( p_mi, on );
    }
    LIBVLC_API void libvlc_video_set_mouse_input( libvlc_media_player_t* p_mi, unsigned on )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_mouse_input( p_mi, on );
    }
    LIBVLC_API int libvlc_video_get_size( libvlc_media_player_t* p_mi, unsigned num, unsigned* px, unsigned* py )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_size( p_mi, num, px, py );
    }
    LIBVLC_API int libvlc_video_get_cursor( libvlc_media_player_t* p_mi, unsigned num, int* px, int* py )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_cursor( p_mi, num, px, py );
    }
    LIBVLC_API float libvlc_video_get_scale( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_scale( p_mi );
    }
    LIBVLC_API void libvlc_video_set_scale( libvlc_media_player_t* p_mi, float f_factor )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_scale( p_mi, f_factor );
    }
    LIBVLC_API char* libvlc_video_get_aspect_ratio( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_aspect_ratio( p_mi );
    }
    LIBVLC_API void libvlc_video_set_aspect_ratio( libvlc_media_player_t* p_mi, const char* psz_aspect )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_aspect_ratio( p_mi, psz_aspect );
    }
    LIBVLC_API libvlc_video_viewpoint_t* libvlc_video_new_viewpoint( void )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_new_viewpoint( );
    }
    LIBVLC_API int libvlc_video_update_viewpoint( libvlc_media_player_t* p_mi, const libvlc_video_viewpoint_t* p_viewpoint, bool b_absolute )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_update_viewpoint( p_mi, p_viewpoint, b_absolute );
    }
    LIBVLC_API int libvlc_video_get_spu( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_spu( p_mi );
    }
    LIBVLC_API int libvlc_video_get_spu_count( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_spu_count( p_mi );
    }
    LIBVLC_API libvlc_track_description_t* libvlc_video_get_spu_description( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_spu_description( p_mi );
    }
    LIBVLC_API int libvlc_video_set_spu( libvlc_media_player_t* p_mi, int i_spu )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_set_spu( p_mi, i_spu );
    }
    LIBVLC_API int64_t libvlc_video_get_spu_delay( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_spu_delay( p_mi );
    }
    LIBVLC_API int libvlc_video_set_spu_delay( libvlc_media_player_t* p_mi, int64_t i_delay )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_set_spu_delay( p_mi, i_delay );
    }
    LIBVLC_API int libvlc_media_player_get_full_title_descriptions( libvlc_media_player_t* p_mi, libvlc_title_description_t*** titles )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_full_title_descriptions( p_mi, titles );
    }
    LIBVLC_API void libvlc_title_descriptions_release( libvlc_title_description_t** p_titles, unsigned i_count )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_title_descriptions_release( p_titles, i_count );
    }
    LIBVLC_API int libvlc_media_player_get_full_chapter_descriptions( libvlc_media_player_t* p_mi, int i_chapters_of_title, libvlc_chapter_description_t*** pp_chapters )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_full_chapter_descriptions( p_mi, i_chapters_of_title, pp_chapters );
    }
    LIBVLC_API void libvlc_chapter_descriptions_release( libvlc_chapter_description_t** p_chapters, unsigned i_count )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_chapter_descriptions_release( p_chapters, i_count );
    }
    LIBVLC_API char* libvlc_video_get_crop_geometry( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_crop_geometry( p_mi );
    }
    LIBVLC_API void libvlc_video_set_crop_geometry( libvlc_media_player_t* p_mi, const char* psz_geometry )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_crop_geometry( p_mi, psz_geometry );
    }
    LIBVLC_API int libvlc_video_get_teletext( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_teletext( p_mi );
    }
    LIBVLC_API void libvlc_video_set_teletext( libvlc_media_player_t* p_mi, int i_page )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_teletext( p_mi, i_page );
    }
    LIBVLC_API int libvlc_video_get_track_count( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_track_count( p_mi );
    }
    LIBVLC_API libvlc_track_description_t* libvlc_video_get_track_description( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_track_description( p_mi );
    }
    LIBVLC_API int libvlc_video_get_track( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_track( p_mi );
    }
    LIBVLC_API int libvlc_video_set_track( libvlc_media_player_t* p_mi, int i_track )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_set_track( p_mi, i_track );
    }
    LIBVLC_API int libvlc_video_take_snapshot( libvlc_media_player_t* p_mi, unsigned num, const char* psz_filepath, unsigned int i_width, unsigned int i_height )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_take_snapshot( p_mi, num, psz_filepath, i_width, i_height );
    }
    LIBVLC_API void libvlc_video_set_deinterlace( libvlc_media_player_t* p_mi, const char* psz_mode )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_deinterlace( p_mi, psz_mode );
    }
    LIBVLC_API int libvlc_video_get_marquee_int( libvlc_media_player_t* p_mi, unsigned option )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_marquee_int( p_mi, option );
    }
    LIBVLC_API char* libvlc_video_get_marquee_string( libvlc_media_player_t* p_mi, unsigned option )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_marquee_string( p_mi, option );
    }
    LIBVLC_API void libvlc_video_set_marquee_int( libvlc_media_player_t* p_mi, unsigned option, int i_val )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_marquee_int( p_mi, option, i_val );
    }
    LIBVLC_API void libvlc_video_set_marquee_string( libvlc_media_player_t* p_mi, unsigned option, const char* psz_text )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_marquee_string( p_mi, option, psz_text );
    }
    LIBVLC_API int libvlc_video_get_logo_int( libvlc_media_player_t* p_mi, unsigned option )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_logo_int( p_mi, option );
    }
    LIBVLC_API void libvlc_video_set_logo_int( libvlc_media_player_t* p_mi, unsigned option, int value )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_logo_int( p_mi, option, value );
    }
    LIBVLC_API void libvlc_video_set_logo_string( libvlc_media_player_t* p_mi, unsigned option, const char* psz_value )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_logo_string( p_mi, option, psz_value );
    }
    LIBVLC_API int libvlc_video_get_adjust_int( libvlc_media_player_t* p_mi, unsigned option )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_adjust_int( p_mi, option );
    }
    LIBVLC_API void libvlc_video_set_adjust_int( libvlc_media_player_t* p_mi, unsigned option, int value )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_adjust_int( p_mi, option, value );
    }
    LIBVLC_API float libvlc_video_get_adjust_float( libvlc_media_player_t* p_mi, unsigned option )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_video_get_adjust_float( p_mi, option );
    }
    LIBVLC_API void libvlc_video_set_adjust_float( libvlc_media_player_t* p_mi, unsigned option, float value )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_video_set_adjust_float( p_mi, option, value );
    }
    LIBVLC_API libvlc_audio_output_t* libvlc_audio_output_list_get( libvlc_instance_t* p_instance )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_output_list_get( p_instance );
    }
    LIBVLC_API void libvlc_audio_output_list_release( libvlc_audio_output_t* p_list )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_audio_output_list_release( p_list );
    }
    LIBVLC_API int libvlc_audio_output_set( libvlc_media_player_t* p_mi, const char* psz_name )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_output_set( p_mi, psz_name );
    }
    LIBVLC_API libvlc_audio_output_device_t* libvlc_audio_output_device_enum( libvlc_media_player_t* mp )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_output_device_enum( mp );
    }
    LIBVLC_API libvlc_audio_output_device_t* libvlc_audio_output_device_list_get( libvlc_instance_t* p_instance, const char* aout )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_output_device_list_get( p_instance, aout );
    }
    LIBVLC_API void libvlc_audio_output_device_list_release( libvlc_audio_output_device_t* p_list )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_audio_output_device_list_release( p_list );
    }
    LIBVLC_API void libvlc_audio_output_device_set( libvlc_media_player_t* mp, const char* module, const char* device_id )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_audio_output_device_set( mp, module, device_id );
    }
    LIBVLC_API char* libvlc_audio_output_device_get( libvlc_media_player_t* mp )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_output_device_get( mp );
    }
    LIBVLC_API void libvlc_audio_toggle_mute( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_audio_toggle_mute( p_mi );
    }
    LIBVLC_API int libvlc_audio_get_mute( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_get_mute( p_mi );
    }
    LIBVLC_API void libvlc_audio_set_mute( libvlc_media_player_t* p_mi, int status )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_audio_set_mute( p_mi, status );
    }
    LIBVLC_API int libvlc_audio_get_volume( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_get_volume( p_mi );
    }
    LIBVLC_API int libvlc_audio_set_volume( libvlc_media_player_t* p_mi, int i_volume )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_set_volume( p_mi, i_volume );
    }
    LIBVLC_API int libvlc_audio_get_track_count( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_get_track_count( p_mi );
    }
    LIBVLC_API libvlc_track_description_t* libvlc_audio_get_track_description( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_get_track_description( p_mi );
    }
    LIBVLC_API int libvlc_audio_get_track( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_get_track( p_mi );
    }
    LIBVLC_API int libvlc_audio_set_track( libvlc_media_player_t* p_mi, int i_track )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_set_track( p_mi, i_track );
    }
    LIBVLC_API int libvlc_audio_get_channel( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_get_channel( p_mi );
    }
    LIBVLC_API int libvlc_audio_set_channel( libvlc_media_player_t* p_mi, int channel )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_set_channel( p_mi, channel );
    }
    LIBVLC_API int64_t libvlc_audio_get_delay( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_get_delay( p_mi );
    }
    LIBVLC_API int libvlc_audio_set_delay( libvlc_media_player_t* p_mi, int64_t i_delay )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_set_delay( p_mi, i_delay );
    }
    LIBVLC_API unsigned libvlc_audio_equalizer_get_preset_count( void )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_equalizer_get_preset_count( );
    }
    LIBVLC_API const char* libvlc_audio_equalizer_get_preset_name( unsigned u_index )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_equalizer_get_preset_name( u_index );
    }
    LIBVLC_API unsigned libvlc_audio_equalizer_get_band_count( void )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_equalizer_get_band_count( );
    }
    LIBVLC_API float libvlc_audio_equalizer_get_band_frequency( unsigned u_index )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_equalizer_get_band_frequency( u_index );
    }
    LIBVLC_API libvlc_equalizer_t* libvlc_audio_equalizer_new( void )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_equalizer_new( );
    }
    LIBVLC_API libvlc_equalizer_t* libvlc_audio_equalizer_new_from_preset( unsigned u_index )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_equalizer_new_from_preset( u_index );
    }
    LIBVLC_API void libvlc_audio_equalizer_release( libvlc_equalizer_t* p_equalizer )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_audio_equalizer_release( p_equalizer );
    }
    LIBVLC_API int libvlc_audio_equalizer_set_preamp( libvlc_equalizer_t* p_equalizer, float f_preamp )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_equalizer_set_preamp( p_equalizer, f_preamp );
    }
    LIBVLC_API float libvlc_audio_equalizer_get_preamp( libvlc_equalizer_t* p_equalizer )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_equalizer_get_preamp( p_equalizer );
    }
    LIBVLC_API int libvlc_audio_equalizer_set_amp_at_index( libvlc_equalizer_t* p_equalizer, float f_amp, unsigned u_band )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_equalizer_set_amp_at_index( p_equalizer, f_amp, u_band );
    }
    LIBVLC_API float libvlc_audio_equalizer_get_amp_at_index( libvlc_equalizer_t* p_equalizer, unsigned u_band )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_audio_equalizer_get_amp_at_index( p_equalizer, u_band );
    }
    LIBVLC_API int libvlc_media_player_set_equalizer( libvlc_media_player_t* p_mi, libvlc_equalizer_t* p_equalizer )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_set_equalizer( p_mi, p_equalizer );
    }
    LIBVLC_API int libvlc_media_player_get_role( libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_get_role( p_mi );
    }
    LIBVLC_API int libvlc_media_player_set_role( libvlc_media_player_t* p_mi, unsigned role )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_player_set_role( p_mi, role );
    }

}