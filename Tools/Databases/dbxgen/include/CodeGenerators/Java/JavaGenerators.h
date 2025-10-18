#pragma once
#ifndef JAVAGENERATORS_H_
#define JAVAGENERATORS_H_
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

#include "CodeGenerators/Java/Databases/JavaDatabasesGenerator.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java
{
    class JavaEnumsGenerator;
    class JavaEnumGenerator : public CodeGenerator<JavaEnumsGenerator, JavaEnumOptions>
    {
        const Metadata::EnumInfo& enumInfo_;
    public:
        using Base = CodeGenerator<JavaEnumsGenerator, JavaEnumOptions>;

        inline JavaEnumGenerator(const JavaEnumsGenerator& owner, const Metadata::EnumInfo& enumInfo);

        void Run();

        static WideString GetUnderlyingType(const Metadata::EnumInfo& enumInfo);

    };

    class JavaEnumsGenerator;
    class JavaKindGenerator : public CodeGenerator<JavaEnumsGenerator, JavaKindOptions>
    {
    public:
        using Base = CodeGenerator<JavaEnumsGenerator, JavaKindOptions>;

        inline JavaKindGenerator(const JavaEnumsGenerator& owner);

        void Run();

    };


    class JavaEnumsGenerator : public GeneratorContainer<JavaDataGenerator, JavaEnumsOptions>
    {

    public:
        using Base = GeneratorContainer<JavaDataGenerator, JavaEnumsOptions>;

        inline JavaEnumsGenerator(const JavaDataGenerator& owner);

        void Run();
    private:
        
        void CreateEnum(const Metadata::EnumInfo& enumInfo);
        void CreateKind();

    };

    inline JavaEnumGenerator::JavaEnumGenerator(const JavaEnumsGenerator& owner, const Metadata::EnumInfo& enumInfo)
        : Base(owner, *owner.Options( ).Add( enumInfo ) ), enumInfo_(enumInfo)
    { }

    inline JavaKindGenerator::JavaKindGenerator(const JavaEnumsGenerator& owner)
        : Base(owner, owner.Options().Kind())
    { }

    class JavaDataTypesGenerator;
    class JavaDataTypeGenerator : public CodeGenerator<JavaDataTypesGenerator, JavaDataTypeOptions>
    {
        const Metadata::ClassInfo& classInfo_;
    public:
        using Base = CodeGenerator<JavaDataTypesGenerator, JavaDataTypeOptions>;

        inline JavaDataTypeGenerator( const JavaDataTypesGenerator& owner, const Metadata::ClassInfo& classInfo );

        void Run( );

        static WideString GetUnderlyingType( const Metadata::EnumInfo& enumInfo );

    };

    
    class JavaDataTypeFactoryGenerator : public CodeGenerator<JavaDataTypesGenerator, JavaDataTypeFactoryOptions>
    {
    public:
        using Base = CodeGenerator<JavaDataTypesGenerator, JavaDataTypeFactoryOptions>;

        inline JavaDataTypeFactoryGenerator( const JavaDataTypesGenerator& owner );

        void Run( );

    };

    class JavaTestDataObjectFactoryGenerator : public CodeGenerator<JavaDataTypesGenerator, JavaTestDataObjectFactoryOptions>
    {
    public:
        using Base = CodeGenerator<JavaDataTypesGenerator, JavaTestDataObjectFactoryOptions>;

        inline JavaTestDataObjectFactoryGenerator( const JavaDataTypesGenerator& owner );

        void Run( );

    };


    
    class JavaDataTypesGenerator : public GeneratorContainer<JavaDataGenerator, JavaDataTypesOptions>
    {
    public:
        using Base = GeneratorContainer<JavaDataGenerator, JavaDataTypesOptions>;

        inline JavaDataTypesGenerator(const JavaDataGenerator& owner);

        void Run();
    private:
        void CreateDataType(const Metadata::ClassInfo& classInfo);
        void CreateFactory();
        void CreateTestDataObjectFactory( );
    };
    
    inline JavaDataTypeGenerator::JavaDataTypeGenerator( const JavaDataTypesGenerator& owner, const Metadata::ClassInfo& classInfo )
        : Base( owner, *owner.Options( ).Add( JavaHelper::GetDataType( classInfo ) + L".java", classInfo ) ), classInfo_( classInfo )
    { }

    inline JavaDataTypeFactoryGenerator::JavaDataTypeFactoryGenerator( const JavaDataTypesGenerator& owner )
        : Base( owner, owner.Options( ).Factory( ) )
    { }

    inline JavaTestDataObjectFactoryGenerator::JavaTestDataObjectFactoryGenerator( const JavaDataTypesGenerator& owner )
        : Base( owner, owner.Options( ).TestDataObjectFactory( ) )
    { }


    
    class JavaDataContextGenerator : public CodeGenerator<JavaDataGenerator, JavaDataContextOptions>
    {
        std::set<WideString> functions_;
    public:
        using Base = CodeGenerator<JavaDataGenerator, JavaDataContextOptions>;

        inline JavaDataContextGenerator(const JavaDataGenerator& owner);

        void Run();
    private:
        void CreateMembers(const Metadata::ClassInfo& classInfo);
        void CreateGetById(const Metadata::ClassInfo& classInfo);
        void CreateGetAll(const Metadata::ClassInfo& classInfo);
        void CreateGetByIndex(const Metadata::ClassInfo& classInfo);
        void CreateGetByIndex(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByNullableIndex(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByIndexAt(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByIndexFrom(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByIndexUntil(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByIndexOver(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
    };
    


    class JavaDataGenerator : public GeneratorContainer<JavaGenerator, JavaDataOptions>
    {
        JavaEnumsGenerator enums_;
        JavaDataTypesGenerator dataTypes_;
        JavaDataContextGenerator dataContext_;
    public:
        using Base = GeneratorContainer<JavaGenerator, JavaDataOptions>;

        inline JavaDataGenerator(const JavaGenerator& owner);

        void Run()
        {
            enums_.Run();
            dataTypes_.Run();
            dataContext_.Run();
        }
    };

    inline JavaEnumsGenerator::JavaEnumsGenerator(const JavaDataGenerator& owner)
        : Base(owner, owner.Options().Enums())
    {
    }

    
    inline JavaDataTypesGenerator::JavaDataTypesGenerator(const JavaDataGenerator& owner)
        : Base(owner, owner.Options().DataTypes())
    {
    }
    

    
    inline JavaDataContextGenerator::JavaDataContextGenerator(const JavaDataGenerator& owner)
        : Base(owner, owner.Options().DataContext())
    {
    }
    

    /*
    class JavaEntitiesGenerator;
    class JavaEntityTypesGenerator : public CodeGenerator<JavaEntitiesGenerator, JavaEntityTypesOptions>
    {
    public:
        using Base = CodeGenerator<JavaEntitiesGenerator, JavaEntityTypesOptions>;

        inline JavaEntityTypesGenerator(const JavaEntitiesGenerator& owner);

        void Run();
    private:
        void CreateEntityType(const Metadata::ClassInfo& classInfo);
        void CreateMember(const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member);
        void CreateBasicMember(const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member);
        void CreateReferenceMember(const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member);
        void CreateCollectionMember(const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member);
        void CreateTimeSeriesMember(const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member);
        void CreateFactory();
    };

    class JavaEntityContextGenerator : public CodeGenerator<JavaEntitiesGenerator, JavaEntityContextOptions>
    {
        std::set<WideString> functions_;
    public:
        using Base = CodeGenerator<JavaEntitiesGenerator, JavaEntityContextOptions>;

        inline JavaEntityContextGenerator(const JavaEntitiesGenerator& owner);

        void Run();
    private:
        void CreateMembers(const Metadata::ClassInfo& classInfo);
        void CreateGetById(const Metadata::ClassInfo& classInfo);
        void CreateGetAll(const Metadata::ClassInfo& classInfo);
        void CreateGetByIndex(const Metadata::ClassInfo& classInfo);
        void CreateGetByIndex(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByNullableIndex(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByIndexAt(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByIndexFrom(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByIndexUntil(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByIndexOver(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
    };

    class JavaEntityChangesGenerator : public CodeGenerator<JavaEntitiesGenerator, JavaEntityChangesOptions>
    {
        std::set<WideString> functions_;
    public:
        using Base = CodeGenerator<JavaEntitiesGenerator, JavaEntityChangesOptions>;

        inline JavaEntityChangesGenerator(const JavaEntitiesGenerator& owner);

        void Run();
    private:
        void CreateEntityIndexClasses(const Metadata::ClassInfo& classInfo);
        void CreateEntityUniqueIndexClass(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo);
        void CreateEntitySingleFieldUniqueIndexClass(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo);
        void CreateEntityMultiFieldUniqueIndexClass(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo);
        void CreateEntityMultiFieldUniqueIndexIntermediateClass(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t fieldIndex);
        void CreateEntityMultiFieldUniqueIndexFinalClass(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo);
        void CreateEntityIndexClass(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo);
        void CreateEntityIndexIntermediateClass(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t fieldIndex);
        void CreateEntityIndexFinalClass(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo);
        void CreateNullableEntityUniqueIndexClass(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo);
        void CreateNullableEntityIndexClass(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo);


        void CreateIndexGetByIndex(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo);
        void CreateIndexGetByIndex(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateIndexGetByNullableIndex(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateIndexGetByIndexAt(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateIndexGetByIndexFrom(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateIndexGetByIndexUntil(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateIndexGetByIndexOver(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);

        void CreateNestedGetByIndex(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);
        void CreateNestedGetByNullableIndex(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);
        void CreateNestedGetByIndexAt(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);
        void CreateNestedGetByIndexFrom(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);
        void CreateNestedGetByIndexUntil(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);
        void CreateNestedGetByIndexOver(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);

        void CreateEntityChanges();
        void CreateGetAll(const Metadata::ClassInfo& classInfo);
        void CreateGetByIndex(const Metadata::ClassInfo& classInfo);
        void CreateGetByIndex(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByNullableIndex(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByIndexAt(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByIndexFrom(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByIndexUntil(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
        void CreateGetByIndexOver(const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& indexInfo, size_t indexMemberCount);
    };


    class JavaEntitiesGenerator : public GeneratorContainer<JavaGenerator, JavaEntitiesOptions>
    {
        JavaEntityTypesGenerator entityTypes_;
        JavaEntityContextGenerator entityContext_;
        JavaEntityChangesGenerator entityChanges_;
    public:
        using Base = GeneratorContainer<JavaGenerator, JavaEntitiesOptions>;

        inline JavaEntitiesGenerator(const JavaGenerator& owner);

        void Run()
        {
            entityTypes_.Run();
            entityContext_.Run();
            entityChanges_.Run();
        }
    };

    inline JavaEntityTypesGenerator::JavaEntityTypesGenerator(const JavaEntitiesGenerator& owner)
        : Base(owner, owner.Options().EntityTypes())
    {
    }

    inline JavaEntityContextGenerator::JavaEntityContextGenerator(const JavaEntitiesGenerator& owner)
        : Base(owner, owner.Options().EntityContext())
    {
    }

    inline JavaEntityChangesGenerator::JavaEntityChangesGenerator(const JavaEntitiesGenerator& owner)
        : Base(owner, owner.Options().EntityChanges())
    {
    }
    */

    class JavaGenerator : public GeneratorContainer<Generator, JavaOptions>
    {
        JavaDataGenerator data_;
        Databases::JavaDatabasesGenerator databases_;
        //JavaEntitiesGenerator entities_;
    public:
        using Base = GeneratorContainer<Generator, JavaOptions>;

        inline JavaGenerator(const Generator& owner);

        void Run()
        {
            data_.Run();
            databases_.Run();
            //entities_.Run();
        }

    };



    inline JavaDataGenerator::JavaDataGenerator(const JavaGenerator& owner)
        : Base(owner, owner.Options().Data()), enums_(*this), dataTypes_(*this), dataContext_(*this)
    { }

    namespace Databases
    {
        inline JavaDatabasesGenerator::JavaDatabasesGenerator(const JavaGenerator& owner)
            : Base(owner, owner.Options().Databases()), msSql_(*this)
        { }
        
    }
    /*
    inline JavaEntitiesGenerator::JavaEntitiesGenerator(const JavaGenerator& owner)
        : Base(owner, owner.Options().Entities()), entityTypes_(*this), entityContext_(*this), entityChanges_(*this)
    { }
    */
}


#endif

