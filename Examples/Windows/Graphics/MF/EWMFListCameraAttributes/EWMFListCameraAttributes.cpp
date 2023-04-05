// EWMFListCameraAttributes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <HWMediaFoundation.h>
#include <HWStrmif.h>

using namespace Harlinn::Windows;
using namespace Harlinn::Windows::DirectShow;
using namespace Harlinn::Common::Core;


void ProcessCameraControl(const AMCameraControl& cameraControl)
{
    auto pan = cameraControl.GetPan();
    std::wcout << "Pan: " << pan.Value << std::endl;

    auto exposure = cameraControl.GetExposure();
    std::wcout << "Exposure: "<< exposure.Value << std::endl;
}




void ProcessMediaSource(const MFMediaSource& mediaSource)
{
    auto cameraControl = mediaSource.As<AMCameraControl>();
    ProcessCameraControl(cameraControl);
}


int main()
{
    Harlinn::Common::Core::ComInitialize initialize;

    MF::MediaFoundation mediaFoundation;

    auto videoDeviceSources = MF::DeviceSources::CreateVideoDeviceSources();

    for (int i = 0; i < videoDeviceSources.size(); i++)
    {
        auto activate = videoDeviceSources[i];
        auto friendlyName = activate.GetString(MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME);
        std::wcout << friendlyName << std::endl;
        auto mediaSource = activate.ActivateObject<MFMediaSource>();
        ProcessMediaSource(mediaSource);
    }
}

