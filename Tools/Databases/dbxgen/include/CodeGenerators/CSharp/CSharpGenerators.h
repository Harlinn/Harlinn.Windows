#pragma once
#ifndef CSHARPGENERATORS_H_
#define CSHARPGENERATORS_H_
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
#include "CodeGenerators/CSharp/Databases/CSharpDatabasesGenerator.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::CSharp
{
    class CSharpEnumsGenerator : public CodeGenerator<CSharpDataGenerator, CSharpEnumsOptions>
    {
    public:
        using Base = CodeGenerator<CSharpDataGenerator, CSharpEnumsOptions>;

        inline CSharpEnumsGenerator( const CSharpDataGenerator& owner );

        void Run( );
    private:
        static WideString GetUnderlyingType( const Metadata::EnumInfo& enumInfo );
        void CreateEnum( const Metadata::EnumInfo& enumInfo );
        void CreateKind( );

    };

    class CSharpDataTypesGenerator : public CodeGenerator<CSharpDataGenerator, CSharpDataTypesOptions>
    {
    public:
        using Base = CodeGenerator<CSharpDataGenerator, CSharpDataTypesOptions>;

        inline CSharpDataTypesGenerator( const CSharpDataGenerator& owner );

        void Run( );
    private:
        void CreateDataType( const Metadata::ClassInfo& classInfo );
        void CreateFactory( );
    };

    class CSharpIDataContextGenerator : public CodeGenerator<CSharpDataGenerator, CSharpIDataContextOptions>
    {
        std::set<WideString> functions_;
    public:
        using Base = CodeGenerator<CSharpDataGenerator, CSharpIDataContextOptions>;

        inline CSharpIDataContextGenerator( const CSharpDataGenerator& owner );

        void Run( );
    private:
        void CreateMembers( const Metadata::ClassInfo& classInfo );
        void CreateGetById( const Metadata::ClassInfo& classInfo );
        void CreateGetAll( const Metadata::ClassInfo& classInfo );
        void CreateGetByIndex( const Metadata::ClassInfo& classInfo );
        void CreateGetByIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByNullableIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexAt( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexFrom( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexUntil( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexOver( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
    };



    class CSharpDataGenerator : public GeneratorContainer<CSharpGenerator, CSharpDataOptions>
    {
        CSharpEnumsGenerator enums_;
        CSharpDataTypesGenerator dataTypes_;
        CSharpIDataContextGenerator dataContext_;
    public:
        using Base = GeneratorContainer<CSharpGenerator, CSharpDataOptions>;

        inline CSharpDataGenerator( const CSharpGenerator& owner );

        void Run( )
        {
            enums_.Run( );
            dataTypes_.Run( );
            dataContext_.Run( );
        }
    };

    inline CSharpEnumsGenerator::CSharpEnumsGenerator( const CSharpDataGenerator& owner )
        : Base( owner, owner.Options( ).Enums( ) )
    {
    }

    inline CSharpDataTypesGenerator::CSharpDataTypesGenerator( const CSharpDataGenerator& owner )
        : Base( owner, owner.Options( ).DataTypes( ) )
    {
    }

    inline CSharpIDataContextGenerator::CSharpIDataContextGenerator( const CSharpDataGenerator& owner )
        : Base( owner, owner.Options( ).DataContext( ) )
    {
    }


    class CSharpEntitiesGenerator;
    class CSharpEntityTypesGenerator : public CodeGenerator<CSharpEntitiesGenerator, CSharpEntityTypesOptions>
    {
    public:
        using Base = CodeGenerator<CSharpEntitiesGenerator, CSharpEntityTypesOptions>;

        inline CSharpEntityTypesGenerator( const CSharpEntitiesGenerator& owner );

        void Run( );
    private:
        void CreateEntityType( const Metadata::ClassInfo& classInfo );
        void CreateMember( const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member );
        void CreateBasicMember( const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member );
        void CreateReferenceMember( const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member );
        void CreateCollectionMember( const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member );
        void CreateTimeSeriesMember( const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member );
        void CreateFactory( );
    };

    class CSharpEntityContextGenerator : public CodeGenerator<CSharpEntitiesGenerator, CSharpEntityContextOptions>
    {
        std::set<WideString> functions_;
    public:
        using Base = CodeGenerator<CSharpEntitiesGenerator, CSharpEntityContextOptions>;

        inline CSharpEntityContextGenerator( const CSharpEntitiesGenerator& owner );

        void Run( );
    private:
        void CreateMembers( const Metadata::ClassInfo& classInfo );
        void CreateGetById( const Metadata::ClassInfo& classInfo );
        void CreateGetAll( const Metadata::ClassInfo& classInfo );
        void CreateGetByIndex( const Metadata::ClassInfo& classInfo );
        void CreateGetByIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByNullableIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexAt( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexFrom( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexUntil( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexOver( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
    };

    class CSharpEntityChangesGenerator : public CodeGenerator<CSharpEntitiesGenerator, CSharpEntityChangesOptions>
    {
        std::set<WideString> functions_;
    public:
        using Base = CodeGenerator<CSharpEntitiesGenerator, CSharpEntityChangesOptions>;

        inline CSharpEntityChangesGenerator( const CSharpEntitiesGenerator& owner );

        void Run( );
    private:
        void CreateEntityIndexClasses( const Metadata::ClassInfo& classInfo );
        void CreateEntityUniqueIndexClass( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo );
        void CreateEntitySingleFieldUniqueIndexClass( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo );
        void CreateEntityMultiFieldUniqueIndexClass( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo );
        void CreateEntityMultiFieldUniqueIndexIntermediateClass( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t fieldIndex );
        void CreateEntityMultiFieldUniqueIndexFinalClass( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo );
        void CreateEntityIndexClass( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo );
        void CreateEntityIndexIntermediateClass( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t fieldIndex );
        void CreateEntityIndexFinalClass( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo );
        void CreateNullableEntityUniqueIndexClass( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo );
        void CreateNullableEntityIndexClass( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo );


        void CreateIndexGetByIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo );
        void CreateIndexGetByIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateIndexGetByNullableIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateIndexGetByIndexAt( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateIndexGetByIndexFrom( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateIndexGetByIndexUntil( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateIndexGetByIndexOver( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );

        void CreateNestedGetByIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );
        void CreateNestedGetByNullableIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );
        void CreateNestedGetByIndexAt( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );
        void CreateNestedGetByIndexFrom( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );
        void CreateNestedGetByIndexUntil( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );
        void CreateNestedGetByIndexOver( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );

        void CreateEntityChanges( );
        void CreateGetAll( const Metadata::ClassInfo& classInfo );
        void CreateGetByIndex( const Metadata::ClassInfo& classInfo );
        void CreateGetByIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByNullableIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexAt( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexFrom( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexUntil( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
        void CreateGetByIndexOver( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount );
    };


    class CSharpEntitiesGenerator : public GeneratorContainer<CSharpGenerator, CSharpEntitiesOptions>
    {
        CSharpEntityTypesGenerator entityTypes_;
        CSharpEntityContextGenerator entityContext_;
        CSharpEntityChangesGenerator entityChanges_;
    public:
        using Base = GeneratorContainer<CSharpGenerator, CSharpEntitiesOptions>;

        inline CSharpEntitiesGenerator( const CSharpGenerator& owner );

        void Run( )
        {
            entityTypes_.Run( );
            entityContext_.Run( );
            entityChanges_.Run( );
        }
    };

    inline CSharpEntityTypesGenerator::CSharpEntityTypesGenerator( const CSharpEntitiesGenerator& owner )
        : Base( owner, owner.Options( ).EntityTypes( ) )
    {
    }

    inline CSharpEntityContextGenerator::CSharpEntityContextGenerator( const CSharpEntitiesGenerator& owner )
        : Base( owner, owner.Options( ).EntityContext( ) )
    {
    }

    inline CSharpEntityChangesGenerator::CSharpEntityChangesGenerator( const CSharpEntitiesGenerator& owner )
        : Base( owner, owner.Options( ).EntityChanges( ) )
    {
    }


    class CSharpGenerator : public GeneratorContainer<Generator, CSharpOptions>
    {
        CSharpDataGenerator data_;
        Databases::CSharpDatabasesGenerator databases_;
        CSharpEntitiesGenerator entities_;
    public:
        using Base = GeneratorContainer<Generator, CSharpOptions>;

        inline CSharpGenerator( const Generator& owner );

        void Run( )
        {
            data_.Run( );
            databases_.Run( );
            entities_.Run( );
        }

    };



    inline CSharpDataGenerator::CSharpDataGenerator( const CSharpGenerator& owner )
        : Base( owner, owner.Options( ).Data( ) ), enums_( *this ), dataTypes_( *this ), dataContext_( *this )
    {
    }

    namespace Databases
    {
        inline CSharpDatabasesGenerator::CSharpDatabasesGenerator( const CSharpGenerator& owner )
            : Base( owner, owner.Options( ).Databases( ) ), msSql_( *this )
        {
        }
    }

    inline CSharpEntitiesGenerator::CSharpEntitiesGenerator( const CSharpGenerator& owner )
        : Base( owner, owner.Options( ).Entities( ) ), entityTypes_( *this ), entityContext_( *this ), entityChanges_( *this )
    {
    }
}

#endif
