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

#include <HCCXML.h>
using namespace Harlinn::Common;

// This example prints the known interfaces implemented by the a COM object identified
// by the CLSID or ProgId provided as an argument to the program.
//
// The Media Foundation H264 Encoder MFT class id is {6CA50344-051A-4DED-9779-A43305165E35}
// 
// Executing: 
//   EQueryInterface {6CA50344-051A-4DED-9779-A43305165E35}
// 
// Displays:
//   IUnknown
//   IMFAttributes
//   IMFRealTimeClientEx
//   ICodecAPI
//   IMFTransform
// 
// There are currently 1491 known interfaces 

int main(int argc, const char* argv[] )
{
    try
    {
        Core::ComInitialize init;
        if ( argc >= 2 )
        {
            auto arg = Core::ToWideString( argv[ 1 ] );
            GUID classId;
            auto hr = CLSIDFromString( arg.c_str( ), &classId );
            if ( FAILED( hr ) )
            {
                hr = CLSIDFromProgID( arg.c_str( ), &classId );
            }
            if ( SUCCEEDED( hr ) )
            {
                auto unk = Core::Unknown::CoCreateInstanceFromClassId( classId );
                Core::Com::PrintSupportedKnownInterfaces( unk );
            }
        }
    }
    catch ( const std::exception& exc )
    {
        printf( "Exception: %s", exc.what( ) );
    }
}
