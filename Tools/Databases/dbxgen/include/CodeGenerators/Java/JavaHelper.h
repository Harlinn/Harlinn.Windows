#pragma once
#ifndef JAVAHELPER_H_
#define JAVAHELPER_H_

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

#include "Metadata/ModelInfo.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java
{
    class JavaHelper
    {
    public:
        using MemberInfo = Metadata::MemberInfo;
        using ClassInfo = Metadata::ClassInfo;
        using IndexInfo = Metadata::IndexInfo;
        using EnumInfo = Metadata::EnumInfo;

        static WideString GetNotNullableBaseType(const MemberInfo& member);
        static WideString GetBaseType(const MemberInfo& member);
        static WideString GetDefaultValue(const MemberInfo& member);
        static WideString GetUnderlyingType(const EnumInfo& enumInfo);
        static WideString GetUnderlyingType(const MemberInfo& member);
        static WideString GetToIntMethodName(const EnumInfo& enumInfo);
        static WideString GetInputArgumentType(const MemberInfo& member);
        static WideString GetInputArgumentName(const MemberInfo& member);
        static WideString GetDataTypeBaseClassName(const ClassInfo& classInfo);
        static WideString GetDataType(const ClassInfo& classInfo);
        static WideString GetEntityType(const ClassInfo& classInfo);
        static WideString GetEntityTypeBaseClassName(const ClassInfo& classInfo);
        static WideString GetEntityCollectionType(const ClassInfo& classInfo);
        static WideString GetUpdateNode(const ClassInfo& classInfo);
        static WideString GetDataTypeConstructorArguments(const ClassInfo& classInfo);
        static WideString GetDataTypeConstructorCallArguments(const ClassInfo& classInfo);
        static WideString GetDataTypeConstructorCallPropertiesArguments(const ClassInfo& classInfo);
        static WideString GetDataTypeConstructorCallComplexReaderPropertiesArguments(const ClassInfo& classInfo, const ClassInfo& derivedOrSelfClassInfo);
        static WideString GetDataTypeBaseConstructorCallArguments(const ClassInfo& classInfo);

        static WideString GetMemberFieldType(const MemberInfo& member);
        static WideString GetMemberFieldName(const MemberInfo& member);
        static bool MemberFieldRequiresDefaultValue(const MemberInfo& member);
        static WideString GetSerializationWriteFunction(const MemberInfo& member);
        static WideString GetSerializationReadFunction(const MemberInfo& member);

        static WideString GetSimpleDataReaderName(const ClassInfo& classInfo);
        static WideString GetComplexDataReaderName(const ClassInfo& classInfo);
        static WideString GetDataReaderName(const ClassInfo& classInfo);
        static WideString GetDataReaderGetFunctionName(const MemberInfo& member);

        static WideString GetInsertFunctionName(const ClassInfo& classInfo);
        static WideString GetInsertFunctionName1(const ClassInfo& classInfo);
        static WideString GetUpdateFunctionName(const ClassInfo& classInfo);
        static WideString GetUpdateFunctionName1(const ClassInfo& classInfo);
        static WideString GetUpdateFunctionName2(const ClassInfo& classInfo);
        static WideString GetDeleteFunctionName(const ClassInfo& classInfo);

        static WideString GetInsertFunctionParameters(const ClassInfo& classInfo);
        static WideString GetInsertFunctionCallParameters(const ClassInfo& classInfo);

        static WideString GetInsertFunctionParameters1(const ClassInfo& classInfo);
        static WideString GetInsertFunctionCallParameters1(const ClassInfo& classInfo);

        static WideString GetUpdateFunctionParameters(const ClassInfo& classInfo);
        static WideString GetUpdateFunctionCallParameters(const ClassInfo& classInfo);

        static WideString GetUpdateFunctionParameters1(const ClassInfo& classInfo);
        static WideString GetUpdateFunctionCallParameters1(const ClassInfo& classInfo);

        static WideString GetUpdateFunctionParameters2(const ClassInfo& classInfo);
        static WideString GetUpdateFunctionCallParameters2(const ClassInfo& classInfo);

        static WideString GetDeleteFunctionParameters(const ClassInfo& classInfo);
        static WideString GetDeleteFunctionCallParameters(const ClassInfo& classInfo);

        static WideString GetSqlCommandParametersAddFunctionName(const MemberInfo& member);

        static WideString GetByIdFunctionName(const ClassInfo& classInfo);
        static WideString GetAllFunctionName(const ClassInfo& classInfo);
        static WideString GetByIndexFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);
        static WideString GetByIndexFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
        {
            return GetByIndexFunctionName(classInfo, indexInfo, 0, indexMemberCount);
        }
        static WideString GetByNullableIndexFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount);
        static WideString GetByIndexFunctionParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount);
        static WideString GetByIndexFunctionCallParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount);

        static WideString GetByNullableIndexFunctionParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount);
        static WideString GetByNullableIndexFunctionCallParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount);

        static WideString GetByIndexFunctionName(const WideString& lastFieldPrefix, const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);
        static WideString GetByIndexAtFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);
        static WideString GetByIndexFromFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);
        static WideString GetByIndexUntilFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);
        static WideString GetByIndexOverFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);
        static WideString GetByIndexFunctionOverParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);
        static WideString GetByIndexFunctionOverCallParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount);

        static WideString GetByIndexFunctionName(const WideString& lastFieldPrefix, const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
        {
            return GetByIndexFunctionName(lastFieldPrefix, classInfo, indexInfo, 0, indexMemberCount);
        }
        static WideString GetByIndexAtFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
        {
            return GetByIndexAtFunctionName(classInfo, indexInfo, 0, indexMemberCount);
        }
        static WideString GetByIndexFromFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
        {
            return GetByIndexFromFunctionName(classInfo, indexInfo, 0, indexMemberCount);
        }
        static WideString GetByIndexUntilFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
        {
            return GetByIndexUntilFunctionName(classInfo, indexInfo, 0, indexMemberCount);
        }
        static WideString GetByIndexOverFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
        {
            return GetByIndexOverFunctionName(classInfo, indexInfo, 0, indexMemberCount);
        }
        static WideString GetByIndexFunctionOverParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
        {
            return GetByIndexFunctionOverParameters(classInfo, indexInfo, 0, indexMemberCount);
        }
        static WideString GetByIndexFunctionOverCallParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
        {
            return GetByIndexFunctionOverCallParameters(classInfo, indexInfo, 0, indexMemberCount);
        }

        static bool IsUnique(const IndexInfo& indexInfo, size_t indexMemberCount);
        static bool RequiresComplexReader(const ClassInfo& classInfo);


        static WideString GetEntityIndexClassName(const IndexInfo& indexInfo);
        static WideString GetEntityNullableIndexClassName(const IndexInfo& indexInfo);






    };
}

#endif
