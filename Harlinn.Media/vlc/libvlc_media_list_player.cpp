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
    LIBVLC_API libvlc_media_list_player_t* libvlc_media_list_player_new( libvlc_instance_t* p_instance )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_player_new( p_instance );
    }
    LIBVLC_API void libvlc_media_list_player_release( libvlc_media_list_player_t* p_mlp )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_list_player_release( p_mlp );
    }
    LIBVLC_API void libvlc_media_list_player_retain( libvlc_media_list_player_t* p_mlp )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_list_player_retain( p_mlp );
    }
    LIBVLC_API libvlc_event_manager_t* libvlc_media_list_player_event_manager( libvlc_media_list_player_t* p_mlp )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_player_event_manager( p_mlp );
    }
    LIBVLC_API void libvlc_media_list_player_set_media_player( libvlc_media_list_player_t* p_mlp, libvlc_media_player_t* p_mi )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_list_player_set_media_player( p_mlp, p_mi );
    }
    LIBVLC_API libvlc_media_player_t* libvlc_media_list_player_get_media_player( libvlc_media_list_player_t* p_mlp )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_player_get_media_player( p_mlp );
    }
    LIBVLC_API void libvlc_media_list_player_set_media_list( libvlc_media_list_player_t* p_mlp, libvlc_media_list_t* p_mlist )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_list_player_set_media_list( p_mlp, p_mlist );
    }
    LIBVLC_API void libvlc_media_list_player_play( libvlc_media_list_player_t* p_mlp )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_list_player_play( p_mlp );
    }
    LIBVLC_API void libvlc_media_list_player_pause( libvlc_media_list_player_t* p_mlp )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_list_player_pause( p_mlp );
    }
    LIBVLC_API void libvlc_media_list_player_set_pause( libvlc_media_list_player_t* p_mlp, int do_pause )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_list_player_set_pause( p_mlp, do_pause );
    }
    LIBVLC_API int libvlc_media_list_player_is_playing( libvlc_media_list_player_t* p_mlp )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_player_is_playing( p_mlp );
    }
    LIBVLC_API libvlc_state_t libvlc_media_list_player_get_state( libvlc_media_list_player_t* p_mlp )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_player_get_state( p_mlp );
    }
    LIBVLC_API int libvlc_media_list_player_play_item_at_index( libvlc_media_list_player_t* p_mlp, int i_index )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_player_play_item_at_index( p_mlp, i_index );
    }
    LIBVLC_API int libvlc_media_list_player_play_item( libvlc_media_list_player_t* p_mlp, libvlc_media_t* p_md )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_player_play_item( p_mlp, p_md );
    }
    LIBVLC_API void libvlc_media_list_player_stop( libvlc_media_list_player_t* p_mlp )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_list_player_stop( p_mlp );
    }
    LIBVLC_API int libvlc_media_list_player_next( libvlc_media_list_player_t* p_mlp )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_player_next( p_mlp );
    }
    LIBVLC_API int libvlc_media_list_player_previous( libvlc_media_list_player_t* p_mlp )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_player_previous( p_mlp );
    }
    LIBVLC_API void libvlc_media_list_player_set_playback_mode( libvlc_media_list_player_t* p_mlp, libvlc_playback_mode_t e_mode )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_list_player_set_playback_mode( p_mlp, e_mode );
    }
}