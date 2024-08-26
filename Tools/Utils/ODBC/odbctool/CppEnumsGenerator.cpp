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
    void CppEnumsGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& enumMap = model.Enums( );

        auto headerGuard = CppHelper::GetHeaderGuard( Filename( ) );
        auto nspace = Options().Namespace( L"::" );
        WriteLine( L"#pragma once" );
        WriteLine( L"#ifndef {}", headerGuard );
        WriteLine( L"#define {}", headerGuard );
        WriteLine( );
        WriteLine( L"#include <HCCDef.h>" );
        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( L"    using namespace Harlinn::Common::Core;" );
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
        WriteLine( L"#endif" );

        Flush( );
    }

    WideString CppEnumsGenerator::GetUnderlyingType( const EnumInfo& enumInfo )
    {
        WideString result = L"Int32";
        auto valueType = enumInfo.ValueType( );
        switch ( valueType )
        {
            case MemberInfoType::SByte:
            {
                result = L"SByte";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = L"Byte";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = L"Int16";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = L"UInt16";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = L"Int32";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = L"UInt32";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = L"Int64";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = L"UInt64";
            }
            break;
        }
        return result;
    }
    void CppEnumsGenerator::CreateEnum( const EnumInfo& enumInfo )
    {
        WideString enumName = enumInfo.Name();
        auto underlyingType = GetUnderlyingType( enumInfo );

        const auto& enumValues = enumInfo.Values( );
        auto valueCount = enumValues.size( );

        WriteLine( L"    enum class {} : {}", enumName, underlyingType );
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
        WriteLine( L"    };" );
        WriteLine( );
    }

    void CppEnumsGenerator::CreateKind( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        WideString enumName = L"Kind";
        

        WriteLine( L"    enum class {} : Int32", enumName );
        WriteLine( L"    {" );
        WriteLine( L"        Unknown = 0," );
        auto classCount = classes.size( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            Write( L"        {} = {}", classInfo.Name(), classInfo.Id() );
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