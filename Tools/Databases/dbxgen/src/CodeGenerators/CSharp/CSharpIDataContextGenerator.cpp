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

#include "CodeGenerators/Generator.h"
#include "CodeGenerators/CSharp/CSharpHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::CSharp
{
    using namespace Harlinn::Tools::DbXGen::Metadata;

    void CSharpIDataContextGenerator::Run( )
    {
        functions_.clear( );
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto nspace = Options( ).Namespace( L"." );

        WriteLine( L"using System;" );
        WriteLine( L"using System.Diagnostics.CodeAnalysis;" );
        WriteLine( L"using System.IO;" );
        WriteLine( );
        WriteLine( L"using Harlinn.Common.Core.Net;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Data;" );
        WriteLine( L"using Harlinn.Common.Core.Net.IO;" );

        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );

        WriteLine( L"    public interface IDataContext : IDataContextBase<Kind>" );
        WriteLine( L"    {" );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateMembers( classInfo );
            
        }
        WriteLine( L"    }" );

        WriteLine( L"}" );
        Flush( );
    }

    void CSharpIDataContextGenerator::CreateMembers( const ClassInfo& classInfo )
    {
        WriteLine( L"        // ---------------------------------------------------------------------" );
        WriteLine( L"        // {} queries", classInfo.Name( ) );
        WriteLine( L"        // ---------------------------------------------------------------------" );
        CreateGetById( classInfo );
        CreateGetAll( classInfo );
        CreateGetByIndex( classInfo );
    }
    void CSharpIDataContextGenerator::CreateGetById( const ClassInfo& classInfo )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByIdFunctionName( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyType = CSharpHelper::GetInputArgumentType( *primaryKey );
        functions_.insert( functionName );

        WriteLine( L"        {}? {}( {} id );", className, functionName, primaryKeyType );

    }
    void CSharpIDataContextGenerator::CreateGetAll( const ClassInfo& classInfo )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetAllFunctionName( classInfo );
        functions_.insert( functionName );

        WriteLine( L"        IList<{}> {}( );", className, functionName );
    }
    void CSharpIDataContextGenerator::CreateGetByIndex( const ClassInfo& classInfo )
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

    void CSharpIDataContextGenerator::CreateGetByIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = className + L"?";
            if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) == false )
            {
                returnType = Format( L"IList<{}>", className );
            }
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        {} {}( {} );", returnType, functionName, arguments );
        }
    }

    void CSharpIDataContextGenerator::CreateGetByNullableIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByNullableIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = Format( L"IList<{}>", className );
            auto arguments = CSharpHelper::GetByNullableIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        {} {}( {} );", returnType, functionName, arguments );
        }
    }

    void CSharpIDataContextGenerator::CreateGetByIndexAt( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByIndexAtFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = className + L"?";
            if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) == false )
            {
                returnType = Format( L"IList<{}>", className );
            }
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        {} {}( {} );", returnType, functionName, arguments );
        }
    }
    void CSharpIDataContextGenerator::CreateGetByIndexFrom( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByIndexFromFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = Format( L"IList<{}>", className );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        {} {}( {} );", returnType, functionName, arguments );
        }
    }
    void CSharpIDataContextGenerator::CreateGetByIndexUntil( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByIndexUntilFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = Format( L"IList<{}>", className );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        {} {}( {} );", returnType, functionName, arguments );
        }
    }
    void CSharpIDataContextGenerator::CreateGetByIndexOver( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByIndexOverFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = Format( L"IList<{}>", className );
            auto arguments = CSharpHelper::GetByIndexFunctionOverParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        {} {}( {} );", returnType, functionName, arguments );
        }
    }

}