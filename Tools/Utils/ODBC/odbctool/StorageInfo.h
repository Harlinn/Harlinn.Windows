#pragma once
#ifndef STORAGEINFO_H_
#define STORAGEINFO_H_

#include "EnumInfo.h"
#include "ClassInfo.h"

namespace Harlinn::ODBC::Tool
{
    class StorageInfo : public std::enable_shared_from_this<StorageInfo>
    {
        std::unordered_map<WideString, std::shared_ptr<EnumInfo>> enums_;
        std::unordered_map<WideString, std::shared_ptr<ClassInfo>> classes_;
    public:
        StorageInfo()
        { }


        void Load( const XmlElement& xmlElement )
        {
            auto self = shared_from_this( );
            auto enumList = xmlElement.ElementsByTagName( L"enum" );
            for ( auto enumElement : enumList )
            {
                auto name = enumElement.Read<WideString>( L"name" );
                auto enumInfo = std::make_shared<EnumInfo>( self, name );
                enums_.emplace( name, enumInfo );
            }


            auto classList = xmlElement.ElementsByTagName( L"class" );
            for ( auto classElement : classList )
            {
                auto name = classElement.Read<WideString>( L"name" );
                auto classInfo = std::make_shared<ClassInfo>( self, name );
                classes_.emplace( name, classInfo );
            }


        }


        static std::shared_ptr<StorageInfo> LoadFromFile( const WideString& filename )
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

                auto result = std::make_shared<StorageInfo>( );

                result->Load( documentElement );
                

                return result;

            }
            else
            {
                return {};
            }

        }






    };

}

#endif
