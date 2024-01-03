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


#include <HCCHTTPServer.h>
#include <HCCApplication.h>

// Execute the following command as administrator before running the server:
// netsh http add urlacl url=http://+:20000/Example user=BUILTIN\Users


using namespace Harlinn::Common::Core;

int main()
{
    auto options = std::make_shared<Harlinn::Common::Core::ApplicationOptions>( );
    options->Load( );
    auto application = std::make_shared<Application>( options );
    application->Start( );
    try
    {
        constexpr size_t NumberOfConcurrentRequests = 12;
        constexpr DWORD ThreadPoolSize = 12;

        Http::Application httpApplication;
        Http::ApiVersion httpApiVersion( 2, 0 );
        auto context = std::make_shared<IO::Context>( ThreadPoolSize );
        Http::Server::HttpServer httpServer( context );
        auto* urlGoup = httpServer.AddUrlGroup( );
        auto httpRequestQueue = std::make_shared<Http::RequestQueue>( httpApiVersion, L"ExRQ" );

        
        urlGoup->AddUrl( L"http://+:20000/Example/" );
        urlGoup->Bind( httpRequestQueue->Handle() );

        auto serverHandler = httpServer.AddRequestHandler<Http::Server::HttpRequestDispatcher>( );
        
        serverHandler->OnProcess.connect( []( const Http::Server::HttpRequestDispatcher& dispatcher, const Http::Server::HttpRequest& request, Http::Server::HttpResponse& response )
        {
            auto& body = response.Body( );
            AnsiString html = "<body><em>Hello</em> from Example HTTP Server</body>";
            body.Write( html.c_str(), html.size() );
        } );
        

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
    application->Stop( );
    return 0;
}
