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
