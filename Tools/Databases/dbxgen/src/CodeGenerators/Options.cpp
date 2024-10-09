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

#include "CodeGenerators/Options.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators
{
    namespace Databases
    {

        void DatabasesOptions::Load( const XmlElement& element )
        {
            if ( element.HasAttribute( L"outdir" ) )
            {
                outputDirectory_ = element.Read<WideString>( L"outdir" );
            }
        }
    }

    namespace Cpp
    {

        void CppOptions::Load( const XmlElement& element )
        {
            if ( element.HasAttribute( L"outdir" ) )
            {
                outputDirectory_ = element.Read<WideString>( L"outdir" );
            }
            if ( element.HasAttribute( L"namespace" ) )
            {
                namespace_ = element.Read<WideString>( L"namespace" );
            }
            if ( element.HasAttribute( L"dllexport" ) )
            {
                dllexport_ = element.Read<WideString>( L"dllexport" );
            }

        }

        void CppTestOptions::Load( const XmlElement& element )
        {
            if ( element.HasAttribute( L"outdir" ) )
            {
                outputDirectory_ = element.Read<WideString>( L"outdir" );
            }
            if ( element.HasAttribute( L"namespace" ) )
            {
                namespace_ = element.Read<WideString>( L"namespace" );
            }
            if ( element.HasAttribute( L"dllexport" ) )
            {
                dllexport_ = element.Read<WideString>( L"dllexport" );
            }
        }
    }

    namespace CSharp
    {
        void CSharpOptions::Load( const XmlElement& element )
        {
            if ( element.HasAttribute( L"outdir" ) )
            {
                outputDirectory_ = element.Read<WideString>( L"outdir" );
            }
            if ( element.HasAttribute( L"namespace" ) )
            {
                namespace_ = element.Read<WideString>( L"namespace" );
            }
        }
    }


    void Options::Load( const XmlElement& element )
    {
        if ( element.HasAttribute( L"model" ) )
        {
            modelFilename_ = element.Read<WideString>( L"model" );
        }
        auto databaseElement = element.Read<XmlElement>( L"database" );
        if ( databaseElement )
        {
            databases_.Load( databaseElement );
        }
        auto cppElement = element.Read<XmlElement>( L"cpp" );
        if ( cppElement )
        {
            cpp_.Load( cppElement );
        }
        auto cppTestElement = element.Read<XmlElement>( L"cpptest" );
        if ( cppTestElement )
        {
            cppTest_.Load( cppTestElement );
        }
        auto csharpElement = element.Read<XmlElement>( L"csharp" );
        if ( csharpElement )
        {
            csharp_.Load( csharpElement );
        }
    }
    std::unique_ptr<Options> Options::LoadFromFile( const WideString& optionsFilename )
    {
        using namespace Harlinn::Common::Core::Xml;

        auto document = Dom::Document::Create( );
        document.SetAsync( false );
        document.SetValidateOnParse( false );
        document.SetResolveExternals( false );
        document.SetPreserveWhiteSpace( false );

        auto success = document.Load( optionsFilename );
        if ( success )
        {
            auto documentElement = document.DocumentElement( );

            auto result = std::make_unique<Options>( );

            result->Load( documentElement );


            return result;

        }
        else
        {
            return {};
        }
    }
}