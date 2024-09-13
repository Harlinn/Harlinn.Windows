#pragma once
#ifndef GENERATOR_H_
#define GENERATOR_H_
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

#include "ModelInfo.h"
#include "Options.h"
#include "CodeStream.h"

namespace Harlinn::ODBC::Tool
{
    class SqlServerGenerator;
    class DatabaseGenerator;
    class CppDatabaseReadersGenerator;
    class CppDataGenerator;
    class CppDatabaseGenerator;
    class CppGenerator;
    class Generator;


    template<typename OwnerT, typename OptionsT>
    class GeneratorContainer
    {
    public:
        using OwnerType = OwnerT;
        using OptionsType = OptionsT;
    private:
        const OwnerType& owner_;
        const OptionsType& options_;
    public:
        GeneratorContainer( const OwnerType& owner, const OptionsType& options )
            : owner_( owner ), options_( options )
        { }

        const OwnerType& Owner( ) const
        {
            return owner_;
        }
        const OptionsType& Options( ) const
        {
            return options_;
        }

        const ModelInfo& Model( ) const
        {
            return Owner( ).Model( );
        }

    };

    template<typename OwnerT, typename OptionsT>
    class CodeGenerator : protected CodeStream
    {
    public:
        using Base = CodeStream;
        using OwnerType = OwnerT;
        using OptionsType = OptionsT;
    private:
        const OwnerType& owner_;
        const OptionsType& options_;
    public:
        CodeGenerator( const OwnerType& owner, const OptionsType& options )
            : Base( options.Filename() ), owner_( owner ), options_( options )
        {
        }

        const OwnerType& Owner( ) const
        {
            return owner_;
        }
        const OptionsType& Options( ) const
        {
            return options_;
        }

        const ModelInfo& Model( ) const
        {
            return Owner( ).Model( );
        }

    };


    // ------------------------------------------------------------------------
    // Database
    // ------------------------------------------------------------------------
    class SqlServerCreateTablesGenerator : public CodeGenerator<SqlServerGenerator, SqlServerCreateTablesOptions>
    {
    public:
        using Base = CodeGenerator<SqlServerGenerator, SqlServerCreateTablesOptions>;
        SqlServerCreateTablesGenerator( const SqlServerGenerator& owner );

        void Run( );
    private:
        static WideString GetColumnName( const MemberInfo& member );
        static WideString GetColumnType( const MemberInfo& member );
        static WideString GetColumnNullable( const MemberInfo& member );
        static WideString GetTableName( const ClassInfo& classInfo );
        static WideString GetIndexName( const IndexInfo& indexInfo );
        static WideString GetColumnNames( const IndexInfo& indexInfo );

        void WriteTableColumn( const ClassInfo& classInfo, const MemberInfo& member );
        void WriteTableIndex( const ClassInfo& classInfo, const IndexInfo& index );
        void WriteTable( const ClassInfo& classInfo );
        void WriteForeignKeys( const ClassInfo& classInfo );
        void WriteForeignKey( const ClassInfo& classInfo, const ReferenceMemberInfo& reference );
        void WriteEntityTypesTable( );
    };



    class SqlServerCreateViewsGenerator : public CodeGenerator<SqlServerGenerator, SqlServerCreateViewsOptions>
    {
    public:
        using Base = CodeGenerator<SqlServerGenerator, SqlServerCreateViewsOptions>;
        SqlServerCreateViewsGenerator( const SqlServerGenerator& owner );

        void Run( );
    private:
        static WideString GetFieldNameForSelect( const MemberInfo& memberInfo );
        void CreateTopLevelView( const ClassInfo& classInfo );
        void CreateView( const ClassInfo& classInfo );
    };

    class SqlServerCreateInsertProceduresGenerator : public CodeGenerator<SqlServerGenerator, SqlServerCreateInsertProceduresOptions>
    {
    public:
        using Base = CodeGenerator<SqlServerGenerator, SqlServerCreateInsertProceduresOptions>;
        SqlServerCreateInsertProceduresGenerator( const SqlServerGenerator& owner );

        void Run( );
    private:
        static WideString GetProcedureParameters( const ClassInfo& classInfo );
        static WideString GetInsertStatement( const ClassInfo& classInfo );
        static WideString GetInsertProcedure( const ClassInfo& classInfo );
        static WideString GetInsertTrigger( const ClassInfo& classInfo );
        void CreateInsertProcedure( const ClassInfo& classInfo );
        void CreateInsertTrigger( const ClassInfo& classInfo );
    };


    class SqlServerCreateUpdateProceduresGenerator : public CodeGenerator<SqlServerGenerator, SqlServerCreateUpdateProceduresOptions>
    {
    public:
        using Base = CodeGenerator<SqlServerGenerator, SqlServerCreateUpdateProceduresOptions>;
        SqlServerCreateUpdateProceduresGenerator( const SqlServerGenerator& owner );

        void Run( );
    private:
        static WideString GetProcedureParameters( const ClassInfo& classInfo );
        static WideString GetTopLevelUpdateStatement( const ClassInfo& classInfo );
        static WideString GetUpdateStatement( const ClassInfo& classInfo );
        void CreateUpdateStatement( const ClassInfo& classInfo );

    };

    class SqlServerCreateDeleteProceduresGenerator : public CodeGenerator<SqlServerGenerator, SqlServerCreateDeleteProceduresOptions>
    {
    public:
        using Base = CodeGenerator<SqlServerGenerator, SqlServerCreateDeleteProceduresOptions>;
        SqlServerCreateDeleteProceduresGenerator( const SqlServerGenerator& owner );

        void Run( );
    private:
        static WideString GetDeleteStatement( const ClassInfo& classInfo );
        void CreateDeleteProcedure( const ClassInfo& classInfo );
    };


    



    class SqlServerGenerator : public GeneratorContainer<DatabaseGenerator, SqlServerOptions>
    {
        SqlServerCreateTablesGenerator createTables_;
        SqlServerCreateViewsGenerator createViews_;
        SqlServerCreateInsertProceduresGenerator createInsertProcedures_;
        SqlServerCreateUpdateProceduresGenerator createUpdateProcedures_;
        SqlServerCreateDeleteProceduresGenerator createDeleteProcedures_;
    public:
        using Base = GeneratorContainer<DatabaseGenerator, SqlServerOptions>;
        SqlServerGenerator( DatabaseGenerator& owner );

        void Run( )
        {
            createTables_.Run( );
            createViews_.Run( );
            createInsertProcedures_.Run( );
            createUpdateProcedures_.Run( );
            createDeleteProcedures_.Run( );
        }

    };



    class DatabaseGenerator : public GeneratorContainer<Generator, DatabaseOptions>
    {
        SqlServerGenerator sqlServer_;
    public:
        using Base = GeneratorContainer<Generator, DatabaseOptions>;
        DatabaseGenerator( const Generator& owner );

        void Run( )
        {
            sqlServer_.Run( );
        }
    };

    inline SqlServerGenerator::SqlServerGenerator( DatabaseGenerator& owner )
        : Base( owner, owner.Options().SqlServer() ),
          createTables_( *this ),
          createViews_( *this ),
          createInsertProcedures_( *this ),
          createUpdateProcedures_( *this ),
          createDeleteProcedures_( *this )
    { }

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
        static WideString GetUnderlyingType( const EnumInfo& enumInfo );
        void CreateEnum( const EnumInfo& enumInfo );
        void CreateKind( );
    };

    class CppDataTypesGenerator : public CodeGenerator<CppDataGenerator, CppDataTypesOptions>
    {
    public:
        using Base = CodeGenerator<CppDataGenerator, CppDataTypesOptions>;
        CppDataTypesGenerator( const CppDataGenerator& owner );

        void Run( );
    private:
        void CreateDataType( const ClassInfo& classInfo );
        void CreateAccessor( const ClassInfo& classInfo, const MemberInfo& member );
        void CreateSetter( const ClassInfo& classInfo, const MemberInfo& member );
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
        : Base( owner, owner.Options().Enums() )
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

    class CppDatabaseReadersGenerator : public CodeGenerator<CppDatabaseGenerator, CppDatabaseReadersOptions>
    {
    public:
        using Base = CodeGenerator<CppDatabaseGenerator, CppDatabaseReadersOptions>;
        CppDatabaseReadersGenerator( const CppDatabaseGenerator& owner );

        void Run( );
    private:
        void CreateBaseClass( );
        void CreateColumnDataType( const ClassInfo& classInfo );
        void CreateQuery( const ClassInfo& classInfo );
        void CreateFieldIds( const ClassInfo& classInfo );
        void CreateBindColumns( const ClassInfo& classInfo );
        void CreateReadUnboundData( const ClassInfo& classInfo );
        void CreateAccessor( const ClassInfo& classInfo, const MemberInfo& member );
        void CreateSetter( const ClassInfo& classInfo, const MemberInfo& member );
        void CreateWriteColumns( const ClassInfo& classInfo );
        void CreateAssignTo( const ClassInfo& classInfo );
        
    };

    class CppDatabaseReadersSourceGenerator : public CodeGenerator<CppDatabaseGenerator, CppDatabaseReadersSourceOptions>
    {
    public:
        using Base = CodeGenerator<CppDatabaseGenerator, CppDatabaseReadersSourceOptions>;
        CppDatabaseReadersSourceGenerator( const CppDatabaseGenerator& owner );

        void Run( );
    private:
        void CreateColumnDataType( const ClassInfo& classInfo );
        void CreateQuery( const ClassInfo& classInfo );

    };


    class CppComplexDatabaseReadersGenerator : public CodeGenerator<CppDatabaseGenerator, CppComplexDatabaseReadersOptions>
    {
    public:
        using Base = CodeGenerator<CppDatabaseGenerator, CppComplexDatabaseReadersOptions>;
        CppComplexDatabaseReadersGenerator( const CppDatabaseGenerator& owner );

        void Run( );
    private:
        void CreateColumnDataType( const ClassInfo& classInfo );
        void CreateQuery( const ClassInfo& classInfo );
        void CreateFieldIds( const ClassInfo& classInfo );
        void CreateBindColumns( const ClassInfo& classInfo );
        void CreateReadUnboundData( const ClassInfo& classInfo );
        void CreateAccessors( const ClassInfo& classInfo );
        
        void CreateWriteColumns( const ClassInfo& classInfo );
    };

    class CppComplexDatabaseReadersSourceGenerator : public CodeGenerator<CppDatabaseGenerator, CppComplexDatabaseReadersSourceOptions>
    {
    public:
        using Base = CodeGenerator<CppDatabaseGenerator, CppComplexDatabaseReadersSourceOptions>;
        CppComplexDatabaseReadersSourceGenerator( const CppDatabaseGenerator& owner );

        void Run( );
    private:
        void CreateColumnDataType( const ClassInfo& classInfo );
        void CreateQuery( const ClassInfo& classInfo );
        
        void CreateBindColumns( const ClassInfo& classInfo );
        void CreateReadUnboundData( const ClassInfo& classInfo );
    };

    class CppStoredProceduresGenerator : public CodeGenerator<CppDatabaseGenerator, CppStoredProceduresOptions>
    {
    public:
        using Base = CodeGenerator<CppDatabaseGenerator, CppStoredProceduresOptions>;
        CppStoredProceduresGenerator( const CppDatabaseGenerator& owner );

        void Run( );
    private:
        void CreateInsert( const ClassInfo& classInfo );
        void CreateUpdate( const ClassInfo& classInfo );
        void CreateDelete( const ClassInfo& classInfo );
    };

    class CppStoredProceduresSourceGenerator : public CodeGenerator<CppDatabaseGenerator, CppStoredProceduresSourceOptions>
    {
    public:
        using Base = CodeGenerator<CppDatabaseGenerator, CppStoredProceduresSourceOptions>;
        CppStoredProceduresSourceGenerator( const CppDatabaseGenerator& owner );

        void Run( );
    private:
        void CreateInsert( const ClassInfo& classInfo );
        void CreateUpdate( const ClassInfo& classInfo );
        void CreateDelete( const ClassInfo& classInfo );
    };



    class CppDatabaseGenerator : public GeneratorContainer<CppGenerator, CppDatabaseOptions>
    {
        CppDatabaseReadersGenerator databaseReaders_;
        CppDatabaseReadersSourceGenerator databaseReadersSource_;
        CppComplexDatabaseReadersGenerator complexDatabaseReaders_;
        CppComplexDatabaseReadersSourceGenerator complexDatabaseReadersSource_;
        CppStoredProceduresGenerator storedProcedures_;
        CppStoredProceduresSourceGenerator storedProceduresSource_;
    public:
        using Base = GeneratorContainer<CppGenerator, CppDatabaseOptions>;
        CppDatabaseGenerator( const CppGenerator& owner );

        void Run( )
        {
            databaseReaders_.Run( );
            databaseReadersSource_.Run( );
            complexDatabaseReaders_.Run( );
            complexDatabaseReadersSource_.Run( );
            storedProcedures_.Run( );
            storedProceduresSource_.Run( );
        }
    };

    inline CppDatabaseReadersGenerator::CppDatabaseReadersGenerator( const CppDatabaseGenerator& owner )
        : Base( owner, owner.Options( ).DatabaseReaders( ) )
    {

    }

    inline CppDatabaseReadersSourceGenerator::CppDatabaseReadersSourceGenerator( const CppDatabaseGenerator& owner )
        : Base( owner, owner.Options( ).DatabaseReadersSource( ) )
    {

    }

    inline CppComplexDatabaseReadersGenerator::CppComplexDatabaseReadersGenerator( const CppDatabaseGenerator& owner )
        : Base( owner, owner.Options( ).ComplexDatabaseReaders( ) )
    {

    }

    inline CppComplexDatabaseReadersSourceGenerator::CppComplexDatabaseReadersSourceGenerator( const CppDatabaseGenerator& owner )
        : Base( owner, owner.Options( ).ComplexDatabaseReadersSource( ) )
    {

    }

    inline CppStoredProceduresGenerator::CppStoredProceduresGenerator( const CppDatabaseGenerator& owner )
        : Base( owner, owner.Options( ).StoredProcedures( ) )
    {

    }

    inline CppStoredProceduresSourceGenerator::CppStoredProceduresSourceGenerator( const CppDatabaseGenerator& owner )
        : Base( owner, owner.Options( ).StoredProceduresSource( ) )
    {

    }


    class CppGenerator : public GeneratorContainer<Generator, CppOptions>
    {
        CppDataGenerator data_;
        CppDatabaseGenerator database_;
    public:
        using Base = GeneratorContainer<Generator, CppOptions>;
        CppGenerator( const Generator& owner );

        void Run( )
        {
            data_.Run( );
            database_.Run( );
        }

        const CppDataGenerator& Data( ) const
        {
            return data_;
        }
        const CppDatabaseGenerator& Database( ) const
        {
            return database_;
        }

    };


    inline CppDataGenerator::CppDataGenerator( const CppGenerator& owner )
        : Base( owner, owner.Options().Data() ), enums_(*this), dataTypes_(*this), dataTypesSource_( *this )
    { }

    inline CppDatabaseGenerator::CppDatabaseGenerator( const CppGenerator& owner )
        : Base( owner, owner.Options( ).Database( ) ), databaseReaders_(*this), databaseReadersSource_(*this), complexDatabaseReaders_( *this ), complexDatabaseReadersSource_( *this ), storedProcedures_( *this ), storedProceduresSource_( *this )
    { }

    class CppDataTestGenerator;
    class CppDataTypesTestGenerator : public CodeGenerator<CppDataTestGenerator, CppDataTypesTestOptions>
    {
    public:
        using Base = CodeGenerator<CppDataTestGenerator, CppDataTypesTestOptions>;
        CppDataTypesTestGenerator( const CppDataTestGenerator& owner );

        void Run( );
    private:
        void CreateSerializationTest( const ClassInfo& classInfo );
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
        : Base( owner, owner.Options( ).Data( ) ), dataTypes_(*this)
    {
    }

    inline CppDatabaseTestGenerator::CppDatabaseTestGenerator( const CppTestGenerator& owner )
        : Base( owner, owner.Options( ).Database( ) )
    {
    }


    // ------------------------------------------------------------------------
    // C#
    // ------------------------------------------------------------------------
    class CSharpDatabaseGenerator;
    class CSharpDataGenerator;
    class CSharpGenerator;

    
    class CSharpDatabaseReadersGenerator : public CodeGenerator<CSharpDatabaseGenerator, CSharpDatabaseReadersOptions>
    {
    public:
        using Base = CodeGenerator<CSharpDatabaseGenerator, CSharpDatabaseReadersOptions>;

        inline CSharpDatabaseReadersGenerator( const CSharpDatabaseGenerator& owner );

        void Run( );
    private:
        void CreateReader( const ClassInfo& classInfo );
        void CreateQuery( const ClassInfo& classInfo );
        void CreateFieldIds( const ClassInfo& classInfo );
        void CreateAccessors( const ClassInfo& classInfo );
        void CreateWriteColumns( const ClassInfo& classInfo );
        void CreateGetDataObject( const ClassInfo& classInfo );
    };

    class CSharpComplexDatabaseReadersGenerator : public CodeGenerator<CSharpDatabaseGenerator, CSharpComplexDatabaseReadersOptions>
    {
    public:
        using Base = CodeGenerator<CSharpDatabaseGenerator, CSharpComplexDatabaseReadersOptions>;

        inline CSharpComplexDatabaseReadersGenerator( const CSharpDatabaseGenerator& owner );

        void Run( )
        {
            Flush( );
        }

    };

    class CSharpStoredProceduresGenerator : public CodeGenerator<CSharpDatabaseGenerator, CSharpStoredProceduresOptions>
    {
    public:
        using Base = CodeGenerator<CSharpDatabaseGenerator, CSharpStoredProceduresOptions>;

        inline CSharpStoredProceduresGenerator( const CSharpDatabaseGenerator& owner );

        void Run( );
    private:
        void CreateInsert( const ClassInfo& classInfo );
        void CreateInsertObject( const ClassInfo& classInfo );
        void CreateUpdate( const ClassInfo& classInfo );
        void CreateUpdateObject( const ClassInfo& classInfo );
        void CreateDelete( const ClassInfo& classInfo );
        void CreateDeleteObject( const ClassInfo& classInfo );
        void AddInsertParameter( const MemberInfo& memberInfo );
        void AddUpdateParameter( const MemberInfo& memberInfo );
        void AddDeleteParameter( const MemberInfo& memberInfo );

        void CreateInsertDataObject( );
        void CreateUpdateDataObject( );
        void CreateDeleteDataObject( );
        void CreateMergeDataObject( );
    };

    class CSharpDatabaseGenerator : public GeneratorContainer<CSharpGenerator, CSharpDatabaseOptions>
    {
        CSharpDatabaseReadersGenerator databaseReaders_;
        CSharpComplexDatabaseReadersGenerator complexDatabaseReaders_;
        CSharpStoredProceduresGenerator storedProcedures_;
    public:
        using Base = GeneratorContainer<CSharpGenerator, CSharpDatabaseOptions>;

        inline CSharpDatabaseGenerator( const CSharpGenerator& owner );

        void Run( )
        {
            databaseReaders_.Run( );
            complexDatabaseReaders_.Run( );
            storedProcedures_.Run( );
        }

    };

    inline CSharpDatabaseReadersGenerator::CSharpDatabaseReadersGenerator( const CSharpDatabaseGenerator& owner )
        : Base( owner, owner.Options().DatabaseReaders() )
    { }

    inline CSharpComplexDatabaseReadersGenerator::CSharpComplexDatabaseReadersGenerator( const CSharpDatabaseGenerator& owner )
        : Base( owner, owner.Options( ).ComplexDatabaseReaders( ) )
    {
    }
    inline CSharpStoredProceduresGenerator::CSharpStoredProceduresGenerator( const CSharpDatabaseGenerator& owner )
        : Base( owner, owner.Options( ).StoredProcedures() )
    {
    }



    
    class CSharpEnumsGenerator : public CodeGenerator<CSharpDataGenerator, CSharpEnumsOptions>
    {
    public:
        using Base = CodeGenerator<CSharpDataGenerator, CSharpEnumsOptions>;

        inline CSharpEnumsGenerator( const CSharpDataGenerator& owner );

        void Run( );
    private:
        static WideString GetUnderlyingType( const EnumInfo& enumInfo );
        void CreateEnum( const EnumInfo& enumInfo );
        void CreateKind( );
        
    };

    class CSharpDataTypesGenerator : public CodeGenerator<CSharpDataGenerator, CSharpDataTypesOptions>
    {
    public:
        using Base = CodeGenerator<CSharpDataGenerator, CSharpDataTypesOptions>;

        inline CSharpDataTypesGenerator( const CSharpDataGenerator& owner );

        void Run( );
    private:
        void CreateDataType( const ClassInfo& classInfo );
        void CreateFactory( );
    };

    
    class CSharpDataGenerator : public GeneratorContainer<CSharpGenerator, CSharpDataOptions>
    {
        CSharpEnumsGenerator enums_;
        CSharpDataTypesGenerator dataTypes_;
    public:
        using Base = GeneratorContainer<CSharpGenerator, CSharpDataOptions>;

        inline CSharpDataGenerator( const CSharpGenerator& owner );

        void Run( )
        {
            enums_.Run( );
            dataTypes_.Run( );
        }
    };

    inline CSharpEnumsGenerator::CSharpEnumsGenerator( const CSharpDataGenerator& owner )
        : Base( owner, owner.Options( ).Enums( ) )
    {
    }

    inline CSharpDataTypesGenerator::CSharpDataTypesGenerator( const CSharpDataGenerator& owner )
        : Base(owner, owner.Options().DataTypes())
    { }

    


    class CSharpGenerator : public GeneratorContainer<Generator, CSharpOptions>
    {
        CSharpDataGenerator data_;
        CSharpDatabaseGenerator database_;
    public:
        using Base = GeneratorContainer<Generator, CSharpOptions>;

        inline CSharpGenerator( const Generator& owner );

        void Run( )
        {
            data_.Run( );
            database_.Run( );
        }

    };

    inline CSharpDatabaseGenerator::CSharpDatabaseGenerator( const CSharpGenerator& owner )
        : Base( owner, owner.Options( ).Database( ) ), databaseReaders_(*this), complexDatabaseReaders_(*this), storedProcedures_(*this)
    {
    }

    inline CSharpDataGenerator::CSharpDataGenerator( const CSharpGenerator& owner )
        : Base( owner, owner.Options().Data() ), enums_(*this), dataTypes_(*this)
    { }



    // ------------------------------------------------------------------------
    // Generator
    // ------------------------------------------------------------------------
    class Generator
    {
        const Tool::Options& options_;
        const ModelInfo& model_;
        DatabaseGenerator database_;
        CppGenerator cpp_;
        CppTestGenerator cppTest_;
        CSharpGenerator csharp_;
    public:
        Generator( const Tool::Options& options, const ModelInfo& model )
            : options_( options ), model_( model ), database_( *this ), cpp_(*this), cppTest_(*this), csharp_(*this)
        { }

        const Tool::Options& Options( ) const
        {
            return options_;
        }

        const ModelInfo& Model( ) const
        {
            return model_;
        }

        void Run( )
        {
            database_.Run( );
            cpp_.Run( );
            cppTest_.Run( );
            csharp_.Run( );
        }
    };

    inline DatabaseGenerator::DatabaseGenerator( const Generator& owner )
        : Base( owner, owner.Options( ).Database() ), sqlServer_( *this )
    { }

    inline CppGenerator::CppGenerator( const Generator& owner )
        : Base( owner, owner.Options( ).Cpp( ) ), data_(*this), database_(*this)
    {
    }
    inline CppTestGenerator::CppTestGenerator( const Generator& owner )
        : Base( owner, owner.Options( ).CppTest( ) ), data_( *this ), database_( *this )
    {
    }

    inline CSharpGenerator::CSharpGenerator( const Generator& owner )
        : Base( owner, owner.Options( ).CSharp( ) ), data_( *this ), database_( *this )
    {
    }


}

#endif
