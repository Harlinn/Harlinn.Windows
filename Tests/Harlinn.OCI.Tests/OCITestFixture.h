#pragma once
#ifndef __OCITESTFIXTURE_H__
#define __OCITESTFIXTURE_H__
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

class LocalFixture
{
public:
    using WideString = Harlinn::Common::Core::WideString;

    WideString Username;
    WideString Password;
    WideString Alias;

    LocalFixture( )
    {
        using namespace Harlinn::Common::Core;
        CoInitializeEx( nullptr, COINIT_MULTITHREADED );
        auto xmlFilename = IO::Directory::GetExecutableDirectory<WideString>( ) + L"Harlinn.OCI.Tests.xml";

        auto document = Xml::Dom::Document::Create( );
        document.SetAsync( false );
        document.SetValidateOnParse( false );
        document.SetResolveExternals( false );
        document.SetPreserveWhiteSpace( true );

        auto success = document.Load( xmlFilename );


        auto documentElement = document.DocumentElement( );
        auto list = documentElement.ElementsByTagName( L"Oracle" );
        if ( list.size( ) )
        {
            Xml::Dom::Element element = list[0];

            auto username = element.Attribute( L"Username" );
            auto password = element.Attribute( L"Password" );
            auto alias = element.Attribute( L"Alias" );

            Username = username.As<WideString>( );
            Password = password.As<WideString>( );
            Alias = alias.As<WideString>( );
        }

    }
    ~LocalFixture( )
    {
        CoUninitialize( );
    }
};


#endif
