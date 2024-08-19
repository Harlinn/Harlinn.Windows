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
    }

    template<typename OwnerT>
    class OptionsContainer
    {
    public:
        using OwnerType = OwnerT;
    private:
        const OwnerType& owner_;
        WideString outputDirectory_;
    public:
        OptionsContainer( const OwnerType& owner, const WideString& outputDirectory )
            : owner_( owner ), outputDirectory_( outputDirectory )
        { }

        const OwnerType& Owner( ) const
        {
            return owner_;
        }

        WideString OutputDirectory( ) const
        {
            return Internal::GetOutputDirectory( owner_, outputDirectory_ );
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
    public:
        OptionsFile( const OwnerType& owner, const WideString& outputDirectory )
            : owner_( owner ), filename_( outputDirectory )
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


    
    class DatabaseOptions : public OptionsContainer<Options>
    {
        SqlServerOptions sqlServer_;
    public:
        using Base = OptionsContainer<Options>;
        DatabaseOptions( const Options& owner )
            : Base(owner, L"Database" ), sqlServer_(*this)
        { }

        const SqlServerOptions& SqlServer( ) const
        {
            return sqlServer_;
        }

    };


    class CppDatabaseReadersOptions : public OptionsFile<CppDatabaseOptions>
    {
    public:
        using Base = OptionsFile<CppDatabaseOptions>;
        CppDatabaseReadersOptions( const CppDatabaseOptions& owner )
            : Base( owner, L"DatabaseReaders.h" )
        { }
    };

    class CppDatabaseOptions : public OptionsContainer<CppOptions>
    {
        CppDatabaseReadersOptions databaseReaders_;
    public:
        using Base = OptionsContainer<CppOptions>;
        CppDatabaseOptions( const CppOptions& owner )
            : Base( owner, L"Database" ), databaseReaders_(*this)
        { }

        const CppDatabaseReadersOptions& DatabaseReaders( ) const
        {
            return databaseReaders_;
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

    class CppOptions;
    class CppDataOptions : public OptionsContainer<CppOptions>
    {
        CppEnumsOptions enums_;
        CppDataTypesOptions dataTypes_;
    public:
        using Base = OptionsContainer<CppOptions>;
        CppDataOptions( const CppOptions& owner )
            : Base( owner, L"Data" ), enums_(*this), dataTypes_(*this)
        { }

        const CppEnumsOptions& Enums( ) const
        {
            return enums_;
        }
        const CppDataTypesOptions& DataTypes( ) const
        {
            return dataTypes_;
        }

    };


    class CppOptions : public OptionsContainer<Options>
    {
        CppDataOptions data_;
        CppDatabaseOptions database_;
    public:
        using Base = OptionsContainer<Options>;
        CppOptions( const Options& owner )
            : Base( owner, L"Cpp" ), data_(*this), database_(*this)
        { }

        const CppDataOptions& Data( ) const
        {
            return data_;
        }
        const CppDatabaseOptions& Database( ) const
        {
            return database_;
        }
    };

    


    class Options
    {
        WideString outputDirectory_ = L"%HCC_HOME%\\Examples\\ODBC\\Barrelman\\Generated";
        DatabaseOptions database_;
        CppOptions cpp_;
    public:
        Options()
            : database_(*this), cpp_(*this)
        { }

        WideString OutputDirectory( ) const
        {
            return Harlinn::Common::Core::Environment::Expand( outputDirectory_ );
        }

        const Tool::DatabaseOptions& Database( ) const
        {
            return database_;
        }

        const CppOptions& Cpp( ) const
        {
            return cpp_;
        }


    };


}

#endif
