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

public class DmExecComputeNodeErrorsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_compute_node_errors]";
    public const string TableName = "dm_exec_compute_node_errors";
    public const string ShortName = "decne";
    public const string Sql = """
        SELECT
          decne.[error_id],
          decne.[Source],
          decne.[Type],
          decne.[create_time],
          decne.[compute_node_id],
          decne.[execution_id],
          decne.[Spid],
          decne.[thread_id],
          decne.[Details],
          decne.[compute_pool_id]
        FROM
          [sys].[dm_exec_compute_node_errors] decne
        """;

    public const int ERRORID_FIELD_ID = 0;
    public const int SOURCE_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;
    public const int CREATETIME_FIELD_ID = 3;
    public const int COMPUTENODEID_FIELD_ID = 4;
    public const int EXECUTIONID_FIELD_ID = 5;
    public const int SPID_FIELD_ID = 6;
    public const int THREADID_FIELD_ID = 7;
    public const int DETAILS_FIELD_ID = 8;
    public const int COMPUTEPOOLID_FIELD_ID = 9;


    public DmExecComputeNodeErrorsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecComputeNodeErrorsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecComputeNodeErrorsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? ErrorId
    {
        get
        {
            return base.GetNullableString(ERRORID_FIELD_ID);
        }
    }

    public string? Source
    {
        get
        {
            return base.GetNullableString(SOURCE_FIELD_ID);
        }
    }

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public DateTime? CreateTime
    {
        get
        {
            return base.GetNullableDateTime(CREATETIME_FIELD_ID);
        }
    }

    public int? ComputeNodeId
    {
        get
        {
            return base.GetNullableInt32(COMPUTENODEID_FIELD_ID);
        }
    }

    public string? ExecutionId
    {
        get
        {
            return base.GetNullableString(EXECUTIONID_FIELD_ID);
        }
    }

    public int? Spid
    {
        get
        {
            return base.GetNullableInt32(SPID_FIELD_ID);
        }
    }

    public int? ThreadId
    {
        get
        {
            return base.GetNullableInt32(THREADID_FIELD_ID);
        }
    }

    public string? Details
    {
        get
        {
            return base.GetNullableString(DETAILS_FIELD_ID);
        }
    }

    public int ComputePoolId
    {
        get
        {
            return base.GetInt32(COMPUTEPOOLID_FIELD_ID);
        }
    }


    public Types.DmExecComputeNodeErrorsDataType ToDataObject()
    {
        return new Types.DmExecComputeNodeErrorsDataType(ErrorId,
            Source,
            Type,
            CreateTime,
            ComputeNodeId,
            ExecutionId,
            Spid,
            ThreadId,
            Details,
            ComputePoolId);
    }

    public List<Types.DmExecComputeNodeErrorsDataType> ToList()
    {
        var list = new List<Types.DmExecComputeNodeErrorsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
