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

#include <gst/HWMGstBuffer.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn::Media;
namespace gst = Harlinn::Media::GStreamer;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( HWMGstBufferTests, LocalFixture )

// --run_test=HWMGstBufferTests/CreateTest1
BOOST_AUTO_TEST_CASE( CreateTest1 )
{
    bool notNull = false;
    {
        auto buffer = gst::Buffer::Create( );
        notNull = buffer != nullptr;
    }
    BOOST_CHECK( notNull );

}


BOOST_AUTO_TEST_SUITE_END( )