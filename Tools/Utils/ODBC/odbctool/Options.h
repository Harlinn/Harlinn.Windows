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

#include "MemberInfo.h"

namespace Harlinn::ODBC::Tool
{
    class SqlServerCreateTablesOptions;
    class SqlServerOptions;
    class DatabaseOptions;
    class CppDatabaseOptions;
    class CppOptions;
    class CSharpDataOptions;
    class CSharpSqlServerDatabaseOptions;
    class CSharpOptions;
    class Options;

    
    namespace Internal
    {
        template<typename OwnerT>
        WideString GetOutputDirectory( const OwnerT& owner, const WideString& outputDirectory )
        {
            return IO::Path::Combine( owner.OutputDirectory( ), outputDirectory);
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
    private:
        const OwnerType& owner_;
        WideString filename_;
        WideString namespace_;
    public:
        OptionsFile( const OwnerType& owner, const WideString& outputDirectory )
            : owner_( owner ), filename_( outputDirectory )
        {
        }

        OptionsFile( const OwnerType& owner, const WideString& outputDirectory, const WideString& namespaceName )
            : owner_( owner ), filename_( outputDirectory ), namespace_( namespaceName )
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
            return IO::Path::Combine( OutputDirectory( ), filename_ );
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

        const WideString& DllExport( ) const
        {
            return Internal::GetDllExport( owner_ );
        }

    };




    class SqlServerCreateTablesOptions : public OptionsFile<SqlServerOptions>
    {
    public:
        using Base = OptionsFile<SqlServerOptions>;
        SqlServerCreateTablesOptions( const SqlServerOptions& owner )
            : Base( owner, L"MsSqlCreateTables.sql" )
        { }
    };

    class SqlServerCreateViewsOptions : public OptionsFile<SqlServerOptions>
    {
    public:
        using Base = OptionsFile<SqlServerOptions>;
        SqlServerCreateViewsOptions( const SqlServerOptions& owner )
            : Base( owner, L"MsSqlCreateViews.sql" )
        { }
    };

    class SqlServerCreateInsertProceduresOptions : public OptionsFile<SqlServerOptions>
    {
    public:
        using Base = OptionsFile<SqlServerOptions>;
        SqlServerCreateInsertProceduresOptions( const SqlServerOptions& owner )
            : Base( owner, L"MsSqlCreateInsertProcedures.sql" )
        {
        }
    };

    class SqlServerCreateUpdateProceduresOptions : public OptionsFile<SqlServerOptions>
    {
    public:
        using Base = OptionsFile<SqlServerOptions>;
        SqlServerCreateUpdateProceduresOptions( const SqlServerOptions& owner )
            : Base( owner, L"MsSqlCreateUpdateProcedures.sql" )
        {
        }
    };

    class SqlServerCreateDeleteProceduresOptions : public OptionsFile<SqlServerOptions>
    {
    public:
        using Base = OptionsFile<SqlServerOptions>;
        SqlServerCreateDeleteProceduresOptions( const SqlServerOptions& owner )
            : Base( owner, L"MsSqlCreateDeleteProcedures.sql" )
        {
        }
    };


    class SqlServerOptions : public OptionsContainer<DatabaseOptions>
    {
        SqlServerCreateTablesOptions createTables_;
        SqlServerCreateViewsOptions createViews_;
        SqlServerCreateInsertProceduresOptions createInsertProcedures_;
        SqlServerCreateUpdateProceduresOptions createUpdateProcedures_;
        SqlServerCreateDeleteProceduresOptions createDeleteProcedures_;
    public:
        using Base = OptionsContainer<DatabaseOptions>;
        SqlServerOptions( const DatabaseOptions& owner )
            : Base( owner, L"MsSql" ), createTables_(*this), createViews_(*this), createInsertProcedures_(*this), createUpdateProcedures_(*this), createDeleteProcedures_(*this)
        { }

        const SqlServerCreateTablesOptions& CreateTables( ) const
        {
            return createTables_;
        }
        const SqlServerCreateViewsOptions& CreateViews( ) const
        {
            return createViews_;
        }


        const SqlServerCreateInsertProceduresOptions& CreateInsertProcedures( ) const 
        { 
            return createInsertProcedures_; 
        }
        const SqlServerCreateUpdateProceduresOptions& CreateUpdateProcedures( ) const 
        { 
            return createUpdateProcedures_; 
        }
        const SqlServerCreateDeleteProceduresOptions& CreateDeleteProcedures( ) const 
        { 
            return createDeleteProcedures_; 
        }

    };


    
    class DatabaseOptions
    {
        const Options& owner_;
        WideString outputDirectory_ = L"%HCC_HOME%\\Examples\\ODBC\\Barrelman\\Generated\\Database";
        SqlServerOptions sqlServer_;
    public:
        
        DatabaseOptions( const Options& owner )
            : owner_( owner ),sqlServer_(*this)
        { }

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

        const SqlServerOptions& SqlServer( ) const
        {
            return sqlServer_;
        }

        void Load( const XmlElement& element );

    };


    class CppDatabaseReadersOptions : public OptionsFile<CppDatabaseOptions>
    {
    public:
        using Base = OptionsFile<CppDatabaseOptions>;
        CppDatabaseReadersOptions( const CppDatabaseOptions& owner )
            : Base( owner, L"DatabaseReaders.h" )
        { }
    };

    class CppDatabaseReadersSourceOptions : public OptionsFile<CppDatabaseOptions>
    {
    public:
        using Base = OptionsFile<CppDatabaseOptions>;
        CppDatabaseReadersSourceOptions( const CppDatabaseOptions& owner )
            : Base( owner, L"DatabaseReaders.cpp" )
        {
        }
    };


    class CppComplexDatabaseReadersOptions : public OptionsFile<CppDatabaseOptions>
    {
    public:
        using Base = OptionsFile<CppDatabaseOptions>;
        CppComplexDatabaseReadersOptions( const CppDatabaseOptions& owner )
            : Base( owner, L"ComplexDatabaseReaders.h" )
        {
        }
    };

    class CppComplexDatabaseReadersSourceOptions : public OptionsFile<CppDatabaseOptions>
    {
    public:
        using Base = OptionsFile<CppDatabaseOptions>;
        CppComplexDatabaseReadersSourceOptions( const CppDatabaseOptions& owner )
            : Base( owner, L"ComplexDatabaseReaders.cpp" )
        {
        }
    };


    class CppStoredProceduresOptions : public OptionsFile<CppDatabaseOptions>
    {
    public:
        using Base = OptionsFile<CppDatabaseOptions>;
        CppStoredProceduresOptions( const CppDatabaseOptions& owner )
            : Base( owner, L"StoredProcedures.h" )
        {
        }
    };

    class CppStoredProceduresSourceOptions : public OptionsFile<CppDatabaseOptions>
    {
    public:
        using Base = OptionsFile<CppDatabaseOptions>;
        CppStoredProceduresSourceOptions( const CppDatabaseOptions& owner )
            : Base( owner, L"StoredProcedures.cpp" )
        {
        }
    };


    class CppDatabaseOptions : public OptionsContainer<CppOptions>
    {
        CppDatabaseReadersOptions databaseReaders_;
        CppDatabaseReadersSourceOptions databaseReadersSource_;
        CppComplexDatabaseReadersOptions complexDatabaseReaders_;
        CppComplexDatabaseReadersSourceOptions complexDatabaseReadersSource_;
        CppStoredProceduresOptions storedProcedures_;
        CppStoredProceduresSourceOptions storedProceduresSource_;
    public:
        using Base = OptionsContainer<CppOptions>;
        CppDatabaseOptions( const CppOptions& owner )
            : Base( owner, L"Database" ), databaseReaders_(*this), databaseReadersSource_( *this ), complexDatabaseReaders_( *this ), complexDatabaseReadersSource_( *this ), storedProcedures_( *this ), storedProceduresSource_( *this )
        { }

        const CppDatabaseReadersOptions& DatabaseReaders( ) const
        {
            return databaseReaders_;
        }

        const CppDatabaseReadersSourceOptions& DatabaseReadersSource( ) const
        {
            return databaseReadersSource_;
        }

        const CppComplexDatabaseReadersOptions& ComplexDatabaseReaders( ) const
        {
            return complexDatabaseReaders_;
        }

        const CppComplexDatabaseReadersSourceOptions& ComplexDatabaseReadersSource( ) const
        {
            return complexDatabaseReadersSource_;
        }

        const CppStoredProceduresOptions& StoredProcedures( ) const
        {
            return storedProcedures_;
        }
        const CppStoredProceduresSourceOptions& StoredProceduresSource( ) const
        {
            return storedProceduresSource_;
        }

    };

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


    class CppOptions;
    class CppDataOptions : public OptionsContainer<CppOptions>
    {
        CppEnumsOptions enums_;
        CppDataTypesOptions dataTypes_;
        CppDataTypesSourceOptions dataTypesSource_;
    public:
        using Base = OptionsContainer<CppOptions>;
        CppDataOptions( const CppOptions& owner )
            : Base( owner, L"Types" ), enums_(*this), dataTypes_(*this), dataTypesSource_( *this )
        { }

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

    };


    class CppOptions 
    {
        const Options& owner_;
        WideString outputDirectory_ = L"%HCC_HOME%\\Examples\\ODBC\\Barrelman\\Generated\\Cpp";
        WideString namespace_ = L"Barrelman";
        WideString dllexport_ = L"BARRELMAN_EXPORT";
        CppDataOptions data_;
        CppDatabaseOptions database_;
    public:
        using Base = OptionsContainer<Options>;
        CppOptions( const Options& owner )
            : owner_( owner ), data_(*this), database_(*this)
        { }

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


        const CppDataOptions& Data( ) const
        {
            return data_;
        }
        const CppDatabaseOptions& Database( ) const
        {
            return database_;
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
        WideString outputDirectory_ = L"%HCC_HOME%\\Tests\\ODBC\\Barrelman.Tests\\Generated\\Cpp";
        WideString namespace_ = L"Barrelman";
        WideString dllexport_ = L"BARRELMAN_EXPORT";
        CppDataTestOptions data_;
        CppDatabaseTestOptions database_;
    public:
        using Base = OptionsContainer<Options>;
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

    class CSharpSqlServerDatabaseOptions;
    class CSharpSqlServerSimpleDatabaseReadersOptions : public OptionsFile<CSharpSqlServerDatabaseOptions>
    {
    public:
        using Base = OptionsFile<CSharpSqlServerDatabaseOptions>;
        CSharpSqlServerSimpleDatabaseReadersOptions( const CSharpSqlServerDatabaseOptions& owner )
            : Base( owner, L"SqlServerSimpleDatabaseReaders.cs" )
        {
        }
    };


    class CSharpSqlServerComplexDatabaseReadersOptions : public OptionsFile<CSharpSqlServerDatabaseOptions>
    {
    public:
        using Base = OptionsFile<CSharpSqlServerDatabaseOptions>;
        CSharpSqlServerComplexDatabaseReadersOptions( const CSharpSqlServerDatabaseOptions& owner )
            : Base( owner, L"SqlServerComplexDatabaseReaders.cs" )
        {
        }
    };

    class CSharpSqlServerStoredProceduresOptions : public OptionsFile<CSharpSqlServerDatabaseOptions>
    {
    public:
        using Base = OptionsFile<CSharpSqlServerDatabaseOptions>;
        CSharpSqlServerStoredProceduresOptions( const CSharpSqlServerDatabaseOptions& owner )
            : Base( owner, L"SqlServerStoredProcedures.cs" )
        {
        }
    };

    class CSharpSqlServerDataContextOptions : public OptionsFile<CSharpSqlServerDatabaseOptions>
    {
    public:
        using Base = OptionsFile<CSharpSqlServerDatabaseOptions>;
        CSharpSqlServerDataContextOptions( const CSharpSqlServerDatabaseOptions& owner )
            : Base( owner, L"SqlServerDataContext.cs" )
        {
        }
    };



    class CSharpSqlServerDatabaseOptions : public OptionsContainer<CSharpOptions>
    {
        CSharpSqlServerSimpleDatabaseReadersOptions simpleDatabaseReaders_;
        CSharpSqlServerComplexDatabaseReadersOptions complexDatabaseReaders_;
        CSharpSqlServerStoredProceduresOptions storedProcedures_;
        CSharpSqlServerDataContextOptions dataContext_;
    public:
        using Base = OptionsContainer<CSharpOptions>;
        CSharpSqlServerDatabaseOptions( const CSharpOptions& owner )
            : Base( owner, L"Database" ), simpleDatabaseReaders_( *this ), complexDatabaseReaders_( *this ), storedProcedures_( *this ), dataContext_( *this )
        {
        }

        const CSharpSqlServerSimpleDatabaseReadersOptions& DatabaseReaders( ) const
        {
            return simpleDatabaseReaders_;
        }

        const CSharpSqlServerComplexDatabaseReadersOptions& ComplexDatabaseReaders( ) const
        {
            return complexDatabaseReaders_;
        }

        const CSharpSqlServerStoredProceduresOptions& StoredProcedures( ) const
        {
            return storedProcedures_;
        }

        const CSharpSqlServerDataContextOptions& DataContext( ) const
        {
            return dataContext_;
        }

    };


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

        CSharpDataOptions(const CSharpOptions& owner )
            : Base( owner, L"Types" ), enums_( *this ), dataTypes_( *this ), dataContext_( *this )
        { }

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
    public:
        using Base = OptionsContainer<CSharpOptions>;

        CSharpEntitiesOptions( const CSharpOptions& owner )
            : Base( owner, L"Entities" ), entityTypes_( *this ), entityContext_( *this )
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

    };


    class CSharpOptions
    {
        const Options& owner_;
        WideString outputDirectory_ = L"%HCC_HOME%\\DotNet\\Examples\\Barrelman\\Barrelman.Data";
        WideString namespace_ = L"Barrelman";
        CSharpDataOptions data_;
        CSharpSqlServerDatabaseOptions sqlServerDatabase_;
        CSharpEntitiesOptions entities_;
    public:
        CSharpOptions( const Options& owner )
            : owner_( owner ), data_(*this), sqlServerDatabase_(*this ), entities_(*this)
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

        const CSharpSqlServerDatabaseOptions& SqlServerDatabase( ) const
        {
            return sqlServerDatabase_;
        }

        const CSharpEntitiesOptions& Entities( ) const
        {
            return entities_;
        }

        void Load( const XmlElement& element );

    };

    


    class Options
    {
        WideString modelFilename_;
        DatabaseOptions database_;
        CppOptions cpp_;
        CppTestOptions cppTest_;
        CSharpOptions csharp_;
    public:
        Options()
            : database_(*this), cpp_(*this), cppTest_(*this), csharp_( *this )
        { }

        const WideString& ModelFilename( ) const
        {
            return modelFilename_;
        }

        const Tool::DatabaseOptions& Database( ) const
        {
            return database_;
        }

        const CppOptions& Cpp( ) const
        {
            return cpp_;
        }

        const CppTestOptions& CppTest( ) const
        {
            return cppTest_;
        }

        const CSharpOptions& CSharp( ) const
        {
            return csharp_;
        }

        void Load( const XmlElement& element );
        static std::unique_ptr<Options> LoadFromFile( const WideString& optionsFilename );


    };


}

#endif
