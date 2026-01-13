/*
   Copyright 2024-2026 Espen Harlinn

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

using namespace Harlinn::Windows;
using namespace Harlinn::Common::Core;

int main()
{
    Harlinn::Common::Core::ComInitialize initialize;
    
    Media::MediaFoundation mediaFoundation;

    auto videoDecoders = Media::Transforms::VideoDecoders();

    for (int i = 0; i < videoDecoders.size(); i++)
    {
        auto activate = videoDecoders[i];
        auto friendlyName = activate.GetString( MFT_FRIENDLY_NAME_Attribute );
        std::wcout << friendlyName << std::endl;
    }
    
}
