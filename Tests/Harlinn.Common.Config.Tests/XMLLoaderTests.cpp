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
#include <hccfg/hccfg_node.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <HCCIO.h>
#include <HCCString.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( )
        {
            Config::Root::Reset( );
        }

        static std::wstring SolutionDirectory( )
        {
            std::wstring executableDir = IO::Directory::GetExecutableDirectory( );
            executableDir = TrimTrailing( executableDir, []( auto c ) { return c == L'\\' || c == L'/'; } );

            auto parentDir = IO::Path::GetParentDirectory( executableDir );
            parentDir = TrimTrailing( parentDir, []( auto c ) { return c == L'\\' || c == L'/'; } );

            auto result = IO::Path::GetParentDirectory( parentDir ) ;
            return result;
        }

        static std::wstring ProjectDirectory( )
        {
            auto solutionDirectory = SolutionDirectory( );
            auto result = solutionDirectory + L"Tests\\Harlinn.Common.Config.Tests\\";
            return result;
        }

        static std::wstring Test1( )
        {
            auto projectDirectory = ProjectDirectory( );
            auto result = projectDirectory + L"Test1.xml";
            return result;
        }

        

    };
}

BOOST_FIXTURE_TEST_SUITE( XmlLoaderTests, LocalFixture )

// --run_test=XmlLoaderTests/LoadTest1
BOOST_AUTO_TEST_CASE( LoadTest1 )
{
    auto fileName = Test1( );
    auto root = Config::Root::Instance( );
    auto elements = root->Elements( );
    BOOST_CHECK( elements != nullptr );

    auto element = elements->AddElement( L"Test1" );

    element->LoadFromURI( fileName );

}
BOOST_AUTO_TEST_SUITE_END( )