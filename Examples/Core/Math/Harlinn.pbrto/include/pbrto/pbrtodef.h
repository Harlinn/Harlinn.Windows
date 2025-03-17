#pragma once
#ifndef PBRTODEF_H_
#define PBRTODEF_H_

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


#ifdef BUILDING_HARLINN_PBRTO
#define PBRTO_EXPORT __declspec(dllexport)
#define PBRTO_TEMPLATE_EXPORT __declspec(dllexport)
#define PBRTO_TEMPLATE_EXPORT_DECL
#else
#define PBRTO_EXPORT __declspec(dllimport)
#define PBRTO_TEMPLATE_EXPORT __declspec(dllimport)
#define PBRTO_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.pbrto.lib")
#endif


#define PBRT_IS_WINDOWS 1
#define PBRT_HAS_INTRIN_H 1

#ifndef _ENABLE_EXTENDED_ALIGNED_STORAGE
#define _ENABLE_EXTENDED_ALIGNED_STORAGE 1
#endif

#ifndef WIN32
#define WIN32 1
#endif

#ifndef _WINDOWS
#define _WINDOWS 1
#endif

#ifndef PBRT_IS_MSVC
#define PBRT_IS_MSVC 1
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#ifndef NOMINMAX
#define NOMINMAX 1
#endif

#ifndef PBRT_NOINLINE
#define PBRT_NOINLINE __declspec( noinline )
#endif

#ifndef PBRT_RESTRICT
#define PBRT_RESTRICT __restrict
#endif

#ifndef PBRT_HAVE__ALIGNED_MALLOC
#define PBRT_HAVE__ALIGNED_MALLOC 1
#endif

#define PBRT_USES_HCCMATH 1
#ifdef PBRT_USES_HCCMATH
#define PBRT_USES_HCCMATH_SINCOS 1
#define PBRT_USES_HCCMATH_SQRT 1
#define PBRT_USES_HCCMATH_HYPOT 1
#define PBRT_USES_HCCMATH_COPYSIGN 1
#define PBRT_USES_HCCMATH_ATAN 1
#define PBRT_USES_HCCMATH_ATAN2 1
#define PBRT_USES_HCCMATH_EXP 1
#define PBRT_USES_HCCMATH_LOG 1
#define PBRT_USES_HCCMATH_LOG2 1
#define PBRT_USES_HCCMATH_LOG10 1
#define PBRT_USES_HCCMATH_FMOD 1
#define PBRT_USES_HCCSIMD 1
#define PBRT_USES_STD 1

#define PBRT_USES_HCCMATH_INTERVAL 1
#endif

#define PBRT_CONSTEXPR //constexpr

#ifdef PBRT_USES_HCCMATH
#include <HCCVectorMath.h>
using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Math;
#endif


#endif
