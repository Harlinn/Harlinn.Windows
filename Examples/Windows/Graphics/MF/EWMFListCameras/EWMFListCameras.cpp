// EWMFListCameras.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <HWMFIDL.h>
#include <HWMediaFoundation.h>

using namespace Harlinn::Windows;
using namespace Harlinn::Common::Core;

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
    }
    
}
