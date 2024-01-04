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
#include "HWMgoption.h"
#include <gst/gst.h>

namespace Harlinn::Media::GLib
{
    HWM_EXPORT Quark OptionErrorQuark( )
    {
        return g_option_error_quark( );
    }

    HWM_EXPORT OptionContext* OptionContextNew( const char* parameterString )
    {
        return reinterpret_cast< OptionContext* >( g_option_context_new( parameterString ) );
    }
    HWM_EXPORT void OptionContextSetSummary( OptionContext* context, const char* summary )
    {
        g_option_context_set_summary( reinterpret_cast< GOptionContext* >( context ), summary );
    }
    HWM_EXPORT const char* OptionContextGetSummary( OptionContext* context )
    {
        return g_option_context_get_summary( reinterpret_cast< GOptionContext* >( context ) );
    }
    HWM_EXPORT void OptionContextSetDescription( OptionContext* context, const char* description )
    {
        g_option_context_set_description( reinterpret_cast< GOptionContext* >( context ), description );
    }
    HWM_EXPORT const char* OptionContextGetDescription( OptionContext* context )
    {
        return g_option_context_get_description( reinterpret_cast< GOptionContext* >( context ) );
    }
    HWM_EXPORT void OptionContextFree( OptionContext* context )
    {
        g_option_context_free( reinterpret_cast< GOptionContext* >( context ) );
    }
    HWM_EXPORT void OptionContextSetHelpEnabled( OptionContext* context, Bool32 helpEnabled )
    {
        g_option_context_set_help_enabled( reinterpret_cast< GOptionContext* >( context ), helpEnabled );
    }
    HWM_EXPORT Bool32 OptionContextGetHelpEnabled( OptionContext* context )
    {
        return g_option_context_get_help_enabled( reinterpret_cast< GOptionContext* >( context ) );
    }
    HWM_EXPORT void OptionContextSetIgnoreUnknownOptions( OptionContext* context, Bool32 ignoreUnknown )
    {
        g_option_context_set_ignore_unknown_options( reinterpret_cast< GOptionContext* >( context ), ignoreUnknown );
    }
    HWM_EXPORT Bool32 OptionContextGetIgnoreUnknownOptions( OptionContext* context )
    {
        return g_option_context_get_ignore_unknown_options( reinterpret_cast< GOptionContext* >( context ) );
    }
    HWM_EXPORT void OptionContextSetStrictPosix( OptionContext* context, Bool32 strictPosix )
    {
        g_option_context_set_strict_posix( reinterpret_cast< GOptionContext* >( context ), strictPosix );
    }
    HWM_EXPORT Bool32 OptionContextGetStrictPosix( OptionContext* context )
    {
        return g_option_context_get_strict_posix( reinterpret_cast< GOptionContext* >( context ) );
    }
    HWM_EXPORT void OptionContextAddMainEntries( OptionContext* context, const OptionEntry* entries, const char* translationDomain )
    {
        g_option_context_add_main_entries( reinterpret_cast< GOptionContext* >( context ), reinterpret_cast< const GOptionEntry* >( entries ), translationDomain );
    }
    HWM_EXPORT Bool32 OptionContextParse( OptionContext* context, Int32* argc, char*** argv, Error** error )
    {
        return g_option_context_parse( reinterpret_cast< GOptionContext* >( context ), argc, argv, reinterpret_cast<GError**>( error ) );
    }
    HWM_EXPORT Bool32 OptionContextParseSTrv( OptionContext* context, char*** arguments, Error** error )
    {
        return g_option_context_parse_strv( reinterpret_cast< GOptionContext* >( context ), arguments, reinterpret_cast< GError** >( error ) );
    }
    HWM_EXPORT void OptionContextSetTranslateFunc( OptionContext* context, TranslateFunc func, Pointer data, DestroyNotify destroyNotify )
    {
        g_option_context_set_translate_func( reinterpret_cast< GOptionContext* >( context ), reinterpret_cast< TranslateFunc >( func ), data, reinterpret_cast< GDestroyNotify >( destroyNotify ) );
    }
    HWM_EXPORT void OptionContextSetTranslationDomain( OptionContext* context, const char* domain )
    {
        g_option_context_set_translation_domain( reinterpret_cast< GOptionContext* >( context ), domain );
    }
    HWM_EXPORT void OptionContextAddGroup( OptionContext* context, OptionGroup* group )
    {
        g_option_context_add_group( reinterpret_cast< GOptionContext* >( context ), reinterpret_cast< GOptionGroup* >( group ) );
    }
    HWM_EXPORT void OptionContextSetMainGroup( OptionContext* context, OptionGroup* group )
    {
        g_option_context_set_main_group( reinterpret_cast< GOptionContext* >( context ), reinterpret_cast< GOptionGroup* >( group ) );
    }
    HWM_EXPORT OptionGroup* OptionContextGetMainGroup( OptionContext* context )
    {
        return reinterpret_cast< OptionGroup* >( g_option_context_get_main_group( reinterpret_cast< GOptionContext* >( context ) ) );
    }
    HWM_EXPORT char* OptionContextGetHelp( OptionContext* context, Bool32 mainHelp, OptionGroup* group )
    {
        return g_option_context_get_help( reinterpret_cast< GOptionContext* >( context ), mainHelp, reinterpret_cast< GOptionGroup* >( group ) );
    }
    HWM_EXPORT OptionGroup* OptionGroupNew( const char* name, const char* description, const char* helpDescription, Pointer userData, DestroyNotify destroy )
    {
        return reinterpret_cast< OptionGroup* >( g_option_group_new( name, description, helpDescription, userData, reinterpret_cast< GDestroyNotify >( destroy ) ) );
    }
    HWM_EXPORT void	OptionGroupSetParseHooks( OptionGroup* group, OptionParseFunc preParseFunc, OptionParseFunc	postParseFunc )
    {
        g_option_group_set_parse_hooks( reinterpret_cast< GOptionGroup* >( group ), reinterpret_cast< GOptionParseFunc >( preParseFunc ), reinterpret_cast< GOptionParseFunc >( postParseFunc ) );
    }
    HWM_EXPORT void	OptionGroupSetErrorHook( OptionGroup* group, OptionErrorFunc errorFunc )
    {
        g_option_group_set_error_hook( reinterpret_cast< GOptionGroup* >( group ), reinterpret_cast< GOptionErrorFunc >( errorFunc ) );
    }
    
    HWM_EXPORT OptionGroup* OptionGroupRef( OptionGroup* group )
    {
        return reinterpret_cast< OptionGroup* >( g_option_group_ref( reinterpret_cast< GOptionGroup* >( group ) ) );
    }
    HWM_EXPORT void OptionGroupUnref( OptionGroup* group )
    {
        g_option_group_unref( reinterpret_cast< GOptionGroup* >( group ) );
    }
    HWM_EXPORT void OptionGroupAddEntries( OptionGroup* group, const OptionEntry* entries )
    {
        g_option_group_add_entries( reinterpret_cast< GOptionGroup* >( group ), reinterpret_cast< const GOptionEntry* >( entries ) );
    }
    HWM_EXPORT void OptionGroupSetTranslateFunc( OptionGroup* group, TranslateFunc func, Pointer data, DestroyNotify destroyNotify )
    {
        g_option_group_set_translate_func( reinterpret_cast< GOptionGroup* >( group ), reinterpret_cast< TranslateFunc >( func ), data, reinterpret_cast< GDestroyNotify >( destroyNotify ) );
    }
    HWM_EXPORT void OptionGroupSetTranslationDomain( OptionGroup* group, const char* domain )
    {
        g_option_group_set_translation_domain( reinterpret_cast< GOptionGroup* >( group ), domain );
    }
}
