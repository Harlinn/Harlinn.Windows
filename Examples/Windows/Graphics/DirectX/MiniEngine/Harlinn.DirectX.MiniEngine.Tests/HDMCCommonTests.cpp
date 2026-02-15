/*
    Copyright 2024-2026 Espen Harlinn

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

using namespace Harlinn::Common::Core;
using namespace Harlinn::Windows::DirectX::MiniEngine;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( HDMCCommonTests, LocalFixture )

// --run_test=HDMCCommonTests/SplatZeroTest
BOOST_AUTO_TEST_CASE( SplatZeroTest )
{
    auto result = SplatZero( );
    Vector4 v = Vector4( result );
#ifdef HDMC_USES_HCC_MATH
    m::Vector<float, 4> vec( v );
    bool allZero =
        vec.x == 0.0f &&
        vec.y == 0.0f &&
        vec.z == 0.0f &&
        vec.w == 0.0f;
    BOOST_TEST( allZero );
#else
    ::DirectX::XMFLOAT4A f;
    ::DirectX::XMStoreFloat4A( &f, v );
    bool allZero =
        f.x == 0.0f &&
        f.y == 0.0f &&
        f.z == 0.0f &&
        f.w == 0.0f;
    BOOST_TEST( allZero );
#endif
}

// --run_test=HDMCCommonTests/SplatOneTest
BOOST_AUTO_TEST_CASE( SplatOneTest )
{
    auto result = SplatOne( );
    Vector4 v = Vector4( result );

#ifdef HDMC_USES_HCC_MATH
    m::Vector<float, 4> vec( v );
    bool allOne =
        vec.x == 1.0f &&
        vec.y == 1.0f &&
        vec.z == 1.0f &&
        vec.w == 1.0f;
    BOOST_TEST( allOne );
#else
    ::DirectX::XMFLOAT4A f;
    ::DirectX::XMStoreFloat4A( &f, v );
    bool allOne =
        f.x == 1.0f &&
        f.y == 1.0f &&
        f.z == 1.0f &&
        f.w == 1.0f;
    BOOST_TEST( allOne );
#endif
}



BOOST_AUTO_TEST_SUITE_END( )