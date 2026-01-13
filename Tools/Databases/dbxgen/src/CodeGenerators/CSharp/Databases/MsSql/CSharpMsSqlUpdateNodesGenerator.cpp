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
#include "CodeGenerators/CSharp/CSharpHelper.h"
#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"


namespace Harlinn::Tools::DbXGen::CodeGenerators::CSharp::Databases::MsSql
{
    using namespace Harlinn::Tools::DbXGen::Metadata;
    using namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql;

    void CSharpMsSqlUpdateNodesGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto nspace = Options( ).Namespace( L"." );

        const auto& dataTypesOptions = Options( ).Owner( ).Owner( ).Owner( ).Data( ).DataTypes( );
        auto dataTypesNamespace = dataTypesOptions.Namespace( L"." );

        WriteLine( L"using System;" );
        WriteLine( L"using System.Diagnostics.CodeAnalysis;" );
        WriteLine( L"using System.IO;" );
        WriteLine( L"using System.Runtime.CompilerServices;" );
        WriteLine( );
        WriteLine( L"using Microsoft.Extensions.Logging;" );
        WriteLine( );
        WriteLine( L"using Harlinn.Common.Core.Net;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Data;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Data.Updates;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Entities;" );
        WriteLine( L"using Harlinn.Common.Core.Net.IO;" );
        WriteLine( );
        WriteLine( L"using {};", dataTypesNamespace );
        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );



        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                CreateUpdateNode( classInfo );
            }

        }
        CreateFactory( );
        CreateUpdateHandler( );

        WriteLine( L"}" );
        Flush( );
    }

    void CSharpMsSqlUpdateNodesGenerator::CreateUpdateNode( const ClassInfo& classInfo )
    {
        auto updateNodeClassName = CSharpHelper::GetUpdateNode( classInfo );
        auto dataClassName = CSharpHelper::GetDataType( classInfo );
        WriteLine( L"    public class {} : SqlServerUpdateNodeBase<Kind>", updateNodeClassName );
        WriteLine( L"    {" );
        WriteLine( L"        public {}( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] {} dataObject )", updateNodeClassName, dataClassName );
        WriteLine( L"            : base(updateHandler, dataObject)" );
        WriteLine( L"        {" );
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;" );
        WriteLine( );
        WriteLine( L"        {} GetData( ) {{ return ({})_GetData( ); }}", dataClassName, dataClassName );
        WriteLine( );
        CreateCollectDependencies( classInfo );
        CreateInsert( classInfo );
        if ( classInfo.HasNullableReferences( ) )
        {
            CreateInsert1( classInfo );
        }
        CreateUpdate( classInfo );
        if ( classInfo.HasNullableReferences( ) )
        {
            CreateUpdate1( classInfo );
            CreateUpdate2( classInfo );
        }
        CreateDelete( classInfo );
        WriteLine( L"    }" );
    }
    void CSharpMsSqlUpdateNodesGenerator::CreateCollectDependencies( const ClassInfo& classInfo )
    {
        auto references = classInfo.References( );
        auto referenceCount = references.size( );
        if ( referenceCount )
        {
            WriteLine( L"        public override void CollectDependencies( )" );
            WriteLine( L"        {" );
            WriteLine( L"            var dataObject = GetData( );" );
            WriteLine( L"            var updateNodes = UpdateNodes;" );
            for ( size_t i = 0; i < referenceCount; i++ )
            {
                const auto& reference = *references[ i ];
                auto propertyName = reference.Name( ).FirstToUpper( );
                if ( reference.Nullable( ) )
                {
                    WriteLine( L"            if( dataObject.{} is Guid referencedId{} )", propertyName, i + 1 );
                    WriteLine( L"            {" );
                    WriteLine( L"                if( updateNodes.TryGetValue( referencedId{}, out var otherNode{} ) )", i + 1, i + 1 );
                    WriteLine( L"                {" );
                    if ( reference.IsOneToOne( ) && reference.Nullable( ) )
                    {
                        WriteLine( L"                    if( otherNode{}.IsNew )", i + 1 );
                        WriteLine( L"                    {" );
                        WriteLine( L"                        RequiresUpdate2 = true;" );
                        WriteLine( L"                    }" );
                    }
                    else
                    {
                        WriteLine( L"                    if( otherNode{}.IsNew )", i + 1 );
                        WriteLine( L"                    {" );
                        WriteLine( L"                        AddDependency( otherNode{} );", i + 1 );
                        WriteLine( L"                    }" );
                    }
                    WriteLine( L"                }" );
                    WriteLine( L"            }" );
                }
                else
                {
                    WriteLine( L"            if( updateNodes.TryGetValue( dataObject.{}, out var otherNode{} ) )", propertyName, i + 1 );
                    WriteLine( L"            {" );
                    if ( reference.IsOneToOne( ) )
                    {
                        WriteLine( L"                if( otherNode{}.IsNew )", i + 1 );
                        WriteLine( L"                {" );
                        WriteLine( L"                    RequiresUpdate2 = true;" );
                        WriteLine( L"                }" );
                    }
                    else
                    {
                        WriteLine( L"                if( otherNode{}.IsNew )", i + 1 );
                        WriteLine( L"                {" );
                        WriteLine( L"                    AddDependency( otherNode{} );", i + 1 );
                        WriteLine( L"                }" );
                    }
                    WriteLine( L"            }" );
                }
            }
            WriteLine( );
            WriteLine( L"        }" );
        }
    }
    void CSharpMsSqlUpdateNodesGenerator::CreateInsert( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetInsertFunctionName( classInfo );
        WriteLine( L"        public override void Insert( )" );
        WriteLine( L"        {" );
        WriteLine( L"            var storedProcedures = StoredProcedures;" );
        WriteLine( L"            var dataObject = GetData( );" );
        WriteLine( L"            storedProcedures.{}( dataObject );", functionName );
        WriteLine( L"        }" );
    }
    void CSharpMsSqlUpdateNodesGenerator::CreateInsert1( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetInsertFunctionName1( classInfo );
        WriteLine( L"        public override void Insert1( )" );
        WriteLine( L"        {" );
        WriteLine( L"            var storedProcedures = StoredProcedures;" );
        WriteLine( L"            var dataObject = GetData( );" );
        WriteLine( L"            storedProcedures.{}( dataObject );", functionName );
        WriteLine( L"        }" );
    }
    void CSharpMsSqlUpdateNodesGenerator::CreateUpdate( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetUpdateFunctionName( classInfo );
        WriteLine( L"        public override void Update( )" );
        WriteLine( L"        {" );
        WriteLine( L"            var storedProcedures = StoredProcedures;" );
        WriteLine( L"            var dataObject = GetData( );" );
        WriteLine( L"            storedProcedures.{}( dataObject );", functionName );
        WriteLine( L"        }" );
    }
    void CSharpMsSqlUpdateNodesGenerator::CreateUpdate1( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetUpdateFunctionName1( classInfo );
        WriteLine( L"        public override void Update1( )" );
        WriteLine( L"        {" );
        WriteLine( L"            var storedProcedures = StoredProcedures;" );
        WriteLine( L"            var dataObject = GetData( );" );
        WriteLine( L"            storedProcedures.{}( dataObject );", functionName );
        WriteLine( L"        }" );
    }
    void CSharpMsSqlUpdateNodesGenerator::CreateUpdate2( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetUpdateFunctionName2( classInfo );
        WriteLine( L"        public override void Update2( )" );
        WriteLine( L"        {" );
        WriteLine( L"            var storedProcedures = StoredProcedures;" );
        WriteLine( L"            var dataObject = GetData( );" );
        WriteLine( L"            storedProcedures.{}( dataObject );", functionName );
        WriteLine( L"        }" );
    }
    void CSharpMsSqlUpdateNodesGenerator::CreateDelete( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetDeleteFunctionName( classInfo );
        WriteLine( L"        public override void Delete( )" );
        WriteLine( L"        {" );
        WriteLine( L"            var storedProcedures = StoredProcedures;" );
        WriteLine( L"            var dataObject = GetData( );" );
        WriteLine( L"            storedProcedures.{}( dataObject );", functionName );
        WriteLine( L"        }" );
    }
    void CSharpMsSqlUpdateNodesGenerator::CreateFactory( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        WriteLine( L"    public class SqlServerUpdateNodeFactory : IUpdateNodeFactory<Kind>" );
        WriteLine( L"    {" );
        WriteLine( L"        public SqlServerUpdateNodeFactory()" );
        WriteLine( L"        {" );
        WriteLine( L"        }" );
        WriteLine( L"        public SqlServerUpdateNodeBase<Kind> Create([DisallowNull] SqlServerUpdateHandlerBase<Kind> updateHandlerBase, [DisallowNull] BaseDataGuid<Kind> data)" );
        WriteLine( L"        {" );
        WriteLine( L"            var updateHandler = (SqlServerUpdateHandler)updateHandlerBase;" );
        WriteLine( L"            var kind = data.GetObjectType();" );
        WriteLine( L"            switch (kind)" );
        WriteLine( L"            {" );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                auto updateNodeClassName = CSharpHelper::GetUpdateNode( classInfo );
                auto dataTypeName = CSharpHelper::GetDataType( classInfo );

                WriteLine( L"                case Kind.{}:", classInfo.Name( ) );
                WriteLine( L"                {" );
                WriteLine( L"                    return new {}( updateHandler, ({})data );", updateNodeClassName, dataTypeName );
                WriteLine( L"                }" );
            }
        }
        WriteLine( L"                default:" );
        WriteLine( L"                {" );
        WriteLine( L"                    throw new ArgumentException($\"Cannot create an update node for kind={kind}.\", \"kind\");" );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( L"    }" );
    }
    void CSharpMsSqlUpdateNodesGenerator::CreateUpdateHandler( )
    {
        WriteLine( L"    public class SqlServerUpdateHandler : SqlServerUpdateHandlerBase<Kind>" );
        WriteLine( L"    {" );
        WriteLine( L"        public SqlServerUpdateHandler([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] StoredProcedures storedProcedures, [DisallowNull] UpdateData<Kind> updateData, [DisallowNull] SqlServerUpdateNodeFactory updateNodeFactory)" );
        WriteLine( L"            : base( loggerFactory, storedProcedures, updateData, updateNodeFactory )" );
        WriteLine( L"        {" );
        WriteLine( L"        }" );
        WriteLine( L"    }" );
    }
}