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

#include <HWMediaFoundation.h>
#include <HCCDateTime.h>
#include <HCCGuid.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Windows;
using namespace Harlinn::Windows::Media;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture() {}
        ~LocalFixture() {}
    };
}

BOOST_FIXTURE_TEST_SUITE(HWMediaFoundationTests, LocalFixture)

// --run_test=HWMediaFoundationTests/MakeIMFAsyncCallbackTest1
BOOST_AUTO_TEST_CASE(MakeIMFAsyncCallbackTest1)
{
    bool invoked = false;
    auto callback = MakeIMFAsyncCallback([&invoked]()
        {
            invoked = true;
        });
    callback.Invoke(nullptr);
    BOOST_CHECK(invoked == true);

}

// --run_test=HWMediaFoundationTests/MakeIMFAsyncCallbackTest2
BOOST_AUTO_TEST_CASE(MakeIMFAsyncCallbackTest2)
{
    bool invoked = false;
    auto callback = MakeIMFAsyncCallback([&invoked]()
        {
            invoked = true;
        });
    {
        auto callbackUnknown = callback.As<Harlinn::Common::Core::Unknown>();
        {
            auto callBackAsyncCallback = callbackUnknown.As<MFAsyncCallback>();
        }
    }


    callback.Invoke(nullptr);
    BOOST_CHECK(invoked == true);

}





BOOST_AUTO_TEST_SUITE_END()
