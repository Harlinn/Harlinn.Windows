#pragma once
#ifndef MSSQLGENERATORS_H_
#define MSSQLGENERATORS_H_
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
#include "CodeGenerators/GeneratorsBase.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql
{
    class MsSqlCreateTablesGenerator : public CodeGenerator<MsSqlGenerator, MsSqlCreateTablesOptions>
    {
    public:
        using Base = CodeGenerator<MsSqlGenerator, MsSqlCreateTablesOptions>;
        MsSqlCreateTablesGenerator( const MsSqlGenerator& owner );

        void Run( );
    private:
        static WideString GetColumnName( const Metadata::MemberInfo& member );
        static WideString GetColumnType( const Metadata::MemberInfo& member );
        static WideString GetColumnNullable( const Metadata::MemberInfo& member );
        static WideString GetTableName( const Metadata::ClassInfo& classInfo );
        static WideString GetIndexName( const Metadata::IndexInfo& indexInfo );
        static WideString GetColumnNames( const Metadata::IndexInfo& indexInfo );

        void WriteTableColumn( const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member );
        void WriteTableIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& index );
        void WriteTable( const Metadata::ClassInfo& classInfo );
        void WriteForeignKeys( const Metadata::ClassInfo& classInfo );
        void WriteForeignKey( const Metadata::ClassInfo& classInfo, const Metadata::ReferenceMemberInfo& reference );
        void WriteEntityTypesTable( );
    };



    class MsSqlCreateViewsGenerator : public CodeGenerator<MsSqlGenerator, MsSqlCreateViewsOptions>
    {
    public:
        using Base = CodeGenerator<MsSqlGenerator, MsSqlCreateViewsOptions>;
        MsSqlCreateViewsGenerator( const MsSqlGenerator& owner );

        void Run( );
    private:
        static WideString GetFieldNameForSelect( const Metadata::MemberInfo& memberInfo );
        void CreateTopLevelView( const Metadata::ClassInfo& classInfo );
        void CreateView( const Metadata::ClassInfo& classInfo );
    };

    class MsSqlCreateInsertProceduresGenerator : public CodeGenerator<MsSqlGenerator, MsSqlCreateInsertProceduresOptions>
    {
    public:
        using Base = CodeGenerator<MsSqlGenerator, MsSqlCreateInsertProceduresOptions>;
        MsSqlCreateInsertProceduresGenerator( const MsSqlGenerator& owner );

        void Run( );
    private:
        static WideString GetProcedureParameters( const Metadata::ClassInfo& classInfo );
        static WideString GetProcedureParameters( const Metadata::ClassInfo& classInfo, const std::vector<std::shared_ptr<Metadata::MemberInfo>>& persistentMembers );
        static WideString GetInsertStatement( const Metadata::ClassInfo& classInfo );
        static WideString GetInsertStatement( const Metadata::ClassInfo& classInfo, const std::vector<std::shared_ptr<Metadata::MemberInfo>>& ownPersistentMembers );
        static WideString GetInsertProcedure( const Metadata::ClassInfo& classInfo );
        static WideString GetInsertProcedure1( const Metadata::ClassInfo& classInfo );
        static WideString GetInsertTrigger( const Metadata::ClassInfo& classInfo );
        void CreateInsertProcedure( const Metadata::ClassInfo& classInfo );
        void CreateInsertTrigger( const Metadata::ClassInfo& classInfo );

        void CreateInsertProcedure1( const Metadata::ClassInfo& classInfo );

    };


    class MsSqlCreateUpdateProceduresGenerator : public CodeGenerator<MsSqlGenerator, MsSqlCreateUpdateProceduresOptions>
    {
    public:
        using Base = CodeGenerator<MsSqlGenerator, MsSqlCreateUpdateProceduresOptions>;
        MsSqlCreateUpdateProceduresGenerator( const MsSqlGenerator& owner );

        void Run( );
    private:
        static WideString GetProcedureParameters( const Metadata::ClassInfo& classInfo );
        static WideString GetTopLevelUpdateStatement( const Metadata::ClassInfo& classInfo );
        static WideString GetUpdateStatement( const Metadata::ClassInfo& classInfo );
        void CreateUpdateStatement( const Metadata::ClassInfo& classInfo );

        static WideString GetProcedureParameters1( const Metadata::ClassInfo& classInfo );
        static WideString GetTopLevelUpdateStatement1( const Metadata::ClassInfo& classInfo );
        static WideString GetUpdateStatement1( const Metadata::ClassInfo& classInfo );
        void CreateUpdateStatement1( const Metadata::ClassInfo& classInfo );

        static WideString GetProcedureParameters2( const Metadata::ClassInfo& classInfo );
        static WideString GetTopLevelUpdateStatement2( const Metadata::ClassInfo& classInfo );
        static WideString GetUpdateStatement2( const Metadata::ClassInfo& classInfo );
        void CreateUpdateStatement2( const Metadata::ClassInfo& classInfo );


    };

    class MsSqlCreateDeleteProceduresGenerator : public CodeGenerator<MsSqlGenerator, MsSqlCreateDeleteProceduresOptions>
    {
    public:
        using Base = CodeGenerator<MsSqlGenerator, MsSqlCreateDeleteProceduresOptions>;
        MsSqlCreateDeleteProceduresGenerator( const MsSqlGenerator& owner );

        void Run( );
    private:
        static WideString GetDeleteStatement( const Metadata::ClassInfo& classInfo );
        void CreateDeleteProcedure( const Metadata::ClassInfo& classInfo );
    };






    class MsSqlGenerator : public GeneratorContainer<DatabasesGenerator, MsSqlOptions>
    {
        MsSqlCreateTablesGenerator createTables_;
        MsSqlCreateViewsGenerator createViews_;
        MsSqlCreateInsertProceduresGenerator createInsertProcedures_;
        MsSqlCreateUpdateProceduresGenerator createUpdateProcedures_;
        MsSqlCreateDeleteProceduresGenerator createDeleteProcedures_;
    public:
        using Base = GeneratorContainer<DatabasesGenerator, MsSqlOptions>;
        MsSqlGenerator( DatabasesGenerator& owner );

        void Run( )
        {
            createTables_.Run( );
            createViews_.Run( );
            createInsertProcedures_.Run( );
            createUpdateProcedures_.Run( );
            createDeleteProcedures_.Run( );
        }

    };
}

#endif
