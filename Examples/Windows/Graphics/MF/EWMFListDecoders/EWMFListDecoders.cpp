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

    auto videoDecoders = MF::Transforms::VideoDecoders();

    for (int i = 0; i < videoDecoders.size(); i++)
    {
        auto activate = videoDecoders[i];
        auto friendlyName = activate.GetString( MFT_FRIENDLY_NAME_Attribute );
        std::wcout << friendlyName << std::endl;
    }
    
}
