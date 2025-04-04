#pragma once

#include <HCCVectorMath.h>
#include <HCCString.h>
#include <HCCTestUtils.h>
#include <pbrto/util/vecmath.h>
#include <pbrto/util/transform.h>
#include <DirectXMath.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <HUTFixture.h>
#include <HUTVectorMath.h>

template<typename ValueT, size_t N >
using RandomGenerator = Harlinn::Common::Core::Test::Generators::RandomGenerator<ValueT, N>;

using Harlinn::Common::Core::Test::Deviation;





