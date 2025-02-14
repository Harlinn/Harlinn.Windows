#pragma once
#ifndef BENCHMARKUTILS_H_
#define BENCHMARKUTILS_H_

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

#include <HCCMath.h>
#include <HCCVectorMath.h>
#include <pbrto/util/vecmath.h>
#include <benchmark/benchmark.h>
#include <HCCTestUtils.h>
#include <DirectXMath.h>

#define RUN_BASIC_MATH_BENCHMARKS 1
#define RUN_VECTOR2FLOAT_BENCHMARKS 1
#define RUN_PBRT_BENCHMARKS 1
#define RUN_DXM_BENCHMARKS 1
#define RUN_SQUAREMATRIX_BENCHMARKS 1
#define RUN_TRANSFORM_BENCHMARKS 1
#define RUN_QUATERNION_BENCHMARKS 1

using namespace Harlinn::Common::Core;
namespace OpenLibM = Harlinn::Common::Core::Math::Internal::OpenLibM;

template<typename ValueT, size_t N >
using RandomGenerator = Test::Generators::RandomGenerator<ValueT, N>;

constexpr size_t SampleCount = 64;



#endif
