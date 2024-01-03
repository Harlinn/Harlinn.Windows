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
    LIBVLC_API libvlc_media_list_t* libvlc_media_list_new( libvlc_instance_t* p_instance )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_new( p_instance );
    }
    LIBVLC_API void libvlc_media_list_release( libvlc_media_list_t* p_ml )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_list_release( p_ml );
    }
    LIBVLC_API void libvlc_media_list_retain( libvlc_media_list_t* p_ml )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_list_retain( p_ml );
    }
    LIBVLC_API void libvlc_media_list_set_media( libvlc_media_list_t* p_ml, libvlc_media_t* p_md )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_list_set_media( p_ml, p_md );
    }
    LIBVLC_API libvlc_media_t* libvlc_media_list_media( libvlc_media_list_t* p_ml )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_media( p_ml );
    }
    LIBVLC_API int libvlc_media_list_add_media( libvlc_media_list_t* p_ml, libvlc_media_t* p_md )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_add_media( p_ml, p_md );
    }
    LIBVLC_API int libvlc_media_list_insert_media( libvlc_media_list_t* p_ml, libvlc_media_t* p_md, int i_pos )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_insert_media( p_ml, p_md, i_pos );
    }
    LIBVLC_API int libvlc_media_list_remove_index( libvlc_media_list_t* p_ml, int i_pos )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_remove_index( p_ml, i_pos );
    }
    LIBVLC_API int libvlc_media_list_count( libvlc_media_list_t* p_ml )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_count( p_ml );
    }
    LIBVLC_API libvlc_media_t* libvlc_media_list_item_at_index( libvlc_media_list_t* p_ml, int i_pos )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_item_at_index( p_ml, i_pos );
    }
    LIBVLC_API int libvlc_media_list_index_of_item( libvlc_media_list_t* p_ml, libvlc_media_t* p_md )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_index_of_item( p_ml, p_md );
    }
    LIBVLC_API int libvlc_media_list_is_readonly( libvlc_media_list_t* p_ml )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_is_readonly( p_ml );
    }
    LIBVLC_API void libvlc_media_list_lock( libvlc_media_list_t* p_ml )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_lock( p_ml );
    }
    LIBVLC_API void libvlc_media_list_unlock( libvlc_media_list_t* p_ml )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_unlock( p_ml );
    }
    LIBVLC_API libvlc_event_manager_t* libvlc_media_list_event_manager( libvlc_media_list_t* p_ml )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_list_event_manager( p_ml );
    }
}