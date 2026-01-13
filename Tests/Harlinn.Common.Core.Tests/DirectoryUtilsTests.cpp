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

#include <HCCDirectoryUtils.h>

using namespace Harlinn::Common::Core;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture() {}
        ~LocalFixture() {}
    };
}

BOOST_FIXTURE_TEST_SUITE(DirectoryUtilsTests, LocalFixture)

// --run_test=DirectoryUtilsTests/ApplicationDirectoriesTest1
BOOST_AUTO_TEST_CASE(ApplicationDirectoriesTest1)
{
    ApplicationDirectories<WideString> applicationDirectories;

    auto& baseName = applicationDirectories.ExecutableBaseName();
    auto& directory = applicationDirectories.ExecutableDirectory();
    auto& rootDirectory = applicationDirectories.RootDirectory();
    auto dataDirectory1 = applicationDirectories.ExpandDirectory(L"Data");
    auto dataDirectory2 = applicationDirectories.ExpandDirectory(L"\\Data");
    auto dataDirectory3 = applicationDirectories.ExpandDirectory(L"Data\\");
    auto dataDirectory4 = applicationDirectories.ExpandDirectory(L"\\Data\\");

    BOOST_CHECK(baseName.empty() == false);
    BOOST_CHECK(directory.empty() == false);
    BOOST_CHECK(rootDirectory.empty() == false);
    BOOST_CHECK(dataDirectory1.empty() == false);
    BOOST_CHECK(dataDirectory1 == dataDirectory2);
    BOOST_CHECK(dataDirectory1 == dataDirectory3);
    BOOST_CHECK(dataDirectory1 == dataDirectory4);


}
BOOST_AUTO_TEST_SUITE_END()