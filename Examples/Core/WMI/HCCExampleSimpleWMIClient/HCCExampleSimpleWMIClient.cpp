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


#include <HCCwbem.h>
namespace hcc = Harlinn::Common::Core;

int main()
{
    int result = 1;

    // Step 1: Initialize COM.
    hcc::Com::Initialize( );
    // Step 2: Set general COM security levels
    hcc::Com::InitializeClientSecurity( );

    try
    {
        // Step 3: Obtain the initial locator to WMI 
        auto locator = hcc::WbemLocator::Create( );

        // Step 4: Connect to WMI using the locator
        auto services = locator.ConnectServer( L"ROOT\\CIMV2" );

        std::cout << "Connected to ROOT\\CIMV2 WMI namespace" << std::endl;

        // Step 5: Set security levels on the proxy 
        hcc::Com::SetClientProxyBlanket( services );

        // Step 6: Use the WbemServices object to make requests of WMI
        // For example, get the name of the operating system
        auto enumerator = services.ExecQuery( L"SELECT * FROM Win32_OperatingSystem" );

        // Step 7: Get the data from the query in step 6 
        while ( auto object = enumerator.Next( ) )
        {
            // Get the value of the Name property
            hcc::Variant property = object.Get( L"Name" );
            std::wcout << "OS Name : " << property.bstrVal << std::endl;
        }
        result = 0;
    }
    catch ( const hcc::Exception& exc )
    {
    }
    catch ( const std::exception& exc )
    {
    }
    catch ( ... )
    {
    }
    hcc::Com::Uninitialize( );
    return result;

}


