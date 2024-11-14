#pragma once
#ifndef FILELIST_H_
#define FILELIST_H_
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

#include <HCCDoxygen.h>
#include <HCCStringBuilder.h>

namespace Doxygen2Md
{
    using namespace Harlinn::Common::Core;

    class FileEntry
    {
        WideString qualifiedName_;
        WideString fileName_;
    public:
        FileEntry( ) = default;
        explicit FileEntry( const WideString& qualifiedName, const WideString& fileName )
            : qualifiedName_( qualifiedName ), fileName_( fileName )
        { }

        const WideString& QualifiedName() const { return qualifiedName_; }
        const WideString& FileName( ) const { return fileName_; }

    };

    class FileList : public std::map<WideString, std::unique_ptr<FileEntry>>
    {
        WideString fileName_;
        WideString outputDirectory_;
    public:
        FileList( ) = default;
        explicit FileList( const WideString& fileName );

        const WideString& FileName( ) const { return fileName_; }
        const WideString& OutputDirectory( ) const { return outputDirectory_; }

        static std::unique_ptr<FileList> LoadFromFile( const WideString& fileName );
        void SaveToFile( const WideString& fileName ) const;
        WideString ToWideString( ) const;
        AnsiString ToAnsiString( ) const;

    };
}

#endif
