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

                    WriteLine( L"    public {} get{}( ) {{", typeName, propertyName );
                    WriteLine( L"        return {};", fieldName );
                    WriteLine( L"    }" );
                    WriteLine( L"    public void set{}( {} value ) {{", propertyName, typeName );
                    WriteLine( L"        if( {} != value ) {{", fieldName );
                    WriteLine( L"            this.{} = value;", fieldName );
                    WriteLine( L"            onPropertyChanged( );" );
                    WriteLine( L"        }" );
                    WriteLine( L"    }" );
                    WriteLine( );
                }
            }
            WriteLine( );
        }
        WriteLine( L"}" );


        Flush( );
    }
}