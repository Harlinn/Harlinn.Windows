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

#include "Generator.h"
#include "SqlServerHelper.h"
#include "CSharpHelper.h"

namespace Harlinn::ODBC::Tool
{
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
        auto className = CSharpHelper::GetEntityIndexClassName( indexInfo );
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        
        WriteLine( L"    public class {}", className );
        WriteLine( L"    {" );
        if ( fieldCount == 1 )
        {
            const auto& field = *fields[ 0 ];
            auto variableName = CSharpHelper::GetInputArgumentName( field );
            auto variableType = CSharpHelper::GetNotNullableBaseType( field );
            auto keyType = CSharpHelper::GetNotNullableBaseType( field );
            auto entityClassName = CSharpHelper::GetEntityType( classInfo );
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
                WriteLine( L"            {");
                WriteLine( L"                if ( _entries.TryGetValue( {}, out var weakReference ) )", variableName );
                WriteLine( L"                {");
                WriteLine( L"                    weakReference.SetTarget( entity );");
                WriteLine( L"                }");
                WriteLine( L"                else");
                WriteLine( L"                {");
                WriteLine( L"                    _entries.Add( {}, new WeakReference<{}>( entity, false ) );", variableName, entityClassName );
                WriteLine( L"                }");
                WriteLine( L"            }");
                WriteLine( L"            else");
                WriteLine( L"            {");
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
            WriteLine( L"        {");
            WriteLine( L"            entity = null;");
            WriteLine( L"            if ( _entries.TryGetValue( {}, out var weakReference ) )", variableName );
            WriteLine( L"            {");
            WriteLine( L"                if ( weakReference.TryGetTarget( out entity ) == false )");
            WriteLine( L"                {");
            WriteLine( L"                    _entries.Remove( {} );", variableName );
            WriteLine( L"                }");
            WriteLine( L"            }");
            WriteLine( L"            return _entries.Count > 0;");
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
        }
        else
        {
            for ( size_t i = 0; i < fieldCount - 1; i++ )
            {
                const auto& field = *fields[ i ];
                WriteLine( L"        public class By{}", field.Name( ) );
                WriteLine( L"        {" );
                auto keyType = CSharpHelper::GetNotNullableBaseType( field );
                const auto& nextField = *fields[ i + 1 ];
                WriteLine( L"            readonly SortedListEx<{}, By{}> _entries = new SortedListEx<{}, By{}>( );", keyType, nextField.Name( ), keyType, nextField.Name( ) );
                WriteLine( L"        }" );
            }
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
        }
        WriteLine( );
        WriteLine( L"    }" );
    }

    void CSharpEntityChangesGenerator::CreateEntityIndexClass( const ClassInfo& classInfo, const IndexInfo& indexInfo )
    {
        const auto& fields = indexInfo.Fields( );
        auto fieldCount = fields.size( );
        auto className = CSharpHelper::GetEntityIndexClassName( indexInfo );
        WriteLine( L"    public class {}", className );
        WriteLine( L"    {" );
        for ( size_t i = 0; i < fieldCount; i++ )
        {
            const auto& field = *fields[ i ];
            if ( i < fieldCount )
            {

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
                WriteLine( L"        }" );
            }
        }
        WriteLine( L"        public class ById" );
        WriteLine( L"        {" );
        auto primaryKey = classInfo.PrimaryKey( );
        auto nextKeyType = CSharpHelper::GetNotNullableBaseType( *primaryKey );
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        WriteLine( L"            readonly SortedListEx<{}, WeakReference<{}>> _entries = new SortedListEx<{}, WeakReference<{}>>( );", nextKeyType, entityClassName, nextKeyType, entityClassName );
        WriteLine( L"        }" );
        WriteLine( L"    }" );
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
                WriteLine( L"        readonly {} _{} = new {}( );", entityIndexClassName, entityIndexClassName.FirstToLower(), entityIndexClassName );
                if ( index.HasNullableElements( ) )
                {
                    auto entityNullableIndexClassName = CSharpHelper::GetEntityNullableIndexClassName( index );
                    WriteLine( L"        readonly {} _{} = new {}( );", entityNullableIndexClassName, entityNullableIndexClassName.FirstToLower( ), entityNullableIndexClassName );
                }
            }
        }
        WriteLine( L"    }" );
        WriteLine( );
    }
}