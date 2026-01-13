#pragma once
#ifndef D2MSUBSTITUTIONTABLE_H_
#define D2MSUBSTITUTIONTABLE_H_

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


#include <HCCRapidXml.h>
#include <HCCIO.h>

namespace Doxygen2Md
{
    using namespace Harlinn::Common;
    using namespace Harlinn::Common::Core;
    using namespace std::literals::string_view_literals;

    class SubstitutionEntry
    {
    public:
        using XmlAttribute = RapidXml::XmlAttribute<char>;
        using XmlNode = RapidXml::XmlNode<char>;
    private:
        static constexpr auto replace = "replace"sv;
        static constexpr auto with = "with"sv;
        std::string replace_;
        std::string with_;
    public:
        SubstitutionEntry( ) = default;
        explicit SubstitutionEntry( const XmlNode& node )
        {
            auto replaceAttribute = node.Attribute( replace );
            if ( !replaceAttribute )
            {
                throw std::invalid_argument( "Missing \"replace\" attribute." );
            }
            auto s = replaceAttribute.Read<std::string>( );
            if ( s.empty( ) )
            {
                throw std::invalid_argument( "The \"replace\" attribute is empty." );
            }
            replace_ = s;
            with_ = node.Read<std::string>( with );
        }
        

        const std::string& Replace( ) const
        {
            return replace_;
        }
        const std::string& With( ) const
        {
            return with_;
        }
    };

    class SubstitutionTable : public std::vector<SubstitutionEntry>
    {
    public:
        using XmlAttribute = RapidXml::XmlAttribute<char>;
        using XmlNode = RapidXml::XmlNode<char>;
    private:
    public:
        SubstitutionTable( ) = default;


        static SubstitutionTable Load( const std::string& path )
        {
            SubstitutionTable result;
            std::string xml;
            IO::File::ReadAndAppendAllTextTo( path, xml );

            if ( xml.size( ) )
            {
                RapidXml::XmlParser xmlParser;
                char* xmlText = xml.data( );
                xmlParser.Parse<RapidXml::ParsingFlags::NonDestructive>( xmlText );

                auto xmlDocument = xmlParser.Document( );

                auto substitutionsNode = xmlDocument.FirstNode( "substitutions" );
                if ( substitutionsNode )
                {
                    auto childNode = substitutionsNode.FirstNode( );
                    if ( childNode )
                    {
                        do
                        {
                            auto nodeName = childNode.Name( );
                            if ( nodeName == "substitution"sv )
                            {
                                SubstitutionEntry entry( childNode );
                                result.push_back( entry );
                            }
                            childNode = childNode.NextSibling( );
                        } while ( childNode );
                    }
                }
            }

            std::ranges::sort( result, []( const auto& first, const auto& second ) 
                {
                    return first.Replace( ) > second.Replace( );
                } );

            return result;
        }
    };



}

#endif