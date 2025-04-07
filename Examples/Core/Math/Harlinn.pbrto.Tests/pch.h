#pragma once
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

#include <HCCVectorMath.h>
#include <HCCString.h>
#include <HCCTestUtils.h>
#include <pbrto/util/vecmath.h>
#include <pbrto/util/transform.h>
#include <pbrto/util/NewVecmath.h>
#include <pbrto/util/NewTransform.h>
#include <DirectXMath.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <HUTFixture.h>
#include <HUTVectorMath.h>

template<typename ValueT, size_t N >
using RandomGenerator = Harlinn::Common::Core::Test::Generators::RandomGenerator<ValueT, N>;

using Harlinn::Common::Core::Test::Deviation;