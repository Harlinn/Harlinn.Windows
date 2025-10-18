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
    void JavaDataTypeGenerator::Run( )
    { 
        auto nspace = Options( ).Namespace( L"." );
        WriteLine( L"package {};", nspace );
        WriteLine( );

        WriteLine( L"import com.harlinn.common.io.*;" );
        WriteLine( L"import com.harlinn.common.types.*;" );
        WriteLine( L"import com.harlinn.common.util.*;" );
        WriteLine( );
        
        auto className = JavaHelper::GetDataType( classInfo_ );
        auto baseClassName = JavaHelper::GetDataTypeBaseClassName( classInfo_ );
        const auto& persistentMembers = classInfo_.OwnPersistentMembers( );

        if ( classInfo_.Abstract( ) )
        {
            WriteLine( L"public abstract class {} extends {} {{", className, baseClassName );
        }
        else
        {
            WriteLine( L"public class {} extends {} {{", className, baseClassName );
        }
        WriteLine( );
        WriteLine( L"    public final int KIND = Kind.{};", classInfo_.Name() );
        WriteLine( );
        // Fields
        for ( const auto& member : persistentMembers )
        {
            if ( member->PrimaryKey( ) == false )
            {
                auto typeName = JavaHelper::GetMemberFieldType( *member );
                auto fieldName = JavaHelper::GetMemberFieldName( *member );
                if ( JavaHelper::MemberFieldRequiresDefaultValue( *member ) )
                {
                    auto defaultValue = JavaHelper::GetDefaultValue( *member );
                    WriteLine( L"    private {} {} = {};", typeName, fieldName, defaultValue );
                }
                else
                {
                    WriteLine( L"    private {} {};", typeName, fieldName );
                }
            }
        }
        WriteLine( );

        WriteLine( L"    public {}( ) {{", className );
        WriteLine( L"    }" );
        auto constructorArguments = JavaHelper::GetDataTypeConstructorArguments( classInfo_ );
        WriteLine( L"    public {}( {} ) {{", className, constructorArguments );
        if ( classInfo_.IsTopLevel( ) )
        {
            WriteLine( L"        super( objectState, id );" );
        }
        else
        {
            auto baseClass = classInfo_.BaseClass( );
            auto baseClassConstructorArguments = JavaHelper::GetDataTypeConstructorCallArguments( *baseClass );
            WriteLine( L"        super( {} );", baseClassConstructorArguments );
        }

        for ( const auto& member : persistentMembers )
        {
            if ( member->PrimaryKey( ) == false )
            {
                auto fieldName = JavaHelper::GetMemberFieldName( *member );
                auto argumentName = JavaHelper::GetInputArgumentName( *member );
                WriteLine( L"        this.{} = {};", fieldName, argumentName );
            }
        }

        WriteLine( L"    }" );

        WriteLine( );

        if ( classInfo_.Abstract( ) == false )
        {
            WriteLine( L"    @Override" );
            WriteLine( L"    public int getObjectType( ) {" );
            WriteLine( L"        return Kind.{};", classInfo_.Name( ) );
            WriteLine( L"    }" );

            WriteLine( L"    @Override" );
            WriteLine( L"    protected AbstractDataObject create( ) {" );
            WriteLine( L"        return new {}( );", className );
            WriteLine( L"    }" );

        }
        WriteLine( );
        if ( persistentMembers.size( ) )
        {
            // Properties
            for ( const auto& member : persistentMembers )
            {
                if ( member->PrimaryKey( ) == false )
                {
                    auto typeName = JavaHelper::GetMemberFieldType( *member );
                    auto fieldName = JavaHelper::GetMemberFieldName( *member );
                    auto propertyName = member->Name( ).FirstToUpper( );
                    auto equals = JavaHelper::GetEquals( *member, fieldName, L"value" );
                    auto deepCopy = JavaHelper::GetDeepCopy( *member, L"value", fieldName );

                    WriteLine( L"    public {} get{}( ) {{", typeName, propertyName );
                    WriteLine( L"        return {};", fieldName );
                    WriteLine( L"    }" );
                    WriteLine( L"    public void set{}( {} value ) {{", propertyName, typeName );
                    WriteLine( L"        if( !{} ) {{", equals );
                    WriteLine( L"            {};", deepCopy );
                    WriteLine( L"            onPropertyChanged( );" );
                    WriteLine( L"        }" );
                    WriteLine( L"    }" );
                    WriteLine( );
                }
            }
            WriteLine( );

            WriteLine( );
            WriteLine( L"    @Override" );
            WriteLine( L"    public void assignTo( AbstractDataObject target ) {" );
            WriteLine( L"        super.assignTo( target );" );
            WriteLine( L"        var targetObject = ( {} )target;", className );
            for ( const auto& member : persistentMembers )
            {
                if ( member->PrimaryKey( ) == false )
                {
                    auto fieldName = JavaHelper::GetMemberFieldName( *member );
                    auto sourceField = Format( L"this.{}", fieldName );
                    auto targetField = Format( L"targetObject.{}", fieldName );
                    auto deepCopy = JavaHelper::GetDeepCopy( *member, sourceField, targetField );
                    WriteLine( L"        {};", deepCopy );
                }
            }
            WriteLine( L"    }" );
            WriteLine( );

            WriteLine( L"    @Override" );
            WriteLine( L"    public boolean equals(Object obj) {" );
            WriteLine( L"        var result = super.equals( obj );" );
            WriteLine( L"        if( !result ) {" );
            WriteLine( L"            return false;" );
            WriteLine( L"        }" );
            WriteLine( L"        var other = ({})obj;", className );
            for ( const auto& member : persistentMembers )
            {
                if ( member->PrimaryKey( ) == false )
                {
                    auto fieldName = JavaHelper::GetMemberFieldName( *member );
                    auto thisField = Format( L"this.{}", fieldName );
                    auto otherField = Format( L"other.{}", fieldName );
                    auto equals = JavaHelper::GetEquals( *member, thisField, otherField );
                    WriteLine( L"        if( !{} ) {{", equals );
                    WriteLine( L"            return false;" );
                    WriteLine( L"        }" );
                }
            }
            WriteLine( L"        return true;" );
            WriteLine( L"    }" );

            WriteLine( );
            WriteLine( L"    @Override" );
            WriteLine( L"    public void writeTo( BinaryWriter destination ) {" );
            WriteLine( L"        super.writeTo( destination );" );
            for ( const auto& member : persistentMembers )
            {
                if ( member->PrimaryKey( ) == false )
                {
                    auto fieldName = JavaHelper::GetMemberFieldName( *member );
                    auto writeFunctionName = JavaHelper::GetSerializationWriteFunction( *member );

                    WriteLine( L"        destination.{}( {} );", writeFunctionName, fieldName );
                }
            }
            WriteLine( L"    }" );
            WriteLine( );
            WriteLine( L"    @Override" );
            WriteLine( L"    public void readFrom(BinaryReader source) {" );
            WriteLine( L"        super.readFrom( source );" );
            for ( const auto& member : persistentMembers )
            {
                if ( member->PrimaryKey( ) == false )
                {
                    auto fieldName = JavaHelper::GetMemberFieldName( *member );
                    auto readFunctionName = JavaHelper::GetSerializationReadFunction( *member );

                    WriteLine( L"        {} = source.{}( );", fieldName, readFunctionName );
                }
            }
            WriteLine( L"    }" );
            WriteLine( );

        }
        WriteLine( L"}" );


        Flush( );
    }
}