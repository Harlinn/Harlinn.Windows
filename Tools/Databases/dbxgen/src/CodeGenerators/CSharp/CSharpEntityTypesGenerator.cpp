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

namespace Harlinn::Tools::DbXGen::CodeGenerators::CSharp
{
    using namespace Harlinn::Tools::DbXGen::Metadata;

    void CSharpEntityTypesGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto nspace = Options( ).Namespace( L"." );

        const auto& dataTypesOptions = Options( ).Owner( ).Owner( ).Data( ).DataTypes( );
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
            CreateEntityType( classInfo );

        }
        CreateFactory( );

        WriteLine( L"}" );
        Flush( );
    }

    void CSharpEntityTypesGenerator::CreateEntityType( const ClassInfo& classInfo )
    {
        auto entityClassName = CSharpHelper::GetEntityType( classInfo );
        auto dataClassName = CSharpHelper::GetDataType( classInfo );
        auto entityBaseClassName = CSharpHelper::GetEntityTypeBaseClassName( classInfo );
        const auto& ownMembers = classInfo.OwnMembers( );
        auto memberCount = ownMembers.size( );

        if ( classInfo.Abstract( ) )
        {
            WriteLine( L"    public abstract class {} : {}", entityClassName, entityBaseClassName );
        }
        else
        {
            WriteLine( L"    public class {} : {}", entityClassName, entityBaseClassName );
        }
        WriteLine( L"    {" );

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *ownMembers[ i ];
            auto memberType = member.Type( );
            if ( memberType == MemberInfoType::Reference || memberType == MemberInfoType::TimeSeries )
            {
                auto fieldName = CSharpHelper::GetMemberFieldName( member );
                WriteLine( L"        WeakReference? {}Reference = null;", fieldName );
            }
        }

        if ( classInfo.Abstract( ) == false )
        {
            WriteLine( L"        public {}( [DisallowNull] EntityContext entityContext, [DisallowNull] {} data )", entityClassName, dataClassName );
            WriteLine( L"            : base( entityContext, data )" );
            WriteLine( L"        {" );
            WriteLine( L"        }" );
            WriteLine( );
        }
        else
        {
            WriteLine( L"        protected {}( [DisallowNull] EntityContext entityContext, [DisallowNull] {} data )", entityClassName, dataClassName );
            WriteLine( L"            : base( entityContext, data )" );
            WriteLine( L"        {" );
            WriteLine( L"        }" );
            WriteLine( );
        }

        if ( classInfo.IsTopLevel( ) )
        {
            WriteLine( L"        public EntityContext? Context => (EntityContext?)_Context;", dataClassName );
            WriteLine( );
            WriteLine( L"        protected EntityContext CheckedContext");
            WriteLine( L"        {");
            WriteLine( L"            get");
            WriteLine( L"            {");
            WriteLine( L"                var context = Context;");
            WriteLine( L"                if ( context is null )");
            WriteLine( L"                {");
            WriteLine( L"                    throw new InvalidOperationException( \"Context is null\" );");
            WriteLine( L"                }");
            WriteLine( L"                return context;");
            WriteLine( L"            }");
            WriteLine( L"        }" );
            WriteLine( );
        }

        
        if ( memberCount )
        {
            WriteLine( L"        private {} GetData( ) ", dataClassName );
            WriteLine( L"        {" );
            WriteLine( L"            return ({})base._GetData( );", dataClassName );
            WriteLine( L"        }" );
            WriteLine( );
            for ( size_t i = 0; i < memberCount; i++ )
            {
                const auto& member = *ownMembers[ i ];
                if ( member.PrimaryKey( ) == false )
                {
                    CreateMember( classInfo, member );
                }
            }
        }


        WriteLine( L"    }" );
        WriteLine( );
    }

    void CSharpEntityTypesGenerator::CreateMember( const ClassInfo& classInfo, const MemberInfo& member )
    {
        auto memberType = member.Type( );
        if ( memberType <= MemberInfoType::Binary )
        {
            CreateBasicMember( classInfo, member );
        }
        else if ( memberType == MemberInfoType::Reference )
        {
            CreateReferenceMember( classInfo, member );
        }
        else if ( memberType == MemberInfoType::Collection )
        {
            CreateCollectionMember( classInfo, member );
        }
        else if ( memberType == MemberInfoType::TimeSeries )
        {
            CreateTimeSeriesMember( classInfo, member );
        }
    }

    void CSharpEntityTypesGenerator::CreateBasicMember( const ClassInfo& classInfo, const MemberInfo& member )
    {
        auto typeName = CSharpHelper::GetMemberFieldType( member );
        auto propertyName = member.Name( ).FirstToUpper( );

        WriteLine( L"        public {} {}", typeName, propertyName );
        WriteLine( L"        {" );
        WriteLine( L"            get => GetData( ).{};", propertyName );
        WriteLine( L"            set" );
        WriteLine( L"            {" );
        WriteLine( L"                var data = GetData( );" );
        WriteLine( L"                if( data.{} != value )", propertyName );
        WriteLine( L"                {" );
        WriteLine( L"                    OnPropertyChanging( );" );
        WriteLine( L"                    data = GetData( );" );
        WriteLine( L"                    data.{} = value;", propertyName );
        WriteLine( L"                    OnPropertyChanged( );" );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( );
    }
    void CSharpEntityTypesGenerator::CreateReferenceMember( const ClassInfo& classInfo, const MemberInfo& member )
    {
        const auto& referenceMemberInfo = static_cast< const ReferenceMemberInfo& >( member );
        auto typeName = CSharpHelper::GetMemberFieldType( member );
        auto propertyName = member.Name( ).FirstToUpper( );
        auto referencedClassInfo = referenceMemberInfo.ReferencedType( );
        auto referencedEntityClassName = CSharpHelper::GetEntityType( *referencedClassInfo );

        auto fieldName = CSharpHelper::GetMemberFieldName( member );
        auto weakReferenceName = Format( L"{}Reference", fieldName );
        auto entityContextFunctionName = CSharpHelper::GetByIdFunctionName( *referencedClassInfo );

        WriteLine( L"        public {} {}Id", typeName, propertyName );
        WriteLine( L"        {" );
        WriteLine( L"            get => GetData( ).{};", propertyName );
        WriteLine( L"            set" );
        WriteLine( L"            {" );
        WriteLine( L"                var data = GetData( );" );
        WriteLine( L"                if( data.{} != value )", propertyName );
        WriteLine( L"                {" );
        WriteLine( L"                    OnPropertyChanging( );" );
        WriteLine( L"                    OnPropertyChanging( \"{}\", false );", propertyName );
        WriteLine( L"                    data = GetData( );" );
        WriteLine( L"                    data.{} = value;", propertyName );
        WriteLine( L"                    OnPropertyChanged( );" );
        WriteLine( L"                    OnPropertyChanged( \"{}\" );", propertyName );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( );

        WideString nullable;
        if ( member.Nullable( ) )
        {
            nullable = L"?";
        }
        WriteLine( L"        public {}{} {}", referencedEntityClassName, nullable, propertyName );
        WriteLine( L"        {" );
        WriteLine( L"            get" );
        WriteLine( L"            {" );
        WriteLine( L"                if({} != null)", weakReferenceName );
        WriteLine( L"                {" );
        WriteLine( L"                    var result = ({}?){}.Target;", referencedEntityClassName, weakReferenceName );
        WriteLine( L"                    if( result != null )" );
        WriteLine( L"                    {" );
        WriteLine( L"                        return result;" );
        WriteLine( L"                    }" );
        WriteLine( L"                }" );
        WriteLine( L"                var data = GetData( );" );
        WriteLine( L"                var context = CheckedContext;" );
        if ( member.Nullable( ) )
        {
            auto variableName = propertyName.FirstToLower( ) + L"Id";
            WriteLine( L"                if( data.{} is Guid {} )", propertyName, variableName );
            WriteLine( L"                {" );
            WriteLine( L"                    var entity = context.{}( {} );", entityContextFunctionName, variableName );
            WriteLine( L"                    if( entity != null )" );
            WriteLine( L"                    {" );
            WriteLine( L"                        {} = new WeakReference( entity );", weakReferenceName );
            WriteLine( L"                    }" );
            WriteLine( L"                    return entity;" );
            WriteLine( L"                }" );
            WriteLine( L"                return null;" );
        }
        else
        {
            WriteLine( L"                var entity = context.{}( data.{} );", entityContextFunctionName, propertyName );
            WriteLine( L"                if( entity != null )" );
            WriteLine( L"                {" );
            WriteLine( L"                    {} = new WeakReference( entity );", weakReferenceName );
            WriteLine( L"                }" );
            WriteLine( L"                else" );
            WriteLine( L"                {" );
            WriteLine( L"                    var message = $\"Cannot find the {} object identified by {{data.{}}}\";", referencedEntityClassName, propertyName );
            WriteLine( L"                    throw new Exception( message );" );
            WriteLine( L"                }" );
            WriteLine( L"                return entity;" );
        }
        WriteLine( L"            }" );
        WriteLine( L"            set" );
        WriteLine( L"            {" );
        if ( member.Nullable( ) )
        {
            WriteLine( L"                {}Id = value != null? value.Id : null;", propertyName );
        }
        else
        {
            WriteLine( L"                {}Id = value != null? value.Id : Guid.Empty;", propertyName );
        }
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( );

    }

    void CSharpEntityTypesGenerator::CreateCollectionMember( const ClassInfo& classInfo, const MemberInfo& member )
    {

    }
    void CSharpEntityTypesGenerator::CreateTimeSeriesMember( const ClassInfo& classInfo, const MemberInfo& member )
    {
        CreateReferenceMember( classInfo, member );
    }


    void CSharpEntityTypesGenerator::CreateFactory( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        WriteLine( L"    public class EntityFactory : IBaseEntityFactory<Kind>");
        WriteLine( L"    {");
        WriteLine( L"        IBaseDataFactory<Kind> _dataFactory;");
        WriteLine( L"        public EntityFactory([DisallowNull] IBaseDataFactory<Kind> dataFactory)");
        WriteLine( L"        {");
        WriteLine( L"            _dataFactory = dataFactory;");
        WriteLine( L"        }");
        WriteLine( L"        public BaseEntity<Kind> Create([DisallowNull] EntityContextBase<Kind> entityContextBase, Kind objectType)");
        WriteLine( L"        {");
        WriteLine( L"            var dataObject = _dataFactory.Create(objectType);");
        WriteLine( L"            return Create(entityContextBase, dataObject);");
        WriteLine( L"        }");
        WriteLine();
        WriteLine( L"        public BaseEntity<Kind> Create([DisallowNull] EntityContextBase<Kind> entityContextBase, [DisallowNull] BaseDataGuid<Kind> dataObject)");
        WriteLine( L"        {");
        WriteLine( L"            var entityContext = (EntityContext)entityContextBase;" );
        WriteLine( L"            var kind = dataObject.GetObjectType();");
        WriteLine( L"            switch (kind)");
        WriteLine( L"            {");
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                auto entityTypeName = CSharpHelper::GetEntityType( classInfo );
                auto dataTypeName = CSharpHelper::GetDataType( classInfo );

                WriteLine( L"                case Kind.{}:", classInfo.Name( ) );
                WriteLine( L"                {" );
                WriteLine( L"                    return new {}( entityContext, ({})dataObject );", entityTypeName, dataTypeName );
                WriteLine( L"                }" );
            }
        }
        WriteLine( L"                default:");
        WriteLine( L"                {");
        WriteLine( L"                    throw new ArgumentException($\"Cannot create an entity object for kind={kind}.\", \"kind\");");
        WriteLine( L"                }");
        WriteLine( L"            }");
        WriteLine( L"        }");
        WriteLine( L"    }" );
    }
}