#pragma once
#ifndef HARLINN_MEDIA_GLIB_HWMGOPTION_H_
#define HARLINN_MEDIA_GLIB_HWMGOPTION_H_

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


#include "HWMgerror.h"

namespace Harlinn::Media::GLib
{
    struct OptionContext;
    struct OptionGroup;
    struct OptionEntry;

    enum class OptionFlags : UInt32
    {
        None = 0,
        Hidden = 1 << 0,
        InMain = 1 << 1,
        Reverse = 1 << 2,
        NoArg = 1 << 3,
        Filename = 1 << 4,
        OptionalArg = 1 << 5,
        NoAlias = 1 << 6
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( OptionFlags, UInt32 );

    enum class OptionArg : UInt32
    {
        None,
        String,
        Int,
        Callback,
        Filename,
        StringArray,
        FilenameArray,
        Double,
        Int64
    };

    using OptionArgFunc = Bool32( * ) ( const char* optionName, const char* value, Pointer userData, Error** error );
    using OptionParseFunc = Bool32( * ) ( OptionContext* context, OptionGroup* group, Pointer userData, Error** error );
    using OptionErrorFunc = void ( * ) ( OptionContext* context, OptionGroup* group, Pointer userData, Error** error );

    enum class OptionError
    {
        UnknownOption,
        BadValue,
        Failed
    };

    HWM_EXPORT Quark OptionErrorQuark( );

    struct OptionEntry
    {
        const char* longName = nullptr;
        char shortName = 0;
        Int32 flags = 0;

        OptionArg arg = OptionArg::None;
        Pointer argData = nullptr;

        const char* description = nullptr;
        const char* argDescription = nullptr;
    };

    constexpr char OptionRemaining[ ] = "";

    HWM_EXPORT OptionContext* OptionContextNew( const char* parameterString );
    HWM_EXPORT void OptionContextSetSummary( OptionContext* context, const char* summary );
    HWM_EXPORT const char* OptionContextGetSummary( OptionContext* context );
    HWM_EXPORT void OptionContextSetDescription( OptionContext* context, const char* description );
    HWM_EXPORT const char* OptionContextGetDescription( OptionContext* context );
    HWM_EXPORT void OptionContextFree( OptionContext* context );
    HWM_EXPORT void OptionContextSetHelpEnabled( OptionContext* context, Bool32 helpEnabled );
    HWM_EXPORT Bool32 OptionContextGetHelpEnabled( OptionContext* context );
    HWM_EXPORT void OptionContextSetIgnoreUnknownOptions( OptionContext* context, Bool32 ignoreUnknown );
    HWM_EXPORT Bool32 OptionContextGetIgnoreUnknownOptions( OptionContext* context );
    HWM_EXPORT void OptionContextSetStrictPosix( OptionContext* context, Bool32 strictPosix );
    HWM_EXPORT Bool32 OptionContextGetStrictPosix( OptionContext* context );
    HWM_EXPORT void OptionContextAddMainEntries( OptionContext* context, const OptionEntry* entries, const char* translationDomain );
    HWM_EXPORT Bool32 OptionContextParse( OptionContext* context, Int32* argc, char*** argv, Error** error );
    HWM_EXPORT Bool32 OptionContextParseSTrv( OptionContext* context, char*** arguments, Error** error );
    HWM_EXPORT void OptionContextSetTranslateFunc( OptionContext* context, TranslateFunc func, Pointer data, DestroyNotify destroyNotify );
    HWM_EXPORT void OptionContextSetTranslationDomain( OptionContext* context, const char* domain );
    HWM_EXPORT void OptionContextAddGroup( OptionContext* context, OptionGroup* group );
    HWM_EXPORT void OptionContextSetMainGroup( OptionContext* context, OptionGroup* group );
    HWM_EXPORT OptionGroup* OptionContextGetMainGroup( OptionContext* context );
    HWM_EXPORT char* OptionContextGetHelp( OptionContext* context, Bool32 mainHelp, OptionGroup* group );
    HWM_EXPORT OptionGroup* OptionGroupNew( const char* name, const char* description, const char* helpDescription, Pointer userData, DestroyNotify destroy );
    HWM_EXPORT void	OptionGroupSetParseHooks( OptionGroup* group, OptionParseFunc preParseFunc, OptionParseFunc	postParseFunc );
    HWM_EXPORT void	OptionGroupSetErrorHook( OptionGroup* group, OptionErrorFunc errorFunc );
    HWM_EXPORT OptionGroup* OptionGroupRef( OptionGroup* group );
    HWM_EXPORT void OptionGroupUnref( OptionGroup* group );
    HWM_EXPORT void OptionGroupAddEntries( OptionGroup* group, const OptionEntry* entries );
    HWM_EXPORT void OptionGroupSetTranslateFunc( OptionGroup* group, TranslateFunc func, Pointer data, DestroyNotify destroyNotify );
    HWM_EXPORT void OptionGroupSetTranslationDomain( OptionGroup* group, const char* domain );



}

#endif
