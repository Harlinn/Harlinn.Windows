/*
   Copyright 2024-2026 Espen Harlinn

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

#include "CodeGenerators/Generator.h"
#include "CodeGenerators/Cpp/CppHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Cpp
{
    using namespace Harlinn::Tools::DbXGen::Metadata;

    void CppIDataContextGenerator::Run( )
    {
        functions_.clear( );
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto headerGuard = CppHelper::GetHeaderGuard( Filename( ) );
        auto nspace = Options( ).Namespace( L"::" );

        WriteLine( L"#pragma once" );
        WriteLine( L"#ifndef {}", headerGuard );
        WriteLine( L"#define {}", headerGuard );
        WriteLine( );
        WriteLine( "#include \"DataTypes.h\"" );
        WriteLine( );

        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( );
        WriteLine( L"    class UpdateData" );
        WriteLine( L"    {" );

        WriteLine( L"    };" );
        WriteLine( );
        WriteLine( L"    class UpdateResult" );
        WriteLine( L"    {" );

        WriteLine( L"    };" );
        WriteLine( );
        WriteLine( L"    class IDataContext" );
        WriteLine( L"    {" );
        WriteLine( );
        WriteLine( L"        virtual bool Insert( BaseData<Kind, Guid>& data ) = 0;");
        WriteLine( L"        virtual bool Update( BaseData<Kind, Guid>& data ) = 0;");
        WriteLine( L"        virtual bool Delete( const BaseData<Kind, Guid>& data ) = 0;");
        WriteLine( L"        virtual bool Merge( BaseData<Kind, Guid>& data ) = 0;" );
        WriteLine( );
        WriteLine( L"        virtual bool Update( const UpdateData& data, UpdateResult& result ) = 0;" );
        WriteLine( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateMembers( classInfo );

        }
        WriteLine( L"    };" );

        WriteLine( L"}" );
        WriteLine( L"#endif" );
        Flush( );
    }

    void CppIDataContextGenerator::CreateMembers( const ClassInfo& classInfo )
    {
        WriteLine( L"        // ---------------------------------------------------------------------" );
        WriteLine( L"        // {} queries", classInfo.Name( ) );
        WriteLine( L"        // ---------------------------------------------------------------------" );
        CreateGetById( classInfo );
        CreateGetAll( classInfo );
        CreateGetByIndex( classInfo );
    }
    void CppIDataContextGenerator::CreateGetById( const ClassInfo& classInfo )
    {
        auto className = CppHelper::GetDataType( classInfo );
        auto functionName = CppHelper::GetByIdFunctionName( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyType = CppHelper::GetInputArgumentType( *primaryKey );
        functions_.insert( functionName );

        WriteLine( L"        virtual std::shared_ptr<{}> {}( {} id ) = 0;", className, functionName, primaryKeyType );

    }
    void CppIDataContextGenerator::CreateGetAll( const ClassInfo& classInfo )
    {
        auto className = CppHelper::GetDataType( classInfo );
        auto functionName = CppHelper::GetAllFunctionName( classInfo );
        functions_.insert( functionName );

        WriteLine( L"        virtual void {}( std::vector<std::shared_ptr<{}>>& result ) = 0;", functionName, className );
    }
    void CppIDataContextGenerator::CreateGetByIndex( const ClassInfo& classInfo )
    {
        auto indexes = classInfo.AllIndexes( );
        auto indexCount = indexes.size( );
        for ( size_t i = 0; i < indexCount; i++ )
        {
            const auto& index = *indexes[ i ];
            const auto& indexMembers = index.Fields( );
            auto indexMemberCount = indexMembers.size( );
            for ( size_t j = 0; j < indexMemberCount; j++ )
            {
                CreateGetByIndex( classInfo, index, j + 1 );
                if ( index.HasNullableElements( j + 1 ) )
                {
                    CreateGetByNullableIndex( classInfo, index, j + 1 );
                }
                if ( index.IsTimeSeries( j + 1 ) )
                {
                    CreateGetByIndexAt( classInfo, index, j + 1 );
                }
                if ( index.IsRange( j + 1 ) )
                {
                    CreateGetByIndexFrom( classInfo, index, j + 1 );
                    CreateGetByIndexUntil( classInfo, index, j + 1 );
                    CreateGetByIndexOver( classInfo, index, j + 1 );
                }
            }
        }
    }

    void CppIDataContextGenerator::CreateGetByIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CppHelper::GetDataType( classInfo );
        auto functionName = CppHelper::GetByIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CppHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            if ( CppHelper::IsUnique( indexInfo, indexMemberCount ) == false )
            {
                WriteLine( L"        virtual void {}( {}, std::vector<std::shared_ptr<{}>>& result ) = 0;", functionName, arguments, className );
            }
            else
            {
                WriteLine( L"        virtual std::shared_ptr<{}> {}( {} ) = 0;", className, functionName, arguments );
            }
        }
    }

    void CppIDataContextGenerator::CreateGetByNullableIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CppHelper::GetDataType( classInfo );
        auto functionName = CppHelper::GetByNullableIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            const auto& fields = indexInfo.Fields( );
            if ( indexMemberCount == 1 )
            {
                WriteLine( L"        virtual void {}( std::vector<std::shared_ptr<{}>>& result ) = 0;", functionName, className );
            }
            else
            {
                auto arguments = CppHelper::GetByNullableIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
                WriteLine( L"        virtual void {}( {}, std::vector<std::shared_ptr<{}>>& result ) = 0;", functionName, arguments, className );
            }
        }
    }

    void CppIDataContextGenerator::CreateGetByIndexAt( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CppHelper::GetDataType( classInfo );
        auto functionName = CppHelper::GetByIndexAtFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CppHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );

            if ( CppHelper::IsUnique( indexInfo, indexMemberCount ) == false )
            {
                WriteLine( L"        virtual void {}( {}, std::vector<std::shared_ptr<{}>>& result ) = 0;", functionName, arguments, className );
            }
            else
            {
                WriteLine( L"        virtual std::shared_ptr<{}> {}( {} ) = 0;", className, functionName, arguments );
            }
        }
    }
    void CppIDataContextGenerator::CreateGetByIndexFrom( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CppHelper::GetDataType( classInfo );
        auto functionName = CppHelper::GetByIndexFromFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CppHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        virtual void {}( {}, std::vector<std::shared_ptr<{}>>& result ) = 0;", functionName, arguments, className );
        }
    }
    void CppIDataContextGenerator::CreateGetByIndexUntil( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CppHelper::GetDataType( classInfo );
        auto functionName = CppHelper::GetByIndexUntilFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CppHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        virtual void {}( {}, std::vector<std::shared_ptr<{}>>& result ) = 0;", functionName, arguments, className );
        }
    }
    void CppIDataContextGenerator::CreateGetByIndexOver( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CppHelper::GetDataType( classInfo );
        auto functionName = CppHelper::GetByIndexOverFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CppHelper::GetByIndexFunctionOverParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        virtual void {}( {}, std::vector<std::shared_ptr<{}>>& result ) = 0;", functionName, arguments, className );
        }
    }

}