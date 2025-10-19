#pragma once
#ifndef JAVAMSSQLGENERATORS_H_
#define JAVAMSSQLGENERATORS_H_
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
#include "CodeGenerators/GeneratorsBase.h"
#include "CodeGenerators/Java/JavaHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java::Databases::MsSql
{
    class JavaMsSqlSimpleReadersGenerator;
    class JavaMsSqlComplexReadersGenerator;

    class JavaMsSqlSimpleDatabaseReaderGenerator : public CodeGenerator<JavaMsSqlSimpleReadersGenerator, JavaMsSqlSimpleDatabaseReaderOptions>
    {
        const Metadata::ClassInfo& classInfo_;
    public:
        using Base = CodeGenerator<JavaMsSqlSimpleReadersGenerator, JavaMsSqlSimpleDatabaseReaderOptions>;

        inline JavaMsSqlSimpleDatabaseReaderGenerator( const JavaMsSqlSimpleReadersGenerator& owner, const Metadata::ClassInfo& classInfo );

        void Run( );
    private:
        void CreateReader( const Metadata::ClassInfo& classInfo );
        void CreateQuery( const Metadata::ClassInfo& classInfo );
        void CreateFieldIds( const Metadata::ClassInfo& classInfo );
        void CreateAccessors( const Metadata::ClassInfo& classInfo );
        void CreateWriteColumns( const Metadata::ClassInfo& classInfo );
        void CreateGetDataObject( const Metadata::ClassInfo& classInfo );
    };

    class JavaMsSqlComplexDatabaseReaderGenerator : public CodeGenerator<JavaMsSqlComplexReadersGenerator, JavaMsSqlComplexDatabaseReaderOptions>
    {
        const Metadata::ClassInfo& classInfo_;
    public:
        using Base = CodeGenerator<JavaMsSqlComplexReadersGenerator, JavaMsSqlComplexDatabaseReaderOptions>;

        inline JavaMsSqlComplexDatabaseReaderGenerator( const JavaMsSqlComplexReadersGenerator& owner, const Metadata::ClassInfo& classInfo );

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

    class JavaMsSqlReadersGenerator;


    class JavaMsSqlSimpleReadersGenerator : public GeneratorContainer<JavaMsSqlReadersGenerator, JavaMsSqlSimpleReadersOptions>
    {
    public:
        using Base = GeneratorContainer<JavaMsSqlReadersGenerator, JavaMsSqlSimpleReadersOptions>;

        JavaMsSqlSimpleReadersGenerator( const JavaMsSqlReadersGenerator& owner );

        void Run( );
    private:
        void CreateReader( const Metadata::ClassInfo& classInfo );
    };

    inline JavaMsSqlSimpleDatabaseReaderGenerator::JavaMsSqlSimpleDatabaseReaderGenerator( const JavaMsSqlSimpleReadersGenerator& owner, const Metadata::ClassInfo& classInfo )
        : Base( owner, *owner.Options( ).Add( classInfo, JavaHelper::GetSimpleDataReaderName( classInfo ) ) ), classInfo_( classInfo )
    { }

    class JavaMsSqlComplexReadersGenerator : public GeneratorContainer<JavaMsSqlReadersGenerator, JavaMsSqlComplexReadersOptions>
    {
    public:
        using Base = GeneratorContainer<JavaMsSqlReadersGenerator, JavaMsSqlComplexReadersOptions>;

        JavaMsSqlComplexReadersGenerator( const JavaMsSqlReadersGenerator& owner );

        void Run( );
    private:
        void CreateReader( const Metadata::ClassInfo& classInfo );
    };

    inline JavaMsSqlComplexDatabaseReaderGenerator::JavaMsSqlComplexDatabaseReaderGenerator( const JavaMsSqlComplexReadersGenerator& owner, const Metadata::ClassInfo& classInfo )
        : Base( owner, *owner.Options( ).Add( classInfo, JavaHelper::GetComplexDataReaderName( classInfo ) ) ), classInfo_( classInfo )
    { }

    class JavaMsSqlReadersGenerator : public GeneratorContainer<JavaMsSqlGenerator, JavaMsSqlReadersOptions>
    {
        JavaMsSqlSimpleReadersGenerator simple_;
        JavaMsSqlComplexReadersGenerator complex_;
    public:
        using Base = GeneratorContainer<JavaMsSqlGenerator, JavaMsSqlReadersOptions>;

        JavaMsSqlReadersGenerator( const JavaMsSqlGenerator& owner );

        void Run( )
        {
            simple_.Run( );
            complex_.Run( );
        }
    };

    inline JavaMsSqlSimpleReadersGenerator::JavaMsSqlSimpleReadersGenerator( const JavaMsSqlReadersGenerator& owner )
        : Base( owner, owner.Options().Simple() )
    { }

    inline JavaMsSqlComplexReadersGenerator::JavaMsSqlComplexReadersGenerator( const JavaMsSqlReadersGenerator& owner )
        : Base( owner, owner.Options( ).Complex( ) )
    { }

    

    class JavaMsSqlStoredProceduresGenerator : public CodeGenerator<JavaMsSqlGenerator, JavaMsSqlStoredProceduresOptions>
    {
    public:
        using Base = CodeGenerator<JavaMsSqlGenerator, JavaMsSqlStoredProceduresOptions>;

        inline JavaMsSqlStoredProceduresGenerator( const JavaMsSqlGenerator& owner );

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
        void AddInsertParameter( int parameterIndex, const Metadata::MemberInfo& memberInfo );
        void AddUpdateParameter( int parameterIndex, const Metadata::MemberInfo& memberInfo );
        void AddDeleteParameter( int parameterIndex, const Metadata::MemberInfo& memberInfo );

        void CreateInsertDataObject( );
        void CreateUpdateDataObject( );
        void CreateDeleteDataObject( );
        void CreateMergeDataObject( );
    };

    
    class JavaMsSqlDataContextGenerator : public CodeGenerator<JavaMsSqlGenerator, JavaMsSqlDataContextOptions>
    {
        std::set<WideString> functions_;
    public:
        using Base = CodeGenerator<JavaMsSqlGenerator, JavaMsSqlDataContextOptions>;

        inline JavaMsSqlDataContextGenerator( const JavaMsSqlGenerator& owner );

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
        void AddParameter( size_t parameterIndex, const Metadata::MemberInfo& memberInfo );
        void AddParameter( size_t parameterIndex, const Metadata::MemberInfo& memberInfo, const WideString& argumentName );
    };
    

    /*
    class JavaMsSqlUpdateNodesGenerator : public CodeGenerator<JavaMsSqlGenerator, JavaMsSqlUpdateNodesOptions>
    {
    public:
        using Base = CodeGenerator<JavaMsSqlGenerator, JavaMsSqlUpdateNodesOptions>;

        inline JavaMsSqlUpdateNodesGenerator( const JavaMsSqlGenerator& owner );

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
    */

    class JavaMsSqlTestDataObjectFactoryGenerator : public CodeGenerator<JavaMsSqlGenerator, JavaMsSqlTestDataObjectFactoryOptions>
    {
    public:
        using Base = CodeGenerator<JavaMsSqlGenerator, JavaMsSqlTestDataObjectFactoryOptions>;

        inline JavaMsSqlTestDataObjectFactoryGenerator( const JavaMsSqlGenerator& owner );

        void Run( );
    private:
        
    };



    class JavaMsSqlGenerator : public GeneratorContainer<JavaDatabasesGenerator, JavaMsSqlOptions>
    {
        JavaMsSqlReadersGenerator readers_;
        JavaMsSqlStoredProceduresGenerator storedProcedures_;
        JavaMsSqlDataContextGenerator dataContext_;
        //JavaMsSqlUpdateNodesGenerator updateNodes_;
        JavaMsSqlTestDataObjectFactoryGenerator testDataObjectFactory_;
    public:
        using Base = GeneratorContainer<JavaDatabasesGenerator, JavaMsSqlOptions>;

        inline JavaMsSqlGenerator( const JavaDatabasesGenerator& owner );

        void Run( )
        {
            readers_.Run( );
            storedProcedures_.Run( );
            dataContext_.Run( );
            //updateNodes_.Run( );
            testDataObjectFactory_.Run( );
        }

    };
    
    inline JavaMsSqlReadersGenerator::JavaMsSqlReadersGenerator( const JavaMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).Readers( ) ), simple_( *this ), complex_( *this )
    { }

    inline JavaMsSqlStoredProceduresGenerator::JavaMsSqlStoredProceduresGenerator( const JavaMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).StoredProcedures( ) )
    { }
    
    inline JavaMsSqlDataContextGenerator::JavaMsSqlDataContextGenerator( const JavaMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).DataContext( ) )
    { }

    /*
    inline JavaMsSqlUpdateNodesGenerator::JavaMsSqlUpdateNodesGenerator( const JavaMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).UpdateNodes( ) )
    { }
    */

    inline JavaMsSqlTestDataObjectFactoryGenerator::JavaMsSqlTestDataObjectFactoryGenerator( const JavaMsSqlGenerator& owner )
        : Base( owner, owner.Options( ).TestDataObjectFactory( ) )
    { }
}

#endif
