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

    void CSharpEntityChangesGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto nspace = Options( ).Namespace( L"." ) + L".Changes";

        const auto& dataTypesOptions = Options( ).Owner( ).Owner( ).Data( ).DataTypes( );
        auto dataTypesNamespace = dataTypesOptions.Namespace( L"." );

        WriteLine( L"using System;" );
        WriteLine( L"using System.Collections.Generic;" );
        WriteLine( L"using System.Diagnostics.CodeAnalysis;" );
        WriteLine( L"using System.IO;" );
        WriteLine( L"using System.Runtime.CompilerServices;" );
        WriteLine( );
        WriteLine( L"using Microsoft.Extensions.Logging;" );
        WriteLine( );
        WriteLine( L"using Harlinn.Common.Core.Net;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Collections.Generic;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Entities;" );
        WriteLine( );
        WriteLine( L"using {};", dataTypesNamespace );
        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );



        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateEntityIndexClasses( classInfo );

        }
        
        CreateEntityChanges( );

        WriteLine( L"}" );
        Flush( );
    }

    void CSharpEntityChangesGenerator::CreateEntityIndexClasses( const ClassInfo& classInfo )
    {
        const auto& indexes = classInfo.Indexes( );
        auto indexCount = indexes.size( );
        for ( size_t i = 0; i < indexCount; i++ )
        {
            const auto& index = *indexes[ i ];
            if ( index.Unique( ) )
            {
                CreateEntityUniqueIndexClass( classInfo, index );
            }
            else
            {
                CreateEntityIndexClass( classInfo, index );
            }
            if ( index.HasNullableElements( ) )
            {
                if ( index.Unique( ) )
                {
                    CreateNullableEntityUniqueIndexClass( classInfo, index );
                }
                else
                {
                    CreateNullableEntityIndexClass( classInfo, index );
                }
            }
        }
    }
    void CSharpEntityChangesGenerator::CreateEntityUniqueIndexClass( const ClassInfo& classInfo, const IndexInfo& indexInfo )
    {
        const auto& fields = indexInfo.Fields( );
        auto fieldCount = fields.size( );
        
        if ( fieldCount == 1 )
        {
            CreateEntitySingleFieldUniqueIndexClass( classInfo, indexInfo );
        }
        else
        {
            CreateEntityMultiFieldUniqueIndexClass( classInfo, indexInfo );
        }
    }

    void CSharpEntityChangesGenerator::CreateEntitySingleFieldUniqueIndexClass( const ClassInfo& classInfo, const IndexInfo& indexInfo )
    {
        const auto& fields = indexInfo.Fields( );
        auto fieldCount = fields.size( );
        auto className = CSharpHelper::GetEntityIndexClassName( indexInfo );
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );

        WriteLine( L"    public class {}", className );
        WriteLine( L"    {" );
        const auto& field = *fields[ 0 ];
        auto variableName = CSharpHelper::GetInputArgumentName( field );
        auto variableType = CSharpHelper::GetNotNullableBaseType( field );
        auto keyType = CSharpHelper::GetNotNullableBaseType( field );
        WriteLine( L"        readonly SortedWeakReferenceList<{}, {}> _entries = new SortedWeakReferenceList<{}, {}>( );", keyType, entityClassName, keyType, entityClassName );
        WriteLine( );
        WriteLine( L"        public {}( )", className );
        WriteLine( L"        {" );
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        public void Add( {} entity )", entityClassName );
        WriteLine( L"        {" );
        WideString propertyName = field.Name( ).FirstToUpper( );
        if ( field.IsReferenceType( ) )
        {
            propertyName += L"Id";
        }
        if ( field.Nullable( ) )
        {

            WriteLine( L"            if ( entity.{} is {} {} )", propertyName, variableType, variableName );
            WriteLine( L"            {" );
            WriteLine( L"                if ( _entries.TryGetValue( {}, out var weakReference ) )", variableName );
            WriteLine( L"                {" );
            WriteLine( L"                    weakReference.SetTarget( entity );" );
            WriteLine( L"                }" );
            WriteLine( L"                else" );
            WriteLine( L"                {" );
            WriteLine( L"                    _entries.Add( {}, new WeakReference<{}>( entity, false ) );", variableName, entityClassName );
            WriteLine( L"                }" );
            WriteLine( L"            }" );
            WriteLine( L"            else" );
            WriteLine( L"            {" );
            WriteLine( L"                throw new ArgumentException( \"entity.{} is null.\", nameof( entity ) );", propertyName );
            WriteLine( L"            }" );
        }
        else
        {
            WriteLine( L"            if( _entries.TryGetValue(entity.{}, out var weakReference ) )", propertyName );
            WriteLine( L"            {" );
            WriteLine( L"                weakReference.SetTarget( entity );" );
            WriteLine( L"            }" );
            WriteLine( L"            else" );
            WriteLine( L"            {" );
            WriteLine( L"                _entries.Add( entity.{}, new WeakReference<{}>( entity, false ) );", propertyName, entityClassName );
            WriteLine( L"            }" );
        }
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        public bool GetBy{}( {} {}, out {}? entity )", propertyName, variableType, variableName, entityClassName );
        WriteLine( L"        {" );
        WriteLine( L"            entity = null;" );
        WriteLine( L"            if ( _entries.TryGetValue( {}, out var weakReference ) )", variableName );
        WriteLine( L"            {" );
        WriteLine( L"                if ( weakReference.TryGetTarget( out entity ) == false )" );
        WriteLine( L"                {" );
        WriteLine( L"                    _entries.Remove( {} );", variableName );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"            return _entries.Count > 0;" );
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        public bool GetFrom({} key, [DisallowNull] IList<{}> result )", variableType, entityClassName );
        WriteLine( L"        {" );
        WriteLine( L"            return _entries.From( key, result );" );
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        public bool GetUntil({} key, [DisallowNull] IList<{}> result )", variableType, entityClassName );
        WriteLine( L"        {" );
        WriteLine( L"            return _entries.Until( key, result );" );
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        public bool GetOver({} firstKey, {} lastKey, [DisallowNull] IList<{}> result )", variableType, variableType, entityClassName );
        WriteLine( L"        {" );
        WriteLine( L"            return _entries.Over( firstKey, lastKey, result );" );
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        public bool GetAll([DisallowNull] IList<{}> result )", entityClassName );
        WriteLine( L"        {" );
        WriteLine( L"            return _entries.All( result );" );
        WriteLine( L"        }" );
        WriteLine( );
        CreateIndexGetByIndex( classInfo, indexInfo );
        WriteLine( L"    }" );
    }
    void CSharpEntityChangesGenerator::CreateEntityMultiFieldUniqueIndexClass( const ClassInfo& classInfo, const IndexInfo& indexInfo )
    {
        const auto& fields = indexInfo.Fields( );
        auto fieldCount = fields.size( );
        auto className = CSharpHelper::GetEntityIndexClassName( indexInfo );
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );

        WriteLine( L"    public class {}", className );
        WriteLine( L"    {" );
        for ( size_t i = 1; i < fieldCount - 1; i++ )
        {
            const auto& field = *fields[ i ];
            CreateEntityMultiFieldUniqueIndexIntermediateClass( classInfo, indexInfo, i );
        }
        WriteLine( );
        CreateEntityMultiFieldUniqueIndexFinalClass( classInfo, indexInfo );

        const auto& firstField = *fields.front( );
        auto firstFieldKeyType = CSharpHelper::GetNotNullableBaseType( firstField );

        const auto& secondField = *fields[ 1 ];
        WriteLine( L"        readonly SortedListEx<{}, By{}> _entries = new SortedListEx<{}, By{}>( );", firstFieldKeyType, secondField.Name( ), firstFieldKeyType, secondField.Name( ) );
    
        CreateIndexGetByIndex( classInfo, indexInfo );
        WriteLine( L"    }" );

    }

    void CSharpEntityChangesGenerator::CreateEntityMultiFieldUniqueIndexIntermediateClass( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t fieldIndex )
    {
        const auto& fields = indexInfo.Fields( );
        auto fieldCount = fields.size( );
        auto className = CSharpHelper::GetEntityIndexClassName( indexInfo );
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        const auto& field = *fields[ fieldIndex ];

        WriteLine( L"        public class By{}", field.Name( ) );
        WriteLine( L"        {" );
        auto keyType = CSharpHelper::GetNotNullableBaseType( field );
        const auto& nextField = *fields[ fieldIndex + 1 ];
        WriteLine( L"            readonly SortedListEx<{}, By{}> _entries = new SortedListEx<{}, By{}>( );", keyType, nextField.Name( ), keyType, nextField.Name( ) );
        WriteLine( L"            List<{}> _emptyKeys = new List<{}>( );", keyType, keyType );
        WriteLine( );
        WriteLine( L"            public By{}( )", field.Name( ) );
        WriteLine( L"            {" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            void RemoveEmptyKeys( )" );
        WriteLine( L"            {" );
        WriteLine( L"                var emptyKeyCount = _emptyKeys.Count;" );
        WriteLine( L"                for ( int i = 0; i < emptyKeyCount; i++ )" );
        WriteLine( L"                {" );
        WriteLine( L"                    _entries.Remove( _emptyKeys[ i ] );" );
        WriteLine( L"                }" );
        WriteLine( L"                _emptyKeys.Clear( );" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public bool GetAll([DisallowNull] IList<{}> result )", entityClassName );
        WriteLine( L"            {" );
        WriteLine( L"                foreach( var entry in _entries )" );
        WriteLine( L"                {" );
        WriteLine( L"                    if( entry.Value.GetAll( result ) == false )" );
        WriteLine( L"                    {" );
        WriteLine( L"                        _emptyKeys.Add( entry.Key );" );
        WriteLine( L"                    }" );
        WriteLine( L"                }" );
        WriteLine( L"                RemoveEmptyKeys( );" );
        WriteLine( L"                return _entries.Count > 0;" );
        WriteLine( L"            }" );
        for ( size_t i = fieldIndex + 1; i < fieldCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto functionName = CSharpHelper::GetByIndexFunctionName( classInfo, indexInfo, fieldIndex, i );
        }
        WriteLine( );
        WriteLine( L"        }" );
    }
    void CSharpEntityChangesGenerator::CreateEntityMultiFieldUniqueIndexFinalClass( const ClassInfo& classInfo, const IndexInfo& indexInfo )
    {
        const auto& fields = indexInfo.Fields( );
        auto fieldCount = fields.size( );
        auto className = CSharpHelper::GetEntityIndexClassName( indexInfo );
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );

        const auto& field = *fields.back( );
        auto variableName = CSharpHelper::GetInputArgumentName( field );
        auto variableType = CSharpHelper::GetNotNullableBaseType( field );
        WriteLine( L"        public class By{}", field.Name( ) );
        WriteLine( L"        {" );
        auto keyType = CSharpHelper::GetNotNullableBaseType( field );

        WriteLine( L"            readonly SortedWeakReferenceList<{}, {}> _entries = new SortedWeakReferenceList<{}, {}>( );", keyType, entityClassName, keyType, entityClassName );
        WriteLine( );
        WriteLine( L"            public By{}( )", field.Name( ) );
        WriteLine( L"            {" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public void Add( {} entity )", entityClassName );
        WriteLine( L"            {" );
        WideString propertyName = field.Name( ).FirstToUpper( );
        if ( field.IsReferenceType( ) )
        {
            propertyName += L"Id";
        }
        if ( field.Nullable( ) )
        {
            auto variableName = CSharpHelper::GetInputArgumentName( field );
            auto variableType = CSharpHelper::GetNotNullableBaseType( field );
            WriteLine( L"                if ( entity.{} is {} {} )", propertyName, variableType, variableName );
            WriteLine( L"                {" );
            WriteLine( L"                    if ( _entries.TryGetValue( {}, out var weakReference ) )", variableName );
            WriteLine( L"                    {" );
            WriteLine( L"                        weakReference.SetTarget( entity );" );
            WriteLine( L"                    }" );
            WriteLine( L"                    else" );
            WriteLine( L"                    {" );
            WriteLine( L"                        _entries.Add( {}, new WeakReference<{}>( entity, false ) );", variableName, entityClassName );
            WriteLine( L"                    }" );
            WriteLine( L"                }" );
            WriteLine( L"                else" );
            WriteLine( L"                {" );
            WriteLine( L"                    throw new ArgumentException( \"entity.{} is null.\", nameof( entity ) );", propertyName );
            WriteLine( L"                }" );
        }
        else
        {
            WriteLine( L"                if( _entries.TryGetValue(entity.{}, out var weakReference ) )", propertyName );
            WriteLine( L"                {" );
            WriteLine( L"                    weakReference.SetTarget( entity );" );
            WriteLine( L"                }" );
            WriteLine( L"                else" );
            WriteLine( L"                {" );
            WriteLine( L"                    _entries.Add( entity.{}, new WeakReference<{}>( entity, false ) );", propertyName, entityClassName );
            WriteLine( L"                }" );
        }
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public bool GetBy{}( {} {}, out {}? entity )", propertyName, variableType, variableName, entityClassName );
        WriteLine( L"            {" );
        WriteLine( L"                entity = null;" );
        WriteLine( L"                if ( _entries.TryGetValue( {}, out var weakReference ) )", variableName );
        WriteLine( L"                {" );
        WriteLine( L"                    if ( weakReference.TryGetTarget( out entity ) == false )" );
        WriteLine( L"                    {" );
        WriteLine( L"                        _entries.Remove( {} );", variableName );
        WriteLine( L"                    }" );
        WriteLine( L"                }" );
        WriteLine( L"                return _entries.Count > 0;" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public bool GetFrom({} key, [DisallowNull] IList<{}> result )", variableType, entityClassName );
        WriteLine( L"            {" );
        WriteLine( L"                return _entries.From( key, result );" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public bool GetUntil({} key, [DisallowNull] IList<{}> result )", variableType, entityClassName );
        WriteLine( L"            {" );
        WriteLine( L"                return _entries.Until( key, result );" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public bool GetOver({} firstKey, {} lastKey, [DisallowNull] IList<{}> result )", variableType, variableType, entityClassName );
        WriteLine( L"            {" );
        WriteLine( L"                return _entries.Over( firstKey, lastKey, result );" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public bool GetAll([DisallowNull] IList<{}> result )", entityClassName );
        WriteLine( L"            {" );
        WriteLine( L"                return _entries.All( result );" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"        }" );
        WriteLine( );
    }



    void CSharpEntityChangesGenerator::CreateEntityIndexClass( const ClassInfo& classInfo, const IndexInfo& indexInfo )
    {
        const auto& fields = indexInfo.Fields( );
        auto fieldCount = fields.size( );
        auto className = CSharpHelper::GetEntityIndexClassName( indexInfo );
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        WriteLine( L"    public class {}", className );
        WriteLine( L"    {" );
        for ( size_t i = 1; i < fieldCount; i++ )
        {
            CreateEntityIndexIntermediateClass( classInfo, indexInfo, i );
        }

        CreateEntityIndexFinalClass( classInfo, indexInfo );

        const auto& field = *fields.front( );
        auto keyType = CSharpHelper::GetNotNullableBaseType( field );

        if ( fieldCount > 1 )
        {
            const auto& nextField = *fields[ 1 ];
            WriteLine( L"        readonly SortedListEx<{}, By{}> _entries = new SortedListEx<{}, By{}>( );", keyType, nextField.Name( ), keyType, nextField.Name( ) );
        }
        else
        {
            WriteLine( L"        readonly SortedListEx<{}, ById> _entries = new SortedListEx<{}, ById>( );", keyType, keyType );
        }
        WriteLine( );
        WriteLine( L"        public {}( )", className );
        WriteLine( L"        {" );
        WriteLine( L"        }" );
        WriteLine( );
        CreateIndexGetByIndex( classInfo, indexInfo );
        WriteLine( L"    }" );
        WriteLine( );
    }

    void CSharpEntityChangesGenerator::CreateEntityIndexIntermediateClass( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t fieldIndex )
    {
        const auto& fields = indexInfo.Fields( );
        auto fieldCount = fields.size( );
        auto className = CSharpHelper::GetEntityIndexClassName( indexInfo );
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );

        for ( size_t i = 1; i < fieldCount; i++ )
        {
            const auto& field = *fields[ i ];

            WriteLine( L"        public class By{}", field.Name( ) );
            WriteLine( L"        {" );
            auto keyType = CSharpHelper::GetNotNullableBaseType( field );
            if ( i != ( fieldCount - 1 ) )
            {
                const auto& nextField = *fields[ i + 1 ];
                WriteLine( L"            readonly SortedListEx<{}, By{}> _entries = new SortedListEx<{}, By{}>( );", keyType, nextField.Name( ), keyType, nextField.Name( ) );
            }
            else
            {
                WriteLine( L"            readonly SortedListEx<{}, ById> _entries = new SortedListEx<{}, ById>( );", keyType, keyType );
            }
            WriteLine( L"            List<{}> _emptyKeys = new List<{}>( );", keyType, keyType );
            WriteLine( );
            WriteLine( L"            public By{}( )", field.Name( ) );
            WriteLine( L"            {" );
            WriteLine( L"            }" );
            WriteLine( );
            WriteLine( L"            void RemoveEmptyKeys( )" );
            WriteLine( L"            {" );
            WriteLine( L"                var emptyKeyCount = _emptyKeys.Count;" );
            WriteLine( L"                for ( int i = 0; i < emptyKeyCount; i++ )" );
            WriteLine( L"                {" );
            WriteLine( L"                    _entries.Remove( _emptyKeys[ i ] );" );
            WriteLine( L"                }" );
            WriteLine( L"                _emptyKeys.Clear( );" );
            WriteLine( L"            }" );
            WriteLine( );
            WriteLine( L"            public bool GetAll([DisallowNull] IList<{}> result )", entityClassName );
            WriteLine( L"            {" );
            WriteLine( L"                foreach( var entry in _entries )" );
            WriteLine( L"                {" );
            WriteLine( L"                    if( entry.Value.GetAll( result ) == false )" );
            WriteLine( L"                    {" );
            WriteLine( L"                        _emptyKeys.Add( entry.Key );" );
            WriteLine( L"                    }" );
            WriteLine( L"                }" );
            WriteLine( L"                RemoveEmptyKeys( );" );
            WriteLine( L"                return _entries.Count > 0;" );
            WriteLine( L"            }" );
            WriteLine( );
            WriteLine( L"        }" );
        }
    }
    void CSharpEntityChangesGenerator::CreateEntityIndexFinalClass( const ClassInfo& classInfo, const IndexInfo& indexInfo )
    {
        const auto& fields = indexInfo.Fields( );
        auto fieldCount = fields.size( );
        auto className = CSharpHelper::GetEntityIndexClassName( indexInfo );
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );

        WriteLine( L"        public class ById" );
        WriteLine( L"        {" );
        auto primaryKey = classInfo.PrimaryKey( );
        auto nextKeyType = CSharpHelper::GetNotNullableBaseType( *primaryKey );

        WriteLine( L"            readonly SortedWeakReferenceList<{}, {}> _entries = new SortedWeakReferenceList<{}, {}>( );", nextKeyType, entityClassName, nextKeyType, entityClassName );
        WriteLine( L"            public ById( )" );
        WriteLine( L"            {" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public void Add( {} entity )", entityClassName );
        WriteLine( L"            {" );
        WriteLine( L"                if( _entries.TryGetValue(entity.Id, out var weakReference ) )" );
        WriteLine( L"                {" );
        WriteLine( L"                    weakReference.SetTarget( entity );" );
        WriteLine( L"                }" );
        WriteLine( L"                else" );
        WriteLine( L"                {" );
        WriteLine( L"                    _entries.Add( entity.Id, new WeakReference<{}>( entity, false ) );", entityClassName );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public bool GetById( Guid id, out {}? entity )", entityClassName );
        WriteLine( L"            {" );
        WriteLine( L"                entity = null;" );
        WriteLine( L"                if ( _entries.TryGetValue( id, out var weakReference ) )" );
        WriteLine( L"                {" );
        WriteLine( L"                    if ( weakReference.TryGetTarget( out entity ) == false )" );
        WriteLine( L"                    {" );
        WriteLine( L"                        _entries.Remove( id );" );
        WriteLine( L"                    }" );
        WriteLine( L"                }" );
        WriteLine( L"                return _entries.Count > 0;" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public bool GetFrom(Guid id, [DisallowNull] IList<{}> result )", entityClassName );
        WriteLine( L"            {" );
        WriteLine( L"                return _entries.From( id, result );" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public bool GetUntil(Guid id, [DisallowNull] IList<{}> result )", entityClassName );
        WriteLine( L"            {" );
        WriteLine( L"                return _entries.Until( id, result );" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public bool GetOver(Guid firstId, Guid lastId, [DisallowNull] IList<{}> result )", entityClassName );
        WriteLine( L"            {" );
        WriteLine( L"                return _entries.Over( firstId, lastId, result );" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"            public bool GetAll([DisallowNull] IList<{}> result )", entityClassName );
        WriteLine( L"            {" );
        WriteLine( L"                return _entries.All( result );" );
        WriteLine( L"            }" );
        WriteLine( );
        WriteLine( L"        }" );
        WriteLine( );

    }


    void CSharpEntityChangesGenerator::CreateNullableEntityUniqueIndexClass( const ClassInfo& classInfo, const IndexInfo& indexInfo )
    {
        auto className = CSharpHelper::GetEntityNullableIndexClassName( indexInfo );
        WriteLine( L"    public class {}", className );
        WriteLine( L"    {" );
        WriteLine( L"    }" );
        WriteLine( );
    }

    void CSharpEntityChangesGenerator::CreateNullableEntityIndexClass( const ClassInfo& classInfo, const IndexInfo& indexInfo )
    {
        auto className = CSharpHelper::GetEntityNullableIndexClassName( indexInfo );
        WriteLine( L"    public class {}", className );
        WriteLine( L"    {" );
        WriteLine( L"    }" );
        WriteLine( );
    }

    


    void CSharpEntityChangesGenerator::CreateIndexGetByIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo )
    {
        const auto& indexMembers = indexInfo.Fields( );
        auto indexMemberCount = indexMembers.size( );
        for ( size_t j = 0; j < indexMemberCount; j++ )
        {
            CreateIndexGetByIndex( classInfo, indexInfo, j + 1 );
            if ( indexInfo.HasNullableElements( j + 1 ) )
            {
                CreateIndexGetByNullableIndex( classInfo, indexInfo, j + 1 );
            }
            if ( indexInfo.IsTimeSeries( j + 1 ) )
            {
                CreateIndexGetByIndexAt( classInfo, indexInfo, j + 1 );
            }
            if ( indexInfo.IsRange( j + 1 ) )
            {
                CreateIndexGetByIndexFrom( classInfo, indexInfo, j + 1 );
                CreateIndexGetByIndexUntil( classInfo, indexInfo, j + 1 );
                CreateIndexGetByIndexOver( classInfo, indexInfo, j + 1 );
            }
        }
    }
    void CSharpEntityChangesGenerator::CreateIndexGetByIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        auto returnType = className + L"?";
        if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) == false )
        {
            returnType = Format( L"List<{}>", className );
        }
        auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
        WriteLine( L"        {" );
        WriteLine( L"            throw new NotImplementedException();" );
        WriteLine( L"        }" );
        WriteLine( );
    }
    void CSharpEntityChangesGenerator::CreateIndexGetByNullableIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByNullableIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        auto returnType = Format( L"List<{}>", className );
        auto arguments = CSharpHelper::GetByNullableIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
        WriteLine( L"        {" );
        WriteLine( L"            throw new NotImplementedException();" );
        WriteLine( L"        }" );
        WriteLine( );

    }
    void CSharpEntityChangesGenerator::CreateIndexGetByIndexAt( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexAtFunctionName( classInfo, indexInfo, indexMemberCount );
        auto returnType = className + L"?";
        if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) == false )
        {
            returnType = Format( L"List<{}>", className );
        }
        auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
        WriteLine( L"        {" );
        WriteLine( L"            throw new NotImplementedException();" );
        WriteLine( L"        }" );
        WriteLine( );
    }
    void CSharpEntityChangesGenerator::CreateIndexGetByIndexFrom( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexFromFunctionName( classInfo, indexInfo, indexMemberCount );
        auto returnType = Format( L"List<{}>", className );
        auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
        WriteLine( L"        {" );
        WriteLine( L"            throw new NotImplementedException();" );
        WriteLine( L"        }" );
        WriteLine( );
    }
    void CSharpEntityChangesGenerator::CreateIndexGetByIndexUntil( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexUntilFunctionName( classInfo, indexInfo, indexMemberCount );
        auto returnType = Format( L"List<{}>", className );
        auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
        WriteLine( L"        {" );
        WriteLine( L"            throw new NotImplementedException();" );
        WriteLine( L"        }" );
        WriteLine( );
    }
    void CSharpEntityChangesGenerator::CreateIndexGetByIndexOver( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexOverFunctionName( classInfo, indexInfo, indexMemberCount );
        auto returnType = Format( L"List<{}>", className );
        auto arguments = CSharpHelper::GetByIndexFunctionOverParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
        WriteLine( L"        {" );
        WriteLine( L"            throw new NotImplementedException();" );
        WriteLine( L"        }" );
        WriteLine( );
    }

    void CSharpEntityChangesGenerator::CreateNestedGetByIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
    }
    void CSharpEntityChangesGenerator::CreateNestedGetByNullableIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
    }
    void CSharpEntityChangesGenerator::CreateNestedGetByIndexAt( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
    }
    void CSharpEntityChangesGenerator::CreateNestedGetByIndexFrom( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
    }
    void CSharpEntityChangesGenerator::CreateNestedGetByIndexUntil( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
    }
    void CSharpEntityChangesGenerator::CreateNestedGetByIndexOver( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
    }

    void CSharpEntityChangesGenerator::CreateEntityChanges( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        WriteLine( L"    public class EntityChanges" );
        WriteLine( L"    {" );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];

            const auto& indexes = classInfo.Indexes( );
            auto indexCount = indexes.size( );
            for ( size_t i = 0; i < indexCount; i++ )
            {
                const auto& index = *indexes[ i ];
                auto entityIndexClassName = CSharpHelper::GetEntityIndexClassName( index );
                WriteLine( L"        readonly {} _{} = new {}( );", entityIndexClassName, entityIndexClassName.FirstToLower( ), entityIndexClassName );
                if ( index.HasNullableElements( ) )
                {
                    auto entityNullableIndexClassName = CSharpHelper::GetEntityNullableIndexClassName( index );
                    WriteLine( L"        readonly {} _{} = new {}( );", entityNullableIndexClassName, entityNullableIndexClassName.FirstToLower( ), entityNullableIndexClassName );
                }
            }
        }

        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateGetAll( classInfo );
            CreateGetByIndex( classInfo );
        }

        WriteLine( L"    }" );
        WriteLine( );
    }

    void CSharpEntityChangesGenerator::CreateGetAll( const ClassInfo& classInfo )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto dataClassName = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetAllFunctionName( classInfo );
        functions_.insert( functionName );

        


        WriteLine( L"        public List<{}> {}( )", entityClassName, functionName );
        WriteLine( L"        {" );
        WriteLine( L"            throw new NotImplementedException();" );
        WriteLine( L"        }" );
        WriteLine( );
    }
    void CSharpEntityChangesGenerator::CreateGetByIndex( const ClassInfo& classInfo )
    {
        auto indexes = classInfo.Indexes( );
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
    void CSharpEntityChangesGenerator::CreateGetByIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            auto dataClassName = CSharpHelper::GetDataType( classInfo );

            auto entityIndexVariableName = Format(L"_{}",CSharpHelper::GetEntityIndexClassName( indexInfo ).FirstToLower());

            if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) )
            {
                auto returnType = entityClassName + L"?";
                WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
                WriteLine( L"        {" );
                WriteLine( L"            return {}.{}( {} );", entityIndexVariableName, functionName, callArguments );
                WriteLine( L"        }" );
            }
            else
            {
                auto returnType = Format( L"List<{}>", entityClassName );
                WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
                WriteLine( L"        {" );
                WriteLine( L"            return {}.{}( {} );", entityIndexVariableName, functionName, callArguments );
                WriteLine( L"        }" );
            }
            WriteLine( );
        }
    }
    void CSharpEntityChangesGenerator::CreateGetByNullableIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        
    }
    void CSharpEntityChangesGenerator::CreateGetByIndexAt( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexAtFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            auto dataClassName = CSharpHelper::GetDataType( classInfo );

            auto entityIndexVariableName = Format( L"_{}", CSharpHelper::GetEntityIndexClassName( indexInfo ).FirstToLower( ) );

            if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) )
            {
                auto returnType = entityClassName + L"?";
                WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
                WriteLine( L"        {" );
                WriteLine( L"            return {}.{}( {} );", entityIndexVariableName, functionName, callArguments );
                WriteLine( L"        }" );
            }
            else
            {
                auto returnType = Format( L"List<{}>", entityClassName );
                WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
                WriteLine( L"        {" );
                WriteLine( L"            return {}.{}( {} );", entityIndexVariableName, functionName, callArguments );
                WriteLine( L"        }" );
            }
            WriteLine( );
        }
    }
    void CSharpEntityChangesGenerator::CreateGetByIndexFrom( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexFromFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            auto dataClassName = CSharpHelper::GetDataType( classInfo );
            auto returnType = Format( L"List<{}>", entityClassName );

            auto entityIndexVariableName = Format( L"_{}", CSharpHelper::GetEntityIndexClassName( indexInfo ).FirstToLower( ) );

            WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            return {}.{}( {} );", entityIndexVariableName, functionName, callArguments );
            WriteLine( L"        }" );
            WriteLine( );
        }
    }
    void CSharpEntityChangesGenerator::CreateGetByIndexUntil( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexUntilFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            auto dataClassName = CSharpHelper::GetDataType( classInfo );
            auto returnType = Format( L"List<{}>", entityClassName );

            auto entityIndexVariableName = Format( L"_{}", CSharpHelper::GetEntityIndexClassName( indexInfo ).FirstToLower( ) );

            WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            return {}.{}( {} );", entityIndexVariableName, functionName, callArguments );
            WriteLine( L"        }" );
            WriteLine( );
        }
    }
    void CSharpEntityChangesGenerator::CreateGetByIndexOver( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto functionName = CSharpHelper::GetByIndexOverFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto arguments = CSharpHelper::GetByIndexFunctionOverParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionOverCallParameters( classInfo, indexInfo, indexMemberCount );
            auto dataClassName = CSharpHelper::GetDataType( classInfo );

            auto entityIndexVariableName = Format( L"_{}", CSharpHelper::GetEntityIndexClassName( indexInfo ).FirstToLower( ) );

            auto returnType = Format( L"List<{}>", entityClassName );
            WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            return {}.{}( {} );", entityIndexVariableName, functionName, callArguments );
            WriteLine( L"        }" );
            WriteLine( );
        }
    }

}