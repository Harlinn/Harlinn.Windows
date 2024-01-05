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
#include "HWMGst.h"
#include <gst/gst.h>

#pragma comment(lib,"gstreamer-1.0.lib") 

namespace Harlinn::Media::GStreamer
{
    HWM_EXPORT void Init( int* argc, char** argv[ ] )
    {
        gst_init( argc, argv );
    }

    HWM_EXPORT Bool32 Init( int* argc, char** argv[ ], Error** error )
    {
        return gst_init_check( argc, argv, reinterpret_cast< GError** >( error ) );
    }

    HWM_EXPORT Bool32 IsInitialized( )
    {
        return gst_is_initialized( );
    }

    HWM_EXPORT OptionGroup* InitGetOptionGroup( )
    {
        return reinterpret_cast< OptionGroup* >( gst_init_get_option_group( ) );
    }

    HWM_EXPORT void Deinit( )
    {
        gst_deinit( );
    }

    HWM_EXPORT void Version( UInt32* major, UInt32* minor, UInt32* micro, UInt32* nano )
    {
        gst_version( major, minor, micro, nano );
    }

    HWM_EXPORT const char* VersionString( )
    {
        return gst_version_string( );
    }

    HWM_EXPORT Bool32 SegtrapIsEnabled( )
    {
        return gst_segtrap_is_enabled( );
    }
    HWM_EXPORT void SegtrapSetEnabled( Bool32 enabled )
    {
        gst_segtrap_set_enabled( enabled );
    }
    HWM_EXPORT Bool32 RegistryForkIsEnabled( )
    {
        return gst_registry_fork_is_enabled( );
    }
    HWM_EXPORT void RegistryForkSetEnabled( Bool32 enabled )
    {
        gst_registry_fork_set_enabled( enabled );
    }
    HWM_EXPORT void UpdateRegistry( )
    {
        gst_update_registry( );
    }
    HWM_EXPORT const char* MainExecutablePath( )
    {
        return gst_get_main_executable_path( );
    }


}
