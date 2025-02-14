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


#include <iostream>
#include <HWMFIDL.h>
#include <HWMediaFoundation.h>

using namespace Harlinn::Windows;
using namespace Harlinn::Windows::Media;


void CheckUrl(const wchar_t* url)
{
    auto sourceResolver = MFSourceResolver::Create();
    auto source = sourceResolver.CreateObjectFromURL(url, MF_RESOLUTION_MEDIASOURCE | MF_RESOLUTION_CONTENT_DOES_NOT_HAVE_TO_MATCH_EXTENSION_OR_MIME_TYPE );
    auto interfaces = Com::GetSupportedKnownInterfaces(source.GetInterfacePointer());
    for (auto& itf : interfaces)
    {
        wprintf(L"%s\n", itf.c_str());
    }

}


int wmain(int argc, wchar_t** argv)
{
    ComInitialize initialize;
    MediaFoundation mediaFoundation;

    const wchar_t* url = L"rtsp://127.0.0.1:44554/sample_h264_100kbit.mp4";
    //const wchar_t* url = L"C:\\Src\\Harlinn.Windows\\Data\\SeaSurveillance.Media.Server\\Movies\\bbb_sunflower_1080p_30fps_normal.mp4";
    CheckUrl(url);
    /*
    if (argc > 1)
    {
        wchar_t* url = argv[1];
        CheckUrl(url);
    }
    */
}
