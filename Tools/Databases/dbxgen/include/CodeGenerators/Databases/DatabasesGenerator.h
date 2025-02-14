#pragma once
#ifndef DATABASESGENERATOR_H_
#define DATABASESGENERATOR_H_
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
#include "CodeGenerators/Databases/MsSql/MsSqlGenerators.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases
{
    class DatabasesGenerator : public GeneratorContainer<Generator, DatabasesOptions>
    {
        MsSql::MsSqlGenerator msSql_;
    public:
        using Base = GeneratorContainer<Generator, DatabasesOptions>;
        DatabasesGenerator( const Generator& owner );

        void Run( )
        {
            msSql_.Run( );
        }
    };

    namespace MsSql
    {
        inline MsSqlGenerator::MsSqlGenerator( DatabasesGenerator& owner )
            : Base( owner, owner.Options( ).MsSql( ) ),
            createTables_( *this ),
            createViews_( *this ),
            createInsertProcedures_( *this ),
            createUpdateProcedures_( *this ),
            createDeleteProcedures_( *this )
        {
        }
    }
}

#endif
