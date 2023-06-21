#pragma once
#ifndef __OCITESTFIXTURE_H__
#define __OCITESTFIXTURE_H__

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
