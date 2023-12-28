// EWMFListCameras.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <HWMFIDL.h>
#include <HWMediaFoundation.h>
#include <HWMFLive555.h>

using namespace Harlinn::Windows;
using namespace Harlinn::Windows::LiveMedia;
using namespace Harlinn::Common::Core;

int main()
{
    Harlinn::Common::Core::ComInitialize initialize;
    MF::MediaFoundation mediaFoundation;

    _putws( L"Video Encoders:" );
    MF::PrintVideoEncoders( );
    _putws( L"Video Decoders:" );
    MF::PrintVideoDecoders( );

    TaskScheduler* taskScheduler = BasicTaskScheduler::createNew( );
    auto* usageEnvironment = BasicUsageEnvironment::createNew( *taskScheduler );

    auto mediaFoundationRTSPServer = MediaFoundationRTSPServer::Create( *usageEnvironment, 39000 );
    
    OutPacketBuffer::maxSize = 600000;
    auto sms = ServerMediaSession::createNew( *usageEnvironment, "Camera", "Camera", "Camera Stream" );
    sms->addSubsession( MediaFoundationMediaSubsession::createNew( *usageEnvironment, True ) );
    mediaFoundationRTSPServer-> addServerMediaSession( sms );

    std::unique_ptr<char[]> rtspUrl( mediaFoundationRTSPServer->rtspURL( sms ) );

    printf( "URL:%s\n", rtspUrl.get( ) );

    // does not return
    usageEnvironment->taskScheduler( ).doEventLoop( ); 

    return 0;
    
}
