#pragma once
#ifndef CPPHELPER_H_
#define CPPHELPER_H_

/*
   Copyright 2024-2026 Espen Harlinn

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
        using IndexInfo = Metadata::IndexInfo;

        static WideString GetHeaderGuard( const WideString& filename );
        static WideString GetNotNullableBaseType( const MemberInfo& member );
        static WideString GetBaseType( const MemberInfo& member );
        static WideString GetDefaultValue( const MemberInfo& member );
        static bool IsByReference( const MemberInfo& member );
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
        static WideString GetInsertFunctionName1( const ClassInfo& classInfo );
        static WideString GetUpdateFunctionName( const ClassInfo& classInfo );
        static WideString GetUpdateFunctionName1( const ClassInfo& classInfo );
        static WideString GetUpdateFunctionName2( const ClassInfo& classInfo );
        static WideString GetDeleteFunctionName( const ClassInfo& classInfo );

        static WideString GetInsertFunctionParameters( const ClassInfo& classInfo, const std::vector<std::shared_ptr<MemberInfo>>& members );
        static WideString GetInsertFunctionCallParameters( const ClassInfo& classInfo, const std::vector<std::shared_ptr<MemberInfo>>& members );
        static WideString GetInsertFunctionParameterMarkers( const ClassInfo& classInfo, const std::vector<std::shared_ptr<MemberInfo>>& members );

        static WideString GetInsertFunctionParameters( const ClassInfo& classInfo );
        static WideString GetInsertFunctionCallParameters( const ClassInfo& classInfo );
        static WideString GetInsertFunctionParameterMarkers( const ClassInfo& classInfo );

        static WideString GetInsertFunctionParameters1( const ClassInfo& classInfo );
        static WideString GetInsertFunctionCallParameters1( const ClassInfo& classInfo );
        static WideString GetInsertFunctionParameterMarkers1( const ClassInfo& classInfo );


        static WideString GetUpdateFunctionParameters( const ClassInfo& classInfo, const std::vector<std::shared_ptr<MemberInfo>>& members );
        static WideString GetUpdateFunctionCallParameters( const ClassInfo& classInfo, const std::vector<std::shared_ptr<MemberInfo>>& members );
        static WideString GetUpdateFunctionParameterMarkers( const ClassInfo& classInfo, const std::vector<std::shared_ptr<MemberInfo>>& members );

        static WideString GetUpdateFunctionParameters( const ClassInfo& classInfo );
        static WideString GetUpdateFunctionCallParameters( const ClassInfo& classInfo );
        static WideString GetUpdateFunctionParameterMarkers( const ClassInfo& classInfo );

        static WideString GetUpdateFunctionParameters1( const ClassInfo& classInfo );
        static WideString GetUpdateFunctionCallParameters1( const ClassInfo& classInfo );
        static WideString GetUpdateFunctionParameterMarkers1( const ClassInfo& classInfo );

        static WideString GetUpdateFunctionParameters2( const ClassInfo& classInfo );
        static WideString GetUpdateFunctionCallParameters2( const ClassInfo& classInfo );
        static WideString GetUpdateFunctionParameterMarkers2( const ClassInfo& classInfo );

        static WideString GetDeleteFunctionParameters( const ClassInfo& classInfo );
        static WideString GetDeleteFunctionCallParameters( const ClassInfo& classInfo );
        static WideString GetDeleteFunctionParameterMarkers( const ClassInfo& classInfo );

        static WideString GetByIdFunctionName( const ClassInfo& classInfo );
        static WideString GetAllFunctionName( const ClassInfo& classInfo );
        static WideString GetByIndexFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );
        static WideString GetByIndexFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
        {
            return GetByIndexFunctionName( classInfo, indexInfo, 0, indexMemberCount );
        }
        static WideString GetByNullableIndexFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount );
        static WideString GetByIndexFunctionParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount );
        static WideString GetByIndexFunctionCallParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount );

        static WideString GetByNullableIndexFunctionParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount );
        static WideString GetByNullableIndexFunctionCallParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount );

        static WideString GetByIndexFunctionName( const WideString& lastFieldPrefix, const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );
        static WideString GetByIndexAtFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );
        static WideString GetByIndexFromFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );
        static WideString GetByIndexUntilFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );
        static WideString GetByIndexOverFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );
        static WideString GetByIndexFunctionOverParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );
        static WideString GetByIndexFunctionOverCallParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount );

        static WideString GetByIndexFunctionName( const WideString& lastFieldPrefix, const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
        {
            return GetByIndexFunctionName( lastFieldPrefix, classInfo, indexInfo, 0, indexMemberCount );
        }
        static WideString GetByIndexAtFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
        {
            return GetByIndexAtFunctionName( classInfo, indexInfo, 0, indexMemberCount );
        }
        static WideString GetByIndexFromFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
        {
            return GetByIndexFromFunctionName( classInfo, indexInfo, 0, indexMemberCount );
        }
        static WideString GetByIndexUntilFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
        {
            return GetByIndexUntilFunctionName( classInfo, indexInfo, 0, indexMemberCount );
        }
        static WideString GetByIndexOverFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
        {
            return GetByIndexOverFunctionName( classInfo, indexInfo, 0, indexMemberCount );
        }
        static WideString GetByIndexFunctionOverParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
        {
            return GetByIndexFunctionOverParameters( classInfo, indexInfo, 0, indexMemberCount );
        }
        static WideString GetByIndexFunctionOverCallParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
        {
            return GetByIndexFunctionOverCallParameters( classInfo, indexInfo, 0, indexMemberCount );
        }

        static bool IsUnique( const IndexInfo& indexInfo, size_t indexMemberCount );
        static bool RequiresComplexReader( const ClassInfo& classInfo );



    };

}

#endif
