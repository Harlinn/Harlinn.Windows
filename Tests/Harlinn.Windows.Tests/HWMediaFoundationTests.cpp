#include <HWMediaFoundation.h>
#include <HCCDateTime.h>
#include <HCCGuid.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Windows;
using namespace Harlinn::Windows::MF;

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
