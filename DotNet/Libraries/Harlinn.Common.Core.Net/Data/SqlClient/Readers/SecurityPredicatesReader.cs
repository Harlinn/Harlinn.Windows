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
using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers;

public class SecurityPredicatesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[security_predicates]";
    public const string TableName = "security_predicates";
    public const string ShortName = "sp";
    public const string Sql = """
        SELECT
          sp.[object_id],
          sp.[security_predicate_id],
          sp.[target_object_id],
          sp.[predicate_definition],
          sp.[predicate_type],
          sp.[predicate_type_desc],
          sp.[Operation],
          sp.[operation_desc]
        FROM
          [sys].[security_predicates] sp
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int SECURITYPREDICATEID_FIELD_ID = 1;
    public const int TARGETOBJECTID_FIELD_ID = 2;
    public const int PREDICATEDEFINITION_FIELD_ID = 3;
    public const int PREDICATETYPE_FIELD_ID = 4;
    public const int PREDICATETYPEDESC_FIELD_ID = 5;
    public const int OPERATION_FIELD_ID = 6;
    public const int OPERATIONDESC_FIELD_ID = 7;


    public SecurityPredicatesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SecurityPredicatesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SecurityPredicatesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int SecurityPredicateId
    {
        get
        {
            return base.GetInt32(SECURITYPREDICATEID_FIELD_ID);
        }
    }

    public int TargetObjectId
    {
        get
        {
            return base.GetInt32(TARGETOBJECTID_FIELD_ID);
        }
    }

    public string? PredicateDefinition
    {
        get
        {
            return base.GetNullableString(PREDICATEDEFINITION_FIELD_ID);
        }
    }

    public int? PredicateType
    {
        get
        {
            return base.GetNullableInt32(PREDICATETYPE_FIELD_ID);
        }
    }

    public string? PredicateTypeDesc
    {
        get
        {
            return base.GetNullableString(PREDICATETYPEDESC_FIELD_ID);
        }
    }

    public int? Operation
    {
        get
        {
            return base.GetNullableInt32(OPERATION_FIELD_ID);
        }
    }

    public string? OperationDesc
    {
        get
        {
            return base.GetNullableString(OPERATIONDESC_FIELD_ID);
        }
    }


    public Types.SecurityPredicatesDataType ToDataObject()
    {
        return new Types.SecurityPredicatesDataType(ObjectId,
            SecurityPredicateId,
            TargetObjectId,
            PredicateDefinition,
            PredicateType,
            PredicateTypeDesc,
            Operation,
            OperationDesc);
    }

    public List<Types.SecurityPredicatesDataType> ToList()
    {
        var list = new List<Types.SecurityPredicatesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
