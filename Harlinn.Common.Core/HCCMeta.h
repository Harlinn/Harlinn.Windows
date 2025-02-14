#pragma once
#ifndef __HCCMETA_H__
#define __HCCMETA_H__
/*
   Copyright 2024-2025 Espen Harlinn

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

#include <HCCDef.h>

namespace Harlinn::Common::Core::Meta
{
    
    using True = boost::mp11::mp_true;
    using False = boost::mp11::mp_false;

    template<typename ...Types>
    using List = boost::mp11::mp_list<Types...>;

    template<typename L, typename IndexT>
    using AtIndex = boost::mp11::mp_at<L, IndexT>;

    template<typename L, size_t index>
    using At = boost::mp11::mp_at_c<L, index>;

    template<template<class...> typename F, typename... L>
    using Transform = boost::mp11::mp_transform<F, L...>;

    template<class L1, class L2> 
    using Assign = boost::mp11::mp_assign<L1, L2>;

    template<template<class...> class F, class L>
    using Apply = boost::mp11::mp_apply<F, L>;

    template<typename L>
    using IsList = boost::mp11::mp_is_list<L>;

    template<typename L>
    using All = boost::mp11::mp_all<L>;

    template<class L, template<class...> class P> 
    using AllOf = boost::mp11::mp_all_of<L, P>;

    template<class L, template<class...> class P>
    inline constexpr bool AllOf_v = boost::mp11::mp_all_of<L, P>::value;

    template<std::size_t N> 
    using SizeT = std::integral_constant<std::size_t, N>;

    template<class... T> 
    using  Plus = boost::mp11::mp_plus<T...>;
    
    template<typename L>
    using SizeOf = boost::mp11::mp_size<L>;

    template<typename L>
    inline constexpr size_t SizeOf_v = SizeOf<L>::value;

}

#endif
