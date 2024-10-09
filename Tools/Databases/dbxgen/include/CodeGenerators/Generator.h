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

#include "Metadata/ModelInfo.h"
#include "Options.h"
#include "CodeStream.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators
{


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

        const Metadata::ModelInfo& Model( ) const
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

        const Metadata::ModelInfo& Model( ) const
        {
            return Owner( ).Model( );
        }

    };

    class Generator;
    // ------------------------------------------------------------------------
    // Database
    // ------------------------------------------------------------------------
    namespace Databases
    {
        class DatabasesGenerator;
        namespace MsSql
        {
            class MsSqlGenerator;
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

    namespace Cpp
    {
        class CppGenerator;
        class CppDataGenerator;
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

        namespace Databases
        {

            class CppDatabasesGenerator;
            namespace MsSql
            {
                class CppMsSqlGenerator;
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
                    void CreateUpdate( const Metadata::ClassInfo& classInfo );
                    void CreateDelete( const Metadata::ClassInfo& classInfo );
                };

                class CppMsSqlStoredProceduresSourceGenerator : public CodeGenerator<CppMsSqlGenerator, CppMsSqlStoredProceduresSourceOptions>
                {
                public:
                    using Base = CodeGenerator<CppMsSqlGenerator, CppMsSqlStoredProceduresSourceOptions>;
                    CppMsSqlStoredProceduresSourceGenerator( const CppMsSqlGenerator& owner );

                    void Run( );
                private:
                    void CreateInsert( const Metadata::ClassInfo& classInfo );
                    void CreateUpdate( const Metadata::ClassInfo& classInfo );
                    void CreateDelete( const Metadata::ClassInfo& classInfo );
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

            class CppDatabasesGenerator : public GeneratorContainer<CppGenerator, CppDatabasesOptions>
            {
                MsSql::CppMsSqlGenerator msSql_;
            public:
                using Base = GeneratorContainer<CppGenerator, CppDatabasesOptions>;
                CppDatabasesGenerator( const CppGenerator& owner );

                void Run( )
                {
                    msSql_.Run( );
                }

            };

            namespace MsSql
            {
                inline CppMsSqlGenerator::CppMsSqlGenerator( const CppDatabasesGenerator& owner )
                    : Base( owner, owner.Options( ).MsSql( ) ), simpleDatabaseReaders_( *this ), simpleDatabaseReadersSource_( *this ), complexDatabaseReaders_( *this ), complexDatabaseReadersSource_( *this ), storedProcedures_( *this ), storedProceduresSource_( *this )
                {
                }
            }

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


    // ------------------------------------------------------------------------
    // C#
    // ------------------------------------------------------------------------
    namespace CSharp
    {
        class CSharpDataGenerator;
        class CSharpGenerator;
        namespace Databases
        {
            class CSharpDatabasesGenerator;
            namespace MsSql
            {
                class CSharpMsSqlGenerator;
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

            class CSharpDatabasesGenerator : public GeneratorContainer<CSharpGenerator, CSharpDatabasesOptions>
            {
                MsSql::CSharpMsSqlGenerator msSql_;
            public:
                using Base = GeneratorContainer<CSharpGenerator, CSharpDatabasesOptions>;

                inline CSharpDatabasesGenerator( const CSharpGenerator& owner );

                void Run( )
                {
                    msSql_.Run( );
                }
            };

            namespace MsSql
            {
                inline CSharpMsSqlGenerator::CSharpMsSqlGenerator( const CSharpDatabasesGenerator& owner )
                    : Base( owner, owner.Options( ).MsSql( ) ), databaseReaders_( *this ), complexDatabaseReaders_( *this ), storedProcedures_( *this ), dataContext_( *this ), updateNodes_( *this )
                {
                }
            }

        }


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


    // ------------------------------------------------------------------------
    // Generator
    // ------------------------------------------------------------------------
    class Generator
    {
        const CodeGenerators::Options& options_;
        const Metadata::ModelInfo& model_;
        Databases::DatabasesGenerator databases_;
        Cpp::CppGenerator cpp_;
        Cpp::CppTestGenerator cppTest_;
        CSharp::CSharpGenerator csharp_;
    public:
        Generator( const CodeGenerators::Options& options, const Metadata::ModelInfo& model )
            : options_( options ), model_( model ), databases_( *this ), cpp_(*this), cppTest_(*this), csharp_(*this)
        { }

        const CodeGenerators::Options& Options( ) const
        {
            return options_;
        }

        const Metadata::ModelInfo& Model( ) const
        {
            return model_;
        }

        void Run( )
        {
            databases_.Run( );
            cpp_.Run( );
            cppTest_.Run( );
            csharp_.Run( );
        }
    };

    namespace Databases
    {
        inline DatabasesGenerator::DatabasesGenerator( const Generator& owner )
            : Base( owner, owner.Options( ).Databases( ) ), msSql_( *this )
        {
        }
    }

    namespace Cpp
    {
        inline CppGenerator::CppGenerator( const Generator& owner )
            : Base( owner, owner.Options( ).Cpp( ) ), data_( *this ), databases_( *this )
        {
        }
        inline CppTestGenerator::CppTestGenerator( const Generator& owner )
            : Base( owner, owner.Options( ).CppTest( ) ), data_( *this ), database_( *this )
        {
        }
    }

    namespace CSharp
    {
        inline CSharpGenerator::CSharpGenerator( const Generator& owner )
            : Base( owner, owner.Options( ).CSharp( ) ), data_( *this ), databases_( *this ), entities_( *this )
        {
        }
    }


}

#endif
