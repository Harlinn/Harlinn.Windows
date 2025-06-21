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


#include <HCCHTTP.h>
#include <HCCApplication.h>

// Execute the following command as administrator before running the server:
// netsh http add urlacl url=http://+:20000/Example user=BUILTIN\Users
// The url is: http://127.0.0.1:20000/Example

using namespace Harlinn::Common;
using namespace Harlinn::Common::Core;

int main()
{
    auto options = std::make_shared<Harlinn::Common::Core::ApplicationOptions>( );
    options->Load( );
    auto application = std::make_shared<Application>( options );
    application->Start( );
    try
    {
        Http::Application httpApplication;
        Http::ApiVersion httpApiVersion( 2, 0 );
        Http::ServerSession httpServerSession( httpApiVersion );
        auto httpRequestQueue = std::make_shared<Http::RequestQueue>( httpApiVersion, L"ExRQ" );
        Byte defaultRequestBuffer[Http::RequestQueue::DefaultRequestBufferSize];

        auto urlGroup = httpServerSession.CreateUrlGroup( );

        urlGroup.AddUrl( L"http://+:20000/Example/" );
        urlGroup.Bind( *httpRequestQueue );

        while ( true )
        {
            std::unique_ptr<Byte[]> largeBuffer;
            Http::Request* httpRequest = reinterpret_cast<Http::Request*>( defaultRequestBuffer );
            UInt32 bytesReceived = 0;
            auto rc = httpRequestQueue->Receive( Http::ReceiveRequestFlags::FlushBody, httpRequest, Http::RequestQueue::DefaultRequestBufferSize, &bytesReceived );
            if ( rc == ERROR_MORE_DATA )
            {
                auto requestId = httpRequest->RequestId;
                largeBuffer = std::make_unique<Byte[]>( bytesReceived );
                httpRequest = reinterpret_cast<Http::Request*>( largeBuffer.get( ) );
                UInt32 bytesReceived2 = 0;
                rc = httpRequestQueue->Receive( requestId, Http::ReceiveRequestFlags::FlushBody, httpRequest, bytesReceived, &bytesReceived2 );
            }
            if ( rc != NO_ERROR )
            {
                ThrowOSError( rc );
            }

            httpRequestQueue->SendResponse( httpRequest->RequestId,200,"OK", "<body><em>Hello</em> from Example HTTP Server</body>" );
        }
    }
    catch ( std::exception& exc )
    {
        auto what = exc.what( );
        printf( "Exception:%s\n", what );
    }


    application->Stop( );
    return 0;
}

