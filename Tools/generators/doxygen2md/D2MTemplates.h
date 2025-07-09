#pragma once
#ifndef D2MTEMPLATES_H_
#define D2MTEMPLATES_H_

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

#include <HCCDoxygen.h>
#include <HCCIO.h>
#include <HCCRapidXml.h>

#include <inja/inja.hpp>

#include "D2MPathBuilder.h"

namespace Doxygen2Md
{
    using namespace Harlinn::Common;
    using namespace Harlinn::Common::Core;


    class Templates
    {
        std::string header_;
        std::string class_list_;
        std::string class_;
        std::string concept_list_;
        std::string concept_;
        std::string enum_list_;
        std::string enum_;
        std::string function_list_;
        std::string function_;
        std::string union_list_;
        std::string union_;
        std::string namespace_list_;
        std::string namespace_;
        std::string variable_list_;
        std::string typedef_list_;
    public:

        const std::string& Header() const { return header_; }
        const std::string& ClassList() const { return class_list_; }
        const std::string& Class() const { return class_; }
        const std::string& ConceptList() const { return concept_list_; }
        const std::string& Concept() const { return concept_; }
        const std::string& EnumList () const { return enum_list_; }
        const std::string& Enum() const { return enum_; }
        const std::string& FunctionList () const { return function_list_; }
        const std::string& Function() const { return function_; }
        const std::string& UnionList () const { return union_list_; }
        const std::string& Union() const { return union_; }
        const std::string& NamespaceList () const { return namespace_list_; }
        const std::string& Namespace () const { return namespace_; }
        const std::string& VariableList () const { return variable_list_; }
        const std::string& TypedefList( ) const { return typedef_list_; }
    private:
        static std::string ReadTemplate( const RapidXml::XmlNode<>& templatesNode, const std::string& templateName, const std::string& templateDirectory )
        {
            auto templateNode = templatesNode.FirstNode( templateName );
            if ( templateNode )
            {
                auto fileAttribute = templateNode.Attribute( "file" );
                if ( fileAttribute )
                {
                    auto filename = fileAttribute.Read<std::string>( );
                    if ( IO::File::Exist( filename ) == false )
                    {
                        auto combined = IO::Path::Combine( templateDirectory, filename );
                        if ( IO::File::Exist( combined ) == false )
                        {
                            throw IO::FileNotFoundException( filename );
                        }
                        filename = combined;
                    }
                    std::string templateText;
                    IO::File::ReadAndAppendAllTextTo( filename, templateText );
                    return templateText;
                }
                else
                {
                    return Html::Decode<std::string>( templateNode.Content<std::string>( ) );
                }
            }
            auto message = std::format( "Unknown xml node: {} ", templateName );
            throw ArgumentException( message.c_str( ), "templateName" );
        }
    public:
        static Templates Load( const std::string& templatesPath )
        {
            std::string xml;
            IO::File::ReadAndAppendAllTextTo( templatesPath, xml );

            if ( xml.size( ) )
            {
                RapidXml::XmlParser xmlParser;
                char* xmlText = xml.data( );
                xmlParser.Parse<RapidXml::ParsingFlags::NonDestructive>( xmlText );

                auto xmlDocument = xmlParser.Document( );

                auto xmlNode = xmlDocument.FirstNode( "templates" );
                if ( xmlNode )
                {
                    auto templateDirectory = IO::Path::GetParentDirectory( templatesPath );

                    Templates result;

                    result.header_ = ReadTemplate(xmlNode,"header", templateDirectory );
                    result.class_list_ = ReadTemplate( xmlNode, "class_list", templateDirectory );
                    result.class_ = ReadTemplate( xmlNode, "class", templateDirectory );
                    result.concept_list_ = ReadTemplate( xmlNode, "concept_list", templateDirectory );
                    result.concept_ = ReadTemplate( xmlNode, "concept", templateDirectory );
                    result.enum_list_ = ReadTemplate( xmlNode, "enum_list", templateDirectory );
                    result.enum_ = ReadTemplate( xmlNode, "enum", templateDirectory );
                    result.function_list_ = ReadTemplate( xmlNode, "function_list", templateDirectory );
                    result.function_ = ReadTemplate( xmlNode, "function", templateDirectory );
                    result.union_list_ = ReadTemplate( xmlNode, "union_list", templateDirectory );
                    result.union_ = ReadTemplate( xmlNode, "union", templateDirectory );
                    result.namespace_list_ = ReadTemplate( xmlNode, "namespace_list", templateDirectory );
                    result.namespace_ = ReadTemplate( xmlNode, "namespace", templateDirectory );
                    result.variable_list_ = ReadTemplate( xmlNode, "variable_list", templateDirectory );
                    result.typedef_list_ = ReadTemplate( xmlNode, "typedef_list", templateDirectory );
                    return result;
                }
            }
            throw std::exception( "Invalid template specification file." );

        }
    };


    class TemplateData 
    {
    protected:
        inja::json data_;
    public:
        virtual ~TemplateData( ) noexcept = default;

        const inja::json& data( ) const
        {
            return data_;
        }
    };

    class CompoundDefTemplateData : public TemplateData
    {
    public:
        CompoundDefTemplateData( const PathBuilder& pathBuilder, Doxygen::Structure::CompoundDef* compoundDef )
        {
            data_[ "page" ][ "title" ] = compoundDef->Title( );
            data_[ "page" ][ "url" ] = pathBuilder.FileRelativeUrlOf( compoundDef );
            data_[ "id" ] = compoundDef->Id( );
            data_[ "kind" ] = to_string( compoundDef->Kind( ) );
            data_[ "qualified_name" ] = compoundDef->QualifiedName( );
            data_[ "name" ] = compoundDef->Name( );

        }

    };




}

#endif
