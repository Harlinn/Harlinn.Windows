#pragma once
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
        AnsiString name_;
        AnsiString contents_;

    public:
        File( GenerateProject::Project* project, const AnsiString& name, const AnsiString& contents )
            : project_( project ), name_( name ), contents_( contents )
        {
        }


        virtual bool Update( )
        {
            return true;
        }


        AnsiString Directory( ) const
        {
            char drive[_MAX_DRIVE + 1];
            char directory[_MAX_PATH + 1];
            _splitpath_s( name_.c_str( ), drive, _MAX_DRIVE + 1, directory, _MAX_PATH + 1, nullptr, 0, nullptr, 0 );
            auto driveLength = LengthOf( drive );
            auto directoryLength = LengthOf( directory );
            if ( driveLength && directoryLength )
            {
                AnsiString result;
                result.reserve( driveLength + directoryLength );
                result.append( drive, driveLength );
                result.append( directory, directoryLength );

                return result;
            }
            else if ( directoryLength )
            {
                AnsiString result;
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
                return AnsiString( );
            }
        }

        AnsiString Filename( ) const
        {
            char name[_MAX_FNAME + 1];
            char ext[_MAX_EXT + 1];
            _splitpath_s( name_.c_str( ), nullptr, 0, nullptr, 0, name, _MAX_FNAME + 1, ext, _MAX_EXT + 1 );
            auto nameLength = LengthOf( name );
            auto extLength = LengthOf( ext );
            AnsiString result;
            result.append( name, nameLength );
            result.append( ext, extLength );
            return result;
        }

        AnsiString FilePath( ) const
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
        const AnsiString& Name( ) const
        {
            return name_;
        }
        const AnsiString& Contents( ) const
        {
            return contents_;
        }

        bool SetTagValue( const AnsiString& tagName, const AnsiString& newValue )
        {
            auto startTag = Format( "<{}>", tagName );
            auto endTag = Format( "</{}>", tagName );

            auto startOffset = contents_.find( startTag );
            if ( startOffset != AnsiString::npos )
            {
                auto valueOffset = startOffset + startTag.size( );
                auto endOffset = contents_.find( endTag, valueOffset );
                if ( endOffset != AnsiString::npos )
                {
                    auto valueLength = endOffset - valueOffset;
                    contents_.replace( valueOffset, valueLength, newValue );
                    return true;
                }
            }
            return false;
        }

        bool SetTagValue( const char* tagName, const AnsiString& newValue )
        {
            return SetTagValue( AnsiString( tagName ), newValue );
        }

        bool SetTagValue( const char* tagName, const char* newValue )
        {
            return SetTagValue( AnsiString( tagName ), AnsiString( newValue) );
        }


        bool Replace( const AnsiString& oldValue, const AnsiString& newValue )
        {
            auto startOffset = contents_.find( oldValue );
            if ( startOffset != AnsiString::npos )
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
        SourceFile( GenerateProject::Project* project, const AnsiString& name, const AnsiString& contents )
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
        ProjectFile( GenerateProject::Project* project, const AnsiString& name, const AnsiString& contents )
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
        ProjectFilterFile( GenerateProject::Project* project, const AnsiString& name, const AnsiString& contents )
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
        ProjectUserFile( GenerateProject::Project* project, const AnsiString& name, const AnsiString& contents )
            : Base( project, name, contents )
        {
        }
    };




}