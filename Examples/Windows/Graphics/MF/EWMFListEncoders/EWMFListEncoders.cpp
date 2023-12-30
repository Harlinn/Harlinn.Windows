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

    auto videoEncoders = MF::Transforms::VideoEncoders();

    for (int i = 0; i < videoEncoders.size(); i++)
    {
        auto activate = videoEncoders[i];
        auto friendlyName = activate.GetString( MFT_FRIENDLY_NAME_Attribute );
        if ( activate.HasAttribute( MFT_TRANSFORM_CLSID_Attribute ) )
        {
            auto clsid = activate.GetGUID( MFT_TRANSFORM_CLSID_Attribute );
            std::wcout << friendlyName << L":" << clsid.ToString( ) << std::endl;
        }
        else
        {
            std::wcout << friendlyName << L": <missing>" << std::endl;
        }
    }
    
}
