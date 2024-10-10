#pragma once
#ifndef CPPGENERATORS_H_
#define CPPGENERATORS_H_
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
#include "CodeGenerators/Cpp/Databases/CppDatabasesGenerator.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Cpp
{
    // ------------------------------------------------------------------------
    // C++
    // ------------------------------------------------------------------------
    class CppEnumsGenerator : public CodeGenerator<CppDataGenerator, CppEnumsOptions>
    {
    public:
        using Base = CodeGenerator<CppDataGenerator, CppEnumsOptions>;
        CppEnumsGenerator( const CppDataGenerator& owner );

        void Run( );
    private:
        static WideString GetUnderlyingType( const Metadata::EnumInfo& enumInfo );
        void CreateEnum( const Metadata::EnumInfo& enumInfo );
        void CreateKind( );
    };

    class CppDataTypesGenerator : public CodeGenerator<CppDataGenerator, CppDataTypesOptions>
    {
    public:
        using Base = CodeGenerator<CppDataGenerator, CppDataTypesOptions>;
        CppDataTypesGenerator( const CppDataGenerator& owner );

        void Run( );
    private:
        void CreateDataType( const Metadata::ClassInfo& classInfo );
        void CreateAccessor( const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member );
        void CreateSetter( const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member );
        void CreateReadDataFrom( );
        void CreateWriteDataTo( );
    };

    class CppDataTypesSourceGenerator : public CodeGenerator<CppDataGenerator, CppDataTypesSourceOptions>
    {
    public:
        using Base = CodeGenerator<CppDataGenerator, CppDataTypesSourceOptions>;
        CppDataTypesSourceGenerator( const CppDataGenerator& owner );

        void Run( );
    private:
        void CreateDataTypeFactory( );
    };



    class CppDataGenerator : public GeneratorContainer<CppGenerator, CppDataOptions>
    {
        CppEnumsGenerator enums_;
        CppDataTypesGenerator dataTypes_;
        CppDataTypesSourceGenerator dataTypesSource_;
    public:
        using Base = GeneratorContainer<CppGenerator, CppDataOptions>;
        CppDataGenerator( const CppGenerator& owner );

        void Run( )
        {
            enums_.Run( );
            dataTypes_.Run( );
            dataTypesSource_.Run( );
        }
    };

    inline CppEnumsGenerator::CppEnumsGenerator( const CppDataGenerator& owner )
        : Base( owner, owner.Options( ).Enums( ) )
    {

    }

    inline CppDataTypesGenerator::CppDataTypesGenerator( const CppDataGenerator& owner )
        : Base( owner, owner.Options( ).DataTypes( ) )
    {

    }

    inline CppDataTypesSourceGenerator::CppDataTypesSourceGenerator( const CppDataGenerator& owner )
        : Base( owner, owner.Options( ).DataTypesSource( ) )
    {

    }

    class CppGenerator : public GeneratorContainer<Generator, CppOptions>
    {
        CppDataGenerator data_;
        Databases::CppDatabasesGenerator databases_;
    public:
        using Base = GeneratorContainer<Generator, CppOptions>;
        CppGenerator( const Generator& owner );

        void Run( )
        {
            data_.Run( );
            databases_.Run( );
        }

        const CppDataGenerator& Data( ) const
        {
            return data_;
        }
        const Databases::CppDatabasesGenerator& Databases( ) const
        {
            return databases_;
        }

    };


    inline CppDataGenerator::CppDataGenerator( const CppGenerator& owner )
        : Base( owner, owner.Options( ).Data( ) ), enums_( *this ), dataTypes_( *this ), dataTypesSource_( *this )
    {
    }

    namespace Databases
    {
        inline CppDatabasesGenerator::CppDatabasesGenerator( const CppGenerator& owner )
            : Base( owner, owner.Options( ).Databases( ) ), msSql_( *this )
        {
        }
    }



    class CppDataTestGenerator;
    class CppDataTypesTestGenerator : public CodeGenerator<CppDataTestGenerator, CppDataTypesTestOptions>
    {
    public:
        using Base = CodeGenerator<CppDataTestGenerator, CppDataTypesTestOptions>;
        CppDataTypesTestGenerator( const CppDataTestGenerator& owner );

        void Run( );
    private:
        void CreateSerializationTest( const Metadata::ClassInfo& classInfo );
    };

    class CppTestGenerator;
    class CppDataTestGenerator : public GeneratorContainer<CppTestGenerator, CppDataTestOptions>
    {
        CppDataTypesTestGenerator dataTypes_;
    public:
        using Base = GeneratorContainer<CppTestGenerator, CppDataTestOptions>;
        CppDataTestGenerator( const CppTestGenerator& owner );

        void Run( )
        {
            dataTypes_.Run( );
        }
    };

    inline CppDataTypesTestGenerator::CppDataTypesTestGenerator( const CppDataTestGenerator& owner )
        : Base( owner, owner.Options( ).DataTypes( ) )
    {

    }



    class CppDatabaseTestGenerator : public GeneratorContainer<CppTestGenerator, CppDatabaseTestOptions>
    {
    public:
        using Base = GeneratorContainer<CppTestGenerator, CppDatabaseTestOptions>;
        CppDatabaseTestGenerator( const CppTestGenerator& owner );

        void Run( )
        {
        }
    };

    class CppTestGenerator : public GeneratorContainer<Generator, CppTestOptions>
    {
        CppDataTestGenerator data_;
        CppDatabaseTestGenerator database_;
    public:
        using Base = GeneratorContainer<Generator, CppTestOptions>;
        CppTestGenerator( const Generator& owner );

        void Run( )
        {
            data_.Run( );
            database_.Run( );
        }

        const CppDataTestGenerator& Data( ) const
        {
            return data_;
        }
        const CppDatabaseTestGenerator& Database( ) const
        {
            return database_;
        }

    };

    inline CppDataTestGenerator::CppDataTestGenerator( const CppTestGenerator& owner )
        : Base( owner, owner.Options( ).Data( ) ), dataTypes_( *this )
    {
    }

    inline CppDatabaseTestGenerator::CppDatabaseTestGenerator( const CppTestGenerator& owner )
        : Base( owner, owner.Options( ).Database( ) )
    {
    }
}

#endif
