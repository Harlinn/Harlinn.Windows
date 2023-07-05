#pragma once
#include "options.h"
#include "files.h"

namespace GenerateProject
{
    class Project
    {
    private:
        Options options_;
        std::unique_ptr<ProjectFile> projectFile_;
        std::unique_ptr<ProjectFilterFile> projectFilterFile_;
        std::unique_ptr<ProjectUserFile> projectUserFile_;
        AnsiString templateMainSourceFileName_;
        AnsiString mainSourceFileName_;
        bool renamedMainSourceFile_ = false;
        std::vector< std::unique_ptr<SourceFile> > sourceFiles_;
    public:
        Project( int argc, char* argv[] )
            : options_( argc, argv )
        {
        }

        const AnsiString GetTemplateMainSourceFileName( ) const
        {
            char name[_MAX_FNAME + 1];
            char ext[_MAX_EXT + 1];
            _splitpath_s( templateMainSourceFileName_.c_str( ), nullptr, 0, nullptr, 0, name, _MAX_FNAME + 1, ext, _MAX_EXT + 1 );
            AnsiString result;
            auto nameLength = LengthOf( name );
            auto extLength = LengthOf( ext );
            result.reserve( nameLength + extLength );
            result.append( name, nameLength );
            result.append( ext, extLength );

            return result;
        }
        const AnsiString GetMainSourceFileName( ) const
        {
            char name[_MAX_FNAME + 1];
            char ext[_MAX_EXT + 1];
            _splitpath_s( mainSourceFileName_.c_str( ), nullptr, 0, nullptr, 0, name, _MAX_FNAME + 1, ext, _MAX_EXT + 1 );
            AnsiString result;
            auto nameLength = LengthOf( name );
            auto extLength = LengthOf( ext );
            result.reserve( nameLength + extLength );
            result.append( name, nameLength );
            result.append( ext, extLength );

            return result;

        }
        bool RenamedMainSourceFile( ) const
        {
            return renamedMainSourceFile_;
        }


        AnsiString TemplateDirectory( ) const
        {
            auto result = options_.TemplateName( );
            if ( result.ends_with( '\\' ) || result.ends_with( '/' ) )
            {
                result.resize( result.size( ) - 1 );
            }
            return result;
        }

        AnsiString ProjectDirectory( ) const
        {
            auto result = options_.ProjectName( );
            if ( result.ends_with( '\\' ) || result.ends_with( '/' ) )
            {
                result.resize( result.size( ) - 1 );
            }
            return result;
        }

        AnsiString TemplateName( ) const
        {
            auto templateDirectory = TemplateDirectory( );
            char name[_MAX_FNAME + 1];
            _splitpath_s( templateDirectory.c_str( ), nullptr, 0, nullptr, 0, name, _MAX_FNAME + 1, nullptr, 0 );
            auto nameLength = LengthOf( name );
            if ( nameLength )
            {
                return AnsiString( name, nameLength );
            }
            else 
            {
                return AnsiString( );
            }
        }

        AnsiString ProjectName( ) const
        {
            auto projectDirectory = ProjectDirectory( );
            char name[_MAX_FNAME + 1];
            _splitpath_s( projectDirectory.c_str( ), nullptr, 0, nullptr, 0, name, _MAX_FNAME + 1, nullptr, 0 );
            auto nameLength = LengthOf( name );
            if ( nameLength )
            {
                return AnsiString( name, nameLength );
            }
            else
            {
                return AnsiString( );
            }
        }


        bool IsTemplateNameValid( ) const
        {
            auto templateName = TemplateName( );
            return templateName.empty( ) == false;
        }


        AnsiString TemplateProjectFileName( ) const
        {
            return TemplateDirectory( ) + '\\' + TemplateName( ) + ".vcxproj";
        }

        AnsiString TemplateProjectFilterFileName( ) const
        {
            return TemplateDirectory( ) + '\\' + TemplateName( ) + ".vcxproj.filters";
        }

        AnsiString TemplateProjectUserFileName( ) const
        {
            return TemplateDirectory( ) + '\\' + TemplateName( ) + ".vcxproj.user";
        }


        AnsiString TemplateMainSourceFileName( ) const
        {
            std::vector<AnsiString> extensions{ {".cpp"},{".cxx"},{".cc"} };
            std::vector<AnsiString> baseNames{ TemplateName( ), {"main"}};
            auto templateDirectory = TemplateDirectory( );
            for ( const auto& baseName : baseNames )
            {
                for ( const auto& extension : extensions )
                {
                    auto fileName = templateDirectory + '\\' + baseName + extension;
                    if ( IO::File::Exist( fileName ) )
                    {
                        return fileName;
                    }
                }
            }
            return AnsiString( );
        }

        AnsiString ProjectFileName( ) const
        {
            return ProjectDirectory( ) + '\\' + ProjectName( ) + ".vcxproj";
        }

        AnsiString ProjectFilterFileName( ) const
        {
            return ProjectDirectory( ) + '\\' + ProjectName( ) + ".vcxproj.filters";
        }

        AnsiString ProjectUserFileName( ) const
        {
            return ProjectDirectory( ) + '\\' + ProjectName( ) + ".vcxproj.user";
        }



        bool TemplateDirectoryExist( ) const
        {
            const auto& templateDirectory = options_.TemplateName( );
            return templateDirectory.empty() == false && IO::Directory::Exist( templateDirectory );
        }

        bool TemplateProjectFileExist( ) const
        {
            auto templateProjectFileName = TemplateProjectFileName( );
            return IO::File::Exist( templateProjectFileName );
        }

        bool TemplateProjectFilterFileExist( ) const
        {
            auto templateProjectFilterFileName = TemplateProjectFilterFileName( );
            return IO::File::Exist( templateProjectFilterFileName );
        }

        bool TemplateProjectUserFileExist( ) const
        {
            auto templateProjectUserFileName = TemplateProjectUserFileName( );
            return IO::File::Exist( templateProjectUserFileName );
        }

        bool TemplateFilesExist( ) const
        {
            return TemplateProjectFileExist( ) &&
                TemplateProjectFilterFileExist( ) &&
                TemplateProjectUserFileExist( );

        }

        bool IsValid( ) const
        {
            if ( options_.IsValid( ) )
            {
                if ( IsTemplateNameValid( ) )
                {
                    if ( TemplateDirectoryExist( ) )
                    {
                        if ( TemplateFilesExist( ) )
                        {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        

        void Process( )
        {
            if ( IsValid( ) )
            {
                if ( Load( ) )
                {
                    Update( );
                    Save( );
                }
            }
        }
    private:
        template<typename T>
        std::unique_ptr<T> LoadFile( const AnsiString& templateFilename, const AnsiString& filename )
        {
            auto contents = IO::File::ReadAllText( templateFilename );
            auto file = std::make_unique<T>(this, filename, contents );
            return file;
        }

        void LoadTemplateProjectFile( );
        void LoadTemplateProjectFilterFile( );
        void LoadTemplateProjectUserFile( );
        bool LoadTemplateMainSourceFile( );

        bool Load( );
        void Update( );
        void Save( );
    };


    inline void Project::LoadTemplateProjectFile( )
    {
        auto templateFilename = TemplateProjectFileName( );
        auto fileName = ProjectFileName( );
        projectFile_ = LoadFile<ProjectFile>( templateFilename, fileName );
    }
    inline void Project::LoadTemplateProjectFilterFile( )
    {
        auto templateFilename = TemplateProjectFilterFileName( );
        auto fileName = ProjectFilterFileName( );
        projectFilterFile_ = LoadFile<ProjectFilterFile>( templateFilename, fileName );
    }
    inline void Project::LoadTemplateProjectUserFile( )
    {
        auto templateFilename = TemplateProjectUserFileName( );
        auto fileName = ProjectUserFileName( );
        projectUserFile_ = LoadFile<ProjectUserFile>( templateFilename, fileName );
    }
    inline bool Project::LoadTemplateMainSourceFile( )
    {
        auto templateMainSourceFileName = TemplateMainSourceFileName( );
        if ( templateMainSourceFileName.empty() == false && IO::File::Exist( templateMainSourceFileName ) )
        {
            char name[_MAX_FNAME + 1];
            char ext[_MAX_EXT + 1];
            _splitpath_s( templateMainSourceFileName.c_str( ), nullptr, 0, nullptr, 0, name, _MAX_FNAME + 1, ext, _MAX_EXT + 1 );
            if ( name[0] && ext[0] )
            {
                AnsiString fileName;
                auto templateName = TemplateName( );
                if ( templateName == name )
                {
                    fileName = ProjectDirectory( ) + '\\' + ProjectName() + ext;
                    renamedMainSourceFile_ = true;
                }
                else
                {
                    fileName = ProjectDirectory( ) + '\\' + name + ext;
                }
                auto file = LoadFile<SourceFile>( templateMainSourceFileName, fileName );
                templateMainSourceFileName_ = templateMainSourceFileName;
                mainSourceFileName_ = fileName;
                sourceFiles_.emplace_back( std::move( file ) );
                return true;
            }
        }
        return false;
    }


    inline bool Project::Load( )
    {
        LoadTemplateProjectFile( );
        LoadTemplateProjectFilterFile( );
        LoadTemplateProjectUserFile( );
        if ( LoadTemplateMainSourceFile( ) )
        {
            return true;
        }
        return false;
    }
    inline void Project::Update( )
    {
        projectFile_->Update( );
        projectFilterFile_->Update( );
        projectUserFile_->Update( );
        for ( auto& file : sourceFiles_ )
        {
            file->Update( );
        }
    }
    inline void Project::Save( )
    {
        projectFile_->Save( );
        projectFilterFile_->Save( );
        projectUserFile_->Save( );
        for ( auto& file : sourceFiles_ )
        {
            file->Save( );
        }
    }

    inline bool ProjectFile::Update( )
    {
        auto result = Base::Update( );
        if ( result )
        {
            auto projectGuid = ToLower( Guid::New( ).ToAnsiString( ) );
            SetTagValue( "ProjectGuid", projectGuid );

            auto rootNamespace = ToLower( Strip( Project( )->ProjectName( ), []( auto c ) { return IsAlpha( c ) == false; } ) );
            SetTagValue( "RootNamespace", rootNamespace );

            if ( Project( )->RenamedMainSourceFile( ) )
            {
                Replace( Project( )->GetTemplateMainSourceFileName(), Project( )->GetMainSourceFileName() );
            }

        }
        return result;
    }

    inline bool ProjectFilterFile::Update( )
    {
        auto result = Base::Update( );
        if ( result )
        {
            if ( Project( )->RenamedMainSourceFile( ) )
            {
                Replace( Project( )->GetTemplateMainSourceFileName( ), Project( )->GetMainSourceFileName( ) );
            }
        }
        return result;
    }



}