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

#include "pch.h"

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Security;
namespace
{
    WideString GetTestFileDirectory( )
    {
        WideString TestDataRoot = Environment::EnvironmentVariable( L"HCC_TEST_DATA_ROOT" );
        auto directoryPath = IO::Path::Combine( TestDataRoot, L"\\ACLTests" );

        if ( IO::Directory::Exist( directoryPath ) == false )
        {
            IO::Directory::Create( directoryPath );
        }
        return directoryPath;
    }

    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( SecurityAccessControlListTests, LocalFixture )

// --run_test=SecurityAccessControlListTests/FileSecurityTest1
BOOST_AUTO_TEST_CASE( FileSecurityTest1 )
{
    auto testFileDirectory = GetTestFileDirectory( );
    auto testFileName = testFileDirectory + L"\\acl.tst";
    if ( IO::File::Exist( testFileName ) )
    {
        IO::File::Delete( testFileName );
    }
    //SecurityId me




    SecurityDescriptor securityDescriptor;
    SecurityAttributes securityAttributes( securityDescriptor );
    IO::FileStream fileStream( testFileName, 
                                    IO::FileAccess::Default, 
                                    IO::FileShare::Default, 
                                    &securityAttributes, 
                                    IO::FileMode::Create, 
                                    IO::FileAttributes::Normal, 
                                    IO::FileOptions::Default );


}

BOOST_AUTO_TEST_SUITE_END( )