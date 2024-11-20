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



#include <HWMFIDL.h>
#include <HWMediaFoundation.h>
#include <HWMFLive555.h>

using namespace Harlinn::Windows;
using namespace Harlinn::Windows::Media::LiveMedia;
using namespace Harlinn::Common::Core;

int main()
{
    Harlinn::Common::Core::ComInitialize initialize;
    Media::MediaFoundation mediaFoundation;

    OutPacketBuffer::maxSize = 300000;

    TaskScheduler* taskScheduler = BasicTaskScheduler::createNew( );
    auto* usageEnvironment = BasicUsageEnvironment::createNew( *taskScheduler );

    auto mediaFoundationRTSPServer = MediaFoundationRTSPServer::Create( *usageEnvironment, 39000 );
    
    auto sms = ServerMediaSession::createNew( *usageEnvironment, "Camera", "Camera", "Camera Stream" );
    sms->addSubsession( MediaFoundationMediaSubsession::createNew( *usageEnvironment, True ) );
    mediaFoundationRTSPServer-> addServerMediaSession( sms );

    std::unique_ptr<char[]> rtspUrl( mediaFoundationRTSPServer->rtspURL( sms ) );

    printf( "URL:%s\n", rtspUrl.get( ) );

    // does not return
    usageEnvironment->taskScheduler( ).doEventLoop( ); 

    return 0;
    
}
