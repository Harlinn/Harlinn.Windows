#pragma once
#ifndef __HJDEF_H__
#define __HJDEF_H__
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

#include <HCCDef.h>

#include <signal.h>
#define _COMPILER_MICROSOFT_ 
#define _OS_WINDOWS_ 

// Required by the julia headers, but not defined when compiling
// using Visual C++ on Windows
template<typename T>
static inline T jl_atomic_load_relaxed( volatile T* obj )
{
    T val = *obj;
    std::atomic_signal_fence( std::memory_order::relaxed );
    return val;
}

//#include <Julia/atomics.h>
#include <Julia/julia.h>

#ifdef BUILDING_HARLINN_JULIA
#define HJ_EXPORT __declspec(dllexport)
#define HJ_TEMPLATE_EXPORT __declspec(dllexport)
#define HJ_TEMPLATE_EXPORT_DECL
#else
#define HJ_EXPORT __declspec(dllimport)
#define HJ_TEMPLATE_EXPORT __declspec(dllimport)
#define HJ_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.Julia.lib")
#endif

#pragma comment(lib,"libjulia.dll.a")

#ifdef _DEBUG
#define HJ_INLINE_DECL HJ_EXPORT
#define HJ_INLINE 
#else
#define HJ_INLINE_DECL 
#define HJ_INLINE inline
#endif

namespace Harlinn::Common::Core
{
}
namespace Harlinn::Julia
{
    using namespace Harlinn::Common::Core;

    using ValueT = jl_value_t;
    using FunctionT = jl_function_t;
    using ModuleT = jl_module_t;
    using DataTypeT = jl_datatype_t;
    using UnionAllT = jl_unionall_t;
    using TypenameT = jl_typename_t;
    using SimpleVectorT = jl_svec_t;
    using ArrayT = jl_array_t;
    using ArrayListT = arraylist_t;
    using HashTableT = htable_t;

}


#endif
