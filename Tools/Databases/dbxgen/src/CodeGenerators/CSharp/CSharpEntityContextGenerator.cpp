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
#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"
#include "CodeGenerators/CSharp/CSharpHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::CSharp
{
    using namespace Harlinn::Tools::DbXGen::Metadata;

    void CSharpEntityContextGenerator::Run( )
    {
        functions_.clear( );
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto nspace = Options( ).Namespace( L"." );

        const auto& dataTypesOptions = Options( ).Owner( ).Owner( ).Data( ).DataTypes( );
        auto dataTypesNamespace = dataTypesOptions.Namespace( L"." );

        WriteLine( L"using System;" );
        WriteLine( L"using System.ComponentModel;" );
        WriteLine( L"using System.Diagnostics.CodeAnalysis;" );
        WriteLine( L"using System.IO;" );
        WriteLine( L"using System.Runtime.CompilerServices;" );
        WriteLine( );
        WriteLine( L"using Microsoft.Extensions.Logging;" ); 
        WriteLine( );
        WriteLine( L"using Harlinn.Common.Core.Net;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Data;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Entities;" );
        WriteLine( L"using Harlinn.Common.Core.Net.IO;" );
        WriteLine( );
        WriteLine( L"using {};", dataTypesNamespace );
        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );

        WriteLine( L"    public class EntityContext : EntityContextBase<Kind>" );
        WriteLine( L"    {" );
        WriteLine( L"        public EntityContext( [DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] IDataContextBase<Kind> dataContext, [DisallowNull] IBaseEntityFactory<Kind> entityFactory, [DisallowNull] IBaseDataFactory<Kind> dataFactory, bool ownsDataContext = true )" );
        WriteLine( L"            : base( loggerFactory, dataContext, entityFactory, dataFactory, ownsDataContext )" );
        WriteLine( L"        {" );
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        public IDataContext DataContext => (IDataContext)DataContextBase;" );
        WriteLine( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateMembers( classInfo );

        }
        WriteLine( L"    }" );

        WriteLine( L"}" );
        Flush( );
    }

    void CSharpEntityContextGenerator::CreateMembers( const ClassInfo& classInfo )
    {
        WriteLine( L"        // ---------------------------------------------------------------------" );
        WriteLine( L"        // {} queries", classInfo.Name( ) );
        WriteLine( L"        // ---------------------------------------------------------------------" );
        CreateGetById( classInfo );
        CreateGetAll( classInfo );
        CreateGetByIndex( classInfo );
    }
    void CSharpEntityContextGenerator::CreateGetById( const ClassInfo& classInfo )
    {
        auto className = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIdFunctionName( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyType = CSharpHelper::GetInputArgumentType( *primaryKey );
        functions_.insert( functionName );

        WriteLine( L"        public {}? {}( {} id )", className, functionName, primaryKeyType );
        WriteLine( L"        {" );
        WriteLine( L"            if( IsDeleted( id ) == false )" );
        WriteLine( L"            {" );
        WriteLine( L"                var entity = ({}?)GetEntityFromCache( id );", className );
        WriteLine( L"                if( entity == null )" );
        WriteLine( L"                {" );
        WriteLine( L"                    var dataContext = DataContext;" );
        WriteLine( L"                    var dataObject = dataContext.{}( id );", functionName );
        WriteLine( L"                    if( dataObject != null )" );
        WriteLine( L"                    {" );
        WriteLine( L"                        entity = ({})AddToContext( dataObject );", className );
        WriteLine( L"                    }" );
        WriteLine( L"                }" );
        WriteLine( L"                return entity;" );
        WriteLine( L"            }" );
        WriteLine( L"            return null;" );
        WriteLine( L"        }" );
        WriteLine( );
    }
    void CSharpEntityContextGenerator::CreateGetAll( const ClassInfo& classInfo )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto dataClassName = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetAllFunctionName( classInfo );
        functions_.insert( functionName );

        WriteLine( L"        public BindingList<{}> {}( )", entityClassName, functionName );
        WriteLine( L"        {" );
        WriteLine( L"            var dataContext = DataContext;" );
        WriteLine( L"            var dataItems = dataContext.{}( );", functionName );
        WriteLine( L"            var result = ToEntityList<{},{}>( dataItems );", entityClassName, dataClassName );
        WriteLine( L"            return result;" );
        WriteLine( L"        }" );
    }
    void CSharpEntityContextGenerator::CreateGetByIndex( const ClassInfo& classInfo )
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
    void CSharpEntityContextGenerator::CreateGetByIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            auto dataClassName = CSharpHelper::GetDataType( classInfo );
            if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) )
            {
                auto returnType = entityClassName + L"?";
                WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
                WriteLine( L"        {" );
                WriteLine( L"            var dataContext = DataContext;" );
                WriteLine( L"            var dataObject = dataContext.{}( {} );", functionName, callArguments );
                WriteLine( L"            if( dataObject != null )" );
                WriteLine( L"            {" );
                WriteLine( L"                if( IsDeleted( dataObject.Id ) == false )" );
                WriteLine( L"                {" );
                WriteLine( L"                    var result = ({})AddToContext( dataObject );", entityClassName );
                WriteLine( L"                    return result;" );
                WriteLine( L"                }" );
                WriteLine( L"            }" );
                WriteLine( L"            return null;" );
                WriteLine( L"        }" );
            }
            else
            {
                auto returnType = Format( L"BindingList<{}>", entityClassName );
                WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
                WriteLine( L"        {" );
                WriteLine( L"            var dataContext = DataContext;" );
                WriteLine( L"            var dataItems = dataContext.{}( {} );", functionName, callArguments );
                WriteLine( L"            var result = ToEntityList<{},{}>( dataItems );", entityClassName, dataClassName );
                WriteLine( L"            return result;" );
                WriteLine( L"        }" );
            }
            WriteLine( );
        }
    }
    void CSharpEntityContextGenerator::CreateGetByNullableIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        
    }
    void CSharpEntityContextGenerator::CreateGetByIndexAt( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexAtFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            auto dataClassName = CSharpHelper::GetDataType( classInfo );
            if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) )
            {
                auto returnType = entityClassName + L"?";
                WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
                WriteLine( L"        {" );
                WriteLine( L"            var dataContext = DataContext;" );
                WriteLine( L"            var dataObject = dataContext.{}( {} );", functionName, callArguments );
                WriteLine( L"            if( dataObject != null )" );
                WriteLine( L"            {" );
                WriteLine( L"                if( IsDeleted( dataObject.Id ) == false )" );
                WriteLine( L"                {" );
                WriteLine( L"                    var result = ({})AddToContext( dataObject );", entityClassName );
                WriteLine( L"                    return result;" );
                WriteLine( L"                }" );
                WriteLine( L"            }" );
                WriteLine( L"            return null;" );
                WriteLine( L"        }" );
            }
            else
            {
                auto returnType = Format( L"BindingList<{}>", entityClassName );
                WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
                WriteLine( L"        {" );
                WriteLine( L"            var dataContext = DataContext;" );
                WriteLine( L"            var dataItems = dataContext.{}( {} );", functionName, callArguments );
                WriteLine( L"            var result = ToEntityList<{},{}>( dataItems );", entityClassName, dataClassName );
                WriteLine( L"            return result;" );
                WriteLine( L"        }" );
            }
            WriteLine( );
        }
    }
    void CSharpEntityContextGenerator::CreateGetByIndexFrom( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexFromFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            auto dataClassName = CSharpHelper::GetDataType( classInfo );
            auto returnType = Format( L"BindingList<{}>", entityClassName );
            WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            var dataContext = DataContext;" );
            WriteLine( L"            var dataItems = dataContext.{}( {} );", functionName, callArguments );
            WriteLine( L"            var result = ToEntityList<{},{}>( dataItems );", entityClassName, dataClassName );
            WriteLine( L"            return result;" );
            WriteLine( L"        }" );
            WriteLine( );
        }
    }
    void CSharpEntityContextGenerator::CreateGetByIndexUntil( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexUntilFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            auto dataClassName = CSharpHelper::GetDataType( classInfo );
            auto returnType = Format( L"BindingList<{}>", entityClassName );
            WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            var dataContext = DataContext;" );
            WriteLine( L"            var dataItems = dataContext.{}( {} );", functionName, callArguments );
            WriteLine( L"            var result = ToEntityList<{},{}>( dataItems );", entityClassName, dataClassName );
            WriteLine( L"            return result;" );
            WriteLine( L"        }" );
            WriteLine( );
        }
    }
    void CSharpEntityContextGenerator::CreateGetByIndexOver( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexOverFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CSharpHelper::GetByIndexFunctionOverParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionOverCallParameters( classInfo, indexInfo, indexMemberCount );
            auto dataClassName = CSharpHelper::GetDataType( classInfo );
            auto returnType = Format( L"BindingList<{}>", entityClassName );
            WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            var dataContext = DataContext;" );
            WriteLine( L"            var dataItems = dataContext.{}( {} );", functionName, callArguments );
            WriteLine( L"            var result = ToEntityList<{},{}>( dataItems );", entityClassName, dataClassName );
            WriteLine( L"            return result;" );
            WriteLine( L"        }" );
            WriteLine( );
        }
    }

}