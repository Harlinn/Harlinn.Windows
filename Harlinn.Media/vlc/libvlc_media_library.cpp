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
    LIBVLC_API libvlc_media_library_t* libvlc_media_library_new( libvlc_instance_t* p_instance )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_library_new( p_instance );
    }
    LIBVLC_API void libvlc_media_library_release( libvlc_media_library_t* p_mlib )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_library_release( p_mlib );
    }
    LIBVLC_API void libvlc_media_library_retain( libvlc_media_library_t* p_mlib )
    {
        auto libVLC = LibVLC::Instance( );
        libVLC->libvlc_media_library_retain( p_mlib );
    }
    LIBVLC_API int libvlc_media_library_load( libvlc_media_library_t* p_mlib )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_library_load( p_mlib );
    }
    LIBVLC_API libvlc_media_list_t* libvlc_media_library_media_list( libvlc_media_library_t* p_mlib )
    {
        auto libVLC = LibVLC::Instance( );
        return libVLC->libvlc_media_library_media_list( p_mlib );
    }

}