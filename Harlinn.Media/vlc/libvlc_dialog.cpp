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
    LIBVLC_API void libvlc_dialog_set_callbacks( libvlc_instance_t* p_instance, const libvlc_dialog_cbs* p_cbs, void* p_data )
    {
        LibVLC::Instance( )->libvlc_dialog_set_callbacks( p_instance, p_cbs, p_data );
    }
    LIBVLC_API void libvlc_dialog_set_context( libvlc_dialog_id* p_id, void* p_context )
    {
        LibVLC::Instance( )->libvlc_dialog_set_context( p_id, p_context );
    }
    LIBVLC_API void* libvlc_dialog_get_context( libvlc_dialog_id* p_id )
    {
        return LibVLC::Instance( )->libvlc_dialog_get_context( p_id );
    }
    LIBVLC_API int libvlc_dialog_post_login( libvlc_dialog_id* p_id, const char* psz_username, const char* psz_password, bool b_store )
    {
        return LibVLC::Instance( )->libvlc_dialog_post_login( p_id, psz_username, psz_password, b_store );
    }
    LIBVLC_API int libvlc_dialog_post_action( libvlc_dialog_id* p_id, int i_action )
    {
        return LibVLC::Instance( )->libvlc_dialog_post_action( p_id, i_action );
    }
    LIBVLC_API int libvlc_dialog_dismiss( libvlc_dialog_id* p_id )
    {
        return LibVLC::Instance( )->libvlc_dialog_dismiss( p_id );
    }
}