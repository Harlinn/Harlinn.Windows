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


#include <HWMVlc.h>

using namespace Harlinn::Media;
using namespace Harlinn::Common::Core;

int main()
{
    Vlc::Arguments arguments;
    arguments.ImportCommandLine( );
    arguments.insert( arguments.begin() +  1, WideString(L"--media-library") );
    arguments.insert( arguments.begin( ) + 2, WideString( L"--no-ignore-config" ) );

    Vlc::Instance instance( arguments );
    instance.SetApplicationId( "EWM Media Server", "1.0", nullptr );
    instance.SetUserAgent( "EWM Media Server", "EWMMS/1.0" );
    instance.AddInterface( "hotkeys,none" );
    instance.AddInterface( "globalhotkeys,none" );

    instance.PlayListPlay( -1, 0, nullptr );
    instance.Wait( );


}
