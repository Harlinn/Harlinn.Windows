#pragma once
#ifndef CPPMARKDOWN_H_
#define CPPMARKDOWN_H_

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

#include "MarkdownBase.h"

namespace Doxygen2Md::Cpp
{

    class CppTypeManager;


    WideString MarkdownOutputFile( const CppTypeManager& typeManager, const Doxygen::CompoundDefTypePtr& compoundDefType );

    class CppMarkdownWriter : public std::enable_shared_from_this<CppMarkdownWriter>, public MarkdownStream
    {

    public:
        using Base = std::enable_shared_from_this<CppMarkdownWriter>;
        CppMarkdownWriter( CppTypeManager& typeManager, const WideString& filename )
            : MarkdownStream( filename )
        {

        }
    };

    class CppCompoundDefType : public CppMarkdownWriter
    {
    public:
        using Base = CppMarkdownWriter;

    };
    using CppCompoundDefTypePtr = std::shared_ptr<CppCompoundDefType>;



    class CppTypeManager
    {
        std::unordered_map< WideStringView, CppCompoundDefTypePtr > types_;
        const Doxygen::DocumentCollection& documentCollection_;
        WideString outputDirectory_;
    public:
        CppTypeManager( const Doxygen::DocumentCollection& documentCollection, const WideString& outputDirectory)
            : documentCollection_( documentCollection ), outputDirectory_( outputDirectory )
        { }

        const std::unordered_map< WideStringView, CppCompoundDefTypePtr >& Types( ) const { return types_; }
        const Doxygen::DocumentCollection& DocumentCollection( ) const { return documentCollection_; }
        const WideString& OutputDirectory( ) const { return outputDirectory_; }

    };



}

#endif
