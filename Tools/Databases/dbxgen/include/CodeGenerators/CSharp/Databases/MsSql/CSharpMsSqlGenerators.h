#pragma once
#ifndef CSHARPMSSQLGENERATORS_H_
#define CSHARPMSSQLGENERATORS_H_
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

namespace Harlinn::Tools::DbXGen::CodeGenerators::CSharp::Databases::MsSql
{
    class CSharpMsSqlSimpleDatabaseReadersGenerator : public CodeGenerator<CSharpMsSqlGenerator, CSharpMsSqlSimpleDatabaseReadersOptions>
    {
    public:
        using Base = CodeGenerator<CSharpMsSqlGenerator, CSharpMsSqlSimpleDatabaseReadersOptions>;

        inline CSharpMsSqlSimpleDatabaseReadersGenerator( const CSharpMsSqlGenerator& owner );

        void Run( );
    private:
        void CreateReader( const Metadata::ClassInfo& classInfo );
        void CreateQuery( const Metadata::ClassInfo& classInfo );
        void CreateFieldIds( const Metadata::ClassInfo& classInfo );
        void CreateAccessors( const Metadata::ClassInfo& classInfo );
        void CreateWriteColumns( const Metadata::ClassInfo& classInfo );
        void CreateGetDataObject( const Metadata::ClassInfo& classInfo );
    };

    class CSharpMsSqlComplexDatabaseReadersGenerator : public CodeGenerator<CSharpMsSqlGenerator, CSharpMsSqlComplexDatabaseReadersOptions>
    {
    public:
        using Base = CodeGenerator<CSharpMsSqlGenerator, CSharpMsSqlComplexDatabaseReadersOptions>;

        inline CSharpMsSqlComplexDatabaseReadersGenerator( const CSharpMsSqlGenerator& owner );

        void Run( );
    private:
        void CreateReader( const Metadata::ClassInfo& classInfo );
        void CreateQuery( const Metadata::ClassInfo& classInfo );
        void CreateFieldIds( const Metadata::ClassInfo& classInfo );
        void CreateAccessors( const Metadata::ClassInfo& classInfo );
        void CreateAccessor( const Metadata::MemberInfo& member, const WideString& propertyName, const WideString& fieldId );

        void CreateWriteTo( const Metadata::ClassInfo& classInfo );
        void CreateGetDataObject( const Metadata::ClassInfo& classInfo );

    };

    class CSharpMsSqlStoredProceduresGenerator : public CodeGenerator<CSharpMsSqlGenerator, CSharpMsSqlStoredProceduresOptions>
    {
    public:
        using Base = CodeGenerator<CSharpMsSqlGenerator, CSharpMsSqlStoredProceduresOptions>;

        inline CSharpMsSqlStoredProceduresGenerator( const CSharpMsSqlGenerator& owner );

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
        void AddInsertParameter( const Metadata::MemberInfo& memberInfo );
        void AddUpdateParameter( const Metadata::MemberInfo& memberInfo );
        void AddDeleteParameter( const Metadata::MemberInfo& memberInfo );

        void CreateInsertDataObject( );
        void CreateUpdateDataObject( );
        void CreateDeleteDataObject( );
        void CreateMergeDataObject( );
    };


    class CSharpMsSqlDataContextGenerator : public CodeGenerator<CSharpMsSqlGenerator, CSharpMsSqlDataContextOptions>
    {
        std::set<WideString> functions_;
    public:
        using Base = CodeGenerator<CSharpMsSqlGenerator, CSharpMsSqlDataContextOptions>;

        inline CSharpMsSqlDataContextGenerator( const CSharpMsSqlGenerator& owner );

        void Run( );
    private:
        void CreateMembers( const Metadata::ClassInfo& classInfo );
        void CreateGetById( const Metadata::ClassInfo& classInfo );
        void CreateGetAll( const Metadata::ClassInfo& classInfo );
        void CreateGetByIndex( const Metadata::ClassInfo& classInfo );
        void CreateGetByIndexDataReader( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexSql( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByNullableIndexReader( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByNullableIndexSql( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByNullableIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexAtDataReader( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexAtSql( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexAt( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexFromDataReader( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexFromSql( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexFrom( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexUntilDataReader( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexUntilSql( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexUntil( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexOverDataReader( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexOverSql( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexOver( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void AddParameter( const Metadata::MemberInfo& memberInfo );
        void AddParameter( const Metadata::MemberInfo& memberInfo, const WideString& argumentName, const WideString& sqlArgumentName );
    };

    class CSharpMsSqlUpdateNodesGenerator : public CodeGenerator<CSharpMsSqlGenerator, CSharpMsSqlUpdateNodesOptions>
    {
    public:
        using Base = CodeGenerator<CSharpMsSqlGenerator, CSharpMsSqlUpdateNodesOptions>;

        inline CSharpMsSqlUpdateNodesGenerator( const CSharpMsSqlGenerator& owner );

        void Run( );
    private:
        void CreateUpdateNode( const Metadata::ClassInfo& classInfo );
        void CreateCollectDependencies( const Metadata::ClassInfo& classInfo );
        void CreateInsert( const Metadata::ClassInfo& classInfo );
        void CreateInsert1( const Metadata::ClassInfo& classInfo );
        void CreateUpdate( const Metadata::ClassInfo& classInfo );
        void CreateUpdate1( const Metadata::ClassInfo& classInfo );
        void CreateUpdate2( const Metadata::ClassInfo& classInfo );
        void CreateDelete( const Metadata::ClassInfo& classInfo );
        void CreateFactory( );
        void CreateUpdateHandler( );
    };


    class CSharpMsSqlGenerator : public GeneratorContainer<CSharpDatabasesGenerator, CSharpMsSqlOptions>
    {
        CSharpMsSqlSimpleDatabaseReadersGenerator databaseReaders_;
        CSharpMsSqlComplexDatabaseReadersGenerator complexDatabaseReaders_;
        CSharpMsSqlStoredProceduresGenerator storedProcedures_;
        CSharpMsSqlDataContextGenerator dataContext_;
        CSharpMsSqlUpdateNodesGenerator updateNodes_;
    public:
        using Base = GeneratorContainer<CSharpDatabasesGenerator, CSharpMsSqlOptions>;

        inline CSharpMsSqlGenerator( const CSharpDatabasesGenerator& owner );

        void Run( )
        {
            databaseReaders_.Run( );
            complexDatabaseReaders_.Run( );
            storedProcedures_.Run( );
            dataContext_.Run( );
            updateNodes_.Run( );
        }

    };

    inline CSharpMsSqlSimpleDatabaseReadersGenerator::CSharpMsSqlSimpleDatabaseReadersGenerator( const CSharpMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).DatabaseReaders( ) )
    {
    }

    inline CSharpMsSqlComplexDatabaseReadersGenerator::CSharpMsSqlComplexDatabaseReadersGenerator( const CSharpMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).ComplexDatabaseReaders( ) )
    {
    }
    inline CSharpMsSqlStoredProceduresGenerator::CSharpMsSqlStoredProceduresGenerator( const CSharpMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).StoredProcedures( ) )
    {
    }

    inline CSharpMsSqlDataContextGenerator::CSharpMsSqlDataContextGenerator( const CSharpMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).DataContext( ) )
    {
    }

    inline CSharpMsSqlUpdateNodesGenerator::CSharpMsSqlUpdateNodesGenerator( const CSharpMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).UpdateNodes( ) )
    {
    }
}

#endif
