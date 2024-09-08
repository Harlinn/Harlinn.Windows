#pragma once
#ifndef CSHARPHELPER_H_
#define CSHARPHELPER_H_

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

#include "ModelInfo.h"

namespace Harlinn::ODBC::Tool
{
    class CSharpHelper
    {
    public:
        static WideString GetBaseType( const MemberInfo& member );
        static WideString GetDefaultValue( const MemberInfo& member );
        static WideString GetInputArgumentType( const MemberInfo& member );
        static WideString GetInputArgumentName( const MemberInfo& member );
        static WideString GetDataTypeBaseClassName( const ClassInfo& classInfo );
        static WideString GetDataType( const ClassInfo& classInfo );

        static WideString GetMemberFieldType( const MemberInfo& member );
        static WideString GetMemberFieldName( const MemberInfo& member );
        static bool MemberFieldRequiresDefaultValue( const MemberInfo& member );
        static WideString GetSerializationWriteFunction( const MemberInfo& member );
        static WideString GetSerializationReadFunction( const MemberInfo& member );

        static WideString GetSimpleDataReaderName( const ClassInfo& classInfo );
        static WideString GetComplexDataReaderName( const ClassInfo& classInfo );
        static WideString GetDataReaderGetFunctionName( const MemberInfo& member );

    };
}

#endif
