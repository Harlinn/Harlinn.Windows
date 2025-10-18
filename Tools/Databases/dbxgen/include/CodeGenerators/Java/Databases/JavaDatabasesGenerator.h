#pragma once
#ifndef JAVAPDATABASESGENERATOR_H_
#define JAVADATABASESGENERATOR_H_
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
#include "CodeGenerators/Java/Databases/MsSql/JavaMsSqlGenerators.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java::Databases
{
    class JavaDatabasesGenerator : public GeneratorContainer<JavaGenerator, JavaDatabasesOptions>
    {
        MsSql::JavaMsSqlGenerator msSql_;
    public:
        using Base = GeneratorContainer<JavaGenerator, JavaDatabasesOptions>;

        inline JavaDatabasesGenerator( const JavaGenerator& owner );

        void Run( )
        {
            msSql_.Run( );
        }
    };

    namespace MsSql
    {
        inline JavaMsSqlGenerator::JavaMsSqlGenerator( const JavaDatabasesGenerator& owner )
            : Base( owner, owner.Options( ).MsSql( ) ), readers_( *this ), storedProcedures_( *this ) /*, dataContext_( *this ), updateNodes_( *this )*/, testDataObjectFactory_( *this )
        { }
    }
}

#endif

