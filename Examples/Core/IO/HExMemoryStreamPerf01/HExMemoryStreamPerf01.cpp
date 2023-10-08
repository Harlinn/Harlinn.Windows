#include <HCCIO.h>
#include <HCCDateTime.h>
#include <HCCApplication.h>
using namespace Harlinn::Common::Core;

int main( )
{
    size_t Iterations = 10000;
    size_t Values = 100000;
    size_t bytesWritten = 0;

    auto options = std::make_shared<Harlinn::Common::Core::ApplicationOptions>( );
    options->Load( );
    auto application = std::make_shared<Application>( options );
    application->Start( );

    Stopwatch stopwatch;
    stopwatch.Start( );
    for ( size_t i = 0; i < Iterations; ++i )
    {
        IO::MemoryStream stream;
        size_t value = i + 1;
        for ( size_t j = 0; j < Values; ++j )
        {
            stream.Write( &value, sizeof( value ) );
        }
        bytesWritten += static_cast<size_t>( stream.Size( ) );
    }
    stopwatch.Stop( );
    auto duration = stopwatch.TotalSeconds( );
    auto bytesPerSecond = static_cast<double>( bytesWritten ) / duration;

    printf( "Wrote %zu bytes in %f seconds, %f bytes per second\n", bytesWritten, duration, bytesPerSecond );

    application->Stop( );
}

