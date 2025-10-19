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

#include "CodeGenerators/Generator.h"
#include "CodeGenerators/Java/JavaHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java
{
    using namespace Harlinn::Tools::DbXGen::Metadata;

    void JavaDataContextGenerator::Run( )
    {
        functions_.clear( );
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto nspace = Options( ).Namespace( L"." );
        WriteLine( L"package {};", nspace );
        WriteLine( );

        WriteLine( L"import java.util.List;" );
        WriteLine( L"import java.util.ArrayList;" );
        WriteLine( L"import com.harlinn.common.io.BinaryReader;" );
        WriteLine( L"import com.harlinn.common.io.BinaryWriter;" );
        WriteLine( L"import com.harlinn.common.types.AbstractDataObject;" );
        WriteLine( L"import com.harlinn.common.util.*;" );
        WriteLine( );

        WriteLine( L"public interface DataContext {" );
        WriteLine( L"    Guid getSessionId( );" );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateMembers( classInfo );

        }
        WriteLine( L"}" );
        Flush( );
    }

    void JavaDataContextGenerator::CreateMembers( const ClassInfo& classInfo )
    {
        
        WriteLine( L"    // ---------------------------------------------------------------------" );
        WriteLine( L"    // {} queries", classInfo.Name( ) );
        WriteLine( L"    // ---------------------------------------------------------------------" );
        CreateGetById( classInfo );
        CreateGetAll( classInfo );
        CreateGetByIndex( classInfo );
    }
    void JavaDataContextGenerator::CreateGetById( const ClassInfo& classInfo )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByIdFunctionName( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyType = JavaHelper::GetInputArgumentType( *primaryKey );
        functions_.insert( functionName );

        WriteLine( L"    {} {}( {} id ) throws Exception;", className, functionName, primaryKeyType );

    }
    void JavaDataContextGenerator::CreateGetAll( const ClassInfo& classInfo )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetAllFunctionName( classInfo );
        functions_.insert( functionName );

        WriteLine( L"    List<{}> {}( ) throws Exception;", className, functionName );
    }
    void JavaDataContextGenerator::CreateGetByIndex( const ClassInfo& classInfo )
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

    void JavaDataContextGenerator::CreateGetByIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = className;
            if ( JavaHelper::IsUnique( indexInfo, indexMemberCount ) == false )
            {
                returnType = Format( L"List<{}>", className );
            }
            auto arguments = JavaHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"    {} {}( {} ) throws Exception;", returnType, functionName, arguments );
        }
    }

    void JavaDataContextGenerator::CreateGetByNullableIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByNullableIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = Format( L"List<{}>", className );
            auto arguments = JavaHelper::GetByNullableIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"    {} {}( {} ) throws Exception;", returnType, functionName, arguments );
        }
    }

    void JavaDataContextGenerator::CreateGetByIndexAt( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByIndexAtFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = className;
            if ( JavaHelper::IsUnique( indexInfo, indexMemberCount ) == false )
            {
                returnType = Format( L"List<{}>", className );
            }
            auto arguments = JavaHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"    {} {}( {} ) throws Exception;", returnType, functionName, arguments );
        }
    }
    void JavaDataContextGenerator::CreateGetByIndexFrom( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByIndexFromFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = Format( L"List<{}>", className );
            auto arguments = JavaHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"    {} {}( {} ) throws Exception;", returnType, functionName, arguments );
        }
    }
    void JavaDataContextGenerator::CreateGetByIndexUntil( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByIndexUntilFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = Format( L"List<{}>", className );
            auto arguments = JavaHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"    {} {}( {} ) throws Exception;", returnType, functionName, arguments );
        }
    }
    void JavaDataContextGenerator::CreateGetByIndexOver( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByIndexOverFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = Format( L"List<{}>", className );
            auto arguments = JavaHelper::GetByIndexFunctionOverParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"    {} {}( {} ) throws Exception;", returnType, functionName, arguments );
        }
    }

}