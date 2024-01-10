#pragma once
#ifndef HARLINN_MEDIA_GLIB_HWMGVARIANT_H_
#define HARLINN_MEDIA_GLIB_HWMGVARIANT_H_
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

#include "HWMgmemory.h"

namespace Harlinn::Media::GLib
{
    class Variant
    {
        GVariant* impl_ = nullptr;
    public:
        Variant( ) = default;
        explicit Variant( GVariant* impl, bool addRef = false )
            : impl_( impl )
        {
            if ( impl_ && addRef )
            {
                if ( g_variant_is_floating( impl_ ) )
                {
                    g_variant_ref_sink( impl_ );
                }
                else
                {
                    g_variant_ref( impl_ );
                }
            }
        }

        Variant( const Variant& other )
            : impl_( other.impl_ )
        {
            if ( impl_ )
            {
                if ( g_variant_is_floating( impl_ ) )
                {
                    g_variant_ref_sink( impl_ );
                }
                else
                {
                    g_variant_ref( impl_ );
                }
            }
        }

        Variant( Variant&& other ) noexcept
            : impl_( other.impl_ )
        {
            other.impl_ = nullptr;
        }


        ~Variant( )
        {
            if ( impl_ )
            {
                g_variant_unref( impl_ );
            }
        }

    };

}

#endif
