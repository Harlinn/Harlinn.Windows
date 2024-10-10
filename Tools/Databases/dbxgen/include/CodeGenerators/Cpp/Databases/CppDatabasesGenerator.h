#pragma once
#ifndef CPPDATABASESGENERATOR_H_
#define CPPDATABASESGENERATOR_H_

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
#include "CodeGenerators/Cpp/Databases/MsSql/CppMsSqlGenerators.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Cpp::Databases
{
    class CppDatabasesGenerator : public GeneratorContainer<CppGenerator, CppDatabasesOptions>
    {
        MsSql::CppMsSqlGenerator msSql_;
    public:
        using Base = GeneratorContainer<CppGenerator, CppDatabasesOptions>;
        CppDatabasesGenerator( const CppGenerator& owner );

        void Run( )
        {
            msSql_.Run( );
        }

    };

    namespace MsSql
    {
        inline CppMsSqlGenerator::CppMsSqlGenerator( const CppDatabasesGenerator& owner )
            : Base( owner, owner.Options( ).MsSql( ) ), simpleDatabaseReaders_( *this ), simpleDatabaseReadersSource_( *this ), complexDatabaseReaders_( *this ), complexDatabaseReadersSource_( *this ), storedProcedures_( *this ), storedProceduresSource_( *this )
        {
        }
    }
}

#endif
