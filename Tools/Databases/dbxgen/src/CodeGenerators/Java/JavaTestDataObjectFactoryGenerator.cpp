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
#include "HCCStringBuilder.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java
{
    using namespace Metadata;

    void JavaTestDataObjectFactoryGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto nspace = Options( ).Namespace( L"." );
        WriteLine( L"package {};", nspace );
        WriteLine( );
        WriteLine( L"import com.harlinn.common.types.*;" );
        WriteLine( L"import com.harlinn.common.util.*;" );
        WriteLine( );
        auto className = JavaHelper::GetTestDataObjectFactory( );
        WriteLine( L"public class {} {{", className );
        WriteLine( );

        for ( const auto& classInfo : classes )
        {
            if ( classInfo->Abstract( ) == false )
            {
                const auto& name = classInfo->Name( );
                WriteLine( L"    public final static Guid {}PrimaryKey = new Guid(Kind.{},(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);", name, name );
            }
        }
        WriteLine( );

        for ( const auto& classInfo : classes )
        {
            if ( classInfo->Abstract( ) == false )
            {
                const auto& name = classInfo->Name( );
                const auto dataObjectClassName = JavaHelper::GetDataType( *classInfo );
                WriteLine( L"    private {} _{} = null;", dataObjectClassName, name.FirstToLower() );
            }
        }

        WriteLine( );

        for ( const auto& classInfo : classes )
        {
            if ( classInfo->Abstract( ) == false )
            {
                const auto& name = classInfo->Name( );
                const auto dataObjectClassName = JavaHelper::GetDataType( *classInfo );
                WriteLine( L"    public {} get{}() {{", dataObjectClassName, name );
                WriteLine( L"        if (_{} == null) {{", name.FirstToLower( ) );
                const auto& members = classInfo->PersistentMembers( );
                auto memberCount = members.size( );
                StringBuilder<wchar_t> sb;
                sb.Append(L"ObjectState.New, {}PrimaryKey", name );
                for ( size_t i = 0; i < memberCount; i++ )
                {
                    const auto& member = members[ i ];
                    if ( member->PrimaryKey( ) == false )
                    {
                        auto typeName = JavaHelper::GetMemberFieldType( *member );
                        auto variableName = JavaHelper::GetInputArgumentName( *member );
                        auto defaultValue = JavaHelper::JavaHelper::GetDefaultValue( *member );
                        if ( member->Nullable( ) == false )
                        {
                            auto memberType = member->Type( );
                            if ( memberType == MemberInfoType::Reference || memberType == MemberInfoType::TimeSeries )
                            {
                                const ReferenceMemberInfo& reference = static_cast<const ReferenceMemberInfo&>( *member );
                                std::shared_ptr<ClassInfo> referencedType = reference.ReferencedType( )->ConcreteClass( );
                                defaultValue = Format( L"{}PrimaryKey", referencedType->Name( ) );
                            }
                            else if ( memberType == MemberInfoType::String )
                            {
                                const StringMemberInfo& stringMemberInfo = static_cast<const StringMemberInfo&>( *member );
                                defaultValue = Format( L"\"{}{}UnitTest\"", member->Name(), name );
                                if ( stringMemberInfo.Size( ) && defaultValue.length( ) > stringMemberInfo.Size( ) )
                                {
                                    defaultValue = defaultValue.substr(0, stringMemberInfo.Size( ) - 1 ) + '\"';
                                }
                            }
                            else if ( memberType == MemberInfoType::DateTime )
                            {
                                defaultValue = L"new DateTime(2025,10,18,9,0,0)";
                            }
                        }
                        WriteLine( L"            {} {} = {};", typeName, variableName, defaultValue );

                        sb.Append( L", {}", variableName );
                    }
                }
                WriteLine( );
                WriteLine( L"            _{} = new {}( {} );", name.FirstToLower( ), dataObjectClassName, sb.ToString( ) );
                WriteLine( L"        }" );
                WriteLine( L"        return _{};", name.FirstToLower( ) );
                WriteLine( L"    }" );
                WriteLine( );
            }
        }

        WriteLine( );

        WriteLine( L"}");
        Flush( );

    }
}