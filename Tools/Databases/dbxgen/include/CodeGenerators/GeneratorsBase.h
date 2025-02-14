#pragma once
#ifndef GENERATORSBASE_H_
#define GENERATORSBASE_H_
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

#include "Metadata/ModelInfo.h"
#include "Options.h"
#include "CodeStream.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators
{
    class Generator;
    namespace Databases
    {
        class DatabasesGenerator;
        namespace MsSql
        {
            class MsSqlGenerator;
        }
    }
    namespace Cpp
    {
        class CppGenerator;
        class CppDataGenerator;
        namespace Databases
        {
            class CppDatabasesGenerator;
            namespace MsSql
            {
                class CppMsSqlGenerator;
            }
        }
    }
    namespace CSharp
    {
        class CSharpDataGenerator;
        class CSharpGenerator;
        namespace Databases
        {
            class CSharpDatabasesGenerator;
            namespace MsSql
            {
                class CSharpMsSqlGenerator;
            }
        }
    }

    template<typename OwnerT, typename OptionsT>
    class GeneratorContainer
    {
    public:
        using OwnerType = OwnerT;
        using OptionsType = OptionsT;
    private:
        const OwnerType& owner_;
        const OptionsType& options_;
    public:
        GeneratorContainer( const OwnerType& owner, const OptionsType& options )
            : owner_( owner ), options_( options )
        {
        }

        const OwnerType& Owner( ) const
        {
            return owner_;
        }
        const OptionsType& Options( ) const
        {
            return options_;
        }

        const Metadata::ModelInfo& Model( ) const
        {
            return Owner( ).Model( );
        }

    };

    template<typename OwnerT, typename OptionsT>
    class CodeGenerator : protected CodeStream
    {
    public:
        using Base = CodeStream;
        using OwnerType = OwnerT;
        using OptionsType = OptionsT;
    private:
        const OwnerType& owner_;
        const OptionsType& options_;
    public:
        CodeGenerator( const OwnerType& owner, const OptionsType& options )
            : Base( options.Filename( ) ), owner_( owner ), options_( options )
        {
        }

        const OwnerType& Owner( ) const
        {
            return owner_;
        }
        const OptionsType& Options( ) const
        {
            return options_;
        }

        const Metadata::ModelInfo& Model( ) const
        {
            return Owner( ).Model( );
        }

    };
}
#endif
