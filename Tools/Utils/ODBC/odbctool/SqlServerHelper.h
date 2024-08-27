#pragma once
#ifndef SQLSERVERHELPER_H_
#define SQLSERVERHELPER_H_
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

#include "ClassInfo.h"


namespace Harlinn::ODBC::Tool
{
    class SqlServerHelper
    {
    public:
        static WideString GetColumnName( const MemberInfo& member );

        static WideString GetColumnType( const MemberInfo& member );

        static WideString GetTableName( const ClassInfo& classInfo );
        static WideString GetShortName( const ClassInfo& classInfo );

        static WideString GetViewName( const ClassInfo& classInfo );


        static WideString GetIndexName( const IndexInfo& indexInfo );

        static WideString GetColumnNames( const IndexInfo& indexInfo );

        static std::vector<std::shared_ptr<MemberInfo>> GetColumnsForSelect( const ClassInfo& classInfo );
        static std::vector<std::shared_ptr<MemberInfo>> GetUnboundColumnsForSelect( const ClassInfo& classInfo );
        static std::vector<std::shared_ptr<MemberInfo>> GetOwnColumnsForSelect( const ClassInfo& classInfo );
        static std::vector<std::shared_ptr<MemberInfo>> GetOwnUnboundColumnsForSelect( const ClassInfo& classInfo );
        static WideString GetColumnNamesForSelect( const ClassInfo& classInfo );

        static std::vector<std::shared_ptr<MemberInfo>> GetColumnsForComplexSelect( const ClassInfo& classInfo );
        static std::vector<std::shared_ptr<MemberInfo>> GetBindableColumnsForComplexSelect( const ClassInfo& classInfo );
        static std::vector<std::shared_ptr<MemberInfo>> GetUnboundColumnsForComplexSelect( const ClassInfo& classInfo );

        static WideString GetInsertProcedureName( const ClassInfo& classInfo );
        static WideString GetInsertTriggerName( const ClassInfo& classInfo );

        static WideString GetUpdateProcedureName( const ClassInfo& classInfo );
        static WideString GetDeleteProcedureName( const ClassInfo& classInfo );


    };
}

#endif
