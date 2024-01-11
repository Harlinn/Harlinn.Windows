#pragma once 
#ifndef HARLINN_MEDIA_GLIB_HWMGMAIN_H_
#define HARLINN_MEDIA_GLIB_HWMGMAIN_H_
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
    class MainContext : public ReferenceBase<MainContext, GMainContext>
    {
    public:
        using Base = ReferenceBase<MainContext, GMainContext>;

        MainContext( ) = default;
        explicit MainContext( WrappedType* impl, ReferenceType referenceType = ReferenceType::None )
            : Base( impl, referenceType )
        {
        }

        static MainContext Create( )
        {
            return MainContext( g_main_context_new( ) );
        }
        static MainContext Create( GMainContextFlags flags )
        {
            return MainContext( g_main_context_new_with_flags( flags ) );
        }

        static Attached<MainContext> Default( )
        {
            return Attached<MainContext>( g_main_context_default( ) );
        }


    };

    class MainLoop : public ReferenceBase<MainLoop, GMainLoop>
    {
    public:
        using Base = ReferenceBase<MainLoop, GMainLoop>;

        MainLoop( ) = default;
        explicit MainLoop( WrappedType* impl, ReferenceType referenceType = ReferenceType::None )
            : Base( impl, referenceType )
        { }

    };

    class Source : public ReferenceBase<Source, GSource>
    {
    public:
        using Base = ReferenceBase<Source, GSource>;

        Source( ) = default;
        explicit Source( WrappedType* impl, ReferenceType referenceType = ReferenceType::None )
            : Base( impl, referenceType )
        {
        }

    };


}

#endif

