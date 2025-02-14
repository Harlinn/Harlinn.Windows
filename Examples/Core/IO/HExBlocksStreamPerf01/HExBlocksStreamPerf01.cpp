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


#include <HCCIO.h>
#include <HCCDateTime.h>
#include <HCCBlocks.h>
#include <HCCApplication.h>
using namespace Harlinn::Common::Core;

int main()
{
    auto options = std::make_shared<Harlinn::Common::Core::ApplicationOptions>( );
    options->Load( );
    auto application = std::make_shared<Application>( options );
    application->Start( );

    size_t Iterations = 10000;
    size_t Values = 100000;
    size_t bytesWritten = 0;

    Stopwatch stopwatch;
    stopwatch.Start( );
    for ( size_t i = 0; i < Iterations; ++i )
    {
        IO::Blocks::Stream stream;
        size_t value = i+1;
        for ( size_t j = 0; j < Values; ++j )
        {
            stream.Write( &value, sizeof( value ) );
        }
        bytesWritten += stream.size( );
    }
    stopwatch.Stop( );
    auto duration = stopwatch.TotalSeconds( );
    auto bytesPerSecond = static_cast<double>( bytesWritten )/ duration;

    printf( "Wrote %zu bytes in %f seconds, %f bytes per second\n", bytesWritten, duration, bytesPerSecond );

    application->Stop( );
}

