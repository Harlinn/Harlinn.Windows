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
#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"


namespace Harlinn::Tools::DbXGen::CodeGenerators::CSharp::Databases::MsSql
{
    using namespace Harlinn::Tools::DbXGen::Metadata;
    using namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql;

    void CSharpMsSqlSimpleDatabaseReadersGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        const auto& dataTypesOptions = Options( ).Owner( ).Owner( ).Owner( ).Data( ).DataTypes( );
        auto dataTypesNamespace = dataTypesOptions.Namespace( L"." );

        auto nspace = Options( ).Namespace( L"." );
        WriteLine( L"using System;" );
        WriteLine( L"using System.Diagnostics.CodeAnalysis;" );
        WriteLine( L"using System.IO;" );
        WriteLine( );
        WriteLine( L"using Microsoft.Data.SqlClient;" );
        WriteLine( L"using Microsoft.Extensions.Logging;" );
        WriteLine( );
        WriteLine( L"using Harlinn.Common.Core.Net;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Data;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Data.SqlClient;" );
        WriteLine( L"using Harlinn.Common.Core.Net.IO;" );
        WriteLine( );
        WriteLine( L"using {};", dataTypesNamespace );
        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );

        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateReader( classInfo );
        }

        WriteLine( L"}" );

        Flush();
    }

    void CSharpMsSqlSimpleDatabaseReadersGenerator::CreateReader( const ClassInfo& classInfo )
    {
        auto className = CSharpHelper::GetSimpleDataReaderName( classInfo );
        WideString baseClassName = L"DataReaderWrapper";
        if ( classInfo.IsTopLevel( ) == false )
        {
            auto baseClass = classInfo.BaseClass( );
            baseClassName = CSharpHelper::GetSimpleDataReaderName( *baseClass );
        }

        if ( classInfo.Abstract( ) )
        {
            WriteLine( L"    public abstract class {} : {}", className, baseClassName );
        }
        else
        {
            WriteLine( L"    public class {} : {}", className, baseClassName );
        }
        WriteLine( L"    {" );
        CreateQuery( classInfo );
        CreateFieldIds( classInfo );
        WriteLine( L"        public {}( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )", className );
        WriteLine( L"            : base(loggerFactory, sqlDataReader, ownsReader )" );
        WriteLine( L"        {" );
        WriteLine( L"        }" );
        WriteLine( );
        CreateAccessors( classInfo );
        CreateWriteColumns( classInfo );
        CreateGetDataObject( classInfo );
        WriteLine( L"    }" );
        WriteLine( );
    }
    void CSharpMsSqlSimpleDatabaseReadersGenerator::CreateQuery( const ClassInfo& classInfo )
    {

        auto topLevelClass = classInfo.TopLevelClass( );

        auto className = CSharpHelper::GetSimpleDataReaderName( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = MsSqlHelper::GetColumnName( *primaryKey );
        auto viewName = MsSqlHelper::GetViewName( classInfo );
        const auto& members = classInfo.PersistentMembers();
        auto memberCount = members.size( );
        auto shortName = classInfo.ShortName( ).ToLower( );

        if ( classInfo.IsTopLevel( ) )
        {
            WriteLine( L"        public const string BaseQuery = \"SELECT \\r\\n\" +" );
        }
        else
        {
            WriteLine( L"        public new const string BaseQuery = \"SELECT \\r\\n\" +" );
        }

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto owner = member.Owner( );
            auto memberName = member.Name( );
            if ( i < memberCount - 1 || member.PrimaryKey( ) )
            {
                WriteLine( L"            \"  {}.[{}], \\r\\n\" +", shortName, memberName );

                if ( member.PrimaryKey( ) && topLevelClass->HasDescendants( ) )
                {
                    if ( i < memberCount - 1 )
                    {
                        WriteLine( L"            \"  {}.[EntityType], \\r\\n\" +", shortName );
                    }
                    else
                    {
                        WriteLine( L"            \"  {}.[EntityType] \\r\\n\" +", shortName );
                    }
                }
            }
            else
            {
                WriteLine( L"            \"  {}.[{}] \\r\\n\" +", shortName, memberName );

            }
        }
        WriteLine( L"            \"FROM [{}] {} \\r\\n\";", viewName, shortName );
        WriteLine( );
        if ( classInfo.IsTopLevel( ) )
        {
            WriteLine( L"        public const string BaseViewName = \"{}\";", viewName );
            WriteLine( L"        public const string ViewAliasName = \"{}\";", shortName );
        }
        else
        {
            WriteLine( L"        public new const string BaseViewName = \"{}\";", viewName );
            WriteLine( L"        public new const string ViewAliasName = \"{}\";", shortName );
        }
        WriteLine( );
    }
    void CSharpMsSqlSimpleDatabaseReadersGenerator::CreateFieldIds( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.OwnPersistentMembers();
        if ( members.empty( ) == false )
        {
            size_t id = 0;
            if ( classInfo.IsTopLevel( ) )
            {
                for ( const auto& member : members )
                {
                    WriteLine( L"        public const int {}_FIELD_ID = {};", member->Name( ).ToUpper( ), id );
                    id++;
                    if ( member->PrimaryKey( ) && classInfo.HasDescendants( ) )
                    {
                        WriteLine( L"        public const int ENTITYTYPE_FIELD_ID = {};", id );
                        id++;
                    }
                }
            }
            else
            {
                auto baseClass = classInfo.BaseClass( );
                while ( baseClass )
                {
                    id += baseClass->OwnPersistentMembers( ).size( );
                    baseClass = baseClass->BaseClass( );
                }

                for ( const auto& member : members )
                {
                    WriteLine( L"        public const int {}_FIELD_ID = {};", member->Name( ).ToUpper( ), id );
                    id++;
                }
            }
            WriteLine( );
        }
    }
    void CSharpMsSqlSimpleDatabaseReadersGenerator::CreateAccessors( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.OwnPersistentMembers( );
        for ( const auto& member : members )
        {
            auto fieldId = Format( L"{}_FIELD_ID", member->Name( ).ToUpper( ) );
            auto getFunctionName = CSharpHelper::GetDataReaderGetFunctionName( *member );
            auto propertyType = CSharpHelper::GetMemberFieldType( *member );
            auto propertyName = member->Name( ).FirstToUpper( );
            auto memberType = member->Type( );

            WriteLine( L"        public {} {}", propertyType, propertyName );
            WriteLine( L"        {" );
            WriteLine( L"            get" );
            WriteLine( L"            {" );
            if ( memberType == MemberInfoType::DateTime )
            {
                if ( member->Nullable( ) )
                {
                    WriteLine( L"                var v = {}( {} );", getFunctionName, fieldId );
                    WriteLine( L"                if( v is long value )" );
                    WriteLine( L"                {" );
                    WriteLine( L"                    return new DateTime( value , DateTimeKind.Utc );" );
                    WriteLine( L"                }" );
                    WriteLine( L"                return null;" );
                }
                else
                {
                    WriteLine( L"                return new DateTime( {}( {} ), DateTimeKind.Utc );", getFunctionName, fieldId );
                }
            }
            else if ( memberType == MemberInfoType::TimeSpan )
            {
                if ( member->Nullable( ) )
                {
                    WriteLine( L"                var v = {}( {} );", getFunctionName, fieldId );
                    WriteLine( L"                if( v is long value )" );
                    WriteLine( L"                {" );
                    WriteLine( L"                    return new TimeSpan( value );" );
                    WriteLine( L"                }" );
                    WriteLine( L"                return null;" );
                }
                else
                {
                    WriteLine( L"                return new TimeSpan( {}( {} ) );", getFunctionName, fieldId );
                }
            }
            else if ( memberType == MemberInfoType::Currency )
            {
                if ( member->Nullable( ) )
                {
                    WriteLine( L"                var v = {}( {} );", getFunctionName, fieldId );
                    WriteLine( L"                if( v is long value )" );
                    WriteLine( L"                {" );
                    WriteLine( L"                    return Currency.FromScaled( value );" );
                    WriteLine( L"                }" );
                    WriteLine( L"                return null;" );
                }
                else
                {
                    WriteLine( L"                return Currency.FromScaled( {}( {} ) );", getFunctionName, fieldId );
                }
            }
            else
            {
                WriteLine( L"                return {}( {} );", getFunctionName, fieldId );
            }
            WriteLine( L"            }" );
            WriteLine( L"        }" );

            if ( member->PrimaryKey( ) && classInfo.HasDescendants( ) )
            {
                WriteLine( L"        public Types.Kind EntityType" );
                WriteLine( L"        {" );
                WriteLine( L"            get" );
                WriteLine( L"            {" );
                WriteLine( L"                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );" );
                WriteLine( L"            }" );
                WriteLine( L"        }" );
            }
            
        }

    }
    void CSharpMsSqlSimpleDatabaseReadersGenerator::CreateWriteColumns( const ClassInfo& classInfo )
    {
        auto members = classInfo.OwnPersistentMembers( );
        auto memberCount = members.size( );
        
        if ( classInfo.IsTopLevel( ) == false )
        {
            WriteLine( L"        public override void WriteTo([DisallowNull] BinaryWriter destination)" );
            WriteLine( L"        {" );
            WriteLine( L"            base.WriteTo( destination );" );
        }
        else
        {
            WriteLine( L"        public virtual void WriteTo([DisallowNull] BinaryWriter destination)" );
            WriteLine( L"        {" );
            WriteLine( L"            destination.Write( Types.Kind.{} );", classInfo.Name( ) );
            WriteLine( L"            destination.Write( ObjectState.Stored );" );
        }
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto fieldName = member.Name().FirstToUpper( );
            auto memberType = member.Type( );
            if ( memberType == MemberInfoType::Binary )
            {
                WriteLine( L"            destination.WriteArray( {} );", fieldName );
            }
            else
            {
                WriteLine( L"            destination.Write( {} );", fieldName );
            }
        }
        WriteLine( L"        }" );
        WriteLine( );

        if ( classInfo.IsTopLevel( ) )
        {
            WriteLine( L"        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )");
            WriteLine( L"        {");
            WriteLine( L"            while ( Read( ) )");
            WriteLine( L"            {");
            WriteLine( L"                destination.Write( true );");
            WriteLine( L"                WriteTo( destination );");
            WriteLine( L"            }");
            WriteLine( L"            destination.Write( false );");
            WriteLine( L"        }" );
            WriteLine( );
        }

    }
    void CSharpMsSqlSimpleDatabaseReadersGenerator::CreateGetDataObject( const ClassInfo& classInfo )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        if ( classInfo.IsTopLevel( ) )
        {
            
            if ( classInfo.HasDescendants( ) )
            {
                if ( classInfo.Abstract( ) )
                {
                    WriteLine( L"        public abstract {} GetDataObject( );", className );
                    WriteLine( );
                    return;
                }
                WriteLine( L"        public virtual {} GetDataObject( )", className );
            }
            else
            {
                WriteLine( L"        public {} GetDataObject( )", className );
            }
            WriteLine( L"        {" );
            auto arguments = CSharpHelper::GetDataTypeConstructorCallPropertiesArguments( classInfo );
            WriteLine( L"            return new {}( {} );", className, arguments );
            WriteLine( L"        }" );
            WriteLine( );
        }
        else
        {
            if ( classInfo.Abstract( ) == false )
            {
                auto topLevelClassInfo = classInfo.TopLevelClass( );
                auto topLevelClassName = CSharpHelper::GetDataType( classInfo );
                WriteLine( L"        public override {} GetDataObject( )", topLevelClassName );
                WriteLine( L"        {" );
                auto arguments = CSharpHelper::GetDataTypeConstructorCallPropertiesArguments( classInfo );
                WriteLine( L"            return new {}( {} );", className, arguments );
                WriteLine( L"        }" );
                WriteLine( );
            }
        }
    }
}