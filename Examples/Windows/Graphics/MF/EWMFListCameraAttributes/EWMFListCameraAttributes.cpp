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

