#pragma once
#ifndef HARLINN_MEDIA_VLC_LIBVLCWRAPPER_H_
#define HARLINN_MEDIA_VLC_LIBVLCWRAPPER_H_
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


#include <HCCHandle.h>

#if __has_include(<vlc/vlc.h>)
#define HARLINN_MEDIA_HAS_VLC 1
#include <vlc/vlc.h>

using namespace Harlinn::Common::Core;

using libvlc_errmsg_func_t = const char*(*)( );
using libvlc_clearerr_func_t = void( * )( );
using libvlc_vprinterr_func_t = const char* ( * )( const char* fmt, va_list ap );
using libvlc_printerr_func_t = const char* (*)( const char* fmt, ... );
using libvlc_new_func_t = libvlc_instance_t* (*)( int argc, const char* const* argv );
using libvlc_release_func_t = void (*)( libvlc_instance_t* p_instance );
using libvlc_retain_func_t = void (*)( libvlc_instance_t* p_instance );
using libvlc_add_intf_func_t = int (*)( libvlc_instance_t* p_instance, const char* name );
using libvlc_set_exit_handler_func_t = void (*)( libvlc_instance_t* p_instance, void ( *cb ) ( void* ), void* opaque );
using libvlc_set_user_agent_func_t = void (*)( libvlc_instance_t* p_instance, const char* name, const char* http );
using libvlc_set_app_id_func_t = void (*)( libvlc_instance_t* p_instance, const char* id, const char* version, const char* icon );
using libvlc_get_version_func_t = const char* ( * )( void );
using libvlc_get_compiler_func_t = const char* ( * )( void );
using libvlc_get_changeset_func_t = const char* ( * )( void );
using libvlc_free_func_t = void ( * )( void* ptr );
using libvlc_event_attach_func_t = int ( * )( libvlc_event_manager_t* p_event_manager, libvlc_event_type_t i_event_type, libvlc_callback_t f_callback, void* user_data );
using libvlc_event_detach_func_t = void ( * )( libvlc_event_manager_t* p_event_manager, libvlc_event_type_t i_event_type, libvlc_callback_t f_callback, void* p_user_data );
using libvlc_event_type_name_func_t = const char* ( * )( libvlc_event_type_t event_type );
using libvlc_log_get_context_func_t = void ( * )( const libvlc_log_t* ctx, const char** module, const char** file, unsigned* line );
using libvlc_log_get_object_func_t = void (*)( const libvlc_log_t* ctx, const char** name, const char** header, uintptr_t* id );
using libvlc_log_unset_func_t = void (*)( libvlc_instance_t* p_instance );
using libvlc_log_set_func_t = void (*)( libvlc_instance_t* p_instance, libvlc_log_cb cb, void* data );
using libvlc_log_set_file_func_t = void ( * )( libvlc_instance_t* p_instance, FILE* stream );
using libvlc_module_description_list_release_func_t = void ( * )( libvlc_module_description_t* p_list );
using libvlc_audio_filter_list_get_func_t = libvlc_module_description_t * ( * )( libvlc_instance_t* p_instance );
using libvlc_video_filter_list_get_func_t = libvlc_module_description_t * ( * )( libvlc_instance_t* p_instance );
using libvlc_clock_func_t = int64_t( * )( void );

// Deprecated
using libvlc_media_player_get_fps_func_t = float (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_set_agl_func_t = void (*)( libvlc_media_player_t* p_mi, uint32_t drawable );
using libvlc_media_player_get_agl_func_t = uint32_t (*)( libvlc_media_player_t* p_mi );
using libvlc_track_description_release_func_t = void (*)( libvlc_track_description_t* p_track_description );
using libvlc_video_get_height_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_video_get_width_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_video_get_title_description_func_t = libvlc_track_description_t* (*)( libvlc_media_player_t* p_mi );
using libvlc_video_get_chapter_description_func_t = libvlc_track_description_t* (*)( libvlc_media_player_t* p_mi, int i_title );
using libvlc_video_set_subtitle_file_func_t = int (*)( libvlc_media_player_t* p_mi, const char* psz_subtitle );
using libvlc_toggle_teletext_func_t = void (*)( libvlc_media_player_t* p_mi );
using libvlc_audio_output_device_count_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_audio_output );
using libvlc_audio_output_device_longname_func_t = char* (*)( libvlc_instance_t* p_instance, const char* psz_output, int i_device );
using libvlc_audio_output_device_id_func_t = char* ( * )( libvlc_instance_t* p_instance, const char* psz_audio_output, int i_device );
using libvlc_audio_output_get_device_type_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_audio_output_set_device_type_func_t = void (*)( libvlc_media_player_t* p_mp, int device_type );
using libvlc_media_parse_func_t = void (*)( libvlc_media_t* p_md );
using libvlc_media_parse_async_func_t = void (*)( libvlc_media_t* p_md );
using libvlc_media_is_parsed_func_t = int (*)( libvlc_media_t* p_md );
using libvlc_media_get_tracks_info_func_t = int (*)( libvlc_media_t* p_md, libvlc_media_track_info_t** tracks );
using libvlc_media_discoverer_new_from_name_func_t = libvlc_media_discoverer_t* (*)( libvlc_instance_t* p_inst, const char* psz_name );
using libvlc_media_discoverer_localized_name_func_t = char* (*)( libvlc_media_discoverer_t* p_mdis );
using libvlc_media_discoverer_event_manager_func_t = libvlc_event_manager_t* (*)( libvlc_media_discoverer_t* p_mdis );
using libvlc_wait_func_t = void (*)( libvlc_instance_t* p_instance );
using libvlc_get_log_verbosity_func_t = unsigned (*)( const libvlc_instance_t* p_instance );
using libvlc_set_log_verbosity_func_t = void (*)( libvlc_instance_t* p_instance, unsigned level );
using libvlc_log_open_func_t = libvlc_log_t* (*)( libvlc_instance_t* p_instance );
using libvlc_log_close_func_t = void (*)( libvlc_log_t* p_log );
using libvlc_log_count_func_t = unsigned (*)( const libvlc_log_t* p_log );
using libvlc_log_clear_func_t = void (*)( libvlc_log_t* p_log );
using libvlc_log_get_iterator_func_t = libvlc_log_iterator_t* (*)( const libvlc_log_t* p_log );
using libvlc_log_iterator_free_func_t = void (*)( libvlc_log_iterator_t* p_iter );
using libvlc_log_iterator_has_next_func_t = int (*)( const libvlc_log_iterator_t* p_iter );
using libvlc_log_iterator_next_func_t = libvlc_log_message_t* (*)( libvlc_log_iterator_t* p_iter, libvlc_log_message_t* p_buf );
using libvlc_playlist_play_func_t = void (*)( libvlc_instance_t* p_instance, int i_id, int i_options, char** ppsz_options );

// Dialog
using libvlc_dialog_set_callbacks_func_t = void (*)( libvlc_instance_t* p_instance, const libvlc_dialog_cbs* p_cbs, void* p_data );
using libvlc_dialog_set_context_func_t = void (*)( libvlc_dialog_id* p_id, void* p_context );
using libvlc_dialog_get_context_func_t = void* (*)( libvlc_dialog_id* p_id );
using libvlc_dialog_post_login_func_t = int (*)( libvlc_dialog_id* p_id, const char* psz_username, const char* psz_password, bool b_store );
using libvlc_dialog_post_action_func_t = int (*)( libvlc_dialog_id* p_id, int i_action );
using libvlc_dialog_dismiss_func_t = int (*)( libvlc_dialog_id* p_id );

// Media
using libvlc_media_new_location_func_t = libvlc_media_t * (*)( libvlc_instance_t* p_instance, const char* psz_mrl );
using libvlc_media_new_path_func_t = libvlc_media_t* (*)( libvlc_instance_t* p_instance, const char* path );
using libvlc_media_new_fd_func_t = libvlc_media_t* (*)( libvlc_instance_t* p_instance, int fd );
using libvlc_media_new_callbacks_func_t = libvlc_media_t* (*)( libvlc_instance_t* instance, libvlc_media_open_cb open_cb, libvlc_media_read_cb read_cb, libvlc_media_seek_cb seek_cb, libvlc_media_close_cb close_cb, void* opaque );
using libvlc_media_new_as_node_func_t = libvlc_media_t* (*)( libvlc_instance_t* p_instance, const char* psz_name );
using libvlc_media_add_option_func_t = void (*)( libvlc_media_t* p_md, const char* psz_options );
using libvlc_media_add_option_flag_func_t = void (*)( libvlc_media_t* p_md, const char* psz_options, unsigned i_flags );
using libvlc_media_retain_func_t = void (*)( libvlc_media_t* p_md );
using libvlc_media_release_func_t = void (*)( libvlc_media_t* p_md );
using libvlc_media_get_mrl_func_t = char* (*)( libvlc_media_t* p_md );
using libvlc_media_duplicate_func_t = libvlc_media_t* (*)( libvlc_media_t* p_md );
using libvlc_media_get_meta_func_t = char* (*)( libvlc_media_t* p_md, libvlc_meta_t e_meta );
using libvlc_media_set_meta_func_t = void (*)( libvlc_media_t* p_md, libvlc_meta_t e_meta, const char* psz_value );
using libvlc_media_save_meta_func_t = int (*)( libvlc_media_t* p_md );
using libvlc_media_get_state_func_t = libvlc_state_t (*)( libvlc_media_t* p_md );
using libvlc_media_get_stats_func_t = int (*)( libvlc_media_t* p_md, libvlc_media_stats_t* p_stats );
using libvlc_media_subitems_func_t = struct libvlc_media_list_t* (*)( libvlc_media_t* p_md );
using libvlc_media_event_manager_func_t = libvlc_event_manager_t* (*)( libvlc_media_t* p_md );
using libvlc_media_get_duration_func_t = libvlc_time_t (*)( libvlc_media_t* p_md );
using libvlc_media_parse_with_options_func_t = int (*)( libvlc_media_t* p_md, libvlc_media_parse_flag_t parse_flag, int timeout );
using libvlc_media_parse_stop_func_t = void (*)( libvlc_media_t* p_md );
using libvlc_media_get_parsed_status_func_t = libvlc_media_parsed_status_t (*)( libvlc_media_t* p_md );
using libvlc_media_set_user_data_func_t = void (*)( libvlc_media_t* p_md, void* p_new_user_data );
using libvlc_media_get_user_data_func_t = void* ( * )( libvlc_media_t* p_md );
using libvlc_media_tracks_get_func_t = unsigned (*)( libvlc_media_t* p_md, libvlc_media_track_t*** tracks );
using libvlc_media_get_codec_description_func_t = const char* (*)( libvlc_track_type_t i_type, uint32_t i_codec );
using libvlc_media_tracks_release_func_t = void (*)( libvlc_media_track_t** p_tracks, unsigned i_count );
using libvlc_media_get_type_func_t = libvlc_media_type_t (*)( libvlc_media_t* p_md );
using libvlc_media_slaves_add_func_t = int (*)( libvlc_media_t* p_md, libvlc_media_slave_type_t i_type, unsigned int i_priority, const char* psz_uri );
using libvlc_media_slaves_clear_func_t = void (*)( libvlc_media_t* p_md );
using libvlc_media_slaves_get_func_t = unsigned int (*)( libvlc_media_t* p_md, libvlc_media_slave_t*** ppp_slaves );
using libvlc_media_slaves_release_func_t = void (*)( libvlc_media_slave_t** pp_slaves, unsigned int i_count );

// Media discoverer
using libvlc_media_discoverer_new_func_t = libvlc_media_discoverer_t* (*)( libvlc_instance_t* p_inst, const char* psz_name );
using libvlc_media_discoverer_start_func_t = int (*)( libvlc_media_discoverer_t* p_mdis );
using libvlc_media_discoverer_stop_func_t = void (*)( libvlc_media_discoverer_t* p_mdis );
using libvlc_media_discoverer_release_func_t = void (*)( libvlc_media_discoverer_t* p_mdis );
using libvlc_media_discoverer_media_list_func_t = libvlc_media_list_t* (*)( libvlc_media_discoverer_t* p_mdis );
using libvlc_media_discoverer_is_running_func_t = int (*)( libvlc_media_discoverer_t* p_mdis );
using libvlc_media_discoverer_list_get_func_t = size_t (*)( libvlc_instance_t* p_inst, libvlc_media_discoverer_category_t i_cat, libvlc_media_discoverer_description_t*** ppp_services );
using libvlc_media_discoverer_list_release_func_t = void (*)( libvlc_media_discoverer_description_t** pp_services, size_t i_count );

// Media library
using libvlc_media_library_new_func_t = libvlc_media_library_t* (*)( libvlc_instance_t* p_instance );
using libvlc_media_library_release_func_t = void (*)( libvlc_media_library_t* p_mlib );
using libvlc_media_library_retain_func_t = void (*)( libvlc_media_library_t* p_mlib );
using libvlc_media_library_load_func_t = int (*)( libvlc_media_library_t* p_mlib );
using libvlc_media_library_media_list_func_t = libvlc_media_list_t* (*)( libvlc_media_library_t* p_mlib );

// Media list
using libvlc_media_list_new_func_t = libvlc_media_list_t* (*)( libvlc_instance_t* p_instance );
using libvlc_media_list_release_func_t = void (*)( libvlc_media_list_t* p_ml );
using libvlc_media_list_retain_func_t = void (*)( libvlc_media_list_t* p_ml );
using libvlc_media_list_set_media_func_t = void (*)( libvlc_media_list_t* p_ml, libvlc_media_t* p_md );
using libvlc_media_list_media_func_t = libvlc_media_t* (*)( libvlc_media_list_t* p_ml );
using libvlc_media_list_add_media_func_t = int (*)( libvlc_media_list_t* p_ml, libvlc_media_t* p_md );
using libvlc_media_list_insert_media_func_t = int (*)( libvlc_media_list_t* p_ml, libvlc_media_t* p_md, int i_pos );
using libvlc_media_list_remove_index_func_t = int (*)( libvlc_media_list_t* p_ml, int i_pos );
using libvlc_media_list_count_func_t = int (*)( libvlc_media_list_t* p_ml );
using libvlc_media_list_item_at_index_func_t = libvlc_media_t* (*)( libvlc_media_list_t* p_ml, int i_pos );
using libvlc_media_list_index_of_item_func_t = int (*)( libvlc_media_list_t* p_ml, libvlc_media_t* p_md );
using libvlc_media_list_is_readonly_func_t = int (*)( libvlc_media_list_t* p_ml );
using libvlc_media_list_lock_func_t = void (*)( libvlc_media_list_t* p_ml );
using libvlc_media_list_unlock_func_t = void (*)( libvlc_media_list_t* p_ml );
using libvlc_media_list_event_manager_func_t = libvlc_event_manager_t* (*)( libvlc_media_list_t* p_ml );

// Media list player
using libvlc_media_list_player_new_func_t = libvlc_media_list_player_t* (*)( libvlc_instance_t* p_instance );
using libvlc_media_list_player_release_func_t = void (*)( libvlc_media_list_player_t* p_mlp );
using libvlc_media_list_player_retain_func_t = void (*)( libvlc_media_list_player_t* p_mlp );
using libvlc_media_list_player_event_manager_func_t = libvlc_event_manager_t* (*)( libvlc_media_list_player_t* p_mlp );
using libvlc_media_list_player_set_media_player_func_t = void (*)( libvlc_media_list_player_t* p_mlp, libvlc_media_player_t* p_mi );
using libvlc_media_list_player_get_media_player_func_t = libvlc_media_player_t* (*)( libvlc_media_list_player_t* p_mlp );
using libvlc_media_list_player_set_media_list_func_t = void (*)( libvlc_media_list_player_t* p_mlp, libvlc_media_list_t* p_mlist );
using libvlc_media_list_player_play_func_t = void (*)( libvlc_media_list_player_t* p_mlp );
using libvlc_media_list_player_pause_func_t = void (*)( libvlc_media_list_player_t* p_mlp );
using libvlc_media_list_player_set_pause_func_t = void (*)( libvlc_media_list_player_t* p_mlp, int do_pause );
using libvlc_media_list_player_is_playing_func_t = int (*)( libvlc_media_list_player_t* p_mlp );
using libvlc_media_list_player_get_state_func_t = libvlc_state_t (*)( libvlc_media_list_player_t* p_mlp );
using libvlc_media_list_player_play_item_at_index_func_t = int (*)( libvlc_media_list_player_t* p_mlp, int i_index );
using libvlc_media_list_player_play_item_func_t = int (*)( libvlc_media_list_player_t* p_mlp, libvlc_media_t* p_md );
using libvlc_media_list_player_stop_func_t = void (*)( libvlc_media_list_player_t* p_mlp );
using libvlc_media_list_player_next_func_t = int (*)( libvlc_media_list_player_t* p_mlp );
using libvlc_media_list_player_previous_func_t = int (*)( libvlc_media_list_player_t* p_mlp );
using libvlc_media_list_player_set_playback_mode_func_t = void (*)( libvlc_media_list_player_t* p_mlp, libvlc_playback_mode_t e_mode );


// Media player
using libvlc_media_player_new_func_t = libvlc_media_player_t* (*)( libvlc_instance_t* p_libvlc_instance );
using libvlc_media_player_new_from_media_func_t = libvlc_media_player_t* (*)( libvlc_media_t* p_md );
using libvlc_media_player_release_func_t = void (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_retain_func_t = void (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_set_media_func_t = void (*)( libvlc_media_player_t* p_mi, libvlc_media_t* p_md );
using libvlc_media_player_get_media_func_t = libvlc_media_t* (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_event_manager_func_t = libvlc_event_manager_t* (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_is_playing_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_play_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_set_pause_func_t = void (*)( libvlc_media_player_t* mp, int do_pause );
using libvlc_media_player_pause_func_t = void (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_stop_func_t = void (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_set_renderer_func_t = int (*)( libvlc_media_player_t* p_mi, libvlc_renderer_item_t* p_item );
using libvlc_video_set_callbacks_func_t = void (*)( libvlc_media_player_t* mp, libvlc_video_lock_cb lock, libvlc_video_unlock_cb unlock, libvlc_video_display_cb display, void* opaque );
using libvlc_video_set_format_func_t = void (*)( libvlc_media_player_t* mp, const char* chroma, unsigned width, unsigned height, unsigned pitch );
using libvlc_video_set_format_callbacks_func_t = void (*)( libvlc_media_player_t* mp, libvlc_video_format_cb setup, libvlc_video_cleanup_cb cleanup );
using libvlc_media_player_set_nsobject_func_t = void (*)( libvlc_media_player_t* p_mi, void* drawable );
using libvlc_media_player_get_nsobject_func_t = void* (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_set_xwindow_func_t = void (*)( libvlc_media_player_t* p_mi, uint32_t drawable );
using libvlc_media_player_get_xwindow_func_t = uint32_t (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_set_hwnd_func_t = void (*)( libvlc_media_player_t* p_mi, void* drawable );
using libvlc_media_player_get_hwnd_func_t = void* (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_set_android_context_func_t = void (*)( libvlc_media_player_t* p_mi, void* p_awindow_handler );
using libvlc_media_player_set_evas_object_func_t = int (*)( libvlc_media_player_t* p_mi, void* p_evas_object );
using libvlc_audio_set_callbacks_func_t = void (*)( libvlc_media_player_t* mp, libvlc_audio_play_cb play, libvlc_audio_pause_cb pause, libvlc_audio_resume_cb resume, libvlc_audio_flush_cb flush, libvlc_audio_drain_cb drain, void* opaque );
using libvlc_audio_set_volume_callback_func_t = void (*)( libvlc_media_player_t* mp, libvlc_audio_set_volume_cb set_volume );
using libvlc_audio_set_format_callbacks_func_t = void (*)( libvlc_media_player_t* mp, libvlc_audio_setup_cb setup, libvlc_audio_cleanup_cb cleanup );
using libvlc_audio_set_format_func_t = void (*)( libvlc_media_player_t* mp, const char* format, unsigned rate, unsigned channels );
using libvlc_media_player_get_length_func_t = libvlc_time_t (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_get_time_func_t = libvlc_time_t (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_set_time_func_t = void (*)( libvlc_media_player_t* p_mi, libvlc_time_t i_time );
using libvlc_media_player_get_position_func_t = float (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_set_position_func_t = void (*)( libvlc_media_player_t* p_mi, float f_pos );
using libvlc_media_player_set_chapter_func_t = void (*)( libvlc_media_player_t* p_mi, int i_chapter );
using libvlc_media_player_get_chapter_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_get_chapter_count_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_will_play_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_get_chapter_count_for_title_func_t = int (*)( libvlc_media_player_t* p_mi, int i_title );
using libvlc_media_player_set_title_func_t = void (*)( libvlc_media_player_t* p_mi, int i_title );
using libvlc_media_player_get_title_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_get_title_count_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_previous_chapter_func_t = void (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_next_chapter_func_t = void (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_get_rate_func_t = float (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_set_rate_func_t = int (*)( libvlc_media_player_t* p_mi, float rate );
using libvlc_media_player_get_state_func_t = libvlc_state_t (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_has_vout_func_t = unsigned (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_is_seekable_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_can_pause_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_program_scrambled_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_next_frame_func_t = void (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_navigate_func_t = void (*)( libvlc_media_player_t* p_mi, unsigned navigate );
using libvlc_media_player_set_video_title_display_func_t = void (*)( libvlc_media_player_t* p_mi, libvlc_position_t position, unsigned int timeout );
using libvlc_media_player_add_slave_func_t = int (*)( libvlc_media_player_t* p_mi, libvlc_media_slave_type_t i_type, const char* psz_uri, bool b_select );
using libvlc_track_description_list_release_func_t = void (*)( libvlc_track_description_t* p_track_description );
using libvlc_toggle_fullscreen_func_t = void (*)( libvlc_media_player_t* p_mi );
using libvlc_set_fullscreen_func_t = void (*)( libvlc_media_player_t* p_mi, int b_fullscreen );
using libvlc_get_fullscreen_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_video_set_key_input_func_t = void (*)( libvlc_media_player_t* p_mi, unsigned on );
using libvlc_video_set_mouse_input_func_t = void (*)( libvlc_media_player_t* p_mi, unsigned on );
using libvlc_video_get_size_func_t = int (*)( libvlc_media_player_t* p_mi, unsigned num, unsigned* px, unsigned* py );
using libvlc_video_get_cursor_func_t = int (*)( libvlc_media_player_t* p_mi, unsigned num, int* px, int* py );
using libvlc_video_get_scale_func_t = float (*)( libvlc_media_player_t* p_mi );
using libvlc_video_set_scale_func_t = void (*)( libvlc_media_player_t* p_mi, float f_factor );
using libvlc_video_get_aspect_ratio_func_t = char* (*)( libvlc_media_player_t* p_mi );
using libvlc_video_set_aspect_ratio_func_t = void (*)( libvlc_media_player_t* p_mi, const char* psz_aspect );
using libvlc_video_new_viewpoint_func_t = libvlc_video_viewpoint_t* (*)( void );
using libvlc_video_update_viewpoint_func_t = int (*)( libvlc_media_player_t* p_mi, const libvlc_video_viewpoint_t* p_viewpoint, bool b_absolute );
using libvlc_video_get_spu_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_video_get_spu_count_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_video_get_spu_description_func_t = libvlc_track_description_t* (*)( libvlc_media_player_t* p_mi );
using libvlc_video_set_spu_func_t = int (*)( libvlc_media_player_t* p_mi, int i_spu );
using libvlc_video_get_spu_delay_func_t = int64_t (*)( libvlc_media_player_t* p_mi );
using libvlc_video_set_spu_delay_func_t = int (*)( libvlc_media_player_t* p_mi, int64_t i_delay );
using libvlc_media_player_get_full_title_descriptions_func_t = int (*)( libvlc_media_player_t* p_mi, libvlc_title_description_t*** titles );
using libvlc_title_descriptions_release_func_t = void (*)( libvlc_title_description_t** p_titles, unsigned i_count );
using libvlc_media_player_get_full_chapter_descriptions_func_t = int (*)( libvlc_media_player_t* p_mi, int i_chapters_of_title, libvlc_chapter_description_t*** pp_chapters );
using libvlc_chapter_descriptions_release_func_t = void (*)( libvlc_chapter_description_t** p_chapters, unsigned i_count );
using libvlc_video_get_crop_geometry_func_t = char* (*)( libvlc_media_player_t* p_mi );
using libvlc_video_set_crop_geometry_func_t = void (*)( libvlc_media_player_t* p_mi, const char* psz_geometry );
using libvlc_video_get_teletext_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_video_set_teletext_func_t = void (*)( libvlc_media_player_t* p_mi, int i_page );
using libvlc_video_get_track_count_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_video_get_track_description_func_t = libvlc_track_description_t* (*)( libvlc_media_player_t* p_mi );
using libvlc_video_get_track_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_video_set_track_func_t = int (*)( libvlc_media_player_t* p_mi, int i_track );
using libvlc_video_take_snapshot_func_t = int (*)( libvlc_media_player_t* p_mi, unsigned num, const char* psz_filepath, unsigned int i_width, unsigned int i_height );
using libvlc_video_set_deinterlace_func_t = void (*)( libvlc_media_player_t* p_mi, const char* psz_mode );
using libvlc_video_get_marquee_int_func_t = int (*)( libvlc_media_player_t* p_mi, unsigned option );
using libvlc_video_get_marquee_string_func_t = char* (*)( libvlc_media_player_t* p_mi, unsigned option );
using libvlc_video_set_marquee_int_func_t = void (*)( libvlc_media_player_t* p_mi, unsigned option, int i_val );
using libvlc_video_set_marquee_string_func_t = void (*)( libvlc_media_player_t* p_mi, unsigned option, const char* psz_text );
using libvlc_video_get_logo_int_func_t = int (*)( libvlc_media_player_t* p_mi, unsigned option );
using libvlc_video_set_logo_int_func_t = void (*)( libvlc_media_player_t* p_mi, unsigned option, int value );
using libvlc_video_set_logo_string_func_t = void (*)( libvlc_media_player_t* p_mi, unsigned option, const char* psz_value );
using libvlc_video_get_adjust_int_func_t = int (*)( libvlc_media_player_t* p_mi, unsigned option );
using libvlc_video_set_adjust_int_func_t = void (*)( libvlc_media_player_t* p_mi, unsigned option, int value );
using libvlc_video_get_adjust_float_func_t = float (*)( libvlc_media_player_t* p_mi, unsigned option );
using libvlc_video_set_adjust_float_func_t = void (*)( libvlc_media_player_t* p_mi, unsigned option, float value );
using libvlc_audio_output_list_get_func_t = libvlc_audio_output_t* (*)( libvlc_instance_t* p_instance );
using libvlc_audio_output_list_release_func_t = void (*)( libvlc_audio_output_t* p_list );
using libvlc_audio_output_set_func_t = int (*)( libvlc_media_player_t* p_mi, const char* psz_name );
using libvlc_audio_output_device_enum_func_t = libvlc_audio_output_device_t* (*)( libvlc_media_player_t* mp );
using libvlc_audio_output_device_list_get_func_t = libvlc_audio_output_device_t* (*)( libvlc_instance_t* p_instance, const char* aout );
using libvlc_audio_output_device_list_release_func_t = void (*)( libvlc_audio_output_device_t* p_list );
using libvlc_audio_output_device_set_func_t = void (*)( libvlc_media_player_t* mp, const char* module, const char* device_id );
using libvlc_audio_output_device_get_func_t = char* (*)( libvlc_media_player_t* mp );
using libvlc_audio_toggle_mute_func_t = void (*)( libvlc_media_player_t* p_mi );
using libvlc_audio_get_mute_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_audio_set_mute_func_t = void (*)( libvlc_media_player_t* p_mi, int status );
using libvlc_audio_get_volume_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_audio_set_volume_func_t = int (*)( libvlc_media_player_t* p_mi, int i_volume );
using libvlc_audio_get_track_count_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_audio_get_track_description_func_t = libvlc_track_description_t* (*)( libvlc_media_player_t* p_mi );
using libvlc_audio_get_track_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_audio_set_track_func_t = int (*)( libvlc_media_player_t* p_mi, int i_track );
using libvlc_audio_get_channel_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_audio_set_channel_func_t = int (*)( libvlc_media_player_t* p_mi, int channel );
using libvlc_audio_get_delay_func_t = int64_t (*)( libvlc_media_player_t* p_mi );
using libvlc_audio_set_delay_func_t = int (*)( libvlc_media_player_t* p_mi, int64_t i_delay );
using libvlc_audio_equalizer_get_preset_count_func_t = unsigned (*)( void );
using libvlc_audio_equalizer_get_preset_name_func_t = const char* (*)( unsigned u_index );
using libvlc_audio_equalizer_get_band_count_func_t = unsigned (*)( void );
using libvlc_audio_equalizer_get_band_frequency_func_t = float (*)( unsigned u_index );
using libvlc_audio_equalizer_new_func_t = libvlc_equalizer_t* (*)( void );
using libvlc_audio_equalizer_new_from_preset_func_t = libvlc_equalizer_t* (*)( unsigned u_index );
using libvlc_audio_equalizer_release_func_t = void (*)( libvlc_equalizer_t* p_equalizer );
using libvlc_audio_equalizer_set_preamp_func_t = int (*)( libvlc_equalizer_t* p_equalizer, float f_preamp );
using libvlc_audio_equalizer_get_preamp_func_t = float (*)( libvlc_equalizer_t* p_equalizer );
using libvlc_audio_equalizer_set_amp_at_index_func_t = int (*)( libvlc_equalizer_t* p_equalizer, float f_amp, unsigned u_band );
using libvlc_audio_equalizer_get_amp_at_index_func_t = float (*)( libvlc_equalizer_t* p_equalizer, unsigned u_band );
using libvlc_media_player_set_equalizer_func_t = int (*)( libvlc_media_player_t* p_mi, libvlc_equalizer_t* p_equalizer );
using libvlc_media_player_get_role_func_t = int (*)( libvlc_media_player_t* p_mi );
using libvlc_media_player_set_role_func_t = int (*)( libvlc_media_player_t* p_mi, unsigned role );

// VLM
using libvlc_vlm_release_func_t = void (*)( libvlc_instance_t* p_instance );
using libvlc_vlm_add_broadcast_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input, const char* psz_output, int i_options, const char* const* ppsz_options, int b_enabled, int b_loop );
using libvlc_vlm_add_vod_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input, int i_options, const char* const* ppsz_options, int b_enabled, const char* psz_mux );
using libvlc_vlm_del_media_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name );
using libvlc_vlm_set_enabled_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, int b_enabled );
using libvlc_vlm_set_output_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_output );
using libvlc_vlm_set_input_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input );
using libvlc_vlm_add_input_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input );
using libvlc_vlm_set_loop_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, int b_loop );
using libvlc_vlm_set_mux_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_mux );
using libvlc_vlm_change_media_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input, const char* psz_output, int i_options, const char* const* ppsz_options, int b_enabled, int b_loop );
using libvlc_vlm_play_media_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name );
using libvlc_vlm_stop_media_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name );
using libvlc_vlm_pause_media_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name );
using libvlc_vlm_seek_media_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, float f_percentage );
using libvlc_vlm_show_media_func_t = const char* (*)( libvlc_instance_t* p_instance, const char* psz_name );
using libvlc_vlm_get_media_instance_position_func_t = float (*)( libvlc_instance_t* p_instance, const char* psz_name, int i_instance );
using libvlc_vlm_get_media_instance_time_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, int i_instance );
using libvlc_vlm_get_media_instance_length_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, int i_instance );
using libvlc_vlm_get_media_instance_rate_func_t = int (*)( libvlc_instance_t* p_instance, const char* psz_name, int i_instance );
using libvlc_vlm_get_event_manager_func_t = libvlc_event_manager_t* (*)( libvlc_instance_t* p_instance );

class LibVLC
{
private:
    WideString libVlcDll_ = GetVlcDll( );
    WideString pluginsDirectory_ = GetVlcPluginsDirectory( );
    ModuleHandle moduleHandle_;
    libvlc_errmsg_func_t errmsg_ = nullptr;
    libvlc_clearerr_func_t clearerr_ = nullptr;
    libvlc_vprinterr_func_t vprinterr_ = nullptr;
    libvlc_printerr_func_t printerr_ = nullptr;
    libvlc_new_func_t new_ = nullptr;
    libvlc_release_func_t release_ = nullptr;
    libvlc_retain_func_t retain_ = nullptr;
    libvlc_add_intf_func_t add_intf_ = nullptr;
    libvlc_set_exit_handler_func_t set_exit_handler_ = nullptr;
    libvlc_set_user_agent_func_t set_user_agent_ = nullptr;
    libvlc_set_app_id_func_t set_app_id_ = nullptr;
    libvlc_get_version_func_t get_version_ = nullptr;
    libvlc_get_compiler_func_t get_compiler_ = nullptr;
    libvlc_get_changeset_func_t get_changeset_ = nullptr;
    libvlc_free_func_t free_ = nullptr;
    libvlc_event_attach_func_t event_attach_ = nullptr;
    libvlc_event_detach_func_t event_detach_ = nullptr;
    libvlc_event_type_name_func_t event_type_name_ = nullptr;
    libvlc_log_get_context_func_t log_get_context_ = nullptr;
    libvlc_log_get_object_func_t log_get_object_ = nullptr;
    libvlc_log_unset_func_t log_unset_ = nullptr;
    libvlc_log_set_func_t log_set_ = nullptr;
    libvlc_log_set_file_func_t log_set_file_ = nullptr;
    libvlc_module_description_list_release_func_t module_description_list_release_ = nullptr;
    libvlc_audio_filter_list_get_func_t audio_filter_list_get_ = nullptr;
    libvlc_video_filter_list_get_func_t video_filter_list_get_ = nullptr;
    libvlc_clock_func_t clock_ = nullptr;

    // Deprecated
    libvlc_media_player_get_fps_func_t media_player_get_fps_ = nullptr;
    libvlc_media_player_set_agl_func_t media_player_set_agl_ = nullptr;
    libvlc_media_player_get_agl_func_t media_player_get_agl_ = nullptr;
    libvlc_track_description_release_func_t track_description_release_ = nullptr;
    libvlc_video_get_height_func_t video_get_height_ = nullptr;
    libvlc_video_get_width_func_t video_get_width_ = nullptr;
    libvlc_video_get_title_description_func_t video_get_title_description_ = nullptr;
    libvlc_video_get_chapter_description_func_t video_get_chapter_description_ = nullptr;
    libvlc_video_set_subtitle_file_func_t video_set_subtitle_file_ = nullptr;
    libvlc_toggle_teletext_func_t toggle_teletext_ = nullptr;
    libvlc_audio_output_device_count_func_t audio_output_device_count_ = nullptr;
    libvlc_audio_output_device_longname_func_t audio_output_device_longname_ = nullptr;
    libvlc_audio_output_device_id_func_t audio_output_device_id_ = nullptr;
    libvlc_audio_output_get_device_type_func_t audio_output_get_device_type_ = nullptr;
    libvlc_audio_output_set_device_type_func_t audio_output_set_device_type_ = nullptr;
    libvlc_media_parse_func_t media_parse_ = nullptr;
    libvlc_media_parse_async_func_t media_parse_async_ = nullptr;
    libvlc_media_is_parsed_func_t media_is_parsed_ = nullptr;
    libvlc_media_get_tracks_info_func_t media_get_tracks_info_ = nullptr;
    libvlc_media_discoverer_new_from_name_func_t media_discoverer_new_from_name_ = nullptr;
    libvlc_media_discoverer_localized_name_func_t media_discoverer_localized_name_ = nullptr;
    libvlc_media_discoverer_event_manager_func_t media_discoverer_event_manager_ = nullptr;
    libvlc_wait_func_t wait_ = nullptr;
    libvlc_get_log_verbosity_func_t get_log_verbosity_ = nullptr;
    libvlc_set_log_verbosity_func_t set_log_verbosity_ = nullptr;
    libvlc_log_open_func_t log_open_ = nullptr;
    libvlc_log_close_func_t log_close_ = nullptr;
    libvlc_log_count_func_t log_count_ = nullptr;
    libvlc_log_clear_func_t log_clear_ = nullptr;
    libvlc_log_get_iterator_func_t log_get_iterator_ = nullptr;
    libvlc_log_iterator_free_func_t log_iterator_free_ = nullptr;
    libvlc_log_iterator_has_next_func_t log_iterator_has_next_ = nullptr;
    libvlc_log_iterator_next_func_t log_iterator_next_ = nullptr;
    libvlc_playlist_play_func_t playlist_play_ = nullptr;

    // Dialog
    libvlc_dialog_set_callbacks_func_t dialog_set_callbacks_ = nullptr;
    libvlc_dialog_set_context_func_t dialog_set_context_ = nullptr;
    libvlc_dialog_get_context_func_t dialog_get_context_ = nullptr;
    libvlc_dialog_post_login_func_t dialog_post_login_ = nullptr;
    libvlc_dialog_post_action_func_t dialog_post_action_ = nullptr;
    libvlc_dialog_dismiss_func_t dialog_dismiss_ = nullptr;

    // Media
    libvlc_media_new_location_func_t media_new_location_ = nullptr;
    libvlc_media_new_path_func_t media_new_path_ = nullptr;
    libvlc_media_new_fd_func_t media_new_fd_ = nullptr;
    libvlc_media_new_callbacks_func_t media_new_callbacks_ = nullptr;
    libvlc_media_new_as_node_func_t media_new_as_node_ = nullptr;
    libvlc_media_add_option_func_t media_add_option_ = nullptr;
    libvlc_media_add_option_flag_func_t media_add_option_flag_ = nullptr;
    libvlc_media_retain_func_t media_retain_ = nullptr;
    libvlc_media_release_func_t media_release_ = nullptr;
    libvlc_media_get_mrl_func_t media_get_mrl_ = nullptr;
    libvlc_media_duplicate_func_t media_duplicate_ = nullptr;
    libvlc_media_get_meta_func_t media_get_meta_ = nullptr;
    libvlc_media_set_meta_func_t media_set_meta_ = nullptr;
    libvlc_media_save_meta_func_t media_save_meta_ = nullptr;
    libvlc_media_get_state_func_t media_get_state_ = nullptr;
    libvlc_media_get_stats_func_t media_get_stats_ = nullptr;
    libvlc_media_subitems_func_t media_subitems_ = nullptr;
    libvlc_media_event_manager_func_t media_event_manager_ = nullptr;
    libvlc_media_get_duration_func_t media_get_duration_ = nullptr;
    libvlc_media_parse_with_options_func_t media_parse_with_options_ = nullptr;
    libvlc_media_parse_stop_func_t media_parse_stop_ = nullptr;
    libvlc_media_get_parsed_status_func_t media_get_parsed_status_ = nullptr;
    libvlc_media_set_user_data_func_t media_set_user_data_ = nullptr;
    libvlc_media_get_user_data_func_t media_get_user_data_ = nullptr;
    libvlc_media_tracks_get_func_t media_tracks_get_ = nullptr;
    libvlc_media_get_codec_description_func_t media_get_codec_description_ = nullptr;
    libvlc_media_tracks_release_func_t media_tracks_release_ = nullptr;
    libvlc_media_get_type_func_t media_get_type_ = nullptr;
    libvlc_media_slaves_add_func_t media_slaves_add_ = nullptr;
    libvlc_media_slaves_clear_func_t media_slaves_clear_ = nullptr;
    libvlc_media_slaves_get_func_t media_slaves_get_ = nullptr;
    libvlc_media_slaves_release_func_t media_slaves_release_ = nullptr;

    // Media discoverer
    libvlc_media_discoverer_new_func_t media_discoverer_new_ = nullptr;
    libvlc_media_discoverer_start_func_t media_discoverer_start_ = nullptr;
    libvlc_media_discoverer_stop_func_t media_discoverer_stop_ = nullptr;
    libvlc_media_discoverer_release_func_t media_discoverer_release_ = nullptr;
    libvlc_media_discoverer_media_list_func_t media_discoverer_media_list_ = nullptr;
    libvlc_media_discoverer_is_running_func_t media_discoverer_is_running_ = nullptr;
    libvlc_media_discoverer_list_get_func_t media_discoverer_list_get_ = nullptr;
    libvlc_media_discoverer_list_release_func_t media_discoverer_list_release_ = nullptr;

    // Media library
    libvlc_media_library_new_func_t media_library_new_ = nullptr;
    libvlc_media_library_release_func_t media_library_release_ = nullptr;
    libvlc_media_library_retain_func_t media_library_retain_ = nullptr;
    libvlc_media_library_load_func_t media_library_load_ = nullptr;
    libvlc_media_library_media_list_func_t media_library_media_list_ = nullptr;

    // Media list
    libvlc_media_list_new_func_t media_list_new_ = nullptr;
    libvlc_media_list_release_func_t media_list_release_ = nullptr;
    libvlc_media_list_retain_func_t media_list_retain_ = nullptr;
    libvlc_media_list_set_media_func_t media_list_set_media_ = nullptr;
    libvlc_media_list_media_func_t media_list_media_ = nullptr;
    libvlc_media_list_add_media_func_t media_list_add_media_ = nullptr;
    libvlc_media_list_insert_media_func_t media_list_insert_media_ = nullptr;
    libvlc_media_list_remove_index_func_t media_list_remove_index_ = nullptr;
    libvlc_media_list_count_func_t media_list_count_ = nullptr;
    libvlc_media_list_item_at_index_func_t media_list_item_at_index_ = nullptr;
    libvlc_media_list_index_of_item_func_t media_list_index_of_item_ = nullptr;
    libvlc_media_list_is_readonly_func_t media_list_is_readonly_ = nullptr;
    libvlc_media_list_lock_func_t media_list_lock_ = nullptr;
    libvlc_media_list_unlock_func_t media_list_unlock_ = nullptr;
    libvlc_media_list_event_manager_func_t media_list_event_manager_ = nullptr;

    // Media list player
    libvlc_media_list_player_new_func_t media_list_player_new_ = nullptr;
    libvlc_media_list_player_release_func_t media_list_player_release_ = nullptr;
    libvlc_media_list_player_retain_func_t media_list_player_retain_ = nullptr;
    libvlc_media_list_player_event_manager_func_t media_list_player_event_manager_ = nullptr;
    libvlc_media_list_player_set_media_player_func_t media_list_player_set_media_player_ = nullptr;
    libvlc_media_list_player_get_media_player_func_t media_list_player_get_media_player_ = nullptr;
    libvlc_media_list_player_set_media_list_func_t media_list_player_set_media_list_ = nullptr;
    libvlc_media_list_player_play_func_t media_list_player_play_ = nullptr;
    libvlc_media_list_player_pause_func_t media_list_player_pause_ = nullptr;
    libvlc_media_list_player_set_pause_func_t media_list_player_set_pause_ = nullptr;
    libvlc_media_list_player_is_playing_func_t media_list_player_is_playing_ = nullptr;
    libvlc_media_list_player_get_state_func_t media_list_player_get_state_ = nullptr;
    libvlc_media_list_player_play_item_at_index_func_t media_list_player_play_item_at_index_ = nullptr;
    libvlc_media_list_player_play_item_func_t media_list_player_play_item_ = nullptr;
    libvlc_media_list_player_stop_func_t media_list_player_stop_ = nullptr;
    libvlc_media_list_player_next_func_t media_list_player_next_ = nullptr;
    libvlc_media_list_player_previous_func_t media_list_player_previous_ = nullptr;
    libvlc_media_list_player_set_playback_mode_func_t media_list_player_set_playback_mode_ = nullptr;

    // Media player
    libvlc_media_player_new_func_t media_player_new_ = nullptr;
    libvlc_media_player_new_from_media_func_t media_player_new_from_media_ = nullptr;
    libvlc_media_player_release_func_t media_player_release_ = nullptr;
    libvlc_media_player_retain_func_t media_player_retain_ = nullptr;
    libvlc_media_player_set_media_func_t media_player_set_media_ = nullptr;
    libvlc_media_player_get_media_func_t media_player_get_media_ = nullptr;
    libvlc_media_player_event_manager_func_t media_player_event_manager_ = nullptr;
    libvlc_media_player_is_playing_func_t media_player_is_playing_ = nullptr;
    libvlc_media_player_play_func_t media_player_play_ = nullptr;
    libvlc_media_player_set_pause_func_t media_player_set_pause_ = nullptr;
    libvlc_media_player_pause_func_t media_player_pause_ = nullptr;
    libvlc_media_player_stop_func_t media_player_stop_ = nullptr;
    libvlc_media_player_set_renderer_func_t media_player_set_renderer_ = nullptr;
    libvlc_video_set_callbacks_func_t video_set_callbacks_ = nullptr;
    libvlc_video_set_format_func_t video_set_format_ = nullptr;
    libvlc_video_set_format_callbacks_func_t video_set_format_callbacks_ = nullptr;
    libvlc_media_player_set_nsobject_func_t media_player_set_nsobject_ = nullptr;
    libvlc_media_player_get_nsobject_func_t media_player_get_nsobject_ = nullptr;
    libvlc_media_player_set_xwindow_func_t media_player_set_xwindow_ = nullptr;
    libvlc_media_player_get_xwindow_func_t media_player_get_xwindow_ = nullptr;
    libvlc_media_player_set_hwnd_func_t media_player_set_hwnd_ = nullptr;
    libvlc_media_player_get_hwnd_func_t media_player_get_hwnd_ = nullptr;
    libvlc_media_player_set_android_context_func_t media_player_set_android_context_ = nullptr;
    libvlc_media_player_set_evas_object_func_t media_player_set_evas_object_ = nullptr;
    libvlc_audio_set_callbacks_func_t audio_set_callbacks_ = nullptr;
    libvlc_audio_set_volume_callback_func_t audio_set_volume_callback_ = nullptr;
    libvlc_audio_set_format_callbacks_func_t audio_set_format_callbacks_ = nullptr;
    libvlc_audio_set_format_func_t audio_set_format_ = nullptr;
    libvlc_media_player_get_length_func_t media_player_get_length_ = nullptr;
    libvlc_media_player_get_time_func_t media_player_get_time_ = nullptr;
    libvlc_media_player_set_time_func_t media_player_set_time_ = nullptr;
    libvlc_media_player_get_position_func_t media_player_get_position_ = nullptr;
    libvlc_media_player_set_position_func_t media_player_set_position_ = nullptr;
    libvlc_media_player_set_chapter_func_t media_player_set_chapter_ = nullptr;
    libvlc_media_player_get_chapter_func_t media_player_get_chapter_ = nullptr;
    libvlc_media_player_get_chapter_count_func_t media_player_get_chapter_count_ = nullptr;
    libvlc_media_player_will_play_func_t media_player_will_play_ = nullptr;
    libvlc_media_player_get_chapter_count_for_title_func_t media_player_get_chapter_count_for_title_ = nullptr;
    libvlc_media_player_set_title_func_t media_player_set_title_ = nullptr;
    libvlc_media_player_get_title_func_t media_player_get_title_ = nullptr;
    libvlc_media_player_get_title_count_func_t media_player_get_title_count_ = nullptr;
    libvlc_media_player_previous_chapter_func_t media_player_previous_chapter_ = nullptr;
    libvlc_media_player_next_chapter_func_t media_player_next_chapter_ = nullptr;
    libvlc_media_player_get_rate_func_t media_player_get_rate_ = nullptr;
    libvlc_media_player_set_rate_func_t media_player_set_rate_ = nullptr;
    libvlc_media_player_get_state_func_t media_player_get_state_ = nullptr;
    libvlc_media_player_has_vout_func_t media_player_has_vout_ = nullptr;
    libvlc_media_player_is_seekable_func_t media_player_is_seekable_ = nullptr;
    libvlc_media_player_can_pause_func_t media_player_can_pause_ = nullptr;
    libvlc_media_player_program_scrambled_func_t media_player_program_scrambled_ = nullptr;
    libvlc_media_player_next_frame_func_t media_player_next_frame_ = nullptr;
    libvlc_media_player_navigate_func_t media_player_navigate_ = nullptr;
    libvlc_media_player_set_video_title_display_func_t media_player_set_video_title_display_ = nullptr;
    libvlc_media_player_add_slave_func_t media_player_add_slave_ = nullptr;
    libvlc_track_description_list_release_func_t track_description_list_release_ = nullptr;
    libvlc_toggle_fullscreen_func_t toggle_fullscreen_ = nullptr;
    libvlc_set_fullscreen_func_t set_fullscreen_ = nullptr;
    libvlc_get_fullscreen_func_t get_fullscreen_ = nullptr;
    libvlc_video_set_key_input_func_t video_set_key_input_ = nullptr;
    libvlc_video_set_mouse_input_func_t video_set_mouse_input_ = nullptr;
    libvlc_video_get_size_func_t video_get_size_ = nullptr;
    libvlc_video_get_cursor_func_t video_get_cursor_ = nullptr;
    libvlc_video_get_scale_func_t video_get_scale_ = nullptr;
    libvlc_video_set_scale_func_t video_set_scale_ = nullptr;
    libvlc_video_get_aspect_ratio_func_t video_get_aspect_ratio_ = nullptr;
    libvlc_video_set_aspect_ratio_func_t video_set_aspect_ratio_ = nullptr;
    libvlc_video_new_viewpoint_func_t video_new_viewpoint_ = nullptr;
    libvlc_video_update_viewpoint_func_t video_update_viewpoint_ = nullptr;
    libvlc_video_get_spu_func_t video_get_spu_ = nullptr;
    libvlc_video_get_spu_count_func_t video_get_spu_count_ = nullptr;
    libvlc_video_get_spu_description_func_t video_get_spu_description_ = nullptr;
    libvlc_video_set_spu_func_t video_set_spu_ = nullptr;
    libvlc_video_get_spu_delay_func_t video_get_spu_delay_ = nullptr;
    libvlc_video_set_spu_delay_func_t video_set_spu_delay_ = nullptr;
    libvlc_media_player_get_full_title_descriptions_func_t media_player_get_full_title_descriptions_ = nullptr;
    libvlc_title_descriptions_release_func_t title_descriptions_release_ = nullptr;
    libvlc_media_player_get_full_chapter_descriptions_func_t media_player_get_full_chapter_descriptions_ = nullptr;
    libvlc_chapter_descriptions_release_func_t chapter_descriptions_release_ = nullptr;
    libvlc_video_get_crop_geometry_func_t video_get_crop_geometry_ = nullptr;
    libvlc_video_set_crop_geometry_func_t video_set_crop_geometry_ = nullptr;
    libvlc_video_get_teletext_func_t video_get_teletext_ = nullptr;
    libvlc_video_set_teletext_func_t video_set_teletext_ = nullptr;
    libvlc_video_get_track_count_func_t video_get_track_count_ = nullptr;
    libvlc_video_get_track_description_func_t video_get_track_description_ = nullptr;
    libvlc_video_get_track_func_t video_get_track_ = nullptr;
    libvlc_video_set_track_func_t video_set_track_ = nullptr;
    libvlc_video_take_snapshot_func_t video_take_snapshot_ = nullptr;
    libvlc_video_set_deinterlace_func_t video_set_deinterlace_ = nullptr;
    libvlc_video_get_marquee_int_func_t video_get_marquee_int_ = nullptr;
    libvlc_video_get_marquee_string_func_t video_get_marquee_string_ = nullptr;
    libvlc_video_set_marquee_int_func_t video_set_marquee_int_ = nullptr;
    libvlc_video_set_marquee_string_func_t video_set_marquee_string_ = nullptr;
    libvlc_video_get_logo_int_func_t video_get_logo_int_ = nullptr;
    libvlc_video_set_logo_int_func_t video_set_logo_int_ = nullptr;
    libvlc_video_set_logo_string_func_t video_set_logo_string_ = nullptr;
    libvlc_video_get_adjust_int_func_t video_get_adjust_int_ = nullptr;
    libvlc_video_set_adjust_int_func_t video_set_adjust_int_ = nullptr;
    libvlc_video_get_adjust_float_func_t video_get_adjust_float_ = nullptr;
    libvlc_video_set_adjust_float_func_t video_set_adjust_float_ = nullptr;
    libvlc_audio_output_list_get_func_t audio_output_list_get_ = nullptr;
    libvlc_audio_output_list_release_func_t audio_output_list_release_ = nullptr;
    libvlc_audio_output_set_func_t audio_output_set_ = nullptr;
    libvlc_audio_output_device_enum_func_t audio_output_device_enum_ = nullptr;
    libvlc_audio_output_device_list_get_func_t audio_output_device_list_get_ = nullptr;
    libvlc_audio_output_device_list_release_func_t audio_output_device_list_release_ = nullptr;
    libvlc_audio_output_device_set_func_t audio_output_device_set_ = nullptr;
    libvlc_audio_output_device_get_func_t audio_output_device_get_ = nullptr;
    libvlc_audio_toggle_mute_func_t audio_toggle_mute_ = nullptr;
    libvlc_audio_get_mute_func_t audio_get_mute_ = nullptr;
    libvlc_audio_set_mute_func_t audio_set_mute_ = nullptr;
    libvlc_audio_get_volume_func_t audio_get_volume_ = nullptr;
    libvlc_audio_set_volume_func_t audio_set_volume_ = nullptr;
    libvlc_audio_get_track_count_func_t audio_get_track_count_ = nullptr;
    libvlc_audio_get_track_description_func_t audio_get_track_description_ = nullptr;
    libvlc_audio_get_track_func_t audio_get_track_ = nullptr;
    libvlc_audio_set_track_func_t audio_set_track_ = nullptr;
    libvlc_audio_get_channel_func_t audio_get_channel_ = nullptr;
    libvlc_audio_set_channel_func_t audio_set_channel_ = nullptr;
    libvlc_audio_get_delay_func_t audio_get_delay_ = nullptr;
    libvlc_audio_set_delay_func_t audio_set_delay_ = nullptr;
    libvlc_audio_equalizer_get_preset_count_func_t audio_equalizer_get_preset_count_ = nullptr;
    libvlc_audio_equalizer_get_preset_name_func_t audio_equalizer_get_preset_name_ = nullptr;
    libvlc_audio_equalizer_get_band_count_func_t audio_equalizer_get_band_count_ = nullptr;
    libvlc_audio_equalizer_get_band_frequency_func_t audio_equalizer_get_band_frequency_ = nullptr;
    libvlc_audio_equalizer_new_func_t audio_equalizer_new_ = nullptr;
    libvlc_audio_equalizer_new_from_preset_func_t audio_equalizer_new_from_preset_ = nullptr;
    libvlc_audio_equalizer_release_func_t audio_equalizer_release_ = nullptr;
    libvlc_audio_equalizer_set_preamp_func_t audio_equalizer_set_preamp_ = nullptr;
    libvlc_audio_equalizer_get_preamp_func_t audio_equalizer_get_preamp_ = nullptr;
    libvlc_audio_equalizer_set_amp_at_index_func_t audio_equalizer_set_amp_at_index_ = nullptr;
    libvlc_audio_equalizer_get_amp_at_index_func_t audio_equalizer_get_amp_at_index_ = nullptr;
    libvlc_media_player_set_equalizer_func_t media_player_set_equalizer_ = nullptr;
    libvlc_media_player_get_role_func_t media_player_get_role_ = nullptr;
    libvlc_media_player_set_role_func_t media_player_set_role_ = nullptr;

    // VLM:
    libvlc_vlm_release_func_t vlm_release_ = nullptr;
    libvlc_vlm_add_broadcast_func_t vlm_add_broadcast_ = nullptr;
    libvlc_vlm_add_vod_func_t vlm_add_vod_ = nullptr;
    libvlc_vlm_del_media_func_t vlm_del_media_ = nullptr;
    libvlc_vlm_set_enabled_func_t vlm_set_enabled_ = nullptr;
    libvlc_vlm_set_output_func_t vlm_set_output_ = nullptr;
    libvlc_vlm_set_input_func_t vlm_set_input_ = nullptr;
    libvlc_vlm_add_input_func_t vlm_add_input_ = nullptr;
    libvlc_vlm_set_loop_func_t vlm_set_loop_ = nullptr;
    libvlc_vlm_set_mux_func_t vlm_set_mux_ = nullptr;
    libvlc_vlm_change_media_func_t vlm_change_media_ = nullptr;
    libvlc_vlm_play_media_func_t vlm_play_media_ = nullptr;
    libvlc_vlm_stop_media_func_t vlm_stop_media_ = nullptr;
    libvlc_vlm_pause_media_func_t vlm_pause_media_ = nullptr;
    libvlc_vlm_seek_media_func_t vlm_seek_media_ = nullptr;
    libvlc_vlm_show_media_func_t vlm_show_media_ = nullptr;
    libvlc_vlm_get_media_instance_position_func_t vlm_get_media_instance_position_ = nullptr;
    libvlc_vlm_get_media_instance_time_func_t vlm_get_media_instance_time_ = nullptr;
    libvlc_vlm_get_media_instance_length_func_t vlm_get_media_instance_length_ = nullptr;
    libvlc_vlm_get_media_instance_rate_func_t vlm_get_media_instance_rate_ = nullptr;
    libvlc_vlm_get_event_manager_func_t vlm_get_event_manager_ = nullptr;


public:
    LibVLC( );

    static LibVLC* Instance( );

    static WideString GetVlcDirectory( );
    static WideString GetVlcDll( );
    static WideString GetVlcPluginsDirectory( );
    
    void Initialize( );
    


    const char* libvlc_errmsg( )
    {
        return errmsg_( );
    }
    void libvlc_clearerr( )
    {
        clearerr_( );
    }

    const char* libvlc_vprinterr( const char* fmt, va_list ap )
    {
        return vprinterr_( fmt, ap );
    }

    const char* libvlc_printerr( const char* fmt, ... )
    {
        va_list argptr;
        va_start( argptr, fmt );
        auto result = vprinterr_( fmt, argptr );
        va_end( argptr );
        return result;
    }

    libvlc_instance_t* libvlc_new( int argc, const char* const* argv )
    {
        return new_( argc, argv );
    }

    void libvlc_release( libvlc_instance_t* p_instance )
    {
        release_( p_instance );
    }

    void libvlc_retain( libvlc_instance_t* p_instance )
    {
        retain_( p_instance );
    }

    int libvlc_add_intf( libvlc_instance_t* p_instance, const char* name )
    {
        return add_intf_( p_instance, name );
    }

    void libvlc_set_exit_handler( libvlc_instance_t* p_instance, void ( *cb ) ( void* ), void* opaque )
    {
        set_exit_handler_( p_instance, cb, opaque );
    }

    void libvlc_set_user_agent( libvlc_instance_t* p_instance, const char* name, const char* http )
    {
        set_user_agent_( p_instance, name, http );
    }

    void libvlc_set_app_id( libvlc_instance_t* p_instance, const char* id, const char* version, const char* icon )
    {
        set_app_id_( p_instance, id, version, icon );
    }

    const char* libvlc_get_version( )
    {
        return get_version_( );
    }

    const char* libvlc_get_compiler( )
    {
        return get_compiler_( );
    }

    const char* libvlc_get_changeset( )
    {
        return get_changeset_( );
    }

    void libvlc_free( void* ptr )
    {
        free_( ptr );
    }

    int libvlc_event_attach( libvlc_event_manager_t* p_event_manager, libvlc_event_type_t i_event_type, libvlc_callback_t f_callback, void* user_data )
    {
        return event_attach_( p_event_manager, i_event_type, f_callback, user_data );
    }

    void libvlc_event_detach( libvlc_event_manager_t* p_event_manager, libvlc_event_type_t i_event_type, libvlc_callback_t f_callback, void* p_user_data )
    {
        event_detach_( p_event_manager, i_event_type, f_callback, p_user_data );
    }

    const char* libvlc_event_type_name( libvlc_event_type_t event_type )
    {
        return event_type_name_( event_type );
    }

    void libvlc_log_get_context( const libvlc_log_t* ctx, const char** module, const char** file, unsigned* line )
    {
        log_get_context_( ctx, module, file, line );
    }

    void libvlc_log_get_object( const libvlc_log_t* ctx, const char** name, const char** header, uintptr_t* id )
    {
        log_get_object_( ctx, name, header, id );
    }

    void libvlc_log_unset( libvlc_instance_t* p_instance )
    {
        log_unset_( p_instance );
    }

    void libvlc_log_set( libvlc_instance_t* p_instance, libvlc_log_cb cb, void* data )
    {
        log_set_( p_instance, cb, data );
    }

    void libvlc_log_set_file( libvlc_instance_t* p_instance, FILE* stream )
    {
        log_set_file_( p_instance, stream );
    }

    void libvlc_module_description_list_release( libvlc_module_description_t* p_list )
    {
        module_description_list_release_( p_list );
    }

    libvlc_module_description_t* libvlc_audio_filter_list_get( libvlc_instance_t* p_instance )
    {
        return audio_filter_list_get_( p_instance );
    }

    libvlc_module_description_t* libvlc_video_filter_list_get( libvlc_instance_t* p_instance )
    {
        return video_filter_list_get_( p_instance );
    }

    int64_t libvlc_clock( )
    {
        return clock_( );
    }
    // Deprecated
    float libvlc_media_player_get_fps( libvlc_media_player_t* p_mi )
    {
        return media_player_get_fps_( p_mi );
    }
    void libvlc_media_player_set_agl( libvlc_media_player_t* p_mi, uint32_t drawable )
    {
        media_player_set_agl_( p_mi, drawable );
    }
    uint32_t libvlc_media_player_get_agl( libvlc_media_player_t* p_mi )
    {
        return media_player_get_agl_( p_mi );
    }
    void libvlc_track_description_release( libvlc_track_description_t* p_track_description )
    {
        track_description_release_( p_track_description );
    }
    int libvlc_video_get_height( libvlc_media_player_t* p_mi )
    {
        return video_get_height_( p_mi );
    }
    int libvlc_video_get_width( libvlc_media_player_t* p_mi )
    {
        return video_get_width_( p_mi );
    }
    libvlc_track_description_t* libvlc_video_get_title_description( libvlc_media_player_t* p_mi )
    {
        return video_get_title_description_( p_mi );
    }
    libvlc_track_description_t* libvlc_video_get_chapter_description( libvlc_media_player_t* p_mi, int i_title )
    {
        return video_get_chapter_description_( p_mi, i_title );
    }
    int libvlc_video_set_subtitle_file( libvlc_media_player_t* p_mi, const char* psz_subtitle )
    {
        return video_set_subtitle_file_( p_mi, psz_subtitle );
    }
    void libvlc_toggle_teletext( libvlc_media_player_t* p_mi )
    {
        toggle_teletext_( p_mi );
    }
    int libvlc_audio_output_device_count( libvlc_instance_t* p_instance, const char* psz_audio_output )
    {
        return audio_output_device_count_( p_instance, psz_audio_output );
    }
    char* libvlc_audio_output_device_longname( libvlc_instance_t* p_instance, const char* psz_output, int i_device )
    {
        return audio_output_device_longname_( p_instance, psz_output, i_device );
    }
    char* libvlc_audio_output_device_id( libvlc_instance_t* p_instance, const char* psz_audio_output, int i_device )
    {
        return audio_output_device_id_( p_instance, psz_audio_output, i_device );
    }
    int libvlc_audio_output_get_device_type( libvlc_media_player_t* p_mi )
    {
        return audio_output_get_device_type_( p_mi );
    }
    void libvlc_audio_output_set_device_type( libvlc_media_player_t* p_mp, int device_type )
    {
        audio_output_set_device_type_( p_mp, device_type );
    }
    void libvlc_media_parse( libvlc_media_t* p_md )
    {
        media_parse_( p_md );
    }
    void libvlc_media_parse_async( libvlc_media_t* p_md )
    {
        media_parse_async_( p_md );
    }
    int libvlc_media_is_parsed( libvlc_media_t* p_md )
    {
        return media_is_parsed_( p_md );
    }
    int libvlc_media_get_tracks_info( libvlc_media_t* p_md, libvlc_media_track_info_t** tracks )
    {
        return media_get_tracks_info_( p_md, tracks );
    }
    libvlc_media_discoverer_t* libvlc_media_discoverer_new_from_name( libvlc_instance_t* p_inst, const char* psz_name )
    {
        return media_discoverer_new_from_name_( p_inst, psz_name );
    }
    char* libvlc_media_discoverer_localized_name( libvlc_media_discoverer_t* p_mdis )
    {
        return media_discoverer_localized_name_( p_mdis );
    }
    libvlc_event_manager_t* libvlc_media_discoverer_event_manager( libvlc_media_discoverer_t* p_mdis )
    {
        return media_discoverer_event_manager_( p_mdis );
    }
    void libvlc_wait( libvlc_instance_t* p_instance )
    {
        wait_( p_instance );
    }
    unsigned libvlc_get_log_verbosity( const libvlc_instance_t* p_instance )
    {
        return get_log_verbosity_( p_instance );
    }
    void libvlc_set_log_verbosity( libvlc_instance_t* p_instance, unsigned level )
    {
        set_log_verbosity_( p_instance, level );
    }
    libvlc_log_t* libvlc_log_open( libvlc_instance_t* p_instance )
    {
        return log_open_( p_instance );
    }
    void libvlc_log_close( libvlc_log_t* p_log )
    {
        log_close_( p_log );
    }
    unsigned libvlc_log_count( const libvlc_log_t* p_log )
    {
        return log_count_( p_log );
    }
    void libvlc_log_clear( libvlc_log_t* p_log )
    {
        log_clear_( p_log );
    }
    libvlc_log_iterator_t* libvlc_log_get_iterator( const libvlc_log_t* p_log )
    {
        return log_get_iterator_( p_log );
    }
    void libvlc_log_iterator_free( libvlc_log_iterator_t* p_iter )
    {
        log_iterator_free_( p_iter );
    }
    int libvlc_log_iterator_has_next( const libvlc_log_iterator_t* p_iter )
    {
        return log_iterator_has_next_( p_iter );
    }
    libvlc_log_message_t* libvlc_log_iterator_next( libvlc_log_iterator_t* p_iter, libvlc_log_message_t* p_buf )
    {
        return log_iterator_next_( p_iter, p_buf );
    }
    void libvlc_playlist_play( libvlc_instance_t* p_instance, int i_id, int i_options, char** ppsz_options )
    {
        return playlist_play_( p_instance, i_id, i_options, ppsz_options );
    }


    // Dialog
    void libvlc_dialog_set_callbacks( libvlc_instance_t* p_instance, const libvlc_dialog_cbs* p_cbs, void* p_data )
    {
        dialog_set_callbacks_( p_instance, p_cbs, p_data );
    }
    void libvlc_dialog_set_context( libvlc_dialog_id* p_id, void* p_context )
    {
        dialog_set_context_( p_id, p_context );
    }
    void* libvlc_dialog_get_context( libvlc_dialog_id* p_id )
    {
        return dialog_get_context_( p_id );
    }
    int libvlc_dialog_post_login( libvlc_dialog_id* p_id, const char* psz_username, const char* psz_password, bool b_store )
    {
        return dialog_post_login_( p_id, psz_username, psz_password, b_store );
    }
    int libvlc_dialog_post_action( libvlc_dialog_id* p_id, int i_action )
    {
        return dialog_post_action_( p_id, i_action );
    }
    int libvlc_dialog_dismiss( libvlc_dialog_id* p_id )
    {
        return dialog_dismiss_( p_id );
    }

    // Media
    libvlc_media_t* libvlc_media_new_location( libvlc_instance_t* p_instance, const char* psz_mrl )
    {
        return media_new_location_( p_instance, psz_mrl );
    }
    libvlc_media_t* libvlc_media_new_path( libvlc_instance_t* p_instance, const char* path )
    {
        return media_new_path_( p_instance, path );
    }
    libvlc_media_t* libvlc_media_new_fd( libvlc_instance_t* p_instance, int fd )
    {
        return media_new_fd_( p_instance, fd );
    }
    libvlc_media_t* libvlc_media_new_callbacks( libvlc_instance_t* instance, libvlc_media_open_cb open_cb, libvlc_media_read_cb read_cb, libvlc_media_seek_cb seek_cb, libvlc_media_close_cb close_cb, void* opaque )
    {
        return media_new_callbacks_( instance, open_cb, read_cb, seek_cb, close_cb, opaque );
    }
    libvlc_media_t* libvlc_media_new_as_node( libvlc_instance_t* p_instance, const char* psz_name )
    {
        return media_new_as_node_( p_instance, psz_name );
    }
    void libvlc_media_add_option( libvlc_media_t* p_md, const char* psz_options )
    {
        media_add_option_( p_md, psz_options );
    }
    void libvlc_media_add_option_flag( libvlc_media_t* p_md, const char* psz_options, unsigned i_flags )
    {
        media_add_option_flag_( p_md, psz_options, i_flags );
    }
    void libvlc_media_retain( libvlc_media_t* p_md )
    {
        media_retain_( p_md );
    }
    void libvlc_media_release( libvlc_media_t* p_md )
    {
        media_release_( p_md );
    }
    char* libvlc_media_get_mrl( libvlc_media_t* p_md )
    {
        return media_get_mrl_( p_md );
    }
    libvlc_media_t* libvlc_media_duplicate( libvlc_media_t* p_md )
    {
        return media_duplicate_( p_md );
    }
    char* libvlc_media_get_meta( libvlc_media_t* p_md, libvlc_meta_t e_meta )
    {
        return media_get_meta_( p_md, e_meta );
    }
    void libvlc_media_set_meta( libvlc_media_t* p_md, libvlc_meta_t e_meta, const char* psz_value )
    {
        media_set_meta_( p_md, e_meta, psz_value );
    }
    int libvlc_media_save_meta( libvlc_media_t* p_md )
    {
        return media_save_meta_( p_md );
    }
    libvlc_state_t libvlc_media_get_state( libvlc_media_t* p_md )
    {
        return media_get_state_( p_md );
    }
    int libvlc_media_get_stats( libvlc_media_t* p_md, libvlc_media_stats_t* p_stats )
    {
        return media_get_stats_( p_md, p_stats );
    }
    struct libvlc_media_list_t* libvlc_media_subitems( libvlc_media_t* p_md )
    {
        return media_subitems_( p_md );
    }
    libvlc_event_manager_t* libvlc_media_event_manager( libvlc_media_t* p_md )
    {
        return media_event_manager_( p_md );
    }
    libvlc_time_t libvlc_media_get_duration( libvlc_media_t* p_md )
    {
        return media_get_duration_( p_md );
    }
    int libvlc_media_parse_with_options( libvlc_media_t* p_md, libvlc_media_parse_flag_t parse_flag, int timeout )
    {
        return media_parse_with_options_( p_md, parse_flag, timeout );
    }
    void libvlc_media_parse_stop( libvlc_media_t* p_md )
    {
        return media_parse_stop_( p_md );
    }
    libvlc_media_parsed_status_t libvlc_media_get_parsed_status( libvlc_media_t* p_md )
    {
        return media_get_parsed_status_( p_md );
    }
    void libvlc_media_set_user_data( libvlc_media_t* p_md, void* p_new_user_data )
    {
        media_set_user_data_( p_md, p_new_user_data );
    }
    void* libvlc_media_get_user_data( libvlc_media_t* p_md )
    {
        return media_get_user_data_( p_md );
    }
    unsigned libvlc_media_tracks_get( libvlc_media_t* p_md, libvlc_media_track_t*** tracks )
    {
        return media_tracks_get_( p_md, tracks );
    }
    const char* libvlc_media_get_codec_description( libvlc_track_type_t i_type, uint32_t i_codec )
    {
        return media_get_codec_description_( i_type, i_codec );
    }
    void libvlc_media_tracks_release( libvlc_media_track_t** p_tracks, unsigned i_count )
    {
        media_tracks_release_( p_tracks, i_count );
    }
    libvlc_media_type_t libvlc_media_get_type( libvlc_media_t* p_md )
    {
        return media_get_type_( p_md );
    }
    int libvlc_media_slaves_add( libvlc_media_t* p_md, libvlc_media_slave_type_t i_type, unsigned int i_priority, const char* psz_uri )
    {
        return media_slaves_add_( p_md, i_type, i_priority, psz_uri );
    }
    void libvlc_media_slaves_clear( libvlc_media_t* p_md )
    {
        media_slaves_clear_( p_md );
    }
    unsigned int libvlc_media_slaves_get( libvlc_media_t* p_md, libvlc_media_slave_t*** ppp_slaves )
    {
        return media_slaves_get_( p_md, ppp_slaves );
    }
    void libvlc_media_slaves_release( libvlc_media_slave_t** pp_slaves, unsigned int i_count )
    {
        media_slaves_release_( pp_slaves, i_count );
    }

    // Media discoverer
    libvlc_media_discoverer_t* libvlc_media_discoverer_new( libvlc_instance_t* p_inst, const char* psz_name )
    {
        return media_discoverer_new_( p_inst, psz_name );
    }
    int libvlc_media_discoverer_start( libvlc_media_discoverer_t* p_mdis )
    {
        return media_discoverer_start_( p_mdis );
    }
    void libvlc_media_discoverer_stop( libvlc_media_discoverer_t* p_mdis )
    {
        media_discoverer_stop_( p_mdis );
    }
    void libvlc_media_discoverer_release( libvlc_media_discoverer_t* p_mdis )
    {
        media_discoverer_release_( p_mdis );
    }
    libvlc_media_list_t* libvlc_media_discoverer_media_list( libvlc_media_discoverer_t* p_mdis )
    {
        return media_discoverer_media_list_( p_mdis );
    }
    int libvlc_media_discoverer_is_running( libvlc_media_discoverer_t* p_mdis )
    {
        return media_discoverer_is_running_( p_mdis );
    }
    size_t libvlc_media_discoverer_list_get( libvlc_instance_t* p_inst, libvlc_media_discoverer_category_t i_cat, libvlc_media_discoverer_description_t*** ppp_services )
    {
        return media_discoverer_list_get_( p_inst, i_cat, ppp_services );
    }
    void libvlc_media_discoverer_list_release( libvlc_media_discoverer_description_t** pp_services, size_t i_count )
    {
        media_discoverer_list_release_( pp_services, i_count );
    }

    // Media library
    libvlc_media_library_t* libvlc_media_library_new( libvlc_instance_t* p_instance )
    {
        return media_library_new_( p_instance );
    }
    void libvlc_media_library_release( libvlc_media_library_t* p_mlib )
    {
        media_library_release_( p_mlib );
    }
    void libvlc_media_library_retain( libvlc_media_library_t* p_mlib )
    {
        media_library_retain_( p_mlib );
    }
    int libvlc_media_library_load( libvlc_media_library_t* p_mlib )
    {
        return media_library_load_( p_mlib );
    }
    libvlc_media_list_t* libvlc_media_library_media_list( libvlc_media_library_t* p_mlib )
    {
        return media_library_media_list_( p_mlib );
    }

    // Media list
    libvlc_media_list_t* libvlc_media_list_new( libvlc_instance_t* p_instance )
    {
        return media_list_new_( p_instance );
    }
    void libvlc_media_list_release( libvlc_media_list_t* p_ml )
    {
        media_list_release_( p_ml );
    }
    void libvlc_media_list_retain( libvlc_media_list_t* p_ml )
    {
        media_list_retain_( p_ml );
    }
    void libvlc_media_list_set_media( libvlc_media_list_t* p_ml, libvlc_media_t* p_md )
    {
        media_list_set_media_( p_ml, p_md );
    }
    libvlc_media_t* libvlc_media_list_media( libvlc_media_list_t* p_ml )
    {
        return media_list_media_( p_ml );
    }
    int libvlc_media_list_add_media( libvlc_media_list_t* p_ml, libvlc_media_t* p_md )
    {
        return media_list_add_media_( p_ml, p_md );
    }
    int libvlc_media_list_insert_media( libvlc_media_list_t* p_ml, libvlc_media_t* p_md, int i_pos )
    {
        return media_list_insert_media_( p_ml, p_md, i_pos );
    }
    int libvlc_media_list_remove_index( libvlc_media_list_t* p_ml, int i_pos )
    {
        return media_list_remove_index_( p_ml, i_pos );
    }
    int libvlc_media_list_count( libvlc_media_list_t* p_ml )
    {
        return media_list_count_( p_ml );
    }
    libvlc_media_t* libvlc_media_list_item_at_index( libvlc_media_list_t* p_ml, int i_pos )
    {
        return media_list_item_at_index_( p_ml, i_pos );
    }
    int libvlc_media_list_index_of_item( libvlc_media_list_t* p_ml, libvlc_media_t* p_md )
    {
        return media_list_index_of_item_( p_ml, p_md );
    }
    int libvlc_media_list_is_readonly( libvlc_media_list_t* p_ml )
    {
        return media_list_is_readonly_( p_ml );
    }
    void libvlc_media_list_lock( libvlc_media_list_t* p_ml )
    {
        media_list_lock_( p_ml );
    }
    void libvlc_media_list_unlock( libvlc_media_list_t* p_ml )
    {
        media_list_unlock_( p_ml );
    }
    libvlc_event_manager_t* libvlc_media_list_event_manager( libvlc_media_list_t* p_ml )
    {
        return media_list_event_manager_( p_ml );
    }

    // Media list player
    libvlc_media_list_player_t* libvlc_media_list_player_new( libvlc_instance_t* p_instance )
    {
        return media_list_player_new_( p_instance );
    }
    void libvlc_media_list_player_release( libvlc_media_list_player_t* p_mlp )
    {
        media_list_player_release_( p_mlp );
    }
    void libvlc_media_list_player_retain( libvlc_media_list_player_t* p_mlp )
    {
        media_list_player_retain_( p_mlp );
    }
    libvlc_event_manager_t* libvlc_media_list_player_event_manager( libvlc_media_list_player_t* p_mlp )
    {
        return media_list_player_event_manager_( p_mlp );
    }
    void libvlc_media_list_player_set_media_player( libvlc_media_list_player_t* p_mlp, libvlc_media_player_t* p_mi )
    {
        media_list_player_set_media_player_( p_mlp, p_mi );
    }
    libvlc_media_player_t* libvlc_media_list_player_get_media_player( libvlc_media_list_player_t* p_mlp )
    {
        return media_list_player_get_media_player_( p_mlp );
    }
    void libvlc_media_list_player_set_media_list( libvlc_media_list_player_t* p_mlp, libvlc_media_list_t* p_mlist )
    {
        media_list_player_set_media_list_( p_mlp, p_mlist );
    }
    void libvlc_media_list_player_play( libvlc_media_list_player_t* p_mlp )
    {
        media_list_player_play_( p_mlp );
    }
    void libvlc_media_list_player_pause( libvlc_media_list_player_t* p_mlp )
    {
        media_list_player_pause_( p_mlp );
    }
    void libvlc_media_list_player_set_pause( libvlc_media_list_player_t* p_mlp, int do_pause )
    {
        media_list_player_set_pause_( p_mlp, do_pause );
    }
    int libvlc_media_list_player_is_playing( libvlc_media_list_player_t* p_mlp )
    {
        return media_list_player_is_playing_( p_mlp );
    }
    libvlc_state_t libvlc_media_list_player_get_state( libvlc_media_list_player_t* p_mlp )
    {
        return media_list_player_get_state_( p_mlp );
    }
    int libvlc_media_list_player_play_item_at_index( libvlc_media_list_player_t* p_mlp, int i_index )
    {
        return media_list_player_play_item_at_index_( p_mlp, i_index );
    }
    int libvlc_media_list_player_play_item( libvlc_media_list_player_t* p_mlp, libvlc_media_t* p_md )
    {
        return media_list_player_play_item_( p_mlp, p_md );
    }
    void libvlc_media_list_player_stop( libvlc_media_list_player_t* p_mlp )
    {
        media_list_player_stop_( p_mlp );
    }
    int libvlc_media_list_player_next( libvlc_media_list_player_t* p_mlp )
    {
        return media_list_player_next_( p_mlp );
    }
    int libvlc_media_list_player_previous( libvlc_media_list_player_t* p_mlp )
    {
        return media_list_player_previous_( p_mlp );
    }
    void libvlc_media_list_player_set_playback_mode( libvlc_media_list_player_t* p_mlp, libvlc_playback_mode_t e_mode )
    {
        media_list_player_set_playback_mode_( p_mlp, e_mode );
    }


    // Media player
    libvlc_media_player_t* libvlc_media_player_new( libvlc_instance_t* p_libvlc_instance )
    {
        return media_player_new_( p_libvlc_instance );
    }
    libvlc_media_player_t* libvlc_media_player_new_from_media( libvlc_media_t* p_md )
    {
        return media_player_new_from_media_( p_md );
    }
    void libvlc_media_player_release( libvlc_media_player_t* p_mi )
    {
        media_player_release_( p_mi );
    }
    void libvlc_media_player_retain( libvlc_media_player_t* p_mi )
    {
        media_player_retain_( p_mi );
    }
    void libvlc_media_player_set_media( libvlc_media_player_t* p_mi, libvlc_media_t* p_md )
    {
        media_player_set_media_( p_mi, p_md );
    }
    libvlc_media_t* libvlc_media_player_get_media( libvlc_media_player_t* p_mi )
    {
        return media_player_get_media_( p_mi );
    }
    libvlc_event_manager_t* libvlc_media_player_event_manager( libvlc_media_player_t* p_mi )
    {
        return media_player_event_manager_( p_mi );
    }
    int libvlc_media_player_is_playing( libvlc_media_player_t* p_mi )
    {
        return media_player_is_playing_( p_mi );
    }
    int libvlc_media_player_play( libvlc_media_player_t* p_mi )
    {
        return media_player_play_( p_mi );
    }
    void libvlc_media_player_set_pause( libvlc_media_player_t* mp, int do_pause )
    {
        media_player_set_pause_( mp, do_pause );
    }
    void libvlc_media_player_pause( libvlc_media_player_t* p_mi )
    {
        media_player_pause_( p_mi );
    }
    void libvlc_media_player_stop( libvlc_media_player_t* p_mi )
    {
        media_player_stop_( p_mi );
    }
    int libvlc_media_player_set_renderer( libvlc_media_player_t* p_mi, libvlc_renderer_item_t* p_item )
    {
        return media_player_set_renderer_( p_mi, p_item );
    }
    void libvlc_video_set_callbacks( libvlc_media_player_t* mp, libvlc_video_lock_cb lock, libvlc_video_unlock_cb unlock, libvlc_video_display_cb display, void* opaque )
    {
        video_set_callbacks_( mp, lock, unlock, display, opaque );
    }
    void libvlc_video_set_format( libvlc_media_player_t* mp, const char* chroma, unsigned width, unsigned height, unsigned pitch )
    {
        video_set_format_( mp, chroma, width, height, pitch );
    }
    void libvlc_video_set_format_callbacks( libvlc_media_player_t* mp, libvlc_video_format_cb setup, libvlc_video_cleanup_cb cleanup )
    {
        video_set_format_callbacks_( mp, setup, cleanup );
    }
    void libvlc_media_player_set_nsobject( libvlc_media_player_t* p_mi, void* drawable )
    {
        media_player_set_nsobject_( p_mi, drawable );
    }
    void* libvlc_media_player_get_nsobject( libvlc_media_player_t* p_mi )
    {
        return media_player_get_nsobject_( p_mi );
    }
    void libvlc_media_player_set_xwindow( libvlc_media_player_t* p_mi, uint32_t drawable )
    {
        media_player_set_xwindow_( p_mi, drawable );
    }
    uint32_t libvlc_media_player_get_xwindow( libvlc_media_player_t* p_mi )
    {
        return media_player_get_xwindow_( p_mi );
    }
    void libvlc_media_player_set_hwnd( libvlc_media_player_t* p_mi, void* drawable )
    {
        media_player_set_hwnd_( p_mi, drawable );
    }
    void* libvlc_media_player_get_hwnd( libvlc_media_player_t* p_mi )
    {
        return media_player_get_hwnd_( p_mi );
    }
    void libvlc_media_player_set_android_context( libvlc_media_player_t* p_mi, void* p_awindow_handler )
    {
        media_player_set_android_context_( p_mi, p_awindow_handler );
    }
    int libvlc_media_player_set_evas_object( libvlc_media_player_t* p_mi, void* p_evas_object )
    {
        return media_player_set_evas_object_( p_mi, p_evas_object );
    }
    void libvlc_audio_set_callbacks( libvlc_media_player_t* mp, libvlc_audio_play_cb play, libvlc_audio_pause_cb pause, libvlc_audio_resume_cb resume, libvlc_audio_flush_cb flush, libvlc_audio_drain_cb drain, void* opaque )
    {
        audio_set_callbacks_( mp, play, pause, resume, flush, drain, opaque );
    }
    void libvlc_audio_set_volume_callback( libvlc_media_player_t* mp, libvlc_audio_set_volume_cb set_volume )
    {
        audio_set_volume_callback_( mp, set_volume );
    }
    void libvlc_audio_set_format_callbacks( libvlc_media_player_t* mp, libvlc_audio_setup_cb setup, libvlc_audio_cleanup_cb cleanup )
    {
        audio_set_format_callbacks_( mp, setup, cleanup );
    }
    void libvlc_audio_set_format( libvlc_media_player_t* mp, const char* format, unsigned rate, unsigned channels )
    {
        audio_set_format_( mp, format, rate, channels );
    }
    libvlc_time_t libvlc_media_player_get_length( libvlc_media_player_t* p_mi )
    {
        return media_player_get_length_( p_mi );
    }
    libvlc_time_t libvlc_media_player_get_time( libvlc_media_player_t* p_mi )
    {
        return media_player_get_time_( p_mi );
    }
    void libvlc_media_player_set_time( libvlc_media_player_t* p_mi, libvlc_time_t i_time )
    {
        media_player_set_time_( p_mi, i_time );
    }
    float libvlc_media_player_get_position( libvlc_media_player_t* p_mi )
    {
        return media_player_get_position_( p_mi );
    }
    void libvlc_media_player_set_position( libvlc_media_player_t* p_mi, float f_pos )
    {
        media_player_set_position_( p_mi, f_pos );
    }
    void libvlc_media_player_set_chapter( libvlc_media_player_t* p_mi, int i_chapter )
    {
        media_player_set_chapter_( p_mi, i_chapter );
    }
    int libvlc_media_player_get_chapter( libvlc_media_player_t* p_mi )
    {
        return media_player_get_chapter_( p_mi );
    }
    int libvlc_media_player_get_chapter_count( libvlc_media_player_t* p_mi )
    {
        return media_player_get_chapter_count_( p_mi );
    }
    int libvlc_media_player_will_play( libvlc_media_player_t* p_mi )
    {
        return media_player_will_play_( p_mi );
    }
    int libvlc_media_player_get_chapter_count_for_title( libvlc_media_player_t* p_mi, int i_title )
    {
        return media_player_get_chapter_count_for_title_( p_mi, i_title );
    }
    void libvlc_media_player_set_title( libvlc_media_player_t* p_mi, int i_title )
    {
        media_player_set_title_( p_mi, i_title );
    }
    int libvlc_media_player_get_title( libvlc_media_player_t* p_mi )
    {
        return media_player_get_title_( p_mi );
    }
    int libvlc_media_player_get_title_count( libvlc_media_player_t* p_mi )
    {
        return media_player_get_title_count_( p_mi );
    }
    void libvlc_media_player_previous_chapter( libvlc_media_player_t* p_mi )
    {
        media_player_previous_chapter_( p_mi );
    }
    void libvlc_media_player_next_chapter( libvlc_media_player_t* p_mi )
    {
        media_player_next_chapter_( p_mi );
    }
    float libvlc_media_player_get_rate( libvlc_media_player_t* p_mi )
    {
        return media_player_get_rate_( p_mi );
    }
    int libvlc_media_player_set_rate( libvlc_media_player_t* p_mi, float rate )
    {
        return media_player_set_rate_( p_mi, rate );
    }
    libvlc_state_t libvlc_media_player_get_state( libvlc_media_player_t* p_mi )
    {
        return media_player_get_state_( p_mi );
    }
    unsigned libvlc_media_player_has_vout( libvlc_media_player_t* p_mi )
    {
        return media_player_has_vout_( p_mi );
    }
    int libvlc_media_player_is_seekable( libvlc_media_player_t* p_mi )
    {
        return media_player_is_seekable_( p_mi );
    }
    int libvlc_media_player_can_pause( libvlc_media_player_t* p_mi )
    {
        return media_player_can_pause_( p_mi );
    }
    int libvlc_media_player_program_scrambled( libvlc_media_player_t* p_mi )
    {
        return media_player_program_scrambled_( p_mi );
    }
    void libvlc_media_player_next_frame( libvlc_media_player_t* p_mi )
    {
        media_player_next_frame_( p_mi );
    }
    void libvlc_media_player_navigate( libvlc_media_player_t* p_mi, unsigned navigate )
    {
        media_player_navigate_( p_mi, navigate );
    }
    void libvlc_media_player_set_video_title_display( libvlc_media_player_t* p_mi, libvlc_position_t position, unsigned int timeout )
    {
        media_player_set_video_title_display_( p_mi, position, timeout );
    }
    int libvlc_media_player_add_slave( libvlc_media_player_t* p_mi, libvlc_media_slave_type_t i_type, const char* psz_uri, bool b_select )
    {
        return media_player_add_slave_( p_mi, i_type, psz_uri, b_select );
    }
    void libvlc_track_description_list_release( libvlc_track_description_t* p_track_description )
    {
        track_description_list_release_( p_track_description );
    }
    void libvlc_toggle_fullscreen( libvlc_media_player_t* p_mi )
    {
        toggle_fullscreen_( p_mi );
    }
    void libvlc_set_fullscreen( libvlc_media_player_t* p_mi, int b_fullscreen )
    {
        set_fullscreen_( p_mi, b_fullscreen );
    }
    int libvlc_get_fullscreen( libvlc_media_player_t* p_mi )
    {
        return get_fullscreen_( p_mi );
    }
    void libvlc_video_set_key_input( libvlc_media_player_t* p_mi, unsigned on )
    {
        video_set_key_input_( p_mi, on );
    }
    void libvlc_video_set_mouse_input( libvlc_media_player_t* p_mi, unsigned on )
    {
        video_set_mouse_input_( p_mi, on );
    }
    int libvlc_video_get_size( libvlc_media_player_t* p_mi, unsigned num, unsigned* px, unsigned* py )
    {
        return video_get_size_( p_mi, num, px, py );
    }
    int libvlc_video_get_cursor( libvlc_media_player_t* p_mi, unsigned num, int* px, int* py )
    {
        return video_get_cursor_( p_mi, num, px, py );
    }
    float libvlc_video_get_scale( libvlc_media_player_t* p_mi )
    {
        return video_get_scale_( p_mi );
    }
    void libvlc_video_set_scale( libvlc_media_player_t* p_mi, float f_factor )
    {
        video_set_scale_( p_mi, f_factor );
    }
    char* libvlc_video_get_aspect_ratio( libvlc_media_player_t* p_mi )
    {
        return video_get_aspect_ratio_( p_mi );
    }
    void libvlc_video_set_aspect_ratio( libvlc_media_player_t* p_mi, const char* psz_aspect )
    {
        video_set_aspect_ratio_( p_mi, psz_aspect );
    }
    libvlc_video_viewpoint_t* libvlc_video_new_viewpoint( void )
    {
        return video_new_viewpoint_( );
    }
    int libvlc_video_update_viewpoint( libvlc_media_player_t* p_mi, const libvlc_video_viewpoint_t* p_viewpoint, bool b_absolute )
    {
        return video_update_viewpoint_( p_mi, p_viewpoint, b_absolute );
    }
    int libvlc_video_get_spu( libvlc_media_player_t* p_mi )
    {
        return video_get_spu_( p_mi );
    }
    int libvlc_video_get_spu_count( libvlc_media_player_t* p_mi )
    {
        return video_get_spu_count_( p_mi );
    }
    libvlc_track_description_t* libvlc_video_get_spu_description( libvlc_media_player_t* p_mi )
    {
        return video_get_spu_description_( p_mi );
    }
    int libvlc_video_set_spu( libvlc_media_player_t* p_mi, int i_spu )
    {
        return video_set_spu_( p_mi, i_spu );
    }
    int64_t libvlc_video_get_spu_delay( libvlc_media_player_t* p_mi )
    {
        return video_get_spu_delay_( p_mi );
    }
    int libvlc_video_set_spu_delay( libvlc_media_player_t* p_mi, int64_t i_delay )
    {
        return video_set_spu_delay_( p_mi, i_delay );
    }
    int libvlc_media_player_get_full_title_descriptions( libvlc_media_player_t* p_mi, libvlc_title_description_t*** titles )
    {
        return media_player_get_full_title_descriptions_( p_mi, titles );
    }
    void libvlc_title_descriptions_release( libvlc_title_description_t** p_titles, unsigned i_count )
    {
        title_descriptions_release_( p_titles, i_count );
    }
    int libvlc_media_player_get_full_chapter_descriptions( libvlc_media_player_t* p_mi, int i_chapters_of_title, libvlc_chapter_description_t*** pp_chapters )
    {
        return media_player_get_full_chapter_descriptions_( p_mi, i_chapters_of_title, pp_chapters );
    }
    void libvlc_chapter_descriptions_release( libvlc_chapter_description_t** p_chapters, unsigned i_count )
    {
        chapter_descriptions_release_( p_chapters, i_count );
    }
    char* libvlc_video_get_crop_geometry( libvlc_media_player_t* p_mi )
    {
        return video_get_crop_geometry_( p_mi );
    }
    void libvlc_video_set_crop_geometry( libvlc_media_player_t* p_mi, const char* psz_geometry )
    {
        video_set_crop_geometry_( p_mi, psz_geometry );
    }
    int libvlc_video_get_teletext( libvlc_media_player_t* p_mi )
    {
        return video_get_teletext_( p_mi );
    }
    void libvlc_video_set_teletext( libvlc_media_player_t* p_mi, int i_page )
    {
        video_set_teletext_( p_mi, i_page );
    }
    int libvlc_video_get_track_count( libvlc_media_player_t* p_mi )
    {
        return video_get_track_count_( p_mi );
    }
    libvlc_track_description_t* libvlc_video_get_track_description( libvlc_media_player_t* p_mi )
    {
        return video_get_track_description_( p_mi );
    }
    int libvlc_video_get_track( libvlc_media_player_t* p_mi )
    {
        return video_get_track_( p_mi );
    }
    int libvlc_video_set_track( libvlc_media_player_t* p_mi, int i_track )
    {
        return video_set_track_( p_mi, i_track );
    }
    int libvlc_video_take_snapshot( libvlc_media_player_t* p_mi, unsigned num, const char* psz_filepath, unsigned int i_width, unsigned int i_height )
    {
        return video_take_snapshot_( p_mi, num, psz_filepath, i_width, i_height );
    }
    void libvlc_video_set_deinterlace( libvlc_media_player_t* p_mi, const char* psz_mode )
    {
        video_set_deinterlace_( p_mi, psz_mode );
    }
    int libvlc_video_get_marquee_int( libvlc_media_player_t* p_mi, unsigned option )
    {
        return video_get_marquee_int_( p_mi, option );
    }
    char* libvlc_video_get_marquee_string( libvlc_media_player_t* p_mi, unsigned option )
    {
        return video_get_marquee_string_( p_mi, option );
    }
    void libvlc_video_set_marquee_int( libvlc_media_player_t* p_mi, unsigned option, int i_val )
    {
        video_set_marquee_int_( p_mi, option, i_val );
    }
    void libvlc_video_set_marquee_string( libvlc_media_player_t* p_mi, unsigned option, const char* psz_text )
    {
        video_set_marquee_string_( p_mi, option, psz_text );
    }
    int libvlc_video_get_logo_int( libvlc_media_player_t* p_mi, unsigned option )
    {
        return video_get_logo_int_( p_mi, option );
    }
    void libvlc_video_set_logo_int( libvlc_media_player_t* p_mi, unsigned option, int value )
    {
        video_set_logo_int_( p_mi, option, value );
    }
    void libvlc_video_set_logo_string( libvlc_media_player_t* p_mi, unsigned option, const char* psz_value )
    {
        video_set_logo_string_( p_mi, option, psz_value );
    }
    int libvlc_video_get_adjust_int( libvlc_media_player_t* p_mi, unsigned option )
    {
        return video_get_adjust_int_( p_mi, option );
    }
    void libvlc_video_set_adjust_int( libvlc_media_player_t* p_mi, unsigned option, int value )
    {
        video_set_adjust_int_( p_mi, option, value );
    }
    float libvlc_video_get_adjust_float( libvlc_media_player_t* p_mi, unsigned option )
    {
        return video_get_adjust_float_( p_mi, option );
    }
    void libvlc_video_set_adjust_float( libvlc_media_player_t* p_mi, unsigned option, float value )
    {
        video_set_adjust_float_( p_mi, option, value );
    }
    libvlc_audio_output_t* libvlc_audio_output_list_get( libvlc_instance_t* p_instance )
    {
        return audio_output_list_get_( p_instance );
    }
    void libvlc_audio_output_list_release( libvlc_audio_output_t* p_list )
    {
        audio_output_list_release_( p_list );
    }
    int libvlc_audio_output_set( libvlc_media_player_t* p_mi, const char* psz_name )
    {
        return audio_output_set_( p_mi, psz_name );
    }
    libvlc_audio_output_device_t* libvlc_audio_output_device_enum( libvlc_media_player_t* mp )
    {
        return audio_output_device_enum_( mp );
    }
    libvlc_audio_output_device_t* libvlc_audio_output_device_list_get( libvlc_instance_t* p_instance, const char* aout )
    {
        return audio_output_device_list_get_( p_instance, aout );
    }
    void libvlc_audio_output_device_list_release( libvlc_audio_output_device_t* p_list )
    {
        audio_output_device_list_release_( p_list );
    }
    void libvlc_audio_output_device_set( libvlc_media_player_t* mp, const char* module, const char* device_id )
    {
        audio_output_device_set_( mp, module, device_id );
    }
    char* libvlc_audio_output_device_get( libvlc_media_player_t* mp )
    {
        return audio_output_device_get_( mp );
    }
    void libvlc_audio_toggle_mute( libvlc_media_player_t* p_mi )
    {
        audio_toggle_mute_( p_mi );
    }
    int libvlc_audio_get_mute( libvlc_media_player_t* p_mi )
    {
        return audio_get_mute_( p_mi );
    }
    void libvlc_audio_set_mute( libvlc_media_player_t* p_mi, int status )
    {
        audio_set_mute_( p_mi, status );
    }
    int libvlc_audio_get_volume( libvlc_media_player_t* p_mi )
    {
        return audio_get_volume_( p_mi );
    }
    int libvlc_audio_set_volume( libvlc_media_player_t* p_mi, int i_volume )
    {
        return audio_set_volume_( p_mi, i_volume );
    }
    int libvlc_audio_get_track_count( libvlc_media_player_t* p_mi )
    {
        return audio_get_track_count_( p_mi );
    }
    libvlc_track_description_t* libvlc_audio_get_track_description( libvlc_media_player_t* p_mi )
    {
        return audio_get_track_description_( p_mi );
    }
    int libvlc_audio_get_track( libvlc_media_player_t* p_mi )
    {
        return audio_get_track_( p_mi );
    }
    int libvlc_audio_set_track( libvlc_media_player_t* p_mi, int i_track )
    {
        return audio_set_track_( p_mi, i_track );
    }
    int libvlc_audio_get_channel( libvlc_media_player_t* p_mi )
    {
        return audio_get_channel_( p_mi );
    }
    int libvlc_audio_set_channel( libvlc_media_player_t* p_mi, int channel )
    {
        return audio_set_channel_( p_mi, channel );
    }
    int64_t libvlc_audio_get_delay( libvlc_media_player_t* p_mi )
    {
        return audio_get_delay_( p_mi );
    }
    int libvlc_audio_set_delay( libvlc_media_player_t* p_mi, int64_t i_delay )
    {
        return audio_set_delay_( p_mi, i_delay );
    }
    unsigned libvlc_audio_equalizer_get_preset_count( void )
    {
        return audio_equalizer_get_preset_count_( );
    }
    const char* libvlc_audio_equalizer_get_preset_name( unsigned u_index )
    {
        return audio_equalizer_get_preset_name_( u_index );
    }
    unsigned libvlc_audio_equalizer_get_band_count( void )
    {
        return audio_equalizer_get_band_count_( );
    }
    float libvlc_audio_equalizer_get_band_frequency( unsigned u_index )
    {
        return audio_equalizer_get_band_frequency_( u_index );
    }
    libvlc_equalizer_t* libvlc_audio_equalizer_new( void )
    {
        return audio_equalizer_new_( );
    }
    libvlc_equalizer_t* libvlc_audio_equalizer_new_from_preset( unsigned u_index )
    {
        return audio_equalizer_new_from_preset_( u_index );
    }
    void libvlc_audio_equalizer_release( libvlc_equalizer_t* p_equalizer )
    {
        audio_equalizer_release_( p_equalizer );
    }
    int libvlc_audio_equalizer_set_preamp( libvlc_equalizer_t* p_equalizer, float f_preamp )
    {
        return audio_equalizer_set_preamp_( p_equalizer, f_preamp );
    }
    float libvlc_audio_equalizer_get_preamp( libvlc_equalizer_t* p_equalizer )
    {
        return audio_equalizer_get_preamp_( p_equalizer );
    }
    int libvlc_audio_equalizer_set_amp_at_index( libvlc_equalizer_t* p_equalizer, float f_amp, unsigned u_band )
    {
        return audio_equalizer_set_amp_at_index_( p_equalizer, f_amp, u_band );
    }
    float libvlc_audio_equalizer_get_amp_at_index( libvlc_equalizer_t* p_equalizer, unsigned u_band )
    {
        return audio_equalizer_get_amp_at_index_( p_equalizer, u_band );
    }
    int libvlc_media_player_set_equalizer( libvlc_media_player_t* p_mi, libvlc_equalizer_t* p_equalizer )
    {
        return media_player_set_equalizer_( p_mi, p_equalizer );
    }
    int libvlc_media_player_get_role( libvlc_media_player_t* p_mi )
    {
        return media_player_get_role_( p_mi );
    }
    int libvlc_media_player_set_role( libvlc_media_player_t* p_mi, unsigned role )
    {
        return media_player_set_role_( p_mi, role );
    }


    // VLM
    void libvlc_vlm_release( libvlc_instance_t* p_instance )
    {
        vlm_release_( p_instance );
    }
    int libvlc_vlm_add_broadcast( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input, const char* psz_output, int i_options, const char* const* ppsz_options, int b_enabled, int b_loop )
    {
        return vlm_add_broadcast_( p_instance, psz_name, psz_input, psz_output, i_options, ppsz_options, b_enabled, b_loop );
    }
    int libvlc_vlm_add_vod( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input, int i_options, const char* const* ppsz_options, int b_enabled, const char* psz_mux )
    {
        return vlm_add_vod_( p_instance, psz_name, psz_input, i_options, ppsz_options, b_enabled, psz_mux );
    }
    int libvlc_vlm_del_media( libvlc_instance_t* p_instance, const char* psz_name )
    {
        return vlm_del_media_( p_instance, psz_name );
    }
    int libvlc_vlm_set_enabled( libvlc_instance_t* p_instance, const char* psz_name, int b_enabled )
    {
        return vlm_set_enabled_( p_instance, psz_name, b_enabled );
    }
    int libvlc_vlm_set_output( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_output )
    {
        return vlm_set_output_( p_instance, psz_name, psz_output );
    }
    int libvlc_vlm_set_input( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input )
    {
        return vlm_set_input_( p_instance, psz_name, psz_input );
    }
    int libvlc_vlm_add_input( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input )
    {
        return vlm_add_input_( p_instance, psz_name, psz_input );
    }
    int libvlc_vlm_set_loop( libvlc_instance_t* p_instance, const char* psz_name, int b_loop )
    {
        return vlm_set_loop_( p_instance, psz_name, b_loop );
    }
    int libvlc_vlm_set_mux( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_mux )
    {
        return vlm_set_mux_( p_instance, psz_name, psz_mux );
    }
    int libvlc_vlm_change_media( libvlc_instance_t* p_instance, const char* psz_name, const char* psz_input, const char* psz_output, int i_options, const char* const* ppsz_options, int b_enabled, int b_loop )
    {
        return vlm_change_media_( p_instance, psz_name, psz_input, psz_output, i_options, ppsz_options, b_enabled, b_loop );
    }
    int libvlc_vlm_play_media( libvlc_instance_t* p_instance, const char* psz_name )
    {
        return vlm_play_media_( p_instance, psz_name );
    }
    int libvlc_vlm_stop_media( libvlc_instance_t* p_instance, const char* psz_name )
    {
        return vlm_stop_media_( p_instance, psz_name );
    }
    int libvlc_vlm_pause_media( libvlc_instance_t* p_instance, const char* psz_name )
    {
        return vlm_pause_media_( p_instance, psz_name );
    }
    int libvlc_vlm_seek_media( libvlc_instance_t* p_instance, const char* psz_name, float f_percentage )
    {
        return vlm_seek_media_( p_instance, psz_name, f_percentage );
    }
    const char* libvlc_vlm_show_media( libvlc_instance_t* p_instance, const char* psz_name )
    {
        return vlm_show_media_( p_instance, psz_name );
    }
    float libvlc_vlm_get_media_instance_position( libvlc_instance_t* p_instance, const char* psz_name, int i_instance )
    {
        return vlm_get_media_instance_position_( p_instance, psz_name, i_instance );
    }
    int libvlc_vlm_get_media_instance_time( libvlc_instance_t* p_instance, const char* psz_name, int i_instance )
    {
        return vlm_get_media_instance_time_( p_instance, psz_name, i_instance );
    }
    int libvlc_vlm_get_media_instance_length( libvlc_instance_t* p_instance, const char* psz_name, int i_instance )
    {
        return vlm_get_media_instance_length_( p_instance, psz_name, i_instance );
    }
    int libvlc_vlm_get_media_instance_rate( libvlc_instance_t* p_instance, const char* psz_name, int i_instance )
    {
        return vlm_get_media_instance_rate_( p_instance, psz_name, i_instance );
    }
    libvlc_event_manager_t* libvlc_vlm_get_event_manager( libvlc_instance_t* p_instance )
    {
        return vlm_get_event_manager_( p_instance );
    }

    

};
#endif
#endif