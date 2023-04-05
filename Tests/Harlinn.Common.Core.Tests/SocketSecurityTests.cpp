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


    class Channel
    {

    };


    class ClientSchannel
    {
        Security::CredentialsHandle credentials_;
    };


    class ServerSchannel
    {

    };




    class ClientThread
    {
        
    public:
        void Run( )
        {
        }
    };

    class ServerThread
    {
        std::atomic<bool> closed_;
        Security::CredentialsHandle credentials_;
    public:
        ServerThread()
        { }
    private:
        void InitializeCredentials( )
        {
            //credentials_ = Security::CredentialsHandle::Schannel( );
        }
    public:
        void Run( )
        {
            while ( closed_ == false )
            {

            }

        }
    };


}


BOOST_FIXTURE_TEST_SUITE( SocketSecurityTests, LocalFixture )

// --run_test=SocketSecurityTests/OpenSystemStoreTest1
BOOST_AUTO_TEST_CASE( OpenSystemStoreTest1 )
{
    
}

BOOST_AUTO_TEST_SUITE_END( )
