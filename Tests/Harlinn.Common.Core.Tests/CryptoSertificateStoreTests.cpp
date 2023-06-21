#include "pch.h"

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Crypto;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( CryptoSertificateStoreTests, LocalFixture )

// --run_test=CryptoSertificateStoreTests/OpenSystemStoreTest1
BOOST_AUTO_TEST_CASE( OpenSystemStoreTest1 )
{
    auto caStore = CertificateStore::OpenSystemStore( "CA" );
    BOOST_CHECK( caStore.Handle() != 0 );
}

// --run_test=CryptoSertificateStoreTests/GetSystemStoreNamesTest1
BOOST_AUTO_TEST_CASE( GetSystemStoreNamesTest1 )
{
    std::vector<WideString> systemStoreNames;
    CertificateStore::GetSystemStoreNames( CertificateStoreLocation::CurrentUser, systemStoreNames );
    BOOST_CHECK( systemStoreNames.size() != 0 );
}

// --run_test=CryptoSertificateStoreTests/GetCertificatesTest1
BOOST_AUTO_TEST_CASE( GetCertificatesTest1 )
{
    auto caStore = CertificateStore::OpenSystemStore( "CA" );
    std::vector<CertificateContext> certificates;
    caStore.GetCertificates( certificates );

    BOOST_CHECK( certificates.size() != 0 );
}



BOOST_AUTO_TEST_SUITE_END( )
