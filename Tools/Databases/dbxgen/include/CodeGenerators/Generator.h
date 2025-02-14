#pragma once
#ifndef GENERATOR_H_
#define GENERATOR_H_
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

#include "GeneratorsBase.h"
#include "CodeGenerators/Databases/DatabasesGenerator.h"
#include "CodeGenerators/Cpp/CppGenerators.h"
#include "CodeGenerators/CSharp/CSharpGenerators.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators
{
    // ------------------------------------------------------------------------
    // Generator
    // ------------------------------------------------------------------------
    class Generator
    {
        const CodeGenerators::Options& options_;
        const Metadata::ModelInfo& model_;
        Databases::DatabasesGenerator databases_;
        Cpp::CppGenerator cpp_;
        Cpp::CppTestGenerator cppTest_;
        CSharp::CSharpGenerator csharp_;
    public:
        Generator( const CodeGenerators::Options& options, const Metadata::ModelInfo& model )
            : options_( options ), model_( model ), databases_( *this ), cpp_(*this), cppTest_(*this), csharp_(*this)
        { }

        const CodeGenerators::Options& Options( ) const
        {
            return options_;
        }

        const Metadata::ModelInfo& Model( ) const
        {
            return model_;
        }

        void Run( )
        {
            databases_.Run( );
            cpp_.Run( );
            cppTest_.Run( );
            csharp_.Run( );
        }
    };

    namespace Databases
    {
        inline DatabasesGenerator::DatabasesGenerator( const Generator& owner )
            : Base( owner, owner.Options( ).Databases( ) ), msSql_( *this )
        {
        }
    }

    namespace Cpp
    {
        inline CppGenerator::CppGenerator( const Generator& owner )
            : Base( owner, owner.Options( ).Cpp( ) ), data_( *this ), databases_( *this )
        {
        }
        inline CppTestGenerator::CppTestGenerator( const Generator& owner )
            : Base( owner, owner.Options( ).CppTest( ) ), data_( *this ), database_( *this )
        {
        }
    }

    namespace CSharp
    {
        inline CSharpGenerator::CSharpGenerator( const Generator& owner )
            : Base( owner, owner.Options( ).CSharp( ) ), data_( *this ), databases_( *this ), entities_( *this )
        {
        }
    }


}

#endif
