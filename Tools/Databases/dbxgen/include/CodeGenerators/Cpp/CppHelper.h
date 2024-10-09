#pragma once
#ifndef CPPHELPER_H_
#define CPPHELPER_H_

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

#include "Metadata/ModelInfo.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Cpp
{
    class CppHelper
    {
    public:
        using MemberInfo = Metadata::MemberInfo;
        using ClassInfo = Metadata::ClassInfo;

        static WideString GetHeaderGuard( const WideString& filename );
        
        static WideString GetBaseType( const MemberInfo& member );
        static WideString GetDefaultValue( const MemberInfo& member );
        static WideString GetInputArgumentType( const MemberInfo& member );
        static WideString GetInputArgumentName( const MemberInfo& member );
        static WideString GetBindParameterFunctionName( const MemberInfo& member );
        static WideString GetMemberFieldType( const MemberInfo& member );
        static WideString GetMemberNullableFieldType( const MemberInfo& member );
        static WideString GetDataMemberFieldType( const MemberInfo& member );
        static WideString GetMemberFieldName( const MemberInfo& member );
        static WideString GetLongMemberFieldName( const MemberInfo& member );
        static WideString GetMemberAccessorName( const MemberInfo& member );
        static WideString GetMemberAccessorReturnType( const MemberInfo& member );
        static WideString GetMemberSetterName( const MemberInfo& member );
        static bool IsBindable( const MemberInfo& member );
        static bool RequiresIndicator( const MemberInfo& member );
        static WideString GetMemberIndicatorName( const MemberInfo& member );

        static bool MemberFieldRequiresDefaultValue( const MemberInfo& member );
        
        static WideString GetColumnDataType( const ClassInfo& classInfo );
        static WideString GetComplexColumnDataType( const ClassInfo& classInfo );
        static WideString GetDataType( const ClassInfo& classInfo );
        static WideString GetSimpleTestValue( const ClassInfo& classInfo, const MemberInfo& member );

        static WideString GetInsertFunctionName( const ClassInfo& classInfo );
        static WideString GetUpdateFunctionName( const ClassInfo& classInfo );
        static WideString GetDeleteFunctionName( const ClassInfo& classInfo );

        static WideString GetInsertFunctionParameters( const ClassInfo& classInfo );
        static WideString GetInsertFunctionCallParameters( const ClassInfo& classInfo );
        static WideString GetInsertFunctionParameterMarkers( const ClassInfo& classInfo );

        static WideString GetUpdateFunctionParameters( const ClassInfo& classInfo );
        static WideString GetUpdateFunctionCallParameters( const ClassInfo& classInfo );
        static WideString GetUpdateFunctionParameterMarkers( const ClassInfo& classInfo );

        static WideString GetDeleteFunctionParameters( const ClassInfo& classInfo );
        static WideString GetDeleteFunctionCallParameters( const ClassInfo& classInfo );
        static WideString GetDeleteFunctionParameterMarkers( const ClassInfo& classInfo );



    };

}

#endif
