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

public class DmDbRdaSchemaUpdateStatusReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_rda_schema_update_status]";
    public const string TableName = "dm_db_rda_schema_update_status";
    public const string ShortName = "ddrsus";
    public const string Sql = """
        SELECT
          ddrsus.[table_id],
          ddrsus.[database_id],
          ddrsus.[task_id],
          ddrsus.[task_type],
          ddrsus.[task_type_desc],
          ddrsus.[task_state],
          ddrsus.[task_state_desc],
          ddrsus.[start_time_utc],
          ddrsus.[end_time_utc],
          ddrsus.[error_number],
          ddrsus.[error_severity],
          ddrsus.[error_state]
        FROM
          [sys].[dm_db_rda_schema_update_status] ddrsus
        """;

    public const int TABLEID_FIELD_ID = 0;
    public const int DATABASEID_FIELD_ID = 1;
    public const int TASKID_FIELD_ID = 2;
    public const int TASKTYPE_FIELD_ID = 3;
    public const int TASKTYPEDESC_FIELD_ID = 4;
    public const int TASKSTATE_FIELD_ID = 5;
    public const int TASKSTATEDESC_FIELD_ID = 6;
    public const int STARTTIMEUTC_FIELD_ID = 7;
    public const int ENDTIMEUTC_FIELD_ID = 8;
    public const int ERRORNUMBER_FIELD_ID = 9;
    public const int ERRORSEVERITY_FIELD_ID = 10;
    public const int ERRORSTATE_FIELD_ID = 11;


    public DmDbRdaSchemaUpdateStatusReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbRdaSchemaUpdateStatusReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbRdaSchemaUpdateStatusReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? TableId
    {
        get
        {
            return base.GetNullableInt32(TABLEID_FIELD_ID);
        }
    }

    public int? DatabaseId
    {
        get
        {
            return base.GetNullableInt32(DATABASEID_FIELD_ID);
        }
    }

    public long? TaskId
    {
        get
        {
            return base.GetNullableInt64(TASKID_FIELD_ID);
        }
    }

    public int? TaskType
    {
        get
        {
            return base.GetNullableInt32(TASKTYPE_FIELD_ID);
        }
    }

    public string? TaskTypeDesc
    {
        get
        {
            return base.GetNullableString(TASKTYPEDESC_FIELD_ID);
        }
    }

    public int? TaskState
    {
        get
        {
            return base.GetNullableInt32(TASKSTATE_FIELD_ID);
        }
    }

    public string? TaskStateDesc
    {
        get
        {
            return base.GetNullableString(TASKSTATEDESC_FIELD_ID);
        }
    }

    public DateTime? StartTimeUtc
    {
        get
        {
            return base.GetNullableDateTime(STARTTIMEUTC_FIELD_ID);
        }
    }

    public DateTime? EndTimeUtc
    {
        get
        {
            return base.GetNullableDateTime(ENDTIMEUTC_FIELD_ID);
        }
    }

    public int? ErrorNumber
    {
        get
        {
            return base.GetNullableInt32(ERRORNUMBER_FIELD_ID);
        }
    }

    public int? ErrorSeverity
    {
        get
        {
            return base.GetNullableInt32(ERRORSEVERITY_FIELD_ID);
        }
    }

    public int? ErrorState
    {
        get
        {
            return base.GetNullableInt32(ERRORSTATE_FIELD_ID);
        }
    }


    public Types.DmDbRdaSchemaUpdateStatusDataType ToDataObject()
    {
        return new Types.DmDbRdaSchemaUpdateStatusDataType(TableId,
            DatabaseId,
            TaskId,
            TaskType,
            TaskTypeDesc,
            TaskState,
            TaskStateDesc,
            StartTimeUtc,
            EndTimeUtc,
            ErrorNumber,
            ErrorSeverity,
            ErrorState);
    }

    public List<Types.DmDbRdaSchemaUpdateStatusDataType> ToList()
    {
        var list = new List<Types.DmDbRdaSchemaUpdateStatusDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
