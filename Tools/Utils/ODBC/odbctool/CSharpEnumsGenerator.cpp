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
#include "CppHelper.h"

namespace Harlinn::ODBC::Tool
{
    void CSharpEnumsGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& enumMap = model.Enums( );

        auto headerGuard = CppHelper::GetHeaderGuard( Filename( ) );
        auto nspace = Options( ).Namespace( L"." );
        WriteLine( );
        WriteLine( L"using System;" );
        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        
        WriteLine( );
        CreateKind( );

        std::vector<std::shared_ptr<EnumInfo>> enums;
        for ( const auto& entry : enumMap )
        {
            enums.emplace_back( entry.second );
        }

        std::sort( enums.begin( ), enums.end( ), []( const auto& first, const auto& second ) { return first->Name( ) < second->Name( ); } );

        for ( const auto& enumInfo : enums )
        {
            CreateEnum( *enumInfo );
        }
        WriteLine( L"}" );

        Flush( );
    }

    WideString CSharpEnumsGenerator::GetUnderlyingType( const EnumInfo& enumInfo )
    {
        WideString result = L"int";
        auto valueType = enumInfo.ValueType( );
        switch ( valueType )
        {
            case MemberInfoType::SByte:
            {
                result = L"sbyte";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = L"byte";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = L"short";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = L"ushort";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = L"int";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = L"uint";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = L"long";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = L"ulong";
            }
            break;
        }
        return result;
    }
    void CSharpEnumsGenerator::CreateEnum( const EnumInfo& enumInfo )
    {
        WideString enumName = enumInfo.Name( );
        auto underlyingType = GetUnderlyingType( enumInfo );

        const auto& enumValues = enumInfo.Values( );
        auto valueCount = enumValues.size( );

        if ( enumInfo.Flags( ) )
        {
            WriteLine( L"    [Flags()]" );
        }
        WriteLine( L"    public enum {} : {}", enumName, underlyingType );
        WriteLine( L"    {" );
        for ( size_t i = 0; i < valueCount; i++ )
        {
            const auto& enumValue = *enumValues[ i ];
            Write( L"        {} = {}", enumValue.Name( ), enumValue.Value( ) );
            if ( i < ( valueCount - 1 ) )
            {
                WriteLine( L"," );
            }
            else
            {
                WriteLine( );
            }
        }
        WriteLine( L"    }" );
        WriteLine( );
    }

    void CSharpEnumsGenerator::CreateKind( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        WideString enumName = L"Kind";


        WriteLine( L"    public enum {} : int", enumName );
        WriteLine( L"    {" );
        WriteLine( L"        Unknown = 0," );
        auto classCount = classes.size( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            Write( L"        {} = {}", classInfo.Name( ), classInfo.Id( ) );
            if ( i < ( classCount - 1 ) )
            {
                WriteLine( L"," );
            }
            else
            {
                WriteLine( );
            }
        }
        WriteLine( L"    };" );
        WriteLine( );

    }

}