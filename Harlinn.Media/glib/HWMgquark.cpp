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
#include "HWMgquark.h"
#include <gst/gst.h>

namespace Harlinn::Media::GLib
{
    using Quark = Int32;

    HWM_EXPORT Quark QuarkTryString( const char* string )
    {
        return g_quark_try_string( string );
    }
    HWM_EXPORT Quark QuarkFromStaticString( const char* string )
    {
        return g_quark_from_static_string( string );
    }
    HWM_EXPORT Quark QuarkFromString( const char* string )
    {
        return g_quark_from_string( string );
    }
    HWM_EXPORT const char* QuarkToString( Quark quark )
    {
        return g_quark_to_string( quark );
    }
    HWM_EXPORT const char* InternString( const char* string )
    {
        return g_intern_string( string );
    }
    HWM_EXPORT const char* InternStaticString( const char* string )
    {
        return g_intern_static_string( string );
    }

}