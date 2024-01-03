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
    LIBVLC_API const char* libvlc_errmsg( void )
    {
        return LibVLC::Instance( )->libvlc_errmsg( );
    }

    LIBVLC_API void libvlc_clearerr( void )
    {
        LibVLC::Instance( )->libvlc_clearerr( );
    }

    LIBVLC_API const char* libvlc_vprinterr( const char* fmt, va_list ap )
    {
        return LibVLC::Instance( )->libvlc_vprinterr( fmt, ap );
    }

    LIBVLC_API const char* libvlc_printerr( const char* fmt, ... )
    {
        va_list argptr;
        va_start( argptr, fmt );
        auto result = LibVLC::Instance( )->libvlc_vprinterr( fmt, argptr );
        va_end( argptr );
        return result;
    }

    LIBVLC_API libvlc_instance_t* libvlc_new( int argc, const char* const* argv )
    {
        return LibVLC::Instance( )->libvlc_new( argc, argv );
    }

    LIBVLC_API void libvlc_release( libvlc_instance_t* p_instance )
    {
        LibVLC::Instance( )->libvlc_release( p_instance );
    }

    LIBVLC_API void libvlc_retain( libvlc_instance_t* p_instance )
    {
        LibVLC::Instance( )->libvlc_retain( p_instance );
    }

    LIBVLC_API int libvlc_add_intf( libvlc_instance_t* p_instance, const char* name )
    {
        return LibVLC::Instance( )->libvlc_add_intf( p_instance, name );
    }

    LIBVLC_API void libvlc_set_exit_handler( libvlc_instance_t* p_instance, void ( *cb ) ( void* ), void* opaque )
    {
        LibVLC::Instance( )->libvlc_set_exit_handler( p_instance, cb, opaque );
    }

    LIBVLC_API void libvlc_set_user_agent( libvlc_instance_t* p_instance, const char* name, const char* http )
    {
        LibVLC::Instance( )->libvlc_set_user_agent( p_instance, name, http );
    }

    LIBVLC_API void libvlc_set_app_id( libvlc_instance_t* p_instance, const char* id, const char* version, const char* icon )
    {
        LibVLC::Instance( )->libvlc_set_app_id( p_instance, id, version, icon );
    }

    LIBVLC_API const char* libvlc_get_version( void )
    {
        return LibVLC::Instance( )->libvlc_get_version( );
    }

    LIBVLC_API const char* libvlc_get_compiler( void )
    {
        return LibVLC::Instance( )->libvlc_get_compiler( );
    }

    LIBVLC_API const char* libvlc_get_changeset( void )
    {
        return LibVLC::Instance( )->libvlc_get_changeset( );
    }   

    LIBVLC_API void libvlc_free( void* ptr )
    {
        LibVLC::Instance( )->libvlc_free( ptr );
    }

    LIBVLC_API int libvlc_event_attach( libvlc_event_manager_t* p_event_manager, libvlc_event_type_t i_event_type, libvlc_callback_t f_callback, void* user_data )
    {
        return LibVLC::Instance( )->libvlc_event_attach( p_event_manager, i_event_type, f_callback, user_data );
    }

    LIBVLC_API void libvlc_event_detach( libvlc_event_manager_t* p_event_manager, libvlc_event_type_t i_event_type, libvlc_callback_t f_callback, void* p_user_data )
    {
        LibVLC::Instance( )->libvlc_event_detach( p_event_manager, i_event_type, f_callback, p_user_data );
    }

    LIBVLC_API const char* libvlc_event_type_name( libvlc_event_type_t event_type )
    {
        return LibVLC::Instance( )->libvlc_event_type_name( event_type );
    }

    LIBVLC_API void libvlc_log_get_context( const libvlc_log_t* ctx, const char** module, const char** file, unsigned* line )
    {
        LibVLC::Instance( )->libvlc_log_get_context( ctx, module, file, line );
    }

    LIBVLC_API void libvlc_log_get_object( const libvlc_log_t* ctx, const char** name, const char** header, uintptr_t* id )
    {
        LibVLC::Instance( )->libvlc_log_get_object( ctx, name, header, id );
    }

    LIBVLC_API void libvlc_log_unset( libvlc_instance_t* p_instance )
    {
        LibVLC::Instance( )->libvlc_log_unset( p_instance );
    }

    LIBVLC_API void libvlc_log_set( libvlc_instance_t* p_instance, libvlc_log_cb cb, void* data )
    {
        LibVLC::Instance( )->libvlc_log_set( p_instance, cb, data );
    }

    LIBVLC_API void libvlc_log_set_file( libvlc_instance_t* p_instance, FILE* stream )
    {
        LibVLC::Instance( )->libvlc_log_set_file( p_instance, stream );
    }

    LIBVLC_API void libvlc_module_description_list_release( libvlc_module_description_t* p_list )
    {
        LibVLC::Instance( )->libvlc_module_description_list_release( p_list );
    }

    LIBVLC_API libvlc_module_description_t* libvlc_audio_filter_list_get( libvlc_instance_t* p_instance )
    {
        return LibVLC::Instance( )->libvlc_audio_filter_list_get( p_instance );
    }

    LIBVLC_API libvlc_module_description_t* libvlc_video_filter_list_get( libvlc_instance_t* p_instance )
    {
        return LibVLC::Instance( )->libvlc_video_filter_list_get( p_instance );
    }

    LIBVLC_API int64_t libvlc_clock( void )
    {
        return LibVLC::Instance( )->libvlc_clock( );
    }

}