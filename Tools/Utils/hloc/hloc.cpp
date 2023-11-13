// hloc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <HCCIO.h>

using namespace Harlinn::Common::Core;


class FileProcessor
{

};


class Options
{
    bool recursive_;

};


class Language : public std::shared_ptr<Language>
{
    WideString name_;
    std::vector<WideString> extensions_;
    size_t numberOfFiles_ = 0;
    size_t numberOfLines_ = 0;
    size_t numberOfBytes_ = 0;
    size_t numberOfLinesWithContent_ = 0;
public:
    Language(const WideString& name )
        : name_( name )
    { }

    void AddExtension( const WideString& extension )
    {
        extensions_.emplace_back( extension );
    }

    WideString CombineExtensions( ) const
    {
        
    }

    

};

class Languages : public std::vector< std::shared_ptr<Language> >
{
public:
    Languages()
    { }

    void Initialize( )
    {
        auto cpp = std::make_shared<Language>( L"C/C++" );
        emplace_back( cpp );
             
        cpp->AddExtension( L"*.cpp" );
        cpp->AddExtension( L"*.cc" );
        cpp->AddExtension( L"*.c" );
        cpp->AddExtension( L"*.cxx" );
        cpp->AddExtension( L"*.hpp" );
        cpp->AddExtension( L"*.hh" );
        cpp->AddExtension( L"*.h" );
        cpp->AddExtension( L"*.hxx" );
        cpp->AddExtension( L"*.inl" );
    }

    void Process( const WideString& fileName )
    {

    }


};


void ProcessDirectory( const std::shared_ptr<Languages>& languages, const WideString& directory )
{
    IO::FileSystemEntries<WideString> fileSystemEntries( directory, L"*" );
    while ( fileSystemEntries.Read( ) )
    {
        auto fullPath = fileSystemEntries.FullPath( );
        if ( fileSystemEntries.IsDirectory( ) )
        {
            ProcessDirectory( languages, fullPath );
        }
        else
        {

        }
    }
}




int main()
{
    
}

