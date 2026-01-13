#pragma once
#ifndef CPPMSSQLGENERATORS_H_
#define CPPMSSQLGENERATORS_H_
/*
   Copyright 2024-2026 Espen Harlinn

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
#include "CodeGenerators/GeneratorsBase.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Cpp::Databases::MsSql
{
    class CppMsSqlSimpleDatabaseReadersGenerator : public CodeGenerator<CppMsSqlGenerator, CppMsSqlSimpleDatabaseReadersOptions>
    {
    public:
        using Base = CodeGenerator<CppMsSqlGenerator, CppMsSqlSimpleDatabaseReadersOptions>;
        CppMsSqlSimpleDatabaseReadersGenerator( const CppMsSqlGenerator& owner );

        void Run( );
    private:
        void CreateBaseClass( );
        void CreateColumnDataType( const Metadata::ClassInfo& classInfo );
        void CreateQuery( const Metadata::ClassInfo& classInfo );
        void CreateFieldIds( const Metadata::ClassInfo& classInfo );
        void CreateBindColumns( const Metadata::ClassInfo& classInfo );
        void CreateReadUnboundData( const Metadata::ClassInfo& classInfo );
        void CreateAccessor( const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member );
        void CreateSetter( const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member );
        void CreateWriteColumns( const Metadata::ClassInfo& classInfo );
        void CreateAssignTo( const Metadata::ClassInfo& classInfo );

    };

    class CppMsSqlSimpleDatabaseReadersSourceGenerator : public CodeGenerator<CppMsSqlGenerator, CppMsSqlSimpleDatabaseReadersSourceOptions>
    {
    public:
        using Base = CodeGenerator<CppMsSqlGenerator, CppMsSqlSimpleDatabaseReadersSourceOptions>;
        CppMsSqlSimpleDatabaseReadersSourceGenerator( const CppMsSqlGenerator& owner );

        void Run( );
    private:
        void CreateColumnDataType( const Metadata::ClassInfo& classInfo );
        void CreateQuery( const Metadata::ClassInfo& classInfo );

    };


    class CppMsSqlComplexDatabaseReadersGenerator : public CodeGenerator<CppMsSqlGenerator, CppMsSqlComplexDatabaseReadersOptions>
    {
    public:
        using Base = CodeGenerator<CppMsSqlGenerator, CppMsSqlComplexDatabaseReadersOptions>;
        CppMsSqlComplexDatabaseReadersGenerator( const CppMsSqlGenerator& owner );

        void Run( );
    private:
        void CreateColumnDataType( const Metadata::ClassInfo& classInfo );
        void CreateQuery( const Metadata::ClassInfo& classInfo );
        void CreateFieldIds( const Metadata::ClassInfo& classInfo );
        void CreateBindColumns( const Metadata::ClassInfo& classInfo );
        void CreateReadUnboundData( const Metadata::ClassInfo& classInfo );
        void CreateAccessors( const Metadata::ClassInfo& classInfo );

        void CreateWriteColumns( const Metadata::ClassInfo& classInfo );
    };

    class CppMsSqlComplexDatabaseReadersSourceGenerator : public CodeGenerator<CppMsSqlGenerator, CppMsSqlComplexDatabaseReadersSourceOptions>
    {
    public:
        using Base = CodeGenerator<CppMsSqlGenerator, CppMsSqlComplexDatabaseReadersSourceOptions>;
        CppMsSqlComplexDatabaseReadersSourceGenerator( const CppMsSqlGenerator& owner );

        void Run( );
    private:
        void CreateColumnDataType( const Metadata::ClassInfo& classInfo );
        void CreateQuery( const Metadata::ClassInfo& classInfo );

        void CreateBindColumns( const Metadata::ClassInfo& classInfo );
        void CreateReadUnboundData( const Metadata::ClassInfo& classInfo );
    };

    class CppMsSqlStoredProceduresGenerator : public CodeGenerator<CppMsSqlGenerator, CppMsSqlStoredProceduresOptions>
    {
    public:
        using Base = CodeGenerator<CppMsSqlGenerator, CppMsSqlStoredProceduresOptions>;
        CppMsSqlStoredProceduresGenerator( const CppMsSqlGenerator& owner );

        void Run( );
    private:
        void CreateInsert( const Metadata::ClassInfo& classInfo );
        void CreateInsert1( const Metadata::ClassInfo& classInfo );
        void CreateInsertObject( const Metadata::ClassInfo& classInfo );
        void CreateInsertObject1( const Metadata::ClassInfo& classInfo );

        void CreateUpdate( const Metadata::ClassInfo& classInfo );
        void CreateUpdate1( const Metadata::ClassInfo& classInfo );
        void CreateUpdate2( const Metadata::ClassInfo& classInfo );
        void CreateUpdateObject( const Metadata::ClassInfo& classInfo );
        void CreateUpdateObject1( const Metadata::ClassInfo& classInfo );
        void CreateUpdateObject2( const Metadata::ClassInfo& classInfo );
        void CreateDelete( const Metadata::ClassInfo& classInfo );
        void CreateDeleteObject( const Metadata::ClassInfo& classInfo );

        void CreateInsertDataObject( );
        void CreateUpdateDataObject( );
        void CreateDeleteDataObject( );
        void CreateMergeDataObject( );

    };

    class CppMsSqlStoredProceduresSourceGenerator : public CodeGenerator<CppMsSqlGenerator, CppMsSqlStoredProceduresSourceOptions>
    {
    public:
        using Base = CodeGenerator<CppMsSqlGenerator, CppMsSqlStoredProceduresSourceOptions>;
        CppMsSqlStoredProceduresSourceGenerator( const CppMsSqlGenerator& owner );

        void Run( );
    private:
        void CreateInsert( const Metadata::ClassInfo& classInfo );
        void CreateInsert1( const Metadata::ClassInfo& classInfo );
        void CreateInsertObject( const Metadata::ClassInfo& classInfo );
        void CreateInsertObject1( const Metadata::ClassInfo& classInfo );
        void CreateUpdate( const Metadata::ClassInfo& classInfo );
        void CreateUpdate1( const Metadata::ClassInfo& classInfo );
        void CreateUpdate2( const Metadata::ClassInfo& classInfo );
        void CreateUpdateObject( const Metadata::ClassInfo& classInfo );
        void CreateUpdateObject1( const Metadata::ClassInfo& classInfo );
        void CreateUpdateObject2( const Metadata::ClassInfo& classInfo );
        void CreateDelete( const Metadata::ClassInfo& classInfo );
        void CreateDeleteObject( const Metadata::ClassInfo& classInfo );

        void CreateInsertDataObject( );
        void CreateUpdateDataObject( );
        void CreateDeleteDataObject( );
        void CreateMergeDataObject( );
    };



    class CppMsSqlGenerator : public GeneratorContainer<CppDatabasesGenerator, CppMsSqlOptions>
    {
        CppMsSqlSimpleDatabaseReadersGenerator simpleDatabaseReaders_;
        CppMsSqlSimpleDatabaseReadersSourceGenerator simpleDatabaseReadersSource_;
        CppMsSqlComplexDatabaseReadersGenerator complexDatabaseReaders_;
        CppMsSqlComplexDatabaseReadersSourceGenerator complexDatabaseReadersSource_;
        CppMsSqlStoredProceduresGenerator storedProcedures_;
        CppMsSqlStoredProceduresSourceGenerator storedProceduresSource_;
    public:
        using Base = GeneratorContainer<CppDatabasesGenerator, CppMsSqlOptions>;
        CppMsSqlGenerator( const CppDatabasesGenerator& owner );

        void Run( )
        {
            simpleDatabaseReaders_.Run( );
            simpleDatabaseReadersSource_.Run( );
            complexDatabaseReaders_.Run( );
            complexDatabaseReadersSource_.Run( );
            storedProcedures_.Run( );
            storedProceduresSource_.Run( );
        }
    };

    inline CppMsSqlSimpleDatabaseReadersGenerator::CppMsSqlSimpleDatabaseReadersGenerator( const CppMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).SimpleDatabaseReaders( ) )
    {

    }

    inline CppMsSqlSimpleDatabaseReadersSourceGenerator::CppMsSqlSimpleDatabaseReadersSourceGenerator( const CppMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).SimpleDatabaseReadersSource( ) )
    {

    }

    inline CppMsSqlComplexDatabaseReadersGenerator::CppMsSqlComplexDatabaseReadersGenerator( const CppMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).ComplexDatabaseReaders( ) )
    {

    }

    inline CppMsSqlComplexDatabaseReadersSourceGenerator::CppMsSqlComplexDatabaseReadersSourceGenerator( const CppMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).ComplexDatabaseReadersSource( ) )
    {

    }

    inline CppMsSqlStoredProceduresGenerator::CppMsSqlStoredProceduresGenerator( const CppMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).StoredProcedures( ) )
    {

    }

    inline CppMsSqlStoredProceduresSourceGenerator::CppMsSqlStoredProceduresSourceGenerator( const CppMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).StoredProceduresSource( ) )
    {

    }
}

#endif
