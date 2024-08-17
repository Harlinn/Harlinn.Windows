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
    class Generator;
    

    class SqlServerCreateTablesGenerator : CodeStream
    {
        const SqlServerGenerator& owner_;
        const Tool::SqlServerCreateTablesOptions options_;
    public:
        using Base = CodeStream;
        SqlServerCreateTablesGenerator( const SqlServerGenerator& owner );

        const SqlServerGenerator& Owner( ) const
        {
            return owner_;
        }

        const Tool::SqlServerCreateTablesOptions& Options( ) const
        {
            return options_;
        }

        const ModelInfo& Model( ) const;

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

    class SqlServerCreateViewsGenerator : CodeStream
    {
        const SqlServerGenerator& owner_;
        const Tool::SqlServerCreateViewsOptions options_;
    public:
        using Base = CodeStream;
        SqlServerCreateViewsGenerator( const SqlServerGenerator& owner );

        const SqlServerGenerator& Owner( ) const
        {
            return owner_;
        }

        const Tool::SqlServerCreateViewsOptions& Options( ) const
        {
            return options_;
        }

        const ModelInfo& Model( ) const;

        void Run( );
    private:
        static WideString GetFieldNameForSelect( const MemberInfo& memberInfo );
        void CreateTopLevelView( const ClassInfo& classInfo );
        void CreateView( const ClassInfo& classInfo );
    };

    class SqlServerCreateInsertProceduresGenerator : CodeStream
    {
        const SqlServerGenerator& owner_;
        const Tool::SqlServerCreateInsertProceduresOptions options_;
    public:
        using Base = CodeStream;
        SqlServerCreateInsertProceduresGenerator( const SqlServerGenerator& owner );

        const SqlServerGenerator& Owner( ) const
        {
            return owner_;
        }

        const Tool::SqlServerCreateInsertProceduresOptions& Options( ) const
        {
            return options_;
        }

        const ModelInfo& Model( ) const;

        void Run( );
    private:
        static WideString GetProcedureParameters( const ClassInfo& classInfo );
        static WideString GetInsertStatement( const ClassInfo& classInfo );
        static WideString GetInsertProcedure( const ClassInfo& classInfo );
        static WideString GetInsertTrigger( const ClassInfo& classInfo );
        void CreateInsertProcedure( const ClassInfo& classInfo );
        void CreateInsertTrigger( const ClassInfo& classInfo );
    };


    class SqlServerCreateUpdateProceduresGenerator : CodeStream
    {
        const SqlServerGenerator& owner_;
        const Tool::SqlServerCreateUpdateProceduresOptions options_;
    public:
        using Base = CodeStream;
        SqlServerCreateUpdateProceduresGenerator( const SqlServerGenerator& owner );

        const SqlServerGenerator& Owner( ) const
        {
            return owner_;
        }

        const Tool::SqlServerCreateUpdateProceduresOptions& Options( ) const
        {
            return options_;
        }

        const ModelInfo& Model( ) const;

        void Run( );
    private:
        static WideString GetProcedureParameters( const ClassInfo& classInfo );
        static WideString GetTopLevelUpdateStatement( const ClassInfo& classInfo );
        static WideString GetUpdateStatement( const ClassInfo& classInfo );
        void CreateUpdateStatement( const ClassInfo& classInfo );

    };

    class SqlServerCreateDeleteProceduresGenerator : CodeStream
    {
        const SqlServerGenerator& owner_;
        const Tool::SqlServerCreateDeleteProceduresOptions options_;
    public:
        using Base = CodeStream;
        SqlServerCreateDeleteProceduresGenerator( const SqlServerGenerator& owner );

        const SqlServerGenerator& Owner( ) const
        {
            return owner_;
        }

        const Tool::SqlServerCreateDeleteProceduresOptions& Options( ) const
        {
            return options_;
        }

        const ModelInfo& Model( ) const;

        void Run( );
    private:
        static WideString GetDeleteStatement( const ClassInfo& classInfo );
        void CreateDeleteProcedure( const ClassInfo& classInfo );
    };


    



    class SqlServerGenerator
    {
        const DatabaseGenerator& owner_;
        const SqlServerOptions& options_;
        SqlServerCreateTablesGenerator createTables_;
        SqlServerCreateViewsGenerator createViews_;
        SqlServerCreateInsertProceduresGenerator createInsertProcedures_;
        SqlServerCreateUpdateProceduresGenerator createUpdateProcedures_;
        SqlServerCreateDeleteProceduresGenerator createDeleteProcedures_;
    public:
        SqlServerGenerator( DatabaseGenerator& owner );


        const DatabaseGenerator& Owner( ) const
        {
            return owner_;
        }

        const SqlServerOptions& Options( ) const
        {
            return options_;
        }

        const ModelInfo& Model( ) const;

        void Run( )
        {
            createTables_.Run( );
            createViews_.Run( );
            createInsertProcedures_.Run( );
            createUpdateProcedures_.Run( );
            createDeleteProcedures_.Run( );
        }

    };

    inline SqlServerCreateTablesGenerator::SqlServerCreateTablesGenerator( const SqlServerGenerator& owner )
        : Base( owner.Options( ).CreateTables( ).Filename() ), owner_( owner ), options_( owner.Options().CreateTables() )
    { }

    inline const ModelInfo& SqlServerCreateTablesGenerator::Model( ) const
    {
        return Owner( ).Model( );
    }

    inline SqlServerCreateViewsGenerator::SqlServerCreateViewsGenerator( const SqlServerGenerator& owner )
        : Base( owner.Options( ).CreateViews( ).Filename( ) ), owner_( owner ), options_( owner.Options( ).CreateViews( ) )
    {
    }

    inline const ModelInfo& SqlServerCreateViewsGenerator::Model( ) const
    {
        return Owner( ).Model( );
    }

    inline SqlServerCreateInsertProceduresGenerator::SqlServerCreateInsertProceduresGenerator( const SqlServerGenerator& owner )
        : Base( owner.Options( ).CreateInsertProcedures( ).Filename( ) ), owner_( owner ), options_( owner.Options( ).CreateInsertProcedures( ) )
    {
    }

    inline const ModelInfo& SqlServerCreateInsertProceduresGenerator::Model( ) const
    {
        return Owner( ).Model( );
    }

    inline SqlServerCreateUpdateProceduresGenerator::SqlServerCreateUpdateProceduresGenerator( const SqlServerGenerator& owner )
        : Base( owner.Options( ).CreateUpdateProcedures( ).Filename( ) ), owner_( owner ), options_( owner.Options( ).CreateUpdateProcedures( ) )
    {
    }

    inline const ModelInfo& SqlServerCreateUpdateProceduresGenerator::Model( ) const
    {
        return Owner( ).Model( );
    }

    inline SqlServerCreateDeleteProceduresGenerator::SqlServerCreateDeleteProceduresGenerator( const SqlServerGenerator& owner )
        : Base( owner.Options( ).CreateDeleteProcedures( ).Filename( ) ), owner_( owner ), options_( owner.Options( ).CreateDeleteProcedures( ) )
    {
    }

    inline const ModelInfo& SqlServerCreateDeleteProceduresGenerator::Model( ) const
    {
        return Owner( ).Model( );
    }


    class DatabaseGenerator
    {
        const Generator& owner_;
        const Tool::DatabaseOptions& options_;
        SqlServerGenerator sqlServer_;
    public:
        DatabaseGenerator( const Generator& owner );

        const Generator& Owner( ) const
        {
            return owner_;
        }

        const Tool::DatabaseOptions& Options( ) const
        {
            return options_;
        }

        const ModelInfo& Model( ) const;

        void Run( )
        {
            sqlServer_.Run( );
        }
    };

    inline SqlServerGenerator::SqlServerGenerator( DatabaseGenerator& owner )
        : owner_( owner ), options_( owner.Options().SqlServer() ), createTables_(*this), createViews_( *this ), createInsertProcedures_(*this), createUpdateProcedures_( *this ), createDeleteProcedures_( *this )
    { }

    inline const ModelInfo& SqlServerGenerator::Model( ) const
    {
        return Owner( ).Model( );
    }


    class Generator
    {
        const Tool::Options& options_;
        const ModelInfo& model_;
        DatabaseGenerator database_;
    public:
        Generator( const Tool::Options& options, const ModelInfo& model )
            : options_( options ), model_( model ), database_( *this )
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
        }
    };

    inline DatabaseGenerator::DatabaseGenerator( const Generator& owner )
        : owner_( owner ), options_( owner.Options( ).Database() ) , sqlServer_( *this )
    { }

    inline const ModelInfo& DatabaseGenerator::Model( ) const
    {
        return Owner( ).Model( );
    }


}

#endif
