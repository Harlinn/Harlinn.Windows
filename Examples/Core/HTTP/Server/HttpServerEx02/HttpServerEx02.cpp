#include <HCCHTTPServer.h>
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
        constexpr size_t NumberOfConcurrentRequests = 12;
        constexpr DWORD ThreadPoolSize = 12;

        auto context = std::make_shared<IO::Context>( ThreadPoolSize );
        Http::Server::HttpServer httpServer( context );
        auto* urlGoup = httpServer.AddUrlGroup( );
        auto requestQueue = httpServer.AddRequestQueue( NumberOfConcurrentRequests, L"ExRQ" );
        urlGoup->AddUrl( L"http://+:20000/Example/" );
        urlGoup->Bind( *requestQueue );


        /*
        for ( size_t i = 0; i < NumberOfConcurrentRequests; ++i )
        {
            serverHandler.ReceiveRequest( requestQueue, Http::ReceiveRequestFlags::FlushBody );
        }
        serverHandler.OnReceiveRequest.connect( []( const Http::ServerRequest& request, Http::ServerResponse& response )
        {
            auto& body = response.Body( );
            body.Write( "<body><em>Hello</em> from Example HTTP Server</body>" );
        } );
        */

        context->Start( );

        puts( "Press enter to exit" );
        while ( getc( stdin ) != '\n' );

        context->Stop( );
    }
    catch ( std::exception& exc )
    {
        std::string message = exc.what( );
        printf( "Exception: %s", message.c_str( ) );
    }
    application.Stop( );
    return 0;
}
