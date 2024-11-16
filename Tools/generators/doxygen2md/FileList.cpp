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

#include "FileList.h"
#include "HCCRapidXml.h"

namespace Doxygen2Md
{
    using namespace std::literals::string_view_literals;
    namespace
    {
        WideString DirectoryName( const WideString& outputDirectory, Doxygen::Structure::Namespace* nspace )
        {
            auto directory = IO::Path::Combine<WideString>( outputDirectory, nspace->Name( ) );
            return directory;
        }

        WideString FileNameBase( const WideString& memberName )
        {
            wchar_t previous;
            StringBuilder<wchar_t> sb;
            for ( const auto& c : memberName )
            {
                if ( IsAlnum( c ) || c == L'_' )
                {
                    sb.Append( c );
                    previous = c;
                }
                else if ( c == L'<' || c == L'>' || c == L':' )
                {
                    if ( previous != L'_' )
                    {
                        sb.Append( L'_' );
                        previous = L'_';
                    }
                }
            }
            return sb.ToString( );
        }

        WideString FileName( Doxygen::Structure::Member* member )
        {
            auto fileNameBase = FileNameBase( member->Name( ) );
            using MemberType = Doxygen::Structure::MemberType;
            auto memberType = member->MemberType( );
            switch ( memberType )
            {
                case MemberType::Class:
                {
                    return Format( L"Class{}.md", fileNameBase );
                }
                break;
                case MemberType::Interface:
                {
                    return Format( L"Interface{}.md", fileNameBase );
                }
                break;
                case MemberType::Struct:
                {
                    return Format( L"Struct{}.md", fileNameBase );
                }
                break;
                case MemberType::Union:
                {
                    return Format( L"Union{}.md", fileNameBase );
                }
                break;
                case MemberType::Namespace:
                {
                    return Format( L"Namespace{}.md", fileNameBase );
                }
                break;
            }
            return {};
        }

        WideString FileName( const WideString& outputDirectory, Doxygen::Structure::Member* member )
        {
            auto fileName = FileName( member );
            return IO::Path::Combine<WideString>( outputDirectory, fileName );
        }

        void Collect( const WideString& outputDirectory, Doxygen::Structure::Member* member, std::map<WideString, WideString>& idToFilenameMap )
        {
            using namespace std::literals::string_view_literals;
            using MemberType = Doxygen::Structure::MemberType;
            auto fileName = FileName( outputDirectory, member );
            std::wcout << fileName << std::endl;

            auto memberType = member->MemberType( );
            if ( memberType == MemberType::Namespace )
            {
                auto nspace = static_cast< Doxygen::Structure::Namespace* >( member );
                if ( nspace->Name( ).IsEmpty( ) || ( nspace->Language( ) == Doxygen::DoxLanguage::CSharp && nspace->Name( ) == L"global"sv ) )
                {
                    fileName = IO::Path::Combine( outputDirectory, L"GlobalNamespace" );
                }
                auto directory = DirectoryName( outputDirectory, nspace );

                const auto& members = nspace->Members( );

            }
        }
    }

    FileList::FileList( const WideString& fileName )
        : fileName_( fileName )
    {
        outputDirectory_ = IO::Path::RemoveTrailingDirectorySeparator( IO::Path::GetParentDirectory( fileName ) );
    }

    std::unique_ptr<FileList> FileList::LoadFromFile( const WideString& fileName )
    {
        auto fileList = std::make_unique<FileList>( fileName );
        const auto& outputDirectory = fileList->OutputDirectory( );
        if ( IO::File::Exist( fileName ) )
        {
            AnsiString xml;
            IO::File::ReadAndAppendAllTextTo( fileName, xml );

            if ( xml.size( ) )
            {
                RapidXml::XmlParser xmlParser;
                char* xmlText = xml.data( );
                xmlParser.Parse<RapidXml::ParsingFlags::NonDestructive>( xmlText );

                auto xmlDocument = xmlParser.Document( );

                auto xmlFileListNode = xmlDocument.FirstNode( "filelist"sv );
                if ( xmlFileListNode )
                {
                    auto xmlFileEntryNode = xmlFileListNode.FirstNode( );
                    if ( xmlFileEntryNode )
                    {
                        do
                        {
                            
                            if ( xmlFileEntryNode.NodeType() == RapidXml::NodeType::node_element )
                            {
                                auto xmlFileEntryNodeName = xmlFileEntryNode.Name( );
                                if ( xmlFileEntryNodeName == "fileentry"sv )
                                {
                                    auto qualifiedName = Html::Decode( xmlFileEntryNode.Read<WideString>( "qualifiedname" ) );
                                    auto fileName = Html::Decode( xmlFileEntryNode.Read<WideString>( "filename" ) );
                                    auto path = IO::Path::FullPath( IO::Path::Combine<WideString>( outputDirectory, fileName ) );
                                    auto fileEntry = std::make_unique<FileEntry>( qualifiedName, path );
                                    fileList->emplace( qualifiedName, std::move(fileEntry) );
                                }
                            }
                            xmlFileEntryNode = xmlFileEntryNode.NextSibling( );
                        } while ( xmlFileEntryNode );
                    }
                }
            }
        }
        return fileList;
    }
    void FileList::SaveToFile( const WideString& fileName ) const
    {
        auto text = ToAnsiString( );
        IO::File::WriteAllText( fileName, text );
    }

    WideString FileList::ToWideString( ) const
    {
        StringBuilder<wchar_t> sb;
        sb.AppendLine( L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>" );
        sb.AppendLine( L"<filelist>" );
        for ( const auto& entry : *this )
        {
            const auto& fileEntry = entry.second;

            auto qualifiedName = Html::Encode( fileEntry->QualifiedName() );
            auto fileName = Html::Encode( IO::Path::RelativePath(outputDirectory_, fileEntry->FileName() ));
            auto entity = Format( L"    <fileentry qualifiedname=\"{}\" filename=\"{}\"/>", qualifiedName, fileName );
            sb.AppendLine( entity );

        }
        sb.AppendLine( L"</filelist>" );
        return sb.ToString( );
    }

    AnsiString FileList::ToAnsiString( ) const
    {
        return AnsiString::From( ToWideString( ) );
    }

}