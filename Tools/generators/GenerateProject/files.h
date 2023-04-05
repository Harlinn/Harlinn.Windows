#pragma once

#include <string>
#include <HCCIO.h>
#include <HCCString.h>
#include <HCCGuid.h>

namespace GenerateProject
{
    using namespace Harlinn::Common::Core;
    class Project;
    class File
    {
        GenerateProject::Project* project_;
        std::string name_;
        std::string contents_;

    public:
        File( GenerateProject::Project* project, const std::string& name, const std::string& contents )
            : project_( project ), name_( name ), contents_( contents )
        {
        }


        virtual bool Update( )
        {
            return true;
        }


        std::string Directory( ) const
        {
            char drive[_MAX_DRIVE + 1];
            char directory[_MAX_PATH + 1];
            _splitpath_s( name_.c_str( ), drive, _MAX_DRIVE + 1, directory, _MAX_PATH + 1, nullptr, 0, nullptr, 0 );
            auto driveLength = LengthOf( drive );
            auto directoryLength = LengthOf( directory );
            if ( driveLength && directoryLength )
            {
                std::string result;
                result.reserve( driveLength + directoryLength );
                result.append( drive, driveLength );
                result.append( directory, directoryLength );

                return result;
            }
            else if ( directoryLength )
            {
                std::string result;
                if ( directory[0] != '\\' && directory[0] != '/' )
                {
                    result.append( ".\\" );
                    result.append( directory, directoryLength - 1 );
                }
                else
                {
                    result.append( directory, directoryLength );
                }
                return result;
            }
            else
            {
                return std::string( );
            }
        }

        std::string Filename( ) const
        {
            char name[_MAX_FNAME + 1];
            char ext[_MAX_EXT + 1];
            _splitpath_s( name_.c_str( ), nullptr, 0, nullptr, 0, name, _MAX_FNAME + 1, ext, _MAX_EXT + 1 );
            auto nameLength = LengthOf( name );
            auto extLength = LengthOf( ext );
            std::string result;
            result.append( name, nameLength );
            result.append( ext, extLength );
            return result;
        }

        std::string FilePath( ) const
        {
            auto result = Directory( );
            if ( result.ends_with( '\\' ) == false && result.ends_with( '/' ) == false )
            {
                result += '\\';
            }
            result += Filename( );
            return result;
        }


        void Save( ) const
        {
            auto directory = IO::Path::FullPath( Directory( ) );
            if ( IO::Directory::Exist( directory ) == false )
            {
                IO::Directory::Create( directory );
            }
            auto filePath = FilePath( );
            IO::File::WriteAllText( filePath, contents_ );
        }



        GenerateProject::Project* Project( ) const
        {
            return project_;
        }
        const std::string& Name( ) const
        {
            return name_;
        }
        const std::string& Contents( ) const
        {
            return contents_;
        }

        bool SetTagValue( const std::string& tagName, const std::string& newValue )
        {
            auto startTag = Format( "<%s>", tagName.c_str( ) );
            auto endTag = Format( "</%s>", tagName.c_str( ) );

            auto startOffset = contents_.find( startTag );
            if ( startOffset != std::string::npos )
            {
                auto valueOffset = startOffset + startTag.size( );
                auto endOffset = contents_.find( endTag, valueOffset );
                if ( endOffset != std::string::npos )
                {
                    auto valueLength = endOffset - valueOffset;
                    contents_.replace( valueOffset, valueLength, newValue );
                    return true;
                }
            }
            return false;
        }

        bool Replace( const std::string& oldValue, const std::string& newValue )
        {
            auto startOffset = contents_.find( oldValue );
            if ( startOffset != std::string::npos )
            {
                auto valueLength = oldValue.size();
                contents_.replace( startOffset, valueLength, newValue );
                return true;
            }
            return false;
        }


    };


    class SourceFile : public File
    {
    public:
        using Base = File;
    public:
        SourceFile( GenerateProject::Project* project, const std::string& name, const std::string& contents )
            : Base( project, name, contents )
        {
        }

    };





    class ProjectFile : public File
    {
    public:
        using Base = File;
    private:
    public:
        ProjectFile( GenerateProject::Project* project, const std::string& name, const std::string& contents )
            : Base( project, name, contents )
        {
        }

        virtual bool Update( ) override;


    };

    class ProjectFilterFile : public File
    {
    public:
        using Base = File;
    private:
    public:
        ProjectFilterFile( GenerateProject::Project* project, const std::string& name, const std::string& contents )
            : Base( project, name, contents )
        {
        }

        virtual bool Update( ) override;
    };

    class ProjectUserFile : public File
    {
    public:
        using Base = File;
    private:
    public:
        ProjectUserFile( GenerateProject::Project* project, const std::string& name, const std::string& contents )
            : Base( project, name, contents )
        {
        }
    };




}