#pragma once
#ifndef HARLINN_MEDIA_GLIB_HWMGTYPES_H_
#define HARLINN_MEDIA_GLIB_HWMGTYPES_H_
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

#include <HWMDef.h>

namespace Harlinn::Media::GLib
{
    using Bool32 = Int32;
    using Pointer = void*;
    using ConstPointer = const void*;
    
    using CompareFunc = Int32( * )( ConstPointer first, ConstPointer second );
    using CompareDataFunc = Int32( * )( ConstPointer first, ConstPointer second, Pointer userData );
    using EqualFunc = Bool32( * )( ConstPointer first, ConstPointer second );
    using EqualFuncFull = Bool32( * )( ConstPointer first, ConstPointer second, Pointer userData );
    using DestroyNotify = void( * )( Pointer data );
    using Func = void( * )( Pointer data, Pointer userData );
    using HashFunc = UInt32( * )( ConstPointer key );
    using HFunc = void( * )( Pointer key, Pointer value, Pointer userData );
    using CopyFunc = Pointer( * )( ConstPointer source, Pointer userData );
    using FreeFunc = void ( * )( Pointer data );
    using TranslateFunc = const char* ( * )( const char* str, Pointer userData );

    constexpr double E = 2.7182818284590452353602874713526624977572470937000;
    constexpr double LN2 = 0.69314718055994530941723212145817656807550013436026;
    constexpr double LN10 = 2.3025850929940456840179914546843642076011014886288;
    constexpr double PI = 3.1415926535897932384626433832795028841971693993751;
    constexpr double PI_2 = 1.5707963267948966192313216916397514420985846996876;
    constexpr double PI_4 = 0.78539816339744830961566084581987572104929234984378;
    constexpr double SQRT2 = 1.4142135623730950488016887242096980785696718753769;

}

#endif
