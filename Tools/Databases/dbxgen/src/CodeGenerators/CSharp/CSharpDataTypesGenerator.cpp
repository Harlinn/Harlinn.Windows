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
    void CSharpDataTypesGenerator::Run( )
    {
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

        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateDataType( classInfo );
        }
        CreateFactory( );

        WriteLine( L"}" );
        Flush( );
    }

    void CSharpDataTypesGenerator::CreateDataType( const Metadata::ClassInfo& classInfo )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto baseClassName = CSharpHelper::GetDataTypeBaseClassName( classInfo );
        const auto& persistentMembers = classInfo.OwnPersistentMembers( );

        if ( classInfo.Abstract( ) )
        {
            WriteLine( L"    public abstract class {} : {}", className, baseClassName );
        }
        else
        {
            WriteLine( L"    public class {} : {}", className, baseClassName );
        }
        WriteLine( L"    {" );

        // Fields
        for ( const auto& member : persistentMembers )
        {
            if ( member->PrimaryKey( ) == false )
            {
                auto typeName = CSharpHelper::GetMemberFieldType( *member );
                auto fieldName = CSharpHelper::GetMemberFieldName( *member );
                if ( CSharpHelper::MemberFieldRequiresDefaultValue( *member ) )
                {
                    auto defaultValue = CSharpHelper::GetDefaultValue( *member );
                    WriteLine( L"        {} {} = {};", typeName, fieldName, defaultValue );
                }
                else
                {
                    WriteLine( L"        {} {};", typeName, fieldName );
                }
            }
        }

        auto constructorArguments = CSharpHelper::GetDataTypeConstructorArguments( classInfo );
        auto baseConstructorCallArguments = CSharpHelper::GetDataTypeBaseConstructorCallArguments( classInfo );


        if ( classInfo.Abstract( ) == false )
        {
            WriteLine( L"        public {}( )", className );
            WriteLine( L"        {" );
            WriteLine( L"        }" );
            WriteLine( );
            WriteLine( L"        public {}( {} )", className, constructorArguments );
            WriteLine( L"            : base( {} )", baseConstructorCallArguments );
            WriteLine( L"        {" );
            for ( const auto& member : persistentMembers )
            {
                if ( member->PrimaryKey( ) == false )
                {
                    auto argumentName = CSharpHelper::GetInputArgumentName( *member );
                    auto fieldName = CSharpHelper::GetMemberFieldName( *member );
                    WriteLine( L"            {} = {};", fieldName, argumentName );
                }
            }
            WriteLine( L"        }" );
            WriteLine( );
            WriteLine( L"        public override Kind GetObjectType()" );
            WriteLine( L"        {" );
            WriteLine( L"            return Kind.{};", classInfo.Name( ) );
            WriteLine( L"        }" );
            WriteLine( );

            WriteLine( L"        public override BaseData<Kind> Create()" );
            WriteLine( L"        {" );
            WriteLine( L"            return new {}( );", className );
            WriteLine( L"        }" );
            WriteLine( );
        }
        else
        {
            WriteLine( L"        protected {}( )", className );
            WriteLine( L"        {" );
            WriteLine( L"        }" );
            WriteLine( );
            WriteLine( L"        protected {}( {} )", className, constructorArguments );
            WriteLine( L"            : base( {} )", baseConstructorCallArguments );
            WriteLine( L"        {" );
            for ( const auto& member : persistentMembers )
            {
                if ( member->PrimaryKey( ) == false )
                {
                    auto argumentName = CSharpHelper::GetInputArgumentName( *member );
                    auto fieldName = CSharpHelper::GetMemberFieldName( *member );
                    WriteLine( L"            {} = {};", fieldName, argumentName );
                }
            }
            WriteLine( L"        }" );
            WriteLine( );
        }

        if ( persistentMembers.size( ) )
        {
            WriteLine( L"        public override void AssignTo( BaseData<Kind> target )" );
            WriteLine( L"        {" );
            WriteLine( L"            base.AssignTo( target );" );
            WriteLine( L"            var destination = ( {} )target;", className );
            for ( const auto& member : persistentMembers )
            {
                if ( member->PrimaryKey( ) == false )
                {
                    auto memberType = member->Type( );
                    auto fieldName = CSharpHelper::GetMemberFieldName( *member );
                    if ( memberType == Metadata::MemberInfoType::Binary )
                    {
                        auto typeName = CSharpHelper::GetMemberFieldType( *member );
                        WriteLine( L"            destination.{} = ({}){}.Clone( );", fieldName, typeName, fieldName );
                    }
                    else
                    {
                        WriteLine( L"            destination.{} = {};", fieldName, fieldName );
                    }

                }
            }
            WriteLine( L"        }" );
            WriteLine( );
            WriteLine( L"        public override bool Equals(BaseData<Kind>? other)" );
            WriteLine( L"        {" );
            WriteLine( L"            if (base.Equals(other))" );
            WriteLine( L"            {" );
            WriteLine( L"                var obj = ( {} )other;", className );
            for ( const auto& member : persistentMembers )
            {
                if ( member->PrimaryKey( ) == false )
                {
                    auto memberType = member->Type( );
                    auto fieldName = CSharpHelper::GetMemberFieldName( *member );
                    if ( memberType == Metadata::MemberInfoType::Binary )
                    {
                        auto typeName = CSharpHelper::GetMemberFieldType( *member );
                        WriteLine( L"                if( obj.{}.Equals( {} ) == false )", fieldName, fieldName );
                    }
                    else
                    {
                        WriteLine( L"                if( obj.{} != {} )", fieldName, fieldName );
                    }
                    WriteLine( L"                {" );
                    WriteLine( L"                    return false;" );
                    WriteLine( L"                }" );
                }
            }
            WriteLine( L"                return true;" );
            WriteLine( L"            }" );
            WriteLine( L"            return false;" );
            WriteLine( L"        }" );
            WriteLine( );
        }
        WriteLine( L"        public override bool IsOfType(Kind objectType)", className );
        WriteLine( L"        {" );
        WriteLine( L"            if( objectType == Kind.{} )", classInfo.Name( ) );
        WriteLine( L"            {" );
        WriteLine( L"                return true;" );
        WriteLine( L"            }" );
        WriteLine( L"            return base.IsOfType( objectType );" );
        WriteLine( L"        }" );
        WriteLine( );
        
        if ( persistentMembers.size( ) )
        {
            // Properties
            for ( const auto& member : persistentMembers )
            {
                if ( member->PrimaryKey( ) == false )
                {
                    auto typeName = CSharpHelper::GetMemberFieldType( *member );
                    auto fieldName = CSharpHelper::GetMemberFieldName( *member );
                    auto propertyName = member->Name( ).FirstToUpper( );



                    WriteLine( L"        public {} {}", typeName, propertyName );
                    WriteLine( L"        {" );
                    WriteLine( L"            get => {};", fieldName );
                    WriteLine( L"            set" );
                    WriteLine( L"            {" );
                    WriteLine( L"                if( {} != value )", fieldName );
                    WriteLine( L"                {" );
                    WriteLine( L"                    {} = value;", fieldName );
                    WriteLine( L"                    OnPropertyChanged( );" );
                    WriteLine( L"                }" );
                    WriteLine( L"            }" );
                    WriteLine( L"        }" );

                }
            }
            WriteLine( );
            WriteLine( L"        public override void WriteTo( [ DisallowNull ] BinaryWriter destination )" );
            WriteLine( L"        {" );
            WriteLine( L"            base.WriteTo( destination );" );
            for ( const auto& member : persistentMembers )
            {
                if ( member->PrimaryKey( ) == false )
                {
                    auto fieldName = CSharpHelper::GetMemberFieldName( *member );
                    auto writeFunctionName = CSharpHelper::GetSerializationWriteFunction( *member );

                    WriteLine( L"            destination.{}( {} );", writeFunctionName, fieldName );
                }
            }
            WriteLine( L"        }" );
            WriteLine( );
            WriteLine( L"        public override void ReadFrom([DisallowNull] BinaryReader source)" );
            WriteLine( L"        {" );
            WriteLine( L"            base.ReadFrom( source );" );
            for ( const auto& member : persistentMembers )
            {
                if ( member->PrimaryKey( ) == false )
                {
                    auto fieldName = CSharpHelper::GetMemberFieldName( *member );
                    auto readFunctionName = CSharpHelper::GetSerializationReadFunction( *member );

                    WriteLine( L"            {} = source.{}( );", fieldName, readFunctionName );
                }
            }
            WriteLine( L"        }" );
            WriteLine( );

        }

        WriteLine( L"    }" );
        WriteLine( );
    }

    void CSharpDataTypesGenerator::CreateFactory( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );


        WriteLine( L"    public class DataObjectFactory : IBaseDataFactory<Kind>" );
        WriteLine( L"    {" );
        WriteLine( L"        public BaseDataGuid<Kind> Create( Kind kind )" );
        WriteLine( L"        {" );
        WriteLine( L"            switch( kind )" );
        WriteLine( L"            {" );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                auto dataTypeName = CSharpHelper::GetDataType( classInfo );
            
                WriteLine( L"                case Kind.{}:", classInfo.Name() );
                WriteLine( L"                {" );
                WriteLine( L"                    return new {}( );", dataTypeName );
                WriteLine( L"                }" );
            }
        }
        WriteLine( L"                default:" );
        WriteLine( L"                {" );
        WriteLine( L"                    throw new ArgumentException( $\"Cannot create an object for kind={kind}.\", \"kind\" );" );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( L"        public BaseDataGuid<Kind> ReadFrom(BinaryReader source)" );
        WriteLine( L"        {" );
        WriteLine( L"            var kind = (Kind)source.ReadInt32( );" );
        WriteLine( L"            var result = Create( kind );" );
        WriteLine( L"            result.ReadFrom( source );" );
        WriteLine( L"            return result;" );
        WriteLine( L"        }" );
        WriteLine( L"        public BaseDataGuid<Kind>? ReadNullableFrom(BinaryReader source)" );
        WriteLine( L"        {" );
        WriteLine( L"            var hasValue = source.ReadBoolean( );" );
        WriteLine( L"            if( hasValue )" );
        WriteLine( L"            {" );
        WriteLine( L"                return ReadFrom( source );" );
        WriteLine( L"            }" );
        WriteLine( L"            return null;" );
        WriteLine( L"        }" );
        WriteLine( L"        public IList<BaseDataGuid<Kind>> ReadStreamFrom(BinaryReader source)" );
        WriteLine( L"        {" );
        WriteLine( L"            var result = new List<BaseDataGuid<Kind>>( );" );
        WriteLine( L"            while( source.ReadBoolean( ) )" );
        WriteLine( L"            {" );
        WriteLine( L"                var dataObject = ReadFrom( source );" );
        WriteLine( L"                result.Add( dataObject );" );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );
        WriteLine( L"        }" );
        WriteLine( L"        public IList<BaseDataGuid<Kind>> ReadListFrom(BinaryReader source)" );
        WriteLine( L"        {" );
        WriteLine( L"            var count = source.ReadSize( );" );
        WriteLine( L"            var result = new List<BaseDataGuid<Kind>>( count );" );
        WriteLine( L"            for( int i = 0; i < count; i++ )" );
        WriteLine( L"            {" );
        WriteLine( L"                var dataObject = ReadFrom( source );" );
        WriteLine( L"                result.Add( dataObject );" );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );
        WriteLine( L"        }" );
        WriteLine( L"    }" );
        WriteLine( );


    }
}