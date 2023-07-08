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