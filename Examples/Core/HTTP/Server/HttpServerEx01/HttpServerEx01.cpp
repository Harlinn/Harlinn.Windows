#include <HCCHTTP.h>
#include <HCCApplication.h>

// Execute the following command as administrator before running the server:
// netsh http add urlacl url=http://+:20000/Example user=BUILTIN\Users

using namespace Harlinn::Common::Core;

int main()
{
    auto options = std::make_shared<Harlinn::Common::Core::ApplicationOptions>( );
    options->Load( );
    Application application( options );
    application.Start( );
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


    application.Stop( );
    return 0;
}

