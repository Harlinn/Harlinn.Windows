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

public class DmExecExternalOperationsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_external_operations]";
    public const string TableName = "dm_exec_external_operations";
    public const string ShortName = "deeo";
    public const string Sql = """
        SELECT
          deeo.[execution_id],
          deeo.[step_index],
          deeo.[operation_type],
          deeo.[operation_name],
          deeo.[map_progress],
          deeo.[reduce_progress],
          deeo.[compute_pool_id]
        FROM
          [sys].[dm_exec_external_operations] deeo
        """;

    public const int EXECUTIONID_FIELD_ID = 0;
    public const int STEPINDEX_FIELD_ID = 1;
    public const int OPERATIONTYPE_FIELD_ID = 2;
    public const int OPERATIONNAME_FIELD_ID = 3;
    public const int MAPPROGRESS_FIELD_ID = 4;
    public const int REDUCEPROGRESS_FIELD_ID = 5;
    public const int COMPUTEPOOLID_FIELD_ID = 6;


    public DmExecExternalOperationsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecExternalOperationsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecExternalOperationsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? ExecutionId
    {
        get
        {
            return base.GetNullableString(EXECUTIONID_FIELD_ID);
        }
    }

    public int? StepIndex
    {
        get
        {
            return base.GetNullableInt32(STEPINDEX_FIELD_ID);
        }
    }

    public string? OperationType
    {
        get
        {
            return base.GetNullableString(OPERATIONTYPE_FIELD_ID);
        }
    }

    public string? OperationName
    {
        get
        {
            return base.GetNullableString(OPERATIONNAME_FIELD_ID);
        }
    }

    public double? MapProgress
    {
        get
        {
            return base.GetNullableDouble(MAPPROGRESS_FIELD_ID);
        }
    }

    public double? ReduceProgress
    {
        get
        {
            return base.GetNullableDouble(REDUCEPROGRESS_FIELD_ID);
        }
    }

    public int ComputePoolId
    {
        get
        {
            return base.GetInt32(COMPUTEPOOLID_FIELD_ID);
        }
    }


    public Types.DmExecExternalOperationsDataType ToDataObject()
    {
        return new Types.DmExecExternalOperationsDataType(ExecutionId,
            StepIndex,
            OperationType,
            OperationName,
            MapProgress,
            ReduceProgress,
            ComputePoolId);
    }

    public List<Types.DmExecExternalOperationsDataType> ToList()
    {
        var list = new List<Types.DmExecExternalOperationsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
