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


#include <HCCLogging.h>
#include <HCCLoggerImpl.h>
#include <HCCApplication.h>

#include <HCCIO.h>
#include <HCCEnvironment.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Logging;

int main()
{
    auto options = std::make_shared<Harlinn::Common::Core::ApplicationOptions>( );
    options->Load( );
    auto application = std::make_shared<Application>( options );
    application->Start( );

    try
    {
        constexpr size_t Iterations = 10;// 1'000;


        constexpr Int32 intValue1 = 1;

        auto logManager = Logging::LogManager::Instance( );
        IO::MemoryStream memoryStream;
        auto textFormatter = std::make_shared<Formatters::TextFormatter<>>( memoryStream );
        logManager->Add( textFormatter );

        Stopwatch stopwatch;
        stopwatch.Start( );

        for ( size_t i = 0; i < Iterations; i++ )
        {
            HCC_DEBUG( "Iteration:{}", i );
        }

        CurrentThread::FlushLogger( );
        stopwatch.Stop( );

        auto duration = stopwatch.TotalSeconds( );
        auto perSecond = Iterations / duration;
        auto average = duration / Iterations;
        auto messagesPosted = logManager->MessagesPosted( );

        printf( "Logged %zu DEBUG records in %f seconds. %f per second, Average %.9f seconds per record, Messages posted: %zu\n", Iterations, duration, perSecond, average, messagesPosted );


        auto statistics = logManager->Statistics( );
        auto statisticsStr = ToAnsiString( statistics );
        printf( "Statistics: %s\n", statisticsStr.c_str( ) );

        auto streamedText = ToAnsiString( memoryStream );
        puts( streamedText.c_str( ) );



    }
    catch ( Exception& exception )
    {
        auto typeName = exception.TypeName( );
        auto message = exception.Message( );
        wprintf( L"Caught %s Exception\nMessage:%s\n", typeName.c_str( ), message.c_str( ) );
    }
    application->Stop( );
}

