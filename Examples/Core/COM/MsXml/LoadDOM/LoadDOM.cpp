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

#include <HCCXML.h>
using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Xml;

void loadDOM( )
{
    auto document = Dom::Document::Create( );
    
    document.SetAsync( false );
    document.SetValidateOnParse( false );
    document.SetResolveExternals( false );

    auto success = document.Load( L"stocks.xml" );
    if ( success )
    {
        auto xml = document.Xml( );
        wprintf( L"XML DOM loaded from stocks.xml:\n%s\n", xml.c_str() );
    }
    else
    {
        auto parserError = document.ParseError( );
        auto reason = parserError.Reason( );
        wprintf( L"Failed to load DOM from stocks.xml. %s\n", reason.c_str() );
    }
}

int main()
{
    try
    {
        ComInitialize init;
        loadDOM( );
    }
    catch ( const std::exception& exc )
    {
        printf( "Exception: %s", exc.what( ) );
    }
}
