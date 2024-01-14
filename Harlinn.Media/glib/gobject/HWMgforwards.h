#pragma once 
#ifndef HARLINN_MEDIA_GLIB_GOBJECT_HWMGFORWARDS_H_
#define HARLINN_MEDIA_GLIB_GOBJECT_HWMGFORWARDS_H_

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

#include "HWMgtype.h"

namespace Harlinn::Media::GLib
{
    class BasicObject;
    class Object;

    template<typename T>
    constexpr bool IsObject = std::is_base_of_v<BasicObject, T>;

    namespace Internal
    {
        template<typename BaseT>
        class BindingImpl;
    }
    using BasicBinding = Internal::BindingImpl<BasicObject>;
    using Binding = Internal::BindingImpl<Object>;


    template<typename T>
    constexpr bool IsBinding = std::is_base_of_v<BasicBinding, T> || std::is_base_of_v<Binding, T>;

    namespace Internal
    {
        template<typename BaseT>
        class BindingGroupImpl;
    }
    using BasicBindingGroup = Internal::BindingGroupImpl<BasicObject>;
    using BindingGroup = Internal::BindingGroupImpl<Object>;

    template<typename T>
    constexpr bool IsBindingGroup = std::is_base_of_v<BasicBindingGroup, T> || std::is_base_of_v<BindingGroup, T>;

    namespace Internal
    {
        template<typename BaseT>
        class ParamSpecImpl;
    }
    using BasicParamSpec = Internal::ParamSpecImpl<BasicObject>;
    using ParamSpec = Internal::ParamSpecImpl<Object>;

    template<typename T>
    constexpr bool IsParamSpec = std::is_base_of_v<BasicParamSpec, T> || std::is_base_of_v<ParamSpec, T>;

}
#endif
