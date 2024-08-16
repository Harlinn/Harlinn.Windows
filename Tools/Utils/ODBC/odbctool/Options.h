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


    class SqlServerCreateTablesOptions
    {
        const SqlServerOptions& owner_;
        WideString filename_ = L"MsSqlCreateTables.sql";
    public:
        SqlServerCreateTablesOptions( const SqlServerOptions& owner );

        const SqlServerOptions& Owner( ) const
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

    class SqlServerCreateViewsOptions
    {
        const SqlServerOptions& owner_;
        WideString filename_ = L"MsSqlCreateViews.sql";
    public:
        SqlServerCreateViewsOptions( const SqlServerOptions& owner );

        const SqlServerOptions& Owner( ) const
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

    class SqlServerOptions
    {
        const DatabaseOptions& owner_;
        WideString outputDirectory_ = L"MsSql";
        SqlServerCreateTablesOptions createTables_;
        SqlServerCreateViewsOptions createViews_;
    public:
        SqlServerOptions( const DatabaseOptions& owner );

        const DatabaseOptions& Owner( ) const
        {
            return owner_;
        }

        WideString OutputDirectory( ) const
        {
            return Internal::GetOutputDirectory( owner_, outputDirectory_ );
        }

        const SqlServerCreateTablesOptions& CreateTables( ) const
        {
            return createTables_;
        }
        const SqlServerCreateViewsOptions& CreateViews( ) const
        {
            return createViews_;
        }

    };

    inline SqlServerCreateTablesOptions::SqlServerCreateTablesOptions( const SqlServerOptions& owner )
        : owner_( owner )
    { }

    inline SqlServerCreateViewsOptions::SqlServerCreateViewsOptions( const SqlServerOptions& owner )
        : owner_( owner )
    {
    }

    
    class DatabaseOptions
    {
        const Options& owner_;
        WideString outputDirectory_ = L"Database";
        SqlServerOptions sqlServer_;
    public:
        DatabaseOptions( const Options& owner );

        const Options& Owner( ) const
        {
            return owner_;
        }

        WideString OutputDirectory( ) const
        {
            return Internal::GetOutputDirectory( owner_, outputDirectory_ );
        }

        const SqlServerOptions& SqlServer( ) const
        {
            return sqlServer_;
        }

    };

    inline SqlServerOptions::SqlServerOptions( const DatabaseOptions& owner )
        : owner_( owner ), createTables_(*this), createViews_(*this)
    {
    }

    class Options
    {
        WideString outputDirectory_ = L"%HCC_HOME%\\Tools\\Utils\\ODBC\\odbctool\\Generated Files";
        DatabaseOptions database_;
    public:
        Options()
            : database_(*this)
        { }

        WideString OutputDirectory( ) const
        {
            return Harlinn::Common::Core::Environment::Expand( outputDirectory_ );
        }

        const Tool::DatabaseOptions& Database( ) const
        {
            return database_;
        }

    };

    inline DatabaseOptions::DatabaseOptions( const Options& owner )
        : owner_( owner ), sqlServer_(*this)
    { }

}

#endif
