#pragma once
#ifndef ODBCTOOLOPTIONS_H_
#define ODBCTOOLOPTIONS_H_
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

#include <HCCXml.h>
#include <HCCIO.h>
#include <HCCEnvironment.h>

namespace Harlinn::Tools::DbXGen
{
    using namespace Harlinn::Common::Core;
}

namespace Harlinn::Tools::DbXGen::CodeGenerators
{

    
    namespace Internal
    {
        template<typename OwnerT>
        WideString GetOutputDirectory( const OwnerT& owner, const WideString& outputDirectory )
        {
            return IO::Path::Combine<WideString>( owner.OutputDirectory( ), outputDirectory);
        }



        template<typename OwnerT>
        WideString GetOutputDirectory( const OwnerT& owner )
        {
            return owner.OutputDirectory( );
        }

        template<typename OwnerT>
        WideString GetNamespace( const WideString& separator, const OwnerT& owner, const WideString& namespaceName )
        {
            return Format( L"{}{}{}", owner.Namespace( separator ), separator, namespaceName );
        }

        template<typename OwnerT>
        WideString GetNamespace( const WideString& separator, const OwnerT& owner )
        {
            return owner.Namespace( separator );
        }

        template<typename OwnerT>
        const WideString& GetDllExport( const OwnerT& owner )
        {
            return owner.DllExport( );
        }

    }

    template<typename OwnerT>
    class OptionsContainer
    {
    public:
        using OwnerType = OwnerT;
        using XmlElement = Common::Core::Xml::Dom::Element;
    private:
        const OwnerType& owner_;
        WideString outputDirectory_;
        WideString namespace_;
    public:
        OptionsContainer( const OwnerType& owner, const WideString& outputDirectory )
            : owner_( owner ), outputDirectory_( outputDirectory )
        { }

        OptionsContainer( const OwnerType& owner, const WideString& outputDirectory, const WideString& namespaceName )
            : owner_( owner ), outputDirectory_( outputDirectory ), namespace_( namespaceName )
        {
        }

        OptionsContainer( const OwnerType& owner, const wchar_t* outputDirectory )
            : owner_( owner ), outputDirectory_( outputDirectory )
        {
        }

        OptionsContainer( const OwnerType& owner, const wchar_t* outputDirectory, const wchar_t* namespaceName )
            : owner_( owner ), outputDirectory_( outputDirectory ), namespace_( namespaceName )
        {
        }

        const OwnerType& Owner( ) const
        {
            return owner_;
        }

        WideString OutputDirectory( ) const
        {
            return Internal::GetOutputDirectory( owner_, outputDirectory_ );
        }

        WideString Namespace( const WideString& separator ) const
        {
            if ( namespace_ )
            {
                return Internal::GetNamespace( separator, owner_, namespace_ );
            }
            else
            {
                return Internal::GetNamespace( separator, owner_, outputDirectory_ );
            }
        }

        WideString Namespace( const wchar_t* separator ) const
        {
            return Namespace( WideString( separator ) );
        }

        const WideString& DllExport( ) const
        {
            return Internal::GetDllExport( owner_ );
        }

    };

    template<typename OwnerT>
    class OptionsFile
    {
    public:
        using OwnerType = OwnerT;
        using XmlElement = Common::Core::Xml::Dom::Element;
    private:
        const OwnerType& owner_;
        WideString filename_;
        WideString namespace_;
    public:
        OptionsFile( const OwnerType& owner, const WideString& filename )
            : owner_( owner ), filename_( filename )
        {
        }

        OptionsFile( const OwnerType& owner, const WideString& filename, const WideString& namespaceName )
            : owner_( owner ), filename_( filename ), namespace_( namespaceName )
        {
        }

        OptionsFile( const OwnerType& owner, const wchar_t* filename )
            : owner_( owner ), filename_( filename )
        {
        }

        OptionsFile( const OwnerType& owner, const wchar_t* filename, const wchar_t* namespaceName )
            : owner_( owner ), filename_( filename ), namespace_( namespaceName )
        {
        }

        const OwnerType& Owner( ) const
        {
            return owner_;
        }

        WideString OutputDirectory( ) const
        {
            return Internal::GetOutputDirectory( owner_ );
        }

        WideString Filename( ) const
        {
            WideString outputDirectory(OutputDirectory( ));
            return IO::Path::Combine<WideString>( outputDirectory, filename_ );
        }

        WideString Namespace( const WideString& separator ) const
        {
            if ( namespace_ )
            {
                return Internal::GetNamespace( separator, owner_, namespace_ );
            }
            else
            {
                return Internal::GetNamespace( separator, owner_ );
            }
        }
        WideString Namespace( const wchar_t* separator ) const
        {
            return Namespace( WideString( separator ) );
        }


        const WideString& DllExport( ) const
        {
            return Internal::GetDllExport( owner_ );
        }

    };

    class Options;
    namespace Databases
    {
        class DatabasesOptions;
        namespace MsSql
        {
            class MsSqlOptions;

            class MsSqlCreateTablesOptions : public OptionsFile<MsSqlOptions>
            {
            public:
                using Base = OptionsFile<MsSqlOptions>;
                MsSqlCreateTablesOptions( const MsSqlOptions& owner )
                    : Base( owner, L"MsSqlCreateTables.sql" )
                {
                }
            };

            class MsSqlCreateViewsOptions : public OptionsFile<MsSqlOptions>
            {
            public:
                using Base = OptionsFile<MsSqlOptions>;
                MsSqlCreateViewsOptions( const MsSqlOptions& owner )
                    : Base( owner, L"MsSqlCreateViews.sql" )
                {
                }
            };

            class MsSqlCreateInsertProceduresOptions : public OptionsFile<MsSqlOptions>
            {
            public:
                using Base = OptionsFile<MsSqlOptions>;
                MsSqlCreateInsertProceduresOptions( const MsSqlOptions& owner )
                    : Base( owner, L"MsSqlCreateInsertProcedures.sql" )
                {
                }
            };

            class MsSqlCreateUpdateProceduresOptions : public OptionsFile<MsSqlOptions>
            {
            public:
                using Base = OptionsFile<MsSqlOptions>;
                MsSqlCreateUpdateProceduresOptions( const MsSqlOptions& owner )
                    : Base( owner, L"MsSqlCreateUpdateProcedures.sql" )
                {
                }
            };

            class MsSqlCreateDeleteProceduresOptions : public OptionsFile<MsSqlOptions>
            {
            public:
                using Base = OptionsFile<MsSqlOptions>;
                MsSqlCreateDeleteProceduresOptions( const MsSqlOptions& owner )
                    : Base( owner, L"MsSqlCreateDeleteProcedures.sql" )
                {
                }
            };


            class MsSqlOptions : public OptionsContainer<DatabasesOptions>
            {
                MsSqlCreateTablesOptions createTables_;
                MsSqlCreateViewsOptions createViews_;
                MsSqlCreateInsertProceduresOptions createInsertProcedures_;
                MsSqlCreateUpdateProceduresOptions createUpdateProcedures_;
                MsSqlCreateDeleteProceduresOptions createDeleteProcedures_;
            public:
                using Base = OptionsContainer<DatabasesOptions>;
                MsSqlOptions( const DatabasesOptions& owner )
                    : Base( owner, L"MsSql" ), createTables_( *this ), createViews_( *this ), createInsertProcedures_( *this ), createUpdateProcedures_( *this ), createDeleteProcedures_( *this )
                {
                }

                const MsSqlCreateTablesOptions& CreateTables( ) const
                {
                    return createTables_;
                }
                const MsSqlCreateViewsOptions& CreateViews( ) const
                {
                    return createViews_;
                }


                const MsSqlCreateInsertProceduresOptions& CreateInsertProcedures( ) const
                {
                    return createInsertProcedures_;
                }
                const MsSqlCreateUpdateProceduresOptions& CreateUpdateProcedures( ) const
                {
                    return createUpdateProcedures_;
                }
                const MsSqlCreateDeleteProceduresOptions& CreateDeleteProcedures( ) const
                {
                    return createDeleteProcedures_;
                }
            };
        }



        class DatabasesOptions
        {
            const Options& owner_;
            WideString outputDirectory_;
            MsSql::MsSqlOptions msSql_;
        public:
            using XmlElement = Common::Core::Xml::Dom::Element;

            DatabasesOptions( const Options& owner )
                : owner_( owner ), msSql_( *this )
            {
            }

            const Options& Owner( ) const
            {
                return owner_;
            }

            WideString OutputDirectory( ) const
            {
                return Harlinn::Common::Core::Environment::Expand( outputDirectory_ );
            }

            WideString Namespace( const WideString& separator ) const
            {
                return {};
            }

            const MsSql::MsSqlOptions& MsSql( ) const
            {
                return msSql_;
            }

            void Load( const XmlElement& element );

        };
    }


    namespace Cpp
    {
        class CppOptions;
        namespace Databases
        {
            class CppDatabasesOptions;
            namespace MsSql
            {
                class CppMsSqlOptions;

                class CppMsSqlSimpleDatabaseReadersOptions : public OptionsFile<CppMsSqlOptions>
                {
                public:
                    using Base = OptionsFile<CppMsSqlOptions>;
                    CppMsSqlSimpleDatabaseReadersOptions( const CppMsSqlOptions& owner )
                        : Base( owner, L"MsSqlSimpleDatabaseReaders.h" )
                    {
                    }
                };

                class CppMsSqlSimpleDatabaseReadersSourceOptions : public OptionsFile<CppMsSqlOptions>
                {
                public:
                    using Base = OptionsFile<CppMsSqlOptions>;
                    CppMsSqlSimpleDatabaseReadersSourceOptions( const CppMsSqlOptions& owner )
                        : Base( owner, L"MsSqlSimpleDatabaseReaders.cpp" )
                    {
                    }
                };


                class CppMsSqlComplexDatabaseReadersOptions : public OptionsFile<CppMsSqlOptions>
                {
                public:
                    using Base = OptionsFile<CppMsSqlOptions>;
                    CppMsSqlComplexDatabaseReadersOptions( const CppMsSqlOptions& owner )
                        : Base( owner, L"MsSqlComplexDatabaseReaders.h" )
                    {
                    }
                };

                class CppMsSqlComplexDatabaseReadersSourceOptions : public OptionsFile<CppMsSqlOptions>
                {
                public:
                    using Base = OptionsFile<CppMsSqlOptions>;
                    CppMsSqlComplexDatabaseReadersSourceOptions( const CppMsSqlOptions& owner )
                        : Base( owner, L"MsSqlComplexDatabaseReaders.cpp" )
                    {
                    }
                };


                class CppMsSqlStoredProceduresOptions : public OptionsFile<CppMsSqlOptions>
                {
                public:
                    using Base = OptionsFile<CppMsSqlOptions>;
                    CppMsSqlStoredProceduresOptions( const CppMsSqlOptions& owner )
                        : Base( owner, L"MsSqlStoredProcedures.h" )
                    {
                    }
                };

                class CppMsSqlStoredProceduresSourceOptions : public OptionsFile<CppMsSqlOptions>
                {
                public:
                    using Base = OptionsFile<CppMsSqlOptions>;
                    CppMsSqlStoredProceduresSourceOptions( const CppMsSqlOptions& owner )
                        : Base( owner, L"MsSqlStoredProcedures.cpp" )
                    {
                    }
                };


                class CppMsSqlOptions : public OptionsContainer<CppDatabasesOptions>
                {
                    CppMsSqlSimpleDatabaseReadersOptions simpleDatabaseReaders_;
                    CppMsSqlSimpleDatabaseReadersSourceOptions simpleDatabaseReadersSource_;
                    CppMsSqlComplexDatabaseReadersOptions complexDatabaseReaders_;
                    CppMsSqlComplexDatabaseReadersSourceOptions complexDatabaseReadersSource_;
                    CppMsSqlStoredProceduresOptions storedProcedures_;
                    CppMsSqlStoredProceduresSourceOptions storedProceduresSource_;
                public:
                    using Base = OptionsContainer<CppDatabasesOptions>;
                    CppMsSqlOptions( const CppDatabasesOptions& owner )
                        : Base( owner, L"MsSql" ), simpleDatabaseReaders_( *this ), simpleDatabaseReadersSource_( *this ), complexDatabaseReaders_( *this ), complexDatabaseReadersSource_( *this ), storedProcedures_( *this ), storedProceduresSource_( *this )
                    {
                    }

                    const CppMsSqlSimpleDatabaseReadersOptions& SimpleDatabaseReaders( ) const
                    {
                        return simpleDatabaseReaders_;
                    }

                    const CppMsSqlSimpleDatabaseReadersSourceOptions& SimpleDatabaseReadersSource( ) const
                    {
                        return simpleDatabaseReadersSource_;
                    }

                    const CppMsSqlComplexDatabaseReadersOptions& ComplexDatabaseReaders( ) const
                    {
                        return complexDatabaseReaders_;
                    }

                    const CppMsSqlComplexDatabaseReadersSourceOptions& ComplexDatabaseReadersSource( ) const
                    {
                        return complexDatabaseReadersSource_;
                    }

                    const CppMsSqlStoredProceduresOptions& StoredProcedures( ) const
                    {
                        return storedProcedures_;
                    }
                    const CppMsSqlStoredProceduresSourceOptions& StoredProceduresSource( ) const
                    {
                        return storedProceduresSource_;
                    }

                };
            }

            class CppDatabasesOptions : public OptionsContainer<CppOptions>
            {
                MsSql::CppMsSqlOptions msSql_;
            public:
                using Base = OptionsContainer<CppOptions>;

                CppDatabasesOptions( const CppOptions& owner )
                    : Base( owner, L"Databases" ), msSql_( *this )
                {

                }

                const MsSql::CppMsSqlOptions& MsSql( ) const
                {
                    return msSql_;
                }

            };
        }

        class CppDataOptions;
        class CppEnumsOptions : public OptionsFile<CppDataOptions>
        {
        public:
            using Base = OptionsFile<CppDataOptions>;
            CppEnumsOptions( const CppDataOptions& owner )
                : Base( owner, L"Enums.h" )
            {
            }
        };

        class CppDataTypesOptions : public OptionsFile<CppDataOptions>
        {
        public:
            using Base = OptionsFile<CppDataOptions>;
            CppDataTypesOptions( const CppDataOptions& owner )
                : Base( owner, L"DataTypes.h" )
            {
            }

        };

        class CppDataTypesSourceOptions : public OptionsFile<CppDataOptions>
        {
        public:
            using Base = OptionsFile<CppDataOptions>;
            CppDataTypesSourceOptions( const CppDataOptions& owner )
                : Base( owner, L"DataTypes.cpp" )
            {
            }
        };

        class CppIDataContextOptions : public OptionsFile<CppDataOptions>
        {
        public:
            using Base = OptionsFile<CppDataOptions>;
            CppIDataContextOptions( const CppDataOptions& owner )
                : Base( owner, L"IDataContext.h" )
            {
            }
        };



        class CppOptions;
        class CppDataOptions : public OptionsContainer<CppOptions>
        {
            CppEnumsOptions enums_;
            CppDataTypesOptions dataTypes_;
            CppDataTypesSourceOptions dataTypesSource_;
            CppIDataContextOptions dataContext_;
        public:
            using Base = OptionsContainer<CppOptions>;
            CppDataOptions( const CppOptions& owner )
                : Base( owner, L"Types" ), enums_( *this ), dataTypes_( *this ), dataTypesSource_( *this ), dataContext_( *this )
            {
            }

            const CppEnumsOptions& Enums( ) const
            {
                return enums_;
            }
            const CppDataTypesOptions& DataTypes( ) const
            {
                return dataTypes_;
            }

            const CppDataTypesSourceOptions& DataTypesSource( ) const
            {
                return dataTypesSource_;
            }

            const CppIDataContextOptions& DataContext( ) const
            {
                return dataContext_;
            }

        };


        class CppOptions
        {
            const Options& owner_;
            WideString outputDirectory_;
            WideString namespace_;
            WideString dllexport_;
            CppDataOptions data_;
            Databases::CppDatabasesOptions databases_;
        public:
            using Base = OptionsContainer<Options>;
            using XmlElement = Common::Core::Xml::Dom::Element;
            CppOptions( const Options& owner )
                : owner_( owner ), data_( *this ), databases_( *this )
            {
            }

            const Options& Owner( ) const
            {
                return owner_;
            }

            WideString OutputDirectory( ) const
            {
                return Harlinn::Common::Core::Environment::Expand( outputDirectory_ );
            }

            WideString Namespace( const WideString& separator ) const
            {
                return namespace_;
            }

            WideString Namespace( const wchar_t* separator ) const
            {
                return namespace_;
            }

            const WideString& DllExport( ) const
            {
                return dllexport_;
            }


            const CppDataOptions& Data( ) const
            {
                return data_;
            }
            const Databases::CppDatabasesOptions& Databases( ) const
            {
                return databases_;
            }

            void Load( const XmlElement& element );
        };


        class CppDataTestOptions;
        class CppDataTypesTestOptions : public OptionsFile<CppDataTestOptions>
        {
        public:
            using Base = OptionsFile<CppDataTestOptions>;
            CppDataTypesTestOptions( const CppDataTestOptions& owner )
                : Base( owner, L"DataTypesTests.cpp" )
            {
            }
        };

        class CppTestOptions;
        class CppDataTestOptions : public OptionsContainer<CppTestOptions>
        {
            CppDataTypesTestOptions dataTypes_;
        public:
            using Base = OptionsContainer<CppTestOptions>;
            CppDataTestOptions( const CppTestOptions& owner )
                : Base( owner, L"Types" ), dataTypes_( *this )
            {
            }

            const CppDataTypesTestOptions& DataTypes( ) const
            {
                return dataTypes_;
            }
        };

        class CppDatabaseTestOptions : public OptionsContainer<CppTestOptions>
        {
        public:
            using Base = OptionsContainer<CppTestOptions>;
            CppDatabaseTestOptions( const CppTestOptions& owner )
                : Base( owner, L"Database" )
            {
            }

        };


        class CppTestOptions
        {
            const Options& owner_;
            WideString outputDirectory_{ L"%HCC_HOME%\\Tests\\ODBC\\Barrelman.Tests\\Generated\\Cpp" };
            WideString namespace_{ L"Barrelman" };
            WideString dllexport_{ L"BARRELMAN_EXPORT" };
            CppDataTestOptions data_;
            CppDatabaseTestOptions database_;
        public:
            using Base = OptionsContainer<Options>;

            using XmlElement = Common::Core::Xml::Dom::Element;

            CppTestOptions( const Options& owner )
                : owner_( owner ), data_( *this ), database_( *this )
            {
            }

            const Options& Owner( ) const
            {
                return owner_;
            }

            WideString OutputDirectory( ) const
            {
                return Harlinn::Common::Core::Environment::Expand( outputDirectory_ );
            }

            WideString Namespace( const WideString& separator ) const
            {
                return namespace_;
            }

            const WideString& DllExport( ) const
            {
                return dllexport_;
            }


            const CppDataTestOptions& Data( ) const
            {
                return data_;
            }
            const CppDatabaseTestOptions& Database( ) const
            {
                return database_;
            }

            void Load( const XmlElement& element );
        };
    }

    namespace CSharp
    {
        class CSharpOptions;

        namespace Databases
        {
            class CSharpDatabasesOptions;
            namespace MsSql
            {
                class CSharpMsSqlOptions;
                class CSharpMsSqlSimpleDatabaseReadersOptions : public OptionsFile<CSharpMsSqlOptions>
                {
                public:
                    using Base = OptionsFile<CSharpMsSqlOptions>;
                    CSharpMsSqlSimpleDatabaseReadersOptions( const CSharpMsSqlOptions& owner )
                        : Base( owner, L"MsSqlSimpleDatabaseReaders.cs" )
                    {
                    }
                };


                class CSharpMsSqlComplexDatabaseReadersOptions : public OptionsFile<CSharpMsSqlOptions>
                {
                public:
                    using Base = OptionsFile<CSharpMsSqlOptions>;
                    CSharpMsSqlComplexDatabaseReadersOptions( const CSharpMsSqlOptions& owner )
                        : Base( owner, L"MsSqlComplexDatabaseReaders.cs" )
                    {
                    }
                };

                class CSharpMsSqlStoredProceduresOptions : public OptionsFile<CSharpMsSqlOptions>
                {
                public:
                    using Base = OptionsFile<CSharpMsSqlOptions>;
                    CSharpMsSqlStoredProceduresOptions( const CSharpMsSqlOptions& owner )
                        : Base( owner, L"MsSqlStoredProcedures.cs" )
                    {
                    }
                };

                class CSharpMsSqlDataContextOptions : public OptionsFile<CSharpMsSqlOptions>
                {
                public:
                    using Base = OptionsFile<CSharpMsSqlOptions>;
                    CSharpMsSqlDataContextOptions( const CSharpMsSqlOptions& owner )
                        : Base( owner, L"MsSqlDataContext.cs" )
                    {
                    }
                };

                class CSharpMsSqlUpdateNodesOptions : public OptionsFile<CSharpMsSqlOptions>
                {
                public:
                    using Base = OptionsFile<CSharpMsSqlOptions>;
                    CSharpMsSqlUpdateNodesOptions( const CSharpMsSqlOptions& owner )
                        : Base( owner, L"MsSqlUpdateNodes.cs" )
                    {
                    }
                };



                class CSharpMsSqlOptions : public OptionsContainer<CSharpDatabasesOptions>
                {
                    CSharpMsSqlSimpleDatabaseReadersOptions simpleDatabaseReaders_;
                    CSharpMsSqlComplexDatabaseReadersOptions complexDatabaseReaders_;
                    CSharpMsSqlStoredProceduresOptions storedProcedures_;
                    CSharpMsSqlDataContextOptions dataContext_;
                    CSharpMsSqlUpdateNodesOptions updateNodes_;
                public:
                    using Base = OptionsContainer<CSharpDatabasesOptions>;
                    CSharpMsSqlOptions( const CSharpDatabasesOptions& owner )
                        : Base( owner, L"MsSql" ), simpleDatabaseReaders_( *this ), complexDatabaseReaders_( *this ), storedProcedures_( *this ), dataContext_( *this ), updateNodes_( *this )
                    {
                    }

                    const CSharpMsSqlSimpleDatabaseReadersOptions& DatabaseReaders( ) const
                    {
                        return simpleDatabaseReaders_;
                    }

                    const CSharpMsSqlComplexDatabaseReadersOptions& ComplexDatabaseReaders( ) const
                    {
                        return complexDatabaseReaders_;
                    }

                    const CSharpMsSqlStoredProceduresOptions& StoredProcedures( ) const
                    {
                        return storedProcedures_;
                    }

                    const CSharpMsSqlDataContextOptions& DataContext( ) const
                    {
                        return dataContext_;
                    }

                    const CSharpMsSqlUpdateNodesOptions& UpdateNodes( ) const
                    {
                        return updateNodes_;
                    }

                };
            }

            class CSharpDatabasesOptions : public OptionsContainer<CSharpOptions>
            {
                MsSql::CSharpMsSqlOptions msSql_;
            public:
                using Base = OptionsContainer<CSharpOptions>;
                CSharpDatabasesOptions( const CSharpOptions& owner )
                    : Base( owner, L"Databases" ), msSql_( *this )
                {
                }

                const MsSql::CSharpMsSqlOptions& MsSql( ) const
                {
                    return msSql_;
                }
            };
        }


        class CSharpDataOptions;

        class CSharpEnumsOptions : public OptionsFile<CSharpDataOptions>
        {
        public:
            using Base = OptionsFile<CSharpDataOptions>;
            CSharpEnumsOptions( const CSharpDataOptions& owner )
                : Base( owner, L"Enums.cs" )
            {
            }
        };

        class CSharpDataTypesOptions : public OptionsFile<CSharpDataOptions>
        {
        public:
            using Base = OptionsFile<CSharpDataOptions>;
            CSharpDataTypesOptions( const CSharpDataOptions& owner )
                : Base( owner, L"DataTypes.cs" )
            {
            }
        };

        class CSharpIDataContextOptions : public OptionsFile<CSharpDataOptions>
        {
        public:
            using Base = OptionsFile<CSharpDataOptions>;
            CSharpIDataContextOptions( const CSharpDataOptions& owner )
                : Base( owner, L"IDataContext.cs" )
            {
            }
        };




        class CSharpDataOptions : public OptionsContainer<CSharpOptions>
        {
            CSharpEnumsOptions enums_;
            CSharpDataTypesOptions dataTypes_;
            CSharpIDataContextOptions dataContext_;
        public:
            using Base = OptionsContainer<CSharpOptions>;

            CSharpDataOptions( const CSharpOptions& owner )
                : Base( owner, L"Types" ), enums_( *this ), dataTypes_( *this ), dataContext_( *this )
            {
            }

            const CSharpEnumsOptions& Enums( ) const
            {
                return enums_;
            }
            const CSharpDataTypesOptions& DataTypes( ) const
            {
                return dataTypes_;
            }

            const CSharpIDataContextOptions& DataContext( ) const
            {
                return dataContext_;
            }

        };

        class CSharpEntitiesOptions;
        class CSharpEntityTypesOptions : public OptionsFile<CSharpEntitiesOptions>
        {
        public:
            using Base = OptionsFile<CSharpEntitiesOptions>;
            CSharpEntityTypesOptions( const CSharpEntitiesOptions& owner )
                : Base( owner, L"EntityTypes.cs" )
            {
            }
        };

        class CSharpEntityChangesOptions : public OptionsFile<CSharpEntitiesOptions>
        {
        public:
            using Base = OptionsFile<CSharpEntitiesOptions>;
            CSharpEntityChangesOptions( const CSharpEntitiesOptions& owner )
                : Base( owner, L"EntityChanges.cs" )
            {
            }
        };

        class CSharpEntityContextOptions : public OptionsFile<CSharpEntitiesOptions>
        {
        public:
            using Base = OptionsFile<CSharpEntitiesOptions>;
            CSharpEntityContextOptions( const CSharpEntitiesOptions& owner )
                : Base( owner, L"EntityContext.cs" )
            {
            }
        };


        class CSharpEntitiesOptions : public OptionsContainer<CSharpOptions>
        {
            CSharpEntityTypesOptions entityTypes_;
            CSharpEntityContextOptions entityContext_;
            CSharpEntityChangesOptions entityChanges_;
        public:
            using Base = OptionsContainer<CSharpOptions>;

            CSharpEntitiesOptions( const CSharpOptions& owner )
                : Base( owner, L"Entities" ), entityTypes_( *this ), entityContext_( *this ), entityChanges_( *this )
            {
            }

            const CSharpEntityTypesOptions& EntityTypes( ) const
            {
                return entityTypes_;
            }

            const CSharpEntityContextOptions& EntityContext( ) const
            {
                return entityContext_;
            }

            const CSharpEntityChangesOptions& EntityChanges( ) const
            {
                return entityChanges_;
            }

        };


        class CSharpOptions
        {
            const Options& owner_;
            WideString outputDirectory_{ L"%HCC_HOME%\\DotNet\\Examples\\Barrelman\\Barrelman.Data" };
            WideString namespace_{ L"Barrelman" };
            CSharpDataOptions data_;
            Databases::CSharpDatabasesOptions databases_;
            CSharpEntitiesOptions entities_;
        public:
            using XmlElement = Common::Core::Xml::Dom::Element;

            CSharpOptions( const Options& owner )
                : owner_( owner ), data_( *this ), databases_( *this ), entities_( *this )
            {
            }

            const Options& Owner( ) const
            {
                return owner_;
            }

            WideString OutputDirectory( ) const
            {
                return Harlinn::Common::Core::Environment::Expand( outputDirectory_ );
            }

            WideString Namespace( const WideString& separator ) const
            {
                return namespace_;
            }

            const CSharpDataOptions& Data( ) const
            {
                return data_;
            }

            const Databases::CSharpDatabasesOptions& Databases( ) const
            {
                return databases_;
            }

            const CSharpEntitiesOptions& Entities( ) const
            {
                return entities_;
            }

            void Load( const XmlElement& element );

        };
    }

    


    class Options
    {
        WideString modelFilename_;
        Databases::DatabasesOptions databases_;
        Cpp::CppOptions cpp_;
        Cpp::CppTestOptions cppTest_;
        CSharp::CSharpOptions csharp_;
    public:
        using XmlElement = Common::Core::Xml::Dom::Element;
        Options()
            : databases_(*this), cpp_(*this), cppTest_(*this), csharp_( *this )
        { }

        const WideString& ModelFilename( ) const
        {
            return modelFilename_;
        }

        const Databases::DatabasesOptions& Databases( ) const
        {
            return databases_;
        }

        const Cpp::CppOptions& Cpp( ) const
        {
            return cpp_;
        }

        const Cpp::CppTestOptions& CppTest( ) const
        {
            return cppTest_;
        }

        const CSharp::CSharpOptions& CSharp( ) const
        {
            return csharp_;
        }

        void Load( const XmlElement& element );
        static std::unique_ptr<Options> LoadFromFile( const WideString& optionsFilename );


    };


}

#endif
