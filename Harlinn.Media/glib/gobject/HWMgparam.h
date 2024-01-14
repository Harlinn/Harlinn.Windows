#pragma once 
#ifndef HARLINN_MEDIA_GLIB_GOBJECT_HWMGPARAM_H_
#define HARLINN_MEDIA_GLIB_GOBJECT_HWMGPARAM_H_
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

#include "HWMgobject.h"

namespace Harlinn::Media::GLib
{
    namespace Internal
    {
        template<typename BaseT>
        class ParamSpecImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( ParamSpecImpl, GParamSpec )

            const char* Blurb( ) const
            {
                return g_param_spec_get_blurb( get( ) );
            }

            Value DefaultValue( ) const
            {
                Value result( g_param_spec_get_default_value( get( ) ) );
                return result;
            }
            void SetDefaultValue( const Value& defaultValue ) const
            {
                g_param_value_set_default( get( ), const_cast< Value* >( &defaultValue ) );
            }

            const char* Name( ) const
            {
                return g_param_spec_get_name( get( ) );
            }

            GQuark NameQuark( ) const
            {
                return g_param_spec_get_name_quark( get( ) );
            }

            const char* Nick( ) const
            {
                return g_param_spec_get_nick( get( ) );
            }

            gpointer QData( GQuark quark ) const
            {
                return g_param_spec_get_qdata( get( ), quark );
            }

            gpointer StealQData( GQuark quark ) const
            {
                return g_param_spec_steal_qdata( get( ), quark );
            }

            void SetQData( GQuark quark, gpointer qdata ) const
            {
                g_param_spec_set_qdata( get( ), quark, qdata );
            }

            void SetQData( GQuark quark, gpointer qdata, GDestroyNotify destroyNotify ) const
            {
                g_param_spec_set_qdata_full( get( ), quark, qdata, destroyNotify );
            }

            GParamSpec* GetRedirectTarget( ) const
            {
                return g_param_spec_get_redirect_target( get( ) );
            }


            bool IsDefault( const GValue* value ) const
            {
                return g_param_value_defaults( get( ), value ) != 0;
            }
            bool IsDefault( const Value& value ) const
            {
                return g_param_value_defaults( get( ), &value ) != 0;
            }

            bool EnsureValid( GValue* value ) const
            {
                return g_param_value_validate( get( ), value );
            }

            bool EnsureValid( Value& value ) const
            {
                return g_param_value_validate( get( ), &value );
            }


            bool IsValid( const GValue* value ) const
            {
                return g_param_value_is_valid( get( ), value );
            }
            bool IsValid( const Value& value ) const
            {
                return g_param_value_is_valid( get( ), &value );
            }


        };
    }
    using BasicParamSpec = Internal::ParamSpecImpl<BasicObject>;
    using ParamSpec = Internal::ParamSpecImpl<Object>;
}

#endif