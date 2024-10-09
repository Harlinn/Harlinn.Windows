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

#include "Metadata/ModelInfo.h"
#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"

namespace Harlinn::Tools::DbXGen::Metadata
{
    std::shared_ptr<EnumInfo> ModelInfo::FindEnum( const WideString& enumName ) const
    {
        auto it = enums_.find( enumName );
        if ( it != enums_.end( ) )
        {
            return ( *it ).second;
        }
        return {};
    }

    std::shared_ptr<TypeInfo> ModelInfo::FindType( const WideString& typeName ) const
    {
        auto it = types_.find( typeName );
        if ( it != types_.end( ) )
        {
            return ( *it ).second;
        }
        return {};
    }

    std::shared_ptr<ClassInfo> ModelInfo::FindClass( const WideString& className ) const
    {
        auto it = classes_.find( className );
        if ( it != classes_.end( ) )
        {
            return ( *it ).second;
        }
        return {};
    }


    void ModelInfo::Load( const XmlElement& xmlElement )
    {
        if ( xmlElement.HasAttribute( L"name" ) )
        {
            auto name = xmlElement.Read<WideString>( L"name" );
            if ( name.Length( ) > 0 )
            {
                name_ = name;
            }
        }

        if ( xmlElement.HasAttribute( L"discriminator" ) )
        {
            auto discriminatorName = xmlElement.Read<WideString>( L"discriminator" );
            if ( discriminatorName.Length( ) > 0 )
            {
                discriminatorName_ = discriminatorName;
            }
        }
        auto self = shared_from_this( );
        auto enumList = xmlElement.SelectNodes<XmlElement>( L"//model/enum" );
        for ( auto enumElement : enumList )
        {
            auto name = enumElement.Read<WideString>( L"name" );
            auto enumInfo = std::make_shared<EnumInfo>( self, name );
            enums_.emplace( name, enumInfo );
        }

        auto typeList = xmlElement.SelectNodes<XmlElement>( L"//model/type" );
        for ( auto typeElement : typeList )
        {
            auto name = typeElement.Read<WideString>( L"name" );
            auto typeInfo = std::make_shared<TypeInfo>( self, name );
            types_.emplace( name, typeInfo );
        }



        auto classList = xmlElement.SelectNodes<XmlElement>( L"//model/class" );
        for ( auto classElement : classList )
        {
            auto name = classElement.Read<WideString>( L"name" );
            auto classInfo = std::make_shared<ClassInfo>( self, name );
            classes_.emplace( name, classInfo );
        }

        for ( auto enumElement : enumList )
        {
            auto name = enumElement.Read<WideString>( L"name" );
            auto enumInfo = FindEnum( name );
            enumInfo->Load( enumElement );
        }

        for ( auto typeElement : typeList )
        {
            auto name = typeElement.Read<WideString>( L"name" );
            auto typeInfo = FindType( name );
            typeInfo->Load( typeElement );
        }

        for ( auto classElement : classList )
        {
            auto name = classElement.Read<WideString>( L"name" );
            auto classInfo = FindClass( name );
            classInfo->Load( classElement );
        }

        std::vector<std::shared_ptr<ClassInfo>> topLevelClassList;
        for ( auto& classInfo : classes_ )
        {
            if ( classInfo.second->IsTopLevel( ) )
            {
                topLevelClassList.emplace_back( classInfo.second );
            }
        }
        
        std::sort( topLevelClassList.begin( ), topLevelClassList.end( ), []( const auto& first, const auto& second ) { return first->Name( ) < second->Name( ); } );

        for ( auto& topLevelClass : topLevelClassList )
        {
            classList_.emplace_back( topLevelClass );
            topLevelClass->AddDerivedClassesToClassList( classList_ );
        }

        int classId = 10000;
        for ( auto& classInfo : classList_ )
        {
            classInfo->SetId( classId );
            classId += 100;
        }
        for ( auto& classInfo : classList_ )
        {
            classInfo->AfterLoad( );
        }
        for ( auto& classInfo : classList_ )
        {
            if ( classInfo->IsTopLevel( ) )
            {
                auto classes = classInfo->AllDerivedClassesAndSelf( );
                std::unordered_map<WideString, WideString> shortNames;
                for ( auto& cls : classes )
                {
                    auto shortName = cls->ShortName();
                    auto it = shortNames.find( shortName );
                    if ( it != shortNames.end( ) )
                    {
                        std::println( std::cout, "Short name {} for {} collides with short name for {}.", AnsiString::From( shortName ), AnsiString::From( cls->Name() ), AnsiString::From( it->second ) );
                    }
                    else
                    {
                        shortNames.emplace( shortName, cls->Name() );

                    }
                }
            }
        }
        Validate( );
    }

    void ModelInfo::Validate( ) const
    {
        for ( auto& classInfo : classList_ )
        {
            classInfo->Validate( );
        }
    }


    std::shared_ptr<ModelInfo> ModelInfo::LoadFromFile( const WideString& filename )
    {
        using namespace Harlinn::Common::Core::Xml;

        auto document = Dom::Document::Create( );
        document.SetAsync( false );
        document.SetValidateOnParse( false );
        document.SetResolveExternals( false );
        document.SetPreserveWhiteSpace( false );

        auto success = document.Load( filename );
        if ( success )
        {
            auto documentElement = document.DocumentElement( );

            auto result = std::make_shared<ModelInfo>( );

            result->Load( documentElement );


            return result;

        }
        else
        {
            return {};
        }

    }
}