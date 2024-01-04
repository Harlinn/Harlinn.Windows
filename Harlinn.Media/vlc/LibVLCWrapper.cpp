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


namespace
{
    std::unique_ptr<LibVLC> instance;
}

LibVLC::LibVLC( )
{
    moduleHandle_ = ModuleHandle( libVlcDll_, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR );
    Initialize( );
}

LibVLC* LibVLC::Instance( )
{
    if ( instance == nullptr )
    {
        instance = std::make_unique<LibVLC>( );
    }
    return instance.get( );
}

void LibVLC::Initialize( )
{
    errmsg_ = ( libvlc_errmsg_func_t )moduleHandle_.GetProcAddress( "libvlc_errmsg" );
    clearerr_ = ( libvlc_clearerr_func_t )moduleHandle_.GetProcAddress( "libvlc_clearerr" );
    vprinterr_ = ( libvlc_vprinterr_func_t )moduleHandle_.GetProcAddress( "libvlc_vprinterr" );
    printerr_ = ( libvlc_printerr_func_t )moduleHandle_.GetProcAddress( "libvlc_printerr" );
    new_ = ( libvlc_new_func_t )moduleHandle_.GetProcAddress( "libvlc_new" );
    release_ = ( libvlc_release_func_t )moduleHandle_.GetProcAddress( "libvlc_release" );
    retain_ = (libvlc_retain_func_t)moduleHandle_.GetProcAddress( "libvlc_retain" );
    add_intf_ = ( libvlc_add_intf_func_t )moduleHandle_.GetProcAddress( "libvlc_add_intf" );
    set_exit_handler_ = ( libvlc_set_exit_handler_func_t )moduleHandle_.GetProcAddress( "libvlc_set_exit_handler" );
    set_user_agent_ = ( libvlc_set_user_agent_func_t )moduleHandle_.GetProcAddress( "libvlc_set_user_agent" );
    set_app_id_ = ( libvlc_set_app_id_func_t )moduleHandle_.GetProcAddress( "libvlc_set_app_id" );
    get_version_ = ( libvlc_get_version_func_t )moduleHandle_.GetProcAddress( "libvlc_get_version" );
    get_compiler_ = ( libvlc_get_compiler_func_t )moduleHandle_.GetProcAddress( "libvlc_get_compiler" );
    get_changeset_ = ( libvlc_get_changeset_func_t )moduleHandle_.GetProcAddress( "libvlc_get_changeset" );
    free_ = ( libvlc_free_func_t )moduleHandle_.GetProcAddress( "libvlc_free" );
    event_attach_ = ( libvlc_event_attach_func_t )moduleHandle_.GetProcAddress( "libvlc_event_attach" );
    event_detach_ = ( libvlc_event_detach_func_t )moduleHandle_.GetProcAddress( "libvlc_event_detach" );
    event_type_name_ = ( libvlc_event_type_name_func_t )moduleHandle_.GetProcAddress( "libvlc_event_type_name" );
    log_get_context_ = ( libvlc_log_get_context_func_t )moduleHandle_.GetProcAddress( "libvlc_log_get_context" );
    log_get_object_ = ( libvlc_log_get_object_func_t )moduleHandle_.GetProcAddress( "libvlc_log_get_object" );
    log_unset_ = ( libvlc_log_unset_func_t )moduleHandle_.GetProcAddress( "libvlc_log_unset" );
    log_set_ = ( libvlc_log_set_func_t )moduleHandle_.GetProcAddress( "libvlc_log_set" );
    log_set_file_ = ( libvlc_log_set_file_func_t )moduleHandle_.GetProcAddress( "libvlc_log_set_file" );
    module_description_list_release_ = ( libvlc_module_description_list_release_func_t )moduleHandle_.GetProcAddress( "libvlc_module_description_list_release" );
    audio_filter_list_get_ = ( libvlc_audio_filter_list_get_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_filter_list_get" );
    video_filter_list_get_ = ( libvlc_video_filter_list_get_func_t )moduleHandle_.GetProcAddress( "libvlc_video_filter_list_get" );
    clock_ = ( libvlc_clock_func_t )moduleHandle_.GetProcAddress( "libvlc_clock" );

    // Deprecated
    media_player_get_fps_ = (libvlc_media_player_get_fps_func_t)moduleHandle_.GetProcAddress( "libvlc_media_player_get_fp" );
    media_player_set_agl_ = ( libvlc_media_player_set_agl_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_ag" );
    media_player_get_agl_ = ( libvlc_media_player_get_agl_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_ag" );
    track_description_release_ = ( libvlc_track_description_release_func_t )moduleHandle_.GetProcAddress( "libvlc_track_description_release" );
    video_get_height_ = ( libvlc_video_get_height_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_height" );
    video_get_width_ = ( libvlc_video_get_width_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_width" );
    video_get_title_description_ = ( libvlc_video_get_title_description_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_title_description" );
    video_get_chapter_description_ = ( libvlc_video_get_chapter_description_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_chapter_description" );
    video_set_subtitle_file_ = ( libvlc_video_set_subtitle_file_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_subtitle_file" );
    toggle_teletext_ = ( libvlc_toggle_teletext_func_t )moduleHandle_.GetProcAddress( "libvlc_toggle_teletext" );
    audio_output_device_count_ = ( libvlc_audio_output_device_count_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_output_device_count" );
    audio_output_device_longname_ = ( libvlc_audio_output_device_longname_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_output_device_longname" );
    audio_output_device_id_ = ( libvlc_audio_output_device_id_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_output_device_id" );
    audio_output_get_device_type_ = ( libvlc_audio_output_get_device_type_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_output_get_device_type" );
    audio_output_set_device_type_ = ( libvlc_audio_output_set_device_type_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_output_set_device_type" );
    media_parse_ = ( libvlc_media_parse_func_t )moduleHandle_.GetProcAddress( "libvlc_media_parse" );
    media_parse_async_ = ( libvlc_media_parse_async_func_t )moduleHandle_.GetProcAddress( "libvlc_media_parse_async" );
    media_is_parsed_ = ( libvlc_media_is_parsed_func_t )moduleHandle_.GetProcAddress( "libvlc_media_is_parsed" );
    media_get_tracks_info_ = ( libvlc_media_get_tracks_info_func_t )moduleHandle_.GetProcAddress( "libvlc_media_get_tracks_info" );
    media_discoverer_new_from_name_ = ( libvlc_media_discoverer_new_from_name_func_t )moduleHandle_.GetProcAddress( "libvlc_media_discoverer_new_from_name" );
    media_discoverer_localized_name_ = ( libvlc_media_discoverer_localized_name_func_t )moduleHandle_.GetProcAddress( "libvlc_media_discoverer_localized_name" );
    media_discoverer_event_manager_ = ( libvlc_media_discoverer_event_manager_func_t )moduleHandle_.GetProcAddress( "libvlc_media_discoverer_event_manager" );
    wait_ = ( libvlc_wait_func_t )moduleHandle_.GetProcAddress( "libvlc_wait" );
    get_log_verbosity_ = ( libvlc_get_log_verbosity_func_t )moduleHandle_.GetProcAddress( "libvlc_get_log_verbosity" );
    set_log_verbosity_ = ( libvlc_set_log_verbosity_func_t )moduleHandle_.GetProcAddress( "libvlc_set_log_verbosity" );
    log_open_ = ( libvlc_log_open_func_t )moduleHandle_.GetProcAddress( "libvlc_log_open" );
    log_close_ = ( libvlc_log_close_func_t )moduleHandle_.GetProcAddress( "libvlc_log_close" );
    log_count_ = ( libvlc_log_count_func_t )moduleHandle_.GetProcAddress( "libvlc_log_count" );
    log_clear_ = ( libvlc_log_clear_func_t )moduleHandle_.GetProcAddress( "libvlc_log_clear" );
    log_get_iterator_ = ( libvlc_log_get_iterator_func_t )moduleHandle_.GetProcAddress( "libvlc_log_get_iterator" );
    log_iterator_free_ = ( libvlc_log_iterator_free_func_t )moduleHandle_.GetProcAddress( "libvlc_log_iterator_free" );
    log_iterator_has_next_ = ( libvlc_log_iterator_has_next_func_t )moduleHandle_.GetProcAddress( "libvlc_log_iterator_has_next" );
    log_iterator_next_ = ( libvlc_log_iterator_next_func_t )moduleHandle_.GetProcAddress( "libvlc_log_iterator_next" );
    playlist_play_ = ( libvlc_playlist_play_func_t )moduleHandle_.GetProcAddress( "libvlc_playlist_play" );

    // Dialog
    dialog_set_callbacks_ = (libvlc_dialog_set_callbacks_func_t)moduleHandle_.GetProcAddress( "libvlc_dialog_set_callbacks" );
    dialog_set_context_ = ( libvlc_dialog_set_context_func_t )moduleHandle_.GetProcAddress( "libvlc_dialog_set_context" );
    dialog_get_context_ = ( libvlc_dialog_get_context_func_t )moduleHandle_.GetProcAddress( "libvlc_dialog_get_context" );
    dialog_post_login_ = ( libvlc_dialog_post_login_func_t )moduleHandle_.GetProcAddress( "libvlc_dialog_post_login" );
    dialog_post_action_ = ( libvlc_dialog_post_action_func_t )moduleHandle_.GetProcAddress( "libvlc_dialog_post_action" );
    dialog_dismiss_ = ( libvlc_dialog_dismiss_func_t )moduleHandle_.GetProcAddress( "libvlc_dialog_dismiss" );

    // Media
    media_new_location_ = (libvlc_media_new_location_func_t )moduleHandle_.GetProcAddress( "libvlc_media_new_location" );
    media_new_path_ = ( libvlc_media_new_path_func_t )moduleHandle_.GetProcAddress( "libvlc_media_new_path" );
    media_new_fd_ = ( libvlc_media_new_fd_func_t )moduleHandle_.GetProcAddress( "libvlc_media_new_fd" );
    media_new_callbacks_ = ( libvlc_media_new_callbacks_func_t )moduleHandle_.GetProcAddress( "libvlc_media_new_callbacks" );
    media_new_as_node_ = ( libvlc_media_new_as_node_func_t )moduleHandle_.GetProcAddress( "libvlc_media_new_as_node" );
    media_add_option_ = ( libvlc_media_add_option_func_t )moduleHandle_.GetProcAddress( "libvlc_media_add_option" );
    media_add_option_flag_ = ( libvlc_media_add_option_flag_func_t )moduleHandle_.GetProcAddress( "libvlc_media_add_option_flag" );
    media_retain_ = ( libvlc_media_retain_func_t )moduleHandle_.GetProcAddress( "libvlc_media_retain" );
    media_release_ = ( libvlc_media_release_func_t )moduleHandle_.GetProcAddress( "libvlc_media_release" );
    media_get_mrl_ = ( libvlc_media_get_mrl_func_t )moduleHandle_.GetProcAddress( "libvlc_media_get_mrl" );
    media_duplicate_ = ( libvlc_media_duplicate_func_t )moduleHandle_.GetProcAddress( "libvlc_media_duplicate" );
    media_get_meta_ = ( libvlc_media_get_meta_func_t )moduleHandle_.GetProcAddress( "libvlc_media_get_meta" );
    media_set_meta_ = ( libvlc_media_set_meta_func_t )moduleHandle_.GetProcAddress( "libvlc_media_set_meta" );
    media_save_meta_ = ( libvlc_media_save_meta_func_t )moduleHandle_.GetProcAddress( "libvlc_media_save_meta" );
    media_get_state_ = ( libvlc_media_get_state_func_t )moduleHandle_.GetProcAddress( "libvlc_media_get_state" );
    media_get_stats_ = ( libvlc_media_get_stats_func_t )moduleHandle_.GetProcAddress( "libvlc_media_get_stats" );
    media_subitems_ = ( libvlc_media_subitems_func_t )moduleHandle_.GetProcAddress( "libvlc_media_subitems" );
    media_event_manager_ = ( libvlc_media_event_manager_func_t )moduleHandle_.GetProcAddress( "libvlc_media_event_manager" );
    media_get_duration_ = ( libvlc_media_get_duration_func_t )moduleHandle_.GetProcAddress( "libvlc_media_get_duration" );
    media_parse_with_options_ = ( libvlc_media_parse_with_options_func_t )moduleHandle_.GetProcAddress( "libvlc_media_parse_with_options" );
    media_parse_stop_ = ( libvlc_media_parse_stop_func_t )moduleHandle_.GetProcAddress( "libvlc_media_parse_stop" );
    media_get_parsed_status_ = ( libvlc_media_get_parsed_status_func_t )moduleHandle_.GetProcAddress( "libvlc_media_get_parsed_status" );
    media_set_user_data_ = ( libvlc_media_set_user_data_func_t )moduleHandle_.GetProcAddress( "libvlc_media_set_user_data" );
    media_get_user_data_ = ( libvlc_media_get_user_data_func_t )moduleHandle_.GetProcAddress( "libvlc_media_get_user_data" );
    media_tracks_get_ = ( libvlc_media_tracks_get_func_t )moduleHandle_.GetProcAddress( "libvlc_media_tracks_get" );
    media_get_codec_description_ = ( libvlc_media_get_codec_description_func_t )moduleHandle_.GetProcAddress( "libvlc_media_get_codec_description" );
    media_tracks_release_ = ( libvlc_media_tracks_release_func_t )moduleHandle_.GetProcAddress( "libvlc_media_tracks_release" );
    media_get_type_ = ( libvlc_media_get_type_func_t )moduleHandle_.GetProcAddress( "libvlc_media_get_type" );
    media_slaves_add_ = ( libvlc_media_slaves_add_func_t )moduleHandle_.GetProcAddress( "libvlc_media_slaves_add" );
    media_slaves_clear_ = ( libvlc_media_slaves_clear_func_t )moduleHandle_.GetProcAddress( "libvlc_media_slaves_clear" );
    media_slaves_get_ = ( libvlc_media_slaves_get_func_t )moduleHandle_.GetProcAddress( "libvlc_media_slaves_get" );
    media_slaves_release_ = ( libvlc_media_slaves_release_func_t )moduleHandle_.GetProcAddress( "libvlc_media_slaves_release" );

    media_discoverer_new_ = ( libvlc_media_discoverer_new_func_t )moduleHandle_.GetProcAddress( "libvlc_media_discoverer_new" );
    media_discoverer_start_ = ( libvlc_media_discoverer_start_func_t )moduleHandle_.GetProcAddress( "libvlc_media_discoverer_star" );
    media_discoverer_stop_ = ( libvlc_media_discoverer_stop_func_t )moduleHandle_.GetProcAddress( "libvlc_media_discoverer_stop" );
    media_discoverer_release_ = ( libvlc_media_discoverer_release_func_t )moduleHandle_.GetProcAddress( "libvlc_media_discoverer_release" );
    media_discoverer_media_list_ = ( libvlc_media_discoverer_media_list_func_t )moduleHandle_.GetProcAddress( "libvlc_media_discoverer_media_list" );
    media_discoverer_is_running_ = ( libvlc_media_discoverer_is_running_func_t )moduleHandle_.GetProcAddress( "libvlc_media_discoverer_is_running" );
    media_discoverer_list_get_ = ( libvlc_media_discoverer_list_get_func_t )moduleHandle_.GetProcAddress( "libvlc_media_discoverer_list_get" );
    media_discoverer_list_release_ = ( libvlc_media_discoverer_list_release_func_t )moduleHandle_.GetProcAddress( "libvlc_media_discoverer_list_release" );


    media_library_new_ = ( libvlc_media_library_new_func_t )moduleHandle_.GetProcAddress( "libvlc_media_library_new" );
    media_library_release_ = ( libvlc_media_library_release_func_t )moduleHandle_.GetProcAddress( "libvlc_media_library_release" );
    media_library_retain_ = ( libvlc_media_library_retain_func_t )moduleHandle_.GetProcAddress( "libvlc_media_library_retain" );
    media_library_load_ = ( libvlc_media_library_load_func_t )moduleHandle_.GetProcAddress( "libvlc_media_library_load" );
    media_library_media_list_ = ( libvlc_media_library_media_list_func_t )moduleHandle_.GetProcAddress( "libvlc_media_library_media_list" );

    media_list_new_ = ( libvlc_media_list_new_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_new" );
    media_list_release_ = ( libvlc_media_list_release_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_release" );
    media_list_retain_ = ( libvlc_media_list_retain_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_retain" );
    media_list_set_media_ = ( libvlc_media_list_set_media_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_set_media" );
    media_list_media_ = ( libvlc_media_list_media_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_media" );
    media_list_add_media_ = ( libvlc_media_list_add_media_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_add_media" );
    media_list_insert_media_ = ( libvlc_media_list_insert_media_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_insert_media" );
    media_list_remove_index_ = ( libvlc_media_list_remove_index_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_remove_index" );
    media_list_count_ = ( libvlc_media_list_count_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_count" );
    media_list_item_at_index_ = ( libvlc_media_list_item_at_index_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_item_at_index" );
    media_list_index_of_item_ = ( libvlc_media_list_index_of_item_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_index_of_item" );
    media_list_is_readonly_ = ( libvlc_media_list_is_readonly_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_is_readonly" );
    media_list_lock_ = ( libvlc_media_list_lock_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_lock" );
    media_list_unlock_ = ( libvlc_media_list_unlock_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_unlock" );
    media_list_event_manager_ = ( libvlc_media_list_event_manager_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_event_manager" );

    media_list_player_new_ = ( libvlc_media_list_player_new_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_new" );
    media_list_player_release_ = ( libvlc_media_list_player_release_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_release" );
    media_list_player_retain_ = ( libvlc_media_list_player_retain_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_retain" );
    media_list_player_event_manager_ = ( libvlc_media_list_player_event_manager_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_event_manager" );
    media_list_player_set_media_player_ = ( libvlc_media_list_player_set_media_player_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_set_media_player" );
    media_list_player_get_media_player_ = ( libvlc_media_list_player_get_media_player_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_get_media_player" );
    media_list_player_set_media_list_ = ( libvlc_media_list_player_set_media_list_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_set_media_list" );
    media_list_player_play_ = ( libvlc_media_list_player_play_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_play" );
    media_list_player_pause_ = ( libvlc_media_list_player_pause_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_pause" );
    media_list_player_set_pause_ = ( libvlc_media_list_player_set_pause_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_set_pause" );
    media_list_player_is_playing_ = ( libvlc_media_list_player_is_playing_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_is_playing" );
    media_list_player_get_state_ = ( libvlc_media_list_player_get_state_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_get_state" );
    media_list_player_play_item_at_index_ = ( libvlc_media_list_player_play_item_at_index_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_play_item_at_index" );
    media_list_player_play_item_ = ( libvlc_media_list_player_play_item_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_play_item" );
    media_list_player_stop_ = ( libvlc_media_list_player_stop_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_stop" );
    media_list_player_next_ = ( libvlc_media_list_player_next_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_next" );
    media_list_player_previous_ = ( libvlc_media_list_player_previous_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_previous" );
    media_list_player_set_playback_mode_ = ( libvlc_media_list_player_set_playback_mode_func_t )moduleHandle_.GetProcAddress( "libvlc_media_list_player_set_playback_mode" );

    media_player_new_ = ( libvlc_media_player_new_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_new" );
    media_player_new_from_media_ = ( libvlc_media_player_new_from_media_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_new_from_media" );
    media_player_release_ = ( libvlc_media_player_release_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_release" );
    media_player_retain_ = ( libvlc_media_player_retain_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_retain" );
    media_player_set_media_ = ( libvlc_media_player_set_media_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_media" );
    media_player_get_media_ = ( libvlc_media_player_get_media_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_media" );
    media_player_event_manager_ = ( libvlc_media_player_event_manager_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_event_manager" );
    media_player_is_playing_ = ( libvlc_media_player_is_playing_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_is_playing" );
    media_player_play_ = ( libvlc_media_player_play_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_play" );
    media_player_set_pause_ = ( libvlc_media_player_set_pause_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_pause" );
    media_player_pause_ = ( libvlc_media_player_pause_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_pause" );
    media_player_stop_ = ( libvlc_media_player_stop_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_stop" );
    media_player_set_renderer_ = ( libvlc_media_player_set_renderer_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_renderer" );
    video_set_callbacks_ = ( libvlc_video_set_callbacks_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_callbacks" );
    video_set_format_ = ( libvlc_video_set_format_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_format" );
    video_set_format_callbacks_ = ( libvlc_video_set_format_callbacks_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_format_callbacks" );
    media_player_set_nsobject_ = ( libvlc_media_player_set_nsobject_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_nsobject" );
    media_player_get_nsobject_ = ( libvlc_media_player_get_nsobject_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_nsobject" );
    media_player_set_xwindow_ = ( libvlc_media_player_set_xwindow_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_xwindow" );
    media_player_get_xwindow_ = ( libvlc_media_player_get_xwindow_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_xwindow" );
    media_player_set_hwnd_ = ( libvlc_media_player_set_hwnd_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_hwnd" );
    media_player_get_hwnd_ = ( libvlc_media_player_get_hwnd_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_hwnd" );
    media_player_set_android_context_ = ( libvlc_media_player_set_android_context_func_t )moduleHandle_.GetProcAddress( "xt_ = " );
    media_player_set_evas_object_ = ( libvlc_media_player_set_evas_object_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_evas_object" );
    audio_set_callbacks_ = ( libvlc_audio_set_callbacks_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_set_callbacks" );
    audio_set_volume_callback_ = ( libvlc_audio_set_volume_callback_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_set_volume_callback" );
    audio_set_format_callbacks_ = ( libvlc_audio_set_format_callbacks_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_set_format_callbacks" );
    audio_set_format_ = ( libvlc_audio_set_format_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_set_format" );
    media_player_get_length_ = ( libvlc_media_player_get_length_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_length" );
    media_player_get_time_ = ( libvlc_media_player_get_time_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_time" );
    media_player_set_time_ = ( libvlc_media_player_set_time_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_time" );
    media_player_get_position_ = ( libvlc_media_player_get_position_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_position" );
    media_player_set_position_ = ( libvlc_media_player_set_position_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_position" );
    media_player_set_chapter_ = ( libvlc_media_player_set_chapter_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_chapter" );
    media_player_get_chapter_ = ( libvlc_media_player_get_chapter_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_chapter" );
    media_player_get_chapter_count_ = ( libvlc_media_player_get_chapter_count_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_chapter_count" );
    media_player_will_play_ = ( libvlc_media_player_will_play_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_will_play" );
    media_player_get_chapter_count_for_title_ = ( libvlc_media_player_get_chapter_count_for_title_func_t )moduleHandle_.GetProcAddress( "le_ = " );
    media_player_set_title_ = ( libvlc_media_player_set_title_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_title" );
    media_player_get_title_ = ( libvlc_media_player_get_title_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_title" );
    media_player_get_title_count_ = ( libvlc_media_player_get_title_count_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_title_count" );
    media_player_previous_chapter_ = ( libvlc_media_player_previous_chapter_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_previous_chapter" );
    media_player_next_chapter_ = ( libvlc_media_player_next_chapter_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_next_chapter" );
    media_player_get_rate_ = ( libvlc_media_player_get_rate_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_rate" );
    media_player_set_rate_ = ( libvlc_media_player_set_rate_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_rate" );
    media_player_get_state_ = ( libvlc_media_player_get_state_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_state" );
    media_player_has_vout_ = ( libvlc_media_player_has_vout_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_has_vout" );
    media_player_is_seekable_ = ( libvlc_media_player_is_seekable_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_is_seekable" );
    media_player_can_pause_ = ( libvlc_media_player_can_pause_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_can_pause" );
    media_player_program_scrambled_ = ( libvlc_media_player_program_scrambled_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_program_scrambled" );
    media_player_next_frame_ = ( libvlc_media_player_next_frame_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_next_frame" );
    media_player_navigate_ = ( libvlc_media_player_navigate_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_navigate" );
    media_player_set_video_title_display_ = ( libvlc_media_player_set_video_title_display_func_t )moduleHandle_.GetProcAddress( "ay_ = " );
    media_player_add_slave_ = ( libvlc_media_player_add_slave_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_add_slave" );
    track_description_list_release_ = ( libvlc_track_description_list_release_func_t )moduleHandle_.GetProcAddress( "libvlc_track_description_list_release" );
    toggle_fullscreen_ = ( libvlc_toggle_fullscreen_func_t )moduleHandle_.GetProcAddress( "libvlc_toggle_fullscreen" );
    set_fullscreen_ = ( libvlc_set_fullscreen_func_t )moduleHandle_.GetProcAddress( "libvlc_set_fullscreen" );
    get_fullscreen_ = ( libvlc_get_fullscreen_func_t )moduleHandle_.GetProcAddress( "libvlc_get_fullscreen" );
    video_set_key_input_ = ( libvlc_video_set_key_input_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_key_input" );
    video_set_mouse_input_ = ( libvlc_video_set_mouse_input_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_mouse_input" );
    video_get_size_ = ( libvlc_video_get_size_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_size" );
    video_get_cursor_ = ( libvlc_video_get_cursor_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_cursor" );
    video_get_scale_ = ( libvlc_video_get_scale_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_scale" );
    video_set_scale_ = ( libvlc_video_set_scale_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_scale" );
    video_get_aspect_ratio_ = ( libvlc_video_get_aspect_ratio_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_aspect_ratio" );
    video_set_aspect_ratio_ = ( libvlc_video_set_aspect_ratio_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_aspect_ratio" );
    video_new_viewpoint_ = ( libvlc_video_new_viewpoint_func_t )moduleHandle_.GetProcAddress( "libvlc_video_new_viewpoint" );
    video_update_viewpoint_ = ( libvlc_video_update_viewpoint_func_t )moduleHandle_.GetProcAddress( "libvlc_video_update_viewpoint" );
    video_get_spu_ = ( libvlc_video_get_spu_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_spu" );
    video_get_spu_count_ = ( libvlc_video_get_spu_count_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_spu_count" );
    video_get_spu_description_ = ( libvlc_video_get_spu_description_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_spu_description" );
    video_set_spu_ = ( libvlc_video_set_spu_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_spu" );
    video_get_spu_delay_ = ( libvlc_video_get_spu_delay_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_spu_delay" );
    video_set_spu_delay_ = ( libvlc_video_set_spu_delay_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_spu_delay" );
    media_player_get_full_title_descriptions_ = ( libvlc_media_player_get_full_title_descriptions_func_t )moduleHandle_.GetProcAddress( "ns_ = " );
    title_descriptions_release_ = ( libvlc_title_descriptions_release_func_t )moduleHandle_.GetProcAddress( "libvlc_title_descriptions_release" );
    media_player_get_full_chapter_descriptions_ = ( libvlc_media_player_get_full_chapter_descriptions_func_t )moduleHandle_.GetProcAddress( "ns_ = " );
    chapter_descriptions_release_ = ( libvlc_chapter_descriptions_release_func_t )moduleHandle_.GetProcAddress( "libvlc_chapter_descriptions_release" );
    video_get_crop_geometry_ = ( libvlc_video_get_crop_geometry_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_crop_geometry" );
    video_set_crop_geometry_ = ( libvlc_video_set_crop_geometry_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_crop_geometry" );
    video_get_teletext_ = ( libvlc_video_get_teletext_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_teletext" );
    video_set_teletext_ = ( libvlc_video_set_teletext_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_teletext" );
    video_get_track_count_ = ( libvlc_video_get_track_count_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_track_count" );
    video_get_track_description_ = ( libvlc_video_get_track_description_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_track_description" );
    video_get_track_ = ( libvlc_video_get_track_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_track" );
    video_set_track_ = ( libvlc_video_set_track_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_track" );
    video_take_snapshot_ = ( libvlc_video_take_snapshot_func_t )moduleHandle_.GetProcAddress( "libvlc_video_take_snapshot" );
    video_set_deinterlace_ = ( libvlc_video_set_deinterlace_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_deinterlace" );
    video_get_marquee_int_ = ( libvlc_video_get_marquee_int_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_marquee_int" );
    video_get_marquee_string_ = ( libvlc_video_get_marquee_string_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_marquee_string" );
    video_set_marquee_int_ = ( libvlc_video_set_marquee_int_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_marquee_int" );
    video_set_marquee_string_ = ( libvlc_video_set_marquee_string_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_marquee_string" );
    video_get_logo_int_ = ( libvlc_video_get_logo_int_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_logo_int" );
    video_set_logo_int_ = ( libvlc_video_set_logo_int_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_logo_int" );
    video_set_logo_string_ = ( libvlc_video_set_logo_string_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_logo_string" );
    video_get_adjust_int_ = ( libvlc_video_get_adjust_int_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_adjust_int" );
    video_set_adjust_int_ = ( libvlc_video_set_adjust_int_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_adjust_int" );
    video_get_adjust_float_ = ( libvlc_video_get_adjust_float_func_t )moduleHandle_.GetProcAddress( "libvlc_video_get_adjust_float" );
    video_set_adjust_float_ = ( libvlc_video_set_adjust_float_func_t )moduleHandle_.GetProcAddress( "libvlc_video_set_adjust_float" );
    audio_output_list_get_ = ( libvlc_audio_output_list_get_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_output_list_get" );
    audio_output_list_release_ = ( libvlc_audio_output_list_release_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_output_list_release" );
    audio_output_set_ = ( libvlc_audio_output_set_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_output_set" );
    audio_output_device_enum_ = ( libvlc_audio_output_device_enum_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_output_device_enum" );
    audio_output_device_list_get_ = ( libvlc_audio_output_device_list_get_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_output_device_list_get" );
    audio_output_device_list_release_ = ( libvlc_audio_output_device_list_release_func_t )moduleHandle_.GetProcAddress( "se_ = " );
    audio_output_device_set_ = ( libvlc_audio_output_device_set_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_output_device_set" );
    audio_output_device_get_ = ( libvlc_audio_output_device_get_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_output_device_get" );
    audio_toggle_mute_ = ( libvlc_audio_toggle_mute_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_toggle_mute" );
    audio_get_mute_ = ( libvlc_audio_get_mute_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_get_mute" );
    audio_set_mute_ = ( libvlc_audio_set_mute_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_set_mute" );
    audio_get_volume_ = ( libvlc_audio_get_volume_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_get_volume" );
    audio_set_volume_ = ( libvlc_audio_set_volume_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_set_volume" );
    audio_get_track_count_ = ( libvlc_audio_get_track_count_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_get_track_count" );
    audio_get_track_description_ = ( libvlc_audio_get_track_description_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_get_track_description" );
    audio_get_track_ = ( libvlc_audio_get_track_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_get_track" );
    audio_set_track_ = ( libvlc_audio_set_track_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_set_track" );
    audio_get_channel_ = ( libvlc_audio_get_channel_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_get_channel" );
    audio_set_channel_ = ( libvlc_audio_set_channel_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_set_channel" );
    audio_get_delay_ = ( libvlc_audio_get_delay_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_get_delay" );
    audio_set_delay_ = ( libvlc_audio_set_delay_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_set_delay" );
    audio_equalizer_get_preset_count_ = ( libvlc_audio_equalizer_get_preset_count_func_t )moduleHandle_.GetProcAddress( "nt_ = " );
    audio_equalizer_get_preset_name_ = ( libvlc_audio_equalizer_get_preset_name_func_t )moduleHandle_.GetProcAddress( "me_ = " );
    audio_equalizer_get_band_count_ = ( libvlc_audio_equalizer_get_band_count_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_equalizer_get_band_count" );
    audio_equalizer_get_band_frequency_ = ( libvlc_audio_equalizer_get_band_frequency_func_t )moduleHandle_.GetProcAddress( "cy_ = " );
    audio_equalizer_new_ = ( libvlc_audio_equalizer_new_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_equalizer_new" );
    audio_equalizer_new_from_preset_ = ( libvlc_audio_equalizer_new_from_preset_func_t )moduleHandle_.GetProcAddress( "et_ = " );
    audio_equalizer_release_ = ( libvlc_audio_equalizer_release_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_equalizer_release" );
    audio_equalizer_set_preamp_ = ( libvlc_audio_equalizer_set_preamp_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_equalizer_set_preamp" );
    audio_equalizer_get_preamp_ = ( libvlc_audio_equalizer_get_preamp_func_t )moduleHandle_.GetProcAddress( "libvlc_audio_equalizer_get_preamp" );
    audio_equalizer_set_amp_at_index_ = ( libvlc_audio_equalizer_set_amp_at_index_func_t )moduleHandle_.GetProcAddress( "ex_ = " );
    audio_equalizer_get_amp_at_index_ = ( libvlc_audio_equalizer_get_amp_at_index_func_t )moduleHandle_.GetProcAddress( "ex_ = " );
    media_player_set_equalizer_ = ( libvlc_media_player_set_equalizer_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_equalizer" );
    media_player_get_role_ = ( libvlc_media_player_get_role_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_get_role" );
    media_player_set_role_ = ( libvlc_media_player_set_role_func_t )moduleHandle_.GetProcAddress( "libvlc_media_player_set_role" );

    // Renderer discoverer
    renderer_item_hold_ = ( libvlc_renderer_item_hold_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_item_hold" );
    renderer_item_release_ = ( libvlc_renderer_item_release_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_item_release" );
    renderer_item_name_ = ( libvlc_renderer_item_name_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_item_name" );
    renderer_item_type_ = ( libvlc_renderer_item_type_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_item_type" );
    renderer_item_icon_uri_ = ( libvlc_renderer_item_icon_uri_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_item_icon_uri" );
    renderer_item_flags_ = ( libvlc_renderer_item_flags_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_item_flags" );
    renderer_discoverer_new_ = ( libvlc_renderer_discoverer_new_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_discoverer_new" );
    renderer_discoverer_release_ = ( libvlc_renderer_discoverer_release_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_discoverer_release" );
    renderer_discoverer_start_ = ( libvlc_renderer_discoverer_start_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_discoverer_start" );
    renderer_discoverer_stop_ = ( libvlc_renderer_discoverer_stop_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_discoverer_stop" );
    renderer_discoverer_event_manager_ = ( libvlc_renderer_discoverer_event_manager_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_discoverer_event_manager" );
    renderer_discoverer_list_get_ = ( libvlc_renderer_discoverer_list_get_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_discoverer_list_get" );
    renderer_discoverer_list_release_ = ( libvlc_renderer_discoverer_list_release_func_t )moduleHandle_.GetProcAddress( "libvlc_renderer_discoverer_list_release" );

    // VLM
    vlm_release_ = (libvlc_vlm_release_func_t)moduleHandle_.GetProcAddress( "libvlc_vlm_release" );
    vlm_add_broadcast_ = ( libvlc_vlm_add_broadcast_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_add_broadcast" );
    vlm_add_vod_ = ( libvlc_vlm_add_vod_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_add_vod" );
    vlm_del_media_ = ( libvlc_vlm_del_media_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_del_media" );
    vlm_set_enabled_ = ( libvlc_vlm_set_enabled_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_set_enabled" );
    vlm_set_output_ = ( libvlc_vlm_set_output_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_set_output" );
    vlm_set_input_ = ( libvlc_vlm_set_input_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_set_input" );
    vlm_add_input_ = ( libvlc_vlm_add_input_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_add_input" );
    vlm_set_loop_ = ( libvlc_vlm_set_loop_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_set_loop" );
    vlm_set_mux_ = ( libvlc_vlm_set_mux_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_set_mux" );
    vlm_change_media_ = ( libvlc_vlm_change_media_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_change_media" );
    vlm_play_media_ = ( libvlc_vlm_play_media_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_play_media" );
    vlm_stop_media_ = ( libvlc_vlm_stop_media_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_stop_media" );
    vlm_pause_media_ = ( libvlc_vlm_pause_media_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_pause_media" );
    vlm_seek_media_ = ( libvlc_vlm_seek_media_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_seek_media" );
    vlm_show_media_ = ( libvlc_vlm_show_media_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_show_media" );
    vlm_get_media_instance_position_ = ( libvlc_vlm_get_media_instance_position_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_get_media_instance_position" );
    vlm_get_media_instance_time_ = ( libvlc_vlm_get_media_instance_time_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_get_media_instance_time" );
    vlm_get_media_instance_length_ = ( libvlc_vlm_get_media_instance_length_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_get_media_instance_length" );
    vlm_get_media_instance_rate_ = ( libvlc_vlm_get_media_instance_rate_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_get_media_instance_rate" );
    vlm_get_event_manager_ = ( libvlc_vlm_get_event_manager_func_t )moduleHandle_.GetProcAddress( "libvlc_vlm_get_event_manager" );

}

WideString LibVLC::GetVlcDirectory( )
{
    auto localMachine = RegistryHandle::LocalMachine( );
    auto vlcKey = localMachine.OpenKey( L"SOFTWARE\\VideoLAN\\VLC", KEY_READ );
    WideString result;
    if ( vlcKey.ReadString( L"InstallDir", result ) )
    {
        auto libVlcDll = result + L"\\libvlc.dll";
        if(IO::File::Exist( libVlcDll ) == false )
        { 
            WideString vlcDir = result = L"C:\\Program Files\\VideoLAN\\VLC";
            libVlcDll = vlcDir + L"\\libvlc.dll";
            if ( IO::File::Exist( libVlcDll ) == false )
            {
                result = vlcDir;
            }
        }
    }
    return result;
}

WideString LibVLC::GetVlcDll( )
{
    auto result = GetVlcDirectory( ) + L"\\libvlc.dll";
    return result;
}
WideString LibVLC::GetVlcPluginsDirectory( )
{
    auto result = GetVlcDirectory( ) + L"\\plugins";
    return result;
}
